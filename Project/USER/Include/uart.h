/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2022-10-17 11:28:51
 * @LastEditors: joel
 * .chen sandote@163.om
 * @LastEditTime: 2023-09-19 10:57:30
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\Include\uart.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#ifndef _UART_H_
#define _UART_H_

#include "uart.h"

#define	CTRL_DATA_ST0  1U
#define	CTRL_DATA_SR0  2U
// // #define	BUFF_LEN  256U

typedef enum
{
    FORWARD,  // ÕýÐò
    BACKWARD, // µ¹Ðò
} EFFECT_DIR; // Á÷¹âË³Ðò

void Uart0_Send_String(uint8_t* sur,uint8_t len);
void DMA_Uart_Init(void);
// // // void Tangram_Buffer_load(void);
// // // void Bubble_Sort_2D(uint8_t *array[0][0], uint8_t row, uint8_t column, uint8_t num);

void Bubble_Sort_2D(uint8_t *array, uint8_t row, uint8_t column, uint8_t num);
// // // // void Data_DMA_load(uint8_t *array, uint8_t num);
// // // // void TangramBuffer_DMA_load(uint8_t Num);

void Slave_ColorData_Allot(void );
void Slave_ColorData_DMA(void);

#endif
