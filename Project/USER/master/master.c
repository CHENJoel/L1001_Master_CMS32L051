/*
 * @Author: DESKTOP-AKTRQKB\MY sandote@163.com
 * @Date: 2023-06-07 10:04:26
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * @LastEditTime: 2023-10-31 15:21:48
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\master\master.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "master.h"

sys_TypeDef sys;
adcdma_task_TypeDef xadc;


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
    FLASHSPI_PageRead((uint8_t *)str, (((uint32_t) & (NORFLASH->ota.data.package)) + APP_INF_ADDR - APP_BASIC_ADDR), len);
}

/* 
 * @Description: 获取ota升级状态
 * @param: 
 * @return: 
*/
void get_first_ota_status(void)
{
    uint8_t version[16];
    get_norflash_firmware_version(&version, sizeof(firmware_inf.version));
    if (version[0] < '0' || version[0] > '9') // 固件信息首位应该为数字字符
    {
        sys.sta.ota_state = NO_OTA; // 最近无升级任务（norflash中无固件信息）
    }
    else
    {
        if (my_strcmp(&version, &firmware_inf.version)) // 版本不一致
        {
            erase_firmware_block();
            clear_firmware_update_flag();
            sys.sta.ota_state = OTA_FAILED; // 升级失败
            printlog("\rFirmware update failed\r\n");
        }
        else // 版本一致
        {
            erase_firmware_block();
            clear_firmware_update_flag();
            sys.sta.ota_state = OTA_SUCCES; // 升级成功
            printlog("\rFirmware update successful\r\n");
        }
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

    sys.sta.LED_Blue = KEEP_OFF;    // 默认关灯
    sys.sta.LED_Red = KEEP_OFF;     // 默认关灯
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
    if (wifi_timeout_cnt > WIFI_OVERTIME)
    {
        sys.sta.LED_Red = SLOW_FLASH; // 配网超时慢闪
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
        sys.sta.LED_Blue = SLOW_FLASH;
        break;
    case WIFI_CONNECTED: // WIFI配置成功且连上路由器
        sys.sta.LED_Blue = SLOW_FLASH;
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


void adc_dma_init(void)
{
    xadc.pindex = 0;
    xadc.mic_finish = 0;
}

/* 
 * @Description:自动切换adc通道进行dma
 * @param: 
 * @return: 
*/
void adc_dma_AutoTrigger(void)
{
    // DMA_Stop(DMA_VECTOR_ADC);

    // ADC_Start(ADC_CHANNEL_2);
    // DMA_Start(DMA_VECTOR_ADC, CTRL_DATA_ADC, DMA_MODE_NORMAL,
    //           DMA_SIZE_HALF, 1, (uint16_t *)&ADC->ADCR, &KEY_Val);
    // while (DMAVEC->CTRL[CTRL_DATA_ADC].DMACT != 0)
    // {
    //     ;
    // }

    // ADC_Start(ADC_CHANNEL_0);
    // DMA_Start(DMA_VECTOR_ADC, CTRL_DATA_ADC, DMA_MODE_NORMAL,
    //           DMA_SIZE_HALF, MIC_BUF_SIZE, (uint16_t *)&ADC->ADCR, &mic.buffer);
}
