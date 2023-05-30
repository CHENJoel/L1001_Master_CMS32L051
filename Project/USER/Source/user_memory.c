#include "user_memory.h"

/*��norflash������ݽ��г�ʼ��*/
void norflash_data_init(void)
{
    printlog("norflash_data_init\r");
    printlog("search_norflash_ranklist\r");
    search_norflash_ranklist();        // ����flash�е��Զ���&�ղص�Ч˳���
    verify_factoryreset_effect_norflash(); // ����Ƿ���Ҫ��ʼ���Դ���Ч
}

/*У���Ч�����Ƿ�Ҫ�ָ���������*/
void verify_factoryreset_effect_norflash(void)
{
    verify_Typedef verify;
    get_effect_verify(&verify);
    if (strcmp(&verify, EF_MEM_VERIFY) != 0) // flashδ����У����Ϣ
    {
        printlog("verify_factoryreset_effect_norflash not pass \r\r");
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
        printlog("get_original_effect num error\n");
        return 0;
    }
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.effect.efdata[efnum], sizeof(Efdetail_TypeDef));
    return 1;
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
    ef_ranklist_TypeDef memranklist; // flash�洢��Ϣ
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
    get_originalef_ranklist(&memranklist);                      // ��ȡ�洢�ĵ�Ч˳���
    if (compare_same_ranklist(&allranklist, &memranklist) == 0) // ���ݲ�һ��ʱ
    {
        save_originalef_ranklist(&allranklist); // ����ѯ������˳���Ϊ׼
    }

    /*�����Զ����Ч���б���Ϣ*/
    get_originalef_ranklist(&memranklist);                      // ��ȡ�洢�ĵ�Ч˳���
    if (compare_same_ranklist(&oriranklist, &memranklist) == 0) // ���ݲ�һ��ʱ
    {
        save_originalef_ranklist(&oriranklist); // ����ѯ������˳���Ϊ׼
    }

    /*�����ղص�Ч���б���Ϣ*/
    get_favoritesef_ranklist(&memranklist);                     // ��ȡ�洢�ĵ�Ч˳���
    if (compare_same_ranklist(&favranklist, &memranklist) == 0) // ���ݲ�һ��ʱ
    {
        save_favoritesef_ranklist(&favranklist); // ����ѯ������˳���Ϊ׼
    }

    // // // // // if (oriranklist.num == memranklist.num)
    // // // // // { // ��ѯ�����б�ߴ���洢����һ��
    // // // // //     if (oriranklist.num != 0)
    // // // // //     {
    // // // // //         temp = 0;
    // // // // //         for (i = 0; i < oriranklist.num; i++)
    // // // // //         {
    // // // // //             for (j = 0; j < oriranklist.num; j++)
    // // // // //             {
    // // // // //                 if (oriranklist.list[j] == memranklist.list[i]) // ��ѯ�б��а������������洢�б�Ҳ����
    // // // // //                 {
    // // // // //                     temp++;
    // // // // //                 }
    // // // // //             }
    // // // // //         }
    // // // // //         if (temp != oriranklist.num) // ��ѯ�б���洢�б������������ͬ���ݲ������б�ߴ磬˵�����������������б��У���˳���б�ָ�Ĭ��ֵ
    // // // // //         {
    // // // // //             save_originalef_ranklist(&oriranklist);
    // // // // //             printlog("favorites ranklist.list initialize to default\r");
    // // // // //             configASSERT(0);
    // // // // //         }
    // // // // //     }
    // // // // // }
    // // // // // else // ��һ�£�������������д���µ�˳���б�
    // // // // // {
    // // // // //     save_originalef_ranklist(&oriranklist);
    // // // // //     printlog("original ranklist.list initialize to default\r");
    // // // // //     configASSERT(0);
    // // // // // }
    // // // // // /*�����ղص�Ч���б���Ϣ*/
    // // // // // get_favoritesef_ranklist(&memranklist); // ��ȡ�洢���ղص�Ч��˳���
    // // // // // if (favranklist.num == memranklist.num)
    // // // // // { // ��ѯ�����б�ߴ���洢����һ��
    // // // // //     if (favranklist.num != 0)
    // // // // //     {
    // // // // //         temp = 0;
    // // // // //         for (i = 0; i < favranklist.num; i++)
    // // // // //         {
    // // // // //             for (j = 0; j < favranklist.num; j++)
    // // // // //             {
    // // // // //                 if (favranklist.list[j] == memranklist.list[i]) // ��ѯ�б��а������������洢�б�Ҳ����
    // // // // //                 {
    // // // // //                     temp++;
    // // // // //                 }
    // // // // //             }
    // // // // //         }
    // // // // //         if (temp != favranklist.num) // ��ѯ�б���洢�б������������ͬ���ݲ������б�ߴ磬˵�����������������б��У���˳���б�ָ�Ĭ��ֵ
    // // // // //         {
    // // // // //             save_favoritesef_ranklist(&favranklist);
    // // // // //             printlog("favorites ranklist.list initialize to default\r");
    // // // // //             configASSERT(0);
    // // // // //         }
    // // // // //     }
    // // // // // }
    // // // // // else // ��һ�£�������������д���µ�˳���б�
    // // // // // {
    // // // // //     save_favoritesef_ranklist(&favranklist);
    // // // // //     printlog("favorites ranklist.list initialize to default\r");
    // // // // //     configASSERT(0);
    // // // // // }
#ifdef printlog_enabled
    printf("original ranklist.sum:%d\r", oriranklist.num);
    printf("favorites ranklist.sum:%d\r", favranklist.num);
#endif
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

/*�洢ȫ����Ч�б�*/
void save_allef_ranklist(ef_ranklist_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.all_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*�洢�Զ����Ч�б�*/
void save_originalef_ranklist(ef_ranklist_TypeDef *p)
{

    // // // printlog("save_originalef_ranklist\r");
    // // // printf("list addr : 0x%x\r\n",p);
    // // // printhex_my(p,10);
    // // // print_ef_ranklist(p);

    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.original_ef_ranklist, sizeof(ef_ranklist_TypeDef));
    // // printlog("FlashSPI_Insert\r");
    // // print_get_original_ef_ranklist();
}
/*�洢�ղص�Ч�б�*/
void save_favoritesef_ranklist(ef_ranklist_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.favorites_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*��˳�����ɾ������*/
uint8_t delete_num_from_ranklist(ef_ranklist_TypeDef *p, uint8_t efnum)
{
    ef_ranklist_TypeDef newranklist; // ����Ϣ
    uint8_t i, j;
    memset(&newranklist, 0, sizeof(newranklist));
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
            newranklist.list[j++] = p->list[i]; // ��ԭ˳���������˳������˱�ɾ���ĵ�Ч������
        }
    }
    if (j == p->num) // ��������ԭ˳���ߴ�һ�£�˵��˳����в����ڱ�ɾ��������
    {
        printlog("delete wrong number in rank list\r");
        return 0;
    }
    else
    {
        newranklist.num = j; // ����˳���ߴ�
        memcpy(p, &newranklist, sizeof(newranklist)); // ����˳���������
        printlog("delete number in rank list successful\r");
        return 1;
    }
}

/*ɾ���Զ����Ч*/
uint8_t delete_original_ef(uint8_t efnum)
{
    ef_ranklist_TypeDef newranklist; // ԭ��Ϣ
    Efdetail_TypeDef ef;
    uint8_t i, j;
    if (efnum < original_ef_basenum)
    {
        printlog("delete original error\r");
        return 0;
    }
    /*�޸ĸõ�Ч����*/
    get_original_effect(&ef, efnum);
    ef.Attribute = EMPTY; // �޸�������Ϣ
    save_effect(&ef, efnum);

    /*��ȫ����Ч˳�����ɾ���õ�Ч*/
    get_allef_ranklist(&newranklist);              // ��ȡȫ����Ч˳���
    delete_num_from_ranklist(&newranklist, efnum); // ɾ������
    save_allef_ranklist(&newranklist);             // ����ȫ����Ч˳���

    /*���Զ����Ч˳�����ɾ���õ�Ч*/
    get_originalef_ranklist(&newranklist);         // ��ȡ�Զ����Ч˳���
    delete_num_from_ranklist(&newranklist, efnum); // ɾ������
    save_originalef_ranklist(&newranklist);        // �����Զ����Ч˳���;

    /*���ղص�Ч˳�����ɾ���õ�Ч*/
    get_favoritesef_ranklist(&newranklist);        // ��ȡ�ղص�Ч˳���
    delete_num_from_ranklist(&newranklist, efnum); // ɾ������
    save_favoritesef_ranklist(&newranklist);       // �����ղص�Ч˳���
}

/*�����Զ����Ч*/
uint8_t add_original_ef(Efdetail_TypeDef *p, uint8_t efnum)
{
    ef_ranklist_TypeDef newranklist; // ����Ϣ
    uint8_t i, j;
    if (efnum < original_ef_basenum)
    {
        printlog("add_original_ef error\r");
        return 0;
    }
    get_originalef_ranklist(&newranklist); // ��ȡԭ��Ϣ
    p->Attribute = ORIGIN;               // ���µ�Ч����
    save_effect(p, efnum);
    for (i = 0; i < newranklist.num; i++)
    {
        if (newranklist.list[i] == efnum) // ԭ���б��Ѵ��� �򲻸���˳���б�
        {

            return 1;
        }
    }
    newranklist.list[newranklist.num] = efnum;
    newranklist.num++;
    save_originalef_ranklist(&newranklist);
    return 1;
}
