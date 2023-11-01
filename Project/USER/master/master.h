/*
 * @Author: DESKTOP-AKTRQKB\MY sandote@163.com
 * @Date: 2023-06-07 10:05:07
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * @LastEditTime: 2023-10-31 15:03:35
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\master\master.h
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _MASTER_H
#define _MASTER_H
#include "Function_Init.H"

#define TIME_5_MINUTE 300

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

typedef struct
{
    uint8_t firmware_dowmload; // �̼�����
    uint8_t ota_state;         //
    uint8_t wifi_state;

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

typedef struct
{
    uint8_t pindex;
    uint8_t mic_finish;
    uint16_t micbuf[200];
    uint16_t keybuf[1];
    uint16_t lasbuf[1];
}adcdma_task_TypeDef;

/*******************************************/

void wifi_module_init(void);    // wifiģ���ʼ��
void mcu_restart(void); // ��Ƭ������
//
void sys_rundata_init(void);    // ��ʼ��ϵͳ��������
//
uint8_t get_norflash_firmware_version(uint8_t* str,uint8_t len);// ��ȡ��norflash�еĹ̼��汾��
void get_first_ota_status(void);   // ��ȡota����״̬
//
void sys_running_cnt(void); // ����ϵͳ����ʱ��
//
void LED_display_init(void);    // ״̬�Ƴ�ʼ״̬
void LED_Display_20ms(void);    // ״̬��ָʾ
#endif
