#ifndef _PRINTLOG_H_
#define _PRINTLOG_H_
#include "Function_Init.H"
#include "comapp.h"

#define printlog_enabled    // 使能打印log
// assert
//断言
#define vAssertCalled(char,int) printf("Error:%s,%d\r\n",char,int)

#ifdef printlog_enabled
    #define printlog(...) printf(__VA_ARGS__)
    #define printAssert() vAssertCalled(__FILE__,__LINE__)
    // #define printlog(str) printf(str)
    #define configASSERT(x) if((x)==0) vAssertCalled(__FILE__,__LINE__)
    #define printnumlog(num) printf("[num:%d]\r",num)
    // // #define configASSERT(x) vAssertCalled(__FILE__,__LINE__)
#else

    #define printlog(...)
    #define configASSERT(x)
    #define printAssert()
    #define printnumlog(num) printf("[num:%d]\r",num)
#endif





/*打印hex*/
void printhex_my(uint8_t *sur, uint32_t len);
/*打印字符串*/
void printstr_my(uint8_t *sur, uint32_t len);
/*打印动态效果*/
void print_flow(Flow_Enum num);
/*打印运动方向*/
void print_direction(Direction_Enum num);
/*打印灯效类型*/
void print_effecttype(EffectType_Enum num);
/*打印灯效属性*/
void print_attribute(Attribute_Enum num);
/*app灯效详情log*/
void print_com_effect_detial_log(com_effect_detial_TypeDef *p);
/*灯效详情log*/
void print_effect_detial(Efdetail_TypeDef *p,uint8_t efnum);
/*打印获取存储区的灯效详情*/
void print_get_ef_detial(uint8_t efnum);
/*打印灯效概述*/
void print_effect_sketch(Efminidetail_TypeDef *p,uint8_t efnum);
/*打印获取自定义灯效列表*/
void print_get_original_ef_ranklist(void);
/*打印获取全部灯效列表*/
void print_get_all_ef_ranklist(void);
/*打印获取收藏灯效列表*/
void print_get_favorites_ef_ranklist(void);
/*打印获取播放列表*/
void print_get_playlist_ranklist(void);
/*打印灯效列表*/
void print_ef_ranklist(ef_ranklist_TypeDef* p);
/*打印播放列表的顺序表*/
void print_playlist_ranklist(playlist_ranklist_TypeDef* p);
/*打印通信播放列表的顺序表*/
void print_com_playlist_ranklist(com_playlist_TypeDef* p);
/*打印播放详情*/
void print_playdetial(playdetail_TypeDef *p, uint8_t playnum);
/*打印app下发播放详情*/
void print_com_playdetial(com_play_detial_TypeDef *p);
/*打印播放历史*/
void print_play_history(void);
/*打印播放状态*/
void print_playstatus(void);
/*打印从机设备信息*/
void print_slave_data(void);
/*打印从机设备的颜色*/
void print_slave_color(void);

/*打印名字*/
void print_name(name_TypeDef*p);
/*打印定时表*/
void print_schedule(void);
#endif
