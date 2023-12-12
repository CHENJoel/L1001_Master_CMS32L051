
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

/*---------------------------------------------------------------------------------*/
/* 
 * @Description: 上报灯效详情
 * @param: 
 * @return: 
*/ 
void mcu_update_ef_detail(uint8_t efindex)
{
    com_effect_detial_TypeDef comef;
    printlog("mcu_update_ef_detail\r");
    comef.idex = efindex;
    get_effect_detail(&comef.Efdata, efindex);
    comef.checksum = (uint8_t)checksum_calculate((uint8_t *)&comef, sizeof(comef) - 1);
    mcu_dp_raw_update(DPID_EFFECT_DETIAL, &comef, sizeof(comef));
    // print_effect_detial(&comef.Efdata, comef.idex);
}



/*---------------------------------------------------------------------------------*/

/* 
 * @Description: 根据指令上报灯效概述
 * @param: 
 * @return: 
*/ 
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
        get_effect_detail(&efdata, sketch.Efdata[i].index);
        sketch.Efdata[i].namelenght = efdata.namelenght;
        memcpy(&sketch.Efdata[i].Name, &efdata.Name, sizeof(sketch.Efdata[i].Name));                             // 名字
        sketch.Efdata[i].Attribute = efdata.Attribute;                                                           // 属性
        sketch.Efdata[i].EffectType = efdata.EffectType;                                                         // 类型
        memcpy(&sketch.Efdata[i].EfColormioniInf, &efdata.EfColorInf, sizeof(sketch.Efdata[i].EfColormioniInf)); // 颜色
        // printlog("update efsketch :%d\r", sketch.Efdata[i].index);
    }
    sketch.checksum = (uint8_t)checksum_calculate((uint8_t *)&sketch, sizeof(sketch) - 1);
    // // printlog("sketch SIZE %d",sizeof(sketch));
    mcu_dp_raw_update(DPID_EFFECT_SKETCH, &sketch, sizeof(sketch));
}
/* 
 * @Description: 上报某灯效概述
 * @param: 
 * @return: 
*/ 
void mcu_update_one_efsketch(uint8_t efnum)
{
    com_effect_sketch_TypeDef sketch;
    Efdetail_TypeDef efdata;
    printlog("mcu_update_one_efsketch : %d\n", efnum);
    memset(&sketch, 0, sizeof(sketch)); // 清零
    sketch.num = 1;
    sketch.Efdata[0].index = efnum; // 索引
    get_effect_detail(&efdata, sketch.Efdata[0].index);
    sketch.Efdata[0].namelenght = efdata.namelenght;
    memcpy(&sketch.Efdata[0].Name, &efdata.Name, sizeof(sketch.Efdata[0].Name));                             // 名字
    sketch.Efdata[0].Attribute = efdata.Attribute;                                                           // 属性
    sketch.Efdata[0].EffectType = efdata.EffectType;                                                         // 类型
    memcpy(&sketch.Efdata[0].EfColormioniInf, &efdata.EfColorInf, sizeof(sketch.Efdata[0].EfColormioniInf)); // 颜色
    sketch.checksum = (uint8_t)checksum_calculate((uint8_t *)&sketch, sizeof(sketch) - 1);
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
        get_effect_detail(&efdata, sketch.Efdata[i].index);
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
    get_allef_ranklist((ef_ranklist_TypeDef *)&com_ranklist.ranklist);
    printlog(">mcu_update_allef_ranklist:%d\r",com_ranklist.ranklist.num);
    com_ranklist.checksum = (uint8_t)checksum_calculate((uint8_t *)&com_ranklist, (uint16_t)sizeof(com_ranklist) - 1);
    mcu_dp_raw_update(DPID_ALL_EFFECT_RANKLIST, &com_ranklist, sizeof(com_ranklist));
    // printhex_my(&com_ranklist, sizeof(com_ranklist));
    print_ef_ranklist(&com_ranklist.ranklist);
}
/*mcu上报自定义灯效的顺序表*/
void mcu_update_originalef_ranklist(void)
{
    com_ranklist_TypeDef com_ranklist;
    
    get_originalef_ranklist((ef_ranklist_TypeDef *)&com_ranklist.ranklist);
    com_ranklist.checksum = (uint8_t)checksum_calculate((uint8_t *)&com_ranklist, (uint16_t)sizeof(com_ranklist) - 1);
    printlog(">mcu_update_originalef_ranklist:%d\r",com_ranklist.ranklist.num);
    mcu_dp_raw_update(DPID_ORIGINAL_EFFECT_RANKLIST, &com_ranklist, sizeof(com_ranklist));
    print_ef_ranklist(&com_ranklist.ranklist);
    // // // printhex_my(&com_ranklist,sizeof(com_ranklist.ranklist));
}
/*mcu上报收藏灯效的顺序表*/
void mcu_update_favoritesef_ranklist(void)
{
    com_ranklist_TypeDef com_ranklist;
    printlog(">mcu_update_favoritesef_ranklist:%d\r",com_ranklist.ranklist.num);
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

/* 
 * @Description: 上报某个“播放列表详情”
 * @param: 
 * @return: 
*/ 
void mcu_update_playdetail(uint8_t playnum)
{
    com_play_detial_TypeDef com;
    printlog("mcu_update_playdetail:%d\r",playnum);
    get_playdetail(&com.pldata, playnum);
    com.idex = playnum;
    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_PLAY_DETIAL, &com, sizeof(com));
    // print_playdetial(&com.pldata, com.idex);
}

/* 
 * @Description: 上报当前正在播放的“播放列表详情”
 * @param: 
 * @return: 
*/ 
void mcu_update_current_playdetail(void)
{
    com_play_detial_TypeDef com;
    if (play.source == SOURCE_LIST)
    {
        printlog("mcu_update_current_playdetail:%d\r", play.detail.listindex);
        get_playdetail(&com.pldata, play.detail.listindex);
        com.idex = play.detail.listindex;
    }
    else
    {
        printlog("mcu_update_current_playdetail -> not in list play\r");
        memset(&com, 0, sizeof(com));
    }
    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_PLAY_CONTROL_DETIAL, &com, sizeof(com));
    // // // // printhex_my(&com, sizeof(com));
    // print_playdetial(&com.pldata, com.idex);
}


/* 
 * @Description: mcu上报播放状态
 * @param: 
 * @return: 
*/ 
void mcu_update_playstatus(void)
{
    com_play_control_TypeDef com;
    printlog("mcu_update_playstatus\r");
    com.type = PLAY_STATUS;// 播放/暂停
    com.value = play.status;
    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_PLAY_CONTROL, &com, sizeof(com));
    com.type = PLAYLIST_INDEX;// 播放列表索引
    com.value = play.detail.listindex;
    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_PLAY_CONTROL, &com, sizeof(com));
    com.type = EFFECT_INDEX;// 效果索引
    com.value = play.detail.efindex;
    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_PLAY_CONTROL, &com, sizeof(com));
    com.type = PLAY_RANDOM_EN;// 随机播放使能
    com.value = play.playmode;
    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_PLAY_CONTROL, &com, sizeof(com));
}
/*-------------------------------------------------------------*/

/* 
 * @Description: 设备形状信息按照app格式进行转换
 * @param: 
 * @return: 
*/ 
app_shape_enum convert_device_shape_data(device_shape_enum shape)
{
    switch (shape)
    {
    case TRIANGLE_L:
        return APP_BTRIANGLE;
    case TRIANGLE_M:
        return APP_MTRIANGLE;
    case TRIANGLE_S:
        return APP_STRIANGLE;
    case SQUARE:
        return APP_SQUARE;
    default:
        return 0;
    }
}

/*
 * @Description: 下载设备信息
 * @param:
 * @param:
 * @return:
 */
void mcu_download_device_detail(uint8_t *sur, uint16_t length)
{
    uint8_t i, j;
    com_device_detail_TypeDef com;
    device_detail_TypeDef device;
    uint16_t data;
    printlog("<mcu_download_device_detail>\r");
    j = length / sizeof(com_device_detail_TypeDef); // 算出设备数量
    for (i = 0; i < j; i++)
    {
        memset(&device, 0, sizeof(device));
        memcpy(&com, sur + (sizeof(com) * i), sizeof(com));
        endian_swap(&device.cooed_x, &com.cooed_x, sizeof(device.cooed_x)); // 大小端转换
        endian_swap(&device.cooed_y, &com.cooed_y, sizeof(device.cooed_y)); // 大小端转换
        refresh_slave_data(&device);
    }
    save_all_slave_data(&slave);
    reset_all_built_in_static_effect(); // 每次更新坐标信息，都重设内置静态灯效颜色数据
    print_slave_data();
    /* 上传顺序表，触发app重新查询所有灯效概述 */
    mcu_update_allef_ranklist();
    mcu_update_originalef_ranklist();
    mcu_update_favoritesef_ranklist();
    //
    // // // // enter_playing_effect_mode();    // 进入正常播放灯效模式
}

/* 
 * @Description:  上报设备信息
 * @param: 
 * @return: 
*/ 
void mcu_update_device_detail(void)
{
    uint8_t i, j;
    com_device_data_TypeDef com;
    printlog("mcu_update_device_detail\r");
    memset(&com, 0, sizeof(com));
    for (i = 0; i < slave.num; i++)
    {
        com.data[i].id = slave.data[i].id;
        com.data[i].shape = convert_device_shape_data(slave.data[i].shape);
        com.data[i].angle = slave.data[i].angle;
        endian_swap(&com.data[i].cooed_x, &slave.data[i].cooed_x, sizeof(com. data[i].cooed_x)); // 大小端转换
        endian_swap(&com.data[i].cooed_y, &slave.data[i].cooed_y, sizeof(com.data[i].cooed_y)); // 大小端转换
        com.data[i].cooed_x = slave.data[i].cooed_x;
        com.data[i].cooed_y = slave.data[i].cooed_y;
    }
    printlog("slave.num:%d\r",slave.num);
    // printhex_my(&com, (slave.num * sizeof(com_device_detail_TypeDef)));
    mcu_dp_raw_update(DPID_DEVICE_DETAIL, &com, (slave.num * sizeof(com_device_detail_TypeDef))); // RAW型数据上报;
}

/*-------------------------------------------------------------*/

/******************************************************************************************************************************************************/
/*






























*/


/*针对DPID_EFFECT_DETIAL的处理函数*/
uint8_t mcu_download_effect_detail_handle(uint8_t *sur, uint16_t length)
{
    printlog("<mcu_download_effect_detail_handle>\r");
    if (com_dataverify(sur, length) == 0)
    {
        return 0;
    }
    print_com_effect_detial_log(sur); // 打印log
    if ((uint8_t)(((com_effect_detial_TypeDef *)sur)->idex) < original_ef_basenum)
    { /* 内置原生灯效 */
        update_built_in_effect((Efdetail_TypeDef *)(&((com_effect_detial_TypeDef *)sur)->Efdata), (uint8_t)(((com_effect_detial_TypeDef *)sur)->idex));
    }
    else
    { /* 自定义灯效 */
        add_original_ef((Efdetail_TypeDef *)(&((com_effect_detial_TypeDef *)sur)->Efdata), (uint8_t)(((com_effect_detial_TypeDef *)sur)->idex));
    }
    mcu_update_allef_ranklist();
    mcu_update_originalef_ranklist();
    mcu_update_favoritesef_ranklist();
    if (play.detail.efindex == (uint8_t)(((com_effect_detial_TypeDef *)sur)->idex)) 
    {
        play_current_effect();  // 当前播放灯效被修改，则需重新加载灯效信息
    }


    return 1;
}

/*针对DPID_ISSUE_CMD的处理函数*/
uint8_t mcu_download_issue_cmd_handle(uint8_t *sur, uint16_t length)
{
    com_issue_cmd_TypeDef *p;
    // // printlog(">mcu_download_issue_cmd_handle<\r");
    if (com_dataverify(sur, length) == 0)
    {
        return 0;
    }
    p = (com_issue_cmd_TypeDef *)sur;
    switch (p->cmd)
    {
    case ASK_EFSKETCH: /*效果概述*/
        printlog(" >> ASK_EFSKETCH\r");
        mcu_update_efsketch(p);
        break;
    case ASK_EFDETAIL: /*效果详情*/
        printlog(" >> ASK_EFDETAIL\r");
        mcu_update_ef_detail(p->data[0]); // mcu上报灯效详情
        break;
    case DELETE_ORIGINAL_EF: /*删除自定义灯效*/
        printlog("DELETE_ORIGINAL_EF\r");
        delete_original_ef(p->data[0]);
        mcu_update_allef_ranklist();
        mcu_update_originalef_ranklist();
        mcu_update_favoritesef_ranklist();
        // // // // // // // mcu_update_originalef_ranklist();
        break;
    case ADD_FAVORITES_EF: /*加入收藏*/
        printlog(" >> ADD_FAVORITES_EF\r");
        add_favorites_ef(p->data[0]);
        // // mcu_update_allef_ranklist();
        // // mcu_update_originalef_ranklist();
        mcu_update_favoritesef_ranklist();
        mcu_update_one_efsketch(p->data[0]);
        break;
    case DELETE_FAVORITES_EF: /*取消收藏*/
        printlog(" >> DELETE_FAVORITES_EF\r");
        delete_favorites_ef(p->data[0]);
        // // mcu_update_allef_ranklist();
        // // mcu_update_originalef_ranklist();
        mcu_update_favoritesef_ranklist();
        mcu_update_one_efsketch(p->data[0]);
        break;
    case ASK_ALLEFRANKLIST: /*请求全部灯效的顺序表*/
        printlog(" >> ASK_ALLEFRANKLIST\r");
        mcu_update_allef_ranklist();
        break;
    case ASK_ORINGINAL_RANKLIST: /*请求自定义灯效的顺序表*/
        printlog(" >> ASK_ORINGINAL_RANKLIST\r");
        mcu_update_originalef_ranklist();
        break;
    case ASK_FAVORITES_RANKLIST: /*请求收藏灯效的顺序表*/
        printlog(" >> ASK_FAVORITES_RANKLIST\r");
        mcu_update_favoritesef_ranklist();
        break;
    case ASK_PLAYLIST_RANKLIST: /*请求播放列表的顺序表*/
        printlog(" >> ASK_PLAYLIST_RANKLIST\r");
        mcu_update_playlist_ranklist();
        break;
    case ASK_EFFECT_RANKLIST: /*请求灯效相关的顺序表*/
        printlog(" >> ASK_EFFECT_RANKLIST\r");
        mcu_update_allef_ranklist();
        mcu_update_originalef_ranklist();
        mcu_update_favoritesef_ranklist();
        break;
    case ASK_PLAY_EFSKETCH: /*请求效果概述*/
        printlog(" >> ASK_PLAY_EFSKETCH\r");
        mcu_update_playlist_efsketch(p);
        break;
    case REAERVE_CMD11: /*保留*/
        break;
    case DELETE_PLAYLIST_RANKLISTLIST: /*删除播放列表中某个详情表*/
        /* 与23（DELETE_PLAYLIST）重复*/
        // // // printlog(" >> DELETE_PLAYLIST_RANKLISTLIST\r");
        // // // delete_playlist(p->data[0]);
        // // // mcu_update_playlist_ranklist();
        break;
    case SWITCH_PLAYLIST: /*切换播放列表*/
        printlog(" >> SWITCH_PLAYLIST\r");
        switch_playlist(p->data[0]);
        break;
    case ASK_PLAYDETAIL: /*请求播放详情*/
        printlog(" >> ASK_PLAYDETAIL\r");
        mcu_update_playdetail(p->data[0]); // 上报某个“播放列表详情”
        break;
    case ASK_PLAYSTATUS: /*请求播放状态*/
        printlog(" >> ASK_PLAYSTATUS\r");
        mcu_update_playstatus(); // 自动上报播放状态
        break;
    case DELETE_SCHEDULE: /*删除定时计划*/
        printlog(" >> DELETE_SCHEDULE\r");
        delete_schedule(p->data[0]);
        mcu_update_clock_list();
        break;
    case ASK_SCHEDULE_DETAIL: /*请求定时详情*/
        printlog(" >> ASK_SCHEDULE_DETAIL\r");
        mcu_update_clock_detial(p->data[0]);
        break;
    case INTER_APPCONNTROL: /*进入app控制*/
        printlog(" >> INTER_APPCONNTROL\r");
        enter_device_pairing_mode(); // 进入灯板配对模式
        turn_off_all_salve_light();  // 关闭所有灯光
        // mcu_update_device_detail();
        // print_slave_data();
        break;
    case EXIT_APPCONNTROL: /*退出app控制*/
        printlog(" >> EXIT_APPCONNTROL\r");
        enter_playing_effect_mode(); // 进入正常播放灯效模式
        break;
    case ASK_SCHEDULE_SKETCH: /*请求定时计划表*/
        printlog(" >> ASK_SCHEDULE_SKETCH\r");
        mcu_update_clock_list();
        break;
    case PLAY_TEMP_EFFECT: /*播放临时灯效*/
        printlog(" >> PLAY_TEMP_EFFECT\r");
        play_free_effect(p->data[0]);
        mcu_update_current_playdetail(); // 上报当前正在播放的“播放列表详情”
        mcu_update_playstatus();         // 自动上报播放状态
        break;
    case RESET_BUILTIN_EF: /* 重置内置灯效 */
        printlog(" >> RESET_BUILTIN_EF\r");
        reset_built_in_effect(p->data[0]);
        mcu_update_one_efsketch(p->data[0]);
        mcu_update_ef_detail(p->data[0]); // mcu上报灯效详情
        break;

    case DELETE_PLAYLIST: // 删除播放列表
        printlog(" >> DELETE_PLAYLIST\r");
        delete_playlist(p->data[0]);
        reload_current_play_list();
        mcu_update_playlist_ranklist();  // 上传新的总表
        mcu_update_current_playdetail(); // 上报当前正在播放的“播放列表详情”
        break;
    case ASK_DEVICE_DETAILS: // 请求灯板信息
        mcu_update_device_detail();
        print_slave_data();
        break;
    case ASK_DEVICE_IDENTIFY: // 请求配对标识
        mcu_update_device_indentify();
        break;
    default:
        printlog(" >> [error] wrong command num:%d\r", p->cmd);
        printAssert();
        break;
    }
    return 1;
}
/*针对DPID_EFFECT_PREVIEW的处理函数*/
void mcu_download_effect_preview(uint8_t *sur, uint16_t length)
{
    printlog("\r<effect_preview>\r");
    print_com_effect_detial_log(sur); // 打印log
    enter_preview_effect_mode(&(((com_effect_detial_TypeDef*)sur)->Efdata));
}

/*针对DPID_PLAY_DETIAL的处理函数*/
uint8_t mcu_download_play_detial(uint8_t *sur, uint16_t length)
{
    printlog("<mcu_download_play_detial>\r");
    if (com_dataverify(sur, length) == 0)
    {
        return 0;
    }
    add_playlist((playdetail_TypeDef *)(&((com_play_detial_TypeDef *)sur)->pldata), (uint8_t)(((com_play_detial_TypeDef *)sur)->idex));
    print_com_playdetial(sur);
    if ((uint8_t)(((com_play_detial_TypeDef *)sur)->idex) == play.detail.listindex)
    {
        reload_current_play_list(); // 当前播放列表有变动，则重新加载
    }
    mcu_update_playlist_ranklist();
    return 1;
}
/*--------------------------------------------------------------------------------------------------------------------------
*/

/* 
 * @Description: 下载播放控制详情
 * @param: 
 * @param: 
 * @return: 
*/ 
uint8_t mcu_download_play_control_detial(uint8_t *sur, uint16_t length)
{
    printlog("<mcu_download_play_control_detial>\r");
    if (com_dataverify(sur, length) == 0)
    {
        return 0;
    }
    switch (((com_play_control_TypeDef *)sur)->type)
    {
    case PLAY_STATUS: // 播放/暂停
        printlog(">PLAY_STATUS\r");
        play.status = (playstatus_enum)(((com_play_control_TypeDef *)sur)->value);

        break;
    case PLAY_SWITCH: // 上下曲切换
        printlog(">PLAY_SWITCH\r");
        switch_lastnext_effect((switchplay_enum)(((com_play_control_TypeDef *)sur)->value));
        break;
    case EFFECT_INDEX: // 效果索引
        printlog(">EFFECT_INDEX\r");
        break;
    case PLAY_RANDOM_EN: //  随机播放使能
        printlog(">PLAY_RANDOM_EN\r");
        switch_playmode((PlayMode_enum)(((com_play_control_TypeDef *)sur)->value));   
        break;
     case PLAY_LOOP_EN:     // 循环播放使能
        printlog(">PLAY_LOOP_EN\r");
        switch_cyclemode((PlayMode_enum)(((com_play_control_TypeDef *)sur)->value));
        break;
    case PLAYLIST_INDEX: // 播放列表索引
        printlog(">PLAYLIST_INDEX\r");
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

/* 
 * @Description: 上传播放控制详情
 * @param: 
 * @param: 
 * @return: 
*/ 
void mcu_update_play_control_detial(playcontrol_type_enum type, uint8_t value)
{
    com_play_control_TypeDef com;
    com.type = type;
    com.value = value;
    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_PLAY_CONTROL, value, sizeof(com));
}

/* 
 * @Description: 上传当前播放的灯效索引
 * @param: 
 * @return: 
*/ 
void mcu_update_current_play_ef_index(void)
{
    mcu_update_play_control_detial(EFFECT_INDEX,play.detail.efindex);
}

// // /* 
// //  * @Description: 上传当前播放状态
// //  * @param: 
// //  * @return: 
// // */ 
// // void mcu_update_current_play_status(void)
// // {
// //     mcu_update_play_control_detial(PLAY_STATUS,play.status);
// // }


/*--------------------------------------------------------------------------------------------------------------------------
*/


/*针对DPID_DEVICE_CONTROL的处理函数*/
uint8_t mcu_download_device_control(uint8_t *sur, uint16_t length)
{
    // // com_device_control_TypeDef* p;
    color_TypeDef color;
    uint8_t i;
    printlog("<mcu_download_device_control>\r");
    enter_device_pairing_mode(); // 进入灯板配对模式
    light_device_pairing_play((app_device_control_Typedef*)sur);
    // print_device_control((app_device_control_Typedef*)sur);
    
    // if (com_dataverify(sur, length) == 0)
    // {
    //     return 0;
    // }
    // printhex_my(sur, length);
    // p = (com_device_control_TypeDef *)sur;

    // printlog("id:%d\r",((com_device_control_TypeDef *)sur)->data[0].id);

    // light_up_only_one_slave(((com_device_control_TypeDef *)sur)->data[0].id);
    // for (i = 0; i < p->num; i++)
    // {
    //     color.brightness = p->data[i].brightness;
    //     color.R = p->data[i].R;
    //     color.G = p->data[i].G;
    //     color.B = p->data[i].B;
    //     color.W = p->data[i].W;
    //     refresh_device_color(&color, p->data[i].id);
    // }
    // // print_slave_color();

    return 1;
}

/*




*/
/*在线下载固件*/
void mcu_firmware_download(uint8_t *sur, uint16_t position, uint16_t length)
{
    static uint32_t packsum = 0; // 升级包校验和
    uint32_t chechsum;
    sys.sta.firmware_dowmload = 1;
    if (length == 0)
    {
        // 固件数据发送完成
        chechsum = get_firmware_chechsum_norflash();
        printlog("package sum is 0x%04x,norflash firmware chechsum:0x%04x\r", packsum, chechsum);
        if (packsum == chechsum) // 校验存储数据是否与升级包一致
        {
            set_firmware_update_flag(packsum);   // 设标志,通知bootload升级固件
            set_firmware_download_finish_flag(); // 设置固件下载完成标志
            /* 重启*/
            printlog("\rsystem restart..\r\n");
            __NVIC_SystemReset();
            /*
            if (check_firmware_update())
            {
                printlog("firmware is correct\r\n");
            }
            else
            {
                printlog("firmware is error\r\n");
            }
            */
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
            set_firmware_downloading_flag();       // 设置固件下载中标志
        }
        download_firmware_to_norflash(sur, position); // 下载固件包
        packsum += checksum_calculate(sur, 256);      // 累计校验和
    }
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

/*-------------------------------------------------------------*/
/* 
 * @Description: 下载指示灯开关状态
 * @param: 
 * @return: 
*/ 
void mcu_download_switch_indicator(uint8_t bool)
{
    printlog("mcu_download_switch_indicator:%d\r", bool);
    if (bool == DISABLE_STA)
    {
        play.work.global_setting.indicator_sta = DISABLE_STA; // 失能状态
    }
    else
    {
        play.work.global_setting.indicator_sta = ENABLE_STA; //使能状态
    }
    save_global_setting(&play.work.global_setting);
}

/* 
 * @Description: 上传指示灯开关状态
 * @param: 
 * @return: 
*/ 
void mcu_update_switch_indicator(void)
{
    printlog("mcu_update_switch_indicator:%d\r", play.work.global_setting.indicator_sta);
    mcu_dp_bool_update(DPID_SWITCH_INDICATOR,play.work.global_setting.indicator_sta); //BOOL型数据上报;
}
/*-------------------------------------------------------------*/

/*
 * @Description: 下载麦克风开关状态
 * @param:
 * @return:
 */
void mcu_download_switch_mic(uint8_t bool)
{
    printlog("mcu_download_switch_mic:%d\r", bool);
    if (bool == DISABLE_STA)
    {
        play.work.global_setting.microphone_ensta = DISABLE_STA; // 失能状态
    }
    else
    {
        play.work.global_setting.microphone_ensta = ENABLE_STA; // 使能状态
    }
    save_global_setting(&play.work.global_setting);
}

/*
 * @Description: 上传麦克风开关状态
 * @param:
 * @return:
 */
void mcu_update_switch_mic(void)
{
    printlog("mcu_update_switch_mic:%d\r", play.work.global_setting.microphone_ensta);
    mcu_dp_bool_update(DPID_SWITCH_MIC, play.work.global_setting.microphone_ensta); // BOOL型数据上报;
}
/*-------------------------------------------------------------*/

/*
 * @Description: 下载全局亮度
 * @param: 无
 * @return: 无
 */
void mcu_download_bright_val(uint8_t bri)
{
    printlog("mcu_download_bright_val:%d\r", bri);

}

/*
 * @Description: 上传全局亮度
 * @param:
 * @return:
 */
void mcu_update_bright_val(void)
{
    // printlog("mcu_update_bright_val:%d\r", play.work.global_setting.brightness_set);
    // mcu_dp_value_update(DPID_BRIGHT_VAL, play.work.global_setting.brightness_set); // VALUE型数据上报;
}

/*---------------------------------------------------------------------------------*/

/* 
 * @Description: 下载自动亮度的开关
 * @param: 
 * @return: 
*/ 
void mcu_download_auto_brightness_switch(uint8_t bool)
{
    printlog("mcu_download_auto_brightness_switch:%d\r", bool);
    if (bool == DISABLE_STA)
    {
       play.work.global_setting.autobright_ensta  = DISABLE_STA; // 失能状态
    }
    else
    {
        play.work.global_setting.autobright_ensta  = ENABLE_STA; // 使能状态
    }
    save_global_setting(&play.work.global_setting);
}

/* 
 * @Description: 上传自动亮度的开关状态
 * @param: 
 * @return: 
*/ 
void mcu_update_auto_brightness_switch(void)
{
    printlog("mcu_update_auto_brightness_switch:%d\r", play.work.global_setting.autobright_ensta);
    mcu_dp_bool_update(DPID_AUTO_BRIGHTNESS_SWITCH,play.work.global_setting.autobright_ensta);
}

/* 
 * @Description: 修改自动亮度开关
 * @param: 
 * @return: 
*/ 
void modify_auto_brightness_switch(enable_status_enum en)
{
    if (en == DISABLE_STA)
    {
       play.work.global_setting.autobright_ensta  = DISABLE_STA; // 失能状态
    }
    else
    {
        play.work.global_setting.autobright_ensta  = ENABLE_STA; // 使能状态
    }
    save_global_setting(&play.work.global_setting);
    mcu_update_auto_brightness_switch();    // 上传自动亮度的开关状态
}

/*---------------------------------------------------------------------------------*/
/* 
 * @Description: 下载自动亮度的模式
 * @param: 
 * @return: 
*/ 
void mcu_download_auto_brightness_mode(uint8_t num)
{
    printlog("mcu_download_auto_brightness_mode:%d\r", num);
    if (num == Illumination)
    {
       play.work.global_setting.autobrightType  = Illumination; // 负反馈自动亮度.照明
    }
    else
    {
        play.work.global_setting.autobrightType  = Ambient; // 正反馈自动亮度.环境
    }
    save_global_setting(&play.work.global_setting);
}

/* 
 * @Description: 上传自动亮度的模式
 * @param: 
 * @return: 
*/ 
void mcu_update_auto_brightness_mode(void)
{
    printlog("mcu_update_auto_brightness_switch:%d\r", play.work.global_setting.autobrightType);
    mcu_dp_enum_update(DPID_AUTO_BRIGHTNESS_MODE, play.work.global_setting.autobrightType);
}


/* 
 * @Description: 下载自动亮度界面内的亮度值
 * @param: 
 * @param: 
 * @return: 
*/ 
void mcu_download_brightness_auto(uint8_t bright)
{
    // // // printlog("mcu_download_brightness_auto:%d\r",bright);
    // // // play.work.global_setting.brightness_set = bright;
    // // // save_global_setting(&play.work.global_setting);
}

/* 
 * @Description: 上传自动亮度界面内的亮度值
 * @param: 
 * @param: 
 * @return: 
*/ 
void mcu_update_brightness_auto(void)
{
// // //    printlog("mcu_update_brightness_auto:%d\r",play.work.global_setting.brightness_set);
// // //    mcu_dp_value_update(DPID_BRIGHTNESS_AUTO, play.work.global_setting.brightness_set); // VALUE型数据上报;
}




/*---------------------------------------------------------------------------------*/
/* 
 * @Description: 下载闹钟计划概述表
 * @param: 
 * @param: 
 * @return: 
*/ 
void mcu_download_clock_list(uint8_t *sur, uint16_t length)
{
   // com_schedule_sketchlist_TypeDef  com;
   clock_list_TypeDef schedule;
   uint8_t i;
   printlog("<mcu_download_clock_list>\r");
   if (com_dataverify(sur, length) == 0)
   {
        return 0;
   }
   get_all_schedule(&schedule);
   if (((com_schedule_sketchlist_TypeDef *)sur)->num == schedule.num)
   {
        for (i = 0; i < schedule.num; i++)
        {
            schedule.list[i].en_sta = ((com_schedule_sketchlist_TypeDef *)sur)->list[i].en_sta; // 更新启用状态
            /*
            schedule.list[i].en_sta = ((com_schedule_sketchlist_TypeDef *)sur)->list[i].en_sta;                       // 启用状态
            schedule.list[i].action = ((com_schedule_sketchlist_TypeDef *)sur)->list[i].action;                       // 动作类型
            schedule.list[i].actiontime.hou_HM = ((com_schedule_sketchlist_TypeDef *)sur)->list[i].actiontime.hou_HM; // 动作时间
            schedule.list[i].actiontime.min_HM = ((com_schedule_sketchlist_TypeDef *)sur)->list[i].actiontime.min_HM; // 动作时间
            schedule.list[i].repeat.week = ((com_schedule_sketchlist_TypeDef *)sur)->list[i].repeat.week;             // 星期计划
            */
        }
   }
   save_all_schedule(&schedule);
// //    mcu_update_clock_list();
   // printlog("com_dataverify pass\r");
   // printhex_my(sur, length);
}

/* 
 * @Description: 上传闹钟计划概述表
 * @param: 
 * @return: 
*/ 
void mcu_update_clock_list(void)
{
    com_schedule_sketchlist_TypeDef  com;
    clock_list_TypeDef schedule;
    uint8_t i;
    printlog("mcu_update_clock_list\r");
    get_all_schedule(&schedule);
    memset(&com, 0, sizeof(com));
    if (schedule.num > SCHEDULE_NUM)
    {
        schedule.num = SCHEDULE_NUM;
        printlog("[error] schedule num is too big:%d\r",schedule.num);
    }

    com.num = schedule.num;
    for (i = 0; i < schedule.num; i++)
    {
        com.list[i].index = i;
        com.list[i].en_sta = schedule.list[i].en_sta;                       // 启用状态
        com.list[i].action = schedule.list[i].action;                       // 动作类型
        com.list[i].actiontime.hou_HM = schedule.list[i].actiontime.hou_HM; // 动作时间
        com.list[i].actiontime.min_HM = schedule.list[i].actiontime.min_HM; // 动作时间
        com.list[i].repeat.week = schedule.list[i].repeat.week;             // 星期计划
    }

    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_CLOCK_LIST, &com, sizeof(com));
}



/*---------------------------------------------------------------------------------*/
/* 
 * @Description: 上传闹钟详情
 * @param: 
 * @return: 
*/ 
void mcu_update_clock_detial(uint8_t num)
{
    com_schedule_detail_TypeDef com;
    clock_detail_TypeDef schedule_detail;
    printlog("mcu_update_clock_detial\r");
    memset(&com, 0, sizeof(com));
    get_schedule_detail(&schedule_detail, num);
    com.index = num;
    copy_schedule_detail_to_com(&schedule_detail, &com);
    com.checksum = (uint8_t)checksum_calculate((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_CLOCK_DETIAL, &com, sizeof(com));
}

/* 
 * @Description: 下载闹钟详情
 * @param: 
 * @param: 
 * @return: 
*/ 
uint8_t mcu_download_clock_detial(uint8_t *sur, uint16_t length)
{
    clock_detail_TypeDef schedule_detail;
    printlog("<mcu_download_clock_detial>\r");
    // // // printhex_my(sur, length);
    copy_schedule_detail_from_com((com_schedule_detail_TypeDef *)sur, &schedule_detail);
    print_clock_detial(&schedule_detail);
    add_clock_schedule(&schedule_detail, ((com_schedule_detail_TypeDef *)sur)->index);
    mcu_update_clock_list();
    // print_all_clock_detail();
}


/*---------------------------------------------------------------------------------*/




/*
 * @Description: 上传设备配对标识
 * @param:
 * @return:
 */
void mcu_update_device_indentify(void)
{
    device_indentify_TypeDef buff;
    get_device_identify(&buff);
    mcu_dp_raw_update(DPID_RESERVED3, &buff.data, buff.length);
}

/*
 * @Description: 下载设备配对标识
 * @param:
 * @return:
 */
void mcu_download_device_indentify(uint8_t *sur, uint16_t length)
{
    device_indentify_TypeDef buff;
    buff.length = length;
    memcpy(&buff.data, sur, length);
    save_device_identify(&buff);
}

/* 
 * @Description: 下载DP数据（保留3）
 * @param: 
 * @param: 
 * @return: 
*/ 
void mcu_download_reserved3(uint8_t *sur, uint16_t length)
{
    printlog("mcu_download_device_indentify:%d\r",length);
    mcu_download_device_indentify(sur, length);
}
/*-------------------------------------------------------------------------*/

/*
 * @Description: 上报当前播放的灯效信息
 * @param:
 * @return:
 */
void mcu_update_current_ef_detail(void)
{
    com_effect_detial_TypeDef comef;
    printlog("mcu_update_current_ef_detail\r");
    comef.idex = play.detail.efindex;
    memcpy(&comef.Efdata, &play.efdetail, sizeof(comef.Efdata));
    comef.checksum = (uint8_t)checksum_calculate((uint8_t *)&comef, sizeof(comef) - 1);
    mcu_dp_raw_update(DPID_RESERVED4, &comef, sizeof(comef));
    print_effect_detial(&comef.Efdata, comef.idex);
}

/* 
 * @Description: 上传dp信息（保留4）
 * @param: 
 * @return: 
*/ 
void mcu_update_reserved4(void) 
{
    mcu_update_current_ef_detail();
}

/*-------------------------------------------------------------------------*/

/* 
 * @Description: 上传播放的灯效的亮度信息
 * @param: 
 * @return: 
*/ 
void mcu_update_current_ef_brightness(void) 
{
    com_current_efbright_TypeDef com;
    printlog("mcu_update_current_ef_brightness\r");
    load_current_ef_brightness(); // 加载当前灯效的亮度
    com.efidex = play.detail.efindex;
    com.Brightness1 = play.efdetail.Brightness1;
    if (play.efdetail.EffectType != RHYTHM_TYPE)
    {
        com.Brightness2 = 101;  // 应app要求，非律动模式此值填101
    }
    else
    {
        com.Brightness2 = play.efdetail.Brightness2;
    }
    printhex_my(&com, sizeof(com));
    mcu_dp_raw_update(DPID_RESERVED5, &com, sizeof(com));
}
/* 
 * @Description: 下载灯效亮度信息
 * @param: 
 * @param: 
 * @return: 
*/ 
void mcu_download_ef_brightness(uint8_t *sur, uint16_t length)
{
    printlog("mcu_download_ef_brightness\r");
    modify_effect_brightness(((com_current_efbright_TypeDef *)sur)->efidex, ((com_current_efbright_TypeDef *)sur)->Brightness1, ((com_current_efbright_TypeDef *)sur)->Brightness2);
    if (((com_current_efbright_TypeDef *)sur)->efidex == play.detail.efindex) // 正常情况下，更新的就是当前播放的灯效
    {
        load_current_ef_brightness();               // 加载当前灯效的亮度
        modify_auto_brightness_switch(DISABLE_STA); // 关闭自动调光
    }
}

/* 
 * @Description: 下载DP信息（保留5）
 * @param: 
 * @param: 
 * @return: 
*/ 
void mcu_download_reserved5(uint8_t *sur, uint16_t length)
{
    mcu_download_ef_brightness(sur, length);
}

/*-------------------------------------------------------------------------*/

/* 
 * @Description: 日志上传服务器
 * @param: 
 * @return: 
*/ 
void log_to_server(LOG_CODE code)
{
    mcu_dp_raw_update(DPID_RESERVED10,&code,sizeof(LOG_CODE));
}
