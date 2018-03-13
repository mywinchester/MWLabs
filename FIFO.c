#include "common.h"
#include "FIFO.h"

/****************************************************************/

/**
 * 类型名:      FIFODefinition/FIFO_t
 * 作用范围:    局部
 * 功能:        FIFO队列结构，存储FIFO队列相关信息
**/
struct FIFODefinition
{
    char *pxBlockUnused;        /* !< 指向未使用的块的指针 > */
    char *pxBlockUsed;          /* !< 指向已使用的块的指针 > */
    uint16_t usFreeSizeInByte;  /* !< FIFO队列空闲大小 > */
    uint16_t usTotalSizeInByte; /* !< FIFO队列总大小 > */
};
typedef struct FIFODefinition FIFO_t;

/****************************************************************/

/**
 * 函数名:      FIFO_Initialize()
 * 功能:        FIFO队列初始化函数
 * 返回值:      (FIFOHandle_t)当前FIFO队列的指针
**/
FIFOHandle_t FIFO_Initialize(void *pvFIFOStorageArea, uint16_t usFIFOStorageSize)
{
    if ((pvFIFOStorageArea != NULL) && (usFIFOStorageSize > sizeof(FIFO_t)))
    {
        FIFO_t *pxNewFIFO = (FIFO_t *)pvFIFOStorageArea;

        pxNewFIFO->usTotalSizeInByte = (uint16_t)usFIFOStorageSize;
        pxNewFIFO->usFreeSizeInByte = (uint16_t)(usFIFOStorageSize - sizeof(FIFO_t));

        pxNewFIFO->pxBlockUsed = pxNewFIFO->pxBlockUnused = (char *)((char *)pxNewFIFO + sizeof(FIFO_t));

        return (FIFOHandle_t)(pxNewFIFO);
    }

    return (FIFOHandle_t)(NULL);
}

/**
 * 函数名:      FIFO_Destroy()
 * 功能:        FIFO队列销毁函数
 * 返回值:      (FIFOHandle_t)当前FIFO队列的指针
**/
FIFOHandle_t FIFO_Destroy(FIFOHandle_t pxFIFO)
{
    return (FIFOHandle_t)(NULL);
}

/**
 * 函数名:      FIFO_UsedSpaceSize()
 * 功能:        查看FIFO队列已使用的空间大小
 * 返回值:      (uint16_t)已使用的空间大小
**/
uint16_t FIFO_UsedSpaceSize(FIFOHandle_t pxFIFO)
{
    FIFO_t *pxOperatingFIFO = (FIFO_t *)pxFIFO;

    return (uint16_t)(pxOperatingFIFO->usTotalSizeInByte - sizeof(FIFO_t) - pxOperatingFIFO->usFreeSizeInByte);
}

/**
 * 函数名:      FIFO_UnusedSpaceSize()
 * 功能:        查看FIFO队列未使用的空间大小
 * 返回值:      (uint16_t)未使用的空间大小
**/
uint16_t FIFO_UnusedSpaceSize(FIFOHandle_t pxFIFO)
{
    FIFO_t *pxOperatingFIFO = (FIFO_t *)pxFIFO;

    return (uint16_t)(pxOperatingFIFO->usFreeSizeInByte);
}

/**
 * 函数名:      FIFO_Read()
 * 功能:        FIFO队列读取
 * 返回值:      (uint16_t)读取到的数据字节大小
**/
uint16_t FIFO_Read(FIFOHandle_t pxFIFO, void *pvDest, uint16_t usSize)
{
    if (pxFIFO != NULL)
    {
        FIFO_t *pxOperatingFIFO = (FIFO_t *)pxFIFO;

        char *pcStartLine = (char *)((char *)pxOperatingFIFO + sizeof(FIFO_t));
        char *pcEndLine = (char *)((char *)pxOperatingFIFO + pxOperatingFIFO->usTotalSizeInByte);

        uint16_t usReadNumber = 0;

        pxOperatingFIFO->usFreeSizeInByte += usSize;

        while (usSize--)
        {
            *((char *)pvDest)++ = *((char *)pxOperatingFIFO->pxBlockUsed)++;

            usReadNumber++;

            if (pxOperatingFIFO->pxBlockUsed == pcEndLine)
            {
                pxOperatingFIFO->pxBlockUsed = pcStartLine;
            }

            if (pxOperatingFIFO->pxBlockUsed == pxOperatingFIFO->pxBlockUnused)
            {
                return (uint16_t)(usReadNumber);
            }
        }

        return (uint16_t)(usReadNumber);
    }

    return (uint16_t)(NULL);
}

/**
 * 函数名:      FIFO_Write()
 * 功能:        FIFO队列写入
 * 返回值:      (ErrorStatus)错误类型值
**/
ErrorStatus FIFO_Write(FIFOHandle_t pxFIFO, const void *pvSrc, uint16_t usSize)
{
    if (pxFIFO != NULL)
    {
        FIFO_t *pxOperatingFIFO = (FIFO_t *)pxFIFO;

        char *pcStartLine = (char *)((char *)pxOperatingFIFO + sizeof(FIFO_t));
        char *pcEndLine = (char *)((char *)pxOperatingFIFO + pxOperatingFIFO->usTotalSizeInByte);

        if (usSize <= pxOperatingFIFO->usFreeSizeInByte)
        {
            pxOperatingFIFO->usFreeSizeInByte -= usSize;

            while (usSize--)
            {
                *((char *)pxOperatingFIFO->pxBlockUnused)++ = *((char *)pvSrc)++;

                if (pxOperatingFIFO->pxBlockUnused == pcEndLine)
                {
                    pxOperatingFIFO->pxBlockUnused = pcStartLine;
                }
            }

            return (ErrorStatus)(SUCCESS);
        }
    }

    return (ErrorStatus)(ERROR);
}