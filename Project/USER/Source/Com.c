/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-05-25 20:19:26
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
 * @LastEditTime: 2023-10-16 10:52:42
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\Source\Com.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "Function_Init.H"
#include "Com.H"
#include "FIFO.h"

unsigned char Device_Data_Array[10];
unsigned char RX_DataPackage[6]; // 从机发来的正确数据包


void DataPackage_TX(uchar dat1, uchar dat2, uchar dat3, uchar dat4, uchar dat5, uchar dat6, uchar dat7)
{
    unsigned char tempCRC;
    tempCRC = 0;
    tempCRC += dat1;
    tempCRC += dat2;
    tempCRC += dat3;
    tempCRC += dat4;
    tempCRC += dat5;
    tempCRC += dat6;
    tempCRC += dat7;
    UART0_Send(dat1);
    UART0_Send(dat2);
    UART0_Send(dat3);
    UART0_Send(dat4);
    UART0_Send(dat5);
    UART0_Send(dat6);
    UART0_Send(dat7);
    UART0_Send(tempCRC);
}



/**
 * @description: 从缓存里提取从机发来的有效数据包
 * @param {FIFOTypeDef} *StructDAT
 * @return {*}
 */
unsigned char DataPackage_Extract(FIFOTypeDef *StructDAT)
{
    unsigned char i;
    unsigned char TempCRC;
    unsigned char Dat1, Dat2, Dat3, Dat4, Dat5, Dat6, Dat7;
    for (i = 0; i < 1000; i++) // 单次限制处理（取出）1000个数据
    {
        if ((*StructDAT).Read != (*StructDAT).Write) // 缓存数据未完全处理（读出）
        {
            /* USER CODE BEGIN */

            /* (*StructDAT).Read 指向当前需要处理的数据 */

            Dat7 = FIFO_ReadByte_Extract(&(*StructDAT), 7);
            if (Dat7 == S_HeadCOM) // 帧头校验（从机数据包）
            {
                Dat6 = FIFO_ReadByte_Extract(&(*StructDAT), 6);
                Dat5 = FIFO_ReadByte_Extract(&(*StructDAT), 5);
                Dat4 = FIFO_ReadByte_Extract(&(*StructDAT), 4);
                Dat3 = FIFO_ReadByte_Extract(&(*StructDAT), 3);
                Dat2 = FIFO_ReadByte_Extract(&(*StructDAT), 2);
                Dat1 = FIFO_ReadByte_Extract(&(*StructDAT), 1);
                TempCRC = 0;
                TempCRC += Dat7;
                TempCRC += Dat6;
                TempCRC += Dat5;
                TempCRC += Dat4;
                TempCRC += Dat3;
                TempCRC += Dat2;
                TempCRC += Dat1;
                if (FIFO_ReadByte_Extract(&(*StructDAT), 0) == TempCRC) // CRC校验
                {
                    RX_DataPackage[0] = Dat6; // 指令类型
                    RX_DataPackage[1] = Dat5;
                    RX_DataPackage[2] = Dat4;
                    RX_DataPackage[3] = Dat3;
                    RX_DataPackage[4] = Dat2;
                    RX_DataPackage[5] = Dat1;
                    return Package_Right;
                }
            }

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
            if (i == 0)
            {
                return Package_Empty; // 缓存读写地址一致，代表缓存中无新内容
            }
            return Package_Wrong; // 读完缓存的新内容，但未发现符合协议的数据包
        }
    }
}

void Uart1_Byte_POP(FIFOTypeDef *StructDAT)
{
    unsigned char temp;
    for (temp = 0; temp < 50; temp++) // 单次限制处理（取出）50个数据
    {
        if ((*StructDAT).Read != (*StructDAT).Write) // 缓存数据未完全处理（读出）
        {
            /* USER CODE BEGIN */

            /* (*StructDAT).Read 指向当前需要处理的数据 */

                // // // printf("%c\n",StructDAT->Buffer[StructDAT->Read]);

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
 * @description: 与从机握手,轮询出所有从机数量以及主副地址ID
 * @param
 * @return {*}
 */

void Slave_Handshake(void)
{
    // // // unsigned int i, j, k, m;
    // // // unsigned char temp;
    // // // unsigned char Temp_Array[Slave_num][Slave_Data_num]; // 临时存储从机设备信息
    // // // unsigned char Temp_SlaveNum = 0;                     // 临时从机信息序号
    // // // unsigned char PackageState;                          // 缓存数据状态
    // // // SlaveDevive_Num = 0;                                 // 最大从机编号复位
    // // // for (i = 0; i <= 250; i++)                           // 逐一与从机的主ID进行握手
    // // // {
    // // //     Uart0_Buffer.Read = Uart0_Buffer.Write; // 清空接收缓存中未读数据
    // // //     DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Handshake_Chief, i, Random_Generate(), Random_Generate(), Random_Generate());
    // // //     delay_5ms();                                                                   // 等待从机读取缓存
    // // //     PackageState = DataPackage_Extract(&Uart0_Buffer);                              // 读取缓存数据状态
    // // //     if ((PackageState == Package_Right) && (RX_DataPackage[0] == S_ChiefMinor_ID)) // 接收到一组从机信息数据包
    // // //     {                                                                              // 记录握手成功的从机信息
    // // //         Slave_Array[SlaveDevive_Num][0] = RX_DataPackage[1];                       // 从机主ID
    // // //         Slave_Array[SlaveDevive_Num][1] = RX_DataPackage[2];                       // 从机副ID
    // // //         SlaveDevive_Num++;
    // // //     }
    // // //     else if (PackageState != Package_Empty) // 非空数据包,但不符合数据协议，数据包有误，代表有多个从机同时占用总线发报数据，需对副ID进行握手校验
    // // //     {
    // // //         for (k = 0; k < 255; k++) // 最大支持254次修改副ID地址来握手
    // // //         {
    // // //             // 与从机的副ID进行握手
    // // //             Temp_SlaveNum = 0;
    // // //             for (m = 0; m <= 255; m++)
    // // //             {
    // // //                 // LED3_REV();
    // // //                 Uart0_Buffer.Read = Uart0_Buffer.Write; // 清空接收缓存中未读数据
    // // //                 DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Handshake_Minor, i, m, Random_Generate(), Random_Generate());
    // // //                 delay_5ms();                                                                   // 等待从机读取缓存
    // // //                 PackageState = DataPackage_Extract(&Uart0_Buffer);                              // 读取缓存数据状态
    // // //                 if ((PackageState == Package_Right) && (RX_DataPackage[0] == S_ChiefMinor_ID)) // 接收到一组从机信息数据包
    // // //                 {                                                                              // 临时记录握手成功的从机信息
    // // //                     Temp_Array[Temp_SlaveNum][0] = RX_DataPackage[1];                          // 从机主ID
    // // //                     Temp_Array[Temp_SlaveNum][1] = RX_DataPackage[2];                          // 从机副ID
    // // //                     Temp_SlaveNum++;
    // // //                 }
    // // //                 else if (PackageState != Package_Empty) // 非空数据包,但不符合数据协议，数据包有误，代表有多个从机同时占用总线发报数据，需对副ID进行握手校验
    // // //                 {
    // // //                     // 通知该主ID下的从机进行副ID强制更新
    // // //                     DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_MinorID_Refresh, i, Random_Generate(), Random_Generate(), Random_Generate());
    // // //                     delay_5ms(); // 等待从机读取缓存
    // // //                     break;       // 继续下一轮的副ID握手
    // // //                 }
    // // //                 if (m == 255)
    // // //                 {
    // // //                     // 副ID握手一圈后，未接收到错误数据，代表该主ID下的副ID握手正常！
    // // //                     for (temp = 0; temp < Temp_SlaveNum; temp++) // 正式记录握手成功的从机信息
    // // //                     {
    // // //                         Slave_Array[SlaveDevive_Num][0] = Temp_Array[temp][0]; // 从机主ID
    // // //                         Slave_Array[SlaveDevive_Num][1] = Temp_Array[temp][1]; // 从机副ID
    // // //                         SlaveDevive_Num++;
    // // //                     }
    // // //                     k = 255; // 结束副ID握手
    // // //                     break;
    // // //                 }
    // // //             }
    // // //         }
    // // //     }
    // // // }
}

/**
 * @description: 自动分配通讯ID与灯光ID
 * @param
 * @return {*}
 */
void Slave_Allocate_ID(void)
{
    // // // Poll_Device_ID();                                                 // 轮询获得设备固定ID，序列ID，设备类型
    // // // Bubble_Sort_2D(&Slave_Array, SlaveDevive_Num, Slave_Data_num, 3); // 根据序列编号进行向下排序
    // // // Post_Device_Commu_ID();                                           // 发布从机通讯ID
    // // // Post_Device_Light_ID();                                           // 发布从机灯光ID
    // // // delay_20ms();                                                     // 等待从机读取缓存
    // // // Poll_Device_Data();                                               // 轮询获得设备通讯ID,灯光ID
    // // // Mark_Device_FixedID_Data();                                       // 标记并记录各固定ID的设备数量（通讯ID）
}

/*
轮询获得设备固定ID，序列ID，设备类型
*/
void Poll_Device_ID(void)
{
    // // // uint8_t i;
    // // // uint8_t PackageState;                 // 缓存数据状态
    // // // for (i = 0; i < SlaveDevive_Num; i++) // 轮询所有ID信息
    // // // {
    // // //     Uart0_Buffer.Read = Uart0_Buffer.Write; // 清空接收缓存中未读数据
    // // //     Check_Device_ID(Slave_Array[i][0], Slave_Array[i][1]);
    // // //     delay_10ms();                                                              // 等待从机读取缓存
    // // //     PackageState = DataPackage_Extract(&Uart0_Buffer);                          // 读取缓存数据状态
    // // //     if ((PackageState == Package_Right) && (RX_DataPackage[0] == S_Device_ID)) // 接收到一组从机信息数据包
    // // //     {
    // // //         if (Slave_Array[i][0] == RX_DataPackage[1] && Slave_Array[i][1] == RX_DataPackage[2]) // 主副ID校验
    // // //         {
    // // //             Slave_Array[i][2] = RX_DataPackage[3]; // 固定ID
    // // //             Slave_Array[i][3] = RX_DataPackage[4]; // 序列ID
    // // //             Slave_Array[i][4] = RX_DataPackage[5]; // 设备类型
    // // //         }
    // // //     }
    // // // }
}
/*
轮询获得设备通讯ID,灯光ID
*/
void Poll_Device_Data(void)
{
    // // // uint8_t i;
    // // // uint8_t PackageState;                 // 缓存数据状态
    // // // for (i = 0; i < SlaveDevive_Num; i++) // 轮询所有ID信息
    // // // {
    // // //     Uart0_Buffer.Read = Uart0_Buffer.Write; // 清空接收缓存中未读数据
    // // //     Check_Device_Data(Slave_Array[i][0], Slave_Array[i][1]);
    // // //     delay_10ms();                                                                // 等待从机读取缓存
    // // //     PackageState = DataPackage_Extract(&Uart0_Buffer);                            // 读取缓存数据状态
    // // //     if ((PackageState == Package_Right) && (RX_DataPackage[0] == S_Device_Data)) // 接收到一组从机信息数据包
    // // //     {
    // // //         if (Slave_Array[i][0] == RX_DataPackage[1] && Slave_Array[i][1] == RX_DataPackage[2]) // 主副ID校验
    // // //         {
    // // //             Slave_Array[i][5] = RX_DataPackage[3]; // 通讯ID
    // // //             Slave_Array[i][6] = RX_DataPackage[4]; // 灯光ID
    // // //         }
    // // //     }
    // // // }
}

/*
发布从机通讯ID
*/
void Post_Device_Commu_ID(void)
{
    // // // uint8_t i;
    // // // for (i = 0; i < SlaveDevive_Num; i++) // 向下发布从机通讯ID
    // // // {
    // // //     Set_CommuID(Slave_Array[i][0], Slave_Array[i][1], 0x30 + i);
    // // //     Set_CommuID(Slave_Array[i][0], Slave_Array[i][1], 0x30 + i);
    // // //     delay_10ms(); // 等待从机读取缓存
    // // // }
}

/*
  发布从机灯光ID
*/
void Post_Device_Light_ID(void)
{
    // // // uint8_t i, j;
    // // // uint8_t temp;
    // // // temp = Slave_Array[0][3];
    // // // j = 0;
    // // // for (i = 0; i < SlaveDevive_Num; i++) // 向下发布从机灯光ID
    // // // {
    // // //     if (Slave_Array[i][3] != temp)
    // // //     {
    // // //         j++;
    // // //     }
    // // //     Set_LightID(Slave_Array[i][0], Slave_Array[i][1], j);
    // // //     Set_LightID(Slave_Array[i][0], Slave_Array[i][1], j);
    // // //     temp = Slave_Array[i][3];
    // // //     delay_10ms(); // 等待从机读取缓存
    // // // }
    // // // ModuleLight_Num = j + 1;
}
/*
  发布从机序列ID
*/
void Post_Device_Series_ID(void)
{
    // // // uint8_t i, j;
    // // // for (i = 0; i < SlaveDevive_Num; i++) // 向下发布从机灯光ID
    // // // {
    // // //     Set_SeriesNum(Slave_Array[i][0], Slave_Array[i][1], Slave_Array[i][8]);
    // // //     Set_SeriesNum(Slave_Array[i][0], Slave_Array[i][1], Slave_Array[i][8]);
    // // //     delay_10ms(); // 等待从机读取缓存
    // // // }
}

/*
    标记并记录各固定ID的设备数量（通讯ID）
*/
void Mark_Device_FixedID_Data(void)
{
    // // // // // uint8_t i, j, k, m, n;
    // // // // // uint8_t temp;
    // // // // // /*筛选出同一固定ID的设备数量*/
    // // // // // for (i = 0; i < SlaveDevive_Num; i++) // 轮询所有ID信息
    // // // // // {
    // // // // //     temp = Slave_Array[i][2];
    // // // // //     m = 0;
    // // // // //     for (j = 0; j < SlaveDevive_Num; j++) // 轮询所有ID信息
    // // // // //     {
    // // // // //         if (Slave_Array[j][2] == temp) // 筛选出同一固定ID的设备数量
    // // // // //         {
    // // // // //             m++;
    // // // // //         }
    // // // // //     }
    // // // // //     n = 0;
    // // // // //     for (j = 0; j < SlaveDevive_Num; j++) // 轮询所有ID信息
    // // // // //     {
    // // // // //         if (Slave_Array[j][2] == temp)
    // // // // //         {
    // // // // //             n++;
    // // // // //             Slave_Array[j][7] = m << 4; // 高四位标记为该固定ID的总设备数
    // // // // //             Slave_Array[j][7] |= n;     // 低四位标记为该固定ID的标号
    // // // // //         }
    // // // // //     }
    // // // // // }
    // // // // // /*记录同一固定ID设备的数量、通讯ID*/
    // // // // // for (i = 0; i < 8; i++)
    // // // // // {
    // // // // //     FixedID_DeviceData[i][1] = 0; // 数据复位
    // // // // //     m = 0;
    // // // // //     for (j = 0; j < SlaveDevive_Num; j++)
    // // // // //     {
    // // // // //         if (Slave_Array[j][2] == FixedID_DeviceData[i][0]) // 存在相对应的设备类型
    // // // // //         {
    // // // // //             FixedID_DeviceData[i][1] = Slave_Array[j][7] >> 4; // 标记拥有该固定ID的设备数量
    // // // // //             FixedID_DeviceData[i][2 + m] = Slave_Array[j][5];  // 拥有该固定ID的设备通讯ID
    // // // // //             m++;
    // // // // //         }
    // // // // //     }
    // // // // // }
}













/**************************************** 新协议 ****************************************/









/**
 * @description: 与从机握手,得出唯一地址
 * @param
 * @return {*}
 */

void Get_Slave_ID(void)
{
    // // // uint16_t i, j;
    // // // uint8_t Temp_Array[16];     // 设备id
    // // // uint8_t Temp_DeviceNum = 0; // 设备数量
    // // // uint8_t PackageState;       // 缓存数据状态
    // // // for (i = 0; i <= 255; i++)  // 最大执行256次冲突处理
    // // // {
    // // //     Temp_DeviceNum = 0;
    // // //     for (j = 0; j <= 255; j++) // 轮询所有id
    // // //     {
    // // //         Uart0_Buffer.Read = Uart0_Buffer.Write;                                    // 清空接收缓存中未读数据
    // // //         DataTx_Master_Check_ID(j);                                                 // 检测此id
    // // //         delay_5ms();                                                               // 等待从机读取缓存
    // // //         PackageState = DataPackage_Extract(&Uart0_Buffer);                         // 读取缓存数据状态
    // // //         if ((PackageState == Package_Right) && (RX_DataPackage[0] == S_Return_ID) && (RX_DataPackage[1] == j)) // 接收到一组从机信息数据包
    // // //         {
    // // //             Temp_Array[Temp_DeviceNum] = RX_DataPackage[1]; // 标记从机ID
    // // //             Temp_DeviceNum++;                               // 标记从机数量
    // // //         }
    // // //         else if (PackageState != Package_Empty) // 非空数据包,但不符合数据协议，数据包有误，代表有多个从机同时占用总线发报数据，即出现ID冲突
    // // //         {
    // // //             DataTx_Refresh_ID(); // 要求从机更新id
    // // //             delay_5ms();         // 等待从机读取缓存
    // // //             break;               // 重新循环轮询
    // // //         }
    // // //         if (j == 255) // 内循环轮询结束，说明此前未发现ID冲突
    // // //         {
    // // //             TangramDevice.Device_sum = Temp_DeviceNum; // 存储设备数量
    // // //             for (i = 0; i < Temp_DeviceNum; i++)
    // // //             {
    // // //                 TangramDevice.SlaveData[i].ID = Temp_Array[i]; // 存储设备id
    // // //             }
    // // //             i = 256; // 退出外循环
    // // //         }
    // // //     }
    // // // }
}

// // // // // // void Get_Slave_Coord(void)
// // // // // // {
// // // // // //     uint8_t i;
// // // // // //     uint8_t PackageState; // 缓存数据状态
// // // // // //     for (i = 0; i < TangramDevice.Device_sum; i++)
// // // // // //     {
// // // // // //         Uart0_Buffer.Read = Uart0_Buffer.Write;                      // 清空接收缓存中未读数据
// // // // // //         DataTx_Master_Check_Ligntnum(TangramDevice.SlaveData[i].ID); // 查询此灯光编号
// // // // // //         delay_5ms();
// // // // // //         PackageState = DataPackage_Extract(&Uart0_Buffer);                                                                                       // 读取缓存数据状态
// // // // // //         if ((PackageState == Package_Right) && (RX_DataPackage[0] == S_Return_LightNum) && (RX_DataPackage[1] == TangramDevice.SlaveData[i].ID)) // 接收到一组从机信息数据包
// // // // // //         {
// // // // // //             TangramDevice.SlaveData[i].Lightnum = RX_DataPackage[2];
// // // // // //         }
// // // // // //         else
// // // // // //         {
// // // // // //             TangramDevice.SlaveData[i].Lightnum = 0;
// // // // // //         }
// // // // // //     }
// // // // // // }

// // // // // // void Set_Slave_Coord(void)
// // // // // // {
// // // // // //     uint8_t i;
// // // // // //     for (i = 0; i < TangramDevice.Device_sum; i++)
// // // // // //     {
// // // // // //         DataTx_Master_Set_Ligntnum(TangramDevice.SlaveData[i].ID, TangramDevice.SlaveData[i].Lightnum);
// // // // // //         DataTx_Master_Set_Ligntnum(TangramDevice.SlaveData[i].ID, TangramDevice.SlaveData[i].Lightnum);
// // // // // //         DataTx_Master_Set_Ligntnum(TangramDevice.SlaveData[i].ID, TangramDevice.SlaveData[i].Lightnum);
// // // // // //         delay_5ms();
// // // // // //     }
// // // // // // }

/* 获取坐标 */
void Get_Slave_Coord(void)
{
    // // // uint8_t i;
    // // // uint8_t PackageState; // 缓存数据状态
    // // // for (i = 0; i < TangramDevice.Device_sum; i++)
    // // // {
    // // //     Uart0_Buffer.Read = Uart0_Buffer.Write;                   // 清空接收缓存中未读数据
    // // //     DataTx_Master_Check_Coord(TangramDevice.SlaveData[i].ID); // 获取坐标
    // // //     delay_5ms();
    // // //     PackageState = DataPackage_Extract(&Uart0_Buffer);                                                                                       // 读取缓存数据状态
    // // //     if ((PackageState == Package_Right) && (RX_DataPackage[0] == S_RETURN_Coord) && (RX_DataPackage[1] == TangramDevice.SlaveData[i].ID)) // 接收到一组从机信息数据包
    // // //     {
    // // //         TangramDevice.SlaveData[i].Coord.X = RX_DataPackage[2];
    // // //         TangramDevice.SlaveData[i].Coord.Y = RX_DataPackage[3];
    // // //     }
    // // //     else
    // // //     {
    // // //         TangramDevice.SlaveData[i].Coord.X = 0;
    // // //         TangramDevice.SlaveData[i].Coord.Y = 0;
    // // //     }
    // // // }
}

/* 设置坐标 */
void Set_Slave_Coord(void)
{
    // // uint8_t i;
    // // for (i = 0; i < TangramDevice.Device_sum; i++)
    // // {
    // //     DataTx_Master_Set_Coord(TangramDevice.SlaveData[i].ID, TangramDevice.SlaveData[i].Coord.X, TangramDevice.SlaveData[i].Coord.Y);
    // //     // // // // // // DataTx_Master_Set_Coord(TangramDevice.SlaveData[i].ID, TangramDevice.SlaveData[i].Coord.X, TangramDevice.SlaveData[i].Coord.Y);
    // //     // // // // // // DataTx_Master_Set_Coord(TangramDevice.SlaveData[i].ID, TangramDevice.SlaveData[i].Coord.X, TangramDevice.SlaveData[i].Coord.Y);
    // //     delay_5ms();
    // // }
}

/* 获取角度 */
void Get_Slave_Angle(void)
{
    // // // uint8_t i;
    // // // uint8_t PackageState; // 缓存数据状态
    // // // for (i = 0; i < TangramDevice.Device_sum; i++)
    // // // {
    // // //     Uart0_Buffer.Read = Uart0_Buffer.Write;                   // 清空接收缓存中未读数据
    // // //     DataTx_Master_Check_Angle(TangramDevice.SlaveData[i].ID); // 获取角度
    // // //     delay_5ms();
    // // //     PackageState = DataPackage_Extract(&Uart0_Buffer);                                                                                       // 读取缓存数据状态
    // // //     if ((PackageState == Package_Right) && (RX_DataPackage[0] == S_RETURN_Angle) && (RX_DataPackage[1] == TangramDevice.SlaveData[i].ID)) // 接收到一组从机信息数据包
    // // //     {
    // // //         TangramDevice.SlaveData[i].Angle = RX_DataPackage[2];
    // // //     }
    // // //     else
    // // //     {
    // // //         TangramDevice.SlaveData[i].Angle = 0;
    // // //     }
    // // // }
}

/* 设置角度 */
void Set_Slave_Angle(void)
{
    // // uint8_t i;
    // // for (i = 0; i < TangramDevice.Device_sum; i++)
    // // {
    // //     DataTx_Master_Set_Angle(TangramDevice.SlaveData[i].ID, TangramDevice.SlaveData[i].Angle);
    // //     delay_5ms();
    // // }
}



void Slave_DataInit(void)
{
    uint8_t i;
    // Get_Slave_ID();    // 获取从机id信息
    // Get_Slave_Coord(); // 获取从机坐标
    // Get_Slave_Angle(); /* 获取角度 */

    // // // Runingnum_Bubble_Sort(); // 灯光排序，计算出运行编号

    // for (i = 0; i < TangramDevice.Device_sum; i++)
    // {
    //     // TangramDevice.SlaveData[i].Container.data1 = 0xFF; // 临时灯光序号
    //     TangramDevice.SlaveData[i].Coord.X = i + 1;        // error：模拟坐标数据
    //     TangramDevice.SlaveData[i].Coord.Y = i + 1;
    // }
    /**************/
    // 茶室七巧板
    // // TangramDevice.SlaveData[0].ID = 0x45;
    // // TangramDevice.SlaveData[0].Coord.X = 0;
    // // TangramDevice.SlaveData[0].Coord.Y = 0;

    // // TangramDevice.SlaveData[1].ID = 0x84;
    // // TangramDevice.SlaveData[1].Coord.X = 1;
    // // TangramDevice.SlaveData[1].Coord.Y = 1;

    // // TangramDevice.SlaveData[2].ID = 0xA9;
    // // TangramDevice.SlaveData[2].Coord.X = 2;
    // // TangramDevice.SlaveData[2].Coord.Y = 2;

    // // TangramDevice.SlaveData[3].ID = 0x1F;
    // // TangramDevice.SlaveData[3].Coord.X = 3;
    // // TangramDevice.SlaveData[3].Coord.Y = 3;

    // // TangramDevice.SlaveData[4].ID = 0xE2;
    // // TangramDevice.SlaveData[4].Coord.X = 4;
    // // TangramDevice.SlaveData[4].Coord.Y = 4;

    // // TangramDevice.SlaveData[5].ID = 0x75;
    // // TangramDevice.SlaveData[5].Coord.X = 5;
    // // TangramDevice.SlaveData[5].Coord.Y = 5;

    // // TangramDevice.SlaveData[6].ID = 0xB3;   //48
    // // TangramDevice.SlaveData[6].Coord.X = 6;
    // // TangramDevice.SlaveData[6].Coord.Y = 6;

    // // TangramDevice.SlaveData[7].ID = 0xC3;
    // // TangramDevice.SlaveData[7].Coord.X = 7;
    // // TangramDevice.SlaveData[7].Coord.Y = 7;

    // // TangramDevice.Device_sum = 8;
    /*********************************/
    TangramDevice.SlaveData[0].ID = 0x06;
    TangramDevice.SlaveData[0].Coord.X = 3;
    TangramDevice.SlaveData[0].Coord.Y = 3;

    TangramDevice.SlaveData[1].ID = 0x13;
    TangramDevice.SlaveData[1].Coord.X = 2;
    TangramDevice.SlaveData[1].Coord.Y = 2;

    TangramDevice.SlaveData[2].ID = 0x2B;
    TangramDevice.SlaveData[2].Coord.X = 1;
    TangramDevice.SlaveData[2].Coord.Y = 1;

    TangramDevice.SlaveData[3].ID = 0x9C;
    TangramDevice.SlaveData[3].Coord.X = 0;
    TangramDevice.SlaveData[3].Coord.Y = 0;
    TangramDevice.Device_sum = 4;
    /*******************/
    // // // // // // // TangramDevice.Device_sum = 10;
    // // // // // // // for (i = 0; i < TangramDevice.Device_sum; i++)
    // // // // // // // {
    // // // // // // //     TangramDevice.SlaveData[i].ID = Random_Generate();
    // // // // // // //     TangramDevice.SlaveData[i].Coord.X = Random_Generate() / 16;
    // // // // // // //     TangramDevice.SlaveData[i].Coord.Y = Random_Generate() / 16;
    // // // // // // // }

    printf("\r\n\r\n\r\n\r\n\r\n\r\n");
    for (i = 0; i < TangramDevice.Device_sum; i++)
    {
        printf("id:%d X:%d Y:%d ,%d\r",TangramDevice.SlaveData[i].ID,TangramDevice.SlaveData[i].Coord.X,TangramDevice.SlaveData[i].Coord.Y,TangramDevice.SlaveData[i].Angle);
    }
    printf("\r\n\r\n");
}


/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/


void slave_data_debug(void) // 生成虚假模组数据
{
    uint8_t i;
    TangramDevice.Device_sum = 4;
    for (i = 0; i < TangramDevice.Device_sum; i++)
    {
        TangramDevice.SlaveData[i].ID = 0xE0 + i;
        TangramDevice.SlaveData[i].DeviceType = i;
        TangramDevice.SlaveData[i].Coord.X = i + 1; // error：模拟坐标数据
        TangramDevice.SlaveData[i].Coord.Y = i + 2;
    }

    // // // // // // // TangramDevice.Device_sum = 10;
    // // // // // // // for (i = 0; i < TangramDevice.Device_sum; i++)
    // // // // // // // {
    // // // // // // //     TangramDevice.SlaveData[i].ID = Random_Generate();
    // // // // // // //     TangramDevice.SlaveData[i].Coord.X = Random_Generate() / 16;
    // // // // // // //     TangramDevice.SlaveData[i].Coord.Y = Random_Generate() / 16;
    // // // // // // // }

    printf("\r\n\r\n\r\n\r\n\r\n\r\n");
     printf(" fake slave data\r\n");
    for (i = 0; i < TangramDevice.Device_sum; i++)
    {
        printf("id:%2x T:%d [%2d,%2d]\r",TangramDevice.SlaveData[i].ID,TangramDevice.SlaveData[i].DeviceType,TangramDevice.SlaveData[i].Coord.X,TangramDevice.SlaveData[i].Coord.Y);
    }
    printf("\r\n\r\n");
}

uint8_t CRC_Calculate(uint8_t *sur, uint8_t len) // 返回CRC校验
{
    uint8_t i;
    uint8_t sur_CRC = 0;
    for (i = 0; i < len; i++)
    {
        // // // // // // printf("sur:%x  ",*sur);
        sur_CRC += *sur++;
        // // // // // // printf("CRC: %x\r",sur_CRC);
    }
    // // // // // // // // printf("\r\n CRC: %x\r",sur_CRC);
    return sur_CRC;
}

/**************************************************************************************************/
void Upload_LightMessage(void)  // 上传灯组信息
{
    uint8_t protocol_buffer[69];
    uint8_t *p_buffer;
    uint8_t protocol_length;
    uint8_t i;
    protocol_length = 4 + TangramDevice.Device_sum * 4;
    p_buffer = protocol_buffer;
    *p_buffer = APP_PROTOCOL_HEADER;        // 帧头
    *++p_buffer = protocol_length;          // 数据长度
    *++p_buffer = REPORT_LIGHT_MESSAGE;     // 指令类型
    *++p_buffer = TangramDevice.Device_sum; // 灯组设备数量

    if (TangramDevice.Device_sum)
    {
        for (i = 0; i < TangramDevice.Device_sum; i++)
        {
            *++p_buffer = TangramDevice.SlaveData[i].ID;         // 灯组设备ID
            *++p_buffer = TangramDevice.SlaveData[i].DeviceType; // 灯组设备类型
            *++p_buffer = TangramDevice.SlaveData[i].Coord.X;    // X坐标
            *++p_buffer = TangramDevice.SlaveData[i].Coord.Y;    // Y坐标
        }
    }
    *++p_buffer = CRC_Calculate(protocol_buffer, protocol_length);               // 校验和
    mcu_dp_raw_update(DPID_USER_PROTOCOL, protocol_buffer, protocol_length + 1); // RAW型数据上报;
    Uart0_Send_String(protocol_buffer, protocol_length + 1);
}

void Download_LightCoord(uint8_t *sur, uint16_t len) // 下载灯组坐标信息
{
    uint8_t i, j;
    uint8_t temp;
    uint8_t *p;
    uint8_t num;
    len -= 4; // 减去指令字段，剩下有用字节数
    sur += 3; // 帧头 长度 指令
    if (len % 3)
    {
        return;
    }
    num = len / 3;
    if (num > 16)
    {
        return;
    }
    for (j = 0; j < num; j++)
    {
        p = sur + j * 3;
        for (i = 0; i < TangramDevice.Device_sum; i++)
        {
            if (*p == TangramDevice.SlaveData[i].ID) // 轮询出相对应的ID
            {
                TangramDevice.SlaveData[i].Coord.X = *(p + 1);
                TangramDevice.SlaveData[i].Coord.Y = *(p + 2);
                Set_Slave_Coord();
                // printf("id:%2x %2d,%2d]\n", TangramDevice.SlaveData[i].ID, *(p + 1), *(p + 2));
            }
        }
    }
}
/**************************************************************************************************/
void Upload_EffectMessage(uint8_t num) // 上传灯效信息
{
    uint8_t protocol_buffer[91];
    uint8_t *p_buffer;
    uint8_t protocol_length;
    uint8_t i;
    EF_para_data_TypeDef EFpara; // 参数信息
    color_group_TypeDef EFcolor; // 色表
    id_group_TypeDef EFid;       // id信息
    memset(&EFid, 0, sizeof(EFid));
    memset(&EFpara, 0, sizeof(EFpara));
    memset(&EFcolor, 0, sizeof(EFcolor));
    if (num > 63)
    {
        return;
    }
    Read_UserEF_Paradata(num, &EFpara);
    Read_UserEF_Colordata(num, &EFcolor);
    Read_UserEF_IDdata(num, &EFid);
    if (EFpara.color_sum > 15) // 数据错误
    {
        EFpara.color_sum = 0;
    }
    if (EFpara.motion == MOTION_STATIC)
    {
        protocol_length = 10 + EFpara.color_sum * 5; // 静态灯效包含id信息
    }
    else
    {
        protocol_length = 10 + EFpara.color_sum * 4;
    }
    p_buffer = &protocol_buffer;
    *p_buffer = APP_PROTOCOL_HEADER;     // 帧头
    *++p_buffer = protocol_length;       // 数据长度
    *++p_buffer = REPORT_EFFECT_MESSAGE; // 指令类型
    *++p_buffer = num;                   // 灯效编号
    *++p_buffer = EFpara.brightness;
    *++p_buffer = EFpara.color_sum;
    *++p_buffer = EFpara.motion;
    *++p_buffer = EFpara.move;
    *++p_buffer = EFpara.Mode;
    *++p_buffer = EFpara.speed;
    for (i = 0; i < EFpara.color_sum; i++)
    {
        *++p_buffer = EFcolor.color[i].R;
        *++p_buffer = EFcolor.color[i].G;
        *++p_buffer = EFcolor.color[i].B;
        *++p_buffer = EFcolor.color[i].W;
    }
    if (EFpara.motion == MOTION_STATIC)
    {
        for (i = 0; i < EFpara.color_sum; i++)
        {
            *++p_buffer = EFid.id_data[i];
        }
    }

    *++p_buffer = CRC_Calculate(protocol_buffer, protocol_length);               // 校验和
    mcu_dp_raw_update(DPID_USER_PROTOCOL, protocol_buffer, protocol_length + 1); // RAW型数据上报;
    Uart0_Send_String(protocol_buffer, protocol_length + 1);
}
void Download_EffectMessage(uint8_t *sur, uint16_t len) // 下载灯效信息
{
    uint8_t i;
    uint8_t *p;
    uint8_t ef_num;              // 灯效编号
    EF_para_data_TypeDef EFpara; // 参数信息
    color_group_TypeDef EFcolor; // 色表
    id_group_TypeDef EFid;       // id信息
    // // // // // // // // // // // // p = &EFpara;
    // // // // // // // // // // // // for (i = 0; i < sizeof(EFpara); i++) // 缓存清零
    // // // // // // // // // // // // {
    // // // // // // // // // // // //     *p++ = 0;
    // // // // // // // // // // // // }
    // // // // // // // // // // // // p = &EFcolor;
    // // // // // // // // // // // // for (i = 0; i < sizeof(EFcolor); i++) // 缓存清零
    // // // // // // // // // // // // {
    // // // // // // // // // // // //     *p++ = 0;
    // // // // // // // // // // // // }
    // // // // // // // // // // // // p = &EFid;
    // // // // // // // // // // // // for (i = 0; i < sizeof(EFid); i++) // 缓存清零
    // // // // // // // // // // // // {
    // // // // // // // // // // // //     *p++ = 0;
    // // // // // // // // // // // // }
    memset(&EFid, 0, sizeof(EFid));
    memset(&EFpara, 0, sizeof(EFpara));
    memset(&EFcolor, 0, sizeof(EFcolor));
    p = sur + 3;
    ef_num = *p;
    EFpara.brightness = *++p;
    EFpara.color_sum = *++p;
    EFpara.motion = *++p;
    EFpara.move = *++p;
    EFpara.Mode = *++p;
    EFpara.speed = *++p;
    if (ef_num > 63)
    {
        printf("ef_num error\r");
        return;
    }
    if (EFpara.color_sum > 15 || EFpara.color_sum == 0)
    {
        printf("color_sum error\r");
        return;
    }
    if (EFpara.motion > 7)
    {
        printf("motion error\r");
        return;
    }
    if (EFpara.move > 5)
    {
        printf("move error\r");
        return;
    }
    if (EFpara.Mode > 1)
    {
        printf("Mode error\r");
        return;
    }
    if (EFpara.motion == MOTION_STATIC)
    {
        if (len != (11 + EFpara.color_sum * 5))
        {
            printf("len error\r");
            return;
        }
    }
    else
    {
        if (len != (11 + EFpara.color_sum * 4))
        {
            printf("len error\r");
            return;
        }
    }

    p = sur + 10;
    for (i = 0; i < EFpara.color_sum; i++)
    {
        EFcolor.color[i].R = *p++;
        EFcolor.color[i].G = *p++;
        EFcolor.color[i].B = *p++;
        EFcolor.color[i].W = *p++;
    }
    if (EFpara.motion == MOTION_STATIC)
    {
        p = sur + 10 + EFpara.color_sum * 4;
        for (i = 0; i < EFpara.color_sum; i++)
        {
            EFid.id_data[i] = *p++;
        }
    }
    Edit_UserEF_IDdata(ef_num, &EFid);
    Edit_UserEF_Paradata(ef_num, &EFpara);
    Edit_UserEF_Colordata(ef_num, &EFcolor);

    Printf_EF_data(ef_num);
}
/**************************************************************************************************/
void Upload_PlayList(uint8_t num) // 上传播放列表
{
    uint8_t protocol_buffer[72];
    uint8_t *p_buffer;
    uint8_t protocol_length;
    uint8_t i;
    playlist_TypeDef list;
    if (num > 19)
    {
        return;
    }
    Read_Playlist(num, &list);
    if (list.list_sum > 59)
    {
        Clear_Playlist(num);
        Read_Playlist(num, &list);
    }
    protocol_length = 8 + list.list_sum;
    p_buffer = &protocol_buffer;
    *p_buffer = APP_PROTOCOL_HEADER; // 帧头
    *++p_buffer = protocol_length;   // 数据长度
    *++p_buffer = REPORT_PLAYLIST;   // 指令类型
    *++p_buffer = num;               // 列表编号
    *++p_buffer = list.play_mode;    // 播放模式
    *++p_buffer = list.switch_hour;  // 切换时间
    *++p_buffer = list.switch_min;   // 切换时间
    *++p_buffer = list.list_sum;     // 列表灯效数量
    for (i = 0; i < list.list_sum; i++)
    {
        *++p_buffer = list.list_table[i];
    }
    *++p_buffer = CRC_Calculate(protocol_buffer, protocol_length);               // 校验和
    mcu_dp_raw_update(DPID_USER_PROTOCOL, protocol_buffer, protocol_length + 1); // RAW型数据上报;
    Uart0_Send_String(protocol_buffer, protocol_length + 1);
}

void Download_PlayList(uint8_t *sur, uint16_t len) // 下载播放列表
{
    uint8_t i, j;
    uint8_t temp;
    uint8_t *p;
    uint8_t num;
    playlist_TypeDef playlist;
    memset(&playlist, 0, sizeof(playlist));
    p = sur + 3;
    num = *p; // 列表编号
    playlist.play_mode = *++p;
    playlist.switch_hour = *++p;
    playlist.switch_min = *++p;
    playlist.list_sum = *++p;
    if (num > 19)
    {
        return;
    }
    if (playlist.list_sum > 59) // 灯效数量
    {
        return;
    }
    for (i = 0; i < playlist.list_sum; i++)
    {
        playlist.list_table[i] = *++p;
    }
    Edit_Playlist(num,&playlist);
}
/**************************************************************************************************/

void Upload_Schedule(uint8_t num) // 上传定时任务
{
    uint8_t protocol_buffer[11];
    uint8_t *p_buffer;
    uint8_t protocol_length;
    uint8_t i;
    schedule_TypeDef schedule;
    if (num >= 64)
    {
        return;
    }
    Read_Schedule(num, &schedule);
    protocol_length = 10;
    p_buffer = &protocol_buffer;
    *p_buffer = APP_PROTOCOL_HEADER; // 帧头
    *++p_buffer = protocol_length;   // 数据长度
    *++p_buffer = REPORT_SCHEDULE;   // 指令类型
    *++p_buffer = num;
    *++p_buffer = schedule.Action;
    *++p_buffer = schedule.Exection_Hou;
    *++p_buffer = schedule.Exection_Min;
    *++p_buffer = schedule.Duration;
    *++p_buffer = schedule.Brightness;
    *++p_buffer = schedule.Repeat_Week;
    *++p_buffer = CRC_Calculate(protocol_buffer, protocol_length);
    mcu_dp_raw_update(DPID_USER_PROTOCOL, protocol_buffer, protocol_length + 1); // RAW型数据上报;
    Uart0_Send_String(protocol_buffer, protocol_length + 1);
}

void Download_Schedule(uint8_t *sur, uint16_t len) // 下载定时任务
{
    uint8_t *p;
    uint8_t num;
    schedule_TypeDef schedule;
    memset(&schedule, 0, sizeof(schedule));
    p = sur + 3;
    num = *p; // 定时任务编号
    schedule.Action = *++p;
    schedule.Exection_Hou = *++p;
    schedule.Exection_Min = *++p;
    schedule.Duration = *++p;
    schedule.Brightness = *++p;
    schedule.Repeat_Week = *++p;
    Edit_Schedule(num, &schedule);
}

/**************************************************************************************************/
void Upload_PlayingState(void) // 上报播放状态
{
    uint8_t protocol_buffer[9];
    protocol_buffer[0] = APP_PROTOCOL_HEADER;       // 帧头
    protocol_buffer[1] = 8;                         // 数据长度
    protocol_buffer[2] = REPORT_PLAYSTATE;          // 指令类型
    protocol_buffer[3] = PlayingState.on_sta;       // bit0 （0暂停/1开始），其他位保留
    protocol_buffer[4] = PlayingState.effect_num;   // 当前灯效编号
    protocol_buffer[5] = PlayingState.playlist_num; // 列表播放编号（值255代表当前是非列表播放）
    protocol_buffer[6] = PlayingState.RESERVED[0];  // 保留
    protocol_buffer[7] = PlayingState.RESERVED[1];  // 保留
    protocol_buffer[8] = CRC_Calculate(protocol_buffer, 8);
    mcu_dp_raw_update(DPID_USER_PROTOCOL, protocol_buffer, 9); // RAW型数据上报;
    Uart0_Send_String(protocol_buffer, 9);
}
void Download_PlayingState(uint8_t *sur, uint16_t len) // 下载播放任务
{
    uint8_t *p;
    schedule_TypeDef schedule;
    memset(&schedule, 0, sizeof(schedule));
    p = sur + 3;
    PlayingState.on_sta=*p;
    PlayingState.effect_num=*++p;
    PlayingState.playlist_num=*++p;
    PlayingState.RESERVED[0]=*++p;
    PlayingState.RESERVED[1]=*++p;
}


/**************************************************************************************************/
void Upload_StateMessage(uint8_t cmd, uint8_t sta) // 上报状态
{
    uint8_t protocol_buffer[5];
    protocol_buffer[0] = APP_PROTOCOL_HEADER;               // 帧头
    protocol_buffer[1] = 4;                                 // 数据长度
    protocol_buffer[2] = cmd;                               // 指令
    protocol_buffer[3] = sta;                               // 状态
    protocol_buffer[4] = CRC_Calculate(protocol_buffer, 4); // 校验
    Uart0_Send_String(protocol_buffer, 5);
}
void Protocol_RGBW_Output(uint8_t *sur, uint16_t len) // 解析出灯组输出颜色
{
    uint8_t i, j;
    uint8_t temp;
    uint8_t *p;
    uint8_t num;
    len--; // 减去一个校验字节，剩下有用字节数
    // // Uart0_Send_String(sur, len);
    if (len % 5)
    {
        return;
    }
    num = len / 5;
    if (num > 16)
    {
        return;
    }

    for (j = 0; j < num; j++)
    {
        p = sur + j * 5;
        for (i = 0; i < TangramDevice.Device_sum; i++)
        {
            if (*p == TangramDevice.SlaveData[i].ID) // 轮询出相对应的ID
            {
                TangramDevice.SlaveData[i].Color.R = *(p + 1);
                TangramDevice.SlaveData[i].Color.G = *(p + 2);
                TangramDevice.SlaveData[i].Color.B = *(p + 3);
                TangramDevice.SlaveData[i].Color.W = *(p + 4);
                printf("ID:%d R %d G %d B %d W  %d\r\n", TangramDevice.SlaveData[i].ID, *(p + 1), *(p + 2), * (p + 3), *(p + 4));
            }
        }
    }
}


void RAW_processing(uint8_t *sur, uint16_t len) // 透传上报
{
    uint8_t crc;
    // LED2_REV();
    // Uart0_Send_String(sur, len);
    crc = CRC_Calculate(sur, len - 1);
    if (crc == *(sur + len - 1) && *sur == APP_PROTOCOL_HEADER) // 校验
    {
        // LED2_REV();
        switch (*(sur + 2))
        {
        case CHECK_LIGHT_MESSAGE:
            Upload_LightMessage(); // 查询灯组信息
            break;
        case SET_LIGHT_COORDINATE:
            Download_LightCoord(sur, len); // 下载灯组坐标信息
            printf("Download_LightCoord\r");
            break;
        case CHECK_EFFECT_MESSAGE:
            Upload_EffectMessage(*(sur + 3)); // 上传灯效信息
        case SET_EFFECT_MESSAGE:
            Download_EffectMessage(sur, len); // 下载灯效信息
            printf("Download_EffectMessage\r");
        case SET_LIGHT_RIGHT_OWNER:           // 设置控灯权限拥有者
            if (*(sur + 3) < 2)
            {
                Light_Owner = *(sur + 3);
                Upload_StateMessage(REPORT_LIGHT_RIGHT_OWNER, Light_Owner);
            }
            break;
        case SET_LIGHT_OUTPUT:
            Protocol_RGBW_Output(sur + 3, len - 3);
            break;
        case CHECK_PLAYLIST:
            Upload_PlayList(*(sur + 3));
            break;
        case SET_PLAYLIST:
            Download_PlayList(sur, len);
            break;
        case CHECK_SCHEDULE:
            Upload_Schedule(*(sur + 3));
            break;
        case SET_SCHEDULE:
            Download_Schedule(sur, len);
            break;
        case CHECK_PLAYSTATE:
            Upload_PlayingState();
            break;
        case SET_PLAYSTATE:
            Download_PlayingState(sur, len);
            break;
        default:
            break;
        }
    }
}
