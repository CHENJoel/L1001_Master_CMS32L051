/*  Copyright (s) 2019 ���ڰ������Ƽ����޹�˾
 *  All rights reserved
 *
 * �ļ����ƣ�driver_w25qxx.h
 * ժҪ��
 *
 * �޸���ʷ     �汾��       Author       �޸�����
 *--------------------------------------------------
 * 2020.6.6      v01        ���ʿƼ�      �����ļ�
 *--------------------------------------------------
*/
#ifndef __W25QXX_H
#define __W25QXX_H

// #include "stm32f1xx_hal.h"
#include "Function_Init.H"

#define  FLASH_WRITEADDR            0x00000
#define  FLASH_READADDR             FLASH_WRITEADDR
#define  FLASH_SECTOR_TO_ERASE      FLASH_WRITEADDR


/************************* SPI Flash ��ض��� *************************/
#if defined W25Q16
#define FLASH_ID                        0xEF3015
#elif defined W25Q64
#define FLASH_ID                        0XEF4017
#elif defined W25Q128
#define FLASH_ID                        0XEF4018
#endif

#define SPI_FLASH_PageSize              256
#define SPI_FLASH_PerWritePageSize      256

#define W25X_WriteEnable		        0x06
#define W25X_WriteDisable		        0x04
#define W25X_ReadStatusReg          0x05
#define W25X_WriteStatusReg         0x01
#define W25X_ReadData			          0x03
#define W25X_FastReadData		        0x0B
#define W25X_FastReadDual		        0x3B
#define W25X_PageProgram		        0x02
#define W25X_BlockErase			        0xD8  // Block Erase (64K bytes)
#define W25X_SectorErase		        0x20
#define W25X_PageErase		          0x81
#define W25X_ChipErase			        0xC7
#define W25X_PowerDown			        0xB9
#define W25X_ReleasePowerDown       0xAB
#define W25X_DeviceID			          0xAB
#define W25X_ManufactDeviceID       0x90
#define W25X_JedecDeviceID          0x9F

#define WIP_Flag                        0x01  /* Write In Progress (WIP) flag */
#define Dummy_Byte                      0x55
/************************* SPI Flash ��ض������ *************************/


enum
{
  RESET = 0,
  SET = !RESET
} ;

/*
 *  ��������uint32_t FLASH_ReadDeviceID(void)
 *  ���������
 *  �����������
 *  ����ֵ�������ⲿFLASH���豸ID
 *  �������ã����ⲿFLASH���豸ID
*/
extern uint32_t FLASH_ReadDeviceID(void);

/*
 *  ��������uint32_t Flash_ReadFlashID(void)
 *  ���������
 *  �����������
 *  ����ֵ�������ⲿFLASH��оƬID
 *  �������ã����ⲿFLASH��оƬID
*/
extern uint32_t Flash_ReadFlashID(void);

/*
 *  ��������void Flash_PowerDown(void)
 *  ���������
 *  �����������
 *  ����ֵ����
 *  �������ã��Ͽ�FLASH
*/
extern void Flash_PowerDown(void);

/*
 *  ��������void Flash_WakeUp(void)
 *  ���������
 *  �����������
 *  ����ֵ����
 *  �������ã�����FLASH
*/
extern void Flash_WakeUp(void);

/*
 *  ��������void FLASH_SectorErase(uint32_t SectorAddr)
 *  ���������SectorAddr -> Ҫ�����ĵ�ַ
 *  �����������
 *  ����ֵ����
 *  �������ã���������
*/
extern void FLASH_SectorErase(uint32_t SectorAddr);

/*
 *  ��������void FLASH_BlockErase(uint32_t BlockAddr)
 *  ���������BlockAddr -> Ҫ���Ŀ��ַ
 *  �����������
 *  ����ֵ����
 *  �������ã������
*/
extern void FLASH_BlockErase(uint32_t BlockAddr);

/*
 *  ��������void FLASH_ChipErase(void)
 *  �����������
 *  �����������
 *  ����ֵ����
 *  �������ã�оƬȫ����
*/
extern void FLASH_ChipErase(void);

/*
 *  ��������void FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
 *  ���������pBuffer -> Ҫд������ָ��;    WriteAddr -> Ҫд��FLASH��ʼ��ַ;  NumByteToWrite -> Ҫд���ֽڸ���
 *  �����������
 *  ����ֵ����
 *  �������ã�ҳд
*/
extern void FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);

/*
 *  ��������void FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite))
 *  ���������pBuffer -> Ҫд������ָ��;    WriteAddr -> Ҫд��FLASH��ʼ��ַ;  NumByteToWrite -> Ҫд���ֽڸ���
 *  �����������
 *  ����ֵ����
 *  �������ã�дN���ֽ�
*/
extern void FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);

/*
 *  ��������void FLASH_BufferRead(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite))
 *  ���������pBuffer -> Ҫ��������ָ��;    WriteAddr -> Ҫ����FLASH��ʼ��ַ;  NumByteToWrite -> Ҫ�����ֽڸ���
 *  �����������
 *  ����ֵ����
 *  �������ã���N���ֽڳ���
*/
extern void FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
extern void FLASH_StartReadSequence(uint32_t ReadAddr);
/********************/
void FLASH_PageErase(uint32_t PageAddr);
#endif
