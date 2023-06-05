#include "appfunction.h"
#include "Function_Init.H"

/*校验通信数据是否正确*/
uint8_t com_dataverify(uint8_t *sur, uint16_t size)
{
    if ((uint8_t)CheckSum_Calu((uint8_t *)sur, size - 1) != *(sur + size - 1))
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
    comef.checksum = (uint8_t)CheckSum_Calu((uint8_t *)&comef, sizeof(comef) - 1);
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
        // // print_effect_sketch((Efminidetail_TypeDef *)&sketch.Efdata[i],sketch.Efdata[i].index);
    }
    sketch.checksum = (uint8_t)CheckSum_Calu((uint8_t *)&sketch, sizeof(sketch) - 1);
    mcu_dp_raw_update(DPID_EFFECT_SKETCH, &sketch, sizeof(sketch));
    // // printlog("mcu_dp_raw_update\r");
    // // printhex_my((uint8_t*)&sketch,sizeof(sketch));
}
/*mcu上报全部灯效的顺序表*/
void mcu_update_allef_ranklist(void)
{
    com_ranklist_TypeDef com_ranklist;
    printlog("mcu_update_allef_ranklist\r");
    get_allef_ranklist((ef_ranklist_TypeDef *)&com_ranklist.ranklist);
    com_ranklist.checksum = (uint8_t)CheckSum_Calu((uint8_t *)&com_ranklist, (uint16_t)sizeof(com_ranklist) - 1);
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
    com_ranklist.checksum = (uint8_t)CheckSum_Calu((uint8_t *)&com_ranklist, (uint16_t)sizeof(com_ranklist) - 1);
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
    com_ranklist.checksum = (uint8_t)CheckSum_Calu((uint8_t *)&com_ranklist, (uint16_t)sizeof(com_ranklist) - 1);
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
    com_ranklist.checksum = (uint8_t)CheckSum_Calu((uint8_t *)&com_ranklist, (uint16_t)sizeof(com_ranklist) - 1);
    mcu_dp_raw_update(DPID_PLAY_LIST, &com_ranklist, sizeof(com_ranklist));
    print_com_playlist_ranklist(&com_ranklist);
}
/*mcu上报播放详情*/
void mcu_update_playdetail(uint8_t playnum)
{
    com_play_detial_TypeDef com;
    printlog("mcu_update_playdetail\r");
    get_playdetail(&com.pldata,playnum);
    com.checksum = (uint8_t)CheckSum_Calu((uint8_t *)&com, (uint16_t)sizeof(com) - 1);
    mcu_dp_raw_update(DPID_PLAY_DETIAL, &com, sizeof(com));
    print_playdetial(&com.pldata,playnum);
}

/******************************************************************************************************************************************************/
/*针对DPID_SWITCH_LED的处理函数*/
void mcu_download_switch_led(uint8_t sw)
{
    if (sw)
    {
        SYS.POWER_SW = 1;
    }
    else
    {
        SYS.POWER_SW = 0;
    }
}

/*针对DPID_EFFECT_DETIAL的处理函数*/
uint8_t mcu_download_effect_detail_handle(uint8_t *sur, uint16_t length)
{
    printlog("mcu_download_effect_detail_handle\r");
    if (com_dataverify(sur, sizeof(com_effect_detial_TypeDef)) == 0)
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
    printf("mcu_download_issue_cmd_handle\r");
    // // // // printhex_my(sur, length);
    if (com_dataverify(sur, sizeof(com_issue_cmd_TypeDef)) == 0)
    {
        return 0;
    }
    p = (com_issue_cmd_TypeDef *)sur;
    switch (p->cmd)
    {
    case ASK_EFSKETCH: /*效果概述*/
        printlog("ASK_EFSKETCH\r");
        mcu_update_efsketch(p);
        // printf("mcu update efsketch:%d [%3d] [%3d] [%3d] [%3d]\r",p->data[0],p->data[1],p->data[2],p->data[3],p->data[4]);
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
    case ASK_PLAYLISTRANKLISTLIST:
        printlog("ASK_PLAYLISTRANKLISTLIST\r");
        mcu_update_playlist_ranklist();
        break;
    case DELETE_PLAYLISTRANKLISTLIST:
        printlog("ASK_PLAYLISTRANKLISTLIST\r");
        delete_playlist(p->data[0]);
        break;
    case ASK_PLAYDETAIL:
        printlog("ASK_PLAYDETAIL\r");
        mcu_update_playdetail(p->data[0]);
        break;
    default:
        printlog("cmd err\r");
        printnumlog(p->cmd);
        configASSERT(0);
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
//    if ((uint8_t)CheckSum_Calu(value, length - 1) == p.sum)
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
void mcu_download_play_detial(uint8_t *sur, uint16_t length)
{
    com_play_detial_TypeDef com;
    printlog("mcu_download_play_detial \r");
    if (com_dataverify(sur, sizeof(com_play_detial_TypeDef)) == 0)
    {
        return 0;
    }
    print_com_playdetial(sur);
    add_playlist((playdetail_TypeDef *)(&((com_play_detial_TypeDef *)  sur)->pldata), (uint8_t)(((com_play_detial_TypeDef *)  sur)->idex));
    mcu_update_playlist_ranklist();
}

/*在线下载固件*/
void mcu_firmware_download(uint8_t *sur, uint16_t position, uint16_t length)
{
    static uint32_t checksum; // 升级包校验和
    if (length == 0)
    {
        // 固件数据发送完成
        if (Download_checksum_verify(checksum)) // 校验
        {
            printf("\rdownload finish!\r\n");
            printf("buffer checksum is 0x%04x\r", checksum);
            OTA_SetFlag(checksum);
            /* 重启*/
            printf("\rSystemReset\r\n");
            __NVIC_SystemReset();
        }
        else
        {
            printf("please restart !\r\n");
        }
    }
    else
    {
        // 固件数据处理
        if (position == 0)
        {
            checksum = 0;
            printf("CheckSum init \r\n", checksum);
        }
        Download_app(position, sur);
        CheckSum_calculate(&checksum, sur);
    }
}
