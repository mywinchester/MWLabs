#ifndef __LABS_QUEUE_H
#define __LABS_QUEUE_H

#ifndef __LABS_CONFIG_H
    #error "include Labs_Config.h" must appear in source files before "Labs_Queue.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void *QueueHandle_t;

QueueHandle_t Queue_Initialize(uint8_t *pucQueueStorageArea, uint16_t usQueueSize);

ErrorStatus Queue_Enqueue(QueueHandle_t pxQueue, int8_t cIdentity, void *pvSrcData, uint16_t usLength);
void *Queue_Dequeue(QueueHandle_t pxQueue, int8_t cIdentity);

#ifdef __cplusplus
}
#endif

#endif /* __LABS_QUEUE_H */