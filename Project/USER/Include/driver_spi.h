/*  Copyright (s) 2019 ���ڰ������Ƽ����޹�˾
 *  All rights reserved
 *
 * �ļ����ƣ�driver_spi.h
 * ժҪ��
 *
 * �޸���ʷ     �汾��       Author       �޸�����
 *--------------------------------------------------
 * 2020.6.6      v01        ���ʿƼ�      �����ļ�
 *--------------------------------------------------
*/
#ifndef __DRIVER_SPI_H
#define __DRIVER_SPI_H

// #include "stm32f1xx_hal.h"
#include "Function_Init.H"
/************************* SPI Ӳ����ض��� *************************/
#define SPIx                             SPI1
// // #define SPIx_CLK_ENABLE()                __HAL_RCC_SPI1_CLK_ENABLE()
// // #define SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
// // #define SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
// // #define SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
// // #define W25_CS_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()

// // #define SPIx_FORCE_RESET()               __HAL_RCC_SPI1_FORCE_RESET()
// // #define SPIx_RELEASE_RESET()             __HAL_RCC_SPI1_RELEASE_RESET()

// #define SPIx_SCK_PIN                     GPIO_PIN_5
// #define SPIx_SCK_GPIO_PORT               GPIOA

// #define SPIx_MISO_PIN                    GPIO_PIN_6
// #define SPIx_MISO_GPIO_PORT              GPIOA

// #define SPIx_MOSI_PIN                    GPIO_PIN_7
// #define SPIx_MOSI_GPIO_PORT              GPIOA

// #define W25_CS_PIN                       GPIO_PIN_4
// #define W25_CS_GPIO_PORT                 GPIOA

// // #define SPI_CLK(level)                   HAL_GPIO_WritePin(SPIx_SCK_GPIO_PORT, SPIx_SCK_PIN, level?GPIO_PIN_SET:GPIO_PIN_RESET)
// // #define SPI_MISO()                       HAL_GPIO_ReadPin(SPIx_MISO_GPIO_PORT, SPIx_MISO_PIN)
// // #define SPI_MOSI(level)                  HAL_GPIO_WritePin(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_PIN, level?GPIO_PIN_SET:GPIO_PIN_RESET)
// // #define W25_CS(level)                    HAL_GPIO_WritePin(W25_CS_GPIO_PORT, W25_CS_PIN, level?GPIO_PIN_SET:GPIO_PIN_RESET)





#define SPIx_MISO_PIN PIN1
#define SPIx_MISO_GPIO_PORT PORT1

#define SPIx_MOSI_PIN PIN2
#define SPIx_MOSI_GPIO_PORT PORT1

#define SPIx_SCK_PIN PIN3
#define SPIx_SCK_GPIO_PORT PORT1

#define W25_CS_PIN PIN4
#define W25_CS_GPIO_PORT PORT1
#define SPI_MISO() PORT_GetBit(SPIx_MISO_GPIO_PORT, SPIx_MISO_PIN)

void SPI_MOSI(uint8_t level);
void SPI_CLK(uint8_t level);
void W25_CS(uint8_t level);
void us_delay(uint32_t us);
/************************* SPI Ӳ����ض������ *************************/
/*
 *  ��������void SPI_Init(void)
 *  ���������
 *  �����������
 *  ����ֵ����
 *  �������ã���ʼ��SPI���ĸ�����
*/
extern void SPI_Init(void);

/*
 *  ��������uint8_t SPI_WriteReadByte(uint8_t data)
 *  ���������data -> Ҫд��һ���ֽ�����
 *  �����������
 *  ����ֵ������������
 *  �������ã�ģ��SPI��дһ���ֽ�
*/
extern uint8_t SPI_WriteReadByte(uint8_t data);

/*
 *  ��������void SPI_WriteByte(uint8_t data)
 *  ���������data -> Ҫд������
 *  �����������
 *  ����ֵ����
 *  �������ã�ģ��SPIдһ���ֽ�
*/
extern void SPI_WriteByte(uint8_t data);

/*
 *  ��������uint8_t SPI_ReadByte(void)
 *  ���������
 *  �����������
 *  ����ֵ������������
 *  �������ã�ģ��SPI��һ���ֽ�
*/
extern uint8_t SPI_ReadByte(void);

#endif  //__DRIVER_SPI_H
