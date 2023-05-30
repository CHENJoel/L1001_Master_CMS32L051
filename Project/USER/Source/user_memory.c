#include "user_memory.h"

/*对norflash里的数据进行初始化*/
void norflash_data_init(void)
{
    printlog("norflash_data_init\r");
    printlog("search_norflash_ranklist\r");
    search_norflash_ranklist();        // 检索flash中的自定义&收藏灯效顺序表
    verify_factoryreset_effect_norflash(); // 检查是否需要初始化自带灯效
}

/*校验灯效数据是否要恢复出厂设置*/
void verify_factoryreset_effect_norflash(void)
{
    verify_Typedef verify;
    get_effect_verify(&verify);
    if (strcmp(&verify, EF_MEM_VERIFY) != 0) // flash未存有校验信息
    {
        printlog("verify_factoryreset_effect_norflash not pass \r\r");
        memset(&verify, 0, sizeof(verify)); // 清零
        sprintf(&verify, EF_MEM_VERIFY);
        copy_built_in_ef_to_norflash(); // 初始化灯效信息
        save_effect_verify(&verify);    // 存入校验信息
    }
    else
    {
        printlog("verify_factoryreset_effect_norflash  pass \r\r");
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


/*内置灯效拷贝至外部norflash内*/
void copy_built_in_ef_to_norflash(void)
{
    Efdetail_TypeDef ef;
    ef_ranklist_TypeDef orgef_ranklist,allef_ranklist;// 自定义灯效顺序表 全部灯效顺序表
    uint8_t i, j;
    p_arry arry;
    for (i = 0; i < built_in_ef_num; i++)
    {
        memset(&ef, 0, sizeof(ef));              // 数据清零
        ef.namelenght = strlen(dfdata[i].name); // 灯效名字长度
        strcpy(&ef.Name, dfdata[i].name);       // 拷贝灯效名字
        ef.EffectType = dfdata[i].EffectType;    // 拷贝灯效类型
        ef.Flow = dfdata[i].Flow;                // 拷贝动态效果
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
    printlog("copy_built_in_ef_to_norflash\r");
    memset((uint8_t *)&allef_ranklist, 0, sizeof(allef_ranklist));
    get_originalef_ranklist(&orgef_ranklist);
    allef_ranklist.num = orgef_ranklist.num + built_in_ef_num;
    memcpy((uint8_t *)&allef_ranklist.list + built_in_ef_num, (uint8_t *)&orgef_ranklist.list, orgef_ranklist.num);// 自定义列表拷贝至内置灯效后面
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

/*比较两个表是否包含的数据是否一样*/
uint8_t compare_same_ranklist(ef_ranklist_TypeDef *ranklist1, ef_ranklist_TypeDef *ranklist2)
{
    uint8_t i, j;
    uint8_t temp;
    if (ranklist2->num == ranklist1->num) // 数量一样
    {
        if (ranklist1->num != 0)
        {
            temp = 0;
            for (i = 0; i < ranklist1->num; i++)
            {
                for (j = 0; j < ranklist1->num; j++)
                {
                    if (ranklist1->list[j] == ranklist2->list[i]) // 轮询列表中包含的索引，存储列表也包含
                    {
                        temp++; // 记录两表中相同数据的个数
                    }
                }
            }
            if (temp == ranklist1->num) // 说明两表中包含的数据一样(顺序可能不一致)
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

/*检索flash中的自定义&收藏灯效顺序表*/
void search_norflash_ranklist(void)
{
    uint8_t i;
    uint8_t temp;
    ef_ranklist_TypeDef memranklist; // flash存储信息
    ef_ranklist_TypeDef allranklist; // 自定义灯效列表
    ef_ranklist_TypeDef oriranklist; // 自定义灯效列表
    ef_ranklist_TypeDef favranklist; // 收藏灯效列表
    Efdetail_TypeDef ef;
    memset(&allranklist, 0, sizeof(allranklist)); // 数据清零
    memset(&oriranklist, 0, sizeof(oriranklist)); // 数据清零
    memset(&favranklist, 0, sizeof(favranklist)); // 数据清零
    /*检索flash中的灯效信息*/
    for (i = 0; i < built_in_ef_num; i++) // 检索内置灯效信息
    {
        FLASHSPI_PageRead((uint8_t *)&temp, (uint32_t)&NORFLASH->efdata.data.effect.efdata[built_in_ef_basenum + i].Attribute, 1); // 读取灯效属性
        if (temp == ORIGIN || temp == FAVORITES)
        {                                                                // 非空灯效，原始/收藏属性
            allranklist.list[allranklist.num] = built_in_ef_basenum + i; // 记录当前灯效索引
            allranklist.num++;
            if (temp == FAVORITES)
            {                                                                // 收藏灯效
                favranklist.list[favranklist.num] = built_in_ef_basenum + i; // 记录当前灯效索引
                favranklist.num++;
            }
        }
    }
    for (i = 0; i < original_ef_num; i++) // 检索自定义灯效信息
    {
        FLASHSPI_PageRead((uint8_t *)&temp, (uint32_t)&NORFLASH->efdata.data.effect.efdata[original_ef_basenum + i].Attribute, 1); // 读取灯效属性
        if (temp == ORIGIN || temp == FAVORITES)
        {                                                                // 非空灯效，原始/收藏属性
            allranklist.list[allranklist.num] = built_in_ef_basenum + i; // 记录当前灯效索引
            allranklist.num++;
            oriranklist.list[oriranklist.num] = original_ef_basenum + i; // 记录当前灯效索引
            oriranklist.num++;
            if (temp == FAVORITES) // 收藏灯效
            {
                favranklist.list[favranklist.num] = original_ef_basenum + i; // 记录当前灯效索引
                favranklist.num++;
            }
        }
    }
    /*分析全部灯效的列表信息*/
    get_originalef_ranklist(&memranklist);                      // 读取存储的灯效顺序表
    if (compare_same_ranklist(&allranklist, &memranklist) == 0) // 数据不一致时
    {
        save_originalef_ranklist(&allranklist); // 以轮询出来的顺序表为准
    }

    /*分析自定义灯效的列表信息*/
    get_originalef_ranklist(&memranklist);                      // 读取存储的灯效顺序表
    if (compare_same_ranklist(&oriranklist, &memranklist) == 0) // 数据不一致时
    {
        save_originalef_ranklist(&oriranklist); // 以轮询出来的顺序表为准
    }

    /*分析收藏灯效的列表信息*/
    get_favoritesef_ranklist(&memranklist);                     // 读取存储的灯效顺序表
    if (compare_same_ranklist(&favranklist, &memranklist) == 0) // 数据不一致时
    {
        save_favoritesef_ranklist(&favranklist); // 以轮询出来的顺序表为准
    }

    // // // // // if (oriranklist.num == memranklist.num)
    // // // // // { // 轮询出的列表尺寸与存储区的一致
    // // // // //     if (oriranklist.num != 0)
    // // // // //     {
    // // // // //         temp = 0;
    // // // // //         for (i = 0; i < oriranklist.num; i++)
    // // // // //         {
    // // // // //             for (j = 0; j < oriranklist.num; j++)
    // // // // //             {
    // // // // //                 if (oriranklist.list[j] == memranklist.list[i]) // 轮询列表中包含的索引，存储列表也包含
    // // // // //                 {
    // // // // //                     temp++;
    // // // // //                 }
    // // // // //             }
    // // // // //         }
    // // // // //         if (temp != oriranklist.num) // 轮询列表与存储列表包含的索引相同内容不等于列表尺寸，说明出现其他索引在列表中，则顺序列表恢复默认值
    // // // // //         {
    // // // // //             save_originalef_ranklist(&oriranklist);
    // // // // //             printlog("favorites ranklist.list initialize to default\r");
    // // // // //             configASSERT(0);
    // // // // //         }
    // // // // //     }
    // // // // // }
    // // // // // else // 不一致，代表数据有误，写入新的顺序列表
    // // // // // {
    // // // // //     save_originalef_ranklist(&oriranklist);
    // // // // //     printlog("original ranklist.list initialize to default\r");
    // // // // //     configASSERT(0);
    // // // // // }
    // // // // // /*分析收藏灯效的列表信息*/
    // // // // // get_favoritesef_ranklist(&memranklist); // 读取存储的收藏灯效的顺序表
    // // // // // if (favranklist.num == memranklist.num)
    // // // // // { // 轮询出的列表尺寸与存储区的一致
    // // // // //     if (favranklist.num != 0)
    // // // // //     {
    // // // // //         temp = 0;
    // // // // //         for (i = 0; i < favranklist.num; i++)
    // // // // //         {
    // // // // //             for (j = 0; j < favranklist.num; j++)
    // // // // //             {
    // // // // //                 if (favranklist.list[j] == memranklist.list[i]) // 轮询列表中包含的索引，存储列表也包含
    // // // // //                 {
    // // // // //                     temp++;
    // // // // //                 }
    // // // // //             }
    // // // // //         }
    // // // // //         if (temp != favranklist.num) // 轮询列表与存储列表包含的索引相同内容不等于列表尺寸，说明出现其他索引在列表中，则顺序列表恢复默认值
    // // // // //         {
    // // // // //             save_favoritesef_ranklist(&favranklist);
    // // // // //             printlog("favorites ranklist.list initialize to default\r");
    // // // // //             configASSERT(0);
    // // // // //         }
    // // // // //     }
    // // // // // }
    // // // // // else // 不一致，代表数据有误，写入新的顺序列表
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

/*获取全部灯效列表*/
void get_allef_ranklist(ef_ranklist_TypeDef *p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.all_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*获取自定义灯效列表*/
void get_originalef_ranklist(ef_ranklist_TypeDef *p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.original_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*获取收藏灯效列表*/
void get_favoritesef_ranklist(ef_ranklist_TypeDef *p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.favorites_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}

/*存储全部灯效列表*/
void save_allef_ranklist(ef_ranklist_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.all_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*存储自定义灯效列表*/
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
/*存储收藏灯效列表*/
void save_favoritesef_ranklist(ef_ranklist_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.favorites_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*从顺序表中删除参数*/
uint8_t delete_num_from_ranklist(ef_ranklist_TypeDef *p, uint8_t efnum)
{
    ef_ranklist_TypeDef newranklist; // 新信息
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
            newranklist.list[j++] = p->list[i]; // 将原顺序表拷贝至新顺序表（除了被删除的灯效索引）
        }
    }
    if (j == p->num) // 拷贝数与原顺序表尺寸一致，说明顺序表中不存在被删除的索引
    {
        printlog("delete wrong number in rank list\r");
        return 0;
    }
    else
    {
        newranklist.num = j; // 更新顺序表尺寸
        memcpy(p, &newranklist, sizeof(newranklist)); // 更新顺序表内索引
        printlog("delete number in rank list successful\r");
        return 1;
    }
}

/*删除自定义灯效*/
uint8_t delete_original_ef(uint8_t efnum)
{
    ef_ranklist_TypeDef newranklist; // 原信息
    Efdetail_TypeDef ef;
    uint8_t i, j;
    if (efnum < original_ef_basenum)
    {
        printlog("delete original error\r");
        return 0;
    }
    /*修改该灯效属性*/
    get_original_effect(&ef, efnum);
    ef.Attribute = EMPTY; // 修改属性信息
    save_effect(&ef, efnum);

    /*从全部灯效顺序表中删除该灯效*/
    get_allef_ranklist(&newranklist);              // 获取全部灯效顺序表
    delete_num_from_ranklist(&newranklist, efnum); // 删除索引
    save_allef_ranklist(&newranklist);             // 保存全部灯效顺序表

    /*从自定义灯效顺序表中删除该灯效*/
    get_originalef_ranklist(&newranklist);         // 获取自定义灯效顺序表
    delete_num_from_ranklist(&newranklist, efnum); // 删除索引
    save_originalef_ranklist(&newranklist);        // 保存自定义灯效顺序表;

    /*从收藏灯效顺序表中删除该灯效*/
    get_favoritesef_ranklist(&newranklist);        // 获取收藏灯效顺序表
    delete_num_from_ranklist(&newranklist, efnum); // 删除索引
    save_favoritesef_ranklist(&newranklist);       // 保存收藏灯效顺序表
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
    get_originalef_ranklist(&newranklist); // 获取原信息
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
