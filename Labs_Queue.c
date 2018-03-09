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
    int8_t cIdentity;               /* !< 块类型 > */
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
    uint16_t usFreeSizeInByte;    /* !< 队列空闲大小 > */
    uint16_t usMaximumSizeInByte; /* !< 队列总大小 > */
};
typedef struct QueueDefinition Queue_t;

/****************************************************************/

static void *vQMEMCPY(void *dest, const void *src, uint16_t size);

/****************************************************************/

/**
 * Name:        Queue_Initialize()
 * Function:    队列初始化函数
 * Return:      (QueueHandle_t)当前队列的指针
**/
QueueHandle_t Queue_Initialize(uint8_t *pucQueueStorageArea, uint16_t usQueueSize)
{
    if ((pucQueueStorageArea != NULL) && (usQueueSize > (sizeof(Queue_t) + sizeof(Block_t))))
    {
        Queue_t *pxNewQueue = (Queue_t *)pucQueueStorageArea;

        pxNewQueue->usMaximumSizeInByte = (uint16_t)usQueueSize;
        pxNewQueue->usFreeSizeInByte = (uint16_t)(usQueueSize - sizeof(Queue_t));

        pxNewQueue->pxBlockUsed = pxNewQueue->pxBlockUnused = (Block_t *)(pucQueueStorageArea + sizeof(Queue_t));
        pxNewQueue->pxBlockUsed->pxNext = NULL;

        return (QueueHandle_t)(pxNewQueue);
    }

    return (QueueHandle_t)(NULL);
}

/**
 * Name:        Queue_Destroy()
 * Function:    队列销毁函数
 * Return:      (QueueHandle_t)当前队列的指针
**/
QueueHandle_t Queue_Destroy(QueueHandle_t pxQueue)
{
    return (QueueHandle_t)(NULL);
}

/**
 * Name:        Queue_IsEmpty()
 * Function:    队列空判断函数
 * Return:      (bool)
**/
bool Queue_IsEmpty(QueueHandle_t pxQueue)
{
    Queue_t *pxOperatingQueue = (Queue_t *)pxQueue;

    return (bool)((pxOperatingQueue->pxBlockUsed->pxNext != NULL) ? (FALSE) : (TRUE));
}

/**
 * Name:        Queue_RemainingSpace()
 * Function:    队列剩余空间查看函数
 * Return:      (uint16_t)当前队列剩余空间
**/
uint16_t Queue_RemainingSpace(QueueHandle_t pxQueue)
{
    Queue_t *pxOperatingQueue = (Queue_t *)pxQueue;

    return (uint16_t)(pxOperatingQueue->usFreeSizeInByte);
}

/**
 * Name:        Queue_Enqueue()
 * Function:    队列入队函数
 * Return:      (ErrorStatus)错误类型值
**/
ErrorStatus Queue_Enqueue(QueueHandle_t pxQueue, int8_t cIdentity, void *pvSrcData, uint16_t usLength)
{
    if (pxQueue != NULL)
    {
        Queue_t *pxOperatingQueue = (Queue_t *)pxQueue;

        if (usLength <= (pxOperatingQueue->usFreeSizeInByte - sizeof(Block_t)))
        {
            if (((pxOperatingQueue + pxOperatingQueue->usMaximumSizeInByte) - pxOperatingQueue->pxBlockUnused - sizeof(Block_t)) <=
                usLength)
            {
                Block_t *pxMovedBlock = (Block_t *)pxOperatingQueue->pxBlockUsed;

                while (pxMovedBlock->pxNext != NULL)
                {
                    pxMovedBlock = vQMEMCPY()
                }
            }
        }
    }
    return (ErrorStatus)(ERROR);
}

/**
 * Name:        Queue_Dequeue()
 * Function:    队列出队函数
 * Return:      (void *)指向当前块数据的指针
**/
void *Queue_Dequeue(QueueHandle_t pxQueue, int8_t cIdentity)
{
}

/**
 * Name:        vQMEMCPY()
 * Function:    数据拷贝函数
 * Return:      (void *)移动后数据块头部的指针
**/
static void *vQMEMCPY(void *dest, const void *src, uint16_t size)
{
    char *pcDEST = dest;
    const char *pcSRC = src;

    while (size--)
    {
        *pcDEST++ = *pcSRC++;
    }

    return (dest);
}