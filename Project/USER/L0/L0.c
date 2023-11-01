/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-08-05 11:38:59
 * @LastEditors: joel
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
 * @LastEditTime: 2023-09-14 14:54:22
 * @FilePath: \L1001_Slave_CMS32L051\Project\USER\L0\L0.c
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#include "L0.h"

/*
 * @Description: 底层指令解析
 * @param: 数据包源指针
 * @param: 数据包长度
 * @return: 无
*/
void boot_command_parse(uint8_t * p, uint16_t len)
{
    // // if ((((large_package_Typedef *)p)->head.dev_adr == ADDR_PUBLIC) || (((large_package_Typedef *)p)->head.dev_adr == *((uint8_t *)(&(UID->UID0))))) // 设备地址校验
    // // {
    switch (((large_package_Typedef *)p)->head.cmd)
    {
    case CMD_BOOT_GET_ROM: // 获取ROM数据
        // // // printlog("CMD_BOOT_GET_ROM\r");
        function_GET_ROM(p, len);
        break;
    case CMD_BOOT_GET_ROMSUM: // 获取ROM校验和
        // // // printlog("CMD_BOOT_GET_ROMSUM\r");
        function_GET_ROMSUM(p, len);
        break;
    case CMD_BOOT_ERASE_APP: // 擦除全部APP区域.仅IAP模式下有效
        // // // printlog("CMD_BOOT_ERASE_APP\r");
        // // // function_ERASE_APP(p, len);
        break;
    case CMD_BOOT_REASE_ROM: // 擦除指定ROM区域.仅IAP模式下有效
        // // // printlog("CMD_BOOT_REASE_ROM\r");
        // // // function_REASE_ROM(p, len);
        break;
    case CMD_BOOT_WRITE_ROM: // 直接写入ROM区域
        // // // printlog("CMD_BOOT_WRITE_ROM\r");
        // // // function_WRITE_ROM(p, len);
        break;
    case CMD_BOOT_INSER_ROM: // 数据插入ROM区域
        // // // printlog("CMD_BOOT_INSER_ROM\r");
        function_INSER_ROM(p, len);
        break;
    case CMD_BOOT_GET_UID: // 获取UID
        // // // printlog("CMD_BOOT_GET_UID\r");
        function_GET_UID(p, len);
        break;
    case CMD_BOOT_GET_BOOT_VERSION: // 获取引导程序版本
        // // // printlog("CMD_BOOT_GET_BOOT_VERSION\r");
        function_GET_BOOT_VERSION(p, len);
        break;
    case CMD_BOOT_GET_APP_VERSION: // 获取应用程序版本
        // // // printlog("CMD_BOOT_GET_APP_VERSION\r");
        function_GET_APP_VERSION(p, len);
        break;
    case CMD_BOOT_GOTO_IAP: // 进入IAP模式
        // // // printlog("CMD_BOOT_GOTO_IAP\r");
        // // // function_GOTO_IAP(p, len);
        function_NVIC_RESET(p, len);
        break;
    case CMD_BOOT_CONNECT: // 建立连接
        // // // printlog("CMD_BOOT_CONNECT\r");
        // // // function_CONNECT(p, len);
        function_NVIC_RESET(p, len);
        break;
    case CMD_BOOT_DISCONNECT: // 断开连接
        // // // printlog("CMD_BOOT_DISCONNECT\r");
        // // // function_DISCONNECT(p, len);
        break;
    case CMD_BOOT_GOTO_APP: // 跳转至APP
        // // // printlog("CMD_BOOT_GOTO_APP\r");
        // // // function_GOTO_APP(p, len);
        break;
    case CMD_BOOT_NVIC_RESET: // 软件复位
        // // // printlog("CMD_BOOT_NVIC_RESET\r");
        function_NVIC_RESET(p, len);
        break;
    case CMD_BOOT_RESET_DATA: // 恢复出厂
        // // // printlog("CMD_BOOT_RESET_DATA\r");
        function_RESET_DATA(p, len);
        break;
    default:
        break;
    }
    // // }
}

/*
 * @Description: 返回16位数据
 * @param:源数据指针
 * @return:16位数据
*/
uint16_t read_16bit_data(uint8_t *sur)
{
    uint16_t data;
    data = sur[0];
    data |= sur[1] << 8;
    return data;
}

/*
 * @Description: 返回32位数据
 * @param:源数据指针
 * @return:32位数据
*/
uint32_t read_32bit_data(uint8_t *sur)
{
    uint32_t data;
    data = sur[0];
    data |= sur[1] << 8;
    data |= sur[2] << 16;
    data |= sur[3] << 24;
    return data;
}

/*
 * @Description: 在地址写入16位数据
 * @param:源数据指针
 * @return:16位数据
 */
void write_16bit_data(uint8_t *tar, uint16_t data)
{
    tar[0] = data;
    tar[1] = data >> 8;
}


/*
 * @Description: 在地址写入32位数据
 * @param:源数据指针
 * @return:32位数据
 */
void write_32bit_data(uint8_t *tar, uint32_t data)
{
    tar[0] = data;
    tar[1] = data >> 8;
    tar[2] = data >> 16;
    tar[3] = data >> 24;
}
