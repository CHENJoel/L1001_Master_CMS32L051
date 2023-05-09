/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2030, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    mcu_api.c
 * @author  涂鸦综合协议开发组
 * @version v1.0.4
 * @date    2021.6.1
 * @brief   用户需要主动调用的函数都在该文件内
 */

/****************************** 免责声明 ！！！ *******************************
由于MCU类型和编译环境多种多样，所以此代码仅供参考，用户请自行把控最终代码质量，
涂鸦不对MCU功能结果负责。
******************************************************************************/

#define MCU_API_GLOBAL

#include "wifi.h"

/**
 * @brief  hex转bcd
 * @param[in] {Value_H} 高字节
 * @param[in] {Value_L} 低字节
 * @return 转换完成后数据
 */
u8 hex_to_bcd(u8 Value_H,u8 Value_L)
{
    u8 bcd_value;
    
    if((Value_H >= '0') && (Value_H <= '9'))
        Value_H -= '0';
    else if((Value_H >= 'A') && (Value_H <= 'F'))
        Value_H = Value_H - 'A' + 10;
    else if((Value_H >= 'a') && (Value_H <= 'f'))
        Value_H = Value_H - 'a' + 10;
     
    bcd_value = Value_H & 0x0f;
    
    bcd_value <<= 4;
    if((Value_L >= '0') && (Value_L <= '9'))
        Value_L -= '0';
    else if((Value_L >= 'A') && (Value_L <= 'F'))
        Value_L = Value_L - 'a' + 10;
    else if((Value_L >= 'a') && (Value_L <= 'f'))
        Value_L = Value_L - 'a' + 10;
    
    bcd_value |= Value_L & 0x0f;

    return bcd_value;
}

/**
 * @brief  将int类型拆分四个字节
 * @param[in] {number} 4字节原数据
 * @param[out] {value} 处理完成后4字节数据
 * @return Null
 */
void int_to_byte(u32 number,u8 value[4])
{
    value[0] = number >> 24;
    value[1] = number >> 16;
    value[2] = number >> 8;
    value[3] = number & 0xff;
}

/**
 * @brief  将4字节合并为1个32bit变量
 * @param[in] {value} 4字节数组
 * @return 合并完成后的32bit变量
 */
u32 byte_to_int(const u8 value[4])
{
    u32 nubmer = 0;

    nubmer = (u32)value[0];
    nubmer <<= 8;
    nubmer |= (u32)value[1];
    nubmer <<= 8;
    nubmer |= (u32)value[2];
    nubmer <<= 8;
    nubmer |= (u32)value[3];
    
    return nubmer;
}

/**
 * @brief  把src所指内存区域的前count个字节设置成字符c
 * @param[out] {src} 待设置的内存首地址
 * @param[in] {ch} 设置的字符
 * @param[in] {count} 设置的内存长度
 * @return 待设置的内存首地址
 */
void *my_memset(void *src,u8 ch,u16 count)
{
    u8 *tmp = (u8 *)src;
    
    if(src == NULL) {
        return NULL;
    }
    
    while(count --) {
        *tmp ++ = ch;
    }
    
    return src;
}

/**
 * @brief  内存拷贝
 * @param[out] {dest} 目标地址
 * @param[in] {src} 源地址
 * @param[in] {count} 拷贝数据个数
 * @return 数据处理完后的源地址
 */
void *my_memcpy(void *dest, const void *src, u16 count)  
{  
    u8 *pdest = (u8 *)dest;  
    const u8 *psrc  = (const u8 *)src;  
    u16 i;
    
    if(dest == NULL || src == NULL) { 
        return NULL;
    }
    
    if((pdest <= psrc) || (pdest > psrc + count)) {  
        for(i = 0; i < count; i ++) {  
            pdest[i] = psrc[i];  
        }  
    }else {
        for(i = count; i > 0; i --) {  
            pdest[i - 1] = psrc[i - 1];  
        }  
    }  
    
    return dest;  
}

/**
 * @brief  求字符串长度
 * @param[in] {str} 字符串地址
 * @return 数据长度
 */
u32 my_strlen(i8 *str)  
{
    u32 len = 0;
    if(str == NULL) { 
        return 0;
    }
    
    for(len = 0; *str ++ != '\0'; ) {
        len ++;
    }
    
    return len;
}

/**
 * @brief  字符串拷贝
 * @param[in] {dest} 目标地址
 * @param[in] {src} 源地址
 * @return 数据处理完后的源地址
 */
i8 *my_strcpy(i8 *dest, const i8 *src)  
{
    i8 *p = dest;
    
    if(dest == NULL || src == NULL) { 
        return NULL;
    }
    
    while(*src!='\0') {
        *dest++ = *src++;
    }
    *dest = '\0';
    return p;
}

/**
 * @brief  字符串比较
 * @param[in] {s1} 字符串 1
 * @param[in] {s2} 字符串 2
 * @return 大小比较值
 * -         0:s1=s2
 * -         <0:s1<s2
 * -         >0:s1>s2
 */
i32 my_strcmp(i8 *s1 , i8 *s2)
{
    while( *s1 && *s2 && *s1 == *s2 ) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

/**
 * @brief  raw型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @param[in] {len} 数据长度
 * @return Null
 * @note   Null
 */
u8 mcu_dp_raw_update(u8 dpid,const u8 value[],u16 len)
{
    u16 send_len = 0;
    
    if(stop_update_flag == ENABLE)
      return SUCCESS;
    //
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_RAW);
    //
    send_len = set_wifi_uart_byte(send_len,len / 0x100);
    send_len = set_wifi_uart_byte(send_len,len % 0x100);
    //
    send_len = set_wifi_uart_buffer(send_len,(u8 *)value,len);
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  bool型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值
 * @return Null
 * @note   Null
 */
u8 mcu_dp_bool_update(u8 dpid,u8 value)
{
    u16 send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_BOOL);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    send_len = set_wifi_uart_byte(send_len,1);
    //
    if(value == FALSE) {
        send_len = set_wifi_uart_byte(send_len,FALSE);
    }else {
        send_len = set_wifi_uart_byte(send_len,1);
    }
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD, MCU_TX_VER, send_len);
    
    return SUCCESS;
}

/**
 * @brief  value型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值
 * @return Null
 * @note   Null
 */
u8 mcu_dp_value_update(u8 dpid,u32 value)
{
    u16 send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_VALUE);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    send_len = set_wifi_uart_byte(send_len,4);
    //
    send_len = set_wifi_uart_byte(send_len,value >> 24);
    send_len = set_wifi_uart_byte(send_len,value >> 16);
    send_len = set_wifi_uart_byte(send_len,value >> 8);
    send_len = set_wifi_uart_byte(send_len,value & 0xff);
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  string型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @param[in] {len} 数据长度
 * @return Null
 * @note   Null
 */
u8 mcu_dp_string_update(u8 dpid,const u8 value[],u16 len)
{
    u16 send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    //
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_STRING);
    //
    send_len = set_wifi_uart_byte(send_len,len / 0x100);
    send_len = set_wifi_uart_byte(send_len,len % 0x100);
    //
    send_len = set_wifi_uart_buffer(send_len,(u8 *)value,len);
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  enum型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值
 * @return Null
 * @note   Null
 */
u8 mcu_dp_enum_update(u8 dpid,u8 value)
{
    u16 send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_ENUM);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    send_len = set_wifi_uart_byte(send_len,1);
    //
    send_len = set_wifi_uart_byte(send_len,value);
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  fault型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值
 * @return Null
 * @note   Null
 */
u8 mcu_dp_fault_update(u8 dpid,u32 value)
{
    u16 send_len = 0;
     
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_BITMAP);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    
    if((value | 0xff) == 0xff) {
        send_len = set_wifi_uart_byte(send_len,1);
        send_len = set_wifi_uart_byte(send_len,value);
    }else if((value | 0xffff) == 0xffff) {
        send_len = set_wifi_uart_byte(send_len,2);
        send_len = set_wifi_uart_byte(send_len,value >> 8);
        send_len = set_wifi_uart_byte(send_len,value & 0xff);
    }else {
        send_len = set_wifi_uart_byte(send_len,4);
        send_len = set_wifi_uart_byte(send_len,value >> 24);
        send_len = set_wifi_uart_byte(send_len,value >> 16);
        send_len = set_wifi_uart_byte(send_len,value >> 8);
        send_len = set_wifi_uart_byte(send_len,value & 0xff);
    }    
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD, MCU_TX_VER, send_len);

    return SUCCESS;
}


/**
 * @brief  mcu获取bool型下发dp值
 * @param[in] {value} dp数据缓冲区地址
 * @param[in] {len} dp数据长度
 * @return 当前dp值
 * @note   Null
 */
u8 mcu_get_dp_download_bool(const u8 value[],u16 len)
{
    return(value[0]);
}

/**
 * @brief  mcu获取value型下发dp值
 * @param[in] {value} dp数据缓冲区地址
 * @param[in] {len} dp数据长度
 * @return 当前dp值
 * @note   Null
 */
u8 mcu_get_dp_download_enum(const u8 value[],u16 len)
{
    return(value[0]);
}

/**
 * @brief  mcu获取enum型下发dp值
 * @param[in] {value} dp数据缓冲区地址
 * @param[in] {len} dp数据长度
 * @return 当前dp值
 * @note   Null
 */
u32 mcu_get_dp_download_value(const u8 value[],u16 len)
{
    return(byte_to_int(value));
}

/**
 * @brief  串口接收数据暂存处理
 * @param[in] {value} 串口收到的1字节数据
 * @return Null
 * @note   在MCU串口处理函数中调用该函数,并将接收到的数据作为参数传入
 */
void uart_receive_input(u8 value)
{
    //#error "请在串口接收中断中调用uart_receive_input(value),串口数据由MCU_SDK处理,用户请勿再另行处理,完成后删除该行" 
    
    if(1 == rx_buf_out - rx_buf_in) {
        //串口接收缓存已满
    }else if((rx_buf_in > rx_buf_out) && ((rx_buf_in - rx_buf_out) >= sizeof(wifi_uart_rx_buf))) {
        //串口接收缓存已满
    }else {
        //串口接收缓存未满
        if(rx_buf_in >= (u8 *)(wifi_uart_rx_buf + sizeof(wifi_uart_rx_buf))) {
            rx_buf_in = (u8 *)(wifi_uart_rx_buf);
        }
        
        *rx_buf_in ++ = value;
    }
}

/**
 * @brief  wifi串口数据处理服务
 * @param  Null
 * @return Null
 * @note   在MCU主函数while循环中调用该函数
 */
void wifi_uart_service(void)
{
    //#error "请直接在main函数的while(1){}中添加wifi_uart_service(),调用该函数不要加任何条件判断,完成后删除该行" 
    static u16 rx_in = 0;
    u16 offset = 0;
    u16 rx_value_len = 0;
    
    while((rx_in < sizeof(wifi_data_process_buf)) && with_data_rxbuff() > 0) {
        wifi_data_process_buf[rx_in ++] = take_byte_rxbuff();
    }
    
    if(rx_in < PROTOCOL_HEAD)
        return;
    
    while((rx_in - offset) >= PROTOCOL_HEAD) {
        if(wifi_data_process_buf[offset + HEAD_FIRST] != FRAME_FIRST) {
            offset ++;
            continue;
        }
        
        if(wifi_data_process_buf[offset + HEAD_SECOND] != FRAME_SECOND) {
            offset ++;
            continue;
        }  
        
        if(wifi_data_process_buf[offset + PROTOCOL_VERSION] != MCU_RX_VER) {
            offset += 2;
            continue;
        }      
        
        rx_value_len = wifi_data_process_buf[offset + LENGTH_HIGH] * 0x100;
        rx_value_len += (wifi_data_process_buf[offset + LENGTH_LOW] + PROTOCOL_HEAD);
        if(rx_value_len > sizeof(wifi_data_process_buf) + PROTOCOL_HEAD) {
            offset += 3;
            continue;
        }
        
        if((rx_in - offset) < rx_value_len) {
            break;
        }
        
        //数据接收完成
        if(get_check_sum((u8 *)wifi_data_process_buf + offset,rx_value_len - 1) != wifi_data_process_buf[offset + rx_value_len - 1]) {
            //校验出错
            //printf("crc error (crc:0x%X  but data:0x%X)\r\n",get_check_sum((u8 *)wifi_data_process_buf + offset,rx_value_len - 1),wifi_data_process_buf[offset + rx_value_len - 1]);
            offset += 3;
            continue;
        }
        
        data_handle(offset);
        offset += rx_value_len;
    }//end while

    rx_in -= offset;
    if(rx_in > 0) {
        my_memcpy((char *)wifi_data_process_buf, (const char *)wifi_data_process_buf + offset, rx_in);
    }
}

/**
 * @brief  协议串口初始化函数
 * @param  Null
 * @return Null
 * @note   在MCU初始化代码中调用该函数
 */
void wifi_protocol_init(void)
{
    #error " 请在main函数中添加wifi_protocol_init()完成wifi协议初始化,并删除该行"
    rx_buf_in = (u8 *)wifi_uart_rx_buf;
    rx_buf_out = (u8 *)wifi_uart_rx_buf;
    
    stop_update_flag = DISABLE;
    
#ifndef WIFI_CONTROL_SELF_MODE
    ty_wifi_work_state = WIFI_SATE_UNKNOW;
    hk_wifi_work_state = WIFI_SATE_UNKNOW;
#endif
}



#ifndef WIFI_CONTROL_SELF_MODE
/**
 * @brief  MCU获取复位wifi成功标志
 * @param  Null
 * @return 复位标志
 * -           0(RESET_WIFI_ERROR):失败
 * -           1(RESET_WIFI_SUCCESS):成功
 * @note   1:MCU主动调用mcu_reset_wifi()后调用该函数获取复位状态
 *         2:如果为模块自处理模式,MCU无须调用该函数
 */
u8 mcu_get_reset_wifi_flag(void)
{
    return reset_wifi_flag;
}

/**
 * @brief  MCU主动重置wifi工作模式
 * @param  Null
 * @return Null
 * @note   1:MCU主动调用,通过mcu_get_reset_wifi_flag()函数获取重置wifi是否成功
 *         2:如果为模块自处理模式,MCU无须调用该函数
 */
void mcu_reset_wifi(void)
{
    reset_wifi_flag = RESET_WIFI_ERROR;
    
    wifi_uart_write_frame(WIFI_RESET_CMD, MCU_TX_VER, 0);
}

/**
 * @brief  获取当前wifi tuya网络状态
 * @param  Null
 * @return tuya网络状态
 * -          CONFIG_STATE: 配置状态
 * -          WIFI_NOT_CONNECTED: WIFI配置成功但未连上路由器
 * -          WIFI_CONNECTED: WIFI配置成功且连上路由器
 * -          WIFI_CONN_CLOUD: WIFI已经连接上云服务器
 * @note   如果为模块自处理模式,MCU无须调用该函数
 */
u8 get_wifi_tuya_state(void)
{
    return ty_wifi_work_state;
}

/**
 * @brief  获取当前wifi homekit网络状态
 * @param  Null
 * @return homekit网络状态
 * -          CONFIG_STATE: 配置状态
 * -          WIFI_NOT_CONNECTED: WIFI配置成功但未连APP
 * -          WIFI_CONNECTED: WIFI配置成功且连上APP
 * @note   如果为模块自处理模式,MCU无须调用该函数
 */
u8 get_wifi_homekit_state(void)
{
    return hk_wifi_work_state;
}
#endif

#ifdef SUPPORT_GREEN_TIME
/**
 * @brief  MCU获取格林时间
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_get_green_time(void)
{
    wifi_uart_write_frame(GET_ONLINE_TIME_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/**
 * @brief  MCU获取系统时间,用于校对本地时钟
 * @param  Null
 * @return Null
 * @note   MCU主动调用完成后在mcu_write_rtctime函数内校对rtc时钟
 */
void mcu_get_system_time(void)
{
    wifi_uart_write_frame(GET_LOCAL_TIME_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef WIFI_TEST_ENABLE
/**
 * @brief  mcu发起wifi功能测试
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_start_wifitest(void)
{
    wifi_uart_write_frame(WIFI_TEST_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef GET_MODULE_REMAIN_MEMORY_ENABLE
/**
 * @brief  获取 WIFI 模块剩余内存
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void get_module_remain_memory(void)
{
    wifi_uart_write_frame(GET_MODULE_REMAIN_MEMORY_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef GET_ROUTE_RSSI_ENABLE
/**
 * @brief  获取当前WIFI信号强度
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_get_router_rssi(void)
{
  wifi_uart_write_frame(GET_ROUTE_RSSI_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef WIFI_HEARTSTOP_ENABLE
/**
 * @brief  通知WIFI模组关闭心跳
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void wifi_heart_stop(void)
{
    wifi_uart_write_frame(HEAT_BEAT_STOP, MCU_TX_VER, 0);
}
#endif

#ifdef GET_WIFI_STATUS_ENABLE
/**
 * @brief  获取当前wifi联网状态
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_get_wifi_connect_status(void)
{
    wifi_uart_write_frame(GET_WIFI_STATUS_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef GET_MODULE_MAC_ENABLE
/**
 * @brief  获取模块MAC
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_get_module_mac(void)
{
    wifi_uart_write_frame(GET_MAC_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef MODULE_EXTEND_FUN_ENABLE
/**
 * @brief  获取模块相关信息
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_get_module_infor(u8 p_get_inf[], u16 data_len)
{
    u16 send_len = 0;
    send_len = set_wifi_uart_byte(send_len, SUB_CMD_GET_MODULE_INFOR);
    send_len = set_wifi_uart_buffer(send_len, p_get_inf, data_len);
    wifi_uart_write_frame(MODULE_EXTEND_FUN_CMD, MCU_TX_VER, send_len);
}
#endif

