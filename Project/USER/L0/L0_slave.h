
#ifndef _L0_SLAVE_H_
#define _L0_SLAVE_H_
#include "Function_Init.H"
// #include <stdlib.h>
#include "L0.H"
/**************************************************************************************************/

#pragma pack(push, 1)

typedef struct
{
    uint8_t cid; // 设备id
    uint8_t R;   // 红
    uint8_t G;   // 绿
    uint8_t B;   // 蓝
    uint8_t br;  // 亮度
} L0_playRGBbr_Typedef;

typedef struct
{
    uint8_t cid; // 设备id
    uint8_t R;   // 红
    uint8_t G;   // 绿
    uint8_t B;   // 蓝
    uint8_t W;   // 白
    uint8_t br;  // 亮度
} L0_playRGBWbr_Typedef;

typedef struct
{
    uint8_t cid;   // 设备id
    uint16_t pwmR; // 红
    uint16_t pwmG; // 绿
    uint16_t pwmB; // 蓝
    uint16_t pwmW; // 白
} L0_playPWM_Typedef;

typedef enum
{
    RGB_COLOR,         // rgb数据
    KELVIN_COLOR,      // 色温数据
} play_colortype_ENUM; // 颜色数据类型

typedef struct
{
    uint8_t cid; // 设备id
    play_colortype_ENUM type;
    uint8_t R;  // 红/色温值
    uint8_t G;  // 绿
    uint8_t B;  // 蓝
    uint8_t br; // 亮度
} L0_playCOLOR_Typedef;

typedef struct
{
    L0_head_Typedef head;                     // 通用数据头
    uint8_t playnum;                          // 播放数量
    L0_playRGBbr_Typedef dev[MAX_SLAVE_NUM]; // 播放详情
} L0_cmd_playRGBbr_Typedef;

typedef struct
{
    L0_head_Typedef head;                     // 通用数据头
    uint8_t playnum;                          // 播放数量
    L0_playRGBWbr_Typedef dev[MAX_SLAVE_NUM]; // 播放详情
} L0_cmd_playRGBWbr_Typedef;

typedef struct
{
    L0_head_Typedef head;                     // 通用数据头
    uint8_t playnum;                          // 播放数量
    L0_playPWM_Typedef dev[MAX_SLAVE_NUM]; // 播放详情
} L0_cmd_playPWM_Typedef;

typedef struct
{
    L0_head_Typedef head;                    // 通用数据头
    uint8_t playnum;                         // 播放数量
    L0_playCOLOR_Typedef dev[MAX_SLAVE_NUM]; // 播放详情
} L0_cmd_playCOLOR_Typedef;
#pragma pack(pop)

/**************************************************************************************************/
#pragma pack(push, 1)
typedef struct
{
    L0_head_Typedef head; // 通用数据头
    uint8_t gr_fine;      // 绿红微调
    uint8_t gb_fine;      // 绿蓝微调
    uint8_t gw_fine;      // 绿白微调
    uint8_t br_fine;     // 亮度微调
} L0_cmd_calibration_data_Typedef;
#pragma pack(pop)

/**************************************************************************************************/
#pragma pack(push, 1)
typedef struct
{
    L0_head_Typedef head; // 通用数据头
    uint8_t cid;
    uint8_t uid;
    uint8_t random[3];  // 随机数
} L0_cmd_id_data_Typedef;
#pragma pack(pop)
/**************************************************************************************************/
#pragma pack(push, 1)
typedef struct
{
    L0_head_Typedef head; // 通用数据头
    uint8_t data[10];
} L0_cmd_general_data_Typedef;
#pragma pack(pop)
/**************************************************************************************************/
/**************************************************************************************************/
#pragma pack(push, 1)
typedef struct
{
    L0_head_Typedef head; // 通用数据头
    uint8_t cid;
    uint8_t shape;        // 形状
    uint16_t adval;        // ad值
    uint8_t random[3];    // 随机数
} L0_cmd_shape_data_Typedef;
#pragma pack(pop)
/**************************************************************************************************/
/**************************************************************************************************/
#pragma pack(push, 1)
typedef struct
{
    L0_head_Typedef head; // 通用数据头
    uint32_t powertimes;  // 开机次数
    uint8_t random[3];    // 随机数
} L0_cmd_powertimes_Typedef;
#pragma pack(pop)
/**************************************************************************************************/
void slave_command_parse(uint8_t *p, uint16_t len);       // 从机指令解析
void Fun_SLAVE_PLAY_RGB(uint8_t *p, uint16_t len);        // 播放灯光
void Fun_SLAVE_PLAY_RGBW(uint8_t *p, uint16_t len);       // 播放灯光
void Fun_SLAVE_PLAY_PWM(uint8_t *p, uint16_t len);        // 播放灯光
void Fun_SLAVE_CONNECT_COID(uint8_t *p, uint16_t len);    // 握手通信ID
void Fun_SLAVE_REFRESH_COID(uint8_t *p, uint16_t len);    // 更新通信ID
void Fun_SLAVE_RESET_COID(uint8_t *p, uint16_t len);      // 恢复通信ID
void Fun_SLAVE_SET_COID(uint8_t *p, uint16_t len);        // 设置通信ID
void Fun_SLAVE_GET_ID(uint8_t *p, uint16_t len);          // 获取ID
void Fun_SLAVE_GET_SHAPE(uint8_t *p, uint16_t len);       // 获取形状
void Fun_SLAVE_GET_CALIBRATION(uint8_t *p, uint16_t len); // 获取校准数据
void Fun_SLAVE_SET_CALIBRATION(uint8_t *p, uint16_t len); // 获取校准数据
void Fun_SLAVE_PLAY_COLOR(uint8_t *p, uint16_t len);      // 播放灯光 “COLOR”格式
/**/
void general_command_parse(uint8_t *p, uint16_t len); // 通用指令解析
void Fun_GENERAL_POWERTIME(uint8_t *p, uint16_t len); // 获取开机次数
#endif
