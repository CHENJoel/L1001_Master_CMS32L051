/*
 * @Author: DESKTOP-AKTRQKB\MY sandote@163.com
 * @Date: 2023-06-27 16:55:54
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * @LastEditTime: 2023-12-06 10:23:10
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\flow\flow.h
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _FLOW_H
#define _FLOW_H
#include "Function_Init.H"

#define Motion_Static_framepara 0        /*��̬֡����*/
#define Motion_Breath_framepara 400      /*����֡����*/
#define Motion_Stream_framepara 400    /*����֡����*/
#define Motion_Reverberate_framepara 400 /*����֡����*/
#define Motion_Hopscotch_framepara 100   /*����֡����*/
#define Motion_Lightning_framepara 1600   /*����֡����*/
#define Motion_Ignite_framepara 250      /*��ȼ֡����*/
#define Motion_Random_framepara 255      /*���֡����*/


void effect_flow(void); // ��Ч����
void effect_play_color_calu(void);  // �����Ч��������

void Flow_Static_Init(void);
void Flow_Breath_Init(void);
void Flow_Stream_Init(void);
void Flow_Reverberate_Init(void);
void Flow_Hopscotch_Init(void);
void Flow_Lightning_Init(void);
void Flow_Ignite_Init(void);
void Flow_Random_Init(void);

void Flow_Static(void);               /*��̬*/
void Flow_Breath(uint8_t speed);      /*����*/
void Flow_Stream(uint8_t speed);      /*����*/
void Flow_Reverberate(uint8_t speed); /*����*/
void Flow_Hopscotch(uint8_t speed);   /*����*/
void Flow_Lightning(uint8_t speed);   /*����*/
void Flow_Ignite(uint8_t speed);      /*��ȼ*/
void Flow_Random(uint8_t speed);      /*���*/

void set_dynamic_effect_to_RGB_COLOR(void); // ���ж�̬��Ч����Ϊ��ɫ����ɫ����

#endif
