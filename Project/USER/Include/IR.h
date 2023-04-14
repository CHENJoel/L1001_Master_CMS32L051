/*
 * @Author: your name
 * @Date: 2022-04-19 14:32:29
 * @LastEditTime: 2022-04-19 16:39:54
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \A5441_Master_CMS32L051\Project\USER\Include\IR.h
 */
#ifndef _IR_H_
#define _IR_H_
#include "IR.H"
#include "Function_Init.H"


#define IR_IO_STA  PORT_GetBit(PORT13, PIN6)

extern void IR_Decode(void); // 解码
extern void IR_Search(void); // 检码

extern unsigned int Remote_Key;


/*

    ---------------
    |             |
    |  S1     S2  |
    |             |
    |  S3     S4  |
    |             |
    |  S5     S6  |
    |             |
    |  S7     S8  |
    |             |
    |  S9     S10 |
    |             |
    |  S11    S12 |
    |             |
    ---------------


    ---------------
    3A  BA  82  02
    1A  9A  A2  22

    2A  AA  92  12
    0A  8A  B2  32
    38  B8  78  F8
    18  98  58  D8

    28  A8  68  E8
    08  88  48  C8
    30  B0  70  F0
    10  90  50  D0

    20  A0  60  E0
    ---------------




*/

#define S1_Val 0X80
#define S2_Val 0X00
#define S3_Val 0X30
#define S4_Val 0X90

#define S5_Val 0X50
#define S6_Val 0XA8
#define S7_Val 0XB0
#define S8_Val 0X68

#define S9_Val  0X70
#define S10_Val 0X28
#define S11_Val 0X60
#define S12_Val 0X10



#endif
