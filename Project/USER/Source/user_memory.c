#include "user_memory.h"

/*У���Ч��ʼ������*/
void norflash_effect_datainit_verify(void)
{
    verify_Typedef verify;
    get_effect_verify(&verify);
    if (strcmp(&verify, EF_MEM_VERIFY) != 0) // flashδ����У����Ϣ
    {
        printlog("norflash_effect_datainit_verify not pass \r\r");
        sprintf(&verify, EF_MEM_VERIFY);
        init_built_in_ef_to_norflash(); // ��ʼ����Ч��Ϣ
        save_effect_verify(&verify);    // ����У����Ϣ
    }
    else
    {
        printlog("norflash_effect_datainit_verify  pass \r\r");
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

/*��norflash������ݽ��г�ʼ��*/
void norflash_data_init(void)
{
    printlog("norflash_data_init\r");
    printlog("init_original_ranklist\r");
    init_original_ranklist();// ��ʼ���Զ����Ч�б�
    norflash_effect_datainit_verify();
}
/*��ʼ�����õ�Ч���ⲿnorflash��*/
void init_built_in_ef_to_norflash(void)
{
    Efdetail_TypeDef ef;
    ef_ranklist_TypeDef orgef_ranklist,allef_ranklist;// �Զ����Ч˳��� ȫ����Ч˳���
    uint8_t i, j;
    p_arry arry;
    for (i = 0; i < built_in_ef_num; i++)
    {
        memset(&ef, 0, sizeof(ef));           // ��������
        strcpy(&ef.Name, dfdata[i].name);     // ������Ч����
        ef.EffectType = dfdata[i].EffectType; // ������Ч����
        ef.Flow = dfdata[i].Flow;             // ������̬Ч��
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
    printlog("init_built_in_ef_to_norflash\r");
    memset((uint8_t *)&allef_ranklist, 0, sizeof(allef_ranklist));
    get_original_ranklist(&orgef_ranklist);
    allef_ranklist.num = orgef_ranklist.num + built_in_ef_num;
    memcpy((uint8_t *)&allef_ranklist.list + built_in_ef_num, (uint8_t *)&orgef_ranklist.list, orgef_ranklist.num);
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

/*��ʼ���Զ����Ч�б�*/
void init_original_ranklist(void)
{
    uint8_t i, j;
    uint8_t temp;
    ef_ranklist_TypeDef memranklist; // ԭ��Ϣ
    ef_ranklist_TypeDef newranklist; // ����Ϣ
    Efdetail_TypeDef ef;
    newranklist.num = 0;
    for (i = 0; i < original_ef_num; i++)
    {
        FLASHSPI_PageRead((uint8_t *)&temp, (uint32_t)&NORFLASH->efdata.data.effect.efdata[original_ef_basenum + i].Attribute, 1); // ��ȡ��Ч����
        if (temp < EMPTY)
        {                                                                // �ǿյ�Ч��ԭʼ/�ղ�����
            newranklist.list[newranklist.num] = original_ef_basenum + i; // ��¼��ǰ��Ч����
            newranklist.num++;
        }
    }
    get_original_ranklist(&memranklist); // ��ȡ�洢��˳���б�
    if (newranklist.num == memranklist.num)
    { // ��ѯ�����б�ߴ���洢����һ��
        if (newranklist.num != 0)
        {
            temp = 0;
            for (i = 0; i < newranklist.num; i++)
            {
                for (j = 0; j < newranklist.num; j++)
                {
                    if (newranklist.list[j] == memranklist.list[i]) // ��ѯ�б��а������������洢�б�Ҳ����
                    {
                        temp++;
                    }
                }
            }
            if (temp != newranklist.num) // ��ѯ�б���洢�б������������ͬ���ݲ������б�ߴ磬˵�����������������б��У���˳���б�ָ�Ĭ��ֵ
            {
                save_originalef_ranklist(&newranklist);
                printlog("original ranklist.list initialize to default\r");
                configASSERT(0);
            }
        }
    }
    else // ��һ�£�������������д���µ�˳���б�
    {
        save_originalef_ranklist(&newranklist);
        printlog("original ranklist.list initialize to default\r");
        configASSERT(0);
    }
#ifdef printlog_enabled
    printf("original ranklist.sum:%d\r", newranklist.num);
#endif
}


/*��ȡ�Զ����Ч�б�*/
void get_original_ranklist(ef_ranklist_TypeDef *p)
{
    memset(p, 0, sizeof(ef_ranklist_TypeDef));
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.original_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}

/*�洢�Զ����Ч�б�*/
void save_originalef_ranklist(ef_ranklist_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.original_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*�洢ȫ����Ч�б�*/
void save_allef_ranklist(ef_ranklist_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.all_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}


/*ɾ���Զ����Ч*/
uint8_t delete_original_ef(uint8_t efnum)
{
    ef_ranklist_TypeDef memranklist; // ԭ��Ϣ
    ef_ranklist_TypeDef newranklist; // ����Ϣ
    Efdetail_TypeDef ef;
    uint8_t i, j;

    if (efnum < original_ef_basenum)
    {
        printlog("delete original error\r");
        return 0;
    }
    get_original_ranklist(&memranklist); // ��ȡԭ��Ϣ
    get_original_effect(&ef, efnum);
    ef.Attribute = EMPTY; // �޸�������Ϣ
    save_effect(&ef, efnum);
    if (memranklist.num == 0)
    {
        printlog("delete original error\r");
        return 0;
    }
    j = 0;
    for (i = 0; i < memranklist.num; i++)
    {
        if (memranklist.list[i] != efnum)
        {
            newranklist.list[j++] = memranklist.list[i]; // ��ԭ˳���������˳������˱�ɾ���ĵ�Ч������
        }
    }
    if (j == memranklist.num) // ��������ԭ˳���ߴ�һ�£�˵��˳����в����ڱ�ɾ��������
    {
        printlog("delete original error\r");
        return 0;
    }
    else
    {
        newranklist.num = j; // ����˳���ߴ�
        save_originalef_ranklist(&newranklist);
        printlog("delete_original_ef\r");
        return 1;
    }
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
    get_original_ranklist(&newranklist); // ��ȡԭ��Ϣ
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
