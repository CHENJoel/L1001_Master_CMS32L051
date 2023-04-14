/*
 * @Author: your name
 * @Date: 2022-02-22 13:27:18
 * @LastEditTime: 2022-06-17 17:33:46
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @Description: ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \A5441_CMS8S6990_Master\code\FIFO.c
 */
#include "FIFO.H"

FIFOTypeDef Uart0_Buffer, Uart1_Buffer;

/**
 * @description:һ�ֽڴ�С������ѹ�뻺��ջ��
 * @param {FIFOTypeDef} *StructDAT  ����ṹ��
 * @param {unsigned char} *Data     ѹջ���ݵ�ָ��
 * @return {*}
 */
void FIFO_Byte_Push(FIFOTypeDef *StructDAT, unsigned char *Data)
{
    (*StructDAT).Buffer[(*StructDAT).Write] = *Data;
    if ((*StructDAT).Write < (FIFO_Buffer_Size - 1))
    {
        (*StructDAT).Write++;
    }
    else
    {
        (*StructDAT).Write = 0;
    }
}


/**
 * @description: �ӻ���ջ����ȡһ�ֽڴ�С�����ݽ��д��� �� ���ж����ݽ��루���β��֣�
 * @param {FIFOTypeDef} *StructDAT  ����ṹ��
 * @return {*}
 */
void FIFO_Byte_POP(FIFOTypeDef *StructDAT)
{
    unsigned char temp;
    for (temp = 0; temp < 50; temp++) // �������ƴ���ȡ����50������
    {
        if ((*StructDAT).Read != (*StructDAT).Write) // ��������δ��ȫ����������
        {
            /* USER CODE BEGIN */

            /* (*StructDAT).Read ָ��ǰ��Ҫ��������� */

            // // if (FrameTail == FrameTail_SET) // ����֡β
            // // {
            // //     if (== FrameHead) // У��֡ͷ
            // //     {
            // //     }
            // // }

            /* USER CODE END */
            if ((*StructDAT).Read < (FIFO_Buffer_Size - 1)) // ָ���´δ�������ݵĵ�ַ
            {
                (*StructDAT).Read++;
            }
            else
            {
                (*StructDAT).Read = 0;
            }
        }
        else
        {
            break;
        }
    }
}

/**
 * @description: ��ȡ����ǰ�����ݡ���ǰ��ĵ� num ��Byte��������Ϣ
 * @param {FIFOTypeDef} *StructDAT
 * @param {unsigned char} num
 * @return {*}
 */
unsigned char FIFO_ReadByte_Extract(FIFOTypeDef *StructDAT,unsigned char num)
{
    unsigned int temp, Addnum;
    temp = FIFO_Buffer_Size + (*StructDAT).Read - num;
    Addnum = temp % FIFO_Buffer_Size;
    return (*StructDAT).Buffer[Addnum];
}
