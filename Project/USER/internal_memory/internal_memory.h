#ifndef _INTERNAL_MEMORY_H
#define _INTERNAL_MEMORY_H

#include "Function_Init.H"

#define FLASH_ONCHIP_ADDR 0x500000 // Ƭ�������������ַ
#define FLASH_ONCHIP_SIZE 0x600    // �����С 1.5k byte

#define FLASH_ONCHIP_PAGE_SIZE 512

typedef struct
{
    uint8_t startflag[16];
    uint32_t package_checksum;
} update_Typedef;

typedef struct
{
    update_Typedef data;
    uint8_t res[FLASH_ONCHIP_PAGE_SIZE-sizeof(update_Typedef)];
} update_area_Typedef;

typedef struct
{
    update_area_Typedef update;
} flash_onchip_Typedef;


#define OCFLASH ((flash_onchip_Typedef *)FLASH_ONCHIP_ADDR) // �û����ݽṹ��ӳ�䵽Ӳ����ַ��



#endif
