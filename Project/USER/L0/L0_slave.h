
#ifndef _L0_SLAVE_H_
#define _L0_SLAVE_H_
#include "Function_Init.H"
// #include <stdlib.h>
#include "L0.H"
/**************************************************************************************************/

#pragma pack(push, 1)

typedef struct
{
    uint8_t cid; // �豸id
    uint8_t R;   // ��
    uint8_t G;   // ��
    uint8_t B;   // ��
    uint8_t br;  // ����
} L0_playRGBbr_Typedef;

typedef struct
{
    uint8_t cid; // �豸id
    uint8_t R;   // ��
    uint8_t G;   // ��
    uint8_t B;   // ��
    uint8_t W;   // ��
    uint8_t br;  // ����
} L0_playRGBWbr_Typedef;

typedef struct
{
    uint8_t cid;   // �豸id
    uint16_t pwmR; // ��
    uint16_t pwmG; // ��
    uint16_t pwmB; // ��
    uint16_t pwmW; // ��
} L0_playPWM_Typedef;

typedef enum
{
    RGB_COLOR,         // rgb����
    KELVIN_COLOR,      // ɫ������
} play_colortype_ENUM; // ��ɫ��������

typedef struct
{
    uint8_t cid; // �豸id
    play_colortype_ENUM type;
    uint8_t R;  // ��/ɫ��ֵ
    uint8_t G;  // ��
    uint8_t B;  // ��
    uint8_t br; // ����
} L0_playCOLOR_Typedef;

typedef struct
{
    L0_head_Typedef head;                     // ͨ������ͷ
    uint8_t playnum;                          // ��������
    L0_playRGBbr_Typedef dev[MAX_SLAVE_NUM]; // ��������
} L0_cmd_playRGBbr_Typedef;

typedef struct
{
    L0_head_Typedef head;                     // ͨ������ͷ
    uint8_t playnum;                          // ��������
    L0_playRGBWbr_Typedef dev[MAX_SLAVE_NUM]; // ��������
} L0_cmd_playRGBWbr_Typedef;

typedef struct
{
    L0_head_Typedef head;                     // ͨ������ͷ
    uint8_t playnum;                          // ��������
    L0_playPWM_Typedef dev[MAX_SLAVE_NUM]; // ��������
} L0_cmd_playPWM_Typedef;

typedef struct
{
    L0_head_Typedef head;                    // ͨ������ͷ
    uint8_t playnum;                         // ��������
    L0_playCOLOR_Typedef dev[MAX_SLAVE_NUM]; // ��������
} L0_cmd_playCOLOR_Typedef;
#pragma pack(pop)

/**************************************************************************************************/
#pragma pack(push, 1)
typedef struct
{
    L0_head_Typedef head; // ͨ������ͷ
    uint8_t gr_fine;      // �̺�΢��
    uint8_t gb_fine;      // ����΢��
    uint8_t gw_fine;      // �̰�΢��
    uint8_t br_fine;     // ����΢��
} L0_cmd_calibration_data_Typedef;
#pragma pack(pop)

/**************************************************************************************************/
#pragma pack(push, 1)
typedef struct
{
    L0_head_Typedef head; // ͨ������ͷ
    uint8_t cid;
    uint8_t uid;
    uint8_t random[3];  // �����
} L0_cmd_id_data_Typedef;
#pragma pack(pop)
/**************************************************************************************************/
#pragma pack(push, 1)
typedef struct
{
    L0_head_Typedef head; // ͨ������ͷ
    uint8_t data[10];
} L0_cmd_general_data_Typedef;
#pragma pack(pop)
/**************************************************************************************************/
/**************************************************************************************************/
#pragma pack(push, 1)
typedef struct
{
    L0_head_Typedef head; // ͨ������ͷ
    uint8_t cid;
    uint8_t shape;        // ��״
    uint16_t adval;        // adֵ
    uint8_t random[3];    // �����
} L0_cmd_shape_data_Typedef;
#pragma pack(pop)
/**************************************************************************************************/
/**************************************************************************************************/
#pragma pack(push, 1)
typedef struct
{
    L0_head_Typedef head; // ͨ������ͷ
    uint32_t powertimes;  // ��������
    uint8_t random[3];    // �����
} L0_cmd_powertimes_Typedef;
#pragma pack(pop)
/**************************************************************************************************/
void slave_command_parse(uint8_t *p, uint16_t len);       // �ӻ�ָ�����
void Fun_SLAVE_PLAY_RGB(uint8_t *p, uint16_t len);        // ���ŵƹ�
void Fun_SLAVE_PLAY_RGBW(uint8_t *p, uint16_t len);       // ���ŵƹ�
void Fun_SLAVE_PLAY_PWM(uint8_t *p, uint16_t len);        // ���ŵƹ�
void Fun_SLAVE_CONNECT_COID(uint8_t *p, uint16_t len);    // ����ͨ��ID
void Fun_SLAVE_REFRESH_COID(uint8_t *p, uint16_t len);    // ����ͨ��ID
void Fun_SLAVE_RESET_COID(uint8_t *p, uint16_t len);      // �ָ�ͨ��ID
void Fun_SLAVE_SET_COID(uint8_t *p, uint16_t len);        // ����ͨ��ID
void Fun_SLAVE_GET_ID(uint8_t *p, uint16_t len);          // ��ȡID
void Fun_SLAVE_GET_SHAPE(uint8_t *p, uint16_t len);       // ��ȡ��״
void Fun_SLAVE_GET_CALIBRATION(uint8_t *p, uint16_t len); // ��ȡУ׼����
void Fun_SLAVE_SET_CALIBRATION(uint8_t *p, uint16_t len); // ��ȡУ׼����
void Fun_SLAVE_PLAY_COLOR(uint8_t *p, uint16_t len);      // ���ŵƹ� ��COLOR����ʽ
/**/
void general_command_parse(uint8_t *p, uint16_t len); // ͨ��ָ�����
void Fun_GENERAL_POWERTIME(uint8_t *p, uint16_t len); // ��ȡ��������
#endif
