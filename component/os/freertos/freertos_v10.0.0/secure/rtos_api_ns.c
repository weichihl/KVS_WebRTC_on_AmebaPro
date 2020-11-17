#include <rtos_api.h>

rtos_func_ns rtos_ns = {
	.taskCreate = xTaskCreateFromSecure,
	.taskDelete = vTaskDelete,
	.taskDelay = vTaskDelay,
	.taskSuspend = vTaskSuspend,
	.taskResume = vTaskResume,
	.taskSuspendAll = vTaskSuspendAll,
	.taskResumeAll = xTaskResumeAll,
	.taskGetTickCount = xTaskGetTickCount,
	.taskGetCurrentTaskHandle = xTaskGetCurrentTaskHandle,
	.taskGetName = pcTaskGetName,
	
	.timerCreate = xTimerCreateFromSecure,
	.timerGenericCommand = xTimerGenericCommandFromSecure,
	.timerIsTimerActive = xTimerIsTimerActive,
	.timerGetPeriod = xTimerGetPeriod,
	.timerGetExpiryTime = xTimerGetExpiryTime,
	.timerGetName = pcTimerGetName,
	
	.eventGroupCreate = xEventGroupCreate,
	.eventGroupDelete = vEventGroupDelete,
	.eventGroupWaitBits = xEventGroupWaitBitsFromSecure,
	.eventGroupSetBits = xEventGroupSetBits,
	.eventGroupClearBits = xEventGroupClearBits,
	.eventGroupSync = xEventGroupSync,
	
	.portMalloc = pvPortMalloc,
	.portFree = vPortFree,
	.portGetFreeHeapSize = xPortGetFreeHeapSize,
	
	.queueGenericCreate = xQueueGenericCreate,
	.queueReceive = xQueueReceive,
    .queuePeek = xQueuePeek,
    .queueSemaphoreTake = xQueueSemaphoreTake,
	.queueGenericSend = xQueueGenericSend,
	.queueGenericReset = xQueueGenericReset
	
};