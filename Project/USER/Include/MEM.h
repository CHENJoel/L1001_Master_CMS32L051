#ifndef MEM_H
#define MEM_H
#include "Function_Init.H"
#include "Inf.h"
/*
FlashоƬ P25T22 ���ڴ�2Mkbit(256KByte)����ַ��0x00000~0x3FFFF

0x00000~0x3FFFF
         _______________________________
0x00000 |                               |   APP OTA������
        |                               |
        |                               |   0x00000~0x0FFFF
        |                               |   size:0x10000,64KByte,65536 Byte
        |                               |
0x0FFFF |_______________________________|    ______________________________________________________________________________
0x10000 |                               |   ϵͳ��Ϣ��
        |                               |
        |                               |    0x10000~0x1FFFF
        |                               |    size:0x10000,64KByte,65536 Byte
        |                               |
0x1FFFF |_______________________________|    ______________________________________________________________________________
0x20000 |                               |   ��Ч��Ϣ��
        |                               |
        |                               |   0x20000~0x2FFFF
        |                               |   size:0x10000,64KByte,65536 Byte
        |                               |
0x2FFFF |_______________________________|    ______________________________________________________________________________
0x30000 |                               |   ������
        |                               |
        |                               |   0x30000~0x3FFFF
        |                               |   size:0x10000,64KByte,65536 Byte
        |                               |
0x3FFFF |_______________________________|    ______________________________________________________________________________


*/

#define NORFLASH_BASE 0UL

#define OTAPACK_BASE (NORFLASH_BASE + 0UL)
#define SYSDATA_BASE (NORFLASH_BASE + 0x10000UL)
#define EFFECT_BASE  (NORFLASH_BASE + 0x20000UL)
#define SPARE_BASE   (NORFLASH_BASE + 0x30000UL)

/*��Ч��Ϣ*/

// typedef struct
// {
//     uint8_t EfNum; // ��Ч����
// } EfIndex_TypeDef;



// extern EffectInf_TypeDef EffectInf;

/**/

/*ϵͳ��Ϣ*/

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
/*����*/
void Print_HEX16(uint32_t addr, uint8_t *sur, uint16_t size);
void SPI_FlashDebug(void);
void ROM_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);

/*********************************/
/*Ӧ��*/
void SYS_Record(void);
void NorFalsh_RW_Test(uint32_t addr);

#endif // MEM_H
