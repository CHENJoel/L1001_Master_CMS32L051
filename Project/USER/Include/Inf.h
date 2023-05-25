#ifndef INF_H
#define INF_H
#include "Function_Init.H"

#pragma pack(push, 1) // �ṹ�尴1�ֽڶ���

#define EfColor_SizeNum 32    // ��Ч����ɫ������������
#define EfColor_miniSizeNum 8 // ��Ч��������ɫ������������
#define Ef_SizeNum 256        // ��Ч��������������Ԥ��256
#define PlayList_SizeNum Ef_SizeNum * 2

#define original_ef_basenum 128 // �Զ����Ч�Ļ����
#define original_ef_num 30      // �Զ����Ч����
#define all_ef_num 60           // ȫ����Ч����

#define built_in_ef_num (sizeof(dfdata) / sizeof(df_data_TypeDef)) // ���õ�Ч����

#define default_ef_Speed 50
#define default_ef_Brightness1 50
#define default_ef_Brightness2 100
#define default_ef_MicSensitivity 100
#define default_ef_Attribute ORIGIN
#define default_ef_Direction DIRECTION_UP

typedef struct
{
    uint8_t Min; // ����
    uint8_t Sec; // ��
} Time_TypeDef;

typedef struct
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
} RGBWInf_TypeDef;

typedef enum /*��̬Ч��*/
{
    FLOW_STATIC, // Static ��̬
    FLOW_BREATH, // Breath ����
    FLOW_STREAM, // Stream ����
    FLOW_REVERB, // Reverberate ����
    FLOW_HOPSCO, // Hopscotch ����
    FLOW_LIGHTN, // Lightning ����
    FLOW_IGNITE, // Ignite ��ȼ
    FLOW_RANDOM, // Random ���
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
    EMPTY,     // ��
} Attribute_Enum;

/******************************************************************************************************************/
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

#pragma pack(push, 1)
typedef struct
{
    uint8_t Name[16];              /* ��Ч���� */
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
#pragma pack(pop)


/******************************************************************************************************************/
typedef struct
{
    // // // Efdetail_TypeDef Default_Efdata[128];  // ���õ�Ч ������0~127
    // // // Efdetail_TypeDef Original_Efdata[128]; // �Զ����Ч ������128~255
    Efdetail_TypeDef efdata[256]; // ���õ�Ч ������0~127     -�Զ����Ч ������128~255
} EffectInf_TypeDef;
/******************************************************************************************************************/
/******************************************************************/

typedef struct /*  */
{
    uint8_t Name[32];               /* �б����� */
    uint8_t num;                    /* ��Ч�б�����Ч���ݵ����� */
    Time_TypeDef DurationTime;      /* ����ʱ�� */
    uint8_t list[PlayList_SizeNum]; /* ��Ч�б� */
} PlayList_TypeDef;

/******************************************************************/

typedef struct /* ��Ч��˳��� */
{
    uint8_t num;             /* ��Ч�б�����Ч���ݵ����� */
    uint8_t list[60];       /* ��Ч�б�.�洢��Ч������ */
} ef_ranklist_TypeDef; /*�洢���ڿռ�ֲ�*/

typedef struct /* �����б��˳��� */
{
    uint8_t num;                   /* ˳���б�����Ч���ݵ����� */
    uint8_t list[60];             /* ˳���б�.�洢���ű�������� */
} playList_ranklist_TypeDef; /*�洢���ڿռ�ֲ�*/

/******************************************************************************************************************/
typedef struct
{
    ef_ranklist_TypeDef all_ef_ranklist;         /* ȫ����Ч��˳���б�*/
    ef_ranklist_TypeDef original_ef_ranklist;    /* �Զ����Ч��˳���б�*/
    ef_ranklist_TypeDef favorites_ef_ranklist;   /* �ղص�Ч��˳���б�*/
    playList_ranklist_TypeDef PlayList_ranklist; /* �����б��˳���б�*/
} ranklist_TypeDef;
/******************************************************************************************************************/
/*********************************************************/
/*��ʱ��*/

typedef enum /*  */
{
    TURN_OFF,
    TURN_ON,
} Action_Enum;

typedef struct /*  */
{
    Action_Enum Action;        // ��������
    uint8_t Ef_id;             // ��Ч��������
    uint8_t UltimateBright;    // ��������
    Time_TypeDef ActionTime;   // ����ʱ��
    Time_TypeDef DurationTime; // ����ʱ��
    union
    {
        uint8_t Week;
        struct
        {
            uint8_t Mon : 1; // ��һ
            uint8_t Tue : 1; // �ܶ�
            uint8_t Wed : 1; // ����
            uint8_t Thu : 1; // ����
            uint8_t Fri : 1; // ����
            uint8_t Sat : 1; // ����
            uint8_t Sun : 1; // ����
        } day;
    } RepeatTime; // �ظ�ʱ��
} Routine_TypeDef;

/******************************************************************************************************************/
typedef struct /*  */
{
    uint8_t Num;              /* ��Ч���ݵ����� */
    Routine_TypeDef list[30]; /* ��ʱ��Ϣ */
} RoutineList_TypeDef;
/******************************************************************************************************************/
/*********************************************/
typedef struct
{
    // union
    // {
    //     uint8_t ON_flag;
    //     struct
    //     {
    //         uint8_t Illumination : 1; // ������
    //         uint8_t Ambient : 1;      // ������
    //     } day;
    // } AutoBrightness; // �Զ�����

    union
    {
        uint8_t byte;
        struct
        {
            uint8_t Illumination : 1; // ������
            uint8_t Ambient : 1;      // ������
            uint8_t StatusLED : 1;    // ָʾ��
            uint8_t MicrophoneEn : 1; // ��˷翪��
        } bit;
    } enable; // �Զ�����
} GeneralSetting_TypeDef;

// // // // int8_t RESERVED[512 - sizeof(Sector0_data_TypeDef)]; // �ռ䱣��

#pragma pack(pop)
#endif
