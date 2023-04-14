/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-05-25 20:19:42
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-06-18 16:50:41
 * @FilePath: \A5441_Master_CMS32L051\Project\USER\Include\Com.h
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _COM_H_
#define _COM_H_
#include "Function_Init.H"

#define uchar unsigned char
#define uint  unsigned int

#define M_HeadCOM 0xAA
#define M_HeadCMD 0xAC
#define S_HeadCOM 0xBA

#define Public_Addr  0xFF    // �㲥��ַ
#define Master_Addr  0xF0    // ������ַ


/* *************** */
#define APP_PROTOCOL_HEADER 0xA5
// #define APP_PROTOCOL_HEADER 0x55

enum /*APP���·�ָ��*/
{
    CHECK_LIGHT_MESSAGE = 0x20, // ��ѯ������Ϣ
    SET_LIGHT_COORDINATE,       // ���õ�������
    CHECK_EFFECT_MESSAGE,       // ��ѯ��Ч��Ϣ
    SET_EFFECT_MESSAGE,         // ���õ�Ч��Ϣ
    SET_LIGHT_RIGHT_OWNER,      // ���ÿص�Ȩ��ӵ����
    SET_LIGHT_OUTPUT,           // ���õ��������ɫ
    CHECK_PLAYLIST,             // ��ѯ�����б�
    SET_PLAYLIST,               // ��ѯ�����б�
    CHECK_SCHEDULE,             // ��ѯʱ���
    SET_SCHEDULE,               // ����ʱ���
    CHECK_PLAYSTATE,            // ��ѯ����״̬
    SET_PLAYSTATE,              // ���ò�����Ϣ
};

enum /*MCU���ϱ�ָ��*/
{
    REPORT_LIGHT_MESSAGE = 0x80, // �ϱ�������Ϣ
    REPORT_EFFECT_MESSAGE,       // �ϱ���Ч��Ϣ
    REPORT_LIGHT_RIGHT_OWNER,    // �ϱ���ǰ�ص�Ȩ��ӵ����
    REPORT_PLAYLIST,             // �ϱ������б�
    REPORT_SCHEDULE,             // �ϱ�ʱ���
    REPORT_PLAYSTATE,            // �ϱ�����״̬
};

void Upload_LightMessage(void);                          // �ϴ�������Ϣ
void Download_LightCoord(uint8_t *sur, uint16_t len);    // ���ص���������Ϣ
void Upload_EffectMessage(uint8_t num);                  // �ϴ���Ч��Ϣ
void Download_EffectMessage(uint8_t *sur, uint16_t len); // ���ص�Ч��Ϣ
void Upload_PlayList(uint8_t num);                       // �ϴ������б�
void Download_PlayList(uint8_t *sur, uint16_t len);      // ���ز����б�
void Upload_Schedule(uint8_t num);                       // �ϴ���ʱ����
void Download_Schedule(uint8_t *sur, uint16_t len);      // ���ض�ʱ����
void Upload_PlayingState(void);                          // �ϱ�����״̬
void Download_PlayingState(uint8_t *sur, uint16_t len);  // ���ز�������
/***************************************************************************/

// // // // // typedef enum
// // // // // {
// // // // //     M_CMD_Handshake_Chief = 0xD0,    // ��ID����
// // // // //     M_CMD_Handshake_Minor = 0xD1,    // ��ID����
// // // // //     M_CMD_Handshake_Commu = 0xD2,    // ͨѶID����
// // // // //     M_CMD_Set_CommuID = 0xD3,        // ����ͨѶID (0x30~0x45)  ���Ƶ��� ʹ�ø�ID
// // // // //     M_CMD_Buffer_Clear = 0xD4,       // ��ջ���
// // // // //     M_CMD_MinorID_Refresh = 0xD5,    // ��IDǿ�Ƹ���
// // // // //     M_CMD_MinorID_AllRefresh = 0xD6, // ȫԱ��IDǿ�Ƹ���
// // // // //     M_CMD_Slave_DataReset = 0xD7,    // �ӻ��ָ���������
// // // // //     M_CMD_Check_Device_ID = 0xD8,    // ��ѯ���豸ID��Ϣ
// // // // //     M_CMD_Set_SeriesNum = 0xD9,      // ��������ID (0x00~0x15) ����˳�� �ο���ID
// // // // //     M_CMD_Set_LightID = 0xDA,        // ���õƹ�ID (0x00~0x15)  ͨ�õ�Ч ʹ�ø�ID
// // // // //     M_CMD_Check_Device_Data = 0xDB,  // ��ѯ�豸��Ϣ
// // // // //     M_CMD_Set_FixedID = 0xDC,        // ���ù̶�ID

// // // // // } MasterCommandType;

typedef enum
{
    M_CMD_Handshake_Chief = 0xD0,    // ��ID����
    M_CMD_Handshake_Minor = 0xD1,    // ��ID����
    M_CMD_Handshake_Commu = 0xD2,    // ͨѶID����
    M_CMD_Set_CommuID = 0xD3,        // ����ͨѶID (0x30~0x45)  ���Ƶ��� ʹ�ø�ID
    M_CMD_Buffer_Clear = 0xD4,       // ��ջ���
    M_CMD_MinorID_Refresh = 0xD5,    // ��IDǿ�Ƹ���C
    M_CMD_MinorID_AllRefresh = 0xD6, // ȫԱ��IDǿ�Ƹ���
    M_CMD_Slave_DataReset = 0xD7,    // �ӻ��ָ���������
    M_CMD_Check_Device_ID = 0xD8,    // ��ѯ���豸ID��Ϣ
    M_CMD_Set_SeriesNum = 0xD9,      // ��������ID (0x00~0x15) ����˳�� �ο���ID
    M_CMD_Set_LightID = 0xDA,        // ���õƹ�ID (0x00~0x15)  ͨ�õ�Ч ʹ�ø�ID
    M_CMD_Check_Device_Data = 0xDB,  // ��ѯ�豸��Ϣ
    M_CMD_Set_FixedID = 0xDC,        // ���ù̶�ID

    M_CMD_ASK_Device_ID_DATA = 0xDD, // ѯ���豸ID��Ϣ
    M_CMD_Unlock_Slave = 0xDE,       // �����豸ID��Ϣ������
    M_CMD_Lock_Slave = 0xDE,         // �����豸ID��Ϣ������
    M_CMD_Set_Device_ID_DATA = 0xDF, // �����豸ID��Ϣ
}
MasterCommandType;




typedef enum
{
    S_ChiefMinor_ID = 0xA0, // �ӻ�����ID
    S_Device_ID = 0xA1,     // �ӻ�ID��Ϣ
    S_Device_Data = 0xA2,   // �ӻ��豸��Ϣ
} SlaveCommandType;

typedef enum
{
    Package_Empty, // �����ݰ�
    Package_Wrong, // �������ݰ�
    Package_Right, // ��ȷ���ݰ�
}PackageType;

typedef enum
{
    Master = 0x10,  // ����
    Triangle_A1 = 0x80, // ����1
    Triangle_A2 = 0x81, // ����2
    Triangle_B1 = 0x90, // ����1
    Triangle_C1 = 0xA0, // С��1
    Triangle_C2 = 0xA1, // С��2
    Triangle_C3 = 0xA2, // С��3
    Triangle_C4 = 0xA3, // С��4
    Square = 0xB0, // ����3
} DeciceType;

#define Check_Device_Data(ChfID, MirID) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Check_Device_Data, ChfID, MirID, Random_Generate(), Random_Generate())
#define Check_Device_ID(ChfID, MirID) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Check_Device_ID, ChfID, MirID, Random_Generate(), Random_Generate())
#define Set_CommuID(ChfID, MirID, CommuID) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Set_CommuID, ChfID, MirID, CommuID, Random_Generate());
#define Set_SeriesNum(ChfID, MirID, SeriesNum) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Set_SeriesNum, ChfID, MirID, SeriesNum, Random_Generate())
#define Set_LightID(ChfID, MirID, LightID) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Set_LightID, ChfID, MirID, LightID, Random_Generate())






/**************************************** ��Э�� ****************************************/
/*


VCC     GND
3K      18K     3511 ����
3K      7.5K    2926 ����
7.5K    3K      1170 С��
18K     3K      585  ������


*/

#define TYPE_Triangle_L_REF 3511
#define TYPE_Triangle_M_REF 2926
#define TYPE_Triangle_S_REF 1170
#define TYPE_Square_REF 585

/* ��Χȡֵ��5% */
#define TYPE_Triangle_L_MAX 3689
#define TYPE_Triangle_L_MIN 3335
#define TYPE_Triangle_M_MAX 3072
#define TYPE_Triangle_M_MIN 2779
#define TYPE_Triangle_S_MAX 1229
#define TYPE_Triangle_S_MIN 1112
#define TYPE_Square_REF_MAX 614
#define TYPE_Square_REF_MIN 556

enum
{
    Triangle_L,         // ��������
    Triangle_M,         // ��������
    Triangle_S,         // С������
    Square_Nor,         // ������
    OTHER_SHAPE = 0xFF, // ������״
};

typedef enum
{
    M_CMD_Check_ID = 0xE0, // ��ѯID
    M_CMD_Refresh_ID,      // ǿ�Ƹ���ID
    M_CMD_Check_Coord,     // ��ѯ�ӻ�����
    M_CMD_Set_Coord,       // ���ôӻ�����
    M_CMD_Check_Angle,     // ��ѯ�ӻ��Ƕ�
    M_CMD_Set_Angle,       // ���ôӻ��Ƕ�
    M_CMD_ROM_PROTECT_ON,  // ���ӻ�д����
    M_CMD_ROM_PROTECT_OFF, // �شӻ�д����
    M_CMD_WRITE_ROM,       // д�ӻ��洢��
    M_CMD_READ_ROM,        // ���ӻ��洢��
    M_CMD_DATA_RESET,      // �ָ���������
} MasterCMDType;

typedef enum
{
    S_Return_ID = 0xB0, // ����ID ��Ϣ
    S_RETURN_Coord,     // ���شӻ�����
    S_RETURN_Angle,     // ���شӻ��Ƕ�
    S_RETURN_ROM_DATA,  // ����ROM����
} SlaveCMDType;

/*������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/
/* ����ָ��.��ѯ��ID */
#define DataTx_Master_Check_ID(id) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Check_ID, id, Random_Generate(), Random_Generate(), Random_Generate())
/* ����ָ��.Ҫ��ӻ�����ID */
#define DataTx_Refresh_ID() DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Refresh_ID, Random_Generate(), Random_Generate(), Random_Generate(), Random_Generate())

/* ����ָ��.��ѯ�˻����� */
#define DataTx_Master_Check_Coord(id) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Check_Coord, id, Random_Generate(), Random_Generate(), Random_Generate())
/* ����ָ��.���ô˻����� */
#define DataTx_Master_Set_Coord(id, x, y) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Set_Coord, id, x, y, Random_Generate())

/* ����ָ��.��ѯ�˻��Ƕ� */
#define DataTx_Master_Check_Angle(id) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Check_Angle, id, Random_Generate(), Random_Generate(), Random_Generate())
/* ����ָ��.���ô˻��Ƕ� */
#define DataTx_Master_Set_Angle(id, angle) DataPackage_TX(M_HeadCMD, Public_Addr, M_CMD_Set_Angle, id, angle, Random_Generate(), Random_Generate())

/* ����ָ��.���ӻ��洢д���� */
#define DataTx_Master_Protect_ON(id) DataPackage_TX(M_HeadCMD, id, M_CMD_ROM_PROTECT_ON, Random_Generate(), Random_Generate(), Random_Generate(), Random_Generate())
/* ����ָ��.�شӻ��洢д���� */
#define DataTx_Master_Protect_OFF(id) DataPackage_TX(M_HeadCMD, id, M_CMD_ROM_PROTECT_OFF, Random_Generate(), Random_Generate(), Random_Generate(), Random_Generate())

/* ����ָ��.д�ӻ��洢�� */
#define DataTx_Master_Write_ROM(id, addr_H, addr_L, data) DataPackage_TX(M_HeadCMD, id, M_CMD_WRITE_ROM, addr_H, addr_L, data, Random_Generate())
/* ����ָ��.���ӻ��洢�� */
#define DataTx_Master_Read_ROM(id, addr_H, addr_L) DataPackage_TX(M_HeadCMD, id, M_CMD_READ_ROM, addr_H, addr_L, Random_Generate(), Random_Generate())

/* ����ָ��.�ָ��������� */
#define DataTx_Master_ResetData(id) DataPackage_TX(M_HeadCMD, id, M_CMD_DATA_RESET, Random_Generate(), Random_Generate(), Random_Generate(), Random_Generate())

/*������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

/* �ӻ�����.���ر���ID */
#define DataTx_Slave_ID(id) DataPackage_TX(S_HeadCOM, S_Return_ID, id, Random_Generate(), Random_Generate(), Random_Generate(), Random_Generate())
/* �ӻ�����.���ر������� */
#define DataTx_Slave_Coord(id, x, y) DataPackage_TX(S_HeadCOM, S_RETURN_Coord, id, x, y, Random_Generate(), Random_Generate())
/* �ӻ�����.���ر����Ƕ� */
#define DataTx_Slave_Angle(id, angle) DataPackage_TX(S_HeadCOM, S_RETURN_Angle, id, angle, Random_Generate(), Random_Generate(), Random_Generate())
/* �ӻ�����.���ش洢������ */
#define DataTx_Slave_ROM_Data(id, addr_H, addr_L, data) DataPackage_TX(S_HeadCOM, S_RETURN_ROM_DATA, id, addr_H, addr_L, data, Random_Generate())

void Uart1_Byte_POP(FIFOTypeDef *StructDAT);

void Com_Init(void);
void Com_Handshake(void);
void DataPackage_TX(uchar dat1, uchar dat2, uchar dat3, uchar dat4, uchar dat5, uchar dat6, uchar dat7);
unsigned char DataPackage_Extract(FIFOTypeDef *StructDAT);                      // �ӻ�������ȡ�ӻ���������Ч���ݰ�
void Slave_Handshake(void);
void Slave_Allocate_ID(void);

void Poll_Device_ID(void);
void Poll_Device_Data(void);
void Post_Device_Commu_ID(void);
void Post_Device_Light_ID(void);
void Post_Device_Series_ID(void);
void Mark_Device_FixedID_Data(void);

void Get_Slave_ID(void);
void Get_Slave_Coord(void); /* ��ȡ���� */
void Set_Slave_Coord(void); /* �������� */
void Get_Slave_Angle(void); /* ��ȡ�Ƕ� */
void Set_Slave_Angle(void); /* ���ýǶ� */

void Slave_DataInit(void);

uint8_t CRC_Calculate(uint8_t *sur, uint8_t len);     // ����CRCУ��

void Upload_EffectMessage(uint8_t eType);             // �ϴ���Ч��Ϣ
void RAW_processing(uint8_t *sur, uint16_t len);      // ͸���ϱ�
void Upload_StateMessage(uint8_t cmd, uint8_t sta);   // �ϱ�״̬
void Protocol_RGBW_Output(uint8_t *sur, uint16_t len); // ���������������ɫ

void slave_data_debug(void); // �������ģ������

#endif
