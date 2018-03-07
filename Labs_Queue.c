#include "Labs_Config.h"
#include "Labs_Queue.h"

/****************************************************************/

/**
 * 类型名：BlockDefinition/Block_t
 * 作用范围：局部
 * 功能：队列块结构，单个队列由一个及以上块构成
**/
struct BlockDefinition
{
    struct BlockDefinition *pxNext; /* !< 指向下一个块的指针 > */
    int8_t ucIdentity;              /* !< 块类型 > */
    uint16_t usLength;              /* !< 块大小 > */
    void *pvStorageData;            /* !< 指向块存储的数据指针 > */
};
typedef struct BlockDefinition Block_t;

/**
 * 类型名：QueueDefinition/Queue_t
 * 作用范围：局部
 * 功能：队列结构，存储队列相关信息
**/
struct QueueDefinition
{
    Block_t *pxBlockUnused;       /* !< 指向未使用的块的指针 > */
    Block_t *pxBlockUsed;         /* !< 指向已使用的块的指针 > */
    bool hasInitialize;           /* !< 队列初始化与否标识 > */
    uint16_t usFreeSizeInByte;    /* !< 队列空闲大小 > */
    uint16_t usMaximumSizeInByte; /* !< 队列总大小 > */
};
typedef struct QueueDefinition Queue_t;

/****************************************************************/

/**
 * Name:        Queue_Initialize
 * Function:    队列初始化函数
 * Return:      (QueueHandle_t)当前队列的指针
**/
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

/**
 * Name:        Queue_Enqueue
 * Function:    队列入队函数
 * Return:      (ErrorStatus)错误类型值
**/
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

/**
 * Name:        Queue_Dequeue
 * Function:    队列出队函数
 * Return:      (void *)指向当前块数据的指针
**/
void *Queue_Dequeue(QueueHandle_t pxQueue, int8_t ucIdentity)
{
#if (configQUEUE_MULTI == 1)
    Queue_t *pxOperatingQueue = (Queue_t *)pxQueue;

#else

#endif /* Multi Queue */
}