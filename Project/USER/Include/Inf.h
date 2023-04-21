#ifndef INF_H
#define INF_H
#include "Function_Init.H"
#pragma pack(push, 1) // �ṹ�尴1�ֽڶ���

#define Dynamic_ColorNum 32 // ��̬��Ч�������ɫ����
#define Static_ColorNum 32  // ��̬̬��Ч�������ɫ����

typedef struct
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
} RGBWInf_TypeDef;

typedef enum /*��̬Ч��*/
{
    MOT_STATIC,   // Static ��̬
    MOT_BREATH,   // Breath ����
    MOT_STREAM,   // Stream ����
    MOT_REVERB,   // Reverberate ����
    MOT_HOPSCO,   // Hopscotch ����
    MOT_LIGHTN,   // Lightning ����
    MOT_IGNITE,   // Ignite ��ȼ
    MOT_RANDOM,   // Random ���
}MotionInf_TypeDef; //

typedef enum /*�˶�����*/
{
    MOV_UP,       // �����ƶ�
    MOV_DOWN,     // �����ƶ�
    MOV_LEFT,     // �����ƶ�
    MOV_RIGHT,    // �����ƶ�
    MOV_SEPARATE, // ���ܷ�ɢ
    MOV_CONVERGE, // ���Ļ��
} MoveInf_Enum;

typedef enum /*��������*/
{
    STATIC_TYPE,  // ��̬
    DYNAMIC_TYPE, // ��̬
    RHYTHM_TYPE,  // �ɶ�
} MotionType_Enum;

typedef enum /*��Ч����*/
{
    ORIGIN,    // ԭʼ
    FAVORITES, // �ղ�
    OTHER,     // ����
} EffectType_Enum;

/********************��̬��Ч����********************/
typedef struct
{
    uint8_t id;           // �ư�id(��̬��Ч)/|������Ч(��̬��Ч)
    RGBWInf_TypeDef color; // �ư��Ӧ�ľ�̬��ɫ(��̬��Ч)|��ɫ��(��̬��Ч)
} DeviceInf_TypeDef;
typedef struct
{
    uint8_t colorNum;                          // ��ɫ����
    DeviceInf_TypeDef device[Static_ColorNum]; // ��̬��Ч����ɫ��Ϣ
} EfColorInf_TypeDef;
/******************************************************************************************************/
// /********************��̬��Ч����********************/
// typedef struct
// {
//     uint16_t colorNum;                          // ��ɫ����
//     RGBWInf_TypeDef Efcolor[Dynamic_ColorNum]; // ��̬��Ч����ɫ��Ϣ
// } DynamicEfInf_TypeDef;
/******************************************************************************************************/
typedef struct
{
    uint8_t Brightness1;               /* ����1 */
    uint8_t Brightness2;               /* ����2 */
    EffectType_Enum EffectType;        /* ��Ч���� */
    MotionType_Enum MotionType;        /* �������� */
    MoveInf_Enum MoveInf;              /* �˶����� */
    MotionInf_TypeDef MotionInf;       /* ��̬Ч�� */
    EfColorInf_TypeDef StaticEfInf;   /* ��ɫ������ */
} Efdata_TypeDef;
#pragma pack(pop)
#endif
