#ifndef __L0_H_
#define __L0_H_
// #include "Function_Init.H"
#include "stdint.h"
#define MAX_SLAVE_NUM 32   // ���ӻ�����
#define MAX_PACKET_SIZE 512 // ���ݰ����ֵ
#define L0_DATAHEAD_SIZE (sizeof(L0_head_Typedef) + sizeof(L0_info_Typedef))   // ͨ������֡ͷ�ߴ�


/*
<��ʽ>
�հ���ַ+ָ��+��������+���ݶ�

*/

typedef enum/*�豸��ַ*/
{
    ADDR_MASTER = 0x00, // ������ַ
                        // 1~254 Ϊ�ӻ���ַ��
    ADDR_PUBLIC = 0xFF, // �㲥��ַ
} DEV_ADDR_ENUM;

typedef enum /*ָ������*/
{
    /*------------------------------------------------------------------------------------------*/
    CMD_MASTER_ORIGIN = 0x10,

    /*------------------------------------------------------------------------------------------*/
    CMD_SLAVE_ORIGIN = 0x70,
    CMD_SLAVE_PLAY_RGB,        // ���ŵƹ� ��RGBbr����ʽ
    CMD_SLAVE_PLAY_RGBW,       // ���ŵƹ� ��RGBWbr����ʽ
    CMD_SLAVE_PLAY_PWM,        // ���ŵƹ� ��PWM����ʽ
    CMD_SLAVE_CONNECT_COID,    // ����ͨ��ID
    CMD_SLAVE_REFRESH_COID,    // ����ͨ��ID
    CMD_SLAVE_RESET_COID,      // �ָ�ͨ��ID
    CMD_SLAVE_SET_COID,        // ����ͨ��ID
    CMD_SLAVE_GET_ID,          // ��ȡ�豸ID
    CMD_SLAVE_GET_SHAPE,       // ��ȡ�豸��״
    CMD_SLAVE_GET_CALIBRATION, // ��ȡУ׼����
    CMD_SLAVE_SET_CALIBRATION, // ����У׼����
    CMD_SLAVE_GET_PRE_CALIBRA, // ��ȡԤ��У׼���� ����
    CMD_SLAVE_SET_PRE_CALIBRA, // ����Ԥ��У׼���� ����
    CMD_SLAVE_PLAY_COLOR,      // ���ŵƹ� ��COLOR����ʽ
    /*------------------------------------------------------------------------------------------*/
    CMD_BOOT_ORIGIN = 0xD0,
    CMD_BOOT_GET_ROM,          // ��ȡROM����
    CMD_BOOT_GET_ROMSUM,       // ��ȡROMУ���
    CMD_BOOT_ERASE_APP,        // ����ȫ��APP����.��IAPģʽ����Ч
    CMD_BOOT_REASE_ROM,        // ����ָ��ROM����.��IAPģʽ����Ч
    CMD_BOOT_WRITE_ROM,        // ֱ��д��ROM����
    CMD_BOOT_INSER_ROM,        // ���ݲ���ROM����
    CMD_BOOT_GET_UID,          // ��ȡUID
    CMD_BOOT_GET_BOOT_VERSION, // ��ȡ��������汾
    CMD_BOOT_GET_APP_VERSION,  // ��ȡӦ�ó���汾
    CMD_BOOT_GOTO_IAP,         // ����IAPģʽ
    CMD_BOOT_CONNECT,          // ��������
    CMD_BOOT_DISCONNECT,       // �Ͽ�����
    CMD_BOOT_GOTO_APP,         // ��ת��APP
    CMD_BOOT_NVIC_RESET,       // �����λ
    CMD_BOOT_RESET_DATA,       // �ָ�����
    /*------------------------------------------------------------------------------------------*/
    CMD_GENERAL_ORIGIN = 0xF0,
    CMD_GENERAL_POWERTIME, // ��ȡ��������
    /*------------------------------------------------------------------------------------------*/
} CMD_ENUM;
typedef enum /*��������*/
{
    MES_ASK, // ��������
    MES_ACK, // Ӧ������
} MES_TYPE_ENUM;

#pragma pack(push, 1)
typedef struct
{
    DEV_ADDR_ENUM dev_adr; // �豸��ַ 8λ
    CMD_ENUM cmd;          // ָ������ 8λ
    MES_TYPE_ENUM type;    // �������� 8λ
} L0_head_Typedef;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    uint32_t addr; // ��ַ
    uint16_t size; // �ߴ�
} L0_info_Typedef;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    L0_head_Typedef head;          // ͨ������ͷ
    L0_info_Typedef info;          // ��������Ϣ��ȱʡ��0
    uint8_t data[MAX_PACKET_SIZE]; // ��������
} large_package_Typedef;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    L0_head_Typedef head; // ͨ������ͷ
    L0_info_Typedef info; // ��������Ϣ��ȱʡ��0
    uint8_t data[4];      // ��������
} small_package_Typedef;
#pragma pack(pop)



#include "boot.h"
/**************************************************************************************************/



/*
 * @Description: �ײ�ָ�����
 * @param: ���ݰ�Դָ��
 * @param: ���ݰ�����
 * @return: ��
*/
void boot_command_parse(uint8_t * p, uint16_t len);

/*
 * @Description: ����16λ����
 * @param:Դ����ָ��
 * @return:16λ����
*/
uint16_t read_16bit_data(uint8_t *sur);

/*
 * @Description: ����32λ����
 * @param:Դ����ָ��
 * @return:32λ����
*/
uint32_t read_32bit_data(uint8_t *sur);

/*
 * @Description: �ڵ�ַд��16λ����
 * @param:Դ����ָ��
 * @return:16λ����
 */
void write_16bit_data(uint8_t *tar, uint16_t data);

/*
 * @Description: �ڵ�ַд��32λ����
 * @param:Դ����ָ��
 * @return:32λ����
 */
void write_32bit_data(uint8_t *tar, uint32_t data);
#endif
