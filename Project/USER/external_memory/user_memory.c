#include "user_memory.h"


// /*64k������Ч��������block��*/
// void EffectData_BlockErase_64k(void)
// {
//     uint32_t i;

// }

/*��norflash������ݽ��г�ʼ��*/
void norflash_data_init(void)
{
    printlog("norflash_data_init\r");
    printlog("search_norflash_ranklist\r");
    search_norflash_ranklist();            // ����flash�е��Զ���&�ղص�Ч˳���
    verify_ranklist();                     // У��˳����������Ƿ���ȷ
    verify_factoryreset_effect_norflash(); // ����Ƿ���Ҫ��ʼ���Դ���Ч
}

/*У��ȫ����Ч˳����������Ƿ���ȷ*/
uint8_t verify_allef_ranklist(void)
{
    ef_ranklist_TypeDef ranklist;
    uint8_t i;
    uint8_t err = 0;
    get_allef_ranklist(&ranklist); // ��ȡԭ��Ϣ
    if (ranklist.num > sizeof(ranklist.list))
    {
        printlog("ef ranklist num error\r");
        printnumlog(ranklist.num);
        err = 1;
    }
    else
    {
        for (i = ranklist.num; i < sizeof(ranklist.list); i++)
        {
            if (ranklist.list[i] != 0)
            {
                err = 1;
                printlog("verify allef ranklist error: not empty\r");
            }
        }
    }
    if (err)
    {
        memset(&ranklist, 0, sizeof(ranklist)); // ����
        save_allef_ranklist(&ranklist);
    }
    return err;
}
/*У���Զ����Ч˳����������Ƿ���ȷ*/
uint8_t verify_originalef_ranklist(void)
{
    ef_ranklist_TypeDef ranklist;
    uint8_t i;
    uint8_t err = 0;
    get_originalef_ranklist(&ranklist); // ��ȡԭ��Ϣ
    if (ranklist.num > sizeof(ranklist.list))
    {
        printlog("ef ranklist num error\r");
        printnumlog(ranklist.num);
        err = 1;
    }
    else
    {
        for (i = ranklist.num; i < sizeof(ranklist.list); i++)
        {
            if (ranklist.list[i] != 0)
            {
                err = 1;
                printlog("verify originalef ranklist error: not empty\r");
            }
        }
    }
    if (err)
    {
        memset(&ranklist, 0, sizeof(ranklist)); // ����
        save_originalef_ranklist(&ranklist);
    }
    return err;
}
/*У���Զ����Ч˳����������Ƿ���ȷ*/
uint8_t verify_favoritesef_ranklist(void)
{
    ef_ranklist_TypeDef ranklist;
    uint8_t i;
    uint8_t err = 0;
    get_favoritesef_ranklist(&ranklist); // ��ȡԭ��Ϣ
    if (ranklist.num > sizeof(ranklist.list))
    {
        printlog("ef ranklist num error\r");
        printnumlog(ranklist.num);
        err = 1;
    }
    else
    {
        for (i = ranklist.num; i < sizeof(ranklist.list); i++)
        {
            if (ranklist.list[i] != 0)
            {
                err = 1;
                printlog("verify favoritesef ranklist error: not empty\r");
            }
        }
    }
    if (err)
    {
        memset(&ranklist, 0, sizeof(ranklist)); // ����
        save_favoritesef_ranklist(&ranklist);
    }
    return err;
}
/*У���Զ����Ч˳����������Ƿ���ȷ*/
uint8_t verify_playlist_ranklist(void)
{
    playlist_ranklist_TypeDef ranklist;
    uint8_t i;
    uint8_t err = 0;
    get_playlist_ranklist(&ranklist); // ��ȡԭ��Ϣ
    if (ranklist.num > sizeof(ranklist.list))
    {
        printlog("ef ranklist num error\r");
        printnumlog(ranklist.num);
        err = 1;
    }
    else
    {
        for (i = ranklist.num; i < sizeof(ranklist.list); i++)
        {
            if (ranklist.list[i] != 0)
            {
                err = 1;
                printlog("verify playlist ranklist error: not empty\r");
            }
        }
    }
    if (err)
    {
        memset(&ranklist, 0, sizeof(ranklist)); // ����
        save_playlist_ranklist(&ranklist);
    }
    return err;
}

/*У��˳����������Ƿ���ȷ*/
void verify_ranklist(void )
{
    verify_allef_ranklist();
    verify_originalef_ranklist();
    verify_favoritesef_ranklist();
    verify_playlist_ranklist();
}

/*У���Ч�����Ƿ�Ҫ�ָ���������*/
void verify_factoryreset_effect_norflash(void)
{
    verify_Typedef verify;
    get_effect_verify(&verify);
    if (strcmp(&verify, EF_MEM_VERIFY) != 0) // flashδ����У����Ϣ
    {
        printlog("verify_factoryreset_effect_norflash not pass \r\r");
        printlog("Erase effect data block...\r");
        schedule_factory_reset();
        clear_all_ef_ranklist();            // ɾ����Ч�б�
        init_default_playlist();            // ���������ò��ű���Ϣ
        memset(&verify, 0, sizeof(verify)); // ����
        sprintf(&verify, EF_MEM_VERIFY);
        copy_built_in_ef_to_norflash(); // ��ʼ����Ч��Ϣ
        save_effect_verify(&verify);    // ����У����Ϣ
    }
    else
    {
        printlog("verify_factoryreset_effect_norflash  pass \r\r");
    }
}

/* ���������ò��ű���Ϣ*/
void init_default_playlist(void)
{
    playdetail_TypeDef playdetail;
    printlog("init default playlist\r\r");
    clear_playlist_ranklist();
    memset(&playdetail, 0, sizeof(playdetail));
    playdetail.name.length = strlen(DEFAULE_PLAYLIST_NAME);
    memcpy(&playdetail.name.text, DEFAULE_PLAYLIST_NAME, playdetail.name.length);
    playdetail.DurationTime.Min = 1;
    playdetail.DurationTime.Sec = 0;
    playdetail.num = sizeof(df_playlist);
    memcpy(&playdetail.list, df_playlist, playdetail.num);
    // printlog("num:%d\r",sizeof(df_playlist));
    print_playdetial(&playdetail, 0);
    add_playlist(&playdetail, 0);
}

/*��ȡ��ЧУ����Ϣ*/
void get_effect_verify(verify_Typedef *p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.verify, sizeof(verify_Typedef));
}
/*�����ЧУ����Ϣ*/
void save_effect_verify(verify_Typedef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.verify, sizeof(verify_Typedef));
    printlog("save_effect_verify\r");
}


/*���õ�Ч�������ⲿnorflash��*/
void copy_built_in_ef_to_norflash(void)
{
    Efdetail_TypeDef ef;
    ef_ranklist_TypeDef orgef_ranklist,allef_ranklist;// �Զ����Ч˳��� ȫ����Ч˳���
    uint8_t i, j;
    p_arry arry;
    for (i = 0; i < built_in_ef_num; i++)
    {
        memset(&ef, 0, sizeof(ef));              // ��������
        ef.namelenght = strlen(dfdata[i].name); // ��Ч���ֳ���
        strcpy(&ef.Name, dfdata[i].name);       // ������Ч����
        ef.EffectType = dfdata[i].EffectType;    // ������Ч����
        ef.Flow = dfdata[i].Flow;                // ������̬Ч��
        arry = dfdata[i].data;
        for (j = 0; j < 8; j++) // ������ɫ����
        {
            if ((*(*(arry + j) + 0) == 255) && (*(*(arry + j) + 1) == 255) && (*(*(arry + j) + 2) == 255) && (*(*(arry + j) + 3) == 255))
            {
                break; // ����������ɫ��־,��������
            }
            ef.EfColorInf.ColorID[j].color.R = *(*(arry + j) + 0);
            ef.EfColorInf.ColorID[j].color.G = *(*(arry + j) + 1);
            ef.EfColorInf.ColorID[j].color.B = *(*(arry + j) + 2);
            ef.EfColorInf.ColorID[j].color.W = *(*(arry + j) + 3);
            ef.EfColorInf.colorNum++;
        }
        ef.Speed = default_ef_Speed;                   // ȱʡֵ
        ef.Brightness1 = default_ef_Brightness1;       // ȱʡֵ
        ef.Brightness2 = default_ef_Brightness2;       // ȱʡֵ
        ef.MicSensitivity = default_ef_MicSensitivity; // ȱʡֵ
        ef.Attribute = default_ef_Attribute;           // ȱʡֵ
        ef.Direction = default_ef_Direction;           // ȱʡֵ
        save_effect(&ef, i);
    }
    printlog("copy_built_in_ef_to_norflash\r");
    memset((uint8_t *)&allef_ranklist, 0, sizeof(allef_ranklist));
    get_originalef_ranklist(&orgef_ranklist);
    allef_ranklist.num = orgef_ranklist.num + built_in_ef_num;
    memcpy((uint8_t *)&allef_ranklist.list + built_in_ef_num, (uint8_t *)&orgef_ranklist.list, orgef_ranklist.num);// �Զ����б��������õ�Ч����
    for (i = 0; i < built_in_ef_num; i++)
    {
        allef_ranklist.list[i] = i;
    }
    save_allef_ranklist(&allef_ranklist);
    printlog("save_allef_ranklist\r");
    print_ef_ranklist(&allef_ranklist);
}




/*�Ƚ��������Ƿ�����������Ƿ�һ��*/
uint8_t compare_same_ranklist(ef_ranklist_TypeDef *ranklist1, ef_ranklist_TypeDef *ranklist2)
{
    uint8_t i, j;
    uint8_t temp;
    if (ranklist2->num == ranklist1->num) // ����һ��
    {
        if (ranklist1->num != 0)
        {
            temp = 0;
            for (i = 0; i < ranklist1->num; i++)
            {
                for (j = 0; j < ranklist1->num; j++)
                {
                    if (ranklist1->list[j] == ranklist2->list[i]) // ��ѯ�б��а������������洢�б�Ҳ����
                    {
                        temp++; // ��¼��������ͬ���ݵĸ���
                    }
                }
            }
            if (temp == ranklist1->num) // ˵�������а���������һ��(˳����ܲ�һ��)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
}

/*����flash�е��Զ���&�ղص�Ч˳���*/
void search_norflash_ranklist(void)
{
    uint8_t i;
    uint8_t temp;
    ef_ranklist_TypeDef ranklist; // flash�洢��Ϣ
    ef_ranklist_TypeDef allranklist; // �Զ����Ч�б�
    ef_ranklist_TypeDef oriranklist; // �Զ����Ч�б�
    ef_ranklist_TypeDef favranklist; // �ղص�Ч�б�
    Efdetail_TypeDef ef;
    memset(&allranklist, 0, sizeof(allranklist)); // ��������
    memset(&oriranklist, 0, sizeof(oriranklist)); // ��������
    memset(&favranklist, 0, sizeof(favranklist)); // ��������
    /*����flash�еĵ�Ч��Ϣ*/
    for (i = 0; i < built_in_ef_num; i++) // �������õ�Ч��Ϣ
    {
        FLASHSPI_PageRead((uint8_t *)&temp, (uint32_t)&NORFLASH->efdata.data.effect.efdata[built_in_ef_basenum + i].Attribute, 1); // ��ȡ��Ч����
        if (temp == ORIGIN || temp == FAVORITES)
        {                                                                // �ǿյ�Ч��ԭʼ/�ղ�����
            allranklist.list[allranklist.num] = built_in_ef_basenum + i; // ��¼��ǰ��Ч����
            allranklist.num++;
            if (temp == FAVORITES)
            {                                                                // �ղص�Ч
                favranklist.list[favranklist.num] = built_in_ef_basenum + i; // ��¼��ǰ��Ч����
                favranklist.num++;
            }
        }
    }
    for (i = 0; i < original_ef_num; i++) // �����Զ����Ч��Ϣ
    {
        FLASHSPI_PageRead((uint8_t *)&temp, (uint32_t)&NORFLASH->efdata.data.effect.efdata[original_ef_basenum + i].Attribute, 1); // ��ȡ��Ч����
        if (temp == ORIGIN || temp == FAVORITES)
        {                                                                // �ǿյ�Ч��ԭʼ/�ղ�����
            allranklist.list[allranklist.num] = built_in_ef_basenum + i; // ��¼��ǰ��Ч����
            allranklist.num++;
            oriranklist.list[oriranklist.num] = original_ef_basenum + i; // ��¼��ǰ��Ч����
            oriranklist.num++;
            if (temp == FAVORITES) // �ղص�Ч
            {
                favranklist.list[favranklist.num] = original_ef_basenum + i; // ��¼��ǰ��Ч����
                favranklist.num++;
            }
        }
    }
    /*����ȫ����Ч���б���Ϣ*/
    get_originalef_ranklist(&ranklist);                      // ��ȡ�洢�ĵ�Ч˳���
    if (compare_same_ranklist(&allranklist, &ranklist) == 0) // ���ݲ�һ��ʱ
    {
        save_originalef_ranklist(&allranklist); // ����ѯ������˳���Ϊ׼
    }

    /*�����Զ����Ч���б���Ϣ*/
    get_originalef_ranklist(&ranklist);                      // ��ȡ�洢�ĵ�Ч˳���
    if (compare_same_ranklist(&oriranklist, &ranklist) == 0) // ���ݲ�һ��ʱ
    {
        save_originalef_ranklist(&oriranklist); // ����ѯ������˳���Ϊ׼
    }

    /*�����ղص�Ч���б���Ϣ*/
    get_favoritesef_ranklist(&ranklist);                     // ��ȡ�洢�ĵ�Ч˳���
    if (compare_same_ranklist(&favranklist, &ranklist) == 0) // ���ݲ�һ��ʱ
    {
        save_favoritesef_ranklist(&favranklist); // ����ѯ������˳���Ϊ׼
    }
#ifdef printlog_enabled
    printf("original ranklist.sum:%d\r", oriranklist.num);
    printf("favorites ranklist.sum:%d\r", favranklist.num);
#endif
}

/*******************************************************************************************************************************************************/

/*������Ч*/
void get_effect(Efdetail_TypeDef *p, uint8_t efnum)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.effect.efdata[efnum], sizeof(Efdetail_TypeDef));
}
/*�����Զ����Ч*/
uint8_t get_original_effect(Efdetail_TypeDef *p, uint8_t efnum)
{
    if (efnum < original_ef_basenum)
    {
        printf("num:%d\r",efnum);
        printlog("get_original_effect num error\n");
        return 0;
    }
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.effect.efdata[efnum], sizeof(Efdetail_TypeDef));
    return 1;
}
/*������������*/
void get_playdetail(playdetail_TypeDef *p, uint8_t playnum)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.play.pldata[playnum], sizeof(playdetail_TypeDef));
}

/*��ȡȫ����Ч�б�*/
void get_allef_ranklist(ef_ranklist_TypeDef *p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.all_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*��ȡ�Զ����Ч�б�*/
void get_originalef_ranklist(ef_ranklist_TypeDef *p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.original_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*��ȡ�ղص�Ч�б�*/
void get_favoritesef_ranklist(ef_ranklist_TypeDef *p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.favorites_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*��ȡ�����б��˳���*/
void get_playlist_ranklist(playlist_ranklist_TypeDef *p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.playlist_ranklist, sizeof(playlist_ranklist_TypeDef));
}
/*��ȡ�����б������*/
void get_playlist_name(name_TypeDef *p, uint8_t playnum)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.play.pldata[playnum].name, sizeof(name_TypeDef));
}
/*��ȡ�ӻ��豸��Ϣ*/
void get_all_slave_data(device_data_TypeDef* p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->sysdata.data.slave, sizeof(device_data_TypeDef));
}
/* ��ȡȫ����ʱ�ƻ�*/
void get_all_schedule(schedule_list_TypeDef *p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->sysdata.data.schedule, sizeof(schedule_list_TypeDef));
}
/* ��ȡ��ʱ����*/
void get_schedule_detail(schedule_detail_TypeDef *p, uint8_t num)
{
    if (num >= SCHEDULE_NUM)
    {
        printlog("[error] get wrong schedule num :%d\r", num);
        printAssert();
        return;
    }
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->sysdata.data.schedule.list[num], sizeof(schedule_detail_TypeDef));
}

// /*��ȡ���������б��˳���*/
// void get_playdetaillist_ranklist(playdetaillist_ranklist_TypeDef *p)
// {
//     FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.playdetaillist_ranklist, sizeof(playdetaillist_ranklist_TypeDef));
// }

/*******************************************************************************************************************************************************/
/*�洢��Ч*/
void save_effect(Efdetail_TypeDef *p, uint8_t efnum)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.effect.efdata[efnum], sizeof(Efdetail_TypeDef));
}
/*�洢�Զ����Ч*/
uint8_t save_original_effect(Efdetail_TypeDef *p, uint8_t efnum)
{
    if (efnum < original_ef_basenum)
    {
        printlog("save_original_effect num error\n");
        return 0;
    }
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.effect.efdata[efnum], sizeof(Efdetail_TypeDef));
    return 1;
}
/*�洢��������*/
void save_playdetail(playdetail_TypeDef *p, uint8_t playnum)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.play.pldata[playnum], sizeof(playdetail_TypeDef));
}
/*�洢ȫ����Ч�б�*/
void save_allef_ranklist(ef_ranklist_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.all_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*�洢�Զ����Ч�б�*/
void save_originalef_ranklist(ef_ranklist_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.original_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*�洢�ղص�Ч�б�*/
void save_favoritesef_ranklist(ef_ranklist_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.favorites_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*�洢�����б��˳���*/
void save_playlist_ranklist(playlist_ranklist_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.playlist_ranklist, sizeof(playlist_ranklist_TypeDef));
}
/*�洢�ӻ��豸��Ϣ*/
void save_all_slave_data(device_data_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->sysdata.data.slave, sizeof(device_data_TypeDef));
}
/* ����ʱ��ƻ���*/
void save_all_schedule(schedule_list_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->sysdata.data.schedule, sizeof(schedule_list_TypeDef));
}

// // /*�洢���������б��˳���*/
// // void save_playdetaillist_ranklist(playdetaillist_ranklist_TypeDef *p)
// // {
// //     FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.playdetaillist_ranklist, sizeof(playdetaillist_ranklist_TypeDef));
// // }

/*******************************************************************************************************************************************************/

/*��˳�����ɾ������*/
uint8_t delete_num_from_effect_ranklist(ef_ranklist_TypeDef *p, uint8_t efnum)
{
    ef_ranklist_TypeDef ranklist; // ����Ϣ
    uint8_t i, j;
    memset(&ranklist, 0, sizeof(ranklist));
    if (p->num > sizeof(ranklist.list))
    {
        printlog("delete number in rank list error\r");
        printnumlog(p->num);
        return 0;
    }
    if (p->num == 0)
    {
        printlog("delete empty rank list\r");
        return 0;
    }
    j = 0;
    for (i = 0; i < p->num; i++)
    {
        if (p->list[i] != efnum)
        {
            ranklist.list[j++] = p->list[i]; // ��ԭ˳���������˳������˱�ɾ���ĵ�Ч������
        }
    }
    if (j == p->num) // ��������ԭ˳���ߴ�һ�£�˵��˳����в����ڱ�ɾ��������
    {
        printlog("delete wrong number in rank list\r");
        return 0;
    }
    else
    {
        ranklist.num = j;                       // ����˳���ߴ硤
        memcpy(p, &ranklist, sizeof(ranklist)); // ����˳���������
        printlog("delete number in rank list successful\r");
        return 1;
    }
}

/*�Ӳ����б�˳�����ɾ��Ԫ��*/
uint8_t delete_num_from_playlist_ranklist(playlist_ranklist_TypeDef *p, uint8_t efnum)
{
    playlist_ranklist_TypeDef ranklist; // ����Ϣ
    uint8_t i, j;
    memset(&ranklist, 0, sizeof(ranklist));
    if (p->num > sizeof(ranklist.list))
    {
        printlog("delete number in rank list error\r");
        printnumlog(p->num);
        return 0;
    }
    if (p->num == 0)
    {
        printlog("delete empty rank list\r");
        return 0;
    }
    j = 0;
    for (i = 0; i < p->num; i++)
    {
        if (p->list[i] != efnum)
        {
            ranklist.list[j++] = p->list[i]; // ��ԭ˳���������˳������˱�ɾ���ĵ�Ч������
        }
    }
    if (j == p->num) // ��������ԭ˳���ߴ�һ�£�˵��˳����в����ڱ�ɾ��������
    {
        printlog("delete wrong number in rank list\r");
        return 0;
    }
    else
    {
        ranklist.num = j;                       // ����˳���ߴ硤
        memcpy(p, &ranklist, sizeof(ranklist)); // ����˳���������
        printlog("delete number in rank list successful\r");
        return 1;
    }
}
/*�ӵ�Ч˳��������Ԫ��*/
uint8_t add_num_from_effect_ranklist(ef_ranklist_TypeDef *p, uint8_t efnum)
{
    ef_ranklist_TypeDef ranklist; // ����Ϣ
    uint8_t i;
    memset(&ranklist, 0, sizeof(ranklist));
    ranklist.num = 0;
    if (p->num > sizeof(ranklist.list))
    {
        printlog("add number in rank list error\r");
        printnumlog(p->num);
        return 0;
    }
    for (i = 0; i < p->num; i++)
    {
        if (p->list[i] != efnum)
        {
            ranklist.list[ranklist.num++] = p->list[i]; // ��ԭ˳���������˳������˱���ӵĵ�Ч������
        }
    }
    if (ranklist.num == p->num) // ��������ԭ˳���ߴ�һ�£�˵��˳����в����ڱ���ӵ������������
    {
        ranklist.list[ranklist.num] = efnum;
        ranklist.num++;                         // ����˳���ߴ�
        memcpy(p, &ranklist, sizeof(ranklist)); // ����˳���������
        printlog("add number in rank list successful\r");
        return 1;
    }
    else
    {
        printlog("Error: add existing number in rank list:%d\r", efnum);
        return 1;
    }
}
/*�Ӳ����б�˳��������Ԫ��*/
uint8_t add_num_from_playlist_ranklist(playlist_ranklist_TypeDef *p, uint8_t efnum)
{
    playlist_ranklist_TypeDef ranklist; // ����Ϣ
    uint8_t i;
    memset(&ranklist, 0, sizeof(ranklist));
    ranklist.num = 0;
    if (p->num > sizeof(ranklist.list))
    {
        printlog("add number in rank list error\r");
        printnumlog(p->num);
        return 0;
    }
    for (i = 0; i < p->num; i++)
    {
        if (p->list[i] != efnum)
        {
            ranklist.list[ranklist.num++] = p->list[i]; // ��ԭ˳���������˳������˱���ӵĵ�Ч������
        }
    }
    if (ranklist.num == p->num) // ��������ԭ˳���ߴ�һ�£�˵��˳����в����ڱ���ӵ������������
    {
        ranklist.list[ranklist.num] = efnum;
        ranklist.num++;                         // ����˳���ߴ�
        memcpy(p, &ranklist, sizeof(ranklist)); // ����˳���������
        printlog("add number in rank list successful\r");
        return 1;
    }
    else
    {
        printlog("add existing number in rank list:%d\r", efnum);
        return 1;
    }
}
/*ɾ���Զ����Ч*/
uint8_t delete_original_ef(uint8_t efnum)
{
    ef_ranklist_TypeDef ranklist; // �б���Ϣ
    Efdetail_TypeDef ef;// ��Ч����
    if (efnum < original_ef_basenum)
    {
        printf("delete_original_ef num :%d\n",efnum);
        printlog("delete original error\r");
        return 0;
    }
    /*�޸ĸõ�Ч����*/
    get_original_effect(&ef, efnum);
    ef.Attribute = EMPTY; // �޸�������Ϣ
    save_effect(&ef, efnum);

    /*��ȫ����Ч˳�����ɾ���õ�Ч*/
    get_allef_ranklist(&ranklist);              // ��ȡȫ����Ч˳���
    delete_num_from_effect_ranklist(&ranklist, efnum); // ɾ������
    save_allef_ranklist(&ranklist);             // ����ȫ����Ч˳���

    /*���Զ����Ч˳�����ɾ���õ�Ч*/
    get_originalef_ranklist(&ranklist);         // ��ȡ�Զ����Ч˳���
    delete_num_from_effect_ranklist(&ranklist, efnum); // ɾ������
    save_originalef_ranklist(&ranklist);        // �����Զ����Ч˳���;

    /*���ղص�Ч˳�����ɾ���õ�Ч*/
    get_favoritesef_ranklist(&ranklist);        // ��ȡ�ղص�Ч˳���
    delete_num_from_effect_ranklist(&ranklist, efnum); // ɾ������
    save_favoritesef_ranklist(&ranklist);       // �����ղص�Ч˳���
}

/*�����Զ����Ч*/
uint8_t add_original_ef(Efdetail_TypeDef *p, uint8_t efnum)
{
    ef_ranklist_TypeDef ranklist; // ����Ϣ
    if (efnum < original_ef_basenum)
    {
        printlog("add_original_ef error\r");
        return 0;
    }
    p->Attribute = ORIGIN; // ���µ�Ч����
    save_effect(p, efnum);

    /*��ȫ����Ч˳����������õ�Ч*/
    get_allef_ranklist(&ranklist);           // ��ȡȫ����Ч˳���
    add_num_from_effect_ranklist(&ranklist, efnum); // ��������
    save_allef_ranklist(&ranklist);          // ����ȫ����Ч˳���

    /*���Զ����Ч˳����������õ�Ч*/
    get_originalef_ranklist(&ranklist);      // ��ȡ�Զ����Ч˳���
    add_num_from_effect_ranklist(&ranklist, efnum); // ��������
    save_originalef_ranklist(&ranklist);     // �����Զ����Ч˳���;
    return 1;
}

/*ɾ�������Զ����Ч*/
void clear_all_original_ef(void)
{
    uint8_t i;
    for (i = original_ef_basenum; i <= 255; i++)
    {
        delete_original_ef(i);
    }
}

/*�ղص�Ч*/
uint8_t add_favorites_ef(uint8_t efnum)
{
    ef_ranklist_TypeDef ranklist; // �б���Ϣ
    Efdetail_TypeDef ef;             // ��Ч����

    get_effect(&ef, efnum);
    ef.Attribute = FAVORITES; // �޸ĳ��ղ�������Ϣ
    save_effect(&ef, efnum);
    get_favoritesef_ranklist(&ranklist); // ��ȡ�б���Ϣ
    add_num_from_effect_ranklist(&ranklist, efnum);
    save_favoritesef_ranklist(&ranklist);
    return 1;
}

/*ȡ���ղص�Ч*/
uint8_t delete_favorites_ef(uint8_t efnum)
{
    ef_ranklist_TypeDef ranklist; // �б���Ϣ
    Efdetail_TypeDef ef;             // ��Ч����

    get_effect(&ef, efnum);
    ef.Attribute = ORIGIN; // �޸ĳ�ԭʼ������Ϣ
    save_effect(&ef, efnum);

    get_favoritesef_ranklist(&ranklist);        // ��ȡ�б���Ϣ
    delete_num_from_effect_ranklist(&ranklist, efnum); // ɾ������
    save_favoritesef_ranklist(&ranklist);
    return 1;
}

/*ɾ�������б�*/
uint8_t delete_playlist(uint8_t listnum)
{
    playlist_ranklist_TypeDef ranklist;                                  // �б���Ϣ
    get_playlist_ranklist(&ranklist);                                    // ��ȡ�б���Ϣ
    delete_num_from_playlist_ranklist(&ranklist, listnum); // ɾ������
    save_playlist_ranklist(&ranklist);
    return 1;
}

/*��Ӳ�����Ϣ*/
uint8_t add_playlist(playdetail_TypeDef *p, uint8_t listnum)
{
    playlist_ranklist_TypeDef ranklist; // �б���Ϣ
    if (listnum >= sizeof(ranklist.list))
    {
        printlog("Error: add existing number in playlist :%d\r", listnum);
        return 0;
    }
    save_playdetail(p, listnum);
    get_playlist_ranklist(&ranklist);
    add_num_from_playlist_ranklist(&ranklist, listnum);
    save_playlist_ranklist(&ranklist);
    return 1;
}

/*ɾ����Ч�б�*/
void clear_all_ef_ranklist(void)
{
    ef_ranklist_TypeDef zi;
    memset(&zi, 0, sizeof(zi));
    save_allef_ranklist(&zi);
    save_originalef_ranklist(&zi);
    save_favoritesef_ranklist(&zi);
}

/*ɾ�������б�*/
void clear_playlist_ranklist(void)
{
    playlist_ranklist_TypeDef zi;
    memset(&zi, 0, sizeof(zi));
    save_playlist_ranklist(&zi);
}
/*��ͨ���п�����ʱ�ƻ�����*/
void copy_schedule_detail_from_com(com_schedule_detail_TypeDef *sur, schedule_detail_TypeDef *tar)
{
    memcpy(&(tar->name), &(sur->name), sizeof(tar->name)); // ��������
    tar->action = sur->action;                             // ��������
    tar->ef_index = sur->ef_index;                         // ��Ч��������
    tar->ultimatebright = sur->ultimatebright;             // ��������
    tar->actiontime.Min = sur->actiontime.Min;             // ����ʱ��
    tar->actiontime.Sec = sur->actiontime.Sec;             // ����ʱ��
    tar->duration = sur->duration;                         // ����ʱ��
    tar->repeat = sur->repeat;                             // ���ڼƻ�
}
/*������ʱ�ƻ�������ͨ����*/
void copy_schedule_detail_to_com(schedule_detail_TypeDef *sur, com_schedule_detail_TypeDef *tar)
{
    memcpy(&(tar->name), &(sur->name), sizeof(tar->name)); // ��������
    tar->action = sur->action;                             // ��������
    tar->ef_index = sur->ef_index;                         // ��Ч��������
    tar->ultimatebright = sur->ultimatebright;             // ��������
    tar->actiontime.Min = sur->actiontime.Min;             // ����ʱ��
    tar->actiontime.Sec = sur->actiontime.Sec;             // ����ʱ��
    tar->duration = sur->duration;                         // ����ʱ��
    tar->repeat = sur->repeat;                             // ���ڼƻ�
}

/*��Ӷ�ʱ�ƻ�*/
uint8_t add_schedule(schedule_detail_TypeDef *p, uint8_t num)
{
    schedule_list_TypeDef schedule;
    printlog("add_schedule %d\r",num);
    get_all_schedule(&schedule);
    if ((schedule.num != 0) && (num > schedule.num || num >= SCHEDULE_NUM))
    {
        printlog("[error] add wrong schedule num :%d\r", num);
        printAssert();
        return 0;
    }
    memcpy(&schedule.list[num], p, sizeof(schedule_detail_TypeDef));
    if (num == schedule.num) // ������ʱ
    {
        schedule.num++;
    }
    save_all_schedule(&schedule);
    return 1;
}

/*ɾ����ʱ�ƻ�*/
uint8_t delete_schedule(uint8_t num)
{
    schedule_list_TypeDef schedule;
    schedule_list_TypeDef schedule_new;
    uint8_t i,j;
    printlog("delete_schedule\r");
    get_all_schedule(&schedule);
    if (num > schedule.num || num >= SCHEDULE_NUM || schedule.num == 0)
    {
        printlog("[error] delete wrong schedule num :%d\r", num);
        printAssert();
        return 0;
    }
    memset(&schedule_new,0,sizeof(schedule_new));
    for ( i = 0; i < schedule.num; i++)
    {
        if (i != num)   // ����û��ɾ�Ķ�ʱ��
        {
            memcpy(&schedule_new.list[schedule_new.num],&schedule.list[i],sizeof(schedule_new.list[i]));
            schedule_new.num++;
        }
    }
    save_all_schedule(&schedule_new);
    return 1;
}
