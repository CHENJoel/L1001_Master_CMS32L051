#include "Function_Init.H"
#include "slave.h"

device_data_TypeDef slave;
device_color_TypeDef slavecolor;
device_control_TypeDef slave_control;

/*生成虚拟灯板信息*/
void generate_virtual_device(void)
{
    uint8_t temp[32];
    uint8_t i;
    memset(&slave, 0, sizeof(slave));
    slave.num=8;
    for ( i = 0; i < 32; i++)
    {
        temp[i] = (i + 1) * 10 + i + 1;
        // while (temp[i]==0||temp[i]==255)
        // {
        //     // temp[i] = Random_Generate();
        //     temp[i] = (i+1)*10+i+1;
        //     // printlog("%d Random_Generate %d\r",i,temp[i]);
        // }
    }
    slave.data[0].id = temp[0];
    slave.data[0].type = TRIANGLE_L;
    slave.data[0].angle = 0;
    slave.data[0].cooed_x = 0;
    slave.data[0].cooed_y = 0;
    /**************************/
    slave.data[1].id = temp[1];
    slave.data[1].type = TRIANGLE_L;
    slave.data[1].angle = 0;
    slave.data[1].cooed_x = 0;
    slave.data[1].cooed_y = 0;
    /**************************/
    slave.data[2].id = temp[2];
    slave.data[2].type = TRIANGLE_M;
    slave.data[2].angle = 0;
    slave.data[2].cooed_x = 0;
    slave.data[2].cooed_y = 0;
    /**************************/
    slave.data[3].id = temp[3];
    slave.data[3].type = TRIANGLE_S;
    slave.data[3].angle = 0;
    slave.data[3].cooed_x = 0;
    slave.data[3].cooed_y = 0;
    /**************************/
    slave.data[4].id = temp[4];
    slave.data[4].type = SQUARE;
    slave.data[4].angle = 0;
    slave.data[4].cooed_x = 0;
    slave.data[4].cooed_y = 0;
    /**************************/
    slave.data[5].id = temp[5];
    slave.data[5].type = TRIANGLE_S;
    slave.data[5].angle = 0;
    slave.data[5].cooed_x = 0;
    slave.data[5].cooed_y = 0;
    /**************************/
    slave.data[6].id = temp[6];
    slave.data[6].type = TRIANGLE_S;
    slave.data[6].angle = 0;
    slave.data[6].cooed_x = 0;
    slave.data[6].cooed_y = 0;
    /**************************/
    slave.data[7].id = temp[7];
    slave.data[7].type = TRIANGLE_S;
    slave.data[7].angle = 0;
    slave.data[7].cooed_x = 0;
    slave.data[7].cooed_y = 0;
    /**************************/
}

/*更新设备信息*/
uint8_t refresh_device_data(device_detail_TypeDef *p)
{
    uint8_t i;
    for (i = 0; i < SLAVEDEVICE_NUM; i++)
    {
        if (p->id == slave.data[i].id) // 轮询出需要被修改的设备id
        {
            slave.data[i].angle = p->angle;
            slave.data[i].cooed_x = p->cooed_x;
            slave.data[i].cooed_y = p->cooed_y;
            printlog("refresh device data :[%02x]\r", p->id);
            return 1;
        }
    }
    printlog("[error] This device id do not exist :[%02x]\r", p->id);
    printAssert();
    return 0;
}
/*更新设备颜色*/
uint8_t refresh_device_color(color_TypeDef *p, uint8_t id)
{
    uint8_t i;
    for (i = 0; i < SLAVEDEVICE_NUM; i++)
    {
        if (id == slave.data[i].id) // 轮询出需要被修改的设备id
        {
            slavecolor.color[i].brightness = p->brightness;
            slavecolor.color[i].R = p->R;
            slavecolor.color[i].G = p->G;
            slavecolor.color[i].B = p->B;
            slavecolor.color[i].W = p->W;
            printlog("refresh device color :[%02x]\r", id);
            return 1;
        }
    }
    printlog("[error] This device id do not exist :[%02x]\r", id);
    printAssert();
    return 0;
}
