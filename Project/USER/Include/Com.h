/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-05-25 20:19:42
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-06-18 16:50:41
 * @FilePath: \A5441_Master_CMS32L051\Project\USER\Include\Com.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _COM_H_
#define _COM_H_
#include "Function_Init.H"

#define uchar unsigned char
#define uint  unsigned int

#define M_HeadCOM 0xAA
#define M_HeadCMD 0xAC
#define S_HeadCOM 0xBA

#define Public_Addr  0xFF    // 广播地址
#define Master_Addr  0xF0    // 主机地址


/* *************** */
#define APP_PROTOCOL_HEADER 0xA5
// #define APP_PROTOCOL_HEADER 0x55

enum /*APP端下发指令*/
{
    CHECK_LIGHT_MESSAGE = 0x20, // 查询灯组信息
    SET_LIGHT_COORDINATE,       // 设置灯组坐标
    CHECK_EFFECT_MESSAGE,       // 查询灯效信息
    SET_EFFECT_MESSAGE,         // 设置灯效信息
    SET_LIGHT_RIGHT_OWNER,      // 设置控灯权限拥有者
    SET_LIGHT_OUTPUT,           // 设置灯组输出颜色
    CHECK_PLAYLIST,             // 查询播放列表
    SET_PLAYLIST,               // 查询播放列表
    CHECK_SCHEDULE,             // 查询时间表
    SET_SCHEDULE,               // 设置时间表
    CHECK_PLAYSTATE,            // 查询播放状态
    SET_PLAYSTATE,              // 设置播放信息
};

enum /*MCU端上报指令*/
{
    REPORT_LIGHT_MESSAGE = 0x80, // 上报灯组信息
    REPORT_EFFECT_MESSAGE,       // 上报灯效信息
    REPORT_LIGHT_RIGHT_OWNER,    // 上报当前控灯权限拥有者
    REPORT_PLAYLIST,             // 上报播放列表
    REPORT_SCHEDULE,             // 上报时间表
    REPORT_PLAYSTATE,            // 上报播放状态
};

void Upload_LightMessage(void);                          // 上传灯组信息
void Download_LightCoord(uint8_t *sur, uint16_t len);    // 下载灯组坐标信息
void Upload_EffectMessage(uint8_t num);                  // 上传灯效信息
void Download_EffectMessage(uint8_t *sur, uint16_t len); // 下载灯效信息
void Upload_PlayList(uint8_t num);                       // 上传播放列表
void Download_PlayList(uint8_t *sur, uint16_t len);      // 下载播放列表
void Upload_Schedule(uint8_t num);                       // 上传定时任务
void Download_Schedule(uint8_t *sur, uint16_t len);      // 下载定时任务
void Upload_PlayingState(void);                          // 上报播放状态
void Download_PlayingState(uint8_t *sur, uint16_t len);  // 下载播放任务
/***************************************************************************/

// // // // // typedef enum
// // // // // {
// // // // //     M_CMD_Handshake_Chief = 0xD0,    // 主ID握手
// // // // //     M_CMD_Handshake_Minor = 0xD1,    // 副ID握手
// // // // //     M_CMD_Handshake_Commu = 0xD2,    // 通讯ID握手
// // // // //     M_CMD_Set_CommuID = 0xD3,        // 设置通讯ID (0x30~0x45)  控制单机 使用该ID
// // // // //     M_CMD_Buffer_Clear = 0xD4,       // 清空缓存
// // // // //     M_CMD_MinorID_Refresh = 0xD5,    // 副ID强制更新
// // // // //     M_CMD_MinorID_AllRefresh = 0xD6, // 全员副ID强制更新
// // // // //     M_CMD_Slave_DataReset = 0xD7,    // 从机恢复出厂设置
// // // // //     M_CMD_Check_Device_ID = 0xD8,    // 查询该设备ID信息
// // // // //     M_CMD_Set_SeriesNum = 0xD9,      // 设置序列ID (0x00~0x15) 流光顺序 参考该ID
// // // // //     M_CMD_Set_LightID = 0xDA,        // 设置灯光ID (0x00~0x15)  通用灯效 使用该ID
// // // // //     M_CMD_Check_Device_Data = 0xDB,  // 查询设备信息
// // // // //     M_CMD_Set_FixedID = 0xDC,        // 设置固定ID

// // // // // } MasterCommandType;

typedef enum
{
    M_CMD_Handshake_Chief = 0xD0,    // 主ID握手
    M_CMD_Handshake_Minor = 0xD1,    // 副ID握手
    M_CMD_Handshake_Commu = 0xD2,    // 通讯ID握手
    M_CMD_Set_CommuID = 0xD3,        // 设置通讯ID (0x30~0x45)  控制单机 使用该ID
    M_CMD_Buffer_Clear = 0xD4,       // 清空缓存
    M_CMD_MinorID_Refresh = 0xD5,    // 副ID强制更新C
    M_CMD_MinorID_AllRefresh = 0xD6, // 全员副ID强制更新
    M_CMD_Slave_DataReset = 0xD7,    // 从机恢复出厂设置
    M_CMD_Check_Device_ID = 0xD8,    // 查询该设备ID信息
    M_CMD_Set_SeriesNum = 0xD9,      // 设置序列ID (0x00~0x15) 流光顺序 参考该ID
    M_CMD_Set_LightID = 0xDA,        // 设置灯光ID (0x00~0x15)  通用灯效 使用该ID
    M_CMD_Check_Device_Data = 0xDB,  // 查询设备信息
    M_CMD_Set_FixedID = 0xDC,        // 设置固定ID

    M_CMD_ASK_Device_ID_DATA = 0xDD, // 询问设备ID信息
    M_CMD_Unlock_Slave = 0xDE,       // 解锁设备ID信息记忆区
    M_CMD_Lock_Slave = 0xDE,         // 上锁设备ID信息记忆区
    M_CMD_Set_Device_ID_DATA = 0xDF, // 设置设备ID信息
}
MasterCommandType;




typedef enum
{
    S_ChiefMinor_ID = 0xA0, // 从机主副ID
    S_Device_ID = 0xA1,     // 从机ID信息
    S_Device_Data = 0xA2,   // 从机设备信息
} SlaveCommandType;

typedef enum
{
    Package_Empty, // 空数据包
    Package_Wrong, // 错误数据包
    Package_Right, // 正确数据包
}PackageType;

typedef enum
{
    Master = 0x10,  // 主机
    Triangle_A1 = 0x80, // 大三1
    Triangle_A2 = 0x81, // 大三2
    Triangle_B1 = 0x90, // 中三1
    Triangle_C1 = 0xA0, // 小三1
    Triangle_C2 = 0xA1, // 小三2
    Triangle_C3 = 0xA2, // 小三3
    Triangle_C4 = 0xA3, // 小三4
    Square = 0xB0, // 方形3
} DeciceType;

#define Check_Device_Data(ChfID, MirID) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Check_Device_Data, ChfID, MirID, Random_Generate(), Random_Generate())
#define Check_Device_ID(ChfID, MirID) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Check_Device_ID, ChfID, MirID, Random_Generate(), Random_Generate())
#define Set_CommuID(ChfID, MirID, CommuID) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Set_CommuID, ChfID, MirID, CommuID, Random_Generate());
#define Set_SeriesNum(ChfID, MirID, SeriesNum) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Set_SeriesNum, ChfID, MirID, SeriesNum, Random_Generate())
#define Set_LightID(ChfID, MirID, LightID) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Set_LightID, ChfID, MirID, LightID, Random_Generate())






/**************************************** 新协议 ****************************************/
/*


VCC     GND
3K      18K     3511 大三
3K      7.5K    2926 中三
7.5K    3K      1170 小三
18K     3K      585  正方形


*/

#define TYPE_Triangle_L_REF 3511
#define TYPE_Triangle_M_REF 2926
#define TYPE_Triangle_S_REF 1170
#define TYPE_Square_REF 585

/* 误差范围取值±5% */
#define TYPE_Triangle_L_MAX 3689
#define TYPE_Triangle_L_MIN 3335
#define TYPE_Triangle_M_MAX 3072
#define TYPE_Triangle_M_MIN 2779
#define TYPE_Triangle_S_MAX 1229
#define TYPE_Triangle_S_MIN 1112
#define TYPE_Square_REF_MAX 614
#define TYPE_Square_REF_MIN 556

enum
{
    Triangle_L,         // 大三角形
    Triangle_M,         // 中三角形
    Triangle_S,         // 小三角形
    Square_Nor,         // 正方形
    OTHER_SHAPE = 0xFF, // 其他形状
};

typedef enum
{
    M_CMD_Check_ID = 0xE0, // 查询ID
    M_CMD_Refresh_ID,      // 强制更新ID
    M_CMD_Check_Coord,     // 查询从机坐标
    M_CMD_Set_Coord,       // 设置从机坐标
    M_CMD_Check_Angle,     // 查询从机角度
    M_CMD_Set_Angle,       // 设置从机角度
    M_CMD_ROM_PROTECT_ON,  // 开从机写保护
    M_CMD_ROM_PROTECT_OFF, // 关从机写保护
    M_CMD_WRITE_ROM,       // 写从机存储区
    M_CMD_READ_ROM,        // 读从机存储区
    M_CMD_DATA_RESET,      // 恢复出厂数据
} MasterCMDType;

typedef enum
{
    S_Return_ID = 0xB0, // 返回ID 信息
    S_RETURN_Coord,     // 返回从机坐标
    S_RETURN_Angle,     // 返回从机角度
    S_RETURN_ROM_DATA,  // 返回ROM数据
} SlaveCMDType;

/*————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/
/* 主机指令.查询此ID */
#define DataTx_Master_Check_ID(id) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Check_ID, id, Random_Generate(), Random_Generate(), Random_Generate())
/* 主机指令.要求从机更新ID */
#define DataTx_Refresh_ID() DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Refresh_ID, Random_Generate(), Random_Generate(), Random_Generate(), Random_Generate())

/* 主机指令.查询此机坐标 */
#define DataTx_Master_Check_Coord(id) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Check_Coord, id, Random_Generate(), Random_Generate(), Random_Generate())
/* 主机指令.设置此机坐标 */
#define DataTx_Master_Set_Coord(id, x, y) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Set_Coord, id, x, y, Random_Generate())

/* 主机指令.查询此机角度 */
#define DataTx_Master_Check_Angle(id) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Check_Angle, id, Random_Generate(), Random_Generate(), Random_Generate())
/* 主机指令.设置此机角度 */
#define DataTx_Master_Set_Angle(id, angle) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Set_Angle, id, angle, Random_Generate(), Random_Generate())

/* 主机指令.开从机存储写保护 */
#define DataTx_Master_Protect_ON(id) DataPackage_TX(M_HeadCMD, id, M_CMD_ROM_PROTECT_ON, Random_Generate(), Random_Generate(), Random_Generate(), Random_Generate())
/* 主机指令.关从机存储写保护 */
#define DataTx_Master_Protect_OFF(id) DataPackage_TX(M_HeadCMD, id, M_CMD_ROM_PROTECT_OFF, Random_Generate(), Random_Generate(), Random_Generate(), Random_Generate())

/* 主机指令.写从机存储区 */
#define DataTx_Master_Write_ROM(id, addr_H, addr_L, data) DataPackage_TX(M_HeadCMD, id, M_CMD_WRITE_ROM, addr_H, addr_L, data, Random_Generate())
/* 主机指令.读从机存储区 */
#define DataTx_Master_Read_ROM(id, addr_H, addr_L) DataPackage_TX(M_HeadCMD, id, M_CMD_READ_ROM, addr_H, addr_L, Random_Generate(), Random_Generate())

/* 主机指令.恢复出厂设置 */
#define DataTx_Master_ResetData(id) DataPackage_TX(M_HeadCMD, id, M_CMD_DATA_RESET, Random_Generate(), Random_Generate(), Random_Generate(), Random_Generate())

/*————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/

/* 从机反馈.返回本机ID */
#define DataTx_Slave_ID(id) DataPackage_TX(S_HeadCOM, S_Return_ID, id, Random_Generate(), Random_Generate(), Random_Generate(), Random_Generate())
/* 从机反馈.返回本机坐标 */
#define DataTx_Slave_Coord(id, x, y) DataPackage_TX(S_HeadCOM, S_RETURN_Coord, id, x, y, Random_Generate(), Random_Generate())
/* 从机反馈.返回本机角度 */
#define DataTx_Slave_Angle(id, angle) DataPackage_TX(S_HeadCOM, S_RETURN_Angle, id, angle, Random_Generate(), Random_Generate(), Random_Generate())
/* 从机反馈.返回存储区数据 */
#define DataTx_Slave_ROM_Data(id, addr_H, addr_L, data) DataPackage_TX(S_HeadCOM, S_RETURN_ROM_DATA, id, addr_H, addr_L, data, Random_Generate())

void Uart1_Byte_POP(FIFOTypeDef *StructDAT);

void Com_Init(void);
void Com_Handshake(void);
void DataPackage_TX(uchar dat1, uchar dat2, uchar dat3, uchar dat4, uchar dat5, uchar dat6, uchar dat7);
unsigned char DataPackage_Extract(FIFOTypeDef *StructDAT);                      // 从缓存里提取从机发来的有效数据包
void Slave_Handshake(void);
void Slave_Allocate_ID(void);

void Poll_Device_ID(void);
void Poll_Device_Data(void);
void Post_Device_Commu_ID(void);
void Post_Device_Light_ID(void);
void Post_Device_Series_ID(void);
void Mark_Device_FixedID_Data(void);

void Get_Slave_ID(void);
void Get_Slave_Coord(void); /* 获取坐标 */
void Set_Slave_Coord(void); /* 设置坐标 */
void Get_Slave_Angle(void); /* 获取角度 */
void Set_Slave_Angle(void); /* 设置角度 */

void Slave_DataInit(void);

uint8_t CRC_Calculate(uint8_t *sur, uint8_t len);     // 返回CRC校验

void Upload_EffectMessage(uint8_t eType);             // 上传灯效信息
void RAW_processing(uint8_t *sur, uint16_t len);      // 透传上报
void Upload_StateMessage(uint8_t cmd, uint8_t sta);   // 上报状态
void Protocol_RGBW_Output(uint8_t *sur, uint16_t len); // 解析出灯组输出颜色

void slave_data_debug(void); // 生成虚假模组数据

#endif
