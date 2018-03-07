#ifndef __LABS_QUEUE_H
#define __LABS_QUEUE_H

#ifndef __LABS_CONFIG_H
    #error "include Labs_Config.h" must appear in source files before "Labs_Queue.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void * QueueHandle_t;

#if (configQUEUE_MULTI == 1)
#define xQueueCreate(pucQueueStorageArea, usQueueSize) xQueue_MultiInitialize(pucQueueStorageArea, usQueueSize)

#else
#define xQueueCreate(pucQueueStorageArea, usQueueSize) xQueue_SingleInitialize(void)

#endif /* Multi Queue */

#ifdef __cplusplus
}
#endif

#endif /* __LABS_QUEUE_H */