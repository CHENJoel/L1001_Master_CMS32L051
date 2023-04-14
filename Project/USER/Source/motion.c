#include "Function_Init.H"
#include "motion.h"

// FrameInfro_TypeDef FrameInfro;
Effect_TypeDef EF_Work;

EFdata_TypeDef EF_WorkData; // Ĭ�ϲ�����
EF_BUFFER_TypeDef EF_Buffer;
/*

enum
{
    MOVE_UP,       // �����ƶ�
    MOVE_DOWN,     // �����ƶ�
    MOVE_LEFT,     // �����ƶ�
    MOVE_RIGHT,    // �����ƶ�
    MOVE_SEPARATE, // ���ܷ�ɢ
    MOVE_CONVERGE, // ���Ļ��
};



*/

// ��ȡ��ǰ��Ч���������

void Fetch_EF_DATA(void)
{
    EF_para_data_TypeDef EF_para_data;
    color_group_TypeDef color_group;
    Read_UserEF_Paradata(EF_Work.EF_ID, &EF_para_data);
    memcpy(&EF_Buffer.para_data, &EF_para_data, sizeof(EF_para_data_TypeDef));
    Read_UserEF_Colordata(EF_Work.EF_ID, &color_group);
    memcpy(&EF_Buffer.color_buffer, &color_group, sizeof(color_group_TypeDef));

    // if (EF_Work.EF_ID <= 30)
    // {
    //     memset(&EF_Buffer.color_buffer, 0, sizeof(EF_Buffer.color_buffer));
    //     memcpy(&EF_Buffer.color_buffer, EF_DefaultData[EF_Work.EF_ID].color_array, EF_DefaultData[EF_Work.EF_ID].color_sum * 4);
    // }
    // else
    // {
    //     Read_UserEF_Colordata(EF_Work.EF_ID, &color_group);
    //     memcpy(&EF_Buffer.color_buffer, &color_group, sizeof(color_group_TypeDef));
    // }

}

// ֡���ȸ�λ
void Frame_Reset(void)
{
    uint8_t i;
    for (i = 0; i < 16; i++)
    {
        Tangram[i].Frame_Now = 0;
    }
}

uint8_t diff_cal(uint8_t val1, uint8_t val2)
{
    if (val1 > val2)
    {
        return val1 - val2;
    }
    else
    {
        return val2 - val1;
    }
}

void Motion_Static_Init(void)
{
    uint16_t i, j, k;
    uint8_t *sur;
    uint8_t *tar;
    uint8_t randomVal;

    EF_Work.FrameInfro.KeySum = EF_Buffer.para_data.color_sum;      // �ؼ�֡��
    EF_Work.FrameInfro.InsertNum = Motion_Static_framepara; // ��֡��
    EF_Work.FrameInfro.IntervalTime = 1;                    // ֡���ʱ��
    EF_Work.FrameInfro.FrameAmount = 1;                     // ��֡��
    EF_Work.FrameInfro.Speed = 1;
    // // EF_Work.FrameInfro.addr_table = EF_WorkData.addr_table;
    tar = EF_Work.FrameInfro.image_adr; // ɫ����ָ��
    sur = &EF_Buffer.color_buffer;      // Դɫ��ָ��
    for (i = 0; i < EF_Work.FrameInfro.KeySum; i++)
    {
        for (j = 0; j < 4; j++) // ����Դ����
        {
            *tar = *sur;
            tar++;
            sur++;
        }
    }

    for (i = 0; i < TangramDevice.Device_sum; i++)
    {
        TangramDevice.SlaveData[i].Runingnum = i;
    }
    EF_Work.Module_WorkNum = TangramDevice.Device_sum;

    if (EF_Work.FrameInfro.KeySum == 1)
    {
        for (i = 0; i < EF_Work.Module_WorkNum; i++)
        {
            Tangram[i].R.Now = *(EF_Work.FrameInfro.image_adr + 0);
            Tangram[i].G.Now = *(EF_Work.FrameInfro.image_adr + 1);
            Tangram[i].B.Now = *(EF_Work.FrameInfro.image_adr + 2);
            Tangram[i].W.Now = *(EF_Work.FrameInfro.image_adr + 3);
        }
    }
    else
    {
        for (i = 0; i < EF_Work.Module_WorkNum; i++)
        {
            randomVal = Random_Generate() % EF_Work.FrameInfro.KeySum;
            Tangram[i].R.Now = *(EF_Work.FrameInfro.image_adr + randomVal * 4 + 0);
            Tangram[i].G.Now = *(EF_Work.FrameInfro.image_adr + randomVal * 4 + 1);
            Tangram[i].B.Now = *(EF_Work.FrameInfro.image_adr + randomVal * 4 + 2);
            Tangram[i].W.Now = *(EF_Work.FrameInfro.image_adr + randomVal * 4 + 3);
        }
    }
}
void Motion_Breath_Init(void)
{
    uint16_t i, j;
    uint8_t *sur;
    uint8_t *tar;

    EF_Work.FrameInfro.KeySum = EF_Buffer.para_data.color_sum * 2;                            // �ؼ�֡��
    EF_Work.FrameInfro.InsertNum = Motion_Breath_framepara;                                                              // ��֡��
    EF_Work.FrameInfro.IntervalTime = 1;                       // ֡���ʱ��
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // ��֡��

    tar = EF_Work.FrameInfro.image_adr;           // ɫ����ָ��
    sur = &EF_Buffer.color_buffer; // Դɫ��ָ��
    for (i = 0; i < EF_Buffer.para_data.color_sum; i++)
    {
        for (j = 0; j < 4; j++) // ����Դ����
        {
            *tar = *sur;
            tar++;
            sur++;
        }
        for (j = 0; j < 4; j++) // �������
        {
            *tar = 0;
            tar++;
        }
    }
}
void Motion_Stream_Init(void)
{
    uint16_t i, j;
    uint8_t *sur;
    uint8_t *tar;
    EF_Work.FrameInfro.KeySum = EF_Buffer.para_data.color_sum;                                // �ؼ�֡��
    EF_Work.FrameInfro.InsertNum = Motion_Stream_framepara;                             // ��֡��
    EF_Work.FrameInfro.IntervalTime = 1;                       // ֡���ʱ��
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // ��֡��

    tar = EF_Work.FrameInfro.image_adr;                                                              // ɫ����ָ��
    sur = &EF_Buffer.color_buffer;                                                    // Դɫ��ָ��
    for (i = 0; i < EF_Work.FrameInfro.KeySum; i++)
    {
        for (j = 0; j < 4; j++) // ����Դ����
        {
            *tar = *sur;
            tar++;
            sur++;
        }
    }
}
void Motion_Reverberate_Init(void)
{
    uint16_t i, j;
    uint8_t *sur;
    uint8_t *tar;
    EF_Work.FrameInfro.KeySum = EF_Buffer.para_data.color_sum * 2 - 1;                        // �ؼ�֡��
    EF_Work.FrameInfro.InsertNum = Motion_Reverberate_framepara;                             // ��֡��
    EF_Work.FrameInfro.IntervalTime = 1;                       // ֡���ʱ��
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // ��֡��
                                                                                                     // printf("k:%d Is:%d It:%d Am:%d\r\n",EF_Work.FrameInfro.KeySum,EF_Work.FrameInfro.InsertNum,EF_Work.FrameInfro.IntervalTime,EF_Work.FrameInfro.FrameAmount);

    tar = EF_Work.FrameInfro.image_adr;                                                              // ɫ����ָ��
    sur = &EF_Buffer.color_buffer;                                                    // Դɫ��ָ��
    for (i = 0; i < EF_Buffer.para_data.color_sum; i++)
    {
        for (j = 0; j < 4; j++) // ����Դ����
        {
            *tar = *sur;
            tar++;
            sur++;
        }
    }
    if (EF_Buffer.para_data.color_sum > 1)
    {
        sur = &EF_Buffer.color_buffer;
        sur += (EF_Buffer.para_data.color_sum - 2) * 4;
        for (i = 0; i < EF_Buffer.para_data.color_sum - 1; i++) // ��䵹���Դ����
        {
            for (j = 0; j < 4; j++)
            {
                *tar = *sur;
                tar++;
                sur++;
            }
            sur -= 8;
        }
    }
}
void Motion_Hopscotch_Init(void)
{
    uint16_t i, j;
    uint8_t *sur;
    uint8_t *tar;

    EF_Work.FrameInfro.KeySum = EF_Buffer.para_data.color_sum;                                // �ؼ�֡��
    EF_Work.FrameInfro.InsertNum = (EF_Work.Module_WorkNum + 1) * Motion_Hopscotch_framepara;        // ��֡��
    EF_Work.FrameInfro.IntervalTime = 1;                                                             // ֡���ʱ��(ʹ�ò�֡��)
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // ��֡��

    // //  printf("k:%d Is:%d It:%d Am:%d\r\n",EF_Work.FrameInfro.KeySum,EF_Work.FrameInfro.InsertNum,EF_Work.FrameInfro.IntervalTime,EF_Work.FrameInfro.FrameAmount);
    tar = EF_Work.FrameInfro.image_adr;                                                              // ɫ����ָ��
    sur = &EF_Buffer.color_buffer;                                                    // Դɫ��ָ��
    for (i = 0; i < EF_Work.FrameInfro.KeySum; i++)
    {
        for (j = 0; j < 4; j++) // ����Դ����
        {
            *tar = *sur;
            tar++;
            sur++;
        }
    }
}
void Motion_Lightning_Init(void)
{
    uint16_t i, j;
    uint8_t *sur;
    uint8_t *tar;

    EF_Work.FrameInfro.KeySum = EF_Buffer.para_data.color_sum;                                // �ؼ�֡��
    EF_Work.FrameInfro.InsertNum = EF_Work.FrameInfro.KeySum * Motion_Lightning_framepara;  // ��֡��*������֡
    EF_Work.FrameInfro.IntervalTime = 1;                       // ֡���ʱ��
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // ��֡��
    // // // // printf("k:%d Is:%d It:%d Am:%d\r\n",EF_Work.FrameInfro.KeySum,EF_Work.FrameInfro.InsertNum,EF_Work.FrameInfro.IntervalTime,EF_Work.FrameInfro.FrameAmount);

    tar = EF_Work.FrameInfro.image_adr;           // ɫ����ָ��
    sur = &EF_Buffer.color_buffer; // Դɫ��ָ��
    for (i = 0; i < EF_Work.FrameInfro.KeySum; i++)
    {
        for (j = 0; j < 4; j++) // ����Դ����
        {
            *tar = *sur;
            tar++;
            sur++;
        }
    }
}
void Motion_Ignite_Init(void)
{
    uint16_t i, j;
    uint8_t *sur;
    uint8_t *tar;

    EF_Work.FrameInfro.KeySum = EF_Buffer.para_data.color_sum;                                // �ؼ�֡��
    EF_Work.FrameInfro.InsertNum = Motion_Ignite_framepara;                             // ��֡��
    EF_Work.FrameInfro.IntervalTime = 1;                       // ֡���ʱ��
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // ��֡��
    // // printf("k:%d Is:%d It:%d Am:%d\r\n",EF_Work.FrameInfro.KeySum,EF_Work.FrameInfro.InsertNum,EF_Work.FrameInfro.IntervalTime,EF_Work.FrameInfro.FrameAmount);

    tar = EF_Work.FrameInfro.image_adr;           // ɫ����ָ��
    sur = &EF_Buffer.color_buffer; // Դɫ��ָ��
    for (i = 0; i < EF_Work.FrameInfro.KeySum; i++)
    {
        for (j = 0; j < 4; j++) // ����Դ����
        {
            *tar = *sur;
            tar++;
            sur++;
        }
    }
}
void Motion_Random_Init(void)
{
    uint16_t i, j;
    uint8_t *sur;
    uint8_t *tar;

    EF_Work.FrameInfro.KeySum = EF_Buffer.para_data.color_sum;                                // �ؼ�֡��
    EF_Work.FrameInfro.InsertNum = Motion_Random_framepara;                             // ��֡��
    EF_Work.FrameInfro.IntervalTime = 1;                       // ֡���ʱ��
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // ��֡��


    tar = EF_Work.FrameInfro.image_adr;           // ɫ����ָ��
    sur = &EF_Buffer.color_buffer; // Դɫ��ָ��
    for (i = 0; i < EF_Work.FrameInfro.KeySum; i++)
    {
        for (j = 0; j < 4; j++) // ����Դ����
        {
            *tar = *sur;
            tar++;
            sur++;
        }
    }
    for (i = 0; i < TangramDevice.Device_sum; i++)
    {
        TangramDevice.SlaveData[i].Runingnum = i; // �����Ч���ַ���
    }
    EF_Work.Module_WorkNum = TangramDevice.Device_sum;
}

void Effect_Init(void)
{
    uint16_t i, j,k;
    uint8_t *sur;
    uint8_t *tar;
    uint8_t temp1, temp2,temp3,temp4;
    uint8_t X_max, X_min, Y_max, Y_min, X_center, Y_center;
    uint8_t X_num,Y_num;
    printf("\r\n");
    Fetch_EF_DATA();// ��ȡ��ǰ��Ч���������
    Frame_Reset();
    // for (i = 0; i < 30; i++)    // ��ȡĬ��������Ϣ
    // {
    // EF_Work.EF_ID = i = 11;
    i=EF_Work.EF_ID;
    printf("EF:%2d\r",EF_Work.EF_ID);


    // EF_Buffer
    // EF_Buffer.para_data



    // // // EF_WorkData.color_array = EF_DefaultData[i].color_array;    // Դɫ��ָ�� �滻�� &EF_Buffer.color_buffer
    // // // EF_WorkData.color_sum = EF_DefaultData[i].color_sum;    // ɫ����ɫ���� �滻�� EF_Buffer.para_data.color_sum
    // // // EF_WorkData.Speed = EF_DefaultData[i].Speed;
    // // // EF_Work.FrameInfro.Speed = EF_WorkData.Speed;   // �ٶ� EF_Work.FrameInfro.Speed=EF_Buffer.para_data.speed

    EF_Work.FrameInfro.Speed=EF_Buffer.para_data.speed;  /*���� EF_Work.FrameInfro.Speed */

    // // // // EF_WorkData.motion_flag = EF_DefaultData[i].motion_flag;    //��Ч���  EF_WorkData.motion_flag=EF_Buffer.para_data.motion��
    // // // // EF_Work.MotionType = EF_WorkData.motion_flag; // ��Ч����

    // // // EF_WorkData.Mode = EF_DefaultData[i].Mode;
    // // // EF_Work.FrameInfro.Mode = EF_WorkData.Mode; // ��ͨ/�ɶ�    EF_Work.FrameInfro.Mode �滻�� EF_Buffer.para_data.Mode

////    EF_WorkData.addr_table = EF_DefaultData[i].addr_table;



    // // // // EF_Work.MoveType = EF_WorkData.move_flag;     // �˶�����   �滻�� EF_Buffer.para_data.move


    EF_Work.FrameInfro.image_adr = (uint8_t *)&EF_Work.Color_buffer; // ɫ������



    /* test */

    X_max = 0;
    X_min = 255;
    Y_max = 0;
    Y_min = 255;

    temp1 = temp2 = 0xFF;
    X_num = Y_num = 0;
    for (i = 0; i < TangramDevice.Device_sum; i++)
    {
        // // // printf("temp1:%d [%d]:%d\r",temp1,i,TangramDevice.SlaveData[i].Coord.X);
        if (temp1 != TangramDevice.SlaveData[i].Coord.X)
        {
            X_num++; // �ۼ�X�����ϵ��豸����
        }
        if (temp2 != TangramDevice.SlaveData[i].Coord.Y)
        {
            Y_num++; // �ۼ�Y�����ϵ��豸����
        }
        if (TangramDevice.SlaveData[i].Coord.X > X_max)
        {
            X_max = TangramDevice.SlaveData[i].Coord.X; // �����X����
        }
        if (TangramDevice.SlaveData[i].Coord.Y > Y_max)
        {
            Y_max = TangramDevice.SlaveData[i].Coord.Y; // �����Y����
        }
        if (TangramDevice.SlaveData[i].Coord.X < X_min)
        {
            X_min = TangramDevice.SlaveData[i].Coord.X; // ����СX����
        }
        if (TangramDevice.SlaveData[i].Coord.Y < Y_min)
        {
            Y_min = TangramDevice.SlaveData[i].Coord.Y; // ����СY����
        }
        temp1 = TangramDevice.SlaveData[i].Coord.X;
        temp2 = TangramDevice.SlaveData[i].Coord.Y;
    }
    // // // printf("X:%d Y:%d\r",X_num,Y_num);
    if (EF_Buffer.para_data.move == MOVE_UP || EF_Buffer.para_data.move == MOVE_DOWN)
    {
        EF_Work.Module_WorkNum = Y_num;
        temp1 = 0;
        temp2 = 0;
        for (j = 0; j < 16; j++)
        {
            for (i = 0; i < TangramDevice.Device_sum; i++)
            {
                if (TangramDevice.SlaveData[i].Coord.Y == j)
                {
                    temp2 = 1; // ��ǰ�������豸
                    if (EF_Buffer.para_data.move == MOVE_UP)
                    {
                        TangramDevice.SlaveData[i].Runingnum = temp1; // ����
                    }
                    else
                    {
                        TangramDevice.SlaveData[i].Runingnum = Y_num - temp1 - 1; // ����;
                    }
                }
            }
            if (temp2)
            {
                temp1++;
                temp2 = 0;
            }
        }
    }
    else if (EF_Buffer.para_data.move == MOVE_LEFT || EF_Buffer.para_data.move == MOVE_RIGHT)
    {
        EF_Work.Module_WorkNum = X_num;
        temp1 = 0;
        temp2 = 0;
        for (j = 0; j < 16; j++)
        {
            for (i = 0; i < TangramDevice.Device_sum; i++)
            {
                if (TangramDevice.SlaveData[i].Coord.X == j)
                {
                    temp2 = 1; // ��ǰ�������豸
                    if (EF_Buffer.para_data.move == MOVE_LEFT)
                    {
                        TangramDevice.SlaveData[i].Runingnum = temp1; // ����
                    }
                    else
                    {
                        TangramDevice.SlaveData[i].Runingnum = X_num - temp1 - 1; // ����;
                    }
                }
            }
            if (temp2)
            {
                temp1++;
                temp2 = 0;
            }
        }
    }
    else if (EF_Buffer.para_data.move == MOVE_SEPARATE || EF_Buffer.para_data.move == MOVE_CONVERGE)
    {

        X_center = (X_max + X_min)/2;
        Y_center = (Y_max + Y_min)/2;
        temp4 = 0;
        for (j = 0; j < 16; j++)
        {
            temp3 = 0;
            for (i = 0; i < TangramDevice.Device_sum; i++)
            {
                temp1 = diff_cal(X_center, TangramDevice.SlaveData[i].Coord.X);
                temp2 = diff_cal(Y_center, TangramDevice.SlaveData[i].Coord.Y);
                if (temp1 > temp2)
                {
                    if (temp1 == j)
                    {
                        temp3 = 1;
                        TangramDevice.SlaveData[i].Runingnum = temp4; // ����
                    }
                }
                else
                {
                    if (temp2 == j)
                    {
                        temp3 = 1;
                        TangramDevice.SlaveData[i].Runingnum = temp4; // ����
                    }
                }
            }
            if (temp3)
            {
                temp4++;
            }
        }
        temp4 = 0;
        if (EF_Buffer.para_data.move == MOVE_CONVERGE)
        {
            for (i = 0; i < TangramDevice.Device_sum; i++)
            {
                if (TangramDevice.SlaveData[i].Runingnum > temp4)
                {
                    temp4 = TangramDevice.SlaveData[i].Runingnum; // ��ѯ�������
                }
            }
            for (i = 0; i < TangramDevice.Device_sum; i++)
            {
                temp1 = TangramDevice.SlaveData[i].Runingnum;
                TangramDevice.SlaveData[i].Runingnum = temp4 - temp1; // ���ɵ�����
            }
        }
    }

    switch (EF_Buffer.para_data.motion) // ���ݵ�Ч�����Զ�������ݣ������µ�ɫ����
    {
    case MOTION_STATIC: /*��̬*/
        Motion_Static_Init();
        break;
    case MOTION_BREATH: /*����*/
        Motion_Breath_Init();
        break;
    case MOTION_STREAM: /*����*/
        Motion_Stream_Init();
        break;
    case MOTION_REVERB: /*����*/
        Motion_Reverberate_Init();
        break;
    case MOTION_HOPSCO: /*����*/
        Motion_Hopscotch_Init();
        break;
    case MOTION_LIGHTN: /*����*/
        Motion_Lightning_Init();
        break;
    case MOTION_IGNITE: /*��ȼ*/
        Motion_Ignite_Init();
        break;
    case MOTION_RANDOM: /*���*/
        Motion_Random_Init();
        break;
    default:
        break;
    }
    printf("k:%d Is:%d It:%d Am:%d\r\n",EF_Work.FrameInfro.KeySum,EF_Work.FrameInfro.InsertNum,EF_Work.FrameInfro.IntervalTime,EF_Work.FrameInfro.FrameAmount);

    // switch (EF_Buffer.para_data.move)
    // {
    // case MOVE_UP:
    //     printf("\r'MOVE_UP'\r\n");
    //     break;
    // case MOVE_DOWN:
    //     printf("\r'MOVE_DOWN'\r\n");
    //     break;
    // case MOVE_LEFT:
    //     printf("\r'MOVE_LEFT'\r\n");
    //     break;
    // case MOVE_RIGHT:
    //     printf("\r'MOVE_RIGHT'\r\n");
    //     break;
    // case MOVE_SEPARATE:
    //     printf("\r'MOVE_SEPARATE'\r\n");
    //     break;
    // case MOVE_CONVERGE:
    //     printf("\r'MOVE_CONVERGE'\r\n");
    //     break;
    // default:
    //     break;
    // }
    printf("Device_sum:%d\r", TangramDevice.Device_sum);
    printf("Module_WorkNum:%d\r", EF_Work.Module_WorkNum);
    for (i = 0; i < TangramDevice.Device_sum; i++)
    {
        printf("ID:[0x%2x] [%d][%d]num: %d \r", TangramDevice.SlaveData[i].ID, TangramDevice.SlaveData[i].Coord.X, TangramDevice.SlaveData[i].Coord.Y, TangramDevice.SlaveData[i].Runingnum);
    }

    // for (i = 0; i < 16; i++)
    // {
    //     Tangram[i].Frame_Now = 0;
    //     printf("[%d] %d\r",i,Tangram[i].Frame_Now);
    // }
}

void Motion_Output(void)
{
    static uint8_t speed_Val;
    static uint8_t Last_Light_Owner;
    uint8_t i;
    if (Light_Owner == Light_Owner_APP) // APP�ص�
    {
        if (Last_Light_Owner != Light_Owner_APP)
        {
            for (i = 0; i < TangramDevice.Device_sum; i++)
            {
                TangramDevice.SlaveData[i].Color.R = 0;
                TangramDevice.SlaveData[i].Color.G = 0;
                TangramDevice.SlaveData[i].Color.B = 0;
                TangramDevice.SlaveData[i].Color.W = 0;
            }
        }
    }
    else // MCU�ص�
    {
        if (EF_Buffer.para_data.Mode == MODE_RHYTHM)
        {
            // if (MIC_Process())
            // {
            //     speed_Val = 50;
            // }
            // else
            // {
            //     if (speed_Val > 2)
            //     {
            //         speed_Val--;
            //     }
            // }
        }
        else // MODE_NORMAL
        {
            speed_Val = EF_Work.FrameInfro.Speed;
        }
        // printf("%d\r",EF_Buffer.para_data.motion);

        switch (EF_Buffer.para_data.motion)
        {
        case MOTION_STATIC: // ��̬
            Motion_Static();
            break;
        case MOTION_BREATH: // ����
            Motion_Breath(speed_Val);
            break;
        case MOTION_STREAM: // ����
            Motion_Stream(speed_Val);
            break;
        case MOTION_REVERB: // ����
            Motion_Reverberate(speed_Val);
            break;
        case MOTION_HOPSCO: // ����
            Motion_Hopscotch(speed_Val);
            break;
        case MOTION_LIGHTN: // ����
            Motion_Lightning(speed_Val);
            break;
        case MOTION_IGNITE: // ��ȼ
            Motion_Ignite(speed_Val);
            break;
        case MOTION_RANDOM: // ���
            Motion_Random(speed_Val);
            break;
        default:
            break;
        }
        Slave_ColorData_Allot();
        // printf("%d,%d,%d,%d\r\n",Tangram[0].R.Now,Tangram[0].G.Now,Tangram[0].B.Now,Tangram[0].W.Now);
    }

    Slave_ColorData_DMA();
    Last_Light_Owner = Light_Owner;
}
void Motion_Static(void) /*����*/
{
    // ���ֳ�ʼ������
}

void Motion_Breath(uint8_t speed) /*����*/
{
    uint8_t i;
    Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[0].Frame_Now, &Tangram[0].Frame_Now, speed);
    ModuleColor_Cal(&EF_Work.FrameInfro, &Tangram[0], 0);
    for (i = 1; i <= EF_Work.Module_WorkNum; i++)
    {
        Tangram[i].R.Now = Tangram[0].R.Now;
        Tangram[i].G.Now = Tangram[0].G.Now;
        Tangram[i].B.Now = Tangram[0].B.Now;
        Tangram[i].W.Now = Tangram[0].W.Now;
    }
    // // // printf("%4d / %4d\r",EF_Work.FrameInfro.FrameAmount, Tangram[0].Frame_Now);
}

void Motion_Stream(uint8_t speed)/*����*/
{
    uint8_t i;
    Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[0].Frame_Now, &Tangram[0].Frame_Now, speed);
    ModuleColor_Cal(&EF_Work.FrameInfro, &Tangram[0], 0);
    for (i = 1; i <= EF_Work.Module_WorkNum; i++)
    {
        Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[i].Frame_Now, &Tangram[i-1].Frame_Now, 60);
        ModuleColor_Cal(&EF_Work.FrameInfro, &Tangram[i], 0);
    }
}

void Motion_Reverberate(uint8_t speed) /*����*/
{
    uint8_t i;
    Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[0].Frame_Now, &Tangram[0].Frame_Now, speed);
    ModuleColor_Cal(&EF_Work.FrameInfro, &Tangram[0], 0);
    for (i = 1; i <= EF_Work.Module_WorkNum; i++)
    {
        Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[i].Frame_Now, &Tangram[i-1].Frame_Now, 60);
        ModuleColor_Cal(&EF_Work.FrameInfro, &Tangram[i], 0);
    }
    // printf("%d %d %d \r",EF_Work.FrameInfro.FrameAmount, Tangram[0].Frame_Now,speed);
}

void Motion_Hopscotch(uint8_t speed) /*����*/
{
    uint8_t i;
    uint8_t Currnt_KF;      // ��ǰ�ؼ�֡��keyframe�����
    uint8_t Next_KF;        // �¸��ؼ�֡��keyframe�����
    uint16_t Temp_FrameNum; // ��ʱ֡��ţ�����Ϊ��ǰ֡��frame�����ڵ�ǰ�ؼ�֡��keyframe������һ�ؼ�֡��keyframe����֮���֡���
    uint8_t Temp_FrameNum2; // ����ʱ֡
    Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[0].Frame_Now, &Tangram[0].Frame_Now, speed);
    Currnt_KF = Tangram[0].Frame_Now / (EF_Work.FrameInfro.InsertNum + 1);     // ���㵱ǰ֡ �Ѿ����� ���/��ǰ �ؼ�֡
    Temp_FrameNum = Tangram[0].Frame_Now % (EF_Work.FrameInfro.InsertNum + 1); //
    Next_KF = Currnt_KF + 1;                                                   // ���㵱ǰ֡ ׼�������� ��һ�ؼ�
    if (Next_KF >= EF_Work.FrameInfro.KeySum)
    {
        Next_KF = 0; // �л�����ĵ�һ���ؼ�֡
    }

    Temp_FrameNum2 = Temp_FrameNum / Motion_Hopscotch_framepara;
    if (Temp_FrameNum2)
    {
        for (i = 0; i <= EF_Work.Module_WorkNum; i++)
        {
            if (i == (Temp_FrameNum2 - 1))
            {
                Tangram[i].R.Now = *(EF_Work.FrameInfro.image_adr + Next_KF * 4 + 0);
                Tangram[i].G.Now = *(EF_Work.FrameInfro.image_adr + Next_KF * 4 + 1);
                Tangram[i].B.Now = *(EF_Work.FrameInfro.image_adr + Next_KF * 4 + 2);
                Tangram[i].W.Now = *(EF_Work.FrameInfro.image_adr + Next_KF * 4 + 3);
            }
            else
            {
                Tangram[i].R.Now = *(EF_Work.FrameInfro.image_adr + Currnt_KF * 4 + 0);
                Tangram[i].G.Now = *(EF_Work.FrameInfro.image_adr + Currnt_KF * 4 + 1);
                Tangram[i].B.Now = *(EF_Work.FrameInfro.image_adr + Currnt_KF * 4 + 2);
                Tangram[i].W.Now = *(EF_Work.FrameInfro.image_adr + Currnt_KF * 4 + 3);
            }
        }
    }
    else
    {
        for (i = 0; i <= EF_Work.Module_WorkNum; i++)
        {
            Tangram[i].R.Now = *(EF_Work.FrameInfro.image_adr + Currnt_KF * 4 + 0);
            Tangram[i].G.Now = *(EF_Work.FrameInfro.image_adr + Currnt_KF * 4 + 1);
            Tangram[i].B.Now = *(EF_Work.FrameInfro.image_adr + Currnt_KF * 4 + 2);
            Tangram[i].W.Now = *(EF_Work.FrameInfro.image_adr + Currnt_KF * 4 + 3);
        }
    }
}
void Motion_Lightning(uint8_t speed) /*����*/
{
    uint16_t temp;
    uint16_t on_p1,on_p2,off_p1,off_p2;
    uint8_t i;
    uint8_t Currnt_KF;                                                    // ��ǰ�ؼ�֡��keyframe�����
    uint16_t Temp_FrameNum;                                                // ��ʱ֡��ţ�����Ϊ��ǰ֡��frame�����ڵ�ǰ�ؼ�֡��keyframe������һ�ؼ�֡��keyframe����֮���֡���
    Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[0].Frame_Now, &Tangram[0].Frame_Now, speed);
    Currnt_KF = Tangram[0].Frame_Now / (EF_Work.FrameInfro.InsertNum + 1);     // ���㵱ǰ֡ �Ѿ����� ���/��ǰ �ؼ�֡
    Temp_FrameNum = Tangram[0].Frame_Now % (EF_Work.FrameInfro.InsertNum + 1); //
    temp = EF_Work.FrameInfro.InsertNum / 10;
    off_p1 = temp * 4;
    off_p2 = temp * 6;
    on_p1 = temp * 5;
    on_p2 = temp * 7;

    // printf("Am:%d Now:%d TF:%d Te:%d OF:%d ON:%d \r",EF_Work.FrameInfro.FrameAmount, Tangram[0].Frame_Now,Temp_FrameNum,temp,off_p1,on_p1);

    if (((Temp_FrameNum > off_p1) && (Temp_FrameNum <= on_p1)) || ((Temp_FrameNum > off_p2) && (Temp_FrameNum <= on_p2)))
    {
        Tangram[0].R.Now = 0;
        Tangram[0].G.Now = 0;
        Tangram[0].B.Now = 0;
        Tangram[0].W.Now = 0;
    }
    else
    {
        Tangram[0].R.Now = *(EF_Work.FrameInfro.image_adr + Currnt_KF * 4 + 0);
        Tangram[0].G.Now = *(EF_Work.FrameInfro.image_adr + Currnt_KF * 4 + 1);
        Tangram[0].B.Now = *(EF_Work.FrameInfro.image_adr + Currnt_KF * 4 + 2);
        Tangram[0].W.Now = *(EF_Work.FrameInfro.image_adr + Currnt_KF * 4 + 3);
    }

    for (i = 1; i <= EF_Work.Module_WorkNum; i++)
    {
        Tangram[i].R.Now = Tangram[0].R.Now;
        Tangram[i].G.Now = Tangram[0].G.Now;
        Tangram[i].B.Now = Tangram[0].B.Now;
        Tangram[i].W.Now = Tangram[0].W.Now;
    }

}

void Motion_Ignite(uint8_t speed) /*��ȼ*/
{
    uint8_t i;
    uint8_t Currnt_KF;      // ��ǰ�ؼ�֡��keyframe�����
    uint8_t Next_KF;        // �¸��ؼ�֡��keyframe�����
    uint16_t Temp_FrameNum; // ��ʱ֡��ţ�����Ϊ��ǰ֡��frame�����ڵ�ǰ�ؼ�֡��keyframe������һ�ؼ�֡��keyframe����֮���֡���
    Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[0].Frame_Now, &Tangram[0].Frame_Now, speed);
    Currnt_KF = Tangram[0].Frame_Now / (EF_Work.FrameInfro.InsertNum + 1);     // ���㵱ǰ֡ �Ѿ����� ���/��ǰ �ؼ�֡
    Temp_FrameNum = Tangram[0].Frame_Now % (EF_Work.FrameInfro.InsertNum + 1); //
    Next_KF = Currnt_KF + 1;                                                   // ���㵱ǰ֡ ׼�������� ��һ�ؼ�
    if (Next_KF >= EF_Work.FrameInfro.KeySum)
    {
        Next_KF = 0; // �л�����ĵ�һ���ؼ�֡
    }
    for (i = 0; i <= EF_Work.Module_WorkNum; i++)   // ��ɫ
    {
        Tangram[i].R.Now = *(EF_Work.FrameInfro.image_adr + Currnt_KF * 4 + 0);
        Tangram[i].G.Now = *(EF_Work.FrameInfro.image_adr + Currnt_KF * 4 + 1);
        Tangram[i].B.Now = *(EF_Work.FrameInfro.image_adr + Currnt_KF * 4 + 2);
        Tangram[i].W.Now = *(EF_Work.FrameInfro.image_adr + Currnt_KF * 4 + 3);
    }
    if (Temp_FrameNum > (EF_Work.FrameInfro.InsertNum / 2))
    {
        Tangram[0].R.Now = *(EF_Work.FrameInfro.image_adr + Next_KF * 4 + 0);
        Tangram[0].G.Now = *(EF_Work.FrameInfro.image_adr + Next_KF * 4 + 1);
        Tangram[0].B.Now = *(EF_Work.FrameInfro.image_adr + Next_KF * 4 + 2);
        Tangram[0].W.Now = *(EF_Work.FrameInfro.image_adr + Next_KF * 4 + 3);
    }
}
void Motion_Random(uint8_t speed) /*���*/
{
    static uint8_t last_KF;
    uint8_t Currnt_KF;      // ��ǰ�ؼ�֡��keyframe�����
    uint8_t i;
    uint8_t temp;
    uint8_t random1, random2, random3;
    Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[0].Frame_Now, &Tangram[0].Frame_Now, speed);
    Currnt_KF = Tangram[0].Frame_Now / (EF_Work.FrameInfro.InsertNum + 1); // ���㵱ǰ֡ �Ѿ����� ���/��ǰ �ؼ�֡
    if (Currnt_KF != last_KF)
    {
        random1 = Random_Generate() % EF_Work.Module_WorkNum; // ��������Ƶ�����
        for (i = 0; i <= random1; i++)
        {
            random2 = Random_Generate() % EF_Work.Module_WorkNum;    // �����������
            random3 = Random_Generate() % EF_Work.FrameInfro.KeySum; // �������ɫ
            Tangram[random2].R.Now = *(EF_Work.FrameInfro.image_adr + random3 * 4 + 0);
            Tangram[random2].G.Now = *(EF_Work.FrameInfro.image_adr + random3 * 4 + 1);
            Tangram[random2].B.Now = *(EF_Work.FrameInfro.image_adr + random3 * 4 + 2);
            Tangram[random2].W.Now = *(EF_Work.FrameInfro.image_adr + random3 * 4 + 3);
        }
    }
    last_KF = Currnt_KF;
}

// ����	reverberate
// ����	Hopscotch
// ����	Lightning
// ��ȼ	Ignite
// ���	Random








/*






    // // // // // switch (EF_Buffer.para_data.move)
    // // // // // {
    // // // // // case MOVE_UP:
    // // // // //     printf("\r\n\r\n'MOVE_UP'\r\n");
    // // // // //     break;
    // // // // // case MOVE_DOWN:
    // // // // //     printf("\r\n\r\n'MOVE_DOWN'\r\n");
    // // // // //     break;
    // // // // // case MOVE_LEFT:
    // // // // //     printf("\r\n\r\n'MOVE_LEFT'\r\n");
    // // // // //     break;
    // // // // // case MOVE_RIGHT:
    // // // // //     printf("\r\n\r\n'MOVE_RIGHT'\r\n");
    // // // // //     break;
    // // // // // case MOVE_SEPARATE:
    // // // // //     printf("\r\n\r\n'MOVE_SEPARATE'\r\n");
    // // // // //     break;
    // // // // // case MOVE_CONVERGE:
    // // // // //     printf("\r\n\r\n'MOVE_CONVERGE'\r\n");
    // // // // //     break;
    // // // // // default:
    // // // // //     break;
    // // // // // }
    // // // // // for (i = 0; i < TangramDevice.Device_sum; i++)
    // // // // // {
    // // // // //     printf("ID:[%d] num: %d \r", TangramDevice.SlaveData[i].ID, TangramDevice.SlaveData[i].Runingnum);
    // // // // // }

    // // printf("\r\n\r\n\r\n");
    // // for (i = 0; i < 16; i++)
    // // {
    // //     for (j = 0; j < 16; j++)
    // //     {
    // //         printf("[%d][%d] ",j,EF_Work.ID_Table[i][j]);
    // //     }
    // //     printf("\r");
    // // }
    // // printf("\r\n\r\n\r\n");
    // else if (EF_Buffer.para_data.move == MOVE_SEPARATE || EF_Buffer.para_data.move == MOVE_CONVERGE)
    // {

    // }





-----------------------------------------------------------------------------------------------------------------------


*/
