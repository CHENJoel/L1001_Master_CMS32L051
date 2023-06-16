#ifndef _NEWOTA_H
#define _NEWOTA_H
#include "Function_Init.H"

#define FIRMWARE_UPDATE_FLAG "FIRMWARE UPDATE" // 固件升级标志

#define BOOTLOADER_ADDR 0x0000 // BOOT基地址
#define APP_BASIC_ADDR 0x5000  // APP基地址

#define FIRMWARE_SIZE (0x10000 - APP_BASIC_ADDR)                // 固件大小
#define FIRMWARE_ADDR (uint32_t) & (NORFLASH->ota.data.package) // 固件存放位置

/*擦除norflash中的固件区*/
void erase_firmware_block64K_norflash(void);
/*下载固件*/
void download_firmware_to_norflash(uint8_t* sur,uint16_t offset);
/*获取norflash中的校验和*/
uint32_t get_firmware_chechsum_norflash(void);
/*设置固件升级标志*/
void set_firmware_update_flag(uint32_t checksum);
/*清除固件升级标志*/
void clear_firmware_update_flag(void);
/*检查是否需要升级*/
uint8_t check_firmware_update(void);
#endif
