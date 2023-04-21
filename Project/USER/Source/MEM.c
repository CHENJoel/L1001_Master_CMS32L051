#include "Function_Init.H"
/*

#define W25_CS_ENABLE()         {W25_CS(0); us_delay(10);}
#define W25_CS_DISABLE()        {W25_CS(1); us_delay(10);}
#define SPI_Delay()             us_delay(1)

FLASH_SectorErase(0);           实测 9.12ms
FLASH_PageWrite(buf, 0, 256);   实测 18ms
FLASH_BufferRead(bufR, 0, 256); 实测 16.7ms

*/

SysRecord_TypeDef SysRecord;
EffectInf_TypeDef EffectInf;
/*

打印NorFlash的存储数据
*/
void Print_HEX16(uint32_t addr, uint8_t *sur, uint16_t size)
{
    uint16_t i;
    uint8_t j = 0;
    printf("\n");
    for (i = 0; i < size; i++)
    {
        if (j == 0)
        {
            printf("|0x%08x| ", addr+i);
        }
        printf("%2x ", *sur++);
        if (++j > 63)
        {
            j = 0;
            printf("\n");
        }
    }
    printf("\n");
}

void SPI_FlashDebug(void)
{

    // // // NorFalsh_RW_Test(0x4FFFFF);

    printf("Efdata_TypeDef");
    Print_StuctSize(Efdata_TypeDef);
    // printf("Efdata_TypeDef size:%d[0x%x]\r\n",sizeof(Efdata_TypeDef),sizeof(Efdata_TypeDef));
    // printf("Efdata_TypeDef size:%d[0x%x]\r\n",sizeof(Efdata_TypeDef),sizeof(Efdata_TypeDef));
    // // printf("size:%d[0x%x]|%d%%\r\n",sizeof(EffectInf_TypeDef),sizeof(EffectInf_TypeDef),(sizeof(EffectInf_TypeDef)*100)/0x10000);
}

/*
用于测试NorFalsh在某地址的读写
*/
void NorFalsh_RW_Test(uint32_t addr)
{
    uint8_t buf[0X100];
    uint8_t bufR[0X200];
    uint16_t i;
    static uint8_t hh;
    memset(&buf, 0, sizeof(buf));
    memset(&bufR, 0, sizeof(bufR));
    for (i = 0; i < sizeof(buf); i++)
    {
        buf[i] = hh;
    }
    hh++;
    FlashSPI_Write(buf, addr, sizeof(buf));
    FLASH_BufferRead(bufR, addr - (sizeof(buf) / 2), sizeof(bufR)); // 暂存原来Flash本页里的数据
    Print_HEX16(addr - (sizeof(buf) / 2), bufR, sizeof(bufR));
}

/*
    源数据的指针
    被写地址
    要写入的字节数(限4096)
*/
void FlashSPI_Write(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint32_t pwrite; // 写flash的指针
    uint16_t pread;  // 源数据待被读取的指针（已写的字节数）
    uint8_t *sur, *tar;
    uint32_t pageAddr;                       // 当前页首地址
    uint16_t pageOffset;                     // 页内偏移地址
    uint16_t pageRemain;                     // 当前页内剩余空间
    uint16_t writeRemain;                    // 剩余需写字节数
    uint8_t flashbuffer[SPI_FLASH_PageSize]; // 暂存
    pwrite = WriteAddr;
    for (pread = 0; pread < NumByteToWrite;)
    {
        pageOffset = pwrite % SPI_FLASH_PageSize;                     // 页内偏移地址
        pageAddr = pwrite - pageOffset;                               // 当前页首地址
        pageRemain = SPI_FLASH_PageSize - pageOffset;                 // 页内剩余空间
        writeRemain = NumByteToWrite - pread;                         // 还未被写的字节数
        FLASH_BufferRead(flashbuffer, pageAddr, sizeof(flashbuffer)); // 暂存原来Flash本页里的数据
        sur = pBuffer + pread;                                        // 读取源数据的第N个数据
        tar = flashbuffer + pageOffset;                               // 修改当前页偏移地址上的数据
        if (pageRemain >= writeRemain)                                // 当前页可以写完剩余数据，写完剩余数据
        {
            memcpy(tar, sur, writeRemain);                               // 拷贝新数据
            FLASH_PageErase(pageAddr);                                   // 擦除本页
            FLASH_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer)); // 写入修改后的页内容
            pwrite += writeRemain;                                       // 指针偏移已写的字节数
            pread += writeRemain;                                        // 指针偏移已写的字节数
        }
        else // 当前页写不完,先写满当前页
        {
            memcpy(tar, sur, pageRemain);                                // 拷贝新数据
            FLASH_PageErase(pageAddr);                                   // 擦除本页
            FLASH_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer)); // 写入修改后的页内容
            pwrite += pageRemain;                                        // 指针偏移已写的字节数
            pread += pageRemain;                                         // 指针偏移已写的字节数
        }
    }
}

void ROM_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint8_t *sur, *tar;
    sur = (uint8_t *)ReadAddr;
    tar = pBuffer;
    memcpy(tar, sur, NumByteToRead); // 拷贝新数据
}


/******************************************************************************************************************************************************************************************************************************************************************************/

void SYS_Record(void)
{
    FLASH_BufferRead((uint8_t *)&SysRecord, SYSDATA_BASE, sizeof(SysRecord)); // 暂存原来Flash本页里的数据
    if (SysRecord.verify == SysRecord_verify)
    {
        SysRecord.runtime++;
    }
    else
    {
        printf("verify %d\r\n", SysRecord.verify);
        SysRecord.verify = SysRecord_verify;
        SysRecord.runtime = 0;
        printf("reset SysRecord\r\n");
    }
    FlashSPI_Write((uint8_t *)&SysRecord, SYSDATA_BASE, sizeof(SysRecord));
    // // printf("run: %d S\r\n",SysRecord.runtime);
    /*FlashSPI_Write(SysRecord, SYSDATA_BASE + (uint32_t)&(((SysRecord_TypeDef *)0)->runtime),sizeof(flashdata.runtime));*/
}
