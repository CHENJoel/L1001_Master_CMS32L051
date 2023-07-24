/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-06-05 09:52:54
 * @LastEditors: joel
 * .chen sandote@163.om
 * @LastEditTime: 2023-06-20 13:31:01
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\ota\newota.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#ifndef _NEWOTA_H
#define _NEWOTA_H
#include "Function_Init.H"

#define FIRMWARE_UPDATE_FLAG "FIRMWARE UPDATE" // �̼�������־

#define BOOTLOADER_ADDR 0x0000 // BOOT����ַ
#define APP_BASIC_ADDR 0x4000  // APP����ַ

#define FIRMWARE_SIZE (0x10000 - APP_BASIC_ADDR)                // �̼���С
#define FIRMWARE_ADDR (uint32_t) & (NORFLASH->ota.data.package) // �̼����λ��

/*����norflash�еĹ̼���*/
void erase_firmware_block64K_norflash(void);
/*���ع̼�*/
void download_firmware_to_norflash(uint8_t* sur,uint16_t offset);
/*��ȡnorflash�е�У���*/
uint32_t get_firmware_chechsum_norflash(void);
/*���ù̼�������־*/
void set_firmware_update_flag(uint32_t checksum);
/*����̼�������־*/
void clear_firmware_update_flag(void);
/*����Ƿ���Ҫ����*/
uint8_t check_firmware_update(void);
#endif
