/*
 * @Author: your name
 * @Date: 2022-04-22 10:36:55
 * @LastEditTime: 2022-04-23 16:34:16
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \A5441_Master_CMS32L051\Project\USER\Source\Light.c
 */

#include "Light.H"





 unsigned char Bright_Array[5] = {10, 30, 80, 155, 255}; // 亮度表
unsigned char Bright_Level;                            // 亮度等级

/**
 * @description:  计算数据属于哪一等级（向上取整）
 * @param {unsigned char} *DataVal      当前数据
 * @param {unsigned char} *array        级别信息数组
 * @param {unsigned char} arrayLength   数据长度
 * @return {*}
 */
unsigned char Level_Calculation(unsigned char *DataVal, unsigned char *array, unsigned char arrayLength)
{
    unsigned char i;
    for (i = 0; i < (arrayLength - 1); i++)
    {
        if (*DataVal <= array[i])
        {
            break;
        }
    }
    return i;
}

/**
 * @description: 自动轮回切换数据等级
 * @param {LightTypeDef} *light         数据结构体
 * @param {unsigned char} *array        级别信息数组
 * @param {unsigned char} arrayLength   数组长度
 * @return {*}
 */
void Light_Level_Change(unsigned char *target,unsigned char *direction, unsigned char *array, unsigned char arrayLength)
{
    unsigned char Temp_Level_Num;
    Temp_Level_Num = Level_Calculation(target, array, arrayLength - 1);  // 计算当前处于哪一等级
    if (*direction > 0)
    {
        if (++Temp_Level_Num >= (arrayLength - 1))
        {
            Temp_Level_Num = arrayLength - 1;
            *direction = 0;
        }
    }
    else
    {
        if (Temp_Level_Num)
        {
            Temp_Level_Num--;
        }
        if (Temp_Level_Num == 0)
        {
            *direction = 1;
        }
    }
    *target = array[Temp_Level_Num];
}

/**
 * @description: 数据增加一个级别
 * @param {unsigned char} *target       目标数据
 * @param {unsigned char} *array        级别信息数组
 * @param {unsigned char} arrayLength   数组长度
 * @return {*}
 */
void Light_Level_Up(unsigned char *target, unsigned char *array, unsigned char arrayLength)
{
    unsigned char Temp_Level_Num;
    Temp_Level_Num = Level_Calculation(target, array, arrayLength - 1); // 计算当前处于哪一等级
    if (++Temp_Level_Num >= (arrayLength - 1))
    {
        Temp_Level_Num = arrayLength - 1;
    }
    *target = array[Temp_Level_Num];
}

/**
 * @description: 数据降低一个级别
 * @param {unsigned char} *target       目标数据
 * @param {unsigned char} *array        级别信息数组
 * @param {unsigned char} arrayLength   数组长度
 * @return {*}
 */
void Light_Level_Down(unsigned char *target, unsigned char *array, unsigned char arrayLength)
{
    unsigned char Temp_Level_Num;
    Temp_Level_Num = Level_Calculation(target, array, arrayLength - 1);  // 计算当前处于哪一等级
    if (Temp_Level_Num)
    {
        Temp_Level_Num--;
    }
    *target = array[Temp_Level_Num];
}

/**
 * @description:  渐变计算
 * @param {unsigned char} *now      当前值
 * @param {unsigned char} *target   目标值
 * @param {unsigned char} step      渐变量
 * @return {*}
 */
void Gradual_Change(unsigned char *now,unsigned char *target, unsigned char step)
{
    unsigned int Temp;
    if (*target > *now)
    {
        Temp = *now + step;
        if (Temp > *target) // 加法数据溢出
        {
            *now = *target;
        }
        else
        {
            *now = Temp;
        }
    }
    else if (*now > *target)
    {
        if (*now > step) // 避免减法时数据溢出
        {
            Temp = *now - step;
            if (Temp < *target)
            {
                *now = *target;
            }
            else
            {
                *now = Temp;
            }
        }
        else
        {
            *now = *target;
        }
    }
    else
    {
        *now = *target;
    }
}



/**************************************************
*函数名称：Value_Step_Change(uint *DataVAL, uchar *Direction,uint Max, uint Min,unsigned char StepVAL)
*函数功能：循环步进渐变
*入口参数：*DataVAL,*Direction,Max,Min,StepVAL| 入口值，方向，最大值，最小值，步进值；
*出口参数：void
**************************************************/

/**
 * @description: 步进加/减
 * @param {unsigned char} *DataVAL      目标数据
 * @param {unsigned char} *Direction    步进方向 1加/0减
 * @param {unsigned char} Max           最大限值
 * @param {unsigned char} Min           最小限值
 * @param {unsigned char} StepVAL       步进值
 * @return {*}
 */
void Value_Step_Change(unsigned char *DataVAL, unsigned char *Direction, unsigned char Max, unsigned char Min, unsigned char StepVAL)
{
    if (*Direction) // 加
    {
        if (*DataVAL < Max - StepVAL)
        {
            (*DataVAL) += StepVAL;
        }
        else
        {
            (*DataVAL) = Max;
        }
    }
    else    // 减
    {
        if (*DataVAL > Min + StepVAL)
        {
            (*DataVAL) -= StepVAL;
        }
        else
        {
            (*DataVAL) = Min;
        }
    }
}


/*
    Value_Step_Change(&CW_Color.Set, &CW_Color.Direction, Color_CW_Array[sizeof(Color_CW_Array) - 1], Color_CW_Array[0], 1);
    if (CW_Color.Set == Color_CW_Array[sizeof(Color_CW_Array) - 1])
    {
        Twinkle_SET(1, 8, 8, 100);
        if (Color_LongRelease)
        {
            TouchReset_Color(); // 长按完成后复位触摸
            CW_Color.Direction = 0;
            Twinkle_SET(0, 7, 7, 100); // 结束闪烁
        }
    }
    else if (CW_Color.Set == Color_CW_Array[0])
    {
        Twinkle_SET(1, 8, 8, 100);
        if (Color_LongRelease)
        {
            TouchReset_Color(); // 长按完成后复位触摸
            CW_Color.Direction = 1;
            Twinkle_SET(0, 7, 7, 100); // 结束闪烁
        }
    }
*/
