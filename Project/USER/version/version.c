/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-06-15 13:43:43
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
.chen sandote@163.om
 * .chen sandote@163.om
 * @LastEditTime: 2023-12-01 17:21:12
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\version\version.c
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#include "version.h"

const firmware_inf_TypeDef firmware_inf __attribute__((at(APP_INF_ADDR))) =
{
    PRODUCT_MODEL,
    FIRMWARE_TYPE,
    FIRMWARE_VER,
    FIRMWARE_DATE,
    FIRMWARE_TIME,
    FIRMWARE_AUTHOR,
};

void print_firmware_information(void)
{
    // // printlog("\r-----------------------------------\r");
    // // printlog("|firmware information|\r");
    // // printlog("MODEL:   ");
    // // printstr_my((uint8_t *)&firmware_inf.model, sizeof(firmware_inf.model));
    // // printlog("TYPE:    ");
    // // printstr_my((uint8_t *)&firmware_inf.type, sizeof(firmware_inf.type));
    // // printlog("VERSION: ");
    // // printstr_my((uint8_t *)&firmware_inf.version, sizeof(firmware_inf.version));
    // // printlog("DATE:    ");
    // // printstr_my((uint8_t *)&firmware_inf.date, sizeof(firmware_inf.date));
    // // printlog("-----------------------------------\r\n");
}
