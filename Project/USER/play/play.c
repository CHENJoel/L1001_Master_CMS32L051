/*
 * @Author: joel
 * .chen sandote@163.om
 * @Date: 2023-06-07 10:12:00
 * @LastEditors: joel
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
.chen sandote@163.om
 * .chen sandote@163.om
 * @LastEditTime: 2023-07-20 15:48:01
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\play\play.c
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#include "play.h"

play_TypeDef play;
// // uint8_t dma_buffer[DMA_BUFFER_SIZE];
const uint8_t bright_table[5] = {15, 25, 55, 75, 100};
// const uint8_t bright_table[5] = {1, 15, 40, 75, 100};

/*播放初始化*/
void play_init(void)
{
    switch_playlist(0); // 切换至默认播放列表
    play.mode = LOOP_MODE;
    memset(&play.detail.history, NULL_EFFECTNUM, sizeof(play.detail.history));
    print_play_history();
}
/*新增历史播放灯效*/
void push_playnum_in_history(uint8_t efnum)
{
    uint8_t buffer[sizeof(play.detail.history)];
    memcpy(&buffer[1], &play.detail.history[0], (sizeof(buffer) - 1));
    buffer[0] = efnum; // 从头部添加新号码
    memcpy(&play.detail.history[0], &buffer[0], sizeof(play.detail.history));
    printlog("push_playnum_in_history:%d\r",efnum);
    print_play_history();
}
/*
 * @Description: 取出历史播放灯效
 * @param:
 * @return:
*/
uint8_t pop_playnum_in_history(void)
{
    uint8_t buffer[sizeof(play.detail.history)];
    uint8_t histoy;
    histoy = play.detail.history[0];
    memcpy(&buffer[0], &play.detail.history[1], (sizeof(buffer) - 1));
    buffer[sizeof(play.detail.history) - 1] = 0xFF; // 从尾部添加无效灯效
    memcpy(&play.detail.history[0], &buffer[0], sizeof(play.detail.history));
    print_play_history();
    return histoy;
}

/*
 * @Description: 暂停播放灯效
 * @param:
 * @return:
*/
void effect_play_pause(void)
{
    play.status = PAUSE;
    printlog("effect_play_pause\r");
}

/*
 * @Description: 继续播放灯效
 * @param:
 * @return:
*/
void effect_play_run(void)
{
    play.status = RUN;
    printlog("effect_play_run\r");
}

/*
 * @Description: 进入app控制模式
 * @param:
 * @return:
*/
void goto_app_control_mode(void)
{
    if (play.control_mode == MCU_CONTROL)
    {
        effect_play_pause();
        turn_off_all_salve_light();

        // // play_color_in_all_salve_light();
        printlog("goto_app_control_mode\r");
    }
    play.control_mode = APP_CONTROL;
}
/*
 * @Description: 进入mcu控制模式
 * @param:
 * @return:
 */
void goto_mcu_control_mode(void)
{
    if (play.control_mode == APP_CONTROL)
    {
        printlog("goto_mcu_control_mode\r");
    }
    play.control_mode = MCU_CONTROL;
    effect_play_run();
}



/*在表中获取下一个元素*/
uint8_t get_list_next_num(uint8_t *list, uint8_t size, uint8_t num)
{
    uint8_t i;
    if (size == 0)
    {
        printlog("[error] wrong number of list size\r");
        return 0;
    }
    for (i = 0; i < size; i++)
    {
        if (list[i] == num)
        {
            if (i < size - 1)
            {
                return list[i + 1];
            }
            else
            {
                return list[0];
            }
        }
    }
}

/*切换灯效*/
uint8_t switch_effect(uint8_t efnum)
{
    // // ef_ranklist_TypeDef eflist;
    uint8_t i;
    printlog("switch effect num:%d\r",efnum);
    if (efnum==255)
    {
        printlog("[error] switch wrong effect num :%d", efnum);
        return 0;
    }
    // // get_allef_ranklist(&eflist);
    // // for (i = 0; i < eflist.num; i++)
    // // {
    // //     if (eflist.list[i] == efnum) // 顺序表内存在被切换的灯效
    // //     {
    // //         j = 1;
    // //         break;
    // //     }
    // // }

    for (i = 0; i < play.detail.num; i++)
    {
        if (play.detail.list[i] == efnum) // 顺序表内存在被切换的灯效
        {
            play_new_effect(efnum);
            push_playnum_in_history(efnum);
            print_playstatus();
            return 1;
        }
    }
    printlog("[error] switch wrong effect num :%d", efnum);
    return 0;
}
/*切换上下灯效*/
uint8_t switch_ln_effect(switchplay_enum num)
{
   playdetail_TypeDef playdetail;
   switch (num)
   {
   case LAST_EFFECT: // 上一个灯效
        switch_last_ef_in_playlist();
        break;
   case NEXT_EFFECT: // 下一个灯效
        switch_next_ef_in_playlist();
        break;
   default:
        printlog("[error] wrong switch effect command %d\r", num);
        printAssert();
        break;
   }
}

/*
 * @Description: 在列表中播放下一灯效
 * @param:
 * @return:
*/
void switch_next_ef_in_playlist(void)
{
   uint8_t num, i, flag;
   if (play.mode == RANDOM_MODE)
   {
       while (1)
       {
            num = Random_Generate();
            flag = 0;
            if (num != play.detail.efnum)
            {
                for (i = 0; i < play.detail.num; i++)
                {
                    if (num != play.detail.list[i])
                    {
                        flag = 1;
                    }
                }
            }
            if (flag)
            {
                break;
            }
       }
       switch_effect(num);
   }
   else /*LOOP_MODE*/
   {
       for (i = 0; i < play.detail.num; i++)
       {
            if (play.detail.list[i] == play.detail.efnum)
            {
                break;
            }
       }
       if (++i >= play.detail.num)
       {
            i = 0;
       }
       switch_effect(play.detail.list[i]);
   }
}

/*
 * @Description: 在列表中播放上一灯效
 * @param:
 * @return:
*/
void switch_last_ef_in_playlist(void)
{
   switch_effect(pop_playnum_in_history());
}

/* 切换播放列表 */
uint8_t switch_playlist(uint8_t listnum)
{
    playlist_ranklist_TypeDef playlist;
    playdetail_TypeDef playdetail;
    uint8_t i;
    uint8_t j = 0;
    printlog("switch playlist num:%d\r",listnum);
    // if (listnum == play.detail.listnum) // 与当前播放表一致
    // {
    //     printlog("[warning]switch same playlist num :%d\r", listnum);
    //     return 0;
    // }
    get_playlist_ranklist(&playlist);
    for (i = 0; i < playlist.num; i++)
    {
        if (playlist.list[i] == listnum) // 顺序表内存在被切换的列表号
        {
            j = 1;
            break;
        }
    }
    if (j)
    {
        play.status = RUN;
        play.detail.listnum = listnum;
        get_playdetail(&playdetail, play.detail.listnum);
        memcpy(&play.detail.list, &playdetail.list, sizeof(play.detail.list));
        play.detail.efnum = play.detail.list[0]; // 列表中第一个灯效
        play.detail.duration.Min = playdetail.DurationTime.Min;
        play.detail.duration.Sec = playdetail.DurationTime.Sec;
        play.detail.num = playdetail.num;
        switch_effect(play.detail.efnum); // 切换灯效

        return 1;
    }
    else
    {
        printlog("[error] switch wrong playlist num :%d\r", listnum);
        return 0;
    }

}

/*------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * @Description: 加载播放灯效信息
 * @param:
 * @return:
*/
void load_play_effect_data(void)
{
    uint8_t i;
    get_effect(&play.efdetail, play.detail.efnum);
    for (i = 0; i < play.efdetail.EfColorInf.colorNum; i++)
    {
        memcpy(&EF_Buffer.color_buffer.color[i],&play.efdetail.EfColorInf.ColorID[i].color, sizeof(RGBWInf_TypeDef));
    }
}

/*
 * @Description: 复位播放帧进度
 * @param:
 * @return:
*/
void play_frame_reset(void)
{
    uint8_t i;
    for (i = 0; i < 32; i++)
    {
        Tangram[i].Frame_Now = 0;
    }
}

/*
 * @Description: 计算出从机的运行编号
 * @param:
 * @return:
*/
void figure_slave_run_number(void)
{
    uint16_t i, j,k;
    uint8_t *sur;
    uint8_t *tar;
    uint16_t temp1, temp2,temp3,temp4;
    uint16_t X_max, X_min, Y_max, Y_min, X_center, Y_center;
    uint16_t X_num,Y_num;

    X_max = 0;
    X_min = -1;
    Y_max = 0;
    Y_min = -1;

    temp1 = temp2 = -1;
    X_num = Y_num = 0;


    for (i = 0; i <slave.num; i++)
    {
        if (temp1 != slave.data[i].cooed_x)
        {
            X_num++; // 累计X坐标上的设备数量
        }
        if (temp2 != slave.data[i].cooed_y)
        {
            Y_num++; // 累计Y坐标上的设备数量
        }
        if (slave.data[i].cooed_x > X_max)
        {
            X_max = slave.data[i].cooed_x; // 求最大X坐标
        }
        if (slave.data[i].cooed_y > Y_max)
        {
            Y_max = slave.data[i].cooed_y; // 求最大Y坐标
        }
        if (slave.data[i].cooed_x < X_min)
        {
            X_min = slave.data[i].cooed_x; // 求最小X坐标
        }
        if (slave.data[i].cooed_y < Y_min)
        {
            Y_min = slave.data[i].cooed_y; // 求最小Y坐标
        }
        temp1 = slave.data[i].cooed_x;
        temp2 = slave.data[i].cooed_y;
    }
    // // printlog("X_num: %d, Y_num: %d\r", X_num, Y_num);
    // // printlog("X_min: %d, Y_min: %d\r", X_min, Y_min);
    if (play.efdetail.Direction == DIRECTION_UP || play.efdetail.Direction == DIRECTION_DOWN)
    {
        EF_Work.Module_WorkNum = Y_num;
        temp1 = 0;
        temp2 = 0;
        for (j = 0; j < 16; j++)
        {
            for (i = 0; i <slave.num; i++)
            {
                if (slave.data[i].cooed_y == j)
                {
                    temp2 = 1; // 当前坐标有设备
                    if (play.efdetail.Direction == DIRECTION_UP)
                    {
                        slave.data[i].runnum = temp1; // 正序
                    }
                    else
                    {
                        slave.data[i].runnum = Y_num - temp1 - 1; // 倒序;
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
    else if (play.efdetail.Direction == DIRECTION_LEFT || play.efdetail.Direction == DIRECTION_RIGHT)
    {
        EF_Work.Module_WorkNum = X_num;
        temp1 = 0;
        temp2 = 0;
        for (j = 0; j < 16; j++)
        {
            for (i = 0; i <slave.num; i++)
            {
                if (slave.data[i].cooed_x == j)
                {
                    temp2 = 1; // 当前坐标有设备
                    if (play.efdetail.Direction == DIRECTION_LEFT)
                    {
                        slave.data[i].runnum = temp1; // 正序
                    }
                    else
                    {
                        slave.data[i].runnum = X_num - temp1 - 1; // 倒序;
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
    else if (play.efdetail.Direction == DIRECTION_SEPARATE || play.efdetail.Direction == DIRECTION_CONVERGE)
    {

        X_center = (X_max + X_min)/2;
        Y_center = (Y_max + Y_min)/2;
        temp4 = 0;
        for (j = 0; j < 16; j++)
        {
            temp3 = 0;
            for (i = 0; i <slave.num; i++)
            {
                temp1 = diff_cal(X_center, slave.data[i].cooed_x);
                temp2 = diff_cal(Y_center, slave.data[i].cooed_y);
                if (temp1 > temp2)
                {
                    if (temp1 == j)
                    {
                        temp3 = 1;
                        slave.data[i].runnum = temp4; // 正序
                    }
                }
                else
                {
                    if (temp2 == j)
                    {
                        temp3 = 1;
                        slave.data[i].runnum = temp4; // 正序
                    }
                }
            }
            if (temp3)
            {
                temp4++;
            }
        }
        temp4 = 0;
        for (i = 0; i < slave.num; i++)
        {
            if (slave.data[i].runnum > temp4)
            {
                temp4 = slave.data[i].runnum; // 轮询出最大编号
            }
        }
        EF_Work.Module_WorkNum = temp4;
        if (play.efdetail.Direction == DIRECTION_CONVERGE)
        {
            for (i = 0; i <slave.num; i++)
            {
                temp1 = slave.data[i].runnum;
                slave.data[i].runnum = temp4 - temp1; // 生成倒序编号
            }
        }
    }
    printlog("Module_WorkNum:%d\r", EF_Work.Module_WorkNum);
}

/*
 * Description: 生成该灯效的动画缓存
 * @param: 无
 * @return: 无
 */
void generate_play_video_buffer(void)
{
    switch (play.efdetail.Flow) // 根据灯效类型自动填充数据，生成新的色表缓存
    {
    case FLOW_STATIC: /*静态*/
        Flow_Static_Init();
        break;
    case FLOW_BREATH: /*呼吸*/
        Flow_Breath_Init();
        break;
    case FLOW_STREAM: /*流动*/
        Flow_Stream_Init();
        break;
    case FLOW_REVERB: /*来回*/
        Flow_Reverberate_Init();
        break;
    case FLOW_HOPSCO: /*跳动*/
        Flow_Hopscotch_Init();
        break;
    case FLOW_LIGHTN: /*闪电*/
        Flow_Lightning_Init();
        break;
    case FLOW_IGNITE: /*点燃*/
        Flow_Ignite_Init();
        break;
    case FLOW_RANDOM: /*随机*/
        Flow_Random_Init();
        break;
    default:
        break;
    }
}
/*
 * @Description: 播放灯效
 * @param:
 * @return:
 */
void play_effect_video(void)
{
    if (play.control_mode == MCU_CONTROL)
    {
        if (play.work.sw_status == SW_ON)
        {
            if (play.status == RUN)
            {
                effect_play_color_calu();
            }
            else
            {
            }
            // // // transmit_slave_play_data();
        }
        else
        {
            // // // turn_off_all_salve_light();
        }
#if !defined(printlog_enabled)
        transmit_slave_play_data();
#endif
    }
    else
    {

    }
}

/*
 * @Description: 播放灯效初始化
 * @param:
 * @return:
 */
void play_effect_init(void)
{
    play.detail.efnum = 17; // df_Snake
    load_play_effect_data();
    // // generate_virtual_device();
    // // play.efdetail.Direction=DIRECTION_CONVERGE;
    play_frame_reset();
    EF_Work.FrameInfro.image_adr = (uint8_t *)&EF_Work.Color_buffer; // 色表缓存区
    figure_slave_run_number();
    generate_play_video_buffer();
}


/*
 * @Description: 播放新灯效
 * @param:
 * @return:
*/
void play_new_effect(uint8_t efnum)
{
    printlog("play_new_effect:%d\r",efnum);
    if (play.detail.efnum == efnum)
    {
        return;
    }
    play.detail.efnum = efnum;
    load_play_effect_data();
    play_frame_reset();
    EF_Work.FrameInfro.image_adr = (uint8_t *)&EF_Work.Color_buffer; // 色表缓存区
    figure_slave_run_number();
    generate_play_video_buffer();
}

/*
 * @Description: 发送从机播放数据
 * @param:
 * @return:
*/
void transmit_slave_play_data(void)
{
    uint8_t i;
    uint16_t size;
    uint8_t buffer[DMA_BUFFER_SIZE];
    if (slave.num) // 有设备在线的时候才发送数据
    {
        ((playpack_Typedef *)(&buffer))->head.type = PLAY_DATA;
        ((playpack_Typedef *)(&buffer))->head.num = slave.num;
        size = sizeof(packhead_Typedef) + slave.num * sizeof(playdata_Typedef);
        for (i = 0; i < slave.num; i++)
        {
            ((playpack_Typedef *)(&buffer))->play[i].addr = slave.data[i].id;
            ((playpack_Typedef *)(&buffer))->play[i].bri = play.work.brightness.now;
            ((playpack_Typedef *)(&buffer))->play[i].R = Tangram[slave.data[i].runnum].R.Now;
            ((playpack_Typedef *)(&buffer))->play[i].G = Tangram[slave.data[i].runnum].G.Now;
            ((playpack_Typedef *)(&buffer))->play[i].B = Tangram[slave.data[i].runnum].B.Now;
            ((playpack_Typedef *)(&buffer))->play[i].W = Tangram[slave.data[i].runnum].W.Now;
        }
        transmit_protocol_frame(&buffer, size, &parse.tx_framebuf); // 通过不定长协议发送
    }
    /**************************/
    // // // uint8_t i;
    // // // uint8_t *p;
    // // // if (slave.num) // 有设备在线的时候才发送数据
    // // // {
    // // //     for (i = 0; i < slave.num; i++)
    // // //     {
    // // //         p = &dma_buffer[i * sizeof(complay_Typedef)];
    // // //         ((complay_Typedef *)p)->head = MPLAY_HEADER;
    // // //         ((complay_Typedef *)p)->addr = slave.data[i].id;
    // // //         ((complay_Typedef *)p)->bri = 255;
    // // //         ((complay_Typedef *)p)->R = Tangram[slave.data[i].runnum].R.Now;
    // // //         ((complay_Typedef *)p)->G = Tangram[slave.data[i].runnum].G.Now;
    // // //         ((complay_Typedef *)p)->B = Tangram[slave.data[i].runnum].B.Now;
    // // //         ((complay_Typedef *)p)->W = Tangram[slave.data[i].runnum].W.Now;
    // // //         ((complay_Typedef *)p)->sum = checksum_calculate(p, sizeof(complay_Typedef) - 1);
    // // //     }
    // // //     DMA_Start(DMA_VECTOR_ST0, CTRL_DATA_ST0, DMA_MODE_NORMAL, DMA_SIZE_BYTE, slave.num * sizeof(complay_Typedef), dma_buffer, (void *)&SCI0->TXD0);
    // // //     DMA_Enable(DMA_VECTOR_ST0);
    // // //     DMA_Trigger(DMA_VECTOR_ST0);
    // // // }
}

/*
 * @Description: 所有灯点亮同个颜色
 * @param: 亮度
 * @param: 红
 * @param: 绿
 * @param: 蓝
 * @param: 白
 * @return: 无
*/
void play_color_in_all_salve_light(uint8_t bri, uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
    uint16_t size;
    uint8_t buffer[sizeof(packhead_Typedef) + sizeof(playdata_Typedef)];
    ((playpack_Typedef *)(&buffer))->head.type = PLAY_DATA;
    ((playpack_Typedef *)(&buffer))->head.num = 1;
    ((playpack_Typedef *)(&buffer))->play[0].addr = Public_Addr;
    ((playpack_Typedef *)(&buffer))->play[0].bri = bri;
    ((playpack_Typedef *)(&buffer))->play[0].R = r;
    ((playpack_Typedef *)(&buffer))->play[0].G = g;
    ((playpack_Typedef *)(&buffer))->play[0].B = b;
    ((playpack_Typedef *)(&buffer))->play[0].W = w;
    transmit_protocol_frame(&buffer, sizeof(buffer), &parse.tx_framebuf); // 通过不定长协议发送

    /**********************/
    // // ((complay_Typedef *)(&dma_buffer))->head = MPLAY_HEADER;
    // // ((complay_Typedef *)(&dma_buffer))->addr = Public_Addr;
    // // ((complay_Typedef *)(&dma_buffer))->bri = bri;
    // // ((complay_Typedef *)(&dma_buffer))->R = r;
    // // ((complay_Typedef *)(&dma_buffer))->G = g;
    // // ((complay_Typedef *)(&dma_buffer))->B = b;
    // // ((complay_Typedef *)(&dma_buffer))->W = w;
    // // ((complay_Typedef *)(&dma_buffer))->sum = checksum_calculate(&dma_buffer, sizeof(complay_Typedef) - 1);

    // // DMA_Start(DMA_VECTOR_ST0, CTRL_DATA_ST0, DMA_MODE_NORMAL, DMA_SIZE_BYTE, sizeof(complay_Typedef), dma_buffer, (void *)&SCI0->TXD0);
    // // DMA_Enable(DMA_VECTOR_ST0);
    // // DMA_Trigger(DMA_VECTOR_ST0);
}

void set_color_data_of_all_light()
{

}

/*
 * @Description: 关闭所有灯板
 * @param: 无
 * @return: 无
*/
void turn_off_all_salve_light(void)
{
    play_color_in_all_salve_light(0,0,0,0,0);
}

/*
 * @Description: 发送特定长度的数据
 * @param: 源数据指针
 * @param: 要发送的长度
 * @return: 无
 */
void transmit_buffer_data(uint8_t *sur, uint16_t len)
{
    if ((((void *)0) == sur) || (0 == len))
    {
        return;
    }
    DMA_Stop(DMA_VECTOR_ST0);
    DMA_Start(DMA_VECTOR_ST0, CTRL_DATA_ST0, DMA_MODE_NORMAL, DMA_SIZE_BYTE, len, sur, (void *)&SCI0->TXD0);
    DMA_Enable(DMA_VECTOR_ST0);
    DMA_Trigger(DMA_VECTOR_ST0);
}
