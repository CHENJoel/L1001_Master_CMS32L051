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

/*
 * @Description: ����flashȫƬ��������
 * @param:
 * @return:
 */
void norflash_reset_to_zreo(void)
{ /* ʵ���ź�ʱ8�� */
    uint8_t buf[256];
    uint32_t adr;
    // printlog("norflash_reset_to_zreo\r");
    // memset(&buf, 0, sizeof(buf));
    // for (adr = 0; adr < 0x40000; adr += sizeof(buf))
    // {
    //     FLASHSPI_PageWrite(&buf, adr, sizeof(buf)); // д���޸ĺ��ҳ����
    //     if (adr % 0x4000 == 0)
    //     {
    //         printlog("norflash reset to zero %x\r", adr);
    //     }
    // }
    printlog("norflashChipErase \r");
    FLASH_ChipErase();
}

/* 
 * @Description: norflash�ָ���������
 * @param: 
 * @return: 
*/ 
void factoryreset_norflash(void)
{
    verify_Typedef verify;
    norflash_reset_to_zreo();
    clear_device_identify();
    printlog("Erase effect data block...\r");
    schedule_factory_reset();
    clear_all_ef_ranklist();            // ɾ����Ч�б�
    init_default_playlist();            // ���������ò��ű���Ϣ
    copy_built_in_ef_to_norflash();     // ��ʼ����Ч��Ϣ
    init_default_global_setting();      // ȫ�����ó�ʼ����Ĭ������
    memset(&verify, 0, sizeof(verify)); // ����
    sprintf(&verify, EF_MEM_VERIFY);    // дУ����Ϣ
    //----------------------------------------------------------------
    save_effect_verify(&verify); // ����У����Ϣ
}

/*У���Ч�����Ƿ�Ҫ�ָ���������*/
void verify_factoryreset_effect_norflash(void)
{
    verify_Typedef verify;
    get_effect_verify(&verify);
    if (strcmp(&verify, EF_MEM_VERIFY) != 0) // flashδ����У����Ϣ
    {
        printlog("verify_factoryreset_effect_norflash not pass \r\r");
        factoryreset_norflash();    // norflash�ָ���������
        search_norflash_ranklist(); // ����flash�е��Զ���&�ղص�Ч˳���
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
    playdetail.DurationTime.min_MS = 1;
    playdetail.DurationTime.sec_MS = 0;
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



/* 
 * @Description: ��������ԭ����Ч
 * @param: 
 * @return: 
*/ 
void reset_built_in_effect(uint8_t efnum)
{
    Efdetail_TypeDef ef;
    uint8_t j;
    p_arry arry;
    if (efnum >= (built_in_ef_basenum + built_in_ef_num))
    {
        printlog("error:reset wrong effect num:%d \r",efnum);
        return 0;
    }
    printlog("---------------------\r");
    printlog("reset built in effect:%d\r", efnum);
    memset(&ef, 0, sizeof(ef));                 // ��������
    ef.namelenght = strlen(dfdata[efnum].name); // ��Ч���ֳ���
    strcpy(&ef.Name, dfdata[efnum].name);       // ������Ч����
    ef.EffectType = dfdata[efnum].EffectType;   // ������Ч����
    ef.Flow = dfdata[efnum].Flow;               // ������̬Ч��
    arry = dfdata[efnum].data;
    if (dfdata[efnum].EffectType == STATIC_TYPE)    // ��̬��Ч
    {
        if (slave.num == 0) // ��ǰû�������κεư�
        {
            ef.EfColorInf.colorNum=1;
            ef.EfColorInf.ColorID[j].id = 0;
            ef.EfColorInf.ColorID[j].color.R = *(*(arry + 0) + 0); // ���һ����ɫ
            ef.EfColorInf.ColorID[j].color.G = *(*(arry + 0) + 1);
            ef.EfColorInf.ColorID[j].color.B = *(*(arry + 0) + 2);
            ef.EfColorInf.ColorID[j].color.W = *(*(arry + 0) + 3);
        }
        else // �Ե�ǰ���ӵĵư���Ϊ
        {
            ef.EfColorInf.colorNum = slave.num; // ��ɫ���������豸����
            for (j = 0; j < ef.EfColorInf.colorNum; j++)
            {
                ef.EfColorInf.ColorID[j].id = slave.data[j].id;
                ef.EfColorInf.ColorID[j].color.R = *(*(arry + 0) + 0); // �����һ����ɫ
                ef.EfColorInf.ColorID[j].color.G = *(*(arry + 0) + 1);
                ef.EfColorInf.ColorID[j].color.B = *(*(arry + 0) + 2);
                ef.EfColorInf.ColorID[j].color.W = *(*(arry + 0) + 3);
            }
        }
    }
    else
    {
        for (j = 0; j < EfColor_SizeNum; j++) // ������ɫ����
        {
            if ((*(*(arry + j) + 0) == 255) && (*(*(arry + j) + 1) == 255) && (*(*(arry + j) + 2) == 255) && (*(*(arry + j) + 3) == 255))
            {
                break; // ����������ɫ��־,��������
            }
            ef.EfColorInf.ColorID[j].id = 0;
            ef.EfColorInf.ColorID[j].color.R = *(*(arry + j) + 0);
            ef.EfColorInf.ColorID[j].color.G = *(*(arry + j) + 1);
            ef.EfColorInf.ColorID[j].color.B = *(*(arry + j) + 2);
            ef.EfColorInf.ColorID[j].color.W = *(*(arry + j) + 3);
            ef.EfColorInf.colorNum++;
        }
    }
    ef.Brightness1 = dfdata[efnum].Brightness1;
    ef.Speed = dfdata[efnum].Speed;
    ef.Direction = dfdata[efnum].Direction;
    ef.Brightness2 = default_ef_Brightness2;       // ȱʡֵ
    ef.MicSensitivity = default_ef_MicSensitivity; // ȱʡֵ
    ef.Attribute = default_ef_Attribute;           // ȱʡֵ
    save_effect(&ef, efnum);
}

// // // /* 
// // //  * @Description: �������þ�̬��Ч��ɫ����
// // //  * @param: 
// // //  * @return: 
// // // */
// // // void reset_built_in_static_effect(uint8_t efindex)
// // // {
// // //     Efdetail_TypeDef ef;
// // //     uint8_t j;
// // //     p_arry arry;
// // //     printlog("reset built in static effect:%d\r", efindex);
// // //     memset(&ef, 0, sizeof(ef));                   // ��������
// // //     ef.namelenght = strlen(dfdata[efindex].name); // ��Ч���ֳ���
// // //     strcpy(&ef.Name, dfdata[efindex].name);       // ������Ч����
// // //     ef.EffectType = dfdata[efindex].EffectType;   // ������Ч����
// // //     ef.Flow = dfdata[efindex].Flow;               // ������̬Ч��
// // //     arry = dfdata[efindex].data;
// // //     ef.EfColorInf.colorNum = slave.num; // ��ɫ���������豸����
// // //     for (j = 0; j < ef.EfColorInf.colorNum; j++)
// // //     {
// // //         ef.EfColorInf.ColorID[j].id = slave.data[j].id;
// // //         ef.EfColorInf.ColorID[j].color.R = *(*(arry + 0) + 0); // �����һ����ɫ
// // //         ef.EfColorInf.ColorID[j].color.G = *(*(arry + 0) + 1);
// // //         ef.EfColorInf.ColorID[j].color.B = *(*(arry + 0) + 2);
// // //         ef.EfColorInf.ColorID[j].color.W = *(*(arry + 0) + 3);
// // //     }
// // //     ef.Brightness1 = dfdata[efindex].Brightness1;
// // //     ef.Speed = dfdata[efindex].Speed;
// // //     ef.Direction = dfdata[efindex].Direction;
// // //     ef.Brightness2 = default_ef_Brightness2;       // ȱʡֵ
// // //     ef.MicSensitivity = default_ef_MicSensitivity; // ȱʡֵ
// // //     ef.Attribute = default_ef_Attribute;           // ȱʡֵ
// // //     save_effect(&ef, efindex);
// // // }


/*
 * @Description: ����ȫ�����þ�̬��Ч��ɫ����
 * @param:
 * @return:
 */
void reset_all_built_in_static_effect(void)
{
    uint8_t efindex;
    uint8_t i;
    for (i = 0; i < built_in_ef_num; i++)
    {
        efindex = built_in_ef_basenum + i;
        if (dfdata[efindex].EffectType == STATIC_TYPE) // ���������ɾ�̬��Ч��Ϣ
        {
            reset_built_in_effect(efindex);
        }
        else
        {

        }
    }
}

/* 
 * @Description: ���õ�Ч�������ⲿnorflash��
 * @param: 
 * @return: 
*/ 
void copy_built_in_ef_to_norflash(void)
{
    Efdetail_TypeDef ef;
    ef_ranklist_TypeDef orgef_ranklist,allef_ranklist;// �Զ����Ч˳��� ȫ����Ч˳���
    uint8_t i, j;
    for (i = 0; i < built_in_ef_num; i++)
    {
        reset_built_in_effect(i);
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
        else
        {
            return 1;
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
    get_allef_ranklist(&ranklist);                           // ��ȡ�洢�ĵ�Ч˳���
    if (compare_same_ranklist(&allranklist, &ranklist) == 0) // ���ݲ�һ��ʱ
    {
        save_allef_ranklist(&allranklist); // ����ѯ������˳���Ϊ׼
        printlog("save new allef ranklist\r");
    }

    /*�����Զ����Ч���б���Ϣ*/
    get_originalef_ranklist(&ranklist);                      // ��ȡ�洢�ĵ�Ч˳���
    if (compare_same_ranklist(&oriranklist, &ranklist) == 0) // ���ݲ�һ��ʱ
    {
        save_originalef_ranklist(&oriranklist); // ����ѯ������˳���Ϊ׼
        printlog("save new originalef ranklist\r");
    }

    /*�����ղص�Ч���б���Ϣ*/
    get_favoritesef_ranklist(&ranklist);                     // ��ȡ�洢�ĵ�Ч˳���
    if (compare_same_ranklist(&favranklist, &ranklist) == 0) // ���ݲ�һ��ʱ
    {
        save_favoritesef_ranklist(&favranklist); // ����ѯ������˳���Ϊ׼
        printlog("save new favoritese ranklist\r");
    }
#ifdef printlog_enabled
    printf("original ranklist.sum:%d\r", oriranklist.num);
    printf("favorites ranklist.sum:%d\r", favranklist.num);
#endif
}

/*******************************************************************************************************************************************************/

/* 
 * @Description: ��ȡ��Ч����
 * @param: ָ��
 * @param: ��Ч����
 * @return: 
*/ 
void get_effect_detail(Efdetail_TypeDef *p, uint8_t efindex)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.effect.efdata[efindex], sizeof(Efdetail_TypeDef));
}

/* 
 * @Description: ��ȡ��Ч������1
 * @param: ��Ч����
 * @param: ����1��ָ��
 * @return: 
*/ 
void get_effect_brightness1(uint8_t efindex,uint8_t *bright1)
{
    FLASHSPI_PageRead(bright1, (uint32_t)&NORFLASH->efdata.data.effect.efdata[efindex].Brightness1, sizeof(uint8_t));
}

/* 
 * @Description: ��ȡ��Ч������2
 * @param: ��Ч����
 * @param: ����2��ָ��
 * @return: 
*/ 
void get_effect_brightness2(uint8_t efindex,uint8_t *bright2)
{
    FLASHSPI_PageRead(bright2, (uint32_t)&NORFLASH->efdata.data.effect.efdata[efindex].Brightness2, sizeof(uint8_t));
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
void get_all_schedule(clock_list_TypeDef *p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->sysdata.data.schedule, sizeof(clock_list_TypeDef));
}
/* ��ȡ��ʱ����*/
void get_schedule_detail(clock_detail_TypeDef *p, uint8_t num)
{
    if (num >= SCHEDULE_NUM)
    {
        printlog("[error] get wrong schedule num :%d\r", num);
        printAssert();
        return;
    }
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->sysdata.data.schedule.list[num], sizeof(clock_detail_TypeDef));
}

/* 
 * @Description: ��ȡϵͳȫ������
 * @param: 
 * @return: 
*/ 
void get_global_setting(global_setting_TypeDef *p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->sysdata.data.global_setting, sizeof(global_setting_TypeDef));
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
    printlog(">>Saving effect: %d\r", efnum);
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
void save_all_schedule(clock_list_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->sysdata.data.schedule, sizeof(clock_list_TypeDef));
}

/* 
 * @Description: ����ϵͳȫ������
 * @param: 
 * @return: 
*/ 
void save_global_setting(global_setting_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->sysdata.data.global_setting, sizeof(global_setting_TypeDef));
}

/* 
 * @Description: ����ȫ������
 * @param: 
 * @return: 
*/
void save_global_brightness_set(void)
{
    save_global_setting(&play.work.global_setting);
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
    printlog("delete_num_from_effect_ranklist:%d\n", efnum);
    memset(&ranklist, 0, sizeof(ranklist));
    if (p->num > sizeof(ranklist.list))
    {
        printlog("error:delete wrong number in effect rank list\r");
        printnumlog(p->num);
        return 0;
    }
    if (p->num == 0)
    {
        printlog("warning:delete empty effect rank list\r");
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
        printlog("warning: delete wrong number in effect rank list\r");
        return 0;
    }
    else
    {
        ranklist.num = j;                       // ����˳���ߴ硤
        memcpy(p, &ranklist, sizeof(ranklist)); // ����˳���������
        printlog("delete number in effect rank list successful\r");
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
        printlog("delete number in playlist rank list error\r");
        printnumlog(p->num);
        return 0;
    }
    if (p->num == 0)
    {
        printlog("delete empty playlist rank list\r");
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
        printlog("warning:delete wrong number in playlistrank list\r");
        return 0;
    }
    else
    {
        ranklist.num = j;                       // ����˳���ߴ硤
        memcpy(p, &ranklist, sizeof(ranklist)); // ����˳���������
        printlog("delete number in playlist rank list successful\r");
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
        printlog("add number in effect rank list error\r");
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
        printlog("add number in effect rank list successful :%d\r", efnum);
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
        printlog("error:delete original ef num :%d\n", efnum);
        // // printlog("delete original error\r");
        return 0;
    }
    printlog("delete_original_ef num :%d\n", efnum);
    /*�޸ĸõ�Ч����*/
    get_original_effect(&ef, efnum);
    ef.Attribute = EMPTY; // �޸�������Ϣ
    save_effect(&ef, efnum);

    /*��ȫ����Ч˳�����ɾ���õ�Ч*/
    printlog("delete from all effect\n");
    get_allef_ranklist(&ranklist);                     // ��ȡȫ����Ч˳���
    print_ef_ranklist(&ranklist);                      // ��ӡ˳���б���Ϣ
    delete_num_from_effect_ranklist(&ranklist, efnum); // ɾ������
    save_allef_ranklist(&ranklist);                    // ����ȫ����Ч˳���
    /**/
    get_allef_ranklist(&ranklist); // ��ȡȫ����Ч˳���
    print_ef_ranklist(&ranklist);  // ��ӡ˳���б���Ϣ

    /*���Զ����Ч˳�����ɾ���õ�Ч*/
    printlog("delete from original effect\n");
    get_originalef_ranklist(&ranklist);                // ��ȡ�Զ����Ч˳���
    print_ef_ranklist(&ranklist);                      // ��ӡ˳���б���Ϣ
    delete_num_from_effect_ranklist(&ranklist, efnum); // ɾ������
    save_originalef_ranklist(&ranklist);               // �����Զ����Ч˳���;
    /**/
    get_originalef_ranklist(&ranklist); // ��ȡȫ����Ч˳���
    print_ef_ranklist(&ranklist);       // ��ӡ˳���б���Ϣ

    /*���ղص�Ч˳�����ɾ���õ�Ч*/
    printlog("delete from favorite effect\n");
    get_favoritesef_ranklist(&ranklist);               // ��ȡ�ղص�Ч˳���
    print_ef_ranklist(&ranklist);                      // ��ӡ˳���б���Ϣ
    delete_num_from_effect_ranklist(&ranklist, efnum); // ɾ������
    save_favoritesef_ranklist(&ranklist);              // �����ղص�Ч˳���
    /**/
    get_favoritesef_ranklist(&ranklist); // ��ȡȫ����Ч˳���
    print_ef_ranklist(&ranklist);        // ��ӡ˳���б���Ϣ
}

/* 
 * @Description: �����Զ����Ч
 * @param: 
 * @param: 
 * @return: 
*/ 
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
    printlog("add in all effect ranklist\r");
    get_allef_ranklist(&ranklist);                  // ��ȡȫ����Ч˳���
    add_num_from_effect_ranklist(&ranklist, efnum); // ��������
    save_allef_ranklist(&ranklist);                 // ����ȫ����Ч˳���

    /*���Զ����Ч˳����������õ�Ч*/
    printlog("add in original effect ranklist\r");
    get_originalef_ranklist(&ranklist);             // ��ȡ�Զ����Ч˳���
    add_num_from_effect_ranklist(&ranklist, efnum); // ��������
    save_originalef_ranklist(&ranklist);            // �����Զ����Ч˳���;

    print_get_ef_detial(efnum);
    return 1;
}

/* 
 * @Description: �������õ�Ч��Ϣ
 * @param: 
 * @param: 
 * @return: 
*/ 
uint8_t update_built_in_effect(Efdetail_TypeDef *p, uint8_t efnum)
{
    Efdetail_TypeDef ef; // ��Ч����
    EfColorInf_TypeDef efcolorinf; /* ��ɫ������ */
    if (efnum >= original_ef_basenum)
    {
        printlog("error:update wrong effect num:%d \r",efnum);
        return 0;
    }
    // // get_effect_detail(&ef, efnum);
    // // memcpy(&efcolorinf, &ef.EfColorInf, sizeof(efcolorinf)); // ����ԭ������ɫ����
    memcpy(&ef, p, sizeof(ef));
    // // // memcpy(&ef.EfColorInf, &efcolorinf, sizeof(efcolorinf)); // �ָ�ԭ������ɫ����
    save_effect(&ef, efnum);
    printlog("update built in effect:%d \r",efnum);
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

    get_effect_detail(&ef, efnum);
    ef.Attribute = FAVORITES; // �޸ĳ��ղ�������Ϣ
    save_effect(&ef, efnum);
    get_favoritesef_ranklist(&ranklist); // ��ȡ�б���Ϣ
    printlog("add efnum in favorites effect ranklist\r");
    add_num_from_effect_ranklist(&ranklist, efnum);
    save_favoritesef_ranklist(&ranklist);
    print_get_favorites_ef_ranklist();
    return 1;
}

/*ȡ���ղص�Ч*/
uint8_t delete_favorites_ef(uint8_t efnum)
{
    ef_ranklist_TypeDef ranklist; // �б���Ϣ
    Efdetail_TypeDef ef;             // ��Ч����

    get_effect_detail(&ef, efnum);
    ef.Attribute = ORIGIN; // �޸ĳ�ԭʼ������Ϣ
    save_effect(&ef, efnum);

    printlog("delete from favorite effect\n");
    get_favoritesef_ranklist(&ranklist);               // ��ȡ�б���Ϣ
    delete_num_from_effect_ranklist(&ranklist, efnum); // ɾ������
    save_favoritesef_ranklist(&ranklist);
    print_get_favorites_ef_ranklist();
    return 1;
}

/*ɾ�������б�*/
uint8_t delete_playlist(uint8_t listnum)
{
    playlist_ranklist_TypeDef ranklist;                    // �б���Ϣ
    playdetail_TypeDef playdetail;                         // ��ɾ�Ĳ�������
    printlog("delete playlist :%d\r", listnum);
    get_playlist_ranklist(&ranklist);                      // ��ȡ�б���Ϣ
    delete_num_from_playlist_ranklist(&ranklist, listnum); // ���ܱ���ɾ��������
    save_playlist_ranklist(&ranklist);                     // ����
    memset(&playdetail, 0, sizeof(playdetail));            // ��ɾ�Ĳ������� ����
    save_playdetail(&playdetail, listnum);                 // ����
    if (play.detail.idex_inlist == listnum)                // ��ɾ�б����ڲ���
    {
        printlog("delete current playlist\r");
    }
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
    mcu_update_current_playdetail(); // �ϱ���ǰ���ڲ��ŵġ������б����顱
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
void copy_schedule_detail_from_com(com_schedule_detail_TypeDef *sur, clock_detail_TypeDef *tar)
{
    memcpy(&(tar->name), &(sur->name), sizeof(tar->name)); // ��������
    tar->en_sta = sur->en_sta;                             // ����״̬
    tar->action = sur->action;                             // ��������
    tar->ef_index = sur->ef_index;                         // ��Ч����
    tar->ultimatebright = sur->ultimatebright;             // ��������
    tar->actiontime.hou_HM = sur->actiontime.hou_HM;       // ����ʱ��
    tar->actiontime.min_HM = sur->actiontime.min_HM;       // ����ʱ��
    tar->duration.hou_HM = sur->duration.hou_HM;           // ����ʱ��
    tar->duration.min_HM = sur->duration.min_HM;           // ����ʱ��
    tar->repeat.week = sur->repeat.week;                   // ���ڼƻ�
}
/*������ʱ�ƻ�������ͨ����*/
void copy_schedule_detail_to_com(clock_detail_TypeDef *sur, com_schedule_detail_TypeDef *tar)
{
    memcpy(&(tar->name), &(sur->name), sizeof(tar->name)); // ��������
    tar->en_sta = sur->en_sta;                             // ����״̬
    tar->action = sur->action;                             // ��������
    tar->ef_index = sur->ef_index;                         // ��Ч����
    tar->ultimatebright = sur->ultimatebright;             // ��������
    tar->actiontime.hou_HM = sur->actiontime.hou_HM;       // ����ʱ��
    tar->actiontime.min_HM = sur->actiontime.min_HM;       // ����ʱ��
    tar->duration.hou_HM = sur->duration.hou_HM;           // ����ʱ��
    tar->duration.min_HM = sur->duration.min_HM;           // ����ʱ��
    tar->repeat.week = sur->repeat.week;                   // ���ڼƻ�
}

/*��Ӷ�ʱ�ƻ�*/
uint8_t add_clock_schedule(clock_detail_TypeDef *p, uint8_t num)
{
    clock_list_TypeDef schedule;
    printlog("add_clock_schedule:%d\r",num);
    uint8_t i;
    get_all_schedule(&schedule);
    if ((schedule.num != 0) && (num > schedule.num || num >= SCHEDULE_NUM))
    {
        printlog("[error] add wrong schedule num :%d\r", num);  // �����Ķ�ʱ��������
        printAssert();
        return 0;
    }

    for (i = 0; i < schedule.num; i++)
    {
        if ((schedule.list[i].actiontime.hou_HM == p->actiontime.hou_HM) && (schedule.list[i].actiontime.min_HM == p->actiontime.min_HM))
        {
            // ������ʱ��Ϣ�ڱ����з����ظ�
            if (i != num)  // ��ͬ��ʱ�����ܸ���ԭ�ж�ʱ����������     
            {
                printlog("[error] refuse to save clock: %d\r", num);
                return 0;   // �ܾ�����
            }
        }
    }
    if (num == schedule.num) // ������ʱ
    {
        schedule.num++;
        printlog("add new clock schedule\r");
    }
    else if (num < schedule.num) // ����ԭ�ж�ʱ
    {
        printlog("update old clock schedule\r");
    }
    else
    {
        printlog("[error] add wrong schedule num :%d\r", num);
        printAssert();
        return 0;
    }
    memcpy(&schedule.list[num], p, sizeof(clock_detail_TypeDef));   // ������������Ϣ
    save_all_schedule(&schedule);
    return 1;
}

/*ɾ����ʱ�ƻ�*/
uint8_t delete_schedule(uint8_t num)
{
    clock_list_TypeDef schedule;
    clock_list_TypeDef schedule_new;
    uint8_t i,j;
    printlog("delete_schedule:%d\r",num);
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


/* 
 * @Description: ȫ�����ó�ʼ����Ĭ������
 * @param: 
 * @return: 
*/
void init_default_global_setting(void)
{
    memcpy(&play.work.global_setting, &global_setting_default, sizeof(global_setting_TypeDef));
    save_global_setting(&play.work.global_setting);
}

/* 
 * @Description: ��ȡ�豸��Ա�ʶ
 * @param: 
 * @return: 
*/ 
void get_device_identify(device_indentify_TypeDef *p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->sysdata.data.device_indentify, sizeof(device_indentify_TypeDef));
}

/* 
 * @Description: �����豸��Ա�ʶ
 * @param: 
 * @return: 
*/ 
void save_device_identify(device_indentify_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->sysdata.data.device_indentify, sizeof(device_indentify_TypeDef));
}


/* 
 * @Description: ����豸��Ա�ʶ
 * @param: 
 * @return: 
*/
void clear_device_identify(void)
{
    device_indentify_TypeDef buff;
    buff.length = 2;    // Ĭ���ֽڳ���
    memset(&buff.data, 0, sizeof(buff.data));
    save_device_identify(&buff);
}

/*-------------------------------------------------------------------------*/

/* 
 * @Description: �޸ĵ�Ч��������Ϣ
 * @param: ��Ч����
 * @param: ����
 * @return: 
*/
void modify_effect_brightness(uint8_t efindex, uint8_t bright1, uint8_t bright2)
{
    Efdetail_TypeDef efdetail; // ��Ч����
    printlog("modify effect brightness [%d]->%d,%d\r", efindex, bright1, bright2);
    if (bright1 < 1 || bright1 > 100)
    {
        printlog("error: invalid brightness\r");
        return;
    }
    get_effect_detail(&efdetail, efindex); // ����ԭ��Ч����
    efdetail.Brightness1 = bright1;        // �޸ĳ�������
    efdetail.Brightness2 = bright2;        //  
    save_effect(&efdetail, efindex);       // ����
    //
    mcu_update_current_ef_brightness(); // �ϴ����ŵĵ�Ч��������Ϣ
    mcu_update_current_ef_detail();     // �ϱ���ǰ���ŵĵ�Ч��Ϣ
    mcu_update_current_ef_detail();     // �ϱ���ǰ���ŵĵ�Ч����
}

/* 
 * @Description: ���ص�ǰ��Ч������
 * @param: 
 * @return: 
*/
void load_current_ef_brightness(void)
{
    get_effect_brightness1(play.detail.efindex, &play.efdetail.Brightness1); // �Ӵ洢�����¼���
    get_effect_brightness2(play.detail.efindex, &play.efdetail.Brightness2);
    play.work.brightness.set = play.efdetail.Brightness1;
}
