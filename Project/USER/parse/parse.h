#ifndef _PARSE_H
#define _PARSE_H
#include "Function_Init.H"
#include <string.h>

#define FRAME_HEAD 0xAA // 帧头
#define FRAME_TAIL 0xBB // 帧尾

#define PROCESS_BUFFER_SIZE 100
typedef struct
{
    uint16_t read;                            // 读指针
    uint8_t process_buf[PROCESS_BUFFER_SIZE]; // 数据处理缓存
} parse_TypeDef;
extern parse_TypeDef parse;

/*=============================================================================
帧头 + [数据段] + 数据长度 + 校验和 + 帧尾

数据长度：数据段的长度（不包括帧头）
校验和：此字之前所有字节的累加和（包括帧头）

*/

/*=============================================================================*/
#define FRAME_TAIL_OFFSET 0  // 帧尾的偏移地址
#define CHECK_SUM_OFFSET 1   // 校验和的偏移地址
#define DATA_LENGTH_OFFSET 2 // 数据长度的偏移地址
#define DATA_END 3           // 数据最后一字节的偏移地址
/*=============================================================================*/

/*获取读指针往前偏离offset个字节的1字节数据*/
uint8_t get_byte_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t pr, uint16_t offset);
/*获取读指针前offset字节的数据段（num个字节）*/
void get_section_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t pr, uint16_t offset, uint8_t *dest, uint16_t num);
/*获取累加和*/
uint32_t get_data_checksum(uint8_t *sur, uint32_t len);
/*fifo解析*/
void fifo_parse(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t *pw, uint8_t *processbuf);
/*解析后的协议数据处理*/
void protocol_data_handle(uint8_t *p, uint32_t len);

#endif
