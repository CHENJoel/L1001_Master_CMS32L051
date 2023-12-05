#ifndef _COMAPP_H_
#define _COMAPP_H_
#include "Function_Init.H"
#include "slave.h"
// #include "play.h"
#pragma pack(push, 1)
// // // // // // // // // // // // // // typedef enum
// // // // // // // // // // // // // // {
// // // // // // // // // // // // // //     ONLY_BRIGHTNESS,   // 只调节亮度信息
// // // // // // // // // // // // // //     MODITIFY_EFFECT,   // 编辑整体灯效信息
// // // // // // // // // // // // // // } ef_bright_flag_enum; // 亮度调节标志
typedef struct
{
    uint8_t idex;             /* 索引 */
    Efdetail_TypeDef Efdata;  /* 灯效详情 */
    uint8_t checksum;         /* 校验和 */
} com_effect_detial_TypeDef;  // 灯效详情
#pragma pack(pop)
/*********************************************************************/
#pragma pack(push, 1)
typedef struct
{
    uint8_t index;                         
    uint8_t namelenght;                     /* 名字字符数量 */
    uint8_t Name[15];                       /* 灯效名字 */
    EffectType_Enum EffectType;             /* 灯效类型 */
    Attribute_Enum Attribute;               /* 灯效属性 */
    EfColorminiInf_TypeDef EfColormioniInf; /* 颜色数据区 */
} Efminidetail_TypeDef;                     // 灯效mini信息
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct
{
    uint8_t num;                    /* 灯效数量 */
    Efminidetail_TypeDef Efdata[4]; /* 概述 */
    uint8_t checksum;                    /* 校验和 */
} com_effect_sketch_TypeDef;        // 灯效概述
#pragma pack(pop)
/*********************************************************************/

#pragma pack(push, 1)
typedef struct /* 灯效的顺序表 */
{
    uint8_t num;         /* 灯效列表中有效数据的数量 */
    uint8_t list[100];   /* 灯效列表.存储灯效索引号 */
} comefranklist_TypeDef; /*存储区内空间分布*/
typedef struct
{
    comefranklist_TypeDef ranklist;
    uint8_t checksum;      /* 校验和 */
} com_ranklist_TypeDef; // 灯效顺序表
#pragma pack(pop)
/*********************************************************************/
#pragma pack(push, 1)

typedef struct
{
    uint8_t length;   /* 字符数量 */
    uint8_t text[15]; /* 名字 */
} comname_TypeDef;

typedef struct
{
    uint8_t index;             /*索引*/
    name_TypeDef name;         /*名字*/
} com_playlist_sketch_TypeDef; // 播放列表概述
typedef struct
{
    uint8_t sum;                          /* 数量 */
    com_playlist_sketch_TypeDef list[14]; /* 播放列表概述 */
    uint8_t checksum;                     /* 校验和 */
} com_playlist_TypeDef;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    uint8_t idex;              /* 索引 */
    playdetail_TypeDef pldata; /* 播放列表详情 */
    uint8_t checksum;          /* 校验和 */
} com_play_detial_TypeDef;     // 播放列表详情
#pragma pack(pop)
/*********************************************************************/
#pragma pack(push, 1)

typedef struct
{
    uint8_t efidex;             /* 索引 */
    uint8_t Brightness1;        /* 亮度1 初始亮度/律动的最低亮度 */
    uint8_t Brightness2;        /* 亮度2 律动最高亮度*/
} com_current_efbright_TypeDef; // 当前灯效亮度值

#pragma pack(pop)

/*********************************************************************/
typedef enum /*APP下发指令枚举*/
{
    ASK_EFSKETCH,                 // 请求效果概述
    ASK_EFDETAIL,                 // 请求效果详情
    DELETE_ORIGINAL_EF,           // 删除自定义灯效
    ADD_FAVORITES_EF,             // 加入收藏
    DELETE_FAVORITES_EF,          // 取消收藏
    ASK_ALLEFRANKLIST,            // 请求全部灯效的顺序表
    ASK_ORINGINAL_RANKLIST,       // 请求自定义灯效的顺序表
    ASK_FAVORITES_RANKLIST,       // 请求收藏灯效的顺序表
    ASK_PLAYLIST_RANKLIST,        // 请求曲目列表的顺序表
    ASK_EFFECT_RANKLIST,          // 请求灯效相关的顺序表(全部、自定义、收藏)
    ASK_PLAY_EFSKETCH,            // 请求效果概述
    REAERVE_CMD11,                // 保留
    DELETE_PLAYLIST_RANKLISTLIST, // 删除播放列表中某个详情表 不使用
    SWITCH_PLAYLIST,              // 切换播放列表
    ASK_PLAYDETAIL,               // 请求播放详情
    ASK_PLAYSTATUS,               // 请求播放状态
    DELETE_SCHEDULE,              // 删除定时计划
    ASK_SCHEDULE_DETAIL,          // 请求定时详情
    INTER_APPCONNTROL,            // 进入app控制
    EXIT_APPCONNTROL,             // 退出app控制
    ASK_SCHEDULE_SKETCH,          // 请求定时概述表
    PLAY_TEMP_EFFECT,             // 播放临时灯效
    RESET_BUILTIN_EF,             // 重置内置灯效
    DELETE_PLAYLIST,              // 删除播放列表
    ASK_DEVICE_DETAILS,           // 请求灯板信息
    ASK_DEVICE_IDENTIFY,          // 请求配对标识

} issue_cmd;
#pragma pack(push, 1)
typedef struct
{
    issue_cmd cmd;       // 指令
    uint8_t data[5];     // 数据
    uint8_t checksum;    // 校验和
} com_issue_cmd_TypeDef; // 下发指令
#pragma pack(pop)

typedef enum
{
    PLAY_STATUS,          // 播放/暂停
    PLAY_SWITCH,          // 上下曲切换
    EFFECT_INDEX,         // 效果索引
    PLAY_RANDOM_EN,       // 随机播放使能
    PLAY_LOOP_EN,         // 循环播放使能
    PLAYLIST_INDEX = 100, // 播放列表索引
} playcontrol_type_enum;  // 操作类型

#pragma pack(push, 1)
typedef struct
{
    playcontrol_type_enum type; // 操作类型
    uint8_t value;              // 操作值
    uint8_t checksum;           // 校验和
} com_play_control_TypeDef;
#pragma pack(pop)

#pragma pack(push, 1)

typedef struct
{
    uint8_t id;              // 灯板id
    app_shape_enum shape;    // 形状
    uint16_t angle;          // 角度
    uint16_t cooed_x;        // x坐标
    uint16_t cooed_y;        // y坐标
} com_device_detail_TypeDef; // 设备详情
typedef struct
{
    com_device_detail_TypeDef data[32];
} com_device_data_TypeDef;
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct
{
    uint8_t id;         // 灯板id
    uint8_t brightness; // 亮度
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
    uint8_t res;           // 保留
} com_devicecolor_TypeDef; // 设备详情

typedef struct
{
    uint8_t num; //
    com_devicecolor_TypeDef data[32];
    uint8_t checksum; // 校验和
} com_device_control_TypeDef;
#pragma pack(pop)

#pragma pack(push, 1)



typedef struct
{
    uint8_t index;
    FUN_ENABLE_STA en_sta;   // 启用状态
    action_enum action;      // 动作类型
    time_HM_TypeDef actiontime; // 动作时间
    repeat_TypeDef repeat;   // 星期计划
} com_schedule_sketch_TypeDef;

typedef struct
{
    uint8_t num;
    com_schedule_sketch_TypeDef list[30];
    uint8_t checksum; // 校验和
} com_schedule_sketchlist_TypeDef;

typedef struct /*  */
{
    uint8_t index;
    name_TypeDef name;
    FUN_ENABLE_STA en_sta;      // 启用状态
    action_enum action;         // 动作类型
    uint8_t ef_index;           // 灯效索引
    uint8_t ultimatebright;     // 最终亮度
    time_HM_TypeDef actiontime; // 动作时间
    time_HM_TypeDef duration;   // 持续时间
    repeat_TypeDef repeat;      // 星期计划
    uint8_t checksum;           // 校验和
} com_schedule_detail_TypeDef;

#pragma pack(pop)




#endif
