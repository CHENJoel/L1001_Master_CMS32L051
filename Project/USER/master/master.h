/*
 * @Author: DESKTOP-AKTRQKB\MY sandote@163.com
 * @Date: 2023-06-07 10:05:07
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * @LastEditTime: 2023-11-30 14:53:30
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\master\master.h
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _MASTER_H
#define _MASTER_H
#include "Function_Init.H"


typedef struct
{
    unsigned char Target;	   //Ŀ��.��˸����
    unsigned char Count;	   //�����.��˸����
    unsigned char Bright_Time; //��.ʱ��
    unsigned char Dark_Time;   //��.ʱ��
    unsigned char On_Flag;	   //��˸��־
    unsigned char Bias;		   //��˸����
} TwinkleTypeDef;
extern TwinkleTypeDef Twinkle;

#define Twinkle_SET(TimesSET, BrightTime, DarkTime,TwinkleBias) \
    Twinkle.Target = TimesSET;                      \
    Twinkle.Bright_Time = BrightTime;               \
    Twinkle.Dark_Time = DarkTime;\
    Twinkle.Bias = TwinkleBias


typedef enum
{
    SEND_END, // �������
    SEND_ING, // ������
} SENDstatus_enum;

typedef struct 
{
    SENDstatus_enum send_sta;   // ���ͽ���
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
    KEEP_ON,       // ����
    SLOW_FLASH,    // ����1Hz
    QUICK_FLASH,   // ����4Hz
    KEEP_OFF,      // Ϩ��
    INTURN_FLASH,  // ������
} LED_STATUS_ENUM; // ָʾ��״̬

typedef enum
{
    NO_OTA,        // ����������
    OTA_GOING,     // ������
    OTA_FAILED,    // ����ʧ��
    OTA_SUCCES,    // �����ɹ�
} OTA_STATUS_ENUM; // ota״̬

typedef enum
{
    NO_ERROR,      // �޴���
} SYS_ERROR_ENUM; // ota״̬

typedef enum
{
    NEXT,  // ��һ��
    LAST,  // ��һ��
} NL_enum; //

typedef struct
{
    uint8_t firmware_dowmload; // �̼�����
    OTA_STATUS_ENUM ota_state; //
    uint8_t wifi_state;
    uint8_t rtc_checkOK; // RCTУ׼���
    SYS_ERROR_ENUM errorcode;
    LED_STATUS_ENUM LED_Red;
    LED_STATUS_ENUM LED_Blue;
} sys_sta_TypeDef;

typedef struct
{
    sys_sta_TypeDef sta;
    uint32_t running_time; // �ϵ�����ʱ��
}sys_TypeDef;
extern sys_TypeDef sys;

//----------------------------
enum
{
    ADC_KEY_INDEX,    // ����
    ADC_CDS_INDEX,    // ����
    ADC_MIC_INDEX,    // ��ͷ
    ADC_FINISH_INDEX, // ��������
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
    uint8_t num;    // �����
    uint8_t seed;   // ����
} random_Typdef;
extern random_Typdef random;

void wifi_module_init(void);    // wifiģ���ʼ��
void mcu_restart(void); // ��Ƭ������
//
void sys_rundata_init(void);    // ��ʼ��ϵͳ��������
//
uint8_t get_norflash_firmware_version(uint8_t* str,uint8_t len);// ��ȡ��norflash�еĹ̼��汾��
void get_first_ota_status(void);                                // ��ȡota����״̬
//
void sys_running_cnt(void); // ����ϵͳ����ʱ��
//
void LED_display_init(void); // ״̬�Ƴ�ʼ״̬
void LED_Display_20ms(void); // ״̬��ָʾ
//
void adc_dma_init(void);
void adc_dma_start(void);    // ��ʼadc��dma
void adc_dma_next_ISR(void); // adc��dmaת����һͨ��
//
void random_init(void);          // �������ʼ��
uint8_t get_random_seed(void);   // ��ȡ���������
uint8_t get_random_number(void); // ��ȡ�����
void refresh_random(void);       // ˢ�������
//
void autoswitch_effects_in_list(void); // �Զ��л��б��еĵ�Ч
//
void set_firmware_downloading_flag(void);     // ���ù̼������б�־
void set_firmware_download_finish_flag(void); // ���ù̼�������ɱ�־
void clear_firmware_download_flag(void);      // ����̼����ر�־

//

uint8_t auto_brightness(void); // �Զ�������
//
void set_global_brightness(uint8_t val); // ����ȫ������
//
uint8_t HEX_To_BCD(uint8_t data); // ����תBCD��
uint8_t BCD_To_HEX(uint8_t bcd);  // BCD��ת��Ϊ����
void write_local_rtc_time(uint8_t *time); // д����rtcʱ��
//
void start_clock_task(clock_detail_TypeDef *sur, rtc_counter_value_t *rtc); // ע����������
void close_clock_task(void);                                                // ������������
void run_clock_task(rtc_counter_value_t *rtc);                              // ������������
//
uint32_t get_abs_diff(uint32_t val1, uint32_t val2); // ����Բ�ֵ

void wifi_fifo_init(void);           // wifi���ڷ���fifo��ʼ��
void wifi_fifo_push(uint8_t data);   // wifi���ڷ���fifoѹ��һ�ֽ�
uint8_t wifi_fifo_send_ISR(void);    // wifi���ڷ���(�жϴ���)
void uart1_send_start(uint8_t data); // ����1ִ�з���1�ֽ�
void uart1_send_end(void);           // ����1��ɷ���
//
void KeyS_Click(void); // ��������
//
void Lignt_Control(void); // �ƹ����
//
void uart_app_init(void); // ����Ӧ�ó�ʼ��
//
void sys_tick_init(void); // ϵͳʱ�ӳ�ʼ��
//
void uart_parse(void); // ���ڽ���
//
void Timer40_Interrupt(void); // ��ʱ��4�жϷ���
// 
uint8_t search_dataindex_in_list(uint8_t data, uint8_t *list, uint8_t listsize);// ��Ѱ�������б��е�ָ��
//
void switch_next_free_effect(NL_enum nl); // �л���һ�����ɵ�Ч

//
void wifi_service(void); // wifi������
//
void autosave_effect_bright(uint8_t reset); // �Զ������Ч����
//
void modify_brightness_level(void);           // �޸����ȼ���
void modify_brightness_step(uint8_t release); // ����������
//
void twinkle_remind(uint8_t *now, uint8_t *tar); // ��˸����

#endif
