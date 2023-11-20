/*
 * @Author: DESKTOP-AKTRQKB\MY sandote@163.com
 * @Date: 2023-07-01 16:13:06
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
 * @LastEditTime: 2023-11-06 15:38:52
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\Source\Sys.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "Sys.h"

void SYS_Clock_Tick(void)
{
    // static unsigned int Tick_base_4MS = 0;   // 系统滴答时钟
    // static unsigned char Tick_base_80uS = 0; // 系统滴答时钟
    // if (++Tick_base_80uS >= 50)
    // {
    //     Tick_base_80uS = 0;
    //     Tick_base_4MS++;

    static unsigned int Tick_base_4MS = 0;
    Tick_base_4MS++;
    T_4MS_FLAG_SetBit();
    refresh_random();   // 刷新随机数
    
    if ((Tick_base_4MS % T_8MS_VALUE) == 0)
    {
        T_8MS_FLAG_SetBit();
    }
    if ((Tick_base_4MS % T_20MS_VALUE) == 0)
    {
        T_20MS_FLAG_SetBit();
    }
    if ((Tick_base_4MS % T_28MS_VALUE) == 0)
    {
        T_28MS_FLAG_SetBit();
    }
    if ((Tick_base_4MS % T_100MS_VALUE) == 0)
    {
        T_100MS_FLAG_SetBit();
    }
    if ((Tick_base_4MS % T_200MS_VALUE) == 0)
    {
        T_200MS_FLAG_SetBit();
    }
    if ((Tick_base_4MS % T_500MS_VALUE) == 0)
    {
        T_500MS_FLAG_SetBit();
    }
    if (Tick_base_4MS % T_1000MS_VALUE == 0)
    {
        T_1000MS_FLAG_SetBit();
    }
    if (Tick_base_4MS >= 3500)
    {
        Tick_base_4MS = 0;
    }
    // }
}
