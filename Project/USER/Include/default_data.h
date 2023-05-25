#ifndef  DEFAULT_DATA_H
#define  DEFAULT_DATA_H
#include"Function_Init.H"

typedef uint8_t (*p_arry)[4]; // ��λ��ɫ����ָ������
typedef struct
{
    uint8_t *name;              /* ��Ч���� */
    p_arry data;                /* ��Ч��ɫָ��*/
    EffectType_Enum EffectType; /* ��Ч���� */
    Flow_Enum Flow;             /* ��̬Ч�� */
} df_data_TypeDef; /*���õ�Ч��Ϣ*/

#define built_in_ef_num 30 // ���õ�Ч����
extern df_data_TypeDef dfdata[built_in_ef_num];

extern const uint8_t df_testcolor1[][4];
extern const uint8_t df_testcolor2[][4];
extern const uint8_t df_testcolor3[][4];
extern const uint8_t df_testcolor4[][4];
extern const uint8_t df_testcolor5[][4];

extern const uint8_t df_White_4000K[][4];
extern const uint8_t df_White_3500K[][4];
extern const uint8_t df_White_3000K[][4];
extern const uint8_t df_White_2700K[][4];
extern const uint8_t df_Vitality[][4];
extern const uint8_t df_Spring[][4];
extern const uint8_t df_Summer[][4];
extern const uint8_t df_Autumn[][4];
extern const uint8_t df_Winter[][4];
extern const uint8_t df_Cyberpunk[][4];
extern const uint8_t df_Deep_Breath[][4];
extern const uint8_t df_Sweet[][4];
extern const uint8_t df_Romantic[][4];
extern const uint8_t df_Aurora[][4];
extern const uint8_t df_Ocean[][4];
extern const uint8_t df_lightning[][4];
extern const uint8_t df_fireworks[][4];
extern const uint8_t df_Snake[][4];
extern const uint8_t df_BouncyBall[][4];
extern const uint8_t df_Lightsaber[][4];
extern const uint8_t df_Thanksgiving[][4];
extern const uint8_t df_Halloween[][4];
extern const uint8_t df_Christmas[][4];
extern const uint8_t df_Colorful[][4];
extern const uint8_t df_Kaleidoscope[][4];
extern const uint8_t df_Rhythm[][4];
extern const uint8_t df_Meditation[][4];
extern const uint8_t df_GamingTime[][4];
extern const uint8_t df_Disco[][4];
extern const uint8_t df_DanceParty[][4];



// typedef struct
// {
//     uint8_t Name[16];              /* ��Ч���� */
//     uint8_t Speed;                 /* �ٶ� */
//     uint8_t Brightness1;           /* ����1 ��ʼ����/�ɶ���������� */
//     uint8_t Brightness2;           /* ����2 �ɶ��������*/
//     uint8_t MicSensitivity;        /* ��ͷ������*/
//     EffectType_Enum EffectType;    /* ��Ч���� */
//     Attribute_Enum Attribute;      /* ��Ч���� */
//     Direction_Enum Direction;      /* �˶����� */
//     Flow_Enum Flow;                /* ��̬Ч�� */
//     EfColorInf_TypeDef EfColorInf; /* ��ɫ������ */
// } Efdetail_TypeDef; // ��Ч����
/*
*/
#endif
