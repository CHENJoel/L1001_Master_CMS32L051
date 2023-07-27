
#include "Function_Init.H"
#include "debug.h"

const uint8_t tastcolor[][4] =
    {
        {0, 0, 0, 255},
        {255, 0, 0, 0},
        {255, 255, 0, 0},
        {0, 255, 0, 0},
        {0, 255, 255, 0},
        {0, 0, 255, 0},
        {255, 128, 0, 0},   // 橙色
        {200, 255, 37, 0},  // 淡黄绿
        {233, 71, 9, 0},    // 橙红
        {237, 175, 32, 0},  // 黄色
        {87, 140, 188, 0},  // 蓝色
        {37, 188, 255, 0},  // 浅蓝
        {23, 129, 232, 0},  // 蓝
        {146, 35, 255, 0},  // 紫
        {230, 45, 232, 0},  // 粉紫
        {255, 13, 192, 0},  // 紫红
        {90, 167, 167, 0},  // 青
        {150, 215, 198, 0}, // 粉绿
        {186, 201, 74, 0},  // 嫩绿
        {240, 218, 220, 0}, // 粉色
        {245, 150, 176, 0}, // 深粉
        {254, 225, 153, 0}, // 黄色
        {118, 214, 201, 0}, // 青色
        {133, 188, 218, 0}, // 蓝色
        {252, 172, 230, 0}, // 浅粉
        {253, 135, 221, 0}, // 粉色
        {250, 28, 195, 0},  // 深粉色
        {238, 0, 242, 0},   // 浅紫红
        {112, 0, 240, 0},   // 浅紫色
        {60, 0, 169, 0},    // 蓝紫色
        {24, 16, 55, 0},    // 深紫色
        {57, 35, 97, 0},    // 紫色
        {113, 84, 174, 0},  // 浅紫
        {128, 156, 228, 0}, // 浅蓝紫
        {98, 191, 215, 0},  // 浅蓝
        {82, 209, 192, 0},  // 浅青
        {121, 246, 194, 0}, // 粉绿
        {4, 164, 94, 0},    // 绿色
        {241, 242, 237, 0}, // 灰白
        {128, 211, 215, 0}, // 浅蓝
        {113, 185, 223, 0}, // 蓝色
        {41, 15, 180, 0},   // 海蓝色
        {246, 234, 246, 0}, // 白紫
        {72, 27, 137, 0},   // 紫色
        {247, 198, 166, 0}, // 橙色
        {247, 131, 137, 0}, // 红色
        {166, 58, 76, 0},   // 朱红
        {38, 38, 94, 0},    // 蓝紫
};
uint8_t test_onoff=1;
uint8_t test_color_num;
uint8_t test_brightness=255;


/*测试灯效的存储读写*/
void
debug_save_effect_detial(void)
{
    static uint8_t i,j;
    uint8_t *pp;
    Efdetail_TypeDef eff;
    // // eff.namelenght = sizeof("effect name test");
    // eff.namelenght = 16;
    sprintf(&eff.Name, "effectname test");
    // // // // // printf("debug\n");
    // // // // // printstr_my(&eff.Name,16);
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
    // printf("sum:%d\n",checksum_calculate(&eff,sizeof(eff)));
    save_effect(&eff,0);

    // memset(&eff,0,sizeof(eff));
    get_effect(&eff,0);
    // printf("sum:%d\n",checksum_calculate(&eff,sizeof(eff)));
    print_effect_detial(&eff,0);
    // printf("\read\r\r");
    // printhex_my(&eff,sizeof(eff));
    i++;
}
/*测试添加自定义灯效*/
void debug_add_original_ef(void)
{
    static uint8_t i=128;
    Efdetail_TypeDef ef;
    // // i = Random_Generate() % original_ef_num;
    // // i += 128;
    i++;
    printf("add original ranklist %d\r", i);
    get_effect(&ef,0);  // 拷贝第0个灯效
    add_original_ef(&ef, i);
    print_get_original_ef_ranklist();
}
/*测试删除自定义灯效*/
void debug_delete_original_ef(void)
{
    ef_ranklist_TypeDef list;
    uint8_t i = 0;
    get_originalef_ranklist(&list);
    if (list.num)
    {
        i = list.list[list.num - 1];
    }
    else
    {
        i = list.list[0];
    }
    printf("delete original ranklist %d\r", i);
    delete_original_ef(i);
    // // printf("delate original ranklist %d\r", i);
    print_get_original_ef_ranklist();
}

void norflash_rw_debug(uint32_t addr)
{
    uint8_t arry[256];
    uint8_t Warry[320];
    static uint8_t i;
    uint32_t readaddr;

    printf("i:%d\r",i);

    memset(arry,0x66,sizeof(arry));

    FLASHSPI_PageRead(arry, addr, sizeof(arry));
    printhex_my(arry,sizeof(arry));


    memset(Warry,i,sizeof(Warry));
    FlashSPI_Insert(Warry, addr, sizeof(Warry));


    readaddr = 256 * (((addr - 256 )/ 256));
    FLASHSPI_PageRead(arry, readaddr, sizeof(arry));
    printhex_my(arry, sizeof(arry));

    memset(arry, 0, sizeof(arry));
    readaddr += sizeof(arry);
    FLASHSPI_PageRead(arry, readaddr, sizeof(arry));
    printhex_my(arry, sizeof(arry));

    memset(arry, 0, sizeof(arry));
    readaddr += sizeof(arry);
    FLASHSPI_PageRead(arry, readaddr, sizeof(arry));
    printhex_my(arry, sizeof(arry));
    i++;

//    FlashROM_Erase()

}


/*
 * @Description: norflash循环读写测试
 * @param:
 * @return:
*/
void norflash_auto_rw_test(void)
{
    // #define TESTSIZE FIRMWARE_SIZE //(256*256)
    #define TESTSIZE (256*1)
    static uint8_t num;
    uint32_t i;
    uint32_t chechsum = 0;
    uint32_t norsum = 0;
    uint8_t arry[256];
    num++;

    memset(arry, num, sizeof(arry));
    // erase_firmware_block64K_norflash(); // 擦除固件区

    FLASH_BlockErase(0);
    for (i = 0; i < TESTSIZE;)
    {
        // // FLASHSPI_PageErase(0);
        FLASH_PageWrite(arry, i, sizeof(arry));
        // // FlashSPI_Insert(arry, i, sizeof(arry));
        chechsum += checksum_calculate(arry, sizeof(arry));
        i += sizeof(arry);
    }
    // norsum = get_firmware_chechsum_norflash();

    for (i = 0; i < TESTSIZE;)
    {
        FLASHSPI_PageRead(arry, i, sizeof(arry));
        norsum += checksum_calculate(arry, sizeof(arry));
        i += sizeof(arry);
    }

    if (norsum==chechsum)
    {
        printlog("[%3d]:chechsum: Ox%04x ,norsum: Ox%04x\r",num,chechsum,norsum);
    }
    else
    {
        LED1_REV();
        LED2_REV();
        printlog("ERROR-[%3d]:chechsum: Ox%04x ,norsum: Ox%04x\r",num,chechsum,norsum);
        printhex_my(arry, sizeof(arry));
    }
    // printlog("[%3d]:chechsum: Ox%04x ,norsum: Ox%04x",num,chechsum,norsum);
    // // FLASH_PageWrite(sur, FIRMWARE_ADDR + offset, 256);



}

/*测试添加播放列表*/
void debug_add_playlist(void)
{
    static uint8_t i;
    playdetail_TypeDef playdetail;
    i++;
    memset(&playdetail,0,sizeof(playdetail));
    printf("add playlist ranklist %d\r", i);
    add_playlist(&playdetail,i);

}


/*测试删除播放列表*/
void debug_delete_playlist(void)
{

    playlist_ranklist_TypeDef ranklist; // 列表信息
    get_playlist_ranklist(&ranklist);
    printf("delete playlist ranklist %d\r", ranklist.list[0]);
    delete_playlist( ranklist.list[0]);
    get_playlist_ranklist(&ranklist);
    print_playlist_ranklist(&ranklist);
}

/*测试添加定时表*/
void debug_add_schedule(void)
{
    schedule_list_TypeDef schedule;
    schedule_detail_TypeDef detail;
    uint8_t i;
    printlog("debug add schedule\r");
    detail.name.length = 4;
    memcpy(&detail.name.text, "test", 4);
    detail.action = TURN_ON;
    detail.ef_index = 8;
    detail.ultimatebright = 89;
    detail.actiontime.Min = 13;
    detail.actiontime.Sec = 24;
    detail.duration.Min = 16;
    detail.duration.Sec = 53;
    detail.repeat.week = 0x66;
    get_all_schedule(&schedule);
    add_schedule(&detail, schedule.num);
}

/*测试删除定时表*/
void debug_delete_schedule(void)
{
    printlog(" debug delete schedule\r");
    delete_schedule(0);
}

/*切换下一内置灯效*/
void debug_play_next_effect(void)
{
    uint8_t num;
    num = play.detail.efnum + 1;
    if (num > 29)
    {
        num = 0;
    }
    play_new_effect(num);
}

/*切换上一内置灯效*/
void debug_play_last_effect(void)
{
    uint8_t num;
    num = play.detail.efnum - 1;
    if (num > 29)
    {
        num = 29;
    }
    play_new_effect(num);
}

void debug(void)
{

}



/*按键1服务调试函数*/
void debug_K1(void)
{
    printf("\rK1\r");
    test_onoff_play();
    // print_slave_data();
    // printf("init effect...\r");
    // // mcu_update_allef_ranklist();
    // copy_built_in_ef_to_norflash(); // 初始化灯效信息
}
/*按键2服务调试函数*/
void debug_K2(void)
{
    printf("\rK2\r");
    test_change_color(1);

}
/*按键3服务调试函数*/
void debug_K3(void)
{
    printf("\rK3\r\n");
    test_change_color(0);

}
/*按键4服务调试函数*/
void debug_K4(void)
{
    printf("\rK4\r");
    test_click_brightness(1);
    // debug_play_next_effect();


}

/*按键5服务调试函数*/
void debug_K5(void)
{
    uint16_t i;
    uint32_t chechsum;
    printf("\rK5\r");
    test_click_brightness(0);
}

/*

dp_download_all_effect_ranklist_handle 空

*/
/*测试开始暂停播放颜色*/
void test_onoff_play(void)
{
    if (test_onoff)
    {
        test_onoff = 0;
    }
    else
    {
        test_onoff = 1;
    }
}

/*测试播放颜色*/
void test_play_color(void)
{
    if (test_onoff)
    {
        play_color_in_all_salve_light(test_brightness, tastcolor[test_color_num][0], tastcolor[test_color_num][1], tastcolor[test_color_num][2], tastcolor[test_color_num][3]);
    }
    else
    {
        play_color_in_all_salve_light(0, tastcolor[test_color_num][0], tastcolor[test_color_num][1], tastcolor[test_color_num][2], tastcolor[test_color_num][3]);
    }
}
/*测试切换颜色*/
void test_change_color(uint8_t dir)
{
    if (dir)
    {
        if (++test_color_num >= (sizeof(tastcolor) / 4))
        {
            test_color_num = 0;
        }
    }
    else
    {
        if (test_color_num)
        {
            test_color_num--;
        }
    }
}
/*测试单击加减亮度*/
void test_click_brightness(uint8_t dir)
{
    if (dir)
    {
        if (test_brightness < 230)
        {
            test_brightness += 30;
        }
        else
        {
            test_brightness = 255;
        }
    }
    else
    {
        if (test_brightness > 30)
        {
            test_brightness -= 30;
        }
        else
        {
            test_brightness = 1;
        }
    }
}
/*测试长按加减亮度*/
void test_long_brightness(uint8_t dir)
{
    if (dir)
    {
        if (test_brightness < 255)
        {
            test_brightness++;
        }
    }
    else
    {
        if (test_brightness > 2)
        {
            test_brightness--;
        }
    }
}
