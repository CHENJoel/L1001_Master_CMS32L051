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
0x9FFF  |_______________________________|     用于4k对齐，块擦除会擦掉此部分数据
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
/* 数据闪存区 1.5K */
#define SECTOR_SIZE 512 // 扇区大小
/********** Flash Sector0 **********/
typedef struct
{
} Sector0_data_TypeDef;
typedef struct
{
    Sector0_data_TypeDef data;
    int8_t RESERVED[512 - sizeof(Sector0_data_TypeDef)]; // 空间保留
} UserData_Sector0_TypeDef;                              /* 0x500000~0x5001FF */
/********** Flash Sector1 **********/

typedef struct
{
} Sector1_data_TypeDef;

typedef struct
{
    Sector1_data_TypeDef data;
    int8_t RESERVED[512 - sizeof(Sector1_data_TypeDef)]; // 空间保留
} UserData_Sector1_TypeDef;                              /* 0x500200~0x5003FF */

/********** Flash Sector2 **********/
#define OTA_FLAG 0xa1234567

typedef struct
{
    uint32_t ota_flag;      // “0xa1234567"做为升级标志
    uint32_t ota_UID0_flag; // UID0作为升级标志
    uint32_t pack_checksum; // 升级包的校验和
    uint32_t ota_checksum;  // 前三者的校验和
} ota_data_TypeDef;

typedef struct
{
    ota_data_TypeDef ota_data;
} Sector2_data_TypeDef;

typedef struct
{
    Sector2_data_TypeDef data;
    int8_t RESERVED[512 - sizeof(Sector2_data_TypeDef)]; // 空间保留
} UserData_Sector2_TypeDef;                              /* 0x500400~0x5005FF */

#define UserData0_ADDR  0x500000
#define UserData1_ADDR  0x500200
#define UserData2_ADDR  0x500400

#define UserData0 ((UserData_Sector0_TypeDef *)UserData0_ADDR)
#define UserData1 ((UserData_Sector1_TypeDef *)UserData1_ADDR)
#define UserData2 ((UserData_Sector2_TypeDef *)UserData2_ADDR)

/****************************************************************************************/


#define EF_COLOR_MAXNUM 8 // 灯效颜色最大数量（固定值8，勿改）

#define ROM_SECTOR0_ADDR 0x500000
#define ROM_SECTOR1_ADDR 0x500200
#define ROM_SECTOR2_ADDR 0x500400

#define DATA_SECTOR0    ((ColorData_TypeDef *) ROM_SECTOR0_ADDR)
#define DATA_SECTOR1    ((ColorData_TypeDef *) ROM_SECTOR1_ADDR)
#define DATA_SECTOR2    ((ColorData_TypeDef *) ROM_SECTOR2_ADDR)


/*******************新存储*****************************/

/*
0XE800
0XEA00
0xEC00EF_PARA_SECTOR_ADDR
0XEE00

0XF000

*/
#define PLAYLIST_SECTOR0_ADDR 0XE800      // 播放列表信息地址 0~7
#define PLAYLIST_SECTOR1_ADDR 0xEA00      // 播放列表信息地址 8~15
#define PLAYLIST_SECTOR2_ADDR 0XEC00      // 播放列表信息地址 16~19
#define SCHEDULE_SECTOR_ADDR 0xEE00       // 定时存储地址 0~63

#define EF_PARA_SECTOR_ADDR 0xF000 // 00~63 灯效参数存储地址
#define EF_IDDA_SECTOR_ADDR 0xF200 // 32~63 灯效设备地址存储地址

#define EF_COLOR_SECTOR0_ADDR 0xF400 // 32~39 灯效颜色存储地址
#define EF_COLOR_SECTOR1_ADDR 0xF600 // 40~47 灯效颜色存储地址

#define EF_COLOR_SECTOR2_ADDR 0xF800 // 48~55 灯效颜色存储地址
#define EF_COLOR_SECTOR3_ADDR 0xFA00 // 56~63 灯效颜色存储地址

#define USER_RESERVED_SECTOR0_ADDR 0xFC00 // 用户信息存储 空间保留
#define USER_RESERVED_SECTOR1_ADDR 0xFE00 // 用户信息存储 空间保留

#define USER_EF_SUM 60   // 0~59 实用60个 + 4个备用预留空间
#define USER_LIST_SUM 20 // 0~19 实用20个 + 4个备用预留空间

#define USER_EF_MAXNUM 59
#define USER_LIST_MAXNUM 19
/****************************************************************************************/
typedef enum
{
    TurnOn = 1, // 开灯
    TurnOFF,    // 关灯
    WakeUp,     // 唤醒
    Sleep,      // 睡眠
} action_TypeDef;
// typedef enum
// {
//     Mon = 1, // 周一
//     Tue,     // 周二
//     Wed,     // 周三
//     Thu,     // 周四
//     Fri,     // 周五
//     Sat,     // 周六
//     Sun,     // 周日
// } week_TypeDef;

typedef struct
{
    action_TypeDef Action; // 动作
    uint8_t Exection_Hou;  // 执行时间.小时
    uint8_t Exection_Min;  // 执行时间.分钟
    uint8_t Duration;      // 执行最终亮度的持续时间.分钟 最大60min
    uint8_t Brightness;    // 最终亮度
    uint8_t Repeat_Week;   // 重复执行.周
    uint8_t RESERVED[2];   // 空间保留
} schedule_TypeDef;        // 8byte
/****************************************************************************************/
typedef struct
{
    schedule_TypeDef group[64]; // 64组定时表
} schedule_memory_TypeDef;

typedef struct
{
    uint8_t play_mode;      // 播放模式 bit0(loop play) bit1(shuffle play)
    uint8_t switch_hour;    // 切换时间 分钟
    uint8_t switch_min;     // 切换时间 秒
    uint8_t list_sum;       // 播放列表 灯效数量
    uint8_t list_table[60]; // 播放列表 灯效编号
} playlist_TypeDef;         // 64byte

typedef struct
{
    playlist_TypeDef group[8]; // 每扇区存8组列表
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
    RGBW_TypeDef color[32]; // 每个灯效最多包含16个颜色
} color_group_TypeDef;
//typedef struct
//{
//    color_group_TypeDef group[8]; // 8组灯效的颜色信息
//} ;             // 用户数据单扇区512Byte

typedef struct
{
    uint8_t id_data[16]; // 静态灯效最多包含16个设备id信息
} id_group_TypeDef;
typedef struct
{
    id_group_TypeDef group[32]; // 32个静态灯效的设备id信息 实际用30个，其余备用
} EF_ID_TypeDef;                // 用户数据单扇区512Byte

typedef struct
{
    uint8_t brightness;    // 默认亮度
    uint8_t color_sum;     // 色表中颜色数量 值0代表该灯效未启用
    Motion_TypeDef motion; // 动效编号,静态/呼吸/流动/来回/跳动/闪电/点燃/随机 0~7
    Move_TypeDef move;     // 运动方向编号,向上/向下/向左/向右/四周发散/中心汇聚 0~5
    MODE_TypeDef Mode;     // 普通/律动
    uint8_t speed;         // 运动速度
    uint8_t RESERVED[2];   // 空间保留
} EF_para_data_TypeDef;    // 8byte
typedef struct
{
    EF_para_data_TypeDef User_EF_Param[64]; // 灯效的参数,前30为内置灯效的参数，后30为自定义灯效的参数,其余为备用
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
void Edit_SectorData(uint32_t sect_addr, uint16_t offset, uint8_t *data_p, uint16_t len); // 编辑ROM FLASH的数据
// // void Edit_UserEF_Colordata(uint8_t num, uint8_t *sur_p, uint8_t len);

void Printf_EF_data(uint8_t num);
void Printf_Playlist_data(uint8_t num);
void Printf_Schedule_data(uint8_t num);
void Clear_EF_data(uint8_t num);  // 灯效信息清零
void Clear_Playlist(uint8_t num); // 播放列表清零
void Verify_EF_data(void);        // 校验灯效信息是否在正常值内
void Verify_PlayList_data(void);  // 校验播放列表信息是否在正常值内

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
