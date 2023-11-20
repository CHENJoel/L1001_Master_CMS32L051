
#include "mic.h"

mic_TypeDef mic;


uint8_t analyse_pulse(uint32_t in)
{

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
    mic.avg = get_average(&xadc.micbuf, (sizeof(xadc.micbuf) / sizeof(uint16_t)));
    // mic.sum = get_summation(&xadc.micbuf, (sizeof(xadc.micbuf) / sizeof(uint16_t)));
    // // play.efdetail.MicSensitivity = 90;
    // // play.efdetail.Brightness2 = 100;
    // // play.efdetail.Brightness1 = 10;
    // mic.avg=800;    
    // sound = mic.avg * play.efdetail.MicSensitivity;
    // // sound = mic.avg * 100;

    // if (sound > 0xFFF)
    // {
    //     sound = 0xFFF;
    // }
    // mic.grade = get_sound_grade(sound, 0xFFF);
    threshold = 40 * (101 - play.efdetail.MicSensitivity);
    // // if (threshold==0)
    // // {
    // //    threshold=40;
    // // }
    
    mic.grade = get_sound_grade(mic.avg, threshold);
    diff = play.efdetail.Brightness2 - play.efdetail.Brightness1;

    temp = diff / 5;
    temp=100;
    mic.bri_tar = play.efdetail.Brightness1 + temp * mic.grade;

    if (mic.bri_tar > play.efdetail.Brightness2)
    {
        mic.bri_tar = play.efdetail.Brightness2;
    }

    // mic.grade = get_sound_grade(mic.avg, 400);
    // mic.bri_tar = mic.grade * (100 / MIC_SOUND_GRADE);
    
    if (mic.bri_tar > mic.bri_now)
    {
        Gradual_Change(&mic.bri_now, &mic.bri_tar, 60);
    }
    else
    {
        Gradual_Change(&mic.bri_now, &mic.bri_tar, 4);
    }
    PRINT(mic, "%d,%d", mic.avg,mic.sum);
    // // PRINT(mic, "%d", mic.avg);
    //  PRINT(sum, "%d", mic.sum);
    // mic.bri_now=mic.avg/41;
    // PRINT(bri_now, "%d", mic.bri_now);
    // PRINT(mic, "%d,%d,%d", mic.avg,mic.grade,mic.bri_tar);
    // // // // if (DMAVEC->CTRL[CTRL_DATA_ADC].DMACT == 0)
    // // // // {
    // // //     // convert_to_real_mic_val(&mic.buffer, MIC_BUF_SIZE);
    // // //     // mic.avg = get_average(&mic.buffer, MIC_BUF_SIZE);
    // // //     // mic.grade = get_sound_grade(mic.avg, 4000);
    // // //     // if (mic.grade < 3)
    // // //     // {
    // // //     //     mic.grade = 2;
    // // //     // }

    // // //     mic.bri_tar = mic.grade * (100 / MIC_SOUND_GRADE);
    // // //     // mic.bri_tar=temp
    // // //      // if (mic.bri_now < temp)
    // // //     // {
    // // //     //     mic.bri_now = temp;
    // // //     //     // // mic.bri_now = mic.bri_tar;
    // // //     // }
    // // //     // else
    // // //     // {
    // // //     //     temp=0;
    // // //     //     Gradual_Change(&mic.bri_now,&temp,10);
    // // //     // }
    // // //     if (mic.bri_tar>mic.bri_now)
    // // //     {
    // // //         Gradual_Change(&mic.bri_now,&mic.bri_tar,60);
    // // //     }
    // // //     else
    // // //     {
    // // //         Gradual_Change(&mic.bri_now,&mic.bri_tar,4);
    // // //     }

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

/*
 * @Description: 获取音量等级
 * @param: 数据
 * @param: 阈值
 * @return: 等级
*/
uint8_t get_sound_grade(uint16_t data, uint16_t max)
{
    uint8_t i;
    uint16_t gra, level;
    // gra = threshold / MIC_SOUND_GRADE;
    gra = threshold >> 4;   //除16
    if (data>(gra*14))
    {
        return 5;
    }
    if (data > (gra * 11))
    {
        return 4;
    }
    if (data > (gra * 8))
    {
        return 3;
    }
    if (data > (gra * 5))
    {
        return 2;
    }
    return 1;
    // // // if (data > (gra * 14))
    // // // {
    // // //     return 1;
    // // // }
    // // // if (data > (gra * 14))
    // // // {
    // // //     return 0;
    // // // }

    // for (i = MIC_SOUND_GRADE; i > 0; i--)
    // {
    //     level = i * gra;
    //     if (data > level)
    //     {
    //         return i;
    //     }
    // }
    // return 1;
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
