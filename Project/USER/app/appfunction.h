#ifndef APPFUNCTION_H
#define APPFUNCTION_H
#include "Function_Init.H"

/*校验通信数据是否正确*/
uint8_t com_dataverify(uint8_t *sur, uint16_t size);
/*mcu上报灯效详情*/
void mcu_update_efdetail(uint8_t efnum);
/*mcu上报灯效概述*/
void mcu_update_efsketch(com_issue_cmd_TypeDef *p);
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
/*mcu上报定时计划概述表*/
void mcu_update_schedule_sketch(void);
/*mcu上报定时详情*/
void mcu_update_schedule_detail(uint8_t num);
/*










*/
/*针对DPID_SWITCH_LED的处理函数*/
void mcu_download_switch_led(uint8_t sw);
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
/*
 */

/*在线下载固件*/
void mcu_firmware_download(uint8_t *sur, uint16_t position, uint16_t length);
#endif
