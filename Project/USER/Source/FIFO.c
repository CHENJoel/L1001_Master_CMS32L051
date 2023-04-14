/*
 * @Author: your name
 * @Date: 2022-02-22 13:27:18
 * @LastEditTime: 2022-06-17 17:33:46
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \A5441_CMS8S6990_Master\code\FIFO.c
 */
#include "FIFO.H"

FIFOTypeDef Uart0_Buffer, Uart1_Buffer;

/**
 * @description:一字节大小的数据压入缓存栈区
 * @param {FIFOTypeDef} *StructDAT  缓存结构体
 * @param {unsigned char} *Data     压栈数据的指针
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
 * @description: 从缓存栈区提取一字节大小的数据进行处理 或 进行多数据解码（屏蔽部分）
 * @param {FIFOTypeDef} *StructDAT  缓存结构体
 * @return {*}
 */
void FIFO_Byte_POP(FIFOTypeDef *StructDAT)
{
    unsigned char temp;
    for (temp = 0; temp < 50; temp++) // 单次限制处理（取出）50个数据
    {
        if ((*StructDAT).Read != (*StructDAT).Write) // 缓存数据未完全处理（读出）
        {
            /* USER CODE BEGIN */

            /* (*StructDAT).Read 指向当前需要处理的数据 */

            // // if (FrameTail == FrameTail_SET) // 出现帧尾
            // // {
            // //     if (== FrameHead) // 校验帧头
            // //     {
            // //     }
            // // }

            /* USER CODE END */
            if ((*StructDAT).Read < (FIFO_Buffer_Size - 1)) // 指出下次处理的数据的地址
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
 * @description: 提取“当前读数据”的前面的第 num 个Byte的数据信息
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
