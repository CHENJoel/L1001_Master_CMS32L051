/* File Info
 * Author:      Joel.chen
 * CreateTime:  2023/6/16 10:55:21
 * LastEditor:  your name
 * ModifyTime:  2023/6/17 14:52:29
 * Description:
 */
#include "parse.h"
parse_TypeDef parse;

/*
 * @Description: 初始化fifo
 * @param: fifo缓存指针
 * @param: fifo缓存大小
 * @param: fifo读指针的指针
 * @param: fifo写指针的指针
 * @return: 无
*/
void fifo_init(uint8_t *buf, uint16_t bufsize, uint16_t *pr, uint16_t *pw)
{
    *pr = 0;
    *pw = 0;
    memset(buf, 0, bufsize);
}

/*
 * @Description: 将一字节数据压入fifo
 * @param: fifo缓存指针
 * @param: fifo缓存大小
 * @param: fifo读指针的指针
 * @param: 被压数据
 * @return:无
 */
void fifo_byte_push(uint8_t *buf, uint16_t bufsize, uint16_t *pw, uint8_t data)
{
    buf[*pw] = data;
    if (++*pw >= bufsize)
    {
        *pw = 0;
    }
}

/*
 * @Description:fifo解析，根据协议取出有效数据段
 * @param: fifo缓存指针
 * @param: fifo缓存大小
 * @param: fifo读指针的指针
 * @param: fifo写指针的指针
 * @param: 解析后的数据存储缓存指针
 * @return:无
 */
void fifo_parse(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t *pw, uint8_t *processbuf)
{
    uint16_t i;
    uint16_t datalength;       // 数据段长度
    uint8_t datasum;           // 数据段的累加和
    for (i = 0; i < 1000; i++) // 限制单次解析次数
    {
        if (*pr != *pw) // 未读完缓存
        {
            if (FRAME_TAIL == get_byte_from_fifo(fifobuf, bufsize, pr, FRAME_TAIL_OFFSET)) // 帧尾校验
            {
                datalength = get_byte_from_fifo(fifobuf, bufsize, pr, DATA_LENGTH_H_OFFSET) << 8; // 数据长度高八位
                datalength |= get_byte_from_fifo(fifobuf, bufsize, pr, DATA_LENGTH_L_OFFSET);     // 数据长度低八位
                if (datalength < PROCESS_RXDATA_LMT)                                              // 限制数据段长度
                {
                    if (FRAME_HEAD == get_byte_from_fifo(fifobuf, bufsize, pr, datalength + DATA_END_OFFSET)) // 帧头校验
                    {
                        get_section_from_fifo(fifobuf, bufsize, pr, DATA_END_OFFSET, processbuf, datalength); // 提取数据段到处理缓存中
                        datasum = get_data_checksum(processbuf, datalength);                                  // 数据区累加和
                        datasum += FRAME_HEAD;                                                                // 累加帧头
                        datasum += (datalength >> 8);                                                         // 累加数据长度高八位
                        datasum += datalength;                                                                // 累加数据长度低八位
                        if (datasum == get_byte_from_fifo(fifobuf, bufsize, pr, CHECK_SUM_OFFSET))            // 校验和
                        {
                            protocol_rxdata_handle(processbuf, datalength); // 处理解析后的数据
                        }
                    }
                }
            }
            if (++*pr >= bufsize) // 指向下一位
            {
                *pr = 0;
            }
        }
        else // 缓存无待读数据
        {
            break;
        }
    }
}

/*
 * @Description: 解析后的纯数据段的处理函数
 * @param:  数据段指针
 * @param:  有效数据长度
 * @return: 无
 */
__weak void protocol_rxdata_handle(uint8_t *p, uint16_t len)
{
   uint8_t i;
    printlog("\rprotocol_rxdata_handle\r");
    for (i = 0; i < len; i++)
    {
        printlog("%02x ", *(p + i));
    }
    printlog("\r\n");
}

/*
 * @Description: 发送协议帧，根据通信协议自动填充协议帧
 * @param: 源数据指针
 * @param: 数据长度
 * @param: 发送缓存指针
 * @return: 无
 */
void transmit_protocol_frame(uint8_t *sur, uint16_t len, uint8_t *txbuf)
{
    if (len > PROCESS_TXDATA_LMT)
    {
        return; // 数据长度超长无效
    }
    txbuf[0] = FRAME_HEAD;                              // 帧头
    memcpy(&txbuf[1], sur, len);                        // 拷贝源数据段
    txbuf[len + 1] = len;                               // 数据段长度低八位
    txbuf[len + 2] = len >> 8;                          // 数据段长度高八位
    txbuf[len + 3] = get_data_checksum(txbuf, len + 3); // 校验和
    txbuf[len + 4] = FRAME_TAIL;                        // 帧尾
    transmit_buffer_data(txbuf, len + FRAME_STRUCT_SIZE);
}

/*====================================================================================================================*/

/*
 * @Description: 发送特定长度的数据
 * @param: 源数据指针
 * @param: 要发送的长度
 * @return: 无
 */
__weak void transmit_buffer_data(uint8_t *sur, uint16_t len)
{
    if ((((void *)0) == sur) || (0 == len))
    {
        return;
    }

    while (len--)
    {
        transmit_byte_data(*sur);
        sur++;
    }
}

/*
 * @Description: 发送一字节数据，请填写发送一字节的函数
 * @param: 要发送的数据
 * @return:无
 */
void transmit_byte_data(uint8_t data)
{
    /* 请填写发送一字节的函数 */
    UART0_Send(data);
    // // printlog("%02x ",data);
}

/*
 * @Description: 在fifo中获取一字节的数据
 * @param: fifo缓存指针
 * @param: fifo缓存大小
 * @param: 当前读指针
 * @param: 要读取的数据基于读指针往前的偏移值，0代表当前读指针指向的数据
 * @return:
 */
uint8_t get_byte_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t offset)
{
    uint32_t p;
    p = bufsize + *pr - offset;
    while (p >= bufsize)
    {
        p -= bufsize;
    }
    return *(fifobuf + p);
}

/*
 * @Description:在fifo中拷贝一段连续数据
 * @param: fifo缓存指针
 * @param: fifo缓存大小
 * @param: 当前读指针
 * @param: 数据最后一字节基于读指针的偏移量
 * @param: 目标数据存放指针
 * @param: 要拷贝的数据量，值要大于等于1，且小于fifo缓存大小
 * @return:无
 */
void get_section_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t offset, uint8_t *dest, uint16_t num)
{
    uint32_t p;      // 被拷数据段的头部指针
    uint32_t remain; // 剩余空间
    while (num > bufsize)
    {
        num -= bufsize; // 防止指针越界
    }
    p = bufsize + *pr - offset - num + 1;
    while (p >= bufsize)
    {
        p -= bufsize;
    }
    remain = bufsize - p;
    if (remain >= num) // 剩余区域能连续拷贝全部数据
    {
        memcpy(dest, fifobuf + p, num);
    }
    else
    {
        memcpy(dest, fifobuf + p, remain);            // 拷贝前段
        memcpy(dest + remain, fifobuf, num - remain); // 拷贝后段
    }
}

/*
 * @Description: 获取累加和
 * @param: 源数据指针
 * @param: 要计算的长度
 * @return: 累加和
 */
uint32_t get_data_checksum(uint8_t *sur, uint16_t len)
{
    uint32_t i;
    uint32_t sum = 0;
    for (i = 0; i < len; i++)
    {
        sum += *sur++;
    }
    return sum;
}
/*
 * @Description:调试函数
 * @param: 无
 * @return:无
 */
void debug_fifo(void)
{
    // uint8_t buf[10];
    // uint8_t i;
    // uint8_t size;
    // printf("\rdebug_fifo\r");
    // printf("source data:\r");
    // size = Random_Generate() % sizeof(buf);
    // for (i = 0; i < size; i++)
    // {
    //     buf[i] = Random_Generate();
    //     printf("%x ", buf[i]);
    // }
    // transmit_protocol_frame(buf, size, parse.tx_framebuf);
}
