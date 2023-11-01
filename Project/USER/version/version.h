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

#define BOOT_INF_ADDR (BOOTLOADER_ADDR + 0X1000) // �̼���Ϣ��¼��ַ
#define APP_INF_ADDR (APP_BASIC_ADDR + 0X1000)   // �̼���Ϣ��¼��ַ

#define FIRMWARE_APP_MASTER "APP_MASTER"   // ����Ӧ�ó���
#define FIRMWARE_APP_SLAVE "APP_SLAVE"     // �ӻ�Ӧ�ó���
#define FIRMWARE_BOOT_MASTER "BOOT_MASTER" // ������������
#define FIRMWARE_BOOT_SLAVE "BOOT_SLAVE"   // �ӻ���������

#define FIRMWARE_TYPE FIRMWARE_APP_MASTER // ����Ӧ�ó���
#define FIRMWARE_VER MCU_VER
#define PRODUCT_MODEL "L1001"       // ��Ʒ�ͺ�
#define FIRMWARE_DATE __DATE__      // �̼�����
#define FIRMWARE_TIME __TIME__      // �̼�ʱ��
#define FIRMWARE_AUTHOR "JOEL.CHEN" // ����

typedef struct
{
    uint8_t model[16];   // ��Ʒ�ͺ�
    uint8_t type[16];    // �̼����� ����/�ӻ�/��������/�ӻ�����
    uint8_t version[16]; // �汾��
    uint8_t date[16];    // ����
    uint8_t time[16];    // ʱ��
    uint8_t author[16];  // ����
    uint8_t reserve[64]; // ����
} firmware_inf_TypeDef;  // �̼���Ϣ

extern const firmware_inf_TypeDef firmware_inf;
void print_firmware_information(void);


#endif

// $K\ARM\ARMCC\bin\fromelf.exe --bin --output=@L.bin !L
// $K\ARM\ARMCC\bin\fromelf.exe --bin --output=@L.bin !L
