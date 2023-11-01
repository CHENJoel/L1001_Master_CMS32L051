#ifndef _PLAY_H
#define _PLAY_H
#include "Function_Init.H"

#include "L0_slave.h"
#define DMA_BUFFER_SIZE (SLAVEDEVICE_NUM * sizeof(playdata_Typedef) + sizeof(packhead_Typedef))
#define NULL_EFFECTNUM 0xFF // ��Ч��Ч���

// // // extern uint8_t dma_buffer[DMA_BUFFER_SIZE];
extern const uint8_t bright_table[5];


typedef enum
{
    PLAYING_MODE,   // ��������ģʽ
    PAIRING_MODE,   // �ư����ģʽ
    PREVIEW_MODE,   // ��ЧԤ��ģʽ
} control_mode_enum; /*����ģʽ*/


typedef enum
{
    SOURCE_LIST,   // �б���
    SOURCE_TEMP,   // ��ʱ����
} playsource_enum; /*����Դ*/

typedef enum
{
    RANDOM_MODE, // �������
    LOOP_MODE,   // ѭ������
} playmode_enum; /*����ѭ��ģʽ*/

typedef enum
{
    RUN,   // ����
    PAUSE, // ��ͣ
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
    uint8_t history[32];            // ����������ŵĵ�Ч��¼
} play_minidetail_TypeDef;          /*�����б�����*/

typedef enum
{
    SW_OFF,
    SW_ON,
} sw_status_enum;

typedef struct
{
    uint8_t now;    // ��ǰֵ
    uint8_t tar;    // Ŀ��ֵ
    uint8_t dir;    // ����
} NTSD_VAL_TypeDef;

typedef struct
{
    sw_status_enum sw_status;              // ȫ�ֿ���
    NTSD_VAL_TypeDef brightness;           // ȫ������
    global_setting_TypeDef global_setting; // ȫ������
} playwork_TypeDef;

typedef struct
{
    control_mode_enum control_mode; // ����ģʽ
    playsource_enum source;         // ����Դ
    playwork_TypeDef work;
    playmode_enum mode;             // ����ģʽ
    playstatus_enum status;         // ����״̬
    play_minidetail_TypeDef detail; // ����������Ϣ
    Efdetail_TypeDef efdetail;      // ��ǰ��Ч��Ϣ
} play_TypeDef;

extern play_TypeDef play;

/*-----------------------------------------------------------*/
// typedef struct
// {
//     uint8_t brightness;    // Ĭ������
//     uint8_t color_sum;     // ɫ������ɫ���� ֵ0����õ�Чδ����
//     Motion_TypeDef motion; // ��Ч���,��̬/����/����/����/����/����/��ȼ/��� 0~7
//     Move_TypeDef move;     // �˶�������,����/����/����/����/���ܷ�ɢ/���Ļ�� 0~5
//     MODE_TypeDef Mode;     // ��ͨ/�ɶ�
//     uint8_t speed;         // �˶��ٶ�
//     uint8_t RESERVED[2];   // �ռ䱣��
// } parabuf_TypeDeff;    // 8byte
// typedef struct
// {
//     EF_para_data_TypeDef User_EF_Param[64]; // ��Ч�Ĳ���,ǰ30Ϊ���õ�Ч�Ĳ�������30Ϊ�Զ����Ч�Ĳ���,����Ϊ����
// } UserEFparadata_TypeDef;

// typedef struct
// {
//     RGBWInf_TypeDef data[EfColor_SizeNum]; // ÿ����Ч������16����ɫ
// } colorbuf_TypeDef;

// typedef struct
// {
//     colorbuf_TypeDef color;
//     parabuf_TypeDeff para;
// } playbuf_TypeDef;


extern Efdetail_TypeDef playbuf;











/*------------------------------------------------------------*/
/*�л���Ч*/
uint8_t switch_effect(uint8_t efnum);
/*�л����µ�Ч*/
uint8_t switch_ln_effect(switchplay_enum num);

/*���б��в�����һ��Ч*/
void switch_next_ef_in_playlist(void);
/*���б��в�����һ��Ч*/
void switch_last_ef_in_playlist(void);
/* �л������б� */
uint8_t switch_playlist(uint8_t listnum);


/*���ų�ʼ��*/
void play_init(void);
/*������ʷ���ŵ�Ч*/
void push_playnum_in_history(uint8_t efnum);

/*
 * @Description: ȡ����ʷ���ŵ�Ч
 * @param:
 * @return:
*/
uint8_t pop_playnum_in_history(void);

//
void enter_device_pairing_mode(void); // ����ư����ģʽ
void enter_playing_effect_mode(void); // �����������ŵ�Чģʽ
void enter_preview_effect_mode(Efdetail_TypeDef* efdetail); // ����Ԥ����Чģʽ
void exit_preview_effect_mode(void);  // �˳�Ԥ����Чģʽ
//

/*�ڱ��л�ȡ��һ��Ԫ��*/
uint8_t get_list_next_num(uint8_t *list, uint8_t size, uint8_t num);


/*
 * @Description: ��ͣ���ŵ�Ч
 * @param:
 * @return:
*/
void effect_play_pause(void);
/*
 * @Description: �������ŵ�Ч
 * @param:
 * @return:
 */
void resume_play_effect(void);
/***************************/
//
void load_local_effect_data(void);                         // ���ر��ص�Ч��Ϣ
void load_preview_effect_data(Efdetail_TypeDef *efdetail); // ����Ԥ����Ч��Ϣ
//
/*��λ����֡����*/
void play_frame_reset(void);
/*ϵͳ���ŵ�Ч��ʼ��*/
void play_sys_effect_init(void);
/*���ɸõ�Ч�Ķ�������*/
void generate_play_video_buffer(void);
/*������ӻ������б��*/
void figure_slave_run_number(void);
/*���ʹӻ���������*/
// // void transmit_slave_play_data(void);
/*���еƵ���ͬ����ɫ*/
void play_color_in_all_salve_light(uint8_t bri, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
/*�ر����еư�*/
void turn_off_all_salve_light(void);





/*���ŵ�Ч*/
void play_effect_video(void);
//
void play_current_effect(void);//��ͷ��ʼ���ŵ�ǰ��Ч
void play_new_effect(uint8_t efnum);     // �����µ�Ч
void play_preview_effect(Efdetail_TypeDef* efdetail); // ����Ԥ����Ч
//
void preprocess_play_effect(void);// Ԥ����������
/***********************************************************************/

void transmit_playdata_RGBbr(void);                    // ���͡�RGBbr����ʽ�Ĳ�������
void transmit_playdata_COLOR(void); // ���͡�COLOR����ʽ�Ĳ�������
void transmit_playsame_RGBbr(L0_playRGBbr_Typedef *x); // �㲥���͡�RGBbr����ʽ�Ĳ�������

//void light_device_pairing_play(app_device_control_Typedef *x); //�ư���ʾ���״̬
#endif
