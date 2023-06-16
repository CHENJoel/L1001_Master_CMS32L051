/*
 * @Author: your name
 * @Date: 2022-04-22 10:36:55
 * @LastEditTime: 2022-04-23 16:34:16
 * @LastEditors: Please set LastEditors
 * @Description: ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \A5441_Master_CMS32L051\Project\USER\Source\Light.c
 */

#include "Light.H"





 unsigned char Bright_Array[5] = {10, 30, 80, 155, 255}; // ���ȱ�
unsigned char Bright_Level;                            // ���ȵȼ�

/**
 * @description:  ��������������һ�ȼ�������ȡ����
 * @param {unsigned char} *DataVal      ��ǰ����
 * @param {unsigned char} *array        ������Ϣ����
 * @param {unsigned char} arrayLength   ���ݳ���
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
 * @description: �Զ��ֻ��л����ݵȼ�
 * @param {LightTypeDef} *light         ���ݽṹ��
 * @param {unsigned char} *array        ������Ϣ����
 * @param {unsigned char} arrayLength   ���鳤��
 * @return {*}
 */
void Light_Level_Change(unsigned char *target,unsigned char *direction, unsigned char *array, unsigned char arrayLength)
{
    unsigned char Temp_Level_Num;
    Temp_Level_Num = Level_Calculation(target, array, arrayLength - 1);  // ���㵱ǰ������һ�ȼ�
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
 * @description: ��������һ������
 * @param {unsigned char} *target       Ŀ������
 * @param {unsigned char} *array        ������Ϣ����
 * @param {unsigned char} arrayLength   ���鳤��
 * @return {*}
 */
void Light_Level_Up(unsigned char *target, unsigned char *array, unsigned char arrayLength)
{
    unsigned char Temp_Level_Num;
    Temp_Level_Num = Level_Calculation(target, array, arrayLength - 1); // ���㵱ǰ������һ�ȼ�
    if (++Temp_Level_Num >= (arrayLength - 1))
    {
        Temp_Level_Num = arrayLength - 1;
    }
    *target = array[Temp_Level_Num];
}

/**
 * @description: ���ݽ���һ������
 * @param {unsigned char} *target       Ŀ������
 * @param {unsigned char} *array        ������Ϣ����
 * @param {unsigned char} arrayLength   ���鳤��
 * @return {*}
 */
void Light_Level_Down(unsigned char *target, unsigned char *array, unsigned char arrayLength)
{
    unsigned char Temp_Level_Num;
    Temp_Level_Num = Level_Calculation(target, array, arrayLength - 1);  // ���㵱ǰ������һ�ȼ�
    if (Temp_Level_Num)
    {
        Temp_Level_Num--;
    }
    *target = array[Temp_Level_Num];
}

/**
 * @description:  �������
 * @param {unsigned char} *now      ��ǰֵ
 * @param {unsigned char} *target   Ŀ��ֵ
 * @param {unsigned char} step      ������
 * @return {*}
 */
void Gradual_Change(unsigned char *now,unsigned char *target, unsigned char step)
{
    unsigned int Temp;
    if (*target > *now)
    {
        Temp = *now + step;
        if (Temp > *target) // �ӷ��������
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
        if (*now > step) // �������ʱ�������
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
*�������ƣ�Value_Step_Change(uint *DataVAL, uchar *Direction,uint Max, uint Min,unsigned char StepVAL)
*�������ܣ�ѭ����������
*��ڲ�����*DataVAL,*Direction,Max,Min,StepVAL| ���ֵ���������ֵ����Сֵ������ֵ��
*���ڲ�����void
**************************************************/

/**
 * @description: ������/��
 * @param {unsigned char} *DataVAL      Ŀ������
 * @param {unsigned char} *Direction    �������� 1��/0��
 * @param {unsigned char} Max           �����ֵ
 * @param {unsigned char} Min           ��С��ֵ
 * @param {unsigned char} StepVAL       ����ֵ
 * @return {*}
 */
void Value_Step_Change(unsigned char *DataVAL, unsigned char *Direction, unsigned char Max, unsigned char Min, unsigned char StepVAL)
{
    if (*Direction) // ��
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
    else    // ��
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
            TouchReset_Color(); // ������ɺ�λ����
            CW_Color.Direction = 0;
            Twinkle_SET(0, 7, 7, 100); // ������˸
        }
    }
    else if (CW_Color.Set == Color_CW_Array[0])
    {
        Twinkle_SET(1, 8, 8, 100);
        if (Color_LongRelease)
        {
            TouchReset_Color(); // ������ɺ�λ����
            CW_Color.Direction = 1;
            Twinkle_SET(0, 7, 7, 100); // ������˸
        }
    }
*/
