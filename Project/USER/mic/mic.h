/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-06-30 14:13:17
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
 * .chen sandote@163.om
 * @LastEditTime: 2023-11-20 09:56:47
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\mic\mic.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#ifndef _MIC_H
#define _MIC_H
#include "Function_Init.H"

#define MIC_BUF_SIZE (sizeof(mic.buffer)/sizeof(uint16_t))
#define MIC_REF 2048
#define MIC_SOUND_GRADE 8 // �����ȼ�
#define MIC_FILTER_TH 50 // �����˲���ֵ

typedef struct
{
    uint16_t buffer[1];
    uint16_t avg;
    uint32_t sum;
    uint8_t grade;
    uint8_t bri_tar;
    uint8_t bri_now;
}mic_TypeDef;
extern mic_TypeDef mic;

/*������ͷ����*/
void process_mic_data(void);
/*��ʼ��ͷ����*/
void start_mic_sample(void);
/*���ֵ*/
uint16_t get_average(uint16_t *sur, uint8_t len);
//
uint32_t get_summation(uint16_t *sur, uint8_t len); // ���
/*ת������ʵֵ*/
void convert_to_real_mic_val(uint16_t *sur, uint8_t len);
/*��ȡ�����ȼ�*/
uint8_t get_sound_grade(uint16_t data, uint16_t max);
#endif
