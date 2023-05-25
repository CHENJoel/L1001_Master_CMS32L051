#ifndef INF_H
#define INF_H
#include "Function_Init.H"

#pragma pack(push, 1) // 结构体按1字节对齐

#define EfColor_SizeNum 32    // 灯效的颜色容量（数量）
#define EfColor_miniSizeNum 8 // 灯效概述的颜色容量（数量）
#define Ef_SizeNum 256        // 灯效容量（数量），预留256
#define PlayList_SizeNum Ef_SizeNum * 2

#define original_ef_basenum 128 // 自定义灯效的基编号
#define original_ef_num 30      // 自定义灯效数量
#define all_ef_num 60           // 全部灯效数量

#define built_in_ef_num (sizeof(dfdata) / sizeof(df_data_TypeDef)) // 内置灯效数量

#define default_ef_Speed 50
#define default_ef_Brightness1 50
#define default_ef_Brightness2 100
#define default_ef_MicSensitivity 100
#define default_ef_Attribute ORIGIN
#define default_ef_Direction DIRECTION_UP

typedef struct
{
    uint8_t Min; // 分钟
    uint8_t Sec; // 秒
} Time_TypeDef;

typedef struct
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
} RGBWInf_TypeDef;

typedef enum /*动态效果*/
{
    FLOW_STATIC, // Static 静态
    FLOW_BREATH, // Breath 呼吸
    FLOW_STREAM, // Stream 流动
    FLOW_REVERB, // Reverberate 来回
    FLOW_HOPSCO, // Hopscotch 跳动
    FLOW_LIGHTN, // Lightning 闪电
    FLOW_IGNITE, // Ignite 点燃
    FLOW_RANDOM, // Random 随机
} Flow_Enum;     //

typedef enum /*运动方向*/
{
    DIRECTION_UP,       // 向上移动
    DIRECTION_DOWN,     // 向下移动
    DIRECTION_LEFT,     // 向左移动
    DIRECTION_RIGHT,    // 向右移动
    DIRECTION_CONVERGE, // 中心汇聚
    DIRECTION_SEPARATE, // 四周发散
} Direction_Enum;

typedef enum /*灯效类型*/
{
    STATIC_TYPE,  // 静态
    DYNAMIC_TYPE, // 动态
    RHYTHM_TYPE,  // 律动
} EffectType_Enum;

typedef enum /*灯效属性*/
{
    ORIGIN,    // 原始（未收藏）
    FAVORITES, // 收藏
    EMPTY,     // 空
} Attribute_Enum;

/******************************************************************************************************************/
/********************灯效数据********************/
typedef struct
{
    uint8_t id;            // 灯板id(静态灯效)/|数据无效(动态灯效)
    RGBWInf_TypeDef color; // 灯板对应的静态颜色(静态灯效)|颜色组(动态灯效)
} ColorID_TypeDef;
typedef struct
{
    uint8_t colorNum;                         // 颜色数量
    ColorID_TypeDef ColorID[EfColor_SizeNum]; // 静态灯效的颜色信息
} EfColorInf_TypeDef;
typedef struct
{
    uint8_t colorNum;                         // 颜色数量
    ColorID_TypeDef ColorID[EfColor_miniSizeNum]; // 静态灯效的颜色信息
} EfColorminiInf_TypeDef;/*灯效概述/简易信息*/

#pragma pack(push, 1)
typedef struct
{
    uint8_t Name[16];              /* 灯效名字 */
    uint8_t Speed;                 /* 速度 */
    uint8_t Brightness1;           /* 亮度1 初始亮度/律动的最低亮度 */
    uint8_t Brightness2;           /* 亮度2 律动最高亮度*/
    uint8_t MicSensitivity;        /* 咪头灵敏度*/
    EffectType_Enum EffectType;    /* 灯效类型 */
    Attribute_Enum Attribute;      /* 灯效属性 */
    Direction_Enum Direction;      /* 运动方向 */
    Flow_Enum Flow;                /* 动态效果 */
    EfColorInf_TypeDef EfColorInf; /* 颜色数据区 */
} Efdetail_TypeDef; // 灯效详情
#pragma pack(pop)


/******************************************************************************************************************/
typedef struct
{
    // // // Efdetail_TypeDef Default_Efdata[128];  // 内置灯效 索引号0~127
    // // // Efdetail_TypeDef Original_Efdata[128]; // 自定义灯效 索引号128~255
    Efdetail_TypeDef efdata[256]; // 内置灯效 索引号0~127     -自定义灯效 索引号128~255
} EffectInf_TypeDef;
/******************************************************************************************************************/
/******************************************************************/

typedef struct /*  */
{
    uint8_t Name[32];               /* 列表名字 */
    uint8_t num;                    /* 灯效列表中有效数据的数量 */
    Time_TypeDef DurationTime;      /* 持续时间 */
    uint8_t list[PlayList_SizeNum]; /* 灯效列表 */
} PlayList_TypeDef;

/******************************************************************/

typedef struct /* 灯效的顺序表 */
{
    uint8_t num;             /* 灯效列表中有效数据的数量 */
    uint8_t list[60];       /* 灯效列表.存储灯效索引号 */
} ef_ranklist_TypeDef; /*存储区内空间分布*/

typedef struct /* 播放列表的顺序表 */
{
    uint8_t num;                   /* 顺序列表中有效数据的数量 */
    uint8_t list[60];             /* 顺序列表.存储播放表的索引号 */
} playList_ranklist_TypeDef; /*存储区内空间分布*/

/******************************************************************************************************************/
typedef struct
{
    ef_ranklist_TypeDef all_ef_ranklist;         /* 全部灯效的顺序列表*/
    ef_ranklist_TypeDef original_ef_ranklist;    /* 自定义灯效的顺序列表*/
    ef_ranklist_TypeDef favorites_ef_ranklist;   /* 收藏灯效的顺序列表*/
    playList_ranklist_TypeDef PlayList_ranklist; /* 播放列表的顺序列表*/
} ranklist_TypeDef;
/******************************************************************************************************************/
/*********************************************************/
/*定时表*/

typedef enum /*  */
{
    TURN_OFF,
    TURN_ON,
} Action_Enum;

typedef struct /*  */
{
    Action_Enum Action;        // 动作类型
    uint8_t Ef_id;             // 灯效的索引号
    uint8_t UltimateBright;    // 最终亮度
    Time_TypeDef ActionTime;   // 动作时间
    Time_TypeDef DurationTime; // 持续时间
    union
    {
        uint8_t Week;
        struct
        {
            uint8_t Mon : 1; // 周一
            uint8_t Tue : 1; // 周二
            uint8_t Wed : 1; // 周三
            uint8_t Thu : 1; // 周四
            uint8_t Fri : 1; // 周五
            uint8_t Sat : 1; // 周六
            uint8_t Sun : 1; // 周日
        } day;
    } RepeatTime; // 重复时间
} Routine_TypeDef;

/******************************************************************************************************************/
typedef struct /*  */
{
    uint8_t Num;              /* 有效数据的数量 */
    Routine_TypeDef list[30]; /* 定时信息 */
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
    //         uint8_t Illumination : 1; // 负反馈
    //         uint8_t Ambient : 1;      // 正反馈
    //     } day;
    // } AutoBrightness; // 自动亮度

    union
    {
        uint8_t byte;
        struct
        {
            uint8_t Illumination : 1; // 负反馈
            uint8_t Ambient : 1;      // 正反馈
            uint8_t StatusLED : 1;    // 指示灯
            uint8_t MicrophoneEn : 1; // 麦克风开关
        } bit;
    } enable; // 自动亮度
} GeneralSetting_TypeDef;

// // // // int8_t RESERVED[512 - sizeof(Sector0_data_TypeDef)]; // 空间保留

#pragma pack(pop)
#endif
