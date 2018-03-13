#ifndef __MWLABS_FIFO_H
#define __MWLABS_FIFO_H

#ifndef __MWLABS_COMMON_H
#error include "common.h" must appear in source files before include "FIFO.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void *FIFOHandle_t;

/**
 * FIFO.h
 * 
 FIFOHandle_t FIFO_Initialize(
                                    void *pvFIFOStorageArea,
                                    uint16_t usFIFOStorageSize
                                );

 * 使用外部数组及给定大小初始化一个FIFO队列，并返回对应的Handle。
 * !!! WARNING: 不要在中断中使用，这将导致未知的情况发生 !!!
 * 
 * @param pvFIFOStorageArea 一个未使用的存储空间，用户需自行开辟该空间，此空间可存在于
 * 直接寻址/无需程序干预的间接寻址的内部或外部RAM空间。在使用该空间作为FIFO区时，不要对
 * 此空间作另外的读写操作。
 * 
 * @param usFIFOStorageSize 作为FIFO队列的空间大小，由于FIFO队列需存储索引，故实际
 * 可存放的数据的大小将比声明的大小更小些（8位MUC上将占用10字节，即实际可用空间为：
 * usFIFOStorageSize - 10）
 * 
 * @return FIFOHandle_t 如果成功初始化该空间作为FIFO队列的使用空间，则会返回一个对应
 * FIFO队列的Handle。如果初始化失败（如传入空间的指针为NULL，或声明该空间的大小不足以
 * 完成对FIFO队列头部的初始化）时，将会返回一个NULL指针。
 * 
 * 示例:
 * 
    static unsigned char ucFIFObuffer[n];
    
    FIFOHandle_t fifo_handle = FIFO_Initialize(&ucFIFObuffer, sizeof(ucFIFObuffer));
    if (fifo_handle != NULL)
    {
        // ... do something
    }else
    {
        // 调整空间大小
    }
 * 
 */
FIFOHandle_t FIFO_Initialize(void *pvFIFOStorageArea, uint16_t usFIFOStorageSize);

/**
 * FIFO.h
 * 
 FIFOHandle_t FIFO_Destroy(
                                    FIFOHandle_t pxFIFO
                                );

 * 释放一个FIFO队列占用的空间，注意使用方式
 * !!! WARNING: 不要在中断中使用，这将导致未知的情况发生 !!!
 * 
 * @param pxFIFO 需要进行释放的FIFO队列
 * 
 * @return FIFOHandle_t 返回一个NULL值，需手动将其赋值给需要释放的FIFOHandle_t
 * 
 * 示例:
 * 
    static unsigned char ucFIFObuffer[n];
    
    FIFOHandle_t fifo_handle = FIFO_Initialize(&ucFIFObuffer, sizeof(ucFIFObuffer));
    // ... 完成FIFO队列需要做的工作，不再需要该FIFO队列
    
    fifo_handle = FIFO_Destroy(fifo_handle);
 * 
 * 注意，当FIFO_Destroy执行成功时，将返回一个NULL指针，将其赋值给需要释放的FIFOHandle_t变量，
 * 即可保证即使在接下来的程序段中使用到该FIFOHandle_t变量，也不会对被释放的空间进行读写操作。
 * 
 */
FIFOHandle_t FIFO_Destroy(FIFOHandle_t pxFIFO);

/**
 * FIFO.h
 * 
 uint16_t FIFO_UsedSpaceSize(
                                    FIFOHandle_t pxFIFO
                                );

 * 查看FIFO队列的已用空间
 * 
 * @param pxFIFO 需要查看已用空间的FIFO队列
 * 
 * @return uint16_t 返回已用空间大小
 * 
 * 示例:
 * 
    static unsigned char ucFIFObuffer[n];
    
    FIFOHandle_t fifo_handle = FIFO_Initialize(&ucFIFObuffer, sizeof(ucFIFObuffer));
    
    unsigned short fifo_been_used = FIFO_UsedSpaceSize(fifo_handle);
 * 
 */
uint16_t FIFO_UsedSpaceSize(FIFOHandle_t pxFIFO);

/**
 * FIFO.h
 * 
 uint16_t FIFO_UnusedSpaceSize(
                                    FIFOHandle_t pxFIFO
                                );

 * 查看FIFO队列的可用空间，该可用空间将比声明的FIFO队列空间略小
 * 
 * @param pxFIFO 需要查看可用空间的FIFO队列
 * 
 * @return uint16_t 返回可用空间大小
 * 
 * 示例:
 * 
    static unsigned char ucFIFObuffer[n];
    
    FIFOHandle_t fifo_handle = FIFO_Initialize(&ucFIFObuffer, sizeof(ucFIFObuffer));
    
    unsigned short fifo_can_used = FIFO_UsedSpaceSize(fifo_handle);
 * 
 */
uint16_t FIFO_UnusedSpaceSize(FIFOHandle_t pxFIFO);

/**
 * FIFO.h
 * 
 uint16_t FIFO_Read(
                                    FIFOHandle_t pxFIFO,
                                    void *pvDest,
                                    uint16_t usSize
                                );

 * 读取FIFO队列中的数据，并将数据出队。要求读取的数据量（usSize）可以比FIFO队列总长度更大，
 * 此时在FIFO队列被完全读出后，读取到的数据量将比要求数据量等于或更小。
 * !!! WARNING: 不要在中断中使用，这将导致未知的情况发生 !!!
 * 
 * @param pxFIFO 需要操作的FIFO队列
 * 
 * @param pvDest 外部BUFF区指针。在调用FIFO读取函数成功后，FIFO队列中数据将按一定长度连续写入
 * 该指针指向的直接寻址/无需程序干预的间接寻址的内部或外部RAM空间。使用前确保该指针指向的空间
 * 足够，并且在FIFO读取过程中不对目标空间进行读写操作
 * 
 * @param usSize 需要读取FIFO队列的数据个数，按字节计数。当FIFO队列中数据被完全读取且未达到
 * usSize约定大小时，仍视作读取成功
 * 
 * @return uint16_t 返回读取数量。在FIFO队列未被完全读出时，返回值将与要求读取的数据量一致。
 * 在FIFO队列被完全读出时，返回值将小于或等于要求读取的数据量。在没有数据被读出时，返回NULL值
 * 
 * 示例:
 * 
    static unsigned char ucFIFObuffer[n];

    FIFOHandle_t fifo_handle = FIFO_Initialize(&ucFIFObuffer, sizeof(ucFIFObuffer));

    if (FIFO_UsedSpaceSize(fifo_handle) != NULL)
    {
        unsigned char operating_data[m];
        unsigned short read_number;
        read_number = FIFO_Read(fifo_handle, &operating_data, sizeof(operating_data));

        if (read_number <= sizeof(operating_data))
        {
            // ... using operating_data
        }
        else
        {
            // ...
        }
    }
    else
    {
        // ... waiting data incoming
    }
 * 
 */
uint16_t FIFO_Read(FIFOHandle_t pxFIFO, void *pvDest, uint16_t usSize);

/**
 * FIFO.h
 * 
 ErrorStatus FIFO_Write(
                                    FIFOHandle_t pxFIFO,
                                    void *pvDest,
                                    uint16_t usSize
                                );

 * 将规定长度的数据写入至FIFO区
 * !!! WARNING: 不要在中断中使用，这将导致未知的情况发生 !!!
 * 
 * @param pxFIFO 需要操作的FIFO队列
 * 
 * @param pvDest 指向需要写入的数据的指针。在调用FIFO写入函数成功后，该指针指向的
 * 直接寻址/无需程序干预的间接寻址的内部或外部RAM空间中的数据将被直接写入FIFO队列中。
 * 
 * @param usSize 需要写入FIFO队列的字节数
 * 
 * @return ErrorStatus 写入成功时返回SUCCESS，否则返回ERROR
 * 
 * 示例:
 * 
    static unsigned char ucFIFObuffer[n];

    FIFOHandle_t fifo_handle = FIFO_Initialize(&ucFIFObuffer, sizeof(ucFIFObuffer));

    unsigned char write_data[m];

    // write_data incoming

    if (FIFO_UnusedSpaceSize(fifo_handle) >= sizeof(write_data))
    {
        ErrorStatus state;
        state = FIFO_Write(fifo_handle, &write_data, sizeof(write_data));

        if (ERROR == state)
        {
            // error handler...
        }
    }
    else
    {
        // ... 
    }
 * 
 */
ErrorStatus FIFO_Write(FIFOHandle_t pxFIFO, const void *pvSrc, uint16_t usSize);

#ifdef __cplusplus
}
#endif

#endif /* __MWLABS_FIFO_H */