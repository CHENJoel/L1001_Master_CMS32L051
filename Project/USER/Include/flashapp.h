#ifndef FLASHAPP_H
#define FLASHAPP_H
#include "Function_Init.H"

#define FLASHSPI_EN
#define FLASHROM_EN

#ifdef FLASHSPI_EN /*片外flash读写*/
#define FLASHSPI_PageSize 256
#define FLASHSPI_PageRead(pBuffer, addr, size) FLASH_BufferRead(pBuffer, addr, size) // 读扇区函数
#define FLASHSPI_PageWrite(pBuffer, addr, size) FLASH_PageWrite(pBuffer, addr, size) // 写扇区函数
#define FLASHSPI_PageErase(addr) FLASH_PageErase(addr)                               // 擦除扇区函数
void FlashSPI_Insert(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
#endif

#ifdef FLASHROM_EN /*片内flash读写*/

#define FLASHROM_PageSize 512                                                           // 扇区大小
#define FLASHROM_PageRead(pBuffer, addr, size) FlashROM_BufferRead(pBuffer, addr, size) // 读扇区函数
#define FLASHROM_PageWrite(pBuffer, addr, size) ProgramPage(addr, size, pBuffer)        // 写扇区函数
#define FLASHROM_PageErase(addr) EraseSector(addr)                                      // 擦除扇区函数

void FlashROM_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead); // 读flash
void FlashROM_Insert(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);   // 在指定flash地址插入数据

#endif

void ROMdata_autosave(uint8_t *sur, uint8_t *mem, uint32_t size); /*自动保存指定数据*/
#endif
