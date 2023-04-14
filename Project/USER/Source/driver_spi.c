/*  Copyright (s) 2019 ���ڰ������Ƽ����޹�˾
 *  All rights reserved
 *
 * �ļ����ƣ�driver_spi.c
 * ժҪ��
 *
 * �޸���ʷ     �汾��       Author       �޸�����
 *--------------------------------------------------
 * 2020.6.6      v01        ���ʿƼ�      �����ļ�
 *--------------------------------------------------
*/
//#include "main.h"
#include "driver_spi.h"
//#include "driver_timer.h"

// #define SPI_Delay()     us_delay(30)    // ʵ��10us����

#define SPI_Delay()     us_delay(50) // ʵ��15us����

void us_delay(uint32_t us)
{
    while (us)
    {
        us--;
    }
}

void SPI_MOSI(uint8_t level)
{
    if (level)
    {
        PORT_SetBit(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_PIN);
    }
    else
    {
        PORT_ClrBit(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_PIN);
    }
}

void SPI_CLK(uint8_t level)
{
    if (level)
    {
        PORT_SetBit(SPIx_SCK_GPIO_PORT, SPIx_SCK_PIN);
    }
    else
    {
        PORT_ClrBit(SPIx_SCK_GPIO_PORT, SPIx_SCK_PIN);
    }
}
void W25_CS(uint8_t level)
{
    if (level)
    {
        PORT_SetBit(W25_CS_GPIO_PORT, W25_CS_PIN);
    }
    else
    {
        PORT_ClrBit(W25_CS_GPIO_PORT, W25_CS_PIN);
    }
}

/*
 *  ��������void SPI_Init(void)
 *  ���������
 *  �����������
 *  ����ֵ����
 *  �������ã���ʼ��SPI���ĸ�����
*/
void SPI_Init(void)
{
    PORT_Init(PORT1, PIN1, INPUT);            /* (16) P11/SDI11/SDA11/ANI8/epwmmo01   MISO */
    PORT_Init(PORT1, PIN2, OPENDRAIN_OUTPUT); /* (15) P12/SDO11/ANI13/epwmmo02        MOSI */
    PORT_Init(PORT1, PIN3, OPENDRAIN_OUTPUT); /* (14) P13/ANI16/epwmmo03              SCLK */
    PORT_Init(PORT1, PIN4, OPENDRAIN_OUTPUT); /* (13) P14/SDA20/ANI17/epwmmo04        CS   */


    W25_CS(1);      // CS��ʼ����
    SPI_CLK(0);     // CLK��ʼ����
}

/*
 *  ��������void SPI_WriteByte(uint8_t data)
 *  ���������data -> Ҫд������
 *  �����������
 *  ����ֵ����
 *  �������ã�ģ��SPIдһ���ֽ�
*/
void SPI_WriteByte(uint8_t data)
{
    uint8_t i = 0;
    uint8_t temp = 0;

    for(i=0; i<8; i++)
    {
        temp = ((data&0x80)==0x80)? 1:0;
        data = data<<1;

        SPI_CLK(0);           //CPOL=0
        SPI_MOSI(temp);
        SPI_Delay();
        SPI_CLK(1);           //CPHA=0
        SPI_Delay();
    }
    SPI_CLK(0);
}

/*
 *  ��������uint8_t SPI_ReadByte(void)
 *  ���������
 *  �����������
 *  ����ֵ������������
 *  �������ã�ģ��SPI��һ���ֽ�
*/
uint8_t SPI_ReadByte(void)
{
    uint8_t i = 0;
    uint8_t read_data = 0xFF;

    for(i=0; i<8; i++)
    {
        read_data = read_data << 1;

        SPI_CLK(0);
        SPI_Delay();
        SPI_CLK(1);
        SPI_Delay();
        if(SPI_MISO())
        {
            read_data = read_data + 1;
        }
    }
    SPI_CLK(0);
    return read_data;
}

/*
 *  ��������uint8_t SPI_WriteReadByte(uint8_t data)
 *  ���������pdata -> Ҫд��һ���ֽ�����
 *  �����������
 *  ����ֵ������������
 *  �������ã�ģ��SPI��дһ���ֽ�
*/
uint8_t SPI_WriteReadByte(uint8_t data)
{
    uint8_t i = 0;
    uint8_t temp = 0;
    uint8_t read_data = 0xFF;

    for(i=0;i<8;i++)
    {
        temp = ((data&0x80)==0x80)? 1:0;
        data = data<<1;
        read_data = read_data<<1;

        SPI_CLK(0);
        SPI_MOSI(temp);
        SPI_Delay();
        SPI_CLK(1);
        SPI_Delay();
        if(SPI_MISO())
        {
            read_data = read_data + 1;
        }
    }
    SPI_CLK(0);
    return read_data;
}
