/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-08-05 16:09:02
 * @LastEditors: joel
.chen sandote@163.om
 * .chen sandote@163.om
 * @LastEditTime: 2023-08-07 22:56:31
 * @FilePath: \L1001_Bootloader\Project\USER\L0\boot.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#ifndef _BOOT_H_
#define _BOOT_H_
#include "Function_Init.H"



void function_GET_ROM(uint8_t *p, uint16_t len);          // ��ȡROM����
void function_GET_ROMSUM(uint8_t *p, uint16_t len);       // ��ȡROMУ���
void function_ERASE_APP(uint8_t *p, uint16_t len);        // ����ȫ��APP����.��IAPģʽ����Ч
void function_REASE_ROM(uint8_t *p, uint16_t len);        // ����ָ��ROM����.��IAPģʽ����Ч
void function_WRITE_ROM(uint8_t *p, uint16_t len);        // ֱ��д��ROM����
void function_INSER_ROM(uint8_t *p, uint16_t len);        // ���ݲ���ROM����
void function_GET_UID(uint8_t *p, uint16_t len);          // ��ȡUID
void function_GET_BOOT_VERSION(uint8_t *p, uint16_t len); // ��ȡ��������汾
void function_GET_APP_VERSION(uint8_t *p, uint16_t len);  // ��ȡӦ�ó���汾
void function_GOTO_IAP(uint8_t *p, uint16_t len);         // ����IAPģʽ
void function_CONNECT(uint8_t *p, uint16_t len);          // ��������
void function_DISCONNECT(uint8_t *p, uint16_t len);       // �Ͽ�����
void function_GOTO_APP(uint8_t *p, uint16_t len);         // ��ת��APP
void function_NVIC_RESET(uint8_t *p, uint16_t len);       // �����λ
void function_RESET_DATA(uint8_t *p, uint16_t len);       // �ָ�����

#endif
