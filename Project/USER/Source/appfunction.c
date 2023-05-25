#include "appfunction.h"
#include "Function_Init.H"

/*校验通信数据是否正确*/
uint8_t com_dataverify(uint8_t *sur, uint16_t size)
{
    if ((uint8_t)CheckSum_Calu((uint8_t *)sur, size - 1) != *(sur + size - 1))
    { // 校验最后一字节是否为校验和
        printlog("com data verify error\r");
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
    mcu_dp_raw_update(DPID_ISSUE_CMD, &comef, sizeof(comef));
}
/*mcu上报灯效概述*/
void mcu_update_efsketch(com_issue_cmd_TypeDef *p)
{
    com_effect_sketch_TypeDef sketch;
    Efdetail_TypeDef efdata;
    memset(&sketch,0,sizeof(sketch));
    printlog("com_issue_cmd\r");
    // // // printhex_my((uint8_t*)p,sizeof(com_issue_cmd_TypeDef));
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

        memcpy(&sketch.Efdata[i].Name, &efdata.Name, sizeof(sketch.Efdata[i].Name));                             // 名字
        sketch.Efdata[i].Attribute = efdata.Attribute;                                                           // 属性
        sketch.Efdata[i].EffectType = efdata.EffectType;                                                         // 类型
        memcpy(&sketch.Efdata[i].EfColormioniInf, &efdata.EfColorInf, sizeof(sketch.Efdata[i].EfColormioniInf)); // 颜色
        print_effect_sketch((Efminidetail_TypeDef *)&sketch.Efdata[i],sketch.Efdata[i].index);
    }
    sketch.checksum = (uint8_t)CheckSum_Calu((uint8_t *)&sketch, sizeof(sketch) - 1);
    // // // // printlog("mcu_dp_raw_update\r");
    // // // // printhex_my((uint8_t*)&sketch,sizeof(sketch));
    mcu_dp_raw_update(DPID_EFFECT_SKETCH, &sketch, sizeof(sketch));
}
/*mcu上报全部灯效的顺序表*/
void mcu_update_allef_ranklist(void)
{
    printlog("mcu_update_allef_ranklist\r");
    // // get_original_ranklist
    // // ef_ranklist_TypeDef
}
/*mcu上报自定义灯效的顺序表*/
void mcu_update_originalef_ranklist(void)
{
    com_ef_ranklist_TypeDef ranklist;
    printlog("mcu_update_originalef_ranklist\r");
    get_original_ranklist((ef_ranklist_TypeDef *)&ranklist);
    ranklist.checksum = (uint8_t)CheckSum_Calu((uint8_t *)&ranklist, (uint16_t)sizeof(ranklist) - 1);
    // // // // print_ef_ranklist(&ranklist);
    // // // // printhex_my(&ranklist,sizeof(ranklist));
    mcu_dp_raw_update(DPID_ORIGINAL_EFFECT_RANKLIST, &ranklist, sizeof(ranklist));

}
/*mcu上报收藏灯效的顺序表*/
void mcu_update_favoritesef_ranklist(void)
{
    printlog("mcu_update_favoritesef_ranklist\r");
    // // // // // com_ef_ranklist_TypeDef ranklist;
    // // // // // get_original_ranklist((ef_ranklist_TypeDef *)&ranklist);
    // // // // // ranklist.checksum = (uint8_t)CheckSum_Calu(&ranklist, (uint16_t)sizeof(ranklist) - 1);
    // // // // // mcu_dp_raw_update(DPID_ORIGINAL_EFFECT_RANKLIST, &ranklist, sizeof(ranklist));
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
    // // // // // // printlog("log:received effct detail\r");
    // // // // // // print_effect_detial((Efdetail_TypeDef *)(&((com_effect_detial_TypeDef *)sur)->Efdata), (uint8_t)(((com_effect_detial_TypeDef *)sur)->idex));
    add_original_ef((Efdetail_TypeDef *)(&((com_effect_detial_TypeDef *)sur)->Efdata), (uint8_t)(((com_effect_detial_TypeDef *)sur)->idex));
    // // // // // // printlog("add_original_ef\r");
    // // // // // // print_get_ef_detial((uint8_t)(((com_effect_detial_TypeDef *)sur)->idex));
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
        mcu_update_efsketch(p);
        printlog("mcu_update_efsketch\r");
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
        break;
    case UNDO_FAVORITES: /*取消收藏*/
        break;
    case ASK_ALLEFRANKLIST: /*请求全部灯效的顺序表*/
        mcu_update_allef_ranklist();
        // // // mcu_update_originalef_ranklist();
        printlog("mcu_update_allef_ranklist\r");
        break;
    case ASK_ORINGINALRANKLIST: /*请求自定义灯效的顺序表*/
        mcu_update_originalef_ranklist();
        printlog("mcu_update_originalef_ranklist\r");
        break;
    case ASK_FAVORITESRANKLIST: /*请求收藏灯效的顺序表*/
        mcu_update_favoritesef_ranklist();
        printlog("mcu_update_favoritesef_ranklist\r");
        break;
    case ASK_PLAYLISTRANKLIST: /*请求播放列表的顺序表*/
        printlog("mcu_update_playlist_ranklist\r");
        break;
    case ASK_EFFECTANKLIST: /*请求播放列表的顺序表*/
        mcu_update_allef_ranklist();
        mcu_update_originalef_ranklist();
        mcu_update_favoritesef_ranklist();
        printlog("mcu_update_effect_ranklist\r");
        break;
    default:
        printlog("cmd err\r");
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
