/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-06-05 09:52:26
 * @LastEditors: joel
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
 * .chen sandote@163.om
 * @LastEditTime: 2023-07-13 16:24:02
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\ota\newota.c
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#include "newota.h"

/*擦除固件区*/
void erase_firmware_block(void)
{
    FLASH_BlockErase((uint32_t) & (NORFLASH->ota.data.package));    // 擦除64k
}

///*固件加载至norflash*/
//void firmware_load_to_norflash(uint16_t position, uint8_t *sur)
//{
////    FLASHSPI_PageWrite(sur, FIRMWARE_ADDR + position, 256);
////    checksum_calculate();
////    // FLASHSPI_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer));
//}

/*擦除norflash中的固件区*/
void erase_firmware_block64K_norflash(void)
{
    FLASH_BlockErase(FIRMWARE_ADDR);
    printlog("erase firmware block in norflash\r");
}
/*下载固件*/
void download_firmware_to_norflash(uint8_t *sur, uint16_t offset)
{
    FLASH_PageWrite(sur, FIRMWARE_ADDR + offset, 256);
    printf("download: Ox%04x [%d%%]\r", FIRMWARE_ADDR + offset, (offset * 100) / FIRMWARE_SIZE);
}
/*获取norflash中的校验和*/
uint32_t get_firmware_chechsum_norflash(void)
{
    uint8_t buffer[256];
    uint32_t checksum = 0;
    uint16_t i;
    printlog("get_firmware_chechsum_norflash\r");
    for (i = 0; i < FIRMWARE_SIZE;)
    {
        FLASHSPI_PageRead(buffer, i, sizeof(buffer));
        checksum += checksum_calculate(buffer, sizeof(buffer));
        i += sizeof(buffer);
    }
    return checksum;
}
/*设置固件升级标志*/
void set_firmware_update_flag(uint32_t checksum)
{
    update_Typedef update;
    printlog("set_firmware_update_flag\r");
    sprintf(&update.startflag, FIRMWARE_UPDATE_FLAG);
    update.package_checksum = checksum;
    FlashROM_Insert(&update, &(OCFLASH->update.data), sizeof(update));
}
/*清除固件升级标志*/
void clear_firmware_update_flag(void)
{
    update_Typedef update;
    printlog("clear_firmware_update_flag\r");
    memset(&update, 0, sizeof(update));
    FlashROM_Insert(&update, &(OCFLASH->update.data), sizeof(update));
}
/*检查是否需要升级*/
uint8_t check_firmware_update(void)
{
    printlog("check_firmware_update\r");
    if (strcmp(&(OCFLASH->update.data.startflag), FIRMWARE_UPDATE_FLAG) == 0) // 检查是否含有升级标志
    {
        if (*((uint32_t *)(&(OCFLASH->update.data.package_checksum))) == get_firmware_chechsum_norflash()) // 检查校验和是否与固件的一致
        {
            return 1;
        }
        else
        {
            clear_firmware_update_flag();
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
