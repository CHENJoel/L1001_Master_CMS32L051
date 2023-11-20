
#include "play.h"

play_TypeDef play;
// // uint8_t dma_buffer[DMA_BUFFER_SIZE];
const uint8_t bright_table[5] = {5, 25, 55, 75, 100};
// const uint8_t bright_table[5] = {1, 15, 40, 75, 100};

/*���ų�ʼ��*/
void play_init(void)
{
    switch_playlist(0); // �л���Ĭ�ϲ����б�
    play.source = SOURCE_LIST;
    play.playmode = PLAY_IN_SEQUENCE;
    memset(&play.detail.history, NULL_EFFECTNUM, sizeof(play.detail.history));
    // print_play_history();
}
/*������ʷ���ŵ�Ч*/
void push_playnum_in_history(uint8_t efnum)
{
    uint8_t buffer[sizeof(play.detail.history)];
    memcpy(&buffer[1], &play.detail.history[0], (sizeof(buffer) - 1));
    buffer[0] = efnum; // ��ͷ������º���
    memcpy(&play.detail.history[0], &buffer[0], sizeof(play.detail.history));
    printlog("push_playnum_in_history:%d\r",efnum);
    // print_play_history();
}
/*
 * @Description: ȡ����ʷ���ŵ�Ч
 * @param:
 * @return:
*/
uint8_t pop_playnum_in_history(void)
{
    uint8_t buffer[sizeof(play.detail.history)];
    uint8_t histoy;
    histoy = play.detail.history[0];
    memcpy(&buffer[0], &play.detail.history[1], (sizeof(buffer) - 1));
    buffer[sizeof(play.detail.history) - 1] = 0xFF; // ��β�������Ч��Ч
    memcpy(&play.detail.history[0], &buffer[0], sizeof(play.detail.history));
    // print_play_history();
    return histoy;
}

/*
 * @Description: ��ͣ���ŵ�Ч
 * @param:
 * @return:
*/
void effect_play_pause(void)
{
    play.status = PAUSE;
    printlog("effect_play_pause\r");
}

/*
 * @Description: �������ŵ�Ч
 * @param:
 * @return:
*/
void resume_play_effect(void)
{
    play.status = RUN;
    printlog("resume_play_effect\r");
}

/*
 * @Description: ����ư����ģʽ
 * @param:
 * @return:
*/
void enter_device_pairing_mode(void)
{
    if (play.control_mode != PAIRING_MODE)
    {
        effect_play_pause();
        // // // turn_off_all_salve_light();

        // // play_color_in_all_salve_light();
        printlog("enter_device_pairing_mode\r");
    }
    play.control_mode = PAIRING_MODE;
}
/*
 * @Description: �����������ŵ�Чģʽ
 * @param:
 * @return:
 */
void enter_playing_effect_mode(void)
{
    if (play.control_mode != PLAYING_MODE)
    {
        printlog("enter_playing_effect_mode\r");
    }
    play.control_mode = PLAYING_MODE;
    resume_play_effect();
}

/* 
 * @Description: ����Ԥ����Чģʽ
 * @param: 
 * @return: 
*/ 
void enter_preview_effect_mode(Efdetail_TypeDef* efdetail)
{
    printlog("enter_preview_effect_mode\r");
    play.control_mode = PREVIEW_MODE;
    play_preview_effect(efdetail);
}


/* 
 * @Description: �˳�Ԥ����Чģʽ
 * @param: 
 * @return: 
*/ 
void exit_preview_effect_mode(void)
{
    if (play.control_mode != PLAYING_MODE)
    {
        printlog("exit_preview_effect_mode\r");
    }
    play.control_mode = PLAYING_MODE;
    play_current_effect();
}


/*�ڱ��л�ȡ��һ��Ԫ��*/
uint8_t get_list_next_num(uint8_t *list, uint8_t size, uint8_t num)
{
    uint8_t i;
    if (size == 0)
    {
        printlog("[error] wrong number of list size\r");
        return 0;
    }
    for (i = 0; i < size; i++)
    {
        if (list[i] == num)
        {
            if (i < size - 1)
            {
                return list[i + 1];
            }
            else
            {
                return list[0];
            }
        }
    }
}

/*�л���Ч*/
uint8_t switch_effect(uint8_t efnum)
{
    // // ef_ranklist_TypeDef eflist;
    uint8_t i;
    printlog("switch effect num:%d\r",efnum);
    if (efnum==255)
    {
        printlog("[error] switch wrong effect num :%d\r", efnum);
        return 0;
    }
    // // get_allef_ranklist(&eflist);
    // // for (i = 0; i < eflist.num; i++)
    // // {
    // //     if (eflist.list[i] == efnum) // ˳����ڴ��ڱ��л��ĵ�Ч
    // //     {
    // //         j = 1;
    // //         break;
    // //     }
    // // }

    for (i = 0; i < play.detail.listefsum; i++)
    {
        if (play.detail.list[i] == efnum) // ˳����ڴ��ڱ��л��ĵ�Ч
        {
            play_new_effect(efnum);
            // push_playnum_in_history(efnum);
            // print_playstatus();
            return 1;
        }
    }
    printlog("[error] switch wrong effect num :%d\r", efnum);
    return 0;
}
/*�л����µ�Ч*/
uint8_t switch_lastnext_effect(switchplay_enum num)
{
    playdetail_TypeDef playdetail;
    switch (num)
    {
    case LAST_EFFECT: // ��һ����Ч
        printlog("play last effect\r");
        switch_last_ef_in_list();
        break;
    case NEXT_EFFECT: // ��һ����Ч
        printlog("play next effect\r");
        switch_next_ef_in_list();
        break;
    default:
        printlog("[error] wrong switch effect command %d\r", num);
        printAssert();
        break;
    }
}

/*
 * @Description: ���б��в�����һ��Ч
 * @param:
 * @return:
*/
void switch_next_ef_in_list(void)
{
    // // // uint8_t cur_efindex;// ��ǰ��Ч
    // // // cur_efindex = play.detail.idex_inlist;
    if (play.source == SOURCE_LIST)
    {

        if (++play.detail.idex_inlist >= play.detail.listefsum) // �Ѿ������һ����Ч
        {
            if (play.cyclemode == CYCLE_IN_LOOP) // ѭ������
            {
                play.detail.idex_inlist = 0;
                start_play_list(play.detail.listindex); // ���²��Ÿ��б�
            }
            else /* CYCLE_IN_ONCE �����б� */
            {
                play.detail.idex_inlist = play.detail.listefsum - 1; // ͣ�����һ����Ч
            }
        }
        else
        {
            play.detail.efindex = play.detail.list[play.detail.idex_inlist]; // ȡ����Ч����
            switch_effect(play.detail.efindex);                              // �л���Ч
        }
    }
    else
    {
        printlog("switch effect failed,not in SOURCE_LIST\r");
    }
    // // //    uint8_t num, i, flag;
    // // //    if (play.playmode == PLAY_IN_RANDOM)
    // // //    {
    // // //        while (1)
    // // //        {
    // // //             num =get_random_number();
    // // //             flag = 0;
    // // //             if (num != play.detail.efindex)
    // // //             {
    // // //                 for (i = 0; i < play.detail.listefsum; i++)
    // // //                 {
    // // //                     if (num != play.detail.list[i])
    // // //                     {
    // // //                         flag = 1;
    // // //                     }
    // // //                 }
    // // //             }
    // // //             if (flag)
    // // //             {
    // // //                 break;
    // // //             }
    // // //        }
    // // //        switch_effect(num);
    // // //    }
    // // //    else /*PLAY_IN_SEQUENCE*/
    // // //    {
    // // //        for (i = 0; i < play.detail.listefsum; i++)
    // // //        {
    // // //             if (play.detail.list[i] == play.detail.efindex)
    // // //             {
    // // //                 break;
    // // //             }
    // // //        }
    // // //        if (++i >= play.detail.listefsum)
    // // //        {
    // // //             i = 0;
    // // //        }
    // // //        switch_effect(play.detail.list[i]);
    // // //    }
}

/*
 * @Description: ���б��в�����һ��Ч
 * @param:
 * @return:
 */
void switch_last_ef_in_list(void)
{
    // // //    switch_effect(pop_playnum_in_history());
    if (play.source == SOURCE_LIST)
    {
        if (play.detail.idex_inlist > 0)
        {
            play.detail.idex_inlist--;
        }
        play.detail.efindex = play.detail.list[play.detail.idex_inlist]; // ȡ����Ч����
        switch_effect(play.detail.efindex);                              // �л���Ч
    }
    else
    {
        printlog("switch effect failed,not in SOURCE_LIST\r");
    }
}

/* �л������б� */
uint8_t switch_playlist(uint8_t listnum)
{
    playlist_ranklist_TypeDef playlist;
    uint8_t i;
    // // uint8_t j = 0;
    printlog("switch playlist num:%d\r",listnum);
    // if (listnum == play.detail.listindex) // �뵱ǰ���ű�һ��
    // {
    //     printlog("[warning]switch same playlist num :%d\r", listnum);
    //     return 0;
    // }
    get_playlist_ranklist(&playlist);
    for (i = 0; i < playlist.num; i++)
    {
       if (playlist.list[i] == listnum) // ˳����ڴ��ڱ��л����б��
       {
            start_play_list(listnum);
            return 1;

       }
    }
    printlog("[error] switch wrong playlist num :%d\r", listnum);
    return 0;


}

/*------------------------------------------------------------------------------------------------------------------------------------*/
/*
 * @Description: �л�����ģʽ
 * @param:
 * @return:
 */
void switch_playmode(PlayMode_enum mod)
{
    /*
        PLAY_IN_RANDOM,   // �������
        PLAY_IN_SEQUENCE, // ˳�򲥷�
        */
    playdetail_TypeDef playdetail;
    if (mod == PLAY_IN_RANDOM)
    {
       play.playmode = PLAY_IN_RANDOM;
    }
    else
    {
       play.playmode = PLAY_IN_SEQUENCE;
    }
    get_playdetail(&playdetail, play.detail.listindex);
    memcpy(&play.detail.list, &playdetail.list, sizeof(play.detail.list));
    if (play.playmode == PLAY_IN_RANDOM)
    {
       permute_list_in_random(&play.detail.list, play.detail.listefsum); // �����������
    }
    adjust_play_list();
    // // print_playstatus();
}

/*
 * @Description: �л�ѭ��ģʽ
 * @param:
 * @return:
 */
void switch_cyclemode(CycleMode_enum mod)
{
    /*
      CYCLE_IN_LOOP, // ѭ������
      CYCLE_IN_ONCE, // �����б�
    */
    if (mod == CYCLE_IN_LOOP)
    {
       play.cyclemode = CYCLE_IN_LOOP;
    }
    else
    {
       play.cyclemode = CYCLE_IN_ONCE;
    }
}

/*
 * @Description: ���ر��ص�Ч��Ϣ
 * @param:
 * @return:
*/
void load_local_effect_data(void)
{
    uint8_t i;
    get_effect_detail(&play.efdetail, play.detail.efindex);
    for (i = 0; i < play.efdetail.EfColorInf.colorNum; i++)
    {
        memcpy(&EF_Buffer.color_buffer.color[i],&play.efdetail.EfColorInf.ColorID[i].color, sizeof(RGBWInf_TypeDef));
    }
}

/* 
 * @Description: ����Ԥ����Ч��Ϣ
 * @param: 
 * @return: 
*/
void load_preview_effect_data(Efdetail_TypeDef *efdetail)
{
    uint8_t i;
    memcpy(&play.efdetail, efdetail, sizeof(Efdetail_TypeDef));
    for (i = 0; i < play.efdetail.EfColorInf.colorNum; i++)
    {
        memcpy(&EF_Buffer.color_buffer.color[i], &play.efdetail.EfColorInf.ColorID[i].color, sizeof(RGBWInf_TypeDef));
    }
}

/*
 * @Description: ��λ����֡����
 * @param:
 * @return:
*/
void play_frame_reset(void)
{
    uint8_t i;
    for (i = 0; i < 32; i++)
    {
        Tangram[i].Frame_Now = 0;
    }
}

/*
 * @Description: ������ӻ������б��
 * @param:
 * @return:
*/
void figure_slave_run_number(void)
{
    uint16_t i, j,k;
    uint8_t *sur;
    uint8_t *tar;
    uint16_t temp1, temp2,temp3,temp4;
    uint16_t X_max, X_min, Y_max, Y_min, X_center, Y_center;
    uint16_t X_num,Y_num;

    X_max = 0;
    X_min = -1;
    Y_max = 0;
    Y_min = -1;

    temp1 = temp2 = -1;
    X_num = Y_num = 0;


    for (i = 0; i <slave.num; i++)
    {
        if (temp1 != slave.data[i].cooed_x)
        {
            X_num++; // �ۼ�X�����ϵ��豸����
        }
        if (temp2 != slave.data[i].cooed_y)
        {
            Y_num++; // �ۼ�Y�����ϵ��豸����
        }
        if (slave.data[i].cooed_x > X_max)
        {
            X_max = slave.data[i].cooed_x; // �����X����
        }
        if (slave.data[i].cooed_y > Y_max)
        {
            Y_max = slave.data[i].cooed_y; // �����Y����
        }
        if (slave.data[i].cooed_x < X_min)
        {
            X_min = slave.data[i].cooed_x; // ����СX����
        }
        if (slave.data[i].cooed_y < Y_min)
        {
            Y_min = slave.data[i].cooed_y; // ����СY����
        }
        temp1 = slave.data[i].cooed_x;
        temp2 = slave.data[i].cooed_y;
    }
    // // printlog("X_num: %d, Y_num: %d\r", X_num, Y_num);
    // // printlog("X_min: %d, Y_min: %d\r", X_min, Y_min);
    if (play.efdetail.Direction == DIRECTION_UP || play.efdetail.Direction == DIRECTION_DOWN)
    {
        EF_Work.Module_WorkNum = Y_num;
        temp1 = 0;
        temp2 = 0;
        for (j = 0; j < 16; j++)
        {
            for (i = 0; i <slave.num; i++)
            {
                if (slave.data[i].cooed_y == j)
                {
                    temp2 = 1; // ��ǰ�������豸
                    if (play.efdetail.Direction == DIRECTION_UP)
                    {
                        slave.data[i].runnum = temp1; // ����
                    }
                    else
                    {
                        slave.data[i].runnum = Y_num - temp1 - 1; // ����;
                    }
                }
            }
            if (temp2)
            {
                temp1++;
                temp2 = 0;
            }
        }
    }
    else if (play.efdetail.Direction == DIRECTION_LEFT || play.efdetail.Direction == DIRECTION_RIGHT)
    {
        EF_Work.Module_WorkNum = X_num;
        temp1 = 0;
        temp2 = 0;
        for (j = 0; j < 16; j++)
        {
            for (i = 0; i <slave.num; i++)
            {
                if (slave.data[i].cooed_x == j)
                {
                    temp2 = 1; // ��ǰ�������豸
                    if (play.efdetail.Direction == DIRECTION_LEFT)
                    {
                        slave.data[i].runnum = temp1; // ����
                    }
                    else
                    {
                        slave.data[i].runnum = X_num - temp1 - 1; // ����;
                    }
                }
            }
            if (temp2)
            {
                temp1++;
                temp2 = 0;
            }
        }
    }
    else if (play.efdetail.Direction == DIRECTION_SEPARATE || play.efdetail.Direction == DIRECTION_CONVERGE)
    {

        X_center = (X_max + X_min)/2;
        Y_center = (Y_max + Y_min)/2;
        temp4 = 0;
        for (j = 0; j < 16; j++)
        {
            temp3 = 0;
            for (i = 0; i <slave.num; i++)
            {
                temp1 = diff_cal(X_center, slave.data[i].cooed_x);
                temp2 = diff_cal(Y_center, slave.data[i].cooed_y);
                if (temp1 > temp2)
                {
                    if (temp1 == j)
                    {
                        temp3 = 1;
                        slave.data[i].runnum = temp4; // ����
                    }
                }
                else
                {
                    if (temp2 == j)
                    {
                        temp3 = 1;
                        slave.data[i].runnum = temp4; // ����
                    }
                }
            }
            if (temp3)
            {
                temp4++;
            }
        }
        temp4 = 0;
        for (i = 0; i < slave.num; i++)
        {
            if (slave.data[i].runnum > temp4)
            {
                temp4 = slave.data[i].runnum; // ��ѯ�������
            }
        }
        EF_Work.Module_WorkNum = temp4;
        if (play.efdetail.Direction == DIRECTION_CONVERGE)
        {
            for (i = 0; i <slave.num; i++)
            {
                temp1 = slave.data[i].runnum;
                slave.data[i].runnum = temp4 - temp1; // ���ɵ�����
            }
        }
    }
    // printlog("Module_WorkNum:%d\r", EF_Work.Module_WorkNum);
}

/*
 * Description: ���ɸõ�Ч�Ķ�������
 * @param: ��
 * @return: ��
 */
void generate_play_video_buffer(void)
{
    if (play.efdetail.EffectType == STATIC_TYPE)
    {
        play.efdetail.Flow = FLOW_STATIC; // ��̬��Ч����Ӧ��̬Ч��
    }

    switch (play.efdetail.Flow) // ���ݵ�Ч�����Զ�������ݣ������µ�ɫ����
    {
    case FLOW_STATIC: /*��̬*/
        Flow_Static_Init();
        break;
    case FLOW_BREATH: /*����*/
        Flow_Breath_Init();
        break;
    case FLOW_STREAM: /*����*/
        Flow_Stream_Init();
        break;
    case FLOW_REVERB: /*����*/
        Flow_Reverberate_Init();
        break;
    case FLOW_HOPSCO: /*����*/
        Flow_Hopscotch_Init();
        break;
    case FLOW_LIGHTN: /*����*/
        Flow_Lightning_Init();
        break;
    case FLOW_IGNITE: /*��ȼ*/
        Flow_Ignite_Init();
        break;
    case FLOW_RANDOM: /*���*/
        Flow_Random_Init();
        break;
    default:
        break;
    }
}
/*
 * @Description: ���ŵ�Ч
 * @param:
 * @return:
 */
void play_effect_video(void)
{
#ifndef printlog_enabled
    if (play.control_mode == PLAYING_MODE) // ��������ģʽ
    {
        if (play.work.sw_status == SW_ON)
        {
            if (play.status == RUN)
            {
                effect_play_color_calu();
            }
            else
            {
            }

            // // transmit_playdata_RGBbr();
            transmit_playdata_COLOR();
            // transmit_playdata_RGBbr();
        }
        else
        {
            turn_off_all_salve_light();
        }
    }
    else if (play.control_mode == PREVIEW_MODE) // ��ЧԤ��ģʽ
    {
        effect_play_color_calu();
        // transmit_playdata_RGBbr();
        transmit_playdata_COLOR();
        // transmit_playdata_RGBbr();
    }
    else /*PAIRING_MODE �ư����ģʽ */
    {
        // // transmit_playdata_RGBbr();
    }
#endif
}

/*
 * @Description: ϵͳ���ŵ�Ч��ʼ��
 * @param:
 * @return:
 */
void play_sys_effect_init(void)
{
    // // play.detail.efindex = 17; // df_Snake
    // // play_current_effect();   
    switch_effect(23);   // "Colorful"
}

/* 
 * @Description: ��ͷ��ʼ���ŵ�ǰ��Ч
 * @param: 
 * @return: 
*/ 
void play_current_effect(void)
{
    load_local_effect_data();
    preprocess_play_effect();
}


/* 
 * @Description: �������ɵ�Ч
 * @param: 
 * @return: 
*/ 
void play_free_effect(uint8_t efnum)
{
    play.source = SOURCE_FREE;
    play_new_effect(efnum);
}

/*
 * @Description: �����µ�Ч
 * @param:
 * @return:
*/
void play_new_effect(uint8_t efnum)
{
    printlog("play_new_effect:%d\r",efnum);
    // if (play.detail.efindex == efnum)
    // {
    //     return;
    // }
    play.detail.efindex = efnum;
    play.work.playtime_cnt = 0;
    play_current_effect();
    // mcu_update_current_play_ef_index();  
    mcu_update_playstatus();
}

/* 
 * @Description: Ԥ����������
 * @return: 
*/ 
void preprocess_play_effect(void)
{   
    play.work.global_setting.brightness_set=play.efdetail.Brightness1;
    play_frame_reset();
    EF_Work.FrameInfro.image_adr = (uint8_t *)&EF_Work.Color_buffer; // ɫ������
    figure_slave_run_number();
    generate_play_video_buffer();
}

/*
 * @Description: ����Ԥ����Ч
 * @param:
 * @return:
*/

void play_preview_effect(Efdetail_TypeDef* efdetail)
{
    printlog("play_preview_effect\r");
    load_preview_effect_data(efdetail);
    preprocess_play_effect();
}

// // // // /*
// // // //  * @Description: ���ʹӻ���������
// // // //  * @param:
// // // //  * @return:
// // // // */
// // // // void transmit_slave_play_data(void)
// // // // {
// // // //     uint8_t i;
// // // //     uint16_t size;
// // // //     uint8_t buffer[DMA_BUFFER_SIZE];
// // // //     calibration_TypeDef calib_t;
// // // //     if (slave.num) // ���豸���ߵ�ʱ��ŷ�������
// // // //     {
// // // //         ((playpack_Typedef *)(&buffer))->head.type = PLAY_DATA;
// // // //         ((playpack_Typedef *)(&buffer))->head.num = slave.num;
// // // //         size = sizeof(packhead_Typedef) + slave.num * sizeof(playdata_Typedef);
// // // //         for (i = 0; i < slave.num; i++)
// // // //         {
// // // //             ((playpack_Typedef *)(&buffer))->play[i].addr = slave.data[i].id;

// // // //             calib_t.shape = slave.data[i].shape;
// // // //             calib_t.color.brightness = play.work.brightness.now;
// // // //             calib_t.color.R = Tangram[slave.data[i].runnum].R.Now;
// // // //             calib_t.color.G = Tangram[slave.data[i].runnum].G.Now;
// // // //             calib_t.color.B = Tangram[slave.data[i].runnum].B.Now;
// // // //             calib_t.color.W = Tangram[slave.data[i].runnum].W.Now;
// // // //             if (calibration_enable)
// // // //             {
// // // //                 calibration_color(&calib_t);
// // // //             }


// // // //             ((playpack_Typedef *)(&buffer))->play[i].bri = calib_t.color.brightness;
// // // //             ((playpack_Typedef *)(&buffer))->play[i].R = calib_t.color.R;
// // // //             ((playpack_Typedef *)(&buffer))->play[i].G = calib_t.color.G;
// // // //             ((playpack_Typedef *)(&buffer))->play[i].B = calib_t.color.B;
// // // //             ((playpack_Typedef *)(&buffer))->play[i].W = calib_t.color.W;

// // // //             // ((playpack_Typedef *)(&buffer))->play[i].bri = play.work.brightness.now;
// // // //             // ((playpack_Typedef *)(&buffer))->play[i].R = Tangram[slave.data[i].runnum].R.Now;
// // // //             // ((playpack_Typedef *)(&buffer))->play[i].G = Tangram[slave.data[i].runnum].G.Now;
// // // //             // ((playpack_Typedef *)(&buffer))->play[i].B = Tangram[slave.data[i].runnum].B.Now;
// // // //             // ((playpack_Typedef *)(&buffer))->play[i].W = Tangram[slave.data[i].runnum].W.Now;
// // // //         }
// // // //         transmit_protocol_frame(&buffer, size, &parse.tx_framebuf); // ͨ��������Э�鷢��
// // // //     }
// // // // }

/*
 * @Description: ���еƵ���ͬ����ɫ
 * @param: ����
 * @param: ��
 * @param: ��
 * @param: ��
 * @param: ��
 * @return: ��
*/
 void play_color_in_all_salve_light(uint8_t bri, uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
    uint16_t size;
    uint8_t buffer[sizeof(packhead_Typedef) + sizeof(playdata_Typedef)];
    ((playpack_Typedef *)(&buffer))->head.type = PLAY_DATA;
    ((playpack_Typedef *)(&buffer))->head.num = 1;
    ((playpack_Typedef *)(&buffer))->play[0].addr = Public_Addr;
    ((playpack_Typedef *)(&buffer))->play[0].bri = bri;
    ((playpack_Typedef *)(&buffer))->play[0].R = r;
    ((playpack_Typedef *)(&buffer))->play[0].G = g;
    ((playpack_Typedef *)(&buffer))->play[0].B = b;
    ((playpack_Typedef *)(&buffer))->play[0].W = w;
    transmit_protocol_frame(&buffer, sizeof(buffer), &parse.tx_framebuf); // ͨ��������Э�鷢��

    /**********************/
    // // ((complay_Typedef *)(&dma_buffer))->head = MPLAY_HEADER;
    // // ((complay_Typedef *)(&dma_buffer))->addr = Public_Addr;
    // // ((complay_Typedef *)(&dma_buffer))->bri = bri;
    // // ((complay_Typedef *)(&dma_buffer))->R = r;
    // // ((complay_Typedef *)(&dma_buffer))->G = g;
    // // ((complay_Typedef *)(&dma_buffer))->B = b;
    // // ((complay_Typedef *)(&dma_buffer))->W = w;
    // // ((complay_Typedef *)(&dma_buffer))->sum = checksum_calculate(&dma_buffer, sizeof(complay_Typedef) - 1);

    // // DMA_Start(DMA_VECTOR_ST0, CTRL_DATA_ST0, DMA_MODE_NORMAL, DMA_SIZE_BYTE, sizeof(complay_Typedef), dma_buffer, (void *)&SCI0->TXD0);
    // // DMA_Enable(DMA_VECTOR_ST0);
    // // DMA_Trigger(DMA_VECTOR_ST0);
}

void set_color_data_of_all_light()
{

}

/*
 * @Description: �ر����еư�
 * @param: ��
 * @return: ��
*/
void turn_off_all_salve_light(void)
{
    L0_playRGBbr_Typedef x;
    x.R = 0;
    x.G = 0;
    x.B = 0;
    x.br = 0;
    transmit_playsame_RGBbr(&x);
    // // // play_color_in_all_salve_light(0,0,0,0,0);

}

/*
 * @Description: �����ض����ȵ�����
 * @param: Դ����ָ��
 * @param: Ҫ���͵ĳ���
 * @return: ��
 */
void transmit_buffer_data(uint8_t *sur, uint16_t len)
{
    if ((((void *)0) == sur) || (0 == len))
    {
        return;
    }
    DMA_Stop(DMA_VECTOR_ST0);
    DMA_Start(DMA_VECTOR_ST0, CTRL_DATA_ST0, DMA_MODE_NORMAL, DMA_SIZE_BYTE, len, sur, (void *)&SCI0->TXD0);
    DMA_Enable(DMA_VECTOR_ST0);
    DMA_Trigger(DMA_VECTOR_ST0);
}

/********************************************************************************************************************/

/*
 * @Description: ���͡�RGBbr����ʽ�Ĳ�������
 * @param:
 * @return:
 */
void transmit_playdata_RGBbr(void)
{
    uint8_t i;
    L0_cmd_playRGBbr_Typedef xPlay;
    if (slave.num) // ���豸���ߵ�ʱ��ŷ�������
    {
        xPlay.head.dev_adr = ADDR_PUBLIC;    // �豸��ַ
        xPlay.head.cmd = CMD_SLAVE_PLAY_RGB; // ���ŵƹ� ��RGBbr����ʽ
        xPlay.head.type = MES_ASK;           // ��������
        xPlay.playnum = slave.num;
        for (i = 0; i < xPlay.playnum; i++)
        {
            xPlay.dev[i].cid = slave.data[i].id;
            xPlay.dev[i].br = play.work.brightness.now;
            // if (Tangram[slave.data[i].runnum].W.Now == RGB_COLOR)
            // {
                xPlay.dev[i].R = Tangram[slave.data[i].runnum].R.Now;
                xPlay.dev[i].G = Tangram[slave.data[i].runnum].G.Now;
                xPlay.dev[i].B = Tangram[slave.data[i].runnum].B.Now;
            // }
            // else // KELVIN_COLOR
            // {
            //     xPlay.dev[i].R = 0;
            //     xPlay.dev[i].G = 0;
            //     xPlay.dev[i].B = 0;
            // }
        }
        transmit_protocol_frame((uint8_t *)&xPlay, &((L0_cmd_playRGBbr_Typedef *)0)->dev[slave.num], &parse.tx_framebuf); // ͨ��������Э�鷢��
    }
}

/*
 * @Description: ���͡�COLOR����ʽ�Ĳ�������
 * @param:
 * @return:
 */
void transmit_playdata_COLOR(void)
{
    uint8_t i;
    L0_cmd_playCOLOR_Typedef xPlay;
    uint16_t kel;
    if (slave.num) // ���豸���ߵ�ʱ��ŷ�������
    {
        xPlay.head.dev_adr = ADDR_PUBLIC;      // �豸��ַ
        xPlay.head.cmd = CMD_SLAVE_PLAY_COLOR; // ���ŵƹ� ��COLOR����ʽ
        xPlay.head.type = MES_ASK;             // ��������
        xPlay.playnum = slave.num;
        for (i = 0; i < xPlay.playnum; i++)
        {
            xPlay.dev[i].cid = slave.data[i].id;
            xPlay.dev[i].br = play.work.brightness.now;
            if (Tangram[slave.data[i].runnum].W.Now == RGB_COLOR)
            {
                xPlay.dev[i].type = RGB_COLOR;
                xPlay.dev[i].R = Tangram[slave.data[i].runnum].R.Now;
                xPlay.dev[i].G = Tangram[slave.data[i].runnum].G.Now;
                xPlay.dev[i].B = Tangram[slave.data[i].runnum].B.Now;
            }
            else // KELVIN_COLOR
            {
                xPlay.dev[i].type = KELVIN_COLOR;
                kel = Tangram[slave.data[i].runnum].R.Now << 8;
                kel |= Tangram[slave.data[i].runnum].G.Now;
                xPlay.dev[i].R = kel / 100;
                xPlay.dev[i].G = 0;
                xPlay.dev[i].B = 0;
            }
        }
        transmit_protocol_frame((uint8_t *)&xPlay, &((L0_cmd_playCOLOR_Typedef*)0)->dev[slave.num], &parse.tx_framebuf); // ͨ��������Э�鷢��
    }
}

/*
 * @Description: �㲥���͡�RGBbr����ʽ�Ĳ�������
 * @param:
 * @return:
 */
void transmit_playsame_COLOR(L0_playCOLOR_Typedef *x)
{
    L0_cmd_playCOLOR_Typedef xPlay;
    if (slave.num) // ���豸���ߵ�ʱ��ŷ�������
    {
        xPlay.head.dev_adr = ADDR_PUBLIC;    // �豸��ַ
        xPlay.head.cmd = CMD_SLAVE_PLAY_COLOR; // ���ŵƹ� ��RGBbr����ʽ
        xPlay.head.type = MES_ASK;           // ��������
        xPlay.playnum = slave.num;
        xPlay.dev[0].cid = ADDR_PUBLIC;
        xPlay.dev[0].br = x->br;
        xPlay.dev[0].type = x->type;
        xPlay.dev[0].R = x->R;
        xPlay.dev[0].G = x->G;
        xPlay.dev[0].B = x->B;
        transmit_protocol_frame((uint8_t *)&xPlay, &((L0_cmd_playCOLOR_Typedef *)0)->dev[1], &parse.tx_framebuf); // ͨ��������Э�鷢��
    }
}

/*
 * @Description: �㲥���͡�RGBbr����ʽ�Ĳ�������
 * @param:
 * @return:
 */
void transmit_playsame_RGBbr(L0_playRGBbr_Typedef *x)
{
    L0_cmd_playRGBbr_Typedef xPlay;
    if (slave.num) // ���豸���ߵ�ʱ��ŷ�������
    {
        xPlay.head.dev_adr = ADDR_PUBLIC;    // �豸��ַ
        xPlay.head.cmd = CMD_SLAVE_PLAY_RGB; // ���ŵƹ� ��RGBbr����ʽ
        xPlay.head.type = MES_ASK;           // ��������
        xPlay.playnum = slave.num;
        xPlay.dev[0].cid = ADDR_PUBLIC;
        xPlay.dev[0].br = x->br;
        xPlay.dev[0].R = x->R;
        xPlay.dev[0].G = x->G;
        xPlay.dev[0].B = x->B;
        transmit_protocol_frame((uint8_t *)&xPlay, &((L0_cmd_playRGBbr_Typedef *)0)->dev[1], &parse.tx_framebuf); // ͨ��������Э�鷢��
    }
}



/* 
 * @Description: �ư���ʾ���״̬
 * @param: 
 * @return: 
*/ 
void light_device_pairing_play(app_device_control_Typedef *x)
{
    uint8_t i;
    L0_cmd_playRGBbr_Typedef xPlay;
    xPlay.playnum = x->lightnum;
    if (xPlay.playnum) // ���豸���ߵ�ʱ��ŷ�������
    {
        xPlay.head.dev_adr = ADDR_PUBLIC;    // �豸��ַ
        xPlay.head.cmd = CMD_SLAVE_PLAY_RGB; // ���ŵƹ� ��RGBbr����ʽ
        xPlay.head.type = MES_ASK;           // ��������
        for (i = 0; i < xPlay.playnum; i++)
        {
            xPlay.dev[i].cid = slave.data[i].id;
            if (x->lightsta[i].lightsta == PERSENT) // ��ǰ����
            {
                xPlay.dev[i].br = 100;
                xPlay.dev[i].R = 255;
                xPlay.dev[i].G = 255;
                xPlay.dev[i].B = 0;
            }
            else if (x->lightsta[i].lightsta == LIGHTED) // �ѵ���
            {
                xPlay.dev[i].br = 20;
                xPlay.dev[i].R = 255;
                xPlay.dev[i].G = 255;
                xPlay.dev[i].B = 0;
            }
            else /* UNLIGHT, // δ����*/
            {
                xPlay.dev[i].br = 0;
                xPlay.dev[i].R = 0;
                xPlay.dev[i].G = 0;
                xPlay.dev[i].B = 0;
            }
        }
        transmit_protocol_frame((uint8_t *)&xPlay, &((L0_cmd_playRGBbr_Typedef *)0)->dev[slave.num], &parse.tx_framebuf); // ͨ��������Э�鷢��
    }
}

/*
 * @Description: ������������б��ڵ�����
 * @param:
 * @param:
 * @return:
 */
void permute_list_in_random(uint8_t *list, uint8_t size)
{
    uint8_t data;
    uint8_t i, j;
    uint8_t random;
    for (j = 0; j < size; j++)
    {
        for (i = 0; i < size; i++)
        {
            random = get_random_number() % size; // �������������
            data = list[random];
            list[random] = list[i];
            list[i] = data;
        }
    }
}

/* 
 * @Description: ��ĳ�����б���Ų����һ��
 * @param: 
 * @param: 
 * @param: 
 * @return: 
*/ 
uint8_t move_data_to_first_in_list(uint8_t data,uint8_t *list, uint8_t listsize)
{
    uint8_t i, j;
    uint8_t templist[PlayList_efMaxNum];
    for (i = 0; i < listsize; i++)
    {
        if (list[i] == data)
        {
            memcpy(&templist[0], &list[i], listsize - i); // ��������
            memcpy(&templist[listsize - i], &list[0], i); // ����ǰ��
            memcpy(list, &templist[0], listsize);         // ����ԭ��
            return 1;
        }
    }
    return 0;
}

/*
 * @Description: ��ԭ���鵹������
 * @param:
 * @param:
 * @return:
 */
void invert_list(uint8_t *list, uint8_t size)
{
    uint8_t i;
    uint8_t temp;
    if (size < 2)
    {
        return;
    }
    for (i = 0; i < (size / 2); i++)
    {
        temp = list[i];
        list[i] = list[size - i - 1];
        list[size - i - 1] = temp;
    }
}

/* 
 * @Description: ��������˳��
 * @param: 
 * @return: 
*/ 
void adjust_play_list(void)
{
    move_data_to_first_in_list(play.detail.efindex, &play.detail.list, play.detail.listefsum); // �����б�
    play.detail.idex_inlist = 0;                                                              // ��ǰ��Ч����Ϊ�б��һ����Ч
}

/*
 * @Description: ��ʼ����һ���б�
 * @param:
 * @return:
 */
void start_play_list(uint8_t listindex)
{
    playdetail_TypeDef playdetail;
    printlog("start_play_list:%d\r",listindex);
    play.source = SOURCE_LIST;
    play.status = RUN;
    play.detail.listindex = listindex;
    get_playdetail(&playdetail, play.detail.listindex);
    memcpy(&play.detail.list, &playdetail.list, sizeof(play.detail.list));
    play.detail.duration.min_MS = playdetail.DurationTime.min_MS;
    play.detail.duration.sec_MS = playdetail.DurationTime.sec_MS;
    play.detail.listefsum = playdetail.num;
    if (play.playmode == PLAY_IN_RANDOM)
    {
        permute_list_in_random(&play.detail.list, play.detail.listefsum); // �����������
    }
    play.detail.idex_inlist = 0;                                     // �б��е�һ����Ч
    play.detail.efindex = play.detail.list[play.detail.idex_inlist]; // ȡ����Ч����
    switch_effect(play.detail.efindex);                              // �л���Ч
}

/* 
 * @Description: �����б���
 * @param: 
 * @return: 
*/
void end_play_list(void)
{
    playdetail_TypeDef playdetail;
    printlog("end_play_list:%d\r", play.detail.listindex);
    play.source = SOURCE_FREE; // �����б��ţ�תΪ���ɲ���
    
    /*
    play.status = RUN;         // ���ֵ�ǰ��Ч
    */
}


/* 
 * @Description: ���¼��ص�ǰ�����б�
 * @param: 
 * @return: 
*/ 
void reload_current_play_list(void)
{
    playlist_ranklist_TypeDef ranklist; // �б���Ϣ
    playdetail_TypeDef playdetail;
    uint8_t list_index;
    uint8_t ef_index;
    printlog("reload_current_play_list\r");
    if (play.source != SOURCE_LIST) 
    {
        return; // ��ǰ�����б���ģʽ������Ҫ������Ϣ
    }
    get_playlist_ranklist(&ranklist);
    if (ranklist.num)
    {
        list_index = search_dataindex_in_list(play.detail.listindex, ranklist.list, ranklist.num);
        if (list_index != 0xFF) // ��ǰ���ڲ��ŵ��б����
        {
            get_playdetail(&playdetail, play.detail.listindex); //
            //
            memcpy(&play.detail.list, &playdetail.list, sizeof(play.detail.list));
            play.detail.duration.min_MS = playdetail.DurationTime.min_MS;
            play.detail.duration.sec_MS = playdetail.DurationTime.sec_MS;
            play.detail.listefsum = playdetail.num;
            //
            ef_index = search_dataindex_in_list(play.detail.efindex, playdetail.list, playdetail.num);
            if (ef_index != 0xFF) // ��ǰ���ڲ��ŵĵ�Ч���б����
            {
                play.detail.idex_inlist = ef_index;                              // ���µ�ǰ��Ч���б��е���ţ�ָ�룩
                play.detail.efindex = play.detail.list[play.detail.idex_inlist]; // ȡ����Ч����
            }
            else // ��ǰ���ŵ�Ч�Ѵ��б���ɾ��
            {
                play.detail.idex_inlist = 0;                                     // ��ͷ����
                play.detail.efindex = play.detail.list[play.detail.idex_inlist]; // ȡ����Ч����
                switch_effect(play.detail.efindex);                              // �е��µ�Ч
            }
        }
        else // ��ǰ���ڲ��ŵ��б��Ѿ���ɾ��
        {
            end_play_list();    // �����б���
        }
    }
    else
    {
        end_play_list();    // �����б���
    }
}


