#include <section_config.h>
#include <osdep_service.h>
#include <skbuff.h>
#ifdef CONFIG_PLATFORM_8195BHP  //Ameba Pro Config setting
#define MAX_SKB_BUF_SIZE     1666	// should >= the size in wlan driver
#define MAX_SKB_BUF_NUM      96         // Please modify here
#define MAX_LOCAL_SKB_NUM    (MAX_SKB_BUF_NUM + 2)
#define SKBUF_IN_DRAM 1
#else
#define MAX_SKB_BUF_SIZE     1650	// should >= the size in wlan driver
#define MAX_SKB_BUF_NUM      8
#define MAX_LOCAL_SKB_NUM    (MAX_SKB_BUF_NUM + 2)
#endif

/* DO NOT modify skb_buf and skb_data structure */
struct skb_buf {
	struct list_head list;
	struct sk_buff skb;
};

struct skb_data {
	struct list_head list;
	unsigned char buf[MAX_SKB_BUF_SIZE];
	atomic_t ref;
};

unsigned int nr_xmitframe = MAX_SKB_BUF_NUM;
unsigned int nr_xmitbuff = MAX_SKB_BUF_NUM;
#ifdef CONFIG_PLATFORM_8195BHP 
#if (MAX_SKB_BUF_NUM >=128)
int tx_beq_desc_num = 128;
#else
int tx_beq_desc_num = MAX_SKB_BUF_NUM;
#endif
#endif
int max_local_skb_num = MAX_LOCAL_SKB_NUM;
int max_skb_buf_num = MAX_SKB_BUF_NUM;

/* DO NOT access skb_pool and skb_data_pool out of wlan driver */
struct skb_buf skb_pool[MAX_LOCAL_SKB_NUM];

#define SKB_DATA_POOL_USING_GLOBAL_BUF	1
#if SKB_DATA_POOL_USING_GLOBAL_BUF
#ifdef  CONFIG_PLATFORM_8195BHP
#if (SKBUF_IN_DRAM == 1)  //If the sram is not enough, it need to put the buffer to DRAM
	SECTION(".eram.bss")
#endif
struct skb_data skb_data_pool[MAX_SKB_BUF_NUM] __attribute__ ((aligned (0x20)));
#else
// SRAM_BD_DATA_SECTION default in SRAM. Can modify image2.icf to link to the end of SDRAM
SRAM_BD_DATA_SECTION
struct skb_data skb_data_pool[MAX_SKB_BUF_NUM];
#endif
void skb_data_size_check(int size)
{
	if(size != MAX_SKB_BUF_SIZE){
		printf("\n\rAssert(%d == %d) failed on line %d in file %s", size, MAX_SKB_BUF_SIZE, __LINE__, __FILE__);
		HALT();
	}
}
#else
#ifdef  CONFIG_PLATFORM_8195BHP
SECTION(".eram.bss")
struct skb_data * skb_data_pool;
#else
// Change to use heap (malloc) to save SRAM memory
SRAM_BD_DATA_SECTION
struct skb_data * skb_data_pool;
#endif
extern struct list_head skbdata_list;
extern int skbdata_used_num;
extern int max_skbdata_used_num;
void init_skb_data_pool(void)
{
	int i;

	skb_data_size_check(MAX_SKB_BUF_SIZE);
	//printf("\ninit_skb_data_pool\n");
	skb_data_pool = (struct skb_data *)rtw_zmalloc(max_skb_buf_num * sizeof(struct skb_data));
	if(!skb_data_pool){
		printf("\nskb_data_pool alloc fail\n");
		return;
	}
	
	memset(skb_data_pool, '\0', max_skb_buf_num*sizeof(struct skb_data));
	INIT_LIST_HEAD(&skbdata_list);
	
	for (i=0; i<max_skb_buf_num; i++) {
		INIT_LIST_HEAD(&skb_data_pool[i].list);
		list_add_tail(&skb_data_pool[i].list, &skbdata_list);
	}
	skbdata_used_num = 0;	
	max_skbdata_used_num = 0;
}

void deinit_skb_data_pool(void)
{
	//printf("\ndeinit_skb_data_pool\n");
	rtw_mfree((void*)skb_data_pool, MAX_SKB_BUF_NUM * sizeof(struct skb_data));
}
#endif