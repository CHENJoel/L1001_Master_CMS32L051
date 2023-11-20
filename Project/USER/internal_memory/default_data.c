#include "Function_Init.H"
#include "default_data.h"
#define endingcolor 255, 255, 255, 255, // 结束颜色标志，用于判断当前为最后一个颜色
const df_data_TypeDef dfdata[built_in_ef_num] =
{
    {"Reading",     (p_arry)df_White_4000K,  STATIC_TYPE, FLOW_STATIC },/*0*/
    {"Working",     (p_arry)df_White_3500K,  STATIC_TYPE, FLOW_STATIC },/*1*/
    {"3000K",       (p_arry)df_White_3000K,  STATIC_TYPE, FLOW_STATIC },/*2*/
    {"Night light", (p_arry)df_White_2700K,  STATIC_TYPE, FLOW_STATIC },/*3*/
    {"vitality",    (p_arry)df_Vitality,     STATIC_TYPE, FLOW_STATIC },/*4*/
    {"Spring",      (p_arry)df_Spring,       STATIC_TYPE, FLOW_STATIC },/*5*/
    {"Summer",      (p_arry)df_Summer,       STATIC_TYPE, FLOW_STATIC },/*6*/
    {"Autumn",      (p_arry)df_Autumn,       STATIC_TYPE, FLOW_STATIC },/*7*/
    {"Winter",      (p_arry)df_Winter,       STATIC_TYPE, FLOW_STATIC },/*8*/
    {"Cyberpunk",   (p_arry)df_Cyberpunk,    STATIC_TYPE, FLOW_STATIC },/*9*/

    {"Deep Breath", (p_arry)df_Deep_Breath,  DYNAMIC_TYPE,FLOW_BREATH },/*10*/
    {"Sweet",       (p_arry)df_Sweet,        DYNAMIC_TYPE,FLOW_BREATH },/*11*/
    {"Romantic",    (p_arry)df_Romantic,     DYNAMIC_TYPE,FLOW_STREAM },/*12*/
    {"Aurora",      (p_arry)df_Aurora,       DYNAMIC_TYPE,FLOW_REVERB },/*13*/
    {"Ocean",       (p_arry)df_Ocean,        DYNAMIC_TYPE,FLOW_REVERB },/*14*/
    {"lightning",   (p_arry)df_lightning,    DYNAMIC_TYPE,FLOW_LIGHTN },/*15*/
    {"fireworks",   (p_arry)df_fireworks,    DYNAMIC_TYPE,FLOW_IGNITE },/*16*/
    {"Snake",       (p_arry)df_Snake,        DYNAMIC_TYPE,FLOW_STREAM },/*17*/
    {"Bouncy ball", (p_arry)df_BouncyBall,   DYNAMIC_TYPE,FLOW_REVERB },/*18*/
    {"Lightsaber",  (p_arry)df_Lightsaber,   DYNAMIC_TYPE,FLOW_IGNITE },/*19*/
    {"Thanksgiving",(p_arry)df_Thanksgiving, DYNAMIC_TYPE,FLOW_REVERB },/*20*/
    {"Halloween",   (p_arry)df_Halloween,    DYNAMIC_TYPE,FLOW_IGNITE },/*21*/
    {"Christmas",   (p_arry)df_Christmas,    DYNAMIC_TYPE,FLOW_HOPSCO },/*22*/
    {"Colorful",    (p_arry)df_Colorful,     DYNAMIC_TYPE,FLOW_RANDOM },/*23*/
    {"Kaleidoscope",(p_arry)df_Kaleidoscope, DYNAMIC_TYPE,FLOW_RANDOM },/*24*/

    {"Rhythm",      (p_arry)df_Rhythm,       RHYTHM_TYPE,FLOW_RANDOM },/*25*/
    {"Meditation",  (p_arry)df_Meditation,   RHYTHM_TYPE,FLOW_BREATH },/*26*/
    {"GamingTime",  (p_arry)df_GamingTime,   RHYTHM_TYPE,FLOW_LIGHTN },/*27*/
    {"Disco",       (p_arry)df_Disco,        RHYTHM_TYPE,FLOW_REVERB },/*28*/
    {"Dance Party",  (p_arry)df_DanceParty,  RHYTHM_TYPE,FLOW_RANDOM },/*29*/
};
// const uint8_t df_playlist[15] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
const uint8_t df_playlist[30] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
const uint8_t df_testcolor1[][4] = {
    {0, 255, 0, 0},
    {endingcolor},
};
const uint8_t df_testcolor2[][4] = {
    {0, 0, 255, 0},
    {endingcolor},
};
const uint8_t df_testcolor3[][4] = {
    {255, 0, 0, 0},
    {endingcolor},
};
const uint8_t df_testcolor4[][4] = {
    {0, 0, 255, 0}, // 蓝色
    {0, 255, 0, 0}, // 绿色
    {255, 0, 0, 0}, // 红色
    {endingcolor},
};
const uint8_t df_testcolor5[][4] = {
    {255, 0, 0, 0},   // 赤
    {255, 165, 0, 0}, // 橙
    {255, 255, 0, 0}, // 黄
    {0, 255, 0, 0},   // 绿
    {0, 127, 255, 0}, // 青
    {0, 0, 255, 0},   // 蓝
    {139, 0, 255, 0}, // 紫
    // {18, 0, 83, 0},   // 黛
    {endingcolor},
};

const uint8_t df_White_4000K[][4] = {
    {0x0F, 0xA0, 0, 1},
    {endingcolor},
};
const uint8_t df_White_3500K[][4] = {
    {0x0D, 0xAC, 0, 1},
    {endingcolor},
};
const uint8_t df_White_3000K[][4] = {
    {0x0B, 0xB8, 0, 1},
    {endingcolor},
};
const uint8_t df_White_2700K[][4] = {
    {0x0A, 0x8C, 0, 1},
    {endingcolor},
};
const uint8_t df_Vitality[][4] = {
    {255, 128, 0, 0}, // 橙色
    {endingcolor},
};
const uint8_t df_Spring[][4] = {
    {200, 255, 37, 0}, // 淡黄绿
    {endingcolor},
};
const uint8_t df_Summer[][4] = {
    {233, 71, 9, 0}, // 橙红
    {endingcolor},
};
const uint8_t df_Autumn[][4] = {
    {237, 175, 32, 0}, // 黄色
    {endingcolor},
};
const uint8_t df_Winter[][4] = {
    {87, 140, 188, 0}, // 蓝色
    {endingcolor},
};
const uint8_t df_Cyberpunk[][4] = {
    {37, 188, 255, 0}, // 浅蓝
    {23, 129, 232, 0}, // 蓝
    {146, 35, 255, 0}, // 紫
    {230, 45, 232, 0}, // 粉紫
    {255, 13, 192, 0}, // 紫红
    {endingcolor},
};
const uint8_t df_Deep_Breath[][4] = {
    {90, 167, 167, 0},  // 青
    {150, 215, 198, 0}, // 粉绿
    {186, 201, 74, 0},  // 嫩绿
    {108, 140, 191, 0}, // 蓝色
    {endingcolor},
};
const uint8_t df_Sweet[][4] = {
    {240, 218, 220, 0}, // 粉色
    {245, 150, 176, 0}, // 深粉
    {254, 225, 153, 0}, // 黄色
    {118, 214, 201, 0}, // 青色
    {133, 188, 218, 0}, // 蓝色
    {endingcolor},
};

const uint8_t df_Romantic[][4] = {
    {252, 172, 230, 0}, // 浅粉
    {253, 135, 221, 0}, // 粉色
    {250, 28, 195, 0},  // 深粉色
    {238, 0, 242, 0},   // 浅紫红
    {112, 0, 240, 0},   // 浅紫色
    {60, 0, 169, 0},    // 蓝紫色
    {endingcolor},
};
const uint8_t df_Aurora[][4] = {
    {24, 16, 55, 0},    // 深紫色
    {57, 35, 97, 0},    // 紫色
    {113, 84, 174, 0},  // 浅紫
    {128, 156, 228, 0}, // 浅蓝紫
    {98, 191, 215, 0},  // 浅蓝
    {82, 209, 192, 0},  // 浅青
    {121, 246, 194, 0}, // 粉绿
    {4, 164, 94, 0},    // 绿色
    {endingcolor},
};

const uint8_t df_Ocean[][4] = {
    {241, 242, 237, 0}, // 灰白
    {128, 211, 215, 0}, // 浅蓝
    {113, 185, 223, 0}, // 蓝色
    {41, 15, 180, 0},   // 海蓝色
    {endingcolor},
};

const uint8_t df_lightning[][4] = {
    {246, 234, 246, 0}, // 白紫
    {72, 27, 137, 0},   // 紫色
    {endingcolor},
};
const uint8_t df_fireworks[][4] = {
    {247, 198, 166, 0}, // 橙色
    {247, 131, 137, 0}, // 红色
    {166, 58, 76, 0},   // 朱红
    {38, 38, 94, 0},    // 蓝紫
    {endingcolor},
};
const uint8_t df_Snake[][4] = {
    {236, 229, 126, 0}, // 黄
    {227, 135, 0, 0},   // 橙
    {83, 155, 87, 0},   // 绿
    {204, 48, 115, 0},  // 紫红
    {237, 229, 196, 0}, // 米白
    {92, 72, 148, 0},   // 紫色
    {endingcolor},
};
const uint8_t df_BouncyBall[][4] = {
    {122, 33, 158, 0},  // 紫色
    {0, 86, 214, 0},    // 蓝色
    {244, 164, 192, 0}, // 粉色
    {118, 87, 64, 0},   // 绿色
    {endingcolor},
};
const uint8_t df_Lightsaber[][4] = {
    {0, 255, 255, 0},   // 蓝
    {0, 255, 0, 0},     // 绿
    {255, 13, 192, 0},  // 紫
    {255, 0, 0, 0},     // 红
    {255, 255, 0, 0},   // 黄
    {227, 135, 0, 0},   // 橙
    {255, 255, 255, 0}, // 白
    {endingcolor},
};
const uint8_t df_Thanksgiving[][4] = {
    {254, 202, 120, 0}, // 淡橙色
    {248, 132, 27, 0},  // 橙色
    {227, 93, 34, 0},   // 橙红色
    {endingcolor},
};

const uint8_t df_Halloween[][4] = {
    {0, 0, 0, 0},       // 黑色
    {247, 103, 24, 0},  // 橙色
    {255, 255, 255, 0}, // 白色
    {endingcolor},
};
const uint8_t df_Christmas[][4] = {
    {25, 70, 31, 0},   // 绿色
    {255, 176, 87, 0}, // 橙色
    {230, 70, 37, 0},  // 橙红
    {154, 5, 2, 0},    // 红色
    {endingcolor},
};
const uint8_t df_Colorful[][4] = {
    {255, 0, 0, 0},   // 赤
    {255, 165, 0, 0}, // 橙
    {255, 255, 0, 0}, // 黄
    {0, 255, 0, 0},   // 绿
    {0, 127, 255, 0}, // 青
    {0, 0, 255, 0},   // 蓝
    {139, 0, 255, 0}, // 紫
    {18, 0, 83, 0},   // 黛
    {endingcolor},
};
const uint8_t df_Kaleidoscope[][4] = {
    {249, 255, 12, 0},  // 黄
    {252, 74, 8, 0},    // 橙
    {226, 0, 57, 0},    // 红
    {57, 0, 123, 0},    // 紫
    {124, 140, 216, 0}, // 浅紫
    {15, 121, 143, 0},  // 青
    {16, 123, 2, 0},    // 深绿
    {137, 218, 7, 0},   // 浅绿
    {endingcolor},
};
const uint8_t df_Rhythm[][4] = {
    {249, 255, 12, 0},  // 黄
    {252, 74, 8, 0},    // 橙
    {226, 0, 57, 0},    // 红
    {57, 0, 123, 0},    // 紫
    {124, 140, 216, 0}, // 浅紫
    {15, 121, 143, 0},  // 青
    {16, 123, 2, 0},    // 深绿
    {137, 218, 7, 0},   // 浅绿
    {endingcolor},
};
const uint8_t df_Meditation[][4] = {
    {0, 64, 128, 0},    // 海军蓝
    {0, 217, 217, 0},   // 蓝绿色
    {232, 183, 212, 0}, // 柔粉
    {endingcolor},
};
const uint8_t df_GamingTime[][4] = {
    {37, 188, 255, 0}, // 浅蓝
    {23, 129, 232, 0}, // 蓝
    {146, 35, 255, 0}, // 紫
    {230, 45, 232, 0}, // 粉紫
    {255, 13, 192, 0}, // 紫红
    {endingcolor},
};
const uint8_t df_Disco[][4] = {
    {0, 0, 255, 0}, // 蓝色
    {0, 255, 0, 0}, // 绿色
    {255, 0, 0, 0}, // 红色
    {endingcolor},
};
const uint8_t df_DanceParty[][4] = {
    {255, 0, 0, 0},   // 赤
    {255, 165, 0, 0}, // 橙
    {255, 255, 0, 0}, // 黄
    {0, 255, 0, 0},   // 绿
    {0, 127, 255, 0}, // 青
    {0, 0, 255, 0},   // 蓝
    {139, 0, 255, 0}, // 紫
    {18, 0, 83, 0},   // 黛
    {endingcolor},
};
/******************************************************************************/
const global_setting_TypeDef global_setting_default = {
    .autobright_ensta = DISABLE_STA,  // 自动亮度开关
    .autobrightType = Illumination,   // 自动亮度类型
    .indicator_sta = ENABLE_STA,      // 指示灯开关
    .microphone_ensta = DISABLE_STA,  // 麦克风开关
    .brightness_set = MAX_BRIGHTNESS, // 全局亮度存储值
};                                    // 全局设置初始值
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/******************************************************************************/
