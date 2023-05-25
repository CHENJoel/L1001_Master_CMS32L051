#include "user_memory.h"

/*校验灯效初始化数据*/
void norflash_effect_datainit_verify(void)
{
    verify_Typedef verify;
    get_effect_verify(&verify);
    if (strcmp(&verify, EF_MEM_VERIFY) != 0) // flash未存有校验信息
    {
        printlog("norflash_effect_datainit_verify not pass \r\r");
        sprintf(&verify, EF_MEM_VERIFY);
        init_built_in_ef_to_norflash(); // 初始化灯效信息
        save_effect_verify(&verify);    // 存入校验信息
    }
    else
    {
        printlog("norflash_effect_datainit_verify  pass \r\r");
    }
}

/*获取灯效校验信息*/
void get_effect_verify(verify_Typedef *p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.verify, sizeof(verify_Typedef));
}
/*保存灯效校验信息*/
void save_effect_verify(verify_Typedef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.verify, sizeof(verify_Typedef));
    printlog("save_effect_verify\r");
}

/*对norflash里的数据进行初始化*/
void norflash_data_init(void)
{
    printlog("norflash_data_init\r");
    printlog("init_original_ranklist\r");
    init_original_ranklist();// 初始化自定义灯效列表
    norflash_effect_datainit_verify();
}
/*初始化内置灯效至外部norflash内*/
void init_built_in_ef_to_norflash(void)
{
    Efdetail_TypeDef ef;
    ef_ranklist_TypeDef orgef_ranklist,allef_ranklist;// 自定义灯效顺序表 全部灯效顺序表
    uint8_t i, j;
    p_arry arry;
    for (i = 0; i < built_in_ef_num; i++)
    {
        memset(&ef, 0, sizeof(ef));           // 数据清零
        strcpy(&ef.Name, dfdata[i].name);     // 拷贝灯效名字
        ef.EffectType = dfdata[i].EffectType; // 拷贝灯效类型
        ef.Flow = dfdata[i].Flow;             // 拷贝动态效果
        arry = dfdata[i].data;
        for (j = 0; j < 8; j++) // 拷贝颜色数据
        {
            if ((*(*(arry + j) + 0) == 255) && (*(*(arry + j) + 1) == 255) && (*(*(arry + j) + 2) == 255) && (*(*(arry + j) + 3) == 255))
            {
                break; // 遇到结束颜色标志,结束拷贝
            }
            ef.EfColorInf.ColorID[j].color.R = *(*(arry + j) + 0);
            ef.EfColorInf.ColorID[j].color.G = *(*(arry + j) + 1);
            ef.EfColorInf.ColorID[j].color.B = *(*(arry + j) + 2);
            ef.EfColorInf.ColorID[j].color.W = *(*(arry + j) + 3);
            ef.EfColorInf.colorNum++;
        }
        ef.Speed = default_ef_Speed;                   // 缺省值
        ef.Brightness1 = default_ef_Brightness1;       // 缺省值
        ef.Brightness2 = default_ef_Brightness2;       // 缺省值
        ef.MicSensitivity = default_ef_MicSensitivity; // 缺省值
        ef.Attribute = default_ef_Attribute;           // 缺省值
        ef.Direction = default_ef_Direction;           // 缺省值
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

/*存储灯效*/
void save_effect(Efdetail_TypeDef *p, uint8_t efnum)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.effect.efdata[efnum], sizeof(Efdetail_TypeDef));
}
/*存储自定义灯效*/
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

/*读出灯效*/
void get_effect(Efdetail_TypeDef *p, uint8_t efnum)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.effect.efdata[efnum], sizeof(Efdetail_TypeDef));
}
/*读出自定义灯效*/
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

/*初始化自定义灯效列表*/
void init_original_ranklist(void)
{
    uint8_t i, j;
    uint8_t temp;
    ef_ranklist_TypeDef memranklist; // 原信息
    ef_ranklist_TypeDef newranklist; // 新信息
    Efdetail_TypeDef ef;
    newranklist.num = 0;
    for (i = 0; i < original_ef_num; i++)
    {
        FLASHSPI_PageRead((uint8_t *)&temp, (uint32_t)&NORFLASH->efdata.data.effect.efdata[original_ef_basenum + i].Attribute, 1); // 读取灯效属性
        if (temp < EMPTY)
        {                                                                // 非空灯效，原始/收藏属性
            newranklist.list[newranklist.num] = original_ef_basenum + i; // 记录当前灯效索引
            newranklist.num++;
        }
    }
    get_original_ranklist(&memranklist); // 读取存储的顺序列表
    if (newranklist.num == memranklist.num)
    { // 轮询出的列表尺寸与存储区的一致
        if (newranklist.num != 0)
        {
            temp = 0;
            for (i = 0; i < newranklist.num; i++)
            {
                for (j = 0; j < newranklist.num; j++)
                {
                    if (newranklist.list[j] == memranklist.list[i]) // 轮询列表中包含的索引，存储列表也包含
                    {
                        temp++;
                    }
                }
            }
            if (temp != newranklist.num) // 轮询列表与存储列表包含的索引相同内容不等于列表尺寸，说明出现其他索引在列表中，则顺序列表恢复默认值
            {
                save_originalef_ranklist(&newranklist);
                printlog("original ranklist.list initialize to default\r");
                configASSERT(0);
            }
        }
    }
    else // 不一致，代表数据有误，写入新的顺序列表
    {
        save_originalef_ranklist(&newranklist);
        printlog("original ranklist.list initialize to default\r");
        configASSERT(0);
    }
#ifdef printlog_enabled
    printf("original ranklist.sum:%d\r", newranklist.num);
#endif
}


/*获取自定义灯效列表*/
void get_original_ranklist(ef_ranklist_TypeDef *p)
{
    memset(p, 0, sizeof(ef_ranklist_TypeDef));
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.original_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}

/*存储自定义灯效列表*/
void save_originalef_ranklist(ef_ranklist_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.original_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*存储全部灯效列表*/
void save_allef_ranklist(ef_ranklist_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.all_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}


/*删除自定义灯效*/
uint8_t delete_original_ef(uint8_t efnum)
{
    ef_ranklist_TypeDef memranklist; // 原信息
    ef_ranklist_TypeDef newranklist; // 新信息
    Efdetail_TypeDef ef;
    uint8_t i, j;

    if (efnum < original_ef_basenum)
    {
        printlog("delete original error\r");
        return 0;
    }
    get_original_ranklist(&memranklist); // 获取原信息
    get_original_effect(&ef, efnum);
    ef.Attribute = EMPTY; // 修改属性信息
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
            newranklist.list[j++] = memranklist.list[i]; // 将原顺序表拷贝至新顺序表（除了被删除的灯效索引）
        }
    }
    if (j == memranklist.num) // 拷贝数与原顺序表尺寸一致，说明顺序表中不存在被删除的索引
    {
        printlog("delete original error\r");
        return 0;
    }
    else
    {
        newranklist.num = j; // 更新顺序表尺寸
        save_originalef_ranklist(&newranklist);
        printlog("delete_original_ef\r");
        return 1;
    }
}

/*新增自定义灯效*/
uint8_t add_original_ef(Efdetail_TypeDef *p, uint8_t efnum)
{
    ef_ranklist_TypeDef newranklist; // 新信息
    uint8_t i, j;
    if (efnum < original_ef_basenum)
    {
        printlog("add_original_ef error\r");
        return 0;
    }
    get_original_ranklist(&newranklist); // 获取原信息
    p->Attribute = ORIGIN;               // 更新灯效属性
    save_effect(p, efnum);
    for (i = 0; i < newranklist.num; i++)
    {
        if (newranklist.list[i] == efnum) // 原有列表已存在 则不更新顺序列表
        {

            return 1;
        }
    }
    newranklist.list[newranklist.num] = efnum;
    newranklist.num++;
    save_originalef_ranklist(&newranklist);
    return 1;
}
