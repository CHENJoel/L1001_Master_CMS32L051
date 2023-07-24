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

帧头 + [数据段] + 数据长度H+L + 校验和 + 帧尾

数据长度：数据段的长度（不包括帧头）
校验和：此字之前所有字节的累加和（包括帧头）
*/
/*=============================================================================*/

#define FRAME_TAIL_OFFSET 0    // 帧尾的偏移地址
#define CHECK_SUM_OFFSET 1     // 校验和的偏移地址
#define DATA_LENGTH_H_OFFSET 2 // 数据长度的偏移地址
#define DATA_LENGTH_L_OFFSET 3 // 数据长度的偏移地址 小端模式
#define DATA_END_OFFSET 4      // 数据最后一字节的偏移地址

#define FRAME_STRUCT_SIZE 5 // 帧结构尺寸

/*=============================================================================*/

/*根据需要修改/删减参数*/
#define FRAME_HEAD 0xAA // 帧头
#define FRAME_TAIL 0xBB // 帧尾

#define PROCESS_RXDATA_LMT 300 // 单次接收的最大数据段尺寸（不包括帧结构），最大不超过256字节
#define PROCESS_TXDATA_LMT 300 // 单次发送的最大数据段尺寸（不包括帧结构），最大不超过256字节
#define FIFO_BUFFER_SIZE 4000  // fifo缓存尺寸

typedef struct
{
    // // uint16_t ins_read;                                           // 其他协议的读指针
    // // uint16_t read;                                               // 读指针
    // // uint16_t write;                                              // 写指针
    // // uint8_t fifo_buffer[FIFO_BUFFER_SIZE];                       // fifo缓存
    // // uint8_t rx_data_buf[PROCESS_RXDATA_LMT];                     // 解析后的数据处理缓存，不含帧结构
    uint8_t tx_framebuf[FRAME_STRUCT_SIZE + PROCESS_TXDATA_LMT]; // 发送帧缓存
} parse_TypeDef;
extern parse_TypeDef parse;

/*=============================================================================*/

/*=========================================================================================================*/
// API函数
/*初始化fifo*/
void fifo_init(uint8_t *buf, uint16_t bufsize, uint16_t *pr, uint16_t *pw);
/*将一字节数据压入fifo*/
void fifo_byte_push(uint8_t *buf, uint16_t bufsize, uint16_t *pw, uint8_t data);
/*fifo解析，根据协议取出有效数据段*/
void fifo_parse(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t *pw, uint8_t *processbuf);
/*解析后的纯数据段的处理函数*/
void protocol_rxdata_handle(uint8_t *p, uint16_t len);
/*发送协议帧，根据通信协议自动填充协议帧*/
void transmit_protocol_frame(uint8_t *sur, uint16_t len, uint8_t *txbuf);

/*=========================================================================================================*/
// 内部实现函数

/*发送特定长度的数据*/
void transmit_buffer_data(uint8_t *sur, uint16_t len);
/*发送一字节数据，请填写发送一字节的函数*/
void transmit_byte_data(uint8_t data);
/*在fifo中获取一字节的数据*/
uint8_t get_byte_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t offset);
/*在fifo中拷贝一段连续数据*/
void get_section_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t offset, uint8_t *dest, uint16_t num);
/*获取累加和*/
uint32_t get_data_checksum(uint8_t *sur, uint16_t len);
/*调试函数*/
void debug_fifo(void);

#endif
