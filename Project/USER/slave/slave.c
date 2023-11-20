/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-06-09 15:56:49
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om

 * .chen sandote@163.om
 * @LastEditTime: 2023-07-21 15:05:17
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\slave\slave.c
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#include "Function_Init.H"
#include "slave.h"
#include "ProtocolCom.H"

uint8_t connect_id; // ��ǰ����ID

device_data_TypeDef slave;
device_color_TypeDef slavecolor;    // �����ʱʹ��
device_control_TypeDef slave_control;

/*
 * @Description: ���ڷ������ݴ�
 * @param: Դ����ָ��
 * @param: ���ݳ���
 * @return: ��
*/
void tx_uart_data(uint8_t *data, uint16_t len)
{
    uint8_t i;
    for (i = 0; i < len; i++)
    {
        UART0_Send(data[i]);
    }
}

/*
 * @Description: �������Ӵӻ��豸
 * @param: �ӻ�id
 * @return: ��
*/
void connect_slave_device(uint8_t id)
{
    L0_cmd_id_data_Typedef x;
    x.head.dev_adr = id;                 // ���ֵ�ַ
    x.head.cmd = CMD_SLAVE_CONNECT_COID; // ����ͨ��ID
    x.head.type = MES_ASK;               // ��������
    x.cid = id;
    transmit_protocol_frame((uint8_t *)&x, &((L0_cmd_id_data_Typedef *)1)->cid, parse.tx_framebuf);

    /************************/
    // comCmd_Typedef com;
    // com.com_head = MCMD_HEADER;
    // com.com_addr = id;
    // com.com_cmdType = CMD_CONTROL;  // ����ָ��
    // com.com_cmd = CMD_CONNECT_COID; // ����ͨ��ID
    // com.com_val1 = get_random_number();
    // com.com_val2 = get_random_number();
    // com.com_checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    // tx_uart_data((uint8_t *)&com, (uint16_t)sizeof(com));
}

/*
 * @Description: Ҫ��������дӻ���ͨѶid
 * @param: �ӻ�id
 * @return: ��
*/
void refresh_slave_comid(void)
{
    L0_cmd_id_data_Typedef x;
    x.head.dev_adr = ADDR_PUBLIC;        // ���ֵ�ַ
    x.head.cmd = CMD_SLAVE_REFRESH_COID; // ����ͨ��ID
    x.head.type = MES_ASK;               // ��������
    transmit_protocol_frame((uint8_t *)&x, &((L0_cmd_id_data_Typedef *)1)->head.type, parse.tx_framebuf);
    /************************/
    // // // comCmd_Typedef com;
    // // // com.com_head = MCMD_HEADER;
    // // // com.com_addr = 0xFF;            // �㲥
    // // // com.com_cmdType = CMD_CONTROL;  // ����ָ��
    // // // com.com_cmd = CMD_REFRESH_COID; // ����ͨ��ID
    // // // com.com_val1 = get_random_number();
    // // // com.com_val2 = get_random_number();
    // // // com.com_checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    // // // tx_uart_data((uint8_t *)&com, (uint16_t)sizeof(com));
}

/*
 * @Description: ����ӻ�����״��Ϣ
 * @param: �ӻ�id
 * @return: ��
*/
void ask_slave_shape(uint8_t id)
{
    L0_cmd_shape_data_Typedef x;
    x.head.dev_adr = id;              // ���ֵ�ַ
    x.head.cmd = CMD_SLAVE_GET_SHAPE; // ��ȡ�豸��״
    x.head.type = MES_ASK;            // ��������
    transmit_protocol_frame((uint8_t *)&x, &((L0_cmd_id_data_Typedef *)1)->head.type, parse.tx_framebuf);
    /*****************************/
    // // // comRW_Typedef com;
    // // // com.com_head = MCMD_HEADER;
    // // // com.com_addr = id;
    // // // com.com_cmdType = CMD_READREG;
    // // // com.com_regaddr = REG_DEVICETYPE; // �豸����
    // // // com.com_regval = get_random_number() << 8;
    // // // com.com_regval += get_random_number();
    // // // com.com_checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    // // // tx_uart_data((uint8_t *)&com, (uint16_t)sizeof(com));
}

/*
 * @Description: ��fifo�������ӻ���Ӧ���ź�
 * @param: fifo����ָ��
 * @param: fifo�����С
 * @param: fifo��ָ���ָ��
 * @param: fifoдָ���ָ��
 * @param: Ӧ�������ָ��
 * @return: Ӧ���״̬
 */
cmdpack_status get_slave_ack_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t *pw, comCmd_Typedef *pack)
{
    uint16_t i;
    for (i = 0; i < 1000; i++) // ���Ƶ��ν�������
    {
        if (*pr != *pw) // δ���껺��
        {
            if (SCMD_HEADER == get_byte_from_fifo(fifobuf, bufsize, pr, 7)) // ֡ͷУ�飨�ӻ����ݰ���
            {
                get_section_from_fifo(fifobuf, bufsize, pr, 0, pack, sizeof(comCmd_Typedef));
                if (pack->com_checksum == (uint8_t)checksum_calculate((uint8_t *)pack, (uint16_t)sizeof(comCmd_Typedef) - 1))
                {
                    return PACK_RIGHT; // У��ͨ����fifo���ڴӻ����ص�ָ��Ӧ���
                }
            }
            if (++*pr >= bufsize) // ָ����һλ
            {
                *pr = 0;
            }
        }
        else // �����޴�������
        {
            if (i == 0)
            {
                return PACK_EMPTY; // �����д��ַһ�£�����������������
            }
            return PACK_WRONG; // ���껺��������ݣ���δ���ַ���Э������ݰ�
        }
    }
    return PACK_WRONG; //
}


/**----------------------------------------------------*/
/*
 * @Description: �����ӻ���Ӧ���ź�
 * @param: fifo����ָ��
 * @param: fifo�����С
 * @param: fifo��ָ���ָ��
 * @param: fifoдָ���ָ��
 * @param: ����������ݴ洢����ָ��
 * @return:��
 */
answer_status parse_slave_answer(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t *pw, uint8_t *processbuf)
{
    uint16_t i;
    uint16_t datalength;       // ���ݶγ���
    uint8_t datasum;           // ���ݶε��ۼӺ�
    for (i = 0; i < 1000; i++) // ���Ƶ��ν�������
    {
        if (*pr != *pw) // δ���껺��
        {
            if (FRAME_TAIL == get_byte_from_fifo(fifobuf, bufsize, pr, FRAME_TAIL_OFFSET)) // ֡βУ��
            {
                datalength = get_byte_from_fifo(fifobuf, bufsize, pr, DATA_LENGTH_H_OFFSET) << 8; // ���ݳ��ȸ߰�λ
                datalength |= get_byte_from_fifo(fifobuf, bufsize, pr, DATA_LENGTH_L_OFFSET);     // ���ݳ��ȵͰ�λ
                if (datalength < PROCESS_RXDATA_LMT)                                              // �������ݶγ���
                {
                    if (FRAME_HEAD == get_byte_from_fifo(fifobuf, bufsize, pr, datalength + DATA_END_OFFSET)) // ֡ͷУ��
                    {
                        get_section_from_fifo(fifobuf, bufsize, pr, DATA_END_OFFSET, processbuf, datalength); // ��ȡ���ݶε���������
                        datasum = get_data_checksum(processbuf, datalength);                                  // �������ۼӺ�
                        datasum += FRAME_HEAD;                                                                // �ۼ�֡ͷ
                        datasum += (datalength >> 8);                                                         // �ۼ����ݳ��ȸ߰�λ
                        datasum += datalength;                                                                // �ۼ����ݳ��ȵͰ�λ
                        if (datasum == get_byte_from_fifo(fifobuf, bufsize, pr, CHECK_SUM_OFFSET))            // У���
                        {
                            protocol_rxdata_handle(processbuf, datalength); // ��������������
                            return ANSWER_RIGHT;    // ��ȷӦ��
                        }
                    }
                }
            }
            if (++*pr >= bufsize) // ָ����һλ
            {
                *pr = 0;
            }
        }
        else // �����޴�������
        {
            if (i == 0)
            {
                return ANSWER_EMPTY; // ��Ӧ�� �����д��ַһ�£�����������������
            }
            return ANSWER_WRONG; // ����Ӧ�� ���껺��������ݣ���δ���ַ���Э������ݰ�
        }
    }
    return ANSWER_WRONG; //
}

/*
 * @Description: ��ѯ�����ߵĴӻ��豸
 * @param: ��
 * @return: ��
*/
void poll_slave_id(void)
{
    uint16_t pWrite; //
    answer_status answer_sta;
    uint8_t i, j;
    uint8_t id_buff[32];      // �豸id
    uint8_t online_num = 0;   // �����豸����
    uint8_t packstatus;       // ָ�����ݰ�״̬
    comCmd_Typedef packbuff;
    memset(&slave, 0, sizeof(slave)); // ���ԭ��Ϣ
    memset(&id_buff, 0, sizeof(id_buff)); //
    for (i = 0; i <= 50; i++)  // ���ִ��256�γ�ͻ����
    {
        online_num = 0;
        for (j = 1; j < 255; j++) // ��ѯ����id��0��255���㲥��Ϊ��Чid
         {
            // Uart0_Buffer.Read = Uart0_Buffer.Write; // ��ս��ջ�����δ������
            // // memset(&packbuff, 0, sizeof(packbuff)); //
            // // packstatus = get_slave_ack_from_fifo(&Uart0_Buffer.Buffer, sizeof(Uart0_Buffer.Buffer), &Uart0_Buffer.Read, &Uart0_Buffer.Write, &packbuff); // ��ȡ��������״̬
            // // if ((packstatus == PACK_RIGHT) && (packbuff.com_addr == j) && (packbuff.com_cmdType == CMD_CTRLACK) && (packbuff.com_cmd == CMD_CONNECT_COID)) // ���յ�һ��ӻ���Ϣ���ݰ�
            // // {
            // //     id_buff[online_num] = j;                 // ��Ǵӻ�ID
            // //     online_num++;                               // ��Ǵӻ�����
            // // }
            // // else if (packstatus != PACK_EMPTY) // �ǿ����ݰ�,������������Э�飬���ݰ����󣬴����ж���ӻ�ͬʱռ�����߷������ݣ�������ID��ͻ
            // // {
            // //     // refresh_slave_comid(); // Ҫ��ȫ���ӻ�����id
            // //     delay_5ms();
            // //     break;               // ����ѭ����ѯ
            // // }
            pWrite = sizeof(parse.fifo_buffer) - DMAVEC->CTRL[CTRL_DATA_SR0].DMACT;
            parse.read = pWrite; // ���buffδ���������
            connect_id = 0; // ��λ����
            connect_slave_device(j); // �������Ӵ�id
            delay_10ms();
            delay_10ms();
            pWrite = sizeof(parse.fifo_buffer) - DMAVEC->CTRL[CTRL_DATA_SR0].DMACT;
            answer_sta = parse_slave_answer(&parse.fifo_buffer, sizeof(parse.fifo_buffer), &parse.read, &pWrite, &parse.rx_processbuf); //
            if (answer_sta == ANSWER_RIGHT)
            {
                if (connect_id == j)
                {
                    id_buff[online_num] = j; // ��Ǵӻ�ID
                    online_num++;            // ��Ǵӻ�����
                }
            }
            else if (answer_sta == ANSWER_WRONG) // Ӧ���쳣�����ܳ���id��ͻ
            {
                refresh_slave_comid(); // Ҫ��ȫ���ӻ�����id
                // delay_5ms();
                delay_10ms();
                break; // ����ѭ����ѯ
            }
            if (j == 254) // ��ѭ����ѯ������˵����ǰδ����ID��ͻ
            {
                slave.num = online_num; // �洢�����豸����
                for (i = 0; i < online_num; i++)
                {
                    slave.data[i].id = id_buff[i]; // �洢�豸id
                }
                return ;
            }
        }
    }
}

/*
 * @Description: ��ȡ�ӻ�����״��Ϣ
 * @param: ��
 * @return: ��
 */
void get_slave_shape(void)
{
    uint8_t i;
    uint16_t pWrite; //
    answer_status answer_sta;
    if (slave.num>32)
    {
        return ; 
    }
    for (i = 0; i < slave.num; i++)
    {
        pWrite = sizeof(parse.fifo_buffer) - DMAVEC->CTRL[CTRL_DATA_SR0].DMACT;
        parse.read = pWrite; // ���buffδ���������
        slave.data[i].shape = OTHER_SHAPE;
        ask_slave_shape(slave.data[i].id);
        delay_10ms();
        delay_10ms();
        delay_10ms();
        pWrite = sizeof(parse.fifo_buffer) - DMAVEC->CTRL[CTRL_DATA_SR0].DMACT;
        answer_sta = parse_slave_answer(&parse.fifo_buffer, sizeof(parse.fifo_buffer), &parse.read, &pWrite, &parse.rx_processbuf); //
    }

    /***************************************/
    // // // // uint8_t i;
    // // // // uint8_t packstatus; // ָ�����ݰ�״̬
    // // // // comRW_Typedef packbuff;
    // // // // for (i = 0; i < slave.num; i++)
    // // // // {
    // // // //     Uart0_Buffer.Read = Uart0_Buffer.Write; // ��ս��ջ�����δ������
    // // // //     ask_slave_shape(slave.data[i].id);
    // // // //     delay_5ms();
    // // // //     packstatus = get_slave_ack_from_fifo(&Uart0_Buffer.Buffer, sizeof(Uart0_Buffer.Buffer), &Uart0_Buffer.Read, &Uart0_Buffer.Write, &packbuff);       // ��ȡ��������״̬
    // // // //     if ((packstatus == PACK_RIGHT) && (packbuff.com_addr == slave.data[i].id) && (packbuff.com_cmdType == CMD_RETURNREG) && (packbuff.com_regaddr == REG_DEVICETYPE)) // ���յ�һ��ӻ���Ϣ���ݰ�
    // // // //     {
    // // // //         slave.data[i].shape = packbuff.com_regval;
    // // // //     }
    // // // //     else
    // // // //     {
    // // // //         slave.data[i].shape = OTHER_SHAPE;
    // // // //     }
    // // // // }
}
/*�����豸��Ϣ*/
uint8_t refresh_slave_data(device_detail_TypeDef *p)
{
    uint8_t i;
    for (i = 0; i < SLAVEDEVICE_NUM; i++)
    {
        if (p->id == slave.data[i].id) // ��ѯ����Ҫ���޸ĵ��豸id
        {
            slave.data[i].angle = p->angle;
            slave.data[i].cooed_x = p->cooed_x;
            slave.data[i].cooed_y = p->cooed_y;
            printlog("refresh device data :[%02x]\r", p->id);
            return 1;
        }
    }
    printlog("[error] This device id do not exist :[%02x]\r", p->id);
    printAssert();
    return 0;
}

/*
 * @Description: ��flash�л�ȡ�ӻ�λ����Ϣ
 * @param: ��
 * @return: ��
*/
void get_slave_place(void)
{
    uint8_t i, j;
    device_data_TypeDef device;
    memset(&device, 0, sizeof(device));
    get_all_slave_data(&device);
    if (device.num > SLAVEDEVICE_NUM)
    {
        printlog("\r[error] wrong device number:%d\r",device.num);
        return;
    }
    for (i = 0; i < slave.num; i++)
    {
        for (j = 0; j < device.num; j++)
        {
            if (slave.data[i].id == device.data[j].id)
            {
                slave.data[i].angle = device.data[j].angle;
                slave.data[i].cooed_x = device.data[j].cooed_x;
                slave.data[i].cooed_y = device.data[j].cooed_y;
            }
        }
    }
}

/*
 * @Description: ��ʼ�����ߵĴӻ���Ϣ
 * @param: ��
 * @return: ��
 */
void slave_online_data_init(void)
{

    // // #ifdef virtual_device
    // //     generate_virtual_device(); // ��������ư���Ϣ
    // // #else
    turn_off_all_salve_light();
    poll_slave_id();           // ��ѯID��Ϣ
    get_slave_shape();         // ��ȡ�ư���״
    generate_virtual_device(); // ��������ư���Ϣ
                               // #endif

    get_slave_place();
    slave_light_in_turn();
    turn_off_all_salve_light();
    print_online_slave_data();
}

/*��������ư���Ϣ*/
void generate_virtual_device(void)
{
    // // uint8_t temp[32];
    // // uint8_t i;
    // // // // memset(&slave, 0, sizeof(slave));
    // // // // slave.num=8;
    // // for ( i = 0; i < 32; i++)
    // // {
    // //     temp[i] = (i + 1) * 10 + i + 1;
    // //     // while (temp[i]==0||temp[i]==255)
    // //     // {
    // //     //     // temp[i] = get_random_number();
    // //     //     temp[i] = (i+1)*10+i+1;
    // //     //     // printlog("%d get_random_number %d\r",i,temp[i]);
    // //     // }
    // // }
    if (slave.num)  // û�����ӵư��ʱ�򣬾�����8������ư���Ϣ
    {
        return;
    }   
    printf("\r----------------------------------------------------------------\r");
    printf("generate_virtual_device \r");
    printf("\r----------------------------------------------------------------\r");
    slave.num = 8;
    slave.data[0].id = 0x11;
    slave.data[0].shape = TRIANGLE_L;
    slave.data[0].angle = 0;
    slave.data[0].cooed_x = 1;
    slave.data[0].cooed_y = 1;
    /**************************/
    slave.data[1].id = 0x22;
    slave.data[1].shape = TRIANGLE_L;
    slave.data[1].angle = 0;
    slave.data[1].cooed_x = 2;
    slave.data[1].cooed_y = 2;
    /**************************/
    slave.data[2].id = 0x33;
    slave.data[2].shape = TRIANGLE_M;
    slave.data[2].angle = 0;
    slave.data[2].cooed_x = 3;
    slave.data[2].cooed_y = 3;
    /**************************/
    slave.data[3].id =0x44;
    slave.data[3].shape = TRIANGLE_S;
    slave.data[3].angle = 0;
    slave.data[3].cooed_x = 4;
    slave.data[3].cooed_y = 4;
    /**************************/
    slave.data[4].id = 0x55;
    slave.data[4].shape = SQUARE;
    slave.data[4].angle = 0;
    slave.data[4].cooed_x = 5;
    slave.data[4].cooed_y = 5;
    /**************************/
    slave.data[5].id = 0x66;
    slave.data[5].shape = TRIANGLE_S;
    slave.data[5].angle = 0;
    slave.data[5].cooed_x = 6;
    slave.data[5].cooed_y = 6;
    /**************************/
    slave.data[6].id =0x77;
    slave.data[6].shape = TRIANGLE_S;
    slave.data[6].angle = 0;
    slave.data[6].cooed_x = 7;
    slave.data[6].cooed_y = 7;
    /**************************/
    slave.data[7].id =0x88;
    slave.data[7].shape = TRIANGLE_S;
    slave.data[7].angle = 0;
    slave.data[7].cooed_x = 8;
    slave.data[7].cooed_y = 8;
    /**************************/
}


/*�����豸��ɫ*/
uint8_t refresh_device_color(color_TypeDef *p, uint8_t id)
{
    uint8_t i;
    for (i = 0; i < SLAVEDEVICE_NUM; i++)
    {
        if (id == slave.data[i].id) // ��ѯ����Ҫ���޸ĵ��豸id
        {
            slavecolor.color[i].brightness = p->brightness;
            slavecolor.color[i].R = p->R;
            slavecolor.color[i].G = p->G;
            slavecolor.color[i].B = p->B;
            slavecolor.color[i].W = p->W;
            printlog("refresh device color :[%02x]\r", id);
            return 1;
        }
    }
    printlog("[error] This device id do not exist :[%02x]\r", id);
    printAssert();
    return 0;
}

/*
 * @Description: ���������ӻ�
 * @param:
 * @return:
 */
void slave_light_in_turn(void)
{
    uint8_t i, j;
    L0_cmd_playRGBbr_Typedef xPlay;
    if (slave.num) // ���豸���ߵ�ʱ��ŷ�������
    {
        xPlay.head.dev_adr = ADDR_PUBLIC;    // �豸��ַ
        xPlay.head.cmd = CMD_SLAVE_PLAY_RGB; // ���ŵƹ� ��RGBbr����ʽ
        xPlay.head.type = MES_ASK;           // ��������
        xPlay.playnum = slave.num;
        for (i = 0; i < xPlay.playnum + 1; i++)
        {
            for (j = 0; j < xPlay.playnum; j++)
            {
                if (j == i)
                {
                    xPlay.dev[j].cid = slave.data[j].id;
                    xPlay.dev[j].br = 100;
                    xPlay.dev[j].R = 0;
                    xPlay.dev[j].G = 255;
                    xPlay.dev[j].B = 0;
                }
                else
                {
                    xPlay.dev[j].cid = slave.data[j].id;
                    xPlay.dev[j].br = 0;
                    xPlay.dev[j].R = 0;
                    xPlay.dev[j].G = 0;
                    xPlay.dev[j].B = 0;
                }
            }
            transmit_protocol_frame((uint8_t *)&xPlay, &((L0_cmd_playRGBbr_Typedef *)0)->dev[slave.num], &parse.tx_framebuf); // ͨ��������Э�鷢��
        delayMS(100);
        }
    }
    /**********************************************************************************************/
    // // // uint8_t i, j;
    // // // uint16_t size;
    // // // uint8_t buffer[DMA_BUFFER_SIZE];
    // // // if (slave.num) // ���豸���ߵ�ʱ��ŷ�������
    // // // {
    // // //     ((playpack_Typedef *)(&buffer))->head.type = PLAY_DATA;
    // // //     ((playpack_Typedef *)(&buffer))->head.num = slave.num;
    // // //     size = sizeof(packhead_Typedef) + slave.num * sizeof(playdata_Typedef);
    // // //     for (i = 0; i < slave.num + 1; i++)
    // // //     {
    // // //         for (j = 0; j < slave.num; j++)
    // // //         {
    // // //             ((playpack_Typedef *)(&buffer))->play[j].addr = slave.data[j].id;
    // // //             ((playpack_Typedef *)(&buffer))->play[j].bri = 255;
    // // //             if (j == i)
    // // //             {
    // // //                 ((playpack_Typedef *)(&buffer))->play[j].R = 0;
    // // //                 ((playpack_Typedef *)(&buffer))->play[j].G = 255;
    // // //                 ((playpack_Typedef *)(&buffer))->play[j].B = 0;
    // // //                 ((playpack_Typedef *)(&buffer))->play[j].W = 0;
    // // //             }
    // // //             else
    // // //             {
    // // //                 ((playpack_Typedef *)(&buffer))->play[j].R = 0;
    // // //                 ((playpack_Typedef *)(&buffer))->play[j].G = 0;
    // // //                 ((playpack_Typedef *)(&buffer))->play[j].B = 0;
    // // //                 ((playpack_Typedef *)(&buffer))->play[j].W = 0;
    // // //             }
    // // //         }
    // // //         transmit_protocol_frame(&buffer, size, &parse.tx_framebuf); // ͨ��������Э�鷢��
    // // //         // delay_500ms();
    // // //         delayMS(50);
    // // //     }
    // // // }
}

/*
 * @Description: ����������һ����
 * @param:
 * @return:
 */
void light_up_only_one_slave(uint8_t id)
{
    uint8_t j;
    uint16_t size;
    uint8_t buffer[DMA_BUFFER_SIZE];
    if (slave.num) // ���豸���ߵ�ʱ��ŷ�������
    {
        ((playpack_Typedef *)(&buffer))->head.type = PLAY_DATA;
        ((playpack_Typedef *)(&buffer))->head.num = slave.num;
        size = sizeof(packhead_Typedef) + slave.num * sizeof(playdata_Typedef);
        for (j = 0; j < slave.num; j++)
        {
            ((playpack_Typedef *)(&buffer))->play[j].addr = slave.data[j].id;
            ((playpack_Typedef *)(&buffer))->play[j].bri = 255;
            if (slave.data[j].id == id)
            {
                ((playpack_Typedef *)(&buffer))->play[j].R = 0;
                ((playpack_Typedef *)(&buffer))->play[j].G = 0;
                ((playpack_Typedef *)(&buffer))->play[j].B = 255;
                ((playpack_Typedef *)(&buffer))->play[j].W = 0;
            }
            else
            {
                ((playpack_Typedef *)(&buffer))->play[j].R = 0;
                ((playpack_Typedef *)(&buffer))->play[j].G = 0;
                ((playpack_Typedef *)(&buffer))->play[j].B = 0;
                ((playpack_Typedef *)(&buffer))->play[j].W = 0;
            }
        }
        transmit_protocol_frame(&buffer, size, &parse.tx_framebuf); // ͨ��������Э�鷢��
    }
}


/* 
 * @Description: ��������������
 * @param: 
 * @param: 
 * @return: 
*/ 
void protocol_rxdata_handle(uint8_t *p, uint16_t len)
{
    if ((((large_package_Typedef *)p)->head.dev_adr == ADDR_PUBLIC) || (((large_package_Typedef *)p)->head.dev_adr == ADDR_MASTER)) // �豸��ַУ��
    {
        // // // boot_command_parse(p, len);
        slave_answer_parse(p, len);
        // // // general_command_parse(p, len);
    }
}


/*
 * @Description: �ӻ�Ӧ�����
 * @param: ���ݰ�Դָ��
 * @param: ���ݰ�����
 * @return: ��
 */
void slave_answer_parse(uint8_t *p, uint16_t len)
{
    switch (((large_package_Typedef *)p)->head.cmd)
    {
    case CMD_SLAVE_CONNECT_COID: // ����ͨ��ID
        Fun_SLAVE_CONNECT_COID(p, len);
        break;
    case CMD_SLAVE_GET_ID: // ��ȡID
        Fun_SLAVE_GET_ID(p, len);
        break;
    case CMD_SLAVE_GET_SHAPE: // ��ȡ��״
        Fun_SLAVE_GET_SHAPE(p, len);
        break;
    case CMD_SLAVE_GET_CALIBRATION: // ��ȡУ׼����
        Fun_SLAVE_GET_CALIBRATION(p, len);
        break;
    default:
        break;
    }
}

void Fun_SLAVE_CONNECT_COID(uint8_t *p, uint16_t len) // ����ͨ��ID
{
#define xID ((L0_cmd_id_data_Typedef *)p)
    if (xID->head.type == MES_ACK) // Ӧ������
    {
        connect_id = xID->cid;
    }
    else
    {
        return;
    }
#undef xID
}
void Fun_SLAVE_GET_ID(uint8_t *p, uint16_t len) // ��ȡID
{
}
void Fun_SLAVE_GET_SHAPE(uint8_t *p, uint16_t len) // ��ȡ��״
{
    uint8_t i;
#define xShape ((L0_cmd_shape_data_Typedef *)p)
    if (xShape->head.type == MES_ACK) // Ӧ������
    {
        for (i = 0; i < slave.num; i++)
        {
            if (xShape->cid == slave.data[i].id)
            {
                slave.data[i].shape = xShape->shape;
                break;
            }
        }
        // get_device_shape();
        // x.head.dev_adr = ADDR_MASTER;                           // ������ַ
        // x.head.cmd = CMD_SLAVE_GET_SHAPE;                       // ��ȡID
        // x.head.type = MES_ACK;                                  // Ӧ������
        // get_device_shape();                                     // ad����
        // x.shape = userdata.shape;                               // ��ȡ��״
        // my_memcpy(&x.adval, &dev_shape_adval, sizeof(x.adval)); // adֵ
        // x.random[0] = get_random_number();
        // x.random[1] = get_random_number();
        // x.random[2] = get_random_number();
        // transmit_protocol_frame((uint8_t *)&x, sizeof(x), parse.tx_framebuf);
    }
#undef xShape  

}
void Fun_SLAVE_GET_CALIBRATION(uint8_t *p, uint16_t len) // ��ȡУ׼����
{
}
