#include "Function_Init.H"
/*

#define W25_CS_ENABLE()         {W25_CS(0); us_delay(10);}
#define W25_CS_DISABLE()        {W25_CS(1); us_delay(10);}
#define SPI_Delay()             us_delay(1)

FLASH_SectorErase(0);           ʵ�� 9.12ms
FLASH_PageWrite(buf, 0, 256);   ʵ�� 18ms
FLASH_BufferRead(bufR, 0, 256); ʵ�� 16.7ms

*/

SysRecord_TypeDef SysRecord;
EffectInf_TypeDef EffectInf;
/*

��ӡNorFlash�Ĵ洢����
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
���ڲ���NorFalsh��ĳ��ַ�Ķ�д
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
    FLASH_BufferRead(bufR, addr - (sizeof(buf) / 2), sizeof(bufR)); // �ݴ�ԭ��Flash��ҳ�������
    Print_HEX16(addr - (sizeof(buf) / 2), bufR, sizeof(bufR));
}

/*
    Դ���ݵ�ָ��
    ��д��ַ
    Ҫд����ֽ���(��4096)
*/
void FlashSPI_Write(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint32_t pwrite; // дflash��ָ��
    uint16_t pread;  // Դ���ݴ�����ȡ��ָ�루��д���ֽ�����
    uint8_t *sur, *tar;
    uint32_t pageAddr;                       // ��ǰҳ�׵�ַ
    uint16_t pageOffset;                     // ҳ��ƫ�Ƶ�ַ
    uint16_t pageRemain;                     // ��ǰҳ��ʣ��ռ�
    uint16_t writeRemain;                    // ʣ����д�ֽ���
    uint8_t flashbuffer[SPI_FLASH_PageSize]; // �ݴ�
    pwrite = WriteAddr;
    for (pread = 0; pread < NumByteToWrite;)
    {
        pageOffset = pwrite % SPI_FLASH_PageSize;                     // ҳ��ƫ�Ƶ�ַ
        pageAddr = pwrite - pageOffset;                               // ��ǰҳ�׵�ַ
        pageRemain = SPI_FLASH_PageSize - pageOffset;                 // ҳ��ʣ��ռ�
        writeRemain = NumByteToWrite - pread;                         // ��δ��д���ֽ���
        FLASH_BufferRead(flashbuffer, pageAddr, sizeof(flashbuffer)); // �ݴ�ԭ��Flash��ҳ�������
        sur = pBuffer + pread;                                        // ��ȡԴ���ݵĵ�N������
        tar = flashbuffer + pageOffset;                               // �޸ĵ�ǰҳƫ�Ƶ�ַ�ϵ�����
        if (pageRemain >= writeRemain)                                // ��ǰҳ����д��ʣ�����ݣ�д��ʣ������
        {
            memcpy(tar, sur, writeRemain);                               // ����������
            FLASH_PageErase(pageAddr);                                   // ������ҳ
            FLASH_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer)); // д���޸ĺ��ҳ����
            pwrite += writeRemain;                                       // ָ��ƫ����д���ֽ���
            pread += writeRemain;                                        // ָ��ƫ����д���ֽ���
        }
        else // ��ǰҳд����,��д����ǰҳ
        {
            memcpy(tar, sur, pageRemain);                                // ����������
            FLASH_PageErase(pageAddr);                                   // ������ҳ
            FLASH_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer)); // д���޸ĺ��ҳ����
            pwrite += pageRemain;                                        // ָ��ƫ����д���ֽ���
            pread += pageRemain;                                         // ָ��ƫ����д���ֽ���
        }
    }
}

void ROM_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint8_t *sur, *tar;
    sur = (uint8_t *)ReadAddr;
    tar = pBuffer;
    memcpy(tar, sur, NumByteToRead); // ����������
}


/******************************************************************************************************************************************************************************************************************************************************************************/

void SYS_Record(void)
{
    FLASH_BufferRead((uint8_t *)&SysRecord, SYSDATA_BASE, sizeof(SysRecord)); // �ݴ�ԭ��Flash��ҳ�������
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
