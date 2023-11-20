#ifndef USERMEMORY_H
#define USERMEMORY_H
#include "Function_Init.H"


#define NORFLASH_BASE 0UL
#define NORFLASH_SIZE 0UL

#define OTAPACK_BASE (NORFLASH_BASE + 0UL)
#define SYSDATA_BASE (NORFLASH_BASE + 0x10000UL)
#define EFFECT_BASE  (NORFLASH_BASE + 0x20000UL)
#define SPARE_BASE   (NORFLASH_BASE + 0x30000UL)


/*
nor flash
P25T22H Memory Organization
Address Range: 0x000000 ~ 0x03F000
Size: 0x40000 , 262144 byte , 2097152 bit , 0x200000 bit


*/
#define OTAPACK_SIZE 0x10000UL
#define SYSDATA_SIZE 0x10000UL
#define EFFECT_SIZE  0x10000UL
#define SPARE_SIZE   0x10000UL
#define VERIFY_SIZE  0xFF

#define EF_MEM_VERIFY "effect data 2023/11/16 qwerdqwe "
#define DEFAULE_PLAYLIST_NAME "default list"

typedef struct
{
    uint8_t str[VERIFY_SIZE]; // 校验区，判断是否为出厂状态
} verify_Typedef;

/************************/
/*64k擦除灯效数据所在block区*/
void EffectData_BlockErase_64k(void);


/*校验顺序表内数据是否正确*/
void verify_ranklist(void );
//
void norflash_reset_to_zreo(void);      // 外置flash全片数据清零
void factoryreset_norflash(void);               // norflash恢复出厂设置
void verify_factoryreset_effect_norflash(void); // 校验灯效数据是否要恢复出厂设置
//
/* 出厂化内置播放表信息*/
void init_default_playlist(void);
/*获取灯效校验信息*/
void get_effect_verify(verify_Typedef *p);
/*保存灯效校验信息*/
void save_effect_verify(verify_Typedef *p);
/*对norflash里的数据进行初始化*/
void norflash_data_init(void);
//
void reset_built_in_effect(uint8_t efnum); // 重置内置原生灯效
void copy_built_in_ef_to_norflash(void);   // 内置灯效拷贝至外部norflash内
//
/*检索flash中的自定义&收藏灯效顺序表*/
void search_norflash_ranklist(void);
/*校验全部灯效顺序表内数据是否正确*/
uint8_t verify_allef_ranklist(void);
/*校验自定义灯效顺序表内数据是否正确*/
uint8_t verify_originalef_ranklist(void);
/*校验自定义灯效顺序表内数据是否正确*/
uint8_t verify_favoritesef_ranklist(void);
/*校验自定义灯效顺序表内数据是否正确*/
uint8_t verify_playlist_ranklist(void);


/*************************************************************************/
/*读出灯效*/
void get_effect_detail(Efdetail_TypeDef *p, uint8_t efnum);
/*读出自定义灯效*/
uint8_t get_original_effect(Efdetail_TypeDef *p, uint8_t efnum);
/*读出播放详情*/
void get_playdetail(playdetail_TypeDef *p, uint8_t playnum);
/*获取全部灯效列表*/
void get_allef_ranklist(ef_ranklist_TypeDef *p);
/*获取自定义灯效列表*/
void get_originalef_ranklist(ef_ranklist_TypeDef *p);
/*获取收藏灯效列表*/
void get_favoritesef_ranklist(ef_ranklist_TypeDef *p);
/*获取播放列表的顺序表*/
void get_playlist_ranklist(playlist_ranklist_TypeDef *p);
/*获取播放列表的名字*/
void get_playlist_name(name_TypeDef *p, uint8_t playnum);
/*获取从机设备信息*/
void get_all_slave_data(device_data_TypeDef* p);
/* 获取全部定时计划*/
void get_all_schedule(clock_list_TypeDef *p);
/* 获取定时详情*/
void get_schedule_detail(clock_detail_TypeDef *p, uint8_t num);
/* 获取系统全局设置 */
void get_global_setting(global_setting_TypeDef *p);
// // // /*获取播放详情列表的顺序表*/
// // // void get_playdetaillist_ranklist(playdetaillist_ranklist_TypeDef *p);
/*************************************************************************/

/*存储灯效*/
void save_effect(Efdetail_TypeDef *p, uint8_t efnum);
/*存储自定义灯效*/
uint8_t save_original_effect(Efdetail_TypeDef *p, uint8_t efnum);
/*存储播放详情*/
void save_playdetail(playdetail_TypeDef *p, uint8_t playnum);
/*存储全部灯效列表*/
void save_allef_ranklist(ef_ranklist_TypeDef *p);
/*存储自定义灯效列表*/
void save_originalef_ranklist(ef_ranklist_TypeDef *p);
/*存储收藏灯效列表*/
void save_favoritesef_ranklist(ef_ranklist_TypeDef *p);
/*存储播放列表的顺序表*/
void save_playlist_ranklist(playlist_ranklist_TypeDef *p);
/*存储从机设备信息*/
void save_all_slave_data(device_data_TypeDef* p);
/* 保存时间计划表*/
void save_all_schedule(clock_list_TypeDef *p);

/*  */

void save_global_setting(global_setting_TypeDef *p); // 保存系统全局设置
void save_global_brightness_set(void);               // 保存全局亮度
//
// // // /*存储播放详情列表的顺序表*/
// // // void save_playdetaillist_ranklist(playdetaillist_ranklist_TypeDef *p);
/*************************************************************************/
/*比较两个表是否包含的数据是否一样*/
uint8_t compare_same_ranklist(ef_ranklist_TypeDef *ranklist1, ef_ranklist_TypeDef *ranklist2);
/*从顺序表中删除参数*/
uint8_t delete_num_from_effect_ranklist(ef_ranklist_TypeDef *p, uint8_t efnum);
/*从灯效顺序表中添加元素*/
uint8_t add_num_from_effect_ranklist(ef_ranklist_TypeDef *p,uint8_t efnum);
/*删除自定义灯效*/
uint8_t delete_original_ef(uint8_t efnum);
//
uint8_t add_original_ef(Efdetail_TypeDef *p, uint8_t efnum);        // 新增自定义灯效
uint8_t update_built_in_effect(Efdetail_TypeDef *p, uint8_t efnum); // 更新内置灯效信息
//
/*删除所有自定义灯效*/
void clear_all_original_ef(void);
/*收藏灯效*/
uint8_t add_favorites_ef(uint8_t efnum);
/*取消收藏灯效*/
uint8_t delete_favorites_ef(uint8_t efnum);
/*删除播放列表*/
uint8_t delete_playlist(uint8_t listnum);
/*添加播放信息*/
uint8_t add_playlist(playdetail_TypeDef *p, uint8_t listnum);

// 



/*删除列表*/
void clear_all_ef_ranklist(void);
/*删除播放列表*/
void clear_playlist_ranklist(void);
/*从通信中拷贝定时计划详情*/
void copy_schedule_detail_from_com(com_schedule_detail_TypeDef *sur, clock_detail_TypeDef *tar);
/*拷贝定时计划详情至通信中*/
void copy_schedule_detail_to_com(clock_detail_TypeDef *sur, com_schedule_detail_TypeDef *tar);
/*添加定时计划*/
uint8_t add_clock_schedule(clock_detail_TypeDef *p, uint8_t num);
/*删除定时计划*/
uint8_t delete_schedule(uint8_t num);
//----------------------------------------------------------------
void init_default_global_setting(void); // 全局设置初始化成默认数据
//
void get_device_identify(device_indentify_TypeDef *p);  // 获取设备配对标识
void save_device_identify(device_indentify_TypeDef *p); // 保存设备配对标识
void clear_device_identify(void);                       // 清除设备配对标识
//
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*

                *** MEMORY MAP ***

         _______________________________
0x0000  |                               |
        |                               |
        |          BOOTLOADER           |   0x0000~0x4FFF
        |                               |   size:0x5000,20480 Byte,20k
        |                               |
        |_______________________________|    ______________________________________________________________________________
0x5000  |                               |   |                                                                              |
        |                               |   |                                                                              |
        |                               |   |                                                                              |
        |                               |   |                                                                              |
        |                               |   |                                                                              |
        |              APP              |   | APP address : 0x5000~0xEFFF                                                  |
        |                               |   | APP size:0xA000,40960 Byte ,40K                                              |
        |                               |   | (app + app checksum ,size:0xA000,40960 Byte )                                |
        |                               |   |                                                                              |
        |                               |   |                                                                              |
        |  _  _  _  _  _  _  _  _  _  _ |   |----------------------                                                        |
0xEFF0  |          APP CHECKSUM         |   | 0xEFF0~0xEFFF size:0x0F,16 Byte (app package checksum)                       |
        |_______________________________|   |______________________________________________________________________________|
0xF000  |        **************         |   size:0x200,512 Byte    data area , 0x1000 4096 Byte,4K
        |_______________________________|
0xF200  |        **************         |   size:0x200,512 Byte
        |_______________________________|
0xF400  |        ****************       |   size:0x200,512 Byte
        |_______________________________|
0xF600  |        ****************       |   size:0x200,512 Byte
        |_______________________________|
0xF800  |        ****************       |   size:0x200,512 Byte
        |_______________________________|
0xFA00  |        ****************       |   size:0x200,512 Byte
        |_______________________________|
0xFC00  |        ****************       |   size:0x200,512 Byte
        |_______________________________|
0xFE00  |        ****************       |   size:0x200,512 Byte
0xFFFF  |_______________________________|   _________________________________________________________________________________
    0x10000

*/

/**************************************************************************************/
/*片外Flash区*/
#define FILE_BASEADDR 0x00000
#define FILE_SIZE 0xA000
/**************************************************************************************/
/*主闪存区*/
#define BOOTLOADER_BASEADDR 0x0000     // 引导程序基地址
// #define BOOTLOADER_SIZE 0x5000         // 引导程序大小 20K,20480byte
// #define APP_BASEADDR 0x5000            // 应用程序基地址
// #define APP_SIZE 0xA000                // 应用程序大小 40K,40960byte
#define FLASH_RESERVED_BASEADDR 0xF000 // fash保留区基地址.后续可拓展为APP/数据存储区
#define FLASH_RESERVED_SIZE 0x1000     // fash保留区大小 4K,4096byte
/*数据闪存*/
#define USERDATA_BASEADDR 0x500000 // 用户数据基地址（数据闪存）
#define USERDATA_SIZE 0x600        // 用户数据大小 1.5K,1536byte
/*****************************************************************************************************************************************/
/*


*/

/*****************************************************************************************************************************************/
/*                                              用户数据存储区 空间分配结构体
 */
typedef struct /*断电可保存数据*/
{
        uint8_t version[16]; // 软件版本字符串
        uint8_t deviceID;    // 设备ID
        uint8_t communID;    // 通讯ID，默认等于设备ID,当线路出现ID冲突时，通讯ID会刷新为其他值
        uint8_t deviceType;  // 设备类型 大中小方
        uint16_t verifyCode; // 出厂识别码，出厂后会被刷写成特殊有效值
        uint16_t starttime;  // 开机次数
} Appdata_Typedef;

typedef struct
{
        uint16_t iap_permit;    // 进入iap升级状态，写特殊值时有效
        uint32_t upload_flag;   // 升级标志，写 UID->UID0时有效
        uint32_t pack_checksum; // 升级包的校验和
        uint32_t verify;        // upload_flag与pack_checksum的校验和
} Bootdata_Typedef;

typedef struct
{
        volatile Bootdata_Typedef Bootdata;
        volatile uint8_t BootdataReservred[256 - sizeof(Bootdata_Typedef)]; // 前256字节为bootloader数据存储
        volatile Appdata_Typedef Appdata;
        volatile uint8_t AppdataReservred[256 - sizeof(Appdata_Typedef)]; // 后256字节为APP数据存储
} Userdata_Typedef;
typedef struct
{
        volatile Userdata_Typedef user;
        volatile uint8_t Reservred[USERDATA_SIZE - sizeof(Userdata_Typedef)]; /*备用区*/
} dataflash_Typedef;                                                          /*数据闪存区 1.5K*/

extern Userdata_Typedef Userdata;                          //
#define DATAFLASH ((dataflash_Typedef *)USERDATA_BASEADDR) // 用户数据结构体映射到硬件地址上
/*****************************************************************************************************************************************/


/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/**********************************************************************************************************************************************************************************************************/
/*
Flash芯片 P25T22 ，内存2Mbit(256KByte)，地址：0x00000~0x3FFFF

0x00000~0x3FFFF
         _______________________________
0x00000 |                               |   APP OTA升级区
        |                               |
        |                               |   0x00000~0x0FFFF
        |                               |   size:0x10000,64KByte,65536 Byte
        |                               |
0x0FFFF |_______________________________|    ______________________________________________________________________________
0x10000 |                               |   系统信息区
        |                               |
        |                               |    0x10000~0x1FFFF
        |                               |    size:0x10000,64KByte,65536 Byte
        |                               |
0x1FFFF |_______________________________|    ______________________________________________________________________________
0x20000 |                               |   灯效信息区
        |                               |
        |                               |   0x20000~0x2FFFF
        |                               |   size:0x10000,64KByte,65536 Byte
        |                               |
0x2FFFF |_______________________________|    ______________________________________________________________________________
0x30000 |                               |   备用区
        |                               |
        |                               |   0x30000~0x3FFFF
        |                               |   size:0x10000,64KByte,65536 Byte
        |                               |
0x3FFFF |_______________________________|    ______________________________________________________________________________


*/

/********************************************************************************************/
/*                              OTA 升级存储区
*/
typedef struct
{
    uint8_t package[OTAPACK_SIZE];
} otadata_Typedef;
typedef struct
{
    volatile otadata_Typedef data;
// // //     volatile uint8_t Reservred[OTAPACK_SIZE - sizeof(otadata_Typedef)]; /*备用区*/
} otapack_area_Typedef;
/********************************************************************************************/

/********************************************************************************************/
/*                              系统信息 存储区
 */
typedef struct
{
        verify_Typedef verify;                     // 数据校验区
        device_data_TypeDef slave;                 // 设备信息
        clock_list_TypeDef schedule;               // 定时任务
        global_setting_TypeDef global_setting;     // 全局设置
        device_indentify_TypeDef device_indentify; // 设备配对标识（app）
} sysdata_Typedef;

typedef struct
{
    volatile sysdata_Typedef data;
    volatile uint8_t Reservred[SYSDATA_SIZE - sizeof(sysdata_Typedef)]; /*备用区*/
} sysdata_area_Typedef;
/********************************************************************************************/

/********************************************************************************************/
/*                              灯效信息 存储区
*/

typedef struct
{
    verify_Typedef verify;     // 数据校验区
    EffectInf_TypeDef effect;  // 灯效存储区
    PlayInf_TypeDef play;      // 播放详情区
    ranklist_TypeDef ranklist; // 各类列表区
} efdata_Typedef;
typedef struct
{
    volatile efdata_Typedef data;
//     volatile uint8_t Reservred[EFFECT_SIZE - sizeof(efdata_Typedef)]; /*备用区*/
} efdata_area_Typedef;
/********************************************************************************************/

/********************************************************************************************/
/*                              备用 存储区
*/
typedef struct
{
    uint8_t res[16];
} spare_Typedef;
typedef struct
{
    volatile spare_Typedef data;
//     volatile uint8_t Reservred[SPARE_SIZE - sizeof(otadata_Typedef)]; /*备用区*/
} spare_area_Typedef;
/************************************************************************************************************************************************/
// 片外flash空间分配
typedef struct
{
    otapack_area_Typedef ota;
    efdata_area_Typedef efdata;
    sysdata_area_Typedef sysdata;
//     spare_area_Typedef  spare;
} norflash_Typedef;
/************************************************************************************************************************************************/

#define NORFLASH ((norflash_Typedef *)NORFLASH_BASE) // 用户数据结构体映射到硬件地址上









#endif
