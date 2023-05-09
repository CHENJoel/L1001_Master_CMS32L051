/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2030, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    homekit.c
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

/******************************************************************************
                                移植须知:
1:请在protocol.h中选择HomeKit品类，然后在此文件中进行HomeKit服务和特性配置选择
2:请勿在中断/定时器中断内调用上报函数
******************************************************************************/

#include "wifi.h"


/******************************************************************************
                    1.HomeKit服务配置选择
               用户可根据产品功能需求打开对应宏
******************************************************************************/
#ifdef HOMEKIT_PRODUCT_TYPE
//#define HOMEKIT_SERV_FAN_V2                                         //风扇
//#define HOMEKIT_SERV_GARAGE_DOOR_OPENER                             //车库门开启器
//#define HOMEKIT_SERV_LIGHTBULB                                      //灯泡
//#define HOMEKIT_SERV_THERMOSTAT                                     //恒温器
//#define HOMEKIT_SERV_DOOR                                           //门
//#define HOMEKIT_SERV_WINDOW                                         //窗户
//#define HOMEKIT_SERV_WINDOW_COVERING                                //窗帘
//#define HOMEKIT_SERV_AIR_PURIFIER                                   //空气净化器
//#define HOMEKIT_SERV_FILTER_MAINTENANCE                             //过滤器维护
//#define HOMEKIT_SERV_AIR_QUALITY_SENSOR                             //空气质量传感器
//#define HOMEKIT_SERV_SLAT                                           //板条
//#define HOMEKIT_SERV_HEATER_COOLER                                  //加热器冷却器
//#define HOMEKIT_SERV_HUMIDIFIER_DEHUMIDIFIER                        //加湿器除湿机
//#define HOMEKIT_SERV_IRRIGATION_SYSTEM                              //灌溉系统
//#define HOMEKIT_SERV_VALVE                                          //阀门
//#define HOMEKIT_SERV_FAUCET                                         //水龙头
#endif


/******************************************************************************
                    2.HomeKit可选特性配置选择
                 用户可根据产品功能需求打开对应宏
******************************************************************************/
/* FAN_V2 风扇服务的可选特性选择 */
#ifdef HOMEKIT_SERV_FAN_V2
//#define FAN_V2_CHAR_NAME                                    //名称
#define FAN_V2_CHAR_CURRENT_FAN_STATE                       //当前风扇状态
#define FAN_V2_CHAR_TARGET_FAN_STATE                        //目标风扇状态
#define FAN_V2_CHAR_ROTATION_DIRECTION                      //转动方向
#define FAN_V2_CHAR_ROTATION_SPEED                          //转速
#define FAN_V2_CHAR_SWING_MODE                              //摇摆模式
#define FAN_V2_CHAR_LOCK_PHYSICAL_CONTROLS                  //锁定物理控制(童锁)
#endif

/* GARAGE_DOOR_OPENER 车库门开启器的可选特性选择 */
#ifdef HOMEKIT_SERV_GARAGE_DOOR_OPENER
//#define GARAGE_DOOR_OPENER_CHAR_NAME                        //名称
#define GARAGE_DOOR_OPENER_CHAR_LOCK_CURRENT_STATE          //锁定当前状态
#define GARAGE_DOOR_OPENER_CHAR_LOCK_TARGET_STATE           //锁定目标状态
#endif

/* LIGHTBULB 灯泡服务的可选特性选择 */
#ifdef HOMEKIT_SERV_LIGHTBULB
//#define LIGHTBULB_CHAR_NAME                                 //名称
#define LIGHTBULB_CHAR_BRIGHTNESS                           //亮度
#define LIGHTBULB_CHAR_HUE                                  //色相
#define LIGHTBULB_CHAR_SATURATION                           //饱和度
#define LIGHTBULB_CHAR_COLOR_TEMPERATURE                    //色温
#endif

/* THERMOSTAT 恒温器服务的可选特性选择 */
#ifdef HOMEKIT_SERV_THERMOSTAT
//#define THERMOSTAT_CHAR_NAME                                //名称
#define THERMOSTAT_CHAR_COOLING_THRESHOLD_TEMPERATURE       //冷却阈值温度
#define THERMOSTAT_CHAR_CURRENT_RELATIVE_HUMIDITY           //当前相对湿度
#define THERMOSTAT_CHAR_HEATING_THRESHOLD_TEMPERATURE       //加热阈值温度
#define THERMOSTAT_CHAR_TARGET_RELATIVE_HUMIDITY            //目标相对湿度
#endif

/* DOOR 门服务的可选特性选择 */
#ifdef HOMEKIT_SERV_DOOR
//#define DOOR_CHAR_NAME                                      //名称
#define DOOR_CHAR_HOLD_POSITION                             //保持位置
#define DOOR_CHAR_OBSTRUCTION_DETECTED                      //检测到障碍物
#endif

/* WINDOW 窗户服务的可选特性选择 */
#ifdef HOMEKIT_SERV_WINDOW
//#define WINDOW_CHAR_NAME                                    //名称
#define WINDOW_CHAR_HOLD_POSITION                           //保持位置
#define WINDOW_CHAR_OBSTRUCTION_DETECTED                    //检测到障碍物
#endif

/* WINDOW_COVERING 窗帘服务的可选特性选择 */
#ifdef HOMEKIT_SERV_WINDOW_COVERING
//#define WINDOW_COVERING_CHAR_NAME                           //名称
#define WINDOW_COVERING_CHAR_HOLD_POSITION                  //保持位置
#define WINDOW_COVERING_CHAR_CURRENT_HORIZONTAL_TILT_ANGLE  //当前水平倾斜角度
#define WINDOW_COVERING_CHAR_TARGET_HORIZONTAL_TILT_ANGLE   //目标水平倾斜角度
#define WINDOW_COVERING_CHAR_CURRENT_VERTICAL_TILT_ANGLE    //当前垂直倾斜角度
#define WINDOW_COVERING_CHAR_TARGET_VERTICAL_TILT_ANGLE     //目标垂直倾斜角度
#define WINDOW_COVERING_CHAR_OBSTRUCTION_DETECTED           //检测到障碍物
#endif

/* AIR_PURIFIER 空气净化器服务的可选特性选择 */
#ifdef HOMEKIT_SERV_AIR_PURIFIER
//#define AIR_PURIFIER_CHAR_NAME                              //名称
#define AIR_PURIFIER_CHAR_ROTATION_SPEED                    //转速
#define AIR_PURIFIER_CHAR_SWING_MODE                        //摇摆模式
#define AIR_PURIFIER_CHAR_LOCK_PHYSICAL_CONTROLS            //锁定物理控制(童锁)
#endif

/* FILTER_MAINTENANCE 过滤器维护服务的可选特性选择 */
#ifdef HOMEKIT_SERV_FILTER_MAINTENANCE
//#define FILTER_MAINTENANCE_CHAR_NAME                        //名称
#define FILTER_MAINTENANCE_CHAR_FILTER_LIFE_LEVEL           //过滤器使用寿命
#define FILTER_MAINTENANCE_CHAR_RESET_FILTER_INDICATION     //重置过滤器指示
#endif

/* AIR_QUALITY_SENSOR 空气质量传感器服务的可选特性选择 */
#ifdef HOMEKIT_SERV_AIR_QUALITY_SENSOR
//#define AIR_QUALITY_SENSOR_CHAR_NAME                        //名称
#define AIR_QUALITY_SENSOR_CHAR_OZONE_DENSITY               //臭氧浓度
#define AIR_QUALITY_SENSOR_CHAR_NITROGEN_DIOXIDE_DENSITY    //二氧化氮密度
#define AIR_QUALITY_SENSOR_CHAR_SULPHUR_DIOXIDE_DENSITY     //二氧化硫浓度
#define AIR_QUALITY_SENSOR_CHAR_PM_2_5_DENSITY              //PM2.5浓度
#define AIR_QUALITY_SENSOR_CHAR_PM_10_DENSITY               //PM10浓度
#define AIR_QUALITY_SENSOR_CHAR_VOC_DENSITY                 //VOC密度
#define AIR_QUALITY_SENSOR_CHAR_STATUS_ACTIVE               //工作状态活跃
#define AIR_QUALITY_SENSOR_CHAR_STATUS_FAULT                //状态故障
#define AIR_QUALITY_SENSOR_CHAR_STATUS_TAMPERED             //状态被篡改
#define AIR_QUALITY_SENSOR_CHAR_STATUS_LOW_BATTERY          //低电量状态
#endif

/* SLAT 板条服务的可选特性选择 */
#ifdef HOMEKIT_SERV_SLAT
//#define SLAT_CHAR_NAME                                      //名称
#define SLAT_CHAR_SWING_MODE                                //摇摆模式
#define SLAT_CHAR_CURRENT_TILT_ANGLE                        //当前倾斜角度
#define SLAT_CHAR_TARGET_TILT_ANGLE                         //目标倾斜角度
#endif

/* HEATER_COOLER 加热器冷却器服务的可选特性选择 */
#ifdef HOMEKIT_SERV_HEATER_COOLER
//#define HEATER_COOLER_CHAR_NAME                             //名称
#define HEATER_COOLER_CHAR_ROTATION_SPEED                   //转速
#define HEATER_COOLER_CHAR_TEMPERATURE_DISPLAY_UNITS        //温度显示单元
#define HEATER_COOLER_CHAR_SWING_MODE                       //摇摆模式
#define HEATER_COOLER_CHAR_COOLING_THRESHOLD_TEMPERATURE    //冷却阈值温度
#define HEATER_COOLER_CHAR_HEATING_THRESHOLD_TEMPERATURE    //加热阈值温度
#define HEATER_COOLER_CHAR_LOCK_PHYSICAL_CONTROLS           //锁定物理控制(童锁)
#endif

/* HUMIDIFIER_DEHUMIDIFIER 加湿器除湿机服务的可选特性选择 */
#ifdef HOMEKIT_SERV_HUMIDIFIER_DEHUMIDIFIER
//#define HUMIDIFIER_DEHUMIDIFIER_CHAR_NAME                                       //名称
#define HUMIDIFIER_DEHUMIDIFIER_CHAR_RELATIVE_HUMIDITY_DEHUMIDIFIER_THRESHOLD   //相对湿度除湿器阈值
#define HUMIDIFIER_DEHUMIDIFIER_CHAR_RELATIVE_HUMIDITY_HUMIDIFIER_THRESHOLD     //相对湿度加湿器阈值
#define HUMIDIFIER_DEHUMIDIFIER_CHAR_ROTATION_SPEED                             //转速
#define HUMIDIFIER_DEHUMIDIFIER_CHAR_SWING_MODE                                 //摇摆模式
#define HUMIDIFIER_DEHUMIDIFIER_CHAR_WATER_LEVEL                                //水位
#define HUMIDIFIER_DEHUMIDIFIER_CHAR_LOCK_PHYSICAL_CONTROLS                     //锁定物理控制(童锁)
#endif

/****** IRRIGATION_SYSTEM 灌溉系统服务的可选特性选择 ******/
#ifdef HOMEKIT_SERV_IRRIGATION_SYSTEM
//#define IRRIGATION_SYSTEM_CHAR_NAME                         //名称
#define IRRIGATION_SYSTEM_CHAR_REMAINING_DURATION           //剩余时间
#define IRRIGATION_SYSTEM_CHAR_STATUS_FAULT                 //状态故障
#endif

/****** VALVE 阀门服务的可选特性选择 ******/
#ifdef HOMEKIT_SERV_VALVE
//#define VALVE_CHAR_NAME                                     //名称
#define VALVE_CHAR_SET_DURATION                             //设置时间
#define VALVE_CHAR_REMAINING_DURATION                       //剩余时间
#define VALVE_CHAR_IS_CONFIGURED                            //已配置
#define VALVE_CHAR_SERVICE_LABEL_INDEX                      //服务标签索引
#define VALVE_CHAR_STATUS_FAULT                             //状态故障
#endif

/****** FAUCET 水龙头服务的可选特性选择 ******/
#ifdef HOMEKIT_SERV_FAUCET
//#define VALVE_CHAR_NAME                                     //名称
#define FAUCET_CHAR_STATUS_FAULT                            //状态故障
#endif



/******************************************************************************
                    3.HomeKit特性配置
根据服务配置选择和特性配置选择配置，
其中有特性默认初始值配置，用户可以根据需要自行调整
******************************************************************************/
#ifdef HOMEKIT_SERV_FAN_V2
i8 hap_serv_uuid_fan_v2_str[] = HAP_SERV_UUID_FAN_V2;
/* FAN_V2 风扇服务的特性 */
i8 fan_v2_char_uuid_active_str[]                            = HAP_CHAR_UUID_ACTIVE; //活动状态
#ifdef FAN_V2_CHAR_NAME
i8 fan_v2_char_uuid_name_str[]                              = HAP_CHAR_UUID_NAME; //名称
#endif
#ifdef FAN_V2_CHAR_CURRENT_FAN_STATE
i8 fan_v2_char_uuid_current_fan_state_str[]                 = HAP_CHAR_UUID_CURRENT_FAN_STATE; //当前风扇状态
#endif
#ifdef FAN_V2_CHAR_TARGET_FAN_STATE
i8 fan_v2_char_uuid_target_fan_state_str[]                  = HAP_CHAR_UUID_TARGET_FAN_STATE; //目标风扇状态
#endif
#ifdef FAN_V2_CHAR_ROTATION_DIRECTION
i8 fan_v2_char_uuid_rotation_direction_str[]                = HAP_CHAR_UUID_ROTATION_DIRECTION; //转动方向
#endif
#ifdef FAN_V2_CHAR_ROTATION_SPEED
i8 fan_v2_char_uuid_rotation_speed_str[]                    = HAP_CHAR_UUID_ROTATION_SPEED; //转速
#endif
#ifdef FAN_V2_CHAR_SWING_MODE
i8 fan_v2_char_uuid_swing_mode_str[]                        = HAP_CHAR_UUID_SWING_MODE; //摇摆模式
#endif
#ifdef FAN_V2_CHAR_LOCK_PHYSICAL_CONTROLS
i8 fan_v2_char_uuid_lock_physical_controls_str[]            = HAP_CHAR_UUID_LOCK_PHYSICAL_CONTROLS; //锁定物理控制(童锁)
#endif

HOMEKIT_CHARACTER_S fan_v2_character[] = {
    {fan_v2_char_uuid_active_str,                           TRUE,   TRUE,   HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
#ifdef FAN_V2_CHAR_NAME
    {fan_v2_char_uuid_name_str,                             FALSE,  FALSE,  HAP_DATA_TYPE_STRING,    .hap_val.s =  /* 在此处可以给特性赋初值 */ },
#endif
#ifdef FAN_V2_CHAR_CURRENT_FAN_STATE
    {fan_v2_char_uuid_current_fan_state_str,                FALSE,  FALSE,  HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef FAN_V2_CHAR_TARGET_FAN_STATE
    {fan_v2_char_uuid_target_fan_state_str,                 FALSE,  FALSE,  HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef FAN_V2_CHAR_ROTATION_DIRECTION
    {fan_v2_char_uuid_rotation_direction_str,               FALSE,  FALSE,  HAP_DATA_TYPE_INT,       .hap_val.i = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef FAN_V2_CHAR_ROTATION_SPEED
    {fan_v2_char_uuid_rotation_speed_str,                   FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,     .hap_val.f = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef FAN_V2_CHAR_SWING_MODE
    {fan_v2_char_uuid_swing_mode_str,                       FALSE,  FALSE,  HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef FAN_V2_CHAR_LOCK_PHYSICAL_CONTROLS
    {fan_v2_char_uuid_lock_physical_controls_str,           FALSE,  FALSE,  HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
#endif
};
#endif


#ifdef HOMEKIT_SERV_GARAGE_DOOR_OPENER
i8 hap_serv_uuid_garage_door_opener_str[] = HAP_SERV_UUID_GARAGE_DOOR_OPENER;
/* GARAGE_DOOR_OPENER 车库门开启器的特性 */
i8 garage_door_opener_char_uuid_current_door_state_str[]        = HAP_CHAR_UUID_CURRENT_DOOR_STATE; //当前门状态
i8 garage_door_opener_char_uuid_target_door_state_str[]         = HAP_CHAR_UUID_TARGET_DOOR_STATE; //目标门状态
i8 garage_door_opener_char_uuid_obstruction_detect_str[]        = HAP_CHAR_UUID_OBSTRUCTION_DETECTED; //检测到障碍物
#ifdef GARAGE_DOOR_OPENER_CHAR_NAME
i8 garage_door_opener_char_uuid_name_str[]                      = HAP_CHAR_UUID_NAME; //名称
#endif
#ifdef GARAGE_DOOR_OPENER_CHAR_LOCK_CURRENT_STATE
i8 garage_door_opener_char_uuid_lock_current_state_str[]        = HAP_CHAR_UUID_LOCK_CURRENT_STATE; //锁定当前状态
#endif
#ifdef GARAGE_DOOR_OPENER_CHAR_LOCK_TARGET_STATE
i8 garage_door_opener_char_uuid_lock_target_state_str[]         = HAP_CHAR_UUID_LOCK_TARGET_STATE; //锁定目标状态
#endif

HOMEKIT_CHARACTER_S garage_door_opener_character[] = {
    {garage_door_opener_char_uuid_current_door_state_str,       TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {garage_door_opener_char_uuid_target_door_state_str,        TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {garage_door_opener_char_uuid_obstruction_detect_str,       TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.b = 0      /* 在此处可以给特性赋初值 */ },
#ifdef GARAGE_DOOR_OPENER_CHAR_NAME
    {garage_door_opener_char_uuid_name_str,                     FALSE,  FALSE,  HAP_DATA_TYPE_STRING,   .hap_val.s =        /* 在此处可以给特性赋初值 */ },
#endif
#ifdef GARAGE_DOOR_OPENER_CHAR_LOCK_CURRENT_STATE
    {garage_door_opener_char_uuid_lock_current_state_str,       FALSE,  FALSE,  HAP_DATA_TYPE_BOOL,     .hap_val.u = 0     /* 在此处可以给特性赋初值 */ },
#endif
#ifdef GARAGE_DOOR_OPENER_CHAR_LOCK_TARGET_STATE
    {garage_door_opener_char_uuid_lock_target_state_str,        FALSE,  FALSE,  HAP_DATA_TYPE_BOOL,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#endif
};
#endif


#ifdef HOMEKIT_SERV_LIGHTBULB
i8 hap_serv_uuid_lightbulb_str[] = HAP_SERV_UUID_LIGHTBULB;
/* LIGHTBULB 灯泡服务的特性 */
i8 lightbulb_char_uuid_on_str[]                             = HAP_CHAR_UUID_ON; //开关
#ifdef LIGHTBULB_CHAR_NAME
i8 lightbulb_char_uuid_name_str[]                           = HAP_CHAR_UUID_NAME; //名称
#endif
#ifdef LIGHTBULB_CHAR_BRIGHTNESS
i8 lightbulb_char_uuid_brightness_str[]                     = HAP_CHAR_UUID_BRIGHTNESS; //亮度
#endif
#ifdef LIGHTBULB_CHAR_HUE
i8 lightbulb_char_uuid_hue_str[]                            = HAP_CHAR_UUID_HUE; //色相
#endif
#ifdef LIGHTBULB_CHAR_SATURATION
i8 lightbulb_char_uuid_saturation_str[]                     = HAP_CHAR_UUID_SATURATION; //饱和度
#endif
#ifdef LIGHTBULB_CHAR_COLOR_TEMPERATURE
i8 lightbulb_char_uuid_color_temperature_str[]              = HAP_CHAR_UUID_COLOR_TEMPERATURE; //色温
#endif

HOMEKIT_CHARACTER_S lightbulb_character[] = {
    {lightbulb_char_uuid_on_str,                            TRUE,   TRUE,   HAP_DATA_TYPE_BOOL,     .hap_val.b = 0      /* 在此处可以给特性赋初值 */ },
#ifdef LIGHTBULB_CHAR_NAME
    {lightbulb_char_uuid_name_str,                          FALSE,  FALSE,  HAP_DATA_TYPE_STRING,   .hap_val.s =        /* 在此处可以给特性赋初值 */ },
#endif
#ifdef LIGHTBULB_CHAR_BRIGHTNESS
    {lightbulb_char_uuid_brightness_str,                    FALSE,  FALSE,  HAP_DATA_TYPE_INT,      .hap_val.i = 0      /* 在此处可以给特性赋初值 */ },
#endif
#ifdef LIGHTBULB_CHAR_HUE
    {lightbulb_char_uuid_hue_str,                           FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,    .hap_val.f = 0      /* 在此处可以给特性赋初值 */ },
#endif
#ifdef LIGHTBULB_CHAR_SATURATION
    {lightbulb_char_uuid_saturation_str,                    FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,    .hap_val.f = 0      /* 在此处可以给特性赋初值 */ },
#endif
#ifdef LIGHTBULB_CHAR_COLOR_TEMPERATURE
    {lightbulb_char_uuid_color_temperature_str,             FALSE,  FALSE,  HAP_DATA_TYPE_UINT,     .hap_val.u = 50     /* 在此处可以给特性赋初值 */ },
#endif
};
#endif


#ifdef HOMEKIT_SERV_THERMOSTAT
i8 hap_serv_uuid_thermostat_str[] = HAP_SERV_UUID_THERMOSTAT;
/* THERMOSTAT 恒温器服务的特性 */
i8 thermostat_char_uuid_current_heating_cooling_state_str[]         = HAP_CHAR_UUID_CURRENT_HEATING_COOLING_STATE; //当前加热冷却状态
i8 thermostat_char_uuid_target_heating_cooling_state_str[]          = HAP_CHAR_UUID_TARGET_HEATING_COOLING_STATE; //目标加热冷却状态
i8 thermostat_char_uuid_current_temperature_str[]                   = HAP_CHAR_UUID_CURRENT_TEMPERATURE; //当前温度
i8 thermostat_char_uuid_target_temperature_str[]                    = HAP_CHAR_UUID_TARGET_TEMPERATURE; //目标温度
i8 thermostat_char_uuid_temperature_display_units_str[]             = HAP_CHAR_UUID_TEMPERATURE_DISPLAY_UNITS; //温度显示单元
#ifdef THERMOSTAT_CHAR_NAME
i8 thermostat_char_uuid_name_str[]                                  = HAP_CHAR_UUID_NAME; //名称
#endif
#ifdef THERMOSTAT_CHAR_COOLING_THRESHOLD_TEMPERATURE
i8 thermostat_char_uuid_cooling_threshold_temperature_str[]         = HAP_CHAR_UUID_COOLING_THRESHOLD_TEMPERATURE; //冷却阈值温度
#endif
#ifdef THERMOSTAT_CHAR_HEATING_THRESHOLD_TEMPERATURE
i8 thermostat_char_uuid_heating_threshold_temperature_str[]         = HAP_CHAR_UUID_HEATING_THRESHOLD_TEMPERATURE; //加热阈值温度
#endif
#ifdef THERMOSTAT_CHAR_CURRENT_RELATIVE_HUMIDITY
i8 thermostat_char_uuid_current_relative_humidity_str[]             = HAP_CHAR_UUID_CURRENT_RELATIVE_HUMIDITY; //当前相对湿度
#endif
#ifdef THERMOSTAT_CHAR_TARGET_RELATIVE_HUMIDITY
i8 thermostat_char_uuid_target_relative_humidity_str[]              = HAP_CHAR_UUID_TARGET_RELATIVE_HUMIDITY; //目标相对湿度
#endif

HOMEKIT_CHARACTER_S thermostat_character[] = {
    {thermostat_char_uuid_current_heating_cooling_state_str,        TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {thermostat_char_uuid_target_heating_cooling_state_str,         TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {thermostat_char_uuid_current_temperature_str,                  TRUE,   TRUE,   HAP_DATA_TYPE_FLOAT,    .hap_val.f = 0      /* 在此处可以给特性赋初值 */ },
    {thermostat_char_uuid_target_temperature_str,                   TRUE,   TRUE,   HAP_DATA_TYPE_FLOAT,    .hap_val.f = 10     /* 在此处可以给特性赋初值 */ },
    {thermostat_char_uuid_temperature_display_units_str,            TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#ifdef THERMOSTAT_CHAR_NAME
    {thermostat_char_uuid_name_str,                                 FALSE,  FALSE,  HAP_DATA_TYPE_STRING,   .hap_val.s =        /* 在此处可以给特性赋初值 */ },
#endif
#ifdef THERMOSTAT_CHAR_COOLING_THRESHOLD_TEMPERATURE
    {thermostat_char_uuid_cooling_threshold_temperature_str,        FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,    .hap_val.f = 10     /* 在此处可以给特性赋初值 */ },
#endif
#ifdef THERMOSTAT_CHAR_HEATING_THRESHOLD_TEMPERATURE
    {thermostat_char_uuid_heating_threshold_temperature_str,        FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,    .hap_val.f = 0      /* 在此处可以给特性赋初值 */ },
#endif
#ifdef THERMOSTAT_CHAR_CURRENT_RELATIVE_HUMIDITY
    {thermostat_char_uuid_current_relative_humidity_str,            FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,    .hap_val.f = 0      /* 在此处可以给特性赋初值 */ },
#endif
#ifdef THERMOSTAT_CHAR_TARGET_RELATIVE_HUMIDITY
    {thermostat_char_uuid_target_relative_humidity_str,             FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,    .hap_val.f = 0      /* 在此处可以给特性赋初值 */ },
#endif
};
#endif


#ifdef HOMEKIT_SERV_DOOR
i8 hap_serv_uuid_door_str[] = HAP_SERV_UUID_DOOR;
/* DOOR 门服务的特性 */
i8 door_char_uuid_current_position_str[]                    = HAP_CHAR_UUID_CURRENT_POSITION; //当前位置
i8 door_char_uuid_target_position_str[]                     = HAP_CHAR_UUID_TARGET_POSITION; //目标位置
i8 door_char_uuid_position_state_str[]                      = HAP_CHAR_UUID_POSITION_STATE; //位置状态
#ifdef DOOR_CHAR_NAME
i8 door_char_uuid_name_str[]                                = HAP_CHAR_UUID_NAME; //名称
#endif
#ifdef DOOR_CHAR_HOLD_POSITION
i8 door_char_uuid_hold_position_str[]                       = HAP_CHAR_UUID_HOLD_POSITION; //保持位置
#endif
#ifdef DOOR_CHAR_OBSTRUCTION_DETECTED
i8 door_char_uuid_obstruction_detect_str[]                  = HAP_CHAR_UUID_OBSTRUCTION_DETECTED; //检测到障碍物
#endif

HOMEKIT_CHARACTER_S door_character[] = {
    {door_char_uuid_current_position_str,                   TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {door_char_uuid_target_position_str,                    TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {door_char_uuid_position_state_str,                     TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#ifdef DOOR_CHAR_NAME
    {door_char_uuid_name_str,                               FALSE,  FALSE,  HAP_DATA_TYPE_STRING,   .hap_val.s =        /* 在此处可以给特性赋初值 */ },
#endif
#ifdef DOOR_CHAR_HOLD_POSITION
    {door_char_uuid_hold_position_str,                      FALSE,  FALSE,  HAP_DATA_TYPE_BOOL,     .hap_val.b = 0     /* 在此处可以给特性赋初值 */ },
#endif
#ifdef DOOR_CHAR_OBSTRUCTION_DETECTED
    {door_char_uuid_obstruction_detect_str,                 FALSE,  FALSE,  HAP_DATA_TYPE_BOOL,     .hap_val.b = 0      /* 在此处可以给特性赋初值 */ },
#endif
};
#endif


#ifdef HOMEKIT_SERV_WINDOW
i8 hap_serv_uuid_window_str[] = HAP_SERV_UUID_WINDOW;
/* WINDOW 窗户服务的特性 */
i8 window_char_uuid_current_position_str[]                  = HAP_CHAR_UUID_CURRENT_POSITION; //当前位置
i8 window_char_uuid_target_position_str[]                   = HAP_CHAR_UUID_TARGET_POSITION; //目标位置
i8 window_char_uuid_position_state_str[]                    = HAP_CHAR_UUID_POSITION_STATE; //位置状态
#ifdef WINDOW_CHAR_NAME
i8 window_char_uuid_name_str[]                              = HAP_CHAR_UUID_NAME; //名称
#endif
#ifdef WINDOW_CHAR_HOLD_POSITION
i8 window_char_uuid_hold_position_str[]                     = HAP_CHAR_UUID_HOLD_POSITION; //保持位置
#endif
#ifdef WINDOW_CHAR_OBSTRUCTION_DETECTED
i8 window_char_uuid_obstruction_detect_str[]                = HAP_CHAR_UUID_OBSTRUCTION_DETECTED; //检测到障碍物
#endif

HOMEKIT_CHARACTER_S window_character[] = {
    {window_char_uuid_current_position_str,                 TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {window_char_uuid_target_position_str,                  TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {window_char_uuid_position_state_str,                   TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#ifdef WINDOW_CHAR_NAME
    {window_char_uuid_name_str,                             FALSE,  FALSE,  HAP_DATA_TYPE_STRING,   .hap_val.s =        /* 在此处可以给特性赋初值 */ },
#endif
#ifdef WINDOW_CHAR_HOLD_POSITION
    {window_char_uuid_hold_position_str,                    FALSE,  FALSE,  HAP_DATA_TYPE_BOOL,     .hap_val.b = 0     /* 在此处可以给特性赋初值 */ },
#endif
#ifdef WINDOW_CHAR_OBSTRUCTION_DETECTED
    {window_char_uuid_obstruction_detect_str,               FALSE,  FALSE,  HAP_DATA_TYPE_BOOL,     .hap_val.b = 0      /* 在此处可以给特性赋初值 */ },
#endif
};
#endif


#ifdef HOMEKIT_SERV_WINDOW_COVERING
i8 hap_serv_uuid_window_covering_str[] = HAP_SERV_UUID_WINDOW_COVERING;
/* WINDOW_COVERING 窗帘服务的特性 */
i8 window_covering_char_uuid_current_position_str[]                     = HAP_CHAR_UUID_CURRENT_POSITION; //当前位置
i8 window_covering_char_uuid_target_position_str[]                      = HAP_CHAR_UUID_TARGET_POSITION; //目标位置
i8 window_covering_char_uuid_position_state_str[]                       = HAP_CHAR_UUID_POSITION_STATE; //位置状态
#ifdef WINDOW_COVERING_CHAR_NAME
i8 window_covering_char_uuid_name_str[]                                 = HAP_CHAR_UUID_NAME; //名称
#endif
#ifdef WINDOW_COVERING_CHAR_HOLD_POSITION
i8 window_covering_char_uuid_hold_position_str[]                        = HAP_CHAR_UUID_HOLD_POSITION; //保持位置
#endif
#ifdef WINDOW_COVERING_CHAR_CURRENT_HORIZONTAL_TILT_ANGLE
i8 window_covering_char_uuid_current_horizontal_tilt_angle_str[]        = HAP_CHAR_UUID_CURRENT_HORIZONTAL_TILT_ANGLE; //当前水平倾斜角度
#endif
#ifdef WINDOW_COVERING_CHAR_TARGET_HORIZONTAL_TILT_ANGLE
i8 window_covering_char_uuid_target_horizontal_tilt_angle_str[]         = HAP_CHAR_UUID_TARGET_HORIZONTAL_TILT_ANGLE; //目标水平倾斜角度
#endif
#ifdef WINDOW_COVERING_CHAR_CURRENT_VERTICAL_TILT_ANGLE
i8 window_covering_char_uuid_current_vertical_tilt_angle_str[]          = HAP_CHAR_UUID_CURRENT_VERTICAL_TILT_ANGLE; //当前垂直倾斜角度
#endif
#ifdef WINDOW_COVERING_CHAR_TARGET_VERTICAL_TILT_ANGLE
i8 window_covering_char_uuid_target_vertical_tilt_angle_str[]           = HAP_CHAR_UUID_TARGET_VERTICAL_TILT_ANGLE; //目标垂直倾斜角度
#endif
#ifdef WINDOW_COVERING_CHAR_OBSTRUCTION_DETECTED
i8 window_covering_char_uuid_obstruction_detect_str[]                   = HAP_CHAR_UUID_OBSTRUCTION_DETECTED; //检测到障碍物
#endif

HOMEKIT_CHARACTER_S window_covering_character[] = {
    {window_covering_char_uuid_current_position_str,                    TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {window_covering_char_uuid_target_position_str,                     TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {window_covering_char_uuid_position_state_str,                      TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#ifdef WINDOW_COVERING_CHAR_NAME
    {window_covering_char_uuid_name_str,                                FALSE,  FALSE,  HAP_DATA_TYPE_STRING,   .hap_val.s =        /* 在此处可以给特性赋初值 */ },
#endif
#ifdef WINDOW_COVERING_CHAR_HOLD_POSITION
    {window_covering_char_uuid_hold_position_str,                       FALSE,  FALSE,  HAP_DATA_TYPE_BOOL,     .hap_val.b = 0     /* 在此处可以给特性赋初值 */ },
#endif
#ifdef WINDOW_COVERING_CHAR_CURRENT_HORIZONTAL_TILT_ANGLE
    {window_covering_char_uuid_current_horizontal_tilt_angle_str,       FALSE,  FALSE,  HAP_DATA_TYPE_INT,      .hap_val.i = 0     /* 在此处可以给特性赋初值 */ },
#endif
#ifdef WINDOW_COVERING_CHAR_TARGET_HORIZONTAL_TILT_ANGLE
    {window_covering_char_uuid_target_horizontal_tilt_angle_str,        FALSE,  FALSE,  HAP_DATA_TYPE_INT,      .hap_val.i = 0     /* 在此处可以给特性赋初值 */ },
#endif
#ifdef WINDOW_COVERING_CHAR_CURRENT_VERTICAL_TILT_ANGLE
    {window_covering_char_uuid_current_vertical_tilt_angle_str,         FALSE,  FALSE,  HAP_DATA_TYPE_INT,      .hap_val.i = 0     /* 在此处可以给特性赋初值 */ },
#endif
#ifdef WINDOW_COVERING_CHAR_TARGET_VERTICAL_TILT_ANGLE
    {window_covering_char_uuid_target_vertical_tilt_angle_str,          FALSE,  FALSE,  HAP_DATA_TYPE_INT,      .hap_val.i = 0     /* 在此处可以给特性赋初值 */ },
#endif
#ifdef WINDOW_COVERING_CHAR_OBSTRUCTION_DETECTED
    {window_covering_char_uuid_obstruction_detect_str,                  FALSE,  FALSE,  HAP_DATA_TYPE_BOOL,     .hap_val.b = 0      /* 在此处可以给特性赋初值 */ },
#endif
};
#endif


#ifdef HOMEKIT_SERV_AIR_PURIFIER
i8 hap_serv_uuid_air_purifier_str[] = HAP_SERV_UUID_AIR_PURIFIER;
/* AIR_PURIFIER 空气净化器服务的特性 */
i8 air_purifier_char_uuid_active_str[]                          = HAP_CHAR_UUID_ACTIVE; //活动状态
i8 air_purifier_char_uuid_current_air_purifier_state_str[]      = HAP_CHAR_UUID_CURRENT_AIR_PURIFIER_STATE; //当前空气净化器状态
i8 air_purifier_char_uuid_target_air_purifier_state_str[]       = HAP_CHAR_UUID_TARGET_AIR_PURIFIER_STATE; //目标空气净化器状态
#ifdef AIR_PURIFIER_CHAR_NAME
i8 air_purifier_char_uuid_name_str[]                            = HAP_CHAR_UUID_NAME; //名称
#endif
#ifdef AIR_PURIFIER_CHAR_ROTATION_SPEED
i8 air_purifier_char_uuid_rotation_speed_str[]                  = HAP_CHAR_UUID_ROTATION_SPEED; //转速
#endif
#ifdef AIR_PURIFIER_CHAR_SWING_MODE
i8 air_purifier_char_uuid_swing_mode_str[]                      = HAP_CHAR_UUID_SWING_MODE; //摇摆模式
#endif
#ifdef AIR_PURIFIER_CHAR_LOCK_PHYSICAL_CONTROLS
i8 air_purifier_char_uuid_lock_physical_controls_str[]          = HAP_CHAR_UUID_LOCK_PHYSICAL_CONTROLS; //锁定物理控制(童锁)
#endif

HOMEKIT_CHARACTER_S air_purifier_character[] = {
    {air_purifier_char_uuid_active_str,                         TRUE,   TRUE,   HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
    {air_purifier_char_uuid_current_air_purifier_state_str,     TRUE,   TRUE,   HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
    {air_purifier_char_uuid_target_air_purifier_state_str,      TRUE,   TRUE,   HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
#ifdef AIR_PURIFIER_CHAR_NAME
    {air_purifier_char_uuid_name_str,                           FALSE,  FALSE,  HAP_DATA_TYPE_STRING,    .hap_val.s =  /* 在此处可以给特性赋初值 */ },
#endif
#ifdef AIR_PURIFIER_CHAR_ROTATION_SPEED
    {air_purifier_char_uuid_rotation_speed_str,                 FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,     .hap_val.f = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef AIR_PURIFIER_CHAR_SWING_MODE
    {air_purifier_char_uuid_swing_mode_str,                     FALSE,  FALSE,  HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef AIR_PURIFIER_CHAR_LOCK_PHYSICAL_CONTROLS
    {air_purifier_char_uuid_lock_physical_controls_str,         FALSE,  FALSE,  HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
#endif
};
#endif


#ifdef HOMEKIT_SERV_FILTER_MAINTENANCE
i8 hap_serv_uuid_filter_maintenance_str[] = HAP_SERV_UUID_FILTER_MAINTENANCE;
/* FILTER_MAINTENANCE 过滤器维护服务的特性 */
i8 filter_maintenance_char_uuid_filter_change_indication_str[]          = HAP_CHAR_UUID_FILTER_CHANGE_INDICATION; //过滤器更换指示
#ifdef FILTER_MAINTENANCE_CHAR_NAME
i8 filter_maintenance_char_uuid_name_str[]                              = HAP_CHAR_UUID_NAME; //名称
#endif
#ifdef FILTER_MAINTENANCE_CHAR_FILTER_LIFE_LEVEL
i8 filter_maintenance_char_uuid_filter_life_level_str[]                 = HAP_CHAR_UUID_FILTER_LIFE_LEVEL; //过滤器使用寿命
#endif
#ifdef FILTER_MAINTENANCE_CHAR_RESET_FILTER_INDICATION
i8 filter_maintenance_char_uuid_reset_filter_indication_str[]           = HAP_CHAR_UUID_RESET_FILTER_INDICATION; //重置过滤器指示
#endif

HOMEKIT_CHARACTER_S filter_maintenance_character[] = {
    {filter_maintenance_char_uuid_filter_change_indication_str,         TRUE,   TRUE,   HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
#ifdef FILTER_MAINTENANCE_CHAR_NAME
    {filter_maintenance_char_uuid_name_str,                             FALSE,  FALSE,  HAP_DATA_TYPE_STRING,    .hap_val.s =  /* 在此处可以给特性赋初值 */ },
#endif
#ifdef FILTER_MAINTENANCE_CHAR_FILTER_LIFE_LEVEL
    {filter_maintenance_char_uuid_filter_life_level_str,                FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,     .hap_val.f = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef FILTER_MAINTENANCE_CHAR_RESET_FILTER_INDICATION
    {filter_maintenance_char_uuid_reset_filter_indication_str,          FALSE,  FALSE,  HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
#endif
};
#endif


#ifdef HOMEKIT_SERV_AIR_QUALITY_SENSOR
i8 hap_serv_uuid_air_quality_sensor_str[] = HAP_SERV_UUID_AIR_QUALITY_SENSOR;
/* AIR_QUALITY_SENSOR 空气质量传感器服务的特性 */
i8 air_quality_sensor_char_uuid_air_quality_str[]                   = HAP_CHAR_UUID_AIR_QUALITY; //空气质量
#ifdef AIR_QUALITY_SENSOR_CHAR_NAME
i8 air_quality_sensor_char_uuid_name_str[]                          = HAP_CHAR_UUID_NAME; //名称
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_OZONE_DENSITY
i8 air_quality_sensor_char_uuid_ozone_density_str[]                 = HAP_CHAR_UUID_OZONE_DENSITY; //臭氧浓度
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_NITROGEN_DIOXIDE_DENSITY
i8 air_quality_sensor_char_uuid_nitrogen_dioxide_density_str[]      = HAP_CHAR_UUID_NITROGEN_DIOXIDE_DENSITY; //二氧化氮密度
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_SULPHUR_DIOXIDE_DENSITY
i8 air_quality_sensor_char_uuid_sulphur_dioxide_density_str[]       = HAP_CHAR_UUID_SULPHUR_DIOXIDE_DENSITY; //二氧化硫浓度
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_PM_2_5_DENSITY
i8 air_quality_sensor_char_uuid_pm_2_5_density_str[]                = HAP_CHAR_UUID_PM_2_5_DENSITY; //PM2.5浓度
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_PM_10_DENSITY
i8 air_quality_sensor_char_uuid_pm_10_density_str[]                 = HAP_CHAR_UUID_PM_10_DENSITY; //PM10浓度
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_VOC_DENSITY
i8 air_quality_sensor_char_uuid_voc_density_str[]                   = HAP_CHAR_UUID_VOC_DENSITY; //VOC密度
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_STATUS_ACTIVE
i8 air_quality_sensor_char_uuid_status_active_str[]                 = HAP_CHAR_UUID_STATUS_ACTIVE; //工作状态活跃
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_STATUS_FAULT
i8 air_quality_sensor_char_uuid_status_fault_str[]                  = HAP_CHAR_UUID_STATUS_FAULT; //状态故障
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_STATUS_TAMPERED
i8 air_quality_sensor_char_uuid_status_tampered_str[]               = HAP_CHAR_UUID_STATUS_TAMPERED; //状态被篡改
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_STATUS_LOW_BATTERY
i8 air_quality_sensor_char_uuid_status_low_battery_str[]            = HAP_CHAR_UUID_STATUS_LOW_BATTERY; //低电量状态
#endif

HOMEKIT_CHARACTER_S air_quality_sensor_character[] = {
    {air_quality_sensor_char_uuid_air_quality_str,                  TRUE,   TRUE,   HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
#ifdef AIR_QUALITY_SENSOR_CHAR_NAME
    {air_quality_sensor_char_uuid_name_str,                         FALSE,  FALSE,  HAP_DATA_TYPE_STRING,    .hap_val.s =  /* 在此处可以给特性赋初值 */ },
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_OZONE_DENSITY
    {air_quality_sensor_char_uuid_ozone_density_str,                FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,     .hap_val.f = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_NITROGEN_DIOXIDE_DENSITY
    {air_quality_sensor_char_uuid_nitrogen_dioxide_density_str,     FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,     .hap_val.f = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_SULPHUR_DIOXIDE_DENSITY
    {air_quality_sensor_char_uuid_sulphur_dioxide_density_str,      FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,     .hap_val.f = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_PM_2_5_DENSITY
    {air_quality_sensor_char_uuid_pm_2_5_density_str,               FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,     .hap_val.f = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_PM_10_DENSITY
    {air_quality_sensor_char_uuid_pm_10_density_str,                FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,     .hap_val.f = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_VOC_DENSITY
    {air_quality_sensor_char_uuid_voc_density_str,                  FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,     .hap_val.f = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_STATUS_ACTIVE
    {air_quality_sensor_char_uuid_status_active_str,                FALSE,  FALSE,  HAP_DATA_TYPE_BOOL,      .hap_val.b = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_STATUS_FAULT
    {air_quality_sensor_char_uuid_status_fault_str,                 FALSE,  FALSE,  HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_STATUS_TAMPERED
    {air_quality_sensor_char_uuid_status_tampered_str,              FALSE,  FALSE,  HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef AIR_QUALITY_SENSOR_CHAR_STATUS_LOW_BATTERY
    {air_quality_sensor_char_uuid_status_low_battery_str,           FALSE,  FALSE,  HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
#endif
};
#endif


#ifdef HOMEKIT_SERV_SLAT
i8 hap_serv_uuid_slat_str[] = HAP_SERV_UUID_SLAT;
/* SLAT 板条服务的特性 */
i8 slat_char_uuid_current_slat_state_str[]                  = HAP_CHAR_UUID_CURRENT_SLAT_STATE; //当前板条状态
i8 slat_char_uuid_slat_type_str[]                           = HAP_CHAR_UUID_SLAT_TYPE; //板条类型
#ifdef SLAT_CHAR_NAME
i8 slat_char_uuid_name_str[]                                = HAP_CHAR_UUID_NAME; //名称
#endif
#ifdef SLAT_CHAR_SWING_MODE
i8 slat_char_uuid_swing_mode_str[]                          = HAP_CHAR_UUID_SWING_MODE; //摇摆模式
#endif
#ifdef SLAT_CHAR_CURRENT_TILT_ANGLE
i8 slat_char_uuid_filter_life_level_str[]                   = HAP_CHAR_UUID_CURRENT_TILT_ANGLE; //当前倾斜角度
#endif
#ifdef SLAT_CHAR_TARGET_TILT_ANGLE
i8 slat_char_uuid_reset_filter_indication_str[]             = HAP_CHAR_UUID_TARGET_TILT_ANGLE; //目标倾斜角度
#endif

HOMEKIT_CHARACTER_S slat_character[] = {
    {slat_char_uuid_current_slat_state_str,                 TRUE,   TRUE,   HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
    {slat_char_uuid_slat_type_str,                          TRUE,   TRUE,   HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
#ifdef SLAT_CHAR_NAME
    {slat_char_uuid_name_str,                               FALSE,  FALSE,  HAP_DATA_TYPE_STRING,    .hap_val.s =  /* 在此处可以给特性赋初值 */ },
#endif
#ifdef SLAT_CHAR_SWING_MODE
    {slat_char_uuid_swing_mode_str,                         FALSE,  FALSE,  HAP_DATA_TYPE_UINT,      .hap_val.u = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef SLAT_CHAR_CURRENT_TILT_ANGLE
    {slat_char_uuid_filter_life_level_str,                  FALSE,  FALSE,  HAP_DATA_TYPE_INT,       .hap_val.i = 0 /* 在此处可以给特性赋初值 */ },
#endif
#ifdef SLAT_CHAR_TARGET_TILT_ANGLE
    {slat_char_uuid_reset_filter_indication_str,            FALSE,  FALSE,  HAP_DATA_TYPE_INT,       .hap_val.i = 0 /* 在此处可以给特性赋初值 */ },
#endif
};
#endif


#ifdef HOMEKIT_SERV_HEATER_COOLER
i8 hap_serv_uuid_heater_cooler_str[] = HAP_SERV_UUID_HEATER_COOLER;
/* HEATER_COOLER 加热器冷却器服务的特性 */
i8 heater_cooler_char_uuid_active_str[]                             = HAP_CHAR_UUID_ACTIVE; //活动状态
i8 heater_cooler_char_uuid_current_temperature_str[]                = HAP_CHAR_UUID_CURRENT_TEMPERATURE; //当前温度
i8 heater_cooler_char_uuid_current_heater_cooler_state_str[]        = HAP_CHAR_UUID_CURRENT_HEATER_COOLER_STATE; //当前加热器冷却器状态
i8 heater_cooler_char_uuid_target_heater_cooler_state_str[]         = HAP_CHAR_UUID_TARGET_HEATER_COOLER_STATE; //目标加热器冷却器状态
#ifdef HEATER_COOLER_CHAR_NAME
i8 heater_cooler_char_uuid_name_str[]                               = HAP_CHAR_UUID_NAME; //名称
#endif
#ifdef HEATER_COOLER_CHAR_ROTATION_SPEED
i8 heater_cooler_char_uuid_rotation_speed_str[]                     = HAP_CHAR_UUID_ROTATION_SPEED; //转速
#endif
#ifdef HEATER_COOLER_CHAR_TEMPERATURE_DISPLAY_UNITS
i8 heater_cooler_char_uuid_temperature_display_units_str[]          = HAP_CHAR_UUID_TEMPERATURE_DISPLAY_UNITS; //温度显示单元
#endif
#ifdef HEATER_COOLER_CHAR_SWING_MODE
i8 heater_cooler_char_uuid_swing_mode_str[]                         = HAP_CHAR_UUID_SWING_MODE; //摇摆模式
#endif
#ifdef HEATER_COOLER_CHAR_COOLING_THRESHOLD_TEMPERATURE
i8 heater_cooler_char_uuid_cooling_threshold_temperature_str[]      = HAP_CHAR_UUID_COOLING_THRESHOLD_TEMPERATURE; //冷却阈值温度
#endif
#ifdef HEATER_COOLER_CHAR_HEATING_THRESHOLD_TEMPERATURE
i8 heater_cooler_char_uuid_heating_threshold_temperature_str[]      = HAP_CHAR_UUID_HEATING_THRESHOLD_TEMPERATURE; //加热阈值温度
#endif
#ifdef HEATER_COOLER_CHAR_LOCK_PHYSICAL_CONTROLS
i8 heater_cooler_char_uuid_lock_physical_controls_str[]             = HAP_CHAR_UUID_LOCK_PHYSICAL_CONTROLS; //锁定物理控制(童锁)
#endif

HOMEKIT_CHARACTER_S heater_cooler_character[] = {
    {heater_cooler_char_uuid_active_str,                            TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {heater_cooler_char_uuid_current_temperature_str,               TRUE,   TRUE,   HAP_DATA_TYPE_FLOAT,    .hap_val.f = 0      /* 在此处可以给特性赋初值 */ },
    {heater_cooler_char_uuid_current_heater_cooler_state_str,       TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {heater_cooler_char_uuid_target_heater_cooler_state_str,        TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 10     /* 在此处可以给特性赋初值 */ },
#ifdef HEATER_COOLER_CHAR_NAME
    {heater_cooler_char_uuid_name_str,                              FALSE,  FALSE,  HAP_DATA_TYPE_STRING,   .hap_val.s =        /* 在此处可以给特性赋初值 */ },
#endif
#ifdef HEATER_COOLER_CHAR_ROTATION_SPEED
    {heater_cooler_char_uuid_rotation_speed_str,                    FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,    .hap_val.f = 0      /* 在此处可以给特性赋初值 */ },
#endif
#ifdef HEATER_COOLER_CHAR_TEMPERATURE_DISPLAY_UNITS
    {heater_cooler_char_uuid_temperature_display_units_str,         FALSE,  FALSE,  HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#endif
#ifdef HEATER_COOLER_CHAR_SWING_MODE
    {heater_cooler_char_uuid_swing_mode_str,                        FALSE,  FALSE,  HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#endif
#ifdef HEATER_COOLER_CHAR_COOLING_THRESHOLD_TEMPERATURE
    {heater_cooler_char_uuid_cooling_threshold_temperature_str,     FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,    .hap_val.f = 10     /* 在此处可以给特性赋初值 */ },
#endif
#ifdef HEATER_COOLER_CHAR_HEATING_THRESHOLD_TEMPERATURE
    {heater_cooler_char_uuid_heating_threshold_temperature_str,     FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,    .hap_val.f = 0      /* 在此处可以给特性赋初值 */ },
#endif
#ifdef HEATER_COOLER_CHAR_LOCK_PHYSICAL_CONTROLS
    {heater_cooler_char_uuid_lock_physical_controls_str,            FALSE,  FALSE,  HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#endif
};
#endif


#ifdef HOMEKIT_SERV_HUMIDIFIER_DEHUMIDIFIER
i8 hap_serv_uuid_humidifier_dehumidifier_str[] = HAP_SERV_UUID_HUMIDIFIER_DEHUMIDIFIER;
/* HUMIDIFIER_DEHUMIDIFIER 加湿器除湿机服务的特性 */
i8 humidifier_dehumidifier_char_uuid_active_str[]                                       = HAP_CHAR_UUID_ACTIVE; //活动状态
i8 humidifier_dehumidifier_char_uuid_current_relative_humidity_str[]                    = HAP_CHAR_UUID_CURRENT_RELATIVE_HUMIDITY; //当前相对湿度
i8 humidifier_dehumidifier_char_uuid_current_humidifier_dehumidifier_state_str[]        = HAP_CHAR_UUID_CURRENT_HUMIDIFIER_DEHUMIDIFIER_STATE; //当前加湿器除湿器状态
i8 humidifier_dehumidifier_char_uuid_target_humidifier_dehumidifier_state_str[]         = HAP_CHAR_UUID_TARGET_HUMIDIFIER_DEHUMIDIFIER_STATE; //目标加湿器除湿器状态
#ifdef HUMIDIFIER_DEHUMIDIFIER_CHAR_NAME
i8 humidifier_dehumidifier_char_uuid_name_str[]                                         = HAP_CHAR_UUID_NAME; //名称
#endif
#ifdef HUMIDIFIER_DEHUMIDIFIER_CHAR_RELATIVE_HUMIDITY_DEHUMIDIFIER_THRESHOLD
i8 humidifier_dehumidifier_char_uuid_relative_humidity_dehumidifier_threshold_str[]     = HAP_CHAR_UUID_RELATIVE_HUMIDITY_DEHUMIDIFIER_THRESHOLD; //相对湿度除湿器阈值
#endif
#ifdef HUMIDIFIER_DEHUMIDIFIER_CHAR_RELATIVE_HUMIDITY_HUMIDIFIER_THRESHOLD
i8 humidifier_dehumidifier_char_uuid_relative_humidity_humidifier_threshold_str[]       = HAP_CHAR_UUID_RELATIVE_HUMIDITY_HUMIDIFIER_THRESHOLD; //相对湿度加湿器阈值
#endif
#ifdef HUMIDIFIER_DEHUMIDIFIER_CHAR_ROTATION_SPEED
i8 humidifier_dehumidifier_char_uuid_rotation_speed_str[]                               = HAP_CHAR_UUID_ROTATION_SPEED; //转速
#endif
#ifdef HUMIDIFIER_DEHUMIDIFIER_CHAR_SWING_MODE
i8 humidifier_dehumidifier_char_uuid_swing_mode_str[]                                   = HAP_CHAR_UUID_SWING_MODE; //摇摆模式
#endif
#ifdef HUMIDIFIER_DEHUMIDIFIER_CHAR_WATER_LEVEL
i8 humidifier_dehumidifier_char_uuid_water_level_str[]                                  = HAP_CHAR_UUID_WATER_LEVEL; //水位
#endif
#ifdef HUMIDIFIER_DEHUMIDIFIER_CHAR_LOCK_PHYSICAL_CONTROLS
i8 humidifier_dehumidifier_char_uuid_lock_physical_controls_str[]                       = HAP_CHAR_UUID_LOCK_PHYSICAL_CONTROLS; //锁定物理控制(童锁)
#endif

HOMEKIT_CHARACTER_S humidifier_dehumidifier_character[] = {
    {humidifier_dehumidifier_char_uuid_active_str,                                      TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {humidifier_dehumidifier_char_uuid_current_relative_humidity_str,                   TRUE,   TRUE,   HAP_DATA_TYPE_FLOAT,    .hap_val.f = 0      /* 在此处可以给特性赋初值 */ },
    {humidifier_dehumidifier_char_uuid_current_humidifier_dehumidifier_state_str,       TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {humidifier_dehumidifier_char_uuid_target_humidifier_dehumidifier_state_str,        TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#ifdef HUMIDIFIER_DEHUMIDIFIER_CHAR_NAME
    {humidifier_dehumidifier_char_uuid_name_str,                                        FALSE,  FALSE,  HAP_DATA_TYPE_STRING,   .hap_val.s =        /* 在此处可以给特性赋初值 */ },
#endif
#ifdef HUMIDIFIER_DEHUMIDIFIER_CHAR_RELATIVE_HUMIDITY_DEHUMIDIFIER_THRESHOLD
    {humidifier_dehumidifier_char_uuid_relative_humidity_dehumidifier_threshold_str,    FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,    .hap_val.f = 0      /* 在此处可以给特性赋初值 */ },
#endif
#ifdef HUMIDIFIER_DEHUMIDIFIER_CHAR_RELATIVE_HUMIDITY_HUMIDIFIER_THRESHOLD
    {humidifier_dehumidifier_char_uuid_relative_humidity_humidifier_threshold_str,      FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,    .hap_val.f = 0      /* 在此处可以给特性赋初值 */ },
#endif
#ifdef HUMIDIFIER_DEHUMIDIFIER_CHAR_ROTATION_SPEED
    {humidifier_dehumidifier_char_uuid_rotation_speed_str,                              FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,    .hap_val.f = 0      /* 在此处可以给特性赋初值 */ },
#endif
#ifdef HUMIDIFIER_DEHUMIDIFIER_CHAR_SWING_MODE
    {humidifier_dehumidifier_char_uuid_swing_mode_str,                                  FALSE,  FALSE,  HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#endif
#ifdef HUMIDIFIER_DEHUMIDIFIER_CHAR_WATER_LEVEL
    {humidifier_dehumidifier_char_uuid_water_level_str,                                 FALSE,  FALSE,  HAP_DATA_TYPE_FLOAT,    .hap_val.f = 0      /* 在此处可以给特性赋初值 */ },
#endif
#ifdef HUMIDIFIER_DEHUMIDIFIER_CHAR_LOCK_PHYSICAL_CONTROLS
    {humidifier_dehumidifier_char_uuid_lock_physical_controls_str,                      FALSE,  FALSE,  HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#endif
};
#endif


#ifdef HOMEKIT_SERV_IRRIGATION_SYSTEM
i8 hap_serv_uuid_irrigation_system_str[] = HAP_SERV_UUID_IRRIGATION_SYSTEM;
/* IRRIGATION_SYSTEM 灌溉系统服务的特性 */
i8 irrigation_system_char_uuid_active_str[]                 = HAP_CHAR_UUID_ACTIVE; //活动状态
i8 irrigation_system_char_uuid_program_mode_str[]           = HAP_CHAR_UUID_PROGRAM_MODE; //程序模式
i8 irrigation_system_char_uuid_in_use_str[]                 = HAP_CHAR_UUID_IN_USE; //使用中
#ifdef IRRIGATION_SYSTEM_CHAR_NAME
i8 irrigation_system_char_uuid_name_str[]                   = HAP_CHAR_UUID_NAME; //名称
#endif
#ifdef IRRIGATION_SYSTEM_CHAR_REMAINING_DURATION
i8 irrigation_system_char_uuid_remaining_duration_str[]     = HAP_CHAR_UUID_REMAINING_DURATION; //剩余时间
#endif
#ifdef IRRIGATION_SYSTEM_CHAR_STATUS_FAULT
i8 irrigation_system_char_uuid_status_fault_str[]           = HAP_CHAR_UUID_STATUS_FAULT; //状态故障
#endif

HOMEKIT_CHARACTER_S irrigation_system_character[] = {
    {irrigation_system_char_uuid_active_str,                TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {irrigation_system_char_uuid_program_mode_str,          TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {irrigation_system_char_uuid_in_use_str,                TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#ifdef IRRIGATION_SYSTEM_CHAR_NAME
    {irrigation_system_char_uuid_name_str,                  FALSE,  FALSE,  HAP_DATA_TYPE_STRING,   .hap_val.s =        /* 在此处可以给特性赋初值 */ },
#endif
#ifdef IRRIGATION_SYSTEM_CHAR_REMAINING_DURATION
    {irrigation_system_char_uuid_remaining_duration_str,    FALSE,  FALSE,  HAP_DATA_TYPE_UINT,     .hap_val.u = 0     /* 在此处可以给特性赋初值 */ },
#endif
#ifdef IRRIGATION_SYSTEM_CHAR_STATUS_FAULT
    {irrigation_system_char_uuid_status_fault_str,          FALSE,  FALSE,  HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#endif
};
#endif


#ifdef HOMEKIT_SERV_VALVE
i8 hap_serv_uuid_valve_str[] = HAP_SERV_UUID_VALVE;
/* VALVE 阀门服务的特性 */
i8 valve_char_uuid_active_str[]                 = HAP_CHAR_UUID_ACTIVE; //活动状态
i8 valve_char_uuid_in_use_str[]                 = HAP_CHAR_UUID_IN_USE; //使用中
i8 valve_char_uuid_valve_type_str[]             = HAP_CHAR_UUID_VALVE_TYPE; //阀门类型
#ifdef VALVE_CHAR_NAME
i8 valve_char_uuid_name_str[]                   = HAP_CHAR_UUID_NAME; //名称
#endif
#ifdef VALVE_CHAR_SET_DURATION
i8 valve_char_uuid_set_duration_str[]           = HAP_CHAR_UUID_SET_DURATION; //设置时间
#endif
#ifdef VALVE_CHAR_REMAINING_DURATION
i8 valve_char_uuid_remaining_duration_str[]     = HAP_CHAR_UUID_REMAINING_DURATION; //剩余时间
#endif
#ifdef VALVE_CHAR_IS_CONFIGURED
i8 valve_char_uuid_is_configured_str[]          = HAP_CHAR_UUID_IS_CONFIGURED; //已配置
#endif
#ifdef VALVE_CHAR_SERVICE_LABEL_INDEX
i8 valve_char_uuid_service_label_index_str[]    = HAP_CHAR_UUID_SERVICE_LABEL_INDEX; //服务标签索引
#endif
#ifdef VALVE_CHAR_STATUS_FAULT
i8 valve_char_uuid_status_fault_str[]           = HAP_CHAR_UUID_STATUS_FAULT; //状态故障
#endif

HOMEKIT_CHARACTER_S valve_character[] = {
    {valve_char_uuid_active_str,                TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {valve_char_uuid_in_use_str,                TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
    {valve_char_uuid_valve_type_str,            TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#ifdef VALVE_CHAR_NAME
    {valve_char_uuid_name_str,                  FALSE,  FALSE,  HAP_DATA_TYPE_STRING,   .hap_val.s =        /* 在此处可以给特性赋初值 */ },
#endif
#ifdef VALVE_CHAR_SET_DURATION
    {valve_char_uuid_set_duration_str,          FALSE,  FALSE,  HAP_DATA_TYPE_UINT,     .hap_val.u = 0     /* 在此处可以给特性赋初值 */ },
#endif
#ifdef VALVE_CHAR_REMAINING_DURATION
    {valve_char_uuid_remaining_duration_str,    FALSE,  FALSE,  HAP_DATA_TYPE_UINT,     .hap_val.u = 0     /* 在此处可以给特性赋初值 */ },
#endif
#ifdef VALVE_CHAR_IS_CONFIGURED
    {valve_char_uuid_is_configured_str,         FALSE,  FALSE,  HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#endif
#ifdef VALVE_CHAR_SERVICE_LABEL_INDEX
    {valve_char_uuid_service_label_index_str,   FALSE,  FALSE,  HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#endif
#ifdef VALVE_CHAR_STATUS_FAULT
    {valve_char_uuid_status_fault_str,          FALSE,  FALSE,  HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#endif
};
#endif


#ifdef HOMEKIT_SERV_FAUCET
i8 hap_serv_uuid_faucet_str[] = HAP_SERV_UUID_FAUCET;
/* FAUCET 水龙头服务的可选特性选择 */
i8 faucet_char_uuid_active_str[]                = HAP_CHAR_UUID_ACTIVE; //活动状态
#ifdef FAUCET_CHAR_NAME
i8 faucet_char_uuid_name_str[]                  = HAP_CHAR_UUID_NAME; //名称
#endif
#ifdef FAUCET_CHAR_STATUS_FAULT
i8 faucet_char_uuid_status_fault_str[]          = HAP_CHAR_UUID_STATUS_FAULT; //状态故障
#endif

HOMEKIT_CHARACTER_S faucet_character[] = {
    {faucet_char_uuid_active_str,               TRUE,   TRUE,   HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#ifdef FAUCET_CHAR_NAME
    {faucet_char_uuid_name_str,                 FALSE,  FALSE,  HAP_DATA_TYPE_STRING,   .hap_val.s =        /* 在此处可以给特性赋初值 */ },
#endif
#ifdef FAUCET_CHAR_STATUS_FAULT
    {faucet_char_uuid_status_fault_str,         FALSE,  FALSE,  HAP_DATA_TYPE_UINT,     .hap_val.u = 0      /* 在此处可以给特性赋初值 */ },
#endif
};
#endif



/******************************************************************************
                    4.HomeKit服务配置
根据服务配置选择和特性配置选择自动配置。如果有多个服务，将会进行服务链接，需要指定一个主服务。
主服务为此配置中的第一个服务，此时需要用户自行调整服务配置的顺序。
******************************************************************************/
#ifdef HOMEKIT_PRODUCT_TYPE
HOMEKIT_SERVICE_S homekit_service[] = {
#ifdef HOMEKIT_SERV_FAN_V2
    {
        0, //需要用户自行修改服务序号，且不能与其他相同
        hap_serv_uuid_fan_v2_str,
        FALSE,
        CNTSOF(fan_v2_character),
        fan_v2_character,
    },
#endif
#ifdef HOMEKIT_SERV_GARAGE_DOOR_OPENER
    {
        1, //需要用户自行修改服务序号，且不能与其他相同
        hap_serv_uuid_garage_door_opener_str,
        FALSE,
        CNTSOF(garage_door_opener_character),
        garage_door_opener_character,
    },
#endif
#ifdef HOMEKIT_SERV_LIGHTBULB
    {
        2, //需要用户自行修改服务序号，且不能与其他相同
        hap_serv_uuid_lightbulb_str,
        FALSE,
        CNTSOF(lightbulb_character),
        lightbulb_character,
    },
#endif
#ifdef HOMEKIT_SERV_THERMOSTAT
    {
        3, //需要用户自行修改服务序号，且不能与其他相同
        hap_serv_uuid_thermostat_str,
        FALSE,
        CNTSOF(thermostat_character),
        thermostat_character,
    },
#endif
#ifdef HOMEKIT_SERV_DOOR
    {
        4, //需要用户自行修改服务序号，且不能与其他相同
        hap_serv_uuid_door_str,
        FALSE,
        CNTSOF(door_character),
        door_character,
    },
#endif
#ifdef HOMEKIT_SERV_WINDOW
    {
        5, //需要用户自行修改服务序号，且不能与其他相同
        hap_serv_uuid_window_str,
        FALSE,
        CNTSOF(window_character),
        window_character,
    },
#endif
#ifdef HOMEKIT_SERV_WINDOW_COVERING
    {
        6, //需要用户自行修改服务序号，且不能与其他相同
        hap_serv_uuid_window_covering_str,
        FALSE,
        CNTSOF(window_covering_character),
        window_covering_character,
    },
#endif
#ifdef HOMEKIT_SERV_AIR_PURIFIER
    {
        7, //需要用户自行修改服务序号，且不能与其他相同
        hap_serv_uuid_air_purifier_str,
        FALSE,
        CNTSOF(air_purifier_character),
        air_purifier_character,
    },
#endif
#ifdef HOMEKIT_SERV_FILTER_MAINTENANCE
    {
        8, //需要用户自行修改服务序号，且不能与其他相同
        hap_serv_uuid_filter_maintenance_str,
        FALSE,
        CNTSOF(filter_maintenance_character),
        filter_maintenance_character,
    },
#endif
#ifdef HOMEKIT_SERV_AIR_QUALITY_SENSOR
    {
        9, //需要用户自行修改服务序号，且不能与其他相同
        hap_serv_uuid_air_quality_sensor_str,
        FALSE,
        CNTSOF(air_quality_sensor_character),
        air_quality_sensor_character,
    },
#endif
#ifdef HOMEKIT_SERV_SLAT
    {
        10, //需要用户自行修改服务序号，且不能与其他相同
        hap_serv_uuid_slat_str,
        FALSE,
        CNTSOF(slat_character),
        slat_character,
    },
#endif
#ifdef HOMEKIT_SERV_HEATER_COOLER
    {
        11, //需要用户自行修改服务序号，且不能与其他相同
        hap_serv_uuid_heater_cooler_str,
        FALSE,
        CNTSOF(heater_cooler_character),
        heater_cooler_character,
    },
#endif
#ifdef HOMEKIT_SERV_HUMIDIFIER_DEHUMIDIFIER
    {
        12, //需要用户自行修改服务序号，且不能与其他相同
        hap_serv_uuid_humidifier_dehumidifier_str,
        FALSE,
        CNTSOF(humidifier_dehumidifier_character),
        humidifier_dehumidifier_character,
    },
#endif
#ifdef HOMEKIT_SERV_IRRIGATION_SYSTEM
    {
        13, //需要用户自行修改服务序号，且不能与其他相同
        hap_serv_uuid_irrigation_system_str,
        FALSE,
        CNTSOF(irrigation_system_character),
        irrigation_system_character,
    },
#endif
#ifdef HOMEKIT_SERV_VALVE
    {
        14, //需要用户自行修改服务序号，且不能与其他相同
        hap_serv_uuid_valve_str,
        FALSE,
        CNTSOF(valve_character),
        valve_character,
    },
#endif
#ifdef HOMEKIT_SERV_FAUCET
    {
        15, //需要用户自行修改服务序号，且不能与其他相同
        hap_serv_uuid_faucet_str,
        FALSE,
        CNTSOF(faucet_character),
        faucet_character,
    },
#endif

};
#endif



/******************************************************************************
                    5.HomeKit功能相关函数
******************************************************************************/
#ifdef HOMEKIT_PRODUCT_TYPE
/**
 * @brief  数值换算成小数部分
 * @param[in] {val} int类型数据
 * @return 转换之后的float类型数据
 * @note   
 */
float int_change_fraction(u32 val)
{
    u32 val_magnitudes = 10;

    while(0 != val / val_magnitudes) {
        val_magnitudes *= 10;
    }

    return (float)val / val_magnitudes;
}

/**
 * @brief  小数部分换算成数值
 * @param[in] {f_val} float类型数据
 * @return 转换之后的int类型数据
 * @note   
 */
u32 fractional_part_change_int(float f_val)
{
    u32 val_magnitudes = 10;
    u8 i = 0;
    float fraction = 0.0f;
    float change_val = 0.0f;
    float val = f_val;

    fraction = val - (u32)val; //取小数部分
    if(0 == fraction) {
        return 0;
    }

    for(i = 0; i < 5; i++) {
        change_val = val * val_magnitudes;
        if(0 == change_val - (u32)change_val) {
            return (u32)change_val - ((u32)val * val_magnitudes);
        }
        val_magnitudes *= 10;
    }

    return (u32)change_val - ((u32)val * val_magnitudes);
}

#ifdef HOMEKIT_CHARACTER_VALID_CFG_ENABLE
/**
 * @brief  特性有效值配置
 * @param  Null
 * @return Null
 * @note   
 */
static void char_valid_value_cfg(void)
{
    //#error "请自行完成特性有效值配置代码,完成后请删除该行"
    static u8 cfg_count = 0;
    u16 send_len = 0;
    char strbuff[80] = {0};
    u8 strlen = 0;
    
    switch(cfg_count++) {
        case 0:
            //请在此处配置有效值配置字符串
            //例如:strlen = sprintf(strbuff, "{\"service_serial\":7,\"char_str\":\"A9\",\"val_type\":0,\"valid_val\":[0,2]}");
        break;
        
        //如果需要配置多个，请添加case
//        case 1:
//            //请在此处配置有效值配置字符串
//        break;
        
        default:
            //有效值配置完成，结束服务配置
            send_len = set_wifi_uart_byte(send_len, HK_SUB_CMD_CFG_QUERY);
            wifi_uart_write_frame(HOMEKIT_FUN_CMD, MCU_TX_VER, send_len);
            cfg_count = 0;
            return;
        break;
    }
    
    send_len = set_wifi_uart_byte(send_len, HK_SUB_CMD_CHARACTER_VALID_CFG);
    send_len = set_wifi_uart_buffer(send_len, strbuff, strlen);
    wifi_uart_write_frame(HOMEKIT_FUN_CMD, MCU_TX_VER, send_len);
}
#endif

/**
 * @brief  HomeKit相关功能处理
 * @param[in] {p_data} 串口数据
 * @return Null
 * @note   
 */
static void homekit_service_cfg(u8 p_data[], u16 data_len)
{
    static u8 service_cfg_count = 0;
    
    u16 send_len = 0;
    u16 i = 0;
    
    switch(p_data[0]) { //子命令
        case HK_SUB_CMD_CFG_QUERY:
            if(0 != CNTSOF(homekit_service)) {
                //发送服务配置
                send_len = 0;
                send_len = set_wifi_uart_byte(send_len, HK_SUB_CMD_SERVICE_CFG);
                send_len = set_wifi_uart_byte(send_len, homekit_service[service_cfg_count].serial);
                send_len = set_wifi_uart_byte(send_len, my_strlen(homekit_service[service_cfg_count].p_service_str));
                send_len = set_wifi_uart_buffer(send_len, homekit_service[service_cfg_count].p_service_str, my_strlen(homekit_service[service_cfg_count].p_service_str));
                wifi_uart_write_frame(HOMEKIT_FUN_CMD, MCU_TX_VER, send_len);
            }
        break;
        
        case HK_SUB_CMD_SERVICE_CFG:
            if(0x00 == p_data[1]) {
                //服务配置成功
                homekit_service[service_cfg_count].config_flag = !p_data[1];
                
                //发送可选特性配置
                send_len = 0;
                send_len = set_wifi_uart_byte(send_len, HK_SUB_CMD_CHARACTER_CFG);
                send_len = set_wifi_uart_byte(send_len, homekit_service[service_cfg_count].serial);
                
                for(i = 0; i < homekit_service[service_cfg_count].character_amount; i++) {
                    if(TRUE == homekit_service[service_cfg_count].p_character_arr[i].character_sort_flag) {
                        continue; //必选特性不必发送
                    }
                    
                    send_len = set_wifi_uart_byte(send_len, my_strlen(homekit_service[service_cfg_count].p_character_arr[i].p_character_str));
                    send_len = set_wifi_uart_buffer(send_len, homekit_service[service_cfg_count].p_character_arr[i].p_character_str, my_strlen(homekit_service[service_cfg_count].p_character_arr[i].p_character_str));
                }
                
                if(2 == send_len) { //无可选特性配置
                    service_cfg_count++; //此服务完成配置
                
                    //判断是否还有服务配置要发送，如果有则继续发送
                    if(service_cfg_count < CNTSOF(homekit_service)) { //还有服务需要配置
                        send_len = 0;
                        send_len = set_wifi_uart_byte(send_len, HK_SUB_CMD_SERVICE_CFG);
                        send_len = set_wifi_uart_byte(send_len, homekit_service[service_cfg_count].serial);
                        send_len = set_wifi_uart_byte(send_len, my_strlen(homekit_service[service_cfg_count].p_service_str));
                        send_len = set_wifi_uart_buffer(send_len, homekit_service[service_cfg_count].p_service_str, my_strlen(homekit_service[service_cfg_count].p_service_str));
                        wifi_uart_write_frame(HOMEKIT_FUN_CMD, MCU_TX_VER, send_len);
                    }else { //所有服务配置完成
#ifdef HOMEKIT_CHARACTER_VALID_CFG_ENABLE
                        //HomeKit特性有效值配置
                        char_valid_value_cfg();
#else
                        //回复服务配置查询，结束服务配置
                        send_len = 0;
                        send_len = set_wifi_uart_byte(send_len, HK_SUB_CMD_CFG_QUERY);
                        wifi_uart_write_frame(HOMEKIT_FUN_CMD, MCU_TX_VER, send_len);
#endif
                        service_cfg_count = 0;
                    }
                }else {
                    //发送可选特性配置
                    wifi_uart_write_frame(HOMEKIT_FUN_CMD, MCU_TX_VER, send_len);
                }
            }else {
                //服务配置失败
            }
        break;
        
        case HK_SUB_CMD_CHARACTER_CFG:
            if(0x00 == p_data[1]) {
                //可选特性配置成功
                u8 character_cfg_num = 0;
                
                for(i = 0; i < homekit_service[service_cfg_count].character_amount; i++) {
                    if(TRUE == homekit_service[service_cfg_count].p_character_arr[i].character_sort_flag) {
                        continue; //必选特性不必处理
                    }
                    character_cfg_num++;
                    if(data_len - 2 < character_cfg_num) {
                        //接收的数据有误
                        
                        service_cfg_count = 0;
                        return;
                    }
                    homekit_service[service_cfg_count].p_character_arr[i].character_config_flag = TRUE;
                }
                
                service_cfg_count++; //此服务完成配置
                
                //判断是否还有服务配置要发送，如果有则继续发送
                if(service_cfg_count < CNTSOF(homekit_service)) { //还有服务需要配置
                    send_len = 0;
                    send_len = set_wifi_uart_byte(send_len, HK_SUB_CMD_SERVICE_CFG);
                    send_len = set_wifi_uart_byte(send_len, homekit_service[service_cfg_count].serial);
                    send_len = set_wifi_uart_byte(send_len, my_strlen(homekit_service[service_cfg_count].p_service_str));
                    send_len = set_wifi_uart_buffer(send_len, homekit_service[service_cfg_count].p_service_str, my_strlen(homekit_service[service_cfg_count].p_service_str));
                    wifi_uart_write_frame(HOMEKIT_FUN_CMD, MCU_TX_VER, send_len);
                }else { //所有服务配置完成
#ifdef HOMEKIT_CHARACTER_VALID_CFG_ENABLE
                    //HomeKit特性有效值配置
                    char_valid_value_cfg();
#else
                    //回复服务配置查询，结束服务配置
                    send_len = 0;
                    send_len = set_wifi_uart_byte(send_len, HK_SUB_CMD_CFG_QUERY);
                    wifi_uart_write_frame(HOMEKIT_FUN_CMD, MCU_TX_VER, send_len);
#endif
                    service_cfg_count = 0;
                }
            }else {
                //可选特性配置失败
            }
        break;
        
        default:break;
    }
}


/**
 * @brief  HomeKit特性下发数据解析
 * @param[in] {p_data} 串口数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   
 */
void homekit_character_parse(u8 p_data[], u16 data_len)
{
    u8 ret = 0;
    u16 offset = 0;
    u8 serv_serial;
    u16 char_str_len = 0;
    i8 char_str[4] = {0};
    u8 char_data_type;
    u16 char_val_len = 0;
    u8 *p_char_data_val = NULL;
    HAP_VALUE_T char_val = {0};
    
    for(offset = 1;offset < data_len; ) {
        serv_serial = p_data[offset];
        char_str_len = p_data[offset + 1];
        my_memcpy(char_str, &p_data[offset + 2], char_str_len);
        char_data_type = p_data[offset + 2 + char_str_len];
        char_val_len = (p_data[offset + 3 + char_str_len] << 8) | p_data[offset + 4 + char_str_len];
        p_char_data_val = p_data + offset + 5 + char_str_len;
        
        switch(char_data_type) {
            case HAP_DATA_TYPE_BOOL:
                char_val.b = p_char_data_val[0]? TRUE : FALSE;
            break;
            
            case HAP_DATA_TYPE_UINT:
                char_val.u = (p_char_data_val[0] << 24) | (p_char_data_val[1] << 16) | (p_char_data_val[2] << 8) | p_char_data_val[3];
            break;
            
            case HAP_DATA_TYPE_INT:
                char_val.i = (p_char_data_val[0] << 24) | (p_char_data_val[1] << 16) | (p_char_data_val[2] << 8) | p_char_data_val[3];
            break;
            
            case HAP_DATA_TYPE_UINT64:
                char_val.i64 = p_char_data_val[0];
                char_val.i64 = (char_val.i64 << 8) | p_char_data_val[1];
                char_val.i64 = (char_val.i64 << 8) | p_char_data_val[2];
                char_val.i64 = (char_val.i64 << 8) | p_char_data_val[3];
                char_val.i64 = (char_val.i64 << 8) | p_char_data_val[4];
                char_val.i64 = (char_val.i64 << 8) | p_char_data_val[5];
                char_val.i64 = (char_val.i64 << 8) | p_char_data_val[6];
                char_val.i64 = (char_val.i64 << 8) | p_char_data_val[7];
            break;
            
            case HAP_DATA_TYPE_FLOAT:
                char_val.f = ((p_char_data_val[0] << 8) | p_char_data_val[1]) + int_change_fraction((p_char_data_val[2] << 8) | p_char_data_val[3]);
            break;
            
            case HAP_DATA_TYPE_STRING:
                char_val.s = (i8 *)malloc(char_val_len + 1);
                if(NULL == char_val.s) {
                    //malloc 错误
                    break;
                }
                memset(char_val.s, 0, char_val_len + 1);
                my_memcpy(char_val.s, p_char_data_val, char_val_len + 1);
            break;
            
            case HAP_DATA_TYPE_RAW:
                char_val.d.buf = (u8 *)malloc(char_val_len);
                if(NULL == char_val.s) {
                    //malloc 错误
                    break;
                }
                memset(char_val.d.buf, 0, char_val_len);
                my_memcpy(char_val.d.buf, p_char_data_val, char_val_len);
            break;

            default:break;
        }
        
        ret = homekit_character_ctrl(serv_serial, char_str, char_data_type, char_val_len, &char_val);
        if(SUCCESS == ret) {
            //成功提示
        }else {
            //错误提示
        }
        
        if(HAP_DATA_TYPE_STRING == char_data_type) {
            free(char_val.s);
        }
        if(HAP_DATA_TYPE_RAW == char_data_type) {
            free(char_val.d.buf);
        }

        offset += (5 + char_str_len + char_val_len);
    }
}


/**
 * @brief  HomeKit相关功能处理
 * @param[in] {p_data} 串口数据
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   
 */
void homekit_function(u8 p_data[], u16 data_len)
{
    switch(p_data[0]) { //子命令
        case HK_SUB_CMD_CFG_QUERY:
        case HK_SUB_CMD_SERVICE_CFG:
        case HK_SUB_CMD_CHARACTER_CFG:
            homekit_service_cfg(p_data, data_len);
        break;
        case HK_SUB_CMD_CTRL_ISSUE:
            homekit_character_parse(p_data, data_len);
        break;
#ifdef HOMEKIT_CHARACTER_VALID_CFG_ENABLE
        case HK_SUB_CMD_CHARACTER_VALID_CFG:
            if(0 != p_data[1]) {
                //可选特性配置失败，可在此添加失败提示和处理代码
                
            }
            
            char_valid_value_cfg(); //HomeKit特性有效值配置
        break;
#endif

        default:break;
    }
}



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
u8 homekit_character_ctrl(u8 serv_serial, i8 p_char_str[], u8 char_data_type, u16 char_val_len, HAP_VALUE_T *p_char_val)
{
    #error "请自行完成 homekit 命令下发处理代码,并删除该行"
    
    u8 serv_i = 0, char_j = 0;
    
    for(serv_i = 0; serv_i < CNTSOF(homekit_service); serv_i++) {
        if(serv_serial == homekit_service[serv_i].serial) {
            for(char_j = 0; char_j < homekit_service[serv_i].character_amount; char_j++) {
                if(0 == my_strcmp(p_char_str, homekit_service[serv_i].p_character_arr[char_j].p_character_str)) {
                    if(char_data_type == homekit_service[serv_i].p_character_arr[char_j].hap_val_type) {

                        //请在此添加特性下发命令处理代码
                        //homekit_service[serv_i].p_service_str:服务
                        //homekit_service[serv_i].p_character_arr[char_j].p_character_str:特性
                        //char_data_type:数据类型
                        //char_val_len:数据长度
                        //p_char_val:数据
                        
                        
                        
                        //可在此添加状态上报。例如：
                        //homekit_character_upload(serv_serial, homekit_service[serv_i].p_character_arr[char_j].p_character_str, char_data_type, char_val_len, p_char_val);
                        return SUCCESS;
                    }
                }
            }
            return ERROR;
        }
    }
    return ERROR;
}

/**
 * @brief  HomeKit特性状态上报
 * @param[in] {serv_serial} 服务序号
 * @param[in] {p_char_str} 特性字符串标识
 * @param[in] {char_data_type} 特性数据类型
 * @param[in] {char_val_len} 特性数据长度
 * @param[in] {p_char_val} 特性数据
 * @return SUCCESS/ERROR
 * @note   用户可自行调用
 */
u8 homekit_character_upload(u8 serv_serial, i8 p_char_str[], u8 char_data_type, u16 char_val_len, HAP_VALUE_T *p_char_val)
{
    u8 serv_i = 0, char_j = 0;
    u16 send_len = 0;
    
    for(serv_i = 0; serv_i < CNTSOF(homekit_service); serv_i++) {
        if(serv_serial == homekit_service[serv_i].serial) {
            for(char_j = 0; char_j < homekit_service[serv_i].character_amount; char_j++) {
                if(0 == my_strcmp(p_char_str, homekit_service[serv_i].p_character_arr[char_j].p_character_str)) {
                    if(char_data_type == homekit_service[serv_i].p_character_arr[char_j].hap_val_type) {
                        send_len = 0;
                        send_len = set_wifi_uart_byte(send_len, HK_SUB_CMD_START_UPLOAD);
                        send_len = set_wifi_uart_byte(send_len, serv_serial);
                        send_len = set_wifi_uart_byte(send_len, my_strlen(homekit_service[serv_i].p_character_arr[char_j].p_character_str));
                        send_len = set_wifi_uart_buffer(send_len, homekit_service[serv_i].p_character_arr[char_j].p_character_str, my_strlen(homekit_service[serv_i].p_character_arr[char_j].p_character_str));
                        send_len = set_wifi_uart_byte(send_len, char_data_type);
                        send_len = set_wifi_uart_byte(send_len, (char_val_len >> 8) & 0xff);
                        send_len = set_wifi_uart_byte(send_len, char_val_len & 0xff);
                        
                        switch(char_data_type) {
                            case HAP_DATA_TYPE_BOOL: {
                                send_len = set_wifi_uart_byte(send_len, p_char_val->b);
                            }
                            break;

                            case HAP_DATA_TYPE_UINT: {
                                send_len = set_wifi_uart_byte(send_len, (p_char_val->u >> 24) & 0xff);
                                send_len = set_wifi_uart_byte(send_len, (p_char_val->u >> 16) & 0xff);
                                send_len = set_wifi_uart_byte(send_len, (p_char_val->u >> 8) & 0xff);
                                send_len = set_wifi_uart_byte(send_len, p_char_val->u & 0xff);
                            }
                            break;

                            case HAP_DATA_TYPE_INT: {
                                send_len = set_wifi_uart_byte(send_len, (p_char_val->i >> 24) & 0xff);
                                send_len = set_wifi_uart_byte(send_len, (p_char_val->i >> 16) & 0xff);
                                send_len = set_wifi_uart_byte(send_len, (p_char_val->i >> 8) & 0xff);
                                send_len = set_wifi_uart_byte(send_len, p_char_val->i & 0xff);

                            }
                            break;

                            case HAP_DATA_TYPE_UINT64: {
                                send_len = set_wifi_uart_byte(send_len, (p_char_val->i64 >> 56) & 0xff);
                                send_len = set_wifi_uart_byte(send_len, (p_char_val->i64 >> 48) & 0xff);
                                send_len = set_wifi_uart_byte(send_len, (p_char_val->i64 >> 40) & 0xff);
                                send_len = set_wifi_uart_byte(send_len, (p_char_val->i64 >> 32) & 0xff);
                                send_len = set_wifi_uart_byte(send_len, (p_char_val->i64 >> 24) & 0xff);
                                send_len = set_wifi_uart_byte(send_len, (p_char_val->i64 >> 16) & 0xff);
                                send_len = set_wifi_uart_byte(send_len, (p_char_val->i64 >> 8) & 0xff);
                                send_len = set_wifi_uart_byte(send_len, p_char_val->i64 & 0xff);
                            }
                            break;

                            case HAP_DATA_TYPE_FLOAT: {
                                u16 float_val_integer = 0, float_val_fraction = 0;
                                float_val_integer = (u16)p_char_val->f;
                                float_val_fraction = fractional_part_change_int(p_char_val->f); //小数部分转换成整数
                                
                                send_len = set_wifi_uart_byte(send_len, (float_val_integer >> 8) & 0xff);
                                send_len = set_wifi_uart_byte(send_len, float_val_integer & 0xff);
                                send_len = set_wifi_uart_byte(send_len, (float_val_fraction >> 8) & 0xff);
                                send_len = set_wifi_uart_byte(send_len, float_val_fraction & 0xff);
                            }
                            break;

                            case HAP_DATA_TYPE_STRING: {
                                send_len = set_wifi_uart_buffer(send_len, p_char_val->s, my_strlen(p_char_val->s));
                            }
                            break;

                            case HAP_DATA_TYPE_RAW: {
                                send_len = set_wifi_uart_buffer(send_len, p_char_val->d.buf, p_char_val->d.buflen);
                            }
                            break;

                            default:
                                return ERROR;
                            break;
                        }
                        
                        wifi_uart_write_frame(HOMEKIT_FUN_CMD, MCU_TX_VER, send_len);
                        
                        return SUCCESS;
                    }
                }
            }
            return ERROR;
        }
    }
    return ERROR;
}

/**
 * @brief  HomeKit特性上报所有状态
 * @param[in] Null
 * @return Null
 * @note   
 */
void homekit_character_upload_all(void)
{
    u8 serv_i = 0, char_j = 0;
    u8 data_len = 0;
    
    for(serv_i = 0; serv_i < CNTSOF(homekit_service); serv_i++) {
        for(char_j = 0; char_j < homekit_service[serv_i].character_amount; char_j++) {
            switch(homekit_service[serv_i].p_character_arr[char_j].hap_val_type) {
                case HAP_DATA_TYPE_BOOL: {
                    data_len = 1;
                }
                break;

                case HAP_DATA_TYPE_UINT: {
                    data_len = 4;
                }
                break;

                case HAP_DATA_TYPE_INT: {
                    data_len = 4;
                }
                break;

                case HAP_DATA_TYPE_UINT64: {
                    data_len = 8;
                }
                break;

                case HAP_DATA_TYPE_FLOAT: {
                    data_len = 4;
                }
                break;

                case HAP_DATA_TYPE_STRING: {
                    data_len = my_strlen(homekit_service[serv_i].p_character_arr[char_j].hap_val.s);
                }
                break;

                case HAP_DATA_TYPE_RAW: {
                    data_len = homekit_service[serv_i].p_character_arr[char_j].hap_val.d.buflen;
                }
                break;

                default:
                    return;
                break;
            }
            homekit_character_upload(homekit_service[serv_i].serial, homekit_service[serv_i].p_character_arr[char_j].p_character_str, homekit_service[serv_i].p_character_arr[char_j].hap_val_type, 
                                        data_len, &homekit_service[serv_i].p_character_arr[char_j].hap_val);
        }
    }
}
#endif

