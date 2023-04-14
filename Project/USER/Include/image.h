/*
 * @Author: your name
 * @Date: 2022-03-25 13:48:26
 * @LastEditTime: 2022-06-14 15:08:46
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \A5441_CMS8S6990_Master\code\image.h
 */
#ifndef _IMAGE_H_
#define _IMAGE_H_
#include "Function_Init.H"
// #include "Color.H"
#define Red             {255,0,0,0}
#define LightRed        {255,50,0,0}
#define Orange          {255,100,0,0}
#define LightYellow     {255,170,0,0}
#define Yellow          {255,255,0,0}
#define LightGreen      {0 ,255,30,0}
#define Green           {0,255,0,0}
#define LightCyan       {0,255,80,0}
#define Cyan            {0,255,255,0}
#define LightBlue       {0,100,255,0}
#define Blue            {0,0,255,0}
#define Purple          {80,0,250,0}
#define LightPink       {255,0,255,0}
#define Pink            {255,0,100,0}

#define White           {0,0,0,255}
#define Black           {0,0,0,0}

// // // // #define Imgae_KF_Num       EffectData[E_Type][E_Color][0]  // 关键帧总数量 （1~255）
// // // // #define Frame_In_Num    EffectData[E_Type][E_Color][1]  // 插帧数（关键帧之间）
// // // // #define Frame_time          EffectData[E_Type][E_Color][2]  // 切帧时间/帧像周期
// // // // #define Frame_Play_Data     EffectData[E_Type][E_Color][3]  // 帧播放数据
// // // // #define Frame_Image_Num     EffectData[E_Type][E_Color][4]  // 当前分组的灯效数量
// // // // #define Frame_Play_Mode     EffectData[E_Type][E_Color][5]  // 帧播放模式
// // // // #define Frame_Pixel_Num     EffectData[E_Type][E_Color][6]  // 每帧包含的像素数量 1~255

// #define Imgae_KF_Num       EffectData[E_Type][E_Color][0]  // 关键帧总数量 （1~255）
// #define Frame_In_Num    EffectData[E_Type][E_Color][1]  // 插帧数（关键帧之间）
// #define Frame_time          EffectData[E_Type][E_Color][2]  // 切帧时间/帧像周期
// #define Frame_Play_Data     EffectData[E_Type][E_Color][3]  // 帧播放数据
// #define Frame_Image_Num     EffectData[E_Type][E_Color][4]  // 当前分组的灯效数量
// #define Frame_Play_Mode     EffectData[E_Type][E_Color][5]  // 帧播放模式
// #define Frame_Pixel_Num     EffectData[E_Type][E_Color][6]  // 每帧包含的像素数量 1~255

#define Imgae_KF_Num    EffectData[E_Type][E_Color][0]  // 关键帧总数量 （1~255）KeyFrames
#define Image_EF_Num    EffectData[E_Type][E_Color][1]  // 当前组别灯效数量
#define Frame_In_Num    EffectData[E_Type][E_Color][2]  // 自动补帧数量（关键帧之间）Insert Frames
#define Frame_Time_N    EffectData[E_Type][E_Color][3]  // 帧间隔（切帧时间）  Frames Time
#define Frame_Px_Num    EffectData[E_Type][E_Color][4]  // 单帧的像素数量 Pixel number
#define Image_Para_1    EffectData[E_Type][E_Color][5]  // 参数1 偏移量
#define Image_Para_2    EffectData[E_Type][E_Color][6]  // 参数2


#define FrameArry_Add       EffectAddress[E_Type][E_Color]  // 灯效的帧信息数组的基地址

#define Frame_All_Sum       (Imgae_KF_Num * (Frame_In_Num + 1))    // 该灯效的总帧数（加上插帧）
    // // uint16_t FrameSum;    // 灯效帧总数

#define FrameSum Image_Dynamic[EffextImage_num].KeyFrameSum *(Image_Dynamic[EffextImage_num].InsertNum + 1) // 灯效帧总数

// typedef enum
// {
//     MOD_
// }Play_Mode;

typedef struct image
{
    uint8_t *image_adr;   // 灯效图像数据指针
    uint8_t KeyFrameSum;  // 关键帧数量
    uint8_t PixelSum;     // 图像的像素数量
    uint8_t InsertNum;    // 自动补帧数量
    uint8_t IntervalTime; // 帧间隔时间
    uint8_t PlayMod;      // 播放模式
    uint8_t Para_1;       // 模式参数
} ImageTypeDef;

/* 新灯效 */
typedef enum
{
    MOTION_STATIC, // Static 静态
    MOTION_BREATH, // Breath 呼吸
    MOTION_STREAM, // Stream 流动
    MOTION_REVERB, // Reverberate 来回
    MOTION_HOPSCO, // Hopscotch 跳动
    MOTION_LIGHTN, // Lightning 闪电
    MOTION_IGNITE, // Ignite 点燃
    MOTION_RANDOM, // Random 随机
} Motion_TypeDef;

typedef enum
{
    MOVE_UP,       // 向上移动
    MOVE_DOWN,     // 向下移动
    MOVE_LEFT,     // 向左移动
    MOVE_RIGHT,    // 向右移动
    MOVE_SEPARATE, // 四周发散
    MOVE_CONVERGE, // 中心汇聚
} Move_TypeDef;

typedef enum
{
    MODE_NORMAL, // 普通模式
    MODE_RHYTHM, // 律动模式
} MODE_TypeDef;

#define arry(ary) ary
#define size(arry) sizeof(arry) / 4
#define time(t) t
#define insert(n) n
#define speed(n) n

typedef struct
{
    uint8_t *image_adr;   // 颜色数据
    uint8_t *addr_table;  // 地址表
    uint8_t KeySum;       // 关键帧数量
    uint16_t InsertNum;   // 自动补帧数量
    uint8_t IntervalTime; // 帧间隔时间
    uint8_t Speed;        // 速度/单次切帧数
    uint32_t FrameAmount; // 总帧数
    // // // // // // uint8_t PixelSum;     // 图像的像素数量 .待删
    MODE_TypeDef Mode;    // 普通/律动
} FrameInfro_TypeDef;     // 帧信息

typedef struct
{
    uint8_t EF_ID; // 灯效编号
    // // // // uint8_t flash_flag; // 灯效复位标志
    // // // // uint8_t Direction;           // 方向
    uint8_t Module_WorkNum;    // 用到的模组数    0~15
    Motion_TypeDef MotionType; // 灯效类型
    Move_TypeDef MoveType;     // 运动方向
    // // // // // // // // uint8_t *para_ptr;           // 灯效参数指针
    uint8_t Color_buffer[256][4]; // 色表缓存

    FrameInfro_TypeDef FrameInfro;
} Effect_TypeDef;

extern Effect_TypeDef EF_Work;

typedef struct
{
    // // uint8_t *addr_table;        // 地址表
    uint8_t *color_array;       // 色表
    uint8_t color_sum;          // 色表中颜色数量
    Motion_TypeDef motion_flag; // 动效编号
    Move_TypeDef move_flag;     // 运动方向编号
    MODE_TypeDef Mode;          // 普通/律动
    uint8_t Speed;
} EFdata_TypeDef;

//流动速度、初始亮度、灯效类型、运动方向、颜色组合 律动还有mic灵敏度
// // // // typedef struct
// // // // {
// // // //     // 颜色指针
// // // //     uint8_t bright;             // 亮度
// // // //     uint8_t speed;              // 速度
// // // //     Motion_TypeDef motion_flag; // 动效编号
// // // //     Move_TypeDef move_flag;     // 运动方向编号

// // // // } defaultdata_TypeDef;

extern ImageTypeDef img1;
extern const ImageTypeDef Image_Dynamic[100];
extern const ImageTypeDef Image_Static[20];

// extern unsigned char const Color_A0[2][4];

extern unsigned char *EffectAddress[][16];
extern unsigned char EffectData[][16][7];

extern const uint8_t Random_ColorTable[15][4];

extern unsigned char const PixelArrey_KeyFrame_A0[][4]; // 像素阵列的关键帧表

extern const unsigned char Rhythm_ColorTable[][4];
extern unsigned char Rhythm_ColorData[];

#endif
