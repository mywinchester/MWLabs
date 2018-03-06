#include "Labs_Config.h"
#include "Labs_Queue.h"

struct BlockDefinition
{
    struct BlockDefinition *pxNext;

    void *pvStorageData;
};
typedef struct BlockDefinition Block_t;

struct QueueDefinition
{
    Block_t *pxBlockUnused;
    Block_t *pxBlockUsed;

    uint16_t usFreeSize;
};
typedef struct QueueDefinition Queue_t;

static uint8_t ucaQueueStorageArea[configQUEUE_SIZE];

QueueHandle_t Queue_Initialize()
{
    Queue_t *pxNewQueue = (Queue_t *)&ucaQueueStorageArea;

    pxNewQueue->usFreeSize = sizeof(ucaQueueStorageArea) - sizeof(Queue_t);

    pxNewQueue->pxBlockUsed = pxNewQueue->pxBlockUnused = (Block_t *)(pxNewQueue + sizeof(Queue_t));

    pxNewQueue->pxBlockUsed->pxNext = NULL;

    pxNewQueue->pxBlockUnused->pxNext = (Block_t *)(pxNewQueue->pxBlockUsed + sizeof(Block_t));
}

void Queue_Enqueue()
{
}

void Queue_Dequeue()
{
}