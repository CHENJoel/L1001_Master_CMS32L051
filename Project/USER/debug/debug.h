/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-05-18 16:57:41
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
.chen sandote@163.om
 * .chen sandote@163.om
 * @LastEditTime: 2023-10-13 16:08:46
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\debug\debug.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#ifndef  DEBUD_H
#define  DEBUD_H
#include "Function_Init.H"

#define log(...) printf(__VA_ARGS__)

void debug(void);


extern uint8_t test_onoff;
extern uint8_t test_color_num;
extern uint8_t test_brightness;

/*norflashѭ����д����*/
void norflash_auto_rw_test(void);

/*���Ե�Ч�Ĵ洢��д*/
void debug_save_effect_detial(void);
/*��������Զ����Ч*/
void debug_add_original_ef(void);
/*����ɾ���Զ����Ч*/
void debug_delete_original_ef(void);
/*����ɾ�������б�*/
void debug_delete_playlist(void);
/*������Ӳ����б�*/
void debug_add_playlist(void);
/*������Ӷ�ʱ��*/
void debug_add_clock_schedule(void);
/*����ɾ����ʱ��*/
void debug_delete_schedule(void);
/*�л���һ���õ�Ч*/
void debug_play_next_effect(void);
/*�л���һ���õ�Ч*/
void debug_play_last_effect(void);

/*���Կ�ʼ��ͣ������ɫ*/
void test_onoff_play(void);
/*���Բ�����ɫ*/
void test_play_color(void);
/*�����л���ɫ*/
void test_change_color(uint8_t dir);
/*���Ե����Ӽ�����*/
void test_click_brightness(uint8_t dir);
/*���Գ����Ӽ�����*/
void test_long_brightness(uint8_t dir);

/*ѭ���л���ɫ*/
void test_switch_color(void);
/*ѭ���л�����*/
void test_switch_brightness(void);
/*ѭ���ϻ�����*/
void test_aging_cycle(void);

void debug_K1_LONG(void);
/*����1������Ժ���*/
void debug_K1(void);
/*����2������Ժ���*/
void debug_K2(void);
/*����3������Ժ���*/
void debug_K3(void);
/*����4������Ժ���*/
void debug_K4(void);
/*����5������Ժ���*/
void debug_K5(void);

/*led����*/
void debug_ledplay(void);


void debug_play_rgbbr(void);
#endif
