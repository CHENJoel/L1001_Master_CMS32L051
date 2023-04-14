#include "Function_Init.H"
#include "OTA.h"

void APP_FLASH_LOADDING(void)
{
    uint8_t flash_buffer[512];
    uint16_t i, j;
    uint32_t percentage;
    uint32_t addr;
    uint8_t *p;
    LED1_ON();
    LED2_OFF();
    printf(" \rLoading flash... \r\n");
    for (addr = 0; addr < OTA_PACK_SIZE; addr += MCU_SECTOR_SIZE)
    {
        FLASH_BufferRead(flash_buffer, FLASH_OTA_PACK_BASE_ADDR + addr, MCU_SECTOR_SIZE);
        EraseSector(APP_BASIC_ADDR + addr); // 擦除ROM页
        ProgramPage(APP_BASIC_ADDR + addr, MCU_SECTOR_SIZE, (uint8_t *)&flash_buffer);
        percentage = (addr * 100) / OTA_PACK_SIZE; // 进度百分比
        printf("\rLoading 0x%04x: %d%%\r", addr, percentage);
        LED2_REV();
        LED1_REV();
    }
    LED1_OFF();
    LED2_OFF();
    OTA_ResetFlag();
    printf("updata finish !\r\n");
    printf("please reset system\r\n");
}
/* 打印数据 */
void Print_Flash(uint8_t *pbuffer)
{
    uint8_t *addr_ptr;
    uint16_t i, j;
    j = 0;
    for (i = 0; i < 256; i++)
    {
        printf("%2x ", *addr_ptr);
        addr_ptr++;
        if (++j > 15)
        {
            j = 0;
            printf("\r");
        }
    }
}
/* APP下载 */
void Download_app(uint32_t offset, uint8_t *pbuffer)
{
    uint32_t addr;
    uint32_t percentage;
    addr = FLASH_OTA_PACK_BASE_ADDR + offset;
    if (addr % FLASH_SECTOR_SIZE == 0)
    {
        FLASH_SectorErase(addr);
        printf("SectorErase Ox%4x\r", addr);
    }
    FLASH_PageWrite(pbuffer, addr, 256);
    percentage = (offset * 100) / OTA_PACK_SIZE; // 进度百分比

    printf("download: Ox%4x [%d%%]\r", addr, percentage);
}
/* 校验和计算 */
void CheckSum_calculate(uint32_t *checkVal, uint8_t *pbuffer)
{
    uint16_t i;
    uint8_t *p;
    p = pbuffer;
    for (i = 0; i < 256; i++) // 单次计算256字节
    {
        *checkVal += *p;
        p++;
    }
}
/* 下载包校验 */
uint8_t Download_checksum_verify(uint32_t checkVal)
{
    uint8_t buff[16];
    uint8_t flashbuffer[16];
    uint32_t flash_verifydata; // flash 中的校验信息
    uint32_t flash_checksum;   // flash 数据的校验和
    uint32_t addr;
    uint8_t j;
    uint32_t percentage;
    printf("\r[ VERIFY DOWNLOADED CHECKSUM ]\r\n");
    flash_checksum = 0;
    for (addr = 0; addr < OTA_PACK_SIZE; addr += 16)
    {
        FLASH_BufferRead(flashbuffer, FLASH_OTA_PACK_BASE_ADDR + addr, 16); // 16字节读取 节省内存
        for (j = 0; j < 16; j++)
        {
            flash_checksum += flashbuffer[j];
        }
        percentage = (addr * 100) / OTA_PACK_SIZE; // 进度百分比
        printf("0x%04x: reading flash %d%%\r", addr, percentage);
    }

    printf("buffer checksum is 0x%4x\r", checkVal);         // 串口缓存的校验和
    printf("flash  checksum is 0x%4x\r\n", flash_checksum); // flash的校验和

    if (checkVal == flash_checksum)
    {
        printf("buffer and flash checksum verify pass !\r"); // 串口缓存的校验和与实际写进flash的数据校验和一致
    }
    else
    {
        printf("buffer and flash verify fail !!!\r\r"); // 校验不通过
        printf("download fail!!!\r\r");
        return 0;
    }
    FLASH_BufferRead(buff, PACK_CHECKSUM_ADDR, sizeof(buff)); // 读出flash中的校验数据
    flash_verifydata = 0;
    flash_verifydata |= buff[3];
    flash_verifydata <<= 8;
    flash_verifydata |= buff[2];
    flash_verifydata <<= 8;
    flash_verifydata |= buff[1];
    flash_verifydata <<= 8;
    flash_verifydata |= buff[0]; // 校验数据 小端模式

    flash_checksum -= buff[0];
    flash_checksum -= buff[1];
    flash_checksum -= buff[2];
    flash_checksum -= buff[3]; // 减去校验数据，还原APP数据的校验和

    printf("APP pack checksum is 0x%4x\r", flash_checksum);

    if (flash_checksum == flash_verifydata) // 校验数据包内是否为app数据
    {
        printf("App pack verify pass !");
        return 1;
    }
    else
    {
        printf("App pack verify fail!!!\r\r"); // 校验不通过
        return 0;
    }
}

/*设置OTA升级标志，代表升级包已准备好*/
void OTA_SetFlag(uint32_t checksum)
{
    ota_data_TypeDef ota_data;
    ota_data.ota_flag = OTA_FLAG;                            // 升级标志
    ota_data.ota_UID0_flag = UID->UID0;                      // UID0
    ota_data.pack_checksum = checksum;                       // 升级包校验和
    ota_data.ota_checksum = OTA_FLAG + UID->UID0 + checksum; // 前三者的校验和
    Edit_SectorData((uint32_t)UserData2_ADDR, &(((UserData_Sector2_TypeDef *)0)->data.ota_data), (uint8_t *)&ota_data, sizeof(ota_data));
}
/*升级结束后清标志位*/
void OTA_ResetFlag(void)
{
    ota_data_TypeDef ota_data;
    memset(&ota_data, 0, sizeof(ota_data)); // OTA标志区全部数据清零
    Edit_SectorData((uint32_t)UserData2_ADDR, &(((UserData_Sector2_TypeDef *)0)->data.ota_data), (uint8_t *)&ota_data, sizeof(ota_data));
    // // // printf("\rreset reload flag\r");
}
/*检查是否存在软件升级标志*/
uint8_t Find_OTA_flag(void)
{
    uint32_t checksum = 0;
    if ((UserData2->data.ota_data.ota_flag == OTA_FLAG) && (UserData2->data.ota_data.ota_UID0_flag == UID->UID0))
    {
        checksum += UserData2->data.ota_data.ota_flag;
        checksum += UserData2->data.ota_data.ota_UID0_flag;
        checksum += UserData2->data.ota_data.pack_checksum;
        if (checksum == UserData2->data.ota_data.ota_checksum)
        {
            return 1; // 校验数据通过
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

uint8_t APP_checksum_verify(void)
{
    uint8_t buff[16];
    uint8_t flashbuffer[16];
    uint32_t flash_verifydata; // flash 中的校验信息
    uint32_t flash_checksum;   // flash 数据的校验和
    uint32_t addr;
    uint8_t j;

    uint32_t percentage;

    printf("\r[ VERIFY PACK CHECKSUM ]\r\n");

    FLASH_BufferRead(buff, PACK_CHECKSUM_ADDR, sizeof(buff)); // 读出flash中的校验数据
    flash_verifydata = 0;
    flash_verifydata |= buff[3];
    flash_verifydata <<= 8;
    flash_verifydata |= buff[2];
    flash_verifydata <<= 8;
    flash_verifydata |= buff[1];
    flash_verifydata <<= 8;
    flash_verifydata |= buff[0]; // 校验数据 小端模式   还原app的校验和

    flash_verifydata += buff[0];
    flash_verifydata += buff[1];
    flash_verifydata += buff[2];
    flash_verifydata += buff[3]; // 计算出升级包的校验和

    if (UserData2->data.ota_data.pack_checksum == flash_verifydata) // 与升级标志处的校验信息进行校验
    {
        printf("OTA pack verify pass !\r");
    }
    else
    {
        printf("OTA pack verify fail !\r");
        return 0;
    }
    flash_checksum = 0;
    for (addr = 0; addr < OTA_PACK_SIZE; addr += 16)
    {
        FLASH_BufferRead(flashbuffer, FLASH_OTA_PACK_BASE_ADDR + addr, 16); // 16字节读取 节省内存
        for (j = 0; j < 16; j++)
        {
            flash_checksum += flashbuffer[j];
        }
        percentage = (addr * 100) / OTA_PACK_SIZE; // 进度百分比
        printf("0x%04x: reading flash %d%%\r", addr, percentage);
    }

    if (UserData2->data.ota_data.pack_checksum == flash_checksum) // 与升级标志处的校验信息进行校验
    {
        printf("OTA pack verify success !\r");
        return 1;
    }
    else
    {
        printf("OTA pack verify fail !\r");
        return 0;
    }
}
void APP_update_check(void) // 升级检查
{
    if (Find_OTA_flag())
    {
        printf("\rfound app update flag\r");
        if (APP_checksum_verify())
        {
            APP_FLASH_LOADDING();
            printf("\r\r\r\r loading app... \r\n");
            JumpToApp();
        }
        else
        {
            printf("\rapp checksum wrong\r");
            JumpToApp();
        }
    }
    else
    {
        JumpToApp(); // 未检测到升级任务
    }
}

/* 寄存器复位*/
void ResetReg(void)
{
    SCI0->ST0 = _0002_SCI_CH1_STOP_TRG_ON | _0001_SCI_CH0_STOP_TRG_ON;
    CGC->PER0 &= ~CGC_PER0_SCI0EN_Msk;
    INTC_DisableIRQ(SR0_IRQn);
}
/* 程序跳转 */
void JumpToApp(void)
{
    ResetReg();
    __set_MSP(*(__IO uint32_t *)APP_BASIC_ADDR);
    ((void (*)())(*(volatile unsigned long *)(APP_BASIC_ADDR + 0x04)))(); // to APP
}
