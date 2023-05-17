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






uint8_t Uart1_rx_buffer[10];



uint8_t temp,temp1,temp2;
unsigned char x,y,z;

unsigned char tempR,tempG,tempB;

unsigned char dir;
uint16_t get_value[8];
uint16_t avg;
uint32_t i;
unsigned char pppp;

unsigned char NOW,TAR;

unsigned char RandomNum;

uint16_t ADC_Buffer[ADC_CNT];	//
// uint16_t ADC_Buffer[200];	//

uint16_t sdghgeydu;
uint8_t uart1_buffer[50];
uint8_t dbywegyeagfy;
unsigned char ADC_DMA_OK;
unsigned char ADC_DMA_EN;
unsigned char FFT_OK;
unsigned char FFT_Flash;	//

uint16_t RunningTimeCnt;

// int FFT_InjectCount = 0;						//数据注入次数
// int FFT_InjectFinishFlag = 0;					//数据注入完成标志

// Complex_TypeDef FFT_Date[FFT_N];					//创建一个复数数组，大小1024个，占用RAM有 8*1024 = 8.192KB 内存，单片机RAM建议大于10K ，否则程序运行不起来

// // uint16_t runtime_cnt;



#define	CTRL_DATA_ST0  1U
#define	CTRL_DATA_SR0  2U

#define	BUFF_LEN  256U


// uint8_t txbuf[BUFF_LEN];
// uint8_t rxbuf[BUFF_LEN];


uint8_t UART_TEST[]={"ACVFST"};

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

	status = UART0_Init(SystemCoreClock, 76800);
	UART1_Init(SystemCoreClock, 76800); // 实际为9600
	UART1_Receive(&Uart1_rx_data, 1);

	if(status == MD_ERROR)
	{
		while(1); // The baud rate 0x9800cannot get at the current system clock frequency.
	}


	printf("\nHello,I am Matser\n\r\n");
	INTC_EnableIRQ(SR0_IRQn); // 开串口接收中断

	tempR = 0;
	tempG = 0;
	tempB = 0;
	LED1_OFF();
	LED2_OFF();
	// LED3_OFF();

	WIFI_SET();
	// // // IT_Init(RTC_64MHZ, 1);	// 92us
	IT_Init(RTC_64MHZ, 1 );	// test
	IT_Start();
	INTC_DisableIRQ(IT_IRQn); /* disable INTIT interrupt */
	/* ADC_Init(); */
	ADC_Set_HardTrigger(1, AD_TRG_IT);
	ADC_Set_Clock(CLOCK_DIV8, 0x0DU);
	ADC_Start(ADC_CHANNEL_0);
	DMA_Start(DMA_VECTOR_ADC, CTRL_DATA_ADC, DMA_MODE_NORMAL,
			  DMA_SIZE_HALF, ADC_CNT, (uint16_t *)&ADC->ADCR, ADC_Buffer);

	User_TM40_IntervalTimer(TM4_CHANNEL_0,5);
	INTC_EnableIRQ(TM00_IRQn);
	RTC_Init(RTC_64MHZ);
    RTC_Start();
	wifi_protocol_init();
	SYS_Init();
	E_Type = 7;
	E_Color = 0;
	SYS.POWER_SW = STA_ON;
	Light_Owner = Light_Owner_MCU;
	// Data_Init();


	/*虚假数据*/

	// // ModeArray[0].Sum = Dynamic_SUM;
    // // ModeArray[1].Sum = Static_SUM;
    // // ModeArray[2].Sum = Rhythm_SUM;

	SYS.Brightness.Target = SYS.Brightness.Set = SYS.Brightness.Now = 255;

	delayMS(100);
	SPI_Init();

	// MemoryStruct_Read();
/*
	Slave_DataInit();
	// slave_data_debug();
	Slave_SelfTest();
	EF_Work.EF_ID=3;
	Effect_Init();



	Effect_DefaultParaData_Init();
	Verify_EF_data();
	Verify_PlayList_data();
	*/
	printf("V1.0.0\r\n");

	// DMA_Stop(DMA_VECTOR_ST0);
	// Debug();
	while (1)
	{
		if (T_4MS_FLAG_GetBit)
		{
			T_4MS_FLAG_ClrBit();
			wifi_uart_service();
			// OTA_ResetFlag();

		}
		if (T_8MS_FLAG_GetBit)
		{
			T_8MS_FLAG_ClrBit();

		}
		if (T_20MS_FLAG_GetBit)
		{
			T_20MS_FLAG_ClrBit();
			// IR_Decode();
			// Motion_Output();
			MIC_Process();
			KeyS_On();

			KeyS_Click();
			Lignt_Control();

			ADC_Start(ADC_CHANNEL_0);
			DMA_Start(DMA_VECTOR_ADC, CTRL_DATA_ADC, DMA_MODE_NORMAL,
					  DMA_SIZE_HALF, ADC_CNT, (uint16_t *)&ADC->ADCR, ADC_Buffer);

			// // // Light_AD_Test();

			// //  Mode_num=2;
			// Frame_Working();

			// // // Scene_MOD();

			// Motion_Output();
			// MIC_Process();
		}
		if (T_28MS_FLAG_GetBit)
		{
			T_28MS_FLAG_ClrBit();

			LED_Display();

			// UART1_Send(&UART_TEST,9);
		}
		if (T_100MS_FLAG_GetBit)
		{
			T_100MS_FLAG_ClrBit();
			// // printf("%d\r\n",EF_Work.EF_ID);
		}
		if (T_200MS_FLAG_GetBit)
		{
			T_200MS_FLAG_ClrBit();
			// printf("test\r\n");
//////			LED2_REV();
		}
		if (T_500MS_FLAG_GetBit)
		{
			T_500MS_FLAG_ClrBit();

			// OTA_ResetFlag();

		}
		if (T_1000MS_FLAG_GetBit)
		{
			T_1000MS_FLAG_ClrBit();
			RTC_Task();
			Debug();
			// SPI_FlashDebug();
			// SYS_Record();
			// LED1_REV();
			//  printf("\r\nAPP running %d S\r\n",RunningTimeCnt++);
			// KeyS_On();
			// APP_checksum_verify(1);
			// printf("test\r\n");
			// APP_update_check();
			// // // runtime_cnt=0x1234;

			// runtime_cnt++;
			// printf("%d\r\n",sizeof(UserData_TypeDef));
			// Memory_AutoUpdate();

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
