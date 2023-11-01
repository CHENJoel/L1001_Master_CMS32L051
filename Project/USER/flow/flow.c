#include "Function_Init.H"
#include "flow.h"


/*
 * @Description: �����Ч��������
 * @param:
 * @return:
*/
void effect_play_color_calu(void)
{
    uint8_t speed_Val = 5;
    switch (play.efdetail.Flow)
    {
    case FLOW_STATIC: // ��̬
        Flow_Static();
        break;
    case FLOW_BREATH: // ����
        Flow_Breath(speed_Val);
        break;
    case FLOW_STREAM: // ����
        Flow_Stream(speed_Val);
        break;
    case FLOW_REVERB: // ����
        Flow_Reverberate(speed_Val);
        break;
    case FLOW_HOPSCO: // ����
        Flow_Hopscotch(speed_Val);
        break;
    case FLOW_LIGHTN: // ����
        Flow_Lightning(speed_Val);
        break;
    case FLOW_IGNITE: // ��ȼ
        Flow_Ignite(speed_Val);
        break;
    case FLOW_RANDOM: // ���
        Flow_Random(speed_Val);
        break;
    default:
        break;
    }
}

void Flow_Static_Init(void)
{
    uint8_t i, j;
    uint8_t flag;
    EF_Work.Module_WorkNum = slave.num;
    for (i = 0; i < slave.num; i++)
    {
        slave.data[i].runnum = i;
        flag = 0;
        for (j = 0; j < play.efdetail.EfColorInf.colorNum; j++)
        {
            if (slave.data[i].id == play.efdetail.EfColorInf.ColorID[j].id) // ���Ѷ����id��ɫ
            {
                Tangram[i].R.Now = play.efdetail.EfColorInf.ColorID[j].color.R;
                Tangram[i].G.Now = play.efdetail.EfColorInf.ColorID[j].color.G;
                Tangram[i].B.Now = play.efdetail.EfColorInf.ColorID[j].color.B;
                Tangram[i].W.Now = play.efdetail.EfColorInf.ColorID[j].color.W;
                flag = 1;
            }
        }
        if (flag == 0)
        {
            flag = Random_Generate() % play.efdetail.EfColorInf.colorNum; // δ�����id�����ɫ
            Tangram[i].R.Now = play.efdetail.EfColorInf.ColorID[flag].color.R;
            Tangram[i].G.Now = play.efdetail.EfColorInf.ColorID[flag].color.G;
            Tangram[i].B.Now = play.efdetail.EfColorInf.ColorID[flag].color.B;
            Tangram[i].W.Now = play.efdetail.EfColorInf.ColorID[flag].color.W;
        }
    }
    /**************************/
    // // // uint8_t *sur;
    // // // uint8_t *tar;
    // // // uint8_t randomVal;

    // // // EF_Work.FrameInfro.KeySum = play.efdetail.EfColorInf.colorNum; // �ؼ�֡��
    // // // EF_Work.FrameInfro.InsertNum = Motion_Static_framepara;    // ��֡��
    // // // EF_Work.FrameInfro.IntervalTime = 1;                       // ֡���ʱ��
    // // // EF_Work.FrameInfro.FrameAmount = 1;                        // ��֡��
    // // // EF_Work.FrameInfro.Speed = 1;
    // // // tar = EF_Work.FrameInfro.image_adr; // ɫ����ָ��
    // // // sur = &EF_Buffer.color_buffer;      // Դɫ��ָ��
    // // // for (i = 0; i < EF_Work.FrameInfro.KeySum; i++)
    // // // {
    // // //     for (j = 0; j < 4; j++) // ����Դ����
    // // //     {
    // // //         *tar = *sur;
    // // //         tar++;
    // // //         sur++;
    // // //     }
    // // // }

    // // // for (i = 0; i < TangramDevice.Device_sum; i++)
    // // // {
    // // //     TangramDevice.SlaveData[i].Runingnum = i;
    // // // }
    // // // EF_Work.Module_WorkNum = TangramDevice.Device_sum;

    // // // if (EF_Work.FrameInfro.KeySum == 1)
    // // // {
    // // //     for (i = 0; i < EF_Work.Module_WorkNum; i++)
    // // //     {
    // // //         Tangram[i].R.Now = *(EF_Work.FrameInfro.image_adr + 0);
    // // //         Tangram[i].G.Now = *(EF_Work.FrameInfro.image_adr + 1);
    // // //         Tangram[i].B.Now = *(EF_Work.FrameInfro.image_adr + 2);
    // // //         Tangram[i].W.Now = *(EF_Work.FrameInfro.image_adr + 3);
    // // //     }
    // // // }
    // // // else
    // // // {
    // // //     for (i = 0; i < EF_Work.Module_WorkNum; i++)
    // // //     {
    // // //         randomVal = Random_Generate() % EF_Work.FrameInfro.KeySum;
    // // //         Tangram[i].R.Now = *(EF_Work.FrameInfro.image_adr + randomVal * 4 + 0);
    // // //         Tangram[i].G.Now = *(EF_Work.FrameInfro.image_adr + randomVal * 4 + 1);
    // // //         Tangram[i].B.Now = *(EF_Work.FrameInfro.image_adr + randomVal * 4 + 2);
    // // //         Tangram[i].W.Now = *(EF_Work.FrameInfro.image_adr + randomVal * 4 + 3);
    // // //     }
    // // // }
}
void Flow_Breath_Init(void)
{
    uint16_t i, j;
    uint8_t *sur;
    uint8_t *tar;

    EF_Work.FrameInfro.KeySum = play.efdetail.EfColorInf.colorNum * 2;                                   // �ؼ�֡��
    EF_Work.FrameInfro.InsertNum = Motion_Breath_framepara;                                          // ��֡��
    EF_Work.FrameInfro.IntervalTime = 1;                                                             // ֡���ʱ��
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // ��֡��

    tar = EF_Work.FrameInfro.image_adr; // ɫ����ָ��
    sur = &EF_Buffer.color_buffer;      // Դɫ��ָ��
    for (i = 0; i < play.efdetail.EfColorInf.colorNum; i++)
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
void Flow_Stream_Init(void)
{
    uint16_t i, j;
    uint8_t *sur;
    uint8_t *tar;
    EF_Work.FrameInfro.KeySum = play.efdetail.EfColorInf.colorNum;                                       // �ؼ�֡��
    EF_Work.FrameInfro.InsertNum = Motion_Stream_framepara;                                          // ��֡��
    EF_Work.FrameInfro.IntervalTime = 1;                                                             // ֡���ʱ��
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // ��֡��

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
}

void Flow_Reverberate_Init(void)
{
    uint16_t i, j;
    uint8_t *sur;
    uint8_t *tar;

    EF_Work.FrameInfro.KeySum = play.efdetail.EfColorInf.colorNum * 2 - 1;                               // �ؼ�֡��
    EF_Work.FrameInfro.InsertNum = Motion_Reverberate_framepara;                                     // ��֡��
    EF_Work.FrameInfro.IntervalTime = 1;                                                             // ֡���ʱ��
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // ��֡��
                                                                                                     // printf("k:%d Is:%d It:%d Am:%d\r\n",EF_Work.FrameInfro.KeySum,EF_Work.FrameInfro.InsertNum,EF_Work.FrameInfro.IntervalTime,EF_Work.FrameInfro.FrameAmount);

    tar = EF_Work.FrameInfro.image_adr; // ɫ����ָ��
    sur = &EF_Buffer.color_buffer;      // Դɫ��ָ��
    for (i = 0; i < play.efdetail.EfColorInf.colorNum; i++)
    {
        for (j = 0; j < 4; j++) // ����Դ����
        {
            *tar = *sur;
            tar++;
            sur++;
        }
    }
    if (play.efdetail.EfColorInf.colorNum > 1)
    {
        sur = &EF_Buffer.color_buffer;
        sur += (play.efdetail.EfColorInf.colorNum - 2) * 4;
        for (i = 0; i < play.efdetail.EfColorInf.colorNum - 1; i++) // ��䵹���Դ����
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
void Flow_Hopscotch_Init(void)
{
    uint16_t i, j;
    uint8_t *sur;
    uint8_t *tar;

    EF_Work.FrameInfro.KeySum = play.efdetail.EfColorInf.colorNum;                                       // �ؼ�֡��
    EF_Work.FrameInfro.InsertNum = (EF_Work.Module_WorkNum + 1) * Motion_Hopscotch_framepara;        // ��֡��
    EF_Work.FrameInfro.IntervalTime = 1;                                                             // ֡���ʱ��(ʹ�ò�֡��)
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // ��֡��

    // //  printf("k:%d Is:%d It:%d Am:%d\r\n",EF_Work.FrameInfro.KeySum,EF_Work.FrameInfro.InsertNum,EF_Work.FrameInfro.IntervalTime,EF_Work.FrameInfro.FrameAmount);
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
}
void Flow_Lightning_Init(void)
{
    uint16_t i, j;
    uint8_t *sur;
    uint8_t *tar;

    EF_Work.FrameInfro.KeySum = play.efdetail.EfColorInf.colorNum;                                       // �ؼ�֡��
    EF_Work.FrameInfro.InsertNum = EF_Work.FrameInfro.KeySum * Motion_Lightning_framepara;           // ��֡��*������֡
    EF_Work.FrameInfro.IntervalTime = 1;                                                             // ֡���ʱ��
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // ��֡��
    // // // // printf("k:%d Is:%d It:%d Am:%d\r\n",EF_Work.FrameInfro.KeySum,EF_Work.FrameInfro.InsertNum,EF_Work.FrameInfro.IntervalTime,EF_Work.FrameInfro.FrameAmount);

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
}
void Flow_Ignite_Init(void)
{
    uint16_t i, j;
    uint8_t *sur;
    uint8_t *tar;

    EF_Work.FrameInfro.KeySum = play.efdetail.EfColorInf.colorNum;                                       // �ؼ�֡��
    EF_Work.FrameInfro.InsertNum = Motion_Ignite_framepara;                                          // ��֡��
    EF_Work.FrameInfro.IntervalTime = 1;                                                             // ֡���ʱ��
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // ��֡��
    // // printf("k:%d Is:%d It:%d Am:%d\r\n",EF_Work.FrameInfro.KeySum,EF_Work.FrameInfro.InsertNum,EF_Work.FrameInfro.IntervalTime,EF_Work.FrameInfro.FrameAmount);

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
}
void Flow_Random_Init(void)
{
    uint8_t i;
    uint8_t num;
    EF_Work.Module_WorkNum = slave.num;
    for (i = 0; i < slave.num; i++)
    {
        slave.data[i].runnum = i;
        num = Random_Generate() % play.efdetail.EfColorInf.colorNum;
        Tangram[i].R.Now = play.efdetail.EfColorInf.ColorID[num].color.R;
        Tangram[i].G.Now = play.efdetail.EfColorInf.ColorID[num].color.G;
        Tangram[i].B.Now = play.efdetail.EfColorInf.ColorID[num].color.B;
        Tangram[i].W.Now = play.efdetail.EfColorInf.ColorID[num].color.W;
    }
    /**************************/



    // // // // uint16_t i, j;
    // // // // uint8_t *sur;
    // // // // uint8_t *tar;

    // // // // EF_Work.FrameInfro.KeySum = play.efdetail.EfColorInf.colorNum;                                       // �ؼ�֡��
    // // // // EF_Work.FrameInfro.InsertNum = Motion_Random_framepara;                                          // ��֡��
    // // // // EF_Work.FrameInfro.IntervalTime = 1;                                                             // ֡���ʱ��
    // // // // EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // ��֡��

    // // // // tar = EF_Work.FrameInfro.image_adr; // ɫ����ָ��
    // // // // sur = &EF_Buffer.color_buffer;      // Դɫ��ָ��
    // // // // for (i = 0; i < EF_Work.FrameInfro.KeySum; i++)
    // // // // {
    // // // //     for (j = 0; j < 4; j++) // ����Դ����
    // // // //     {
    // // // //         *tar = *sur;
    // // // //         tar++;
    // // // //         sur++;
    // // // //     }
    // // // // }
    // // // // for (i = 0; i < TangramDevice.Device_sum; i++)
    // // // // {
    // // // //     TangramDevice.SlaveData[i].Runingnum = i; // �����Ч���ַ���
    // // // // }
    // // // // EF_Work.Module_WorkNum = TangramDevice.Device_sum;
}

/*********************************************************************************************************/
void Flow_Static(void) /*����*/
{
    // ���ֳ�ʼ������
}
void Flow_Breath(uint8_t speed) /*����*/
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

void Flow_Stream(uint8_t speed) /*����*/
{
    uint8_t i;
    Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[0].Frame_Now, &Tangram[0].Frame_Now, speed);
    ModuleColor_Cal(&EF_Work.FrameInfro, &Tangram[0], 0);
    for (i = 1; i <= EF_Work.Module_WorkNum; i++)
    {
        Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[i].Frame_Now, &Tangram[i - 1].Frame_Now, 60);
        ModuleColor_Cal(&EF_Work.FrameInfro, &Tangram[i], 0);
    }
}

void Flow_Reverberate(uint8_t speed) /*����*/
{
    uint8_t i;
    Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[0].Frame_Now, &Tangram[0].Frame_Now, speed);
    ModuleColor_Cal(&EF_Work.FrameInfro, &Tangram[0], 0);
    for (i = 1; i <= EF_Work.Module_WorkNum; i++)
    {
        Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[i].Frame_Now, &Tangram[i - 1].Frame_Now, 60);
        ModuleColor_Cal(&EF_Work.FrameInfro, &Tangram[i], 0);
    }
    // printf("%d %d %d \r",EF_Work.FrameInfro.FrameAmount, Tangram[0].Frame_Now,speed);
}

void Flow_Hopscotch(uint8_t speed) /*����*/
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
void Flow_Lightning(uint8_t speed) /*����*/
{
    uint16_t temp;
    uint16_t on_p1, on_p2, off_p1, off_p2;
    uint8_t i;
    uint8_t Currnt_KF;      // ��ǰ�ؼ�֡��keyframe�����
    uint16_t Temp_FrameNum; // ��ʱ֡��ţ�����Ϊ��ǰ֡��frame�����ڵ�ǰ�ؼ�֡��keyframe������һ�ؼ�֡��keyframe����֮���֡���
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

void Flow_Ignite(uint8_t speed) /*��ȼ*/
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
    for (i = 0; i <= EF_Work.Module_WorkNum; i++) // ��ɫ
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
void Flow_Random(uint8_t speed) /*���*/
{
    static uint32_t flow_random_timer = 0;
    uint8_t i;
    uint8_t num;
    flow_random_timer += (speed * 100);
    if (flow_random_timer > 50000)
    {
        flow_random_timer = 0;
        for (i = 0; i < slave.num; i++)
        {
            slave.data[i].runnum = i;
            num = Random_Generate() % play.efdetail.EfColorInf.colorNum;
            Tangram[i].R.Now = play.efdetail.EfColorInf.ColorID[num].color.R;
            Tangram[i].G.Now = play.efdetail.EfColorInf.ColorID[num].color.G;
            Tangram[i].B.Now = play.efdetail.EfColorInf.ColorID[num].color.B;
            Tangram[i].W.Now = play.efdetail.EfColorInf.ColorID[num].color.W;
        }
    }

    /********************************/
    // // // static uint8_t last_KF;
    // // // uint8_t Currnt_KF; // ��ǰ�ؼ�֡��keyframe�����
    // // // uint8_t i;
    // // // uint8_t temp;
    // // // uint8_t random1, random2, random3;
    // // // Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[0].Frame_Now, &Tangram[0].Frame_Now, speed);
    // // // Currnt_KF = Tangram[0].Frame_Now / (EF_Work.FrameInfro.InsertNum + 1); // ���㵱ǰ֡ �Ѿ����� ���/��ǰ �ؼ�֡
    // // // if (Currnt_KF != last_KF)
    // // // {
    // // //     random1 = Random_Generate() % EF_Work.Module_WorkNum; // ��������Ƶ�����
    // // //     for (i = 0; i <= random1; i++)
    // // //     {
    // // //         random2 = Random_Generate() % EF_Work.Module_WorkNum;    // �����������
    // // //         random3 = Random_Generate() % EF_Work.FrameInfro.KeySum; // �������ɫ
    // // //         Tangram[random2].R.Now = *(EF_Work.FrameInfro.image_adr + random3 * 4 + 0);
    // // //         Tangram[random2].G.Now = *(EF_Work.FrameInfro.image_adr + random3 * 4 + 1);
    // // //         Tangram[random2].B.Now = *(EF_Work.FrameInfro.image_adr + random3 * 4 + 2);
    // // //         Tangram[random2].W.Now = *(EF_Work.FrameInfro.image_adr + random3 * 4 + 3);
    // // //     }
    // // // }
    // // // last_KF = Currnt_KF;
}

// // // // /*********************************************************************************************************/
// // // // /*
// // // //  * @Description: ��ʼ����Ч �����ء�
// // // //  * @param:
// // // //  * @return:
// // // // */
// // // // void Flow_Reverberate_Init(void)
// // // // {
// // // //     uint16_t i, j;
// // // //     uint8_t *sur;
// // // //     uint8_t *tar;

// // // //     EF_Work.FrameInfro.KeySum = play.efdetail.EfColorInf.colorNum * 2 - 1;                               // �ؼ�֡��
// // // //     EF_Work.FrameInfro.InsertNum = Motion_Reverberate_framepara;                                     // ��֡��
// // // //     EF_Work.FrameInfro.IntervalTime = 1;                                                             // ֡���ʱ��
// // // //     EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // ��֡��
// // // //     printf("k:%d Is:%d It:%d Am:%d\r\n", EF_Work.FrameInfro.KeySum, EF_Work.FrameInfro.InsertNum, EF_Work.FrameInfro.IntervalTime, EF_Work.FrameInfro.FrameAmount);
// // // //     tar = EF_Work.FrameInfro.image_adr; // ɫ����ָ��
// // // //     sur = &EF_Buffer.color_buffer;      // Դɫ��ָ��
// // // //     for (i = 0; i < play.efdetail.EfColorInf.colorNum; i++)
// // // //     {
// // // //         for (j = 0; j < 4; j++) // ����Դ����
// // // //         {
// // // //             *tar = *sur;
// // // //             tar++;
// // // //             sur++;
// // // //         }
// // // //     }
// // // //     if (play.efdetail.EfColorInf.colorNum > 1)
// // // //     {
// // // //         sur = &EF_Buffer.color_buffer;
// // // //         sur += (play.efdetail.EfColorInf.colorNum - 2) * 4;
// // // //         for (i = 0; i < play.efdetail.EfColorInf.colorNum - 1; i++) // ��䵹���Դ����
// // // //         {
// // // //             for (j = 0; j < 4; j++)
// // // //             {
// // // //                 *tar = *sur;
// // // //                 tar++;
// // // //                 sur++;
// // // //             }
// // // //             sur -= 8;
// // // //         }
// // // //     }
// // // // }


// // // // void Flow_Reverberate(uint8_t speed) /*����*/
// // // // {
// // // //     uint8_t i;
// // // //     Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[0].Frame_Now, &Tangram[0].Frame_Now, speed);
// // // //     ModuleColor_Cal(&EF_Work.FrameInfro, &Tangram[0], 0);
// // // //     for (i = 1; i <= EF_Work.Module_WorkNum; i++)
// // // //     {
// // // //         Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[i].Frame_Now, &Tangram[i - 1].Frame_Now, 60);
// // // //         ModuleColor_Cal(&EF_Work.FrameInfro, &Tangram[i], 0);
// // // //     }
// // // //     // // // printf("%d %d %d \r",EF_Work.FrameInfro.FrameAmount, Tangram[0].Frame_Now,speed);
// // // // }
