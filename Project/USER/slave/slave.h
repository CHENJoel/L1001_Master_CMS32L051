#ifndef _SLAVE_H
#define _SLAVE_H
#include "Function_Init.H"

#define SLAVEDEVICE_NUM 32 // 最大支持的从机设备数量

typedef enum
{
    TRIANGLE_L, // 大三
    TRIANGLE_M, // 中三
    TRIANGLE_S, // 小三
    SQUARE,     // 方形
} device_type_enum;

typedef struct
{
    uint8_t id;            // 灯板id
    device_type_enum type; // 形状
    uint16_t angle;        // 角度
    uint16_t cooed_x;      // x坐标
    uint16_t cooed_y;      // y坐标
} device_detail_TypeDef;   // 设备详情

typedef struct
{
    uint8_t num;                    // 设备数量
    device_detail_TypeDef data[SLAVEDEVICE_NUM]; // 设备详情
} device_data_TypeDef;              // 设备信息

extern device_data_TypeDef slave;

typedef struct
{
    uint8_t brightness; // 亮度
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
} color_TypeDef;

typedef struct
{
    color_TypeDef color[SLAVEDEVICE_NUM];
} device_color_TypeDef;
extern device_color_TypeDef slavecolor;

typedef struct
{
    uint8_t control; //
} device_control_TypeDef; //
extern device_control_TypeDef slave_control;

/*生成虚拟灯板信息*/
void generate_virtual_device(void);
/*更新设备信息*/
uint8_t refresh_device_data(device_detail_TypeDef *p);
/*更新设备颜色*/
uint8_t refresh_device_color(color_TypeDef *p, uint8_t id);

#endif
