/*
 * @Author: DESKTOP-AKTRQKB\MY sandote@163.com
 * @Date: 2022-10-24 10:14:56
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * @LastEditTime: 2023-11-25 13:30:34
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\Include\motion.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _MOTION_H_
#define _MOTION_H_
#include "Function_Init.H"



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

// // // void Motion_Output(void);
void Motion_Static(void);               /*静态*/
void Motion_Breath(uint8_t speed);      /*呼吸*/
void Motion_Stream(uint8_t speed);      /*流动*/
void Motion_Reverberate(uint8_t speed); /*来回*/
void Motion_Hopscotch(uint8_t speed);   /*跳动*/
void Motion_Lightning(uint8_t speed);   /*闪电*/
void Motion_Ignite(uint8_t speed);      /*点燃*/
void Motion_Random(uint8_t speed);      /*随机*/

#endif
