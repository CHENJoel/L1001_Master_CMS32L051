/*
 * @Author: your name
 * @Date: 2022-04-22 10:37:07
 * @LastEditTime: 2022-04-23 15:22:42
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \A5441_Master_CMS32L051\Project\USER\Include\Light.h
 */
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Light.H"
#include "Function_Init.H"



extern unsigned char Bright_Array[5];
extern unsigned char Bright_Level;                            // 亮度等级
// 自动切换数据等级
void Light_Level_Change(unsigned char *target,unsigned char *direction, unsigned char *array, unsigned char arrayLength);
// 数据增加一个级别
void Light_Level_Up(unsigned char *target, unsigned char *array, unsigned char arrayLength);
// 数据降低一个级别
void Light_Level_Down(unsigned char *target, unsigned char *array, unsigned char arrayLength);
// 渐变计算
void Gradual_Change(unsigned char *now,unsigned char *target, unsigned char step);
#endif
