#include "Labs_Config.h"
#include "Labs_Queue.h"

struct BlockDefinition
{
    struct BlockDefinition *pxNext;

    int8_t ucIdentity;
    uint16_t usLength;
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

QueueHandle_t Queue_Initialize(uint8_t *pucQueueStorageArea, uint16_t usQueueSize)
{
#if (configQUEUE_MULTI == 1)
    Queue_t *pxNewQueue = (Queue_t *)pucQueueStorageArea;

    if (pxNewQueue != NULL && usQueueSize != NULL)
    {
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

#else
    static uint8_t ucaQueueStorageArea[configQUEUE_SIZEINBYTE];
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

#endif /* Multi Queue */

    return (QueueHandle_t)NULL;
}

ErrorStatus Queue_Enqueue(QueueHandle_t pxQueue, int8_t ucIdentity, void *pcSrcData, uint16_t usLength)
{
#if (configQUEUE_MULTI == 1)
    if ((pxQueue != NULL) && (usLength != NULL))
    {
        Queue_t *pxOperatingQueue = (Queue_t *)pxQueue;

        if (usLength <= pxOperatingQueue->usFreeSizeInByte + sizeof(Block_t))
        {
            Block_t *pxNewBlock = pxOperatingQueue->pxBlockUnused;

            char *pcDest = pxNewBlock->pvStorageData;
            const char *pcSrc = pcSrcData;

            pxNewBlock->ucIdentity = (int8_t)ucIdentity;
            pxNewBlock->usLength = (uint16_t)usLength;

            while (usLength--)
            {
                *pcDest++ = *pcSrc++;
            }
        }
    }

#else

#endif /* Multi Queue */
}

void *Queue_Dequeue(QueueHandle_t pxQueue, int8_t ucIdentity)
{
#if (configQUEUE_MULTI == 1)
    Queue_t *pxOperatingQueue = (Queue_t *)pxQueue;

#else

#endif /* Multi Queue */
}