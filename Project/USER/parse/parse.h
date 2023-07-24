/* File Info
 * Author:      Joel.chen
 * CreateTime:  2023/6/16 10:55:27
 * LastEditor:  your name
 * ModifyTime:  2023/6/17 14:52:35
 * Description:
 */

#ifndef _PARSE_H
#define _PARSE_H
#include "Function_Init.H"
#include <string.h>

/*=============================================================================

֡ͷ + [���ݶ�] + ���ݳ���H+L + У��� + ֡β

���ݳ��ȣ����ݶεĳ��ȣ�������֡ͷ��
У��ͣ�����֮ǰ�����ֽڵ��ۼӺͣ�����֡ͷ��
*/
/*=============================================================================*/

#define FRAME_TAIL_OFFSET 0    // ֡β��ƫ�Ƶ�ַ
#define CHECK_SUM_OFFSET 1     // У��͵�ƫ�Ƶ�ַ
#define DATA_LENGTH_H_OFFSET 2 // ���ݳ��ȵ�ƫ�Ƶ�ַ
#define DATA_LENGTH_L_OFFSET 3 // ���ݳ��ȵ�ƫ�Ƶ�ַ С��ģʽ
#define DATA_END_OFFSET 4      // �������һ�ֽڵ�ƫ�Ƶ�ַ

#define FRAME_STRUCT_SIZE 5 // ֡�ṹ�ߴ�

/*=============================================================================*/

/*������Ҫ�޸�/ɾ������*/
#define FRAME_HEAD 0xAA // ֡ͷ
#define FRAME_TAIL 0xBB // ֡β

#define PROCESS_RXDATA_LMT 300 // ���ν��յ�������ݶγߴ磨������֡�ṹ������󲻳���256�ֽ�
#define PROCESS_TXDATA_LMT 300 // ���η��͵�������ݶγߴ磨������֡�ṹ������󲻳���256�ֽ�
#define FIFO_BUFFER_SIZE 4000  // fifo����ߴ�

typedef struct
{
    // // uint16_t ins_read;                                           // ����Э��Ķ�ָ��
    // // uint16_t read;                                               // ��ָ��
    // // uint16_t write;                                              // дָ��
    // // uint8_t fifo_buffer[FIFO_BUFFER_SIZE];                       // fifo����
    // // uint8_t rx_data_buf[PROCESS_RXDATA_LMT];                     // ����������ݴ����棬����֡�ṹ
    uint8_t tx_framebuf[FRAME_STRUCT_SIZE + PROCESS_TXDATA_LMT]; // ����֡����
} parse_TypeDef;
extern parse_TypeDef parse;

/*=============================================================================*/

/*=========================================================================================================*/
// API����
/*��ʼ��fifo*/
void fifo_init(uint8_t *buf, uint16_t bufsize, uint16_t *pr, uint16_t *pw);
/*��һ�ֽ�����ѹ��fifo*/
void fifo_byte_push(uint8_t *buf, uint16_t bufsize, uint16_t *pw, uint8_t data);
/*fifo����������Э��ȡ����Ч���ݶ�*/
void fifo_parse(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t *pw, uint8_t *processbuf);
/*������Ĵ����ݶεĴ�����*/
void protocol_rxdata_handle(uint8_t *p, uint16_t len);
/*����Э��֡������ͨ��Э���Զ����Э��֡*/
void transmit_protocol_frame(uint8_t *sur, uint16_t len, uint8_t *txbuf);

/*=========================================================================================================*/
// �ڲ�ʵ�ֺ���

/*�����ض����ȵ�����*/
void transmit_buffer_data(uint8_t *sur, uint16_t len);
/*����һ�ֽ����ݣ�����д����һ�ֽڵĺ���*/
void transmit_byte_data(uint8_t data);
/*��fifo�л�ȡһ�ֽڵ�����*/
uint8_t get_byte_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t offset);
/*��fifo�п���һ����������*/
void get_section_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t offset, uint8_t *dest, uint16_t num);
/*��ȡ�ۼӺ�*/
uint32_t get_data_checksum(uint8_t *sur, uint16_t len);
/*���Ժ���*/
void debug_fifo(void);

#endif
