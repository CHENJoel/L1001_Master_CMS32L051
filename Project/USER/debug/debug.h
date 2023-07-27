#ifndef  DEBUD_H
#define  DEBUD_H
#include "Function_Init.H"

#define log(...) printf(__VA_ARGS__)

void Debug(void);


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
void debug_add_schedule(void);
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
#endif
