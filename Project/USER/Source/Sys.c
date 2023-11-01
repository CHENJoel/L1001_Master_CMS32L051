
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
