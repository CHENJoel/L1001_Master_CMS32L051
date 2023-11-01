#ifndef __L0_H_
#define __L0_H_
// #include "Function_Init.H"
#include "stdint.h"
#define MAX_SLAVE_NUM 32   // 最大从机数量
#define MAX_PACKET_SIZE 512 // 数据包最大值
#define L0_DATAHEAD_SIZE (sizeof(L0_head_Typedef) + sizeof(L0_info_Typedef))   // 通用数据帧头尺寸


/*
<格式>
收包地址+指令+报文类型+数据段

*/

typedef enum/*设备地址*/
{
    ADDR_MASTER = 0x00, // 主机地址
                        // 1~254 为从机地址段
    ADDR_PUBLIC = 0xFF, // 广播地址
} DEV_ADDR_ENUM;

typedef enum /*指令类型*/
{
    /*------------------------------------------------------------------------------------------*/
    CMD_MASTER_ORIGIN = 0x10,

    /*------------------------------------------------------------------------------------------*/
    CMD_SLAVE_ORIGIN = 0x70,
    CMD_SLAVE_PLAY_RGB,        // 播放灯光 “RGBbr”格式
    CMD_SLAVE_PLAY_RGBW,       // 播放灯光 “RGBWbr”格式
    CMD_SLAVE_PLAY_PWM,        // 播放灯光 “PWM”格式
    CMD_SLAVE_CONNECT_COID,    // 握手通信ID
    CMD_SLAVE_REFRESH_COID,    // 更新通信ID
    CMD_SLAVE_RESET_COID,      // 恢复通信ID
    CMD_SLAVE_SET_COID,        // 设置通信ID
    CMD_SLAVE_GET_ID,          // 获取设备ID
    CMD_SLAVE_GET_SHAPE,       // 获取设备形状
    CMD_SLAVE_GET_CALIBRATION, // 获取校准数据
    CMD_SLAVE_SET_CALIBRATION, // 设置校准数据
    CMD_SLAVE_GET_PRE_CALIBRA, // 获取预设校准数据 暂无
    CMD_SLAVE_SET_PRE_CALIBRA, // 设置预设校准数据 暂无
    CMD_SLAVE_PLAY_COLOR,      // 播放灯光 “COLOR”格式
    /*------------------------------------------------------------------------------------------*/
    CMD_BOOT_ORIGIN = 0xD0,
    CMD_BOOT_GET_ROM,          // 获取ROM数据
    CMD_BOOT_GET_ROMSUM,       // 获取ROM校验和
    CMD_BOOT_ERASE_APP,        // 擦除全部APP区域.仅IAP模式下有效
    CMD_BOOT_REASE_ROM,        // 擦除指定ROM区域.仅IAP模式下有效
    CMD_BOOT_WRITE_ROM,        // 直接写入ROM区域
    CMD_BOOT_INSER_ROM,        // 数据插入ROM区域
    CMD_BOOT_GET_UID,          // 获取UID
    CMD_BOOT_GET_BOOT_VERSION, // 获取引导程序版本
    CMD_BOOT_GET_APP_VERSION,  // 获取应用程序版本
    CMD_BOOT_GOTO_IAP,         // 进入IAP模式
    CMD_BOOT_CONNECT,          // 建立连接
    CMD_BOOT_DISCONNECT,       // 断开连接
    CMD_BOOT_GOTO_APP,         // 跳转至APP
    CMD_BOOT_NVIC_RESET,       // 软件复位
    CMD_BOOT_RESET_DATA,       // 恢复出厂
    /*------------------------------------------------------------------------------------------*/
    CMD_GENERAL_ORIGIN = 0xF0,
    CMD_GENERAL_POWERTIME, // 获取开机次数
    /*------------------------------------------------------------------------------------------*/
} CMD_ENUM;
typedef enum /*报文类型*/
{
    MES_ASK, // 发出请求
    MES_ACK, // 应答请求
} MES_TYPE_ENUM;

#pragma pack(push, 1)
typedef struct
{
    DEV_ADDR_ENUM dev_adr; // 设备地址 8位
    CMD_ENUM cmd;          // 指令类型 8位
    MES_TYPE_ENUM type;    // 报文类型 8位
} L0_head_Typedef;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    uint32_t addr; // 地址
    uint16_t size; // 尺寸
} L0_info_Typedef;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    L0_head_Typedef head;          // 通用数据头
    L0_info_Typedef info;          // 数据区信息，缺省补0
    uint8_t data[MAX_PACKET_SIZE]; // 其他数据
} large_package_Typedef;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    L0_head_Typedef head; // 通用数据头
    L0_info_Typedef info; // 数据区信息，缺省补0
    uint8_t data[4];      // 其他数据
} small_package_Typedef;
#pragma pack(pop)



#include "boot.h"
/**************************************************************************************************/



/*
 * @Description: 底层指令解析
 * @param: 数据包源指针
 * @param: 数据包长度
 * @return: 无
*/
void boot_command_parse(uint8_t * p, uint16_t len);

/*
 * @Description: 返回16位数据
 * @param:源数据指针
 * @return:16位数据
*/
uint16_t read_16bit_data(uint8_t *sur);

/*
 * @Description: 返回32位数据
 * @param:源数据指针
 * @return:32位数据
*/
uint32_t read_32bit_data(uint8_t *sur);

/*
 * @Description: 在地址写入16位数据
 * @param:源数据指针
 * @return:16位数据
 */
void write_16bit_data(uint8_t *tar, uint16_t data);

/*
 * @Description: 在地址写入32位数据
 * @param:源数据指针
 * @return:32位数据
 */
void write_32bit_data(uint8_t *tar, uint32_t data);
#endif
