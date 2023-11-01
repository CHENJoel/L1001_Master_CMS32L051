
/*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*-*/
// // /*
// //  * @Description: 从机指令解析
// //  * @param: 数据包源指针
// //  * @param: 数据包长度
// //  * @return: 无
// //  */
// // void slave_command_parse(uint8_t *p, uint16_t len)
// // {
// //     switch (((large_package_Typedef *)p)->head.cmd)
// //     {
// //     case CMD_SLAVE_PLAY_RGB: // 播放灯光 “RGBbr”格式
// //         Fun_SLAVE_PLAY_RGB(p, len);
// //         break;
// //     case CMD_SLAVE_PLAY_RGBW: // 播放灯光  “RGBWbr”格式
// //         Fun_SLAVE_PLAY_RGBW(p, len);
// //         break;
// //     case CMD_SLAVE_PLAY_PWM: // 播放灯光 “PWM”格式
// //         Fun_SLAVE_PLAY_PWM(p, len);
// //         break;
// //     case CMD_SLAVE_CONNECT_COID: // 握手通信ID
// //         Fun_SLAVE_CONNECT_COID(p, len);
// //         break;
// //     case CMD_SLAVE_REFRESH_COID: // 更新通信ID
// //         Fun_SLAVE_REFRESH_COID(p, len);
// //         break;
// //     case CMD_SLAVE_RESET_COID: // 恢复通信ID
// //         Fun_SLAVE_RESET_COID(p, len);
// //         break;
// //     case CMD_SLAVE_SET_COID: // 设置通信ID
// //         Fun_SLAVE_SET_COID(p, len);
// //         break;
// //     case CMD_SLAVE_GET_ID: // 获取ID
// //         Fun_SLAVE_GET_ID(p, len);
// //         break;
// //     case CMD_SLAVE_GET_SHAPE: // 获取形状
// //         Fun_SLAVE_GET_SHAPE(p, len);
// //         break;
// //     case CMD_SLAVE_GET_CALIBRATION: // 获取校准数据
// //         Fun_SLAVE_GET_CALIBRATION(p, len);
// //         break;
// //     case CMD_SLAVE_SET_CALIBRATION: // 设置校准数据
// //         Fun_SLAVE_SET_CALIBRATION(p, len);
// //         break;
// //     default:
// //         break;
// //     }
// // }

// // void Fun_SLAVE_PLAY_RGB(uint8_t *p, uint16_t len) // 播放灯光 “RGBbr”格式
// // {
// // #define xPlay ((L0_cmd_playRGBbr_Typedef *)p)
// //     uint8_t i;
// //     L0_playRGBbr_Typedef *px;
// //     RGBbr_Typedef RGBbr;
// //     px = (L0_playRGBbr_Typedef *)&(xPlay->dev);
// //     if (xPlay->head.type == MES_ASK) // 发出请求
// //     {
// //         if (xPlay->playnum > MAX_SLAVE_NUM)
// //         {
// //             return;
// //         }
// //         for (i = 0; i < xPlay->playnum; i++)
// //         {
// //             if (px->cid == userdata.cid || px->cid == ADDR_PUBLIC)
// //             {
// //                 RGBbr.R = px->R;
// //                 RGBbr.G = px->G;
// //                 RGBbr.B = px->B;
// //                 RGBbr.br = px->br;
// //                 RGBbr_to_PWM(&RGBbr);
// //                 pwm_drive();
// //                 return;
// //             }
// //             else
// //             {
// //             }
// //             px++;
// //         }
// //     }
// //     else
// //     {
// //         return;
// //     }
// // #undef xPlay
// // }
// // void Fun_SLAVE_PLAY_RGBW(uint8_t *p, uint16_t len) // 播放灯光 “RGBWbr”格式
// // {
// // #define xPlay ((L0_cmd_playRGBWbr_Typedef *)p)
// //     uint8_t i;
// //     L0_playRGBWbr_Typedef *px;
// //     RGBWbr_Typedef RGBWbr;
// //     px = (L0_playRGBWbr_Typedef *)&(xPlay->dev);
// //     if (xPlay->head.type == MES_ASK) // 发出请求
// //     {
// //         if (xPlay->playnum > MAX_SLAVE_NUM)
// //         {
// //             return;
// //         }
// //         for (i = 0; i < xPlay->playnum; i++)
// //         {
// //             if (px->cid == userdata.cid || px->cid == ADDR_PUBLIC)
// //             {
// //                 RGBWbr.R = px->R;
// //                 RGBWbr.G = px->G;
// //                 RGBWbr.B = px->B;
// //                 RGBWbr.W = px->W;
// //                 RGBWbr.br = px->br;
// //                 RGBWbr_to_PWM(&RGBWbr);
// //                 pwm_drive();
// //                 return;
// //             }
// //             else
// //             {
// //             }
// //             px++;
// //         }
// //     }
// //     else
// //     {
// //         return;
// //     }
// // #undef xPlay
// // }
// // void Fun_SLAVE_PLAY_PWM(uint8_t *p, uint16_t len) // 播放灯光 “PWM”格式
// // {
// // #define xPlay ((L0_cmd_playPWM_Typedef *)p)
// //     uint8_t i;
// //     L0_playPWM_Typedef *px;
// //     px = (L0_playPWM_Typedef *)&(xPlay->dev);
// //     if (xPlay->head.type == MES_ASK) // 发出请求
// //     {
// //         if (xPlay->playnum > MAX_SLAVE_NUM)
// //         {
// //             return;
// //         }
// //         for (i = 0; i < xPlay->playnum; i++)
// //         {
// //             if (px->cid == userdata.cid || px->cid == ADDR_PUBLIC)
// //             {
// //                 my_memcpy(&pwm_now.R, &px->pwmR, sizeof(pwm_now.R));
// //                 my_memcpy(&pwm_now.G, &px->pwmG, sizeof(pwm_now.G));
// //                 my_memcpy(&pwm_now.B, &px->pwmB, sizeof(pwm_now.B));
// //                 my_memcpy(&pwm_now.W, &px->pwmW, sizeof(pwm_now.W));
// //                 pwm_drive();
// //                 return;
// //             }
// //             else
// //             {
// //             }
// //             px++;
// //         }
// //     }
// //     else
// //     {
// //         return;
// //     }
// // #undef xPlay
// // }

// // void Fun_SLAVE_CONNECT_COID(uint8_t *p, uint16_t len) // 握手通信ID
// // {
// // #define xID ((L0_cmd_id_data_Typedef *)p)
// //     L0_cmd_id_data_Typedef x;
// //     if (xID->cid == userdata.cid && xID->head.type == MES_ASK) // 发出握手请求
// //     {
// //         x.head.dev_adr = ADDR_MASTER;        // 主机地址
// //         x.head.cmd = CMD_SLAVE_CONNECT_COID; // 握手通信ID
// //         x.head.type = MES_ACK;               // 应答请求
// //         x.cid = userdata.cid;
// //         x.uid = userdata.uid;
// //         x.random[0] = get_random_number();
// //         x.random[1] = get_random_number();
// //         x.random[2] = get_random_number();
// //         transmit_protocol_frame((uint8_t *)&x, sizeof(x), parse.tx_framebuf);
// //     }
// //     else
// //     {
// //         return;
// //     }
// // #undef xID
// // }
// // void Fun_SLAVE_REFRESH_COID(uint8_t *p, uint16_t len) // 更新通信ID
// // {
// // #define xID ((L0_cmd_id_data_Typedef *)p)
// //     if (xID->head.type == MES_ASK) // 发出请求
// //     {
// //         refresh_cid_from_random(); // 更新cid
// //     }
// //     else
// //     {
// //         return;
// //     }
// // #undef xID
// // }

// // void Fun_SLAVE_RESET_COID(uint8_t *p, uint16_t len) // 恢复通信ID
// // {
// // #define xID ((L0_cmd_id_data_Typedef *)p)
// //     if (xID->head.type == MES_ASK) // 发出请求
// //     {
// //         set_cid_from_uid();
// //     }
// //     else
// //     {
// //         return;
// //     }
// // #undef xID
// // }

// // void Fun_SLAVE_SET_COID(uint8_t *p, uint16_t len) // 设置通信ID
// // {
// // #define xID ((L0_cmd_id_data_Typedef *)p)
// //     if (xID->head.type == MES_ASK) // 发出请求
// //     {
// //         set_cid(xID->cid);
// //     }
// //     else
// //     {
// //         return;
// //     }
// // #undef xID
// // }

// // void Fun_SLAVE_GET_ID(uint8_t *p, uint16_t len) // 获取设备ID
// // {
// // #define xID ((L0_cmd_id_data_Typedef *)p)
// //     L0_cmd_id_data_Typedef x;
// //     if (xID->head.type == MES_ASK) // 发出请求
// //     {
// //         x.head.dev_adr = ADDR_MASTER;  // 主机地址
// //         x.head.cmd = CMD_SLAVE_GET_ID; // 获取ID
// //         x.head.type = MES_ACK;         // 应答请求
// //         x.cid = userdata.cid;
// //         x.uid = userdata.uid;
// //         x.random[0] = get_random_number();
// //         x.random[1] = get_random_number();
// //         x.random[2] = get_random_number();
// //         transmit_protocol_frame((uint8_t *)&x, sizeof(x), parse.tx_framebuf);
// //     }
// //     else
// //     {
// //         return;
// //     }
// // #undef xID
// // }

// // void Fun_SLAVE_GET_SHAPE(uint8_t *p, uint16_t len) // 获取形状
// // {
// // #define xShape ((L0_cmd_shape_data_Typedef *)p)
// //     L0_cmd_shape_data_Typedef x;
// //     if (xShape->head.type == MES_ASK) // 发出请求
// //     {
// //         get_device_shape();
// //         x.head.dev_adr = ADDR_MASTER;                           // 主机地址
// //         x.head.cmd = CMD_SLAVE_GET_SHAPE;                       // 获取ID
// //         x.head.type = MES_ACK;                                  // 应答请求
// //         get_device_shape();                                     // ad采样
// //         x.shape = userdata.shape;                               // 获取形状
// //         my_memcpy(&x.adval, &dev_shape_adval, sizeof(x.adval)); // ad值
// //         x.random[0] = get_random_number();
// //         x.random[1] = get_random_number();
// //         x.random[2] = get_random_number();
// //         transmit_protocol_frame((uint8_t *)&x, sizeof(x), parse.tx_framebuf);
// //     }
// // #undef xShape
// // }

// // void Fun_SLAVE_GET_CALIBRATION(uint8_t *p, uint16_t len) // 获取校准数据
// // {
// // #define xCalibration ((L0_cmd_calibration_data_Typedef *)p)
// //     L0_cmd_calibration_data_Typedef x;
// //     if (xCalibration->head.type == MES_ASK) // 发出请求
// //     {
// //         x.head.dev_adr = ADDR_MASTER;                                     // 主机地址
// //         x.head.cmd = CMD_SLAVE_GET_CALIBRATION;                           // 获取校准数据
// //         x.head.type = MES_ACK;                                            // 应答请求
// //         my_memcpy(&x.gr_fine, &userdata.fine.gr_fine, sizeof(x.gr_fine)); // 绿红微调
// //         my_memcpy(&x.gb_fine, &userdata.fine.gr_fine, sizeof(x.gb_fine)); // 绿蓝微调
// //         my_memcpy(&x.gw_fine, &userdata.fine.gr_fine, sizeof(x.gw_fine)); // 绿白微调
// //         my_memcpy(&x.br_fine, &userdata.fine.br_fine, sizeof(x.br_fine)); // 亮度微调
// //         transmit_protocol_frame((uint8_t *)&x, sizeof(x), parse.tx_framebuf);
// //     }
// //     else
// //     {
// //         return;
// //     }
// // #undef xCalibration
// // }
// // void Fun_SLAVE_SET_CALIBRATION(uint8_t *p, uint16_t len) // 设置校准数据
// // {
// // #define xCalibration ((L0_cmd_calibration_data_Typedef *)p)
// //     colorfine_Typedef fine;
// //     if (xCalibration->head.type == MES_ASK) // 发出请求
// //     {
// //         my_memcpy(&fine.gr_fine, &xCalibration->gr_fine, sizeof(xCalibration->gr_fine));
// //         my_memcpy(&fine.gb_fine, &xCalibration->gb_fine, sizeof(xCalibration->gb_fine));
// //         my_memcpy(&fine.gw_fine, &xCalibration->gw_fine, sizeof(xCalibration->gw_fine));
// //         my_memcpy(&fine.br_fine, &xCalibration->br_fine, sizeof(xCalibration->gw_fine));
// //         modify_colorfine(&fine);
// //         calibrate_init(&fine, &calib);
// //     }
// //     else
// //     {
// //         return;
// //     }
// // #undef xCalibration
// // }

// // /*
// //  * @Description: 通用指令解析
// //  * @param: 数据包源指针
// //  * @param: 数据包长度
// //  * @return: 无
// //  */
// // void general_command_parse(uint8_t *p, uint16_t len)
// // {
// //     switch (((large_package_Typedef *)p)->head.cmd)
// //     {
// //     case CMD_GENERAL_POWERTIME: // 获取开机次数
// //         Fun_GENERAL_POWERTIME(p, len);
// //         break;
// //     default:
// //         break;
// //     }
// // }

// // void Fun_GENERAL_POWERTIME(uint8_t *p, uint16_t len) // 获取开机次数
// // {
// // #define xPT ((L0_cmd_powertimes_Typedef *)p)
// //     L0_cmd_powertimes_Typedef x;
// //     if (xPT->head.type == MES_ASK) // 发出请求
// //     {
// //         get_device_shape();
// //         x.head.dev_adr = ADDR_MASTER;                                         // 主机地址
// //         x.head.cmd = CMD_GENERAL_POWERTIME;                                   // 获取开机次数
// //         x.head.type = MES_ACK;                                                // 应答请求
// //         my_memcpy(&x.powertimes, &userdata.powertimes, sizeof(x.powertimes)); // 开机次数
// //         x.random[0] = get_random_number();
// //         x.random[1] = get_random_number();
// //         x.random[2] = get_random_number();
// //         transmit_protocol_frame((uint8_t *)&x, sizeof(x), parse.tx_framebuf);
// //     }
// // #undef xPT
// // }
