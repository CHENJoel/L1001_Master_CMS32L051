#ifndef _MOTION_H_
#define _MOTION_H_
#include "Function_Init.H"



#define base_frame 10

#define Motion_Static_framepara 0        /*静态帧参数*/
#define Motion_Breath_framepara 255      /*呼吸帧参数*/
#define Motion_Stream_framepara 255      /*流动帧参数*/
#define Motion_Reverberate_framepara 255 /*来回帧参数*/
#define Motion_Hopscotch_framepara 255   /*跳动帧参数*/
#define Motion_Lightning_framepara 255   /*闪电帧参数*/
#define Motion_Ignite_framepara 500      /*点燃帧参数*/
#define Motion_Random_framepara 255      /*随机帧参数*/

void Effect_Init(void);   // 灯效初始化
void Fetch_EF_DATA(void); // 提取当前灯效的相关数据
void Frame_Reset(void);   // 帧进度复位

void Motion_Static_Init(void);
void Motion_Breath_Init(void);
void Motion_Stream_Init(void);
void Motion_Reverberate_Init(void);
void Motion_Hopscotch_Init(void);
void Motion_Lightning_Init(void);
void Motion_Ignite_Init(void);
void Motion_Random_Init(void);

void Motion_Output(void);
void Motion_Static(void);               /*静态*/
void Motion_Breath(uint8_t speed);      /*呼吸*/
void Motion_Stream(uint8_t speed);      /*流动*/
void Motion_Reverberate(uint8_t speed); /*来回*/
void Motion_Hopscotch(uint8_t speed);   /*跳动*/
void Motion_Lightning(uint8_t speed);   /*闪电*/
void Motion_Ignite(uint8_t speed);      /*点燃*/
void Motion_Random(uint8_t speed);      /*随机*/

#endif
