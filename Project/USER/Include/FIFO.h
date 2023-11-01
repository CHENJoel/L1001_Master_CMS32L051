/*
 * @Author: your name
 * @Date: 2022-02-22 13:26:59
 * @LastEditTime: 2023-10-16 10:50:50
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * @Description: ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \A5441_CMS8S6990_Master\code\FIFO.h
 */
#ifndef _FIFO_H_
#define _FIFO_H_

// ����Э��Ϊ8�ֽڵ����ݴ�
// // #define  FrameHead  FIFO_ReadByte_Extract(&(*StructDAT), 7)    // ֡ͷ
// // #define  COM_CRC    FIFO_ReadByte_Extract(&(*StructDAT), 1)    // У��ֵ
// // #define  FrameTail  FIFO_ReadByte_Extract(&(*StructDAT), 0)    // ֡β

#define FIFO_Buffer_Size 100 // ��������С

typedef struct
{
    unsigned char Buffer[FIFO_Buffer_Size]; /* ������       */
    unsigned int Write;                     /* ��������дָ�� */
    unsigned int Read;                      /* ����������ָ�� */
} FIFOTypeDef;
// // // extern FIFOTypeDef Uart0_Buffer, Uart1_Buffer;
// // extern FIFOTypeDef Uart0_Buffer;
extern unsigned char RX_DataPackage[6];    // �ӻ���������ȷ���ݰ�

void FIFO_Byte_Push(FIFOTypeDef *StructDAT, unsigned char *Data);               // ������ѹ�뻺��
void FIFO_Byte_POP(FIFOTypeDef *StructDAT);                                     // �ӻ����������
unsigned char FIFO_ReadByte_Extract(FIFOTypeDef *StructDAT, unsigned char num); // ��ȡĳ����


#endif
