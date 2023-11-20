/*
 * @Author: DESKTOP-AKTRQKB\MY sandote@163.com
 * @Date: 2023-05-31 16:54:36
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * @LastEditTime: 2023-11-11 13:59:05
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\internal_memory\internal_memory.h
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _INTERNAL_MEMORY_H
#define _INTERNAL_MEMORY_H

#include "Function_Init.H"

#define FLASH_ONCHIP_ADDR 0x500000 // Ƭ�������������ַ
#define FLASH_ONCHIP_SIZE 0x600    // �����С 1.5k byte

#define FLASH_ONCHIP_PAGE_SIZE 512

#define OTA_updateFLAG_SIZE 16  // OTA������־�ַ�����
#define FW_downloadFLAG_SIZE 32 // �̼������ر�־�ַ�����

typedef struct
{
    uint8_t startflag[OTA_updateFLAG_SIZE];
    uint32_t package_checksum;
} update_Typedef;

typedef struct
{
    update_Typedef data;
    uint8_t res[FLASH_ONCHIP_PAGE_SIZE-sizeof(update_Typedef)];
} update_area_Typedef;


typedef struct
{
    uint8_t FW_downloadFLAG[FW_downloadFLAG_SIZE];
} userdata_Typedef;

typedef struct
{
    userdata_Typedef data;
    uint8_t res[FLASH_ONCHIP_PAGE_SIZE-sizeof(userdata_Typedef)];
} user_area_Typedef;

typedef struct
{
    update_area_Typedef update;
    user_area_Typedef user;
} flash_onchip_Typedef;

#define OCFLASH ((flash_onchip_Typedef *)FLASH_ONCHIP_ADDR) // �û����ݽṹ��ӳ�䵽Ӳ����ַ��



#endif
