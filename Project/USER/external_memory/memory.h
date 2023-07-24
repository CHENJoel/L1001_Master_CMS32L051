#ifndef _MEMORY_H_
#define _MEMORY_H_
#include "Function_Init.H"
#include "Color.H"

#define EFFECT_FLASH_BASE   0x500200

#define Dynamic_SUM 3
#define Static_SUM 2
#define Rhythm_SUM 1

/*

                *** MEMORY MAP ***

         _______________________________
0x0000  |                               |
        |                               |
        |          BOOTLOADER           |   0x0000~0x4FFF
        |                               |   size:0x5000,20480 Byte
        |                               |
        |_______________________________|    ______________________________________________________________________________
0x5000  |                               |   |                                                                              |
        |                               |   |                                                                              |
        |                               |   |                                                                              |
        |                               |   |                                                                              |
        |                               |   |                                                                              |
        |              APP              |   | 0x5000~0xE7F0                                                                |
        |                               |   | size:0x97F0,38896 Byte                                                       |
        |                               |   |                                                                              |
        |                               |   |                                                                              |
        |                               |   |                                                                              |
        |_______________________________|   |----------------------                                                        |
0xE7F0  |          APP CHECKSUM         |   | 0xE7F0~0xE7FF size:0x0F,16 Byte (app + app checksum ,size:0x9800,38912 Byte )|
        |_______________________________|   |______________________________________________________________________________|
0xE800  |        PLAYLIST_SECTOR0       |   size:0x200,512 Byte
        | ______________________________|
0xEA00  |        PLAYLIST_SECTOR1       |   size:0x200,512 Byte
        |_______________________________|
0xEC00  |        PLAYLIST_SECTOR2       |   size:0x200,512 Byte
        |_______________________________|
0xEE00  |        SCHEDULE_SECTOR        |   size:0x200,512 Byte
        |_______________________________|
0xF000  |        EF_PARA_SECTOR         |   size:0x200,512 Byte
        |_______________________________|
0xF200  |        EF_IDDA_SECTOR         |   size:0x200,512 Byte
        |_______________________________|
0xF400  |        EF_COLOR_SECTOR0       |   size:0x200,512 Byte
        |_______________________________|
0xF600  |        EF_COLOR_SECTOR1       |   size:0x200,512 Byte
        |_______________________________|
0xF800  |        EF_COLOR_SECTOR2       |   size:0x200,512 Byte
        |_______________________________|
0xFA00  |        EF_COLOR_SECTOR3       |   size:0x200,512 Byte
        |_______________________________|
0xFC00  |        RESERVED_SECTOR0       |   size:0x200,512 Byte
        |_______________________________|
0xFE00  |        RESERVED_SECTOR1       |   size:0x200,512 Byte
0xFFFF  |_______________________________|   _________________________________________________________________________________
        0x10000



         *** EXTERN NOR_FLASH MAP ***

         _______________________________     _____________________________________________
0x0000  |                               |   |                                             |
        |                               |   |                                             |
        |            OTA APP            |   |                                             |
        |                               |   |             OTA APP PACK                    |
        |                               |   |             0x0000~0x97FF                   |
        |_______________________________|   |             size:0x9800,38912 Byte          |
0x97F0  |        PACK CHECKSUM          |   |                                             |
0x97FF  |_______________________________|   |_____________________________________________|
0x9800  |          DO NOT USE !         |     0x9800~0x9FFF size:0x800,2048 Byte
0x9FFF  |_______________________________|     ����4k���룬�����������˲�������
0xA000  |                               |
        |          RESERVED             |
        |                               |
        |                               |
        |_______________________________|

*/





/****************************************************************************************/
typedef struct
{
    uint32_t checksum;
    int8_t RESERVED[12];
} APP_CHECKSUM_TypeDef;

#define APP_CHECKSUM_ADDR 0xE7F0
#define APP_CHECKSUM ((APP_CHECKSUM_TypeDef *)APP_CHECKSUM_ADDR)

/****************************************************************************************/
/* ���������� 1.5K */
#define SECTOR_SIZE 512 // ������С
/********** Flash Sector0 **********/
typedef struct
{
} Sector0_data_TypeDef;
typedef struct
{
    Sector0_data_TypeDef data;
    int8_t RESERVED[512 - sizeof(Sector0_data_TypeDef)]; // �ռ䱣��
} UserData_Sector0_TypeDef;                              /* 0x500000~0x5001FF */
/********** Flash Sector1 **********/

typedef struct
{
} Sector1_data_TypeDef;

typedef struct
{
    Sector1_data_TypeDef data;
    int8_t RESERVED[512 - sizeof(Sector1_data_TypeDef)]; // �ռ䱣��
} UserData_Sector1_TypeDef;                              /* 0x500200~0x5003FF */

/********** Flash Sector2 **********/
#define OTA_FLAG 0xa1234567

typedef struct
{
    uint32_t ota_flag;      // ��0xa1234567"��Ϊ������־
    uint32_t ota_UID0_flag; // UID0��Ϊ������־
    uint32_t pack_checksum; // ��������У���
    uint32_t ota_checksum;  // ǰ���ߵ�У���
} ota_data_TypeDef;

typedef struct
{
    ota_data_TypeDef ota_data;
} Sector2_data_TypeDef;

typedef struct
{
    Sector2_data_TypeDef data;
    int8_t RESERVED[512 - sizeof(Sector2_data_TypeDef)]; // �ռ䱣��
} UserData_Sector2_TypeDef;                              /* 0x500400~0x5005FF */

#define UserData0_ADDR  0x500000
#define UserData1_ADDR  0x500200
#define UserData2_ADDR  0x500400

#define UserData0 ((UserData_Sector0_TypeDef *)UserData0_ADDR)
#define UserData1 ((UserData_Sector1_TypeDef *)UserData1_ADDR)
#define UserData2 ((UserData_Sector2_TypeDef *)UserData2_ADDR)

/****************************************************************************************/


#define EF_COLOR_MAXNUM 8 // ��Ч��ɫ����������̶�ֵ8����ģ�

#define ROM_SECTOR0_ADDR 0x500000
#define ROM_SECTOR1_ADDR 0x500200
#define ROM_SECTOR2_ADDR 0x500400

#define DATA_SECTOR0    ((ColorData_TypeDef *) ROM_SECTOR0_ADDR)
#define DATA_SECTOR1    ((ColorData_TypeDef *) ROM_SECTOR1_ADDR)
#define DATA_SECTOR2    ((ColorData_TypeDef *) ROM_SECTOR2_ADDR)


/*******************�´洢*****************************/

/*
0XE800
0XEA00
0xEC00EF_PARA_SECTOR_ADDR
0XEE00

0XF000

*/
#define PLAYLIST_SECTOR0_ADDR 0XE800      // �����б���Ϣ��ַ 0~7
#define PLAYLIST_SECTOR1_ADDR 0xEA00      // �����б���Ϣ��ַ 8~15
#define PLAYLIST_SECTOR2_ADDR 0XEC00      // �����б���Ϣ��ַ 16~19
#define SCHEDULE_SECTOR_ADDR 0xEE00       // ��ʱ�洢��ַ 0~63

#define EF_PARA_SECTOR_ADDR 0xF000 // 00~63 ��Ч�����洢��ַ
#define EF_IDDA_SECTOR_ADDR 0xF200 // 32~63 ��Ч�豸��ַ�洢��ַ

#define EF_COLOR_SECTOR0_ADDR 0xF400 // 32~39 ��Ч��ɫ�洢��ַ
#define EF_COLOR_SECTOR1_ADDR 0xF600 // 40~47 ��Ч��ɫ�洢��ַ

#define EF_COLOR_SECTOR2_ADDR 0xF800 // 48~55 ��Ч��ɫ�洢��ַ
#define EF_COLOR_SECTOR3_ADDR 0xFA00 // 56~63 ��Ч��ɫ�洢��ַ

#define USER_RESERVED_SECTOR0_ADDR 0xFC00 // �û���Ϣ�洢 �ռ䱣��
#define USER_RESERVED_SECTOR1_ADDR 0xFE00 // �û���Ϣ�洢 �ռ䱣��

#define USER_EF_SUM 60   // 0~59 ʵ��60�� + 4������Ԥ���ռ�
#define USER_LIST_SUM 20 // 0~19 ʵ��20�� + 4������Ԥ���ռ�

#define USER_EF_MAXNUM 59
#define USER_LIST_MAXNUM 19
/****************************************************************************************/
typedef enum
{
    TurnOn = 1, // ����
    TurnOFF,    // �ص�
    WakeUp,     // ����
    Sleep,      // ˯��
} action_TypeDef;
// typedef enum
// {
//     Mon = 1, // ��һ
//     Tue,     // �ܶ�
//     Wed,     // ����
//     Thu,     // ����
//     Fri,     // ����
//     Sat,     // ����
//     Sun,     // ����
// } week_TypeDef;

typedef struct
{
    action_TypeDef Action; // ����
    uint8_t Exection_Hou;  // ִ��ʱ��.Сʱ
    uint8_t Exection_Min;  // ִ��ʱ��.����
    uint8_t Duration;      // ִ���������ȵĳ���ʱ��.���� ���60min
    uint8_t Brightness;    // ��������
    uint8_t Repeat_Week;   // �ظ�ִ��.��
    uint8_t RESERVED[2];   // �ռ䱣��
} schedule_TypeDef;        // 8byte
/****************************************************************************************/
typedef struct
{
    schedule_TypeDef group[64]; // 64�鶨ʱ��
} schedule_memory_TypeDef;

typedef struct
{
    uint8_t play_mode;      // ����ģʽ bit0(loop play) bit1(shuffle play)
    uint8_t switch_hour;    // �л�ʱ�� ����
    uint8_t switch_min;     // �л�ʱ�� ��
    uint8_t list_sum;       // �����б� ��Ч����
    uint8_t list_table[60]; // �����б� ��Ч���
} playlist_TypeDef;         // 64byte

typedef struct
{
    playlist_TypeDef group[8]; // ÿ������8���б�
} playlist_memory_TypeDef;

/****************************************************************************************/
typedef struct
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
} RGBW_TypeDef;

typedef struct
{
    RGBW_TypeDef color[32]; // ÿ����Ч������16����ɫ
} color_group_TypeDef;
//typedef struct
//{
//    color_group_TypeDef group[8]; // 8���Ч����ɫ��Ϣ
//} ;             // �û����ݵ�����512Byte

typedef struct
{
    uint8_t id_data[16]; // ��̬��Ч������16���豸id��Ϣ
} id_group_TypeDef;
typedef struct
{
    id_group_TypeDef group[32]; // 32����̬��Ч���豸id��Ϣ ʵ����30�������౸��
} EF_ID_TypeDef;                // �û����ݵ�����512Byte

typedef struct
{
    uint8_t brightness;    // Ĭ������
    uint8_t color_sum;     // ɫ������ɫ���� ֵ0����õ�Чδ����
    Motion_TypeDef motion; // ��Ч���,��̬/����/����/����/����/����/��ȼ/��� 0~7
    Move_TypeDef move;     // �˶�������,����/����/����/����/���ܷ�ɢ/���Ļ�� 0~5
    MODE_TypeDef Mode;     // ��ͨ/�ɶ�
    uint8_t speed;         // �˶��ٶ�
    uint8_t RESERVED[2];   // �ռ䱣��
} EF_para_data_TypeDef;    // 8byte
typedef struct
{
    EF_para_data_TypeDef User_EF_Param[64]; // ��Ч�Ĳ���,ǰ30Ϊ���õ�Ч�Ĳ�������30Ϊ�Զ����Ч�Ĳ���,����Ϊ����
} UserEFparadata_TypeDef;

typedef struct
{
    color_group_TypeDef color_buffer;
    EF_para_data_TypeDef para_data;
} EF_BUFFER_TypeDef;
extern EF_BUFFER_TypeDef EF_Buffer;

/****************************************************************************************/

void Effect_DefaultParaData_Init(void);
void Effect_DefaultColorData_Init(void);
void Edit_SectorData(uint32_t sect_addr, uint16_t offset, uint8_t *data_p, uint16_t len); // �༭ROM FLASH������
// // void Edit_UserEF_Colordata(uint8_t num, uint8_t *sur_p, uint8_t len);

void Printf_EF_data(uint8_t num);
void Printf_Playlist_data(uint8_t num);
void Printf_Schedule_data(uint8_t num);
void Clear_EF_data(uint8_t num);  // ��Ч��Ϣ����
void Clear_Playlist(uint8_t num); // �����б�����
void Verify_EF_data(void);        // У���Ч��Ϣ�Ƿ�������ֵ��
void Verify_PlayList_data(void);  // У�鲥���б���Ϣ�Ƿ�������ֵ��

void Edit_UserEF_IDdata(uint8_t num, id_group_TypeDef *id_group);
void Read_UserEF_IDdata(uint8_t num, id_group_TypeDef *id_group);
void Edit_UserEF_Colordata(uint8_t num, color_group_TypeDef *colordata);
void Read_UserEF_Colordata(uint8_t num, color_group_TypeDef *colordata);
void Edit_UserEF_Paradata(uint8_t num, EF_para_data_TypeDef *paradata);
void Read_UserEF_Paradata(uint8_t num, EF_para_data_TypeDef *paradata);
void Edit_Playlist(uint8_t num, playlist_TypeDef *list_p);
void Read_Playlist(uint8_t num, playlist_TypeDef *list_p);
void Edit_Schedule(uint8_t num, schedule_TypeDef *p);
void Read_Schedule(uint8_t num, schedule_TypeDef *p);
/*********************************************************************/
// // // // // // typedef struct
// // // // // // {
// // // // // //     // // uint16_t ddfo[5];
// // // // // //     // RGBWTypeDef asgyd;
// // // // // // }Memory_TypeDef;

// // // // // // extern Memory_TypeDef SysMemory;


typedef struct
{
    uint8_t par0;
    uint8_t par1;
    uint8_t par2;
    uint8_t par3;
}EffctParameter_TypeDef;

typedef struct
{
    EffctParameter_TypeDef Dynamic_EffectPar[4];
    EffctParameter_TypeDef Static_EffectPar[4];
    EffctParameter_TypeDef Rhythm_EffectPar[4];
}Effct_Par_TypeDef;


#define Effct_Par   ((Effct_Par_TypeDef*)EFFECT_FLASH_BASE)


void Edit_SectorData(uint32_t sect_addr, uint16_t offset, uint8_t *data_p, uint16_t len);
void Memorydebug(void);

// void MemoryStruct_Read(void);
// void MemoryStruct_Write(void);
// void Memory_AutoUpdate(void);

// void Effect_DefaultParaData_Init(void);
// void Edit_UserEffect_ColorData(uint8_t num, uint8_t *sur_p, uint8_t len);
// void Edit_UserEffect_ParaData(uint8_t num,EffectData_TypeDef *paradata);
#endif
