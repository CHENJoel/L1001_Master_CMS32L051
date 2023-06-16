#include "parse.h"
parse_TypeDef parse;

/*��ȡ��ָ����ǰƫ��offset���ֽڵ�1�ֽ�����*/
uint8_t get_byte_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t pr, uint16_t offset)
{
    /*
    offset��0Ϊ��ǰ��ָ��ָ���ֵ
    */
    uint32_t p;
    p = bufsize + pr - offset;
    while (p >= bufsize)
    {
        p -= bufsize;
    }
    return *(fifobuf + p);
}

/*��ȡ��ָ��ǰoffset�ֽڵ����ݶΣ�num���ֽڣ�*/
void get_section_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t pr, uint16_t offset, uint8_t *dest, uint16_t num)
{
    /*
        ����ȡ���ֽ�����С�ڻ����С
        num��Ҫ���������ݸ�����ֵ���ڵ���1
    */
    uint32_t p;      // �������ݶε�ͷ��ָ��
    uint32_t remain; // ʣ��ռ�
    while (num > bufsize)
    {
        num -= bufsize; // ��ָֹ��Խ��
    }
    p = bufsize + pr - offset - num + 1;
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
/*��ȡ�ۼӺ�*/
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

/*fifo����*/
void fifo_parse(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t *pw, uint8_t *processbuf)
{
    uint16_t i;
    uint8_t datalength;        // ���ݶγ���
    uint8_t datasum;           // ���ݶε��ۼӺ�
    for (i = 0; i < 1000; i++) // ���Ƶ��ν�������
    {
        if (*pr != *pw) // δ���껺��
        {
            if (FRAME_TAIL == get_byte_from_fifo(fifobuf, bufsize, *pr, FRAME_TAIL_OFFSET)) // ֡βУ��
            {
                datalength = get_byte_from_fifo(fifobuf, bufsize, *pr, DATA_LENGTH_OFFSET);                         // ���ݳ���
                if (FRAME_HEAD == get_byte_from_fifo(fifobuf, bufsize, *pr, datalength + (DATA_LENGTH_OFFSET + 1))) // ֡ͷУ��
                {
                    get_section_from_fifo(fifobuf, bufsize, *pr, DATA_END, processbuf, datalength); // ��ȡ���ݶε���������
                    datasum = get_data_checksum(processbuf, datalength);                            // �������ۼӺ�
                    datasum += FRAME_HEAD;                                                          // �ۼ�֡ͷ
                    datasum += datalength;                                                          // �ۼ����ݳ���
                    if (datasum == get_byte_from_fifo(fifobuf, bufsize, *pr, CHECK_SUM_OFFSET))     // У���
                    {
                        protocol_data_handle(processbuf, datalength); // ��������������
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

/*�������Э�����ݴ���*/
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
