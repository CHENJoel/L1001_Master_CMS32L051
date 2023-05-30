#ifndef _PRINTLOG_H_
#define _PRINTLOG_H_
#include "Function_Init.H"
#include "comapp.h"

#define printlog_enabled    // 使能打印log

//断言
#define vAssertCalled(char,int) printf("Error:%s,%d\r\n",char,int)


#ifdef printlog_enabled
    #define printlog(str) printf(str)
    #define configASSERT(x) if((x)==0) vAssertCalled(__FILE__,__LINE__)
#else
    #define printlog(str) ;
    #define configASSERT(x) ;
#endif





/*打印hex*/
void printhex_my(uint8_t *sur, uint8_t len);
/*打印字符串*/
void printstr_my(uint8_t *sur, uint8_t len);
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
/*打印灯效列表*/
void print_ef_ranklist(ef_ranklist_TypeDef* p);
#endif
