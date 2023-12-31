/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-04-01 16:53:48
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
 * @LastEditTime: 2023-12-02 11:25:39
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\Include\Function_Init.H
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
 * @Author: your name
 * @Date: 2022-04-01 16:53:48
 * @LastEditTime: 2022-06-10 16:01:20
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @Description: ??koroFileHeader???? ????: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \A5441_Master_CMS32L051\Project\USER\Include\Function_Init.H
 */

#ifndef _Function_Init_H_
#define _Function_Init_H_

// // #include "Function_Init.H"
#include <stdlib.h>
#include "userdefine.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "CMS32L051.h"
#include "sci.h"
#include "gpio.h"
#include "tim4.h"
#include "adc.h"
#include "flash.h"
#include "rtc.h"
#include "dma.h"
#include"wdt.h"


#include "FIFO.h"
#include "IR.H"
#include "image.H"
#include "Color.H"

#include "Light.H"
#include "key.h"
#include "Com.H"
#include "fft.h"
#include "uart.h"
#include "A5441_Master.h"
#include "Sys.h"
#include "ware.h"

#include "wifi.h"
#include "memory.h"
#include "driver_spi.h"
#include "driver_w25qxx.h"
#include "motion.h"
#include "colorbox.h"
#include "OTA.h"
#include "MEM.h"
#include "Inf.h"


#include "comapp.h"
#include "user_memory.h"
#include "debug.h"
#include "flashapp.h"
#include "default_data.h"
#include "internal_memory.h"
#include "newota.h"
#include "master.h"
#include "play.h"
#include "slave.h"
#include "factory.h"
#include "version.h"
#include "parse.h"
#include "ProtocolCom.H"
#include "flow.h"
#include "mic.h"
#include "calibration.H"
// // #include "L0.H"
// // #include "L0_slave.h"
#include "appfunction.h"    
#include "printlog.h"




#define IR_Version 0

#define MAXNUM_32_BIT 0xFFFFFFFF

/* OTA固件生成需要确认的地方 */

// #define OLD_VERSION 1

#ifdef OLD_VERSION

#define LED_R_PORT PORT12
#define LED_B_PORT PORT12

#define LED_R_PIN PIN3 
#define LED_B_PIN PIN4 

#define LED_Blue_flash() PORT_ToggleBit(LED_B_PORT, LED_B_PIN) // 闪烁
#define LED_Blue_on() PORT_SetBit(LED_B_PORT, LED_B_PIN)       // 亮
#define LED_Blue_off() PORT_ClrBit(LED_B_PORT, LED_B_PIN)      // 灭

#define LED_Red_flash() PORT_ToggleBit(LED_R_PORT, LED_R_PIN) // 闪烁
#define LED_Red_on() PORT_SetBit(LED_R_PORT, LED_R_PIN)       // 亮
#define LED_Red_off() PORT_ClrBit(LED_R_PORT, LED_R_PIN)      // 灭


#else

#define LED_R_PORT PORT12
#define LED_B_PORT PORT12

#define LED_R_PIN PIN4  // 新板
#define LED_B_PIN PIN3  // 新板

#define LED_Blue_flash() PORT_ToggleBit(LED_B_PORT, LED_B_PIN) // 闪烁
#define LED_Blue_on() PORT_ClrBit(LED_B_PORT, LED_B_PIN)       // 亮
#define LED_Blue_off() PORT_SetBit(LED_B_PORT, LED_B_PIN)      // 灭

#define LED_Red_flash() PORT_ToggleBit(LED_R_PORT, LED_R_PIN) // 闪烁
#define LED_Red_on() PORT_ClrBit(LED_R_PORT, LED_R_PIN)       // 亮
#define LED_Red_off() PORT_SetBit(LED_R_PORT, LED_R_PIN)      // 灭



#endif




// // // #define LED_R_PIN PIN3  // 旧板
// // // #define LED_B_PIN PIN4  // 旧板


#define LED1_ON() PORT_SetBit(PORT12, PIN4)
#define LED1_OFF() PORT_ClrBit(PORT12, PIN4)

#define LED2_ON() PORT_SetBit(PORT12, PIN3)
#define LED2_OFF() PORT_ClrBit(PORT12, PIN3)

#define LED1_REV() PORT_ToggleBit(PORT12, PIN4);
#define LED2_REV() PORT_ToggleBit(PORT12, PIN3);



#define LED_FLASH_INTURN()                  \
    LED_Blue_flash();                       \
    if (PORT_GetBit(LED_B_PORT, LED_B_PIN)) \
    {                                       \
        PORT_ClrBit(LED_R_PORT, LED_R_PIN); \
    }                                       \
    else                                    \
    {                                       \
        PORT_SetBit(LED_R_PORT, LED_R_PIN); \
    }


extern unsigned char temp;
extern uint16_t avg;

// #define LED3_REV()                 \
//     if (PORT_GetBit(PORT12, PIN2)) \
//     {                              \
//         PORT_ClrBit(PORT12, PIN2); \
//     }                              \
//     else                           \
//     {                              \
//         PORT_SetBit(PORT12, PIN2); \
//     }

// // // // // #define LED4_REV()                 \
// // // // //     if (PORT_GetBit(PORT12, PIN3)) \
// // // // //     {                              \
// // // // //         PORT_ClrBit(PORT12, PIN3); \
// // // // //     }                              \
// // // // //     else                           \
// // // // //     {                              \
// // // //         PORT_SetBit(PORT12, PIN3); \
// // // // //     }

/*  IO  */

#define K1_sta  PORT_GetBit(PORT1, PIN4)
#define K2_sta  PORT_GetBit(PORT1, PIN3)
#define K3_sta  PORT_GetBit(PORT1, PIN2)
#define K4_sta  PORT_GetBit(PORT1, PIN1)
#define K5_sta  PORT_GetBit(PORT2, PIN2)

/*
 VCC 4095

 中间值			3756
 5/6Vcc 3413
 中间值			3345
 4/5Vcc 3276
 中间值			3173
 3/4Vcc 3071
 中间值			2900
 2/3Vcc 2730
 中间值  		2388
 1/2Vcc 2047
 中间值	 		1023
         0
*/

#define Ref_ON  3756
#define	Ref_K5	3345	//
#define	Ref_K4	3173	//
#define	Ref_K3	2900	//
#define	Ref_K2	2388	//
#define	Ref_K1	1023	//


/*   Timer  */

extern unsigned char Tick_Clock_Flag;   // 滴答时钟标志位

#define T_1000MS_VALUE	250
#define T_500MS_VALUE	125
#define T_200MS_VALUE 	50
#define T_100MS_VALUE 	25
#define T_28MS_VALUE  	7
#define T_20MS_VALUE  	5
#define T_8MS_VALUE	    2
#define T_4MS_VALUE 	1

#define T_1000MS_FLAG_SetBit()   Tick_Clock_Flag |= 0x80
#define T_500MS_FLAG_SetBit()    Tick_Clock_Flag |= 0x40
#define T_200MS_FLAG_SetBit()    Tick_Clock_Flag |= 0x20
#define T_100MS_FLAG_SetBit()    Tick_Clock_Flag |= 0x10
#define T_28MS_FLAG_SetBit()     Tick_Clock_Flag |= 0x08
#define T_20MS_FLAG_SetBit()     Tick_Clock_Flag |= 0x04
#define T_8MS_FLAG_SetBit()      Tick_Clock_Flag |= 0x02
#define T_4MS_FLAG_SetBit()      Tick_Clock_Flag |= 0x01

#define T_1000MS_FLAG_ClrBit()   Tick_Clock_Flag &= 0x7F
#define T_500MS_FLAG_ClrBit()    Tick_Clock_Flag &= 0xBF
#define T_200MS_FLAG_ClrBit()    Tick_Clock_Flag &= 0xDF
#define T_100MS_FLAG_ClrBit()    Tick_Clock_Flag &= 0xEF
#define T_28MS_FLAG_ClrBit()     Tick_Clock_Flag &= 0xF7
#define T_20MS_FLAG_ClrBit()     Tick_Clock_Flag &= 0xFB
#define T_8MS_FLAG_ClrBit()      Tick_Clock_Flag &= 0xFD
#define T_4MS_FLAG_ClrBit()      Tick_Clock_Flag &= 0xFE

#define T_1000MS_FLAG_GetBit   Tick_Clock_Flag & 0x80
#define T_500MS_FLAG_GetBit    Tick_Clock_Flag & 0x40
#define T_200MS_FLAG_GetBit    Tick_Clock_Flag & 0x20
#define T_100MS_FLAG_GetBit    Tick_Clock_Flag & 0x10
#define T_28MS_FLAG_GetBit     Tick_Clock_Flag & 0x08
#define T_20MS_FLAG_GetBit     Tick_Clock_Flag & 0x04
#define T_8MS_FLAG_GetBit      Tick_Clock_Flag & 0x02
#define T_4MS_FLAG_GetBit      Tick_Clock_Flag & 0x01


/* */

/*   Remote  */

#define Rm_S12_FLAG_SetBit() Remote_Key |= 0x0800
#define Rm_S11_FLAG_SetBit() Remote_Key |= 0x0400
#define Rm_S10_FLAG_SetBit() Remote_Key |= 0x0200
#define Rm_S9_FLAG_SetBit()  Remote_Key |= 0x0100
#define Rm_S8_FLAG_SetBit()  Remote_Key |= 0x0080
#define Rm_S7_FLAG_SetBit()  Remote_Key |= 0x0040
#define Rm_S6_FLAG_SetBit()  Remote_Key |= 0x0020
#define Rm_S5_FLAG_SetBit()  Remote_Key |= 0x0010
#define Rm_S4_FLAG_SetBit()  Remote_Key |= 0x0008
#define Rm_S3_FLAG_SetBit()  Remote_Key |= 0x0004
#define Rm_S2_FLAG_SetBit()  Remote_Key |= 0x0002
#define Rm_S1_FLAG_SetBit()  Remote_Key |= 0x0001

#define Rm_S12_FLAG_ClrBit() Remote_Key &= 0xF7FF
#define Rm_S11_FLAG_ClrBit() Remote_Key &= 0xFBFF
#define Rm_S10_FLAG_ClrBit() Remote_Key &= 0xFDFF
#define Rm_S9_FLAG_ClrBit()  Remote_Key &= 0xFEFF
#define Rm_S8_FLAG_ClrBit()  Remote_Key &= 0xFF7F
#define Rm_S7_FLAG_ClrBit()  Remote_Key &= 0xFFBF
#define Rm_S6_FLAG_ClrBit()  Remote_Key &= 0xFFDF
#define Rm_S5_FLAG_ClrBit()  Remote_Key &= 0xFFEF
#define Rm_S4_FLAG_ClrBit()  Remote_Key &= 0xFFF7
#define Rm_S3_FLAG_ClrBit()  Remote_Key &= 0xFFFB
#define Rm_S2_FLAG_ClrBit()  Remote_Key &= 0xFFFD
#define Rm_S1_FLAG_ClrBit()  Remote_Key &= 0xFFFE

#define Rm_S12_STA Remote_Key & 0x0800
#define Rm_S11_STA Remote_Key & 0x0400
#define Rm_S10_STA Remote_Key & 0x0200
#define Rm_S9_STA  Remote_Key & 0x0100
#define Rm_S8_STA  Remote_Key & 0x0080
#define Rm_S7_STA  Remote_Key & 0x0040
#define Rm_S6_STA  Remote_Key & 0x0020
#define Rm_S5_STA  Remote_Key & 0x0010
#define Rm_S4_STA  Remote_Key & 0x0008
#define Rm_S3_STA  Remote_Key & 0x0004
#define Rm_S2_STA  Remote_Key & 0x0002
#define Rm_S1_STA  Remote_Key & 0x0001

/* */

/*   Flash  */






/* */


extern void MAMAMAM_asdbnwudh(void);

extern void test_asdbnwudh(void);


extern void GPIO_Init(void);
extern void SYS_Init(void);
// void SYS_Clock_Tick(void);
extern void SYS_Clock_Tick(void);

extern void delay(unsigned int ms);
void User_TM40_IntervalTimer(tm4_channel_t ch, uint16_t num);
void User_TM41_IntervalTimer(tm4_channel_t ch, uint16_t num);

void Uart_Buffer_POP(FIFOTypeDef *StructDAT);
void Timer40_Interrupt(void);

void KeyS_Click(void);
unsigned int  Rhythm_Cal(unsigned int adc_val);

void All_Color_Calculate(void);
void Image_Reset(void);

void Data_TX(unsigned char add, unsigned char bri, unsigned char RR, unsigned char GG, unsigned char BB, unsigned char WW);
void Lignt_Control(void);
void Flash_Update(void);
void UID_Read(void);

//delay
void delay_10us(void);


void Rhythm_Effect(void);
void Sound_Process(void);



void ID_Init(void);
void Memory_Read(void);
void Menory_Write(void);
void Data_Init(void);
unsigned char Random_Generate(void);

void Remote_Click(unsigned char *KeyVal);
void HEX_Convert(unsigned int HEXtemp);

void delayMS(uint32_t n);

#endif
