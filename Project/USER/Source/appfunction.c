#include "appfunction.h"
#include "Function_Init.H"

/*У��ͨ�������Ƿ���ȷ*/
uint8_t com_dataverify(uint8_t *sur, uint16_t size)
{
    if ((uint8_t)CheckSum_Calu((uint8_t *)sur, size - 1) != *(sur + size - 1))
    { // У�����һ�ֽ��Ƿ�ΪУ���
        printlog("com data verify error\r");
        return 0;
    }
    return 1;
}


/*mcu�ϱ���Ч����*/
void mcu_update_efdetail(uint8_t efnum)
{
    com_effect_detial_TypeDef comef;
    comef.idex = efnum;
    get_effect(&comef.Efdata, efnum);
    comef.checksum = (uint8_t)CheckSum_Calu((uint8_t *)&comef, sizeof(comef) - 1);
    mcu_dp_raw_update(DPID_ISSUE_CMD, &comef, sizeof(comef));
}
/*mcu�ϱ���Ч����*/
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
        sketch.Efdata[i].index = p->data[i + 1]; // ����
        get_effect(&efdata, sketch.Efdata[i].index);

        memcpy(&sketch.Efdata[i].Name, &efdata.Name, sizeof(sketch.Efdata[i].Name));                             // ����
        sketch.Efdata[i].Attribute = efdata.Attribute;                                                           // ����
        sketch.Efdata[i].EffectType = efdata.EffectType;                                                         // ����
        memcpy(&sketch.Efdata[i].EfColormioniInf, &efdata.EfColorInf, sizeof(sketch.Efdata[i].EfColormioniInf)); // ��ɫ
        print_effect_sketch((Efminidetail_TypeDef *)&sketch.Efdata[i],sketch.Efdata[i].index);
    }
    sketch.checksum = (uint8_t)CheckSum_Calu((uint8_t *)&sketch, sizeof(sketch) - 1);
    // // // // printlog("mcu_dp_raw_update\r");
    // // // // printhex_my((uint8_t*)&sketch,sizeof(sketch));
    mcu_dp_raw_update(DPID_EFFECT_SKETCH, &sketch, sizeof(sketch));
}
/*mcu�ϱ�ȫ����Ч��˳���*/
void mcu_update_allef_ranklist(void)
{
    printlog("mcu_update_allef_ranklist\r");
    // // get_original_ranklist
    // // ef_ranklist_TypeDef
}
/*mcu�ϱ��Զ����Ч��˳���*/
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
/*mcu�ϱ��ղص�Ч��˳���*/
void mcu_update_favoritesef_ranklist(void)
{
    printlog("mcu_update_favoritesef_ranklist\r");
    // // // // // com_ef_ranklist_TypeDef ranklist;
    // // // // // get_original_ranklist((ef_ranklist_TypeDef *)&ranklist);
    // // // // // ranklist.checksum = (uint8_t)CheckSum_Calu(&ranklist, (uint16_t)sizeof(ranklist) - 1);
    // // // // // mcu_dp_raw_update(DPID_ORIGINAL_EFFECT_RANKLIST, &ranklist, sizeof(ranklist));
}
/******************************************************************************************************************************************************/
/*���DPID_SWITCH_LED�Ĵ�����*/
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

/*���DPID_EFFECT_DETIAL�Ĵ�����*/
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

/*���DPID_ISSUE_CMD�Ĵ�����*/
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
    case ASK_EFSKETCH: /*Ч������*/
        mcu_update_efsketch(p);
        printlog("mcu_update_efsketch\r");
        break;
    case ASK_EFDETAIL:                   /*Ч������*/
        mcu_update_efdetail(p->data[0]); // mcu�ϱ���Ч����
        printlog("mcu_update_efdetail\r");
        break;
    case DELETE_EF: /*ɾ��Ч��*/
        delete_original_ef(p->data[0]);
        printlog("delete_original_ef\r");
        break;
    case ADD_FAVORITES: /*�����ղ�*/
        break;
    case UNDO_FAVORITES: /*ȡ���ղ�*/
        break;
    case ASK_ALLEFRANKLIST: /*����ȫ����Ч��˳���*/
        mcu_update_allef_ranklist();
        // // // mcu_update_originalef_ranklist();
        printlog("mcu_update_allef_ranklist\r");
        break;
    case ASK_ORINGINALRANKLIST: /*�����Զ����Ч��˳���*/
        mcu_update_originalef_ranklist();
        printlog("mcu_update_originalef_ranklist\r");
        break;
    case ASK_FAVORITESRANKLIST: /*�����ղص�Ч��˳���*/
        mcu_update_favoritesef_ranklist();
        printlog("mcu_update_favoritesef_ranklist\r");
        break;
    case ASK_PLAYLISTRANKLIST: /*���󲥷��б��˳���*/
        printlog("mcu_update_playlist_ranklist\r");
        break;
    case ASK_EFFECTANKLIST: /*���󲥷��б��˳���*/
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
/*���DPID_EFFECT_PREVIEW�Ĵ�����*/
void mcu_download_effect_preview(uint8_t *sur, uint16_t length)
{
    printlog("effect_preview \r");
//    com_effect_detial_TypeDef p;
//    printlog("\r\r\r{effect_preview}\r\r");
//    memcpy(&p, value, sizeof(p));
//    if ((uint8_t)CheckSum_Calu(value, length - 1) == p.sum)
//    {
//        print_com_effect_detial_log(&p); // ��ӡlog
//    }
//    else
//    {
//        printlog("check sum err\r");
//        configASSERT(0);
//        printhex_my(value, length);
//    }
}
