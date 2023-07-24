#include "appfunction.h"
#include "Function_Init.H"

/*校验通信数据是否正确*/
uint8_t com_dataverify(uint8_t *sur, uint16_t size)
{
    if ((uint8_t)checksum_calculate((uint8_t *)sur, size - 1) != *(sur + size - 1))
    { // 校验最后一字节是否为校验和
        printhex_my(sur, size);
        printlog("com data verify error\r\n");
        return 0;
    }
    return 1;
}

/*mcu上报灯效详情*/
void mcu_update_efdetail(uint8_t efnum)
{
    com_effect_detial_TypeDef comef;
    comef.idex = efnum;
    get_effect(&comef.Efdata, efnum);
    comef.checksum = (uint8_t)checksum_calculate((uint8_t *)&comef, sizeof(comef) - 1);
    mcu_dp_raw_update(DPID_EFFECT_DETIAL, &comef, sizeof(comef));
}
/*mcu上报灯效概述*/
void mcu_update_efsketch(com_issue_cmd_TypeDef *p)
{
    com_effect_sketch_TypeDef sketch;
    Efdetail_TypeDef efdata;
    memset(&sketch, 0, sizeof(sketch)); // 清零
    uint8_t i;
    if (p->data[0] > 4)
    {
        return;
    }
    sketch.num = p->data[0];
    for (i = 0; i < sketch.num; i++)
    {
        sketch.Efdata[i].index = p->data[i + 1]; // 索引
        get_effect(&efdata, sketch.Efdata[i].index);
        sketch.Efdata[i].namelenght = efdata.namelenght;
        memcpy(&sketch.Efdata[i].Name, &efdata.Name, sizeof(sketch.Efdata[i].Name));                             // 名字
        sketch.Efdata[i].Attribute = efdata.Attribute;                                                           // 属性
        sketch.Efdata[i].EffectType = efdata.EffectType;                                                         // 类型
        memcpy(&sketch.Efdata[i].EfColormioniInf, &efdata.EfColorInf, sizeof(sketch.Efdata[i].EfColormioniInf)); // 颜色
    }
    sketch.checksum = (uint8_t)checksum_calculate((uint8_t *)&sketch, sizeof(sketch) - 1);
    // // printlog("sketch SIZE %d",sizeof(sketch));
    mcu_dp_raw_update(DPID_EFFECT_SKETCH, &sketch, sizeof(sketch));
}
/*mcu上报灯效概述-从播放列表的dp上传*/
void mcu_update_playlist_efsketch(com_issue_cmd_TypeDef *p)
{
    com_effect_sketch_TypeDef sketch;
    Efdetail_TypeDef efdata;
    memset(&sketch, 0, sizeof(sketch)); // 清零
    uint8_t i;
    if (p->data[0] > 4)
    {
        return;
    }
    sketch.num = p->data[0];
    for (i = 0; i < sketch.num; i++)
    {
        sketch.Efdata[i].index = p->data[i + 1]; // 索引
        get_effect(&efdata, sketch.Efdata[i].index);
        sketch.Efdata[i].namelenght = efdata.namelenght;
        memcpy(&sketch.Efdata[i].Name, &efdata.Name, sizeof(sketch.Efdata[i].Name));                             // 名字
        sketch.Efdata[i].Attribute = efdata.Attribute;                                                           // 属性
        sketch.Efdata[i].EffectType = efdata.EffectType;                                                         // 类型
        memcpy(&sketch.Efdata[i].EfColormioniInf, &efdata.EfColorInf, sizeof(sketch.Efdata[i].EfColormioniInf)); // 颜色
    }
    sketch.checksum = (uint8_t)checksum_calculate((uint8_t *)&sketch, sizeof(sketch) - 1);
    mcu_dp_raw_update(DPID_PLAYLIST_EFFECT_SKETCH, &sketch, sizeof(sketch));
}
/*mcu上报全部灯效的顺序表*/
void mcu_update_allef_ranklist(void)
{
    com_ranklist_TypeDef com_ranklist;
    printlog("mcu_update_allef_ranklist\r");
    get_allef_ranklist((ef_ranklist_TypeDef *)&com_ranklist.ranklist);
    com_ranklist.checksum = (uint8_t)checksum_calculate((uint8_t *)&com_ranklist, (uint16_t)sizeof(com_ranklist) - 1);
    mcu_dp_raw_update(DPID_ALL_EFFECT_RANKLIST, &com_ranklist, sizeof(com_ranklist));
    // // printhex_my(&com_ranklist, sizeof(com_ranklist));
    print_ef_ranklist(&com_ranklist.ranklist);
}
/*mcu上报自定义灯效的顺序表*/
void mcu_update_originalef_ranklist(void)
{
    com_ranklist_TypeDef com_ranklist;
    printlog("mcu_update_originalef_ranklist\r");
    get_originalef_ranklist((ef_ranklist_TypeDef *)&com_ranklist.ranklist);
    com_ranklist.checksum = (uint8_t)checksum_calculate((uint8_t *)&com_ranklist, (uint16_t)sizeof(com_ranklist) - 1);
    mcu_dp_raw_update(DPID_ORIGINAL_EFFECT_RANKLIST, &com_ranklist, sizeof(com_ranklist));
    print_ef_ranklist(&com_ranklist.ranklist);
    // // // printhex_my(&com_ranklist,sizeof(com_ranklist.ranklist));
}
/*mcu上报收藏灯效的顺序表*/
void mcu_update_favoritesef_ranklist(void)
{
    com_ranklist_TypeDef com_ranklist;
    printlog("mcu_update_favoritesef_ranklist\r");
    get_favoritesef_ranklist((ef_ranklist_TypeDef *)&com_ranklist.ranklist);
    com_ranklist.checksum = (uint8_t)checksum_calculate((uint8_t *)&com_ranklist, (uint16_t)sizeof(com_ranklist) - 1);
    mcu_dp_raw_update(DPID_FAVORITES_EFFECT_RANKLIST, &com_ranklist, sizeof(com_ranklist));
    print_ef_ranklist(&com_ranklist.ranklist);
}
/*mcu上报播放列表的顺序表*/
void mcu_update_playlist_ranklist(void)
{
    com_playlist_TypeDef com_ranklist;
    playlist_ranklist_TypeDef ranklist;
    name_TypeDef name;
    uint8_t i;
    printlog("mcu_update_playlist_ranklist\r");
    get_playlist_ranklist((playlist_ranklist_TypeDef *)&ranklist);
    print_playlist_ranklist(&ranklist);
    memset(&com_ranklist, 0, sizeof(com_ranklist));
    com_ranklist.sum = ranklist.num; // 获取列表个数
    for (i = 0; i < com_ranklist.sum; i++)
    {
        com_ranklist.list[i].index = ranklist.list[i];                          // 拷贝索引号
        get_playlist_name(&name, com_ranklist.list[i].index);                   // 获取列表详情的名字
        com_ranklist.list[i].name.length = name.length;                         // 拷贝名字长度
        memcpy(&com_ranklist.list[i].name.text, &name.text, sizeof(name.text)); // 拷贝名字
    }
    com_ranklist.checksum = (uint8_t)checksum_calculate((uint8_t *)&com_ranklist, (uint16_t)sizeof(com_ranklist) - 1);
    mcu_dp_raw_update(DPID_PLAY_LIST, &com_ranklist, sizeof(com_ranklist));
    print_com_playlist_ranklist(&com_ranklist);
}
/*mcu上报播放详情*/
void mcu_update_playdetail(uint8_t playnum)
{
    com_play_detial_TypeDef com;
    printlog("mcu_update_playdetail\r");
    get_playdetail(&com.pldata, playnum);
    com.idex = playnum;
    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_PLAY_DETIAL, &com, sizeof(com));
    print_playdetial(&com.pldata, com.idex);
}
/*mcu上报当前播放详情*/
void mcu_update_current_playdetail(void)
{
    com_play_detial_TypeDef com;
    printlog("mcu_update_current_playdetail\r");
    get_playdetail(&com.pldata, play.detail.listnum);
    com.idex = play.detail.listnum;
    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_PLAY_CONTROL_DETIAL, &com, sizeof(com));
    // // // // printhex_my(&com, sizeof(com));
    print_playdetial(&com.pldata, com.idex);
}

/*mcu上报播放状态*/
void mcu_update_playstatus(void)
{
    com_play_control_TypeDef com;
    com.type = PLAY_STATUS;// 播放/暂停
    com.value = play.status;
    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_PLAY_CONTROL, &com, sizeof(com));
    com.type = PLAYLIST_INDEX;// 播放列表索引
    com.value = play.detail.listnum;
    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_PLAY_CONTROL, &com, sizeof(com));
    com.type = EFFECT_INDEX;// 效果索引
    com.value = play.detail.efnum;
    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_PLAY_CONTROL, &com, sizeof(com));
    com.type = PLAY_MODE;// 播放循环模式
    com.value = play.mode;
    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_PLAY_CONTROL, &com, sizeof(com));
}
/*mcu上报设备信息*/
void mcu_update_device_detail(void)
{
    uint8_t i, j;
    com_device_data_TypeDef com;
    printlog("mcu_update_device_detail\r");
    memset(&com, 0, sizeof(com));
    for (i = 0; i < slave.num; i++)
    {
        com.data[i].id = slave.data[i].id;
        com.data[i].shape = slave.data[i].shape;
        com.data[i].angle = slave.data[i].angle;
        com.data[i].cooed_x = slave.data[i].cooed_x;
        com.data[i].cooed_y = slave.data[i].cooed_y;
    }
    printlog("slave.num:%d\r",slave.num);
    printhex_my(&com, (slave.num * sizeof(com_device_detail_TypeDef)));
    mcu_dp_raw_update(DPID_DEVICE_DETAIL, &com, (slave.num * sizeof(com_device_detail_TypeDef))); // RAW型数据上报;
}

/*mcu上报定时计划概述表*/
void mcu_update_schedule_sketch(void)
{
    com_schedule_sketchlist_TypeDef  com;
    schedule_list_TypeDef schedule;
    uint8_t i;
    printlog("mcu_update_schedule_sketch\r");
    get_all_schedule(&schedule);
    memset(&com, 0, sizeof(com));
    if (schedule.num < SCHEDULE_NUM)
    {
        com.num=schedule.num;
        for (i = 0; i < schedule.num; i++)
        {
            com.list[i].index = i;
            com.list[i].action = schedule.list[i].action;                 // 动作类型
            com.list[i].actiontime.Min = schedule.list[i].actiontime.Min; // 动作时间
            com.list[i].actiontime.Sec = schedule.list[i].actiontime.Sec; // 动作时间
            com.list[i].repeat = schedule.list[i].repeat;                 // 星期计划
        }
    }
    else
    {
        printlog("[error] schedule data exception \r");
        printAssert();
    }
    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_CLOCK_LIST, &com, sizeof(com));
}
/*mcu上报定时详情*/
void mcu_update_schedule_detail(uint8_t num)
{
    com_schedule_detail_TypeDef com;
    schedule_detail_TypeDef schedule_detail;
    printlog("mcu_update_schedule_detail\r");
    memset(&com, 0, sizeof(com));
    get_schedule_detail(&schedule_detail, num);
    com.index = num;
    copy_schedule_detail_to_com(&schedule_detail, &com);
    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_CLOCK_DETIAL, &com, sizeof(com));
}



/******************************************************************************************************************************************************/
/*






























*/


/*针对DPID_EFFECT_DETIAL的处理函数*/
uint8_t mcu_download_effect_detail_handle(uint8_t *sur, uint16_t length)
{
    printlog("mcu_download_effect_detail_handle\r");
    if (com_dataverify(sur, length) == 0)
    {
        return 0;
    }
    add_original_ef((Efdetail_TypeDef *)(&((com_effect_detial_TypeDef *)sur)->Efdata), (uint8_t)(((com_effect_detial_TypeDef *)sur)->idex));
    mcu_update_allef_ranklist();
    mcu_update_originalef_ranklist();
    return 1;
}

/*针对DPID_ISSUE_CMD的处理函数*/
uint8_t mcu_download_issue_cmd_handle(uint8_t *sur, uint16_t length)
{
    com_issue_cmd_TypeDef *p;
    // // // // printlog("mcu_download_issue_cmd_handle\r");
    if (com_dataverify(sur, length) == 0)
    {
        return 0;
    }
    p = (com_issue_cmd_TypeDef *)sur;
    switch (p->cmd)
    {
    case ASK_EFSKETCH: /*效果概述*/
        printlog("ASK_EFSKETCH\r");
        mcu_update_efsketch(p);
        // printlog("mcu update efsketch:%d [%3d] [%3d] [%3d] [%3d]\r",p->data[0],p->data[1],p->data[2],p->data[3],p->data[4]);
        // printlog("mcu_update_efsketch\r");
        break;
    case ASK_EFDETAIL:                   /*效果详情*/
        mcu_update_efdetail(p->data[0]); // mcu上报灯效详情
        printlog("mcu_update_efdetail\r");
        break;
    case DELETE_EF: /*删除效果*/
        delete_original_ef(p->data[0]);
        printlog("delete_original_ef\r");
        break;
    case ADD_FAVORITES: /*加入收藏*/
        add_favorites_ef(p->data[0]);
        printlog("add_favorites_ef\r");
        break;
    case DELETE_FAVORITES: /*取消收藏*/
        delete_favorites_ef(p->data[0]);
        printlog("delete_favorites_ef\r");
        break;
    case ASK_ALLEFRANKLIST: /*请求全部灯效的顺序表*/
        printlog("ASK_ALLEFRANKLIST\r");
        mcu_update_allef_ranklist();
        break;
    case ASK_ORINGINALRANKLIST: /*请求自定义灯效的顺序表*/
        printlog("ASK_ORINGINALRANKLIST\r");
        mcu_update_originalef_ranklist();
        break;
    case ASK_FAVORITESRANKLIST: /*请求收藏灯效的顺序表*/
        printlog("ASK_FAVORITESRANKLIST\r");
        mcu_update_favoritesef_ranklist();
        break;
    case ASK_PLAYLISTRANKLIST: /*请求播放列表的顺序表*/
        printlog("ASK_PLAYLISTRANKLIST\r");
        mcu_update_playlist_ranklist();
        break;
    case ASK_EFFECTANKLIST: /*请求灯效相关的顺序表*/
        printlog("ASK_EFFECTANKLIST\r");
        mcu_update_allef_ranklist();
        mcu_update_originalef_ranklist();
        mcu_update_favoritesef_ranklist();
        break;
    case ASK_PLAY_EFSKETCH: /*请求效果概述*/
        printlog("ASK_PLAY_EFSKETCH\r");
        mcu_update_playlist_efsketch(p);
        break;
    case REAERVE_CMD11: /*保留*/
        break;
    case DELETE_PLAYLISTRANKLISTLIST: /*删除播放列表中某个详情表*/
        printlog("DELETE_PLAYLISTRANKLISTLIST\r");
        delete_playlist(p->data[0]);
        break;
    case SWITCH_PLAYLIST: /*切换播放列表*/
        printlog("SWITCH_PLAYLIST\r");
        switch_playlist(p->data[0]);
        mcu_update_current_playdetail(); // 自动上报当前播放详情
        mcu_update_playstatus();         // 自动上报播放状态
        break;
    case ASK_PLAYDETAIL: /*请求播放详情*/
        printlog("ASK_PLAYDETAIL\r");
        mcu_update_playdetail(p->data[0]);
        break;
    case ASK_PLAYSTATUS: /*请求播放状态*/
        printlog("ASK_PLAYSTATUS\r");
        break;
    case DELETE_SCHEDULE: /*删除定时计划*/
        printlog("DELETE_SCHEDULE\r");
        delete_schedule(p->data[0]);
        break;
    case ASK_SCHEDULE_DETAIL: /*请求定时详情*/
        printlog("ASK_SCHEDULE_DETAIL\r");
        mcu_update_schedule_detail(p->data[0]);
        break;
    case ASK_DEVICEDATA: /*请求灯板信息*/
        printlog("ASK_DEVICEDATA\r");
        mcu_update_device_detail();
        print_slave_data();
        break;
    case EXIT_APPCONNTROL: /*退出app控制*/
        printlog("EXIT_APPCONNTROL\r");

        break;
    case ASK_SCHEDULE_SKETCH: /*请求定时计划表*/
        printlog("ASK_SCHEDULE_SKETCH\r");
        mcu_update_schedule_sketch();
        break;
    case PLAY_TEMP_EFFECT: /*播放临时灯效*/
        printlog("PLAY_TEMP_EFFECT\r");
        play_new_effect(p->data[0]);
        mcu_update_current_playdetail(); // 自动上报当前播放详情
        mcu_update_playstatus();         // 自动上报播放状态
        break;
    default:
        printlog("[error] wrong command num:%d\r", p->cmd);
        printAssert();
        break;
    }
    return 1;
}
/*针对DPID_EFFECT_PREVIEW的处理函数*/
void mcu_download_effect_preview(uint8_t *sur, uint16_t length)
{
    printlog("effect_preview \r");
//    com_effect_detial_TypeDef p;
//    printlog("\r\r\r{effect_preview}\r\r");
//    memcpy(&p, value, sizeof(p));
//    if ((uint8_t)checksum_calculate(value, length - 1) == p.sum)
//    {
//        print_com_effect_detial_log(&p); // 打印log
//    }
//    else
//    {
//        printlog("check sum err\r");
//        configASSERT(0);
//        printhex_my(value, length);
//    }
}

/*针对DPID_PLAY_DETIAL的处理函数*/
uint8_t mcu_download_play_detial(uint8_t *sur, uint16_t length)
{
    printlog("mcu_download_play_detial \r");
    if (com_dataverify(sur, length) == 0)
    {
        return 0;
    }
    add_playlist((playdetail_TypeDef *)(&((com_play_detial_TypeDef *)  sur)->pldata), (uint8_t)(((com_play_detial_TypeDef *)  sur)->idex));
    print_com_playdetial(sur);
    mcu_update_playlist_ranklist();
    return 1;
}
/*针对DPID_PLAY_CONTROL_DETIAL的处理函数*/
uint8_t mcu_download_play_control_detial(uint8_t *sur, uint16_t length)
{
    printlog("mcu_download_play_control_detial\r");
    if (com_dataverify(sur, length) == 0)
    {
        return 0;
    }
    switch (((com_play_control_TypeDef *)sur)->type)
    {
    case PLAY_STATUS: // 播放/暂停
        play.status = (playstatus_enum)(((com_play_control_TypeDef *)sur)->value);
        break;
    case PLAY_SWITCH: // 上下曲切换
        switch_ln_effect((switchplay_enum)(((com_play_control_TypeDef *)sur)->value));
        break;
    case EFFECT_INDEX: // 效果索引

        break;
    case PLAY_MODE: // 播放循环模式
        play.mode = (playmode_enum)(((com_play_control_TypeDef *)sur)->value);
        break;
    case PLAYLIST_INDEX: // 播放列表索引
        switch_playlist((((com_play_control_TypeDef *)sur)->value));
        break;
    default:
        printlog("[error] wrong play type num:%d\r", ((com_play_control_TypeDef *)sur)->type);
        printAssert();
        break;
    }
    print_playstatus();
    return 1;
}

/*针对DPID_DEVICE_DETAIL的处理函数*/
void mcu_download_device_detail(uint8_t *sur, uint16_t length)
{
    uint8_t i, j;
    com_device_detail_TypeDef com;
    device_detail_TypeDef device;
    printlog("mcu_download_device_detail\r");
    j = length / sizeof(com_device_detail_TypeDef); // 算出设备数量
    for (i = 0; i < j; i++)
    {
        memset(&device, 0, sizeof(device));
        memcpy(&com, sur + (sizeof(com) * i), sizeof(com));
        device.id = com.id;
        device.angle = com.angle;
        device.cooed_x = com.cooed_x;
        device.cooed_y = com.cooed_y;
        refresh_slave_data(&device);
    }
    save_all_slave_data(&slave);
    print_slave_data();
    goto_mcu_control_mode();    // 进入mcu控制模式
}
/*针对DPID_DEVICE_CONTROL的处理函数*/
uint8_t mcu_download_device_control(uint8_t *sur, uint16_t length)
{
    // // com_device_control_TypeDef* p;
    color_TypeDef color;
    uint8_t i;
    printlog("mcu_download_device_control\r");
    goto_app_control_mode(); // 进入app控制模式
    if (com_dataverify(sur, length) == 0)
    {
        return 0;
    }
    printhex_my(sur, length);
    // // p = (com_device_control_TypeDef *)sur;

    // // printlog("id:%d\r",((com_device_control_TypeDef *)sur)->data[0].id);

    light_up_only_one_slave(((com_device_control_TypeDef *)sur)->data[0].id);
    // // for (i = 0; i < p->num; i++)
    // // {
    // //     color.brightness = p->data[i].brightness;
    // //     color.R = p->data[i].R;
    // //     color.G = p->data[i].G;
    // //     color.B = p->data[i].B;
    // //     color.W = p->data[i].W;
    // //     refresh_device_color(&color, p->data[i].id);
    // // }
    // // print_slave_color();

    return 1;
}
/*针对DPID_CLOCK_DETIAL的处理函数*/
uint8_t mcu_download_clock_detial(uint8_t *sur, uint16_t length)
{
    schedule_detail_TypeDef schedule_detail;

    printlog("mcu_download_clock_detial\r");
    copy_schedule_detail_from_com((com_schedule_detail_TypeDef *)sur, &schedule_detail);
    print_schedule_detial(&schedule_detail);
    add_schedule(&schedule_detail, ((com_schedule_detail_TypeDef *)sur)->index);
    mcu_update_schedule_sketch();
    print_all_schedule();
}
/*




*/
/*在线下载固件*/
void mcu_firmware_download(uint8_t *sur, uint16_t position, uint16_t length)
{
    static uint32_t packsum = 0; // 升级包校验和
    uint32_t chechsum;
    if (length == 0)
    {
        // 固件数据发送完成

        chechsum = get_firmware_chechsum_norflash();
        printlog("package sum is 0x%04x,norflash firmware chechsum:0x%04x\r", packsum, chechsum);
        if (packsum == chechsum) // 校验存储数据是否与升级包一致
        {
            set_firmware_update_flag(packsum); // 设标志
            /* 重启*/
            printlog("\rsystem restart..\r\n");
            __NVIC_SystemReset();
            // // if (check_firmware_update())
            // // {
            // //     printlog("firmware is correct\r\n");
            // // }
            // // else
            // // {
            // //     printlog("firmware is error\r\n");
            // // }
        }
        else
        {
            printlog("firmware is error\r\n");
        }
    }
    else
    {
        // 固件数据处理
        if (position == 0) // 收包初始化
        {
            packsum = 0;
            clear_firmware_update_flag();       // 清标志
            erase_firmware_block64K_norflash(); // 擦除固件区
        }
        download_firmware_to_norflash(sur, position); // 下载固件包
        packsum += checksum_calculate(sur, 256);      // 累计校验和
    }
}

/*
 * @Description: 针对DPID_BRIGHT_VAL的处理函数
 * @param: 无
 * @return: 无
*/
void mcu_download_bright_val(uint8_t bri)
{
    printlog("mcu_download_bright_val:%d\r",bri);
    play.work.brightness.set = bri;
}

/*
 * @Description: 上传亮度
 * @param:
 * @return:
*/
void mcu_update_bright_val(void)
{
    printlog("mcu_download_bright_val:%d\r",play.work.brightness.set);
    mcu_dp_value_update(DPID_BRIGHT_VAL,play.work.brightness.set); //VALUE型数据上报;
}

/*
 * @Description: 针对DPID_SWITCH_LED的处理函数
 * @param: 无
 * @return: 无
*/
void mcu_download_switch_led(uint8_t sw)
{
    printlog("mcu_download_switch_led:%d\r",sw);
    if (sw)
    {
        play.work.sw_status = SW_ON;
    }
    else
    {
        play.work.sw_status = SW_OFF;
    }
}

/*
 * @Description: 上报开关状态
 * @param: 无
 * @return: 无
*/
void mcu_update_switch_led(void)
{
    printlog("mcu_update_switch_led:%d\r", play.work.sw_status);
    mcu_dp_bool_update(DPID_SWITCH_LED, play.work.sw_status); // BOOL型数据上报;
}




/*---------------------------------------------------------------------------------*/
/*































































*/
