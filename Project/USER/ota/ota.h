#ifndef _OTA_H
#define _OTA_H
/*
实测
从云端下载需70秒
校验45秒
加载20秒



*/



/*


*/


#define BOOTLOADER_BASIC_ADDR 0     // bootoader基地址
#define BOOTLOADER_SIZE 0x5000      // 20k

// #define APP_SIZE 0x97F0             // 38k
#define CHECKSUM_OFFSET_ADDR 0x9FF0 // APP后16字节作为校验和存放区
#define MCU_SECTOR_SIZE 512         // 扇区大小

#define USER_DATA_BASIC_ADDR 0xE800 // 用户数据存储区
#define USER_DATA_SIZE 0x1800       // 用户数据存储区大小

#define OTA_PACK_SIZE 0x9800
#define PACK_CHECKSUM_ADDR 0x97F0

#define FLASH_OTA_PACK_BASE_ADDR 0x00
#define FLASH_SECTOR_SIZE 4096

void Print_Flash(uint8_t *pbuffer);                            // 打印数据
void Download_app(uint32_t offset, uint8_t *pbuffer);          // APP下载
void CheckSum_calculate(uint32_t *checkVal, uint8_t *pbuffer); // 校验和计算
uint8_t Download_checksum_verify(uint32_t checkVal);           // 下载包校验
void OTA_SetFlag(uint32_t checksum);                           // 设置OTA升级标志，代表升级包已准备好
void OTA_ResetFlag(void);                                      // 升级结束后清标志位
uint8_t Find_OTA_flag(void);                                   // 检查是否存在软件升级标志
uint8_t APP_checksum_verify(void);                             // 升级包校验
void APP_update_check(void);                                   // 升级检查
void ResetReg(void);                                           // 寄存器复位
void JumpToApp(void);                                          // 程序跳转
/*******************************/





#endif
