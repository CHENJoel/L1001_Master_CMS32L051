
/*
 * @Author: DESKTOP-AKTRQKB\MY sandote@163.com
 * @Date: 2023-06-07 10:04:26
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * @LastEditTime: 2023-12-05 16:28:40
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\master\master.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "master.h"
random_Typdef random;
sys_TypeDef sys;
adcdma_task_TypeDef xadc;
FlagTypeDef flag;
fifo_t uart1_fifo;
TwinkleTypeDef Twinkle;

/* 
 * @Description: wifi模组初始化
 * @param: 
 * @return: 
*/ 
void wifi_module_init(void)
{   
	wifi_protocol_init();   // 协议串口初始化函数
	open_module_reset_state_serve();	// 打开模块重置状态通知
}

/* 
 * @Description: 单片机重启
 * @param: 
 * @return: 
*/ 
void mcu_restart(void)
{
    printlog("/r/r/r/r/rmcu restart.../r");
    __NVIC_SystemReset();
}

/* 
 * @Description: 获取在norflash中的固件版本号
 * @param: 
 * @param: 
 * @return: 
*/ 
uint8_t get_norflash_firmware_version(uint8_t* str,uint8_t len)
{
    FLASHSPI_PageRead((uint8_t *)str, (uint32_t)&((firmware_inf_TypeDef*)(((uint32_t) & (NORFLASH->ota.data.package)) + APP_INF_ADDR- APP_BASIC_ADDR ))->version, len);
}






/*
 * @Description: 设置固件下载中标志
 * @param:
 * @return:
 */
void set_firmware_downloading_flag(void)
{
    uint8_t download[FW_downloadFLAG_SIZE];
    printlog("set_firmware_downloading_flag\r");
    sprintf(&download, FIRMWARE_DOWNLOAD_FLAG);
    FlashROM_Insert(&download, &(OCFLASH->user.data.FW_downloadFLAG), sizeof(download));
}

/* 
 * @Description: 设置固件下载完成标志
 * @param: 
 * @return: 
*/ 
void set_firmware_download_finish_flag(void)
{
    uint8_t download[FW_downloadFLAG_SIZE];
    printlog("set_firmware_download_finish_flag\r");
    sprintf(&download, FIRMWARE_IN_FLASH_FLAG);
    FlashROM_Insert(&download, &(OCFLASH->user.data.FW_downloadFLAG), sizeof(download));
}



/*
 * @Description: 清除固件下载标志
 * @param:
 * @return:
 */
void clear_firmware_download_flag(void)
{
    uint8_t download[FW_downloadFLAG_SIZE];
    printlog("clear_firmware_download_flag\r");
    memset(&download, 0, sizeof(download));
    FlashROM_Insert(&download, &(OCFLASH->user.data.FW_downloadFLAG), sizeof(download));
}

/*
 * @Description: 获取ota升级状态
 * @param:
 * @return:
 */
void get_first_ota_status(void)
{
    uint8_t version[OTA_updateFLAG_SIZE];

    #define FIRMWARE_DOWNLOAD_FLAG "FIRMWARE DOWNLOAD" // 固件下载标志
    #define FIRMWARE_IN_FLASH_FLAG "FIRMWARE IN FLASH" // 固件在本地标志
    if (my_strcmp(&(OCFLASH->user.data.FW_downloadFLAG), FIRMWARE_IN_FLASH_FLAG) == 0) // 检查是否含有固件在本地标志
    {
        printlog("found frimware in norflash flag\r");
        get_norflash_firmware_version(&version, sizeof(firmware_inf.version));
        if (my_strcmp(&version, &firmware_inf.version)) // 版本不一致
        {
            erase_firmware_block();
            sys.sta.ota_state = OTA_FAILED; // 升级失败
            printlog("\rFirmware update failed\r\n");
        }
        else // 版本一致
        {
            erase_firmware_block();
            sys.sta.ota_state = OTA_SUCCES; // 升级成功
            printlog("\rFirmware update successful\r\n");
        }
        clear_firmware_download_flag();
    }
    else if (strcmp(&(OCFLASH->user.data.FW_downloadFLAG), FIRMWARE_DOWNLOAD_FLAG) == 0)
    {
        sys.sta.ota_state = OTA_FAILED; // 固件下载失败（norflash中无固件信息）
        printlog("frimware download failed \r");    
        clear_firmware_download_flag();
    }
    else
    {
        sys.sta.ota_state = NO_OTA; // 最近无升级任务
        printlog("\rno ota\r\n");
    }
}

/* 
 * @Description: 初始化系统运行数据
 * @param: 
 * @return: 
*/ 
void sys_rundata_init(void)
{
   
    memset(&sys,0,sizeof(sys));
    get_first_ota_status();
}

/* 
 * @Description: 计算系统运行时间
 * @param: 
 * @return: 
*/ 
void sys_running_cnt(void)
{
    if (++sys.running_time == 0)
    {
        sys.running_time--; // 限制在最大值
    }
}

/* 
 * @Description: 状态灯初始状态
 * @param: 
 * @return: 
*/ 
void LED_display_init(void)
{
    sys.sta.LED_Red = KEEP_ON;
    LED_Red_on();
    sys.sta.LED_Blue = KEEP_OFF;
    LED_Blue_off();
}

/* 
 * @Description: 状态灯指示
 * @param: 
 * @return: 
*/ 
void LED_Display_20ms(void)
{
#define T_1HZ 50
#define T_4HZ 12
#define WIFI_OVERTIME (50 * 60 * 1) // wifi配网超时时间为3分钟
    static uint8_t led_time_base;
    static uint16_t wifi_timeout_cnt;

    if (++led_time_base > T_1HZ)
    {
        led_time_base = 1;
    }
    //----------------------------------------------------------------

    sys.sta.LED_Blue = KEEP_ON; // 默认关灯
    sys.sta.LED_Red = KEEP_OFF; // 默认关灯
    //----------------------------------------------------------------

    if (sys.sta.firmware_dowmload)
    {
        sys.sta.ota_state = OTA_GOING;
    }
    else
    {
        if ((sys.sta.ota_state == OTA_SUCCES || sys.sta.ota_state == OTA_FAILED) && (sys.running_time < TIME_5_MINUTE))
        {
            /* 5分钟内保存升级成功/失败状态 */
        }
        else
        {
            sys.sta.ota_state = NO_OTA;
        }
    }
    //----------------------------------------------------------------
    sys.sta.wifi_state = mcu_get_wifi_work_state();
    if (sys.sta.wifi_state == WIFI_NOT_CONNECTED || sys.sta.wifi_state == WIFI_CONNECTED)
    {
        /* wifi配置成功，但未连上服务器，开始计算超时 */
        if (++wifi_timeout_cnt == 0)
        {
            wifi_timeout_cnt--;
        }
    }
    else
    {
        wifi_timeout_cnt = 0;
    }

    switch (sys.sta.wifi_state)
    {
    case SMART_CONFIG_STATE: // smartconfig配置状态
        sys.sta.LED_Blue = QUICK_FLASH;
        break;
    case AP_STATE: // AP配置状态
        sys.sta.LED_Blue = QUICK_FLASH;
        break;
    case WIFI_NOT_CONNECTED: // WIFI配置成功但未连上路由器

        if (wifi_timeout_cnt > WIFI_OVERTIME)
        {
            sys.sta.LED_Red = SLOW_FLASH; // 配网超时慢闪
        }
        else
        {
            sys.sta.LED_Blue = SLOW_FLASH;
        }
        break;
    case WIFI_CONNECTED: // WIFI配置成功且连上路由器
        if (wifi_timeout_cnt > WIFI_OVERTIME)
        {
            sys.sta.LED_Red = SLOW_FLASH; // 配网超时慢闪
        }
        else
        {
            sys.sta.LED_Blue = SLOW_FLASH;
        }
        break;

    case WIFI_CONN_CLOUD:
        if (play.work.global_setting.indicator_sta == ENABLE_STA)
        {
            sys.sta.LED_Blue = KEEP_ON;
        }
        else
        {
            sys.sta.LED_Blue = KEEP_OFF;
            sys.sta.LED_Red = KEEP_OFF; 
        }
        break;
    case WIFI_LOW_POWER: // WIFI处于低功耗模式
        /*重置后，未进入配网时的状态*/
        break;
    case SMART_AND_AP_STATE: // WIFI smartconfig&AP 模式
        sys.sta.LED_Blue = QUICK_FLASH;
        break;

    default: /*WIFI_SATE_UNKNOW*/
        sys.sta.LED_Red = SLOW_FLASH; // 工作异常 慢闪
        break;
    }


    //----------------------------------------------------------------
    if (sys.sta.errorcode && play.work.global_setting.indicator_sta == ENABLE_STA)
    {
        sys.sta.LED_Red = SLOW_FLASH; // 工作异常 慢闪
    }
    //----------------------------------------------------------------
    
    if (sys.sta.ota_state == OTA_SUCCES)
    {
        sys.sta.LED_Blue = KEEP_ON;
    }

    if (sys.sta.ota_state == OTA_FAILED)
    {
        sys.sta.LED_Blue = KEEP_ON;
        sys.sta.LED_Red = QUICK_FLASH;
    }

    if ( sys.sta.ota_state == OTA_GOING)
    {
        sys.sta.LED_Blue = INTURN_FLASH;
        sys.sta.LED_Red = INTURN_FLASH;
    }
    if (sys.sta.LED_Red == SLOW_FLASH || sys.sta.LED_Red == QUICK_FLASH)
    {
        sys.sta.LED_Blue = KEEP_OFF;
    }

    //----------------------------------------------------------------
    // 闪烁执行
    //----------------------------------------------------------------
    if ((led_time_base % T_4HZ) == 0)
    {
        if (sys.sta.LED_Blue == QUICK_FLASH) // 快闪4Hz
        {
            LED_Blue_flash();
        }
        if (sys.sta.LED_Red == QUICK_FLASH)
        {
            LED_Red_flash();
        }
        if (sys.sta.LED_Blue == INTURN_FLASH) // 交替闪
        {
            LED_FLASH_INTURN();
        }
    }
    if ((led_time_base % T_1HZ) == 0)
    {
        if (sys.sta.LED_Blue == SLOW_FLASH)
        {
            LED_Blue_flash();
        }
        if (sys.sta.LED_Red == SLOW_FLASH)
        {
            LED_Red_flash();
        }
    }
    if (sys.sta.LED_Blue == KEEP_ON)
    {
        LED_Blue_on();
    }
    if (sys.sta.LED_Blue == KEEP_OFF)
    {
        LED_Blue_off();
    }
    if (sys.sta.LED_Red == KEEP_ON)
    {
        LED_Red_on();
    }
    if (sys.sta.LED_Red == KEEP_OFF)
    {
        LED_Red_off();
    }

#undef T_1HZ
#undef T_4HZ
#undef WIFI_OVERTIME
}

// // // void LED_Display_20ms(void)
// // // {
// // //     static uint8_t blink_timecnt;
// // //     uint8_t get_wifi_state;
// // //     uint8_t blink_frequency;
// // //     // get_wifi_state = get_wifi_homekit_state();
// // //     // printf("homekit_STA:%d\n",get_wifi_state);
// // //     get_wifi_state = mcu_get_wifi_work_state();
// // //     // printf("tuya_STA:%d\r\n",get_wifi_state);
// // // /*
// // //  * -          SMART_CONFIG_STATE: smartconfig配置状态
// // //  * -          AP_STATE: AP配置状态
// // //  * -          WIFI_NOT_CONNECTED: WIFI配置成功但未连上路由器
// // //  * -          WIFI_CONNECTED: WIFI配置成功且连上路由器
// // //  * -          WIFI_CONN_CLOUD: WIFI已经连接上云服务器
// // //  * -          WIFI_LOW_POWER: WIFI处于低功耗模式
// // //  * -          SMART_AND_AP_STATE: WIFI smartconfig&AP 模式
// // // */
// // //     switch (get_wifi_state)
// // //     {
// // //     case SMART_CONFIG_STATE: // smartconfig配置状态
// // //         blink_frequency = 2;
// // //         break;
// // //     case AP_STATE: // AP配置状态
// // //         blink_frequency = 2;
// // //         break;
// // //     case WIFI_NOT_CONNECTED: // WIFI配置成功但未连上路由器
// // //         blink_frequency = 15;
// // //         break;
// // //     case WIFI_CONNECTED: // WIFI配置成功且连上路由器
// // //         blink_frequency = 60;
// // //         break;
// // //     case WIFI_CONN_CLOUD: // WIFI已经连接上云服务器
// // //         blink_frequency = 85;
// // //         break;
// // //     case WIFI_LOW_POWER: // WIFI处于低功耗模式
// // //         blink_frequency = 2;
// // //         break;
// // //     case SMART_AND_AP_STATE: // WIFI smartconfig&AP 模式
// // //         blink_frequency = 2;
// // //         break;
// // //     // case WIFI_SATE_UNKNOW:
// // //     //     blink_frequency = 100;
// // //     //     break;
// // //     default:
// // //         blink_frequency = 100;
// // //         break;
// // //     }

// // //     if (blink_frequency > 90)
// // //     {
// // //         LED1_OFF();
// // //         blink_timecnt = 0;
// // //     }
// // //     else
// // //     {
// // //         if (++blink_timecnt > blink_frequency)
// // //         {
// // //             blink_timecnt = 0;
// // //             LED1_REV();
// // //         }
// // //     }

// // //     if (play.work.sw_status == SW_ON)
// // //     {
// // //         LED2_ON();
// // //     }
// // //     else
// // //     {
// // //         LED2_OFF();
// // //     }
// // // }

/* 
 * @Description: 初始化adc的dma
 * @param: 
 * @return: 
*/ 
void adc_dma_init(void)
{
    adc_dma_start();
}

/* 
 * @Description: 开始adc的dma
 * @param: 
 * @return: 
*/ 
void adc_dma_start(void)
{
    // if (xadc.index!=ADC_FINISH_INDEX)
    // {
    //     return;
    // }

    // // // DMA_Stop(DMA_VECTOR_ADC);
    // LED_Red_on();
    // LED_Red_flash();
    xadc.index = ADC_KEY_INDEX;
    ADC_Stop();
    ADC_Start(ADC_CHANNEL_2);
    DMA_Start(DMA_VECTOR_ADC, CTRL_DATA_ADC, DMA_MODE_NORMAL,
              DMA_SIZE_HALF, (sizeof(xadc.keybuf) / sizeof(uint16_t)), (uint16_t *)&ADC->ADCR, &xadc.keybuf);
            // //    ADC->ADM0 |= ADCS;
    // // ADC_Start(ADC_CHANNEL_0);
    // // DMA_Start(DMA_VECTOR_ADC, CTRL_DATA_ADC, DMA_MODE_NORMAL,
    // //           DMA_SIZE_HALF, (sizeof(xadc.micbuf) / sizeof(uint16_t)), (uint16_t *)&ADC->ADCR, &xadc.micbuf);
                //   LED_Blue_off();
    //    ADC->ADM0 |= ADCS;
    // while (DMAVEC->CTRL[CTRL_DATA_ADC].DMACT != 0)
    // {
    //     ;
    // }
    // LED_Blue_on();
}

/* 
 * @Description: adc的dma转换下一通道
 * @param: 
 * @return: 
*/
void adc_dma_next_ISR(void)
{   
    ADC_Stop();
    DMA_Stop(DMA_VECTOR_ADC);
    switch (xadc.index)
    {
    case ADC_KEY_INDEX: // 按键

        xadc.index = ADC_CDS_INDEX; // 开始转换光敏
        ADC_Start(ADC_CHANNEL_36);
        DMA_Start(DMA_VECTOR_ADC, CTRL_DATA_ADC, DMA_MODE_NORMAL,
                  DMA_SIZE_HALF, (sizeof(xadc.cdsbuf) / sizeof(uint16_t)), (uint16_t *)&ADC->ADCR, &xadc.cdsbuf);
                // //    ADC->ADM0 |= ADCS;
        break;
    case ADC_CDS_INDEX: // 光敏
      
        xadc.index = ADC_MIC_INDEX; // 开始转换咪头
        ADC_Start(ADC_CHANNEL_0);
        DMA_Start(DMA_VECTOR_ADC, CTRL_DATA_ADC, DMA_MODE_NORMAL,
                  DMA_SIZE_HALF, (sizeof(xadc.micbuf) / sizeof(uint16_t)), (uint16_t *)&ADC->ADCR, &xadc.micbuf);
                // //    ADC->ADM0 |= ADCS;
        break;
    default: /* ADC_MIC_INDEX 咪头*/

        xadc.index = ADC_FINISH_INDEX;  // 结束标志
        DMA_Stop(DMA_VECTOR_ADC);
        break;
    }
    
}

/*
 * @Description: 随机数初始化
 * @param:
 * @return:
*/
void random_init(void)
{
    random.seed = get_random_seed();
    refresh_random();
}

/*
 * @Description: 获取随机数种子
 * @param:
 * @return:
*/
uint8_t get_random_seed(void)
{
    uint16_t *p;
    uint8_t i;
    uint16_t seed;
    seed = 0;
    p = (uint16_t *)UID;
    for (i = 0; i < 8; i++)
    {
        seed += *p++;
    }
    return (uint8_t)seed;
}


/*
 * @Description: 获取随机数
 * @param:
 * @return:
*/
uint8_t get_random_number(void)
{
    refresh_random();
    return random.num;
}

/*
 * @Description: 刷新随机数
 * @param:
 * @return:
*/
void refresh_random(void)
{
    random.num++;
    random.num += random.seed;
}

/*
 * @Description: 自动切换列表中的灯效
 * @param:
 * @return:
 */
void autoswitch_effects_in_list(void)
{
    uint32_t time;
    if (play.control_mode == PLAYING_MODE) // 正常播放模式
    {
        if (play.work.sw_status == SW_ON)
        {
            if (play.status == RUN)
            {
                if (play.work.playtime_cnt < MAXNUM_32_BIT)
                {
                    play.work.playtime_cnt++;
                }
                if (play.source == SOURCE_LIST) // 列表播放
                {
                    time = play.detail.duration.min_MS * 60;
                    time += play.detail.duration.sec_MS;
                    if (play.work.playtime_cnt > time)
                    {
                        play.work.playtime_cnt = 0;
                        switch_next_ef_in_list();
                    }
                }
            }
        }
    }
}

/* 
 * @Description: 自动调亮度
 * @param: 
 * @return: 
*/ 
uint8_t auto_brightness(void)
{
    uint8_t bright;
    uint16_t val;
    val = xadc.cdsbuf + 1;

    val = (val * 100) >> 12;
    if (val > 95)
    {
        val = 100;
    }
    else if (val < 5)
    {
        val = 5;
    }

    if (play.work.global_setting.autobrightType == Illumination) // 负反馈自动亮度.照明
    {
        bright = 100 - val;
        return bright;
    }
    else // 正反馈自动亮度.环境
    {
        bright = val;
        return bright;
    }
    // PRINT(cds, "%d", xadc.cdsbuf);
}




/*
 * @Description: 设置全局亮度
 * @param:
 * @return:
 */
void set_global_brightness(uint8_t val)
{
    // play.work.global_setting.brightness_set = val;
    // save_global_brightness_set();
    // mcu_update_bright_val();
    // // // mcu_update_brightness_auto();
}
// 数据转BCD码
uint8_t HEX_To_BCD(uint8_t data)
{
    uint8_t HSB, LSB; // 高四位 低四位
    HSB = data / 10;
    LSB = data % 10;
    LSB = LSB + HSB * 16;
    return LSB;
}
// BCD码转换为数据
uint8_t BCD_To_HEX(uint8_t bcd)
{
    uint8_t HSB, LSB; // 高四位 低四位
    HSB = bcd / 16;
    LSB = bcd % 16;
    LSB = LSB + HSB * 10;
    return LSB;
}

/* 
 * @Description: rtc的BCD码转换为HEX
 * @param: 
 * @return: 
*/ 
void RTC_BCD_To_HEX(rtc_counter_value_t *rtc)
{
    rtc->sec = BCD_To_HEX(rtc->sec);
    rtc->min = BCD_To_HEX(rtc->min);
    rtc->hour = BCD_To_HEX(rtc->hour);
    rtc->day = BCD_To_HEX(rtc->day);
    rtc->week = BCD_To_HEX(rtc->week);
    rtc->month = BCD_To_HEX(rtc->month);
    rtc->year = BCD_To_HEX(rtc->year);
}
/* 
 * @Description: HEX转换为rtc的BCD码
 * @param: 
 * @return: 
*/ 
void RTC_HEX_To_BCD(rtc_counter_value_t *rtc)
{
    rtc->sec = HEX_To_BCD(rtc->sec);
    rtc->min = HEX_To_BCD(rtc->min);
    rtc->hour = HEX_To_BCD(rtc->hour);
    rtc->day = HEX_To_BCD(rtc->day);
    rtc->week = HEX_To_BCD(rtc->week);
    rtc->month = HEX_To_BCD(rtc->month);
    rtc->year = HEX_To_BCD(rtc->year);
}

/*
 * @Description: 写本地rtc时钟
 * @param:
 * @return:
 */
void write_local_rtc_time(uint8_t * time)
{
    rtc_counter_value_t rtc;
    if (time[0] == 1)
    {
        // 正确接收到wifi模块返回的本地时钟数据
        printlog("get local time successfully\r");
        rtc.year = time[1];  // Time[1] 为年份，0x00 表示 2000 年
        rtc.month = time[2]; // Time[2] 为月份，从 1 开始到12 结束
        rtc.day = time[3];   // Time[3] 为日期，从 1 开始到31 结束
        rtc.hour = time[4];  // Time[4] 为时钟，从 0 开始到23 结束
        rtc.min = time[5];   // Time[5] 为分钟，从 0 开始到59 结束
        rtc.sec = time[6];   // Time[6] 为秒钟，从 0 开始到59 结束
        if (time[7] == 7)
        {
            rtc.week = 0;
        }
        else
        {
            rtc.week = time[7]; // Time[7] 为星期，从 1 开始到 7 结束，1代表星期一
        }
        RTC_HEX_To_BCD(&rtc);
        RTC_Set_CounterValue(&rtc);
        sys.sta.rtc_checkOK = 1;
        print_local_rtc_time();
    }
    else
    {
        sys.sta.rtc_checkOK = 0;
        // 获取本地时钟数据出错,有可能是当前wifi模块未联网
        // printlog("get local time wrong \r");
    }
     
}

/*
 * @Description: 注册闹钟任务
 * @param:
 * @param:
 * @return:
 */
void start_clock_task(clock_detail_TypeDef *sur, rtc_counter_value_t *rtc)
{
    printlog("start_clock_task\r");
    play.clock.status = CLOCK_ON;                          // 注册闹钟
    play.clock.action_day = rtc->day;                      // 注册日期
    play.clock.action = sur->action;                       // 动作类型
    play.clock.ef_index = sur->ef_index;                   // 灯效索引
    play.clock.ultimatebright = sur->ultimatebright;       // 最终亮度
    play.clock.actiontime.hou_HM = sur->actiontime.hou_HM; // 动作时间
    play.clock.actiontime.min_HM = sur->actiontime.min_HM; // 动作时间
    play.clock.duration.hou_HM = sur->duration.hou_HM;     // 持续时间
    play.clock.duration.min_HM = sur->duration.min_HM;     // 持续时间
    play.clock.repeat.week = sur->repeat.week;             // 星期计划

    if (play.clock.action == TURN_OFF)
    {
        // // play.clock.ultimatebright = bright_table[0];
        play.work.sw_status = SW_OFF;
    }

    if (play.clock.action == TURN_ON)
    {
        play.work.sw_status = SW_ON;
        play.control_mode = PLAYING_MODE;
        play.status = RUN;
        switch_effect(play.clock.ef_index);
    }

}

/* 
 * @Description: 结束闹钟任务
 * @return: 
*/ 
void close_clock_task(void )
{
    // printlog("close_clock_task\r");
    // if (play.clock.action == TURN_ON)
    // {
    //     set_global_brightness(play.clock.ultimatebright);
    // }
    // else // TURN_OFF
    // {
    //     play.work.sw_status = SW_OFF;
    //     mcu_update_switch_led();
    // }
    play.clock.status = NO_CLOCK;
}

/* 
 * @Description: 运行闹钟任务
 * @param: 
 * @return: 
*/ 
void run_clock_task(rtc_counter_value_t* rtc)
{
    time_HM_TypeDef offtime; // 动作关闭时间
    uint32_t actiontime_s;   // 执行时间.秒
    uint32_t endtime_s;      // 结束时间.秒
    uint32_t nowtime_s;      // 当前时间.秒
    uint32_t diftime_s;      // 间隔时间.秒
    uint8_t dif_bright;      // 亮度差
    if (play.clock.status == CLOCK_ON)
    {
        // // offtime.min_HM = play.clock.actiontime.min_HM + play.clock.duration.min_HM;
        // // offtime.hou_HM = play.clock.actiontime.hou_HM + play.clock.duration.min_HM;
        // // // // // // // // if (offtime.min_HM >= 60)
        // // // // // // // // {
        // // // // // // // //     offtime.min_HM = 0;
        // // // // // // // //     offtime.hou_HM++;
        // // // // // // // // }
        // // // // // // // // if (offtime.hou_HM >= 24)
        // // // // // // // // {
        // // // // // // // //     offtime.hou_HM = 0;
        // // // // // // // // }
        // // // // // // // // if (offtime.hou_HM == rtc.hour && offtime.hou_HM == rtc.min) // 小时/分钟
        // // // // // // // // {
        // // // // // // // // }

        actiontime_s = play.clock.actiontime.hou_HM * HOUR_SECOND;
        actiontime_s += play.clock.actiontime.min_HM * MINUTE_SECOND;

        endtime_s = actiontime_s + play.clock.duration.hou_HM * HOUR_SECOND;
        endtime_s += play.clock.duration.min_HM * MINUTE_SECOND;

        nowtime_s = rtc->hour * HOUR_SECOND;    
        nowtime_s += rtc->min * MINUTE_SECOND;

        if (nowtime_s < actiontime_s)
        {
            nowtime_s += DAY_SECOND;
        }

        if (nowtime_s >= endtime_s)
        {
            close_clock_task();
        }
        else
        {
            diftime_s = endtime_s - nowtime_s;
            // // // if (play.efdetail.EffectType == RHYTHM_TYPE) // 律动模式
            // // // {
            // // //     // // // play.work.brightness.now = mic.bri_now;
            // // // }
            // // // else
            // // // {

            // // // }
            // // // if (play.clock.ultimatebright > play.work.brightness.now)
            // // // {
            // // //     if ()
            // // //     {
                    
            // // //     }
                
            // // //     dif_bright = play.clock.ultimatebright - play.work.brightness.now;
            // // // }
            // // // else
            // // // {
            // // //     dif_bright = play.work.brightness.now - play.clock.ultimatebright;
            // // // }
            dif_bright = get_abs_diff(play.efdetail.Brightness1, play.efdetail.Brightness2);
            dif_bright = get_abs_diff(play.work.brightness.now, dif_bright);
            play.clock.bright = dif_bright / diftime_s;
            printlog("clock: now:%d,tar:%d\r", play.work.brightness.now, play.clock.bright);
        }
    }
}

/* 
 * @Description: 闹钟服务
 * @param: 
 * @return: 
*/ 
void clock_server(void)
{
    static uint8_t minute_last; // 上次时间 分钟
    rtc_counter_value_t rtc;
    clock_list_TypeDef clock_list;
    
    uint8_t i;
    RTC_Get_CounterValue(&rtc);
    RTC_BCD_To_HEX(&rtc);
    if (sys.sta.rtc_checkOK == 0 || rtc.year == 0)
    {
        mcu_get_system_time(); // 申请网络时间进行本地rtc校准
    }
    else
    {
        // print_local_rtc_time(); // 打印时间
        if (rtc.min != minute_last)
        {
            get_all_schedule(&clock_list);
            if (clock_list.num) // 有闹钟任务
            {
                for (i = 0; i < clock_list.num; i++)
                {
                    if (clock_list.list[i].en_sta == FUN_ENABLE) // 当前闹钟启用
                    {
                        if (clock_list.list[i].repeat.week & (1 << rtc.week)) // 在周重复日期内
                        {
                            if (clock_list.list[i].actiontime.hou_HM == rtc.hour && clock_list.list[i].actiontime.min_HM == rtc.min) // 小时/分钟
                            {
                                start_clock_task(&clock_list.list[i], &rtc);
                                close_clock_task();
                            }
                        }
											}
                 }
            }
        }
        // run_clock_task(&rtc);
    }
    minute_last = rtc.min;
}


/* 
 * @Description: 求绝对差值
 * @param: 
 * @param: 
 * @return: 
*/
uint32_t get_abs_diff(uint32_t val1, uint32_t val2)
{
    if (val1 > val2)
    {
        return val1 - val2;
    }
    else
    {
        return val2 - val1;
    }
}

/* 
 * @Description: wifi串口发送fifo初始化
 * @param: 
 * @return: 
*/ 
void wifi_fifo_init(void)
{
    uart1_fifo.send_sta = SEND_END;
    uart1_fifo.read = 0;
    uart1_fifo.write = 0;
}

/* 
 * @Description: wifi串口发送fifo压进一字节
 * @param: 
 * @return: 
*/ 
void wifi_fifo_push(uint8_t data)
{
    uart1_fifo.buffer[uart1_fifo.write] = data;
    if (++uart1_fifo.write >= sizeof(uart1_fifo.buffer))
    {
        uart1_fifo.write = 0;
    }
}

/*
 * @Description: wifi串口发送(中断触发)
 * @param:
 * @return:
 */
uint8_t wifi_fifo_send_ISR(void)
{
    if (uart1_fifo.send_sta == SEND_END)
    {   
        if (uart1_fifo.read != uart1_fifo.write)
        {
            uart1_send_start(uart1_fifo.buffer[uart1_fifo.read]);
            uart1_fifo.send_sta = SEND_ING;
        }
    }
}

/* 
 * @Description: 串口1执行发送1字节
 * @param: 
 * @return: 
*/
void uart1_send_start(uint8_t data)
{
    SCI0->TXD1 = data;
}

/*
 * @Description: 串口1完成发送
 * @param:
 * @return:
 */
void uart1_send_end(void)
{
    if (uart1_fifo.send_sta == SEND_ING)
    {
        uart1_fifo.send_sta = SEND_END;
        if (++uart1_fifo.read >= sizeof(uart1_fifo.buffer))
        {
            uart1_fifo.read = 0;
        }
    }
}


/* 
 * @Description: 按键功能
 * @param: 
 * @return: 
*/ 
void KeyS_Click(void)
{
    static unsigned char temp;

    unsigned char *str;
    uint8_t Level_Num_Temp;

    uint16_t i, j;
    uint8_t *p;
    // uint8_t test_buf[] = {0xA5, 0x0F, 0x21, 0xE0, 0x01, 0x01, 0xE1, 0x02, 0x02, 0xE2, 0x03, 0x03, 0xE3, 0x04, 0x04, 0x6F};

    if (KEY1_Click)
    {
        if (play.work.sw_status == SW_ON)
        {
            play.work.sw_status = SW_OFF;
        }
        else
        {
            play.work.sw_status = SW_ON;
        }
        mcu_update_switch_led();
        debug_K1();
    }
    if (KEY2_Click)
    {

        // test_change_color();
        // switch_last_ef_in_list();

        switch_next_free_effect(LAST);
        debug_K2();
    }
    if (KEY3_Click)
    {
        debug_K3();
        // switch_next_ef_in_list();
        // debug_play_last_effect();

        // test_click_brightness(1);

        switch_next_free_effect(NEXT);
    }
    if (KEY4_Click)
    {
        debug_K4();
        modify_brightness_level();
        // debug_play_next_effect();
        // test_click_brightness(0);

       
        // // set_global_brightness(play.work.global_setting.brightness_set);
        // // mcu_update_brightness_auto();
    }
    if (KEY5_Click)
    {
        debug_K5();
        change_rhythm_mode();
    }
    /*************************************/

    if (KEY1_Long)
    {
    }
    if (KEY2_Long)
    {
    }
    if (KEY3_Long)
    {
        // test_long_brightness(1);
    }
    if (KEY4_Long)
    {
        // test_long_brightness(0);
    }
    if (KEY5_Long)
    {
    }
    /**************************/
    if (KEY1_LongOnce)
    {
        debug_K1_LONG();
        printlog("reset wifi\r\n");
        // delay_500ms();
        // delay_500ms();
        mcu_reset_wifi();
        factoryreset_norflash();
        SYS_Init();
        // mcu_restart();
    }
    if (KEY2_LongOnce)
    {
    }
    if (KEY3_LongOnce)
    {
    }
    if (KEY4_LongOnce)
    {
    }
    if (KEY5_LongOnce)
    {
    }
    if (KEY4_Long)
    {
        modify_brightness_step(KEY4_LongRelease);
    }

    KEY1_AllClick_Reset;
    KEY2_AllClick_Reset;
    KEY3_AllClick_Reset;
    KEY4_AllClick_Reset;
    KEY5_AllClick_Reset;

    KEY1_AllLong_Reset;
    KEY2_AllLong_Reset;
    KEY3_AllLong_Reset;
    KEY4_AllLong_Reset;
    KEY5_AllLong_Reset;


}


/* 
 * @Description: 灯光控制
 * @param: 
 * @return: 
*/ 
void Lignt_Control(void)
{

    if (play.work.sw_status == SW_ON)
    {
        if (play.efdetail.EffectType == RHYTHM_TYPE) // 律动模式
        {
            play.work.brightness.now = mic.bri_now;
        }
        else
        {
            if (play.work.global_setting.autobright_ensta == ENABLE_STA)
            {
                play.work.brightness.tar = auto_brightness(); // 自动亮度
            }
            else
            {
                play.work.brightness.tar = play.work.brightness.set;
            }
            if (Twinkle.On_Flag == 0)
            {
                Gradual_Change(&play.work.brightness.now, &play.work.brightness.tar, 3);
            }
            else    
            {
                // 闪烁程序控制亮度
            }
        }
    }
    else
    {
        play.work.brightness.tar = 0;
        Gradual_Change(&play.work.brightness.now, &play.work.brightness.tar, 3);
    }
    twinkle_remind(&play.work.brightness.now, &play.work.brightness.tar);   // 闪烁
    // // printlog("now:%3d,tar:%3d\r",play.work.brightness.now,play.work.brightness.tar);
}

/* 
 * @Description: 串口应用初始化
 * @param: 
 * @return: 
*/ 
void uart_app_init(void)
{
    /*
	UART0_Init(SystemCoreClock, 76800);	// 实际为76800
	UART1_Init(SystemCoreClock, 76800); // 实际为9600
	_0050_SCI_CK01_fCLK_5

	UART0_Init(SystemCoreClock, 115200); // 实际为115200
	UART1_Init(SystemCoreClock, 76800); // 实际为9600
	_0050_SCI_CK01_fCLK_5
	其他波特率需重新设置参数
	*/
	// // // UART0_Init(SystemCoreClock, 76800); // 实际为76800
	UART0_Init(SystemCoreClock, 115200); // 实际为115200
	UART1_Init(SystemCoreClock, 76800); // 实际为9600
	UART1_Receive(&Uart1_rx_data, 1);
	printf("\nHello,I am Matser\n");
    wifi_fifo_init();
	INTC_EnableIRQ(SR1_IRQn);       /* enable INTSR1 interrupt */
    INTC_EnableIRQ(ST1_IRQn);       /* enable INTSR1 interrupt */

    DMA_Start(DMA_VECTOR_SR0, CTRL_DATA_SR0, DMA_MODE_REPEAT, DMA_SIZE_BYTE, sizeof(parse.fifo_buffer),  (void*)&SCI0->RXD0, (void*)&parse.fifo_buffer);
	DMA_Enable(DMA_VECTOR_SR0);
	NVIC_ClearPendingIRQ(SR0_IRQn); /* clear INTSR1 interrupt flag */
	INTC_EnableIRQ(SR0_IRQn);       /* enable INTSR1 interrupt */
}

/* 
 * @Description: 系统时钟初始化
 * @param: 
 * @return: 
*/ 
void sys_tick_init(void)
{

    User_TM40_IntervalTimer(TM4_CHANNEL_0, 500);
    INTC_EnableIRQ(TM00_IRQn);
}

/*
 * @Description: 串口解析
 * @param: 无
 * @return: 无
*/
void uart_parse(void)
{
    uint16_t pWrite;
    pWrite = sizeof(parse.fifo_buffer) - DMAVEC->CTRL[CTRL_DATA_SR0].DMACT;
    fifo_parse(&parse.fifo_buffer, sizeof(parse.fifo_buffer), &parse.read, &pWrite, &parse.rx_processbuf); // 不定长协议解析
}

/* 
 * @Description: 定时器4中断服务
 * @param: 
 * @return: 
*/ 
void Timer40_Interrupt(void)
{
    wifi_fifo_send_ISR();
    SYS_Clock_Tick();   // 4ms中断一次  
}

/* 
 * @Description: 
 * @param: 
 * @return: 
*/ 
void change_rhythm_mode(void)
{
    if (play.work.rhythm_sta == RHYTHM_ON)
    {
        play.work.rhythm_sta = RHYTHM_OFF;
        printlog("RHYTHM_OFF\r");
        if (play.efdetail.EffectType == RHYTHM_TYPE)
        {
            switch_next_free_effect(NEXT);
        }
    }
    else
    {
        play.work.rhythm_sta = RHYTHM_ON;
        printlog("RHYTHM_ON\r");
        if (play.efdetail.EffectType != RHYTHM_TYPE)
        {
            switch_next_free_effect(NEXT);
        }
    }
}

/*
 * @Description: 搜寻数据在列表中的指针
 * @param:
 * @param:
 * @param:
 * @return:
 */
uint8_t search_dataindex_in_list(uint8_t data, uint8_t *list, uint8_t listsize)
{
    uint8_t i;
    for (i = 0; i < listsize; i++)
    {
        if (list[i] == data)
        {
            return i;
        }
    }
    return 0xFF; // 没在列表发现该数
}

/* 
 * @Description: 切换下一个自由灯效
 * @param: 
 * @return: 
*/ 
void switch_next_free_effect(NL_enum nl)
{
    ef_ranklist_TypeDef allef;
    Efdetail_TypeDef efdetail;
    uint8_t num;
    uint8_t i, j;
    get_allef_ranklist(&allef);
    if (nl == LAST)
    {
        invert_list(&allef.list, allef.num); // 倒序
    }
    i = search_dataindex_in_list(play.detail.efindex, &allef.list, allef.num); // 找到当前灯效在全部灯效中的位置
    if (i == 0xFF)
    {
        i = 0;  // 当前灯效不在列表中，则从头开始播放
    }
    move_data_to_first_in_list(allef.list[i], &allef.list, allef.num);      // 挪至第一位

    for (i = 1; i < allef.num; i++)
    {
        get_effect_detail(&efdetail, allef.list[i]);
        if (play.work.rhythm_sta == RHYTHM_ON) // 切换律动灯效
        {
            if (efdetail.EffectType == RHYTHM_TYPE)
            {
                modify_playsource(SOURCE_FREE);
                play_new_effect(allef.list[i]);
                return;
            }
        }
        else // 切换非律动灯效
        {
            if (efdetail.EffectType != RHYTHM_TYPE)
            {
                modify_playsource(SOURCE_FREE);
                play_new_effect(allef.list[i]);
                return;
            }
        }
    }
}

/* 
 * @Description: wifi服务函数
 * @param: 
 * @return: 
*/ 
void wifi_service(void)
{
    // if (uart1_fifo.send_sta == SEND_END)
    // {
        wifi_uart_service();
    // }
}

/* 
 * @Description: 自动保存灯效亮度
 * @param: 
 * @return: 
*/ 
void autosave_effect_bright(uint8_t reset)
{
#define BRIGHTNESS_SAVE_TIME 178                 // 亮度自动保存时间 178*28ms 约5秒
    static uint8_t bright_last = 0;              // 上次亮度值
    static uint8_t bright_steady_time = 0;       // 稳定时间
    if (play.efdetail.EffectType == RHYTHM_TYPE) // 律动模式
    {
        bright_steady_time = 0;
    }
    if (reset)
    {
        bright_steady_time = 0;
    }
    if (bright_last != play.work.brightness.set)
    {
        bright_steady_time = 0;
    }
    else
    {
        if (bright_steady_time < 0xFF)
        {
            bright_steady_time++;
        }
    }
    if (bright_steady_time == BRIGHTNESS_SAVE_TIME) // 亮度设置值稳定后
    {
        if (play.work.brightness.set != play.efdetail.Brightness1)  // 亮度有修改时
        {
            modify_effect_brightness(play.detail.efindex, play.work.brightness.set, 1); // 将亮度保存进当前灯效
        }
    }
    bright_last = play.work.brightness.set;
}

/* 
 * @Description: 修改亮度级别
 * @param: 
 * @return: 
*/
void modify_brightness_level(void)
{
    if (play.work.sw_status == SW_ON)
    {
        Light_Level_Change(&play.work.brightness.set, &play.work.brightness.dir, bright_table, sizeof(bright_table));
        autosave_effect_bright(1);
    }
}

/*
 * @Description: 长按调亮度
 * @param: 长按释放标志
 * @return:
 */
void modify_brightness_step(uint8_t release)
{

    Value_Step_Change(&play.work.brightness.set, &play.work.brightness.dir, bright_table[sizeof(bright_table) - 1], bright_table[0], 1);
    if (play.work.brightness.set == bright_table[sizeof(bright_table) - 1])
    {
        // Twinkle_SET(1, 15, 15, 30);
        if (release)
        {
            play.work.brightness.dir = 0;
            // Twinkle_SET(0, 15, 15, 30); // 结束闪烁
        }
    }
    else if (play.work.brightness.set == bright_table[0])
    {
        // Twinkle_SET(1, 15, 15, 30);
        if (release)
        {
            play.work.brightness.dir = 1;
            // Twinkle_SET(0, 15, 15, 30); // 结束闪烁
        }
    }
    autosave_effect_bright(1);
}

/* 
 * @Description: 闪烁提醒
 * @param: 输出当前亮度
 * @param: 输入目标亮度
 * @return: 
*/ 
void twinkle_remind(uint8_t* now, uint8_t* tar)
{
    static uint8_t BaseTimeCNT;
    uint8_t Period;
    uint8_t Brightness_Temp;
    Period = Twinkle.Bright_Time + Twinkle.Dark_Time; // 闪烁周期时间
    if (Twinkle.Target > 0)
    {
        Twinkle.On_Flag = 1; // 闪烁目标次数不为0时，自动打开闪烁标志位，开启闪烁
    }
    if (Twinkle.On_Flag)
    {
        BaseTimeCNT++;
        if (BaseTimeCNT <= Twinkle.Dark_Time) // 暗阶段
        {
            if (*tar <= (100 - Twinkle.Bias)) // Bias不可大于127
            {
                *now = *tar + Twinkle.Bias;
            }
            else
            {
                *now = *tar - Twinkle.Bias;
            }
        }
        else // 亮阶段
        {
            *now = *tar;
            if (BaseTimeCNT >= Period) // 完整闪烁周期完成
            {
                Twinkle.Count++;
                if (Twinkle.Count >= Twinkle.Target) // 完成目标闪烁次数
                {
                    Twinkle.On_Flag = 0;
                    Twinkle.Count = 0;
                    Twinkle.Target = 0;
                    BaseTimeCNT = 0;
                }
                BaseTimeCNT = 0;
            }
        }
    }
}


/* 
 * @Description: 间隔定时器中断服务函数
 * @param: 
 * @return: 
*/ 
void it_callback_Handle(void)
{
    

    // LED_Red_flash();
}
