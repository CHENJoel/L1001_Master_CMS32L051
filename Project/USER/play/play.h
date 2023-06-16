#ifndef _PLAY_H
#define _PLAY_H
#include "Function_Init.H"

#define NULL_EFFECTNUM 0xFF // ��Ч��Ч���

typedef enum
{
    RANDOM_MODE, // �������
    LOOP_MODE,   // ѭ������
} playmode_enum; /*����ѭ��ģʽ*/

typedef enum
{
    PAUSE, // ��ͣ
    RUN,   // ����
} playstatus_enum;

typedef enum
{
    LAST_EFFECT, // ��һ����Ч
    NEXT_EFFECT, // ��һ����Ч
} switchplay_enum;

typedef struct /*  */
{
    uint8_t listnum;                // ��ǰ�����б�������
    uint8_t efnum;                  // ��ǰ���ŵ�Ч����
    time_TypeDef duration;          // ����ʱ��
    uint8_t num;                    /* ��Ч�б�����Ч���ݵ����� */
    uint8_t list[PlayList_SizeNum]; /* ��Ч�б� */
    uint8_t history[10];         // ����������ŵĵ�Ч��¼
} play_minidetail_TypeDef;          /*�����б�����*/

typedef struct
{
    playmode_enum mode;             // ����ģʽ
    playstatus_enum status;         // ����״̬
    play_minidetail_TypeDef detail; // ����������Ϣ
} play_TypeDef;

extern play_TypeDef play;

/*�л���Ч*/
uint8_t switch_effect(uint8_t efnum);
/*�л����µ�Ч*/
uint8_t switch_ln_effect(switchplay_enum num);
/* �л������б� */
uint8_t switch_playlist(uint8_t listnum);
/*���ų�ʼ��*/
void play_init(void);
/*�ڱ���������Ч���*/
void add_num_in_list(uint8_t efnum);
/*�ڱ��л�ȡ��һ��Ԫ��*/
uint8_t get_list_next_num(uint8_t *list, uint8_t size, uint8_t num);
#endif
