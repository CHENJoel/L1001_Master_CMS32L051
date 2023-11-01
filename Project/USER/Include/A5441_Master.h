#ifndef _A5441_MASTER_H_
#define _A5441_MASTER_H_

#include "Function_Init.H"


typedef union
{
    unsigned char byte;
    struct
    {
        unsigned bit0 : 1;
        unsigned bit1 : 1;
        unsigned bit2 : 1;
        unsigned bit3 : 1;
        unsigned bit4 : 1;
        unsigned bit5 : 1;
        unsigned bit6 : 1;
        unsigned bit7 : 1;
    } bits;
}FlagTypeDef;

extern FlagTypeDef flag;

#define RTC_CheckFinish flag.bits.bit0

typedef struct
{
    uint8_t num;    // 随机数
    uint8_t seed;   // 种子
} random_Typdef;

typedef struct
{
    uint8_t on_sta;
    uint8_t effect_num; // 当前播放的列表编号，255代表未执行列表播放
    uint8_t playlist_num;
    uint8_t RESERVED[2];
} PlayingStateTypeDef;

extern PlayingStateTypeDef PlayingState;

enum
{
    STA_OFF = 0,
    STA_ON = 1,
};

typedef struct
{
    uint8_t Direction; //方向 1为加，0为减
    uint8_t Now;       //当前值
    uint8_t Target;    //目标值
    uint8_t Set;       //设定值
} LightTypeDef;

// // typedef struct
// // {
// //     uint8_t POWER_SW;        // 开关
// //     LightTypeDef Brightness; // 亮度
// // } SYS_TypeDef;
// // extern SYS_TypeDef SYS;

enum
{
    DYNAMIC_EFFECT, // 动态
    STATIC_EFFECT,  // 静态
    RHYTHM_EFFECT,  // 律动
};

enum
{
    Light_Owner_MCU = 0, // MCU控灯
    Light_Owner_APP = 1, // APP控灯
};


typedef struct RunningMode
{
    uint8_t Now;
    uint8_t Sum;
} ModeTypeDef;

extern ModeTypeDef ModeArray[3];
extern uint8_t Mode_num;

typedef struct
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
} RGBW_Val;

typedef struct
{
    uint8_t X;
    uint8_t Y;
} Coord_TypeDef;
typedef struct
{
    uint8_t data1;
    // uint8_t data2;
}ContainerTypeDef;

typedef struct
{
    uint8_t ID;                 // id地址
    uint8_t DeviceType;         // 设备类型
    uint8_t Lightnum;           // 灯光序号
    uint8_t Runingnum;          // 实际灯光运行编号（根据灯光序号排序）
    RGBW_Val Color;             // 颜色
    Coord_TypeDef Coord;        // 坐标
    uint8_t Angle;              // 角度 值0~180
    ContainerTypeDef Container; // 容器，暂存使用
} SlaveTypeDef;

typedef struct
{
    uint8_t Device_sum;         // 设备数量
    uint8_t Light_sum;          // 灯光数量（按灯光序号）
    SlaveTypeDef SlaveData[32]; // 从机数据包
} DeviceTypeDef;
extern DeviceTypeDef TangramDevice;

#define EffextImage_num ModeArray[Mode_num].Now // 效果编号

#define Slave_num 16
#define Slave_Data_num 10

extern uint8_t uart1_sendend_flag; // 串口1发送结束标志
extern uint8_t Light_Owner; // 0：MCU控灯    1：APP控灯


extern const uint8_t IR_KeyTable[44];
extern uint8_t IR_KeyVal;
extern const uint8_t Numboard_KeyTable[10];
extern uint8_t FixedID_DeviceData[8][1];

extern uint8_t Uart1_rx_data; // 串口1接收的数据

extern unsigned char Module_Num; // 已链接的灯板模块数量

extern unsigned char Sequence_arr[16]; // 在线灯组顺序
extern unsigned char Light_Sum;        // 在线灯组数量
extern unsigned char E_Type;           // 灯效类型
extern unsigned char E_Color;          // 灯效颜色    每个灯效类型都包含一组灯效颜色，保存在二维数组内

extern unsigned char Device_Chief_ID; // 主ID
extern unsigned char Device_Minor_ID; // 副ID
extern unsigned char Device_Commu_ID; // 通讯ID
extern unsigned char Device_Type;     // 设备类型

extern unsigned char Random_sys;  // 发生系统随机数
extern unsigned char Random_base; // 随机基础数

extern unsigned char Slave_Array[1][Slave_Data_num]; // 从机设备信息
extern unsigned char SlaveDevive_Num;    // 最大从机编号
extern unsigned char ModuleLight_Num; // 灯光序列数量
extern unsigned char Module_Num;      // 已链接的从机序列数量



void KeyS_On(void);
void Scene_MOD(void);
void Paring_Mod(uint8_t *keyval,uint8_t reset);
void NewParing_Mod(uint8_t *keyval,uint8_t reset);
// // // // void Frame_Working(void);

// // // // // // // // void Module_All_GradualChange(uint8_t modele_num);
// // // // // // void Module_SelfTest(void);

uint8_t MIC_Process(void);
// // void Runingnum_Bubble_Sort(void);

void Slave_SelfTest(void);

void DataUpdata_TO_APP(uint8_t *data_addr);

uint8_t KEY_AD_Test(void);
uint8_t Light_AD_Test(void);

uint8_t DATA_To_BCD(uint8_t data); // 数据转BCD码
uint8_t BCD_To_DATA(uint8_t bcd);  // BCD码转换为数据
void RTC_Check(uint8_t time[]);
void RTC_Task(void);

uint32_t checksum_calculate(uint8_t *sur, uint32_t len); // 计算校验和

/*********/

void uart_app_init(void);        // 串口应用初始化
void sys_tick_init(void);        // 系统时钟初始化
void uart_parse(void);           // 串口解析
void random_init(void);          // 随机数初始化
uint8_t get_random_seed(void);   // 获取随机数种子
uint8_t get_random_number(void); // 获取随机数
void refresh_random(void);       // 刷新随机数

void Lignt_Control(void);
#endif
