#ifndef FLASHAPP_H
#define FLASHAPP_H
#include "Function_Init.H"

#define FLASHSPI_EN
#define FLASHROM_EN

#ifdef FLASHSPI_EN /*Ƭ��flash��д*/
#define FLASHSPI_PageSize 256
#define FLASHSPI_PageRead(pBuffer, addr, size) FLASH_BufferRead(pBuffer, addr, size) // ����������
#define FLASHSPI_PageWrite(pBuffer, addr, size) FLASH_PageWrite(pBuffer, addr, size) // д��������
#define FLASHSPI_PageErase(addr) FLASH_PageErase(addr)                               // ������������
void FlashSPI_Insert(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
#endif

#ifdef FLASHROM_EN /*Ƭ��flash��д*/

#define FLASHROM_PageSize 512                                                           // ������С
#define FLASHROM_PageRead(pBuffer, addr, size) FlashROM_BufferRead(pBuffer, addr, size) // ����������
#define FLASHROM_PageWrite(pBuffer, addr, size) ProgramPage(addr, size, pBuffer)        // д��������
#define FLASHROM_PageErase(addr) EraseSector(addr)                                      // ������������

void FlashROM_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead); // ��flash
void FlashROM_Insert(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);   // ��ָ��flash��ַ��������

#endif

void ROMdata_autosave(uint8_t *sur, uint8_t *mem, uint32_t size); /*�Զ�����ָ������*/
#endif
