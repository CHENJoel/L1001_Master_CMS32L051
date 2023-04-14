/*
 * @Author: your name
 * @Date: 2021-08-20 14:47:42
 * @LastEditTime: 2022-04-19 16:38:59
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \A5423_SC8F2892\IR.C
 */

#include "Function_Init.H"
#include "IR.H"

#define IR_START_MAX   60 //引导码 标准56.3*80uS=4500uS
#define IR_START_MIN   51
#define IR_LOGIC_1_MAX 24 //逻辑1 标准21.1*80uS=1690uS
#define IR_LOGIC_1_MIN 18
#define IR_LOGIC_0_MAX 10 //逻辑0 标准7*80uS=565uS
#define IR_LOGIC_0_MIN 4

unsigned long IR_DATA_Buffer; // 完整数据包
unsigned char IR_UPDATA_Flag; // 数据更新标志位
unsigned int Remote_Key;

void IR_Decode(void); // 解码
void IR_Search(void); // 检码

/**
 * @description:   红外解码
 * @param {*}
 * @return {*}
 */

void IR_Decode(void)
{
    unsigned char IR_Data1, IR_Data2, IR_Data3, IR_Data4;
    IR_KeyVal = 0xFF;
    if (IR_UPDATA_Flag) // 发现数据更新后进行解码
    {

        IR_UPDATA_Flag = 0;
        // LED1_REV();
        IR_Data1 = IR_DATA_Buffer;       // 数据码的反码
        IR_Data2 = IR_DATA_Buffer >> 8;  // 数据码
        IR_Data3 = IR_DATA_Buffer >> 16; // 客户码2
        IR_Data4 = IR_DATA_Buffer >> 24; // 客户码1
        UART0_Send(IR_Data1);
        UART0_Send(IR_Data2);
        UART0_Send(IR_Data3);
        UART0_Send(IR_Data4);
        // printf("%d\r\n",IR_Data2);

        if (IR_Data1 + IR_Data2 == 255) // 数据反码校验
        {
            if (IR_Data3 == 0XFF && IR_Data4 == 0X00) // 客户码校验
            {
                // // // Remote_Click(&IR_Data2);

                IR_KeyVal = KeyNum_Match(&IR_Data2, &IR_KeyTable, sizeof(IR_KeyTable));
                switch (IR_Data2)
                {
                case S1_Val:
                    Rm_S1_FLAG_SetBit();
                    break;
                case S2_Val:
                    Rm_S2_FLAG_SetBit();
                    break;
                case S3_Val:
                    Rm_S3_FLAG_SetBit();
                    break;
                case S4_Val:
                    Rm_S4_FLAG_SetBit();
                    break;
                case S5_Val:
                    Rm_S5_FLAG_SetBit();
                    break;
                case S6_Val:
                    Rm_S6_FLAG_SetBit();
                    break;
                case S7_Val:
                    Rm_S7_FLAG_SetBit();
                    break;
                case S8_Val:
                    Rm_S8_FLAG_SetBit();
                    break;
                case S9_Val:
                    Rm_S9_FLAG_SetBit();
                    break;
                case S10_Val:
                    Rm_S10_FLAG_SetBit();
                    break;
                case S11_Val:
                    Rm_S11_FLAG_SetBit();
                    break;
                case S12_Val:
                    Rm_S12_FLAG_SetBit();
                    break;
                default:
                    break;
                }
            }
        }
    }
}

/**
 * @description:   红外检码
 * @param {*}
 * @return {*}
 */

void IR_Search(void)
{
    static unsigned char CNT = 0;
    static unsigned char BitCNT = 0;     // 已采集的数据Bit数
    static unsigned char Last_LEVEL;     // 上次检测电平
    static unsigned char Start_Flag;     // 数据引导头出现标志位
    static unsigned long DataBuffer = 0; // 缓存数据包
    // // LED2_REV();
    if (IR_IO_STA)
    {
        if (CNT < 0XFF) // 检测高电平脉宽
        {
            CNT++;
        }
        Last_LEVEL = 1;
        // LED1_OFF();
    }
    else
    {
        // LED1_ON();
        if (Last_LEVEL == 1) // 下降沿
        {
            if (CNT > IR_LOGIC_0_MIN)
            {
                if (CNT < IR_LOGIC_0_MAX) // 逻辑0
                {
                    if (Start_Flag) // 引导头出现，数据才有效
                    {
                        BitCNT++;
                        DataBuffer <<= 1; // 数据位写0
                        if (BitCNT >= 32) // 共32位数据（不计引导头）
                        {
                            IR_DATA_Buffer = DataBuffer; //记录完整数据缓存	等待解码
                            IR_UPDATA_Flag = 1;
                            BitCNT = 0;
                            Start_Flag = 0;
                        }
                    }
                }
                else if (CNT > IR_LOGIC_1_MIN)
                {
                    if (CNT < IR_LOGIC_1_MAX) // 逻辑1
                    {
                        if (Start_Flag) // 引导头出现，数据才有效
                        {
                            BitCNT++;
                            DataBuffer <<= 1;
                            DataBuffer |= 0x01; // 数据位写1
                            if (BitCNT >= 32)   // 共32位数据（不计引导头）
                            {
                                IR_DATA_Buffer = DataBuffer; //记录完整数据缓存	等待解码
                                IR_UPDATA_Flag = 1;
                                BitCNT = 0;
                                Start_Flag = 0;
                            }
                        }
                    }
                    else if (CNT > IR_START_MIN)
                    {
                        if (CNT < IR_START_MAX) // 出现引导头，复位数据，准备采集
                        {
                            BitCNT = 0;
                            DataBuffer = 0;
                            Start_Flag = 1;
                        }
                        else //  CNT > IR_START_MAX
                        {
                            Start_Flag = 0; // 非协议内脉宽，认为出错，丢弃数据包
                            DataBuffer = 0;
                        }
                    }
                    else //  IR_LOGIC_1_MAX < CNT < IR_START_MIN
                    {
                        Start_Flag = 0; // 非协议内脉宽，认为出错，丢弃数据包
                        DataBuffer = 0;
                    }
                }
                else //  IR_LOGIC_0_MAX < CNT < IR_LOGIC_1_MIN
                {
                    Start_Flag = 0; // 非协议内脉宽，认为出错，丢弃数据包
                    DataBuffer = 0;
                }
            }
            else // CNT < IR_LOGIC_0_MIN
            {
                Start_Flag = 0; // 非协议内脉宽，认为出错，丢弃数据包
                DataBuffer = 0;
            }
            CNT = 0;
        }
        Last_LEVEL = 0;
    }
}
