#ifndef  DEBUD_H
#define  DEBUD_H
#include "Function_Init.H"

#define log(...) printf(__VA_ARGS__)

void Debug(void);


extern uint8_t test_onoff;
extern uint8_t test_color_num;
extern uint8_t test_brightness;

/*norflashѭ����д����*/
void norflash_auto_rw_test(void);

/*���Ե�Ч�Ĵ洢��д*/
void debug_save_effect_detial(void);
/*��������Զ����Ч*/
void debug_add_original_ef(void);
/*����ɾ���Զ����Ч*/
void debug_delete_original_ef(void);
/*����ɾ�������б�*/
void debug_delete_playlist(void);
/*������Ӳ����б�*/
void debug_add_playlist(void);
/*������Ӷ�ʱ��*/
void debug_add_schedule(void);
/*����ɾ����ʱ��*/
void debug_delete_schedule(void);
/*�л���һ���õ�Ч*/
void debug_play_next_effect(void);
/*�л���һ���õ�Ч*/
void debug_play_last_effect(void);

/*���Կ�ʼ��ͣ������ɫ*/
void test_onoff_play(void);
/*���Բ�����ɫ*/
void test_play_color(void);
/*�����л���ɫ*/
void test_change_color(uint8_t dir);
/*���Ե����Ӽ�����*/
void test_click_brightness(uint8_t dir);
/*���Գ����Ӽ�����*/
void test_long_brightness(uint8_t dir);

/*����1������Ժ���*/
void debug_K1(void);
/*����2������Ժ���*/
void debug_K2(void);
/*����3������Ժ���*/
void debug_K3(void);
/*����4������Ժ���*/
void debug_K4(void);
/*����5������Ժ���*/
void debug_K5(void);
#endif
