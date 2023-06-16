#include "Function_Init.H"
#include "flashapp.H"
#include "flash.h"

#ifdef FLASHSPI_EN /*片外flash读写*/
/*
    源数据的指针
    被写地址
    要写入的字节数(限4096)
*/
// 在指定flash地址插入数据
void FlashSPI_Insert(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint32_t pwrite; // 写flash的指针
    uint16_t pread;  // 源数据待被读取的指针（已写的字节数）
    uint8_t *sur, *tar;
    uint32_t pageAddr;                      // 当前页首地址
    uint16_t pageOffset;                    // 页内偏移地址
    uint16_t pageRemain;                    // 当前页内剩余空间
    uint16_t writeRemain;                   // 剩余需写字节数
    uint8_t flashbuffer[FLASHSPI_PageSize]; // 暂存,大小为flash的页大小
    pwrite = WriteAddr;
    for (pread = 0; pread < NumByteToWrite;)
    {
        pageOffset = pwrite % sizeof(flashbuffer);     // 页内偏移地址
        pageAddr = pwrite - pageOffset;                // 当前页首地址
        pageRemain = sizeof(flashbuffer) - pageOffset; // 页内剩余空间(还可以被写新数据的空间)
        writeRemain = NumByteToWrite - pread;          // 还未被写的字节数

        sur = pBuffer + pread;          // 读取源数据的第N个数据
        tar = flashbuffer + pageOffset; // 修改当前页偏移地址上的数据
        if (pageRemain >= writeRemain)  // 当前页可以写完剩余数据，写完剩余数据（可写空间>=需写数量）
        {
            if (pageOffset != 0 || writeRemain != sizeof(flashbuffer)) // 偏移为0，且刚好是写满整页新数据时，则不需要读出flash原来的数据,直接覆盖新数据缓存即可
            {
                FLASHSPI_PageRead(flashbuffer, pageAddr, sizeof(flashbuffer)); // 暂存原来Flash本页里的数据
            }
            memcpy(tar, sur, writeRemain);                                  // 拷贝新数据
            FLASHSPI_PageErase(pageAddr);                                   // 擦除本页
            FLASHSPI_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer)); // 写入修改后的页内容
            pwrite += writeRemain;                                          // 指针偏移已写的字节数
            pread += writeRemain;                                           // 指针偏移已写的字节数
        }
        else // 当前页写不完,先写满当前页（可写空间<需写数量）
        {
            if (pageOffset != 0 || pageRemain != sizeof(flashbuffer)) // 偏移为0，且刚好是写满整页新数据时，则不需要读出flash原来的数据
            {
                FLASHSPI_PageRead(flashbuffer, pageAddr, sizeof(flashbuffer)); // 暂存原来Flash本页里的数据
            }
            memcpy(tar, sur, pageRemain);                                   // 拷贝新数据
            FLASHSPI_PageErase(pageAddr);                                   // 擦除本页
            FLASHSPI_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer)); // 写入修改后的页内容
            pwrite += pageRemain;                                           // 指针偏移已写的字节数
            pread += pageRemain;                                            // 指针偏移已写的字节数
        }
    }
}




#endif

#ifdef FLASHROM_EN /*片内flash读写*/

/*
    缓存指针
    被读地址
    要读出的字节数(限4096)
*/
void FlashROM_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint8_t *sur, *tar;
    sur = (uint8_t *)ReadAddr;
    tar = pBuffer;
    memcpy(tar, sur, NumByteToRead); // 拷贝新数据
}

/*
    源数据的指针
    被写地址
    要写入的字节数(限4096)
*/
// 在指定flash地址插入数据
void FlashROM_Insert(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint32_t pwrite; // 写flash的指针
    uint16_t pread;  // 源数据待被读取的指针（已写的字节数）
    uint8_t *sur, *tar;
    uint32_t pageAddr;                      // 当前页首地址
    uint16_t pageOffset;                    // 页内偏移地址
    uint16_t pageRemain;                    // 当前页内剩余空间
    uint16_t writeRemain;                   // 剩余需写字节数
    uint8_t flashbuffer[FLASHROM_PageSize]; // 暂存,大小为flash的页大小
    pwrite = WriteAddr;
    for (pread = 0; pread < NumByteToWrite;)
    {
        pageOffset = pwrite % sizeof(flashbuffer);     // 页内偏移地址
        pageAddr = pwrite - pageOffset;                // 当前页首地址
        pageRemain = sizeof(flashbuffer) - pageOffset; // 页内剩余空间(还可以被写新数据的空间)
        writeRemain = NumByteToWrite - pread;          // 还未被写的字节数

        sur = pBuffer + pread;          // 读取源数据的第N个数据
        tar = flashbuffer + pageOffset; // 修改当前页偏移地址上的数据
        if (pageRemain >= writeRemain)  // 当前页可以写完剩余数据，写完剩余数据（可写空间>=需写数量）
        {
            if (pageOffset != 0 || writeRemain != sizeof(flashbuffer)) // 偏移为0，且刚好是写满整页新数据时，则不需要读出flash原来的数据,直接覆盖新数据缓存即可
            {
                FLASHROM_PageRead(flashbuffer, pageAddr, sizeof(flashbuffer)); // 暂存原来Flash本页里的数据
            }
            memcpy(tar, sur, writeRemain);                                  // 拷贝新数据
            FLASHROM_PageErase(pageAddr);                                   // 擦除本页
            FLASHROM_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer)); // 写入修改后的页内容
            pwrite += writeRemain;                                          // 指针偏移已写的字节数
            pread += writeRemain;                                           // 指针偏移已写的字节数
        }
        else // 当前页写不完,先写满当前页（可写空间<需写数量）
        {
            if (pageOffset != 0 || pageRemain != sizeof(flashbuffer)) // 偏移为0，且刚好是写满整页新数据时，则不需要读出flash原来的数据
            {
                FLASHROM_PageRead(flashbuffer, pageAddr, sizeof(flashbuffer)); // 暂存原来Flash本页里的数据
            }
            memcpy(tar, sur, pageRemain);                                   // 拷贝新数据
            FLASHROM_PageErase(pageAddr);                                   // 擦除本页
            FLASHROM_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer)); // 写入修改后的页内容
            pwrite += pageRemain;                                           // 指针偏移已写的字节数
            pread += pageRemain;                                            // 指针偏移已写的字节数
        }
    }
}
#endif

/*******************************************************************************/
/*自动保存指定数据*/
void ROMdata_autosave(uint8_t *sur, uint8_t *mem, uint32_t size)
{
    uint32_t i;
    uint8_t *psur;
    uint8_t *pmem;
    uint8_t flag = 0;
    psur = sur;
    pmem = mem;
    for (i = 0; i < size; i++)
    {
        if (*psur != *pmem) // 数据不匹配
        {
            flag = 1;
            break;
        }
        psur++;
        pmem++;
    }
    if (flag)
    {
        FlashROM_Insert(sur, (uint32_t)mem, size); // 将新数据存储至闪存
    }
}
