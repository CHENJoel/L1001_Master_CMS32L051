#ifndef PROTOCOLCOM_H
#define PROTOCOLCOM_H


#define p_REG(reg) (uint32_t *)&reg, sizeof(reg)

#ifndef MARK1001
#define MARK1001 0x1001 // 特殊有效值(标记寄存器是否有效启用)
#endif
/*
    通讯规则
主机接收     来自上位机和从机的数据
从机接收     来自上位机和主机的数据
上位机接收   来自主机和从机的数据
引导程序接收 来自上位机的数据
*/

/*****************************************************************************************************************************************/
/*                                                                      通讯相关
 */
#define Public_Addr 0xFF // 广播地址

typedef enum
{
    PLAY_DATA = 0xA0, // 播放数据
} dataType;           // 数据类型

/***********************************************************************************/
// 定长协议
#pragma pack(push, 1)
typedef struct
{
    uint8_t addr; // 接收地址
    uint8_t bri;  // 亮度
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
} playdata_Typedef;
typedef struct
{
    dataType type; // 数据类型
    uint8_t num;   // 播放数据的个数
} packhead_Typedef;
typedef struct
{
    packhead_Typedef head;
    playdata_Typedef play[256];
} playpack_Typedef;
#pragma pack(pop)

/***********************************************************************************/
/*                                                 通讯数据包
 */
typedef enum /*帧头类型*/
{
    MPLAY_HEADER = 0xAA, // 主机数据包引导头.播放颜色
    MCMD_HEADER = 0xBB,  // 主机数据包引导头.指令
    SCMD_HEADER = 0xCC,  // 从机数据包引导头.指令
    BCMD_HEADER = 0xDD,  // 引导程序数据包引导头.指令
    UPPER_HEADER = 0xEE, // 上位机数据包引导头
    FRAEME_TAIL = 0xAD,  // 帧尾
} Comheadnum;

typedef enum /*指令类型*/
{
    CMD_READREG,   // 读数据寄存器 /*操作索引的寄存器 RAM区*/
    CMD_WRITEREG,  // 写数据寄存器 /*操作索引的寄存器 RAM区*/
    CMD_RETURNREG, // 返回数据寄存器

    CMD_READADDR,  // 读地址数据 /*操作地址上的数据 ROM区*/
    CMD_WRITEADDR, // 写地址数据 /*操作地址上的数据 ROM区*/
    CMD_RETURADDR, // 返回地址数据

    CMD_CONTROL, // 控制指令
    CMD_CTRLACK, // 应答控制指令
} CmdTypenum;

typedef enum /*通讯寄存器-索引表*/
{
    /*引导程序寄存器-索引*/
    BOOTLOAER_REG = 0X100,
    /*从机寄存器-索引*/
    SLAVE_REG_ORIGIN = 0x200,
    REG_WERTE_PROTECT, // 写保护寄存器
    REG_DEVICEID,      // 设备ID
    REG_COMMUNID,      // 通讯ID
    REG_STARTTIME,     // 开机次数
    REG_DEVICETYPE,    // 设备类型
    /*主机寄存器-索引*/
    MASTER_REG_ORIGIN = 0x300,
    /*通用寄存器-索引*/
    GENERAL_REG_ORIGIN = 0x400,
    MAX_REGENUM = 0xFFFF, // 16位枚举
} Regenum;

typedef enum /*通讯指令-索引表*/
{
    /*引导程序指令-索引*/
    BOOTLOAER_CMD_ORIGIN = 0x100,
    CMD_GOTO_APP,      // 跳转至APP
    CMD_FLASH_ERASE,   // 擦除FLASH
    CMD_FLASH_PROGRAM, // FLASH编程
    CMD_FLASH_INSERT,  // FLASH插入数据
    CMD_FLASH_READ,    // 读出FLASH
    CMD_FLASH_SUM,     // FLASH累加和
    CMD_MCU_UID,       // UID
    CMD_BOOT_VERSION,  // 引导程序版本信息
    CMD_APP_VERSION,   // 应用程序版本信息
    /*从机指令-索引*/
    SLAVE_CMD_ORIGIN = 0x200,
    CMD_CONNECT_COID,  // 握手通信ID
    CMD_REFRESH_COID,  // 更新通信ID
    CMD_RESETUSERDATA, // 数据恢复默认值
    /*主机指令-索引*/
    MASTER_CMD_ORIGIN = 0x300,
    /*通用指令-索引*/
    GENERAL_CMD_ORIGIN = 0x400,
    CMD_RESET_DEVICE,     // 复位设备
    CMD_GOTO_IAPMODE,     // 进入程序升级状态
    MAX_CMDENUM = 0xFFFF, // 16位枚举
} Cmdenum;
/***********************************************************************************/
/*                                                 通讯数据包 格式结构体
 */
#pragma pack(push, 1)
typedef struct
{
    Comheadnum head; // 协议头
    uint8_t addr;    // 接收地址
    uint8_t bri;     // 亮度
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
    uint8_t sum;
} complay_Typedef; /*播放.通讯数据格式*/
#pragma pack(pop)
/********************************************************/
#pragma pack(push, 1)
typedef struct
{
    Comheadnum com_head;    // 协议头
    uint8_t com_addr;       // 接收地址
    CmdTypenum com_cmdType; // 指令类型
    uint16_t com_regaddr;   // 寄存器地址/索引 小端模式
    uint16_t com_regval;    // 寄存器值 小端模式
    uint8_t com_checksum;   // 校验和
} comRW_Typedef;            /*寄存器/地址读写.通讯数据格式*/
#pragma pack(pop)
/********************************************************/
#pragma pack(push, 1)
typedef struct
{
    Comheadnum com_head;    // 协议头
    uint8_t com_addr;       // 接收地址
    CmdTypenum com_cmdType; // 指令类型
    Cmdenum com_cmd;        // 命令 2字节
    uint8_t com_val1;       // 值1/随机数
    uint8_t com_val2;       // 值2/随机数
    uint8_t com_checksum;   // 校验和
} comCmd_Typedef;           /*控制指令.通讯数据格式*/
#pragma pack(pop)
/********************************************************/

// // // // #pragma pack(push, 1)
// // // // typedef struct
// // // // {
// // // //     Comheadnum iap_head;    // 协议头
// // // //     uint8_t iap_addr;       // 接收地址
// // // //     CmdTypenum iap_cmdType; // 指令类型-控制指令
// // // //     Cmdenum iap_cmd;        // 编程指令
// // // //     uint16_t packaddr;      // 固件包地址
// // // //     uint8_t packbuffer[512];      // 固件
// // // //     uint8_t iap_checksum;   // 校验和
// // // //     Comheadnum iap_tail;    // 帧尾
// // // // } iappack_Typedef;          /*数据包.格式*/
// // // // #pragma pack(pop)
/********************************************************/

/*应答返回寄存器/地址的值*/
void ACK_comRW(CmdTypenum CmdType, uint16_t cmd, uint16_t Val);
/*应答控制指令*/
void ACK_comCmd(CmdTypenum CmdType, Cmdenum cmd, uint8_t Val1, uint8_t Val2);
/*指令处理*/
void Instruction_Process(void);
/*寄存器读写*/
void CmdReg_RW(CmdTypenum CmdType, Regenum RegNum, uint32_t Val, uint32_t *pREG, uint8_t size);
/*指定地址读写1字节*/
void CmdAdr_RW(CmdTypenum CmdType, uint32_t addr, uint32_t Val);
/*指令分析*/
void Command_Analyse(CmdTypenum CmdType, uint16_t Reg, uint16_t Val);
/*计算校验和*/
uint16_t CheckSum_Calu(uint8_t *sur, uint16_t len);
/*****************************************************************************************************************************************/
/*








*/
typedef enum
{
    HANKSHAKE = 0xD0,     // 通信握手
    ERASEAPP,             // 擦除APP扇区
    APPDATA,              // APP数据
    GOAPP,                // 跳转至APP
    REG_MAXADDR = 0xFFFF, // 寄存器索引/地址 为2字节
} RegisterType;

#endif
