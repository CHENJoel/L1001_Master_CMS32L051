
#include "Function_Init.H"
#include "uart.h"

uint8_t Tangram_Buffer[128];
uint8_t DMA_Buffer[128];

void Uart0_Send_String(uint8_t* sur,uint8_t len)
{
    uint8_t i;
    // // // printf("\r\n");
    for ( i = 0; i < len; i++)
    {
        UART0_Send(*sur++);
        // // // printf("%x ",*sur++);
    }
    // // // printf("\r\n");
}

void DMA_Uart_Init(void)
{
    // DMA_Start(DMA_VECTOR_ST0, CTRL_DATA_ST0, DMA_MODE_NORMAL, DMA_SIZE_BYTE, 30, (void *)&txbuf[0], (void *)&SCI0->TXD0);
    // DMA_Enable(DMA_VECTOR_ST0);
}

void Module_ValSet(uint8_t DR,uint8_t DG,uint8_t DB,uint8_t DW)
{


}

void Tangram_Buffer_load(void)
{
    unsigned char adr;
    unsigned char *ptr;

    unsigned char Dat_R, Dat_G, Dat_B, Dat_W;
    unsigned char DatCRC;

    // ModuleLight_Num = 16;    // Debug


    // // Tangram[0].R=0x01;
    // // Tangram[0].G=0x02;
    // // Tangram[0].B=0x03;
    // // Tangram[0].W=0x04;
    // // Tangram[0].W=0x04;

    // // Tangram[1].R=0x11;
    // // Tangram[1].G=0x12;
    // // Tangram[1].B=0x13;
    // // Tangram[1].W=0x14;

    // // Tangram[2].R=0x21;
    // // Tangram[2].G=0x22;
    // // Tangram[2].B=0x23;
    // // Tangram[2].W=0x24;

    // // Tangram[3].R=0x31;
    // // Tangram[3].G=0x32;
    // // Tangram[3].B=0x33;
    // // Tangram[3].W=0x34;

    // // Tangram[4].R=0x41;
    // // Tangram[4].G=0x42;
    // // Tangram[4].B=0x43;
    // // Tangram[4].W=0x44;

    // // Tangram[5].R=0x51;
    // // Tangram[5].G=0x52;
    // // Tangram[5].B=0x53;
    // // Tangram[5].W=0x54;

    // // Tangram[6].R=0x61;
    // // Tangram[6].G=0x62;
    // // Tangram[6].B=0x63;
    // // Tangram[6].W=0x64;

    // // Tangram[7].R=0x71;
    // // Tangram[7].G=0x72;
    // // Tangram[7].B=0x73;
    // // Tangram[7].W=0x74;

    // // Tangram.MO9.R=0x81;
    // // Tangram.MO9.G=0x82;
    // // Tangram[8].B=0x83;
    // // Tangram[8].W=0x84;

    // // Tangram[9].R=0x91;
    // // Tangram[9].G=0x92;
    // // Tangram[9].B=0x93;
    // // Tangram[9].W=0x94;

    // // Tangram[10].R=0xA1;
    // // Tangram[10].G=0xA2;
    // // Tangram[10].B=0xA3;
    // // Tangram[10].W=0xA4;

    // // Tangram[11].R=0xB1;
    // // Tangram[11].G=0xB2;
    // // Tangram[11].B=0xB3;
    // // Tangram[11].W=0xB4;

    // // Tangram[12].R=0xC1;
    // // Tangram[12].G=0xC2;
    // // Tangram[12].B=0xC3;
    // // Tangram[12].W=0xC4;

    // // Tangram[13].R=0xD1;
    // // Tangram[13].G=0xD2;
    // // Tangram[13].B=0xD3;
    // // Tangram[13].W=0xD4;

    // // Tangram[14].R=0xE1;
    // // Tangram[14].G=0xE2;
    // // Tangram[14].B=0xE3;
    // // Tangram[14].W=0xE4;

    // // Tangram[15].R=0xF1;
    // // Tangram[15].G=0xF2;
    // // Tangram[15].B=0xF3;
    // // Tangram[15].W=0xF4;




    ptr = &Tangram;
    for (adr = 0; adr < ModuleLight_Num; adr++)
    {
        // ptr->
        Dat_R = *(ptr + 0 + adr * 6);
        Dat_G = *(ptr + 1 + adr * 6);
        Dat_B = *(ptr + 2 + adr * 6);
        Dat_W = *(ptr + 3 + adr * 6);

        DatCRC = M_HeadCOM;
        DatCRC += adr;
        DatCRC += SYS.Brightness.Now;
        DatCRC += Dat_R;
        DatCRC += Dat_G;
        DatCRC += Dat_B;
        DatCRC += Dat_W;

        Tangram_Buffer[0 + adr * 8] = M_HeadCOM;      // 帧头
        Tangram_Buffer[1 + adr * 8] = adr;            // 地址
        Tangram_Buffer[2 + adr * 8] = SYS.Brightness.Now; // 亮度
        Tangram_Buffer[3 + adr * 8] = Dat_R;
        Tangram_Buffer[4 + adr * 8] = Dat_G;
        Tangram_Buffer[5 + adr * 8] = Dat_B;
        Tangram_Buffer[6 + adr * 8] = Dat_W;
        Tangram_Buffer[7 + adr * 8] = DatCRC; // 校验
    }

    DMA_Start(DMA_VECTOR_ST0, CTRL_DATA_ST0, DMA_MODE_NORMAL, DMA_SIZE_BYTE, ModuleLight_Num * 8, (void *)&Tangram_Buffer[0], (void *)&SCI0->TXD0);

    // // // DMA_Start(DMA_VECTOR_ST0, CTRL_DATA_ST0, DMA_MODE_REPEAT, DMA_SIZE_BYTE, 8, (void *)&Tangram_Buffer[0], (void *)&SCI0->TXD0);
    DMA_Enable(DMA_VECTOR_ST0);
    DMA_Trigger(DMA_VECTOR_ST0);



    //     DMA_Stop(DMA_VECTOR_ST0);
    // DMA_Start(DMA_VECTOR_ST0, CTRL_DATA_ST0, DMA_MODE_NORMAL, DMA_SIZE_BYTE, 128, (void *)&Tangram_Buffer[0], (void *)&SCI0->TXD0);
    // DMA_Enable(DMA_VECTOR_ST0);
    // DMA_Trigger(DMA_VECTOR_ST0);

}

// 向从机分配对应颜色数据
void Slave_ColorData_Allot(void)
{
    uint8_t i, j;
    for (i = 0; i < TangramDevice.Device_sum; i++)
    {
        for (j = 0; j < TangramDevice.Device_sum; j++)
        {
            if (TangramDevice.SlaveData[j].Runingnum == i) // 轮询出相同运行灯光编号的从机
            {
                TangramDevice.SlaveData[j].Color.R = Tangram[i].R.Now;
                TangramDevice.SlaveData[j].Color.G = Tangram[i].G.Now;
                TangramDevice.SlaveData[j].Color.B = Tangram[i].B.Now;
                TangramDevice.SlaveData[j].Color.W = Tangram[i].W.Now;
            }
        }
    }
}

void Slave_ColorData_DMA(void)
{
    uint8_t i;
    uint8_t DatCRC;
    uint8_t *buff_ptr;
    for (i = 0; i < TangramDevice.Device_sum; i++)
    {
        DatCRC = M_HeadCOM;
        DatCRC += TangramDevice.SlaveData[i].ID;
        DatCRC += SYS.Brightness.Now;
        DatCRC += TangramDevice.SlaveData[i].Color.R;
        DatCRC += TangramDevice.SlaveData[i].Color.G;
        DatCRC += TangramDevice.SlaveData[i].Color.B;
        DatCRC += TangramDevice.SlaveData[i].Color.W;

        buff_ptr = &DMA_Buffer[i * 8];                  // 取址
        *buff_ptr = M_HeadCOM;                          // 帧头
        buff_ptr++;                                     //      地址偏移
        *buff_ptr = TangramDevice.SlaveData[i].ID;      // 地址
        buff_ptr++;                                     //      地址偏移
        *buff_ptr = SYS.Brightness.Now;                 // 亮度
        buff_ptr++;                                     //      地址偏移
        *buff_ptr = TangramDevice.SlaveData[i].Color.B; // 红
        buff_ptr++;                                     //      地址偏移
        *buff_ptr = TangramDevice.SlaveData[i].Color.R; // 绿
        buff_ptr++;                                     //      地址偏移
        *buff_ptr = TangramDevice.SlaveData[i].Color.G; // 蓝
        buff_ptr++;                                     //      地址偏移
        *buff_ptr = TangramDevice.SlaveData[i].Color.W; // 白
        buff_ptr++;                                     //      地址偏移
        *buff_ptr = DatCRC;                             // 校验
                                                        /*
                                                        方式2
                                                                DMA_Buffer[0 + i * 8] = M_HeadCOM;                          // 帧头
                                                                DMA_Buffer[1 + i * 8] = TangramDevice.SlaveData[i].ID;      // 地址
                                                                DMA_Buffer[2 + i * 8] = SYS.Brightness.Now;                 // 亮度
                                                                DMA_Buffer[3 + i * 8] = TangramDevice.SlaveData[i].Color.R; // 红
                                                                DMA_Buffer[4 + i * 8] = TangramDevice.SlaveData[i].Color.G; // 绿
                                                                DMA_Buffer[5 + i * 8] = TangramDevice.SlaveData[i].Color.B; // 蓝
                                                                DMA_Buffer[6 + i * 8] = TangramDevice.SlaveData[i].Color.W; // 白
                                                                DMA_Buffer[7 + i * 8] = DatCRC;                             // 校验
                                                                */
    }
    if (TangramDevice.Device_sum > 0)   // 有设备在线的时候才发送数据
    {
        DMA_Start(DMA_VECTOR_ST0, CTRL_DATA_ST0, DMA_MODE_NORMAL, DMA_SIZE_BYTE, TangramDevice.Device_sum * 8, (void *)&DMA_Buffer[0], (void *)&SCI0->TXD0);
        DMA_Enable(DMA_VECTOR_ST0);
        DMA_Trigger(DMA_VECTOR_ST0);
    }
    else
    {
        printf("No device connect !\r\n");
    }
}

void TangramBuffer_DMA_load(uint8_t Num)
{
    uint8_t i;
    uint8_t Dat_R, Dat_G, Dat_B, Dat_W;
    uint8_t DatCRC;

    for (i = 0; i < Num; i++)
    {
        Dat_R = Tangram[i].R.Now;
        Dat_G = Tangram[i].G.Now;
        Dat_B = Tangram[i].B.Now;
        Dat_W = Tangram[i].W.Now;

        DatCRC = M_HeadCOM;
        DatCRC += i;
        DatCRC += SYS.Brightness.Now;
        DatCRC += Dat_R;
        DatCRC += Dat_G;
        DatCRC += Dat_B;
        DatCRC += Dat_W;

        Tangram_Buffer[0 + i * 8] = M_HeadCOM;      // 帧头
        Tangram_Buffer[1 + i * 8] = i;              // 地址
        Tangram_Buffer[2 + i * 8] = SYS.Brightness.Now; // 亮度
        Tangram_Buffer[3 + i * 8] = Dat_R;          // 红
        Tangram_Buffer[4 + i * 8] = Dat_G;          // 绿
        Tangram_Buffer[5 + i * 8] = Dat_B;          // 蓝
        Tangram_Buffer[6 + i * 8] = Dat_W;          // 白
        Tangram_Buffer[7 + i * 8] = DatCRC;         // 校验
    }
    DMA_Start(DMA_VECTOR_ST0, CTRL_DATA_ST0, DMA_MODE_NORMAL, DMA_SIZE_BYTE, Num * 8, (void *)&Tangram_Buffer[0], (void *)&SCI0->TXD0);
    DMA_Enable(DMA_VECTOR_ST0);
    DMA_Trigger(DMA_VECTOR_ST0);
}

void Data_DMA_load(uint8_t *array, uint8_t num)
{
    uint8_t i;
    uint8_t Dat_R, Dat_G, Dat_B, Dat_W, Dat_Bri, Dat_Adr;
    uint8_t DatCRC;

    for (i = 0; i < num; i++)
    {
        Dat_Adr = *(array + 0 + i * 6);
        Dat_Bri = *(array + 1 + i * 6);
        Dat_R = *(array + 2 + i * 6);
        Dat_G = *(array + 3 + i * 6);
        Dat_B = *(array + 4 + i * 6);
        Dat_W = *(array + 5 + i * 6);

        DatCRC = M_HeadCOM;
        DatCRC += Dat_Adr;
        DatCRC += Dat_Bri;
        DatCRC += Dat_R;
        DatCRC += Dat_G;
        DatCRC += Dat_B;
        DatCRC += Dat_W;

        Tangram_Buffer[0 + i * 8] = M_HeadCOM; // 帧头
        Tangram_Buffer[1 + i * 8] = Dat_Adr;   // 地址
        Tangram_Buffer[2 + i * 8] = Dat_Bri;   // 亮度
        Tangram_Buffer[3 + i * 8] = Dat_R;
        Tangram_Buffer[4 + i * 8] = Dat_G;
        Tangram_Buffer[5 + i * 8] = Dat_B;
        Tangram_Buffer[6 + i * 8] = Dat_W;
        Tangram_Buffer[7 + i * 8] = DatCRC; // 校验
    }
    DMA_Stop(DMA_VECTOR_ST0);
    DMA_Start(DMA_VECTOR_ST0, CTRL_DATA_ST0, DMA_MODE_NORMAL, DMA_SIZE_BYTE, num*8, (void *)&Tangram_Buffer[0], (void *)&SCI0->TXD0);
    DMA_Enable(DMA_VECTOR_ST0);
    DMA_Trigger(DMA_VECTOR_ST0);
}

/**
 * @description: 二维数组排序
 * @param
 * @return {*}
 */
void Bubble_Sort_2D(uint8_t *array, uint8_t row, uint8_t column, uint8_t num)
{
    unsigned char tempArray[column];
    unsigned char i, j, k;
    for (i = 0; i < row - 1; i++)
    {
        for (j = 0; j < row - 1 - i; j++)
        {
            if (*(array + j * column + num) > *(array + (j + 1) * column + num))
            {
                for (k = 0; k < column; k++)
                {
                    tempArray[k] = *(array + j * column + k);
                }
                for (k = 0; k < column; k++)
                {
                    *(array + j * column + k) = *(array + (j + 1) * column + k);
                }
                for (k = 0; k < column; k++)
                {
                    *(array + (j + 1) * column + k) = tempArray[k];
                }
            }
        }
    }
}
