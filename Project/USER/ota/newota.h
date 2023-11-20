/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-06-05 09:52:54
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * .chen sandote@163.om
 * @LastEditTime: 2023-11-11 14:07:08
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\ota\newota.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#ifndef _NEWOTA_H
#define _NEWOTA_H
#include "Function_Init.H"

#define FIRMWARE_UPDATE_FLAG "FIRMWARE UPDATE"    // �̼�������־
#define FIRMWARE_DOWNLOAD_FLAG "FIRMWARE DOWNLOAD" // �̼����ر�־
#define FIRMWARE_IN_FLASH_FLAG "FIRMWARE IN FLASH" // �̼��ڱ��ر�־

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
/**/
void set_firmware_update_flag(uint32_t checksum); // ���ù̼�������־
void clear_firmware_update_flag(void);            // ����̼�������־
//
uint8_t check_firmware_update(void);    // ����Ƿ���Ҫ����
//


#endif
