
#include "Function_Init.H"
#include "debug.h"

const uint8_t tastcolor[][4] =
    {
        // // {0, 0, 0, 255},
        {255, 0, 0, 0},
        {255, 255, 0, 0},
        {0, 255, 0, 0},
        {0, 255, 255, 0},
        {0, 0, 255, 0},
        {255, 0, 255, 0},
        // // {255, 0, 130, 0},
        // // {255, 0, 60, 0},
        // // {255, 0, 20, 0},
        // // {180, 0, 255, 0},
        // // {130, 0, 255, 0},
        // // {75, 0, 255, 0},
        // // {10, 0, 255, 0},
        // // {150, 255, 0, 0},
        // // {120, 255, 0, 0},
        // // {60, 255, 0, 0},
        // // {10, 255, 0, 0},
        // // {255, 200, 0, 0},
        // // {255, 160, 0, 0},
        // // {255, 130, 0, 0},
        // // {255, 80, 0, 0},
        // // {255, 60, 0, 0},
        // // {255, 40, 0, 0},
        // // {255, 20, 0, 0},
        // // {0, 255, 200, 0},
        // // {0, 255, 180, 0},
        // // {0, 255, 160, 0},
        // // {0, 255, 130, 0},
        // // {0, 255, 100, 0},
        // // {0, 255, 80, 0},
        // // {0, 255, 60, 0},
        // // {0, 255, 10, 0},
        // // {0, 210, 255, 0},
        // // {0, 200, 255, 0},
        // // {0, 170, 255, 0},
        // // {0, 140, 255, 0},
        // // {0, 100, 255, 0},
        // // {0, 75, 255, 0},
        // // {0, 55, 255, 0},
        // // {0, 35, 255, 0},
        // // {0, 10, 255, 0},
        // // {255, 128, 0, 0},   // 橙色
        // // {200, 255, 37, 0},  // 淡黄绿
        // // {233, 71, 9, 0},    // 橙红
        // // {237, 175, 32, 0},  // 黄色
        // // {87, 140, 188, 0},  // 蓝色
        // // {37, 188, 255, 0},  // 浅蓝
        // // {23, 129, 232, 0},  // 蓝
        // // {146, 35, 255, 0},  // 紫
        // // {230, 45, 232, 0},  // 粉紫
        // // {255, 13, 192, 0},  // 紫红
        // // {90, 167, 167, 0},  // 青
        // // {150, 215, 198, 0}, // 粉绿
        // // {186, 201, 74, 0},  // 嫩绿
        // // {240, 218, 220, 0}, // 粉色
        // // {245, 150, 176, 0}, // 深粉
        // // {254, 225, 153, 0}, // 黄色
        // // {118, 214, 201, 0}, // 青色
        // // {133, 188, 218, 0}, // 蓝色
        // // {252, 172, 230, 0}, // 浅粉
        // // {253, 135, 221, 0}, // 粉色
        // // {250, 28, 195, 0},  // 深粉色
        // // {238, 0, 242, 0},   // 浅紫红
        // // {112, 0, 240, 0},   // 浅紫色
        // // {60, 0, 169, 0},    // 蓝紫色
        // // {24, 16, 55, 0},    // 深紫色
        // // {57, 35, 97, 0},    // 紫色
        // // {113, 84, 174, 0},  // 浅紫
        // // {128, 156, 228, 0}, // 浅蓝紫
        // // {98, 191, 215, 0},  // 浅蓝
        // // {82, 209, 192, 0},  // 浅青
        // // {121, 246, 194, 0}, // 粉绿
        // // {4, 164, 94, 0},    // 绿色
        // // {241, 242, 237, 0}, // 灰白
        // // {128, 211, 215, 0}, // 浅蓝
        // // {113, 185, 223, 0}, // 蓝色
        // // {41, 15, 180, 0},   // 海蓝色
        // // {246, 234, 246, 0}, // 白紫
        // // {72, 27, 137, 0},   // 紫色
        // // {247, 198, 166, 0}, // 橙色
        // // {247, 131, 137, 0}, // 红色
        // // {166, 58, 76, 0},   // 朱红
        // // {38, 38, 94, 0},    // 蓝紫
};
uint8_t test_onoff=1;
uint8_t test_color_num;
uint8_t test_brightness=50;


/*测试灯效的存储读写*/
void debug_save_effect_detial(void)
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
    get_effect_detail(&eff,0);
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
    // // i = get_random_number() % original_ef_num;
    // // i += 128;
    i++;
    printf("add original ranklist %d\r", i);
    get_effect_detail(&ef,0);  // 拷贝第0个灯效
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
    #define TEST_BASEADDR 0x20000
    // // #define TEST_BASEADDR 0x500
    static uint8_t num;
    uint32_t i;
    uint32_t chechsum = 0;
    uint32_t norsum = 0;
    uint8_t arry[256];
    
    num++;

    memset(arry, num, sizeof(arry));
    // erase_firmware_block64K_norflash(); // 擦除固件区

    // FLASH_BlockErase(0+TEST_BASEADDR);q
    for (i = 0; i < TESTSIZE;)
    {
        // // FLASHSPI_PageErase(0);
        
        // // FLASHSPI_PageWrite(arry, i+TEST_BASEADDR, sizeof(arry));
        FlashSPI_Insert(arry, i+TEST_BASEADDR, sizeof(arry));
        chechsum += checksum_calculate(arry, sizeof(arry));
        i += sizeof(arry);
    }
    // norsum = get_firmware_chechsum_norflash();

    for (i = 0; i < TESTSIZE;)
    {
        FLASHSPI_PageRead(arry, i+TEST_BASEADDR, sizeof(arry));
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
void debug_add_clock_schedule(void)
{
    clock_list_TypeDef schedule;
    clock_detail_TypeDef detail;
    uint8_t i;
    printlog("debug add schedule\r");
    detail.name.length = 4;
    memcpy(&detail.name.text, "test", 4);
    detail.action = TURN_ON;
    detail.ef_index = 8;
    detail.ultimatebright = 89;
    detail.actiontime.hou_HM = 13;
    detail.actiontime.min_HM = 24;
    detail.duration.hou_HM = 16;
    detail.duration.min_HM = 53;
    detail.repeat.week = 0x66;
    get_all_schedule(&schedule);
    add_clock_schedule(&detail, schedule.num);
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
    num = play.detail.efindex + 1;
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
    num = play.detail.efindex - 1;
    if (num > 29)
    {
        num = 29;
    }
    play_new_effect(num);
}

void debug(void)
{
    // static uint8_t ppp;
    // ppp++;
    // UART1_Send(&ppp, 1);  
    // static uint8_t i;
    // if (i)
    // {
    //     i = 0;
    //     // SPI_MOSI(0);
    //     // SPI_CLK(0);
    //     // W25_CS(0);
    //     // LED1_OFF();
    //     LED2_REV();
    //     PORT_ClrBit(PORT1, PIN2);
    //     PORT_ClrBit(PORT1, PIN3);
    //     PORT_ClrBit(PORT1, PIN4);

    //     PORT_ClrBit(PORT12, PIN4);
    // }
    // else
    // {
    //     i = 1;
    //     // SPI_MOSI(1);
    //     // SPI_CLK(1);
    //     // W25_CS(1);
    //     PORT_SetBit(PORT1, PIN2);
    //     PORT_SetBit(PORT1, PIN3);
    //     PORT_SetBit(PORT1, PIN4);
    //     PORT_SetBit(PORT12, PIN4);
    //      LED2_REV();
    // }
    // norflash_rw_debug(0);
    // slave.num=3;
    // // transmit_playdata_RGBbr();
    // void transmit_playsame_RGBbr(L0_playRGBbr_Typedef *x)
    // L0_playRGBbr_Typedef x;
    // x.
    // transmit_playsame_RGBbr();
}


void debug_K1_LONG(void)
{
    // if (calibration_enable)
    // {
    //     calibration_enable = 0;
    // }
    // else
    // {
    //     calibration_enable = 1;
    // }
}

/*按键1服务调试函数*/
void debug_K1(void)
{
    // printf("\rK1\r");
    // debug_add_original_ef();
    // slave_light_in_turn();
    // connect_slave_device(0X36);
    // // LED1_REV();
    // poll_slave_id();
    // slave_light_in_turn();
    // test_onoff_play();
    // print_slave_data();
    // printf("init effect...\r");
    // // mcu_update_allef_ranklist();
    // copy_built_in_ef_to_norflash(); // 初始化灯效信息
}
/*按键2服务调试函数*/
void debug_K2(void)
{
    // printf("\rK2\r");
    // slave_light_in_turn();
    // test_change_color(1);
    // print_get_all_ef_ranklist();
}
/*按键3服务调试函数*/
void debug_K3(void)
{
    // printf("\rK3\r\n");
    // test_change_color(0);
    //   print_get_favorites_ef_ranklist();  
    // print_all_clock_detail();
    // search_norflash_ranklist();
}
/*按键4服务调试函数*/
void debug_K4(void)
{
    // print_online_slave_data();
    // // init_default_playlist();            // 出厂化内置播放表信息
    // uint8_t version[OTA_updateFLAG_SIZE];

    // get_norflash_firmware_version(&version, sizeof(version));
    // printhex_my(&version, sizeof(version));
    // printlog("\r");
    // printstr_my(&version, sizeof(version));
    // printlog("get_norflash_firmware_version:%s\r", &version);

    // L0_playCOLOR_Typedef x;
    // x.br = 100;
    // x.type = 1;
    // x.R = 70;
    // x.G = 0;
    // x.B = 0;
    // transmit_playsame_COLOR(&x);
    // ef_ranklist_TypeDef ranklist; // 列表信息
    // debug_add_clock_schedule();
    // print_all_clock_detail();
    // printf("\rK4\r");
    // test_click_brightness(1);
    // debug_play_next_effect();
    // test_switch_brightness();
    // // printlog("-------------------------------------------------------------------------------\n");
    // // printlog("all effect\n");
    // // get_allef_ranklist(&ranklist); // 获取全部灯效顺序表
    // // print_ef_ranklist(&ranklist);  // 打印顺序列表信息
    // // printlog("original effect\n");
    // // get_originalef_ranklist(&ranklist); // 获取全部灯效顺序表
    // // print_ef_ranklist(&ranklist);       // 打印顺序列表信息
    // // printlog("favorite effect\n");
    // // get_favoritesef_ranklist(&ranklist); // 获取全部灯效顺序表
    // // print_ef_ranklist(&ranklist);        // 打印顺序列表信息
    // // printlog("-------------------------------------------------------------------------------\n");
    // factoryreset_norflash();
    // // set_firmware_download_finish_flag();
}

/*按键5服务调试函数*/
void debug_K5(void)
{
    // // play_new_effect(12);
//    static  Direction_Enum dir;
//     if (++dir > DIRECTION_SEPARATE)
//     {
//         dir = 0;
//     }

    // // if (dir == DIRECTION_SEPARATE)
    // // {
    // //     dir = DIRECTION_CONVERGE;
    // // }
    // // else
    // // {
    // //     dir = DIRECTION_SEPARATE;
    // // }
    // light_in_direction(dir);
//     light_in_direction(dir);
    // // print_get_playlist_ranklist();
    // print_get_all_ef_ranklist();
    // // set_firmware_downloading_flag();
//  static uint8_t aaaaaa;
//     wifi_fifo_push(aaaaaa++);

// // norflash_auto_rw_test();
// debug_add_original_ef();

    // uint8_t i;
    // uint8_t list[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10};

    // invert_list(list, sizeof(list));
    // // permute_list_in_random(list, sizeof(list));
    // printlog("list\r");
    // for (i = 0; i < sizeof(list); i++)
    // {
    //     printlog("%d ", list[i]);
    // }
    // printlog("\r");
    // // // // // // // move_data_to_first_in_list(0, list, sizeof(list));
    // // // // // // // for (i = 0; i < sizeof(list); i++)
    // // // // // // // {
    // // // // // // //     printlog("%d ", list[i]);
    // // // // // // // }
    // // // // // // // printlog("\r\n");
    // L0_playCOLOR_Typedef x;
    // x.br = 100;
    // x.type = 1;
    // x.R = 30;
    // x.G = 0;
    // x.B = 0;
    // transmit_playsame_COLOR(&x);
    // // // uint16_t i;
    // // // uint32_t chechsum;
    // // // uint8_t num;
    // // // // debug_delete_schedule();
    // // // // printf("\rK5\r");
    // // // // test_click_brightness(0);
    // // // // if (calibration_enable)
    // // // // {
    // // // //     calibration_enable = 0;
    // // // // }
    // // // // else
    // // // // {
    // // // //     calibration_enable = 1;
    // // // // }
    // // // num = slave.num;
    // // // slave.num = 32;
    // // // transmit_playdata_RGBbr();
    // // // slave.num = num;
    // // norflash_reset_to_zreo();
    // // //     printlog("-------------------------------------------------------------------------------\n");
    // // // print_get_original_ef_ranklist();
    // // // print_get_all_ef_ranklist();
    // // // print_get_favorites_ef_ranklist();
    // // //     printlog("-------------------------------------------------------------------------------\n");
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
    uint8_t i;
    static uint8_t j = 0;
    switch (j)
    {
    case 0:
        if (Tangram[0].R.Now < 250)
        {
            Tangram[0].R.Now+=3;
        }
        else
        {
            j++;
        }
        break;
    case 1:
        if (Tangram[0].G.Now < 250)
        {
            Tangram[0].G.Now+=3;
        }
        else
        {
            j++;
        }
        break;
    case 2:
        if (Tangram[0].B.Now < 250)
        {
            Tangram[0].B.Now+=3;
            Tangram[0].R.Now-=3;
        }
        else
        {
            j++;
        }
        break;
    case 3:

        if (Tangram[0].G.Now)
        {
            Tangram[0].G.Now-=3;
        }
        if (Tangram[0].B.Now)
        {
            Tangram[0].B.Now-=3;
        }
        else
        {
            j++;
        }
        break;
    default:
        if (Tangram[0].R.Now)
        {
            Tangram[0].R.Now-=3;
        }
        j = 0;
        break;
    }

    play_color_in_all_salve_light(255,Tangram[0].R.Now,Tangram[0].G.Now,Tangram[0].B.Now,Tangram[0].W.Now);

    // // Tangram[0].R.Now = tastcolor[test_color_num][0];
    // // Tangram[0].G.Now = tastcolor[test_color_num][1];
    // // Tangram[0].B.Now = tastcolor[test_color_num][2];
    // // Tangram[0].W.Now = tastcolor[test_color_num][3];
    // if (test_onoff)
    // {
    //     // Tangram[0].R.Now = tastcolor[test_color_num][0];
    //     // Tangram[0].G.Now = tastcolor[test_color_num][1];
    //     // Tangram[0].B.Now = tastcolor[test_color_num][2];
    //     // Tangram[0].W.Now = tastcolor[test_color_num][3];
    //     for ( i = 0; i < slave.num; i++)
    //     {
    //         slave.data[i].runnum = 0;
    //     }
    //     play.work.brightness.now = test_brightness;
    //     transmit_slave_play_data();
    // }
    // else
    // {
    //     play_color_in_all_salve_light(0, tastcolor[test_color_num][0], tastcolor[test_color_num][1], tastcolor[test_color_num][2], tastcolor[test_color_num][3]);
    // }
    // // if (test_onoff)
    // // {
    // //     play_color_in_all_salve_light(test_brightness, tastcolor[test_color_num][0], tastcolor[test_color_num][1], tastcolor[test_color_num][2], tastcolor[test_color_num][3]);
    // // }
    // // else
    // // {
    // //     play_color_in_all_salve_light(0, tastcolor[test_color_num][0], tastcolor[test_color_num][1], tastcolor[test_color_num][2], tastcolor[test_color_num][3]);
    // // }
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

/*
 * @Description: 循环切换亮度
 * @param:
 * @return:
 */
void test_switch_brightness(void)
{
    uint16_t temp;

    temp = test_brightness + 10;
    if (temp > 100)
    {
        test_brightness = 0;
    }
    else
    {
        test_brightness = temp;
    }
    // // if (test_brightness < 230)
    // // {
    // //     test_brightness += 30;
    // // }
    // // else if (test_brightness == 255)
    // // {
    // //     test_brightness = 0;
    // // }
    // // else
    // // {
    // //     test_brightness = 255;
    // // }
}

/*
 * @Description: 循环切换颜色
 * @param:
 * @return:
*/
void test_switch_color(void)
{
    if (++test_color_num >= (sizeof(tastcolor) / 4))
    {
        test_color_num = 0;
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


/*
 * @Description: 循环老化测试
 * @param:
 * @return:
*/
void test_aging_cycle(void)
{
    test_switch_color();
    test_switch_brightness();
}

/*
 * @Description: led测试
 * @param:
 * @return:
*/
void debug_ledplay(void)
{
    static uint8_t sta;
    static uint8_t i;
    if (++i > 6)
    {
        i = 0;
        switch (sta)
        {
        case 0:
            LED2_ON();
            LED1_ON();
            sta++;
            break;
        case 1:
            LED2_OFF();
            LED1_ON();
            sta++;
            break;
        case 2:
            LED2_ON();
            LED1_OFF();
            sta++;
            break;
        default:
            LED2_OFF();
            LED1_OFF();
            sta = 0;
            break;
        }
    }
}

void debug_play_rgbbr(void)
{
    uint8_t buf[10];
    buf[0] = 0xFF;
    buf[1] = 0x71;
    buf[2] = 0x00;
    buf[3] = 0x01;
    buf[4] = 0xFF;
    buf[5] = tastcolor[test_color_num][0];                // r
    buf[6] = tastcolor[test_color_num][1];                // g
    buf[7] = tastcolor[test_color_num][2];                // b
    buf[8] = test_brightness;                             // br
    transmit_protocol_frame(&buf, 9, &parse.tx_framebuf); // 通过不定长协议发送
}
