#include "Function_Init.H"
#include "flashapp.H"
#include "flash.h"

#ifdef FLASHSPI_EN /*Ƭ��flash��д*/
/*
    Դ���ݵ�ָ��
    ��д��ַ
    Ҫд����ֽ���(��4096)
*/
// ��ָ��flash��ַ��������
void FlashSPI_Insert(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint32_t pwrite; // дflash��ָ��
    uint16_t pread;  // Դ���ݴ�����ȡ��ָ�루��д���ֽ�����
    uint8_t *sur, *tar;
    uint32_t pageAddr;                      // ��ǰҳ�׵�ַ
    uint16_t pageOffset;                    // ҳ��ƫ�Ƶ�ַ
    uint16_t pageRemain;                    // ��ǰҳ��ʣ��ռ�
    uint16_t writeRemain;                   // ʣ����д�ֽ���
    uint8_t flashbuffer[FLASHSPI_PageSize]; // �ݴ�,��СΪflash��ҳ��С
    pwrite = WriteAddr;
    for (pread = 0; pread < NumByteToWrite;)
    {
        pageOffset = pwrite % sizeof(flashbuffer);     // ҳ��ƫ�Ƶ�ַ
        pageAddr = pwrite - pageOffset;                // ��ǰҳ�׵�ַ
        pageRemain = sizeof(flashbuffer) - pageOffset; // ҳ��ʣ��ռ�(�����Ա�д�����ݵĿռ�)
        writeRemain = NumByteToWrite - pread;          // ��δ��д���ֽ���

        sur = pBuffer + pread;          // ��ȡԴ���ݵĵ�N������
        tar = flashbuffer + pageOffset; // �޸ĵ�ǰҳƫ�Ƶ�ַ�ϵ�����
        if (pageRemain >= writeRemain)  // ��ǰҳ����д��ʣ�����ݣ�д��ʣ�����ݣ���д�ռ�>=��д������
        {
            if (pageOffset != 0 || writeRemain != sizeof(flashbuffer)) // ƫ��Ϊ0���Ҹպ���д����ҳ������ʱ������Ҫ����flashԭ��������,ֱ�Ӹ��������ݻ��漴��
            {
                FLASHSPI_PageRead(flashbuffer, pageAddr, sizeof(flashbuffer)); // �ݴ�ԭ��Flash��ҳ�������
            }
            memcpy(tar, sur, writeRemain);                                  // ����������
            FLASHSPI_PageErase(pageAddr);                                   // ������ҳ
            FLASHSPI_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer)); // д���޸ĺ��ҳ����
            pwrite += writeRemain;                                          // ָ��ƫ����д���ֽ���
            pread += writeRemain;                                           // ָ��ƫ����д���ֽ���
        }
        else // ��ǰҳд����,��д����ǰҳ����д�ռ�<��д������
        {
            if (pageOffset != 0 || pageRemain != sizeof(flashbuffer)) // ƫ��Ϊ0���Ҹպ���д����ҳ������ʱ������Ҫ����flashԭ��������
            {
                FLASHSPI_PageRead(flashbuffer, pageAddr, sizeof(flashbuffer)); // �ݴ�ԭ��Flash��ҳ�������
            }
            memcpy(tar, sur, pageRemain);                                   // ����������
            FLASHSPI_PageErase(pageAddr);                                   // ������ҳ
            FLASHSPI_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer)); // д���޸ĺ��ҳ����
            pwrite += pageRemain;                                           // ָ��ƫ����д���ֽ���
            pread += pageRemain;                                            // ָ��ƫ����д���ֽ���
        }
    }
}




#endif

#ifdef FLASHROM_EN /*Ƭ��flash��д*/

/*
    ����ָ��
    ������ַ
    Ҫ�������ֽ���(��4096)
*/
void FlashROM_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint8_t *sur, *tar;
    sur = (uint8_t *)ReadAddr;
    tar = pBuffer;
    memcpy(tar, sur, NumByteToRead); // ����������
}

/*
    Դ���ݵ�ָ��
    ��д��ַ
    Ҫд����ֽ���(��4096)
*/
// ��ָ��flash��ַ��������
void FlashROM_Insert(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint32_t pwrite; // дflash��ָ��
    uint16_t pread;  // Դ���ݴ�����ȡ��ָ�루��д���ֽ�����
    uint8_t *sur, *tar;
    uint32_t pageAddr;                      // ��ǰҳ�׵�ַ
    uint16_t pageOffset;                    // ҳ��ƫ�Ƶ�ַ
    uint16_t pageRemain;                    // ��ǰҳ��ʣ��ռ�
    uint16_t writeRemain;                   // ʣ����д�ֽ���
    uint8_t flashbuffer[FLASHROM_PageSize]; // �ݴ�,��СΪflash��ҳ��С
    pwrite = WriteAddr;
    for (pread = 0; pread < NumByteToWrite;)
    {
        pageOffset = pwrite % sizeof(flashbuffer);     // ҳ��ƫ�Ƶ�ַ
        pageAddr = pwrite - pageOffset;                // ��ǰҳ�׵�ַ
        pageRemain = sizeof(flashbuffer) - pageOffset; // ҳ��ʣ��ռ�(�����Ա�д�����ݵĿռ�)
        writeRemain = NumByteToWrite - pread;          // ��δ��д���ֽ���

        sur = pBuffer + pread;          // ��ȡԴ���ݵĵ�N������
        tar = flashbuffer + pageOffset; // �޸ĵ�ǰҳƫ�Ƶ�ַ�ϵ�����
        if (pageRemain >= writeRemain)  // ��ǰҳ����д��ʣ�����ݣ�д��ʣ�����ݣ���д�ռ�>=��д������
        {
            if (pageOffset != 0 || writeRemain != sizeof(flashbuffer)) // ƫ��Ϊ0���Ҹպ���д����ҳ������ʱ������Ҫ����flashԭ��������,ֱ�Ӹ��������ݻ��漴��
            {
                FLASHROM_PageRead(flashbuffer, pageAddr, sizeof(flashbuffer)); // �ݴ�ԭ��Flash��ҳ�������
            }
            memcpy(tar, sur, writeRemain);                                  // ����������
            FLASHROM_PageErase(pageAddr);                                   // ������ҳ
            FLASHROM_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer)); // д���޸ĺ��ҳ����
            pwrite += writeRemain;                                          // ָ��ƫ����д���ֽ���
            pread += writeRemain;                                           // ָ��ƫ����д���ֽ���
        }
        else // ��ǰҳд����,��д����ǰҳ����д�ռ�<��д������
        {
            if (pageOffset != 0 || pageRemain != sizeof(flashbuffer)) // ƫ��Ϊ0���Ҹպ���д����ҳ������ʱ������Ҫ����flashԭ��������
            {
                FLASHROM_PageRead(flashbuffer, pageAddr, sizeof(flashbuffer)); // �ݴ�ԭ��Flash��ҳ�������
            }
            memcpy(tar, sur, pageRemain);                                   // ����������
            FLASHROM_PageErase(pageAddr);                                   // ������ҳ
            FLASHROM_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer)); // д���޸ĺ��ҳ����
            pwrite += pageRemain;                                           // ָ��ƫ����д���ֽ���
            pread += pageRemain;                                            // ָ��ƫ����д���ֽ���
        }
    }
}
#endif

/*******************************************************************************/
/*�Զ�����ָ������*/
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
        if (*psur != *pmem) // ���ݲ�ƥ��
        {
            flag = 1;
            break;
        }
        psur++;
        pmem++;
    }
    if (flag)
    {
        FlashROM_Insert(sur, (uint32_t)mem, size); // �������ݴ洢������
    }
}
