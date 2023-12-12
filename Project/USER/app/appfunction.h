/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-05-19 11:16:26
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * .chen sandote@163.om
 * @LastEditTime: 2023-12-12 11:30:55
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\app\appfunction.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#ifndef APPFUNCTION_H
#define APPFUNCTION_H
#include "log.h"
/*************************************************************/
/*DPID_DEVICE_CONTROL*/

typedef enum
{
    UNLIGHT, // δ����
    LIGHTED, // �ѵ���
    PERSENT, // ��ǰ����
} LIGHTSTATUS_ENUM;

#pragma pack(push, 1)
typedef struct
{
    uint8_t id;                // �ư�id
    uint8_t index;             // ����
    LIGHTSTATUS_ENUM lightsta; // ����״̬
} app_lightstatus_Typedef;

typedef struct
{
    uint8_t lightnum;   // �ư�����
    app_lightstatus_Typedef lightsta[32];
} app_device_control_Typedef;
#pragma pack(pop)
/*************************************************************/



/*У��ͨ�������Ƿ���ȷ*/
uint8_t com_dataverify(uint8_t *sur, uint16_t size);
//
void mcu_update_ef_detail(uint8_t efindex); // �ϱ���Ч����
//
void mcu_update_efsketch(com_issue_cmd_TypeDef *p); // ����ָ���ϱ���Ч����
void mcu_update_one_efsketch(uint8_t efnum);        // �ϱ�ĳ��Ч����
/*mcu�ϱ���Ч����-�Ӳ����б��dp�ϴ�*/
void mcu_update_playlist_efsketch(com_issue_cmd_TypeDef *p);


/*mcu�ϱ�ȫ����Ч��˳���*/
void mcu_update_allef_ranklist(void);
/*mcu�ϱ��Զ����Ч��˳���*/
void mcu_update_originalef_ranklist(void);
/*mcu�ϱ��ղص�Ч��˳���*/
void mcu_update_favoritesef_ranklist(void);
/*mcu�ϱ������б��˳���*/
void mcu_update_playlist_ranklist(void);
//
void mcu_update_playdetail(uint8_t playnum); // �ϱ�ĳ���������б����顱
void mcu_update_current_playdetail(void);    // �ϱ���ǰ���ڲ��ŵġ������б����顱
//
/*mcu�ϱ�����״̬*/
void mcu_update_playstatus(void);

//
app_shape_enum convert_device_shape_data(device_shape_enum shape); // �豸��״��Ϣ����app��ʽ����ת��
void mcu_download_device_detail(uint8_t *sur, uint16_t length);    // �����豸��Ϣ
void mcu_update_device_detail(void);                               // �ϱ��豸��Ϣ
//
/*










*/

/*���DPID_EFFECT_DETIAL�Ĵ�����*/
uint8_t mcu_download_effect_detail_handle(uint8_t *sur, uint16_t length);
/*���DPID_ISSUE_CMD�Ĵ�����*/
uint8_t mcu_download_issue_cmd_handle(uint8_t *sur, uint16_t length);
/*���DPID_EFFECT_PREVIEW�Ĵ�����*/
void mcu_download_effect_preview(uint8_t *sur, uint16_t length);
/*���DPID_PLAY_DETIAL�Ĵ�����*/
uint8_t mcu_download_play_detial(uint8_t *sur, uint16_t length);
//

uint8_t mcu_download_play_control_detial(uint8_t *sur, uint16_t length);        // ���ز��ſ�������
void mcu_update_play_control_detial(playcontrol_type_enum type, uint8_t value); // �ϴ����ſ�������
void mcu_update_current_play_ef_index();                                        // �ϴ���ǰ���ŵĵ�Ч����

//

/*���DPID_DEVICE_CONTROL�Ĵ�����*/
uint8_t mcu_download_device_control(uint8_t *sur, uint16_t length);
/*�������ع̼�*/
void mcu_firmware_download(uint8_t *sur, uint16_t position, uint16_t length);
//
/*���DPID_BRIGHT_VAL�Ĵ�����*/
void mcu_download_bright_val(uint8_t bri);
/*�ϴ�����*/
void mcu_update_bright_val(void);
/*���DPID_SWITCH_LED�Ĵ�����*/
void mcu_download_switch_led(uint8_t sw);
/*�ϱ�����״̬*/
void mcu_update_switch_led(void);

//
void mcu_download_switch_indicator(uint8_t bool); // ����ָʾ�ƿ���״̬
void mcu_update_switch_indicator(void);           // �ϴ�ָʾ�ƿ���״̬
//

void mcu_download_switch_mic(uint8_t bool); // ������˷翪��״̬
void mcu_update_switch_mic(void);           // �ϴ���˷翪��״̬
//
void mcu_download_auto_brightness_switch(uint8_t bool);    // �����Զ����ȵĿ���
void mcu_update_auto_brightness_switch(void);              // �ϴ��Զ����ȵĿ���״̬
void modify_auto_brightness_switch(enable_status_enum en); // �޸��Զ����ȿ���
//
void mcu_download_auto_brightness_mode(uint8_t num); // �����Զ����ȵ�ģʽ
void mcu_update_auto_brightness_mode(void);          // �ϴ��Զ����ȵ�ģʽ
//
void mcu_download_brightness_auto(uint8_t bright); // �����Զ����Ƚ����ڵ�����ֵ
void mcu_update_brightness_auto(void);             // �ϴ��Զ����Ƚ����ڵ�����ֵ
//
void mcu_download_clock_list(uint8_t *sur, uint16_t length); // �������Ӽƻ�������
void mcu_update_clock_list(void);                            // �ϴ����Ӽƻ�������
//
uint8_t mcu_download_clock_detial(uint8_t *sur, uint16_t length); // ������������
void mcu_update_clock_detial(uint8_t num);                        // �ϴ���������
//
void mcu_update_device_indentify(void);                            // �ϴ��豸��Ա�ʶ
void mcu_download_device_indentify(uint8_t *sur, uint16_t length); // �����豸��Ա�ʶ
void mcu_download_reserved3(uint8_t *sur, uint16_t length);        // ����DP���ݣ�����3��
//
void mcu_update_current_ef_detail(void); // �ϱ���ǰ���ŵĵ�Ч��Ϣ
void mcu_update_reserved4(void);             // �ϴ�dp��Ϣ������4��
//
void mcu_update_current_ef_brightness(void); // �ϴ����ŵĵ�Ч��������Ϣ
void mcu_download_ef_brightness(uint8_t *sur, uint16_t length); // ���ص�Ч������Ϣ
void mcu_download_reserved5(uint8_t *sur, uint16_t length); // ����DP��Ϣ������5��
//
void log_to_server(LOG_CODE code);

//
#endif
