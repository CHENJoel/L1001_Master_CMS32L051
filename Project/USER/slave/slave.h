#ifndef _SLAVE_H
#define _SLAVE_H
#include "Function_Init.H"
#include "ProtocolCom.H"

#define SLAVEDEVICE_NUM 32 // 最大支持的从机设备数量

extern uint8_t connect_id; // 当前握手ID

typedef enum
{
    ANSWER_EMPTY, // 无应答
    ANSWER_WRONG, // 错误应答
    ANSWER_RIGHT, // 正确应答
} answer_status;  // 应答状态

typedef enum
{
    TRIANGLE_L,         // 大三角形
    TRIANGLE_M,         // 中三角形
    TRIANGLE_S,         // 小三角形
    SQUARE,             // 正方形
    OTHER_SHAPE = 0xFF, // 其他形状
} device_shape_enum;


typedef struct
{
    uint8_t id;              // 灯板id
    device_shape_enum shape; // 形状
    uint16_t angle;          // 角度
    uint16_t cooed_x;        // x坐标
    uint16_t cooed_y;        // y坐标
    uint8_t runnum;          // 运行顺序编号（存储值无实际作用）
} device_detail_TypeDef;     // 设备详情

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
uint8_t refresh_slave_data(device_detail_TypeDef *p);
/*更新设备颜色*/
uint8_t refresh_device_color(color_TypeDef *p, uint8_t id);


/*************************************/

typedef enum
{
    PACK_EMPTY,   // 空数据包
    PACK_WRONG,   // 错误数据包
    PACK_RIGHT,   // 正确数据包
} cmdpack_status; // 指令数据包状态

/*串口发出数据串*/
void tx_uart_data(uint8_t *data, uint16_t len);
/*握手连接从机设备*/
void connect_slave_device(uint8_t id);
/*要求更新所有从机的通讯id*/
void refresh_slave_comid(void);
/*请求从机的形状信息*/
void ask_slave_shape(uint8_t id);
/*在fifo解析出从机的应答信号*/
cmdpack_status get_slave_ack_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t *pw, comCmd_Typedef *pack);
/*轮询出在线的从机设备*/
void poll_slave_id(void);
/*获取从机的形状信息*/
void get_slave_shape(void);
/*获取从机位置信息*/
void get_slave_place(void);
/*初始化在线的从机信息*/
void slave_online_data_init(void);



/*轮流点亮从机*/
void slave_light_in_turn(void);
/*
 * @Description: 仅点亮其中一个灯
 * @param:
 * @return:
*/
void light_up_only_one_slave(uint8_t id);

/********/

void slave_answer_parse(uint8_t *p, uint16_t len);//从机应答解析


#endif
