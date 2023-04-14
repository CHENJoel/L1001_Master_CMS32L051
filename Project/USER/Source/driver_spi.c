/*  Copyright (s) 2019 深圳百问网科技有限公司
 *  All rights reserved
 *
 * 文件名称：driver_spi.c
 * 摘要：
 *
 * 修改历史     版本号       Author       修改内容
 *--------------------------------------------------
 * 2020.6.6      v01        百问科技      创建文件
 *--------------------------------------------------
*/
//#include "main.h"
#include "driver_spi.h"
//#include "driver_timer.h"

// #define SPI_Delay()     us_delay(30)    // 实测10us左右

#define SPI_Delay()     us_delay(50) // 实测15us左右

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
 *  函数名：void SPI_Init(void)
 *  输入参数：
 *  输出参数：无
 *  返回值：无
 *  函数作用：初始化SPI的四根引脚
*/
void SPI_Init(void)
{
    PORT_Init(PORT1, PIN1, INPUT);            /* (16) P11/SDI11/SDA11/ANI8/epwmmo01   MISO */
    PORT_Init(PORT1, PIN2, OPENDRAIN_OUTPUT); /* (15) P12/SDO11/ANI13/epwmmo02        MOSI */
    PORT_Init(PORT1, PIN3, OPENDRAIN_OUTPUT); /* (14) P13/ANI16/epwmmo03              SCLK */
    PORT_Init(PORT1, PIN4, OPENDRAIN_OUTPUT); /* (13) P14/SDA20/ANI17/epwmmo04        CS   */


    W25_CS(1);      // CS初始化高
    SPI_CLK(0);     // CLK初始化低
}

/*
 *  函数名：void SPI_WriteByte(uint8_t data)
 *  输入参数：data -> 要写的数据
 *  输出参数：无
 *  返回值：无
 *  函数作用：模拟SPI写一个字节
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
 *  函数名：uint8_t SPI_ReadByte(void)
 *  输入参数：
 *  输出参数：无
 *  返回值：读到的数据
 *  函数作用：模拟SPI读一个字节
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
 *  函数名：uint8_t SPI_WriteReadByte(uint8_t data)
 *  输入参数：pdata -> 要写的一个字节数据
 *  输出参数：无
 *  返回值：读到的数据
 *  函数作用：模拟SPI读写一个字节
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
