/*
 * @Author: DESKTOP-AKTRQKB\MY sandote@163.com
 * @Date: 2023-06-07 10:05:07
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * @LastEditTime: 2023-10-31 15:03:35
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\master\master.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _MASTER_H
#define _MASTER_H
#include "Function_Init.H"

#define TIME_5_MINUTE 300

typedef enum
{
    KEEP_ON,       // 常亮
    SLOW_FLASH,    // 慢闪1Hz
    QUICK_FLASH,   // 快闪4Hz
    KEEP_OFF,      // 熄灭
    INTURN_FLASH,  // 交替闪
} LED_STATUS_ENUM; // 指示灯状态

typedef enum
{
    NO_OTA,        // 无升级任务
    OTA_GOING,     // 升级中
    OTA_FAILED,    // 升级失败
    OTA_SUCCES,    // 升级成功
} OTA_STATUS_ENUM; // ota状态

typedef enum
{
    NO_ERROR,      // 无错误
} SYS_ERROR_ENUM; // ota状态

typedef struct
{
    uint8_t firmware_dowmload; // 固件下载
    uint8_t ota_state;         //
    uint8_t wifi_state;

    SYS_ERROR_ENUM errorcode;
    LED_STATUS_ENUM LED_Red;
    LED_STATUS_ENUM LED_Blue;
} sys_sta_TypeDef;

typedef struct
{
    sys_sta_TypeDef sta;
    uint32_t running_time; // 上电运行时间
}sys_TypeDef;
extern sys_TypeDef sys;

typedef struct
{
    uint8_t pindex;
    uint8_t mic_finish;
    uint16_t micbuf[200];
    uint16_t keybuf[1];
    uint16_t lasbuf[1];
}adcdma_task_TypeDef;

/*******************************************/

void wifi_module_init(void);    // wifi模组初始化
void mcu_restart(void); // 单片机重启
//
void sys_rundata_init(void);    // 初始化系统运行数据
//
uint8_t get_norflash_firmware_version(uint8_t* str,uint8_t len);// 获取在norflash中的固件版本号
void get_first_ota_status(void);   // 获取ota升级状态
//
void sys_running_cnt(void); // 计算系统运行时间
//
void LED_display_init(void);    // 状态灯初始状态
void LED_Display_20ms(void);    // 状态灯指示
#endif
