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

/*�����̼���*/
void erase_firmware_block(void)
{
    FLASH_BlockErase((uint32_t) & (NORFLASH->ota.data.package));    // ����64k
}

///*�̼�������norflash*/
//void firmware_load_to_norflash(uint16_t position, uint8_t *sur)
//{
////    FLASHSPI_PageWrite(sur, FIRMWARE_ADDR + position, 256);
////    checksum_calculate();
////    // FLASHSPI_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer));
//}

/*����norflash�еĹ̼���*/
void erase_firmware_block64K_norflash(void)
{
    FLASH_BlockErase(FIRMWARE_ADDR);
    printlog("erase firmware block in norflash\r");
}
/*���ع̼�*/
void download_firmware_to_norflash(uint8_t *sur, uint16_t offset)
{
    FLASH_PageWrite(sur, FIRMWARE_ADDR + offset, 256);
    printf("download: Ox%04x [%d%%]\r", FIRMWARE_ADDR + offset, (offset * 100) / FIRMWARE_SIZE);
}
/*��ȡnorflash�е�У���*/
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
/*���ù̼�������־*/
void set_firmware_update_flag(uint32_t checksum)
{
    update_Typedef update;
    printlog("set_firmware_update_flag\r");
    sprintf(&update.startflag, FIRMWARE_UPDATE_FLAG);
    update.package_checksum = checksum;
    FlashROM_Insert(&update, &(OCFLASH->update.data), sizeof(update));
}
/*����̼�������־*/
void clear_firmware_update_flag(void)
{
    update_Typedef update;
    printlog("clear_firmware_update_flag\r");
    memset(&update, 0, sizeof(update));
    FlashROM_Insert(&update, &(OCFLASH->update.data), sizeof(update));
}
/*����Ƿ���Ҫ����*/
uint8_t check_firmware_update(void)
{
    printlog("check_firmware_update\r");
    if (strcmp(&(OCFLASH->update.data.startflag), FIRMWARE_UPDATE_FLAG) == 0) // ����Ƿ���������־
    {
        if (*((uint32_t *)(&(OCFLASH->update.data.package_checksum))) == get_firmware_chechsum_norflash()) // ���У����Ƿ���̼���һ��
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
