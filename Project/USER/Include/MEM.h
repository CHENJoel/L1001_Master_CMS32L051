#ifndef MEM_H
#define MEM_H
#include "Function_Init.H"
#include "Inf.h"













#define SysRecord_verify 0x25a3cbf3
typedef struct
{
    uint32_t runtime;
    uint32_t verify;
}SysRecord_TypeDef;





#define Print_StuctSize(x) printf(" size:%d[0x%x]\r\n",sizeof(x),sizeof(x));











/*FlashSPI_Write(flashdata, SYSDATA_BASE + (uint32_t)&(((SysRecord_TypeDef *)0)->runtime),sizeof(flashdata.runtime));*/
extern SysRecord_TypeDef SysRecord;
/******************************/
/*Çý¶¯*/
void Print_HEX16(uint32_t addr, uint8_t *sur, uint16_t size);
void SPI_FlashDebug(void);
void ROM_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);

/*********************************/
/*Ó¦ÓÃ*/
void SYS_Record(void);
void NorFalsh_RW_Test(uint32_t addr);

#endif // MEM_H
