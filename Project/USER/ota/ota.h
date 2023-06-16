#ifndef _OTA_H
#define _OTA_H
/*
ʵ��
���ƶ�������70��
У��45��
����20��



*/



/*


*/


#define BOOTLOADER_BASIC_ADDR 0     // bootoader����ַ
#define BOOTLOADER_SIZE 0x5000      // 20k

// #define APP_SIZE 0x97F0             // 38k
#define CHECKSUM_OFFSET_ADDR 0x9FF0 // APP��16�ֽ���ΪУ��ʹ����
#define MCU_SECTOR_SIZE 512         // ������С

#define USER_DATA_BASIC_ADDR 0xE800 // �û����ݴ洢��
#define USER_DATA_SIZE 0x1800       // �û����ݴ洢����С

#define OTA_PACK_SIZE 0x9800
#define PACK_CHECKSUM_ADDR 0x97F0

#define FLASH_OTA_PACK_BASE_ADDR 0x00
#define FLASH_SECTOR_SIZE 4096

void Print_Flash(uint8_t *pbuffer);                            // ��ӡ����
void Download_app(uint32_t offset, uint8_t *pbuffer);          // APP����
void CheckSum_calculate(uint32_t *checkVal, uint8_t *pbuffer); // У��ͼ���
uint8_t Download_checksum_verify(uint32_t checkVal);           // ���ذ�У��
void OTA_SetFlag(uint32_t checksum);                           // ����OTA������־��������������׼����
void OTA_ResetFlag(void);                                      // �������������־λ
uint8_t Find_OTA_flag(void);                                   // ����Ƿ�������������־
uint8_t APP_checksum_verify(void);                             // ������У��
void APP_update_check(void);                                   // �������
void ResetReg(void);                                           // �Ĵ�����λ
void JumpToApp(void);                                          // ������ת
/*******************************/





#endif
