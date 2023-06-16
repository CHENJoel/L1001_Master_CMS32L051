#ifndef _COMAPP_H_
#define _COMAPP_H_
#include "Function_Init.H"
#include "slave.h"
// #include "play.h"
#pragma pack(push, 1)
typedef struct
{
    uint8_t idex;            /* ���� */
    Efdetail_TypeDef Efdata;   /* ��Ч���� */
    uint8_t checksum;             /* У��� */
} com_effect_detial_TypeDef; // ��Ч����
#pragma pack(pop)
/*********************************************************************/
#pragma pack(push, 1)
typedef struct
{
    uint8_t index;                          /*����*/
    uint8_t namelenght;                     /* �����ַ����� */
    uint8_t Name[15];                       /* ��Ч���� */
    EffectType_Enum EffectType;             /* ��Ч���� */
    Attribute_Enum Attribute;               /* ��Ч���� */
    EfColorminiInf_TypeDef EfColormioniInf; /* ��ɫ������ */
} Efminidetail_TypeDef;                     // ��Чmini��Ϣ
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct
{
    uint8_t num;                    /* ��Ч���� */
    Efminidetail_TypeDef Efdata[4]; /* ���� */
    uint8_t checksum;                    /* У��� */
} com_effect_sketch_TypeDef;        // ��Ч����
#pragma pack(pop)
/*********************************************************************/

#pragma pack(push, 1)
typedef struct /* ��Ч��˳��� */
{
    uint8_t num;         /* ��Ч�б�����Ч���ݵ����� */
    uint8_t list[100];   /* ��Ч�б�.�洢��Ч������ */
} comefranklist_TypeDef; /*�洢���ڿռ�ֲ�*/
typedef struct
{
    comefranklist_TypeDef ranklist;
    uint8_t checksum;      /* У��� */
} com_ranklist_TypeDef; // ��Ч˳���
#pragma pack(pop)
/*********************************************************************/
#pragma pack(push, 1)

typedef struct
{
    uint8_t length;   /* �ַ����� */
    uint8_t text[15]; /* ���� */
} comname_TypeDef;

typedef struct
{
    uint8_t index;             /*����*/
    name_TypeDef name;         /*����*/
} com_playlist_sketch_TypeDef; // �����б�����
typedef struct
{
    uint8_t sum;                          /* ���� */
    com_playlist_sketch_TypeDef list[14]; /* �����б����� */
    uint8_t checksum;                     /* У��� */
} com_playlist_TypeDef;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    uint8_t idex;              /* ���� */
    playdetail_TypeDef pldata; /* �����б����� */
    uint8_t checksum;          /* У��� */
} com_play_detial_TypeDef;     // �����б�����
#pragma pack(pop)
/*********************************************************************/
typedef enum /*APP�·�ָ��ö��*/
{
    ASK_EFSKETCH,                // ����Ч������
    ASK_EFDETAIL,                // ����Ч������
    DELETE_EF,                   // ɾ��Ч��
    ADD_FAVORITES,               // �����ղ�
    DELETE_FAVORITES,            // ȡ���ղ�
    ASK_ALLEFRANKLIST,           // ����ȫ����Ч��˳���
    ASK_ORINGINALRANKLIST,       // �����Զ����Ч��˳���
    ASK_FAVORITESRANKLIST,       // �����ղص�Ч��˳���
    ASK_PLAYLISTRANKLIST,        // ������Ŀ�б���˳���
    ASK_EFFECTANKLIST,           // �����Ч��ص�˳���(ȫ�����Զ��塢�ղ�)
    ASK_PLAY_EFSKETCH,           // ����Ч������
    REAERVE_CMD11,               // ����
    DELETE_PLAYLISTRANKLISTLIST, // ɾ�������б���ĳ�������
    SWITCH_PLAYLIST,             // �л������б�
    ASK_PLAYDETAIL,              // ���󲥷�����
    ASK_PLAYSTATUS,              // ���󲥷�״̬
    DELETE_SCHEDULE,             // ɾ����ʱ�ƻ�
    ASK_SCHEDULE_DETAIL,         // ����ʱ����
    ASK_DEVICEDATA,              // ����ư���Ϣ
    EXIT_APPCONNTROL,            // �˳�app����
    ASK_SCHEDULE_SKETCH,         // ����ʱ������
} issue_cmd;
#pragma pack(push, 1)
typedef struct
{
    issue_cmd cmd;       // ָ��
    uint8_t data[5];     // ����
    uint8_t checksum;    // У���
} com_issue_cmd_TypeDef; // �·�ָ��
#pragma pack(pop)

typedef enum
{
    PLAY_STATUS,          // ����/��ͣ
    PLAY_SWITCH,          // �������л�
    EFFECT_INDEX,         // Ч������
    PLAY_MODE,            // ����ѭ��ģʽ
    PLAYLIST_INDEX = 100, // �����б�����
} playcontrol_type_enum;  // ��������

#pragma pack(push, 1)
typedef struct
{
    playcontrol_type_enum type;           // ��������
    uint8_t value;          // ����ֵ
    uint8_t checksum;       // У���
} com_play_control_TypeDef;
#pragma pack(pop)

#pragma pack(push, 1)

typedef struct
{
    uint8_t id;              // �ư�id
    device_type_enum type;   // ��״
    uint16_t angle;          // �Ƕ�
    uint16_t cooed_x;        // x����
    uint16_t cooed_y;        // y����
} com_device_detail_TypeDef; // �豸����
typedef struct
{
    com_device_detail_TypeDef data[32];
} com_device_data_TypeDef;
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct
{
    uint8_t id;         // �ư�id
    uint8_t brightness; // ����
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
    uint8_t res;           // ����
} com_devicecolor_TypeDef; // �豸����

typedef struct
{
    uint8_t num; //
    com_devicecolor_TypeDef data[32];
    uint8_t checksum; // У���
} com_device_control_TypeDef;
#pragma pack(pop)

#pragma pack(push, 1)

// sketch

typedef struct
{
    uint8_t index;
    action_enum action;      // ��������
    time_TypeDef actiontime; // ����ʱ��
    repeat_TypeDef repeat;   // ���ڼƻ�
} com_schedule_sketch_TypeDef;

typedef struct
{
    uint8_t num;
    com_schedule_sketch_TypeDef list[30];
    uint8_t checksum; // У���
} com_schedule_sketchlist_TypeDef;

typedef struct /*  */
{
    uint8_t index;
    name_TypeDef name;
    action_enum action;      // ��������
    uint8_t ef_index;        // ��Ч��������
    uint8_t ultimatebright;  // ��������
    time_TypeDef actiontime; // ����ʱ��
    time_TypeDef duration;   // ����ʱ��
    repeat_TypeDef repeat;   // ���ڼƻ�
    uint8_t checksum;        // У���
} com_schedule_detail_TypeDef;

#pragma pack(pop)

#endif