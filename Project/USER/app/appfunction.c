#include "appfunction.h"
#include "Function_Init.H"

/*У��ͨ�������Ƿ���ȷ*/
uint8_t com_dataverify(uint8_t *sur, uint16_t size)
{
    if ((uint8_t)CheckSum_Calu((uint8_t *)sur, size - 1) != *(sur + size - 1))
    { // У�����һ�ֽ��Ƿ�ΪУ���
        printhex_my(sur, size);
        printlog("com data verify error\r\n");
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
    mcu_dp_raw_update(DPID_EFFECT_DETIAL, &comef, sizeof(comef));
}
/*mcu�ϱ���Ч����*/
void mcu_update_efsketch(com_issue_cmd_TypeDef *p)
{
    com_effect_sketch_TypeDef sketch;
    Efdetail_TypeDef efdata;
    memset(&sketch, 0, sizeof(sketch)); // ����
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
        sketch.Efdata[i].namelenght = efdata.namelenght;
        memcpy(&sketch.Efdata[i].Name, &efdata.Name, sizeof(sketch.Efdata[i].Name));                             // ����
        sketch.Efdata[i].Attribute = efdata.Attribute;                                                           // ����
        sketch.Efdata[i].EffectType = efdata.EffectType;                                                         // ����
        memcpy(&sketch.Efdata[i].EfColormioniInf, &efdata.EfColorInf, sizeof(sketch.Efdata[i].EfColormioniInf)); // ��ɫ
        // // print_effect_sketch((Efminidetail_TypeDef *)&sketch.Efdata[i],sketch.Efdata[i].index);
    }
    sketch.checksum = (uint8_t)CheckSum_Calu((uint8_t *)&sketch, sizeof(sketch) - 1);
    mcu_dp_raw_update(DPID_EFFECT_SKETCH, &sketch, sizeof(sketch));
    // // printlog("mcu_dp_raw_update\r");
    // // printhex_my((uint8_t*)&sketch,sizeof(sketch));
}
/*mcu�ϱ�ȫ����Ч��˳���*/
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
/*mcu�ϱ��Զ����Ч��˳���*/
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
/*mcu�ϱ��ղص�Ч��˳���*/
void mcu_update_favoritesef_ranklist(void)
{
    com_ranklist_TypeDef com_ranklist;
    printlog("mcu_update_favoritesef_ranklist\r");
    get_favoritesef_ranklist((ef_ranklist_TypeDef *)&com_ranklist.ranklist);
    com_ranklist.checksum = (uint8_t)CheckSum_Calu((uint8_t *)&com_ranklist, (uint16_t)sizeof(com_ranklist) - 1);
    mcu_dp_raw_update(DPID_FAVORITES_EFFECT_RANKLIST, &com_ranklist, sizeof(com_ranklist));
    print_ef_ranklist(&com_ranklist.ranklist);
}
/*mcu�ϱ������б��˳���*/
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
    com_ranklist.sum = ranklist.num; // ��ȡ�б����
    for (i = 0; i < com_ranklist.sum; i++)
    {
        com_ranklist.list[i].index = ranklist.list[i];                          // ����������
        get_playlist_name(&name, com_ranklist.list[i].index);                   // ��ȡ�б����������
        com_ranklist.list[i].name.length = name.length;                         // �������ֳ���
        memcpy(&com_ranklist.list[i].name.text, &name.text, sizeof(name.text)); // ��������
    }
    com_ranklist.checksum = (uint8_t)CheckSum_Calu((uint8_t *)&com_ranklist, (uint16_t)sizeof(com_ranklist) - 1);
    mcu_dp_raw_update(DPID_PLAY_LIST, &com_ranklist, sizeof(com_ranklist));
    print_com_playlist_ranklist(&com_ranklist);
}
/*mcu�ϱ���������*/
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
    add_original_ef((Efdetail_TypeDef *)(&((com_effect_detial_TypeDef *)sur)->Efdata), (uint8_t)(((com_effect_detial_TypeDef *)sur)->idex));
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
        printlog("ASK_EFSKETCH\r");
        mcu_update_efsketch(p);
        // printf("mcu update efsketch:%d [%3d] [%3d] [%3d] [%3d]\r",p->data[0],p->data[1],p->data[2],p->data[3],p->data[4]);
        // printlog("mcu_update_efsketch\r");
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
        add_favorites_ef(p->data[0]);
        printlog("add_favorites_ef\r");
        break;
    case DELETE_FAVORITES: /*ȡ���ղ�*/
        delete_favorites_ef(p->data[0]);
        printlog("delete_favorites_ef\r");
        break;
    case ASK_ALLEFRANKLIST: /*����ȫ����Ч��˳���*/
        printlog("ASK_ALLEFRANKLIST\r");
        mcu_update_allef_ranklist();
        break;
    case ASK_ORINGINALRANKLIST: /*�����Զ����Ч��˳���*/
        printlog("ASK_ORINGINALRANKLIST\r");
        mcu_update_originalef_ranklist();
        break;
    case ASK_FAVORITESRANKLIST: /*�����ղص�Ч��˳���*/
        printlog("ASK_FAVORITESRANKLIST\r");
        mcu_update_favoritesef_ranklist();
        break;
    case ASK_PLAYLISTRANKLIST: /*���󲥷��б��˳���*/
        printlog("ASK_PLAYLISTRANKLIST\r");
        mcu_update_playlist_ranklist();
        break;
    case ASK_EFFECTANKLIST: /*�����Ч��ص�˳���*/
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

/*���DPID_PLAY_DETIAL�Ĵ�����*/
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

/*�������ع̼�*/
void mcu_firmware_download(uint8_t *sur, uint16_t position, uint16_t length)
{
    static uint32_t checksum; // ������У���
    if (length == 0)
    {
        // �̼����ݷ������
        if (Download_checksum_verify(checksum)) // У��
        {
            printf("\rdownload finish!\r\n");
            printf("buffer checksum is 0x%04x\r", checksum);
            OTA_SetFlag(checksum);
            /* ����*/
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
        // �̼����ݴ���
        if (position == 0)
        {
            checksum = 0;
            printf("CheckSum init \r\n", checksum);
        }
        Download_app(position, sur);
        CheckSum_calculate(&checksum, sur);
    }
}
