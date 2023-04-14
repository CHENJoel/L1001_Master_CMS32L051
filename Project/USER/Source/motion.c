#include "Function_Init.H"
#include "motion.h"

// FrameInfro_TypeDef FrameInfro;
Effect_TypeDef EF_Work;

EFdata_TypeDef EF_WorkData; // 默认参数表
EF_BUFFER_TypeDef EF_Buffer;
/*

enum
{
    MOVE_UP,       // 向上移动
    MOVE_DOWN,     // 向下移动
    MOVE_LEFT,     // 向左移动
    MOVE_RIGHT,    // 向右移动
    MOVE_SEPARATE, // 四周发散
    MOVE_CONVERGE, // 中心汇聚
};



*/

// 提取当前灯效的相关数据

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

// 帧进度复位
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

    EF_Work.FrameInfro.KeySum = EF_Buffer.para_data.color_sum;      // 关键帧数
    EF_Work.FrameInfro.InsertNum = Motion_Static_framepara; // 插帧数
    EF_Work.FrameInfro.IntervalTime = 1;                    // 帧间隔时间
    EF_Work.FrameInfro.FrameAmount = 1;                     // 总帧数
    EF_Work.FrameInfro.Speed = 1;
    // // EF_Work.FrameInfro.addr_table = EF_WorkData.addr_table;
    tar = EF_Work.FrameInfro.image_adr; // 色表缓存指针
    sur = &EF_Buffer.color_buffer;      // 源色表指针
    for (i = 0; i < EF_Work.FrameInfro.KeySum; i++)
    {
        for (j = 0; j < 4; j++) // 复制源数据
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

    EF_Work.FrameInfro.KeySum = EF_Buffer.para_data.color_sum * 2;                            // 关键帧数
    EF_Work.FrameInfro.InsertNum = Motion_Breath_framepara;                                                              // 插帧数
    EF_Work.FrameInfro.IntervalTime = 1;                       // 帧间隔时间
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // 总帧数

    tar = EF_Work.FrameInfro.image_adr;           // 色表缓存指针
    sur = &EF_Buffer.color_buffer; // 源色表指针
    for (i = 0; i < EF_Buffer.para_data.color_sum; i++)
    {
        for (j = 0; j < 4; j++) // 复制源数据
        {
            *tar = *sur;
            tar++;
            sur++;
        }
        for (j = 0; j < 4; j++) // 填充数据
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
    EF_Work.FrameInfro.KeySum = EF_Buffer.para_data.color_sum;                                // 关键帧数
    EF_Work.FrameInfro.InsertNum = Motion_Stream_framepara;                             // 插帧数
    EF_Work.FrameInfro.IntervalTime = 1;                       // 帧间隔时间
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // 总帧数

    tar = EF_Work.FrameInfro.image_adr;                                                              // 色表缓存指针
    sur = &EF_Buffer.color_buffer;                                                    // 源色表指针
    for (i = 0; i < EF_Work.FrameInfro.KeySum; i++)
    {
        for (j = 0; j < 4; j++) // 复制源数据
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
    EF_Work.FrameInfro.KeySum = EF_Buffer.para_data.color_sum * 2 - 1;                        // 关键帧数
    EF_Work.FrameInfro.InsertNum = Motion_Reverberate_framepara;                             // 插帧数
    EF_Work.FrameInfro.IntervalTime = 1;                       // 帧间隔时间
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // 总帧数
                                                                                                     // printf("k:%d Is:%d It:%d Am:%d\r\n",EF_Work.FrameInfro.KeySum,EF_Work.FrameInfro.InsertNum,EF_Work.FrameInfro.IntervalTime,EF_Work.FrameInfro.FrameAmount);

    tar = EF_Work.FrameInfro.image_adr;                                                              // 色表缓存指针
    sur = &EF_Buffer.color_buffer;                                                    // 源色表指针
    for (i = 0; i < EF_Buffer.para_data.color_sum; i++)
    {
        for (j = 0; j < 4; j++) // 复制源数据
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
        for (i = 0; i < EF_Buffer.para_data.color_sum - 1; i++) // 填充倒序的源数据
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

    EF_Work.FrameInfro.KeySum = EF_Buffer.para_data.color_sum;                                // 关键帧数
    EF_Work.FrameInfro.InsertNum = (EF_Work.Module_WorkNum + 1) * Motion_Hopscotch_framepara;        // 插帧数
    EF_Work.FrameInfro.IntervalTime = 1;                                                             // 帧间隔时间(使用插帧数)
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // 总帧数

    // //  printf("k:%d Is:%d It:%d Am:%d\r\n",EF_Work.FrameInfro.KeySum,EF_Work.FrameInfro.InsertNum,EF_Work.FrameInfro.IntervalTime,EF_Work.FrameInfro.FrameAmount);
    tar = EF_Work.FrameInfro.image_adr;                                                              // 色表缓存指针
    sur = &EF_Buffer.color_buffer;                                                    // 源色表指针
    for (i = 0; i < EF_Work.FrameInfro.KeySum; i++)
    {
        for (j = 0; j < 4; j++) // 复制源数据
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

    EF_Work.FrameInfro.KeySum = EF_Buffer.para_data.color_sum;                                // 关键帧数
    EF_Work.FrameInfro.InsertNum = EF_Work.FrameInfro.KeySum * Motion_Lightning_framepara;  // 插帧数*基础插帧
    EF_Work.FrameInfro.IntervalTime = 1;                       // 帧间隔时间
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // 总帧数
    // // // // printf("k:%d Is:%d It:%d Am:%d\r\n",EF_Work.FrameInfro.KeySum,EF_Work.FrameInfro.InsertNum,EF_Work.FrameInfro.IntervalTime,EF_Work.FrameInfro.FrameAmount);

    tar = EF_Work.FrameInfro.image_adr;           // 色表缓存指针
    sur = &EF_Buffer.color_buffer; // 源色表指针
    for (i = 0; i < EF_Work.FrameInfro.KeySum; i++)
    {
        for (j = 0; j < 4; j++) // 复制源数据
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

    EF_Work.FrameInfro.KeySum = EF_Buffer.para_data.color_sum;                                // 关键帧数
    EF_Work.FrameInfro.InsertNum = Motion_Ignite_framepara;                             // 插帧数
    EF_Work.FrameInfro.IntervalTime = 1;                       // 帧间隔时间
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // 总帧数
    // // printf("k:%d Is:%d It:%d Am:%d\r\n",EF_Work.FrameInfro.KeySum,EF_Work.FrameInfro.InsertNum,EF_Work.FrameInfro.IntervalTime,EF_Work.FrameInfro.FrameAmount);

    tar = EF_Work.FrameInfro.image_adr;           // 色表缓存指针
    sur = &EF_Buffer.color_buffer; // 源色表指针
    for (i = 0; i < EF_Work.FrameInfro.KeySum; i++)
    {
        for (j = 0; j < 4; j++) // 复制源数据
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

    EF_Work.FrameInfro.KeySum = EF_Buffer.para_data.color_sum;                                // 关键帧数
    EF_Work.FrameInfro.InsertNum = Motion_Random_framepara;                             // 插帧数
    EF_Work.FrameInfro.IntervalTime = 1;                       // 帧间隔时间
    EF_Work.FrameInfro.FrameAmount = EF_Work.FrameInfro.KeySum * (EF_Work.FrameInfro.InsertNum + 1); // 总帧数


    tar = EF_Work.FrameInfro.image_adr;           // 色表缓存指针
    sur = &EF_Buffer.color_buffer; // 源色表指针
    for (i = 0; i < EF_Work.FrameInfro.KeySum; i++)
    {
        for (j = 0; j < 4; j++) // 复制源数据
        {
            *tar = *sur;
            tar++;
            sur++;
        }
    }
    for (i = 0; i < TangramDevice.Device_sum; i++)
    {
        TangramDevice.SlaveData[i].Runingnum = i; // 随机灯效不分方向
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
    Fetch_EF_DATA();// 提取当前灯效的相关数据
    Frame_Reset();
    // for (i = 0; i < 30; i++)    // 提取默认配置信息
    // {
    // EF_Work.EF_ID = i = 11;
    i=EF_Work.EF_ID;
    printf("EF:%2d\r",EF_Work.EF_ID);


    // EF_Buffer
    // EF_Buffer.para_data



    // // // EF_WorkData.color_array = EF_DefaultData[i].color_array;    // 源色表指针 替换成 &EF_Buffer.color_buffer
    // // // EF_WorkData.color_sum = EF_DefaultData[i].color_sum;    // 色表颜色数量 替换成 EF_Buffer.para_data.color_sum
    // // // EF_WorkData.Speed = EF_DefaultData[i].Speed;
    // // // EF_Work.FrameInfro.Speed = EF_WorkData.Speed;   // 速度 EF_Work.FrameInfro.Speed=EF_Buffer.para_data.speed

    EF_Work.FrameInfro.Speed=EF_Buffer.para_data.speed;  /*保留 EF_Work.FrameInfro.Speed */

    // // // // EF_WorkData.motion_flag = EF_DefaultData[i].motion_flag;    //动效编号  EF_WorkData.motion_flag=EF_Buffer.para_data.motion；
    // // // // EF_Work.MotionType = EF_WorkData.motion_flag; // 灯效类型

    // // // EF_WorkData.Mode = EF_DefaultData[i].Mode;
    // // // EF_Work.FrameInfro.Mode = EF_WorkData.Mode; // 普通/律动    EF_Work.FrameInfro.Mode 替换成 EF_Buffer.para_data.Mode

////    EF_WorkData.addr_table = EF_DefaultData[i].addr_table;



    // // // // EF_Work.MoveType = EF_WorkData.move_flag;     // 运动方向   替换成 EF_Buffer.para_data.move


    EF_Work.FrameInfro.image_adr = (uint8_t *)&EF_Work.Color_buffer; // 色表缓存区



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
            X_num++; // 累计X坐标上的设备数量
        }
        if (temp2 != TangramDevice.SlaveData[i].Coord.Y)
        {
            Y_num++; // 累计Y坐标上的设备数量
        }
        if (TangramDevice.SlaveData[i].Coord.X > X_max)
        {
            X_max = TangramDevice.SlaveData[i].Coord.X; // 求最大X坐标
        }
        if (TangramDevice.SlaveData[i].Coord.Y > Y_max)
        {
            Y_max = TangramDevice.SlaveData[i].Coord.Y; // 求最大Y坐标
        }
        if (TangramDevice.SlaveData[i].Coord.X < X_min)
        {
            X_min = TangramDevice.SlaveData[i].Coord.X; // 求最小X坐标
        }
        if (TangramDevice.SlaveData[i].Coord.Y < Y_min)
        {
            Y_min = TangramDevice.SlaveData[i].Coord.Y; // 求最小Y坐标
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
                    temp2 = 1; // 当前坐标有设备
                    if (EF_Buffer.para_data.move == MOVE_UP)
                    {
                        TangramDevice.SlaveData[i].Runingnum = temp1; // 正序
                    }
                    else
                    {
                        TangramDevice.SlaveData[i].Runingnum = Y_num - temp1 - 1; // 倒序;
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
                    temp2 = 1; // 当前坐标有设备
                    if (EF_Buffer.para_data.move == MOVE_LEFT)
                    {
                        TangramDevice.SlaveData[i].Runingnum = temp1; // 正序
                    }
                    else
                    {
                        TangramDevice.SlaveData[i].Runingnum = X_num - temp1 - 1; // 倒序;
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
                        TangramDevice.SlaveData[i].Runingnum = temp4; // 正序
                    }
                }
                else
                {
                    if (temp2 == j)
                    {
                        temp3 = 1;
                        TangramDevice.SlaveData[i].Runingnum = temp4; // 正序
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
                    temp4 = TangramDevice.SlaveData[i].Runingnum; // 轮询出最大编号
                }
            }
            for (i = 0; i < TangramDevice.Device_sum; i++)
            {
                temp1 = TangramDevice.SlaveData[i].Runingnum;
                TangramDevice.SlaveData[i].Runingnum = temp4 - temp1; // 生成倒序编号
            }
        }
    }

    switch (EF_Buffer.para_data.motion) // 根据灯效类型自动填充数据，生成新的色表缓存
    {
    case MOTION_STATIC: /*静态*/
        Motion_Static_Init();
        break;
    case MOTION_BREATH: /*呼吸*/
        Motion_Breath_Init();
        break;
    case MOTION_STREAM: /*流动*/
        Motion_Stream_Init();
        break;
    case MOTION_REVERB: /*来回*/
        Motion_Reverberate_Init();
        break;
    case MOTION_HOPSCO: /*跳动*/
        Motion_Hopscotch_Init();
        break;
    case MOTION_LIGHTN: /*闪电*/
        Motion_Lightning_Init();
        break;
    case MOTION_IGNITE: /*点燃*/
        Motion_Ignite_Init();
        break;
    case MOTION_RANDOM: /*随机*/
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
    if (Light_Owner == Light_Owner_APP) // APP控灯
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
    else // MCU控灯
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
        case MOTION_STATIC: // 静态
            Motion_Static();
            break;
        case MOTION_BREATH: // 呼吸
            Motion_Breath(speed_Val);
            break;
        case MOTION_STREAM: // 流动
            Motion_Stream(speed_Val);
            break;
        case MOTION_REVERB: // 来回
            Motion_Reverberate(speed_Val);
            break;
        case MOTION_HOPSCO: // 跳动
            Motion_Hopscotch(speed_Val);
            break;
        case MOTION_LIGHTN: // 闪电
            Motion_Lightning(speed_Val);
            break;
        case MOTION_IGNITE: // 点燃
            Motion_Ignite(speed_Val);
            break;
        case MOTION_RANDOM: // 随机
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
void Motion_Static(void) /*呼吸*/
{
    // 保持初始化数据
}

void Motion_Breath(uint8_t speed) /*呼吸*/
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

void Motion_Stream(uint8_t speed)/*流动*/
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

void Motion_Reverberate(uint8_t speed) /*来回*/
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

void Motion_Hopscotch(uint8_t speed) /*跳动*/
{
    uint8_t i;
    uint8_t Currnt_KF;      // 当前关键帧（keyframe）编号
    uint8_t Next_KF;        // 下个关键帧（keyframe）编号
    uint16_t Temp_FrameNum; // 临时帧编号，换算为当前帧（frame）处于当前关键帧（keyframe）至下一关键帧（keyframe）的之间的帧编号
    uint8_t Temp_FrameNum2; // 子临时帧
    Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[0].Frame_Now, &Tangram[0].Frame_Now, speed);
    Currnt_KF = Tangram[0].Frame_Now / (EF_Work.FrameInfro.InsertNum + 1);     // 计算当前帧 已经过的 最近/当前 关键帧
    Temp_FrameNum = Tangram[0].Frame_Now % (EF_Work.FrameInfro.InsertNum + 1); //
    Next_KF = Currnt_KF + 1;                                                   // 计算当前帧 准备经过的 下一关键
    if (Next_KF >= EF_Work.FrameInfro.KeySum)
    {
        Next_KF = 0; // 切回数组的第一个关键帧
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
void Motion_Lightning(uint8_t speed) /*闪电*/
{
    uint16_t temp;
    uint16_t on_p1,on_p2,off_p1,off_p2;
    uint8_t i;
    uint8_t Currnt_KF;                                                    // 当前关键帧（keyframe）编号
    uint16_t Temp_FrameNum;                                                // 临时帧编号，换算为当前帧（frame）处于当前关键帧（keyframe）至下一关键帧（keyframe）的之间的帧编号
    Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[0].Frame_Now, &Tangram[0].Frame_Now, speed);
    Currnt_KF = Tangram[0].Frame_Now / (EF_Work.FrameInfro.InsertNum + 1);     // 计算当前帧 已经过的 最近/当前 关键帧
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

void Motion_Ignite(uint8_t speed) /*点燃*/
{
    uint8_t i;
    uint8_t Currnt_KF;      // 当前关键帧（keyframe）编号
    uint8_t Next_KF;        // 下个关键帧（keyframe）编号
    uint16_t Temp_FrameNum; // 临时帧编号，换算为当前帧（frame）处于当前关键帧（keyframe）至下一关键帧（keyframe）的之间的帧编号
    Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[0].Frame_Now, &Tangram[0].Frame_Now, speed);
    Currnt_KF = Tangram[0].Frame_Now / (EF_Work.FrameInfro.InsertNum + 1);     // 计算当前帧 已经过的 最近/当前 关键帧
    Temp_FrameNum = Tangram[0].Frame_Now % (EF_Work.FrameInfro.InsertNum + 1); //
    Next_KF = Currnt_KF + 1;                                                   // 计算当前帧 准备经过的 下一关键
    if (Next_KF >= EF_Work.FrameInfro.KeySum)
    {
        Next_KF = 0; // 切回数组的第一个关键帧
    }
    for (i = 0; i <= EF_Work.Module_WorkNum; i++)   // 底色
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
void Motion_Random(uint8_t speed) /*随机*/
{
    static uint8_t last_KF;
    uint8_t Currnt_KF;      // 当前关键帧（keyframe）编号
    uint8_t i;
    uint8_t temp;
    uint8_t random1, random2, random3;
    Frame_Skewing(EF_Work.FrameInfro.FrameAmount, &Tangram[0].Frame_Now, &Tangram[0].Frame_Now, speed);
    Currnt_KF = Tangram[0].Frame_Now / (EF_Work.FrameInfro.InsertNum + 1); // 计算当前帧 已经过的 最近/当前 关键帧
    if (Currnt_KF != last_KF)
    {
        random1 = Random_Generate() % EF_Work.Module_WorkNum; // 随机出亮灯的数量
        for (i = 0; i <= random1; i++)
        {
            random2 = Random_Generate() % EF_Work.Module_WorkNum;    // 随机出亮灯组
            random3 = Random_Generate() % EF_Work.FrameInfro.KeySum; // 随机出颜色
            Tangram[random2].R.Now = *(EF_Work.FrameInfro.image_adr + random3 * 4 + 0);
            Tangram[random2].G.Now = *(EF_Work.FrameInfro.image_adr + random3 * 4 + 1);
            Tangram[random2].B.Now = *(EF_Work.FrameInfro.image_adr + random3 * 4 + 2);
            Tangram[random2].W.Now = *(EF_Work.FrameInfro.image_adr + random3 * 4 + 3);
        }
    }
    last_KF = Currnt_KF;
}

// 来回	reverberate
// 跳动	Hopscotch
// 闪电	Lightning
// 点燃	Ignite
// 随机	Random








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
