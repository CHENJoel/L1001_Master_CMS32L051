#ifndef INF_H
#define INF_H
#include "Function_Init.H"

#define MAX_BRIGHTNESS 100  // 最大亮度

#define EfColor_SizeNum 32    // 灯效的颜色容量（数量）
#define EfColor_miniSizeNum 8 // 灯效概述的颜色容量（数量）
#define Ef_SizeNum 256        // 灯效容量（数量），预留256
#define PlayList_efMaxNum 60   // 播放列表的索引数量
#define SCHEDULE_NUM 30       // 定时计划表数量
#define LIST_MAXNUM 13  // 列表最大个数

#define original_ef_basenum 128                      // 自定义灯效的基编号
#define original_ef_num 30                           // 自定义灯效数量
#define built_in_ef_basenum 0                        // 内置灯效的基编号
#define built_in_ef_num 30                           // 内置灯效数量
#define all_ef_num built_in_ef_num + original_ef_num // 全部灯效数量

#define default_ef_Speed 50
#define default_ef_Brightness1 50
#define default_ef_Brightness2 100
#define default_ef_MicSensitivity 100
#define default_ef_Attribute ORIGIN
#define default_ef_Direction DIRECTION_UP


typedef enum
{
    DISABLE_STA,      // 失能状态
    ENABLE_STA,       // 使能状态
} enable_status_enum; // 使能状态

/*********************************************/

typedef enum
{
    Illumination,      // 负反馈自动亮度.照明
    Ambient,           // 正反馈自动亮度.环境
} autobrightType_enum; // 自动亮度类型

typedef struct
{
    enable_status_enum autobright_ensta; // 自动亮度开关
    autobrightType_enum autobrightType;  // 自动亮度类型
    enable_status_enum indicator_sta;    // 指示灯开关
    enable_status_enum microphone_ensta; // 麦克风开关
    uint8_t brightness_set;              // 全局亮度存储值
    
} global_setting_TypeDef;

extern const global_setting_TypeDef global_setting_default;

typedef struct
{
    uint8_t hou_HM; // 小时
    uint8_t min_HM;  // 分钟
} time_HM_TypeDef;

typedef struct
{
    uint8_t min_MS; // 分钟
    uint8_t sec_MS; // 秒
} time_MS_TypeDef;

typedef struct
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
} RGBWInf_TypeDef;

typedef enum /*动态效果*/
{
    FLOW_STATIC, // Static 静态 0
    FLOW_BREATH, // Breath 呼吸 1
    FLOW_STREAM, // Stream 流动 2
    FLOW_REVERB, // Reverberate 来回 3
    FLOW_HOPSCO, // Hopscotch 跳动 4
    FLOW_LIGHTN, // Lightning 闪电 5
    FLOW_IGNITE, // Ignite 点燃 6
    FLOW_RANDOM, // Random 随机 7
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
    EMPTY,     // 空（删除）
} Attribute_Enum;

/******************************************************************************************************************/
#pragma pack(push, 1) // 结构体按1字节对齐
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

typedef struct
{
    uint8_t namelenght;            /* 名字字符数量 */
    uint8_t Name[15];              /* 灯效名字 */
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



/******************************************************************************************************************/
typedef struct
{
    Efdetail_TypeDef efdata[256]; // 内置灯效 索引号0~127     -自定义灯效 索引号128~255
} EffectInf_TypeDef;
/******************************************************************************************************************/
/******************************************************************/

typedef struct
{
    uint8_t length;   /* 字符数量 */
    uint8_t text[15]; /* 名字 */
} name_TypeDef;

typedef struct /*  */
{
    name_TypeDef name;               /* 名字*/
    time_MS_TypeDef DurationTime;    /* 持续时间 */
    uint8_t num;                     /* 灯效列表中有效数据的数量 */
    uint8_t list[PlayList_efMaxNum]; /* 灯效列表 */
} playdetail_TypeDef; /*播放列表详情*/

typedef struct
{
    playdetail_TypeDef pldata[256]; // 内置灯效 索引号0~127     -自定义灯效 索引号128~255
} PlayInf_TypeDef;  /*播放列表详情*/
/******************************************************************/

typedef struct /* 灯效的顺序表 */
{
    uint8_t num;       /* 灯效列表中有效数据的数量 */
    uint8_t list[60];  /* 灯效列表.存储灯效索引号 */
} ef_ranklist_TypeDef; /*存储区内空间分布*/

typedef struct /* 播放列表的顺序表 */
{
    uint8_t num;             /* 顺序列表中有效数据的数量 */
    uint8_t list[13];        /* 顺序列表.存储顺序表的索引号 */
} playlist_ranklist_TypeDef; /* 存储区内空间分布 */

/******************************************************************************************************************/
typedef struct
{
    ef_ranklist_TypeDef all_ef_ranklist;                     /* 全部灯效的顺序列表*/
    ef_ranklist_TypeDef original_ef_ranklist;                /* 自定义灯效的顺序列表*/
    ef_ranklist_TypeDef favorites_ef_ranklist;               /* 收藏灯效的顺序列表*/
    playlist_ranklist_TypeDef playlist_ranklist;             /* 播放列表的顺序列表*/
    // // playdetaillist_ranklist_TypeDef playdetaillist_ranklist; /* 播放详情的顺序列表*/
} ranklist_TypeDef;
/******************************************************************************************************************/
/*********************************************************/
/*定时表*/
typedef enum
{
    FUN_DISABLE, // 功能未启用
    FUN_ENABLE,  // 功能启用
} FUN_ENABLE_STA; // 启用状态

typedef enum /*  */
{
    TURN_OFF,
    TURN_ON,
} action_enum;

typedef union
{
    uint8_t week;
    struct
    {
        uint8_t Sun : 1; // 周日
        uint8_t Mon : 1; // 周一
        uint8_t Tue : 1; // 周二
        uint8_t Wed : 1; // 周三
        uint8_t Thu : 1; // 周四
        uint8_t Fri : 1; // 周五
        uint8_t Sat : 1; // 周六
    } day;
} repeat_TypeDef; // 重复时间

typedef struct /*  */
{
    name_TypeDef name;
    FUN_ENABLE_STA en_sta;      // 启用状态
    action_enum action;         // 动作类型
    uint8_t ef_index;           // 灯效索引
    uint8_t ultimatebright;     // 最终亮度
    time_HM_TypeDef actiontime; // 动作时间
    time_HM_TypeDef duration;   // 持续时间
    repeat_TypeDef repeat;      // 星期计划
} clock_detail_TypeDef;

/******************************************************************************************************************/
typedef struct /*  */
{
    uint8_t num;                      /* 有效数据的数量 */
    clock_detail_TypeDef list[SCHEDULE_NUM]; /* 定时信息 */
} clock_list_TypeDef;
/******************************************************************************************************************/

typedef struct /*  */
{
    uint8_t length;    // 数据长度
    uint8_t data[256]; // 仅供APP使用，嵌入式不使用
    /*
    【Type】：形状类型  长度1
    【角度】：正/负（1:正 0:负，长度1）+数字（长度1）   总长度2
    【x值】：  数字   总长度2
    【y值】：  数字   总长度2
    【id】：    长度1
*/
} device_indentify_TypeDef;



// // // // int8_t RESERVED[512 - sizeof(Sector0_data_TypeDef)]; // 空间保留

#pragma pack(pop)
#endif
