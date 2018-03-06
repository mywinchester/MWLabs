#include "Labs_Config.h"
#include "Labs_Queue.h"

struct BlockDefinition
{
    struct BlockDefinition *pxFront;
    struct BlockDefinition *pxRear;

    void *pvStorageData;
};
typedef struct BlockDefinition Block_t;

struct QueueDefinition
{
    Block_t *pxBlockUnused;
    Block_t *pxBlockUsed;
};
typedef struct QueueDefinition Queue_t;