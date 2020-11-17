 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

#include "mmf2_module.h"
#include "audio_api.h"
#include "module_audio.h"
#include "avcodec.h"

//------------------------------------------------------------------------------

#define AUDIO_DMA_PAGE_NUM 2
#define AUDIO_DMA_PAGE_SIZE (320)	// 20ms: 160 samples, 16bit

#define TX_PAGE_SIZE 	AUDIO_DMA_PAGE_SIZE //64*N bytes, max: 4095. 128, 4032 
#define TX_PAGE_NUM 	AUDIO_DMA_PAGE_NUM
#define RX_PAGE_SIZE 	AUDIO_DMA_PAGE_SIZE //64*N bytes, max: 4095. 128, 4032
#define RX_PAGE_NUM 	AUDIO_DMA_PAGE_NUM

#define TX_CACHE_DEPTH	16


static uint8_t dma_txdata[TX_PAGE_SIZE*TX_PAGE_NUM]__attribute__ ((aligned (0x20))); 
static uint8_t dma_rxdata[RX_PAGE_SIZE*RX_PAGE_NUM]__attribute__ ((aligned (0x20))); 

#define AUDIO_TX_PCM_QUEUE_LENGTH (20)

typedef struct pcm_tx_cache_s{
	xQueueHandle queue;
	uint16_t idx;
	uint8_t  buffer[AUDIO_DMA_PAGE_SIZE];	// for sw output cache handler
	uint8_t  txbuf[AUDIO_DMA_PAGE_SIZE];	// for interrupt 
}pcm_tx_cache_t;

static pcm_tx_cache_t	*pcm_tx_cache = NULL;


#define LOGIC_INPUT_NUM	4
static int logic_input_num = 1;		// for non-mix mode

#if LOGIC_INPUT_NUM==2
#warning ****VERY IMPORTANT : AUDIO must connect to MIMO/MISO INPUT 0 and 1 ****
// TODO : remove this limitation
#endif

#if LOGIC_INPUT_NUM!=4 && LOGIC_INPUT_NUM!=2
#error ONLY SUPPORT 4 and 2
#endif
//-------------AEC interrupt handler ------------------------------------------
#if ENABLE_SPEEX_AEC==1

static uint8_t last_tx_buf[AUDIO_DMA_PAGE_SIZE];
static uint8_t last_rx_buf[AUDIO_DMA_PAGE_SIZE];

int last_tx_ts, proc_tx_ts;
int last_rx_ts, proc_rx_ts;

static uint8_t proc_tx_buf[AUDIO_DMA_PAGE_SIZE];
static uint8_t proc_rx_buf[AUDIO_DMA_PAGE_SIZE];

#define SPEEX_SAMPLE_RATE (8000)
#define AEC_LOOP	1
#define M 8
#define NN (AUDIO_DMA_PAGE_SIZE/2/AEC_LOOP)
#define TAIL_LENGTH_IN_MILISECONDS (20*M)
#define TAIL (TAIL_LENGTH_IN_MILISECONDS * (SPEEX_SAMPLE_RATE / 1000) )

#include "AEC.h"

#endif //ENABLE_SPEEX_AEC

#define CONFIG_MMF_AUDIO_DEBUG 1

#if defined(CONFIG_MMF_AUDIO_DEBUG)
#include <audio_debug.h>
int audio_tx_debug_cnt = 0x7fffffff;
int audio_rx_debug_cnt = 0x7fffffff;
int audio_rx_aec_cnt = 0x7fffffff;
int audio_rx_debug_mode = 0;
#endif

static void audio_tx_complete(uint32_t arg, uint8_t *pbuf)
{
	audio_ctx_t* ctx = (audio_ctx_t*)arg;
	audio_t *obj = (audio_t *)ctx->audio;
	uint8_t *ptx_buf;
	
#if ENABLE_SPEEX_AEC==1	
	last_tx_ts = xTaskGetTickCountFromISR();
	memcpy(last_tx_buf, pbuf, AUDIO_DMA_PAGE_SIZE);
#endif	
	ptx_buf = (uint8_t *)audio_get_tx_page_adr(obj);
#if LOGIC_INPUT_NUM==4 || LOGIC_INPUT_NUM==2
	if(ctx->params.mix_mode){
		for(int i=0;i<logic_input_num;i++){
			if ( xQueueReceiveFromISR(pcm_tx_cache[i].queue, pcm_tx_cache[i].txbuf, NULL) != pdPASS ) {
				memset(pcm_tx_cache[i].txbuf, 0, AUDIO_DMA_PAGE_SIZE);
			}
		}
		if(ctx->params.word_length == WL_16BIT){
			int16_t *ptx_tmp = (int16_t *)ptx_buf;
			int16_t *cache_txbuf0 = (int16_t *)pcm_tx_cache[0].txbuf;
			int16_t *cache_txbuf1 = (int16_t *)pcm_tx_cache[1].txbuf;
	#if LOGIC_INPUT_NUM==4
			int16_t *cache_txbuf2 = (int16_t *)pcm_tx_cache[2].txbuf;
			int16_t *cache_txbuf3 = (int16_t *)pcm_tx_cache[3].txbuf;
	#endif
			for(int i=0;i<AUDIO_DMA_PAGE_SIZE/2;i++){
				ptx_tmp[i] = cache_txbuf0[i]/LOGIC_INPUT_NUM+cache_txbuf1[i]/LOGIC_INPUT_NUM
	#if LOGIC_INPUT_NUM==4
					       + cache_txbuf2[i]/LOGIC_INPUT_NUM+cache_txbuf3[i]/LOGIC_INPUT_NUM
	#endif  
						   ;
			}
		}else{
			for(int i=0;i<AUDIO_DMA_PAGE_SIZE;i++){
				ptx_buf[i] = (int8_t)pcm_tx_cache[0].txbuf[i]/LOGIC_INPUT_NUM+(int8_t)pcm_tx_cache[1].txbuf[i]/LOGIC_INPUT_NUM
	#if LOGIC_INPUT_NUM==4	
					       + (int8_t)pcm_tx_cache[2].txbuf[i]/LOGIC_INPUT_NUM+(int8_t)pcm_tx_cache[3].txbuf[i]/LOGIC_INPUT_NUM
	#endif
						   ;
			}
		}
	}else
#endif
	{
		if ( xQueueReceiveFromISR(pcm_tx_cache[0].queue, ptx_buf, NULL) != pdPASS ) {
			memset(ptx_buf, 0, AUDIO_DMA_PAGE_SIZE);
		}
	}
	
#if defined(AUDIO_DEBUG_H)
	if(audio_tx_debug_ena==1)
	{
		printf("start tx playback debug\n\r");
		audio_tx_debug_cnt = 0;
		audio_tx_debug_ena = 0;
	}
	
	if(audio_tx_debug_cnt < audio_tx_debug_len )
	{
		memcpy(ptx_buf, &audio_tx_debug_buffer[audio_tx_debug_cnt], AUDIO_DMA_PAGE_SIZE);
		audio_tx_debug_cnt += AUDIO_DMA_PAGE_SIZE;
		if(audio_tx_debug_cnt >= audio_tx_debug_len)
			printf("done for tx playback debug\n\r");
		
	}
#endif
	
	//if ( xQueueReceiveFromISR(audio_tx_pcm_queue, ptx_buf, NULL) != pdPASS ) {
	//    memset(ptx_buf, 0, AUDIO_DMA_PAGE_SIZE);
	//}
	audio_set_tx_page(obj, (uint8_t *)ptx_buf);
}

static void audio_rx_complete(uint32_t arg, uint8_t *pbuf)
{
	audio_ctx_t* ctx = (audio_ctx_t*)arg;
	audio_t *obj = (audio_t *)ctx->audio;
	uint32_t audio_rx_ts = xTaskGetTickCountFromISR();
	// set timestamp to 1st sample
	audio_rx_ts -= 1000 * (AUDIO_DMA_PAGE_SIZE/ctx->word_length) / ctx->sample_rate;
	
#if AUDIO_LOOPBACK
	uint8_t *ptx_addre;
	ptx_addre = audio_get_tx_page_adr(obj);
	memcpy((void*)ptx_addre, (void*)pbuf, TX_PAGE_SIZE);
	audio_set_tx_page(obj, ptx_addre);
#endif

	
#if ENABLE_SPEEX_AEC==1
	if(ctx->params.enable_aec){
		last_rx_ts = xTaskGetTickCountFromISR();
		memcpy(last_rx_buf, pbuf, AUDIO_DMA_PAGE_SIZE);
		if(ctx->aec_rx_done_sema)
			xSemaphoreGiveFromISR(ctx->aec_rx_done_sema, NULL);
		
	}else
#endif
	{
		BaseType_t xTaskWokenByReceive = pdFALSE;
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		
		mm_context_t *mctx = (mm_context_t*)ctx->parent;
		mm_queue_item_t* output_item;
		if(mctx->output_recycle && (xQueueReceiveFromISR(mctx->output_recycle, &output_item, &xTaskWokenByReceive) == pdTRUE)){
			
			memcpy((void*)output_item->data_addr,(void*)pbuf, RX_PAGE_SIZE);
			output_item->size = RX_PAGE_SIZE;
			output_item->timestamp = audio_rx_ts;
			output_item->type = AV_CODEC_ID_PCM_RAW;
			
			xQueueSendFromISR(mctx->output_ready, (void*)&output_item, &xHigherPriorityTaskWoken);		
		}
		audio_set_rx_page(obj);
		
		if( xHigherPriorityTaskWoken || xTaskWokenByReceive)
			taskYIELD ();
	}
}

#if ENABLE_SPEEX_AEC==1	
static void audio_rx_handle_thread(void *param)
{
	audio_ctx_t* ctx = (audio_ctx_t*)param;
	mm_context_t *mctx = (mm_context_t*)ctx->parent;
	mm_queue_item_t* output_item;
	
	audio_t *obj = (audio_t *)ctx->audio;

	int sampleRate = SPEEX_SAMPLE_RATE;

	AEC_init(NN, sampleRate, WEBRTC_AECM, TAIL, 1, 18, 0, 1, 1.0f);
		
	while (1) {
		xSemaphoreTake(ctx->aec_rx_done_sema, portMAX_DELAY);
		
		uint32_t audio_rx_ts = xTaskGetTickCountFromISR();
		
		if(!mctx->output_recycle || (xQueueReceive(mctx->output_recycle, &output_item, 0xFFFFFFFF) != pdTRUE)){
			// drop current frame
			// NOT SEND
			audio_set_rx_page(obj);
			continue;
		}

		// last tx rx buffer may be corrupted by interrupt, backup processing data first
		proc_tx_ts = last_tx_ts;
		proc_rx_ts = last_rx_ts;
		
		memcpy(proc_tx_buf, last_tx_buf, AUDIO_DMA_PAGE_SIZE);
		memcpy(proc_rx_buf, last_rx_buf, AUDIO_DMA_PAGE_SIZE);
		
#if defined(AUDIO_DEBUG_H)	
	if(audio_rx_debug_ena!=0)
	{
                #if defined(AUDIO_DEBUG_ENABLE)
		printf("start rx recording\n\r");
                #endif
		audio_rx_debug_cnt = 0;
		audio_rx_debug_ena = 0;
	}
	
	if(audio_rx_debug_cnt < audio_rx_debug_len )
	{
		memcpy(&audio_rx_debug_buffer[audio_rx_debug_cnt], last_rx_buf, AUDIO_DMA_PAGE_SIZE);
		audio_rx_debug_cnt += AUDIO_DMA_PAGE_SIZE;
		if(audio_rx_debug_cnt >= audio_rx_debug_len ){
                        #if defined(AUDIO_DEBUG_ENABLE)
			printf("done for rx (mic) recording\n\r");
                        #endif
                }
	}
#endif			
		
		int aec_proc_time = xTaskGetTickCount();
		AEC_process((int16_t *)(proc_tx_buf), (int16_t *)(proc_rx_buf), (int16_t *)output_item->data_addr);
		
		aec_proc_time = xTaskGetTickCount() - aec_proc_time;
		if(aec_proc_time > 20){
                        #if defined(AUDIO_DEBUG_ENABLE)
			printf("AEC proc execution too long %dms\n\r", aec_proc_time);
                        #endif
		}

#if defined(AUDIO_DEBUG_H)	
		if(audio_rx_aec_ena!=0)
		{
			printf("start rx aec recording\n\r");
			audio_rx_aec_cnt = 0;
			audio_rx_aec_ena = 0;
		}
		
		if(audio_rx_aec_cnt < audio_rx_aec_len )
		{
			memcpy(&audio_rx_aec_buffer[audio_rx_aec_cnt], (void*)output_item->data_addr, AUDIO_DMA_PAGE_SIZE);
			audio_rx_aec_cnt += AUDIO_DMA_PAGE_SIZE;
			if(audio_rx_aec_cnt >= audio_rx_aec_len ){
                          #if defined(AUDIO_DEBUG_ENABLE)
				printf("done for rx (aec) recording\n\r");
                          #endif      
                        }
		}
#endif	
		
		if(proc_tx_ts != last_tx_ts){
                        #if defined(AUDIO_DEBUG_ENABLE)
			printf("TX buffer update when AEC processing\n\r");
                        #endif
			if(last_tx_ts - proc_tx_ts > 20){
                                #if defined(AUDIO_DEBUG_ENABLE)
				printf("last_tx_ts, proc_tx_ts diff %d > 20ms\n\r", last_tx_ts-proc_tx_ts);
                                #endif
			}
		}
		
		if(proc_rx_ts != last_rx_ts){
                        #if defined(AUDIO_DEBUG_ENABLE)
			printf("RX buffer update when AEC processing\n\r");
                        #endif
			if(last_rx_ts - proc_rx_ts > 20){
                                #if defined(AUDIO_DEBUG_ENABLE)
				printf("last_rx_ts, proc_rx_ts diff %d > 20ms\n\r", last_rx_ts-proc_rx_ts);
                                #endif
			}			
		}

		output_item->size = RX_PAGE_SIZE;
		output_item->timestamp = audio_rx_ts;
		output_item->type = AV_CODEC_ID_PCM_RAW;
		
		xQueueSend(mctx->output_ready, (void*)&output_item, 0xFFFFFFFF);
		
		audio_set_rx_page(obj);
	}
}
#endif

int audio_control(void *p, int cmd, int arg)
{
	audio_ctx_t* ctx = (audio_ctx_t*)p;
	int sample_rate = 8000;
	
	switch(cmd){
        case CMD_AUDIO_SET_AUDIO_STOP:
                audio_trx_stop(ctx->audio);
                break;
        case CMD_AUDIO_SET_AUDIO_START:
                audio_trx_start(ctx->audio);
                break;
        case CMD_AUDIO_SET_ADC_GAIN:
                audio_adc_digital_vol(ctx->audio,arg);
                break;
        case CMD_AUDIO_SET_DAC_GAIN:
                audio_dac_digital_vol(ctx->audio,arg);
                break;
	case CMD_AUDIO_SET_PARAMS:
		memcpy(&ctx->params, (void*)arg, sizeof(audio_params_t));
                printf("sample rate = %d\r\n",ctx->params.sample_rate);
		break;
	case CMD_AUDIO_GET_PARAMS:
		memcpy((void*)arg, &ctx->params, sizeof(audio_params_t));
		break;
	case CMD_AUDIO_SET_AEC_ENABLE:
#if ENABLE_SPEEX_AEC==1	
		printf("AEC Enable: %d.\r\n", arg);
		if(arg != 0)
			ctx->params.enable_aec = 1;
		else
			ctx->params.enable_aec = 0;
#endif
		break;
	case CMD_AUDIO_SET_SAMPLERATE:
			ctx->params.sample_rate = arg;
			break;
	case CMD_AUDIO_SET_RESET:
#if ENABLE_SPEEX_AEC==1	
			if(ctx->params.sample_rate==ASR_8KHZ || ctx->params.sample_rate==ASR_16KHZ)
			{
				if(ctx->params.sample_rate==ASR_8KHZ)
					sample_rate = 8000;
				else if(ctx->params.sample_rate==ASR_16KHZ)
					sample_rate = 16000;
				NS_destory();
				AGC_destory();
				AEC_destory();

				AEC_init(NN, sample_rate, WEBRTC_AECM, TAIL, 1, 18, 0, 1, 1.0f);
				NS_init(sample_rate, 1);
				AGC_init(sample_rate, 1, 24, 0);
			}
#endif

			audio_tx_stop(ctx->audio);
			audio_rx_stop(ctx->audio);
			audio_deinit(ctx->audio);
			audio_init(ctx->audio, OUTPUT_SINGLE_EDNED, MIC_SINGLE_EDNED, AUDIO_CODEC_2p8V); //LINE_IN_MODE//MIC_DIFFERENTIAL, OUTPUT_SINGLE_EDNED, OUTPUT_CAPLESS, OUTPUT_DIFFERENTIAL

			//audio_mic_analog_gain(ctx->audio, 1, AUDIO_MIC_40DB);
			//audio_adc_digital_vol(ctx->audio, 0x7F);
			audio_dac_digital_vol(ctx->audio, 0xAF);
			//audio_headphone_analog_mute(ctx->audio, 1);
			
			//Init RX dma
			audio_set_rx_dma_buffer(ctx->audio, dma_rxdata, RX_PAGE_SIZE);
			audio_rx_irq_handler(ctx->audio, audio_rx_complete,(uint32_t)ctx);
			
			//Init TX dma
			audio_set_tx_dma_buffer(ctx->audio, dma_txdata, TX_PAGE_SIZE);
			audio_tx_irq_handler(ctx->audio, audio_tx_complete,(uint32_t)ctx);
			
			audio_set_param(ctx->audio, ctx->params.sample_rate, ctx->params.word_length);  // ASR_8KHZ, ASR_16KHZ //ASR_48KHZ
			printf("sample rate = %d\r\n",ctx->params.sample_rate);
	audio_mic_analog_gain(ctx->audio, 1, ctx->params.mic_gain); // default 0DB	
	audio_trx_start(ctx->audio);
			printf("audio_reset\r\n");
			break;
	case CMD_AUDIO_APPLY:
#if ENABLE_SPEEX_AEC==1	
		if (ctx->params.sample_rate != ASR_8KHZ && ctx->params.sample_rate != ASR_16KHZ){
			printf("\r\n aec error : sample rate should be 8KHz if enable AEC \n\r");
			goto audio_control_fail;
		}
		if(ctx->params.enable_aec){
			ctx->aec_rx_done_sema = xSemaphoreCreateBinary();
			if(!ctx->aec_rx_done_sema)
				goto audio_control_fail;
			if(xTaskCreate(audio_rx_handle_thread, ((const char*)"audio_rx"), 4096 + 2048, (void*)ctx, tskIDLE_PRIORITY + 1, &ctx->aec_rx_task) != pdPASS) {
				rt_printf("\r\n audio_rx_handle_thread: Create Task Error\n");
				goto audio_control_fail;
			}
		}
		
		NS_init(SPEEX_SAMPLE_RATE, 1);
		AGC_init(SPEEX_SAMPLE_RATE, 1, 24, 0);
#endif		
		// mix mode --> LOGIC_INPUT_NUM input, non-mix mode 1 input
		if(ctx->params.mix_mode) logic_input_num = LOGIC_INPUT_NUM;
		pcm_tx_cache = malloc(logic_input_num*sizeof(pcm_tx_cache_t));
		if(!pcm_tx_cache){
			rt_printf("\r\n pcm tx cache: Create Error\n");
			goto audio_control_fail;
		}
		memset(pcm_tx_cache, 0, logic_input_num*sizeof(pcm_tx_cache_t));
		for(int i=0;i<logic_input_num;i++){
			memset(pcm_tx_cache[i].txbuf, 0x80, AUDIO_DMA_PAGE_SIZE);	// set to audio level 0;
			pcm_tx_cache[i].queue = xQueueCreate(AUDIO_TX_PCM_QUEUE_LENGTH, AUDIO_DMA_PAGE_SIZE);
			if(!pcm_tx_cache[i].queue)
				goto audio_control_fail;
		}
		
		if (ctx->params.sample_rate == ASR_8KHZ)
			ctx->sample_rate = 8000;
		else if (ctx->params.sample_rate == AUDIO_SR_16KHZ)
			ctx->sample_rate = 16000;
		else if (ctx->params.sample_rate == AUDIO_SR_32KHZ)
			ctx->sample_rate = 32000;
		else if (ctx->params.sample_rate == AUDIO_SR_44p1KHZ)
			ctx->sample_rate = 44100;
		else if (ctx->params.sample_rate == AUDIO_SR_48KHZ)
			ctx->sample_rate = 48000;
		else if (ctx->params.sample_rate == AUDIO_SR_88p2KHZ)
			ctx->sample_rate = 88200;
		else if (ctx->params.sample_rate == AUDIO_SR_96KHZ)
			ctx->sample_rate = 96000;
		
		if (ctx->params.word_length == WL_8BIT)
			ctx->word_length = 1;
		else if (ctx->params.word_length == WL_16BIT)
			ctx->word_length = 2;
		else if (ctx->params.word_length == WL_24BIT)
			ctx->word_length = 3;
		printf("sample rate = %d\r\n",ctx->params.sample_rate);
		audio_set_param(ctx->audio, ctx->params.sample_rate, ctx->params.word_length);  // ASR_8KHZ, ASR_16KHZ //ASR_48KHZ
		audio_mic_analog_gain(ctx->audio, 1, ctx->params.mic_gain); // default 0DB	
		audio_trx_start(ctx->audio);
		//audio_set_tx_page(ctx->audio, audio_get_tx_page_adr(ctx->audio));
		break;
	}
	return 0;
audio_control_fail:
	mm_printf("audio_control fail\n\r");
	if(ctx->aec_rx_done_sema){
		vSemaphoreDelete(ctx->aec_rx_done_sema);
		ctx->aec_rx_done_sema = NULL;
	}
	
	if(ctx->aec_rx_task){
		vTaskDelete(ctx->aec_rx_task);
		ctx->aec_rx_task = NULL;
	}
	
	if(pcm_tx_cache){
		for(int i=0;i<logic_input_num;i++)
			if(pcm_tx_cache[i].queue) vQueueDelete(pcm_tx_cache[i].queue);
		free(pcm_tx_cache);
	}
	
	return -1;
}

int module_audio_ns = 1;
int module_audio_agc = 1;
int audio_handle(void* p, void* input, void* output)
{
	//audio_ctx_t* ctx = (audio_ctx_t*)p;
	mm_queue_item_t* input_item = (mm_queue_item_t*)input;
	
	uint8_t* input_data = (uint8_t*)input_item->data_addr;
	
	(void)output;
	
	int cache_idx = input_item->in_idx > (logic_input_num-1)? 0 : input_item->in_idx;
	pcm_tx_cache_t *cache = &pcm_tx_cache[cache_idx];
	
	if(module_audio_ns)
		NS_process(input_item->size/2, (int16_t*)input_data);
	if(module_audio_agc)
		AGC_process(input_item->size/2, (int16_t*)input_data);
	
	for (int i=0; i<input_item->size; i++) {
		cache->buffer[cache->idx++] = input_data[i];
		if (cache->idx == AUDIO_DMA_PAGE_SIZE) {
			//if (xQueueSend(audio_tx_pcm_queue, pcm_tx_cache, 1000) != pdTRUE) {
			if (xQueueSend(cache->queue, cache->buffer, 1000) != pdTRUE) {
				printf("fail to send tx queue\r\n");
			}
			cache->idx = 0;
		}
	}
	
	//
	return 0;
}

void* audio_destroy(void* p)
{
	audio_ctx_t* ctx = (audio_ctx_t*)p;
	
	if(pcm_tx_cache){
		for(int i=0;i<logic_input_num;i++)
			if(pcm_tx_cache[i].queue) vQueueDelete(pcm_tx_cache[i].queue);
		free(pcm_tx_cache);
	}
	//if(pcm_tx_cache) free(pcm_tx_cache);
	//if(audio_tx_pcm_queue) vQueueDelete(audio_tx_pcm_queue);
	
	if(ctx && ctx->aec_rx_done_sema) vSemaphoreDelete(ctx->aec_rx_done_sema);
	if(ctx && ctx->aec_rx_task) vTaskDelete(ctx->aec_rx_task);
	if(ctx && ctx->audio) free(ctx->audio);
	if(ctx) free(ctx);
	
#if ENABLE_SPEEX_AEC==1
	NS_destory();
	AGC_destory();
#endif
	
	return NULL;
}

void* audio_create(void* parent)
{
	audio_ctx_t *ctx = malloc(sizeof(audio_ctx_t));
	if(!ctx) return NULL;
	
	ctx->parent = parent;
	
	ctx->audio = malloc(sizeof(audio_t));
	if(!ctx->audio)	goto audio_create_fail;
	memset(ctx->audio, 0, sizeof(audio_t));
	
#if ENABLE_SPEEX_AEC==1	
	memset(last_tx_buf, 0, AUDIO_DMA_PAGE_SIZE);	//MIC_SINGLE_EDNED
#endif	
	//audio_init(ctx->audio, OUTPUT_SINGLE_EDNED, MIC_DIFFERENTIAL, AUDIO_CODEC_2p8V); //LINE_IN_MODE//MIC_DIFFERENTIAL, OUTPUT_SINGLE_EDNED, OUTPUT_CAPLESS, OUTPUT_DIFFERENTIAL
	audio_init(ctx->audio, OUTPUT_SINGLE_EDNED, MIC_SINGLE_EDNED, AUDIO_CODEC_2p8V); //LINE_IN_MODE//MIC_DIFFERENTIAL, OUTPUT_SINGLE_EDNED, OUTPUT_CAPLESS, OUTPUT_DIFFERENTIAL
	
	//audio_mic_analog_gain(ctx->audio, 1, AUDIO_MIC_40DB);
	//audio_adc_digital_vol(ctx->audio, 0x7F);
	audio_dac_digital_vol(ctx->audio, 0xAF);
	//audio_headphone_analog_mute(ctx->audio, 1);
	
	//Init RX dma
	audio_set_rx_dma_buffer(ctx->audio, dma_rxdata, RX_PAGE_SIZE);
	audio_rx_irq_handler(ctx->audio, audio_rx_complete,(uint32_t)ctx);
	
	//Init TX dma
	audio_set_tx_dma_buffer(ctx->audio, dma_txdata, TX_PAGE_SIZE);
	audio_tx_irq_handler(ctx->audio, audio_tx_complete,(uint32_t)ctx);	
	
	// Init TX Cache Queue
	//audio_tx_pcm_queue = xQueueCreate(AUDIO_TX_PCM_QUEUE_LENGTH, AUDIO_DMA_PAGE_SIZE);
	//if(!audio_tx_pcm_queue)
	//	goto audio_create_fail;
	
	return ctx;
	
audio_create_fail:
	
	audio_destroy((void*)ctx);
	return NULL;
}

void* audio_new_item(void *p)
{
	//audio_ctx_t* ctx = (audio_ctx_t*)p;
	// get parameter
	
	return malloc(AUDIO_DMA_PAGE_SIZE);
}

void* audio_del_item(void *p, void *d)
{
	if(d) free(d);
	return NULL;
}

mm_module_t audio_module = {
	.create = audio_create,
	.destroy = audio_destroy,
	.control = audio_control,
	.handle = audio_handle,
	
	.new_item = audio_new_item,
	.del_item = audio_del_item,
	
	.output_type = MM_TYPE_ADSP|MM_TYPE_ASINK,     // no output
	.module_type = MM_TYPE_ASRC|MM_TYPE_ASINK,
	.name = "AUDIO"
};
