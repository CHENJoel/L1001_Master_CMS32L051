
#include "Function_Init.H"
#include "A5441_Master.h"



PlayingStateTypeDef PlayingState;

// uint8_t test_buffer[256];

// ModeTypeDef Dynam,Stati,Rhyth;  // 动态、静态、律动

// // // SYS_TypeDef SYS;

DeviceTypeDef TangramDevice;
// // ModeTypeDef ModeArray[3];

uint8_t Mode_num;
uint8_t Light_Owner; // 0：MCU控灯    1：APP控灯
uint8_t Work_MOD;    // 亮灯/配对
uint8_t Last_Work_MOD;
uint8_t Uart1_rx_data; // 串口1接收的数据

uint8_t uart1_sendend_flag; // 串口1发送结束标志

/* 新灯效 */

uint8_t numtemp;




unsigned char E_Type;  // 灯效类型
unsigned char E_Color; // 灯效颜色
unsigned char Effect_Num;   // 当前灯效编号

// uint8_t EffextImage_num;    // 效果编号

unsigned char Tick_Clock_Flag;   // 滴答时钟标志位

extern unsigned char NOW,TAR;



unsigned char Light_Sum;        // 在线灯组数量


unsigned char UID_Array[16];
unsigned char UID_8bit;


unsigned char Device_Chief_ID; // 主ID
unsigned char Device_Minor_ID; // 副ID
unsigned char Device_Commu_ID; // 通讯ID
unsigned char Device_Type;     // 设备类型

unsigned char Random_sys;  // 发生系统随机数
unsigned char Random_base; // 随机基础数

uint8_t Bufferarray[1][6];  // 待删

unsigned char SlaveDevive_Num; // 已链接的从机数量
unsigned char ModuleLight_Num; // 灯光序列数量
unsigned char Module_Num;      // 已链接的从机序列数量
unsigned char Slave_Array[1][Slave_Data_num]; // 从机设备信息 // 待删
/*
                      // 从机设备信息
[0] Device_Chief_ID;  // 主ID (0x00~0xFA)
[1] Device_Minor_ID;  // 副ID (0x00~0xFF)
[2] Device_FixedID;   // 固定ID (0x80~0xB0) 预设灯效 使用该ID
[3] Device_SeriesNum; // 序列ID (0x00~0x15) 流光顺序 参考该ID
[4] Device_Type;      // 设备类型 (0x80~0xB0)

[5] Device_Commu_ID; // 通讯ID (0x30~0x45)  控制单机 使用该ID
[6] Device_Light_ID; // 灯光ID (0x00~0x15)  通用灯效 使用该ID
[7]                  // 高四位为该固定ID的总设备数,低四位为该固定ID的标号
[8]                  // 临时序列ID
[9]                  // 临时变量
*/
uint8_t FixedID_DeviceData[8][1];   // 待删
/*
[0][0] Triangle_A1 [0][1] 拥有该固定ID的设备数量  [0][2]~[0][17] 设备通讯地址
[1][0] Triangle_A2 [1][1] 拥有该固定ID的设备数量
[2][0] Triangle_B1 [2][1] 拥有该固定ID的设备数量
[3][0] Triangle_C1 [3][1] 拥有该固定ID的设备数量
[4][0] Triangle_C2 [4][1] 拥有该固定ID的设备数量
[5][0] Triangle_C3 [5][1] 拥有该固定ID的设备数量
[6][0] Triangle_C4 [6][1] 拥有该固定ID的设备数量
[7][0] Square      [7][1] 拥有该固定ID的设备数量
*/

uint8_t IR_KeyVal = 0xff;
uint8_t Keyboard_NumVal = 0xff; // 数字键盘值

const uint8_t IR_KeyTable[44]=
{
    0x3A, 0xBA, 0x82, 0x02,
    0x1A, 0x9A, 0xA2, 0x22,
    0x2A, 0xAA, 0x92, 0x12,
    0x0A, 0x8A, 0xB2, 0x32,
    0x38, 0xB8, 0x78, 0xF8,
    0x18, 0x98, 0x58, 0xD8,
    0x28, 0xA8, 0x68, 0xE8,
    0x08, 0x88, 0x48, 0xC8,
    0x30, 0xB0, 0x70, 0xF0,
    0x10, 0x90, 0x50, 0xD0,
    0x20, 0xA0, 0x60, 0xE0,
};


const uint8_t Numboard_KeyTable[10]=
{
/*
    0,
    1,2,3,
    4,5,6,
    7,8,9,
*/
/*    43,
    32,33,34,
    36,37,38,
    40,41,42,
*/
    28,29,30,
    32,33,34,
    36,37,38,
       41,
};


uint32_t device_id = 0, flash_id = 0;

unsigned char bhsdgudcuu=0xff;


void GPIO_Init(void)
{
    PORT_Init(PORT2, PIN0, ANALOG_INPUT);  /* (1)  P20/ANI0         */
    PORT_Init(PORT4, PIN0, INPUT);         /* (2)  P40/SWIO         */
                                        /* (3)  RESETB           */
    PORT_Init(PORT13, PIN7, INPUT);        /* (4)  P137/SWCLK       */
    PORT_Init(PORT12, PIN2, OUTPUT);       /* (5)  P122/X2/EXCLK    */
    PORT_Init(PORT12, PIN1, INPUT);        /* (6)  P121/X1          */
                                        /* (7)  VSS              */
                                        /* (8)  NC               */
                                        /* (9)  VDD              */
    PORT_Init(PORT13, PIN6, ANALOG_INPUT); /* (10) P136/INTP0/ANI36 */
    #ifdef IR_Version
        PORT_Init(PORT13, PIN6, INPUT); /* (10) P136/INTP0/ANI36 */
    #else
        PORT_Init(PORT13, PIN6, ANALOG_INPUT); /* (10) P136/INTP0/ANI36 */
    #endif
    PORT_Init(PORT2, PIN1, PULLUP_INPUT);     /* (20) P21/ANI1                        */
    PORT_Init(PORT2, PIN2, ANALOG_INPUT);     /* (19) P22/ANI2                        */
    PORT_Init(PORT2, PIN3, INPUT);            /* (18) P23/ANI3                        */
    PORT_Init(PORT1, PIN0, OUTPUT);           /* (17) P10/SCLK11/SCL11/ANI9/epwmmo00  */
    PORT_Init(PORT1, PIN1, INPUT);            /* (16) P11/SDI11/SDA11/ANI8/epwmmo01   MISO */
    // // // PORT_Init(PORT1, PIN2, OPENDRAIN_OUTPUT); /* (15) P12/SDO11/ANI13/epwmmo02        MOSI */
    // // // PORT_Init(PORT1, PIN3, OPENDRAIN_OUTPUT); /* (14) P13/ANI16/epwmmo03              SCLK */
    // // // PORT_Init(PORT1, PIN4, OPENDRAIN_OUTPUT); /* (13) P14/SDA20/ANI17/epwmmo04        CS   */
    PORT_Init(PORT1, PIN2, OUTPUT); /* (15) P12/SDO11/ANI13/epwmmo02        MOSI */
    PORT_Init(PORT1, PIN3, OUTPUT); /* (14) P13/ANI16/epwmmo03              SCLK */
    PORT_Init(PORT1, PIN4, OUTPUT); /* (13) P14/SDA20/ANI17/epwmmo04        CS   */
    PORT_Init(PORT12, PIN4, OUTPUT);          /* (12) P124/XT2/EXCLKS                 */
    PORT_Init(PORT12, PIN3, OUTPUT);          /* (11) P123/XT1                        */

    // GPIO_PullUp_Enable(PORT1, PIN1);
    // GPIO_PullUp_Enable(PORT1, PIN2);
    // GPIO_PullUp_Enable(PORT1, PIN3);
    // GPIO_PullUp_Enable(PORT1, PIN4);
}


void SYS_Init(void)
{
    flag.byte=0;
    sys_rundata_init();
    ID_Init();
    norflash_data_init();
   
    slave_online_data_init();

    global_setting_init();
    play_init();
    play_sys_effect_init();
    // schedule_factory_reset
}



/* 
 * @Description: 全局设置数据初始化
 * @param: 
 * @return: 
*/ 
void global_setting_init(void)
{
    get_global_setting(&play.work.global_setting);
}


/**
 * @description: 检测所有按键的动作
 * @param {*}
 * @return {*}
 */
void KeyS_On(void)
{
    uint8_t keyVal;
    keyVal = KEY_AD_Test();
    //  DMA_Stop(DMA_VECTOR_ADC);
    // // keyVal = ADC_Converse(ADC_CHANNEL_2, 1, &keyVal);

    Key_On(&K1, keyVal, 1, 2, 250, 1, 0);
    Key_On(&K2, keyVal, 2, 2, 50, 1, 0);
    Key_On(&K3, keyVal, 3, 2, 50, 1, 0);
    Key_On(&K4, keyVal, 4, 2, 50, 1, 0);
    Key_On(&K5, keyVal, 5, 2, 50, 1, 0);
    

    // // // // if (keyVal)
    // // // // {
    // // // //     printlog("Key:%d\r", keyVal);
    // // // // }
    
  
}








void delay(unsigned int ms)
{
    unsigned int x,y;
    for (x=ms;x>0;x--)
    {
        for (y=220;y>0;y--)
        {
            ;
        }
    }
}



/***********************************************************************************************************************
* Function Name: TM40_IntervalTimer
* @brief  TM40 specified channel operates as interval timer mode.
* @param  ch - specify the channel number
* @param  num - specify the number count clock
* @return None
***********************************************************************************************************************/
void User_TM40_IntervalTimer(tm4_channel_t ch, uint16_t num)
{
    CGC->PER0 |= CGC_PER0_TM40EN_Msk;    /* enables input clock supply */
    TM40->TPS0 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0080_TM4_CKM1_fCLK_8 | _0002_TM4_CKM0_fCLK_2;

    /* stop specify channel */
    TM40_Channel_Stop(ch);

    switch(ch)
    {
        case TM4_CHANNEL_0:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM00_IRQn);
            NVIC_ClearPendingIRQ(TM00_IRQn);
            /* Channel 0 is used as interval timer */
            TM40->TMR00 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM40->TDR00 = num - 1;
            TM40->TOE0 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
            /* enable interrupt */
            INTC_EnableIRQ(TM00_IRQn);
            break;
        case TM4_CHANNEL_1:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM01_IRQn);
            NVIC_ClearPendingIRQ(TM01_IRQn);
            /* Channel 1 is used as interval timer */
            TM40->TMR01 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM40->TDR01 = num - 1;
            TM40->TOE0 &= ~_0002_TM4_CH1_OUTPUT_ENABLE;
            /* enable interrupt */
            INTC_EnableIRQ(TM01_IRQn);
            break;
        case TM4_CHANNEL_2:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM02_IRQn);
            NVIC_ClearPendingIRQ(TM02_IRQn);
            /* Channel 2 is used as interval timer */
            TM40->TMR02 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM40->TDR02 = num - 1;
            TM40->TOE0 &= ~_0004_TM4_CH2_OUTPUT_ENABLE;
            /* enable interrupt */
            INTC_EnableIRQ(TM02_IRQn);
            break;
        case TM4_CHANNEL_3:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM03_IRQn);
            NVIC_ClearPendingIRQ(TM03_IRQn);
            /* Channel 3 is used as interval timer */
            TM40->TMR03 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM40->TDR03 = num - 1;
            TM40->TOE0 &= ~_0008_TM4_CH3_OUTPUT_ENABLE;
            /* enable interrupt */
            INTC_EnableIRQ(TM03_IRQn);
            break;
        default:
            break;
    }
    /* Start specify channel */
    TM40_Channel_Start(ch);
}
/***********************************************************************************************************************
* Function Name: ADC_Converse
* @brief  This function starts the AD converter and returns the conversion result in the buf
*         It is suitable for software trigger mode with polling mode.
* @param  ch - specify the ad channel
* @param  sz - set the times of ad conversion
* @param  buf - the address where to write the conversion result
* @return average value
***********************************************************************************************************************/
uint16_t User_ADC_Converse(adc_channel_t ch, uint32_t sz, uint16_t *buf)
{
    uint32_t i;
    volatile uint8_t  flag;
    uint32_t total = 0;

    INTC_DisableIRQ(ADC_IRQn);     /* disable INTAD interrupt */
//-----------------------------------------------------------------------
// normal mode
//-----------------------------------------------------------------------
    /* Soft Trigger one-shot select mode */
	ADC->ADM0 &= ~ADCE;
    ADC->ADM1 = _08_AD_CONVMODE_ONESELECT ;
    ADC->ADTRG = _00_AD_TRIGGER_SOFTWARE;
    ADC->ADM0 |= ADCE;

    /* specify ad channel */
    ADC->ADS  = ch;

    /* Execute ADC converse and get the conversion result */
    for (i=0; i<sz; i++)
    {
        /* ADC start */
        ADC->ADM0 |= ADCS;

        /* waiting interrupt flag */
        while(INTC_GetPendingIRQ(ADC_IRQn) == 0);
        INTC_ClearPendingIRQ(ADC_IRQn);     /* clear INTAD interrupt flag */

        /* Get the conversion result */
        *buf++ = ADC->ADCR;
        /* Calculate the total value of the conversion result */
        total += ADC->ADCR;
    }

    return (total / sz); // return average value
}



void PWM()
{
		// // TM41_PWM_1Period_3Duty(255,1,1,1);
		// delayMS(10);
		// TM41_Channel_Stop(TM4_CHANNEL_0 | TM4_CHANNEL_1 | TM4_CHANNEL_2 | TM4_CHANNEL_3);
}

void Data_TX(unsigned char add, unsigned char bri, unsigned char RR, unsigned char GG, unsigned char BB, unsigned char WW)
{
    unsigned char tempCRC;
    tempCRC = 0;
    tempCRC += add;
    tempCRC += bri;
    tempCRC += RR;
    tempCRC += GG;
    tempCRC += BB;
    tempCRC += WW;

    UART0_Send(M_HeadCOM);
    UART0_Send(add);
    UART0_Send(bri);
    UART0_Send(RR);
    UART0_Send(GG);
    UART0_Send(BB);
    UART0_Send(WW);
    UART0_Send(tempCRC);
}



void Lighting_effect_Flowing(void)
{
    static unsigned int Time_Cnt;

    // Frame_Play_Mode=1;
    //  if (Frame_Play_Mode)	// 普通帧模式
    //  {

    if (++Time_Cnt >= Frame_Time_N)
    {
        Time_Cnt = 0;
        if (Frame_Px_Num == 1) // 点成像
        {
            // Color_Flowing(&L1, 1);
            // Color_Skewing(&L2, &L1, Image_Para_1);
            // Color_Skewing(&L3, &L2, Image_Para_1);
            // Color_Skewing(&L4, &L3, Image_Para_1);

            // Color_Skewing(&L5, &L4, Image_Para_1);
            // Color_Skewing(&L6, &L5, Image_Para_1);
            // Color_Skewing(&L7, &L6, Image_Para_1);
            // Color_Skewing(&L8, &L7, Image_Para_1);

            // Color_Skewing(&L9, &L8, Image_Para_1);
            // Color_Skewing(&L10, &L9, Image_Para_1);
            // Color_Skewing(&L11, &L10, Image_Para_1);
            // Color_Skewing(&L12, &L11, Image_Para_1);

            // Color_Skewing(&L13, &L12, Image_Para_1);
            // Color_Skewing(&L14, &L13, Image_Para_1);
            // Color_Skewing(&L15, &L14, Image_Para_1);
            // Color_Skewing(&L16, &L1, Image_Para_1);

            // Pixel_Calculate(&L1, FrameArry_Add, 0);
            // Pixel_Calculate(&L2, FrameArry_Add, 0);
            // Pixel_Calculate(&L3, FrameArry_Add, 0);
            // Pixel_Calculate(&L4, FrameArry_Add, 0);

            // Pixel_Calculate(&L5, FrameArry_Add, 0);
            // Pixel_Calculate(&L6, FrameArry_Add, 0);
            // Pixel_Calculate(&L7, FrameArry_Add, 0);
            // Pixel_Calculate(&L8, FrameArry_Add, 0);

            // Pixel_Calculate(&L9, FrameArry_Add, 0);
            // Pixel_Calculate(&L10, FrameArry_Add, 0);
            // Pixel_Calculate(&L11, FrameArry_Add, 0);
            // Pixel_Calculate(&L12, FrameArry_Add, 0);

            // Pixel_Calculate(&L13, FrameArry_Add, 0);
            // Pixel_Calculate(&L14, FrameArry_Add, 0);
            // Pixel_Calculate(&L15, FrameArry_Add, 0);
            // Pixel_Calculate(&L16, FrameArry_Add, 0);
        }
        else
        {
        }
    }

    // // // // if (++Time_Cnt >= 0)
    // // // // {
    // // // // 	Time_Cnt = 0;

    // Color_Flowing(&L1, 1);

    // // // // 	// // L1.Frame_Now=Random%16;
    // // // L2.Frame_Now = L1.Frame_Now;
    // // // L3.Frame_Now = L1.Frame_Now;
    // // // L4.Frame_Now = L1.Frame_Now;

    // // // L5.Frame_Now = L1.Frame_Now;
    // // // L6.Frame_Now = L1.Frame_Now;
    // // // L7.Frame_Now = L1.Frame_Now;
    // // // L8.Frame_Now = L1.Frame_Now;

    // // Pixel_Calculate(&L1, FrameArry_Add, 0);
    // // Pixel_Calculate(&L2, FrameArry_Add, 1);
    // // Pixel_Calculate(&L3, FrameArry_Add, 2);
    // // Pixel_Calculate(&L4, FrameArry_Add, 3);

    // // Pixel_Calculate(&L5, FrameArry_Add, 4);
    // // Pixel_Calculate(&L6, FrameArry_Add, 5);
    // // Pixel_Calculate(&L7, FrameArry_Add, 6);
    // // Pixel_Calculate(&L8, FrameArry_Add, 7);

    // // Pixel_Calculate(&L9, FrameArry_Add, 8);
    // // Pixel_Calculate(&L10, FrameArry_Add, 9);
    // // Pixel_Calculate(&L11, FrameArry_Add, 10);
    // // Pixel_Calculate(&L12, FrameArry_Add, 11);

    // // Pixel_Calculate(&L13, FrameArry_Add, 12);
    // // Pixel_Calculate(&L14, FrameArry_Add, 13);
    // // Pixel_Calculate(&L15, FrameArry_Add, 14);
    // Pixel_Calculate(&L16, FrameArry_Add, 15);

    // All_Color_DirectChange();
    // All_Color_Send();
    // // // // }

    // // // // // 	if (Frame_time == 0)
    // // // // // 	{

    // printf("L1= %d\n",L1.Frame_Now);
    // printf("L2= %d\n",L2.Frame_Now);
    // printf("L3= %d\r\n",L3.Frame_Now);

    // All_Color_Calculate();

    // Pixel_Calculate(&L1, EffectAddress[0][1], 0);
    // Pixel_Calculate(&L2, EffectAddress[0][1], 0);
    // Pixel_Calculate(&L3, EffectAddress[0][1], 0);
    // Pixel_Calculate(&L4, EffectAddress[0][1], 0);

    // Pixel_Calculate(&L5, EffectAddress[0][1], 0);
    // Pixel_Calculate(&L6, EffectAddress[0][1], 0);
    // Pixel_Calculate(&L7, EffectAddress[0][1], 0);
    // Pixel_Calculate(&L8, EffectAddress[0][1], 0);

    // (&L1);
    // // // // // 	}


    // E_Type = 0;
    // E_Color = 0;
    // // printf("\nTy %d\n",E_Type);
    // // printf("Co %d\n",E_Color);
    // // // printf("G= %d\n",L1.G);
    // // printf("R= %d\n",L1.R.Now);
    // // printf("G= %d\n",L1.G.Now);
    // // printf("B= %d\n",L1.B.Now);
    // // printf("F= %d\r\n",L1.Frame_Now);

}

void Image_Reset(void)
{
    // Tangram[0].Frame_Now=0;
    // Tangram[1].Frame_Now=0;
    // Tangram[2].Frame_Now=0;
    // Tangram[3].Frame_Now=0;

    // Tangram[4].Frame_Now=0;
    // Tangram[5].Frame_Now=0;
    // Tangram[6].Frame_Now=0;
    // Tangram[7].Frame_Now=0;

    // Tangram[8].Frame_Now=0;
    // Tangram[9].Frame_Now=0;
    // Tangram[10].Frame_Now=0;
    // Tangram[11].Frame_Now=0;

    // Tangram[12].Frame_Now=0;
    // Tangram[13].Frame_Now=0;
    // Tangram[14].Frame_Now=0;
    // Tangram[15].Frame_Now=0;




    // // L1.Frame_Now=0;
    // // L2.Frame_Now=0;
    // // L3.Frame_Now=0;
    // // L4.Frame_Now=0;

    // // L5.Frame_Now=0;
    // // L6.Frame_Now=0;
    // // L7.Frame_Now=0;
    // // L8.Frame_Now=0;

    // // L9.Frame_Now=0;
    // // L10.Frame_Now=0;
    // // L11.Frame_Now=0;
    // // L12.Frame_Now=0;

    // // L13.Frame_Now=0;
    // // L14.Frame_Now=0;
    // // L15.Frame_Now=0;
    // // L16.Frame_Now=0;
}

void All_Color_DirectChange(void)
{
//    Color_DirectChange(&L1);
//    Color_DirectChange(&L2);
//    Color_DirectChange(&L3);
//    Color_DirectChange(&L4);

//    Color_DirectChange(&L5);
//    Color_DirectChange(&L6);
//    Color_DirectChange(&L7);
//    Color_DirectChange(&L8);

//    Color_DirectChange(&L9);
//    Color_DirectChange(&L10);
//    Color_DirectChange(&L11);
//    Color_DirectChange(&L12);

//    Color_DirectChange(&L13);
//    Color_DirectChange(&L14);
//    Color_DirectChange(&L15);
//    Color_DirectChange(&L16);
}
void All_Color_Calculate(void)
{
    // Pixel_Calculate(&L16, FrameArry_Add, 0);

    // Pixel_Calculate(&L1, EffectAddress[0][1], 0);
    // Pixel_Calculate(&L2, EffectAddress[0][1], 0);
    // Pixel_Calculate(&L3, EffectAddress[0][1], 0);
    // Pixel_Calculate(&L4, EffectAddress[0][1], 0);

    // Pixel_Calculate(&L5, EffectAddress[0][1], 0);
    // Pixel_Calculate(&L6, EffectAddress[0][1], 0);
    // Pixel_Calculate(&L7, EffectAddress[0][1], 0);
    // Pixel_Calculate(&L8, EffectAddress[0][1], 0);

    // Color_Calculate(ColorTable[Effect_Type][Effect_Color], &L9);
    // Color_Calculate(ColorTable[Effect_Type][Effect_Color], &L10);
    // Color_Calculate(ColorTable[Effect_Type][Effect_Color], &L11);
    // Color_Calculate(ColorTable[Effect_Type][Effect_Color], &L12);

    // Color_Calculate(ColorTable[Effect_Type][Effect_Color], &L13);
    // Color_Calculate(ColorTable[Effect_Type][Effect_Color], &L14);
    // Color_Calculate(ColorTable[Effect_Type][Effect_Color], &L15);
    // Color_Calculate(ColorTable[Effect_Type][Effect_Color], &L16);
}



void Sound_Process(void)
{
    // // unsigned int Soundtemp;
    // // unsigned int ttemp = 0;
    // // unsigned char i;
    // // if (DMAVEC->CTRL[CTRL_DATA_ADC].DMACT == 0)
    // // {
    // //     for (i = 0; i < ADC_CNT; i++)
    // //     {
    // //         if (ADC_Buffer[i] < 2048)
    // //         {
    // //             ttemp = 2048 - ADC_Buffer[i];
    // //         }
    // //         else
    // //         {
    // //             ttemp = ADC_Buffer[i] - 2048;
    // //         }
    // //         Soundtemp +=ttemp;
    // //     }
    // //     Soundtemp = Soundtemp / ADC_CNT;
    // //     // printf("A%d\n",Soundtemp);
    // //     if (Soundtemp<10)
    // //     {
    // //         L4.G.Now=10;
    // //     }
    // //     else if (Soundtemp>255)
    // //     {
    // //         L4.G.Now=255;
    // //     }

    // //     else
    // //     {
    // //         L4.G.Now=Soundtemp;
    // //     }

    // //     printf("%d\n",Soundtemp);
    // //     FFT_Flash = 1;
    // // }
}

void Rhythm_Effect()
{

}

void All_Color_Send(void)
{
    // if (On_Flag)
    // {
    // Color_Data_Send(&L1,0X00);
    // Color_Data_Send(&L2,0X01);
    // Color_Data_Send(&L3,0X02);
    // Color_Data_Send(&L4,0X03);

    // Color_Data_Send(&L5,0X04);
    // Color_Data_Send(&L6,0X05);
    // Color_Data_Send(&L7,0X06);
    // Color_Data_Send(&L8,0X07);

    // Color_Data_Send(&L9,0X08);
    // Color_Data_Send(&L10,0X09);
    // Color_Data_Send(&L11,0X0A);
    // Color_Data_Send(&L12,0X0B);

    // Color_Data_Send(&L13,0X0C);
    // Color_Data_Send(&L14,0X0D);
    // Color_Data_Send(&L15,0X0E);
    // Color_Data_Send(&L16,0X0F);

    // demo_Send(&L16,5);
    // }
    // else
    // {
    // 	Data_Send(0, 0, 0, 0);
    // 	Data_Send(1, 0, 0, 0);
    // 	Data_Send(2, 0, 0, 0);
    // 	Data_Send(3, 0, 0, 0);

    // 	Data_Send(4, 0, 0, 0);
    // 	Data_Send(5, 0, 0, 0);
    // 	Data_Send(6, 0, 0, 0);
    // 	Data_Send(7, 0, 0, 0);

    // 	Data_Send(8, 0, 0, 0);
    // 	Data_Send(9, 0, 0, 0);
    // 	Data_Send(10, 0, 0, 0);
    // 	Data_Send(11, 0, 0, 0);

    // 	Data_Send(12, 0, 0, 0);
    // 	Data_Send(13, 0, 0, 0);
    // 	Data_Send(14, 0, 0, 0);
    // 	Data_Send(15, 0, 0, 0);
    // }
}


unsigned int  Rhythm_Cal(unsigned int adc_val)
{
    unsigned int temp;
    if (adc_val > 2047)
    {
        temp = adc_val - 2047;
    }
    else
    {
        temp = 2047 - adc_val;
    }
    // printf("A%d\r", adc_val);
    // printf("B%d\r\n", temp);
    return temp;
}


void Light_CMD_Send(unsigned char Cmd, unsigned char add,unsigned char Val1, unsigned char Val2)
{
    /*
        0.帧头
        1.地址
        2.指令
        3.值1
        4.值2
        5.CRC
        6.帧尾
    */
    unsigned char tempCRC;
    tempCRC = 0;
    tempCRC += add;
    tempCRC += Cmd;
    tempCRC += Val1;
    tempCRC += Val2;
    UART0_Send(M_HeadCOM);
    UART0_Send(add);
    UART0_Send(Cmd);
    UART0_Send(Val1);
    UART0_Send(Val2);
    UART0_Send(tempCRC);
//    UART0_Send(FrameTail);
}






void ID_Init(void)
{
    uint32_t *w_ptr;
    unsigned char i;
    unsigned char UID_Array[16];    // 128bit 唯一码
    w_ptr = (uint32_t *)0x00500894;
    Device_Chief_ID = 0;
    for (i = 0; i < 16; i++)
    {
        UID_Array[i] = *w_ptr++;
        Device_Chief_ID += UID_Array[i];
    }
    if (Device_Chief_ID > 250)  // 251~255为功能保留地址，需要避让
    {
        Device_Chief_ID += 10;
    }
    Random_base = 0;
    for (i = 0; i < 16;)
    {
        Random_base += UID_Array[i]; // 产生随机数种子
        i += 2;
    }
    srand(Random_base); // 随机数播种
}

void Memory_Read(void)
{
    uint32_t *w_ptr;
    unsigned char i;
    uint32_t Memory_Buffer[16];
    w_ptr = (uint32_t *)0x500000;
    for (i = 0; i < sizeof(Memory_Buffer) / 4; i++)
    {
        Memory_Buffer[i] = *w_ptr++;
    }
    Device_Minor_ID = Memory_Buffer[1]; // 副ID
    Device_Commu_ID = Memory_Buffer[2]; // 通讯ID
    // Device_Light_ID = Memory_Buffer[3];  // 灯光ID
    // Device_SeriesNum = Memory_Buffer[4]; // 序列编号
    Device_Type = Memory_Buffer[5];      // 设备类型

    // printf("%d\n", Memory_Buffer[1]);
    // printf("%d\n", Memory_Buffer[2]);
    // printf("%d\n", Memory_Buffer[3]);
    // printf("%d\n", Memory_Buffer[4]);
    // printf("%d\n\n", Memory_Buffer[5]);
}

void Menory_Write(void)
{
    static unsigned char test;
    uint32_t Memory_Buffer[16];
    Memory_Buffer[1] = Device_Minor_ID; // 副ID
    Memory_Buffer[2] = Device_Commu_ID; // 通讯ID
    // Memory_Buffer[3] = Device_Light_ID;  // 灯光ID
    // Memory_Buffer[4] = Device_SeriesNum; // 序列编号
    Memory_Buffer[5] = Device_Type;      // 设备类型

    EraseSector(0x500000);
    ProgramPage(0x500000, sizeof(Memory_Buffer), (uint8_t *)Memory_Buffer);
}

void Data_Init(void)
{
    uint8_t i;
    Memory_Read();
    ID_Init();
    delay_20ms();

//    FixedID_DeviceData[0][0]=Triangle_A1;
//    FixedID_DeviceData[1][0]=Triangle_A2;
//    FixedID_DeviceData[2][0]=Triangle_B1;
//    FixedID_DeviceData[3][0]=Triangle_C1;
//    FixedID_DeviceData[4][0]=Triangle_C2;
//    FixedID_DeviceData[5][0]=Triangle_C3;
//    FixedID_DeviceData[6][0]=Triangle_C4;
//    FixedID_DeviceData[7][0]=Square;

    Slave_Handshake();
    Slave_Allocate_ID();

    // ModeArray[0].Sum = 95;
    // ModeArray[1].Sum = 20;
    // ModeArray[2].Sum = 1;

    // for ( i = 0; i < ModuleLight_Num; i++)
    // {
    //     // Tangram[i].Priority=ModuleLight_Num;
    //     Tangram[i].Model.Priority=255;
    // }


}


// // // // /**
// // // //  * @description:
// // // //  * @param {FIFOTypeDef} *StructDAT
// // // //  * @return {*}
// // // //  */
// // // // void Uart_Buffer_POP(FIFOTypeDef *StructDAT)
// // // // {
// // // //     unsigned char temp;
// // // //     for (temp = 0; temp < 1000; temp++) // 单次限制处理（取出）50个数据
// // // //     {
// // // //         if ((*StructDAT).Read != (*StructDAT).Write) // 缓存数据未完全处理（读出）
// // // //         {
// // // //             /* USER CODE BEGIN */

// // // //             /* (*StructDAT).Read 指向当前需要处理的数据 */

// // // //             // if (FrameTail == FrameTail_SET) // 出现帧尾
// // // //             // {
// // // //             //     if (M_HeadCOM == M_HeadCOM) // 校验帧头
// // // //             //     {
// // // //             //     }
// // // //             // }
// // // //             // UART0_Send((*StructDAT).Buffer[(*StructDAT).Read]);
// // // //             printf("%d %d %d %d\r",(*StructDAT).Write,(*StructDAT).Read,(*StructDAT).Buffer[(*StructDAT).Read],(*StructDAT).Buffer[(*StructDAT).Read+1]);

// // // //             /* USER CODE END */
// // // //             if ((*StructDAT).Read < (FIFO_Buffer_Size - 1)) // 指出下次处理的数据的地址
// // // //             {
// // // //                 (*StructDAT).Read++;
// // // //             }
// // // //             else
// // // //             {
// // // //                 (*StructDAT).Read = 0;
// // // //             }
// // // //         }
// // // //         else
// // // //         {
// // // //             break;
// // // //         }
// // // //     }
// // // // }

void HEX_Convert(unsigned int HEXtemp)
{
    unsigned char WAN, QIAN, BAI, SHI, GE;
    WAN = HEXtemp / 10000;
    QIAN = HEXtemp % 10000 / 1000;
    BAI = HEXtemp % 10000 % 1000 / 100;
    SHI = HEXtemp % 10000 % 1000 % 100 / 10;
    GE = HEXtemp % 10000 % 1000 % 100 % 10;

    UART0_Send(WAN + 48);
    UART0_Send(QIAN + 48);
    UART0_Send(BAI + 48);
    UART0_Send(SHI + 48);
    UART0_Send(GE + 48);

    UART0_Send(13);
    UART0_Send(10);
}

void Remote_Click(unsigned char *KeyVal)
{
    unsigned char temp;
    temp = KeyNum_Match(KeyVal, &IR_KeyTable, sizeof(IR_KeyTable));
    // HEX_Convert(temp);
    switch (temp)
    {
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        break;
    case 11:
        break;
    case 12:
        break;
    case 13:
        break;
    case 14:
        break;
    case 15:
        break;
    case 16:
        break;
    case 17:
        break;
    case 18:
        break;
    case 19:
        break;
    case 20:
        break;
    case 21:
        break;
    case 22:
        break;
    case 23:
        break;
    case 24:
        break;
    case 25:
        break;
    case 26:
        break;
    case 27:
        break;
    case 28:
        break;
    case 29:
        break;
    case 30:
        break;
    case 31:
        break;
    case 32:
        break;
    case 33:
        break;
    case 34:
        break;
    case 35:
        break;
    case 36:
        break;
    case 37:
        break;
    case 38:
        break;
    case 39:
        break;
    case 40:
        break;
    case 41:
        break;
    case 42:
        break;
    case 43:
        break;
    default:
        break;
    }
}


// // // void NewParing_Mod(uint8_t *keyval, uint8_t reset)
// // // {
// // //     static uint8_t TimeCnt;
// // //     uint8_t timeFlag;
// // //     uint8_t i, j, k;
// // //     static uint8_t BreathVal, dirflag;
// // //     static uint8_t Cursor=0; // 光标
// // //     static uint8_t Num=1;    // 序号
// // //     // static uint8_t Setnum; // 已设编号的数量
// // //     if (reset) // 初始化数据
// // //     {
// // //         TimeCnt = 0;
// // //         timeFlag = 0;
// // //         BreathVal = dirflag = 0;
// // //         Cursor = 0;
// // //         Num = 1;
// // //         for (i = 0; i < TangramDevice.Device_sum; i++)
// // //         {
// // //             TangramDevice.SlaveData[i].Container.data1 = 0xFF; // 临时灯光序号
// // //         }
// // //     }
// // //     switch (*keyval)
// // //     {
// // //     case 5: // 确认键
// // //         TangramDevice.SlaveData[Cursor].Container.data1 = Num;
// // //         j = 1;
// // //         for (i = 0; i < TangramDevice.Device_sum; i++)
// // //         {
// // //             if (TangramDevice.SlaveData[i].Container.data1 == 0xFF)
// // //             {
// // //                 j = 0;
// // //             }
// // //         }
// // //         if (j)
// // //         {
// // //             Work_MOD = 0; // 退出配对模式
// // //             /* 复位参数 */
// // //             TimeCnt = 0;
// // //             timeFlag = 0;
// // //             BreathVal = dirflag = 0;
// // //             Cursor = 0;
// // //             Num = 1;
// // //             for (i = 0; i < TangramDevice.Device_sum; i++)
// // //             {
// // //                 TangramDevice.SlaveData[i].Lightnum=TangramDevice.SlaveData[i].Container.data1;
// // //                 TangramDevice.SlaveData[i].Container.data1=0XFF;
// // //             }
// // //             Set_Slave_Coord();
// // //             Slave_DataInit();
// // //             Slave_SelfTest();
// // //         }
// // //         break;
// // //     case 8: // 光标切换键
// // //         // // // j=0;
// // //         // // // for (i = 0; i < TangramDevice.Device_sum; i++)
// // //         // // // {
// // //         // // //     if (TangramDevice.SlaveData[i].Container.data1 == 0xFF)
// // //         // // //     {
// // //         // // //         j++;
// // //         // // //     }
// // //         // // // }
// // //         Cursor++;
// // //         if (Cursor >= TangramDevice.Device_sum)
// // //         {
// // //             Cursor = 0;
// // //         }
// // //         break;
// // //     case 9:
// // //         if (Num < 32)
// // //         {
// // //             Num++;
// // //         }
// // //         break;
// // //     }

// // //     if (dirflag)
// // //     {
// // //         if (BreathVal < 245)
// // //         {
// // //             BreathVal += 10;
// // //         }
// // //         else
// // //         {
// // //             dirflag = 0;
// // //         }
// // //     }
// // //     else
// // //     {
// // //         if (BreathVal > 10)
// // //         {
// // //             BreathVal -= 10;
// // //         }
// // //         else
// // //         {
// // //             dirflag = 1;
// // //         }
// // //     }
// // //     for (i = 0; i < TangramDevice.Device_sum; i++)
// // //     {
// // //         // // if (TangramDevice.SlaveData[i].Container.data1 == Num)
// // //         // // {
// // //         // //     TangramDevice.SlaveData[i].Color.R = 0;
// // //         // //     TangramDevice.SlaveData[i].Color.G = 0;
// // //         // //     TangramDevice.SlaveData[i].Color.B = 255;
// // //         // //     TangramDevice.SlaveData[i].Color.W = 0;
// // //         // // }
// // //         // // else if (i == Cursor)
// // //         // // {
// // //         // //     TangramDevice.SlaveData[i].Color.R = 0;
// // //         // //     TangramDevice.SlaveData[i].Color.G = 0;
// // //         // //     TangramDevice.SlaveData[i].Color.B = BreathVal;
// // //         // //     TangramDevice.SlaveData[i].Color.W = 0;
// // //         // // }
// // //         // // else if (TangramDevice.SlaveData[i].Container.data1 != 0xFF)
// // //         // // {
// // //         // //     TangramDevice.SlaveData[i].Color.R = 0;
// // //         // //     TangramDevice.SlaveData[i].Color.G = 255;
// // //         // //     TangramDevice.SlaveData[i].Color.B = 0;
// // //         // //     TangramDevice.SlaveData[i].Color.W = 0;
// // //         // // }
// // //         // // else
// // //         // // {
// // //         // //     TangramDevice.SlaveData[i].Color.R = 0;
// // //         // //     TangramDevice.SlaveData[i].Color.G = 0;
// // //         // //     TangramDevice.SlaveData[i].Color.B = 0;
// // //         // //     TangramDevice.SlaveData[i].Color.W = 0;
// // //         // // }

// // //         if (TangramDevice.SlaveData[i].Container.data1 == 0xFF)
// // //         {
// // //             if (i == Cursor)
// // //             {
// // //                 TangramDevice.SlaveData[i].Color.R = 0;
// // //                 TangramDevice.SlaveData[i].Color.G = 0;
// // //                 TangramDevice.SlaveData[i].Color.B = 0;
// // //                 TangramDevice.SlaveData[i].Color.W = BreathVal;
// // //             }
// // //             else
// // //             {
// // //                 TangramDevice.SlaveData[i].Color.R = 0;
// // //                 TangramDevice.SlaveData[i].Color.G = 0;
// // //                 TangramDevice.SlaveData[i].Color.B = 0;
// // //                 TangramDevice.SlaveData[i].Color.W = 0;
// // //             }
// // //         }
// // //         else
// // //         {
// // //             if (TangramDevice.SlaveData[i].Container.data1 == Num)
// // //             {
// // //                 if (i == Cursor)
// // //                 {
// // //                     TangramDevice.SlaveData[i].Color.R = 0;
// // //                     TangramDevice.SlaveData[i].Color.G = 0;
// // //                     TangramDevice.SlaveData[i].Color.B = BreathVal;
// // //                     TangramDevice.SlaveData[i].Color.W = 0;
// // //                 }
// // //                 else
// // //                 {
// // //                     TangramDevice.SlaveData[i].Color.R = 0;
// // //                     TangramDevice.SlaveData[i].Color.G = 0;
// // //                     TangramDevice.SlaveData[i].Color.B = 255;
// // //                     TangramDevice.SlaveData[i].Color.W = 0;
// // //                 }
// // //             }
// // //             else
// // //             {
// // //                 if (i == Cursor)
// // //                 {
// // //                     TangramDevice.SlaveData[i].Color.R = 0;
// // //                     TangramDevice.SlaveData[i].Color.G = BreathVal;
// // //                     TangramDevice.SlaveData[i].Color.B = 0;
// // //                     TangramDevice.SlaveData[i].Color.W = 0;
// // //                 }
// // //                 else
// // //                 {
// // //                     TangramDevice.SlaveData[i].Color.R = 0;
// // //                     TangramDevice.SlaveData[i].Color.G = 255;
// // //                     TangramDevice.SlaveData[i].Color.B = 0;
// // //                     TangramDevice.SlaveData[i].Color.W = 0;
// // //                 }
// // //             }
// // //         }

// // //         // if (TangramDevice.SlaveData[i].Container.data1 == 0xFF)
// // //         // {
// // //         //     TangramDevice.SlaveData[i].Color.R = 0;
// // //         //     TangramDevice.SlaveData[i].Color.G = 0;
// // //         //     TangramDevice.SlaveData[i].Color.B = 0;
// // //         //     TangramDevice.SlaveData[i].Color.W = 0;
// // //         // }
// // //         // else
// // //         // {
// // //         //     if (i == Cursor)
// // //         //     {
// // //         //         TangramDevice.SlaveData[i].Color.R = 0;
// // //         //         TangramDevice.SlaveData[i].Color.G = 0;
// // //         //         TangramDevice.SlaveData[i].Color.B = BreathVal;
// // //         //         TangramDevice.SlaveData[i].Color.W = 0;
// // //         //     }
// // //         //     // // if (TangramDevice.SlaveData[i].Container.data1 == Num)
// // //         //     // // {
// // //         //     // //     TangramDevice.SlaveData[i].Color.R = 0;
// // //         //     // //     TangramDevice.SlaveData[i].Color.G = 0;
// // //         //     // //     TangramDevice.SlaveData[i].Color.B = 255;
// // //         //     // //     TangramDevice.SlaveData[i].Color.W = 0;
// // //         //     // // }
// // //         //     // // else if (TangramDevice.SlaveData[i].Container.data1 == Cursor)
// // //         //     // // {
// // //         //     // //     TangramDevice.SlaveData[i].Color.R = 0;
// // //         //     // //     TangramDevice.SlaveData[i].Color.G = 0;
// // //         //     // //     TangramDevice.SlaveData[i].Color.B = BreathVal;
// // //         //     // //     TangramDevice.SlaveData[i].Color.W = 0;
// // //         //     // // }
// // //         //     // // else
// // //         //     // // {
// // //         //     // //     TangramDevice.SlaveData[i].Color.R = 0;
// // //         //     // //     TangramDevice.SlaveData[i].Color.G = 255;
// // //         //     // //     TangramDevice.SlaveData[i].Color.B = 0;
// // //         //     // //     TangramDevice.SlaveData[i].Color.W = 0;
// // //         //     // // }
// // //         // }
// // //     }
// // //     // printf("%d %d %d\r\n",BreathVal,Cursor,Num);
// // //     Slave_ColorData_DMA();
// // // }

// // // void Paring_Mod(uint8_t *keyval,uint8_t reset)
// // // {
// // //     static uint8_t TimeCnt;
// // //     uint8_t timeFlag;
// // //     static uint8_t temp;
// // //     uint8_t i, j, k;
// // //     static uint8_t BreathVal,dirflag;
// // //     static uint8_t Module_Select;       // 选中的固定ID
// // //     static uint8_t Module_LastSelect;   // 上次选中的固定ID
// // //     static uint8_t Module_Select_num;   // 选中的固定ID的编号（可能有多个相同固定ID设备在线）
// // //     static uint8_t Module_ComID;
// // //     if (reset) // 初始化数据
// // //     {
// // //         TimeCnt = 0;
// // //         timeFlag = 0;
// // //         BreathVal = dirflag = 0;
// // //         Module_LastSelect = Module_Select = 0;
// // //         Module_Select_num = 0;
// // //         Module_ComID = 0;
// // //         for (i = 0; i < SlaveDevive_Num; i++)
// // //         {
// // //             Slave_Array[i][8] = 0;  // 清临时变量
// // //         }
// // //     }

// // //     switch (*keyval)
// // //     {
// // //     case Key_Tri_A1:
// // //         Module_LastSelect = Module_Select;
// // //         Module_Select = Triangle_A1;
// // //         if (Module_LastSelect != Module_Select)
// // //         {
// // //             Module_Select_num = 0;
// // //         }
// // //         else
// // //         {
// // //             if (++Module_Select_num >= FixedID_DeviceData[0][1])
// // //             {
// // //                 Module_Select_num = 0;
// // //             }
// // //         }
// // //         break;
// // //     case Key_Tri_A2:
// // //         Module_LastSelect = Module_Select;
// // //         Module_Select = Triangle_A2;
// // //         if (Module_LastSelect != Module_Select)
// // //         {
// // //             Module_Select_num = 0;
// // //         }
// // //         else
// // //         {
// // //             if (++Module_Select_num >= FixedID_DeviceData[1][1])
// // //             {
// // //                 Module_Select_num = 0;
// // //             }
// // //         }
// // //         break;
// // //     case Key_Tri_B1:
// // //         Module_LastSelect = Module_Select;
// // //         Module_Select = Triangle_B1;
// // //         if (Module_LastSelect != Module_Select)
// // //         {
// // //             Module_Select_num = 0;
// // //         }
// // //         else
// // //         {
// // //             if (++Module_Select_num >= FixedID_DeviceData[2][1])
// // //             {
// // //                 Module_Select_num = 0;
// // //             }
// // //         }
// // //         break;
// // //     case Key_Tri_C1:
// // //         Module_LastSelect = Module_Select;
// // //         Module_Select = Triangle_C1;
// // //         if (Module_LastSelect != Module_Select)
// // //         {
// // //             Module_Select_num = 0;
// // //         }
// // //         else
// // //         {
// // //             if (++Module_Select_num >= FixedID_DeviceData[3][1])
// // //             {
// // //                 Module_Select_num = 0;
// // //             }
// // //         }
// // //         break;
// // //     case Key_Tri_C2:
// // //         Module_LastSelect = Module_Select;
// // //         Module_Select = Triangle_C2;
// // //         if (Module_LastSelect != Module_Select)
// // //         {
// // //             Module_Select_num = 0;
// // //         }
// // //         else
// // //         {
// // //             if (++Module_Select_num >= FixedID_DeviceData[4][1])
// // //             {
// // //                 Module_Select_num = 0;
// // //             }
// // //         }
// // //         break;
// // //     case Key_Tri_C3:
// // //         Module_LastSelect = Module_Select;
// // //         Module_Select = Triangle_C3;
// // //         if (Module_LastSelect != Module_Select)
// // //         {
// // //             Module_Select_num = 0;
// // //         }
// // //         else
// // //         {
// // //             if (++Module_Select_num >= FixedID_DeviceData[5][1])
// // //             {
// // //                 Module_Select_num = 0;
// // //             }
// // //         }
// // //         break;
// // //     case Key_Tri_C4:
// // //         Module_LastSelect = Module_Select;
// // //         Module_Select = Triangle_C4;
// // //         if (Module_LastSelect != Module_Select)
// // //         {
// // //             Module_Select_num = 0;
// // //         }
// // //         else
// // //         {
// // //             if (++Module_Select_num >= FixedID_DeviceData[6][1])
// // //             {
// // //                 Module_Select_num = 0;
// // //             }
// // //         }
// // //         break;
// // //     case Key_Square:
// // //         Module_LastSelect = Module_Select;
// // //         Module_Select = Square;
// // //         if (Module_LastSelect != Module_Select)
// // //         {
// // //             Module_Select_num = 0;
// // //         }
// // //         else
// // //         {
// // //             if (++Module_Select_num >= FixedID_DeviceData[7][1])
// // //             {
// // //                 Module_Select_num = 0;
// // //             }
// // //         }
// // //         break;
// // //     case Key_Fu_SET:
// // //         delay_20ms();
// // //         delay_20ms();
// // //         delay_20ms();
// // //         delay_20ms(); // 等待从机完成缓存处理
// // //         Post_Device_Series_ID();
// // //         delay_20ms();
// // //         delay_20ms();
// // //         delay_20ms();
// // //         delay_20ms();
// // //         // // Poll_Device_ID();
// // //         Slave_Allocate_ID();
// // //         TimeCnt = 0;
// // //         timeFlag = 0;
// // //         BreathVal = dirflag = 0;
// // //         Module_LastSelect = Module_Select = 0;
// // //         Module_Select_num = 0;
// // //         Module_ComID = 0;
// // //         for (i = 0; i < SlaveDevive_Num; i++)
// // //         {
// // //             Slave_Array[i][8] = 0; // 清临时变量
// // //         }
// // //         Work_MOD=0; // 退出配对模式
// // //         //////////////////////////////////////////////////////////////////

// // //         // Data_DMA_load(&Bufferarray, SlaveDevive_Num);
// // //         // // delay_20ms();delay_20ms();delay_20ms();delay_20ms();delay_20ms();delay_20ms();
// // //         // // for (i = 0; i < ModuleLight_Num; i++)
// // //         // // {
// // //         // //     for (j = 0; j < ModuleLight_Num; j++)
// // //         // //     {
// // //         // //         Bufferarray[i][0] = i;
// // //         // //         Bufferarray[i][1] = 255;
// // //         // //         if (i == j)
// // //         // //         {
// // //         // //             Bufferarray[i][2] = 255;
// // //         // //             Bufferarray[i][3] = 0;
// // //         // //             Bufferarray[i][4] = 0;
// // //         // //             Bufferarray[i][5] = 0;
// // //         // //         }
// // //         // //         else
// // //         // //         {
// // //         // //             Bufferarray[i][2] = 0;
// // //         // //             Bufferarray[i][3] = 0;
// // //         // //             Bufferarray[i][4] = 0;
// // //         // //             Bufferarray[i][5] = 0;
// // //         // //         }
// // //         // //     }
// // //         // //     delay_20ms();delay_20ms();delay_20ms();delay_20ms();delay_20ms();delay_20ms();
// // //         // //     delay_20ms();delay_20ms();delay_20ms();delay_20ms();delay_20ms();delay_20ms();
// // //         // //     Data_DMA_load(&Bufferarray, ModuleLight_Num);
// // //         // // }


// // //         Slave_SelfTest();
// // //         Module_SelfTest();
// // //         /*










// // //         */
// // //         break;
// // //         default:

// // //             break;
// // //         }

// // //     for (i = 0; i < 8; i++)     // 8种固定ID
// // //     {
// // //         if (Module_Select == FixedID_DeviceData[i][0])
// // //         {
// // //             Module_ComID = FixedID_DeviceData[i][2 + Module_Select_num];
// // //         }
// // //     }

// // //     Keyboard_Out(keyval, &Keyboard_NumVal);

// // //     if (dirflag)
// // //     {
// // //         if (BreathVal < 250)
// // //         {
// // //             BreathVal += 2;
// // //         }
// // //         else
// // //         {
// // //             dirflag = 0;
// // //         }
// // //     }
// // //     else
// // //     {
// // //         if (BreathVal > 5)
// // //         {
// // //             BreathVal -= 2;
// // //         }
// // //         else
// // //         {
// // //             dirflag = 1;
// // //         }
// // //     }

// // //     if (++TimeCnt > 30)
// // //     {
// // //         TimeCnt = 0;
// // //         timeFlag = 1;
// // //     }
// // //     if (timeFlag)
// // //     {
// // //         if (++temp >= SlaveDevive_Num)
// // //         {
// // //             temp = 0;
// // //         }
// // //     }
// // //     if (*keyval != 0xFF)
// // //     {
// // //         // printf("key=%d\n", *keyval);
// // //         // printf("ID=%d\n", Module_ComID);
// // //     }

// // //     // if (Keyboard_NumVal != 0xFF)
// // //     // {
// // //     //     printf("OUT=%d\n\n", Keyboard_NumVal);
// // //     // }
// // //     // printf("ID=%d\n", Module_ComID);
// // //     // printf("key=%d\n",*OutVal);
// // //     if (Keyboard_NumVal != 0XFF)
// // //     {
// // //         printf("ID=%d\n", Module_ComID);
// // //         // printf("key=%d\n\n", Keyboard_NumVal);
// // //         if ((Keyboard_NumVal <= 16) && (Keyboard_NumVal > 0))
// // //         {

// // //             // printf("Num=%d\n\n", Keyboard_NumVal);
// // //             // printf("selectID=%d\n", Module_ComID);
// // //             for (i = 0; i < SlaveDevive_Num; i++)
// // //             {
// // //                 // printf("Slave:%d Module:%d\n", Slave_Array[i][5],Module_ComID);
// // //                 if (Slave_Array[i][5] == Module_ComID)
// // //                 {
// // //                     Slave_Array[i][8] = Keyboard_NumVal;
// // //                     // printf("set %d %d\n\n", Slave_Array[i][5],Keyboard_NumVal);
// // //                 }
// // //             }
// // //         }
// // //     }

// // //     for (i = 0; i < SlaveDevive_Num; i++)
// // //     {

// // //         if (Slave_Array[i][5] == Module_ComID)
// // //         {
// // //             if (Slave_Array[i][8]) // 已设置编号
// // //             {
// // //                 Bufferarray[i][0] = Slave_Array[i][5];
// // //                 Bufferarray[i][1] = 255;
// // //                 Bufferarray[i][2] = 0;
// // //                 Bufferarray[i][3] = 255;
// // //                 Bufferarray[i][4] = 0;
// // //                 Bufferarray[i][5] = 0;
// // //             }
// // //             else
// // //             {
// // //                 Bufferarray[i][0] = Slave_Array[i][5];
// // //                 Bufferarray[i][1] = 255;
// // //                 Bufferarray[i][2] = 0;
// // //                 Bufferarray[i][3] = 0;
// // //                 Bufferarray[i][4] = 0;
// // //                 Bufferarray[i][5] = BreathVal;
// // //             }

// // //         }
// // //         else
// // //         {

// // //             if (Slave_Array[i][8]) // 已设置编号
// // //             {
// // //                 Bufferarray[i][0] = Slave_Array[i][5];
// // //                 Bufferarray[i][1] = 20;
// // //                 Bufferarray[i][2] = 0;
// // //                 Bufferarray[i][3] = 255;
// // //                 Bufferarray[i][4] = 0;
// // //                 Bufferarray[i][5] = 0;
// // //             }
// // //             else
// // //             {
// // //                 Bufferarray[i][0] = Slave_Array[i][5];
// // //                 Bufferarray[i][1] = 20;
// // //                 Bufferarray[i][2] = 0;
// // //                 Bufferarray[i][3] = 0;
// // //                 Bufferarray[i][4] = 0;
// // //                 Bufferarray[i][5] = BreathVal;
// // //             }
// // //         }
// // //     }
// // //     Data_DMA_load(&Bufferarray, SlaveDevive_Num);
// // // }

// // // // // void Scene_MOD(void)
// // // // // {
// // // // //     static uint8_t ProcessNum;
// // // // //     static uint8_t TimeCnt;
// // // // //     static uint8_t Cursor;
// // // // //     static uint8_t Flash_flag;
// // // // //     // static uint8_t Work_MOD;
// // // // //     // static uint8_t Last_Work_MOD;
// // // // //     uint8_t timeFlag;
// // // // //     static uint8_t temp;
// // // // //     uint8_t i, j, k;

// // // // //     if (++TimeCnt > 5)
// // // // //     {
// // // // //         TimeCnt=0;
// // // // //         Flash_flag = ~Flash_flag;
// // // // //         timeFlag=1;
// // // // //     }


// // // // //     switch (Work_MOD)
// // // // //     {
// // // // //     case 0:
// // // // //         if (IR_KeyVal==4)
// // // // //         {
// // // // //             Work_MOD=1;
// // // // //         }
// // // // //         // Frame_Working();

// // // // //         break;
// // // // //     case 1:
// // // // //         if (IR_KeyVal==4)
// // // // //         {
// // // // //             Work_MOD=0;
// // // // //         }

// // // // //         if (Last_Work_MOD != Work_MOD)
// // // // //         {
// // // // //             NewParing_Mod(&IR_KeyVal, 1);
// // // // //         }
// // // // //         else
// // // // //         {
// // // // //             NewParing_Mod(&IR_KeyVal, 0);
// // // // //         }
// // // // //         break;

// // // // //     default:
// // // // //         break;
// // // // //     }
// // // // //     Last_Work_MOD = Work_MOD;
// // // // //     if (IR_KeyVal==43)
// // // // //     {

// // // // //         Slave_SelfTest();

// // // // //     }

// // // // // }

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // void Frame_Working(void)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     static uint16_t Time_Cnt;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     static uint8_t Last_Light_Owner;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     uint8_t i;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     if (Light_Owner == Light_Owner_APP) // APP控灯
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         if (Last_Light_Owner != Light_Owner_APP)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             for (i = 0; i < TangramDevice.Device_sum; i++)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 TangramDevice.SlaveData[i].Color.R = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 TangramDevice.SlaveData[i].Color.G = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 TangramDevice.SlaveData[i].Color.B = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 TangramDevice.SlaveData[i].Color.W = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     else // MCU控灯
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         if (++Time_Cnt >= Image_Dynamic[EffextImage_num].IntervalTime)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             Time_Cnt = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             switch (Mode_num)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             case 0:
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 if (Image_Dynamic[EffextImage_num].PixelSum == 1)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     Frame_Skewing(FrameSum, &Tangram[0].Frame_Now, &Tangram[0].Frame_Now, 1);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     ImagePixel_Cal(&Image_Dynamic[EffextImage_num], &Tangram[0], 0);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     for (i = 1; i < 15; i++)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                         Frame_Skewing(FrameSum, &Tangram[i].Frame_Now, &Tangram[i - 1].Frame_Now, Image_Dynamic[EffextImage_num].Para_1);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                         ImagePixel_Cal(&Image_Dynamic[EffextImage_num], &Tangram[i], 0);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 else
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     for (i = 0; i < 15; i++)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                         Frame_Skewing(FrameSum, &Tangram[i].Frame_Now, &Tangram[i].Frame_Now, Image_Dynamic[EffextImage_num].Para_1);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                         ImagePixel_Cal(&Image_Dynamic[EffextImage_num], &Tangram[i], i);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 break;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             case 1:
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 for (i = 0; i < 15; i++)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     StaticPixel_Cal(&Image_Static[EffextImage_num], &Tangram[i], i);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 break;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             case 2:
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 MIC_Process();
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 Module_All_GradualChange(TangramDevice.Light_sum);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 break;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             default:
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 break;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         Slave_ColorData_Allot();
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     Last_Light_Owner = Light_Owner;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     Slave_ColorData_DMA();
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // }

// // // // // void Module_SelfTest(void)
// // // // // {
// // // // //     uint8_t i, j;
// // // // //     for (i = 0; i <= ModuleLight_Num; i++)
// // // // //     {
// // // // //         for (j = 0; j < ModuleLight_Num; j++)
// // // // //         {
// // // // //             if (j == i)
// // // // //             {
// // // // //                 Tangram[j].R.Now = 0;
// // // // //                 Tangram[j].G.Now = 255;
// // // // //                 Tangram[j].B.Now = 0;
// // // // //                 Tangram[j].W.Now = 0;
// // // // //             }
// // // // //             else
// // // // //             {
// // // // //                 Tangram[j].R.Now = 0;
// // // // //                 Tangram[j].G.Now = 0;
// // // // //                 Tangram[j].B.Now = 0;
// // // // //                 Tangram[j].W.Now = 0;
// // // // //             }
// // // // //         }
// // // // //         delay_500ms();
// // // // //         TangramBuffer_DMA_load(ModuleLight_Num);
// // // // //     }
// // // // // }

// // void Slave_SelfTest(void)
// // {
// //     uint8_t i, j;
// //     if (TangramDevice.Device_sum)
// //     {
// //         for (i = 0; i < TangramDevice.Device_sum; i++)
// //         {
// //             for (j = 0; j < TangramDevice.Device_sum; j++)
// //             {
// //                 // if (TangramDevice.SlaveData[j].Runingnum == i)
// //                 if (j == i)
// //                 {
// //                     TangramDevice.SlaveData[j].Color.R = 0;
// //                     TangramDevice.SlaveData[j].Color.G = 0;
// //                     TangramDevice.SlaveData[j].Color.B = 0;
// //                     TangramDevice.SlaveData[j].Color.W = 255;
// //                 }
// //                 else
// //                 {
// //                     TangramDevice.SlaveData[j].Color.R = 0;
// //                     TangramDevice.SlaveData[j].Color.G = 0;
// //                     TangramDevice.SlaveData[j].Color.B = 0;
// //                     TangramDevice.SlaveData[j].Color.W = 0;
// //                 }
// //             }
// //             delay_500ms();
// //             Slave_ColorData_DMA();
// //         }
// //         delay_500ms();
// //         for (j = 0; j < TangramDevice.Device_sum; j++)
// //         {
// //             TangramDevice.SlaveData[j].Color.R = 0;
// //             TangramDevice.SlaveData[j].Color.G = 0;
// //             TangramDevice.SlaveData[j].Color.B = 0;
// //             TangramDevice.SlaveData[j].Color.W = 0;
// //         }
// //         Slave_ColorData_DMA();
// //     }
// //     else
// //     {
// //         printf("\r\n\r\n\r\n\r\n\r\n\r\nFound zero device!\r\n\r\n\r\n\r\n");
// //     }
// // }

// // // // // // // // // // // // // // // // void Module_All_GradualChange(uint8_t modele_num)
// // // // // // // // // // // // // // // // {
// // // // // // // // // // // // // // // //     uint8_t i;
// // // // // // // // // // // // // // // //     for (i = 0; i < modele_num; i++)
// // // // // // // // // // // // // // // //     {
// // // // // // // // // // // // // // // //         // // // Module_Gradual_Change(&Tangram[i]);
// // // // // // // // // // // // // // // //         Model_Gradual_Change(&Tangram[i]);
// // // // // // // // // // // // // // // //     }

// // // // // // // // // // // // // // // // //    TangramBuffer_DMA_load(modele_num);
// // // // // // // // // // // // // // // // }


uint8_t MIC_Process(void)
{
    // uint16_t Max,Min,Average,BaseVal;
    // uint16_t SoundRange;
    // uint8_t i, j;
    // uint16_t temp;
    // static uint16_t Last_Max = 0;

    // if (DMAVEC->CTRL[CTRL_DATA_ADC].DMACT == 0)
    // {
    //     // LED2_REV();
    //     // ADC_Stop();
    //     Max = 0;
    //     Min = 0xFFFF;
    //     for (i = 0; i < ADC_CNT; i++)
    //     {
    //         if (Max < ADC_Buffer[i])
    //         {
    //             Max = ADC_Buffer[i];
    //         }
    //         if (Min > ADC_Buffer[i])
    //         {
    //             Min = ADC_Buffer[i];
    //         }
    //     }
    //     Average = ADC_Buffer[0];
    //     SoundRange = Max - Min;
    //     BaseVal = Max + Min;
    //     BaseVal = BaseVal / 2;
    //     // printf("%d\r\n",SoundRange);
    //     Last_Max = Max;
    //     // if (Edge_detect(SoundRange))
    //     // {
    //     //     // Random_ColorTrigger(ModuleLight_Num);
    //     //     // ColorTrigger(TangramDevice.Light_sum);
    //     //     // printf("Trigger\n");
    //     // }

    //     // DMA_Start(DMA_VECTOR_ADC, CTRL_DATA_ADC, DMA_MODE_NORMAL,
    //     //           DMA_SIZE_HALF, ADC_CNT, (uint16_t *)&ADC->ADCR, ADC_Buffer);

    //     // ADC_Set_HardTrigger(1, AD_TRG_IT);
    //     // ADC_Set_Clock(CLOCK_DIV8, 0x0DU);
    //     // ADC_Start(ADC_CHANNEL_0);
    //     // DMA_Start(DMA_VECTOR_ADC, CTRL_DATA_ADC, DMA_MODE_NORMAL,
    //     //           DMA_SIZE_HALF, ADC_CNT, (uint16_t *)&ADC->ADCR, ADC_Buffer);

    //     return Edge_detect(SoundRange);
    // }
}


// // // /**
// // //  * @description: 灯光运行编号排序
// // //  * @param
// // //  * @return {*}
// // //  */
// // // // void Runingnum_Bubble_Sort(uint8_t *array, uint8_t row, uint8_t column, uint8_t num)
// // // void Runingnum_Bubble_Sort(void)
// // // {
// // //     uint8_t TempArray[16][2];
// // //     uint8_t temp;
// // //     uint8_t i, j, k;

// // //     // printf("\r\n\r\n\r\n");
// // //     for (i = 0; i < TangramDevice.Device_sum; i++)  // 提取灯光序号
// // //     {
// // //         TempArray[i][0] = TangramDevice.SlaveData[i].ID;
// // //         TempArray[i][1] = TangramDevice.SlaveData[i].Lightnum;
// // //         printf("[%d][%d] \n", TempArray[i][0], TempArray[i][1]);
// // //     }

// // //     Bubble_Sort_2D(&TempArray, TangramDevice.Device_sum, 2, 1); // 对灯光序号进行排序

// // //     // printf("\r\n\r\nBubble...\r\n\r\n\r\n");

// // //     temp = TempArray[0][1];
// // //     j = 0;
// // //     for (i = 0; i < TangramDevice.Device_sum; i++)
// // //     {
// // //         if (TempArray[i][1] != temp)
// // //         {
// // //             j++;
// // //         }
// // //         for (k = 0; k < TangramDevice.Device_sum; k++) // 写入重新编排后的灯光运行序号
// // //         {
// // //             if (TangramDevice.SlaveData[k].ID == TempArray[i][0])
// // //             {
// // //                 TangramDevice.SlaveData[k].Runingnum = j;
// // //             }
// // //         }
// // //         temp = TempArray[i][1];
// // //     }
// // //     TangramDevice.Light_sum = j + 1;

// // //     // // // printf("\r\nLight_sum=%d\r\n", TangramDevice.Light_sum);

// // //     // // // for (i = 0; i < TangramDevice.Device_sum; i++)
// // //     // // // {
// // //     // // //     printf("[%d][%d]\n", TempArray[i][0], TempArray[i][1]);
// // //     // // // }
// // //     printf("\r\n\r\n");
// // //     for (i = 0; i < TangramDevice.Device_sum; i++)
// // //     {
// // //         printf("ID[%d][%d][%d] \n", TangramDevice.SlaveData[i].ID, TangramDevice.SlaveData[i].Lightnum, TangramDevice.SlaveData[i].Runingnum);
// // //     }
// // //     printf("\nDevice_sum %d\nLight_sum %d\n\n",TangramDevice.Device_sum,TangramDevice.Light_sum);
// // // }

// // // // void DataUpdata_TO_APP(uint8_t *data_addr)
// // // // {
// // // //     if (data_addr == &SYS.POWER_SW)
// // // //     {
// // // //         mcu_dp_bool_update(DPID_SWITCH_LED,SYS.POWER_SW); //BOOL型数据上报;
// // // //     }
// // // //     else if (data_addr == &SYS.Brightness.Set)
// // // //     {
// // // //         mcu_dp_value_update(DPID_BRIGHT_VAL,SYS.Brightness.Set); //VALUE型数据上报;
// // // //     }
// // // //     // 代码待修改
// // // // }

uint8_t KEY_AD_Test(void)
{
    uint16_t KEY_Val;
    
    // // DMA_Stop(DMA_VECTOR_ADC);

    // // ADC_Start(ADC_CHANNEL_2);
    // // DMA_Start(DMA_VECTOR_ADC, CTRL_DATA_ADC, DMA_MODE_NORMAL,
    // //           DMA_SIZE_HALF, 1, (uint16_t *)&ADC->ADCR, &KEY_Val);
    // // LED_Blue_off();
    // //         //    ADC->ADM0 |= ADCS;
    // // while (DMAVEC->CTRL[CTRL_DATA_ADC].DMACT != 0)
    // // {
    // //     ;
    // // }
    // // LED_Blue_on();
    // // // // KEY_Val = ADC_Converse(ADC_CHANNEL_2, 1, &KEY_Val);
    KEY_Val=xadc.keybuf;
    // // printf("k:%d\r", KEY_Val);
    if (KEY_Val > Ref_ON) // 3756
    {
        return 0;
    }
    if (KEY_Val > Ref_K5) // 3685
    {
        return 5;	
    }
    if (KEY_Val > Ref_K4) // 3173
    {
        return 4;
    }
    if (KEY_Val > Ref_K3) // 2900
    {
        return 3;
    }
    if (KEY_Val > Ref_K2) // 2388
    {
        return 2;
    }
    if (KEY_Val > Ref_K1) // 1023
    {
        return 1;
    }
    return 0;

}
uint8_t Light_AD_Test(void)
{
    // // uint16_t light_Val[200];
    // // // LED_Blue_off();
    // // // light_Val[0] = ADC_Converse(ADC_CHANNEL_36, 1, &light_Val);
    // // // printf("%d\r\n",light_Val);
    // // // LED_Blue_on();

    
    // // // DMA_Stop(DMA_VECTOR_ADC);

    // // ADC_Start(ADC_CHANNEL_36);
    // // DMA_Start(DMA_VECTOR_ADC, CTRL_DATA_ADC, DMA_MODE_NORMAL,
    // //           DMA_SIZE_HALF, 1, (uint16_t *)&ADC->ADCR, &light_Val);
    // // while (DMAVEC->CTRL[CTRL_DATA_ADC].DMACT != 0)
    // // {
    // //     // ;
    // //     printlog("dma:%x\r", DMAVEC->CTRL[CTRL_DATA_ADC].DMACT);
    // //     // // DMAVEC->CTRL[CTRL_DATA_SR0].DMACT;
    // // }
    // // //  printf("%d\r\n",light_Val[0]);
    // //  LED_Blue_on();
}





// // // void RTC_Check(uint8_t time[])
// // // {
// // //     rtc_counter_value_t counter_val;
// // //     if (time[1] > 30) // 最大年份2030年，溢出代表未获取正确网络时间
// // //     {
// // //         // printf("time error\r");
// // //     }
// // //     else
// // //     {
// // //         if (RTC_CheckFinish == 0)
// // //         {
// // //             // printf("set time\r\r");
// // //             // printf("WIFI 20%d/%d/%d  %d %d:%d:%d\n", time[1], time[2], time[3], time[7], time[4], time[5], time[6]);
// // //             counter_val.year = HEX_To_BCD(time[1]);
// // //             counter_val.month = HEX_To_BCD(time[2]);
// // //             counter_val.day = HEX_To_BCD(time[3]);
// // //             counter_val.hour = HEX_To_BCD(time[4]);
// // //             counter_val.min = HEX_To_BCD(time[5]);
// // //             counter_val.sec = HEX_To_BCD(time[6]);
// // //             counter_val.week = HEX_To_BCD(time[7]);
// // //             RTC_Set_CounterValue(&counter_val);
// // //             RTC_CheckFinish = 1;
// // //         }
// // //     }

// // //     /*
// // //     Time[0] 为是否获取时间成功标志，为 0 表示失败，为 1表示成功
// // //     Time[1] 为年份，0x00 表示 2000 年
// // //     Time[2] 为月份，从 1 开始到12 结束
// // //     Time[3] 为日期，从 1 开始到31 结束
// // //     Time[4] 为时钟，从 0 开始到23 结束
// // //     Time[5] 为分钟，从 0 开始到59 结束
// // //     Time[6] 为秒钟，从 0 开始到59 结束
// // //     Time[7] 为星期，从 1 开始到 7 结束，1代表星期一
// // //    */
// // // }

// // // void RTC_Task(void)
// // // {
// // //     // rtc_counter_value_t counter_val;
// // //     // if (RTC_CheckFinish == 0)
// // //     // {
// // //         mcu_get_system_time();  // 从网络获取时间
// // //     // }
// // //     // else
// // //     // {
// // //     //     RTC_Get_CounterValue(&counter_val);
// // //     //     // printf("     20%d/%d/%d  %d %d:%d:%d\r\n",BCD_To_HEX(counter_val.year),BCD_To_HEX(counter_val.month),BCD_To_HEX(counter_val.day),BCD_To_HEX(counter_val.week),BCD_To_HEX(counter_val.hour),BCD_To_HEX(counter_val.min),BCD_To_HEX(counter_val.sec));
// // //     // }
// // // }


/*计算校验和*/
uint32_t checksum_calculate(uint8_t *sur, uint32_t len)
{
	uint32_t i;
	uint32_t sum = 0;
	for (i = 0; i < len; i++)
	{
		sum += *sur++;
	}
	return sum;
}


void watchdog_test(void)
{
// //     extern volatile uint32_t g_WdtIntTaken; 	/* WDT interrupt flag */
// //     -----------------------------------------------------------------------
// // Configure Option Byte C0H to enable WDT in system_CMS32L051.c
// // -----------------------------------------------------------------------
// //     PORT->PMC7 = 0x00;
// // 	PORT->P7  |= (3<<1);
// // 	PORT->PM7 &= ~(3<<1); // P71, P72 output mode

// // 	tmp = RST->RESF;
// // 	if(tmp & RST_RESF_WDTRF_Msk)
// // 	{
// // 		printf("WDT Reset taken! RESF = 0x%02x\n", tmp);
// // 		PORT->P7 ^= (1<<1); 	// P71 toggle
// // 		while(1)
// // 		{
// // 			WDT_Restart();
// // 		}
// // 	}
// // 	else
// // 	{
// // 		while(g_WdtIntTaken == 0){;}
// // 		printf("WDT Interrupt taken! RESF = 0x%02x\n", RST->RESF);
// // 		PORT->P7 ^= (1<<2); 	// P72 toggle
// // 		while(1);
// // 	}
}




/* 
 * @Description: 间隔定时器中断服务函数
 * @param: 
 * @return: 
*/ 
void it_callback_Handle(void)
{
    


}



