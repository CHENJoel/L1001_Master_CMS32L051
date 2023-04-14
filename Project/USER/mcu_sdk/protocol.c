/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2030, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    protocol.c
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

/******************************************************************************
                                移植须知:
1:MCU必须在while中直接调用mcu_api.c内的wifi_uart_service()函数
2:程序正常初始化完成后,建议不进行关串口中断,如必须关中断,关中断时间必须短,关中断会引起串口数据包丢失
3:请勿在中断/定时器中断内调用上报函数
******************************************************************************/

#include "wifi.h"

/******************************************************************************
                              第一步:初始化
1:在需要使用到wifi相关文件的文件中include "wifi.h"
2:在MCU初始化中调用mcu_api.c文件中的wifi_protocol_init()函数
3:将MCU串口单字节发送函数填入protocol.c文件中uart_transmit_output函数内,并删除#error
4:在MCU串口接收函数中调用mcu_api.c文件内的uart_receive_input函数,并将接收到的字节作为参数传入
5:单片机进入while循环后调用mcu_api.c文件内的wifi_uart_service()函数
******************************************************************************/

/******************************************************************************
                        1:dp数据点序列类型对照表
          **此为自动生成代码,如在开发平台有相关修改请重新下载MCU_SDK**
******************************************************************************/
const DOWNLOAD_CMD_S download_cmd[] =
{
  {DPID_SWITCH_LED, DP_TYPE_BOOL},
  {DPID_WORK_MODE, DP_TYPE_ENUM},
  {DPID_USER_PROTOCOL, DP_TYPE_RAW},
  {DPID_BRIGHT_VAL, DP_TYPE_VALUE},
  {DPID_SWITCH_MIC, DP_TYPE_BOOL},
  {DPID_SWITCH_INDICATOR, DP_TYPE_BOOL},
  {DPID_EFFECT_NUM, DP_TYPE_VALUE},
  {DPID_PLAYLIST_NUM, DP_TYPE_VALUE},
  {DPID_BRIGHTNESS_AUTO, DP_TYPE_VALUE},
  {DPID_SYSTEM_STATE, DP_TYPE_VALUE},
  {DPID_RUNNING_STATE, DP_TYPE_VALUE},
};


/******************************************************************************
                           2:串口单字节发送函数
请将MCU串口发送函数填入该函数内,并将接收到的数据作为参数传入串口发送函数
******************************************************************************/

/**
 * @brief  串口发送数据
 * @param[in] {value} 串口要发送的1字节数据
 * @return Null
 */
void uart_transmit_output(u8 value)
{
    // #error "请将MCU串口发送函数填入该函数,并删除该行"
    UART1_Send(&value, 1);
/*
    //Example:
    extern void Uart_PutChar(u8 value);
    Uart_PutChar(value);	                                //串口发送函数
*/
}

/******************************************************************************
                           第二步:实现具体用户函数
1:APP下发数据处理
2:数据上报处理
******************************************************************************/

/******************************************************************************
                            1:所有数据上报处理
当前函数处理全部数据上报(包括可下发/可上报和只上报)
  需要用户按照实际情况实现:
  1:需要实现可下发/可上报数据点上报
  2:需要实现只上报数据点上报
此函数为MCU内部必须调用
用户也可调用此函数实现全部数据上报
******************************************************************************/

//自动化生成数据上报函数

/**
 * @brief  系统所有dp点信息上传,实现APP和muc数据同步
 * @param  Null
 * @return Null
 * @note   此函数SDK内部需调用，MCU必须实现该函数内数据上报功能，包括只上报和可上报可下发型数据
 */
void all_data_update(void)
{
    // #error "请在此处理可下发可上报数据及只上报数据示例,处理完成后删除该行"
    mcu_dp_bool_update(DPID_SWITCH_LED,SYS.POWER_SW); //BOOL型数据上报;
    mcu_dp_value_update(DPID_BRIGHT_VAL,SYS.Brightness.Set); //VALUE型数据上报;
    /*
    //此代码为平台自动生成，请按照实际数据修改每个可下发可上报函数和只上报函数
    mcu_dp_bool_update(DPID_SWITCH_LED,当前开关); //BOOL型数据上报;
    mcu_dp_enum_update(DPID_WORK_MODE,当前工作模式); //枚举型数据上报;
    mcu_dp_raw_update(DPID_USER_PROTOCOL,当前自定义协议指针,当前自定义协议数据长度); //RAW型数据上报;
    mcu_dp_value_update(DPID_BRIGHT_VAL,当前亮度值); //VALUE型数据上报;
    mcu_dp_bool_update(DPID_SWITCH_MIC,当前麦克风开关); //BOOL型数据上报;
    mcu_dp_bool_update(DPID_SWITCH_INDICATOR,当前指示灯开关); //BOOL型数据上报;
    mcu_dp_value_update(DPID_EFFECT_NUM,当前当前灯效编号); //VALUE型数据上报;
    mcu_dp_value_update(DPID_PLAYLIST_NUM,当前当前播放列表编号); //VALUE型数据上报;
    mcu_dp_value_update(DPID_BRIGHTNESS_AUTO,当前自动亮度调节); //VALUE型数据上报;
    mcu_dp_value_update(DPID_SYSTEM_STATE,当前系统状态标志); //VALUE型数据上报;
    mcu_dp_value_update(DPID_RUNNING_STATE,当前运行状态标志); //VALUE型数据上报;

    */
#ifdef HOMEKIT_FUN_ENABLE
    homekit_character_upload_all();
#endif
}


/******************************************************************************
                                WARNING!!!
                            2:所有数据上报处理
自动化代码模板函数,具体请用户自行实现数据处理
******************************************************************************/
/*****************************************************************************
函数名称 : dp_download_switch_led_handle
功能描述 : 针对DPID_SWITCH_LED的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_switch_led_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为BOOL
    unsigned char ret;
    //0:off/1:on
    unsigned char switch_led;

    switch_led = mcu_get_dp_download_bool(value,length);
    if(switch_led == 0) {
        //bool off
        SYS.POWER_SW = STA_OFF;
    }else {
        //bool on
        SYS.POWER_SW = STA_ON;
    }

    //There should be a report after processing the DP
    ret = mcu_dp_bool_update(DPID_SWITCH_LED,switch_led);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_work_mode_handle
功能描述 : 针对DPID_WORK_MODE的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_work_mode_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为ENUM
    unsigned char ret;
    unsigned char work_mode;

    work_mode = mcu_get_dp_download_enum(value,length);
    switch(work_mode) {
        case 0:
        break;

        case 1:
        break;

        case 2:
        break;

        case 3:
        break;

        default:

        break;
    }

    //There should be a report after processing the DP
    ret = mcu_dp_enum_update(DPID_WORK_MODE, work_mode);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_user_protocol_handle
功能描述 : 针对DPID_USER_PROTOCOL的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_user_protocol_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为RAW
    unsigned char ret;
    /*
    //RAW type data processing

    */
    RAW_processing(value,length);
    //There should be a report after processing the DP
    ret = mcu_dp_raw_update(DPID_USER_PROTOCOL,value,length);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_bright_val_handle
功能描述 : 针对DPID_BRIGHT_VAL的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_bright_val_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为VALUE
    unsigned char ret;
    unsigned long bright_val;

    bright_val = mcu_get_dp_download_value(value,length);
    /*
    //VALUE type data processing

    */
    SYS.Brightness.Set = bright_val;
    // There should be a report after processing the DP
    ret = mcu_dp_value_update(DPID_BRIGHT_VAL,bright_val);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_switch_mic_handle
功能描述 : 针对DPID_SWITCH_MIC的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_switch_mic_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为BOOL
    unsigned char ret;
    //0:off/1:on
    unsigned char switch_mic;

    switch_mic = mcu_get_dp_download_bool(value,length);
    if(switch_mic == 0) {
        //bool off
    }else {
        //bool on
    }

    //There should be a report after processing the DP
    ret = mcu_dp_bool_update(DPID_SWITCH_MIC,switch_mic);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_switch_indicator_handle
功能描述 : 针对DPID_SWITCH_INDICATOR的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_switch_indicator_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为BOOL
    unsigned char ret;
    //0:off/1:on
    unsigned char switch_indicator;

    switch_indicator = mcu_get_dp_download_bool(value,length);
    if(switch_indicator == 0) {
        //bool off
    }else {
        //bool on
    }

    //There should be a report after processing the DP
    ret = mcu_dp_bool_update(DPID_SWITCH_INDICATOR,switch_indicator);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_effect_num_handle
功能描述 : 针对DPID_EFFECT_NUM的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_effect_num_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为VALUE
    unsigned char ret;
    unsigned long effect_num;

    effect_num = mcu_get_dp_download_value(value,length);
    /*
    //VALUE type data processing

    */

    //There should be a report after processing the DP
    ret = mcu_dp_value_update(DPID_EFFECT_NUM,effect_num);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_playlist_num_handle
功能描述 : 针对DPID_PLAYLIST_NUM的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_playlist_num_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为VALUE
    unsigned char ret;
    unsigned long playlist_num;

    playlist_num = mcu_get_dp_download_value(value,length);
    /*
    //VALUE type data processing

    */

    //There should be a report after processing the DP
    ret = mcu_dp_value_update(DPID_PLAYLIST_NUM,playlist_num);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_brightness_auto_handle
功能描述 : 针对DPID_BRIGHTNESS_AUTO的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_brightness_auto_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为VALUE
    unsigned char ret;
    unsigned long brightness_auto;

    brightness_auto = mcu_get_dp_download_value(value,length);
    /*
    //VALUE type data processing

    */

    //There should be a report after processing the DP
    ret = mcu_dp_value_update(DPID_BRIGHTNESS_AUTO,brightness_auto);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_system_state_handle
功能描述 : 针对DPID_SYSTEM_STATE的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_system_state_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为VALUE
    unsigned char ret;
    unsigned long system_state;

    system_state = mcu_get_dp_download_value(value,length);
    /*
    //VALUE type data processing

    */

    //There should be a report after processing the DP
    ret = mcu_dp_value_update(DPID_SYSTEM_STATE,system_state);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_running_state_handle
功能描述 : 针对DPID_RUNNING_STATE的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_running_state_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为VALUE
    unsigned char ret;
    unsigned long running_state;

    running_state = mcu_get_dp_download_value(value,length);
    /*
    //VALUE type data processing

    */

    //There should be a report after processing the DP
    ret = mcu_dp_value_update(DPID_RUNNING_STATE,running_state);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}




/******************************************************************************
                                WARNING!!!
此部分函数用户请勿修改!!
******************************************************************************/

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
u8 dp_download_handle(u8 dpid,const u8 value[], u16 length)
{
    /*********************************
    当前函数处理可下发/可上报数据调用
    具体函数内需要实现下发数据处理
    完成用需要将处理结果反馈至APP端,否则APP会认为下发失败
    ***********************************/
    u8 ret;
    switch(dpid) {
        case DPID_SWITCH_LED:
            //开关处理函数
            ret = dp_download_switch_led_handle(value,length);
        break;
        case DPID_WORK_MODE:
            //工作模式处理函数
            ret = dp_download_work_mode_handle(value,length);
        break;
        case DPID_USER_PROTOCOL:
            //自定义协议处理函数
            ret = dp_download_user_protocol_handle(value,length);
        break;
        case DPID_BRIGHT_VAL:
            //亮度值处理函数
            ret = dp_download_bright_val_handle(value,length);
        break;
        case DPID_SWITCH_MIC:
            //麦克风开关处理函数
            ret = dp_download_switch_mic_handle(value,length);
        break;
        case DPID_SWITCH_INDICATOR:
            //指示灯开关处理函数
            ret = dp_download_switch_indicator_handle(value,length);
        break;
        case DPID_EFFECT_NUM:
            //当前灯效编号处理函数
            ret = dp_download_effect_num_handle(value,length);
        break;
        case DPID_PLAYLIST_NUM:
            //当前播放列表编号处理函数
            ret = dp_download_playlist_num_handle(value,length);
        break;
        case DPID_BRIGHTNESS_AUTO:
            //自动亮度调节处理函数
            ret = dp_download_brightness_auto_handle(value,length);
        break;
        case DPID_SYSTEM_STATE:
            //系统状态标志处理函数
            ret = dp_download_system_state_handle(value,length);
        break;
        case DPID_RUNNING_STATE:
            //运行状态标志处理函数
            ret = dp_download_running_state_handle(value,length);
        break;


        default:
        break;
    }
    return ret;
}

/**
 * @brief  获取所有dp命令总和
 * @param[in] Null
 * @return 下发命令总和
 * @note   该函数用户不能修改
 */
u8 get_download_cmd_total(void)
{
    return(sizeof(download_cmd) / sizeof(download_cmd[0]));
}


/******************************************************************************
                                WARNING!!!
此代码为SDK内部调用,请按照实际dp数据实现函数内部数据
******************************************************************************/

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
void upgrade_package_choose(u8 package_sz)
{
// // //    #error "请自行实现请自行实现升级包大小选择代码,完成后请删除该行"
    u16 send_len = 0;
    send_len = set_wifi_uart_byte(send_len, package_sz);
    wifi_uart_write_frame(UPDATE_START_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  MCU进入固件升级模式
 * @param[in] {value} 固件缓冲区
 * @param[in] {position} 当前数据包在于固件位置
 * @param[in] {length} 当前固件包长度(固件包长度为0时,表示固件包发送完成)
 * @return Null
 * @note   MCU需要自行实现该功能
 */
u8 mcu_firm_update_handle(const u8 value[],u32 position,u16 length)
{
    // // #error "请自行完成MCU固件升级代码,完成后请删除该行"
    static uint32_t checksum;   // 升级包校验和
    if (length == 0)
    {
        //固件数据发送完成
        if (Download_checksum_verify(checksum)) // 校验
        {
            printf("\rdownload finish!\r\n");
            printf("buffer checksum is 0x%04x\r", checksum);
            OTA_SetFlag(checksum);
            /* 重启*/
            printf("\rSystemReset\r\n");
            __NVIC_SystemReset();
        }
        else
        {
            printf("please restart !\r\n");
        }
    }
    else
    {
        //固件数据处理
        if (position == 0)
        {
            checksum = 0;
            printf("CheckSum init \r\n", checksum);
        }
        Download_app(position, value);
        CheckSum_calculate(&checksum, value);
    }

    return SUCCESS;
}
#endif

#ifdef SUPPORT_GREEN_TIME
/**
 * @brief  获取到的格林时间
 * @param[in] {time} 获取到的格林时间数据
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_greentime(u8 time[])
{
    // #error "请自行完成相关代码,并删除该行"
    /*
    time[0] 为是否获取时间成功标志，为 0 表示失败，为 1表示成功
    time[1] 为年份，0x00 表示 2000 年
    time[2] 为月份，从 1 开始到12 结束
    time[3] 为日期，从 1 开始到31 结束
    time[4] 为时钟，从 0 开始到23 结束
    time[5] 为分钟，从 0 开始到59 结束
    time[6] 为秒钟，从 0 开始到59 结束
    */
    if(time[0] == 1) {
        //正确接收到wifi模块返回的格林数据
        // printf("get greentime\r\n");

    }else {
        //获取格林时间出错,有可能是当前wifi模块未联网

    }
}
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/**
 * @brief  MCU校对本地RTC时钟
 * @param[in] {time} 获取到的格林时间数据
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_write_rtctime(u8 time[])
{
    // // // #error "请自行完成RTC时钟写入代码,并删除该行"
    /*
    Time[0] 为是否获取时间成功标志，为 0 表示失败，为 1表示成功
    Time[1] 为年份，0x00 表示 2000 年
    Time[2] 为月份，从 1 开始到12 结束
    Time[3] 为日期，从 1 开始到31 结束
    Time[4] 为时钟，从 0 开始到23 结束
    Time[5] 为分钟，从 0 开始到59 结束
    Time[6] 为秒钟，从 0 开始到59 结束
    Time[7] 为星期，从 1 开始到 7 结束，1代表星期一
   */
    if(time[0] == 1) {
        RTC_Check(&time[0]);
        //正确接收到wifi模块返回的本地时钟数据
        // printf("20%d/%d/%d   %d:%d:%d\n",time[1],time[2],time[3],time[4],time[5],time[6]);
    }else {
        //获取本地时钟数据出错,有可能是当前wifi模块未联网
        // printf("get time ERROR!\r\n");
    }
}
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
void wifi_test_result(u8 result,u8 rssi)
{
    // // #error "请自行实现wifi功能测试成功/失败代码,完成后请删除该行"
    if(result == 0) {
        //测试失败
        if(rssi == 0x00) {
            //未扫描到名称为tuya_mdev_test路由器,请检查
        }else if(rssi == 0x01) {
            //模块未授权
        }
    }else {
        //测试成功
        //rssi为信号强度(0-100, 0信号最差，100信号最强)
    }
}
#endif

#ifdef GET_MODULE_REMAIN_MEMORY_ENABLE
/**
 * @brief  获取模块内存
 * @param[in] {module_memory} 获取模块内存的大小
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void remain_memory_result(u32 module_memory)
{
    //#error "请自行实现获取模块内存处理代码,完成后请删除该行"

}
#endif

#ifdef GET_ROUTE_RSSI_ENABLE
/**
 * @brief  获取当前WIFI信号强度
 * @param[in] {rssi} 获取信号强度结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_router_rssi_result(u8 rssi)
{
	//#error "请自行实现获取当前WIFI信号强度处理代码,完成后请删除该行"
    if(0 == rssi) {
        //获取失败
    }else {
        //rssi为负值，表示信号强度，单位为db
    }
}
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
void update_wifi_status(u8 wifi_state_flag, u8 wifi_state)
{
    // // // #error "请自行完成获取 WIFI 状态结果代码,并删除该行"
    if(0x00 == wifi_state_flag) { //tuya网络状态
        ty_wifi_work_state = wifi_state;
        switch(wifi_state) {
            case 0:
                //配置状态
            break;

            case 1:
                //WIFI 已配置但未连上路由器
            break;

            case 2:
                //WIFI 已配置且连上路由器
            break;

            case 3:
                //已连上路由器且连接到云端
            break;

            default:break;
        }
    }else {
        switch(wifi_state) { //homekit网络状态
            case 0:
                hk_wifi_work_state = wifi_state;
                //待绑定或绑定中
            break;

            case 1:
                hk_wifi_work_state = wifi_state;
                //WIFI 已配置但未连接APP
            break;

            case 2:
                hk_wifi_work_state = wifi_state;
                //WIFI 已配置且已连接APP
            break;

            case 3:
                //配件连接提示
                //收到此状态，表示用户发送了配件识别，需要设备5s内有所反馈，例如网络指示灯闪烁3次，或蜂鸣器响3声
            break;

            default:break;
        }
    }
}
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
void mcu_get_mac(u8 mac[])
{
    #error "请自行完成mac获取代码,并删除该行"
    /*
    mac[0]为是否获取mac成功标志，0x00 表示成功，为0x01表示失败
    mac[1]~mac[6]:当获取 MAC地址标志位如果mac[0]为成功，则表示模块有效的MAC地址
   */

    if(mac[0] == 1) {
        //获取mac出错
    }else {
        //正确接收到wifi模块返回的mac地址
    }
}
#endif

#ifdef MODULE_EXTEND_FUN_ENABLE
/**
 * @brief  获取WIFI模块相关数据信息结果
 * @param[in] {p_data} 串口数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note
 */
static void get_module_infor_result(u8 p_data[], u16 data_len)
{
    #error "请自行完成获取WIFI模块相关数据信息结果处理代码,并删除该行"

    char *p_str = NULL;

    if(0 != p_data[0]) {
        //失败
    }else {
        //成功
        u8 country_code = 0;
        p_data[data_len] = '\0';
        p_str = strstr((char *)&p_data[1], "cc\":");
        if(NULL != p_str) {
            p_str += my_strlen("cc\":");
            country_code = *p_str - '0';
            //country_code:国家码：
            //0：表示CN，包含区域：中国，韩国，新加坡，澳大利亚，日本（1-13），其他。
            //1：表示US，包含区域为：美国，台湾，加拿大。
            //2：表示JP，包含区域为：日本（1-14）。
            //3：表示EU，包含区域为：欧洲。
            //请在此添加国家码处理代码

        }
    }
}

/**
 * @brief  模块拓展服务相关功能处理
 * @param[in] {p_data} 串口数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note
 */
void module_extend_function(u8 p_data[], u16 data_len)
{
    switch(p_data[0]) { //子命令
        case SUB_CMD_GET_MODULE_INFOR:
            get_module_infor_result(&p_data[1], data_len - 1);
        break;

        default:break;
    }
}
#endif

#ifdef SUPPORT_MCU_FIRM_UPDATE
#if MCU_FIRMWARE_BACKUP_AREA_TYPE == 1
/**
 * @brief  设备新功能设置通知结果
 * @param[in] {result} 结果
 * @return Null
 * @note
 */
static void mcu_set_module_new_func_info_result(u8 result)
{
    switch(result) {
        case 0:
            //成功
        break;

        case 1:
            //数据字段内容不合法
        break;

        case 2:
            //设置执行失败
        break;

        default:break;
    }
}

/**
 * @brief  MCU设置新功能结果处理
 * @param[in] {p_data} 串口数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note
 */
void mcu_set_new_func_result(u8 p_data[], u16 data_len)
{
    switch(p_data[0]) { //子命令
        case NEW_FUNC_SET_INFO_SUBCMD:
            mcu_set_module_new_func_info_result(p_data[1]);
        break;

        default:break;
    }
}
#endif
#endif
