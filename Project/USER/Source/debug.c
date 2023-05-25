#include "Function_Init.H"
#include "debug.h"


/*测试灯效的存储读写*/
void debug_save_effect_detial(void)
{
    static uint8_t i,j;
    uint8_t *pp;
    Efdetail_TypeDef eff;
    sprintf(&eff.Name, "effect name test");
    eff.Speed = i++;
    eff.Brightness1 += i * 5;
    eff.Brightness2 += i * 5;
    eff.MicSensitivity = i++;
    eff.EffectType = i++;
    eff.Attribute = i++;
    eff.Direction = i++;
    eff.Flow = i++;
    pp = &eff.EfColorInf.ColorID;
    for (j = 0; j < sizeof(eff.EfColorInf) - 1; j++)
    {
        *pp++ = j;
    }
    // printf("\rsave\r");
    // memset(&eff,i,sizeof(eff));
    // printhex_my(&eff,sizeof(eff));
    // printf("sum:%d\n",CheckSum_Calu(&eff,sizeof(eff)));
    save_effect(&eff,0);

    // memset(&eff,0,sizeof(eff));
    get_effect(&eff,0);
    // printf("sum:%d\n",CheckSum_Calu(&eff,sizeof(eff)));
    print_effect_detial(&eff,0);
    // printf("\read\r\r");
    // printhex_my(&eff,sizeof(eff));
    i++;
}
/*测试添加自定义灯效*/
void debug_add_original_ef(void)
{
    uint8_t i;
    Efdetail_TypeDef ef;
    i = Random_Generate() % original_ef_num;
    i += 128;
    printf("add original ranklist %d\r", i);
    add_original_ef(&ef, i);
    print_get_original_ef_ranklist();
}
/*测试删除自定义灯效*/
void debug_delete_original_ef(void)
{
    ef_ranklist_TypeDef list;
    uint8_t i = 0;
    get_original_ranklist(&list);
    if (list.num)
    {
        i = list.list[list.num - 1];
    }
    else
    {
        i = list.list[0];
    }
    delete_original_ef(i);
    printf("delate original ranklist %d\r", i);
    print_get_original_ef_ranklist();
}

void debug(void)
{

}



/*按键1服务调试函数*/
void debug_K1(void)
{

}
/*按键2服务调试函数*/
void debug_K2(void)
{
    debug_add_original_ef();
}
/*按键3服务调试函数*/
void debug_K3(void)
{
    debug_delete_original_ef();
}
/*按键4服务调试函数*/
void debug_K4(void)
{
    init_original_ranklist();
    print_get_original_ef_ranklist();
}

/*按键5服务调试函数*/
void debug_K5(void)
{
    init_built_in_ef_to_norflash();
    // // printf("Original_Efdata %d \r",(uint32_t)(((uint32_t)&((EffectInf_TypeDef *)0)->Original_Efdata) / sizeof(Efdetail_TypeDef)));
}
