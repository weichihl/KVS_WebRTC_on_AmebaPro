#include "rtos_api.h"
//#include "diag.h"

#define MAX_SECURE_TASK 16
struct secure_task{
    TaskFunction_t pxTaskCode;
    void * Parameters;
    TaskHandle_t pxNonSecureHandle;
};

struct secure_task xSecureTask[MAX_SECURE_TASK] = {0};

void __attribute__((cmse_nonsecure_entry)) vSecureTaskDispatcher(void * Parameters)
{
    //
    uint32_t ulTaskId = (uint32_t)Parameters;
    if(ulTaskId == 0xFFFFFFFF)  return;
    
    //rt_printfl(" I am in Secure %x %x %x !!!\n\r", ulTaskId, xSecureTask[ulTaskId].pxTaskCode, xSecureTask[ulTaskId].Parameters );
    xSecureTask[ulTaskId].pxTaskCode(xSecureTask[ulTaskId].Parameters);
}

uint32_t ulSecureTaskAdd(TaskFunction_t pxTaskCode, void * Parameters)
{
    int empty_slot = -1;
    // find a null slot
    for(int i=0;i<MAX_SECURE_TASK;i++)
    {
        if(xSecureTask[i].pxTaskCode == NULL){
            empty_slot = i;
            break;
        }
    }
    if(empty_slot<0) return 0xFFFFFFFF;
    
    xSecureTask[empty_slot].pxTaskCode = pxTaskCode;
    xSecureTask[empty_slot].Parameters = Parameters;
    
    return (uint32_t)empty_slot;
}

void vSecureTaskSetNSHandle(uint32_t ulTaskId, TaskHandle_t pxHandle)
{
    xSecureTask[ulTaskId].pxNonSecureHandle = pxHandle;
}

uint32_t ulSecureTaskGetIdByNSHandle(TaskHandle_t pxHandle)
{
    for(int i=0;i<MAX_SECURE_TASK;i++)
    {
        if(pxHandle == xSecureTask[i].pxNonSecureHandle)
            return (uint32_t)i;
    }
    return 0xFFFFFFFF;
}

void vSecureTaskDel(uint32_t ulTaskId)
{
    if(ulTaskId == 0xFFFFFFFF)  return;
    
    xSecureTask[ulTaskId].pxTaskCode = NULL;
    xSecureTask[ulTaskId].Parameters = NULL;
}
