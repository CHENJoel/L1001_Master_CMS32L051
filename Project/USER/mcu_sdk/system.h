/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2030, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    system.h
 * @author  涂鸦综合协议开发组
 * @version v1.0.4
 * @date    2021.6.1
 * @brief   串口数据处理，用户无需关心该文件实现内容
 */

/****************************** 免责声明 ！！！ *******************************
由于MCU类型和编译环境多种多样，所以此代码仅供参考，用户请自行把控最终代码质量，
涂鸦不对MCU功能结果负责。
******************************************************************************/

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

#include "tuya_type.h"

#ifdef SYSTEM_GLOBAL
  #define SYSTEM_EXTERN
#else
  #define SYSTEM_EXTERN   extern
#endif

//=============================================================================
//Byte order of the frame
//=============================================================================
#define         HEAD_FIRST                      0
#define         HEAD_SECOND                     1        
#define         PROTOCOL_VERSION                2
#define         FRAME_TYPE                      3
#define         LENGTH_HIGH                     4
#define         LENGTH_LOW                      5
#define         DATA_START                      6

//=============================================================================
//Data frame type
//=============================================================================
#define         HEAT_BEAT_CMD                   0x00                            //心跳包
#define         PRODUCT_INFO_CMD                0x01                            //产品信息
#define         WORK_MODE_CMD                   0x02                            //查询MCU 设定的模块工作模式
#define         WIFI_STATE_CMD                  0x03                            //wifi工作状态
#define         WIFI_RESET_CMD                  0x04                            //重置wifi
#define         DATA_QUERT_CMD                  0x06                            //命令下发
#define         STATE_UPLOAD_CMD                0x07                            //状态上报
#define         STATE_QUERY_CMD                 0x08                            //状态查询
#define         UPDATE_START_CMD                0x0a                            //升级开始
#define         UPDATE_TRANS_CMD                0x0b                            //升级传输
#define         GET_ONLINE_TIME_CMD             0x0c                            //获取系统时间(格林时间)
#define         WIFI_TEST_CMD                   0x0e                            //wifi功能测试（扫描指定路由）
#define         GET_MODULE_REMAIN_MEMORY_CMD    0x0f                            //获取模块内存
#define         GET_LOCAL_TIME_CMD              0x1c                            //获取本地时间
#define         GET_ROUTE_RSSI_CMD              0x24                            //获取当前WIFI信号强度
#define         HEAT_BEAT_STOP                  0x25                            //关闭WIFI模组心跳
#define         GET_WIFI_STATUS_CMD             0x2b                            //获取当前wifi联网状态
#define         GET_MAC_CMD                     0x2d                            //获取模块mac
#define         MODULE_EXTEND_FUN_CMD           0x34                            //模块拓展服务
#define         HOMEKIT_FUN_CMD                 0x36                            //HomeKit相关功能
#define         NEW_FUNCTION_CMD                0x37                            //新功能命令


//=============================================================================
//子命令
//=============================================================================
#ifdef MODULE_EXTEND_FUN_CMD //模块拓展服务
#define     SUB_CMD_GET_MODULE_INFOR            0x07                            //获取WIFI模块相关数据信息
#endif

#ifdef HOMEKIT_FUN_CMD //HomeKit相关功能
#define     HK_SUB_CMD_CFG_QUERY                0x01                            //HomeKit配置查询
#define     HK_SUB_CMD_SERVICE_CFG              0x02                            //HomeKit服务配置
#define     HK_SUB_CMD_CTRL_ISSUE               0x03                            //HomeKit命令下发
#define     HK_SUB_CMD_START_UPLOAD             0x04                            //HomeKit状态上报
#define     HK_SUB_CMD_CHARACTER_CFG            0x05                            //HomeKit可选特性配置
#define     HK_SUB_CMD_CHARACTER_VALID_CFG      0x06                            //HomeKit特性有效值配置
#endif

#ifdef NEW_FUNCTION_CMD //新功能命令
#define     NEW_FUNC_SET_INFO_SUBCMD            0x00                            //设备新功能设置通知命令
#endif




//=============================================================================
#define MCU_RX_VER              0x00                                            //模块发送帧协议版本号
#define MCU_TX_VER              0x03                                            //MCU 发送帧协议版本号(默认)
#define PROTOCOL_HEAD           0x07                                            //固定协议头长度
#define FRAME_FIRST             0x55                                            //帧头第一字节
#define FRAME_SECOND            0xaa                                            //帧头第二字节
//============================================================================= 
SYSTEM_EXTERN volatile u8 wifi_data_process_buf[PROTOCOL_HEAD + WIFI_DATA_PROCESS_LMT];     //串口数据处理缓存
SYSTEM_EXTERN volatile u8 wifi_uart_rx_buf[PROTOCOL_HEAD + WIFI_UART_RECV_BUF_LMT];         //串口接收缓存
SYSTEM_EXTERN volatile u8 wifi_uart_tx_buf[PROTOCOL_HEAD + WIFIR_UART_SEND_BUF_LMT];        //串口发送缓存
//
SYSTEM_EXTERN volatile u8 *rx_buf_in;
SYSTEM_EXTERN volatile u8 *rx_buf_out;

SYSTEM_EXTERN volatile u8 stop_update_flag;                                                 //ENABLE:停止一切数据上传  DISABLE:恢复一切数据上传

#ifndef WIFI_CONTROL_SELF_MODE
SYSTEM_EXTERN volatile u8 reset_wifi_flag;                                                  //重置wifi标志(TRUE:成功/FALSE:失败)
SYSTEM_EXTERN volatile u8 ty_wifi_work_state;                                               //wifi模块当前tuya网络状态
SYSTEM_EXTERN volatile u8 hk_wifi_work_state;                                               //wifi模块当前homekit网络状态
#endif


/**
 * @brief  写wifi_uart字节
 * @param[in] {dest} 缓存区其实地址
 * @param[in] {byte} 写入字节值
 * @return 写入完成后的总长度
 */
u16 set_wifi_uart_byte(u16 dest, u8 byte);

/**
 * @brief  写wifi_uart_buffer
 * @param[in] {dest} 目标地址
 * @param[in] {src} 源地址
 * @param[in] {len} 数据长度
 * @return 写入结束的缓存地址
 */
u16 set_wifi_uart_buffer(u16 dest, const u8 *src, u16 len);

/**
 * @brief  计算校验和
 * @param[in] {pack} 数据源指针
 * @param[in] {pack_len} 计算校验和长度
 * @return 校验和
 */
u8 get_check_sum(u8 *pack, u16 pack_len);

/**
 * @brief  向wifi串口发送一帧数据
 * @param[in] {fr_type} 帧类型
 * @param[in] {fr_ver} 帧版本
 * @param[in] {len} 数据长度
 * @return Null
 */
void wifi_uart_write_frame(u8 fr_type, u8 fr_ver, u16 len);

/**
 * @brief  数据帧处理
 * @param[in] {offset} 数据起始位
 * @return Null
 */
void data_handle(u16 offset);

/**
 * @brief  判断串口接收缓存中是否有数据
 * @param  Null
 * @return 是否有数据
 */
u8 with_data_rxbuff(void);

/**
 * @brief  读取队列1字节数据
 * @param  Null
 * @return Read the data
 */
u8 take_byte_rxbuff(void);
#endif
  
  
