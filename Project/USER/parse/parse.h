#ifndef _PARSE_H
#define _PARSE_H
#include "Function_Init.H"
#include <string.h>

#define FRAME_HEAD 0xAA // ֡ͷ
#define FRAME_TAIL 0xBB // ֡β

#define PROCESS_BUFFER_SIZE 100
typedef struct
{
    uint16_t read;                            // ��ָ��
    uint8_t process_buf[PROCESS_BUFFER_SIZE]; // ���ݴ�����
} parse_TypeDef;
extern parse_TypeDef parse;

/*=============================================================================
֡ͷ + [���ݶ�] + ���ݳ��� + У��� + ֡β

���ݳ��ȣ����ݶεĳ��ȣ�������֡ͷ��
У��ͣ�����֮ǰ�����ֽڵ��ۼӺͣ�����֡ͷ��

*/

/*=============================================================================*/
#define FRAME_TAIL_OFFSET 0  // ֡β��ƫ�Ƶ�ַ
#define CHECK_SUM_OFFSET 1   // У��͵�ƫ�Ƶ�ַ
#define DATA_LENGTH_OFFSET 2 // ���ݳ��ȵ�ƫ�Ƶ�ַ
#define DATA_END 3           // �������һ�ֽڵ�ƫ�Ƶ�ַ
/*=============================================================================*/

/*��ȡ��ָ����ǰƫ��offset���ֽڵ�1�ֽ�����*/
uint8_t get_byte_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t pr, uint16_t offset);
/*��ȡ��ָ��ǰoffset�ֽڵ����ݶΣ�num���ֽڣ�*/
void get_section_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t pr, uint16_t offset, uint8_t *dest, uint16_t num);
/*��ȡ�ۼӺ�*/
uint32_t get_data_checksum(uint8_t *sur, uint32_t len);
/*fifo����*/
void fifo_parse(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t *pw, uint8_t *processbuf);
/*�������Э�����ݴ���*/
void protocol_data_handle(uint8_t *p, uint32_t len);

#endif
