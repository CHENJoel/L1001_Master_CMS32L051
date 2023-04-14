/*  Copyright (s) 2019 ���ڰ������Ƽ����޹�˾
 *  All rights reserved
 *
 * �ļ����ƣ�driver_w25qxx.c
 * ժҪ��
 *
 * �޸���ʷ     �汾��       Author       �޸�����
 *--------------------------------------------------
 * 2020.6.6      v01        ���ʿƼ�      �����ļ�
 *--------------------------------------------------
*/

//#include "main.h"
//#include "driver_usart.h"
#include "driver_spi.h"
#include "driver_w25qxx.h"
//#include "driver_timer.h"

// �����ض���
#define W25_CS_ENABLE()         {W25_CS(0); us_delay(100);}
#define W25_CS_DISABLE()        {W25_CS(1); us_delay(100);}
#define W25_RW_Byte(data)       SPI_WriteReadByte(data)



/*
 *  ��������uint32_t FLASH_ReadDeviceID(void)
 *  ���������
 *  �����������
 *  ����ֵ�������ⲿFLASH���豸ID
 *  �������ã����ⲿFLASH���豸ID
*/
uint32_t FLASH_ReadDeviceID(void)
{
    uint32_t temp[4];

    W25_CS_ENABLE();

    W25_RW_Byte(W25X_DeviceID);
    temp[0] = W25_RW_Byte(Dummy_Byte);
    temp[1] = W25_RW_Byte(Dummy_Byte);
    temp[2] = W25_RW_Byte(Dummy_Byte);
    temp[3] = W25_RW_Byte(Dummy_Byte); //deviceID

    W25_CS_DISABLE();

    return temp[3];
}

/*
 *  ��������uint32_t Flash_ReadFlashID(void)
 *  ���������
 *  �����������
 *  ����ֵ�������ⲿFLASH��оƬID
 *  �������ã����ⲿFLASH��оƬID
*/
uint32_t Flash_ReadFlashID(void)
{
    uint32_t temp[4];

    W25_CS_ENABLE();

    W25_RW_Byte(W25X_JedecDeviceID);
    temp[0] = W25_RW_Byte(Dummy_Byte);
    temp[1] = W25_RW_Byte(Dummy_Byte);
    temp[2] = W25_RW_Byte(Dummy_Byte);

    W25_CS_DISABLE();

    temp[3] = (temp[0] << 16) | (temp[1] << 8) | temp[2];

    return temp[3];
}

/*
 *  ��������static void Flash_WritenEN(void)
 *  ���������
 *  �����������
 *  ����ֵ����
 *  �������ã�дʹ��
*/
static void Flash_WritenEN(void)
{
    W25_CS_ENABLE();
    W25_RW_Byte(W25X_WriteEnable);
    W25_CS_DISABLE();
}

/*
 *  ��������static void FLASH_WaitForWriteEnd(void)
 *  ���������
 *  �����������
 *  ����ֵ����
 *  �������ã��ȴ�д���
*/
static void FLASH_WaitForWriteEnd(void)
{
    uint8_t flash_status = 0;

    W25_CS_ENABLE();
    W25_RW_Byte(W25X_ReadStatusReg);

    do
    {
        flash_status = W25_RW_Byte(Dummy_Byte);
    }
    while ((flash_status & WIP_Flag) == SET);
    W25_CS_DISABLE();
}

/*
 *  ��������void Flash_PowerDown(void)
 *  ���������
 *  �����������
 *  ����ֵ����
 *  �������ã��Ͽ�FLASH
*/
void Flash_PowerDown(void)
{
    W25_CS_ENABLE();

    W25_RW_Byte(W25X_PowerDown);

    W25_CS_DISABLE();
}

/*
 *  ��������void Flash_WakeUp(void)
 *  ���������
 *  �����������
 *  ����ֵ����
 *  �������ã�����FLASH
*/
void Flash_WakeUp(void)
{
    W25_CS_ENABLE();

    W25_RW_Byte(W25X_ReleasePowerDown);

    W25_CS_DISABLE();
}

/*
 *  ��������void FLASH_SectorErase(uint32_t SectorAddr)
 *  ���������SectorAddr -> Ҫ����������ַ
 *  �����������
 *  ����ֵ����
 *  �������ã���������
*/
void FLASH_SectorErase(uint32_t SectorAddr)
{
    Flash_WritenEN();
    FLASH_WaitForWriteEnd();

    W25_CS_ENABLE();
    W25_RW_Byte(W25X_SectorErase);
    W25_RW_Byte((SectorAddr & 0xFF0000) >> 16);
    W25_RW_Byte((SectorAddr & 0xFF00) >> 8);
    W25_RW_Byte(SectorAddr & 0xFF);
    W25_CS_DISABLE();

    FLASH_WaitForWriteEnd();
}

/*
 *  ��������void FLASH_BlockErase(uint32_t BlockAddr)
 *  ���������BlockAddr -> Ҫ�����Ŀ��ַ
 *  �����������
 *  ����ֵ����
 *  �������ã������
*/
void FLASH_BlockErase(uint32_t BlockAddr)
{
    Flash_WritenEN();
    FLASH_WaitForWriteEnd();

    W25_CS_ENABLE();
    W25_RW_Byte(W25X_BlockErase);
    W25_RW_Byte((BlockAddr & 0xFF0000) >> 16);
    W25_RW_Byte((BlockAddr & 0xFF00) >> 8);
    W25_RW_Byte(BlockAddr & 0xFF);
    W25_CS_DISABLE();

    FLASH_WaitForWriteEnd();
}
/*
 *  ��������void FLASH_ChipErase(void)
 *  �����������
 *  �����������
 *  ����ֵ����
 *  �������ã�оƬȫ����
*/
void FLASH_ChipErase(void)
{
    Flash_WritenEN();

    W25_CS_ENABLE();
    W25_RW_Byte(W25X_ChipErase);
    W25_CS_DISABLE();

    FLASH_WaitForWriteEnd();
}

/*
 *  ��������void FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
 *  ���������pBuffer -> Ҫд������ָ��;    WriteAddr -> Ҫд��FLASH��ʼ��ַ;  NumByteToWrite -> Ҫд���ֽڸ���
 *  �����������
 *  ����ֵ����
 *  �������ã�ҳд
*/
void FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    Flash_WritenEN();

    W25_CS_ENABLE();
    W25_RW_Byte(W25X_PageProgram);
    W25_RW_Byte((WriteAddr & 0xFF0000) >> 16);
    W25_RW_Byte((WriteAddr & 0xFF00) >> 8);
    W25_RW_Byte(WriteAddr & 0xFF);

    if(NumByteToWrite > SPI_FLASH_PerWritePageSize)
    {
        NumByteToWrite = SPI_FLASH_PerWritePageSize;
    }

    while (NumByteToWrite--)
    {
        W25_RW_Byte(*pBuffer);
        pBuffer++;
    }

    W25_CS_DISABLE();

    FLASH_WaitForWriteEnd();
}

/*
 *  ��������void FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite))
 *  ���������pBuffer -> Ҫд������ָ��;    WriteAddr -> Ҫд��FLASH��ʼ��ַ;  NumByteToWrite -> Ҫд���ֽڸ���
 *  �����������
 *  ����ֵ����
 *  �������ã�дN���ֽ�
*/
void FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    Addr = WriteAddr % SPI_FLASH_PageSize;

    count = SPI_FLASH_PageSize - Addr;

    NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;

    NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

    if (Addr == 0)
    {
        if (NumOfPage == 0)
        {
            FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
        }
        else
        {
            while (NumOfPage--)
            {
                FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
                WriteAddr +=  SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }

            FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else
    {
        if (NumOfPage == 0)
        {
            if (NumOfSingle > count)
            {
                temp = NumOfSingle - count;

                FLASH_PageWrite(pBuffer, WriteAddr, count);
                WriteAddr +=  count;
                pBuffer += count;

                FLASH_PageWrite(pBuffer, WriteAddr, temp);
            }
            else
            {
                FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else
        {
            NumByteToWrite -= count;
            NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
            NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

            FLASH_PageWrite(pBuffer, WriteAddr, count);
            WriteAddr +=  count;
            pBuffer += count;

            while (NumOfPage--)
            {
                FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
                WriteAddr +=  SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }
            if (NumOfSingle != 0)
            {
                FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

/*
 *  ��������void FLASH_BufferRead(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite))
 *  ���������pBuffer -> Ҫ��������ָ��;    WriteAddr -> Ҫ����FLASH��ʼ��ַ;  NumByteToWrite -> Ҫ�����ֽڸ���
 *  �����������
 *  ����ֵ����
 *  �������ã���N���ֽڳ���
*/
void FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    W25_CS_ENABLE();

    W25_RW_Byte(W25X_ReadData);

    W25_RW_Byte((ReadAddr & 0xFF0000) >> 16);

    W25_RW_Byte((ReadAddr& 0xFF00) >> 8);

    W25_RW_Byte(ReadAddr & 0xFF);

    while (NumByteToRead--)
    {
        *pBuffer = W25_RW_Byte(Dummy_Byte);
        pBuffer++;
    }

    W25_CS_DISABLE();
}

void FLASH_StartReadSequence(uint32_t ReadAddr)
{
    W25_CS_ENABLE();

    W25_RW_Byte(W25X_ReadData);
    W25_RW_Byte((ReadAddr & 0xFF0000) >> 16);
    W25_RW_Byte((ReadAddr& 0xFF00) >> 8);
    W25_RW_Byte(ReadAddr & 0xFF);

    W25_CS_DISABLE();
}
