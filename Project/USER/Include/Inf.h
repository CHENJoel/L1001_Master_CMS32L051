#ifndef INF_H
#define INF_H
#include "Function_Init.H"

#pragma pack(push, 1) // �ṹ�尴1�ֽڶ���

#define EfColor_SizeNum 32 // ��Ч����ɫ������������
#define Ef_SizeNum 30      // ��Ч��������������Ԥ��256
#define PlayList_SizeNum Ef_SizeNum * 2

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
    DIRECTION_SEPARATE, // ���ܷ�ɢ
    DIRECTION_CONVERGE, // ���Ļ��
} Direction_Enum;

typedef enum /*��Ч����*/
{
    STATIC_TYPE,  // ��̬
    DYNAMIC_TYPE, // ��̬
    RHYTHM_TYPE,  // �ɶ�
} EffectType_Enum;

typedef enum /*��Ч����*/
{
    ORIGIN,    // ԭʼ
    FAVORITES, // �ղ�
    OTHER,     // ������ɾ��
} Attribute_Enum;

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
/******************************************************************************************************/

typedef struct
{
    uint8_t Name[30];              /* ��Ч���� */
    uint8_t Speed;                 /* �ٶ� */
    uint8_t Brightness1;           /* ����1 ��ʼ����/�ɶ���������� */
    uint8_t Brightness2;           /* ����2 �ɶ��������*/
    uint8_t MicSensitivity;        /* ��ͷ������*/
    EffectType_Enum EffectType;    /* ��Ч���� */
    Attribute_Enum MotionType;     /* ��Ч���� */
    Direction_Enum Direction;      /* �˶����� */
    Flow_Enum Flow;                /* ��̬Ч�� */
    EfColorInf_TypeDef EfColorInf; /* ��ɫ������ */
} Efdata_TypeDef;

typedef struct
{
    Efdata_TypeDef Default_Efdata[Ef_SizeNum];  // ���õ�Ч ������0~127
    Efdata_TypeDef Original_Efdata[Ef_SizeNum]; // �Զ����Ч ������128~256
} EffectInf_TypeDef;

/******************************************************************/

typedef struct /* �����б���Ϣ */
{
    uint8_t Name[30];               /* �б����� */
    uint8_t Num;                    /* ��Ч�б�����Ч���ݵ����� */
    Time_TypeDef DurationTime;      /* ����ʱ�� */
    uint8_t List[PlayList_SizeNum]; /* ��Ч�б� */
} PlayList_TypeDef;

/******************************************************************/

typedef struct /* ��Ч��˳��� */
{
    uint8_t Num;              /* ��Ч�б�����Ч���ݵ����� */
    uint8_t List[Ef_SizeNum]; /* ��Ч�б�.�洢��Ч������ */
} Ef_RankList_TypeDef;

typedef struct /* �����б��˳��� */
{
    uint8_t Num;              /* �����б�����Ч���ݵ����� */
    uint8_t List[Ef_SizeNum]; /* �����б�.�洢���ű�������� */
} PlayList_RankList_TypeDef;

typedef struct
{
    Ef_RankList_TypeDef Default_Ef_RankList;     /* ���õ�Ч��˳���б�*/
    Ef_RankList_TypeDef Original_Ef_RankList;    /* �Զ����Ч��˳���б�*/
    Ef_RankList_TypeDef Favorites_Ef_RankList;   /* �ղص�Ч��˳���б�*/
    PlayList_RankList_TypeDef PlayList_RankList; /* �����б��˳���б�*/
} List_TypeDef;
/*********************************************************/
/*��ʱ��*/

typedef enum /* �����б���Ϣ */
{
    TURN_OFF,
    TURN_ON,
} Action_Enum;

typedef struct /* �����б���Ϣ */
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
