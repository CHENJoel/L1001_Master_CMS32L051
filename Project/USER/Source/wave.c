#include "Function_Init.H"
#include "ware.h"

uint8_t Edge_detect(uint16_t data)
{
    static uint16_t Last_data;   // 上次数据
    static uint16_t start_data;  // 起始数据
    static uint8_t time_cnt;     // 上升计时
    static uint8_t rising_flag;  // 上升沿
    static uint8_t falling_flag; // 下降沿
    static uint8_t rising_time;  // 上升时间
                                 // static uint16_t rising_range; // 上升幅度
                                 // static uint16_t rising_rate;

    uint16_t rising_range=0; // 上升幅度
    uint16_t rising_rate=0;
    uint8_t temp = 0;
    if (data > Last_data)
    {
        if (rising_flag==0)
        {
            start_data = Last_data;
        }
        rising_flag = 1;
        falling_flag = 0;
    }
    else if (data < Last_data)
    {
        falling_flag = 1;
    }
    if (rising_flag)
    {
        if (time_cnt < 255)
        {
            time_cnt++;
        }
    }
    if (falling_flag)
    {
        falling_flag = 0;
        if (rising_flag)
        {
            rising_flag = 0;
            rising_range = Last_data - start_data;
            rising_time = time_cnt;
            rising_rate = rising_range / rising_time;
            // temp = 1;
            // Ware_process(rising_range, time_cnt);
            time_cnt = 0;
        }
    }
    else
    {
        // printf("%d,%d,%d,%d\n",data,rising_range,time_cnt,rising_rate);
    }
    // printf("%d,%d,%d,%d,%d,%d,%d\n", data,Last_data, start_data, rising_range, rising_time, rising_rate,temp);
    if (rising_range < 200)
    {
        rising_range = 0;
    }
    if (rising_range>255)
    {
        rising_range=255;
    }

    // printf("%d,%d,%d\n", data, rising_range, rising_rate);
    // printf("%d,%d\n", data, rising_range);
    Last_data = data;
    return rising_range;
}

// void Ware_process(uint16_t rising_range, uint8_t rising_time)
// {

// }

uint8_t Ware_process(uint16_t range)
{
    static uint8_t i = 0;
    static uint16_t dat_buff[5];
    uint8_t j;
    uint16_t Max;
    // if (i < 5)
    // {
    dat_buff[i] = range;
    if (++i >= 5)
    {
        i = 0;
        Max = 0;
        for (j = 0; j < 5; j++)
        {
            if (Max < dat_buff[j])
            {
                Max = dat_buff[j];
            }
        }
        if (Max > 100)
        {
            return Max;
        }
    }
    return 0;
    // }
}
