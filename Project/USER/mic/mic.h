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
 * @LastEditTime: 2023-12-09 16:32:48
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
    // uint16_t buffer[1];
    uint16_t avg;
    uint32_t sum;
    uint8_t grade;
    uint8_t sound;
    uint8_t pulse;  // 脉冲强度
    uint8_t frequ;  // 脉冲强度
    uint8_t bri_tar;
    uint8_t bri_now;
    uint16_t logavg;
    uint16_t logavg_last;
    uint16_t differ;
    uint16_t longavg;
}mic_TypeDef;
extern mic_TypeDef mic;


typedef struct
{
    uint8_t pw;
    uint8_t cnt;
    uint16_t data[16];
}datalog_TypeDef;
extern datalog_TypeDef miclog;

typedef struct
{
    uint8_t pw;
    uint8_t cnt;
    uint16_t data[64];
}longdatalog_TypeDef;
extern longdatalog_TypeDef longmiclog;


typedef struct
{
    uint16_t cnt;     
    uint16_t max_val;   // 采样时间内的最大值
    uint16_t min_val;   // 采样时间内的最小值

    uint16_t max_level; // 输出最大水平
    uint16_t min_level; // 输出最小水平

}rangelevel_TypeDef;
extern rangelevel_TypeDef micrange;

///
uint8_t get_mic_pulse(uint8_t in);                                      // 获取声音脉冲强度
uint8_t get_sound_intensity(uint32_t data, uint16_t sens);              // 获取声音强度
uint8_t convert_bright_in_range(uint8_t val, uint8_t ra1, uint8_t ra2); // 输出亮度转换成区间值
//
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
//
void fft_test(void);    //  傅里叶变换测试


//
void init_data_log(datalog_TypeDef *log);
void put_data_in_log(datalog_TypeDef *log, uint16_t data,uint8_t len);
uint16_t get_avg_in_log(datalog_TypeDef *log);
void calculate_refer_range(uint16_t data, uint8_t sens);
uint8_t get_sound(uint16_t data);
#endif
