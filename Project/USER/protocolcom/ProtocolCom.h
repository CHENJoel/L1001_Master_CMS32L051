#ifndef PROTOCOLCOM_H
#define PROTOCOLCOM_H


#define p_REG(reg) (uint32_t *)&reg, sizeof(reg)

#ifndef MARK1001
#define MARK1001 0x1001 // ������Чֵ(��ǼĴ����Ƿ���Ч����)
#endif
/*
    ͨѶ����
��������     ������λ���ʹӻ�������
�ӻ�����     ������λ��������������
��λ������   ���������ʹӻ�������
����������� ������λ��������
*/

/*****************************************************************************************************************************************/
/*                                                                      ͨѶ���
 */
#define Public_Addr 0xFF // �㲥��ַ

typedef enum
{
    PLAY_DATA = 0xA0, // ��������
} dataType;           // ��������

/***********************************************************************************/
// ����Э��
#pragma pack(push, 1)
typedef struct
{
    uint8_t addr; // ���յ�ַ
    uint8_t bri;  // ����
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
} playdata_Typedef;
typedef struct
{
    dataType type; // ��������
    uint8_t num;   // �������ݵĸ���
} packhead_Typedef;
typedef struct
{
    packhead_Typedef head;
    playdata_Typedef play[256];
} playpack_Typedef;
#pragma pack(pop)

/***********************************************************************************/
/*                                                 ͨѶ���ݰ�
 */
typedef enum /*֡ͷ����*/
{
    MPLAY_HEADER = 0xAA, // �������ݰ�����ͷ.������ɫ
    MCMD_HEADER = 0xBB,  // �������ݰ�����ͷ.ָ��
    SCMD_HEADER = 0xCC,  // �ӻ����ݰ�����ͷ.ָ��
    BCMD_HEADER = 0xDD,  // �����������ݰ�����ͷ.ָ��
    UPPER_HEADER = 0xEE, // ��λ�����ݰ�����ͷ
    FRAEME_TAIL = 0xAD,  // ֡β
} Comheadnum;

typedef enum /*ָ������*/
{
    CMD_READREG,   // �����ݼĴ��� /*���������ļĴ��� RAM��*/
    CMD_WRITEREG,  // д���ݼĴ��� /*���������ļĴ��� RAM��*/
    CMD_RETURNREG, // �������ݼĴ���

    CMD_READADDR,  // ����ַ���� /*������ַ�ϵ����� ROM��*/
    CMD_WRITEADDR, // д��ַ���� /*������ַ�ϵ����� ROM��*/
    CMD_RETURADDR, // ���ص�ַ����

    CMD_CONTROL, // ����ָ��
    CMD_CTRLACK, // Ӧ�����ָ��
} CmdTypenum;

typedef enum /*ͨѶ�Ĵ���-������*/
{
    /*��������Ĵ���-����*/
    BOOTLOAER_REG = 0X100,
    /*�ӻ��Ĵ���-����*/
    SLAVE_REG_ORIGIN = 0x200,
    REG_WERTE_PROTECT, // д�����Ĵ���
    REG_DEVICEID,      // �豸ID
    REG_COMMUNID,      // ͨѶID
    REG_STARTTIME,     // ��������
    REG_DEVICETYPE,    // �豸����
    /*�����Ĵ���-����*/
    MASTER_REG_ORIGIN = 0x300,
    /*ͨ�üĴ���-����*/
    GENERAL_REG_ORIGIN = 0x400,
    MAX_REGENUM = 0xFFFF, // 16λö��
} Regenum;

typedef enum /*ͨѶָ��-������*/
{
    /*��������ָ��-����*/
    BOOTLOAER_CMD_ORIGIN = 0x100,
    CMD_GOTO_APP,      // ��ת��APP
    CMD_FLASH_ERASE,   // ����FLASH
    CMD_FLASH_PROGRAM, // FLASH���
    CMD_FLASH_INSERT,  // FLASH��������
    CMD_FLASH_READ,    // ����FLASH
    CMD_FLASH_SUM,     // FLASH�ۼӺ�
    CMD_MCU_UID,       // UID
    CMD_BOOT_VERSION,  // ��������汾��Ϣ
    CMD_APP_VERSION,   // Ӧ�ó���汾��Ϣ
    /*�ӻ�ָ��-����*/
    SLAVE_CMD_ORIGIN = 0x200,
    CMD_CONNECT_COID,  // ����ͨ��ID
    CMD_REFRESH_COID,  // ����ͨ��ID
    CMD_RESETUSERDATA, // ���ݻָ�Ĭ��ֵ
    /*����ָ��-����*/
    MASTER_CMD_ORIGIN = 0x300,
    /*ͨ��ָ��-����*/
    GENERAL_CMD_ORIGIN = 0x400,
    CMD_RESET_DEVICE,     // ��λ�豸
    CMD_GOTO_IAPMODE,     // �����������״̬
    MAX_CMDENUM = 0xFFFF, // 16λö��
} Cmdenum;
/***********************************************************************************/
/*                                                 ͨѶ���ݰ� ��ʽ�ṹ��
 */
#pragma pack(push, 1)
typedef struct
{
    Comheadnum head; // Э��ͷ
    uint8_t addr;    // ���յ�ַ
    uint8_t bri;     // ����
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
    uint8_t sum;
} complay_Typedef; /*����.ͨѶ���ݸ�ʽ*/
#pragma pack(pop)
/********************************************************/
#pragma pack(push, 1)
typedef struct
{
    Comheadnum com_head;    // Э��ͷ
    uint8_t com_addr;       // ���յ�ַ
    CmdTypenum com_cmdType; // ָ������
    uint16_t com_regaddr;   // �Ĵ�����ַ/���� С��ģʽ
    uint16_t com_regval;    // �Ĵ���ֵ С��ģʽ
    uint8_t com_checksum;   // У���
} comRW_Typedef;            /*�Ĵ���/��ַ��д.ͨѶ���ݸ�ʽ*/
#pragma pack(pop)
/********************************************************/
#pragma pack(push, 1)
typedef struct
{
    Comheadnum com_head;    // Э��ͷ
    uint8_t com_addr;       // ���յ�ַ
    CmdTypenum com_cmdType; // ָ������
    Cmdenum com_cmd;        // ���� 2�ֽ�
    uint8_t com_val1;       // ֵ1/�����
    uint8_t com_val2;       // ֵ2/�����
    uint8_t com_checksum;   // У���
} comCmd_Typedef;           /*����ָ��.ͨѶ���ݸ�ʽ*/
#pragma pack(pop)
/********************************************************/

// // // // #pragma pack(push, 1)
// // // // typedef struct
// // // // {
// // // //     Comheadnum iap_head;    // Э��ͷ
// // // //     uint8_t iap_addr;       // ���յ�ַ
// // // //     CmdTypenum iap_cmdType; // ָ������-����ָ��
// // // //     Cmdenum iap_cmd;        // ���ָ��
// // // //     uint16_t packaddr;      // �̼�����ַ
// // // //     uint8_t packbuffer[512];      // �̼�
// // // //     uint8_t iap_checksum;   // У���
// // // //     Comheadnum iap_tail;    // ֡β
// // // // } iappack_Typedef;          /*���ݰ�.��ʽ*/
// // // // #pragma pack(pop)
/********************************************************/

/*Ӧ�𷵻ؼĴ���/��ַ��ֵ*/
void ACK_comRW(CmdTypenum CmdType, uint16_t cmd, uint16_t Val);
/*Ӧ�����ָ��*/
void ACK_comCmd(CmdTypenum CmdType, Cmdenum cmd, uint8_t Val1, uint8_t Val2);
/*ָ���*/
void Instruction_Process(void);
/*�Ĵ�����д*/
void CmdReg_RW(CmdTypenum CmdType, Regenum RegNum, uint32_t Val, uint32_t *pREG, uint8_t size);
/*ָ����ַ��д1�ֽ�*/
void CmdAdr_RW(CmdTypenum CmdType, uint32_t addr, uint32_t Val);
/*ָ�����*/
void Command_Analyse(CmdTypenum CmdType, uint16_t Reg, uint16_t Val);
/*����У���*/
uint16_t CheckSum_Calu(uint8_t *sur, uint16_t len);
/*****************************************************************************************************************************************/
/*








*/
typedef enum
{
    HANKSHAKE = 0xD0,     // ͨ������
    ERASEAPP,             // ����APP����
    APPDATA,              // APP����
    GOAPP,                // ��ת��APP
    REG_MAXADDR = 0xFFFF, // �Ĵ�������/��ַ Ϊ2�ֽ�
} RegisterType;

#endif
