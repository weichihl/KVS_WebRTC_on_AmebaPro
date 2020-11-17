#include <stdint.h>
#include <stdlib.h>
#include "rtl8195bhp.h"
#include "tm9_cp3.h"
#include "diag.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hal_timer.h"

#if configUSE_TICKLESS_IDLE==1
	#error not support when configUSE_TICKLESS_IDLE=1, please set to 0 in FreeRTOSConfig.h
#endif

//
struct mtype0{
	int event_id[2];
	int val_curr[2];
	long long val_acc[2];	
};

struct mtype1{
	int event_id;
	int resv0;
	int val_curr;
	int resv1;
	long long val_acc;
	long long tick_acc;
};


struct measure_item{
	int mid;
	int in_use;
	int type;
	char unit;		// p(ppm), %, K, M, G
	union{
		struct mtype0 type0;
		struct mtype1 type1;
	}m;
};

#define MAX_MEASURE_ITEMS	4
struct measure_item m_items[MAX_MEASURE_ITEMS];

#define M_ONECOUNTER		0x00
#define M_FETCH_INST		(M_ONECOUNTER+1)
#define M_CYCLE				(M_ONECOUNTER+2)
#define M_COMP_INST			(M_ONECOUNTER+3)
#define M_COMP_AXI_READ		(M_ONECOUNTER+4)
#define M_COMP_AXI_WRITE	(M_ONECOUNTER+5)

#define M_TWOCOUNTER		0x80
#define M_CPI				(M_TWOCOUNTER+1)
#define M_DCACHE_MISS_RATE	(M_TWOCOUNTER+2)
#define M_ICACHE_MISS_RATE	(M_TWOCOUNTER+3)
#define M_BRANCH_PRED_MISS_RATE 	(M_TWOCOUNTER+4)

/**
  \brief   init meausre
  \details init measure by cleaning m_items content
  \param[in]   void
 
  \return      void
*/
void measure_init(void)
{
#if configUSE_TICKLESS_IDLE==1
	rt_printf("measure_init: not support tickless\n\r");
#else
	memset(m_items, 0, sizeof(m_items));
#endif
}

/**
  \brief   add meausre
  \details add measure to m_items record
  \param[in]   mid     measure id
 
  \return      m_items index or -1(error)
*/
int measure_add(int mid)
{
#if configUSE_TICKLESS_IDLE==1
	rt_printf("measure_init: not support tickless\n\r");
#else	
	for(int i=0;i<MAX_MEASURE_ITEMS;i++){
		if(m_items[i].in_use == 0){
			m_items[i].in_use = 1;
			m_items[i].mid = mid;
			return i;
		}
	}
#endif	
	return -1;
}


/**
  \brief   delete meausre
  \details delete measure from m_items record
  \param[in]   mid     measure id

  \return      m_items index or -1(error)
*/
int measure_del(int mid)
{
#if configUSE_TICKLESS_IDLE==1
	rt_printf("measure_init: not support tickless\n\r");
#else	
	for(int i=0;i<MAX_MEASURE_ITEMS;i++){
		if(m_items[i].mid == mid){
			m_items[i].in_use = 0;
			m_items[i].mid = 0;
			return i;
		}
	}
#endif	
	return -1;
}

static hal_timer_adapter_t m_timer_adp;

void m_timer_handler(void *dummy)
{
#if configUSE_TICKLESS_IDLE==1
	rt_printf("measure_init: not support tickless\n\r");
#else		
	for(int i=0;i<MAX_MEASURE_ITEMS;i++){
		if(m_items[i].in_use == 1){
			if(m_items[i].type==0){
				m_items[i].m.type0.val_curr[0] = CP3_ReadAndClean_Counter(m_items[i].m.type0.event_id[0]);
				m_items[i].m.type0.val_curr[1] = CP3_ReadAndClean_Counter(m_items[i].m.type0.event_id[1]);
				
				m_items[i].m.type0.val_acc[0] += m_items[i].m.type0.val_curr[0];
				m_items[i].m.type0.val_acc[1] += m_items[i].m.type0.val_curr[1];
			}else{
				m_items[i].m.type1.val_curr = CP3_ReadAndClean_Counter(m_items[i].m.type1.event_id);
				m_items[i].m.type1.val_acc += m_items[i].m.type1.val_curr;
				m_items[i].m.type1.tick_acc += 50; // ms
			}
		}	
	}
#endif	
}

/**
  \brief   measure start
  \details handle measure id and add corrospond event id to CP3
  
  \return      void
*/
void measure_start(void)
{
#if configUSE_TICKLESS_IDLE==1
	rt_printf("measure_init: not support tickless\n\r");
#else		
	int event_id[8] ={0};
	int eidx = 0;

	// register 1sec timer interrupt handler to do regular update
	timer_id_t free_id = hal_timer_allocate(NULL);
	if (free_id >= MaxGTimerNum) {
        rt_printf ("fail to get a free timer\n");
        return;
    }

    int ret = hal_timer_init (&m_timer_adp, free_id);
    if (ret != HAL_OK) {
        rt_printf ("timer init fail %d", ret);
    }
	hal_timer_start_periodical (&m_timer_adp, 50*1000, (timer_callback_t) m_timer_handler, (void *)NULL);
	
	for(int i=0;i<MAX_MEASURE_ITEMS;i++){
		switch(m_items[i].mid){
		case M_CYCLE:
			m_items[i].type = 1;
			m_items[i].m.type1.event_id = eidx;
			event_id[eidx++] = 0x02;	// cycle
			break;
		case M_FETCH_INST:
			m_items[i].type = 1;
			m_items[i].m.type1.event_id = eidx;
			event_id[eidx++] = 0x01;	// fetch inst
			break;
		case M_COMP_INST:
			m_items[i].type = 1;
			m_items[i].m.type1.event_id = eidx;
			event_id[eidx++] = 0x03;	// comp inst
			break;
		case M_COMP_AXI_READ:
			m_items[i].type = 1;
			m_items[i].m.type1.event_id = eidx;
			event_id[eidx++] = 0x66;	// axi read
			break;
		case M_COMP_AXI_WRITE:
			m_items[i].type = 1;
			m_items[i].m.type1.event_id = eidx;
			event_id[eidx++] = 0x67;	// axi write
			break;
		case M_CPI:
			m_items[i].type = 0;
			m_items[i].m.type0.event_id[0] = eidx;
			event_id[eidx++] = 0x02;	// cycle
			m_items[i].m.type0.event_id[1] = eidx;
			event_id[eidx++] = 0x03;	// complete instruction
			break;
		case M_DCACHE_MISS_RATE:
			m_items[i].type = 0;
			m_items[i].m.type0.event_id[0] = eidx;
			event_id[eidx++] = 0x34;	// dcache miss
			m_items[i].m.type0.event_id[1] = eidx;
			event_id[eidx++] = 0x33;	// dcache hit
			break;
		case M_ICACHE_MISS_RATE:
			m_items[i].type = 0;
			m_items[i].m.type0.event_id[0] = eidx;
			event_id[eidx++] = 0x31;	// icache miss
			m_items[i].m.type0.event_id[1] = eidx;
			event_id[eidx++] = 0x30;	// icache hit
			break;
		case M_BRANCH_PRED_MISS_RATE:
			m_items[i].type = 0;
			m_items[i].m.type0.event_id[0] = eidx;
			event_id[eidx++] = 0x17;	// branch prediction miss
			m_items[i].m.type0.event_id[1] = eidx;
			event_id[eidx++] = 0x16;	// all branch
			break;	
		}
		
		if(eidx >= 8){
			rt_printf("Reach max cp3 counter limit\n\r");
			break;
		}
	}
	
	CP3_Set_Counter_Dual_Mode(0xf);
	CP3_Set_Lo_Counter(event_id[0], event_id[2], event_id[4], event_id[6]);
	CP3_Set_High_Counter(event_id[1], event_id[3], event_id[5], event_id[7]);
	CP3_Enable_Counter();
#endif	
}

/**
  \brief   measure stop
  \details stop CP3 counter and remove timer

  \return      void
*/
void measure_stop(void)
{
#if configUSE_TICKLESS_IDLE==1
	rt_printf("measure_init: not support tickless\n\r");
#else		
	hal_timer_deinit (&m_timer_adp);
	CP3_Disable_Counter();
#endif	
}

/**
  \brief   get measure data
  \details get measure data and calculating from m_items value
  \param[in]   mid     measure id
  \param[in]   *curr   counting per second(instant value), float type, for type0 it is curr[0]/curr[1], for type1 it is curr*20(50ms sampling)
  \param[in]   *acc    counting per second(long term value), float type, for type0 it is acc[0]/acc[1], for type1 it is acc*1000/tick(ms)

  \return      void
*/
void measure_get(int mid, float *curr, float *acc)
{
#if configUSE_TICKLESS_IDLE==1
	rt_printf("measure_init: not support tickless\n\r");
#else		
	for(int i=0;i<MAX_MEASURE_ITEMS;i++){
		if(m_items[i].mid == mid){
			if(m_items[i].type==0){
				*curr = (float)m_items[i].m.type0.val_curr[0]/(float)m_items[i].m.type0.val_curr[1];
				*acc = (float)m_items[i].m.type0.val_acc[0]/(float)m_items[i].m.type0.val_acc[1];
			}else{
				*curr = (float)m_items[i].m.type1.val_curr*20;
				*acc = (float)m_items[i].m.type1.val_acc*1000/(float)m_items[i].m.type1.tick_acc;
			}
		}
	}
#endif	
}

/**
  \brief   get measure raw data
  \details get raw measure data from m_items
  \param[in]   mid     measure id
  \param[in]   *curr   should be two element array ex curr[2], function will fill curr[2] according to type
  \param[in]   *acc    should be two element array ex acc[2], function will fill acc[2] according to type

  \return      void
*/
void measure_get_raw(int mid, int *curr, long long *acc)
{
#if configUSE_TICKLESS_IDLE==1
	rt_printf("measure_init: not support tickless\n\r");
#else		
	for(int i=0;i<MAX_MEASURE_ITEMS;i++){
		if(m_items[i].mid == mid){
			if(m_items[i].type==0){
				curr[0] = m_items[i].m.type0.val_curr[0];
				curr[1] = m_items[i].m.type0.val_curr[1];
				acc[0] = m_items[i].m.type0.val_acc[0];
				acc[1] = m_items[i].m.type0.val_acc[1];
			}else{
				curr[0] = m_items[i].m.type1.val_curr;
				curr[1] = 0;
				acc[0] = m_items[i].m.type1.val_acc;
				acc[1] = m_items[i].m.type1.tick_acc;
			}
		}
	}
#endif	
}


/**
  \brief   clean measure count
  \details clean measure items's content and clean CP3 counter
  \param[in]   mid     measure id

  \return      void
*/
void measure_clean(int mid)
{
#if configUSE_TICKLESS_IDLE==1
	rt_printf("measure_init: not support tickless\n\r");
#else		
	for(int i=0;i<MAX_MEASURE_ITEMS;i++){
		if(m_items[i].mid == mid){
			if(m_items[i].type==0){
				m_items[i].m.type0.val_curr[0] = m_items[i].m.type0.val_curr[1] = 0;
				m_items[i].m.type0.val_acc[0] = m_items[i].m.type0.val_acc[1] = 0;
				CP3_Write_Counter(m_items[i].m.type0.event_id[0], 0);
				CP3_Write_Counter(m_items[i].m.type0.event_id[1], 0);
			}else{
				m_items[i].m.type1.val_curr = 0;
				m_items[i].m.type1.val_acc = m_items[i].m.type1.tick_acc = 0;
				CP3_Write_Counter(m_items[i].m.type1.event_id, 0);
			}			
		}
	}
#endif
}


// example usage
void measure_task(void* dummy)
{
	measure_init();
	measure_add(M_DCACHE_MISS_RATE);
	measure_add(M_ICACHE_MISS_RATE);
	measure_add(M_CPI);
	measure_add(M_BRANCH_PRED_MISS_RATE);
	//measure_add(M_FETCH_INST);
	measure_start();
	while(1){
		float curr, acc;
		
		vTaskDelay(5000);
		
		measure_get(M_DCACHE_MISS_RATE, &curr, &acc);
		rt_printf("DCMISS inst %f, acc %f\n\r", curr, acc);
		measure_get(M_ICACHE_MISS_RATE, &curr, &acc);
		rt_printf("ICMISS inst %f, acc %f\n\r", curr, acc);
		measure_get(M_CPI, &curr, &acc); 
		rt_printf("CPI inst %f, acc %f\n\r", curr, acc);
		measure_get(M_BRANCH_PRED_MISS_RATE, &curr, &acc); 
		rt_printf("BP MISS %f, acc %f\n\r", curr, acc);
	}
}

void measure_test(void)
{
	xTaskCreate(measure_task, "mtask", 512, NULL, 1, NULL);
}


