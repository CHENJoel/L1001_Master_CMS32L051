/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-05-18 16:57:41
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
.chen sandote@163.om
 * .chen sandote@163.om
 * @LastEditTime: 2023-10-13 16:08:46
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\debug\debug.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#ifndef  DEBUD_H
#define  DEBUD_H
#include "Function_Init.H"

#define log(...) printf(__VA_ARGS__)

void debug(void);


extern uint8_t test_onoff;
extern uint8_t test_color_num;
extern uint8_t test_brightness;

/*norflash循环读写测试*/
void norflash_auto_rw_test(void);

/*测试灯效的存储读写*/
void debug_save_effect_detial(void);
/*测试添加自定义灯效*/
void debug_add_original_ef(void);
/*测试删除自定义灯效*/
void debug_delete_original_ef(void);
/*测试删除播放列表*/
void debug_delete_playlist(void);
/*测试添加播放列表*/
void debug_add_playlist(void);
/*测试添加定时表*/
void debug_add_clock_schedule(void);
/*测试删除定时表*/
void debug_delete_schedule(void);
/*切换下一内置灯效*/
void debug_play_next_effect(void);
/*切换上一内置灯效*/
void debug_play_last_effect(void);

/*测试开始暂停播放颜色*/
void test_onoff_play(void);
/*测试播放颜色*/
void test_play_color(void);
/*测试切换颜色*/
void test_change_color(uint8_t dir);
/*测试单击加减亮度*/
void test_click_brightness(uint8_t dir);
/*测试长按加减亮度*/
void test_long_brightness(uint8_t dir);

/*循环切换颜色*/
void test_switch_color(void);
/*循环切换亮度*/
void test_switch_brightness(void);
/*循环老化测试*/
void test_aging_cycle(void);

void debug_K1_LONG(void);
/*按键1服务调试函数*/
void debug_K1(void);
/*按键2服务调试函数*/
void debug_K2(void);
/*按键3服务调试函数*/
void debug_K3(void);
/*按键4服务调试函数*/
void debug_K4(void);
/*按键5服务调试函数*/
void debug_K5(void);

/*led测试*/
void debug_ledplay(void);


void debug_play_rgbbr(void);
#endif
