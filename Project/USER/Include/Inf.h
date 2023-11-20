#ifndef INF_H
#define INF_H
#include "Function_Init.H"

#define MAX_BRIGHTNESS 100  // �������

#define EfColor_SizeNum 32    // ��Ч����ɫ������������
#define EfColor_miniSizeNum 8 // ��Ч��������ɫ������������
#define Ef_SizeNum 256        // ��Ч��������������Ԥ��256
#define PlayList_efMaxNum 60   // �����б����������
#define SCHEDULE_NUM 30       // ��ʱ�ƻ�������
#define LIST_MAXNUM 13  // �б�������

#define original_ef_basenum 128                      // �Զ����Ч�Ļ����
#define original_ef_num 30                           // �Զ����Ч����
#define built_in_ef_basenum 0                        // ���õ�Ч�Ļ����
#define built_in_ef_num 30                           // ���õ�Ч����
#define all_ef_num built_in_ef_num + original_ef_num // ȫ����Ч����

#define default_ef_Speed 50
#define default_ef_Brightness1 50
#define default_ef_Brightness2 100
#define default_ef_MicSensitivity 100
#define default_ef_Attribute ORIGIN
#define default_ef_Direction DIRECTION_UP


typedef enum
{
    DISABLE_STA,      // ʧ��״̬
    ENABLE_STA,       // ʹ��״̬
} enable_status_enum; // ʹ��״̬

/*********************************************/

typedef enum
{
    Illumination,      // �������Զ�����.����
    Ambient,           // �������Զ�����.����
} autobrightType_enum; // �Զ���������

typedef struct
{
    enable_status_enum autobright_ensta; // �Զ����ȿ���
    autobrightType_enum autobrightType;  // �Զ���������
    enable_status_enum indicator_sta;    // ָʾ�ƿ���
    enable_status_enum microphone_ensta; // ��˷翪��
    uint8_t brightness_set;              // ȫ�����ȴ洢ֵ
    
} global_setting_TypeDef;

extern const global_setting_TypeDef global_setting_default;

typedef struct
{
    uint8_t hou_HM; // Сʱ
    uint8_t min_HM;  // ����
} time_HM_TypeDef;

typedef struct
{
    uint8_t min_MS; // ����
    uint8_t sec_MS; // ��
} time_MS_TypeDef;

typedef struct
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
} RGBWInf_TypeDef;

typedef enum /*��̬Ч��*/
{
    FLOW_STATIC, // Static ��̬ 0
    FLOW_BREATH, // Breath ���� 1
    FLOW_STREAM, // Stream ���� 2
    FLOW_REVERB, // Reverberate ���� 3
    FLOW_HOPSCO, // Hopscotch ���� 4
    FLOW_LIGHTN, // Lightning ���� 5
    FLOW_IGNITE, // Ignite ��ȼ 6
    FLOW_RANDOM, // Random ��� 7
} Flow_Enum;     //

typedef enum /*�˶�����*/
{
    DIRECTION_UP,       // �����ƶ�
    DIRECTION_DOWN,     // �����ƶ�
    DIRECTION_LEFT,     // �����ƶ�
    DIRECTION_RIGHT,    // �����ƶ�
    DIRECTION_CONVERGE, // ���Ļ��
    DIRECTION_SEPARATE, // ���ܷ�ɢ
} Direction_Enum;

typedef enum /*��Ч����*/
{
    STATIC_TYPE,  // ��̬
    DYNAMIC_TYPE, // ��̬
    RHYTHM_TYPE,  // �ɶ�
} EffectType_Enum;

typedef enum /*��Ч����*/
{
    ORIGIN,    // ԭʼ��δ�ղأ�
    FAVORITES, // �ղ�
    EMPTY,     // �գ�ɾ����
} Attribute_Enum;

/******************************************************************************************************************/
#pragma pack(push, 1) // �ṹ�尴1�ֽڶ���
/********************��Ч����********************/
typedef struct
{
    uint8_t id;            // �ư�id(��̬��Ч)/|������Ч(��̬��Ч)
    RGBWInf_TypeDef color; // �ư��Ӧ�ľ�̬��ɫ(��̬��Ч)|��ɫ��(��̬��Ч)
} ColorID_TypeDef;
typedef struct
{
    uint8_t colorNum;                         // ��ɫ����
    ColorID_TypeDef ColorID[EfColor_SizeNum]; // ��̬��Ч����ɫ��Ϣ
} EfColorInf_TypeDef;
typedef struct
{
    uint8_t colorNum;                         // ��ɫ����
    ColorID_TypeDef ColorID[EfColor_miniSizeNum]; // ��̬��Ч����ɫ��Ϣ
} EfColorminiInf_TypeDef;/*��Ч����/������Ϣ*/

typedef struct
{
    uint8_t namelenght;            /* �����ַ����� */
    uint8_t Name[15];              /* ��Ч���� */
    uint8_t Speed;                 /* �ٶ� */
    uint8_t Brightness1;           /* ����1 ��ʼ����/�ɶ���������� */
    uint8_t Brightness2;           /* ����2 �ɶ��������*/
    uint8_t MicSensitivity;        /* ��ͷ������*/
    EffectType_Enum EffectType;    /* ��Ч���� */
    Attribute_Enum Attribute;      /* ��Ч���� */
    Direction_Enum Direction;      /* �˶����� */
    Flow_Enum Flow;                /* ��̬Ч�� */
    EfColorInf_TypeDef EfColorInf; /* ��ɫ������ */
} Efdetail_TypeDef; // ��Ч����



/******************************************************************************************************************/
typedef struct
{
    Efdetail_TypeDef efdata[256]; // ���õ�Ч ������0~127     -�Զ����Ч ������128~255
} EffectInf_TypeDef;
/******************************************************************************************************************/
/******************************************************************/

typedef struct
{
    uint8_t length;   /* �ַ����� */
    uint8_t text[15]; /* ���� */
} name_TypeDef;

typedef struct /*  */
{
    name_TypeDef name;               /* ����*/
    time_MS_TypeDef DurationTime;    /* ����ʱ�� */
    uint8_t num;                     /* ��Ч�б�����Ч���ݵ����� */
    uint8_t list[PlayList_efMaxNum]; /* ��Ч�б� */
} playdetail_TypeDef; /*�����б�����*/

typedef struct
{
    playdetail_TypeDef pldata[256]; // ���õ�Ч ������0~127     -�Զ����Ч ������128~255
} PlayInf_TypeDef;  /*�����б�����*/
/******************************************************************/

typedef struct /* ��Ч��˳��� */
{
    uint8_t num;       /* ��Ч�б�����Ч���ݵ����� */
    uint8_t list[60];  /* ��Ч�б�.�洢��Ч������ */
} ef_ranklist_TypeDef; /*�洢���ڿռ�ֲ�*/

typedef struct /* �����б��˳��� */
{
    uint8_t num;             /* ˳���б�����Ч���ݵ����� */
    uint8_t list[13];        /* ˳���б�.�洢˳���������� */
} playlist_ranklist_TypeDef; /* �洢���ڿռ�ֲ� */

/******************************************************************************************************************/
typedef struct
{
    ef_ranklist_TypeDef all_ef_ranklist;                     /* ȫ����Ч��˳���б�*/
    ef_ranklist_TypeDef original_ef_ranklist;                /* �Զ����Ч��˳���б�*/
    ef_ranklist_TypeDef favorites_ef_ranklist;               /* �ղص�Ч��˳���б�*/
    playlist_ranklist_TypeDef playlist_ranklist;             /* �����б��˳���б�*/
    // // playdetaillist_ranklist_TypeDef playdetaillist_ranklist; /* ���������˳���б�*/
} ranklist_TypeDef;
/******************************************************************************************************************/
/*********************************************************/
/*��ʱ��*/
typedef enum
{
    FUN_DISABLE, // ����δ����
    FUN_ENABLE,  // ��������
} FUN_ENABLE_STA; // ����״̬

typedef enum /*  */
{
    TURN_OFF,
    TURN_ON,
} action_enum;

typedef union
{
    uint8_t week;
    struct
    {
        uint8_t Sun : 1; // ����
        uint8_t Mon : 1; // ��һ
        uint8_t Tue : 1; // �ܶ�
        uint8_t Wed : 1; // ����
        uint8_t Thu : 1; // ����
        uint8_t Fri : 1; // ����
        uint8_t Sat : 1; // ����
    } day;
} repeat_TypeDef; // �ظ�ʱ��

typedef struct /*  */
{
    name_TypeDef name;
    FUN_ENABLE_STA en_sta;      // ����״̬
    action_enum action;         // ��������
    uint8_t ef_index;           // ��Ч����
    uint8_t ultimatebright;     // ��������
    time_HM_TypeDef actiontime; // ����ʱ��
    time_HM_TypeDef duration;   // ����ʱ��
    repeat_TypeDef repeat;      // ���ڼƻ�
} clock_detail_TypeDef;

/******************************************************************************************************************/
typedef struct /*  */
{
    uint8_t num;                      /* ��Ч���ݵ����� */
    clock_detail_TypeDef list[SCHEDULE_NUM]; /* ��ʱ��Ϣ */
} clock_list_TypeDef;
/******************************************************************************************************************/

typedef struct /*  */
{
    uint8_t length;    // ���ݳ���
    uint8_t data[256]; // ����APPʹ�ã�Ƕ��ʽ��ʹ��
    /*
    ��Type������״����  ����1
    ���Ƕȡ�����/����1:�� 0:��������1��+���֣�����1��   �ܳ���2
    ��xֵ����  ����   �ܳ���2
    ��yֵ����  ����   �ܳ���2
    ��id����    ����1
*/
} device_indentify_TypeDef;



// // // // int8_t RESERVED[512 - sizeof(Sector0_data_TypeDef)]; // �ռ䱣��

#pragma pack(pop)
#endif
