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



void function_GET_ROM(uint8_t *p, uint16_t len);          // 获取ROM数据
void function_GET_ROMSUM(uint8_t *p, uint16_t len);       // 获取ROM校验和
void function_ERASE_APP(uint8_t *p, uint16_t len);        // 擦除全部APP区域.仅IAP模式下有效
void function_REASE_ROM(uint8_t *p, uint16_t len);        // 擦除指定ROM区域.仅IAP模式下有效
void function_WRITE_ROM(uint8_t *p, uint16_t len);        // 直接写入ROM区域
void function_INSER_ROM(uint8_t *p, uint16_t len);        // 数据插入ROM区域
void function_GET_UID(uint8_t *p, uint16_t len);          // 获取UID
void function_GET_BOOT_VERSION(uint8_t *p, uint16_t len); // 获取引导程序版本
void function_GET_APP_VERSION(uint8_t *p, uint16_t len);  // 获取应用程序版本
void function_GOTO_IAP(uint8_t *p, uint16_t len);         // 进入IAP模式
void function_CONNECT(uint8_t *p, uint16_t len);          // 建立连接
void function_DISCONNECT(uint8_t *p, uint16_t len);       // 断开连接
void function_GOTO_APP(uint8_t *p, uint16_t len);         // 跳转至APP
void function_NVIC_RESET(uint8_t *p, uint16_t len);       // 软件复位
void function_RESET_DATA(uint8_t *p, uint16_t len);       // 恢复出厂

#endif
