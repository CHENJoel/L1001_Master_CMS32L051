/* File Info
 * Author:      your name
 * CreateTime:  2023/8/5 16:08:53
 * LastEditor:  your name
 * ModifyTime:  2023/8/14 11:12:50
 * Description:
*/
#include "boot.h"
#include "Function_Init.H"


/*
 * @Description: 获取ROM数据
 * @param: 源数据指针
 * @param: 数据长度
 * @return: 无
*/
void function_GET_ROM(uint8_t *p, uint16_t len)
{
    uint32_t addr;
    uint16_t size;
    large_package_Typedef pack;
    if (((large_package_Typedef *)p)->head.type == MES_ASK) // 发出请求
    {
        addr = read_32bit_data((uint8_t *)&((large_package_Typedef *)p)->info.addr);
        size = read_16bit_data((uint8_t *)&((large_package_Typedef *)p)->info.size);
        if (size <= MAX_PACKET_SIZE)
        {
            pack.head.dev_adr = ADDR_PUBLIC; // 广播回复
            pack.head.cmd = CMD_BOOT_GET_ROM;
            pack.head.type = MES_ACK; // 应答请求
            write_32bit_data(&pack.info.addr, addr);
            write_16bit_data(&pack.info.size, size);
            my_memcpy(&pack.data, (uint8_t *)addr, size);
            transmit_protocol_frame(&pack, L0_DATAHEAD_SIZE + size, parse.tx_framebuf);
        }
    }
}

/*
 * @Description: 获取ROM校验和
 * @param:
 * @param:
 * @return:
*/
void function_GET_ROMSUM(uint8_t *p, uint16_t len)
{
    uint32_t addr;
    uint16_t size;
    small_package_Typedef pack;
    uint32_t sum;
    if (((small_package_Typedef *)p)->head.type == MES_ASK) // 发出请求
    {
        addr = read_32bit_data((uint8_t *)&((large_package_Typedef *)p)->info.addr);
        size = read_16bit_data((uint8_t *)&((large_package_Typedef *)p)->info.size);
        if (size <= 0xFFFF)
        {
            pack.head.dev_adr = ADDR_PUBLIC; // 广播回复
            pack.head.cmd = CMD_BOOT_GET_ROMSUM;
            pack.head.type = MES_ACK; // 应答请求
            write_32bit_data(&pack.info.addr, addr);
            write_16bit_data(&pack.info.size, size);
            sum = get_data_checksum((uint8_t *)addr, size);
            write_32bit_data((uint8_t *)&pack.data, sum);
            transmit_protocol_frame(&pack, sizeof(pack), parse.tx_framebuf);
        }
    }
}

/*
 * @Description: 擦除全部APP区域.仅IAP模式下有效
 * @param:
 * @param:
 * @return:
*/
void function_ERASE_APP(uint8_t *p, uint16_t len)
{
    // small_package_Typedef pack;
    // if (gdata.iap_status == IAP_STA && gdata.connect_status == CONNECT_STA) // 当前在IAP模式下且已建立连接
    // {
    //     if (((large_package_Typedef *)p)->head.type == MES_ASK) // 发出请求
    //     {
    //         if (len == (L0_DATAHEAD_SIZE + 0)) // 校验数据长度是否符合协议要求
    //         {
    //             // iap_flash_erase(APP_BASIC_ADDR, FIRMWARE_SIZE);
    //             /*
    //             pack.head.dev_adr = ADDR_PUBLIC; // 广播回复
    //             pack.head.cmd = CMD_BOOT_ERASE_APP;
    //             pack.head.type = MES_ACK; // 应答请求
    //             write_32bit_data(&pack.info.addr, APP_BASIC_ADDR);
    //             write_16bit_data(&pack.info.size, FIRMWARE_SIZE);
    //             write_32bit_data((uint8_t *)&pack.data, 0);
    //             transmit_protocol_frame(&pack, sizeof(pack), parse.tx_framebuf);
    //             */
    //         }
    //     }
    // }
}

/*
 * @Description: 擦除指定ROM区域.仅IAP模式下有效
 * @param:
 * @param:
 * @return:
*/
void function_REASE_ROM(uint8_t *p, uint16_t len)
{
    // // uint32_t addr;
    // // uint16_t size;
    // // small_package_Typedef pack;
    // // if (gdata.iap_status == IAP_STA && gdata.connect_status == CONNECT_STA) // 当前在IAP模式下且已建立连接
    // // {
    // //     if (((large_package_Typedef *)p)->head.type == MES_ASK) // 发出请求
    // //     {
    // //         if (len == (L0_DATAHEAD_SIZE + 0)) // 校验数据长度是否符合协议要求
    // //         {
    // //             addr = read_32bit_data((uint8_t *)&((large_package_Typedef *)p)->info.addr);
    // //             size = read_16bit_data((uint8_t *)&((large_package_Typedef *)p)->info.size);
    // //             iap_flash_erase(addr, size);
    // //             /*
    // //             pack.head.dev_adr = ADDR_PUBLIC; // 广播回复
    // //             pack.head.cmd = CMD_BOOT_REASE_ROM;
    // //             pack.head.type = MES_ACK; // 应答请求
    // //             write_32bit_data(&pack.info.addr, addr);
    // //             write_16bit_data(&pack.info.size, size);
    // //             write_32bit_data((uint8_t *)&pack.data, 0);
    // //             transmit_protocol_frame(&pack, sizeof(pack), parse.tx_framebuf);
    // //             */
    // //         }
    // //     }
    // // }
}

/*
 * @Description: 直接写入ROM区域
 * @param:
 * @param:
 * @return:
*/
void function_WRITE_ROM(uint8_t *p, uint16_t len)
{
    // uint32_t addr;
    // uint16_t size;
    // uint8_t *sur;
    // small_package_Typedef pack;
    // if (gdata.iap_status == IAP_STA && gdata.connect_status == CONNECT_STA) // 当前在IAP模式下且已建立连接
    // {
    //     if (((large_package_Typedef *)p)->head.type == MES_ASK) // 发出请求
    //     {
    //         addr = read_32bit_data((uint8_t *)&((large_package_Typedef *)p)->info.addr);
    //         size = read_16bit_data((uint8_t *)&((large_package_Typedef *)p)->info.size);
    //         if (len == (L0_DATAHEAD_SIZE + size)) // 校验数据长度是否符合协议要求
    //         {
    //             sur = (uint8_t *)&((large_package_Typedef *)p)->data;
    //             iap_flash_program(addr, size, sur);
    //             /*
    //             pack.head.dev_adr = ADDR_PUBLIC; // 广播回复
    //             pack.head.cmd = CMD_BOOT_WRITE_ROM;
    //             pack.head.type = MES_ACK; // 应答请求
    //             write_32bit_data(&pack.info.addr, addr);
    //             write_16bit_data(&pack.info.size, size);
    //             write_32bit_data((uint8_t *)&pack.data, 0);
    //             transmit_protocol_frame(&pack, sizeof(pack), parse.tx_framebuf);
    //             */
    //         }
    //     }
    // }
}

/*
 * @Description: 数据插入ROM区域
 * @param:
 * @param:
 * @return:
*/
void function_INSER_ROM(uint8_t *p, uint16_t len)
{
    // uint32_t addr;
    // uint16_t size;
    // uint8_t *sur;
    // small_package_Typedef pack;
    // if (gdata.iap_status == IAP_STA && gdata.connect_status == CONNECT_STA) // 当前在IAP模式下且已建立连接
    // {
    //     if (((large_package_Typedef *)p)->head.type == MES_ASK) // 发出请求
    //     {
    //         addr = read_32bit_data((uint8_t *)&((large_package_Typedef *)p)->info.addr);
    //         size = read_16bit_data((uint8_t *)&((large_package_Typedef *)p)->info.size);
    //         if (len == (L0_DATAHEAD_SIZE + size)) // 校验数据长度是否符合协议要求
    //         {
    //             sur = (uint8_t *)&((large_package_Typedef *)p)->data;
    //             iap_flash_insert(addr, size, sur);
    //             /*
    //             pack.head.dev_adr = ADDR_PUBLIC; // 广播回复
    //             pack.head.cmd = CMD_BOOT_INSER_ROM;
    //             pack.head.type = MES_ACK; // 应答请求
    //             write_32bit_data(&pack.info.addr, addr);
    //             write_16bit_data(&pack.info.size, size);
    //             write_32bit_data((uint8_t *)&pack.data, 0);
    //             transmit_protocol_frame(&pack, sizeof(pack), parse.tx_framebuf);
    //             */
    //         }
    //     }
    // }
}

/*
 * @Description: 获取UID
 * @param:
 * @param:
 * @return:
*/
void function_GET_UID(uint8_t *p, uint16_t len)
{
    large_package_Typedef pack;
    if (((large_package_Typedef *)p)->head.type == MES_ASK) // 发出请求
    {
        pack.head.dev_adr = ADDR_PUBLIC; // 广播回复
        pack.head.cmd = CMD_BOOT_GET_UID;
        pack.head.type = MES_ACK; // 应答请求
        write_32bit_data(&pack.info.addr, 0);
        write_16bit_data(&pack.info.size, 0);
        my_memcpy(&pack.data, UID, sizeof(UID_Type));
        transmit_protocol_frame(&pack, L0_DATAHEAD_SIZE + sizeof(UID_Type), parse.tx_framebuf);
    }
}

/*
 * @Description: 获取引导程序版本
 * @param:
 * @param:
 * @return:
*/
void function_GET_BOOT_VERSION(uint8_t *p, uint16_t len)
{
    large_package_Typedef pack;
    if (((large_package_Typedef *)p)->head.type == MES_ASK) // 发出请求
    {
        pack.head.dev_adr = ADDR_PUBLIC; // 广播回复
        pack.head.cmd = CMD_BOOT_GET_BOOT_VERSION;
        pack.head.type = MES_ACK; // 应答请求
        write_32bit_data(&pack.info.addr, 0);
        write_16bit_data(&pack.info.size, 0);
        my_memcpy(&pack.data,(uint8_t*)BOOT_INF_ADDR, sizeof(firmware_inf_TypeDef));
        transmit_protocol_frame(&pack, L0_DATAHEAD_SIZE + sizeof(firmware_inf_TypeDef), parse.tx_framebuf);
    }
}


/*
 * @Description: 获取应用程序版本
 * @param:
 * @param:
 * @return:
*/
void function_GET_APP_VERSION(uint8_t *p, uint16_t len)
{
    large_package_Typedef pack;
    if (((large_package_Typedef *)p)->head.type == MES_ASK) // 发出请求
    {
        pack.head.dev_adr = ADDR_PUBLIC; // 广播回复
        pack.head.cmd = CMD_BOOT_GET_APP_VERSION;
        pack.head.type = MES_ACK; // 应答请求
        write_32bit_data(&pack.info.addr, 0);
        write_16bit_data(&pack.info.size, 0);
        my_memcpy(&pack.data,(uint8_t*)APP_INF_ADDR, sizeof(firmware_inf_TypeDef));
        transmit_protocol_frame(&pack, L0_DATAHEAD_SIZE + sizeof(firmware_inf_TypeDef), parse.tx_framebuf);
    }
}

/*
 * @Description: 进入IAP模式
 * @param:
 * @param:
 * @return:
*/
void function_GOTO_IAP(uint8_t *p, uint16_t len)
{
    // small_package_Typedef pack;
    // gdata.iap_status = IAP_STA;
    // pack.head.dev_adr = ADDR_PUBLIC; // 广播回复
    // pack.head.cmd = CMD_BOOT_GOTO_IAP;
    // pack.head.type = MES_ACK; // 应答请求
    // /*
    //     write_32bit_data(&pack.info.addr, 0);
    //     write_16bit_data(&pack.info.size, 0);
    //     write_32bit_data((uint8_t *)&pack.data, gdata.iap_status);
    //     transmit_protocol_frame(&pack, sizeof(pack), parse.tx_framebuf);
    // */
}

/*
 * @Description: 建立连接
 * @param:
 * @param:
 * @return:
*/
void function_CONNECT(uint8_t *p, uint16_t len)
{
    // small_package_Typedef pack;
    // gdata.connect_status = CONNECT_STA;
    // pack.head.dev_adr = ADDR_PUBLIC; // 广播回复
    // pack.head.cmd = CMD_BOOT_CONNECT;
    // pack.head.type = MES_ACK; // 应答请求
    // write_32bit_data(&pack.info.addr, 0);
    // write_16bit_data(&pack.info.size, 0);
    // write_32bit_data((uint8_t *)&pack.data, gdata.connect_status);
    // transmit_protocol_frame(&pack, sizeof(pack), parse.tx_framebuf);
}

/*
 * @Description: 断开连接
 * @param:
 * @param:
 * @return:
*/
void function_DISCONNECT(uint8_t *p, uint16_t len)
{
    // small_package_Typedef pack;
    // gdata.connect_status = 0;
    // pack.head.dev_adr = ADDR_PUBLIC; // 广播回复
    // pack.head.cmd = CMD_BOOT_DISCONNECT;
    // pack.head.type = MES_ACK; // 应答请求
    // write_32bit_data(&pack.info.addr, 0);
    // write_16bit_data(&pack.info.size, 0);
    // write_32bit_data((uint8_t *)&pack.data, gdata.connect_status);
    // transmit_protocol_frame(&pack, sizeof(pack), parse.tx_framebuf);
}

/*
 * @Description: 跳转至APP
 * @param:
 * @param:
 * @return:
*/
void function_GOTO_APP(uint8_t *p, uint16_t len)
{
    // printlog("Go To APP\r");
    // GoToAPP();
}

/*
 * @Description: 软件复位
 * @param:
 * @param:
 * @return:
*/
void function_NVIC_RESET(uint8_t *p, uint16_t len)
{
    // printlog(" NVIC SystemReset\r");
    __NVIC_SystemReset();
}

/*
 * @Description: 恢复出厂
 * @param:
 * @param:
 * @return:
*/
void function_RESET_DATA(uint8_t *p, uint16_t len)
{
}
