#include "user_memory.h"


// /*64k擦除灯效数据所在block区*/
// void EffectData_BlockErase_64k(void)
// {
//     uint32_t i;

// }

/*对norflash里的数据进行初始化*/
void norflash_data_init(void)
{
    printlog("norflash_data_init\r");
    printlog("search_norflash_ranklist\r");
    search_norflash_ranklist();            // 检索flash中的自定义&收藏灯效顺序表
    verify_ranklist();                     // 校验顺序表内数据是否正确
    verify_factoryreset_effect_norflash(); // 检查是否需要初始化自带灯效
}

/*校验全部灯效顺序表内数据是否正确*/
uint8_t verify_allef_ranklist(void)
{
    ef_ranklist_TypeDef ranklist;
    uint8_t i;
    uint8_t err = 0;
    get_allef_ranklist(&ranklist); // 获取原信息
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
        memset(&ranklist, 0, sizeof(ranklist)); // 置零
        save_allef_ranklist(&ranklist);
    }
    return err;
}
/*校验自定义灯效顺序表内数据是否正确*/
uint8_t verify_originalef_ranklist(void)
{
    ef_ranklist_TypeDef ranklist;
    uint8_t i;
    uint8_t err = 0;
    get_originalef_ranklist(&ranklist); // 获取原信息
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
        memset(&ranklist, 0, sizeof(ranklist)); // 置零
        save_originalef_ranklist(&ranklist);
    }
    return err;
}
/*校验自定义灯效顺序表内数据是否正确*/
uint8_t verify_favoritesef_ranklist(void)
{
    ef_ranklist_TypeDef ranklist;
    uint8_t i;
    uint8_t err = 0;
    get_favoritesef_ranklist(&ranklist); // 获取原信息
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
        memset(&ranklist, 0, sizeof(ranklist)); // 置零
        save_favoritesef_ranklist(&ranklist);
    }
    return err;
}
/*校验自定义灯效顺序表内数据是否正确*/
uint8_t verify_playlist_ranklist(void)
{
    playlist_ranklist_TypeDef ranklist;
    uint8_t i;
    uint8_t err = 0;
    get_playlist_ranklist(&ranklist); // 获取原信息
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
        memset(&ranklist, 0, sizeof(ranklist)); // 置零
        save_playlist_ranklist(&ranklist);
    }
    return err;
}

/*校验顺序表内数据是否正确*/
void verify_ranklist(void )
{
    verify_allef_ranklist();
    verify_originalef_ranklist();
    verify_favoritesef_ranklist();
    verify_playlist_ranklist();
}

/*校验灯效数据是否要恢复出厂设置*/
void verify_factoryreset_effect_norflash(void)
{
    verify_Typedef verify;
    get_effect_verify(&verify);
    if (strcmp(&verify, EF_MEM_VERIFY) != 0) // flash未存有校验信息
    {
        printlog("verify_factoryreset_effect_norflash not pass \r\r");
        printlog("Erase effect data block...\r");
        schedule_factory_reset();
        clear_all_ef_ranklist();            // 删除灯效列表
        init_default_playlist();            // 出厂化内置播放表信息
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

/* 出厂化内置播放表信息*/
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
    ef_ranklist_TypeDef ranklist; // flash存储信息
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
    get_originalef_ranklist(&ranklist);                      // 读取存储的灯效顺序表
    if (compare_same_ranklist(&allranklist, &ranklist) == 0) // 数据不一致时
    {
        save_originalef_ranklist(&allranklist); // 以轮询出来的顺序表为准
    }

    /*分析自定义灯效的列表信息*/
    get_originalef_ranklist(&ranklist);                      // 读取存储的灯效顺序表
    if (compare_same_ranklist(&oriranklist, &ranklist) == 0) // 数据不一致时
    {
        save_originalef_ranklist(&oriranklist); // 以轮询出来的顺序表为准
    }

    /*分析收藏灯效的列表信息*/
    get_favoritesef_ranklist(&ranklist);                     // 读取存储的灯效顺序表
    if (compare_same_ranklist(&favranklist, &ranklist) == 0) // 数据不一致时
    {
        save_favoritesef_ranklist(&favranklist); // 以轮询出来的顺序表为准
    }
#ifdef printlog_enabled
    printf("original ranklist.sum:%d\r", oriranklist.num);
    printf("favorites ranklist.sum:%d\r", favranklist.num);
#endif
}

/*******************************************************************************************************************************************************/

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
        printf("num:%d\r",efnum);
        printlog("get_original_effect num error\n");
        return 0;
    }
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.effect.efdata[efnum], sizeof(Efdetail_TypeDef));
    return 1;
}
/*读出播放详情*/
void get_playdetail(playdetail_TypeDef *p, uint8_t playnum)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.play.pldata[playnum], sizeof(playdetail_TypeDef));
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
/*获取播放列表的顺序表*/
void get_playlist_ranklist(playlist_ranklist_TypeDef *p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.playlist_ranklist, sizeof(playlist_ranklist_TypeDef));
}
/*获取播放列表的名字*/
void get_playlist_name(name_TypeDef *p, uint8_t playnum)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.play.pldata[playnum].name, sizeof(name_TypeDef));
}
/*获取从机设备信息*/
void get_all_slave_data(device_data_TypeDef* p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->sysdata.data.slave, sizeof(device_data_TypeDef));
}
/* 获取全部定时计划*/
void get_all_schedule(schedule_list_TypeDef *p)
{
    FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->sysdata.data.schedule, sizeof(schedule_list_TypeDef));
}
/* 获取定时详情*/
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

// /*获取播放详情列表的顺序表*/
// void get_playdetaillist_ranklist(playdetaillist_ranklist_TypeDef *p)
// {
//     FLASHSPI_PageRead((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.playdetaillist_ranklist, sizeof(playdetaillist_ranklist_TypeDef));
// }

/*******************************************************************************************************************************************************/
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
/*存储播放详情*/
void save_playdetail(playdetail_TypeDef *p, uint8_t playnum)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.play.pldata[playnum], sizeof(playdetail_TypeDef));
}
/*存储全部灯效列表*/
void save_allef_ranklist(ef_ranklist_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.all_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*存储自定义灯效列表*/
void save_originalef_ranklist(ef_ranklist_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.original_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*存储收藏灯效列表*/
void save_favoritesef_ranklist(ef_ranklist_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.favorites_ef_ranklist, sizeof(ef_ranklist_TypeDef));
}
/*存储播放列表的顺序表*/
void save_playlist_ranklist(playlist_ranklist_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.playlist_ranklist, sizeof(playlist_ranklist_TypeDef));
}
/*存储从机设备信息*/
void save_all_slave_data(device_data_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->sysdata.data.slave, sizeof(device_data_TypeDef));
}
/* 保存时间计划表*/
void save_all_schedule(schedule_list_TypeDef *p)
{
    FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->sysdata.data.schedule, sizeof(schedule_list_TypeDef));
}

// // /*存储播放详情列表的顺序表*/
// // void save_playdetaillist_ranklist(playdetaillist_ranklist_TypeDef *p)
// // {
// //     FlashSPI_Insert((uint8_t *)p, (uint32_t)&NORFLASH->efdata.data.ranklist.playdetaillist_ranklist, sizeof(playdetaillist_ranklist_TypeDef));
// // }

/*******************************************************************************************************************************************************/

/*从顺序表中删除参数*/
uint8_t delete_num_from_effect_ranklist(ef_ranklist_TypeDef *p, uint8_t efnum)
{
    ef_ranklist_TypeDef ranklist; // 新信息
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
            ranklist.list[j++] = p->list[i]; // 将原顺序表拷贝至新顺序表（除了被删除的灯效索引）
        }
    }
    if (j == p->num) // 拷贝数与原顺序表尺寸一致，说明顺序表中不存在被删除的索引
    {
        printlog("delete wrong number in rank list\r");
        return 0;
    }
    else
    {
        ranklist.num = j;                       // 更新顺序表尺寸·
        memcpy(p, &ranklist, sizeof(ranklist)); // 更新顺序表内索引
        printlog("delete number in rank list successful\r");
        return 1;
    }
}

/*从播放列表顺序表中删除元素*/
uint8_t delete_num_from_playlist_ranklist(playlist_ranklist_TypeDef *p, uint8_t efnum)
{
    playlist_ranklist_TypeDef ranklist; // 新信息
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
            ranklist.list[j++] = p->list[i]; // 将原顺序表拷贝至新顺序表（除了被删除的灯效索引）
        }
    }
    if (j == p->num) // 拷贝数与原顺序表尺寸一致，说明顺序表中不存在被删除的索引
    {
        printlog("delete wrong number in rank list\r");
        return 0;
    }
    else
    {
        ranklist.num = j;                       // 更新顺序表尺寸·
        memcpy(p, &ranklist, sizeof(ranklist)); // 更新顺序表内索引
        printlog("delete number in rank list successful\r");
        return 1;
    }
}
/*从灯效顺序表中添加元素*/
uint8_t add_num_from_effect_ranklist(ef_ranklist_TypeDef *p, uint8_t efnum)
{
    ef_ranklist_TypeDef ranklist; // 新信息
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
            ranklist.list[ranklist.num++] = p->list[i]; // 将原顺序表拷贝至新顺序表（除了被添加的灯效索引）
        }
    }
    if (ranklist.num == p->num) // 拷贝数与原顺序表尺寸一致，说明顺序表中不存在被添加的索引，需添加
    {
        ranklist.list[ranklist.num] = efnum;
        ranklist.num++;                         // 更新顺序表尺寸
        memcpy(p, &ranklist, sizeof(ranklist)); // 更新顺序表内索引
        printlog("add number in rank list successful\r");
        return 1;
    }
    else
    {
        printlog("Error: add existing number in rank list:%d\r", efnum);
        return 1;
    }
}
/*从播放列表顺序表中添加元素*/
uint8_t add_num_from_playlist_ranklist(playlist_ranklist_TypeDef *p, uint8_t efnum)
{
    playlist_ranklist_TypeDef ranklist; // 新信息
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
            ranklist.list[ranklist.num++] = p->list[i]; // 将原顺序表拷贝至新顺序表（除了被添加的灯效索引）
        }
    }
    if (ranklist.num == p->num) // 拷贝数与原顺序表尺寸一致，说明顺序表中不存在被添加的索引，需添加
    {
        ranklist.list[ranklist.num] = efnum;
        ranklist.num++;                         // 更新顺序表尺寸
        memcpy(p, &ranklist, sizeof(ranklist)); // 更新顺序表内索引
        printlog("add number in rank list successful\r");
        return 1;
    }
    else
    {
        printlog("add existing number in rank list:%d\r", efnum);
        return 1;
    }
}
/*删除自定义灯效*/
uint8_t delete_original_ef(uint8_t efnum)
{
    ef_ranklist_TypeDef ranklist; // 列表信息
    Efdetail_TypeDef ef;// 灯效详情
    if (efnum < original_ef_basenum)
    {
        printf("delete_original_ef num :%d\n",efnum);
        printlog("delete original error\r");
        return 0;
    }
    /*修改该灯效属性*/
    get_original_effect(&ef, efnum);
    ef.Attribute = EMPTY; // 修改属性信息
    save_effect(&ef, efnum);

    /*从全部灯效顺序表中删除该灯效*/
    get_allef_ranklist(&ranklist);              // 获取全部灯效顺序表
    delete_num_from_effect_ranklist(&ranklist, efnum); // 删除索引
    save_allef_ranklist(&ranklist);             // 保存全部灯效顺序表

    /*从自定义灯效顺序表中删除该灯效*/
    get_originalef_ranklist(&ranklist);         // 获取自定义灯效顺序表
    delete_num_from_effect_ranklist(&ranklist, efnum); // 删除索引
    save_originalef_ranklist(&ranklist);        // 保存自定义灯效顺序表;

    /*从收藏灯效顺序表中删除该灯效*/
    get_favoritesef_ranklist(&ranklist);        // 获取收藏灯效顺序表
    delete_num_from_effect_ranklist(&ranklist, efnum); // 删除索引
    save_favoritesef_ranklist(&ranklist);       // 保存收藏灯效顺序表
}

/*新增自定义灯效*/
uint8_t add_original_ef(Efdetail_TypeDef *p, uint8_t efnum)
{
    ef_ranklist_TypeDef ranklist; // 新信息
    if (efnum < original_ef_basenum)
    {
        printlog("add_original_ef error\r");
        return 0;
    }
    p->Attribute = ORIGIN; // 更新灯效属性
    save_effect(p, efnum);

    /*从全部灯效顺序表中新增该灯效*/
    get_allef_ranklist(&ranklist);           // 获取全部灯效顺序表
    add_num_from_effect_ranklist(&ranklist, efnum); // 新增索引
    save_allef_ranklist(&ranklist);          // 保存全部灯效顺序表

    /*从自定义灯效顺序表中新增该灯效*/
    get_originalef_ranklist(&ranklist);      // 获取自定义灯效顺序表
    add_num_from_effect_ranklist(&ranklist, efnum); // 新增索引
    save_originalef_ranklist(&ranklist);     // 保存自定义灯效顺序表;
    return 1;
}

/*删除所有自定义灯效*/
void clear_all_original_ef(void)
{
    uint8_t i;
    for (i = original_ef_basenum; i <= 255; i++)
    {
        delete_original_ef(i);
    }
}

/*收藏灯效*/
uint8_t add_favorites_ef(uint8_t efnum)
{
    ef_ranklist_TypeDef ranklist; // 列表信息
    Efdetail_TypeDef ef;             // 灯效详情

    get_effect(&ef, efnum);
    ef.Attribute = FAVORITES; // 修改成收藏属性信息
    save_effect(&ef, efnum);
    get_favoritesef_ranklist(&ranklist); // 获取列表信息
    add_num_from_effect_ranklist(&ranklist, efnum);
    save_favoritesef_ranklist(&ranklist);
    return 1;
}

/*取消收藏灯效*/
uint8_t delete_favorites_ef(uint8_t efnum)
{
    ef_ranklist_TypeDef ranklist; // 列表信息
    Efdetail_TypeDef ef;             // 灯效详情

    get_effect(&ef, efnum);
    ef.Attribute = ORIGIN; // 修改成原始属性信息
    save_effect(&ef, efnum);

    get_favoritesef_ranklist(&ranklist);        // 获取列表信息
    delete_num_from_effect_ranklist(&ranklist, efnum); // 删除索引
    save_favoritesef_ranklist(&ranklist);
    return 1;
}

/*删除播放列表*/
uint8_t delete_playlist(uint8_t listnum)
{
    playlist_ranklist_TypeDef ranklist;                                  // 列表信息
    get_playlist_ranklist(&ranklist);                                    // 获取列表信息
    delete_num_from_playlist_ranklist(&ranklist, listnum); // 删除索引
    save_playlist_ranklist(&ranklist);
    return 1;
}

/*添加播放信息*/
uint8_t add_playlist(playdetail_TypeDef *p, uint8_t listnum)
{
    playlist_ranklist_TypeDef ranklist; // 列表信息
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

/*删除灯效列表*/
void clear_all_ef_ranklist(void)
{
    ef_ranklist_TypeDef zi;
    memset(&zi, 0, sizeof(zi));
    save_allef_ranklist(&zi);
    save_originalef_ranklist(&zi);
    save_favoritesef_ranklist(&zi);
}

/*删除播放列表*/
void clear_playlist_ranklist(void)
{
    playlist_ranklist_TypeDef zi;
    memset(&zi, 0, sizeof(zi));
    save_playlist_ranklist(&zi);
}
/*从通信中拷贝定时计划详情*/
void copy_schedule_detail_from_com(com_schedule_detail_TypeDef *sur, schedule_detail_TypeDef *tar)
{
    memcpy(&(tar->name), &(sur->name), sizeof(tar->name)); // 拷贝名字
    tar->action = sur->action;                             // 动作类型
    tar->ef_index = sur->ef_index;                         // 灯效的索引号
    tar->ultimatebright = sur->ultimatebright;             // 最终亮度
    tar->actiontime.Min = sur->actiontime.Min;             // 动作时间
    tar->actiontime.Sec = sur->actiontime.Sec;             // 动作时间
    tar->duration = sur->duration;                         // 持续时间
    tar->repeat = sur->repeat;                             // 星期计划
}
/*拷贝定时计划详情至通信中*/
void copy_schedule_detail_to_com(schedule_detail_TypeDef *sur, com_schedule_detail_TypeDef *tar)
{
    memcpy(&(tar->name), &(sur->name), sizeof(tar->name)); // 拷贝名字
    tar->action = sur->action;                             // 动作类型
    tar->ef_index = sur->ef_index;                         // 灯效的索引号
    tar->ultimatebright = sur->ultimatebright;             // 最终亮度
    tar->actiontime.Min = sur->actiontime.Min;             // 动作时间
    tar->actiontime.Sec = sur->actiontime.Sec;             // 动作时间
    tar->duration = sur->duration;                         // 持续时间
    tar->repeat = sur->repeat;                             // 星期计划
}

/*添加定时计划*/
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
    if (num == schedule.num) // 新增定时
    {
        schedule.num++;
    }
    save_all_schedule(&schedule);
    return 1;
}

/*删除定时计划*/
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
        if (i != num)   // 拷贝没被删的定时表
        {
            memcpy(&schedule_new.list[schedule_new.num],&schedule.list[i],sizeof(schedule_new.list[i]));
            schedule_new.num++;
        }
    }
    save_all_schedule(&schedule_new);
    return 1;
}
