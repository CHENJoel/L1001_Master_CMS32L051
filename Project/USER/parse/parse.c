#include "parse.h"
parse_TypeDef parse;

/*获取读指针往前偏离offset个字节的1字节数据*/
uint8_t get_byte_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t pr, uint16_t offset)
{
    /*
    offset：0为当前读指针指向的值
    */
    uint32_t p;
    p = bufsize + pr - offset;
    while (p >= bufsize)
    {
        p -= bufsize;
    }
    return *(fifobuf + p);
}

/*获取读指针前offset字节的数据段（num个字节）*/
void get_section_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t pr, uint16_t offset, uint8_t *dest, uint16_t num)
{
    /*
        被提取的字节数需小于缓存大小
        num：要拷贝的数据个数，值大于等于1
    */
    uint32_t p;      // 被拷数据段的头部指针
    uint32_t remain; // 剩余空间
    while (num > bufsize)
    {
        num -= bufsize; // 防止指针越界
    }
    p = bufsize + pr - offset - num + 1;
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
/*获取累加和*/
uint32_t get_data_checksum(uint8_t *sur, uint32_t len)
{
    uint32_t i;
    uint32_t sum = 0;
    for (i = 0; i < len; i++)
    {
        sum += *sur++;
    }
    return sum;
}

/*fifo解析*/
void fifo_parse(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t *pw, uint8_t *processbuf)
{
    uint16_t i;
    uint8_t datalength;        // 数据段长度
    uint8_t datasum;           // 数据段的累加和
    for (i = 0; i < 1000; i++) // 限制单次解析次数
    {
        if (*pr != *pw) // 未读完缓存
        {
            if (FRAME_TAIL == get_byte_from_fifo(fifobuf, bufsize, *pr, FRAME_TAIL_OFFSET)) // 帧尾校验
            {
                datalength = get_byte_from_fifo(fifobuf, bufsize, *pr, DATA_LENGTH_OFFSET);                         // 数据长度
                if (FRAME_HEAD == get_byte_from_fifo(fifobuf, bufsize, *pr, datalength + (DATA_LENGTH_OFFSET + 1))) // 帧头校验
                {
                    get_section_from_fifo(fifobuf, bufsize, *pr, DATA_END, processbuf, datalength); // 提取数据段到处理缓存中
                    datasum = get_data_checksum(processbuf, datalength);                            // 数据区累加和
                    datasum += FRAME_HEAD;                                                          // 累加帧头
                    datasum += datalength;                                                          // 累加数据长度
                    if (datasum == get_byte_from_fifo(fifobuf, bufsize, *pr, CHECK_SUM_OFFSET))     // 校验和
                    {
                        protocol_data_handle(processbuf, datalength); // 处理解析后的数据
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

/*解析后的协议数据处理*/
void protocol_data_handle(uint8_t *p, uint32_t len)
{
    uint8_t i;
    // printlog("protocol_data_handle\r");
    // for ( i = 0; i < len; i++)
    // {
    //     printlog("%x ",*(p+i));
    // }
    // printlog("\r\n");
}
