/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-05-23 16:56:30
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
.chen sandote@163.om
 * .chen sandote@163.om
 * @LastEditTime: 2023-11-30 13:20:45
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\internal_memory\default_data.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#ifndef  DEFAULT_DATA_H
#define  DEFAULT_DATA_H
#include"Function_Init.H"

typedef uint8_t (*p_arry)[4]; // 二位颜色数组指针类型
typedef struct
{
    uint8_t *name;              /* 灯效名字 */
    p_arry data;                /* 灯效颜色指针*/
    EffectType_Enum EffectType; /* 灯效类型 */
    Flow_Enum Flow;             /* 动态效果 */
    uint8_t Brightness1;        /* 亮度1 初始亮度/律动的最低亮度 */
    uint8_t Speed;              /* 速度 */
    Direction_Enum Direction;   /* 运动方向 */
} df_data_TypeDef;              /*内置灯效信息*/
extern const uint8_t df_playlist[30];
// extern const uint8_t df_playlist[15];
extern const df_data_TypeDef dfdata[built_in_ef_num];

extern const uint8_t df_testcolor1[][4];
extern const uint8_t df_testcolor2[][4];
extern const uint8_t df_testcolor3[][4];
extern const uint8_t df_testcolor4[][4];
extern const uint8_t df_testcolor5[][4];

extern const uint8_t df_White_4000K[][4];
extern const uint8_t df_White_3500K[][4];
extern const uint8_t df_White_3000K[][4];
extern const uint8_t df_White_2700K[][4];
extern const uint8_t df_Vitality[][4];
extern const uint8_t df_Spring[][4];
extern const uint8_t df_Summer[][4];
extern const uint8_t df_Autumn[][4];
extern const uint8_t df_Winter[][4];
extern const uint8_t df_Cyberpunk[][4];
extern const uint8_t df_Deep_Breath[][4];
extern const uint8_t df_Sweet[][4];
extern const uint8_t df_Romantic[][4];
extern const uint8_t df_Aurora[][4];
extern const uint8_t df_Ocean[][4];
extern const uint8_t df_lightning[][4];
extern const uint8_t df_fireworks[][4];
extern const uint8_t df_Snake[][4];
extern const uint8_t df_BouncyBall[][4];
extern const uint8_t df_Lightsaber[][4];
extern const uint8_t df_Thanksgiving[][4];
extern const uint8_t df_Halloween[][4];
extern const uint8_t df_Christmas[][4];
extern const uint8_t df_Colorful[][4];
extern const uint8_t df_Kaleidoscope[][4];
extern const uint8_t df_Rhythm[][4];
extern const uint8_t df_Meditation[][4];
extern const uint8_t df_GamingTime[][4];
extern const uint8_t df_Disco[][4];
extern const uint8_t df_DanceParty[][4];



/*
*/
#endif
