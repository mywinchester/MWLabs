#ifndef __MWLABS_FIFO_H
#define __MWLABS_FIFO_H

#ifndef __MWLABS_COMMON_H
    #error include "common.h" must appear in source files before include "FIFO.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void *FIFOHandle_t;

FIFOHandle_t FIFO_Initialize(void *pvFIFOStorageArea, uint16_t usFIFOStorageSize);
FIFOHandle_t FIFO_Destroy(FIFOHandle_t pxFIFO);
uint16_t FIFO_UsedSpaceSize(FIFOHandle_t pxFIFO);
uint16_t FIFO_UnusedSpaceSize(FIFOHandle_t pxFIFO);
ErrorStatus FIFO_Read(FIFOHandle_t pxFIFO, void *pvDest, uint16_t usSize);
ErrorStatus FIFO_Write(FIFOHandle_t pxFIFO, const void *pvSrc, uint16_t usSize);

#ifdef __cplusplus
}
#endif

#endif /* __MWLABS_FIFO_H */