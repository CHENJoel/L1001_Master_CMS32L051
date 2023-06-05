#include "Function_Init.H"
#include "memory.h"

// // // // Memory_TypeDef SysMemory;

void Clear_EF_data(uint8_t num) // ��Ч��Ϣ����
{
    EF_para_data_TypeDef EFpara; // ������Ϣ
    color_group_TypeDef EFcolor; // ɫ��
    id_group_TypeDef EFid;       // id��Ϣ
    memset(&EFid, 0, sizeof(EFid));
    memset(&EFpara, 0, sizeof(EFpara));
    memset(&EFcolor, 0, sizeof(EFcolor));
    Edit_UserEF_IDdata(num, &EFid);
    Edit_UserEF_Paradata(num, &EFpara);
    Edit_UserEF_Colordata(num, &EFcolor);
}
void Clear_Playlist(uint8_t num)
{
    playlist_TypeDef list;
    memset(&list, 0, sizeof(list)); // ��������
    Edit_Playlist(num, &list);
}

// У���Ч��Ϣ�Ƿ�������ֵ��
void Verify_EF_data(void)
{
    EF_para_data_TypeDef EFpara; // ������Ϣ
    color_group_TypeDef EFcolor; // ɫ��
    id_group_TypeDef EFid;       // id��Ϣ
    uint8_t i,flag;

    for (i = 0; i < USER_EF_SUM; i++)
    {
        Read_UserEF_Paradata(i, &EFpara);
        flag = 0;
        if (EFpara.color_sum > 15)
        {
            flag = 1;
            // // printf("color_sum: %d \r",EFpara.color_sum);
        }
        if (EFpara.motion > 7)
        {
            flag = 1;
            // // printf("motion: %d \r",EFpara.motion);
        }
        if (EFpara.move > 5)
        {
            flag = 1;
            // // printf("move: %d \r",EFpara.move);
        }
        if (EFpara.Mode > 1)
        {
            flag = 1;
            // // printf("Mode: %d \r",EFpara.Mode);
        }
        if (flag)
        {
            Clear_EF_data(i);
            printf("clear effect num: %d \r\n",i);
        }
        // // // Printf_EF_data(i);
    }
}
// У�鲥���б���Ϣ�Ƿ�������ֵ��
void Verify_PlayList_data(void)
{
    playlist_TypeDef list;
    uint8_t i, j, flag;

    for (i = 0; i < USER_LIST_SUM; i++)
    {
        Read_Playlist(i, &list);
        flag = 0;
        if (list.play_mode > 3)
        {
            flag = 1;
        }
        if (list.switch_min > 59)
        {
            flag = 1;
        }
        if (list.list_sum > USER_EF_MAXNUM)
        {
            flag = 1;
        }
        else
        {
            for (j = 0; j < list.list_sum; j++)
            {
                if (list.list_table[j] > USER_EF_MAXNUM)
                {
                    flag = 1;
                }
            }
        }
        if (flag)
        {
            Clear_Playlist(i);
            printf("clear playlist num: %d \r\n", i);
        }
        // // // Printf_Playlist_data(i);
    }
}

void Printf_EF_data(uint8_t num)
{
    EF_para_data_TypeDef EFpara; // ������Ϣ
    color_group_TypeDef EFcolor; // ɫ��
    id_group_TypeDef EFid;       // id��Ϣ
    uint8_t i,j;
    Read_UserEF_Paradata(num, &EFpara);
    Read_UserEF_Colordata(num, &EFcolor);
    Read_UserEF_IDdata(num, &EFid);

    printf("\reffect num: %d \r",num);
    printf("brightness: %d\r",EFpara.brightness);
    printf("color_sum: %d\r",EFpara.color_sum);
    printf("motion: %d\r",EFpara.motion);
    printf("move: %d\r",EFpara.move);
    printf("Mode: %d\r",EFpara.Mode);
    printf("speed: %d\r",EFpara.speed);
    printf("\r[ color table ]\r\r");
    for ( i = 0; i < 16; i++)
    {
        printf("%2x %2x %2x %2x \r", EFcolor.color[i].R, EFcolor.color[i].G, EFcolor.color[i].B, EFcolor.color[i].W);
    }
    printf("\r[ id table ]\r\r");
    j = 0;
    for (i = 0; i < 16; i++)
    {
        printf("%2x ", EFid.id_data[i]);
        if (++j > 3)
        {
            j = 0;
            printf("\r");
        }
    }
    printf("\r\r\r\r");
}

void Printf_Playlist_data(uint8_t num)
{
    playlist_TypeDef list;
    uint8_t i,j;
    Read_Playlist(num, &list);

    printf("\rplaylist num: %d \r",num);
    printf("play_mode: %d\r",list.play_mode);
    printf("switch_hour: %d\r",list.switch_hour);
    printf("switch_min: %d\r",list.switch_min);
    printf("list_sum: %d\r",list.list_sum);
    printf("\r[ list table ]\r\r");
    j = 0;
    for (i = 0; i < 60; i++)
    {
        printf("[%2x] ", list.list_table[i]);
        if (++j > 5)
        {
            j = 0;
            printf("\r");
        }
    }
    printf("\r\r\r\r");
}


void Printf_Schedule_data(uint8_t num)
{
    schedule_TypeDef p;
    Read_Schedule(num, &p);

    printf("\rSchedule num: %d \r",num);
    printf("Action: %d\r",p.Action);
    printf("Duration: %d\r",p.Duration);
    printf("Brightness: %d\r",p.Brightness);
    printf("Exection_Hou: %d\r",p.Exection_Hou);
    printf("Exection_Min: %d\r",p.Exection_Min);
    printf("Repeat_Week: %d\r",p.Repeat_Week);
    printf("\r\r\r\r");
}

/*
�༭ROM������
*/
void Edit_SectorData(uint32_t sect_addr, uint16_t offset, uint8_t *data_p, uint16_t len)
{
    uint16_t i;
    uint8_t *sur, *tar;
    uint8_t buffer[SECTOR_SIZE];
    sur = (uint8_t *)sect_addr;
    tar = (uint8_t *)&buffer;
    for (i = 0; i < SECTOR_SIZE; i++)
    {
        *tar++ = *sur++; // ��ԭ���ݰ�������
    }
    sur = data_p;
    tar = (uint8_t *)&buffer + offset;
    for (i = 0; i < len; i++)
    {
        *tar++ = *sur++; // ��������������
    }
    EraseSector(sect_addr);                                  // ��������
    ProgramPage(sect_addr, SECTOR_SIZE, (uint8_t *)&buffer); // д��������
}

/*
�༭�Զ����Ч����ɫ��
*/
void Edit_UserEF_Colordata(uint8_t num, color_group_TypeDef *colordata)
{
    uint32_t sector_addr;     // �洢������ַ
    uint16_t offset;          // ������ƫ�Ƶ�ַ
    if (num < 32 || num > 63) // 0~31 Ϊ���õ�Ч���,32~63 �Զ����Ч
    {
        return;
    }
    num -= 32;
    sector_addr = EF_COLOR_SECTOR0_ADDR + SECTOR_SIZE * (num / 8); // ÿ�������洢8����ɫ����
    offset = (num % 8) * sizeof(color_group_TypeDef);
    Edit_SectorData(sector_addr, offset, (uint8_t *)colordata, sizeof(color_group_TypeDef));
}
/*
����Ч����ɫ��
*/
void Read_UserEF_Colordata(uint8_t num, color_group_TypeDef *colordata)
{
    uint32_t sector_addr; // �洢������ַ
    uint16_t offset;      // ������ƫ�Ƶ�ַ
    // // // // // // uint16_t i;
    // // // // // // uint8_t *sur, *tar;
    if (num < 30) // 0~29 Ϊ���õ�Ч���,30~59 �Զ����Ч
    {
        memset(colordata, 0, sizeof(color_group_TypeDef)); // ��������
        memcpy(colordata, EF_DefaultData[num].color_array, EF_DefaultData[EF_Work.EF_ID].color_sum * 4);
    }
    else if (num < 60)
    {
        num -= 30;
        sector_addr = EF_COLOR_SECTOR0_ADDR + SECTOR_SIZE * (num / 8); // ÿ�������洢8����ɫ����
        offset = (num % 8) * sizeof(color_group_TypeDef);
        memcpy(colordata, sector_addr + offset, sizeof(color_group_TypeDef));
    }

    // // // sur = sector_addr + offset;
    // // // tar = colordata;
    // // // for (i = 0; i < sizeof(color_group_TypeDef); i++)
    // // // {
    // // //     *tar++ = *sur++;
    // // // }
}

/*
�༭�Զ��徲̬��Ч��id��Ϣ
*/
void Edit_UserEF_IDdata(uint8_t num, id_group_TypeDef *id_group)
{
    uint16_t offset;          // ������ƫ�Ƶ�ַ
    if (num < 32 || num > 63) // 0~31 Ϊ���õ�Ч���,32~63 �Զ����Ч
    {
        return;
    }
    num -= 32;
    offset = num * sizeof(id_group_TypeDef);
    Edit_SectorData(EF_IDDA_SECTOR_ADDR, offset, (uint8_t *)id_group, sizeof(id_group_TypeDef));
}
/*
���Զ��徲̬��Ч��id��Ϣ
*/
void Read_UserEF_IDdata(uint8_t num, id_group_TypeDef *id_group)
{
    uint32_t sector_addr; // �洢������ַ
    uint16_t offset;      // ������ƫ�Ƶ�ַ
    uint16_t i;
    uint8_t *sur, *tar;
    if (num < 32 || num > 63) // 0~31 Ϊ���õ�Ч���,32~63 �Զ����Ч
    {
        return;
    }
    num -= 32;

    sector_addr = EF_IDDA_SECTOR_ADDR;
    offset = num * sizeof(id_group_TypeDef);
    sur = sector_addr + offset;
    tar = id_group;
    for (i = 0; i < sizeof(id_group_TypeDef); i++)
    {
        *tar++ = *sur++;
    }
}
/*
�༭�Զ����Ч�Ĳ���
*/
void Edit_UserEF_Paradata(uint8_t num, EF_para_data_TypeDef *paradata)
{
    uint16_t offset; // ������ƫ�Ƶ�ַ
    if (num > 63)    // 0~31 Ϊ���õ�Ч���,32~63 �Զ����Ч
    {
        return;
    }
    offset = num * sizeof(EF_para_data_TypeDef);
    Edit_SectorData(EF_PARA_SECTOR_ADDR, offset, (uint8_t *)paradata, sizeof(EF_para_data_TypeDef));
}
/*
�����Զ����Ч�Ĳ���
*/
void Read_UserEF_Paradata(uint8_t num, EF_para_data_TypeDef *paradata)
{
    uint32_t sector_addr; // �洢������ַ
    uint16_t offset;      // ������ƫ�Ƶ�ַ
    uint16_t i;
    uint8_t *sur, *tar;
    if (num > 63)    // 0~31 Ϊ���õ�Ч���,32~63 �Զ����Ч
    {
        return;
    }
    sector_addr = EF_PARA_SECTOR_ADDR;
    offset = num * sizeof(EF_para_data_TypeDef);
    sur = sector_addr + offset;
    tar = paradata;
    for (i = 0; i < sizeof(EF_para_data_TypeDef); i++)
    {
        *tar++ = *sur++;
    }
}
void Edit_Playlist(uint8_t num, playlist_TypeDef *list_p)
{
    uint32_t sector_addr; // �洢������ַ
    uint16_t offset;      // ������ƫ�Ƶ�ַ
    uint8_t i;
    if (num > 19)
    {
        return;
    }
    if (list_p->list_sum > 59)
    {
        return;
    }
    if (list_p->switch_min > 59)
    {
        return;
    }
    for (i = 0; i < list_p->list_sum; i++)
    {
        if (list_p->list_table[i] > 59)
        {
            return;
        }
    }
    sector_addr = PLAYLIST_SECTOR0_ADDR + SECTOR_SIZE * (num / 8); // ÿ�������洢8���б�
    offset = (num % 8) * sizeof(playlist_TypeDef);
    Edit_SectorData(sector_addr, offset, (uint8_t *)list_p, sizeof(playlist_TypeDef));
}

void Read_Playlist(uint8_t num, playlist_TypeDef *list_p)
{
    uint32_t sector_addr; // �洢������ַ
    uint16_t offset;      // ������ƫ�Ƶ�ַ
    uint16_t i;
    uint8_t *sur, *tar;
    if (num > 19)
    {
        return;
    }
    sector_addr = PLAYLIST_SECTOR0_ADDR + SECTOR_SIZE * (num / 8); // ÿ�������洢8���б�
    offset = (num % 8) * sizeof(playlist_TypeDef);
    sur = sector_addr + offset;
    tar = list_p;
    for (i = 0; i < sizeof(color_group_TypeDef); i++)
    {
        *tar++ = *sur++;
    }
}

void Edit_Schedule(uint8_t num, schedule_TypeDef *p)
{
    uint32_t sector_addr; // �洢������ַ
    uint16_t offset;      // ������ƫ�Ƶ�ַ
    uint8_t i;

    if (num >= 64)
    {
        return;
    }
    if (p->Action > 4)
    {
        return;
    }
    if (p->Duration >= 60)
    {
        return;
    }
    if (p->Exection_Hou >= 24)
    {
        return;
    }
    if (p->Exection_Min >= 60)
    {
        return;
    }
    if (p->Repeat_Week > 7)
    {
        return;
    }
    sector_addr = SCHEDULE_SECTOR_ADDR;
    offset = num * sizeof(schedule_TypeDef);
    Edit_SectorData(sector_addr, offset, (uint8_t *)p, sizeof(schedule_TypeDef));
}
void Read_Schedule(uint8_t num, schedule_TypeDef *p)
{
    uint32_t sector_addr; // �洢������ַ
    uint16_t offset;      // ������ƫ�Ƶ�ַ
    uint16_t i;
    uint8_t *sur, *tar;
    if (num >= 64)
    {
        return;
    }
    sector_addr = SCHEDULE_SECTOR_ADDR;
    offset = num * sizeof(schedule_TypeDef);
    sur = sector_addr + offset;
    tar = p;
    for (i = 0; i < sizeof(schedule_TypeDef); i++)
    {
        *tar++ = *sur++;
    }
}

/*
��ʼ��ԭʼ����
*/
void Effect_DefaultParaData_Init(void)
{
    uint16_t i;
    uint8_t *sur, *tar;
    UserEFparadata_TypeDef UserDatabuffer; // ������
    sur = (uint8_t *)EF_PARA_SECTOR_ADDR;
    tar = (uint8_t *)&UserDatabuffer;
    for (i = 0; i < (uint16_t)sizeof(UserDatabuffer); i++)
    {
        *tar++ = *sur++; // ��ԭ���ݰ�������
    }
    for (i = 0; i < 30; i++) // ��Ĭ�����ݸ�����������
    {
        UserDatabuffer.User_EF_Param[i].brightness = 255;
        UserDatabuffer.User_EF_Param[i].color_sum = EF_DefaultData[i].color_sum;
        UserDatabuffer.User_EF_Param[i].motion = EF_DefaultData[i].motion_flag;
        UserDatabuffer.User_EF_Param[i].move = EF_DefaultData[i].move_flag;
        UserDatabuffer.User_EF_Param[i].Mode = EF_DefaultData[i].Mode;
        UserDatabuffer.User_EF_Param[i].speed = EF_DefaultData[i].Speed;
        UserDatabuffer.User_EF_Param[i].RESERVED[0] = 0;
        UserDatabuffer.User_EF_Param[i].RESERVED[1] = 0;
    }
    EraseSector(EF_PARA_SECTOR_ADDR);                                                     // ��������
    ProgramPage(EF_PARA_SECTOR_ADDR, sizeof(UserDatabuffer), (uint8_t *)&UserDatabuffer); // д��������
}

// // // // // // // // // // // // // // // // /*
// // // // // // // // // // // // // // // // ��ʼ��ԭʼ��ɫ���ݱ�
// // // // // // // // // // // // // // // // */
// // // // // // // // // // // // // // // // void Effect_DefaultColorData_Init(void)
// // // // // // // // // // // // // // // // {
// // // // // // // // // // // // // // // //     uint16_t i, j;
// // // // // // // // // // // // // // // //     color_group_TypeDef UserDatabuffer; // ��ɫ������
// // // // // // // // // // // // // // // //     for (i = 0; i < 30; i++)
// // // // // // // // // // // // // // // //     {
// // // // // // // // // // // // // // // //         memset(&UserDatabuffer, 0, sizeof(UserDatabuffer));
// // // // // // // // // // // // // // // //         memcpy(&UserDatabuffer, EF_DefaultData[i].color_array, EF_DefaultData[i].color_sum * 4);
// // // // // // // // // // // // // // // //         Edit_UserEF_Colordata(i, &UserDatabuffer);
// // // // // // // // // // // // // // // //     }
// // // // // // // // // // // // // // // // }

/*********************************************************************************/

// // // void MemoryStruct_Read(void)
// // // {
// // //     uint16_t i;
// // //     uint8_t *addr_ptr, *struct_ptr;
// // //     addr_ptr = (uint8_t *)0x500000;
// // //     struct_ptr = (uint8_t *)&SysMemory;
// // //     for (i = 0; i < sizeof(SysMemory); i++)
// // //     {
// // //         *struct_ptr = *addr_ptr;
// // //         struct_ptr++;
// // //         addr_ptr++;
// // //     }
// // //     // // // printf("Read...\r\n");
// // //     // // // // // // for (i = 0; i < 5; i++)
// // //     // // // // // // {
// // //     // // // // // //     SysMemory.ddfo[i] = 255 + temp++;
// // //     // // // // // //     printf("%d ", SysMemory.ddfo[i]);
// // //     // // // // // // }
// // // }

// // // void MemoryStruct_Write(void)
// // // {
// // //     EraseSector(0x500000);
// // //     ProgramPage(0x500000, sizeof(SysMemory), (uint8_t *)&SysMemory);
// // //     // // // printf("Write...\r\n");
// // // }

// // // void Memory_AutoUpdate(void)
// // // {
// // //     uint16_t i;
// // //     uint8_t *addr_ptr, *struct_ptr;
// // //     addr_ptr = (uint8_t *)0x500000;
// // //     struct_ptr = (uint8_t *)&SysMemory;
// // //     for (i = 0; i < sizeof(SysMemory); i++)
// // //     {
// // //         if (*struct_ptr != *addr_ptr) // RAM��ROM���ݲ�һ��ʱ��RAM����ROM
// // //         {
// // //             /*
// // //                 addr_ptr = (uint8_t *)0x500000;
// // //                 struct_ptr = (uint8_t *)&SysMemory;
// // //                 printf("\r\ndifferent...\r\n");
// // //                 for (i = 0; i < sizeof(SysMemory); i++)
// // //                 {
// // //                     printf("%d:  RAM:%d ROM:%d\r", i, *struct_ptr, *addr_ptr);
// // //                     struct_ptr++;
// // //                     addr_ptr++;
// // //                 }
// // //             */
// // //             MemoryStruct_Write();
// // //             return;
// // //         }
// // //         struct_ptr++;
// // //         addr_ptr++;
// // //     }
// // // }
