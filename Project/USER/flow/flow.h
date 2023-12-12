/*
 * @Author: DESKTOP-AKTRQKB\MY sandote@163.com
 * @Date: 2023-06-27 16:55:54
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * @LastEditTime: 2023-12-06 10:23:10
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\flow\flow.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _FLOW_H
#define _FLOW_H
#include "Function_Init.H"

#define Motion_Static_framepara 0        /*静态帧参数*/
#define Motion_Breath_framepara 400      /*呼吸帧参数*/
#define Motion_Stream_framepara 400    /*流动帧参数*/
#define Motion_Reverberate_framepara 400 /*来回帧参数*/
#define Motion_Hopscotch_framepara 100   /*跳动帧参数*/
#define Motion_Lightning_framepara 1600   /*闪电帧参数*/
#define Motion_Ignite_framepara 250      /*点燃帧参数*/
#define Motion_Random_framepara 255      /*随机帧参数*/


void effect_flow(void); // 灯效流动
void effect_play_color_calu(void);  // 计算灯效播放数据

void Flow_Static_Init(void);
void Flow_Breath_Init(void);
void Flow_Stream_Init(void);
void Flow_Reverberate_Init(void);
void Flow_Hopscotch_Init(void);
void Flow_Lightning_Init(void);
void Flow_Ignite_Init(void);
void Flow_Random_Init(void);

void Flow_Static(void);               /*静态*/
void Flow_Breath(uint8_t speed);      /*呼吸*/
void Flow_Stream(uint8_t speed);      /*流动*/
void Flow_Reverberate(uint8_t speed); /*来回*/
void Flow_Hopscotch(uint8_t speed);   /*跳动*/
void Flow_Lightning(uint8_t speed);   /*闪电*/
void Flow_Ignite(uint8_t speed);      /*点燃*/
void Flow_Random(uint8_t speed);      /*随机*/

void set_dynamic_effect_to_RGB_COLOR(void); // 所有动态灯效都设为非色温颜色数据

#endif
