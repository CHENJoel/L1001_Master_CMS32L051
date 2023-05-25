#include "Function_Init.H"
#include "printlog.h"

/*打印hex*/
void printhex_my(uint8_t *sur, uint8_t len)
{
    uint8_t i;
    // printf("\n");
    for (i = 0; i < len; i++)
    {
        printf("%02x ", sur[i]);
    }
    printf("\n");
}

/*打印字符串*/
void printstr_my(uint8_t *sur, uint8_t len)
{
    uint8_t i;
    for (i = 0; i < len; i++)
    {
        printf("%c", sur[i]);
    }
    printf("\n");
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
    // printf("idex:%d\r", p->idex);
    // printf("Name:");
    // printstr_my(&p->Efdata.Name, sizeof(p->Efdata.Name));
    // printf("Speed:%d\r", p->Efdata.Speed);
    // printf("Bright1:%d\r", p->Efdata.Brightness1);
    // printf("Bright2:%d\r", p->Efdata.Brightness2);
    // printf("Mic:%d\r", p->Efdata.MicSensitivity);
    // print_effecttype(p->Efdata.EffectType);
    // print_attribute(p->Efdata.Attribute);
    // print_direction(p->Efdata.Direction);
    // print_flow(p->Efdata.Flow);
    // printf("ColorNum:%d\r", p->Efdata.EfColorInf.colorNum);
    // for (i = 0; i < EfColor_SizeNum; i++)
    // {
    //     printf(">%3d|%2x,%2x,%2x,%2x     ", p->Efdata.EfColorInf.ColorID[i].id, p->Efdata.EfColorInf.ColorID[i].color.R, p->Efdata.EfColorInf.ColorID[i].color.G, p->Efdata.EfColorInf.ColorID[i].color.B, p->Efdata.EfColorInf.ColorID[i].color.W);
    //     if ((i % 4) == 3)
    //     {
    //         printf("\r");
    //     }
    // }
    print_effect_detial(&p->Efdata, p->idex);
    printf("checksum:0x%02x\r", p->checksum);
#endif
}

/*灯效详情log*/
void print_effect_detial(Efdetail_TypeDef *p,uint8_t efnum)
{
    uint8_t i = 0;
    printf("idex:%d\r", efnum);
    printf("Name:");
    printstr_my(&p->Name, sizeof(p->Name));
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
}

/*打印灯效概述*/
void print_effect_sketch(Efminidetail_TypeDef *p,uint8_t efnum)
{
    uint8_t i = 0;
    printf("idex:%d\r", efnum);
    printf("Name:");
    printstr_my(&p->Name, sizeof(p->Name));
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
    ef_ranklist_TypeDef memranklist;
    get_original_ranklist(&memranklist); // 获取原信息
    printf("ef_ranklist sum:%d\r", memranklist.num);
    for (i = 0; i < memranklist.num; i++)
    {
        printf("[%3d] ", memranklist.list[i]);
    }
    printf("\r\n");
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
