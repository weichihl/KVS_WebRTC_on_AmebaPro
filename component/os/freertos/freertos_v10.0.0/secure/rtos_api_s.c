#if !defined(__ICCARM__)
#include <arm_cmse.h>
#endif
//#include <stdio.h>
#include "rtos_api.h"

#define STACK_ID_IDX	2

extern void TZ_Set_Task_Name(int id, char* name);
extern char* TZ_Get_Task_Name(int id);

extern uint32_t ulSecureTaskAdd(TaskFunction_t pxTaskCode, void * Parameters);
extern void vSecureTaskSetNSHandle(uint32_t ulTaskId, TaskHandle_t pxHandle);
extern uint32_t ulSecureTaskGetIdByNSHandle(TaskHandle_t pxHandle);
extern void vSecureTaskDel(uint32_t ulTaskId);

rtos_func_ns rtos_ns;

uint32_t __attribute__((cmse_nonsecure_entry)) rtos_init (rtos_func_ns *rtos)
{
	memcpy(&rtos_ns, rtos, sizeof(rtos_func_ns));
	return 0;
}

//---------------------------------------------------------------------------------------
// RTOS wrapper
//---------------------------------------------------------------------------------------
BaseType_t xTaskCreate(	TaskFunction_t pxTaskCode,
						const char * const pcName,
						const uint16_t usSecureStackDepth,
						void * const pvParameters,
						UBaseType_t uxPriority,
						TaskHandle_t * const pxCreatedTask ) /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
{
	#if defined(__ICCARM__)	
	TaskHandle_t (__cmse_nonsecure_call *wrapper)( uint32_t ulTaskId, uint16_t usSecureStackDepth, UBaseType_t uxPriority);
	wrapper = ( TaskHandle_t (__cmse_nonsecure_call *)( uint32_t , uint16_t , UBaseType_t ) )rtos_ns.taskCreate;
	if(wrapper)
	#else
	TaskHandle_t __attribute__((cmse_nonsecure_call)) (*wrapper)( uint32_t ulTaskId, uint16_t usSecureStackDepth, UBaseType_t uxPriority);
	wrapper = cmse_nsfptr_create(rtos_ns.taskCreate);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
        uint32_t ulTaskId = ulSecureTaskAdd(pxTaskCode, pvParameters);
        if(ulTaskId == 0xFFFFFFFF)  return pdFAIL;
        
		TaskHandle_t createdTask = wrapper(ulTaskId, usSecureStackDepth, uxPriority);
		if(pxCreatedTask)
			*pxCreatedTask = createdTask;
		if(createdTask){
			// TODO: store secure domain task name
			uint32_t *tmp = (uint32_t*)createdTask;
			uint32_t sid = tmp[2];
			TZ_Set_Task_Name(sid, (char*)pcName);
			#if SET_NS_NAME
			//char* name = (char*)pcTaskGetName(createdTask);
			//strncpy(name, pcName, strlen("secure"));
			#endif
            vSecureTaskSetNSHandle(ulTaskId, createdTask);
			return pdTRUE;
		}
		else{
            vSecureTaskDel(ulTaskId);
            return pdFAIL;
        }
	}
	return pdFAIL;	
}

void vTaskDelete( TaskHandle_t xTaskToDelete )
{
	#if defined(__ICCARM__)	
	void (__cmse_nonsecure_call *wrapper)( TaskHandle_t xTaskToDelete );
	wrapper = ( void (__cmse_nonsecure_call *)( TaskHandle_t ) )rtos_ns.taskDelete;
	if(wrapper)
	#else
	void __attribute__((cmse_nonsecure_call)) (*wrapper)( TaskHandle_t xTaskToDelete );
	wrapper = cmse_nsfptr_create(rtos_ns.taskDelete);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
        uint32_t ulTaskId = ulSecureTaskGetIdByNSHandle(xTaskToDelete);
        if(ulTaskId != 0xFFFFFFFF)
            vSecureTaskDel(ulTaskId);
		wrapper(xTaskToDelete);
	}
}

void vTaskDelay(TickType_t xTicksToDelay)
{
	#if defined(__ICCARM__)	
	void (__cmse_nonsecure_call *wrapper)(TickType_t xTicksToDelay);
	wrapper = ( void (__cmse_nonsecure_call *)(TickType_t) )rtos_ns.taskDelay;
	if(wrapper)
	#else	
	void __attribute__((cmse_nonsecure_call)) (*wrapper)(TickType_t xTicksToDelay);
	wrapper = cmse_nsfptr_create(rtos_ns.taskDelay);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		wrapper(xTicksToDelay);
	}
}

void vTaskSuspend( TaskHandle_t xTaskToSuspend ) 
{
	#if defined(__ICCARM__)	
	void (__cmse_nonsecure_call *wrapper)(TaskHandle_t xTaskToSuspend);
	wrapper = ( void (__cmse_nonsecure_call *)(TaskHandle_t) )rtos_ns.taskSuspend;
	if(wrapper)
	#else		
	void __attribute__((cmse_nonsecure_call)) (*wrapper)(TaskHandle_t xTaskToSuspend);
	wrapper = cmse_nsfptr_create(rtos_ns.taskSuspend);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		wrapper(xTaskToSuspend);
	}	
}

void vTaskResume( TaskHandle_t xTaskToResume )
{
	#if defined(__ICCARM__)	
	void (__cmse_nonsecure_call *wrapper)(TaskHandle_t xTaskToResume);
	wrapper = ( void (__cmse_nonsecure_call *)(TaskHandle_t) )rtos_ns.taskResume;
	if(wrapper)
	#else	
	void __attribute__((cmse_nonsecure_call)) (*wrapper)(TaskHandle_t xTaskToResume);
	wrapper = cmse_nsfptr_create(rtos_ns.taskResume);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		wrapper(xTaskToResume);
	}		
}

void vTaskSuspendAll( void ) 
{
	#if defined(__ICCARM__)	
	void (__cmse_nonsecure_call *wrapper)(void);
	wrapper = ( void (__cmse_nonsecure_call *)(void) )rtos_ns.taskSuspendAll;
	if(wrapper)
	#else	
	void __attribute__((cmse_nonsecure_call)) (*wrapper)(void);
	wrapper = cmse_nsfptr_create(rtos_ns.taskSuspendAll);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		wrapper();
	}		
}

BaseType_t xTaskResumeAll( void ) 
{
	#if defined(__ICCARM__)	
	BaseType_t (__cmse_nonsecure_call *wrapper)(void);
	wrapper = ( BaseType_t (__cmse_nonsecure_call *)(void) )rtos_ns.taskResumeAll;
	if(wrapper)
	#else	
	BaseType_t __attribute__((cmse_nonsecure_call)) (*wrapper)(void);
	wrapper = cmse_nsfptr_create(rtos_ns.taskResumeAll);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper();
	}		
	return pdFAIL;
}

TickType_t xTaskGetTickCount( void ) 
{
	#if defined(__ICCARM__)	
	TickType_t (__cmse_nonsecure_call *wrapper)(void);
	wrapper = ( TickType_t (__cmse_nonsecure_call *)(void) )rtos_ns.taskGetTickCount;
	if(wrapper)
	#else		
	TickType_t __attribute__((cmse_nonsecure_call)) (*wrapper)(void);
	wrapper = cmse_nsfptr_create(rtos_ns.taskGetTickCount);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper();
	}		
	return 0;	
}

TaskHandle_t xTaskGetCurrentTaskHandle( void )
{
	#if defined(__ICCARM__)	
	TaskHandle_t (__cmse_nonsecure_call *wrapper)(void);
	wrapper = ( TaskHandle_t (__cmse_nonsecure_call *)(void) )rtos_ns.taskGetCurrentTaskHandle;
	if(wrapper)
	#else		
	TaskHandle_t __attribute__((cmse_nonsecure_call)) (*wrapper)(void);
	wrapper = cmse_nsfptr_create(rtos_ns.taskGetCurrentTaskHandle);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper();
	}		
	return NULL;		
}


char* pcTaskGetName( TaskHandle_t xTaskToQuery )
{
	#if defined(__ICCARM__)	
	char* (__cmse_nonsecure_call *wrapper)(TaskHandle_t xTaskToQuery);
	wrapper = ( char* (__cmse_nonsecure_call *)(TaskHandle_t) )rtos_ns.taskGetName;
	if(wrapper)
	#else		
	char* __attribute__((cmse_nonsecure_call)) (*wrapper)(TaskHandle_t xTaskToQuery);
	wrapper = cmse_nsfptr_create(rtos_ns.taskGetName);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		char *str = wrapper(xTaskToQuery);
		#if !SET_NS_NAME
		if(strcmp("secure", str)==0){
			TaskHandle_t tmp_hdl =  xTaskGetCurrentTaskHandle();
			uint32_t *tmp = (uint32_t*)tmp_hdl;
			uint32_t sid = tmp[2];
			str = TZ_Get_Task_Name(sid);
		}
		#endif
		return str;
	}		
	return "FAIL";		
}

void *pvPortMallocNS( size_t xWantedSize )
{
	#if defined(__ICCARM__)	
	void * (__cmse_nonsecure_call *wrapper)( size_t xWantedSize );
	wrapper = ( void * (__cmse_nonsecure_call *)( size_t ) )rtos_ns.portMalloc;
	if(wrapper)
	#else			
	void * __attribute__((cmse_nonsecure_call)) (*wrapper)( size_t xWantedSize );
	wrapper = cmse_nsfptr_create(rtos_ns.portMalloc);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper(xWantedSize);
	}
	return NULL;	
}

void vPortFreeNS( void *pv )
{
	#if defined(__ICCARM__)	
	void (__cmse_nonsecure_call *wrapper)( void *pv );
	wrapper = ( void (__cmse_nonsecure_call *)( void * ) )rtos_ns.portFree;
	if(wrapper)
	#else		
	void __attribute__((cmse_nonsecure_call)) (*wrapper)( void *pv );
	wrapper = cmse_nsfptr_create(rtos_ns.portFree);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		// check pv on ns-mem?
		wrapper(pv);
	}
}


TimerHandle_t xTimerCreate( const char * const pcTimerName, const TickType_t xTimerPeriodInTicks, const UBaseType_t uxAutoReload, void * const pvTimerID, TimerCallbackFunction_t pxCallbackFunction )
{
	#if defined(__ICCARM__)	
	TimerHandle_t (__cmse_nonsecure_call *wrapper)( TickType_t xTimerPeriodInTicks, UBaseType_t uxAutoReload, void * pvTimerID, TimerCallbackFunction_t pxCallbackFunction );
	wrapper = ( TimerHandle_t (__cmse_nonsecure_call *)( TickType_t , UBaseType_t , void * , TimerCallbackFunction_t ) )rtos_ns.timerCreate;
	if(wrapper)
	#else		
	TimerHandle_t __attribute__((cmse_nonsecure_call)) (*wrapper)( TickType_t xTimerPeriodInTicks, UBaseType_t uxAutoReload, void * pvTimerID, TimerCallbackFunction_t pxCallbackFunction );
	wrapper = cmse_nsfptr_create(rtos_ns.timerCreate);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		TimerHandle_t tmp =  wrapper(xTimerPeriodInTicks, uxAutoReload, pvTimerID, pxCallbackFunction);
		#if NS_SET_NAME
		char * name = (char*)pcTimerGetName(tmp);
		strncmp(name, pcTimerName, strlen("_sectimer"));
		#endif
		return tmp;
	}
	return NULL;
}

BaseType_t xTimerIsTimerActive( TimerHandle_t xTimer )
{
	#if defined(__ICCARM__)	
	BaseType_t (__cmse_nonsecure_call *wrapper)( TimerHandle_t xTimer );
	wrapper = ( BaseType_t (__cmse_nonsecure_call *)( TimerHandle_t ) )rtos_ns.timerIsTimerActive;
	if(wrapper)
	#else		
	BaseType_t __attribute__((cmse_nonsecure_call)) (*wrapper)( TimerHandle_t xTimer );
	wrapper = cmse_nsfptr_create(rtos_ns.timerIsTimerActive);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper(xTimer);
	}
	return pdFAIL;	
}

TickType_t xTimerGetPeriod( TimerHandle_t xTimer )
{
	#if defined(__ICCARM__)	
	TickType_t (__cmse_nonsecure_call *wrapper)( TimerHandle_t xTimer );
	wrapper = ( TickType_t (__cmse_nonsecure_call *)( TimerHandle_t ) )rtos_ns.timerGetPeriod;
	if(wrapper)
	#else	
	TickType_t __attribute__((cmse_nonsecure_call)) (*wrapper)( TimerHandle_t xTimer );
	wrapper = cmse_nsfptr_create(rtos_ns.timerGetPeriod);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper(xTimer);
	}
	return 0;	
}

TickType_t xTimerGetExpiryTime( TimerHandle_t xTimer )
{
	#if defined(__ICCARM__)	
	TickType_t (__cmse_nonsecure_call *wrapper)( TimerHandle_t xTimer );
	wrapper = ( TickType_t (__cmse_nonsecure_call *)( TimerHandle_t ) )rtos_ns.timerGetExpiryTime;
	if(wrapper)
	#else		
	TickType_t __attribute__((cmse_nonsecure_call)) (*wrapper)( TimerHandle_t xTimer );
	wrapper = cmse_nsfptr_create(rtos_ns.timerGetExpiryTime);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper(xTimer);
	}
	return 0;	
}

const char * pcTimerGetName( TimerHandle_t xTimer )
{
	#if defined(__ICCARM__)	
	const char * (__cmse_nonsecure_call *wrapper)( TimerHandle_t xTimer );
	wrapper = ( const char * (__cmse_nonsecure_call *)( TimerHandle_t ) )rtos_ns.timerGetName;
	if(wrapper)
	#else			
	const char * __attribute__((cmse_nonsecure_call)) (*wrapper)( TimerHandle_t xTimer );
	wrapper = cmse_nsfptr_create(rtos_ns.timerGetName);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper(xTimer);
	}
	return NULL;	
}

BaseType_t xTimerGenericCommand( TimerHandle_t xTimer, const BaseType_t xCommandID, const TickType_t xOptionalValue, BaseType_t * const pxHigherPriorityTaskWoken, const TickType_t xTicksToWait )
{
	#if defined(__ICCARM__)	
	BaseType_t (__cmse_nonsecure_call *wrapper)( uint32_t * params );
	wrapper = ( BaseType_t (__cmse_nonsecure_call *)( uint32_t * ) )rtos_ns.timerGenericCommand;
	if(wrapper)
	#else		
	BaseType_t __attribute__((cmse_nonsecure_call)) (*wrapper)( uint32_t * params );	
	wrapper = cmse_nsfptr_create(rtos_ns.timerGenericCommand);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		uint32_t *params = pvPortMallocNS(sizeof(uint32_t)*8);
		if(!params)	return pdFAIL;
		params[0] = (uint32_t)xTimer;
		params[1] = (uint32_t)xCommandID;
		params[2] = (uint32_t)xOptionalValue;	
		params[3] = (uint32_t)pxHigherPriorityTaskWoken;
		params[4] = (uint32_t)xTicksToWait;
		
		BaseType_t ret = wrapper(params);
		vPortFreeNS(params);
		return ret;
	}
	return pdFAIL;	
}

EventGroupHandle_t xEventGroupCreate( void )
{
	#if defined(__ICCARM__)	
	EventGroupHandle_t (__cmse_nonsecure_call *wrapper)( void );
	wrapper = ( EventGroupHandle_t (__cmse_nonsecure_call *)( void ) )rtos_ns.eventGroupCreate;
	if(wrapper)
	#else		
	EventGroupHandle_t __attribute__((cmse_nonsecure_call)) (*wrapper)( void );
	wrapper = cmse_nsfptr_create(rtos_ns.eventGroupCreate);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper();
	}
	return 0;	
}

void vEventGroupDelete( EventGroupHandle_t xEventGroup )
{
	#if defined(__ICCARM__)	
	void (__cmse_nonsecure_call *wrapper)( EventGroupHandle_t xEventGroup );
	wrapper = ( void (__cmse_nonsecure_call *)( EventGroupHandle_t ) )rtos_ns.eventGroupDelete;
	if(wrapper)
	#else	
	void __attribute__((cmse_nonsecure_call)) (*wrapper)( EventGroupHandle_t xEventGroup );
	wrapper = cmse_nsfptr_create(rtos_ns.eventGroupDelete);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		wrapper(xEventGroup);
	}
}	

EventBits_t xEventGroupWaitBits( EventGroupHandle_t xEventGroup, const EventBits_t uxBitsToWaitFor, const BaseType_t xClearOnExit, const BaseType_t xWaitForAllBits, TickType_t xTicksToWait )
{
	#if defined(__ICCARM__)	
	EventBits_t (__cmse_nonsecure_call *wrapper)( uint32_t * params );
	wrapper = ( EventBits_t (__cmse_nonsecure_call *)( uint32_t * ) )rtos_ns.eventGroupWaitBits;
	if(wrapper)
	#else		
	EventBits_t __attribute__((cmse_nonsecure_call)) (*wrapper)( uint32_t * params );	
	wrapper = cmse_nsfptr_create(rtos_ns.eventGroupWaitBits);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		uint32_t *params = pvPortMallocNS(sizeof(uint32_t)*8);
		if(!params)	return pdFAIL;
		params[0] = (uint32_t)xEventGroup;
		params[1] = (uint32_t)uxBitsToWaitFor;
		params[2] = (uint32_t)xClearOnExit;	
		params[3] = (uint32_t)xWaitForAllBits;
		params[4] = (uint32_t)xTicksToWait;
		
		EventBits_t ret = wrapper(params);
		vPortFreeNS(params);
		return ret;
	}
	return 0;		
}

EventBits_t xEventGroupSetBits( EventGroupHandle_t xEventGroup, const EventBits_t uxBitsToSet )
{
	#if defined(__ICCARM__)	
	EventBits_t (__cmse_nonsecure_call *wrapper)( EventGroupHandle_t xEventGroup, const EventBits_t uxBitsToSet );
	wrapper = ( EventBits_t (__cmse_nonsecure_call *)( EventGroupHandle_t , const EventBits_t ) )rtos_ns.eventGroupSetBits;
	if(wrapper)
	#else			
	EventBits_t __attribute__((cmse_nonsecure_call)) (*wrapper)( EventGroupHandle_t xEventGroup, const EventBits_t uxBitsToSet );
	wrapper = cmse_nsfptr_create(rtos_ns.eventGroupSetBits);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper(xEventGroup, uxBitsToSet);
	}
	return 0;		
}

EventBits_t xEventGroupClearBits( EventGroupHandle_t xEventGroup, const EventBits_t uxBitsToClear )
{
	#if defined(__ICCARM__)	
	EventBits_t (__cmse_nonsecure_call *wrapper)( EventGroupHandle_t xEventGroup, EventBits_t uxBitsToClear );
	wrapper = ( EventBits_t (__cmse_nonsecure_call *)( EventGroupHandle_t , EventBits_t ) )rtos_ns.eventGroupClearBits;
	if(wrapper)
	#else		
	EventBits_t __attribute__((cmse_nonsecure_call)) (*wrapper)( EventGroupHandle_t xEventGroup, EventBits_t uxBitsToClear );
	wrapper = cmse_nsfptr_create(rtos_ns.eventGroupClearBits);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper(xEventGroup, uxBitsToClear);
	}
	return 0;	
}

EventBits_t xEventGroupSync( EventGroupHandle_t xEventGroup, const EventBits_t uxBitsToSet, const EventBits_t uxBitsToWaitFor, TickType_t xTicksToWait )
{
	#if defined(__ICCARM__)	
	EventBits_t (__cmse_nonsecure_call *wrapper)( EventGroupHandle_t xEventGroup, const EventBits_t uxBitsToSet, const EventBits_t uxBitsToWaitFor, TickType_t xTicksToWait );
	wrapper = ( EventBits_t (__cmse_nonsecure_call *)( EventGroupHandle_t , const EventBits_t , const EventBits_t , TickType_t ) )rtos_ns.eventGroupSync;
	if(wrapper)
	#else			
	EventBits_t __attribute__((cmse_nonsecure_call)) (*wrapper)( EventGroupHandle_t xEventGroup, const EventBits_t uxBitsToSet, const EventBits_t uxBitsToWaitFor, TickType_t xTicksToWait );
	wrapper = cmse_nsfptr_create(rtos_ns.eventGroupSync);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper(xEventGroup, uxBitsToSet, uxBitsToWaitFor, xTicksToWait);
	}
	return 0;		
}

size_t xPortGetFreeHeapSizeNS( void )
{
	#if defined(__ICCARM__)	
	size_t (__cmse_nonsecure_call *wrapper)( void );
	wrapper = ( size_t (__cmse_nonsecure_call *)( void ) )rtos_ns.portGetFreeHeapSize;
	if(wrapper)
	#else		
	size_t __attribute__((cmse_nonsecure_call)) (*wrapper)( void );
	wrapper = cmse_nsfptr_create(rtos_ns.portGetFreeHeapSize);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper();
	}
	return 0;
}

QueueHandle_t xQueueGenericCreate( const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize, const uint8_t ucQueueType )
{
	#if defined(__ICCARM__)	
	QueueHandle_t (__cmse_nonsecure_call *wrapper)(UBaseType_t uxQueueLength, UBaseType_t uxItemSize, uint8_t ucQueueType);
	wrapper = ( QueueHandle_t (__cmse_nonsecure_call *)(UBaseType_t , UBaseType_t , uint8_t ) )rtos_ns.queueGenericCreate;
	if(wrapper)
	#else		
	QueueHandle_t __attribute__((cmse_nonsecure_call)) (*wrapper)(UBaseType_t uxQueueLength, UBaseType_t uxItemSize, uint8_t ucQueueType);
	wrapper = cmse_nsfptr_create(rtos_ns.queueGenericCreate);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper(uxQueueLength, uxItemSize, ucQueueType);
	}
	return NULL;
}	

BaseType_t xQueueReceive( QueueHandle_t xQueue, void * const pvBuffer, TickType_t xTicksToWait)
{
	#if defined(__ICCARM__)	
	BaseType_t (__cmse_nonsecure_call *wrapper)(QueueHandle_t xQueue, void * pvBuffer, TickType_t xTicksToWait);
	wrapper = ( BaseType_t (__cmse_nonsecure_call *)(QueueHandle_t , void * , TickType_t) )rtos_ns.queueReceive;
	if(wrapper)
	#else	
	BaseType_t __attribute__((cmse_nonsecure_call)) (*wrapper)(QueueHandle_t xQueue, void * pvBuffer, TickType_t xTicksToWait);
	wrapper = cmse_nsfptr_create(rtos_ns.queueReceive);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper(xQueue, pvBuffer, xTicksToWait);
	}	
	return pdFAIL;
}

BaseType_t xQueuePeek( QueueHandle_t xQueue, void * const pvBuffer, TickType_t xTicksToWait )
{
	#if defined(__ICCARM__)	
	BaseType_t (__cmse_nonsecure_call *wrapper)(QueueHandle_t xQueue, void * pvBuffer, TickType_t xTicksToWait);
	wrapper = ( BaseType_t (__cmse_nonsecure_call *)(QueueHandle_t , void * , TickType_t ) )rtos_ns.queuePeek;
	if(wrapper)
	#else	
	BaseType_t __attribute__((cmse_nonsecure_call)) (*wrapper)(QueueHandle_t xQueue, void * pvBuffer, TickType_t xTicksToWait);
	wrapper = cmse_nsfptr_create(rtos_ns.queuePeek);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper(xQueue, pvBuffer, xTicksToWait);
	}	
	return pdFAIL;
}

BaseType_t xQueueSemaphoreTake( QueueHandle_t xQueue, TickType_t xTicksToWait )
{
	#if defined(__ICCARM__)	
	BaseType_t (__cmse_nonsecure_call *wrapper)(QueueHandle_t xQueue, TickType_t xTicksToWait);
	wrapper = ( BaseType_t (__cmse_nonsecure_call *)(QueueHandle_t , TickType_t ) )rtos_ns.queueSemaphoreTake;
	if(wrapper)
	#else	
	BaseType_t __attribute__((cmse_nonsecure_call)) (*wrapper)(QueueHandle_t xQueue, TickType_t xTicksToWait);
	wrapper = cmse_nsfptr_create(rtos_ns.queueSemaphoreTake);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper(xQueue, xTicksToWait);
	}	
	return pdFAIL;
}

BaseType_t xQueueGenericSend( QueueHandle_t xQueue, const void * const pvItemToQueue, TickType_t xTicksToWait, const BaseType_t xCopyPosition )
{
	#if defined(__ICCARM__)	
	BaseType_t (__cmse_nonsecure_call *wrapper)(QueueHandle_t xQueue, const void * pvItemToQueue, TickType_t xTicksToWait, BaseType_t xCopyPosition);
	wrapper = ( BaseType_t (__cmse_nonsecure_call *)(QueueHandle_t , const void * , TickType_t , BaseType_t ) )rtos_ns.queueGenericSend;
	if(wrapper)
	#else		
	BaseType_t __attribute__((cmse_nonsecure_call)) (*wrapper)(QueueHandle_t xQueue, const void * pvItemToQueue, TickType_t xTicksToWait, BaseType_t xCopyPosition);
	wrapper = cmse_nsfptr_create(rtos_ns.queueGenericSend);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper(xQueue, (void*)pvItemToQueue, xTicksToWait, xCopyPosition);
	}		
	return pdFAIL;
}

BaseType_t xQueueGenericReset( QueueHandle_t xQueue, BaseType_t xNewQueue )
{
	#if defined(__ICCARM__)	
	BaseType_t (__cmse_nonsecure_call *wrapper)(QueueHandle_t xQueue, BaseType_t xNewQueue);
	wrapper = ( BaseType_t (__cmse_nonsecure_call *)(QueueHandle_t , BaseType_t ) )rtos_ns.queueGenericReset;
	if(wrapper)
	#else		
	BaseType_t __attribute__((cmse_nonsecure_call)) (*wrapper)(QueueHandle_t xQueue, BaseType_t xNewQueue);
	wrapper = cmse_nsfptr_create(rtos_ns.queueGenericReset);
	if (wrapper && cmse_is_nsfptr(wrapper)) 
	#endif
	{
		return wrapper(xQueue, xNewQueue);
	}
	return pdFAIL;
}


//--- Aserrt and Malloc fail callback
void vAssertCalled( uint32_t ulLine, const char *pcfile )
{
	// 
	while(1);
}

void vApplicationMallocFailedHook( void )
{
	asm(" nop");
}
