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
#ifdef FLASHSPI_EN /*片外flash读写*/

#define FLASHSPI_PageSize 256                                                        // 页大小
#define FLASHSPI_PageRead(pBuffer, addr, size) FLASH_BufferRead(pBuffer, addr, size) // 读扇区函数
#define FLASHSPI_PageWrite(pBuffer, addr, size) FLASH_PageWrite(pBuffer, addr, size) // 写扇区函数
#define FLASHSPI_PageErase(addr) FLASH_PageErase(addr)                               // 擦除扇区函数

/*在片外flash的指定位置插入数据*/
void FlashSPI_Insert(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
/*擦除片外flash指定位置的数据*/
void FlashSPI_Erase(uint32_t adr, uint16_t size);
#endif
/*===================================================================================================================*/
#ifdef FLASHROM_EN /*片内flash读写*/

#define FLASHROM_PageSize 512                                                           // 页大小                                                        // 扇区大小
#define FLASHROM_PageRead(pBuffer, addr, size) FlashROM_BufferRead(pBuffer, addr, size) // 读扇区函数
#define FLASHROM_PageWrite(pBuffer, addr, size) ProgramPage(addr, size, pBuffer)        // 写扇区函数
#define FLASHROM_PageErase(addr) EraseSector(addr)                                      // 擦除扇区函数
/*在片内flash的指定位置插入数据*/
void FlashROM_Insert(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);   // 在指定flash地址插入数据
/*擦除片内flash指定位置的数据*/
void FlashROM_Erase(uint32_t adr, uint16_t size);
/*读出片内flash的数据*/
void FlashROM_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead); // 读flash

#endif
/*===================================================================================================================*/

void ROMdata_autosave(uint8_t *sur, uint8_t *mem, uint32_t size); /*自动保存指定数据*/
#endif
