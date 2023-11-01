/*
 * @Author: DESKTOP-AKTRQKB\MY sandote@163.com
 * @Date: 2022-10-17 11:28:51
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * @LastEditTime: 2023-10-31 15:30:15
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\Source\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/***********************************************************************************************************************
* Copyright (C) . All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : main.c
* Version      :
* Device(s)    : CMS32L051
* Tool-Chain   : MDK(armcc)
* Description  : This file is a template.
* Creation Date: 2019/12/25
**********************************************?*************************************************************************/

/**************************************************************************************
*********************************
Macro Definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include <stdio.h>
#include "CMS32L051.h"
#include "userdefine.h"
#include "sci.h"
#include "tim4.h"
#include <math.h>
#include "Light.H"
#include "Function_Init.H"


unsigned char dir;

uint32_t i;


unsigned char RandomNum;



uint16_t RunningTimeCnt;

uint16_t runtime_cnt;

uint8_t test_str[]="z26x\r\n";



/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint32_t g_ticks;


void tempdelay(unsigned int ttempus)
{
	while (ttempus)
	{
		ttempus--;
	}
}


void delayMS(uint32_t n)
{
	g_ticks = n;
	while(g_ticks);
}



int main()
{
	MD_STATUS status;
	uint32_t msCnt; // count value of 1ms

	__disable_irq();
	SCB->VTOR = APP_BASIC_ADDR;
	__DMB();
	__enable_irq();

	ADC_Init();
	GPIO_Init();
	//-----------------------------------------------------------------------
	// Systick setting
	//-----------------------------------------------------------------------
	SystemCoreClockUpdate();
	msCnt = SystemCoreClock / 1000;
	SysTick_Config(1*msCnt);
	// delayMS(200); 	// delay 200ms

//-----------------------------------------------------------------------
// Init UART0 for retarget printf/scanf etc.
//-----------------------------------------------------------------------
	SystemCoreClockUpdate();
	// // // status = UART0_Init(SystemCoreClock, 9600);

	uart_app_init();	

	LED1_OFF();
	LED2_OFF();

	
	/* ADC_Init(); */
	ADC_Set_HardTrigger(1, AD_TRG_IT);
	ADC_Set_Clock(CLOCK_DIV8, 0x0DU);
	start_mic_sample();
	// ADC_Start(ADC_CHANNEL_0);
	// DMA_Start(DMA_VECTOR_ADC, CTRL_DATA_ADC, DMA_MODE_NORMAL,
	// 		  DMA_SIZE_HALF, ADC_CNT, (uint16_t *)&ADC->ADCR, ADC_Buffer);

	// // User_TM40_IntervalTimer(TM4_CHANNEL_0,5);
	// // INTC_EnableIRQ(TM00_IRQn);
	// // RTC_Init(RTC_64MHZ);
    // // RTC_Start();
	LED_display_init();
	sys_tick_init();
	wifi_module_init();
	E_Type = 7;
	E_Color = 0;
	// // SYS.POWER_SW = STA_ON;
	Light_Owner = Light_Owner_MCU;
	// // // // Data_Init();
	
	random_init();         // 随机数初始化
	delayMS(100);
	turn_off_all_salve_light();
	SPI_Init();
	adc_dma_init();
	SYS_Init();

	play.work.sw_status = SW_ON;
	play.status = RUN;
	LED1_ON();
	LED2_OFF();
	turn_off_all_salve_light();
	while (1)
	{
		if (T_4MS_FLAG_GetBit)
		{
			T_4MS_FLAG_ClrBit();
			WDT_Restart();
			// // uart_parse();
			// LED2_REV();
			wifi_uart_service();
			// // printf("test\r\n");
		}
		if (T_8MS_FLAG_GetBit)
		{
			T_8MS_FLAG_ClrBit();
			// // test_play_color();
		}
		if (T_20MS_FLAG_GetBit)
		{
			T_20MS_FLAG_ClrBit();

			// // Motion_Output();


			// MIC_Process();
			KeyS_On();
			WDT_Restart();
			KeyS_Click();

			LED_Display_20ms();


			// debug();
			// // Motion_Output();
			// MIC_Process();
		}
		if (T_28MS_FLAG_GetBit)
		{
			T_28MS_FLAG_ClrBit();

			Lignt_Control();
			process_mic_data();
			play_effect_video();
		}
		if (T_100MS_FLAG_GetBit)
		{
			T_100MS_FLAG_ClrBit();
		}
		if (T_200MS_FLAG_GetBit)
		{
			T_200MS_FLAG_ClrBit();
			// // norflash_auto_rw_test();
		}
		if (T_500MS_FLAG_GetBit)
		{
			T_500MS_FLAG_ClrBit();
		}
		if (T_1000MS_FLAG_GetBit)
		{
			T_1000MS_FLAG_ClrBit();
			debug();
			RTC_Task();
		
		}
	}
}

/***********************************************************************************************************************
* Function Name: SysTick Handler
* Description  : Decreament the g_ticks value
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void SysTick_Handler(void)
{
	g_ticks--;
}

/***********************************************************************************************************************
* Function Name: HardFault_Handler
* Description  : Hard Fault handler to report stacked register values
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
// Hard Fault handler in C, with stack frame location and LR value
// extracted from the assembly wrapper as input parameters
void hard_fault_handler_c(unsigned int * hardfault_args, unsigned lr_value)
{
	unsigned int stacked_r0;
	unsigned int stacked_r1;
	unsigned int stacked_r2;
	unsigned int stacked_r3;
	unsigned int stacked_r12;
	unsigned int stacked_lr;
	unsigned int stacked_pc;
	unsigned int stacked_psr;

	stacked_r0 = ((unsigned long) hardfault_args[0]);
	stacked_r1 = ((unsigned long) hardfault_args[1]);
	stacked_r2 = ((unsigned long) hardfault_args[2]);
	stacked_r3 = ((unsigned long) hardfault_args[3]);
	stacked_r12 = ((unsigned long) hardfault_args[4]);
	stacked_lr = ((unsigned long) hardfault_args[5]);
	stacked_pc = ((unsigned long) hardfault_args[6]);
	stacked_psr = ((unsigned long) hardfault_args[7]);

	printf ("[Hard fault handler]\r\n");
	printf ("R0 = %x\r\n", stacked_r0);
	printf ("R1 = %x\r\n", stacked_r1);
	printf ("R2 = %x\r\n", stacked_r2);
	printf ("R3 = %x\r\n", stacked_r3);
	printf ("R12 = %x\r\n", stacked_r12);
	printf ("Stacked LR = %x\r\n", stacked_lr);
	printf ("Stacked PC = %x\r\n", stacked_pc);
	printf ("Stacked PSR = %x\r\n", stacked_psr);
	printf ("Current LR = %x\r\n", lr_value);


	while(1); // endless loop
	__NVIC_SystemReset();
}

/***********************************************************************************************************************
* Function Name: HardFault_Handler
* Description  : Assembly wrapper using Embedded Assembler in Keil MDK
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
// Hard Fault handler wrapper in assembly
// It extracts the location of stack frame and passes it to handler
// in C as a pointer. We also extract the LR value as second
// parameter.
__asm void HardFault_Handler(void)
{
		MOVS 	r0, #4
		MOV 	r1, LR
		TST 	r0, r1
		BEQ 	stacking_used_MSP
		MRS 	R0, PSP ; first parameter - stacking was using PSP
		B 		get_LR_and_branch
stacking_used_MSP
		MRS 	R0, MSP ; first parameter - stacking was using MSP
get_LR_and_branch
		MOV 	R1, LR ; second parameter is LR current value
		LDR 	R2,=__cpp(hard_fault_handler_c)
		BX 		R2
}
