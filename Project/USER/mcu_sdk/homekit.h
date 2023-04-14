/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2030, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    homekit.h
 * @author  涂鸦综合协议开发组
 * @version v1.0.4
 * @date    2021.6.1
 * @brief   
 *          此文件包含HomeKit功能实现
 */

/****************************** 免责声明 ！！！ *******************************
由于MCU类型和编译环境多种多样，所以此代码仅供参考，用户请自行把控最终代码质量，
涂鸦不对MCU功能结果负责。
******************************************************************************/

#ifndef __HOMEKIT_H_
#define __HOMEKIT_H_

#include "tuya_type.h"


#define CNTSOF(a)   (sizeof(a)/sizeof(a[0]))

//=============================================================================
//HomeKit数据结构
//=============================================================================
typedef struct {
    u8 *buf;
    u16 buflen;
}HAP_DATA_RAW_T;

/** HAP Value */
typedef union {
    bool_t b;
    u32 u;
    i32 i;
    u64 i64;
    float f;
    i8 *s;
    HAP_DATA_RAW_T d;

}HAP_VALUE_T;

typedef struct {
    i8 *p_character_str;                            //特性字符串标识
    bool_t character_sort_flag;                     //特性分类  TRUE:必选特性/FALSE:可选特性
    bool_t character_config_flag;                   //服务配置标志  FALSE:未配置成功/TRUE:已配置成功
    u8 hap_val_type;                                //特性数据类型
    HAP_VALUE_T hap_val;                            //特性数据
}HOMEKIT_CHARACTER_S;

typedef struct {
    u8 serial;                                      //服务序号
    i8 *p_service_str;                              //服务字符串标识
    bool_t config_flag;                             //服务配置标志  FALSE:未配置成功/TRUE:已配置成功
    u8 character_amount;                            //特性数量
    HOMEKIT_CHARACTER_S *p_character_arr;           //特性
}HOMEKIT_SERVICE_S;


//=============================================================================
//HomeKit相关字符串标识
//=============================================================================

//HomeKit服务字符串标识
#define HAP_SERV_UUID_ACCESSORY_INFORMATION         "3E"
#define HAP_SERV_UUID_PROTOCOL_INFORMATION          "A2"
#define HAP_SERV_UUID_FAN                           "40"
#define HAP_SERV_UUID_GARAGE_DOOR_OPENER            "41"
#define HAP_SERV_UUID_LIGHTBULB                     "43"
#define HAP_SERV_UUID_LOCK_MANAGEMENT               "44"
#define HAP_SERV_UUID_LOCK_MECHANISM                "45"
#define HAP_SERV_UUID_SWITCH                        "49"
#define HAP_SERV_UUID_OUTLET                        "47"
#define HAP_SERV_UUID_THERMOSTAT                    "4A"
#define HAP_SERV_UUID_AIR_QUALITY_SENSOR            "8D"
#define HAP_SERV_UUID_SECURITY_SYSTEM               "7E"
#define HAP_SERV_UUID_CARBON_MONOXIDE_SENSOR        "7F"
#define HAP_SERV_UUID_CONTACT_SENSOR                "80"
#define HAP_SERV_UUID_DOOR                          "81"
#define HAP_SERV_UUID_HUMIDITY_SENSOR               "82"
#define HAP_SERV_UUID_LEAK_SENSOR                   "83"
#define HAP_SERV_UUID_LIGHT_SENSOR                  "84"
#define HAP_SERV_UUID_MOTION_SENSOR                 "85"
#define HAP_SERV_UUID_OCCUPANCY_SENSOR              "86"
#define HAP_SERV_UUID_SMOKE_SENSOR                  "87"
#define HAP_SERV_UUID_STATLESS_PROGRAMMABLE_SWITCH  "89"
#define HAP_SERV_UUID_TEMPERATURE_SENSOR            "8A"
#define HAP_SERV_UUID_WINDOW                        "8B"
#define HAP_SERV_UUID_WINDOW_COVERING               "8C"
#define HAP_SERV_UUID_BATTERY_SERVICE               "96"
#define HAP_SERV_UUID_CARBON_DIOXIDE_SENSOR         "97"
#define HAP_SERV_UUID_FAN_V2                        "B7"
#define HAP_SERV_UUID_SLAT                          "B9"
#define HAP_SERV_UUID_FILTER_MAINTENANCE            "BA"
#define HAP_SERV_UUID_AIR_PURIFIER                  "BB"
#define HAP_SERV_UUID_HEATER_COOLER                 "BC"
#define HAP_SERV_UUID_HUMIDIFIER_DEHUMIDIFIER       "BD"
#define HAP_SERV_UUID_SERVICE_LABEL                 "CC"
#define HAP_SERV_UUID_IRRIGATION_SYSTEM             "CF"
#define HAP_SERV_UUID_VALVE                         "D0"
#define HAP_SERV_UUID_FAUCET                        "D7"

//HomeKit特性字符串标识
#define HAP_CHAR_UUID_ADMINISTRATOR_ONLY_ACCESS                 "1"
#define HAP_CHAR_UUID_BRIGHTNESS                                "8"
#define HAP_CHAR_UUID_COOLING_THRESHOLD_TEMPERATURE             "D"
#define HAP_CHAR_UUID_CURRENT_DOOR_STATE                        "E"
#define HAP_CHAR_UUID_CURRENT_HEATING_COOLING_STATE             "F"
#define HAP_CHAR_UUID_CURRENT_RELATIVE_HUMIDITY                 "10"
#define HAP_CHAR_UUID_CURRENT_TEMPERATURE                       "11"
#define HAP_CHAR_UUID_FIRMWARE_REVISION                         "52"
#define HAP_CHAR_UUID_HARDWARE_REVISION                         "53"
#define HAP_CHAR_UUID_HEATING_THRESHOLD_TEMPERATURE             "12"
#define HAP_CHAR_UUID_HUE                                       "13"
#define HAP_CHAR_UUID_IDENTIFY                                  "14"
#define HAP_CHAR_UUID_LOCK_CONTROL_POINT                        "19"
#define HAP_CHAR_UUID_LOCK_CURRENT_STATE                        "1D"
#define HAP_CHAR_UUID_LOCK_LAST_KNOWN_ACTION                    "1C"
#define HAP_CHAR_UUID_LOCK_MANAGEMENT_AUTO_SECURITY_TIMEOUT     "1A"
#define HAP_CHAR_UUID_LOCK_TARGET_STATE                         "1E"
#define HAP_CHAR_UUID_LOGS                                      "1F"
#define HAP_CHAR_UUID_MANUFACTURER                              "20"
#define HAP_CHAR_UUID_MODEL                                     "21"
#define HAP_CHAR_UUID_MOTION_DETECTED                           "22"
#define HAP_CHAR_UUID_NAME                                      "23"
#define HAP_CHAR_UUID_OBSTRUCTION_DETECTED                      "24"
#define HAP_CHAR_UUID_ON                                        "25"
#define HAP_CHAR_UUID_OUTLET_IN_USE                             "26"
#define HAP_CHAR_UUID_ROTATION_DIRECTION                        "28"
#define HAP_CHAR_UUID_ROTATION_SPEED                            "29"
#define HAP_CHAR_UUID_SATURATION                                "2F"
#define HAP_CHAR_UUID_SERIAL_NUMBER                             "30"
#define HAP_CHAR_UUID_TARGET_DOOR_STATE                         "32"
#define HAP_CHAR_UUID_TARGET_HEATING_COOLING_STATE              "33"
#define HAP_CHAR_UUID_TARGET_RELATIVE_HUMIDITY                  "34"
#define HAP_CHAR_UUID_TARGET_TEMPERATURE                        "35"
#define HAP_CHAR_UUID_TEMPERATURE_DISPLAY_UNITS                 "36"
#define HAP_CHAR_UUID_VERSION                                   "37"
#define HAP_CHAR_UUID_AIR_PARTICULATE_DENSITY                   "64"
#define HAP_CHAR_UUID_AIR_PARTICULATE_SIZE                      "65"
#define HAP_CHAR_UUID_SECURITY_SYSTEM_CURRENT_STATE             "66"
#define HAP_CHAR_UUID_SECURITY_SYSTEM_TARGET_STATE              "67"
#define HAP_CHAR_UUID_BATTERY_LEVEL                             "68"
#define HAP_CHAR_UUID_CARBON_MONOXIDE_DETECTED                  "69"
#define HAP_CHAR_UUID_CONTACT_SENSOR_STATE                      "6A"
#define HAP_CHAR_UUID_CURRENT_AMBIENT_LIGHT_LEVEL               "6B"
#define HAP_CHAR_UUID_CURRENT_HORIZONTAL_TILT_ANGLE             "6C"
#define HAP_CHAR_UUID_CURRENT_POSITION                          "6D"
#define HAP_CHAR_UUID_CURRENT_VERTICAL_TILT_ANGLE               "6E"
#define HAP_CHAR_UUID_HOLD_POSITION                             "6F"
#define HAP_CHAR_UUID_LEAK_DETECTED                             "70"
#define HAP_CHAR_UUID_OCCUPANCY_DETECTED                        "71"
#define HAP_CHAR_UUID_POSITION_STATE                            "72"
#define HAP_CHAR_UUID_PROGRAMMABLE_SWITCH_EVENT                 "73"
#define HAP_CHAR_UUID_STATUS_ACTIVE                             "75"
#define HAP_CHAR_UUID_SMOKE_DETECTED                            "76"
#define HAP_CHAR_UUID_STATUS_FAULT                              "77"
#define HAP_CHAR_UUID_STATUS_JAMMED                             "78"
#define HAP_CHAR_UUID_STATUS_LOW_BATTERY                        "79"
#define HAP_CHAR_UUID_STATUS_TAMPERED                           "7A"
#define HAP_CHAR_UUID_TARGET_HORIZONTAL_TILT_ANGLE              "7B"
#define HAP_CHAR_UUID_TARGET_POSITION                           "7C"
#define HAP_CHAR_UUID_TARGET_VERTICAL_TILT_ANGLE                "7D"
#define HAP_CHAR_UUID_STATUS_SECURITY_SYSTEM_ALARM_TYPE         "8E"
#define HAP_CHAR_UUID_CHARGING_STATE                            "8F"
#define HAP_CHAR_UUID_CARBON_MONOXIDE_LEVEL                     "90"
#define HAP_CHAR_UUID_CARBON_MONOXIDE_PEAK_LEVEL                "91"
#define HAP_CHAR_UUID_CARBON_DIOXIDE_DETECTED                   "92"
#define HAP_CHAR_UUID_CARBON_DIOXIDE_LEVEL                      "93"
#define HAP_CHAR_UUID_CARBON_DIOXIDE_PEAK_LEVEL                 "94"
#define HAP_CHAR_UUID_AIR_QUALITY                               "95"
#define HAP_CHAR_UUID_ACCESSORY_FLAGS                           "A6"
#define HAP_CHAR_UUID_LOCK_PHYSICAL_CONTROLS                    "A7"
#define HAP_CHAR_UUID_CURRENT_AIR_PURIFIER_STATE                "A9"
#define HAP_CHAR_UUID_CURRENT_SLAT_STATE                        "AA"
#define HAP_CHAR_UUID_SLAT_TYPE                                 "C0"
#define HAP_CHAR_UUID_FILTER_LIFE_LEVEL                         "AB"
#define HAP_CHAR_UUID_FILTER_CHANGE_INDICATION                  "AC"
#define HAP_CHAR_UUID_RESET_FILTER_INDICATION                   "AD"
#define HAP_CHAR_UUID_TARGET_AIR_PURIFIER_STATE                 "A8"
#define HAP_CHAR_UUID_TARGET_FAN_STATE                          "BF"
#define HAP_CHAR_UUID_CURRENT_FAN_STATE                         "AF"
#define HAP_CHAR_UUID_ACTIVE                                    "B0"
#define HAP_CHAR_UUID_SWING_MODE                                "B6"
#define HAP_CHAR_UUID_CURRENT_TILT_ANGLE                        "C1"
#define HAP_CHAR_UUID_TARGET_TILT_ANGLE                         "C2"
#define HAP_CHAR_UUID_OZONE_DENSITY                             "C3"
#define HAP_CHAR_UUID_NITROGEN_DIOXIDE_DENSITY                  "C4"
#define HAP_CHAR_UUID_SULPHUR_DIOXIDE_DENSITY                   "C5"
#define HAP_CHAR_UUID_PM_2_5_DENSITY                            "C6"
#define HAP_CHAR_UUID_PM_10_DENSITY                             "C7"
#define HAP_CHAR_UUID_VOC_DENSITY                               "C8"
#define HAP_CHAR_UUID_SERVICE_LABEL_INDEX                       "CB"
#define HAP_CHAR_UUID_SERVICE_LABEL_NAMESPACE                   "CD"
#define HAP_CHAR_UUID_COLOR_TEMPERATURE                         "CE"
#define HAP_CHAR_UUID_CURRENT_HEATER_COOLER_STATE               "B1"
#define HAP_CHAR_UUID_TARGET_HEATER_COOLER_STATE                "B2"
#define HAP_CHAR_UUID_CURRENT_HUMIDIFIER_DEHUMIDIFIER_STATE     "B3"
#define HAP_CHAR_UUID_TARGET_HUMIDIFIER_DEHUMIDIFIER_STATE      "B4"
#define HAP_CHAR_UUID_WATER_LEVEL                               "B5"
#define HAP_CHAR_UUID_RELATIVE_HUMIDITY_DEHUMIDIFIER_THRESHOLD  "C9"
#define HAP_CHAR_UUID_RELATIVE_HUMIDITY_HUMIDIFIER_THRESHOLD    "CA"
#define HAP_CHAR_UUID_PROGRAM_MODE                              "D1"
#define HAP_CHAR_UUID_IN_USE                                    "D2"
#define HAP_CHAR_UUID_SET_DURATION                              "D3"
#define HAP_CHAR_UUID_REMAINING_DURATION                        "D4"
#define HAP_CHAR_UUID_VALVE_TYPE                                "D5"
#define HAP_CHAR_UUID_IS_CONFIGURED                             "D6"
#define HAP_CHAR_UUID_PRODUCT_DATA                              "220"





#ifdef HOMEKIT_PRODUCT_TYPE
/**
 * @brief  HomeKit相关功能处理
 * @param[in] {p_data} 串口数据
 * @return Null
 * @note   
 */
void homekit_function(u8 p_data[], u16 data_len);

/**
 * @brief  HomeKit特性命令下发
 * @param[in] {serv_serial} 服务序号
 * @param[in] {p_char_str} 特性字符串标识
 * @param[in] {char_data_type} 特性数据类型
 * @param[in] {char_val_len} 特性数据长度
 * @param[in] {p_char_val} 特性数据
 * @return SUCCESS/ERROR
 * @note   
 */
u8 homekit_character_ctrl(u8 serv_serial, i8 p_char_str[], u8 char_data_type, u16 char_val_len, HAP_VALUE_T *p_char_val);

/**
 * @brief  HomeKit特性状态上报
 * @param[in] {serv_serial} 服务序号
 * @param[in] {p_char_str} 特性字符串标识
 * @param[in] {char_data_type} 特性数据类型
 * @param[in] {char_val_len} 特性数据长度
 * @param[in] {p_char_val} 特性数据
 * @return SUCCESS/ERROR
 * @note   
 */
u8 homekit_character_upload(u8 serv_serial, i8 p_char_str[], u8 char_data_type, u16 char_val_len, HAP_VALUE_T *p_char_val);

/**
 * @brief  HomeKit特性上报所有状态
 * @param[in] Null
 * @return Null
 * @note   
 */
void homekit_character_upload_all(void);
#endif

#endif
