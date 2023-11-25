
#ifndef _PRINTLOG_H_
#define _PRINTLOG_H_
#include "Function_Init.H"
#include "comapp.h"
#include "L0_slave.h"
// #define printlog_enabled     // 使能打印log
#define virtual_device  // 虚拟灯板信息



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

#define PRINT(window, fmt, args...) printlog("{"#window"}"fmt"\n", ##args)

// C语言示例代码
//         1.首先定义宏函数简化后期工作（ARMCC/ARMGCC/GCC编译器）：
//             #define PRINT(window, fmt, args...) printf("{"#window"}"fmt"\n", ##args)
//         2.若要将电压和电流数据进行绘图，并将功率数据分窗显示，可这样调用：
//             PRINT(plotter, "%d,%d", current, voltage);
//             PRINT(power, "the power is %d W", current * voltage);
//         3.实际显示效果可能如下：
//             {plotter}3,2
//             {power}the power is 6 W



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
//
void print_clock_detial(clock_detail_TypeDef *p); // 打印定时表详情
void print_all_clock_detail(void);                // 打印全部定时表详情
//
/*打印在线从机信息*/
void print_online_slave_data(void);
/*运行灯效详情log*/
void print_play_effect_detial(void);

/*app控制灯板的log*/
void print_device_control(app_device_control_Typedef *x);
//

void print_local_rtc_time(void); // 打印本地rtc时钟
//

void print_mini_device_data(mini_device_data_TypeDef *dev); // 打印设备迷你信息
//
void print_xPlay_color(L0_cmd_playCOLOR_Typedef *xPlay,uint8_t num);    // 打印颜色输出

#endif
