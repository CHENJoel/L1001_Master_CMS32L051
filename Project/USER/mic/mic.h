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
#define MIC_SOUND_GRADE 8 // 音量等级
#define MIC_FILTER_TH 50 // 底噪滤波阈值

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

/*处理咪头数据*/
void process_mic_data(void);
/*开始咪头采样*/
void start_mic_sample(void);
/*求均值*/
uint16_t get_average(uint16_t *sur, uint8_t len);
//
uint32_t get_summation(uint16_t *sur, uint8_t len); // 求和
/*转换成真实值*/
void convert_to_real_mic_val(uint16_t *sur, uint8_t len);
/*获取音量等级*/
uint8_t get_sound_grade(uint16_t data, uint16_t max);
#endif
