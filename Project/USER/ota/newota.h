#ifndef _NEWOTA_H
#define _NEWOTA_H
#include "Function_Init.H"

#define FIRMWARE_UPDATE_FLAG "FIRMWARE UPDATE" // �̼�������־

#define BOOTLOADER_ADDR 0x0000 // BOOT����ַ
#define APP_BASIC_ADDR 0x5000  // APP����ַ

#define FIRMWARE_SIZE (0x10000 - APP_BASIC_ADDR)                // �̼���С
#define FIRMWARE_ADDR (uint32_t) & (NORFLASH->ota.data.package) // �̼����λ��

/*����norflash�еĹ̼���*/
void erase_firmware_block64K_norflash(void);
/*���ع̼�*/
void download_firmware_to_norflash(uint8_t* sur,uint16_t offset);
/*��ȡnorflash�е�У���*/
uint32_t get_firmware_chechsum_norflash(void);
/*���ù̼�������־*/
void set_firmware_update_flag(uint32_t checksum);
/*����̼�������־*/
void clear_firmware_update_flag(void);
/*����Ƿ���Ҫ����*/
uint8_t check_firmware_update(void);
#endif
