
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
// //  * @Description: �ӻ�ָ�����
// //  * @param: ���ݰ�Դָ��
// //  * @param: ���ݰ�����
// //  * @return: ��
// //  */
// // void slave_command_parse(uint8_t *p, uint16_t len)
// // {
// //     switch (((large_package_Typedef *)p)->head.cmd)
// //     {
// //     case CMD_SLAVE_PLAY_RGB: // ���ŵƹ� ��RGBbr����ʽ
// //         Fun_SLAVE_PLAY_RGB(p, len);
// //         break;
// //     case CMD_SLAVE_PLAY_RGBW: // ���ŵƹ�  ��RGBWbr����ʽ
// //         Fun_SLAVE_PLAY_RGBW(p, len);
// //         break;
// //     case CMD_SLAVE_PLAY_PWM: // ���ŵƹ� ��PWM����ʽ
// //         Fun_SLAVE_PLAY_PWM(p, len);
// //         break;
// //     case CMD_SLAVE_CONNECT_COID: // ����ͨ��ID
// //         Fun_SLAVE_CONNECT_COID(p, len);
// //         break;
// //     case CMD_SLAVE_REFRESH_COID: // ����ͨ��ID
// //         Fun_SLAVE_REFRESH_COID(p, len);
// //         break;
// //     case CMD_SLAVE_RESET_COID: // �ָ�ͨ��ID
// //         Fun_SLAVE_RESET_COID(p, len);
// //         break;
// //     case CMD_SLAVE_SET_COID: // ����ͨ��ID
// //         Fun_SLAVE_SET_COID(p, len);
// //         break;
// //     case CMD_SLAVE_GET_ID: // ��ȡID
// //         Fun_SLAVE_GET_ID(p, len);
// //         break;
// //     case CMD_SLAVE_GET_SHAPE: // ��ȡ��״
// //         Fun_SLAVE_GET_SHAPE(p, len);
// //         break;
// //     case CMD_SLAVE_GET_CALIBRATION: // ��ȡУ׼����
// //         Fun_SLAVE_GET_CALIBRATION(p, len);
// //         break;
// //     case CMD_SLAVE_SET_CALIBRATION: // ����У׼����
// //         Fun_SLAVE_SET_CALIBRATION(p, len);
// //         break;
// //     default:
// //         break;
// //     }
// // }

// // void Fun_SLAVE_PLAY_RGB(uint8_t *p, uint16_t len) // ���ŵƹ� ��RGBbr����ʽ
// // {
// // #define xPlay ((L0_cmd_playRGBbr_Typedef *)p)
// //     uint8_t i;
// //     L0_playRGBbr_Typedef *px;
// //     RGBbr_Typedef RGBbr;
// //     px = (L0_playRGBbr_Typedef *)&(xPlay->dev);
// //     if (xPlay->head.type == MES_ASK) // ��������
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
// // void Fun_SLAVE_PLAY_RGBW(uint8_t *p, uint16_t len) // ���ŵƹ� ��RGBWbr����ʽ
// // {
// // #define xPlay ((L0_cmd_playRGBWbr_Typedef *)p)
// //     uint8_t i;
// //     L0_playRGBWbr_Typedef *px;
// //     RGBWbr_Typedef RGBWbr;
// //     px = (L0_playRGBWbr_Typedef *)&(xPlay->dev);
// //     if (xPlay->head.type == MES_ASK) // ��������
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
// // void Fun_SLAVE_PLAY_PWM(uint8_t *p, uint16_t len) // ���ŵƹ� ��PWM����ʽ
// // {
// // #define xPlay ((L0_cmd_playPWM_Typedef *)p)
// //     uint8_t i;
// //     L0_playPWM_Typedef *px;
// //     px = (L0_playPWM_Typedef *)&(xPlay->dev);
// //     if (xPlay->head.type == MES_ASK) // ��������
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

// // void Fun_SLAVE_CONNECT_COID(uint8_t *p, uint16_t len) // ����ͨ��ID
// // {
// // #define xID ((L0_cmd_id_data_Typedef *)p)
// //     L0_cmd_id_data_Typedef x;
// //     if (xID->cid == userdata.cid && xID->head.type == MES_ASK) // ������������
// //     {
// //         x.head.dev_adr = ADDR_MASTER;        // ������ַ
// //         x.head.cmd = CMD_SLAVE_CONNECT_COID; // ����ͨ��ID
// //         x.head.type = MES_ACK;               // Ӧ������
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
// // void Fun_SLAVE_REFRESH_COID(uint8_t *p, uint16_t len) // ����ͨ��ID
// // {
// // #define xID ((L0_cmd_id_data_Typedef *)p)
// //     if (xID->head.type == MES_ASK) // ��������
// //     {
// //         refresh_cid_from_random(); // ����cid
// //     }
// //     else
// //     {
// //         return;
// //     }
// // #undef xID
// // }

// // void Fun_SLAVE_RESET_COID(uint8_t *p, uint16_t len) // �ָ�ͨ��ID
// // {
// // #define xID ((L0_cmd_id_data_Typedef *)p)
// //     if (xID->head.type == MES_ASK) // ��������
// //     {
// //         set_cid_from_uid();
// //     }
// //     else
// //     {
// //         return;
// //     }
// // #undef xID
// // }

// // void Fun_SLAVE_SET_COID(uint8_t *p, uint16_t len) // ����ͨ��ID
// // {
// // #define xID ((L0_cmd_id_data_Typedef *)p)
// //     if (xID->head.type == MES_ASK) // ��������
// //     {
// //         set_cid(xID->cid);
// //     }
// //     else
// //     {
// //         return;
// //     }
// // #undef xID
// // }

// // void Fun_SLAVE_GET_ID(uint8_t *p, uint16_t len) // ��ȡ�豸ID
// // {
// // #define xID ((L0_cmd_id_data_Typedef *)p)
// //     L0_cmd_id_data_Typedef x;
// //     if (xID->head.type == MES_ASK) // ��������
// //     {
// //         x.head.dev_adr = ADDR_MASTER;  // ������ַ
// //         x.head.cmd = CMD_SLAVE_GET_ID; // ��ȡID
// //         x.head.type = MES_ACK;         // Ӧ������
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

// // void Fun_SLAVE_GET_SHAPE(uint8_t *p, uint16_t len) // ��ȡ��״
// // {
// // #define xShape ((L0_cmd_shape_data_Typedef *)p)
// //     L0_cmd_shape_data_Typedef x;
// //     if (xShape->head.type == MES_ASK) // ��������
// //     {
// //         get_device_shape();
// //         x.head.dev_adr = ADDR_MASTER;                           // ������ַ
// //         x.head.cmd = CMD_SLAVE_GET_SHAPE;                       // ��ȡID
// //         x.head.type = MES_ACK;                                  // Ӧ������
// //         get_device_shape();                                     // ad����
// //         x.shape = userdata.shape;                               // ��ȡ��״
// //         my_memcpy(&x.adval, &dev_shape_adval, sizeof(x.adval)); // adֵ
// //         x.random[0] = get_random_number();
// //         x.random[1] = get_random_number();
// //         x.random[2] = get_random_number();
// //         transmit_protocol_frame((uint8_t *)&x, sizeof(x), parse.tx_framebuf);
// //     }
// // #undef xShape
// // }

// // void Fun_SLAVE_GET_CALIBRATION(uint8_t *p, uint16_t len) // ��ȡУ׼����
// // {
// // #define xCalibration ((L0_cmd_calibration_data_Typedef *)p)
// //     L0_cmd_calibration_data_Typedef x;
// //     if (xCalibration->head.type == MES_ASK) // ��������
// //     {
// //         x.head.dev_adr = ADDR_MASTER;                                     // ������ַ
// //         x.head.cmd = CMD_SLAVE_GET_CALIBRATION;                           // ��ȡУ׼����
// //         x.head.type = MES_ACK;                                            // Ӧ������
// //         my_memcpy(&x.gr_fine, &userdata.fine.gr_fine, sizeof(x.gr_fine)); // �̺�΢��
// //         my_memcpy(&x.gb_fine, &userdata.fine.gr_fine, sizeof(x.gb_fine)); // ����΢��
// //         my_memcpy(&x.gw_fine, &userdata.fine.gr_fine, sizeof(x.gw_fine)); // �̰�΢��
// //         my_memcpy(&x.br_fine, &userdata.fine.br_fine, sizeof(x.br_fine)); // ����΢��
// //         transmit_protocol_frame((uint8_t *)&x, sizeof(x), parse.tx_framebuf);
// //     }
// //     else
// //     {
// //         return;
// //     }
// // #undef xCalibration
// // }
// // void Fun_SLAVE_SET_CALIBRATION(uint8_t *p, uint16_t len) // ����У׼����
// // {
// // #define xCalibration ((L0_cmd_calibration_data_Typedef *)p)
// //     colorfine_Typedef fine;
// //     if (xCalibration->head.type == MES_ASK) // ��������
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
// //  * @Description: ͨ��ָ�����
// //  * @param: ���ݰ�Դָ��
// //  * @param: ���ݰ�����
// //  * @return: ��
// //  */
// // void general_command_parse(uint8_t *p, uint16_t len)
// // {
// //     switch (((large_package_Typedef *)p)->head.cmd)
// //     {
// //     case CMD_GENERAL_POWERTIME: // ��ȡ��������
// //         Fun_GENERAL_POWERTIME(p, len);
// //         break;
// //     default:
// //         break;
// //     }
// // }

// // void Fun_GENERAL_POWERTIME(uint8_t *p, uint16_t len) // ��ȡ��������
// // {
// // #define xPT ((L0_cmd_powertimes_Typedef *)p)
// //     L0_cmd_powertimes_Typedef x;
// //     if (xPT->head.type == MES_ASK) // ��������
// //     {
// //         get_device_shape();
// //         x.head.dev_adr = ADDR_MASTER;                                         // ������ַ
// //         x.head.cmd = CMD_GENERAL_POWERTIME;                                   // ��ȡ��������
// //         x.head.type = MES_ACK;                                                // Ӧ������
// //         my_memcpy(&x.powertimes, &userdata.powertimes, sizeof(x.powertimes)); // ��������
// //         x.random[0] = get_random_number();
// //         x.random[1] = get_random_number();
// //         x.random[2] = get_random_number();
// //         transmit_protocol_frame((uint8_t *)&x, sizeof(x), parse.tx_framebuf);
// //     }
// // #undef xPT
// // }
