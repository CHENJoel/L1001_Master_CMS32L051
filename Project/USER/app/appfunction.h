#ifndef APPFUNCTION_H
#define APPFUNCTION_H
#include "Function_Init.H"

/*У��ͨ�������Ƿ���ȷ*/
uint8_t com_dataverify(uint8_t *sur, uint16_t size);
/*mcu�ϱ���Ч����*/
void mcu_update_efdetail(uint8_t efnum);
/*mcu�ϱ���Ч����*/
void mcu_update_efsketch(com_issue_cmd_TypeDef *p);
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
void mcu_download_play_detial(uint8_t *sur, uint16_t length);
/*
*/

/*�������ع̼�*/
void mcu_firmware_download(uint8_t *sur, uint16_t position, uint16_t length);
#endif
