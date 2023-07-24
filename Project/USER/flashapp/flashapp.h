/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-05-18 15:08:24
 * @LastEditors: joel
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
 * .chen sandote@163.om
 * @LastEditTime: 2023-07-14 13:55:28
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\flashapp\flashapp.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#ifndef FLASHAPP_H
#define FLASHAPP_H
#include "Function_Init.H"

#define FLASHSPI_EN
#define FLASHROM_EN
/*===================================================================================================================*/
#ifdef FLASHSPI_EN /*Ƭ��flash��д*/

#define FLASHSPI_PageSize 256                                                        // ҳ��С
#define FLASHSPI_PageRead(pBuffer, addr, size) FLASH_BufferRead(pBuffer, addr, size) // ����������
#define FLASHSPI_PageWrite(pBuffer, addr, size) FLASH_PageWrite(pBuffer, addr, size) // д��������
#define FLASHSPI_PageErase(addr) FLASH_PageErase(addr)                               // ������������

/*��Ƭ��flash��ָ��λ�ò�������*/
void FlashSPI_Insert(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
/*����Ƭ��flashָ��λ�õ�����*/
void FlashSPI_Erase(uint32_t adr, uint16_t size);
#endif
/*===================================================================================================================*/
#ifdef FLASHROM_EN /*Ƭ��flash��д*/

#define FLASHROM_PageSize 512                                                           // ҳ��С                                                        // ������С
#define FLASHROM_PageRead(pBuffer, addr, size) FlashROM_BufferRead(pBuffer, addr, size) // ����������
#define FLASHROM_PageWrite(pBuffer, addr, size) ProgramPage(addr, size, pBuffer)        // д��������
#define FLASHROM_PageErase(addr) EraseSector(addr)                                      // ������������
/*��Ƭ��flash��ָ��λ�ò�������*/
void FlashROM_Insert(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);   // ��ָ��flash��ַ��������
/*����Ƭ��flashָ��λ�õ�����*/
void FlashROM_Erase(uint32_t adr, uint16_t size);
/*����Ƭ��flash������*/
void FlashROM_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead); // ��flash

#endif
/*===================================================================================================================*/

void ROMdata_autosave(uint8_t *sur, uint8_t *mem, uint32_t size); /*�Զ�����ָ������*/
#endif
