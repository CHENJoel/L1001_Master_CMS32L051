/*
 * @Author: your name
 * @Date: 2022-04-22 10:37:07
 * @LastEditTime: 2022-04-23 15:22:42
 * @LastEditors: Please set LastEditors
 * @Description: ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \A5441_Master_CMS32L051\Project\USER\Include\Light.h
 */
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Light.H"
#include "Function_Init.H"



extern unsigned char Bright_Array[5];
extern unsigned char Bright_Level;                            // ���ȵȼ�
// �Զ��л����ݵȼ�
void Light_Level_Change(unsigned char *target,unsigned char *direction, unsigned char *array, unsigned char arrayLength);
// ��������һ������
void Light_Level_Up(unsigned char *target, unsigned char *array, unsigned char arrayLength);
// ���ݽ���һ������
void Light_Level_Down(unsigned char *target, unsigned char *array, unsigned char arrayLength);
// �������
void Gradual_Change(unsigned char *now,unsigned char *target, unsigned char step);
#endif
