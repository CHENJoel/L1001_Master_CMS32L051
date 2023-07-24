#ifndef _FLOW_H
#define _FLOW_H
#include "Function_Init.H"


/*
 * @Description: 计算灯效播放数据
 * @param:
 * @return:
*/
void effect_play_color_calu(void);

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

#endif
