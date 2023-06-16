#include "play.h"

play_TypeDef play;

/*播放初始化*/
void play_init(void)
{
    switch_playlist(0); // 切换至默认播放列表
    play.mode = LOOP_MODE;
    memset(&play.detail.history, NULL_EFFECTNUM, sizeof(play.detail.history));
    print_play_history();
}
/*在表中新增灯效编号*/
void add_num_in_list(uint8_t efnum)
{
    uint8_t buffer[sizeof(play.detail.history)];
    memcpy(&buffer[1], &play.detail.history, (sizeof(buffer) - 1));
    buffer[0] = efnum; // 从头部添加新号码
    memcpy(&play.detail.history, buffer, sizeof(play.detail.history));
    print_play_history();
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
    ef_ranklist_TypeDef eflist;
    uint8_t i;
    uint8_t j = 0;
    printlog("switch effect num:%d\r",efnum);
    get_allef_ranklist(&eflist);
    for (i = 0; i < eflist.num; i++)
    {
        if (eflist.list[i] == efnum) // 顺序表内存在被切换的灯效
        {
            j = 1;
            break;
        }
    }
    if (j)
    {
        /*切换灯效准备*/
        return 1;
    }
    else
    {
        printlog("[error] switch wrong effect num :%d", efnum);
        return 0;
    }
}
/*切换上下灯效*/
uint8_t switch_ln_effect(switchplay_enum num)
{
    playdetail_TypeDef playdetail;
    switch (num)
    {
    case LAST_EFFECT:// 上一个灯效
        switch_effect(play.detail.history[0]);
        break;
    case NEXT_EFFECT:// 下一个灯效
        // get_playdetail(&playdetail);

        break;
    default:
        printlog("[error] wrong switch effect command %d\r",num);
        printAssert();
        break;
    }
}

/* 切换播放列表 */
uint8_t switch_playlist(uint8_t listnum)
{
    playlist_ranklist_TypeDef playlist;
    playdetail_TypeDef playdetail;
    uint8_t i;
    uint8_t j = 0;
    printlog("switch playlist num:%d\r",listnum);
    if (listnum == play.detail.listnum) // 与当前播放表一致
    {
        printlog("[warning]switch same playlist num :%d\r", listnum);
        return 0;
    }
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
