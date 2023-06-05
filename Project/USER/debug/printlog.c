#include "Function_Init.H"
#include "printlog.h"

/*打印hex*/
void printhex_my(uint8_t *sur, uint32_t len)
{
    uint32_t i;
// printf("\n");
#if defined(printlog_enabled)
    for (i = 0; i < len; i++)
    {
        printf("%02x ", sur[i]);
        if (i % 63 == 0&&i!=0)
        {
            printf("\n");
        }
    }
    printf("\n");
#endif // printlog_enabled
}

/*打印字符串*/
void printstr_my(uint8_t *sur, uint32_t len)
{
    uint32_t i;
#if defined(printlog_enabled)
    for (i = 0; i < len; i++)
    {
        printf("%c", sur[i]);
    }
    printf("\n");
#endif // printlog_enabled
}

/*打印动态效果*/
void print_flow(Flow_Enum num)
{
    printf("Flow:");
    switch (num)
    {
    case FLOW_STATIC:
        printf("Static\r");
        break;
    case FLOW_BREATH:
        printf("Breath\r");
        break;
    case FLOW_STREAM:
        printf("Stream\r");
        break;
    case FLOW_REVERB:
        printf("Reverberate\r");
        break;
    case FLOW_HOPSCO:
        printf("Hopscotch\r");
        break;
    case FLOW_LIGHTN:
        printf("Lightning\r");
        break;
    case FLOW_IGNITE:
        printf("Ignite\r");
        break;
    case FLOW_RANDOM:
        printf("Random\r");
        break;
    default:
        printf("   [error num:%d]\r", num);
        break;
    }
}
/*打印运动方向*/
void print_direction(Direction_Enum num)
{
    printf("Direction:");
    switch (num)
    {
    case DIRECTION_UP:
        printf("up\r");
        break;
    case DIRECTION_DOWN:
        printf("down\r");
        break;
    case DIRECTION_LEFT:
        printf("left\r");
        break;
    case DIRECTION_RIGHT:
        printf("right\r");
        break;
    case DIRECTION_SEPARATE:
        printf("disperse\r");
        break;
    case DIRECTION_CONVERGE:
        printf("concentrate\r");
        break;
    default:
        printf("   [error num:%d]\r", num);
        break;
    }
}
/*打印灯效类型*/
void print_effecttype(EffectType_Enum num)
{
    printf("EffectType:");
    switch (num)
    {
    case STATIC_TYPE:
        printf("static\r");
        break;
    case DYNAMIC_TYPE:
        printf("dynamic\r");
        break;
    case RHYTHM_TYPE:
        printf("rhythm\r");
        break;
    default:
        printf("   [error num:%d]\r", num);
        break;
    }
}
/*打印灯效属性*/
void print_attribute(Attribute_Enum num)
{
    printf("Attribute:");
    switch (num)
    {
    case ORIGIN:
        printf("origin\r");
        break;
    case FAVORITES:
        printf("favorite\r");
        break;
    case EMPTY:
        printf("empty\r");
        break;
    default:
        printf("   [error num:%d]\r", num);
        break;
    }
}

/*app灯效详情log*/
void print_com_effect_detial_log(com_effect_detial_TypeDef *p)
{
    uint8_t i = 0;
#ifdef printlog_enabled
    print_effect_detial(&p->Efdata, p->idex);
    printf("checksum:0x%02x\r", p->checksum);
#endif
}

/*灯效详情log*/
void print_effect_detial(Efdetail_TypeDef *p,uint8_t efnum)
{
    uint8_t i = 0;
    printf("idex:%d\r", efnum);
    printf("namelenght:%d\r", p->namelenght);
    printf("Name:");
    printstr_my(&p->Name, p->namelenght);
    printf("Speed:%d\r", p->Speed);
    printf("Bright1:%d\r", p->Brightness1);
    printf("Bright2:%d\r", p->Brightness2);
    printf("Mic:%d\r", p->MicSensitivity);
    print_effecttype(p->EffectType);
    print_attribute(p->Attribute);
    print_direction(p->Direction);
    print_flow(p->Flow);
    printf("ColorNum:%d\r", p->EfColorInf.colorNum);
    for (i = 0; i < EfColor_SizeNum; i++)
    {
        printf(">%3d|%2x,%2x,%2x,%2x     ", p->EfColorInf.ColorID[i].id, p->EfColorInf.ColorID[i].color.R, p->EfColorInf.ColorID[i].color.G, p->EfColorInf.ColorID[i].color.B, p->EfColorInf.ColorID[i].color.W);
        if ((i % 4) == 3)
        {
            printf("\r");
        }
    }
    printf("\r");
}

/*打印灯效概述*/
void print_effect_sketch(Efminidetail_TypeDef *p,uint8_t efnum)
{
    uint8_t i = 0;
    printf("idex:%d\r", efnum);
    printf("Name:");
    // // printf("namelenght:%d\r", p->namelenght);
    printstr_my(&p->Name, p->namelenght);
    print_effecttype(p->EffectType);
    print_attribute(p->Attribute);
    printf("ColorNum:%d\r", p->EfColormioniInf.colorNum);
    for (i = 0; i < EfColor_miniSizeNum; i++)
    {
        printf(">%3d|%2x,%2x,%2x,%2x     ", p->EfColormioniInf.ColorID[i].id, p->EfColormioniInf.ColorID[i].color.R, p->EfColormioniInf.ColorID[i].color.G, p->EfColormioniInf.ColorID[i].color.B, p->EfColormioniInf.ColorID[i].color.W);
        if ((i % 4) == 3)
        {
            printf("\r");
        }
    }
    printf("\r");
}

/*打印获取存储区的灯效详情*/
void print_get_ef_detial(uint8_t efnum)
{
    Efdetail_TypeDef ef;
    printlog("log:read flash effect detial\r");
    get_effect(&ef,efnum);
    print_effect_detial(&ef,efnum);
}

/*打印获取自定义灯效列表*/
void print_get_original_ef_ranklist(void)
{
    uint8_t i;
    ef_ranklist_TypeDef ranklist;
    get_originalef_ranklist(&ranklist); // 获取原信息
    printf("original effect sum:%d\r", ranklist.num);
    for (i = 0; i < ranklist.num; i++)
    {
        printf("[%3d] ", ranklist.list[i]);
    }
    printf("\r");
}
/*打印获取全部灯效列表*/
void print_get_all_ef_ranklist(void)
{
    uint8_t i;
    ef_ranklist_TypeDef ranklist;
    get_allef_ranklist(&ranklist); // 获取原信息
    printf("all effect ranklist sum:%d\r", ranklist.num);
    for (i = 0; i < ranklist.num; i++)
    {
        printf("[%3d] ", ranklist.list[i]);
    }
    printf("\r");
}
/*打印获取收藏灯效列表*/
void print_get_favorites_ef_ranklist(void)
{
    uint8_t i;
    ef_ranklist_TypeDef ranklist;
    get_favoritesef_ranklist(&ranklist); // 获取原信息
    printf("favorites effect ranklist sum:%d\r", ranklist.num);
    for (i = 0; i < ranklist.num; i++)
    {
        printf("[%3d] ", ranklist.list[i]);
    }
    printf("\r");
}
/*打印获取播放列表*/
void print_get_playlist_ranklist(void)
{
    uint8_t i;
    playlist_ranklist_TypeDef ranklist;
    get_playlist_ranklist(&ranklist); // 获取原信息
    printf("playlist ranklist sum:%d\r", ranklist.num);
    for (i = 0; i < ranklist.num; i++)
    {
        printf("[%3d] ", ranklist.list[i]);
    }
    printf("\r");
}


/*打印灯效列表*/
void print_ef_ranklist(ef_ranklist_TypeDef* p)
{
    uint8_t i;
    printf("ef_ranklist num:%d\r", p->num);
    for (i = 0; i < p->num; i++)
    {
        printf("[%3d] ",p->list[i]);
    }
    printf("\r\n");
}
/*打印播放列表的顺序表*/
void print_playlist_ranklist(playlist_ranklist_TypeDef* p)
{
    uint8_t i;
    printf("playlist_ranklist num:%d\r", p->num);
    for (i = 0; i < p->num; i++)
    {
        printf("[%3d] ",p->list[i]);
    }
    printf("\r\n");
}
/*打印通信播放列表的顺序表*/
void print_com_playlist_ranklist(com_playlist_TypeDef* p)
{
    uint8_t i;
    printf("com_playlist_TypeDef num:%d\r", p->sum);
    for (i = 0; i < p->sum; i++)
    {
        printf("[%3d] ",p->list[i].index);
        printstr_my(&(p->list[i].name.text),p->list[i].name.length);
    }
    printf("\r\n");
}

/*打印播放详情*/
void print_playdetial(playdetail_TypeDef *p, uint8_t playnum)
{
    uint8_t i;
    printf("idex:%d\r", playnum);
    printf("namelenght:%d\r", p->name.length);
    printf("name:");
    printstr_my(&p->name.text, p->name.length);
    printf("Min:%d\r", p->DurationTime.Min);
    printf("Sec:%d\r", p->DurationTime.Sec);
    printf("num:%d\r", p->num);
    for (i = 0; i < PlayList_SizeNum; i++)
    {
        printf("[%d] ", p->list[i]);
        if ((i % 4) == 9)
        {
            printf("\r");
        }
    }
    printf("\r");
}

/*打印app下发播放详情*/
void print_com_playdetial(com_play_detial_TypeDef *p)
{
#ifdef printlog_enabled
    printf("print_com_playdetial\r");
    print_playdetial(&p->pldata, p->idex);
    printf("checksum:0x%02x\r", p->checksum);
#endif
}
