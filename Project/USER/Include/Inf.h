#ifndef INF_H
#define INF_H
#include "Function_Init.H"
#pragma pack(push, 1) // 结构体按1字节对齐

#define Dynamic_ColorNum 32 // 动态灯效的最大颜色数量
#define Static_ColorNum 32  // 静态态灯效的最大颜色数量

typedef struct
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
} RGBWInf_TypeDef;

typedef enum /*动态效果*/
{
    MOT_STATIC,   // Static 静态
    MOT_BREATH,   // Breath 呼吸
    MOT_STREAM,   // Stream 流动
    MOT_REVERB,   // Reverberate 来回
    MOT_HOPSCO,   // Hopscotch 跳动
    MOT_LIGHTN,   // Lightning 闪电
    MOT_IGNITE,   // Ignite 点燃
    MOT_RANDOM,   // Random 随机
}MotionInf_TypeDef; //

typedef enum /*运动方向*/
{
    MOV_UP,       // 向上移动
    MOV_DOWN,     // 向下移动
    MOV_LEFT,     // 向左移动
    MOV_RIGHT,    // 向右移动
    MOV_SEPARATE, // 四周发散
    MOV_CONVERGE, // 中心汇聚
} MoveInf_Enum;

typedef enum /*动作类型*/
{
    STATIC_TYPE,  // 静态
    DYNAMIC_TYPE, // 动态
    RHYTHM_TYPE,  // 律动
} MotionType_Enum;

typedef enum /*灯效类型*/
{
    ORIGIN,    // 原始
    FAVORITES, // 收藏
    OTHER,     // 其他
} EffectType_Enum;

/********************静态灯效数据********************/
typedef struct
{
    uint8_t id;           // 灯板id(静态灯效)/|数据无效(动态灯效)
    RGBWInf_TypeDef color; // 灯板对应的静态颜色(静态灯效)|颜色组(动态灯效)
} DeviceInf_TypeDef;
typedef struct
{
    uint8_t colorNum;                          // 颜色数量
    DeviceInf_TypeDef device[Static_ColorNum]; // 静态灯效的颜色信息
} EfColorInf_TypeDef;
/******************************************************************************************************/
// /********************静态灯效数据********************/
// typedef struct
// {
//     uint16_t colorNum;                          // 颜色数量
//     RGBWInf_TypeDef Efcolor[Dynamic_ColorNum]; // 动态灯效的颜色信息
// } DynamicEfInf_TypeDef;
/******************************************************************************************************/
typedef struct
{
    uint8_t Brightness1;               /* 亮度1 */
    uint8_t Brightness2;               /* 亮度2 */
    EffectType_Enum EffectType;        /* 灯效类型 */
    MotionType_Enum MotionType;        /* 动作类型 */
    MoveInf_Enum MoveInf;              /* 运动方向 */
    MotionInf_TypeDef MotionInf;       /* 动态效果 */
    EfColorInf_TypeDef StaticEfInf;   /* 颜色数据区 */
} Efdata_TypeDef;
#pragma pack(pop)
#endif
