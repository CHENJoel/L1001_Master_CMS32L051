/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-06-09 15:56:49
 * @LastEditors: joel
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


device_data_TypeDef slave;
device_color_TypeDef slavecolor;    // 配对临时使用
device_control_TypeDef slave_control;

/*
 * @Description: 串口发出数据串
 * @param: 源数据指针
 * @param: 数据长度
 * @return: 无
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
 * @Description: 握手连接从机设备
 * @param: 从机id
 * @return: 无
*/
void connect_slave_device(uint8_t id)
{
    comCmd_Typedef com;
    com.com_head = MCMD_HEADER;
    com.com_addr = id;
    com.com_cmdType = CMD_CONTROL;  // 控制指令
    com.com_cmd = CMD_CONNECT_COID; // 握手通信ID
    com.com_val1 = Random_Generate();
    com.com_val2 = Random_Generate();
    com.com_checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    tx_uart_data((uint8_t *)&com, (uint16_t)sizeof(com));
}

/*
 * @Description: 要求更新所有从机的通讯id
 * @param: 从机id
 * @return: 无
*/
void refresh_slave_comid(void)
{
    comCmd_Typedef com;
    com.com_head = MCMD_HEADER;
    com.com_addr = 0xFF;            // 广播
    com.com_cmdType = CMD_CONTROL;  // 控制指令
    com.com_cmd = CMD_REFRESH_COID; // 更新通信ID
    com.com_val1 = Random_Generate();
    com.com_val2 = Random_Generate();
    com.com_checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    tx_uart_data((uint8_t *)&com, (uint16_t)sizeof(com));
}

/*
 * @Description: 请求从机的形状信息
 * @param: 从机id
 * @return: 无
*/
void ask_slave_shape(uint8_t id)
{
    comRW_Typedef com;
    com.com_head = MCMD_HEADER;
    com.com_addr = id;
    com.com_cmdType = CMD_READREG;
    com.com_regaddr = REG_DEVICETYPE; // 设备类型
    com.com_regval = Random_Generate() << 8;
    com.com_regval += Random_Generate();
    com.com_checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    tx_uart_data((uint8_t *)&com, (uint16_t)sizeof(com));
}

/*
 * @Description: 在fifo解析出从机的应答信号
 * @param: fifo缓存指针
 * @param: fifo缓存大小
 * @param: fifo读指针的指针
 * @param: fifo写指针的指针
 * @param: 应答包缓存指针
 * @return: 应答包状态
 */
cmdpack_status get_slave_ack_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t *pw, comCmd_Typedef *pack)
{
    uint16_t i;
    for (i = 0; i < 1000; i++) // 限制单次解析次数
    {
        if (*pr != *pw) // 未读完缓存
        {
            if (SCMD_HEADER == get_byte_from_fifo(fifobuf, bufsize, pr, 7)) // 帧头校验（从机数据包）
            {
                get_section_from_fifo(fifobuf, bufsize, pr, 0, pack, sizeof(comCmd_Typedef));
                if (pack->com_checksum == (uint8_t)checksum_calculate((uint8_t *)pack, (uint16_t)sizeof(comCmd_Typedef) - 1))
                {
                    return PACK_RIGHT; // 校验通过，fifo存在从机返回的指令应答包
                }
            }
            if (++*pr >= bufsize) // 指向下一位
            {
                *pr = 0;
            }
        }
        else // 缓存无待读数据
        {
            if (i == 0)
            {
                return PACK_EMPTY; // 缓存读写地址一致，代表缓存中无新内容
            }
            return PACK_WRONG; // 读完缓存的新内容，但未发现符合协议的数据包
        }
    }
    return PACK_WRONG; //
}

/*
 * @Description: 轮询出在线的从机设备
 * @param: 无
 * @return: 无
*/
void poll_slave_id(void)
{
    uint8_t i, j;
    uint8_t id_buff[32];      // 设备id
    uint8_t online_num = 0;   // 在线设备数量
    uint8_t packstatus;       // 指令数据包状态
    comCmd_Typedef packbuff;
    memset(&slave, 0, sizeof(slave)); // 清除原信息
    memset(&id_buff, 0, sizeof(id_buff)); //
    for (i = 0; i <= 50; i++)  // 最大执行256次冲突处理
    {
        online_num = 0;
        for (j = 1; j < 255; j++) // 轮询所有id，0和255（广播）为无效id
         {
            Uart0_Buffer.Read = Uart0_Buffer.Write; // 清空接收缓存中未读数据
            connect_slave_device(j);                // 握手连接此id
            delay_5ms();
            memset(&packbuff, 0, sizeof(packbuff)); //
            packstatus = get_slave_ack_from_fifo(&Uart0_Buffer.Buffer, sizeof(Uart0_Buffer.Buffer), &Uart0_Buffer.Read, &Uart0_Buffer.Write, &packbuff); // 读取缓存数据状态
            if ((packstatus == PACK_RIGHT) && (packbuff.com_addr == j) && (packbuff.com_cmdType == CMD_CTRLACK) && (packbuff.com_cmd == CMD_CONNECT_COID)) // 接收到一组从机信息数据包
            {
                id_buff[online_num] = j;                 // 标记从机ID
                online_num++;                               // 标记从机数量
            }
            else if (packstatus != PACK_EMPTY) // 非空数据包,但不符合数据协议，数据包有误，代表有多个从机同时占用总线发报数据，即出现ID冲突
            {
                refresh_slave_comid(); // 要求全部从机更新id
                delay_5ms();
                break;               // 重新循环轮询
            }
            if (j == 254) // 内循环轮询结束，说明此前未发现ID冲突
            {
                slave.num = online_num; // 存储在线设备数量
                for (i = 0; i < online_num; i++)
                {
                    slave.data[i].id = id_buff[i]; // 存储设备id
                }
                return ;
            }
        }
    }
}

/*
 * @Description: 获取从机的形状信息
 * @param: 无
 * @return: 无
 */
void get_slave_shape(void)
{
    uint8_t i;
    uint8_t packstatus; // 指令数据包状态
    comRW_Typedef packbuff;
    for (i = 0; i < slave.num; i++)
    {
        Uart0_Buffer.Read = Uart0_Buffer.Write; // 清空接收缓存中未读数据
        ask_slave_shape(slave.data[i].id);
        delay_5ms();
        packstatus = get_slave_ack_from_fifo(&Uart0_Buffer.Buffer, sizeof(Uart0_Buffer.Buffer), &Uart0_Buffer.Read, &Uart0_Buffer.Write, &packbuff);       // 读取缓存数据状态
        if ((packstatus == PACK_RIGHT) && (packbuff.com_addr == slave.data[i].id) && (packbuff.com_cmdType == CMD_RETURNREG) && (packbuff.com_regaddr == REG_DEVICETYPE)) // 接收到一组从机信息数据包
        {
            slave.data[i].shape = packbuff.com_regval;
        }
        else
        {
            slave.data[i].shape = OTHER_SHAPE;
        }
    }
}
/*更新设备信息*/
uint8_t refresh_slave_data(device_detail_TypeDef *p)
{
    uint8_t i;
    for (i = 0; i < SLAVEDEVICE_NUM; i++)
    {
        if (p->id == slave.data[i].id) // 轮询出需要被修改的设备id
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
 * @Description: 从flash中获取从机位置信息
 * @param: 无
 * @return: 无
*/
void get_slave_place(void)
{
    uint8_t i, j;
    device_data_TypeDef device;
    memset(&device, 0, sizeof(device));
    get_all_slave_data(&device);
    if (device.num > SLAVEDEVICE_NUM)
    {
        printlog("[error] wrong device number:%d",device.num);
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
 * @Description: 初始化在线的从机信息
 * @param: 无
 * @return: 无
*/
void slave_online_data_init(void)
{

#ifdef virtual_device
    generate_virtual_device(); // 生成虚拟灯板信息
#else
    poll_slave_id();    // 轮询ID信息
    get_slave_shape();  // 获取灯板形状
#endif

    get_slave_place();
    slave_light_in_turn();
    print_online_slave_data();
}






/*生成虚拟灯板信息*/
void generate_virtual_device(void)
{
    uint8_t temp[32];
    uint8_t i;
    // // memset(&slave, 0, sizeof(slave));
    // // slave.num=8;
    for ( i = 0; i < 32; i++)
    {
        temp[i] = (i + 1) * 10 + i + 1;
        // while (temp[i]==0||temp[i]==255)
        // {
        //     // temp[i] = Random_Generate();
        //     temp[i] = (i+1)*10+i+1;
        //     // printlog("%d Random_Generate %d\r",i,temp[i]);
        // }
    }
    slave.num = 8;
    slave.data[0].id = temp[0];
    slave.data[0].shape = TRIANGLE_L;
    slave.data[0].angle = 0;
    slave.data[0].cooed_x = 1;
    slave.data[0].cooed_y = 1;
    /**************************/
    slave.data[1].id = temp[1];
    slave.data[1].shape = TRIANGLE_L;
    slave.data[1].angle = 0;
    slave.data[1].cooed_x = 2;
    slave.data[1].cooed_y = 2;
    /**************************/
    slave.data[2].id = temp[2];
    slave.data[2].shape = TRIANGLE_M;
    slave.data[2].angle = 0;
    slave.data[2].cooed_x = 3;
    slave.data[2].cooed_y = 3;
    /**************************/
    slave.data[3].id = temp[3];
    slave.data[3].shape = TRIANGLE_S;
    slave.data[3].angle = 0;
    slave.data[3].cooed_x = 4;
    slave.data[3].cooed_y = 4;
    /**************************/
    slave.data[4].id = temp[4];
    slave.data[4].shape = SQUARE;
    slave.data[4].angle = 0;
    slave.data[4].cooed_x = 5;
    slave.data[4].cooed_y = 5;
    /**************************/
    slave.data[5].id = temp[5];
    slave.data[5].shape = TRIANGLE_S;
    slave.data[5].angle = 0;
    slave.data[5].cooed_x = 6;
    slave.data[5].cooed_y = 6;
    /**************************/
    slave.data[6].id = temp[6];
    slave.data[6].shape = TRIANGLE_S;
    slave.data[6].angle = 0;
    slave.data[6].cooed_x = 7;
    slave.data[6].cooed_y = 7;
    /**************************/
    slave.data[7].id = temp[7];
    slave.data[7].shape = TRIANGLE_S;
    slave.data[7].angle = 0;
    slave.data[7].cooed_x = 8;
    slave.data[7].cooed_y = 8;
    /**************************/
}


/*更新设备颜色*/
uint8_t refresh_device_color(color_TypeDef *p, uint8_t id)
{
    uint8_t i;
    for (i = 0; i < SLAVEDEVICE_NUM; i++)
    {
        if (id == slave.data[i].id) // 轮询出需要被修改的设备id
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
 * @Description: 轮流点亮从机
 * @param:
 * @return:
*/
void slave_light_in_turn(void)
{
    uint8_t i, j;
    uint16_t size;
    uint8_t buffer[DMA_BUFFER_SIZE];
    if (slave.num) // 有设备在线的时候才发送数据
    {
        ((playpack_Typedef *)(&buffer))->head.type = PLAY_DATA;
        ((playpack_Typedef *)(&buffer))->head.num = slave.num;
        size = sizeof(packhead_Typedef) + slave.num * sizeof(playdata_Typedef);
        for (i = 0; i < slave.num + 1; i++)
        {
            for (j = 0; j < slave.num; j++)
            {
                ((playpack_Typedef *)(&buffer))->play[j].addr = slave.data[j].id;
                ((playpack_Typedef *)(&buffer))->play[j].bri = 255;
                if (j == i)
                {
                    ((playpack_Typedef *)(&buffer))->play[j].R = 0;
                    ((playpack_Typedef *)(&buffer))->play[j].G = 255;
                    ((playpack_Typedef *)(&buffer))->play[j].B = 0;
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
            transmit_protocol_frame(&buffer, size, &parse.tx_framebuf); // 通过不定长协议发送
            // delay_500ms();
            delayMS(50);
        }
    }
}

/*
 * @Description: 仅点亮其中一个灯
 * @param:
 * @return:
*/
void light_up_only_one_slave(uint8_t id)
{
    uint8_t j;
    uint16_t size;
    uint8_t buffer[DMA_BUFFER_SIZE];
    if (slave.num) // 有设备在线的时候才发送数据
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
        transmit_protocol_frame(&buffer, size, &parse.tx_framebuf); // 通过不定长协议发送
    }
}
