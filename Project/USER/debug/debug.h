#ifndef  DEBUD_H
#define  DEBUD_H
#include "Function_Init.H"

#define log(...) printf(__VA_ARGS__)

void Debug(void);




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
