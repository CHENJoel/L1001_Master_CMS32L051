#ifndef _VERSION_H
#define _VERSION_H
#include "Function_Init.H"

#define BOOT_INF_ADDR (BOOTLOADER_ADDR + 0X1000) // 固件信息记录地址
#define APP_INF_ADDR (APP_BASIC_ADDR + 0X1000)   // 固件信息记录地址

#define PRODUCT_MODEL "L1001" // 产品型号

#define FIRMWARE_DATE "2023/06/15" // 固件日期

#define FIRMWARE_MASTER "MASTER" // 主机程序
#define FIRMWARE_SLAVE "SLAVE"   // 从机程序
#define FIRMWARE_BOOT "BOOT"     // 引导程序

typedef struct
{
    uint8_t model[16];   // 产品型号
    uint8_t type[16];    // 固件类型 主机/从机/启动
    uint8_t version[16]; // 版本号
    uint8_t date[16];    // 日期
    uint8_t reserve[64]; // 保留
} firmware_inf_TypeDef;  // 固件信息

extern volatile const firmware_inf_TypeDef firmware_inf;
void print_firmware_information(void);


#endif

// $K\ARM\ARMCC\bin\fromelf.exe --bin --output=@L.bin !L
// $K\ARM\ARMCC\bin\fromelf.exe --bin --output=@L.bin !L
