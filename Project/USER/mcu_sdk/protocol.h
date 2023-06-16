/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2030, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    protocol.h
 * @author  涂鸦综合协议开发组
 * @version v1.0.4
 * @date    2021.6.1
 * @brief
 *                       *******非常重要，一定要看哦！！！********
 *          1. 用户在此文件中实现数据下发/上报功能
 *          2. DP的ID/TYPE及数据处理函数都需要用户按照实际定义实现
 *          3. 当开始某些宏定义后需要用户实现代码的函数内部有#err提示,完成函数后请删除该#err
 */

/****************************** 免责声明 ！！！ *******************************
由于MCU类型和编译环境多种多样，所以此代码仅供参考，用户请自行把控最终代码质量，
涂鸦不对MCU功能结果负责。
******************************************************************************/

#ifndef __PROTOCOL_H_
#define __PROTOCOL_H_

#include "tuya_type.h"

/******************************************************************************
                           用户相关信息配置
******************************************************************************/
/******************************************************************************
                       1:修改产品信息
******************************************************************************/
#define PRODUCT_KEY "8vb1nbz2e9vb1sxv"    //开发平台创建产品后生成的16位字符产品唯一标识

#define MCU_VER "1.1.3"         //用户的软件版本,用于MCU固件升级,MCU升级版本需修改

/* HomeKit产品品类选择。 服务配置选择和特性配置选择请在homekit.c中进行 */
//#define HOMEKIT_PRODUCT_TYPE    3             //风扇
//#define HOMEKIT_PRODUCT_TYPE    4             //车库门开启器
#define HOMEKIT_PRODUCT_TYPE    5             //照明
//#define HOMEKIT_PRODUCT_TYPE    9             //恒温器
//#define HOMEKIT_PRODUCT_TYPE    12            //门
//#define HOMEKIT_PRODUCT_TYPE    13            //窗户
//#define HOMEKIT_PRODUCT_TYPE    14            //窗帘
//#define HOMEKIT_PRODUCT_TYPE    19            //空气净化器
//#define HOMEKIT_PRODUCT_TYPE    20            //加热器冷却器（取暖器，cooler）
//#define HOMEKIT_PRODUCT_TYPE    22            //加湿器
//#define HOMEKIT_PRODUCT_TYPE    23            //除湿器
//#define HOMEKIT_PRODUCT_TYPE    28            //洒水器
//#define HOMEKIT_PRODUCT_TYPE    29            //水龙头
//#define HOMEKIT_PRODUCT_TYPE    30            //淋浴系统

#ifdef HOMEKIT_PRODUCT_TYPE
/* 是否需要配置特性有效值 */
#define HOMEKIT_CHARACTER_VALID_CFG_ENABLE
#endif

/******************************************************************************
                          2:MCU是否需要支固件升级
如需要支持MCU固件升级,请开启该宏
MCU可调用mcu_api.c文件内的mcu_firm_update_query()函数获取当前MCU固件更新情况
                        ********WARNING!!!**********
当前接收缓冲区为关闭固件更新功能的大小,固件升级包可选择，默认256字节大小
如需要开启该功能,需要较大的串口接收缓冲区
******************************************************************************/
#define         SUPPORT_MCU_FIRM_UPDATE                 //开启MCU固件升级功能(默认关闭)
#ifdef SUPPORT_MCU_FIRM_UPDATE
/*  固件包大小选择  */
#define PACKAGE_SIZE                   0        //包大小为256字节
//#define PACKAGE_SIZE                   1        //包大小为512字节
//#define PACKAGE_SIZE                   2        //包大小为1024字节

/*  MCU固件区类型  */
#define MCU_FIRMWARE_BACKUP_AREA_TYPE   0       //MCU是双固件区（默认）
//#define MCU_FIRMWARE_BACKUP_AREA_TYPE   1       //MCU是单固件区
#endif

/******************************************************************************
                         3:定义收发缓存:
                    如当前使用MCU的RAM不够,可修改为24
******************************************************************************/
#ifndef SUPPORT_MCU_FIRM_UPDATE
#define WIFI_UART_RECV_BUF_LMT          16              //串口数据接收缓存区大小,如MCU的RAM不够,可根据MCU实际情况适当缩小
#define WIFI_DATA_PROCESS_LMT           24              //串口数据处理缓存区大小,根据用户DP数据大小量定,建议大于24
#else
#define WIFI_UART_RECV_BUF_LMT          300             //串口数据接收缓存区大小,如MCU的RAM不够,可缩小

//请在此处选择合适的串口数据处理缓存大小（根据上面MCU固件升级包选择的大小和是否开启天气服务来选择开启多大的缓存）
#define WIFI_DATA_PROCESS_LMT           300             //串口数据处理缓存大小,如需MCU固件升级,若单包大小选择256,则缓存必须大于260,若开启天气服务,则需要更大
//#define WIFI_DATA_PROCESS_LMT           600             //串口数据处理缓存大小,如需MCU固件升级,若单包大小选择512,则缓存必须大于520,若开启天气服务,则需要更大
//#define WIFI_DATA_PROCESS_LMT           1200            //串口数据处理缓存大小,如需MCU固件升级,若单包大小选择1024,则缓存必须大于1030,若开启天气服务,则需要更大
#endif
#define WIFIR_UART_SEND_BUF_LMT         300              //根据用户DP数据大小量定,必须大于51

/******************************************************************************
                        4:定义模块工作方式
模块自处理:
          wifi指示灯和wifi复位按钮接在wifi模块上(开启WIFI_CONTROL_SELF_MODE宏)
          并正确定义 TY_STATE_LED、HK_STATE_LED 和 WF_RESET_KEY
MCU与模块配合处理:
          wifi指示灯和wifi复位按钮接在MCU上(关闭WIFI_CONTROL_SELF_MODE宏)
          MCU在需要处理复位wifi的地方调用mcu_api.c文件内的mcu_reset_wifi()函数,并可调用mcu_get_reset_wifi_flag()函数返回复位wifi结果
******************************************************************************/
//#define         WIFI_CONTROL_SELF_MODE                       //使用wifi自处理请开启该宏，并指定tuya-WiFi指示灯、HomeKit-WiFi指示灯、按键的模组IO。若使用MCU与模块配合处理，请关闭该宏
#ifdef          WIFI_CONTROL_SELF_MODE                      //模块自处理
  #define     TY_STATE_LED            0                     //wifi模块tuya网络状态指示，请根据实际使用的模块IO管脚设置
  #define     HK_STATE_LED            4                     //wifi模块HomeKit网络状态指示，请根据实际使用的模块IO管脚设置
  #define     WF_RESERT_KEY           5                     //wifi模块重置按键，请根据实际使用的模块IO管脚设置
#endif

/******************************************************************************
                      MCU是否需要支持校时功能（本地时间）
如需要请开启该宏,并在Protocol.c文件内mcu_write_rtctime实现代码
mcu_write_rtctime内部有#err提示,完成函数后请删除该#err
mcu在wifi模块正确联网后可调用mcu_get_system_time()函数发起校时功能
******************************************************************************/
#define         SUPPORT_MCU_RTC_CHECK                //开启校时功能

/******************************************************************************
                      MCU是否需要支持wifi功能测试
如需要请开启该宏,并且mcu在需要wifi功能测试处调用mcu_api.c文件内mcu_start_wifitest
并在protocol.c文件wifi_test_result函数内查看测试结果,
wifi_test_result内部有#err提示,完成函数后请删除该#err
******************************************************************************/
#define         WIFI_TEST_ENABLE                //开启WIFI产测功能（扫描指定路由）

/******************************************************************************
                      MCU是否需要支持获取模块内存
如需要请开启该宏,并且mcu在需要获取模块内存处调用mcu_api.c文件内get_module_remain_memory
并在protocol.c文件remain_memory_result函数内查看结果,
remain_memory_result内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         GET_MODULE_REMAIN_MEMORY_ENABLE        //开启获取模块内存

/******************************************************************************
                      MCU是否需要支持获取当前WIFI信号强度
如需要请开启该宏,并且mcu在需要wifi功能测试处调用mcu_api.c文件内mcu_get_router_rssi
并在protocol.c文件get_router_rssi_result函数内查看测试结果,
get_router_rssi_result内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         GET_ROUTE_RSSI_ENABLE                //开启获取当前WIFI信号强度

/******************************************************************************
                      是否开启WIFI模组心跳关闭功能
如需要请开启该宏,调用mcu_api.c文件内wifi_heart_stop函数即可停止心跳
******************************************************************************/
//#define         WIFI_HEARTSTOP_ENABLE           //开启心跳停止功能

#ifndef WIFI_CONTROL_SELF_MODE
/******************************************************************************
                      MCU是否需要开启获取当前WIFI联网状态功能
如需要请开启该宏,并且mcu在需要获取当前WIFI联网状态处调用mcu_api.c文件内mcu_get_wifi_connect_status
并在protocol.c文件wifi_test_result函数内查看结果,
wifi_test_result内部有#err提示,完成函数后请删除该#err
******************************************************************************/
#define         GET_WIFI_STATUS_ENABLE                  //开启获取当前WIFI联网状态功能
#endif

/******************************************************************************
                      MCU是否需要开启获取模块mac地址功能
如需要请开启该宏,并且mcu在需要获取模块mac地址处调用mcu_api.c文件内mcu_get_module_mac
并在protocol.c文件mcu_get_mac函数内查看结果,
mcu_get_mac内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         GET_MODULE_MAC_ENABLE                   //开启获取模块mac地址功能

/******************************************************************************
                      MCU是否需要支持获取格林时间功能
如需要请开启该宏,并且mcu在需要获取格林时间处调用mcu_api.c文件内mcu_get_green_time
并在protocol.c文件mcu_get_greentime函数内查看结果,
mcu_get_greentime内部有#err提示,完成函数后请删除该#err
mcu在wifi模块正确联网后可调用mcu_get_green_time()函数发起校时功能
******************************************************************************/
//#define         SUPPORT_GREEN_TIME                      //开启格林时间功能

/******************************************************************************
                      MCU是否需要支持模块拓展服务
如需要请开启该宏,并且mcu在需要模块拓展服务处调用mcu_api.c文件内相关函数
并在protocol.c文件模块拓展服务相关函数内处理结果,
相关函数内部有#err提示,完成函数后请删除该#err
******************************************************************************/
//#define         MODULE_EXTEND_FUN_ENABLE                //开启模块拓展服务




/******************************************************************************
                        1:dp数据点序列号重新定义
          **此为自动生成代码,如在开发平台有相关修改请重新下载MCU_SDK**
******************************************************************************/
//开关(可下发可上报)
//备注:
#define DPID_SWITCH_LED 20
//工作模式(可下发可上报)
//备注:
#define DPID_WORK_MODE 21
//白光亮度(可下发可上报)
//备注:
#define DPID_BRIGHT_VALUE 22
//倒计时(可下发可上报)
//备注:
#define DPID_COUNTDOWN 26
//播放列表的某个效果的详情(可下发可上报)
//备注:
#define DPID_PLAYLIST_EFFECT_SKETCH 101
//播放控制(可下发可上报)
//备注:
//100:播放列表的索引
//0:播放/暂停控制
//1:上下曲控制
//2: 效果索引
//3:循环模式
//-------------------------
//操作类型为100: 下发播放列表的索引
//操作类型为0: 0-暂停,1-播放
//操作类型为1: 0-上一曲,1-下一曲
//操作类型为2: 播放效果索引(注意,app只解析,,固件上报当前的索引)
//操作类型为3: 0-循环模式1,1-循环模式2
#define DPID_PLAY_CONTROL 102
//特效列表数据(可下发可上报)
//备注:与返回参数一致，可下发可上报、透传型（Raw）、格式如下:
//索引	0	1	0-32 所有effects的序号，查询详情效果详情入参
//动作类型	1	1	0:Static,、1:Dynamic、2：Rhythm
//效果类型	2	1	1：Origin、2：favorites、0：其他
//形状数量	2	1	效果中七灯块的数量
//色调1	3、4	2	0-360，0X0000-0X0168
//饱和度1	5、6	2	0-1000, 0X0000-0X03E8
//色调2	7、8	2	0-360，0X0000-0X0168
//饱和度2	9、10	2	0-1000, 0X0000-0X03E8
#define DPID_EFFECT_LIST 103
//某个特效的详情(可下发可上报)
//备注:索引	0	1	0-16
//效果类型	1	1	1：Origin、2：favorites、0：其他
//动作类型	2	1	0:Static,、1:Dynamic、2：Rhythm
//motion 类型	3	1	0:breath,、1:stream、2：reverberate，3Hopscotch,4lighting,5:lgnite,6Random
//亮度1	4	1	0-100%，百分比的值
//亮度2	5	1	0-100%，如若不是 Rhthm，则传值101
//麦克风	6	1	0-100%，如若不是 Rhthm，则传值101
//方向	7	1	0、1、2、3、4、5（上/下/左/右/内聚/外扩）
//形状类型	8	1	0、1、2、3
//位置	9	2	0x0000,高位代表x，地位代表y
//角度	10	2	0-360
//...
//颜色序列
#define DPID_EFFECT_DETIAL 104
//自定义协议(可下发可上报)
//备注:自定义协议透传
#define DPID_USER_PROTOCOL 105
//亮度值(可下发可上报)
//备注:
#define DPID_BRIGHT_VAL 106
//麦克风开关(可下发可上报)
//备注:
#define DPID_SWITCH_MIC 107
//指示灯开关(可下发可上报)
//备注:
#define DPID_SWITCH_INDICATOR 108
//当前灯效编号(可下发可上报)
//备注:
#define DPID_EFFECT_NUM 109
//当前播放列表编号(可下发可上报)
//备注:
#define DPID_PLAYLIST_NUM 110
//自动亮度调节(可下发可上报)
//备注:
#define DPID_BRIGHTNESS_AUTO 111
//系统状态标志(可下发可上报)
//备注:16bit标志位
#define DPID_SYSTEM_STATE 112
//运行状态标志(可下发可上报)
//备注:16bit标志位
#define DPID_RUNNING_STATE 113
//播放列表(可下发可上报)
//备注:索引1	0	1	播放列表索引，用来记录
//播放状态1	1	1	0:暂停 1:播放
//循环模式1	2	1	0：循环模式1，1:循环模式2
//索引2	4	1	播放列表索引，用来记录
//播放状态2	5	1	0:暂停 1:播放
//循环模式2	6	1	0：循环模式1，1:循环模式2
#define DPID_PLAY_LIST 114
//播放详情(可下发可上报)
//备注:索引	0	1	播放列表索引，用来记录
//播放状态	1	1	0:暂停 1:播放
//循环模式	2	1	0：循环模式1，1:循环模式2
//效果索引1	3	1	0-所有效果个数
//duration1	4	1	0-240s
//效果索引2	5		0-所有效果个数
//duration12	6	1	0-所有效果个数
#define DPID_PLAY_DETIAL 115
//连接状态(可下发可上报)
//备注:0	1	保留
//1	1	0:断开，1连接
#define DPID_LINK_STATUS 116
//全局状态(可下发可上报)
//备注:效果索引	0	1	0- 百分比
//当前效果索引	1	1
//色调1	2、3	2	0-360，0X0000-0X0168
//饱和度1	4、5	2	0-1000, 0X0000-0X03E8
//色调2	6、7	2	0-360，0X0000-0X0168
//饱和度2	8、5	2	0-1000, 0X0000-0X03E8
#define DPID_GLOBAL_STATUS 117
//下发指令(可下发可上报)
//备注:
#define DPID_ISSUE_CMD 118
//效果预览(可下发可上报)
//备注:效果编辑界面预览,操作任意参数下发上报
#define DPID_EFFECT_PREVIEW 119
//全部灯效的顺序列表(可下发可上报)
//备注:
#define DPID_ALL_EFFECT_RANKLIST 120
//自定义灯效的顺序列表(可下发可上报)
//备注:
#define DPID_ORIGINAL_EFFECT_RANKLIST 121
//收藏灯效的顺序列表(可下发可上报)
//备注:
#define DPID_FAVORITES_EFFECT_RANKLIST 122
//播放列表的顺序列表(可下发可上报)
//备注:
#define DPID_PLAYLIST_RANKLIST 123
//灯效概述(可下发可上报)
//备注:
#define DPID_EFFECT_SKETCH 124
//播放控制效果详情(可下发可上报)
//备注:dp上报播放控制时候的播放列表详情,请求参数为列表索引,上报内容和播放详情一致,请求指令标识为13
#define DPID_PLAY_CONTROL_DETIAL 125
//所有闹钟列表(可下发可上报)
//备注:
#define DPID_CLOCK_LIST 126
//闹钟详情(可下发可上报)
//备注:
#define DPID_CLOCK_DETIAL 127
//灯板信息(可下发可上报)
//备注:id、坐标、角度、
#define DPID_DEVICE_DETAIL 128
//控制灯板(可下发可上报)
//备注:控制灯板亮灯
#define DPID_DEVICE_CONTROL 129



/**
 * @brief  串口发送数据
 * @param[in] {value} 串口要发送的1字节数据
 * @return Null
 */
void uart_transmit_output(u8 value);

/**
 * @brief  系统所有dp点信息上传,实现APP和muc数据同步
 * @param  Null
 * @return Null
 * @note   MCU必须实现该函数内数据上报功能
 */
void all_data_update(void);

/**
 * @brief  dp下发处理函数
 * @param[in] {dpid} dpid 序号
 * @param[in] {value} dp数据缓冲区地址
 * @param[in] {length} dp数据长度
 * @return dp处理结果
 * -           0(ERROR): 失败
 * -           1(SUCCESS): 成功
 * @note   该函数用户不能修改
 */
u8 dp_download_handle(u8 dpid,const u8 value[], u16 length);

/**
 * @brief  获取所有dp命令总和
 * @param[in] Null
 * @return 下发命令总和
 * @note   该函数用户不能修改
 */
u8 get_download_cmd_total(void);

#ifdef SUPPORT_MCU_FIRM_UPDATE
/**
 * @brief  升级包大小选择
 * @param[in] {package_sz} 升级包大小
 * @ref           0x00: 256byte (默认)
 * @ref           0x01: 512byte
 * @ref           0x02: 1024byte
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void upgrade_package_choose(u8 package_sz);

/**
 * @brief  MCU进入固件升级模式
 * @param[in] {value} 固件缓冲区
 * @param[in] {position} 当前数据包在于固件位置
 * @param[in] {length} 当前固件包长度(固件包长度为0时,表示固件包发送完成)
 * @return Null
 * @note   MCU需要自行实现该功能
 */
u8 mcu_firm_update_handle(const u8 value[],u32 position,u16 length);
#endif

#ifdef SUPPORT_GREEN_TIME
/**
 * @brief  获取到的格林时间
 * @param[in] {time} 获取到的格林时间数据
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_greentime(u8 time[]);
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/**
 * @brief  MCU校对本地RTC时钟
 * @param[in] {time} 获取到的格林时间数据
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_write_rtctime(u8 time[]);
#endif

#ifdef WIFI_TEST_ENABLE
/**
 * @brief  wifi功能测试反馈
 * @param[in] {result} wifi功能测试结果
 * @ref       0: 失败
 * @ref       1: 成功
 * @param[in] {rssi} 测试成功表示wifi信号强度/测试失败表示错误类型
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void wifi_test_result(u8 result,u8 rssi);
#endif

#ifdef GET_MODULE_REMAIN_MEMORY_ENABLE
/**
 * @brief  获取模块内存
 * @param[in] {module_memory} 获取模块内存的大小
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void remain_memory_result(u32 module_memory);
#endif

#ifdef GET_ROUTE_RSSI_ENABLE
/**
 * @brief  获取当前WIFI信号强度
 * @param[in] {rssi} 获取信号强度结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_router_rssi_result(u8 rssi);
#endif

#ifdef GET_WIFI_STATUS_ENABLE
/**
 * @brief  更新 WIFI 状态结果
 * @param[in] {wifi_state_flag} 网络状态标志  0x00:tuya网络状态/0x01:homekit网络状态
 * @param[in] {wifi_state} 网络状态值
 * @ref       0x00: wifi状态 1
 * @ref       0x02: wifi状态 3
 * @ref       0x03: wifi状态 4
 * @ref       0x04: wifi状态 5
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void update_wifi_status(u8 wifi_state_flag, u8 wifi_state);
#endif

#ifdef GET_MODULE_MAC_ENABLE
/**
 * @brief  获取模块mac结果
 * @param[in] {mac} 模块 MAC 数据
 * @ref       mac[0]: 为是否获取mac成功标志，0x00 表示成功，0x01 表示失败
 * @ref       mac[1]~mac[6]: 当获取 MAC地址标志位如果mac[0]为成功，则表示模块有效的MAC地址
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_mac(u8 mac[]);
#endif

#ifdef MODULE_EXTEND_FUN_ENABLE
/**
 * @brief  模块拓展服务相关功能处理
 * @param[in] {p_data} 串口数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note
 */
void module_extend_function(u8 p_data[], u16 data_len);
#endif

#ifdef SUPPORT_MCU_FIRM_UPDATE
#if MCU_FIRMWARE_BACKUP_AREA_TYPE == 1
/**
 * @brief  MCU设置新功能结果处理
 * @param[in] {p_data} 串口数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note
 */
void mcu_set_new_func_result(u8 p_data[], u16 data_len);
#endif
#endif


#endif
