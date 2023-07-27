
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
        {255, 128, 0, 0},   // ��ɫ
        {200, 255, 37, 0},  // ������
        {233, 71, 9, 0},    // �Ⱥ�
        {237, 175, 32, 0},  // ��ɫ
        {87, 140, 188, 0},  // ��ɫ
        {37, 188, 255, 0},  // ǳ��
        {23, 129, 232, 0},  // ��
        {146, 35, 255, 0},  // ��
        {230, 45, 232, 0},  // ����
        {255, 13, 192, 0},  // �Ϻ�
        {90, 167, 167, 0},  // ��
        {150, 215, 198, 0}, // ����
        {186, 201, 74, 0},  // ����
        {240, 218, 220, 0}, // ��ɫ
        {245, 150, 176, 0}, // ���
        {254, 225, 153, 0}, // ��ɫ
        {118, 214, 201, 0}, // ��ɫ
        {133, 188, 218, 0}, // ��ɫ
        {252, 172, 230, 0}, // ǳ��
        {253, 135, 221, 0}, // ��ɫ
        {250, 28, 195, 0},  // ���ɫ
        {238, 0, 242, 0},   // ǳ�Ϻ�
        {112, 0, 240, 0},   // ǳ��ɫ
        {60, 0, 169, 0},    // ����ɫ
        {24, 16, 55, 0},    // ����ɫ
        {57, 35, 97, 0},    // ��ɫ
        {113, 84, 174, 0},  // ǳ��
        {128, 156, 228, 0}, // ǳ����
        {98, 191, 215, 0},  // ǳ��
        {82, 209, 192, 0},  // ǳ��
        {121, 246, 194, 0}, // ����
        {4, 164, 94, 0},    // ��ɫ
        {241, 242, 237, 0}, // �Ұ�
        {128, 211, 215, 0}, // ǳ��
        {113, 185, 223, 0}, // ��ɫ
        {41, 15, 180, 0},   // ����ɫ
        {246, 234, 246, 0}, // ����
        {72, 27, 137, 0},   // ��ɫ
        {247, 198, 166, 0}, // ��ɫ
        {247, 131, 137, 0}, // ��ɫ
        {166, 58, 76, 0},   // ���
        {38, 38, 94, 0},    // ����
};
uint8_t test_onoff=1;
uint8_t test_color_num;
uint8_t test_brightness=255;


/*���Ե�Ч�Ĵ洢��д*/
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
/*��������Զ����Ч*/
void debug_add_original_ef(void)
{
    static uint8_t i=128;
    Efdetail_TypeDef ef;
    // // i = Random_Generate() % original_ef_num;
    // // i += 128;
    i++;
    printf("add original ranklist %d\r", i);
    get_effect(&ef,0);  // ������0����Ч
    add_original_ef(&ef, i);
    print_get_original_ef_ranklist();
}
/*����ɾ���Զ����Ч*/
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
 * @Description: norflashѭ����д����
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
    // erase_firmware_block64K_norflash(); // �����̼���

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

/*������Ӳ����б�*/
void debug_add_playlist(void)
{
    static uint8_t i;
    playdetail_TypeDef playdetail;
    i++;
    memset(&playdetail,0,sizeof(playdetail));
    printf("add playlist ranklist %d\r", i);
    add_playlist(&playdetail,i);

}


/*����ɾ�������б�*/
void debug_delete_playlist(void)
{

    playlist_ranklist_TypeDef ranklist; // �б���Ϣ
    get_playlist_ranklist(&ranklist);
    printf("delete playlist ranklist %d\r", ranklist.list[0]);
    delete_playlist( ranklist.list[0]);
    get_playlist_ranklist(&ranklist);
    print_playlist_ranklist(&ranklist);
}

/*������Ӷ�ʱ��*/
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

/*����ɾ����ʱ��*/
void debug_delete_schedule(void)
{
    printlog(" debug delete schedule\r");
    delete_schedule(0);
}

/*�л���һ���õ�Ч*/
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

/*�л���һ���õ�Ч*/
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



/*����1������Ժ���*/
void debug_K1(void)
{
    printf("\rK1\r");
    test_onoff_play();
    // print_slave_data();
    // printf("init effect...\r");
    // // mcu_update_allef_ranklist();
    // copy_built_in_ef_to_norflash(); // ��ʼ����Ч��Ϣ
}
/*����2������Ժ���*/
void debug_K2(void)
{
    printf("\rK2\r");
    test_change_color(1);

}
/*����3������Ժ���*/
void debug_K3(void)
{
    printf("\rK3\r\n");
    test_change_color(0);

}
/*����4������Ժ���*/
void debug_K4(void)
{
    printf("\rK4\r");
    test_click_brightness(1);
    // debug_play_next_effect();


}

/*����5������Ժ���*/
void debug_K5(void)
{
    uint16_t i;
    uint32_t chechsum;
    printf("\rK5\r");
    test_click_brightness(0);
}

/*

dp_download_all_effect_ranklist_handle ��

*/
/*���Կ�ʼ��ͣ������ɫ*/
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

/*���Բ�����ɫ*/
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
/*�����л���ɫ*/
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
/*���Ե����Ӽ�����*/
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
/*���Գ����Ӽ�����*/
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
