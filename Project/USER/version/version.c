#include "version.h"

volatile const firmware_inf_TypeDef firmware_inf __attribute__((at(APP_INF_ADDR))) =
{
    PRODUCT_MODEL,
    FIRMWARE_MASTER,
    MCU_VER,
    FIRMWARE_DATE,
};

void print_firmware_information(void)
{
    printlog("\r-----------------------------------\r");
    printlog("|firmware information|\r");
    printlog("MODEL:   ");
    printstr_my((uint8_t *)&firmware_inf.model, sizeof(firmware_inf.model));
    printlog("TYPE:    ");
    printstr_my((uint8_t *)&firmware_inf.type, sizeof(firmware_inf.type));
    printlog("VERSION: ");
    printstr_my((uint8_t *)&firmware_inf.version, sizeof(firmware_inf.version));
    printlog("DATE:    ");
    printstr_my((uint8_t *)&firmware_inf.date, sizeof(firmware_inf.date));
    printlog("-----------------------------------\r\n");
}
