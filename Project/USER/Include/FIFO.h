/*
 * @Author: your name
 * @Date: 2022-02-22 13:26:59
 * @LastEditTime: 2023-10-16 10:50:50
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \A5441_CMS8S6990_Master\code\FIFO.h
 */
#ifndef _FIFO_H_
#define _FIFO_H_

// 例：协议为8字节的数据串
// // #define  FrameHead  FIFO_ReadByte_Extract(&(*StructDAT), 7)    // 帧头
// // #define  COM_CRC    FIFO_ReadByte_Extract(&(*StructDAT), 1)    // 校验值
// // #define  FrameTail  FIFO_ReadByte_Extract(&(*StructDAT), 0)    // 帧尾

#define FIFO_Buffer_Size 100 // 缓存区大小

typedef struct
{
    unsigned char Buffer[FIFO_Buffer_Size]; /* 缓存区       */
    unsigned int Write;                     /* 缓存区待写指针 */
    unsigned int Read;                      /* 缓存区待读指针 */
} FIFOTypeDef;
// // // extern FIFOTypeDef Uart0_Buffer, Uart1_Buffer;
// // extern FIFOTypeDef Uart0_Buffer;
extern unsigned char RX_DataPackage[6];    // 从机发来的正确数据包

void FIFO_Byte_Push(FIFOTypeDef *StructDAT, unsigned char *Data);               // 将数据压入缓存
void FIFO_Byte_POP(FIFOTypeDef *StructDAT);                                     // 从缓存读出数据
unsigned char FIFO_ReadByte_Extract(FIFOTypeDef *StructDAT, unsigned char num); // 提取某数据


#endif
