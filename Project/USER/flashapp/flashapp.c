#include "Function_Init.H"
#include "flashapp.H"
#include "flash.h"
#include "wdt.h"

#ifdef FLASHSPI_EN /*Ƭ��flash��д*/
/*
 * @Description: ��Ƭ��flash��ָ��λ�ò�������
 * @param: Դ���ݵ�ָ��
 * @param: ��д��ַ
 * @param: ��д������(��4096)
 * @return: ��
 */
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
        WDT_Restart();
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

/*
 * @Description: ����Ƭ��flashָ��λ�õ�����
 * @param: �����ݵ��׵�ַ
 * @param: ��������
 * @return: ��
 */
void FlashSPI_Erase(uint32_t adr, uint16_t size)
{
    uint32_t perase;                        // ������ַ
    uint32_t i;                             // �Ѳ�����
    uint32_t pageaddr;                      // ��ǰҳ�׵�ַ
    uint32_t pageoffset;                    // ҳ��ƫ�Ƶ�ַ
    uint32_t pageremain;                    // ҳ��ʣ��ռ�
    uint32_t eraseremain;                   // Ŀ��ʣ�౻��
    uint8_t flashbuffer[FLASHSPI_PageSize]; // �ݴ�,��СΪflash��ҳ��С
    perase = adr;
    for (i = 0; i < size;)
    {
        WDT_Restart();
        pageoffset = perase % FLASHSPI_PageSize; // ҳ��ƫ�Ƶ�ַ
        pageaddr = perase - pageoffset;          // ��ǰҳ�׵�ַ
        pageremain = sizeof(flashbuffer) - pageoffset;
        eraseremain = size - i;
        if (pageremain >= eraseremain) // ��ǰҳ�������ʣ���������
        {
            if (eraseremain == sizeof(flashbuffer)) // ��ǰ��ҳ�豻���꣺...][xxxxxxxxxx][...
            {
                FLASHSPI_PageErase(perase);
            }
            else // [xxx.......]/[.......xxx]/[...xxxx...]
            {
                FLASHSPI_PageRead(flashbuffer, pageaddr, sizeof(flashbuffer));  // �ݴ�ԭ��Flash��ҳ�������
                memset(&flashbuffer[pageoffset], 0xFF, eraseremain);            // ����������Ĩ������
                FLASHSPI_PageErase(pageaddr);                                   // ������ҳ
                FLASHSPI_PageWrite(flashbuffer, pageaddr, sizeof(flashbuffer)); // д���޸ĺ��ҳ��
            }
            perase += eraseremain;
            i += eraseremain;
        }
        else // ���걾ҳ���������ҳ
        {
            if (pageremain == sizeof(flashbuffer)) // ��ǰ��ҳ�豻���꣺  [xxxxxxxxxx][xxx
            {
                FLASHSPI_PageErase(perase);
            }
            else //  [.......xxx][xxx
            {
                FLASHSPI_PageRead(flashbuffer, pageaddr, sizeof(flashbuffer));  // �ݴ�ԭ��Flash��ҳ�������
                memset(&flashbuffer[pageoffset], 0xFF, pageremain);             // ����������Ĩ������
                FLASHSPI_PageErase(pageaddr);                                   // ������ҳ
                FLASHSPI_PageWrite(flashbuffer, pageaddr, sizeof(flashbuffer)); // д���޸ĺ��ҳ��
            }
            perase += pageremain;
            i += pageremain;
        }
    }
}
#endif

/*==============================================================================================================================*/

#ifdef FLASHROM_EN /*Ƭ��flash��д*/

/*
 * @Description: ��Ƭ��flash��ָ��λ�ò�������
 * @param: Դ���ݵ�ָ��
 * @param: ��д��ַ
 * @param: ��д������(��4096)
 * @return: ��
 */
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
        WDT_Restart();
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
/*
 * @Description: ����Ƭ��flashָ��λ�õ�����
 * @param: �����ݵ��׵�ַ
 * @param: ��������
 * @return: ��
 */
void FlashROM_Erase(uint32_t adr, uint16_t size)
{
    uint32_t perase;                        // ������ַ
    uint32_t i;                             // �Ѳ�����
    uint32_t pageaddr;                      // ��ǰҳ�׵�ַ
    uint32_t pageoffset;                    // ҳ��ƫ�Ƶ�ַ
    uint32_t pageremain;                    // ҳ��ʣ��ռ�
    uint32_t eraseremain;                   // Ŀ��ʣ�౻��
    uint8_t flashbuffer[FLASHROM_PageSize]; // �ݴ�,��СΪflash��ҳ��С
    perase = adr;
    for (i = 0; i < size;)
    {
        WDT_Restart();
        pageoffset = perase % FLASHROM_PageSize; // ҳ��ƫ�Ƶ�ַ
        pageaddr = perase - pageoffset;          // ��ǰҳ�׵�ַ
        pageremain = sizeof(flashbuffer) - pageoffset;
        eraseremain = size - i;

        if (pageremain >= eraseremain) // ��ǰҳ�������ʣ���������
        {
            if (eraseremain == sizeof(flashbuffer)) // ��ǰ��ҳ�豻���꣺...][xxxxxxxxxx][...
            {
                FLASHROM_PageErase(perase);
            }
            else // [xxx.......]/[.......xxx]/[...xxxx...]
            {
                FLASHROM_PageRead(flashbuffer, pageaddr, sizeof(flashbuffer));  // �ݴ�ԭ��Flash��ҳ�������
                memset(&flashbuffer[pageoffset], 0xFF, eraseremain);            // ����������Ĩ������
                FLASHROM_PageErase(pageaddr);                                   // ������ҳ
                FLASHROM_PageWrite(flashbuffer, pageaddr, sizeof(flashbuffer)); // д���޸ĺ��ҳ��
            }
            perase += eraseremain;
            i += eraseremain;
        }
        else // ���걾ҳ���������ҳ
        {
            if (pageremain == sizeof(flashbuffer)) // ��ǰ��ҳ�豻���꣺  [xxxxxxxxxx][xxx
            {
                FLASHROM_PageErase(perase);
            }
            else //  [.......xxx][xxx
            {
                FLASHROM_PageRead(flashbuffer, pageaddr, sizeof(flashbuffer));  // �ݴ�ԭ��Flash��ҳ�������
                memset(&flashbuffer[pageoffset], 0xFF, pageremain);             // ����������Ĩ������
                FLASHROM_PageErase(pageaddr);                                   // ������ҳ
                FLASHROM_PageWrite(flashbuffer, pageaddr, sizeof(flashbuffer)); // д���޸ĺ��ҳ��
            }
            perase += pageremain;
            i += pageremain;
        }
    }
}

/*
 * @Description: ����Ƭ��flash������
 * @param: ����ָ��
 * @param: ����ַ
 * @param: ������
 * @return: ��
 */
void FlashROM_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint8_t *sur, *tar;
    WDT_Restart();
    sur = (uint8_t *)ReadAddr;
    tar = pBuffer;
    memcpy(tar, sur, NumByteToRead); // ����������
}
#endif

/*==============================================================================================================================*/

/*
 * @Description: �Զ����汻�޸ĵ�����
 * @param: Դ����ָ��
 * @param: Ŀ������ָ��
 * @param: �Ա�����
 * @return: ��
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
