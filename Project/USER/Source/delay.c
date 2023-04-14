/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-05-31 16:17:48
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-05-31 16:26:48
 * @FilePath: \A5441_Master_CMS32L051\Project\USER\Source\delay.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "Function_Init.H"
#include "delay.H"


void delay_100us(void)
{
    unsigned int delaycnt;
    delaycnt=230;
    while (delaycnt--)
    {
       __NOP();
    }
}


void delay_1ms(void)
{
    uint16_t i;
    i = 2100;
    while (i--)
    {
        __NOP();
    }
}

void delay_5ms(void)
{
    uint16_t i;
    i = 10100;
    while (i--)
    {
        __NOP();
    }
}

void delay_10ms(void)
{
    uint16_t i;
    i = 20200;
    while (i--)
    {
        __NOP();
    }
}

void delay_20ms(void)
{
    uint16_t i;
    i = 40400;
    while (i--)
    {
        __NOP();
    }
}

void delay_500ms(void)
{
    delay_20ms();delay_20ms();delay_20ms();delay_20ms();delay_20ms();
    delay_20ms();delay_20ms();delay_20ms();delay_20ms();delay_20ms();
    delay_20ms();delay_20ms();delay_20ms();delay_20ms();delay_20ms();
    delay_20ms();delay_20ms();delay_20ms();delay_20ms();delay_20ms();
}
