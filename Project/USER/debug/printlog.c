#include "Function_Init.H"


/*打印hex*/
void printhex_my(uint8_t *sur, uint32_t len)
{
#if defined(printlog_enabled)
    uint32_t i;
    // printf("\n");
    for (i = 0; i < len; i++)
    {
        printf("%02x ", sur[i]);
        if ((i + 1) % 64 == 0) // 自动换行
        {
            printf("\n");
        }
    }
    printf("\n");
#endif // printlog_enabled
}

/*打印字符串*/
void printstr_my(uint8_t *sur, uint32_t len)
{
#if defined(printlog_enabled)
    uint32_t i;
    for (i = 0; i < len; i++)
    {
        printf("%c", sur[i]);
    }
    printf("\r");
#endif // printlog_enabled
}

/*打印动态效果*/
void print_flow(Flow_Enum num)
{
#if defined(printlog_enabled)
    printf("Flow:");
    switch (num)
    {
    case FLOW_STATIC:
        printf("Static\r");
        break;
    case FLOW_BREATH:
        printf("Breath\r");
        break;
    case FLOW_STREAM:
        printf("Stream\r");
        break;
    case FLOW_REVERB:
        printf("Reverberate\r");
        break;
    case FLOW_HOPSCO:
        printf("Hopscotch\r");
        break;
    case FLOW_LIGHTN:
        printf("Lightning\r");
        break;
    case FLOW_IGNITE:
        printf("Ignite\r");
        break;
    case FLOW_RANDOM:
        printf("Random\r");
        break;
    default:
        printf("   [error num:%d]\r", num);
        break;
    }
#endif // printlog_enabled
}
/*打印运动方向*/
void print_direction(Direction_Enum num)
{
#if defined(printlog_enabled)
    printf("Direction:");
    switch (num)
    {
    case DIRECTION_UP:
        printf("up\r");
        break;
    case DIRECTION_DOWN:
        printf("down\r");
        break;
    case DIRECTION_LEFT:
        printf("left\r");
        break;
    case DIRECTION_RIGHT:
        printf("right\r");
        break;
    case DIRECTION_SEPARATE:
        printf("disperse\r");
        break;
    case DIRECTION_CONVERGE:
        printf("concentrate\r");
        break;
    default:
        printf("   [error num:%d]\r", num);
        break;
    }
#endif // printlog_enabled
}
/*打印灯效类型*/
void print_effecttype(EffectType_Enum num)
{
#if defined(printlog_enabled)
    printf("EffectType:");
    switch (num)
    {
    case STATIC_TYPE:
        printf("static\r");
        break;
    case DYNAMIC_TYPE:
        printf("dynamic\r");
        break;
    case RHYTHM_TYPE:
        printf("rhythm\r");
        break;
    default:
        printf("   [error num:%d]\r", num);
        break;
    }
#endif // printlog_enabled
}
/*打印灯效属性*/
void print_attribute(Attribute_Enum num)
{
#if defined(printlog_enabled)
    printf("Attribute:");
    switch (num)
    {
    case ORIGIN:
        printf("origin\r");
        break;
    case FAVORITES:
        printf("favorite\r");
        break;
    case EMPTY:
        printf("empty\r");
        break;
    default:
        printf("   [error num:%d]\r", num);
        break;
    }
#endif // printlog_enabled
}

/*app灯效详情log*/
void print_com_effect_detial_log(com_effect_detial_TypeDef *p)
{
#if defined(printlog_enabled)
    uint8_t i = 0;
    print_effect_detial(&p->Efdata, p->idex);
    printf("checksum:0x%02x\r", p->checksum);
#endif
}

/*灯效详情log*/
void print_effect_detial(Efdetail_TypeDef *p, uint8_t efnum)
{
#if defined(printlog_enabled)
    uint8_t i = 0;
    printf("---------------- effect detial ----------------\r");
    printf("idex:%d\r", efnum);
    printf("namelenght:%d\r", p->namelenght);
    printf("Name:");
    printstr_my(&p->Name, p->namelenght);
    printf("Speed:%d\r", p->Speed);
    printf("Bright1:%d\r", p->Brightness1);
    printf("Bright2:%d\r", p->Brightness2);
    printf("Mic:%d\r", p->MicSensitivity);
    print_effecttype(p->EffectType);
    print_attribute(p->Attribute);
    print_direction(p->Direction);
    print_flow(p->Flow);
    printf("ColorNum:%d\r", p->EfColorInf.colorNum);
    for (i = 0; i < p->EfColorInf.colorNum; i++)
    // // for (i = 0; i < EfColor_SizeNum; i++)
    {
        printf("|%02x|%3d,%3d,%3d,%3d ", p->EfColorInf.ColorID[i].id, p->EfColorInf.ColorID[i].color.R, p->EfColorInf.ColorID[i].color.G, p->EfColorInf.ColorID[i].color.B, p->EfColorInf.ColorID[i].color.W);
        if ((i % 4) == 3)
        {
            printf("\r");
        }
    }
    printf("\r----------------\r");
#endif // printlog_enabled
}

/*打印灯效概述*/
void print_effect_sketch(Efminidetail_TypeDef *p, uint8_t efnum)
{
#if defined(printlog_enabled)
    uint8_t i = 0;
    printf("idex:%d\r", efnum);
    printf("Name:");
    // // printf("namelenght:%d\r", p->namelenght);
    printstr_my(&p->Name, p->namelenght);
    print_effecttype(p->EffectType);
    print_attribute(p->Attribute);
    printf("ColorNum:%d\r", p->EfColormioniInf.colorNum);
    for (i = 0; i < EfColor_miniSizeNum; i++)
    {
        printf(">%3d|%2x,%2x,%2x,%2x     ", p->EfColormioniInf.ColorID[i].id, p->EfColormioniInf.ColorID[i].color.R, p->EfColormioniInf.ColorID[i].color.G, p->EfColormioniInf.ColorID[i].color.B, p->EfColormioniInf.ColorID[i].color.W);
        if ((i % 4) == 3)
        {
            printf("\r");
        }
    }
    printf("\r");
#endif // printlog_enabled
}

/*打印获取存储区的灯效详情*/
void print_get_ef_detial(uint8_t efnum)
{
#if defined(printlog_enabled)
    Efdetail_TypeDef ef;
    printlog("read flash effect detial\r");
    get_effect_detail(&ef, efnum);
    print_effect_detial(&ef, efnum);
#endif // printlog_enabled
}

/*打印获取自定义灯效列表*/
void print_get_original_ef_ranklist(void)
{
#if defined(printlog_enabled)
    uint8_t i;
    ef_ranklist_TypeDef ranklist;
    get_originalef_ranklist(&ranklist); // 获取原信息
    printf("original effect sum:%d\r", ranklist.num);
    for (i = 0; i < ranklist.num; i++)
    {
        printf("[%3d] ", ranklist.list[i]);
    }
    printf("\r");
#endif // printlog_enabled
}
/*打印获取全部灯效列表*/
void print_get_all_ef_ranklist(void)
{
#if defined(printlog_enabled)
    uint8_t i;
    ef_ranklist_TypeDef ranklist;
    get_allef_ranklist(&ranklist); // 获取原信息
    printf("all effect ranklist sum:%d\r", ranklist.num);
    for (i = 0; i < ranklist.num; i++)
    {
        printf("[%3d] ", ranklist.list[i]);
    }
    printf("\r");
#endif // printlog_enabled
}
/*打印获取收藏灯效列表*/
void print_get_favorites_ef_ranklist(void)
{
#if defined(printlog_enabled)
    uint8_t i;
    ef_ranklist_TypeDef ranklist;
    get_favoritesef_ranklist(&ranklist); // 获取原信息
    printf("favorites effect ranklist sum:%d\r", ranklist.num);
    for (i = 0; i < ranklist.num; i++)
    {
        printf("[%3d] ", ranklist.list[i]);
    }
    printf("\r");
#endif // printlog_enabled
}
/*打印获取播放列表*/
void print_get_playlist_ranklist(void)
{
#if defined(printlog_enabled)
    uint8_t i;
    playlist_ranklist_TypeDef ranklist;
    get_playlist_ranklist(&ranklist); // 获取原信息
    printf("playlist ranklist sum:%d\r", ranklist.num);
    for (i = 0; i < ranklist.num; i++)
    {
        printf("[%3d] ", ranklist.list[i]);
    }
    printf("\r");
#endif // printlog_enabled
}

/*打印灯效列表*/
void print_ef_ranklist(ef_ranklist_TypeDef *p)
{
#if defined(printlog_enabled)
    uint8_t i;
    printf("ef_ranklist num:%d\r", p->num);
    for (i = 0; i < p->num; i++)
    {
        printf("[%3d] ", p->list[i]);
    }
    printf("\r\n");
#endif // printlog_enabled
}
/*打印播放列表的顺序表*/
void print_playlist_ranklist(playlist_ranklist_TypeDef *p)
{
#if defined(printlog_enabled)
    uint8_t i;
    printf("playlist_ranklist num:%d\r", p->num);
    for (i = 0; i < p->num; i++)
    {
        printf("[%3d] ", p->list[i]);
    }
    printf("\r\n");
#endif // printlog_enabled
}
/*打印通信播放列表的顺序表*/
void print_com_playlist_ranklist(com_playlist_TypeDef *p)
{
#if defined(printlog_enabled)
    uint8_t i;
    printf("com_playlist_TypeDef num:%d\r", p->sum);
    for (i = 0; i < p->sum; i++)
    {
        printf("[%d] ", p->list[i].index);
        printstr_my(&(p->list[i].name.text), p->list[i].name.length);
    }
    printf("\r\n");
#endif // printlog_enabled
}

/*打印播放详情*/
void print_playdetial(playdetail_TypeDef *p, uint8_t playnum)
{
#if defined(printlog_enabled)
    uint8_t i;
    printf("\r[ print_playdetial ]\r");
    printf("idex:%d\r", playnum);
    printf("namelenght:%d\r", p->name.length);
    printf("name:");
    printstr_my(&p->name.text, p->name.length);
    printf("Min:%d\r", p->DurationTime.min_MS);
    printf("Sec:%d\r", p->DurationTime.sec_MS);
    printf("num:%d\r", p->num);

    // // for (i = 0; i < PlayList_efMaxNum; i++)
    for (i = 0; i < p->num; i++)
    {
        printf("[%d] ", p->list[i]);
        if ((i % 4) == 9)
        {
            printf("\r");
        }
    }
    printf("----------------------------------------------\r\r");
    
#endif // printlog_enabled
}

/*打印app下发播放详情*/
void print_com_playdetial(com_play_detial_TypeDef *p)
{
#ifdef printlog_enabled
    printf("[ print_com_playdetial ]\r");
    print_playdetial(&p->pldata, p->idex);
    printf("checksum:0x%02x\r", p->checksum);
#endif
}
/*打印播放历史*/
void print_play_history(void)
{
#if defined(printlog_enabled)
    uint8_t i;
    printf("----------------------------------------------\r");
    printf("[ print_play_history ]\r");
    for (i = 0; i < sizeof(play.detail.history); i++)
    {
        printf("%3d ", play.detail.history[i]);
    }
    printf("\r----------------------------------------------\r");
#endif // printlog_enabled
}

/*打印播放状态*/
void print_playstatus(void)
{
#if defined(printlog_enabled)
    uint8_t i;
    printf("\r----------------------------------------------\r");
    printf(">print_playstatus\r");
    if (play.status == PAUSE)
    {
        printlog("PAUSE\r");
    }
    else if (play.status == RUN)
    {
        printlog("RUN\r");
    }
    if (play.playmode == PLAY_IN_SEQUENCE)
    {
        printlog("PLAY_IN_SEQUENCE\r");
    }
    else if (play.playmode == PLAY_IN_RANDOM)
    {
        printlog("PLAY_IN_RANDOM\r");
    }
    if (play.cyclemode == CYCLE_IN_LOOP)
    {
        printlog("CYCLE_IN_LOOP\r");
    }
    else if (play.cyclemode == CYCLE_IN_ONCE)
    {
        printlog("CYCLE_IN_ONCE\r");
    }
    printlog("list   num:%d\r", play.detail.listindex);
    printlog("effect num:%d\r", play.detail.efindex);
    printlog("min:%d sec:%d\r", play.detail.duration.min_MS, play.detail.duration.sec_MS);
    /*-----*/
    printlog("list(%2d ):\r", play.detail.listefsum);
    for (i = 0; i < play.detail.listefsum; i++)
    {
        printf("%d ",play.detail.list[i]);
        if ((i % 4) == 9)
        {
            printf("\r");
        }
    }
    printf("\r\r");
    // print_play_history();
#endif // printlog_enabled
}
/*打印从机设备信息*/
void print_slave_data(void)
{
#if defined(printlog_enabled)
    uint8_t i;
    printlog("\r------------------------------------------------\r");
    printlog("device data\r");
    // for (i = 0; i < 32; i++)
    for (i = 0; i < slave.num; i++)
    {
        printlog("%2d. id:[%02x] type:%d, angle:%3d, x:%3d, y:%3d num:%2d\r", i, slave.data[i].id, slave.data[i].shape, slave.data[i].angle, slave.data[i].cooed_x, slave.data[i].cooed_y, slave.data[i].runnum);
    }
    printlog("------------------------------------------------\r\r");
#endif // printlog_enabled
}

/*打印从机设备的颜色*/
void print_slave_color(void)
{
#if defined(printlog_enabled)
    uint8_t i;
    printlog("\r------------------------------------------------\r");
    printlog("device color\r");
    for (i = 0; i < slave.num; i++)
    {
        printlog("[%02x]: %3d, R:%02x, G:%02x, B:%02x, W:%02x\r", slave.data[i].id, slavecolor.color[i].brightness, slavecolor.color[i].R, slavecolor.color[i].G, slavecolor.color[i].B, slavecolor.color[i].W);
    }
    printlog("------------------------------------------------\r\r");
#endif // printlog_enabled
}

/*打印名字*/
void print_name(name_TypeDef *p)
{
#if defined(printlog_enabled)
    printf("name:");
    printstr_my(&(p->text), p->length);
#endif // printlog_enabled
}

/* 
 * @Description: 打印定时表详情
 * @param: 
 * @return: 
*/ 
void print_clock_detial(clock_detail_TypeDef *p)
{
#if defined(printlog_enabled)
    printf("<clock_detial>\r");
    print_name(&(p->name));
    if (p->en_sta == FUN_ENABLE)
    {
        printlog("enable\r");
    }
    else if (p->en_sta == FUN_DISABLE)
    {
        printlog("disable\r");
    }
    else
    {
        printlog("en: error\r");
    }
    if (p->action == TURN_OFF)
    {
        printlog("action: OFF\r");
    }
    else if (p->action == TURN_ON)
    {
        printlog("action: ON\r");
    }
    else
    {
        printlog("action: error\r");
    }
    printlog("effect: %d\r", p->ef_index);
    printlog("ultimatebright: %d\r", p->ultimatebright);
    printlog("actiontime: %02d:%02d\r", p->actiontime.hou_HM, p->actiontime.min_HM);
    printlog("duration: %02d:%02d\r", p->duration.hou_HM, p->duration.min_HM);
    printlog("repeat: %02x\r\n", p->repeat.week);
#endif
}


/* 
 * @Description: 打印全部定时表
 * @param: 
 * @return: 
*/ 
void print_all_clock_detail(void)
{
#if defined(printlog_enabled)
    clock_list_TypeDef schedule;
    uint8_t i;
    get_all_schedule(&schedule);
    printlog("\r---------------------------------------------------------------\r");
    printlog("<all_clock_detail>\r");
    printlog("size:%d\r", schedule.num);
    for (i = 0; i < schedule.num; i++)
    {
        printlog("\rnum:[%d]\r", i);
        print_clock_detial(&schedule.list[i]);
    }
    printlog("----------------------------------------\r\r");
#endif // printlog_enabled
}

/*
 * @Description: 打印在线从机信息
 * @param:
 * @return:
 */
void print_online_slave_data(void)
{
#if defined(printlog_enabled)
    uint8_t i;
    printlog("\r\r\r\r\r\r\r\r\r\r\r\r\n");
    printlog("\rprint_slave_data\r");
    printlog("slave num:%d\r", slave.num);
    for (i = 0; i < slave.num; i++)
    {
        printlog("[0x%02x] ", slave.data[i].id);
        switch (slave.data[i].shape)
        {
        case TRIANGLE_L:
            printlog("TRIANGLE_L ");
            break;
        case TRIANGLE_M:
            printlog("TRIANGLE_M ");
            break;
        case TRIANGLE_S:
            printlog("TRIANGLE_S ");
            break;
        case SQUARE:
            printlog("SQUARE     ");
            break;
        default:
            printlog("other      ");
            break;
        }
        printlog("runnum:%2d ", slave.data[i].runnum);
        printlog("angle:%5d ", slave.data[i].angle);
        printlog("X :%5d ", slave.data[i].cooed_x);
        printlog("Y :%5d \r", slave.data[i].cooed_y);
    }
    printlog("\r----------------------------------------\r\r");
#endif // printlog_enabled
}

/*
 * @Description: 运行灯效详情log
 * @param:
 * @return:
 */
void print_play_effect_detial(void)
{
#if defined(printlog_enabled)
    printlog("print_play_effect_detial");
    print_effect_detial(&play.efdetail, play.detail.efindex);
#endif // printlog_enabled
}

/* 
 * @Description: app控制灯板的log
 * @param: 
 * @return: 
*/ 
void print_device_control(app_device_control_Typedef*x)
{
    uint8_t i;
#if defined(printlog_enabled)
    printlog("print_device_control");
    printf("lightnum:%d\r", x->lightnum);
    for ( i = 0; i < x->lightnum; i++)
    {
       printf("id:%02x index:%02d sta:%02x\r",x->lightsta[i].id,x->lightsta[i].index,x->lightsta[i].lightsta);
    }
    printf("\r\n");
#endif // printlog_enabled
}

/* 
 * @Description: 打印本地rtc时钟
 * @param: 
 * @return: 
*/ 
void print_local_rtc_time(void)
{
#if defined(printlog_enabled)
    rtc_counter_value_t rtc;
    RTC_Get_CounterValue(&rtc);
    RTC_BCD_To_HEX(&rtc);
    // // printf("\r>> local rtc\r");
    printf("20%d/%d/%d %d %d:%d:%d\r\n", rtc.year, rtc.month, rtc.day, rtc.week, rtc.hour, rtc.min, rtc.sec);
#endif // printlog_enabled
}



/* 
 * @Description: 打印设备迷你信息
 * @param: 
 * @return: 
*/ 
void print_mini_device_data(mini_device_data_TypeDef *dev)
{
#if defined(printlog_enabled)
    uint8_t i;
    printlog("\r------------------------------------------------\r");
    printlog("mini device data\r");
    for (i = 0; i < dev->num; i++)
    {
        printlog("%2d. id:[%02x] x:%5d, y:%5d num:%2d\r", i, dev->data[i].id, dev->data[i].cooed_x, dev->data[i].cooed_y, dev->data[i].runnum);
    }
    printlog("------------------------------------------------\r\r");
#endif // printlog_enabled
}

/* 
 * @Description: 打印颜色输出
 * @param: 
 * @param: 
 * @return: 
*/ 
void print_xPlay_color(L0_cmd_playCOLOR_Typedef *xPlay,uint8_t num)
{
    #if defined(printlog_enabled)
    uint8_t i;
    printlog("\r------------------------------------------------\r");
    for (i = 0; i < num; i++)
    {
        printlog("id:[%02x] br:%3d R:%3d, G:%3d B:%3d\r", xPlay->dev[i].cid, xPlay->dev[i].br, xPlay->dev[i].R, xPlay->dev[i].G, xPlay->dev[i].B);
    }
    printlog("------------------------------------------------\r");
#endif // printlog_enabled
}
