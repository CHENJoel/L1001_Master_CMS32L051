/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-06-15 13:43:49
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
 * .chen sandote@163.om
 * @LastEditTime: 2023-10-30 14:39:36
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\version\version.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#ifndef _VERSION_H
#define _VERSION_H  
#include "Function_Init.H"

#define BOOT_INF_ADDR (BOOTLOADER_ADDR + 0X1000) // 固件信息记录地址
#define APP_INF_ADDR (APP_BASIC_ADDR + 0X1000)   // 固件信息记录地址

#define FIRMWARE_APP_MASTER "APP_MASTER"   // 主机应用程序
#define FIRMWARE_APP_SLAVE "APP_SLAVE"     // 从机应用程序
#define FIRMWARE_BOOT_MASTER "BOOT_MASTER" // 主机引导程序
#define FIRMWARE_BOOT_SLAVE "BOOT_SLAVE"   // 从机引导程序

#define FIRMWARE_TYPE FIRMWARE_APP_MASTER // 主机应用程序
#define FIRMWARE_VER MCU_VER
#define PRODUCT_MODEL "L1001"       // 产品型号
#define FIRMWARE_DATE __DATE__      // 固件日期
#define FIRMWARE_TIME __TIME__      // 固件时间
#define FIRMWARE_AUTHOR "JOEL.CHEN" // 作者

typedef struct
{
    uint8_t model[16];   // 产品型号
    uint8_t type[16];    // 固件类型 主机/从机/主机引导/从机引导
    uint8_t version[16]; // 版本号
    uint8_t date[16];    // 日期
    uint8_t time[16];    // 时间
    uint8_t author[16];  // 作者
    uint8_t reserve[64]; // 保留
} firmware_inf_TypeDef;  // 固件信息

extern const firmware_inf_TypeDef firmware_inf;
void print_firmware_information(void);


#endif

// $K\ARM\ARMCC\bin\fromelf.exe --bin --output=@L.bin !L
// $K\ARM\ARMCC\bin\fromelf.exe --bin --output=@L.bin !L
