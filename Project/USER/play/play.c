
#include "play.h"

play_TypeDef play;
// // uint8_t dma_buffer[DMA_BUFFER_SIZE];
const uint8_t bright_table[5] = {5, 25, 55, 75, 100};
// const uint8_t bright_table[5] = {1, 15, 40, 75, 100};

/*
 * @Description: 修改播放源
 * @param:
 * @return:
 */
void modify_playsource(playsource_enum source)
{
    if (play.source == source) // 播放源发生改变时，代表“播放列表详情”也改变
    {
        play.source = source;
        mcu_update_current_playdetail(); // 上报当前正在播放的“播放列表详情”
    }
    else
    {
        play.source = source;
    }
}

/*播放初始化*/
void play_init(void)
{
    switch_playlist(0); // 切换至默认播放列表
    modify_playsource(SOURCE_LIST);
    play.playmode = PLAY_IN_SEQUENCE;
    memset(&play.detail.history, NULL_EFFECTNUM, sizeof(play.detail.history));
    // print_play_history();
}
/*新增历史播放灯效*/
void push_playnum_in_history(uint8_t efnum)
{
    uint8_t buffer[sizeof(play.detail.history)];
    memcpy(&buffer[1], &play.detail.history[0], (sizeof(buffer) - 1));
    buffer[0] = efnum; // 从头部添加新号码
    memcpy(&play.detail.history[0], &buffer[0], sizeof(play.detail.history));
    printlog("push_playnum_in_history:%d\r",efnum);
    // print_play_history();
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
    // print_play_history();
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
void resume_play_effect(void)
{
    play.status = RUN;
    printlog("resume_play_effect\r");
}

/*
 * @Description: 进入灯板配对模式
 * @param:
 * @return:
*/
void enter_device_pairing_mode(void)
{
    if (play.control_mode != PAIRING_MODE)
    {
        effect_play_pause();
        // // // turn_off_all_salve_light();

        // // play_color_in_all_salve_light();
        printlog("enter_device_pairing_mode\r");
    }
    play.control_mode = PAIRING_MODE;
}
/*
 * @Description: 进入正常播放灯效模式
 * @param:
 * @return:
 */
void enter_playing_effect_mode(void)
{
    if (play.control_mode != PLAYING_MODE)
    {
        printlog("enter_playing_effect_mode\r");
    }
    play.control_mode = PLAYING_MODE;
    resume_play_effect();
}

/* 
 * @Description: 进入预览灯效模式
 * @param: 
 * @return: 
*/ 
void enter_preview_effect_mode(Efdetail_TypeDef* efdetail)
{
    printlog("enter_preview_effect_mode\r");
    play.control_mode = PREVIEW_MODE;
    play_preview_effect(efdetail);
}


/* 
 * @Description: 退出预览灯效模式
 * @param: 
 * @return: 
*/ 
void exit_preview_effect_mode(void)
{
    if (play.control_mode != PLAYING_MODE)
    {
        printlog("exit_preview_effect_mode\r");
    }
    play.control_mode = PLAYING_MODE;
    play_current_effect();
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
    uint8_t i;
    printlog("switch effect num:%d\r",efnum);
    if (efnum==255)
    {
        printlog("[error] switch wrong effect num :%d\r", efnum);
        return 0;
    }
    for (i = 0; i < play.detail.listefsum; i++)
    {
        if (play.detail.list[i] == efnum) // 顺序表内存在被切换的灯效
        {
            play_new_effect(efnum);
            // print_playstatus();
            return 1;
        }
    }
    printlog("[error] switch wrong effect num :%d\r", efnum);
    return 0;
}
/*切换上下灯效*/
uint8_t switch_lastnext_effect(switchplay_enum num)
{
    playdetail_TypeDef playdetail;
    switch (num)
    {
    case LAST_EFFECT: // 上一个灯效
        printlog("play last effect\r");
        switch_last_ef_in_list();
        break;
    case NEXT_EFFECT: // 下一个灯效
        printlog("play next effect\r");
        switch_next_ef_in_list();
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
void switch_next_ef_in_list(void)
{
    // // // uint8_t cur_efindex;// 当前灯效
    // // // cur_efindex = play.detail.idex_inlist;
    if (play.source == SOURCE_LIST)
    {

        if (++play.detail.idex_inlist >= play.detail.listefsum) // 已经到最后一个灯效
        {
            if (play.cyclemode == CYCLE_IN_LOOP) // 循环播放
            {
                play.detail.idex_inlist = 0;
                start_play_list(play.detail.listindex); // 重新播放该列表
            }
            else /* CYCLE_IN_ONCE 单次列表 */
            {
                play.detail.idex_inlist = play.detail.listefsum - 1; // 停在最后一个灯效
            }
        }
        else
        {
            play.detail.efindex = play.detail.list[play.detail.idex_inlist]; // 取出灯效索引
            switch_effect(play.detail.efindex);                              // 切换灯效
        }
    }
    else
    {
        printlog("switch effect failed,not in SOURCE_LIST\r");
    }
    // // //    uint8_t num, i, flag;
    // // //    if (play.playmode == PLAY_IN_RANDOM)
    // // //    {
    // // //        while (1)
    // // //        {
    // // //             num =get_random_number();
    // // //             flag = 0;
    // // //             if (num != play.detail.efindex)
    // // //             {
    // // //                 for (i = 0; i < play.detail.listefsum; i++)
    // // //                 {
    // // //                     if (num != play.detail.list[i])
    // // //                     {
    // // //                         flag = 1;
    // // //                     }
    // // //                 }
    // // //             }
    // // //             if (flag)
    // // //             {
    // // //                 break;
    // // //             }
    // // //        }
    // // //        switch_effect(num);
    // // //    }
    // // //    else /*PLAY_IN_SEQUENCE*/
    // // //    {
    // // //        for (i = 0; i < play.detail.listefsum; i++)
    // // //        {
    // // //             if (play.detail.list[i] == play.detail.efindex)
    // // //             {
    // // //                 break;
    // // //             }
    // // //        }
    // // //        if (++i >= play.detail.listefsum)
    // // //        {
    // // //             i = 0;
    // // //        }
    // // //        switch_effect(play.detail.list[i]);
    // // //    }
}

/*
 * @Description: 在列表中播放上一灯效
 * @param:
 * @return:
 */
void switch_last_ef_in_list(void)
{
    // // //    switch_effect(pop_playnum_in_history());
    if (play.source == SOURCE_LIST)
    {
        if (play.detail.idex_inlist > 0)
        {
            play.detail.idex_inlist--;
        }
        play.detail.efindex = play.detail.list[play.detail.idex_inlist]; // 取出灯效索引
        switch_effect(play.detail.efindex);                              // 切换灯效
    }
    else
    {
        printlog("switch effect failed,not in SOURCE_LIST\r");
    }
}

/* 切换播放列表 */
uint8_t switch_playlist(uint8_t listnum)
{
    playlist_ranklist_TypeDef playlist;
    uint8_t i;
    printlog("switch playlist num:%d\r",listnum);
    get_playlist_ranklist(&playlist);
    for (i = 0; i < playlist.num; i++)
    {
        if (playlist.list[i] == listnum) // 顺序表内存在被切换的列表号
        {
            start_play_list(listnum);
            mcu_update_current_playdetail(); // 上报当前正在播放的“播放列表详情”
            mcu_update_playstatus();         // 自动上报播放状态
            return 1;
        }
    }
    printlog("[error] switch wrong playlist num :%d\r", listnum);
    return 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------*/
/*
 * @Description: 切换播放模式
 * @param:
 * @return:
 */
void switch_playmode(PlayMode_enum mod)
{
    /*
        PLAY_IN_RANDOM,   // 随机播放
        PLAY_IN_SEQUENCE, // 顺序播放
        */
    playdetail_TypeDef playdetail;
    if (mod == PLAY_IN_RANDOM)
    {
       play.playmode = PLAY_IN_RANDOM;
    }
    else
    {
       play.playmode = PLAY_IN_SEQUENCE;
    }
    get_playdetail(&playdetail, play.detail.listindex);
    memcpy(&play.detail.list, &playdetail.list, sizeof(play.detail.list));
    if (play.playmode == PLAY_IN_RANDOM)
    {
       permute_list_in_random(&play.detail.list, play.detail.listefsum); // 生成随机播放
    }
    adjust_play_list();
    // // print_playstatus();
}

/*
 * @Description: 切换循环模式
 * @param:
 * @return:
 */
void switch_cyclemode(CycleMode_enum mod)
{
    /*
      CYCLE_IN_LOOP, // 循环播放
      CYCLE_IN_ONCE, // 单次列表
    */
    if (mod == CYCLE_IN_LOOP)
    {
       play.cyclemode = CYCLE_IN_LOOP;
    }
    else
    {
       play.cyclemode = CYCLE_IN_ONCE;
    }
}

/*
 * @Description: 加载本地灯效信息
 * @param:
 * @return:
*/
void load_local_effect_data(void)
{
    uint8_t i;
    get_effect_detail(&play.efdetail, play.detail.efindex);
    for (i = 0; i < play.efdetail.EfColorInf.colorNum; i++)
    {
        memcpy(&EF_Buffer.color_buffer.color[i],&play.efdetail.EfColorInf.ColorID[i].color, sizeof(RGBWInf_TypeDef));
    }
}

/* 
 * @Description: 加载预览灯效信息
 * @param: 
 * @return: 
*/
void load_preview_effect_data(Efdetail_TypeDef *efdetail)
{
    uint8_t i;
    memcpy(&play.efdetail, efdetail, sizeof(Efdetail_TypeDef));
    for (i = 0; i < play.efdetail.EfColorInf.colorNum; i++)
    {
        memcpy(&EF_Buffer.color_buffer.color[i], &play.efdetail.EfColorInf.ColorID[i].color, sizeof(RGBWInf_TypeDef));
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

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // /*
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //  * @Description: 根据方向计算出从机的运行编号
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //  * @param:
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //  * @return:
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // */
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // void figure_slave_run_number_in_direction(Direction_Enum dir)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     uint16_t i, j,k;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     uint8_t *sur;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     uint8_t *tar;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     uint16_t temp1, temp2,temp3,temp4;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     uint16_t X_max, X_min, Y_max, Y_min, X_center, Y_center;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     uint16_t X_num,Y_num;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     uint16_t last_coord;    // 上一个坐标
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     X_max = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     X_min = -1;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     Y_max = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     Y_min = -1;

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     temp1 = temp2 = -1;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     X_num = Y_num = 0;

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     print_direction(dir);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     for (i = 0; i <slave.num; i++)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         if (temp1 != slave.data[i].cooed_x)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             X_num++; // 累计X坐标上的设备数量
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         if (temp2 != slave.data[i].cooed_y)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             Y_num++; // 累计Y坐标上的设备数量
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         if (slave.data[i].cooed_x > X_max)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             X_max = slave.data[i].cooed_x; // 求最大X坐标
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         if (slave.data[i].cooed_y > Y_max)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             Y_max = slave.data[i].cooed_y; // 求最大Y坐标
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         if (slave.data[i].cooed_x < X_min)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             X_min = slave.data[i].cooed_x; // 求最小X坐标
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         if (slave.data[i].cooed_y < Y_min)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             Y_min = slave.data[i].cooed_y; // 求最小Y坐标
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         temp1 = slave.data[i].cooed_x;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         temp2 = slave.data[i].cooed_y;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     printlog("X_num: %d, Y_num: %d\r", X_num, Y_num);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     printlog("X_min: %d, Y_min: %d\r", X_min, Y_min);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     if (dir == DIRECTION_UP || dir == DIRECTION_DOWN)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         EF_Work.Module_WorkNum = Y_num;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         temp1 = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         temp2 = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         for (j = 0; j < 16; j++)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             for (i = 0; i <slave.num; i++)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 if (slave.data[i].cooed_y == j)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     temp2 = 1; // 当前坐标有设备
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     if (dir == DIRECTION_UP)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                         slave.data[i].runnum = temp1; // 正序
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     else
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                         slave.data[i].runnum = Y_num - temp1 - 1; // 倒序;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             if (temp2)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 temp1++;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 temp2 = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     else if (dir == DIRECTION_LEFT || dir == DIRECTION_RIGHT)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         EF_Work.Module_WorkNum = X_num;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         temp1 = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         temp2 = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         for (j = 0; j < 16; j++)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             for (i = 0; i <slave.num; i++)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 if (slave.data[i].cooed_x == j)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     temp2 = 1; // 当前坐标有设备
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     if (dir == DIRECTION_LEFT)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                         slave.data[i].runnum = temp1; // 正序
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     else
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                         slave.data[i].runnum = X_num - temp1 - 1; // 倒序;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             if (temp2)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 temp1++;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 temp2 = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     else if (dir == DIRECTION_SEPARATE || dir == DIRECTION_CONVERGE)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     {

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         X_center = (X_max + X_min)/2;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         Y_center = (Y_max + Y_min)/2;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         temp4 = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         for (j = 0; j < 16; j++)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             temp3 = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             for (i = 0; i <slave.num; i++)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 temp1 = diff_cal(X_center, slave.data[i].cooed_x);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 temp2 = diff_cal(Y_center, slave.data[i].cooed_y);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 if (temp1 > temp2)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     if (temp1 == j)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                         temp3 = 1;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                         slave.data[i].runnum = temp4; // 正序
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 else
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     if (temp2 == j)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                         temp3 = 1;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                         slave.data[i].runnum = temp4; // 正序
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                     }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             if (temp3)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 temp4++;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         temp4 = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         for (i = 0; i < slave.num; i++)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             if (slave.data[i].runnum > temp4)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 temp4 = slave.data[i].runnum; // 轮询出最大编号
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         EF_Work.Module_WorkNum = temp4;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         if (dir == DIRECTION_CONVERGE)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             for (i = 0; i <slave.num; i++)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             {
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 temp1 = slave.data[i].runnum;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //                 slave.data[i].runnum = temp4 - temp1; // 生成倒序编号
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //             }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //         }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     }
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //     printlog("Module_WorkNum:%d\r", EF_Work.Module_WorkNum);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // }



/* 
 * @Description: 冒泡排序坐标
 * @param: 坐标数组指针
 * @param: 数组长度
 * @param: 排序根据（横坐标/纵坐标）
 * @return: 
*/ 
void bubble_sort_location(mini_device_detail_TypeDef *sur,uint8_t len,Coord_ENUM coor)
{
    uint8_t i,j;
    mini_device_detail_TypeDef device;
    for (i = 0; i < len; i++)
    {
        for (j = i + 1; j < len; j++)
        {
            if (coor == ABSCISSA) // 横坐标
            {
                if (sur[i].cooed_x > sur[j].cooed_x)
                {
                    /* 交换位置 */
                    memcpy(&device, &sur[i], sizeof(device));
                    memcpy(&sur[i], &sur[j], sizeof(device));
                    memcpy(&sur[j], &device, sizeof(device));
                }
            }
            else if (coor == ORDINATE) // 纵坐标
            {
                if (sur[i].cooed_y > sur[j].cooed_y)
                {
                    /* 交换位置 */
                    memcpy(&device, &sur[i], sizeof(device));
                    memcpy(&sur[i], &sur[j], sizeof(device));
                    memcpy(&sur[j], &device, sizeof(device));
                }
            }
            else
            {
                if ((sur[i].cooed_x > sur[j].cooed_x) || (sur[i].cooed_y > sur[j].cooed_y))
                {
                    /* 交换位置 */
                    memcpy(&device, &sur[i], sizeof(device));
                    memcpy(&sur[i], &sur[j], sizeof(device));
                    memcpy(&sur[j], &device, sizeof(device));
                }
            }
        }
    }
}

/*
 * @Description: 根据方向计算出从机的运行编号
 * @param:
 * @return:
*/
void figure_slave_run_number_in_direction(Direction_Enum dir)
{
    mini_device_data_TypeDef minidevice;
    uint8_t center;
    uint8_t i, j;
    for (i = 0; i < slave.num; i++)
    {
        minidevice.num = slave.num;
        minidevice.data[i].id = slave.data[i].id;
        minidevice.data[i].cooed_x = slave.data[i].cooed_x;
        minidevice.data[i].cooed_y = slave.data[i].cooed_y;
    }
    
    if (dir == DIRECTION_UP || dir == DIRECTION_DOWN)// 向上移动/向下移动
    {
        EF_Work.Module_WorkNum = minidevice.num;
        bubble_sort_location(&minidevice.data, minidevice.num, ORDINATE); // 根据纵坐标排序    
        for (i = 0; i < minidevice.num; i++)
        {
            if (dir == DIRECTION_UP)
            {
                minidevice.data[i].runnum = i; // 正序
            }
            else
            {
                minidevice.data[i].runnum = minidevice.num - i - 1; // 倒序;
            }
        }
    }
    else if (dir == DIRECTION_LEFT || dir == DIRECTION_RIGHT)   // 向左移动/向右移动
    {
        EF_Work.Module_WorkNum = minidevice.num;
        bubble_sort_location(&minidevice.data, minidevice.num, ABSCISSA); // 根据横坐标排序
        for (i = 0; i < minidevice.num; i++)
        {
            if (dir == DIRECTION_LEFT)
            {
                minidevice.data[i].runnum = i; // 正序
            }
            else
            {
                minidevice.data[i].runnum = minidevice.num - i - 1; // 倒序;
            }
        }
    }
    else if (dir == DIRECTION_SEPARATE || dir == DIRECTION_CONVERGE) // 中心汇聚/四周发散
    {
        EF_Work.Module_WorkNum = (minidevice.num + 1) / 2;
        bubble_sort_location(&minidevice.data, minidevice.num, XandY); // 根据横纵坐标排序
        center = minidevice.num / 2;
        for (i = 0; i < minidevice.num; i++)
        {
            if (i < center)
            {
                minidevice.data[i].runnum = center - i; // 正序
            }
            else
            {
                minidevice.data[i].runnum = i - center;
            }
        }
        if (dir == DIRECTION_CONVERGE)
        {
            for (i = 0; i < minidevice.num; i++) // 倒序;
            {
                minidevice.data[i].runnum = center - minidevice.data[i].runnum;
            }
        }
    }
    /* 将计算出来的运行编号拷贝至灯板信息中 */
    for (i = 0; i < slave.num; i++)
    {
        for (j = 0; j < minidevice.num; j++)
        {
            if (slave.data[i].id == minidevice.data[j].id)
            {
                slave.data[i].runnum = minidevice.data[j].runnum;
                break;
            }
        }
    }
    print_direction(dir);
    printlog("Module_WorkNum:%d\r", EF_Work.Module_WorkNum);
    // print_mini_device_data(&minidevice);
}




/*
 * Description: 生成该灯效的动画缓存
 * @param: 无
 * @return: 无
 */
void generate_play_video_buffer(void)
{
    if (play.efdetail.EffectType == STATIC_TYPE)
    {
        play.efdetail.Flow = FLOW_STATIC; // 静态灯效，对应静态效果
    }

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
#ifndef printlog_enabled
    if (play.control_mode == PLAYING_MODE) // 正常播放模式
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
            transmit_playdata_COLOR();
       
        }
        else
        {
            turn_off_all_salve_light();
        }
    }
    else if (play.control_mode == PREVIEW_MODE) // 灯效预览模式
    {
        effect_play_color_calu();
        transmit_playdata_COLOR();
    }
    else /*PAIRING_MODE 灯板配对模式 */
    {
        // // transmit_playdata_RGBbr();
    }
#endif
}

/*
 * @Description: 系统播放灯效初始化
 * @param:
 * @return:
 */
void play_sys_effect_init(void)
{
    // // play.detail.efindex = 17; // df_Snake
    // // play_current_effect();   
    switch_effect(23);   // "Colorful"
}

/* 
 * @Description: 从头开始播放当前灯效
 * @param: 
 * @return: 
*/ 
void play_current_effect(void)
{
    play.control_mode = PLAYING_MODE;
    load_local_effect_data();     // 加载灯效信息
    preprocess_play_effect();     // 预处理播放数据
    load_current_ef_brightness(); // 加载亮度
}


/* 
 * @Description: 播放自由灯效
 * @param: 
 * @return: 
*/ 
void play_free_effect(uint8_t efnum)
{
    play_new_effect(efnum);
    modify_playsource(SOURCE_FREE);
}

/*
 * @Description: 播放新灯效
 * @param:
 * @return:
*/
void play_new_effect(uint8_t efnum)
{
    printlog("play_new_effect:%d\r",efnum);
    play.detail.efindex = efnum;
    play.work.playtime_cnt = 0;
    play_current_effect();
    mcu_update_playstatus();            // mcu上报播放状态
    mcu_update_current_ef_detail();     // 上报当前播放的灯效信息
    mcu_update_current_ef_brightness(); // 上传播放的灯效的亮度信息
}

/* 
 * @Description: 预处理播放数据
 * @return: 
*/ 
void preprocess_play_effect(void)
{
    // // play.work.global_setting.brightness_set = play.efdetail.Brightness1;
    play_frame_reset();
    EF_Work.FrameInfro.image_adr = (uint8_t *)&EF_Work.Color_buffer; // 色表缓存区
    figure_slave_run_number_in_direction(play.efdetail.Direction);
    generate_play_video_buffer();   // 生成该灯效的动画缓存
}

/*
 * @Description: 播放预览灯效
 * @param:
 * @return:
*/

void play_preview_effect(Efdetail_TypeDef* efdetail)
{
    printlog("play_preview_effect\r");
    load_preview_effect_data(efdetail);
    preprocess_play_effect();
    if (play.efdetail.EffectType != RHYTHM_TYPE)
    {
        play.work.brightness.set = play.efdetail.Brightness1;
    }
}

// // // // /*
// // // //  * @Description: 发送从机播放数据
// // // //  * @param:
// // // //  * @return:
// // // // */
// // // // void transmit_slave_play_data(void)
// // // // {
// // // //     uint8_t i;
// // // //     uint16_t size;
// // // //     uint8_t buffer[DMA_BUFFER_SIZE];
// // // //     calibration_TypeDef calib_t;
// // // //     if (slave.num) // 有设备在线的时候才发送数据
// // // //     {
// // // //         ((playpack_Typedef *)(&buffer))->head.type = PLAY_DATA;
// // // //         ((playpack_Typedef *)(&buffer))->head.num = slave.num;
// // // //         size = sizeof(packhead_Typedef) + slave.num * sizeof(playdata_Typedef);
// // // //         for (i = 0; i < slave.num; i++)
// // // //         {
// // // //             ((playpack_Typedef *)(&buffer))->play[i].addr = slave.data[i].id;

// // // //             calib_t.shape = slave.data[i].shape;
// // // //             calib_t.color.brightness = play.work.brightness.now;
// // // //             calib_t.color.R = Tangram[slave.data[i].runnum].R.Now;
// // // //             calib_t.color.G = Tangram[slave.data[i].runnum].G.Now;
// // // //             calib_t.color.B = Tangram[slave.data[i].runnum].B.Now;
// // // //             calib_t.color.W = Tangram[slave.data[i].runnum].W.Now;
// // // //             if (calibration_enable)
// // // //             {
// // // //                 calibration_color(&calib_t);
// // // //             }


// // // //             ((playpack_Typedef *)(&buffer))->play[i].bri = calib_t.color.brightness;
// // // //             ((playpack_Typedef *)(&buffer))->play[i].R = calib_t.color.R;
// // // //             ((playpack_Typedef *)(&buffer))->play[i].G = calib_t.color.G;
// // // //             ((playpack_Typedef *)(&buffer))->play[i].B = calib_t.color.B;
// // // //             ((playpack_Typedef *)(&buffer))->play[i].W = calib_t.color.W;

// // // //             // ((playpack_Typedef *)(&buffer))->play[i].bri = play.work.brightness.now;
// // // //             // ((playpack_Typedef *)(&buffer))->play[i].R = Tangram[slave.data[i].runnum].R.Now;
// // // //             // ((playpack_Typedef *)(&buffer))->play[i].G = Tangram[slave.data[i].runnum].G.Now;
// // // //             // ((playpack_Typedef *)(&buffer))->play[i].B = Tangram[slave.data[i].runnum].B.Now;
// // // //             // ((playpack_Typedef *)(&buffer))->play[i].W = Tangram[slave.data[i].runnum].W.Now;
// // // //         }
// // // //         transmit_protocol_frame(&buffer, size, &parse.tx_framebuf); // 通过不定长协议发送
// // // //     }
// // // // }

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
    L0_playRGBbr_Typedef x;
    x.R = 0;
    x.G = 0;
    x.B = 0;
    x.br = 0;
    transmit_playsame_RGBbr(&x);
    // // // play_color_in_all_salve_light(0,0,0,0,0);

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
    // // DMA_Stop(DMA_VECTOR_ST0);
    DMA_Start(DMA_VECTOR_ST0, CTRL_DATA_ST0, DMA_MODE_NORMAL, DMA_SIZE_BYTE, len, sur, (void *)&SCI0->TXD0);
    DMA_Enable(DMA_VECTOR_ST0);
    DMA_Trigger(DMA_VECTOR_ST0);
}

/********************************************************************************************************************/

/*
 * @Description: 发送“RGBbr”格式的播放数据
 * @param:
 * @return:
 */
void transmit_playdata_RGBbr(void)
{
    uint8_t i;
    L0_cmd_playRGBbr_Typedef xPlay;
    if (slave.num) // 有设备在线的时候才发送数据
    {
        xPlay.head.dev_adr = ADDR_PUBLIC;    // 设备地址
        xPlay.head.cmd = CMD_SLAVE_PLAY_RGB; // 播放灯光 “RGBbr”格式
        xPlay.head.type = MES_ASK;           // 发出请求
        xPlay.playnum = slave.num;
        for (i = 0; i < xPlay.playnum; i++)
        {
            xPlay.dev[i].cid = slave.data[i].id;
            xPlay.dev[i].br = play.work.brightness.now;
            // if (Tangram[slave.data[i].runnum].W.Now == RGB_COLOR)
            // {
                xPlay.dev[i].R = Tangram[slave.data[i].runnum].R.Now;
                xPlay.dev[i].G = Tangram[slave.data[i].runnum].G.Now;
                xPlay.dev[i].B = Tangram[slave.data[i].runnum].B.Now;
            // }
            // else // KELVIN_COLOR
            // {
            //     xPlay.dev[i].R = 0;
            //     xPlay.dev[i].G = 0;
            //     xPlay.dev[i].B = 0;
            // }
        }
        transmit_protocol_frame((uint8_t *)&xPlay, &((L0_cmd_playRGBbr_Typedef *)0)->dev[slave.num], &parse.tx_framebuf); // 通过不定长协议发送
    }
}

/*
 * @Description: 发送“COLOR”格式的播放数据
 * @param:
 * @return:
 */
void transmit_playdata_COLOR(void)
{
    uint8_t i;
    L0_cmd_playCOLOR_Typedef xPlay;
    uint16_t kel;
    if (slave.num) // 有设备在线的时候才发送数据
    {
        xPlay.head.dev_adr = ADDR_PUBLIC;      // 设备地址
        xPlay.head.cmd = CMD_SLAVE_PLAY_COLOR; // 播放灯光 “COLOR”格式
        xPlay.head.type = MES_ASK;             // 发出请求
        xPlay.playnum = slave.num;
        for (i = 0; i < xPlay.playnum; i++)
        {
            xPlay.dev[i].cid = slave.data[i].id;
            xPlay.dev[i].br = play.work.brightness.now;
            if (Tangram[slave.data[i].runnum].W.Now == RGB_COLOR)
            {
                xPlay.dev[i].type = RGB_COLOR;
                xPlay.dev[i].R = Tangram[slave.data[i].runnum].R.Now;
                xPlay.dev[i].G = Tangram[slave.data[i].runnum].G.Now;
                xPlay.dev[i].B = Tangram[slave.data[i].runnum].B.Now;
            }
            else // KELVIN_COLOR
            {
                xPlay.dev[i].type = KELVIN_COLOR;
                kel = Tangram[slave.data[i].runnum].R.Now << 8;
                kel |= Tangram[slave.data[i].runnum].G.Now;
                xPlay.dev[i].R = kel / 100;
                xPlay.dev[i].G = 0;
                xPlay.dev[i].B = 0;
            }
        }
        transmit_protocol_frame((uint8_t *)&xPlay, &((L0_cmd_playCOLOR_Typedef*)0)->dev[slave.num], &parse.tx_framebuf); // 通过不定长协议发送
    }
}

/*
 * @Description: 广播发送“RGBbr”格式的播放数据
 * @param:
 * @return:
 */
void transmit_playsame_COLOR(L0_playCOLOR_Typedef *x)
{
    L0_cmd_playCOLOR_Typedef xPlay;
    if (slave.num) // 有设备在线的时候才发送数据
    {
        xPlay.head.dev_adr = ADDR_PUBLIC;    // 设备地址
        xPlay.head.cmd = CMD_SLAVE_PLAY_COLOR; // 播放灯光 “RGBbr”格式
        xPlay.head.type = MES_ASK;           // 发出请求
        xPlay.playnum = slave.num;
        xPlay.dev[0].cid = ADDR_PUBLIC;
        xPlay.dev[0].br = x->br;
        xPlay.dev[0].type = x->type;
        xPlay.dev[0].R = x->R;
        xPlay.dev[0].G = x->G;
        xPlay.dev[0].B = x->B;
        transmit_protocol_frame((uint8_t *)&xPlay, &((L0_cmd_playCOLOR_Typedef *)0)->dev[1], &parse.tx_framebuf); // 通过不定长协议发送
    }
}

/*
 * @Description: 广播发送“RGBbr”格式的播放数据
 * @param:
 * @return:
 */
void transmit_playsame_RGBbr(L0_playRGBbr_Typedef *x)
{
    L0_cmd_playRGBbr_Typedef xPlay;
    if (slave.num) // 有设备在线的时候才发送数据
    {
        xPlay.head.dev_adr = ADDR_PUBLIC;    // 设备地址
        xPlay.head.cmd = CMD_SLAVE_PLAY_RGB; // 播放灯光 “RGBbr”格式
        xPlay.head.type = MES_ASK;           // 发出请求
        xPlay.playnum = slave.num;
        xPlay.dev[0].cid = ADDR_PUBLIC;
        xPlay.dev[0].br = x->br;
        xPlay.dev[0].R = x->R;
        xPlay.dev[0].G = x->G;
        xPlay.dev[0].B = x->B;
        transmit_protocol_frame((uint8_t *)&xPlay, &((L0_cmd_playRGBbr_Typedef *)0)->dev[1], &parse.tx_framebuf); // 通过不定长协议发送
    }
}



/* 
 * @Description: 灯板显示配对状态
 * @param: 
 * @return: 
*/ 
void light_device_pairing_play(app_device_control_Typedef *x)
{
    uint8_t i;
    L0_cmd_playRGBbr_Typedef xPlay;
    xPlay.playnum = x->lightnum;
    if (xPlay.playnum) // 有设备在线的时候才发送数据
    {
        xPlay.head.dev_adr = ADDR_PUBLIC;    // 设备地址
        xPlay.head.cmd = CMD_SLAVE_PLAY_RGB; // 播放灯光 “RGBbr”格式
        xPlay.head.type = MES_ASK;           // 发出请求
        for (i = 0; i < xPlay.playnum; i++)
        {
            xPlay.dev[i].cid = slave.data[i].id;
            if (x->lightsta[i].lightsta == PERSENT) // 当前点亮
            {
                xPlay.dev[i].br = 100;
                xPlay.dev[i].R = 255;
                xPlay.dev[i].G = 255;
                xPlay.dev[i].B = 0;
            }
            else if (x->lightsta[i].lightsta == LIGHTED) // 已点亮
            {
                xPlay.dev[i].br = 20;
                xPlay.dev[i].R = 255;
                xPlay.dev[i].G = 255;
                xPlay.dev[i].B = 0;
            }
            else /* UNLIGHT, // 未点亮*/
            {
                xPlay.dev[i].br = 0;
                xPlay.dev[i].R = 0;
                xPlay.dev[i].G = 0;
                xPlay.dev[i].B = 0;
            }
        }
        transmit_protocol_frame((uint8_t *)&xPlay, &((L0_cmd_playRGBbr_Typedef *)0)->dev[slave.num], &parse.tx_framebuf); // 通过不定长协议发送
    }
}

/*
 * @Description: 重新随机排列列表内的数据
 * @param:
 * @param:
 * @return:
 */
void permute_list_in_random(uint8_t *list, uint8_t size)
{
    uint8_t data;
    uint8_t i, j;
    uint8_t random;
    for (j = 0; j < size; j++)
    {
        for (i = 0; i < size; i++)
        {
            random = get_random_number() % size; // 随机交换两个数
            data = list[random];
            list[random] = list[i];
            list[i] = data;
        }
    }
}

/* 
 * @Description: 将某数从列表中挪至第一项
 * @param: 
 * @param: 
 * @param: 
 * @return: 
*/ 
uint8_t move_data_to_first_in_list(uint8_t data,uint8_t *list, uint8_t listsize)
{
    uint8_t i, j;
    uint8_t templist[PlayList_efMaxNum];
    for (i = 0; i < listsize; i++)
    {
        if (list[i] == data)
        {
            memcpy(&templist[0], &list[i], listsize - i); // 拷贝后面
            memcpy(&templist[listsize - i], &list[0], i); // 拷贝前面
            memcpy(list, &templist[0], listsize);         // 覆盖原表
            return 1;
        }
    }
    return 0;
}

/*
 * @Description: 将原数组倒序排列
 * @param:
 * @param:
 * @return:
 */
void invert_list(uint8_t *list, uint8_t size)
{
    uint8_t i;
    uint8_t temp;
    if (size < 2)
    {
        return;
    }
    for (i = 0; i < (size / 2); i++)
    {
        temp = list[i];
        list[i] = list[size - i - 1];
        list[size - i - 1] = temp;
    }
}

/* 
 * @Description: 调整播放顺序
 * @param: 
 * @return: 
*/ 
void adjust_play_list(void)
{
    move_data_to_first_in_list(play.detail.efindex, &play.detail.list, play.detail.listefsum); // 调整列表
    play.detail.idex_inlist = 0;                                                              // 当前灯效调整为列表第一个灯效
}

/*
 * @Description: 开始播放一个列表
 * @param:
 * @return:
 */
void start_play_list(uint8_t listindex)
{
    playdetail_TypeDef playdetail;
    printlog("start_play_list:%d\r",listindex);
    
    play.detail.listindex = listindex;
    get_playdetail(&playdetail, play.detail.listindex);
    memcpy(&play.detail.list, &playdetail.list, sizeof(play.detail.list));
    play.detail.duration.min_MS = playdetail.DurationTime.min_MS;
    play.detail.duration.sec_MS = playdetail.DurationTime.sec_MS;
    play.detail.listefsum = playdetail.num;
    if (play.playmode == PLAY_IN_RANDOM)
    {
        permute_list_in_random(&play.detail.list, play.detail.listefsum); // 生成随机播放
    }
    play.detail.idex_inlist = 0;                                     // 列表中第一个灯效
    play.detail.efindex = play.detail.list[play.detail.idex_inlist]; // 取出灯效索引
    switch_effect(play.detail.efindex);                              // 切换灯效
    play.status = RUN;
    modify_playsource(SOURCE_LIST);
}

/* 
 * @Description: 结束列表播放
 * @param: 
 * @return: 
*/
void end_play_list(void)
{
    playdetail_TypeDef playdetail;
    printlog("end_play_list:%d\r", play.detail.listindex);
    modify_playsource(SOURCE_FREE);  // 结束列表播放，转为自由播放

    /*
    play.status = RUN;         // 保持当前灯效
    */
}

/* 
 * @Description: 重新加载当前播放列表
 * @param: 
 * @return: 
*/ 
void reload_current_play_list(void)
{
    playlist_ranklist_TypeDef ranklist; // 列表信息
    playdetail_TypeDef playdetail;
    uint8_t list_index;
    uint8_t ef_index;
    printlog("reload_current_play_list\r");
    if (play.source != SOURCE_LIST) 
    {
        return; // 当前不是列表播放模式，则不需要更新信息
    }
    get_playlist_ranklist(&ranklist);
    if (ranklist.num)
    {
        list_index = search_dataindex_in_list(play.detail.listindex, ranklist.list, ranklist.num);
        if (list_index != 0xFF) // 当前正在播放的列表存在
        {
            get_playdetail(&playdetail, play.detail.listindex); //
            //
            memcpy(&play.detail.list, &playdetail.list, sizeof(play.detail.list));
            play.detail.duration.min_MS = playdetail.DurationTime.min_MS;
            play.detail.duration.sec_MS = playdetail.DurationTime.sec_MS;
            play.detail.listefsum = playdetail.num;
            //
            ef_index = search_dataindex_in_list(play.detail.efindex, playdetail.list, playdetail.num);
            if (ef_index != 0xFF) // 当前正在播放的灯效在列表存在
            {
                play.detail.idex_inlist = ef_index;                              // 更新当前灯效在列表中的序号（指针）
                play.detail.efindex = play.detail.list[play.detail.idex_inlist]; // 取出灯效索引
            }
            else // 当前播放灯效已从列表中删除
            {
                play.detail.idex_inlist = 0;                                     // 从头播放
                play.detail.efindex = play.detail.list[play.detail.idex_inlist]; // 取出灯效索引
                switch_effect(play.detail.efindex);                              // 切到新灯效
            }
        }
        else // 当前正在播放的列表已经被删除
        {
            switch_playlist(0); // 切到默认列表播放
        }
    }
    else
    {
        /*
        正常情况下至少会存在一个默认列表（不会被删除掉），不会执行到这里
        */
        end_play_list();    // 结束列表播放
    }
}


/* 
 * @Description: 测试显示fft
 * @param: 
 * @return: 
*/ 
void transmit_play_fft(void)
{
    uint8_t i;
    L0_cmd_playCOLOR_Typedef xPlay;
    uint16_t kel;
    uint16_t col;
    if (slave.num) // 有设备在线的时候才发送数据
    {
        xPlay.head.dev_adr = ADDR_PUBLIC;      // 设备地址
        xPlay.head.cmd = CMD_SLAVE_PLAY_COLOR; // 播放灯光 “COLOR”格式
        xPlay.head.type = MES_ASK;             // 发出请求
        xPlay.playnum = slave.num;
        for (i = 0; i < xPlay.playnum; i++)
        {
            xPlay.dev[i].cid = slave.data[i].id;
            // xPlay.dev[i].br = play.work.brightness.now;
            // // if (Tangram[slave.data[i].runnum].W.Now == RGB_COLOR)
            // // {
            // //     xPlay.dev[i].type = RGB_COLOR;
            // //     xPlay.dev[i].R = Tangram[slave.data[i].runnum].R.Now;
            // //     xPlay.dev[i].G = Tangram[slave.data[i].runnum].G.Now;
            // //     xPlay.dev[i].B = Tangram[slave.data[i].runnum].B.Now;
            // // }
            // // else // KELVIN_COLOR
            // // {
            // //     xPlay.dev[i].type = KELVIN_COLOR;
            // //     kel = Tangram[slave.data[i].runnum].R.Now << 8;
            // //     kel |= Tangram[slave.data[i].runnum].G.Now;
            // //     xPlay.dev[i].R = kel / 100;
            // //     xPlay.dev[i].G = 0;
            // //     xPlay.dev[i].B = 0;
            // // }
            // col = (uint16_t )dd[i].real>>2;
            if (col>255)
            {
               col=255;
            }
            
            xPlay.dev[i].br = 100;
            xPlay.dev[i].type = RGB_COLOR;
            xPlay.dev[i].R = col;
            xPlay.dev[i].G = 255 - col;
            xPlay.dev[i].B = 0;
        }
        transmit_protocol_frame((uint8_t *)&xPlay, &((L0_cmd_playCOLOR_Typedef*)0)->dev[slave.num], &parse.tx_framebuf); // 通过不定长协议发送
    }
}
