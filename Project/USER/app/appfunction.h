/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-05-19 11:16:26
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * .chen sandote@163.om
 * @LastEditTime: 2023-10-28 14:04:55
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\app\appfunction.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#ifndef APPFUNCTION_H
#define APPFUNCTION_H

/*************************************************************/
/*DPID_DEVICE_CONTROL*/

typedef enum
{
    UNLIGHT, // 未点亮
    LIGHTED, // 已点亮
    PERSENT, // 当前点亮
} LIGHTSTATUS_ENUM;

#pragma pack(push, 1)
typedef struct
{
    uint8_t id;                // 灯板id
    uint8_t index;             // 索引
    LIGHTSTATUS_ENUM lightsta; // 亮灯状态
} app_lightstatus_Typedef;

typedef struct
{
    uint8_t lightnum;   // 灯板数量
    app_lightstatus_Typedef lightsta[32];
} app_device_control_Typedef;
#pragma pack(pop)
/*************************************************************/



/*校验通信数据是否正确*/
uint8_t com_dataverify(uint8_t *sur, uint16_t size);
/*mcu上报灯效详情*/
void mcu_update_efdetail(uint8_t efnum);
//
void mcu_update_efsketch(com_issue_cmd_TypeDef *p); // 根据指令上报灯效概述
void mcu_update_one_efsketch(uint8_t efnum); // 上报某灯效概述
/*mcu上报灯效概述-从播放列表的dp上传*/
void mcu_update_playlist_efsketch(com_issue_cmd_TypeDef *p);


/*mcu上报全部灯效的顺序表*/
void mcu_update_allef_ranklist(void);
/*mcu上报自定义灯效的顺序表*/
void mcu_update_originalef_ranklist(void);
/*mcu上报收藏灯效的顺序表*/
void mcu_update_favoritesef_ranklist(void);
/*mcu上报播放列表的顺序表*/
void mcu_update_playlist_ranklist(void);
/*mcu上报播放详情*/
void mcu_update_playdetail(uint8_t playnum);
/*mcu上报当前播放详情*/
void mcu_update_current_playdetail(void);
/*mcu上报播放状态*/
void mcu_update_playstatus(void);


/*










*/

/*针对DPID_EFFECT_DETIAL的处理函数*/
uint8_t mcu_download_effect_detail_handle(uint8_t *sur, uint16_t length);
/*针对DPID_ISSUE_CMD的处理函数*/
uint8_t mcu_download_issue_cmd_handle(uint8_t *sur, uint16_t length);
/*针对DPID_EFFECT_PREVIEW的处理函数*/
void mcu_download_effect_preview(uint8_t *sur, uint16_t length);
/*针对DPID_PLAY_DETIAL的处理函数*/
uint8_t mcu_download_play_detial(uint8_t *sur, uint16_t length);
/*针对DPID_PLAY_CONTROL_DETIAL的处理函数*/
uint8_t mcu_download_play_control_detial(uint8_t *sur, uint16_t length);
/*针对DPID_DEVICE_DETAIL的处理函数*/
void mcu_download_device_detail(uint8_t *sur, uint16_t length);
/*针对DPID_DEVICE_CONTROL的处理函数*/
uint8_t mcu_download_device_control(uint8_t *sur, uint16_t length);
/*针对DPID_BRIGHT_VAL的处理函数*/
void mcu_download_bright_val(uint8_t bri);
/*上传亮度*/
void mcu_update_bright_val(void);
/*针对DPID_SWITCH_LED的处理函数*/
void mcu_download_switch_led(uint8_t sw);
/*上报开关状态*/
void mcu_update_switch_led(void);

//
void mcu_download_switch_indicator(uint8_t bool); // 下载指示灯开关状态
void mcu_update_switch_indicator(void);           // 上传指示灯开关状态
//

void mcu_download_switch_mic(uint8_t bool); // 下载麦克风开关状态
void mcu_update_switch_mic(void);           // 上传麦克风开关状态
//
void mcu_download_auto_brightness_switch(uint8_t bool); // 下载自动亮度的开关
void mcu_update_auto_brightness_switch(void);           // 上传自动亮度的开关
//
void mcu_download_auto_brightness_mode(uint8_t num); // 下载自动亮度的模式
void mcu_update_auto_brightness_mode(void);          // 上传自动亮度的模式
//
void mcu_download_clock_list(uint8_t *sur, uint16_t length); // 下载闹钟计划概述表
void mcu_update_clock_list(void);                            // 上传闹钟计划概述表
//
/**/
uint8_t mcu_download_clock_detial(uint8_t *sur, uint16_t length); // 下载闹钟详情
void mcu_update_clock_detial(uint8_t num);                        // 上传闹钟详情
//

/*在线下载固件*/
void mcu_firmware_download(uint8_t *sur, uint16_t position, uint16_t length);
#endif
