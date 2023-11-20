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

#define FIRMWARE_UPDATE_FLAG "FIRMWARE UPDATE"    // 固件升级标志
#define FIRMWARE_DOWNLOAD_FLAG "FIRMWARE DOWNLOAD" // 固件下载标志
#define FIRMWARE_IN_FLASH_FLAG "FIRMWARE IN FLASH" // 固件在本地标志

#define BOOTLOADER_ADDR 0x0000 // BOOT基地址
#define APP_BASIC_ADDR 0x4000  // APP基地址

#define FIRMWARE_SIZE (0x10000 - APP_BASIC_ADDR)                // 固件大小
#define FIRMWARE_ADDR (uint32_t) & (NORFLASH->ota.data.package) // 固件存放位置

/*擦除norflash中的固件区*/
void erase_firmware_block64K_norflash(void);
/*下载固件*/
void download_firmware_to_norflash(uint8_t* sur,uint16_t offset);
/*获取norflash中的校验和*/
uint32_t get_firmware_chechsum_norflash(void);
/**/
void set_firmware_update_flag(uint32_t checksum); // 设置固件升级标志
void clear_firmware_update_flag(void);            // 清除固件升级标志
//
uint8_t check_firmware_update(void);    // 检查是否需要升级
//


#endif
