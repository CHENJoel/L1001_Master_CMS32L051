#include "Function_Init.H"
#include "flashapp.H"
#include "flash.h"
#include "wdt.h"

#ifdef FLASHSPI_EN /*片外flash读写*/
/*
 * @Description: 在片外flash的指定位置插入数据
 * @param: 源数据的指针
 * @param: 被写地址
 * @param: 被写的数量(限4096)
 * @return: 无
 */
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
        WDT_Restart();
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

/*
 * @Description: 擦除片外flash指定位置的数据
 * @param: 擦数据的首地址
 * @param: 擦除数量
 * @return: 无
 */
void FlashSPI_Erase(uint32_t adr, uint16_t size)
{
    uint32_t perase;                        // 被擦地址
    uint32_t i;                             // 已擦数量
    uint32_t pageaddr;                      // 当前页首地址
    uint32_t pageoffset;                    // 页内偏移地址
    uint32_t pageremain;                    // 页内剩余空间
    uint32_t eraseremain;                   // 目标剩余被擦
    uint8_t flashbuffer[FLASHSPI_PageSize]; // 暂存,大小为flash的页大小
    perase = adr;
    for (i = 0; i < size;)
    {
        WDT_Restart();
        pageoffset = perase % FLASHSPI_PageSize; // 页内偏移地址
        pageaddr = perase - pageoffset;          // 当前页首地址
        pageremain = sizeof(flashbuffer) - pageoffset;
        eraseremain = size - i;
        if (pageremain >= eraseremain) // 当前页可以完成剩余擦除工作
        {
            if (eraseremain == sizeof(flashbuffer)) // 当前整页需被擦完：...][xxxxxxxxxx][...
            {
                FLASHSPI_PageErase(perase);
            }
            else // [xxx.......]/[.......xxx]/[...xxxx...]
            {
                FLASHSPI_PageRead(flashbuffer, pageaddr, sizeof(flashbuffer));  // 暂存原来Flash本页里的数据
                memset(&flashbuffer[pageoffset], 0xFF, eraseremain);            // 被擦除区域抹除数据
                FLASHSPI_PageErase(pageaddr);                                   // 擦除本页
                FLASHSPI_PageWrite(flashbuffer, pageaddr, sizeof(flashbuffer)); // 写入修改后的页内
            }
            perase += eraseremain;
            i += eraseremain;
        }
        else // 擦完本页，还需擦下页
        {
            if (pageremain == sizeof(flashbuffer)) // 当前整页需被擦完：  [xxxxxxxxxx][xxx
            {
                FLASHSPI_PageErase(perase);
            }
            else //  [.......xxx][xxx
            {
                FLASHSPI_PageRead(flashbuffer, pageaddr, sizeof(flashbuffer));  // 暂存原来Flash本页里的数据
                memset(&flashbuffer[pageoffset], 0xFF, pageremain);             // 被擦除区域抹除数据
                FLASHSPI_PageErase(pageaddr);                                   // 擦除本页
                FLASHSPI_PageWrite(flashbuffer, pageaddr, sizeof(flashbuffer)); // 写入修改后的页内
            }
            perase += pageremain;
            i += pageremain;
        }
    }
}
#endif

/*==============================================================================================================================*/

#ifdef FLASHROM_EN /*片内flash读写*/

/*
 * @Description: 在片内flash的指定位置插入数据
 * @param: 源数据的指针
 * @param: 被写地址
 * @param: 被写的数量(限4096)
 * @return: 无
 */
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
        WDT_Restart();
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
/*
 * @Description: 擦除片内flash指定位置的数据
 * @param: 擦数据的首地址
 * @param: 擦除数量
 * @return: 无
 */
void FlashROM_Erase(uint32_t adr, uint16_t size)
{
    uint32_t perase;                        // 被擦地址
    uint32_t i;                             // 已擦数量
    uint32_t pageaddr;                      // 当前页首地址
    uint32_t pageoffset;                    // 页内偏移地址
    uint32_t pageremain;                    // 页内剩余空间
    uint32_t eraseremain;                   // 目标剩余被擦
    uint8_t flashbuffer[FLASHROM_PageSize]; // 暂存,大小为flash的页大小
    perase = adr;
    for (i = 0; i < size;)
    {
        WDT_Restart();
        pageoffset = perase % FLASHROM_PageSize; // 页内偏移地址
        pageaddr = perase - pageoffset;          // 当前页首地址
        pageremain = sizeof(flashbuffer) - pageoffset;
        eraseremain = size - i;

        if (pageremain >= eraseremain) // 当前页可以完成剩余擦除工作
        {
            if (eraseremain == sizeof(flashbuffer)) // 当前整页需被擦完：...][xxxxxxxxxx][...
            {
                FLASHROM_PageErase(perase);
            }
            else // [xxx.......]/[.......xxx]/[...xxxx...]
            {
                FLASHROM_PageRead(flashbuffer, pageaddr, sizeof(flashbuffer));  // 暂存原来Flash本页里的数据
                memset(&flashbuffer[pageoffset], 0xFF, eraseremain);            // 被擦除区域抹除数据
                FLASHROM_PageErase(pageaddr);                                   // 擦除本页
                FLASHROM_PageWrite(flashbuffer, pageaddr, sizeof(flashbuffer)); // 写入修改后的页内
            }
            perase += eraseremain;
            i += eraseremain;
        }
        else // 擦完本页，还需擦下页
        {
            if (pageremain == sizeof(flashbuffer)) // 当前整页需被擦完：  [xxxxxxxxxx][xxx
            {
                FLASHROM_PageErase(perase);
            }
            else //  [.......xxx][xxx
            {
                FLASHROM_PageRead(flashbuffer, pageaddr, sizeof(flashbuffer));  // 暂存原来Flash本页里的数据
                memset(&flashbuffer[pageoffset], 0xFF, pageremain);             // 被擦除区域抹除数据
                FLASHROM_PageErase(pageaddr);                                   // 擦除本页
                FLASHROM_PageWrite(flashbuffer, pageaddr, sizeof(flashbuffer)); // 写入修改后的页内
            }
            perase += pageremain;
            i += pageremain;
        }
    }
}

/*
 * @Description: 读出片内flash的数据
 * @param: 缓存指针
 * @param: 读地址
 * @param: 读数量
 * @return: 无
 */
void FlashROM_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint8_t *sur, *tar;
    WDT_Restart();
    sur = (uint8_t *)ReadAddr;
    tar = pBuffer;
    memcpy(tar, sur, NumByteToRead); // 拷贝新数据
}
#endif

/*==============================================================================================================================*/

/*
 * @Description: 自动保存被修改的数据
 * @param: 源数据指针
 * @param: 目标数据指针
 * @param: 对比数量
 * @return: 无
 */
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
