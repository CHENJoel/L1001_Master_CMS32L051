#ifndef INF_H
#define INF_H
#include "Function_Init.H"

#pragma pack(push, 1) // 结构体按1字节对齐

#define EfColor_SizeNum 32 // 灯效的颜色容量（数量）
#define Ef_SizeNum 30      // 灯效容量（数量），预留256
#define PlayList_SizeNum Ef_SizeNum * 2

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
    DIRECTION_SEPARATE, // 四周发散
    DIRECTION_CONVERGE, // 中心汇聚
} Direction_Enum;

typedef enum /*灯效类型*/
{
    STATIC_TYPE,  // 静态
    DYNAMIC_TYPE, // 动态
    RHYTHM_TYPE,  // 律动
} EffectType_Enum;

typedef enum /*灯效属性*/
{
    ORIGIN,    // 原始
    FAVORITES, // 收藏
    OTHER,     // 其他，删除
} Attribute_Enum;

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
/******************************************************************************************************/

typedef struct
{
    uint8_t Name[30];              /* 灯效名字 */
    uint8_t Speed;                 /* 速度 */
    uint8_t Brightness1;           /* 亮度1 初始亮度/律动的最低亮度 */
    uint8_t Brightness2;           /* 亮度2 律动最高亮度*/
    uint8_t MicSensitivity;        /* 咪头灵敏度*/
    EffectType_Enum EffectType;    /* 灯效类型 */
    Attribute_Enum MotionType;     /* 灯效属性 */
    Direction_Enum Direction;      /* 运动方向 */
    Flow_Enum Flow;                /* 动态效果 */
    EfColorInf_TypeDef EfColorInf; /* 颜色数据区 */
} Efdata_TypeDef;

typedef struct
{
    Efdata_TypeDef Default_Efdata[Ef_SizeNum];  // 内置灯效 索引号0~127
    Efdata_TypeDef Original_Efdata[Ef_SizeNum]; // 自定义灯效 索引号128~256
} EffectInf_TypeDef;

/******************************************************************/

typedef struct /* 播放列表信息 */
{
    uint8_t Name[30];               /* 列表名字 */
    uint8_t Num;                    /* 灯效列表中有效数据的数量 */
    Time_TypeDef DurationTime;      /* 持续时间 */
    uint8_t List[PlayList_SizeNum]; /* 灯效列表 */
} PlayList_TypeDef;

/******************************************************************/

typedef struct /* 灯效的顺序表 */
{
    uint8_t Num;              /* 灯效列表中有效数据的数量 */
    uint8_t List[Ef_SizeNum]; /* 灯效列表.存储灯效索引号 */
} Ef_RankList_TypeDef;

typedef struct /* 播放列表的顺序表 */
{
    uint8_t Num;              /* 播放列表中有效数据的数量 */
    uint8_t List[Ef_SizeNum]; /* 播放列表.存储播放表的索引号 */
} PlayList_RankList_TypeDef;

typedef struct
{
    Ef_RankList_TypeDef Default_Ef_RankList;     /* 内置灯效的顺序列表*/
    Ef_RankList_TypeDef Original_Ef_RankList;    /* 自定义灯效的顺序列表*/
    Ef_RankList_TypeDef Favorites_Ef_RankList;   /* 收藏灯效的顺序列表*/
    PlayList_RankList_TypeDef PlayList_RankList; /* 播放列表的顺序列表*/
} List_TypeDef;
/*********************************************************/
/*定时表*/

typedef enum /* 播放列表信息 */
{
    TURN_OFF,
    TURN_ON,
} Action_Enum;

typedef struct /* 播放列表信息 */
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
