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
 * @Description: �ײ�ָ�����
 * @param: ���ݰ�Դָ��
 * @param: ���ݰ�����
 * @return: ��
*/
void boot_command_parse(uint8_t * p, uint16_t len)
{
    // // if ((((large_package_Typedef *)p)->head.dev_adr == ADDR_PUBLIC) || (((large_package_Typedef *)p)->head.dev_adr == *((uint8_t *)(&(UID->UID0))))) // �豸��ַУ��
    // // {
    switch (((large_package_Typedef *)p)->head.cmd)
    {
    case CMD_BOOT_GET_ROM: // ��ȡROM����
        // // // printlog("CMD_BOOT_GET_ROM\r");
        function_GET_ROM(p, len);
        break;
    case CMD_BOOT_GET_ROMSUM: // ��ȡROMУ���
        // // // printlog("CMD_BOOT_GET_ROMSUM\r");
        function_GET_ROMSUM(p, len);
        break;
    case CMD_BOOT_ERASE_APP: // ����ȫ��APP����.��IAPģʽ����Ч
        // // // printlog("CMD_BOOT_ERASE_APP\r");
        // // // function_ERASE_APP(p, len);
        break;
    case CMD_BOOT_REASE_ROM: // ����ָ��ROM����.��IAPģʽ����Ч
        // // // printlog("CMD_BOOT_REASE_ROM\r");
        // // // function_REASE_ROM(p, len);
        break;
    case CMD_BOOT_WRITE_ROM: // ֱ��д��ROM����
        // // // printlog("CMD_BOOT_WRITE_ROM\r");
        // // // function_WRITE_ROM(p, len);
        break;
    case CMD_BOOT_INSER_ROM: // ���ݲ���ROM����
        // // // printlog("CMD_BOOT_INSER_ROM\r");
        function_INSER_ROM(p, len);
        break;
    case CMD_BOOT_GET_UID: // ��ȡUID
        // // // printlog("CMD_BOOT_GET_UID\r");
        function_GET_UID(p, len);
        break;
    case CMD_BOOT_GET_BOOT_VERSION: // ��ȡ��������汾
        // // // printlog("CMD_BOOT_GET_BOOT_VERSION\r");
        function_GET_BOOT_VERSION(p, len);
        break;
    case CMD_BOOT_GET_APP_VERSION: // ��ȡӦ�ó���汾
        // // // printlog("CMD_BOOT_GET_APP_VERSION\r");
        function_GET_APP_VERSION(p, len);
        break;
    case CMD_BOOT_GOTO_IAP: // ����IAPģʽ
        // // // printlog("CMD_BOOT_GOTO_IAP\r");
        // // // function_GOTO_IAP(p, len);
        function_NVIC_RESET(p, len);
        break;
    case CMD_BOOT_CONNECT: // ��������
        // // // printlog("CMD_BOOT_CONNECT\r");
        // // // function_CONNECT(p, len);
        function_NVIC_RESET(p, len);
        break;
    case CMD_BOOT_DISCONNECT: // �Ͽ�����
        // // // printlog("CMD_BOOT_DISCONNECT\r");
        // // // function_DISCONNECT(p, len);
        break;
    case CMD_BOOT_GOTO_APP: // ��ת��APP
        // // // printlog("CMD_BOOT_GOTO_APP\r");
        // // // function_GOTO_APP(p, len);
        break;
    case CMD_BOOT_NVIC_RESET: // �����λ
        // // // printlog("CMD_BOOT_NVIC_RESET\r");
        function_NVIC_RESET(p, len);
        break;
    case CMD_BOOT_RESET_DATA: // �ָ�����
        // // // printlog("CMD_BOOT_RESET_DATA\r");
        function_RESET_DATA(p, len);
        break;
    default:
        break;
    }
    // // }
}

/*
 * @Description: ����16λ����
 * @param:Դ����ָ��
 * @return:16λ����
*/
uint16_t read_16bit_data(uint8_t *sur)
{
    uint16_t data;
    data = sur[0];
    data |= sur[1] << 8;
    return data;
}

/*
 * @Description: ����32λ����
 * @param:Դ����ָ��
 * @return:32λ����
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
 * @Description: �ڵ�ַд��16λ����
 * @param:Դ����ָ��
 * @return:16λ����
 */
void write_16bit_data(uint8_t *tar, uint16_t data)
{
    tar[0] = data;
    tar[1] = data >> 8;
}


/*
 * @Description: �ڵ�ַд��32λ����
 * @param:Դ����ָ��
 * @return:32λ����
 */
void write_32bit_data(uint8_t *tar, uint32_t data)
{
    tar[0] = data;
    tar[1] = data >> 8;
    tar[2] = data >> 16;
    tar[3] = data >> 24;
}
