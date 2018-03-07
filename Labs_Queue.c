#include "Labs_Config.h"
#include "Labs_Queue.h"

struct BlockDefinition
{
    struct BlockDefinition *pxNext;

    uint8_t ucIdentity;
    void *pvStorageData;
};
typedef struct BlockDefinition Block_t;

struct QueueDefinition
{
    Block_t *pxBlockUnused;
    Block_t *pxBlockUsed;

    bool hasInitialize;
    uint16_t usFreeSizeInByte;
};
typedef struct QueueDefinition Queue_t;

#if (configQUEUE_MULTI == 1)
QueueHandle_t xQueue_MultiInitialize(uint8_t *pucQueueStorageArea, uint16_t usQueueSize)
{
    if (pucQueueStorageArea != NULL && usQueueSize != NULL)
    {
        Queue_t *pxNewQueue = (Queue_t *)pucQueueStorageArea;

        if (pxNewQueue->hasInitialize != FALSE)
        {
            if (usQueueSize > sizeof(Queue_t))
            {
                pxNewQueue->usFreeSizeInByte = usQueueSize - sizeof(Queue_t);

                pxNewQueue->pxBlockUsed = pxNewQueue->pxBlockUnused = (Block_t *)(pucQueueStorageArea + sizeof(Queue_t));

                pxNewQueue->hasInitialize = (bool)TRUE;

                return (QueueHandle_t)pxNewQueue;
            }
        }
    }

    return (QueueHandle_t)NULL;
}

#else
static uint8_t ucaQueueStorageArea[configQUEUE_SIZEINBYTE];

QueueHandle_t xQueue_SingleInitialize(void)
{
    Queue_t *pxNewQueue = (Queue_t *)&ucaQueueStorageArea;

    if (pxNewQueue->hasInitialize != FALSE)
    {
        if (sizeof(ucaQueueStorageArea) > sizeof(Queue_t))
        {
            pxNewQueue->usFreeSizeInByte = sizeof(ucaQueueStorageArea) - sizeof(Queue_t);

            pxNewQueue->pxBlockUsed = pxNewQueue->pxBlockUnused = (Block_t *)(&ucaQueueStorageArea + sizeof(Queue_t));

            pxNewQueue->hasInitialize = (bool)TRUE;

            return (QueueHandle_t)pxNewQueue;
        }
    }

    return (QueueHandle_t)NULL;
}

#endif /* Multi Queue */

void Queue_Enqueue()
{
}

void Queue_Dequeue()
{
}