#ifndef _COMAPP_H_
#define _COMAPP_H_
#include "Function_Init.H"

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
} com_ef_ranklist_TypeDef; // ��Ч˳���
#pragma pack(pop)
/*********************************************************************/
typedef enum /*APP�·�ָ��ö��*/
{
    ASK_EFSKETCH,          // Ч������
    ASK_EFDETAIL,          // Ч������
    DELETE_EF,             // ɾ��Ч��
    ADD_FAVORITES,         // �����ղ�
    UNDO_FAVORITES,        // ȡ���ղ�
    ASK_ALLEFRANKLIST,     // ����ȫ����Ч��˳���
    ASK_ORINGINALRANKLIST, // �����Զ����Ч��˳���
    ASK_FAVORITESRANKLIST, // �����ղص�Ч��˳���
    ASK_PLAYLISTRANKLIST,  // ���󲥷��б���˳���
    ASK_EFFECTANKLIST,  // �����Ч��ص�˳���
} issue_cmd;
#pragma pack(push, 1)
typedef struct
{
    issue_cmd cmd;      // ָ��
    uint8_t data[5];     // ����
    uint8_t checksum;         // У���
} com_issue_cmd_TypeDef; // �·�ָ��
#pragma pack(pop)

#endif