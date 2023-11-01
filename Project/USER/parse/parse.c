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
 * @Description: ��ʼ��fifo
 * @param: fifo����ָ��
 * @param: fifo�����С
 * @param: fifo��ָ���ָ��
 * @param: fifoдָ���ָ��
 * @return: ��
*/
void fifo_init(uint8_t *buf, uint16_t bufsize, uint16_t *pr, uint16_t *pw)
{
    *pr = 0;
    *pw = 0;
    memset(buf, 0, bufsize);
}

/*
 * @Description: ��һ�ֽ�����ѹ��fifo
 * @param: fifo����ָ��
 * @param: fifo�����С
 * @param: fifo��ָ���ָ��
 * @param: ��ѹ����
 * @return:��
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
 * @Description:fifo����������Э��ȡ����Ч���ݶ�
 * @param: fifo����ָ��
 * @param: fifo�����С
 * @param: fifo��ָ���ָ��
 * @param: fifoдָ���ָ��
 * @param: ����������ݴ洢����ָ��
 * @return:��
 */
void fifo_parse(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t *pw, uint8_t *processbuf)
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
            break;
        }
    }
}

/*
 * @Description: ������Ĵ����ݶεĴ�����
 * @param:  ���ݶ�ָ��
 * @param:  ��Ч���ݳ���
 * @return: ��
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
 * @Description: ����Э��֡������ͨ��Э���Զ����Э��֡
 * @param: Դ����ָ��
 * @param: ���ݳ���
 * @param: ���ͻ���ָ��
 * @return: ��
 */
void transmit_protocol_frame(uint8_t *sur, uint16_t len, uint8_t *txbuf)
{
    if (len > PROCESS_TXDATA_LMT)
    {
        return; // ���ݳ��ȳ�����Ч
    }
    txbuf[0] = FRAME_HEAD;                              // ֡ͷ
    memcpy(&txbuf[1], sur, len);                        // ����Դ���ݶ�
    txbuf[len + 1] = len;                               // ���ݶγ��ȵͰ�λ
    txbuf[len + 2] = len >> 8;                          // ���ݶγ��ȸ߰�λ
    txbuf[len + 3] = get_data_checksum(txbuf, len + 3); // У���
    txbuf[len + 4] = FRAME_TAIL;                        // ֡β
    transmit_buffer_data(txbuf, len + FRAME_STRUCT_SIZE);
}

/*====================================================================================================================*/

/*
 * @Description: �����ض����ȵ�����
 * @param: Դ����ָ��
 * @param: Ҫ���͵ĳ���
 * @return: ��
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
 * @Description: ����һ�ֽ����ݣ�����д����һ�ֽڵĺ���
 * @param: Ҫ���͵�����
 * @return:��
 */
void transmit_byte_data(uint8_t data)
{
    /* ����д����һ�ֽڵĺ��� */
    UART0_Send(data);
    // // printlog("%02x ",data);
}

/*
 * @Description: ��fifo�л�ȡһ�ֽڵ�����
 * @param: fifo����ָ��
 * @param: fifo�����С
 * @param: ��ǰ��ָ��
 * @param: Ҫ��ȡ�����ݻ��ڶ�ָ����ǰ��ƫ��ֵ��0����ǰ��ָ��ָ�������
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
 * @Description:��fifo�п���һ����������
 * @param: fifo����ָ��
 * @param: fifo�����С
 * @param: ��ǰ��ָ��
 * @param: �������һ�ֽڻ��ڶ�ָ���ƫ����
 * @param: Ŀ�����ݴ��ָ��
 * @param: Ҫ��������������ֵҪ���ڵ���1����С��fifo�����С
 * @return:��
 */
void get_section_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t offset, uint8_t *dest, uint16_t num)
{
    uint32_t p;      // �������ݶε�ͷ��ָ��
    uint32_t remain; // ʣ��ռ�
    while (num > bufsize)
    {
        num -= bufsize; // ��ָֹ��Խ��
    }
    p = bufsize + *pr - offset - num + 1;
    while (p >= bufsize)
    {
        p -= bufsize;
    }
    remain = bufsize - p;
    if (remain >= num) // ʣ����������������ȫ������
    {
        memcpy(dest, fifobuf + p, num);
    }
    else
    {
        memcpy(dest, fifobuf + p, remain);            // ����ǰ��
        memcpy(dest + remain, fifobuf, num - remain); // �������
    }
}

/*
 * @Description: ��ȡ�ۼӺ�
 * @param: Դ����ָ��
 * @param: Ҫ����ĳ���
 * @return: �ۼӺ�
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
 * @Description:���Ժ���
 * @param: ��
 * @return:��
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
