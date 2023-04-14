/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2030, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    system.c
 * @author  涂鸦综合协议开发组
 * @version v1.0.4
 * @date    2021.6.1
 * @brief   串口数据处理，用户无需关心该文件实现内容
 */

/****************************** 免责声明 ！！！ *******************************
由于MCU类型和编译环境多种多样，所以此代码仅供参考，用户请自行把控最终代码质量，
涂鸦不对MCU功能结果负责。
******************************************************************************/

#define SYSTEM_GLOBAL

#include "wifi.h"

extern const DOWNLOAD_CMD_S download_cmd[];



/**
 * @brief  写wifi_uart字节
 * @param[in] {dest} 缓存区其实地址
 * @param[in] {byte} 写入字节值
 * @return 写入完成后的总长度
 */
u16 set_wifi_uart_byte(u16 dest, u8 byte)
{
    u8 *obj = (u8 *)wifi_uart_tx_buf + DATA_START + dest;
    
    *obj = byte;
    dest += 1;
    
    return dest;
}

/**
 * @brief  写wifi_uart_buffer
 * @param[in] {dest} 目标地址
 * @param[in] {src} 源地址
 * @param[in] {len} 数据长度
 * @return 写入结束的缓存地址
 */
u16 set_wifi_uart_buffer(u16 dest, const u8 *src, u16 len)
{
    u8 *obj = (u8 *)wifi_uart_tx_buf + DATA_START + dest;
    
    my_memcpy(obj,src,len);
    
    dest += len;
    return dest;
}

/**
 * @brief  计算校验和
 * @param[in] {pack} 数据源指针
 * @param[in] {pack_len} 计算校验和长度
 * @return 校验和
 */
u8 get_check_sum(u8 *pack, u16 pack_len)
{
    u16 i;
    u8 check_sum = 0;
    
    for(i = 0; i < pack_len; i ++) {
        check_sum += *pack ++;
    }
    
    return check_sum;
}

/**
 * @brief  串口发送一段数据
 * @param[in] {in} 发送缓存指针
 * @param[in] {len} 数据发送长度
 * @return Null
 */
static void wifi_uart_write_data(u8 *in, u16 len)
{
  if((NULL == in) || (0 == len)) {
      return;
  }
  
  while(len --) {
      uart_transmit_output(*in);
      in ++;
  }
}

/**
 * @brief  向wifi串口发送一帧数据
 * @param[in] {fr_type} 帧类型
 * @param[in] {fr_ver} 帧版本
 * @param[in] {len} 数据长度
 * @return Null
 */
void wifi_uart_write_frame(u8 fr_type, u8 fr_ver, u16 len)
{
    u8 check_sum = 0;
    
    if(len + PROTOCOL_HEAD > sizeof(wifi_uart_tx_buf)) {
        //串口发送缓存已满
    }
    
    wifi_uart_tx_buf[HEAD_FIRST] = 0x55;
    wifi_uart_tx_buf[HEAD_SECOND] = 0xaa;
    wifi_uart_tx_buf[PROTOCOL_VERSION] = fr_ver;
    wifi_uart_tx_buf[FRAME_TYPE] = fr_type;
    wifi_uart_tx_buf[LENGTH_HIGH] = len >> 8;
    wifi_uart_tx_buf[LENGTH_LOW] = len & 0xff;
    
    len += PROTOCOL_HEAD;
    check_sum = get_check_sum((u8 *)wifi_uart_tx_buf, len - 1);
    wifi_uart_tx_buf[len - 1] = check_sum;
    
    wifi_uart_write_data((u8 *)wifi_uart_tx_buf, len);
}


#ifdef SUPPORT_MCU_FIRM_UPDATE
#if MCU_FIRMWARE_BACKUP_AREA_TYPE == 1
/**
 * @brief  MCU设置新功能
 * @param  Null
 * @return Null
 */
static void mcu_set_new_func(void)
{
    u16 send_len = 0;
    u8 strlen = 0;
    u8 str[32] = {0};
    
    send_len = set_wifi_uart_byte(send_len, NEW_FUNC_SET_INFO_SUBCMD);
    
    send_len = set_wifi_uart_buffer(send_len, "{", my_strlen("{"));
    
    sprintf((char *)str,"\"mcu_ota\":%d", MCU_FIRMWARE_BACKUP_AREA_TYPE);
    send_len = set_wifi_uart_buffer(send_len, str, my_strlen((i8*)str));
    
    send_len = set_wifi_uart_buffer(send_len, "}", my_strlen("}"));
    
    wifi_uart_write_frame(NEW_FUNCTION_CMD, MCU_TX_VER, send_len);
}
#endif
#endif


/**
 * @brief  心跳包检测
 * @param  Null
 * @return Null
 */
static void heat_beat_check(void)
{
    u16 send_len = 0;
    static u8 mcu_reset_state = FALSE;
    
    if(FALSE == mcu_reset_state) {
        send_len = set_wifi_uart_byte(send_len, FALSE);
        mcu_reset_state = TRUE;
    }else {
        send_len = set_wifi_uart_byte(send_len, TRUE);
    }
    
    wifi_uart_write_frame(HEAT_BEAT_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  产品信息上传
 * @param  Null
 * @return Null
 */
static void product_info_update(void)
{
    u16 send_len = 0;
    u8 str[32] = {0};
    
    sprintf((char *)str,"{\"p\":\"%s\"",PRODUCT_KEY);
    send_len = set_wifi_uart_buffer(send_len, str, my_strlen(str));
    sprintf((char *)str,",\"v\":\"%s\"",MCU_VER);
    send_len = set_wifi_uart_buffer(send_len, str, my_strlen(str));
#ifdef HOMEKIT_PRODUCT_TYPE
    sprintf((char *)str,",\"pt\":%d",HOMEKIT_PRODUCT_TYPE);
    send_len = set_wifi_uart_buffer(send_len, str, my_strlen(str));
#endif
  
    send_len = set_wifi_uart_buffer(send_len, "}", my_strlen("}"));
    
    wifi_uart_write_frame(PRODUCT_INFO_CMD, MCU_TX_VER, send_len);
    
#ifdef SUPPORT_MCU_FIRM_UPDATE
#if MCU_FIRMWARE_BACKUP_AREA_TYPE == 1
    mcu_set_new_func();
#endif
#endif
}

/**
 * @brief  mcu查询mcu和wifi的工作模式
 * @param  Null
 * @return Null
 */
static void get_mcu_wifi_mode(void)
{
    u16 send_len = 0;
    
#ifdef WIFI_CONTROL_SELF_MODE                                   //模块自处理
    send_len = set_wifi_uart_byte(length, TY_STATE_LED);
    send_len = set_wifi_uart_byte(length, HK_STATE_LED);
    send_len = set_wifi_uart_byte(length, WF_RESERT_KEY);
#endif
    
    wifi_uart_write_frame(WORK_MODE_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  获取制定DPID在数组中的序号
 * @param[in] {dpid} dpid
 * @return dp序号
 */
static u8 get_dowmload_dpid_index(u8 dpid)
{
    u8 index;
    u8 total = get_download_cmd_total();
    
    for(index = 0; index < total; index ++) {
        if(download_cmd[index].dp_id == dpid) {
            break;
        }
    }
    
    return index;
}

/**
 * @brief  下发数据处理
 * @param[in] {value} 下发数据源指针
 * @return 返回数据处理结果
 */
static u8 data_point_handle(const u8 value[])
{
    u8 dp_id,index;
    u8 dp_type;
    u8 ret;
    u16 dp_len;
    
    dp_id = value[0];
    dp_type = value[1];
    dp_len = value[2] * 0x100;
    dp_len += value[3];
    
    index = get_dowmload_dpid_index(dp_id);

    if(dp_type != download_cmd[index].dp_type) {
        //错误提示
        return FALSE;
    }else {
        ret = dp_download_handle(dp_id,value + 4,dp_len);
    }
    
    return ret;
}


/**
 * @brief  数据帧处理
 * @param[in] {offset} 数据起始位
 * @return Null
 */
void data_handle(u16 offset)
{
#ifdef SUPPORT_MCU_FIRM_UPDATE
    u8 *firmware_addr = NULL;
    static u16 firm_size;                                            //升级包一包的大小
    static u32 firm_length;                                           //MCU升级文件长度
    static u8 firm_update_flag = 0;                                  //MCU升级标志
    u32 dp_len;
    u8 firm_flag;                                                    //升级包大小标志
#else
    u16 dp_len;
#endif
  
    u8 ret;
    u16 i,total_len;
    u8 cmd_type = wifi_data_process_buf[offset + FRAME_TYPE];
    u8 result;
    u32 module_memory;


#ifdef WIFI_TEST_ENABLE
    u8 rssi;
#endif
    
    switch(cmd_type)
    {
        case HEAT_BEAT_CMD:                                     //心跳包
            heat_beat_check();
        break;
    
        case PRODUCT_INFO_CMD:                                  //产品信息
            product_info_update();
        break;
    
        case WORK_MODE_CMD:                                     //查询MCU设定的模块工作模式
            get_mcu_wifi_mode();
        break;
    
#ifndef WIFI_CONTROL_SELF_MODE
        case WIFI_STATE_CMD:                                    //wifi工作状态
            update_wifi_status(wifi_data_process_buf[offset + DATA_START], wifi_data_process_buf[offset + DATA_START + 1]);
            wifi_uart_write_frame(WIFI_STATE_CMD, MCU_TX_VER, 0);
        break;

        case WIFI_RESET_CMD:                                    //重置wifi(wifi返回成功)
            reset_wifi_flag = RESET_WIFI_SUCCESS;
        break;
#endif
    
        case DATA_QUERT_CMD:                                    //命令下发
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
    
            for(i = 0;i < total_len; ) {
                dp_len = wifi_data_process_buf[offset + DATA_START + i + 2] * 0x100;
                dp_len += wifi_data_process_buf[offset + DATA_START + i + 3];
                //
                ret = data_point_handle((u8 *)wifi_data_process_buf + offset + DATA_START + i);
      
                if(SUCCESS == ret) {
                    //成功提示
                }else {
                    //错误提示
                }
      
                i += (dp_len + 4);
            }
        break;
    
        case STATE_QUERY_CMD:                                   //状态查询
            all_data_update();
        break;
    
#ifdef SUPPORT_MCU_FIRM_UPDATE
        case UPDATE_START_CMD:                                  //升级开始
            //获取升级包大小全局变量
            firm_flag = PACKAGE_SIZE;
            if(firm_flag == 0) {
                firm_size = 256;
            }else if(firm_flag == 1) {
                firm_size = 512;
            }else if(firm_flag == 2) { 
                firm_size = 1024;
            }

            firm_length = wifi_data_process_buf[offset + DATA_START];
            firm_length <<= 8;
            firm_length |= wifi_data_process_buf[offset + DATA_START + 1];
            firm_length <<= 8;
            firm_length |= wifi_data_process_buf[offset + DATA_START + 2];
            firm_length <<= 8;
            firm_length |= wifi_data_process_buf[offset + DATA_START + 3];
            
            upgrade_package_choose(PACKAGE_SIZE);
            firm_update_flag = UPDATE_START_CMD;
        break;
    
        case UPDATE_TRANS_CMD:                                  //升级传输
            if(firm_update_flag == UPDATE_START_CMD) {
                //停止一切数据上报
                stop_update_flag = ENABLE;
      
                total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
      
                dp_len = wifi_data_process_buf[offset + DATA_START];
                dp_len <<= 8;
                dp_len |= wifi_data_process_buf[offset + DATA_START + 1];
                dp_len <<= 8;
                dp_len |= wifi_data_process_buf[offset + DATA_START + 2];
                dp_len <<= 8;
                dp_len |= wifi_data_process_buf[offset + DATA_START + 3];
      
                firmware_addr = (u8 *)wifi_data_process_buf;
                firmware_addr += (offset + DATA_START + 4);
      
                if((total_len == 4) && (dp_len == firm_length)) {
                    //最后一包
                    ret = mcu_firm_update_handle(firmware_addr,dp_len,0);
                    firm_update_flag = 0;
                }else if((total_len - 4) <= firm_size) {
                    ret = mcu_firm_update_handle(firmware_addr,dp_len,total_len - 4);
                }else {
                    firm_update_flag = 0;
                    ret = ERROR;
                }
      
                if(ret == SUCCESS) {
                    wifi_uart_write_frame(UPDATE_TRANS_CMD, MCU_TX_VER, 0);
                }
                //恢复一切数据上报
                stop_update_flag = DISABLE;    
            }
        break;
#endif

#ifdef SUPPORT_GREEN_TIME
        case GET_ONLINE_TIME_CMD:                               //获取格林时间
            mcu_get_greentime((u8 *)(wifi_data_process_buf + offset + DATA_START));
        break;
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
        case GET_LOCAL_TIME_CMD:                               //获取本地时间
            mcu_write_rtctime((u8 *)(wifi_data_process_buf + offset + DATA_START));
        break;
#endif
 
#ifdef WIFI_TEST_ENABLE
        case WIFI_TEST_CMD:                                     //wifi功能测试（扫描指定路由）
            result = wifi_data_process_buf[offset + DATA_START];
            rssi = wifi_data_process_buf[offset + DATA_START + 1];
            wifi_test_result(result, rssi);
        break;
#endif

#ifdef GET_MODULE_REMAIN_MEMORY_ENABLE
        case GET_MODULE_REMAIN_MEMORY_CMD:                      //获取模块内存
            module_memory = wifi_data_process_buf[offset + DATA_START] << 3;
            module_memory += wifi_data_process_buf[offset + DATA_START + 1] << 2;
            module_memory += wifi_data_process_buf[offset + DATA_START + 2] << 1;
            module_memory += wifi_data_process_buf[offset + DATA_START + 3] << 0;

            remain_memory_result(module_memory);
        break;
#endif

#ifdef GET_ROUTE_RSSI_ENABLE
        case GET_ROUTE_RSSI_CMD:                                //获取当前WIFI信号强度
            get_router_rssi_result(wifi_data_process_buf[offset + DATA_START]);
        break;
#endif

#ifdef GET_WIFI_STATUS_ENABLE
        case GET_WIFI_STATUS_CMD:                               //获取当前wifi联网状态
            update_wifi_status(wifi_data_process_buf[offset + DATA_START], wifi_data_process_buf[offset + DATA_START + 1]);
        break;
#endif

#ifdef GET_MODULE_MAC_ENABLE
        case GET_MAC_CMD:                                       //获取模块mac
            mcu_get_mac((u8 *)(wifi_data_process_buf + offset + DATA_START));
        break;
#endif

#ifdef MODULE_EXTEND_FUN_ENABLE
        case MODULE_EXTEND_FUN_CMD:                             //模块拓展服务
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            module_extend_function((u8 *)(wifi_data_process_buf + offset + DATA_START), total_len);
        break;
#endif

#ifdef HOMEKIT_PRODUCT_TYPE
        case HOMEKIT_FUN_CMD:                                   //HomeKit相关功能
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            homekit_function((u8 *)(wifi_data_process_buf + offset + DATA_START), total_len);
        break;
#endif

#ifdef SUPPORT_MCU_FIRM_UPDATE
#if MCU_FIRMWARE_BACKUP_AREA_TYPE == 1
        case NEW_FUNCTION_CMD:                                   //新功能命令
            total_len = (wifi_data_process_buf[offset + LENGTH_HIGH] << 8) | wifi_data_process_buf[offset + LENGTH_LOW];
            mcu_set_new_func_result((u8 *)(wifi_data_process_buf + offset + DATA_START), total_len);
        break;
#endif
#endif
        
        
        default:break;
    }
}

/**
 * @brief  判断串口接收缓存中是否有数据
 * @param  Null
 * @return 是否有数据
 */
u8 with_data_rxbuff(void)
{
    if(rx_buf_in != rx_buf_out)
        return 1;
    else
        return 0;
}

/**
 * @brief  读取队列1字节数据
 * @param  Null
 * @return Read the data
 */
u8 take_byte_rxbuff(void)
{
    u8 value;
    
    if(rx_buf_out != rx_buf_in) {
        //有数据
        if(rx_buf_out >= (u8 *)(wifi_uart_rx_buf + sizeof(wifi_uart_rx_buf))) {
            //数据已经到末尾
            rx_buf_out = (u8 *)(wifi_uart_rx_buf);
        }
        
        value = *rx_buf_out ++;   
    }
    
    return value;
}

