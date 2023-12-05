/*
 * @Author: DESKTOP-AKTRQKB\MY sandote@163.com
 * @Date: 2023-06-07 10:05:07
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * @LastEditTime: 2023-11-30 14:53:30
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\master\master.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _MASTER_H
#define _MASTER_H
#include "Function_Init.H"


typedef struct
{
    unsigned char Target;	   //目标.闪烁次数
    unsigned char Count;	   //已完成.闪烁次数
    unsigned char Bright_Time; //亮.时长
    unsigned char Dark_Time;   //暗.时长
    unsigned char On_Flag;	   //闪烁标志
    unsigned char Bias;		   //闪烁幅度
} TwinkleTypeDef;
extern TwinkleTypeDef Twinkle;

#define Twinkle_SET(TimesSET, BrightTime, DarkTime,TwinkleBias) \
    Twinkle.Target = TimesSET;                      \
    Twinkle.Bright_Time = BrightTime;               \
    Twinkle.Dark_Time = DarkTime;\
    Twinkle.Bias = TwinkleBias


typedef enum
{
    SEND_END, // 发送完成
    SEND_ING, // 发送中
} SENDstatus_enum;

typedef struct 
{
    SENDstatus_enum send_sta;   // 发送结束
    uint16_t read;
    uint16_t write;
    uint8_t buffer[300];
}fifo_t;

extern fifo_t uart1_fifo;



typedef union
{
    unsigned char byte;
    struct
    {
        unsigned bit0 : 1;
        unsigned bit1 : 1;
        unsigned bit2 : 1;
        unsigned bit3 : 1;
        unsigned bit4 : 1;
        unsigned bit5 : 1;
        unsigned bit6 : 1;
        unsigned bit7 : 1;
    } bits;
}FlagTypeDef;

extern FlagTypeDef flag;



#define RTC_CheckFinish flag.bits.bit0

#define TIME_5_MINUTE 300
#define DAY_SECOND (24 * 60 * 60)
#define HOUR_SECOND (60 * 60)
#define MINUTE_SECOND 60

typedef enum
{
    KEEP_ON,       // 常亮
    SLOW_FLASH,    // 慢闪1Hz
    QUICK_FLASH,   // 快闪4Hz
    KEEP_OFF,      // 熄灭
    INTURN_FLASH,  // 交替闪
} LED_STATUS_ENUM; // 指示灯状态

typedef enum
{
    NO_OTA,        // 无升级任务
    OTA_GOING,     // 升级中
    OTA_FAILED,    // 升级失败
    OTA_SUCCES,    // 升级成功
} OTA_STATUS_ENUM; // ota状态

typedef enum
{
    NO_ERROR,      // 无错误
} SYS_ERROR_ENUM; // ota状态

typedef enum
{
    NEXT,  // 下一个
    LAST,  // 上一个
} NL_enum; //

typedef struct
{
    uint8_t firmware_dowmload; // 固件下载
    OTA_STATUS_ENUM ota_state; //
    uint8_t wifi_state;
    uint8_t rtc_checkOK; // RCT校准完成
    SYS_ERROR_ENUM errorcode;
    LED_STATUS_ENUM LED_Red;
    LED_STATUS_ENUM LED_Blue;
} sys_sta_TypeDef;

typedef struct
{
    sys_sta_TypeDef sta;
    uint32_t running_time; // 上电运行时间
}sys_TypeDef;
extern sys_TypeDef sys;

//----------------------------
enum
{
    ADC_KEY_INDEX,    // 按键
    ADC_CDS_INDEX,    // 光敏
    ADC_MIC_INDEX,    // 咪头
    ADC_FINISH_INDEX, // 结束索引
};

typedef enum
{
    semaphore_take,
    semaphore_give,
}semaphore_enum;

typedef struct
{
    uint8_t index;
    semaphore_enum mic_semop;
    uint16_t micbuf[65];
    uint16_t keybuf;
    uint16_t cdsbuf;
}adcdma_task_TypeDef;
extern adcdma_task_TypeDef xadc;

/*******************************************/
typedef struct
{
    uint8_t num;    // 随机数
    uint8_t seed;   // 种子
} random_Typdef;
extern random_Typdef random;

void wifi_module_init(void);    // wifi模组初始化
void mcu_restart(void); // 单片机重启
//
void sys_rundata_init(void);    // 初始化系统运行数据
//
uint8_t get_norflash_firmware_version(uint8_t* str,uint8_t len);// 获取在norflash中的固件版本号
void get_first_ota_status(void);                                // 获取ota升级状态
//
void sys_running_cnt(void); // 计算系统运行时间
//
void LED_display_init(void); // 状态灯初始状态
void LED_Display_20ms(void); // 状态灯指示
//
void adc_dma_init(void);
void adc_dma_start(void);    // 开始adc的dma
void adc_dma_next_ISR(void); // adc的dma转换下一通道
//
void random_init(void);          // 随机数初始化
uint8_t get_random_seed(void);   // 获取随机数种子
uint8_t get_random_number(void); // 获取随机数
void refresh_random(void);       // 刷新随机数
//
void autoswitch_effects_in_list(void); // 自动切换列表中的灯效
//
void set_firmware_downloading_flag(void);     // 设置固件下载中标志
void set_firmware_download_finish_flag(void); // 设置固件下载完成标志
void clear_firmware_download_flag(void);      // 清除固件下载标志

//

uint8_t auto_brightness(void); // 自动调亮度
//
void set_global_brightness(uint8_t val); // 设置全局亮度
//
uint8_t HEX_To_BCD(uint8_t data); // 数据转BCD码
uint8_t BCD_To_HEX(uint8_t bcd);  // BCD码转换为数据
void write_local_rtc_time(uint8_t *time); // 写本地rtc时钟
//
void start_clock_task(clock_detail_TypeDef *sur, rtc_counter_value_t *rtc); // 注册闹钟任务
void close_clock_task(void);                                                // 结束闹钟任务
void run_clock_task(rtc_counter_value_t *rtc);                              // 运行闹钟任务
//
uint32_t get_abs_diff(uint32_t val1, uint32_t val2); // 求绝对差值

void wifi_fifo_init(void);           // wifi串口发送fifo初始化
void wifi_fifo_push(uint8_t data);   // wifi串口发送fifo压进一字节
uint8_t wifi_fifo_send_ISR(void);    // wifi串口发送(中断触发)
void uart1_send_start(uint8_t data); // 串口1执行发送1字节
void uart1_send_end(void);           // 串口1完成发送
//
void KeyS_Click(void); // 按键功能
//
void Lignt_Control(void); // 灯光控制
//
void uart_app_init(void); // 串口应用初始化
//
void sys_tick_init(void); // 系统时钟初始化
//
void uart_parse(void); // 串口解析
//
void Timer40_Interrupt(void); // 定时器4中断服务
// 
uint8_t search_dataindex_in_list(uint8_t data, uint8_t *list, uint8_t listsize);// 搜寻数据在列表中的指针
//
void switch_next_free_effect(NL_enum nl); // 切换下一个自由灯效

//
void wifi_service(void); // wifi服务函数
//
void autosave_effect_bright(uint8_t reset); // 自动保存灯效亮度
//
void modify_brightness_level(void);           // 修改亮度级别
void modify_brightness_step(uint8_t release); // 长按调亮度
//
void twinkle_remind(uint8_t *now, uint8_t *tar); // 闪烁提醒

#endif
