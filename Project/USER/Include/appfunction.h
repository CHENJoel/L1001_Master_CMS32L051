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

#endif
