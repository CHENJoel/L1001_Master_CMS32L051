
#include "mic.h"

mic_TypeDef mic;
datalog_TypeDef miclog;
longdatalog_TypeDef longmiclog;
rangelevel_TypeDef micrange;
/*
 * @Description: 获取声音脉冲强度
 * @param:
 * @return:
 */
uint8_t get_mic_pulse(uint8_t in)
{
    static uint8_t last_data;
    static uint8_t min;
    uint8_t out = 0;
#define MIC_PULSE_MAX 100
#define MIC_PULSE_MIN 0
    if (in > last_data) // 上升沿开始
    {
        min = last_data;
    }
    else if (in < last_data) // 开始下降沿
    {
        out = last_data - min;
    }
    last_data = in;
    if (out > MIC_PULSE_MAX)
    {
        out = MIC_PULSE_MAX;
    }
    if (out < MIC_PULSE_MIN)
    {
        out = MIC_PULSE_MIN;
    }
    return out;
}

/* 
 * @Description: 计算脉冲频率
 * @param: 
 * @return: 
*/ 
void convert_mic_frequency(uint8_t pulse)
{
#define MIC_PERIOD 100   // 计算周期
#define MIC_FREQ_MAX 100
#define MIC_FREQ_MIN 1

    static uint8_t fretime_cnt;
    static uint8_t pulse_cnt;
    uint16_t mic_freq;
    if (++fretime_cnt > MIC_PERIOD)
    {
        // // mic_freq = pulse_cnt * 100 / MIC_PERIOD;    // 
        // mic_freq *= 5;
        mic_freq = pulse_cnt * 10;
        if (mic_freq > MIC_FREQ_MAX)
        {
            mic_freq = MIC_FREQ_MAX;
        }
        if (mic_freq < MIC_FREQ_MIN)
        {
            mic_freq = MIC_FREQ_MIN;
        }
        mic.frequ = mic_freq;
        fretime_cnt = 0;
        pulse_cnt = 0;
    }
    else
    {
        if (pulse)
        {
            pulse_cnt++;
        }
    }
}

/*
 * @Description: 获取声音强度
* @param: 数据0~4095
 * @param: 灵敏度0~100
 * @return: 等级0~100
 */
uint8_t get_sound_intensity(uint32_t data, uint16_t sens)
{
    uint32_t grade;
    uint16_t max;
    if (sens > 100)
    {
        return 100;
    }
    max = 4 * (100 - sens) + 4;
    data *= 100;
    grade = data / max;
    if (grade > 100)
    {
        grade = 100;
    }
    return grade;
    //----------------------------------------------------------------

}

/* 
 * @Description: 输出亮度转换成区间值
 * @param: 原始亮度 0~100
 * @param: 边界1 0~100
 * @param: 边界2 0~100
 * @return: 输出亮度 0~100
*/ 
uint8_t convert_bright_in_range(uint8_t val, uint8_t ra1, uint8_t ra2)
{
    uint8_t diff; // 量程
    uint8_t out;
    if (ra1 > ra2)
    {
        diff = ra1 - ra2;
        out = diff * val / 100;
        return ra2 + out;
    }
    else
    {
        diff = ra2 - ra1;
        out = diff * val / 100;
        return ra1 + out;
    }
}

/*
 * @Description: 处理咪头数据
 * @param:
 * @return:
*/
void process_mic_data(void)
{
    // // start_mic_sample();
    uint8_t i;
    uint16_t temp;
    uint32_t sound;    
    uint16_t diff;
    uint16_t threshold;

    // play.efdetail.Brightness1=0;
    // play.efdetail.Brightness2=100;
    // play.efdetail.MicSensitivity=100;


    // if (play.work.global_setting.microphone_ensta==ENABLE_STA)
    // {
        mic.avg = get_average(&xadc.micbuf, (sizeof(xadc.micbuf) / sizeof(uint16_t))); // 获取声音均值
        // // mic.sound = get_sound_intensity(mic.avg, play.efdetail.MicSensitivity);        // 获取声音强度
    // }
    // else
    // {
    //     mic.sound = 100;
    // }
    put_data_in_log(&miclog, mic.avg, sizeof(miclog.data) / sizeof(miclog.data[0]));
    mic.logavg = get_avg_in_log(&miclog);
    // // mic.longavg = get_avg_in_log(&longmiclog);
    calculate_refer_range(mic.logavg,play.efdetail.MicSensitivity);
    mic.sound = get_sound(mic.logavg);
    mic.pulse = get_mic_pulse(mic.logavg); 
    // // mic.pulse = get_mic_pulse(mic.sound);                                                                   // 获取声音脉冲强度
    convert_mic_frequency(mic.pulse);                                                                       // 计算脉冲频率

    mic.bri_tar = convert_bright_in_range(mic.sound, play.efdetail.Brightness1, play.efdetail.Brightness2); // 输出亮度转换成区间值
    
    // // put_data_in_log(&longmiclog,mic.avg,sizeof(longmiclog.data)/sizeof(longmiclog.data[0]));
    // if (mic.bri_tar > mic.bri_now)
    // {
    //     Gradual_Change(&mic.bri_now, &mic.bri_tar, 60);
    // }
    // else
    // {
    //     Gradual_Change(&mic.bri_now, &mic.bri_tar, 50);
    // }

    Gradual_Change(&mic.bri_now, &mic.bri_tar, 60);
    // // mic.bri_now= mic.bri_tar ;
    if (mic.bri_now > 100)
    {
        mic.bri_now = 255;
    }

    if (mic.logavg > mic.logavg_last)
    {
        mic.differ = mic.logavg - mic.logavg_last;
    }
    else
    {
        mic.differ = 0;
    }

    mic.logavg_last = mic.logavg;

    // PRINT(bir, "%d,%d", mic.logavg, mic.bri_now);
    // // PRINT(mic, "%d,%d", mic.avg,mic.sum);
    // PRINT(mic, "%d,%d", mic.avg,mic.logavg);
    // PRINT(avg, "%d,%d,%d", mic.logavg, micrange.min_level, micrange.max_level);
    // PRINT(avg, "%d,%d", mic.logavg,mic.longavg);
    // PRINT(dif, "%d,%d", mic.logavg,mic.differ);
    // PRINT(avg, "%d,%d,%d",mic.avg, mic.logavg,mic.longavg);
    // PRINT(mic, "%d,%d,%d", mic.avg, mic.sound,mic.logavg);
    //  PRINT(sum, "%d", mic.sum);
    // mic.bri_now=mic.avg/41;
    // PRINT(bri_now, "%d", mic.bri_now);
    // PRINT(mic, "%d,%d,%d", mic.avg,mic.grade,mic.bri_tar);

    // // //     // printlog("bri_now %d",mic.bri_now);
    // // //     //  PRINT(bri_now, "%d", mic.bri_now);
    // // //     // play_color_in_all_salve_light(mic.bri_now,0,255,0,0);
    // // //     // PRINT(mic, "%d,%d,%d", mic.avg,mic.grade,mic.bri_now);
    // // //     // PRINT(mic, "%d", mic.avg);
    // // //     // PRINT(mic, "%d,%d,%d,%d", mic.avg,mic.grade,temp);
    // // //     // PRINT(mic, "%d,%d,%d,%d", mic.avg,mic.grade,temp,mic.bri_now);
    // // //     // start_mic_sample();

    // // // // }
}

/*
 * @Description: 开始咪头采样
 * @param:
 * @return:
*/
void start_mic_sample(void)
{
    // // // LED_Blue_on();

    // // // DMA_Stop(DMA_VECTOR_ADC);
    // // // ADC_Start(ADC_CHANNEL_0);
    // // // DMA_Start(DMA_VECTOR_ADC, CTRL_DATA_ADC, DMA_MODE_NORMAL,
    // // //           DMA_SIZE_HALF, MIC_BUF_SIZE, (uint16_t *)&ADC->ADCR, &mic.buffer);
    // // // while (DMAVEC->CTRL[CTRL_DATA_ADC].DMACT != 0)
    // // // {
    // // //     ;
    // // // }
    // // // LED_Blue_off();
}

/*
 * @Description: 求均值
 * @param: 源数据指针
 * @param: 数据长度
 * @return: 均值
*/
uint16_t get_average(uint16_t *sur, uint8_t len)
{
    uint32_t avg=0;
    uint16_t i;
    for (i = 0; i < len; i++)
    {
        avg += sur[i];
    }
    avg /= len;

    // avg = sur[0];
    // // for (i = 1; i < len; i++)
    // // {
    // //     avg += sur[i];
    // //     avg /= 2;
    // // }
    return avg;
}

/* 
 * @Description: 求和
 * @param: 
 * @param: 
 * @return: 
*/ 
uint32_t get_summation(uint16_t *sur, uint8_t len)
{
    uint32_t sum = 0;
    uint8_t i;
    for (i = 0; i < len; i++)
    {
        sum += sur[i];
    }
    return sum;
}


/*
 * @Description: 转换成真实值，相对基准值的绝对值
 * @param: 源数据指针
 * @param: 数据长度
 * @return:
 */
void convert_to_real_mic_val(uint16_t *sur, uint8_t len)
{
    uint16_t i;
    for (i = 0; i < len; i++)
    {
        // if (sur[i] > MIC_REF)
        // {
        //     sur[i] = sur[i] - MIC_REF;
        // }
        // else
        // {
        //     sur[i] = MIC_REF - sur[i];
        // }
        if (sur[i] < MIC_FILTER_TH) // 滤底噪
        {
            sur[i] = MIC_FILTER_TH/2;
        }
    }
}



// Gradual_Change(&SYS.Brightness.Now, &SYS.Brightness.Target, 10);
/*
 * @Description: 律动模式
 * @param:
 * @return:
*/
void rhythm_mode(void)
{

}

/* 
 * @Description: 傅里叶变换测试
 * @param: 
 * @return: 
*/ 
void fft_test(void)
{
    uint8_t i;
    uint16_t data[FFT_N/2];
    uint16_t lastdata[FFT_N/2];
    uint16_t num=0;
    #ifndef printlog_enabled
    LED_Red_off();
    LED_Blue_off();
    for ( i = 0; i < FFT_N; i++)
    {
        Refresh_Data(i,(double)xadc.micbuf[i]);
        PRINT(mic, "%d",xadc.micbuf[i]);
    }
    // data_of_N_FFT[FFT_N] = {5120,0,4096,0,3072,0,4096,0,5120,0,4096,0,3072,0,4096,0,5120,0,4096,0,3072,0,4096,0,5120,0,4096,0,3072,0,4096,0,5120,0,4096,0,3072,0,4096,0,5120,0,4096,0,3072,0,4096,0,5120,0,4096,0,3072,0,4096,0,5120,0,4096,0,3072,0,4096,0,

// };		
    Init_FFT();
    FFT();      // 4ms
    abs_fft();

    for (i = 0; i < sizeof(data) / sizeof(uint16_t); i++)
    {
        data[i] = (uint16_t)data_of_N_FFT[i].real;
    }
    
    
    
    for (i = 0; i < sizeof(data) / sizeof(uint16_t); i++)
    {
        if (data[i]> lastdata[i])
        {
           num++;
        }
    }


    for (i = 0; i < sizeof(data) / sizeof(uint16_t); i++)
    {
        lastdata[i] = data[i];
    }
    num*=100;
    PRINT(num, "%d",num);       
    PRINT(fft, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",data[1],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9],data[10],data[11],data[12],data[13],data[14],data[15]);       
    // / // LED_Blue_on();
    // PRINT(fft, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", data_of_N_FFT[30].real,data_of_N_FFT[1].real,data_of_N_FFT[2].real,data_of_N_FFT[3].real,data_of_N_FFT[4].real,data_of_N_FFT[5].real,data_of_N_FFT[6].real,data_of_N_FFT[7].real,data_of_N_FFT[8].real,data_of_N_FFT[9].real,data_of_N_FFT[10].real,data_of_N_FFT[11].real,data_of_N_FFT[12].real,data_of_N_FFT[13].real,data_of_N_FFT[14].real,data_of_N_FFT[15].real);
    // // PRINT(fft, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", (uint32_t)data_of_N_FFT[0].real,(uint32_t)data_of_N_FFT[1].real,(uint32_t)data_of_N_FFT[2].real,(uint32_t)data_of_N_FFT[3].real,(uint32_t)data_of_N_FFT[4].real,(uint32_t)data_of_N_FFT[5].real,(uint32_t)data_of_N_FFT[6].real,(uint32_t)data_of_N_FFT[7].real,(uint32_t)data_of_N_FFT[8].real,(uint32_t)data_of_N_FFT[9].real,(uint32_t)data_of_N_FFT[10].real,(uint32_t)data_of_N_FFT[11].real,(uint32_t)data_of_N_FFT[12].real,(uint32_t)data_of_N_FFT[13].real,(uint32_t)data_of_N_FFT[14].real,(uint32_t)data_of_N_FFT[15].real);
    // // PRINT(fft, "%lf", data_of_N_FFT[0].real);
    // LED_Red_on();
    // printf("fft");
    // for ( i = 0; i < FFT_N/2; i++)
    // {
    //     printf("%d,%lf\r",(uint16_t)i,data_of_N_FFT[i].real);
    //     // // PRINT("%d,%lf\r",(uint16_t)i,data_of_N_FFT[i].real);
    // }
			
    // // // PRINT(fft, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", data_of_N_FFT[0].real,data_of_N_FFT[1].real,data_of_N_FFT[2].real,data_of_N_FFT[3].real,data_of_N_FFT[4].real,data_of_N_FFT[5].real,data_of_N_FFT[6].real,data_of_N_FFT[7].real,data_of_N_FFT[9].real,data_of_N_FFT[10].real,data_of_N_FFT[11].real,data_of_N_FFT[12].real,data_of_N_FFT[13].real,data_of_N_FFT[14].real,data_of_N_FFT[15].real);
    #endif
}

void init_data_log(datalog_TypeDef *log)
{
    my_memset(log, 0, sizeof(datalog_TypeDef));
}

void put_data_in_log(datalog_TypeDef *log, uint16_t data,uint8_t len)
{
    log->data[log->pw] = data;
    if (++log->pw >= len)
    {
        log->pw = 0;
    }
    if (++log->cnt >= len)
    {
        log->cnt = len;
    }

    // // // if (++log->pw >= (sizeof(log->data) / sizeof(log->data[0])))
    // // // {
    // // //    log->pw = 0;
    // // // }
    // // // if (++log->cnt>= (sizeof(log->data) / sizeof(log->data[0])))
    // // // {
    // // //     log->cnt = (sizeof(log->data) / sizeof(log->data[0]));
    // // // }
    
}

uint16_t get_avg_in_log(datalog_TypeDef *log)
{
    uint8_t i;
    uint32_t sum = 0;
    for (i = 0; i < log->cnt; i++)
    {
        sum += log->data[i];
    }
    return sum / log->cnt;
}


/* 
 * @Description: 计算基准范围
 * @param: 
 * @return: 
*/
void calculate_refer_range(uint16_t data, uint8_t sens)
{
#define RANGE_CALCULATE_TIME 250
#define MIN_RANG 200       
    uint16_t range;
    if (micrange.max_val < data)
    {
        micrange.max_val = data; // 求最大值
    }
    if (micrange.min_val > data)
    {
        micrange.min_val = data; // 求最小值
    }
    if (micrange.cnt <= RANGE_CALCULATE_TIME)
    {
        micrange.cnt++;
    }
    else
    {
        micrange.cnt = 0;
        micrange.max_level = micrange.max_val * 1;
        micrange.min_level = micrange.min_val;
        micrange.max_val = 0;
        micrange.min_val = 0xFFFF;
        range = micrange.max_level - micrange.min_level;
        if (range < MIN_RANG)
        {
            range = MIN_RANG;
        }
        range = range * (120 - sens) / 100;
        micrange.max_level = micrange.min_level + range;    
    }
}

uint8_t get_sound(uint16_t data)
{
    uint16_t range;
    range = micrange.max_level - micrange.min_level;
    if (data > micrange.max_level)
    {
        data = micrange.max_level;
    }
    if (data < micrange.min_level)
    {
        data = micrange.min_level;
    }
    data -= micrange.min_level;
    return data * 100 / range;
    // // // // // // // // // // data = data * 100 / range;
     // // // // // // // // // // data = data / 20;
    // // // // // // // // // // data = (data + 1) * 20;
    // // // // // // // // // // return data;
}
