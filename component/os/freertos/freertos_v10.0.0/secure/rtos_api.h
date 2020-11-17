#ifndef RTOSAPI_H
#define RTOSAPI_H

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <timers.h>
#include <event_groups.h>


typedef struct rtos_function{
	// task.h
	TaskHandle_t (*taskCreate)( uint32_t pxTaskCode, uint16_t usSecureStackDepth, UBaseType_t uxPriority);
	void (*taskDelete)( TaskHandle_t xTaskToDelete );
	void (*taskDelay)( TickType_t xTicksToDelay );
	void (*taskSuspend)( TaskHandle_t xTaskToSuspend );
	void (*taskResume)( TaskHandle_t xTaskToResume );
	void (*taskSuspendAll)( void );
	BaseType_t (*taskResumeAll)( void );
	TickType_t (*taskGetTickCount)( void );
	TaskHandle_t (*taskGetCurrentTaskHandle)( void );
	char* (*taskGetName)( TaskHandle_t xTaskToQuery );
	
	// timers.h
	TimerHandle_t (*timerCreate)( TickType_t xTimerPeriodInTicks, UBaseType_t uxAutoReload, void * pvTimerID, TimerCallbackFunction_t pxCallbackFunction );	
	BaseType_t (*timerGenericCommand)( uint32_t* params );
	BaseType_t (*timerIsTimerActive)( TimerHandle_t xTimer );
	TickType_t (*timerGetPeriod)( TimerHandle_t xTimer );
	TickType_t (*timerGetExpiryTime)( TimerHandle_t xTimer );
	const char * (*timerGetName)( TimerHandle_t xTimer );
	
	// event_groups.h
	EventGroupHandle_t (*eventGroupCreate)( void );
	void (*eventGroupDelete)( EventGroupHandle_t xEventGroup );
	EventBits_t (*eventGroupWaitBits)( uint32_t* params );
	EventBits_t (*eventGroupSetBits)( EventGroupHandle_t xEventGroup, EventBits_t uxBitsToSet );
	EventBits_t (*eventGroupClearBits)( EventGroupHandle_t xEventGroup, EventBits_t uxBitsToClear );
	EventBits_t (*eventGroupSync)( EventGroupHandle_t xEventGroup, EventBits_t uxBitsToSet, EventBits_t uxBitsToWaitFor, TickType_t xTicksToWait );
	
	// non-secure heap allocation
	void * (*portMalloc)( size_t xWantedSize );
	void (*portFree)( void *pv );
	size_t (*portGetFreeHeapSize)( void );
	
	// queue.h, semphr.h
	QueueHandle_t (*queueGenericCreate)( UBaseType_t uxQueueLength, UBaseType_t uxItemSize, uint8_t ucQueueType );
	//BaseType_t (*queueGenericReceive)( QueueHandle_t xQueue, void * pvBuffer, TickType_t xTicksToWait, BaseType_t xJustPeeking );
    BaseType_t (*queueReceive)( QueueHandle_t xQueue, void * const pvBuffer, TickType_t xTicksToWait );
    BaseType_t (*queuePeek)( QueueHandle_t xQueue, void * const pvBuffer, TickType_t xTicksToWait );
    BaseType_t (*queueSemaphoreTake)( QueueHandle_t xQueue, TickType_t xTicksToWait );
	BaseType_t (*queueGenericSend)( QueueHandle_t xQueue, const void * pvItemToQueue, TickType_t xTicksToWait, BaseType_t xCopyPosition );
	BaseType_t (*queueGenericReset)( QueueHandle_t xQueue, BaseType_t xNewQueue );
}rtos_func_ns;

uint32_t rtos_init (rtos_func_ns *rtos);

extern rtos_func_ns rtos_ns;

#endif
