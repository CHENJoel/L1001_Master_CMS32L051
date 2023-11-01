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
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "Function_Init.H"
#include "Com.H"
#include "FIFO.h"

unsigned char Device_Data_Array[10];
unsigned char RX_DataPackage[6]; // �ӻ���������ȷ���ݰ�


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
 * @description: �ӻ�������ȡ�ӻ���������Ч���ݰ�
 * @param {FIFOTypeDef} *StructDAT
 * @return {*}
 */
unsigned char DataPackage_Extract(FIFOTypeDef *StructDAT)
{
    unsigned char i;
    unsigned char TempCRC;
    unsigned char Dat1, Dat2, Dat3, Dat4, Dat5, Dat6, Dat7;
    for (i = 0; i < 1000; i++) // �������ƴ���ȡ����1000������
    {
        if ((*StructDAT).Read != (*StructDAT).Write) // ��������δ��ȫ����������
        {
            /* USER CODE BEGIN */

            /* (*StructDAT).Read ָ��ǰ��Ҫ��������� */

            Dat7 = FIFO_ReadByte_Extract(&(*StructDAT), 7);
            if (Dat7 == S_HeadCOM) // ֡ͷУ�飨�ӻ����ݰ���
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
                if (FIFO_ReadByte_Extract(&(*StructDAT), 0) == TempCRC) // CRCУ��
                {
                    RX_DataPackage[0] = Dat6; // ָ������
                    RX_DataPackage[1] = Dat5;
                    RX_DataPackage[2] = Dat4;
                    RX_DataPackage[3] = Dat3;
                    RX_DataPackage[4] = Dat2;
                    RX_DataPackage[5] = Dat1;
                    return Package_Right;
                }
            }

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
            if (i == 0)
            {
                return Package_Empty; // �����д��ַһ�£�����������������
            }
            return Package_Wrong; // ���껺��������ݣ���δ���ַ���Э������ݰ�
        }
    }
}

void Uart1_Byte_POP(FIFOTypeDef *StructDAT)
{
    unsigned char temp;
    for (temp = 0; temp < 50; temp++) // �������ƴ���ȡ����50������
    {
        if ((*StructDAT).Read != (*StructDAT).Write) // ��������δ��ȫ����������
        {
            /* USER CODE BEGIN */

            /* (*StructDAT).Read ָ��ǰ��Ҫ��������� */

                // // // printf("%c\n",StructDAT->Buffer[StructDAT->Read]);

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
 * @description: ��ӻ�����,��ѯ�����дӻ������Լ�������ַID
 * @param
 * @return {*}
 */

void Slave_Handshake(void)
{
    // // // unsigned int i, j, k, m;
    // // // unsigned char temp;
    // // // unsigned char Temp_Array[Slave_num][Slave_Data_num]; // ��ʱ�洢�ӻ��豸��Ϣ
    // // // unsigned char Temp_SlaveNum = 0;                     // ��ʱ�ӻ���Ϣ���
    // // // unsigned char PackageState;                          // ��������״̬
    // // // SlaveDevive_Num = 0;                                 // ���ӻ���Ÿ�λ
    // // // for (i = 0; i <= 250; i++)                           // ��һ��ӻ�����ID��������
    // // // {
    // // //     Uart0_Buffer.Read = Uart0_Buffer.Write; // ��ս��ջ�����δ������
    // // //     DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Handshake_Chief, i, Random_Generate(), Random_Generate(), Random_Generate());
    // // //     delay_5ms();                                                                   // �ȴ��ӻ���ȡ����
    // // //     PackageState = DataPackage_Extract(&Uart0_Buffer);                              // ��ȡ��������״̬
    // // //     if ((PackageState == Package_Right) && (RX_DataPackage[0] == S_ChiefMinor_ID)) // ���յ�һ��ӻ���Ϣ���ݰ�
    // // //     {                                                                              // ��¼���ֳɹ��Ĵӻ���Ϣ
    // // //         Slave_Array[SlaveDevive_Num][0] = RX_DataPackage[1];                       // �ӻ���ID
    // // //         Slave_Array[SlaveDevive_Num][1] = RX_DataPackage[2];                       // �ӻ���ID
    // // //         SlaveDevive_Num++;
    // // //     }
    // // //     else if (PackageState != Package_Empty) // �ǿ����ݰ�,������������Э�飬���ݰ����󣬴����ж���ӻ�ͬʱռ�����߷������ݣ���Ը�ID��������У��
    // // //     {
    // // //         for (k = 0; k < 255; k++) // ���֧��254���޸ĸ�ID��ַ������
    // // //         {
    // // //             // ��ӻ��ĸ�ID��������
    // // //             Temp_SlaveNum = 0;
    // // //             for (m = 0; m <= 255; m++)
    // // //             {
    // // //                 // LED3_REV();
    // // //                 Uart0_Buffer.Read = Uart0_Buffer.Write; // ��ս��ջ�����δ������
    // // //                 DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Handshake_Minor, i, m, Random_Generate(), Random_Generate());
    // // //                 delay_5ms();                                                                   // �ȴ��ӻ���ȡ����
    // // //                 PackageState = DataPackage_Extract(&Uart0_Buffer);                              // ��ȡ��������״̬
    // // //                 if ((PackageState == Package_Right) && (RX_DataPackage[0] == S_ChiefMinor_ID)) // ���յ�һ��ӻ���Ϣ���ݰ�
    // // //                 {                                                                              // ��ʱ��¼���ֳɹ��Ĵӻ���Ϣ
    // // //                     Temp_Array[Temp_SlaveNum][0] = RX_DataPackage[1];                          // �ӻ���ID
    // // //                     Temp_Array[Temp_SlaveNum][1] = RX_DataPackage[2];                          // �ӻ���ID
    // // //                     Temp_SlaveNum++;
    // // //                 }
    // // //                 else if (PackageState != Package_Empty) // �ǿ����ݰ�,������������Э�飬���ݰ����󣬴����ж���ӻ�ͬʱռ�����߷������ݣ���Ը�ID��������У��
    // // //                 {
    // // //                     // ֪ͨ����ID�µĴӻ����и�IDǿ�Ƹ���
    // // //                     DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_MinorID_Refresh, i, Random_Generate(), Random_Generate(), Random_Generate());
    // // //                     delay_5ms(); // �ȴ��ӻ���ȡ����
    // // //                     break;       // ������һ�ֵĸ�ID����
    // // //                 }
    // // //                 if (m == 255)
    // // //                 {
    // // //                     // ��ID����һȦ��δ���յ��������ݣ��������ID�µĸ�ID����������
    // // //                     for (temp = 0; temp < Temp_SlaveNum; temp++) // ��ʽ��¼���ֳɹ��Ĵӻ���Ϣ
    // // //                     {
    // // //                         Slave_Array[SlaveDevive_Num][0] = Temp_Array[temp][0]; // �ӻ���ID
    // // //                         Slave_Array[SlaveDevive_Num][1] = Temp_Array[temp][1]; // �ӻ���ID
    // // //                         SlaveDevive_Num++;
    // // //                     }
    // // //                     k = 255; // ������ID����
    // // //                     break;
    // // //                 }
    // // //             }
    // // //         }
    // // //     }
    // // // }
}

/**
 * @description: �Զ�����ͨѶID��ƹ�ID
 * @param
 * @return {*}
 */
void Slave_Allocate_ID(void)
{
    // // // Poll_Device_ID();                                                 // ��ѯ����豸�̶�ID������ID���豸����
    // // // Bubble_Sort_2D(&Slave_Array, SlaveDevive_Num, Slave_Data_num, 3); // �������б�Ž�����������
    // // // Post_Device_Commu_ID();                                           // �����ӻ�ͨѶID
    // // // Post_Device_Light_ID();                                           // �����ӻ��ƹ�ID
    // // // delay_20ms();                                                     // �ȴ��ӻ���ȡ����
    // // // Poll_Device_Data();                                               // ��ѯ����豸ͨѶID,�ƹ�ID
    // // // Mark_Device_FixedID_Data();                                       // ��ǲ���¼���̶�ID���豸������ͨѶID��
}

/*
��ѯ����豸�̶�ID������ID���豸����
*/
void Poll_Device_ID(void)
{
    // // // uint8_t i;
    // // // uint8_t PackageState;                 // ��������״̬
    // // // for (i = 0; i < SlaveDevive_Num; i++) // ��ѯ����ID��Ϣ
    // // // {
    // // //     Uart0_Buffer.Read = Uart0_Buffer.Write; // ��ս��ջ�����δ������
    // // //     Check_Device_ID(Slave_Array[i][0], Slave_Array[i][1]);
    // // //     delay_10ms();                                                              // �ȴ��ӻ���ȡ����
    // // //     PackageState = DataPackage_Extract(&Uart0_Buffer);                          // ��ȡ��������״̬
    // // //     if ((PackageState == Package_Right) && (RX_DataPackage[0] == S_Device_ID)) // ���յ�һ��ӻ���Ϣ���ݰ�
    // // //     {
    // // //         if (Slave_Array[i][0] == RX_DataPackage[1] && Slave_Array[i][1] == RX_DataPackage[2]) // ����IDУ��
    // // //         {
    // // //             Slave_Array[i][2] = RX_DataPackage[3]; // �̶�ID
    // // //             Slave_Array[i][3] = RX_DataPackage[4]; // ����ID
    // // //             Slave_Array[i][4] = RX_DataPackage[5]; // �豸����
    // // //         }
    // // //     }
    // // // }
}
/*
��ѯ����豸ͨѶID,�ƹ�ID
*/
void Poll_Device_Data(void)
{
    // // // uint8_t i;
    // // // uint8_t PackageState;                 // ��������״̬
    // // // for (i = 0; i < SlaveDevive_Num; i++) // ��ѯ����ID��Ϣ
    // // // {
    // // //     Uart0_Buffer.Read = Uart0_Buffer.Write; // ��ս��ջ�����δ������
    // // //     Check_Device_Data(Slave_Array[i][0], Slave_Array[i][1]);
    // // //     delay_10ms();                                                                // �ȴ��ӻ���ȡ����
    // // //     PackageState = DataPackage_Extract(&Uart0_Buffer);                            // ��ȡ��������״̬
    // // //     if ((PackageState == Package_Right) && (RX_DataPackage[0] == S_Device_Data)) // ���յ�һ��ӻ���Ϣ���ݰ�
    // // //     {
    // // //         if (Slave_Array[i][0] == RX_DataPackage[1] && Slave_Array[i][1] == RX_DataPackage[2]) // ����IDУ��
    // // //         {
    // // //             Slave_Array[i][5] = RX_DataPackage[3]; // ͨѶID
    // // //             Slave_Array[i][6] = RX_DataPackage[4]; // �ƹ�ID
    // // //         }
    // // //     }
    // // // }
}

/*
�����ӻ�ͨѶID
*/
void Post_Device_Commu_ID(void)
{
    // // // uint8_t i;
    // // // for (i = 0; i < SlaveDevive_Num; i++) // ���·����ӻ�ͨѶID
    // // // {
    // // //     Set_CommuID(Slave_Array[i][0], Slave_Array[i][1], 0x30 + i);
    // // //     Set_CommuID(Slave_Array[i][0], Slave_Array[i][1], 0x30 + i);
    // // //     delay_10ms(); // �ȴ��ӻ���ȡ����
    // // // }
}

/*
  �����ӻ��ƹ�ID
*/
void Post_Device_Light_ID(void)
{
    // // // uint8_t i, j;
    // // // uint8_t temp;
    // // // temp = Slave_Array[0][3];
    // // // j = 0;
    // // // for (i = 0; i < SlaveDevive_Num; i++) // ���·����ӻ��ƹ�ID
    // // // {
    // // //     if (Slave_Array[i][3] != temp)
    // // //     {
    // // //         j++;
    // // //     }
    // // //     Set_LightID(Slave_Array[i][0], Slave_Array[i][1], j);
    // // //     Set_LightID(Slave_Array[i][0], Slave_Array[i][1], j);
    // // //     temp = Slave_Array[i][3];
    // // //     delay_10ms(); // �ȴ��ӻ���ȡ����
    // // // }
    // // // ModuleLight_Num = j + 1;
}
/*
  �����ӻ�����ID
*/
void Post_Device_Series_ID(void)
{
    // // // uint8_t i, j;
    // // // for (i = 0; i < SlaveDevive_Num; i++) // ���·����ӻ��ƹ�ID
    // // // {
    // // //     Set_SeriesNum(Slave_Array[i][0], Slave_Array[i][1], Slave_Array[i][8]);
    // // //     Set_SeriesNum(Slave_Array[i][0], Slave_Array[i][1], Slave_Array[i][8]);
    // // //     delay_10ms(); // �ȴ��ӻ���ȡ����
    // // // }
}

/*
    ��ǲ���¼���̶�ID���豸������ͨѶID��
*/
void Mark_Device_FixedID_Data(void)
{
    // // // // // uint8_t i, j, k, m, n;
    // // // // // uint8_t temp;
    // // // // // /*ɸѡ��ͬһ�̶�ID���豸����*/
    // // // // // for (i = 0; i < SlaveDevive_Num; i++) // ��ѯ����ID��Ϣ
    // // // // // {
    // // // // //     temp = Slave_Array[i][2];
    // // // // //     m = 0;
    // // // // //     for (j = 0; j < SlaveDevive_Num; j++) // ��ѯ����ID��Ϣ
    // // // // //     {
    // // // // //         if (Slave_Array[j][2] == temp) // ɸѡ��ͬһ�̶�ID���豸����
    // // // // //         {
    // // // // //             m++;
    // // // // //         }
    // // // // //     }
    // // // // //     n = 0;
    // // // // //     for (j = 0; j < SlaveDevive_Num; j++) // ��ѯ����ID��Ϣ
    // // // // //     {
    // // // // //         if (Slave_Array[j][2] == temp)
    // // // // //         {
    // // // // //             n++;
    // // // // //             Slave_Array[j][7] = m << 4; // ����λ���Ϊ�ù̶�ID�����豸��
    // // // // //             Slave_Array[j][7] |= n;     // ����λ���Ϊ�ù̶�ID�ı��
    // // // // //         }
    // // // // //     }
    // // // // // }
    // // // // // /*��¼ͬһ�̶�ID�豸��������ͨѶID*/
    // // // // // for (i = 0; i < 8; i++)
    // // // // // {
    // // // // //     FixedID_DeviceData[i][1] = 0; // ���ݸ�λ
    // // // // //     m = 0;
    // // // // //     for (j = 0; j < SlaveDevive_Num; j++)
    // // // // //     {
    // // // // //         if (Slave_Array[j][2] == FixedID_DeviceData[i][0]) // �������Ӧ���豸����
    // // // // //         {
    // // // // //             FixedID_DeviceData[i][1] = Slave_Array[j][7] >> 4; // ���ӵ�иù̶�ID���豸����
    // // // // //             FixedID_DeviceData[i][2 + m] = Slave_Array[j][5];  // ӵ�иù̶�ID���豸ͨѶID
    // // // // //             m++;
    // // // // //         }
    // // // // //     }
    // // // // // }
}













/**************************************** ��Э�� ****************************************/









/**
 * @description: ��ӻ�����,�ó�Ψһ��ַ
 * @param
 * @return {*}
 */

void Get_Slave_ID(void)
{
    // // // uint16_t i, j;
    // // // uint8_t Temp_Array[16];     // �豸id
    // // // uint8_t Temp_DeviceNum = 0; // �豸����
    // // // uint8_t PackageState;       // ��������״̬
    // // // for (i = 0; i <= 255; i++)  // ���ִ��256�γ�ͻ����
    // // // {
    // // //     Temp_DeviceNum = 0;
    // // //     for (j = 0; j <= 255; j++) // ��ѯ����id
    // // //     {
    // // //         Uart0_Buffer.Read = Uart0_Buffer.Write;                                    // ��ս��ջ�����δ������
    // // //         DataTx_Master_Check_ID(j);                                                 // ����id
    // // //         delay_5ms();                                                               // �ȴ��ӻ���ȡ����
    // // //         PackageState = DataPackage_Extract(&Uart0_Buffer);                         // ��ȡ��������״̬
    // // //         if ((PackageState == Package_Right) && (RX_DataPackage[0] == S_Return_ID) && (RX_DataPackage[1] == j)) // ���յ�һ��ӻ���Ϣ���ݰ�
    // // //         {
    // // //             Temp_Array[Temp_DeviceNum] = RX_DataPackage[1]; // ��Ǵӻ�ID
    // // //             Temp_DeviceNum++;                               // ��Ǵӻ�����
    // // //         }
    // // //         else if (PackageState != Package_Empty) // �ǿ����ݰ�,������������Э�飬���ݰ����󣬴����ж���ӻ�ͬʱռ�����߷������ݣ�������ID��ͻ
    // // //         {
    // // //             DataTx_Refresh_ID(); // Ҫ��ӻ�����id
    // // //             delay_5ms();         // �ȴ��ӻ���ȡ����
    // // //             break;               // ����ѭ����ѯ
    // // //         }
    // // //         if (j == 255) // ��ѭ����ѯ������˵����ǰδ����ID��ͻ
    // // //         {
    // // //             TangramDevice.Device_sum = Temp_DeviceNum; // �洢�豸����
    // // //             for (i = 0; i < Temp_DeviceNum; i++)
    // // //             {
    // // //                 TangramDevice.SlaveData[i].ID = Temp_Array[i]; // �洢�豸id
    // // //             }
    // // //             i = 256; // �˳���ѭ��
    // // //         }
    // // //     }
    // // // }
}

// // // // // // void Get_Slave_Coord(void)
// // // // // // {
// // // // // //     uint8_t i;
// // // // // //     uint8_t PackageState; // ��������״̬
// // // // // //     for (i = 0; i < TangramDevice.Device_sum; i++)
// // // // // //     {
// // // // // //         Uart0_Buffer.Read = Uart0_Buffer.Write;                      // ��ս��ջ�����δ������
// // // // // //         DataTx_Master_Check_Ligntnum(TangramDevice.SlaveData[i].ID); // ��ѯ�˵ƹ���
// // // // // //         delay_5ms();
// // // // // //         PackageState = DataPackage_Extract(&Uart0_Buffer);                                                                                       // ��ȡ��������״̬
// // // // // //         if ((PackageState == Package_Right) && (RX_DataPackage[0] == S_Return_LightNum) && (RX_DataPackage[1] == TangramDevice.SlaveData[i].ID)) // ���յ�һ��ӻ���Ϣ���ݰ�
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

/* ��ȡ���� */
void Get_Slave_Coord(void)
{
    // // // uint8_t i;
    // // // uint8_t PackageState; // ��������״̬
    // // // for (i = 0; i < TangramDevice.Device_sum; i++)
    // // // {
    // // //     Uart0_Buffer.Read = Uart0_Buffer.Write;                   // ��ս��ջ�����δ������
    // // //     DataTx_Master_Check_Coord(TangramDevice.SlaveData[i].ID); // ��ȡ����
    // // //     delay_5ms();
    // // //     PackageState = DataPackage_Extract(&Uart0_Buffer);                                                                                       // ��ȡ��������״̬
    // // //     if ((PackageState == Package_Right) && (RX_DataPackage[0] == S_RETURN_Coord) && (RX_DataPackage[1] == TangramDevice.SlaveData[i].ID)) // ���յ�һ��ӻ���Ϣ���ݰ�
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

/* �������� */
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

/* ��ȡ�Ƕ� */
void Get_Slave_Angle(void)
{
    // // // uint8_t i;
    // // // uint8_t PackageState; // ��������״̬
    // // // for (i = 0; i < TangramDevice.Device_sum; i++)
    // // // {
    // // //     Uart0_Buffer.Read = Uart0_Buffer.Write;                   // ��ս��ջ�����δ������
    // // //     DataTx_Master_Check_Angle(TangramDevice.SlaveData[i].ID); // ��ȡ�Ƕ�
    // // //     delay_5ms();
    // // //     PackageState = DataPackage_Extract(&Uart0_Buffer);                                                                                       // ��ȡ��������״̬
    // // //     if ((PackageState == Package_Right) && (RX_DataPackage[0] == S_RETURN_Angle) && (RX_DataPackage[1] == TangramDevice.SlaveData[i].ID)) // ���յ�һ��ӻ���Ϣ���ݰ�
    // // //     {
    // // //         TangramDevice.SlaveData[i].Angle = RX_DataPackage[2];
    // // //     }
    // // //     else
    // // //     {
    // // //         TangramDevice.SlaveData[i].Angle = 0;
    // // //     }
    // // // }
}

/* ���ýǶ� */
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
    // Get_Slave_ID();    // ��ȡ�ӻ�id��Ϣ
    // Get_Slave_Coord(); // ��ȡ�ӻ�����
    // Get_Slave_Angle(); /* ��ȡ�Ƕ� */

    // // // Runingnum_Bubble_Sort(); // �ƹ����򣬼�������б��

    // for (i = 0; i < TangramDevice.Device_sum; i++)
    // {
    //     // TangramDevice.SlaveData[i].Container.data1 = 0xFF; // ��ʱ�ƹ����
    //     TangramDevice.SlaveData[i].Coord.X = i + 1;        // error��ģ����������
    //     TangramDevice.SlaveData[i].Coord.Y = i + 1;
    // }
    /**************/
    // �������ɰ�
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


void slave_data_debug(void) // �������ģ������
{
    uint8_t i;
    TangramDevice.Device_sum = 4;
    for (i = 0; i < TangramDevice.Device_sum; i++)
    {
        TangramDevice.SlaveData[i].ID = 0xE0 + i;
        TangramDevice.SlaveData[i].DeviceType = i;
        TangramDevice.SlaveData[i].Coord.X = i + 1; // error��ģ����������
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

uint8_t CRC_Calculate(uint8_t *sur, uint8_t len) // ����CRCУ��
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
void Upload_LightMessage(void)  // �ϴ�������Ϣ
{
    uint8_t protocol_buffer[69];
    uint8_t *p_buffer;
    uint8_t protocol_length;
    uint8_t i;
    protocol_length = 4 + TangramDevice.Device_sum * 4;
    p_buffer = protocol_buffer;
    *p_buffer = APP_PROTOCOL_HEADER;        // ֡ͷ
    *++p_buffer = protocol_length;          // ���ݳ���
    *++p_buffer = REPORT_LIGHT_MESSAGE;     // ָ������
    *++p_buffer = TangramDevice.Device_sum; // �����豸����

    if (TangramDevice.Device_sum)
    {
        for (i = 0; i < TangramDevice.Device_sum; i++)
        {
            *++p_buffer = TangramDevice.SlaveData[i].ID;         // �����豸ID
            *++p_buffer = TangramDevice.SlaveData[i].DeviceType; // �����豸����
            *++p_buffer = TangramDevice.SlaveData[i].Coord.X;    // X����
            *++p_buffer = TangramDevice.SlaveData[i].Coord.Y;    // Y����
        }
    }
    *++p_buffer = CRC_Calculate(protocol_buffer, protocol_length);               // У���
    mcu_dp_raw_update(DPID_USER_PROTOCOL, protocol_buffer, protocol_length + 1); // RAW�������ϱ�;
    Uart0_Send_String(protocol_buffer, protocol_length + 1);
}

void Download_LightCoord(uint8_t *sur, uint16_t len) // ���ص���������Ϣ
{
    uint8_t i, j;
    uint8_t temp;
    uint8_t *p;
    uint8_t num;
    len -= 4; // ��ȥָ���ֶΣ�ʣ�������ֽ���
    sur += 3; // ֡ͷ ���� ָ��
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
            if (*p == TangramDevice.SlaveData[i].ID) // ��ѯ�����Ӧ��ID
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
void Upload_EffectMessage(uint8_t num) // �ϴ���Ч��Ϣ
{
    uint8_t protocol_buffer[91];
    uint8_t *p_buffer;
    uint8_t protocol_length;
    uint8_t i;
    EF_para_data_TypeDef EFpara; // ������Ϣ
    color_group_TypeDef EFcolor; // ɫ��
    id_group_TypeDef EFid;       // id��Ϣ
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
    if (EFpara.color_sum > 15) // ���ݴ���
    {
        EFpara.color_sum = 0;
    }
    if (EFpara.motion == MOTION_STATIC)
    {
        protocol_length = 10 + EFpara.color_sum * 5; // ��̬��Ч����id��Ϣ
    }
    else
    {
        protocol_length = 10 + EFpara.color_sum * 4;
    }
    p_buffer = &protocol_buffer;
    *p_buffer = APP_PROTOCOL_HEADER;     // ֡ͷ
    *++p_buffer = protocol_length;       // ���ݳ���
    *++p_buffer = REPORT_EFFECT_MESSAGE; // ָ������
    *++p_buffer = num;                   // ��Ч���
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

    *++p_buffer = CRC_Calculate(protocol_buffer, protocol_length);               // У���
    mcu_dp_raw_update(DPID_USER_PROTOCOL, protocol_buffer, protocol_length + 1); // RAW�������ϱ�;
    Uart0_Send_String(protocol_buffer, protocol_length + 1);
}
void Download_EffectMessage(uint8_t *sur, uint16_t len) // ���ص�Ч��Ϣ
{
    uint8_t i;
    uint8_t *p;
    uint8_t ef_num;              // ��Ч���
    EF_para_data_TypeDef EFpara; // ������Ϣ
    color_group_TypeDef EFcolor; // ɫ��
    id_group_TypeDef EFid;       // id��Ϣ
    // // // // // // // // // // // // p = &EFpara;
    // // // // // // // // // // // // for (i = 0; i < sizeof(EFpara); i++) // ��������
    // // // // // // // // // // // // {
    // // // // // // // // // // // //     *p++ = 0;
    // // // // // // // // // // // // }
    // // // // // // // // // // // // p = &EFcolor;
    // // // // // // // // // // // // for (i = 0; i < sizeof(EFcolor); i++) // ��������
    // // // // // // // // // // // // {
    // // // // // // // // // // // //     *p++ = 0;
    // // // // // // // // // // // // }
    // // // // // // // // // // // // p = &EFid;
    // // // // // // // // // // // // for (i = 0; i < sizeof(EFid); i++) // ��������
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
void Upload_PlayList(uint8_t num) // �ϴ������б�
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
    *p_buffer = APP_PROTOCOL_HEADER; // ֡ͷ
    *++p_buffer = protocol_length;   // ���ݳ���
    *++p_buffer = REPORT_PLAYLIST;   // ָ������
    *++p_buffer = num;               // �б���
    *++p_buffer = list.play_mode;    // ����ģʽ
    *++p_buffer = list.switch_hour;  // �л�ʱ��
    *++p_buffer = list.switch_min;   // �л�ʱ��
    *++p_buffer = list.list_sum;     // �б��Ч����
    for (i = 0; i < list.list_sum; i++)
    {
        *++p_buffer = list.list_table[i];
    }
    *++p_buffer = CRC_Calculate(protocol_buffer, protocol_length);               // У���
    mcu_dp_raw_update(DPID_USER_PROTOCOL, protocol_buffer, protocol_length + 1); // RAW�������ϱ�;
    Uart0_Send_String(protocol_buffer, protocol_length + 1);
}

void Download_PlayList(uint8_t *sur, uint16_t len) // ���ز����б�
{
    uint8_t i, j;
    uint8_t temp;
    uint8_t *p;
    uint8_t num;
    playlist_TypeDef playlist;
    memset(&playlist, 0, sizeof(playlist));
    p = sur + 3;
    num = *p; // �б���
    playlist.play_mode = *++p;
    playlist.switch_hour = *++p;
    playlist.switch_min = *++p;
    playlist.list_sum = *++p;
    if (num > 19)
    {
        return;
    }
    if (playlist.list_sum > 59) // ��Ч����
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

void Upload_Schedule(uint8_t num) // �ϴ���ʱ����
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
    *p_buffer = APP_PROTOCOL_HEADER; // ֡ͷ
    *++p_buffer = protocol_length;   // ���ݳ���
    *++p_buffer = REPORT_SCHEDULE;   // ָ������
    *++p_buffer = num;
    *++p_buffer = schedule.Action;
    *++p_buffer = schedule.Exection_Hou;
    *++p_buffer = schedule.Exection_Min;
    *++p_buffer = schedule.Duration;
    *++p_buffer = schedule.Brightness;
    *++p_buffer = schedule.Repeat_Week;
    *++p_buffer = CRC_Calculate(protocol_buffer, protocol_length);
    mcu_dp_raw_update(DPID_USER_PROTOCOL, protocol_buffer, protocol_length + 1); // RAW�������ϱ�;
    Uart0_Send_String(protocol_buffer, protocol_length + 1);
}

void Download_Schedule(uint8_t *sur, uint16_t len) // ���ض�ʱ����
{
    uint8_t *p;
    uint8_t num;
    schedule_TypeDef schedule;
    memset(&schedule, 0, sizeof(schedule));
    p = sur + 3;
    num = *p; // ��ʱ������
    schedule.Action = *++p;
    schedule.Exection_Hou = *++p;
    schedule.Exection_Min = *++p;
    schedule.Duration = *++p;
    schedule.Brightness = *++p;
    schedule.Repeat_Week = *++p;
    Edit_Schedule(num, &schedule);
}

/**************************************************************************************************/
void Upload_PlayingState(void) // �ϱ�����״̬
{
    uint8_t protocol_buffer[9];
    protocol_buffer[0] = APP_PROTOCOL_HEADER;       // ֡ͷ
    protocol_buffer[1] = 8;                         // ���ݳ���
    protocol_buffer[2] = REPORT_PLAYSTATE;          // ָ������
    protocol_buffer[3] = PlayingState.on_sta;       // bit0 ��0��ͣ/1��ʼ��������λ����
    protocol_buffer[4] = PlayingState.effect_num;   // ��ǰ��Ч���
    protocol_buffer[5] = PlayingState.playlist_num; // �б��ű�ţ�ֵ255����ǰ�Ƿ��б��ţ�
    protocol_buffer[6] = PlayingState.RESERVED[0];  // ����
    protocol_buffer[7] = PlayingState.RESERVED[1];  // ����
    protocol_buffer[8] = CRC_Calculate(protocol_buffer, 8);
    mcu_dp_raw_update(DPID_USER_PROTOCOL, protocol_buffer, 9); // RAW�������ϱ�;
    Uart0_Send_String(protocol_buffer, 9);
}
void Download_PlayingState(uint8_t *sur, uint16_t len) // ���ز�������
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
void Upload_StateMessage(uint8_t cmd, uint8_t sta) // �ϱ�״̬
{
    uint8_t protocol_buffer[5];
    protocol_buffer[0] = APP_PROTOCOL_HEADER;               // ֡ͷ
    protocol_buffer[1] = 4;                                 // ���ݳ���
    protocol_buffer[2] = cmd;                               // ָ��
    protocol_buffer[3] = sta;                               // ״̬
    protocol_buffer[4] = CRC_Calculate(protocol_buffer, 4); // У��
    Uart0_Send_String(protocol_buffer, 5);
}
void Protocol_RGBW_Output(uint8_t *sur, uint16_t len) // ���������������ɫ
{
    uint8_t i, j;
    uint8_t temp;
    uint8_t *p;
    uint8_t num;
    len--; // ��ȥһ��У���ֽڣ�ʣ�������ֽ���
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
            if (*p == TangramDevice.SlaveData[i].ID) // ��ѯ�����Ӧ��ID
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


void RAW_processing(uint8_t *sur, uint16_t len) // ͸���ϱ�
{
    uint8_t crc;
    // LED2_REV();
    // Uart0_Send_String(sur, len);
    crc = CRC_Calculate(sur, len - 1);
    if (crc == *(sur + len - 1) && *sur == APP_PROTOCOL_HEADER) // У��
    {
        // LED2_REV();
        switch (*(sur + 2))
        {
        case CHECK_LIGHT_MESSAGE:
            Upload_LightMessage(); // ��ѯ������Ϣ
            break;
        case SET_LIGHT_COORDINATE:
            Download_LightCoord(sur, len); // ���ص���������Ϣ
            printf("Download_LightCoord\r");
            break;
        case CHECK_EFFECT_MESSAGE:
            Upload_EffectMessage(*(sur + 3)); // �ϴ���Ч��Ϣ
        case SET_EFFECT_MESSAGE:
            Download_EffectMessage(sur, len); // ���ص�Ч��Ϣ
            printf("Download_EffectMessage\r");
        case SET_LIGHT_RIGHT_OWNER:           // ���ÿص�Ȩ��ӵ����
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
