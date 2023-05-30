#ifndef _COMAPP_H_
#define _COMAPP_H_
#include "Function_Init.H"

#pragma pack(push, 1)
typedef struct
{
    uint8_t idex;            /* 索引 */
    Efdetail_TypeDef Efdata;   /* 灯效详情 */
    uint8_t checksum;             /* 校验和 */
} com_effect_detial_TypeDef; // 灯效详情
#pragma pack(pop)
/*********************************************************************/
#pragma pack(push, 1)
typedef struct
{
    uint8_t index;                          /*索引*/
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
} com_ef_ranklist_TypeDef; // 灯效顺序表
#pragma pack(pop)
/*********************************************************************/
typedef enum /*APP下发指令枚举*/
{
    ASK_EFSKETCH,          // 效果概述
    ASK_EFDETAIL,          // 效果详情
    DELETE_EF,             // 删除效果
    ADD_FAVORITES,         // 加入收藏
    UNDO_FAVORITES,        // 取消收藏
    ASK_ALLEFRANKLIST,     // 请求全部灯效的顺序表
    ASK_ORINGINALRANKLIST, // 请求自定义灯效的顺序表
    ASK_FAVORITESRANKLIST, // 请求收藏灯效的顺序表
    ASK_PLAYLISTRANKLIST,  // 请求播放列表的顺序表
    ASK_EFFECTANKLIST,  // 请求灯效相关的顺序表
} issue_cmd;
#pragma pack(push, 1)
typedef struct
{
    issue_cmd cmd;      // 指令
    uint8_t data[5];     // 数据
    uint8_t checksum;         // 校验和
} com_issue_cmd_TypeDef; // 下发指令
#pragma pack(pop)

#endif
