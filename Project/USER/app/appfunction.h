#ifndef APPFUNCTION_H
#define APPFUNCTION_H
#include "Function_Init.H"

/*У��ͨ�������Ƿ���ȷ*/
uint8_t com_dataverify(uint8_t *sur, uint16_t size);
/*mcu�ϱ���Ч����*/
void mcu_update_efdetail(uint8_t efnum);
/*mcu�ϱ���Ч����*/
void mcu_update_efsketch(com_issue_cmd_TypeDef *p);
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
/*mcu�ϱ���������*/
void mcu_update_playdetail(uint8_t playnum);
/*mcu�ϱ���ǰ��������*/
void mcu_update_current_playdetail(void);
/*mcu�ϱ�����״̬*/
void mcu_update_playstatus(void);
/*mcu�ϱ���ʱ�ƻ�������*/
void mcu_update_schedule_sketch(void);
/*mcu�ϱ���ʱ����*/
void mcu_update_schedule_detail(uint8_t num);
/*










*/
/*���DPID_SWITCH_LED�Ĵ�����*/
void mcu_download_switch_led(uint8_t sw);
/*���DPID_EFFECT_DETIAL�Ĵ�����*/
uint8_t mcu_download_effect_detail_handle(uint8_t *sur, uint16_t length);
/*���DPID_ISSUE_CMD�Ĵ�����*/
uint8_t mcu_download_issue_cmd_handle(uint8_t *sur, uint16_t length);
/*���DPID_EFFECT_PREVIEW�Ĵ�����*/
void mcu_download_effect_preview(uint8_t *sur, uint16_t length);
/*���DPID_PLAY_DETIAL�Ĵ�����*/
uint8_t mcu_download_play_detial(uint8_t *sur, uint16_t length);
/*���DPID_PLAY_CONTROL_DETIAL�Ĵ�����*/
uint8_t mcu_download_play_control_detial(uint8_t *sur, uint16_t length);
/*���DPID_DEVICE_DETAIL�Ĵ�����*/
void mcu_download_device_detail(uint8_t *sur, uint16_t length);
/*���DPID_DEVICE_CONTROL�Ĵ�����*/
uint8_t mcu_download_device_control(uint8_t *sur, uint16_t length);
/*
 */

/*�������ع̼�*/
void mcu_firmware_download(uint8_t *sur, uint16_t position, uint16_t length);
#endif
