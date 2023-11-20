#ifndef _A5441_MASTER_H_
#define _A5441_MASTER_H_

#include "Function_Init.H"






typedef struct
{
    uint8_t on_sta;
    uint8_t effect_num; // ��ǰ���ŵ��б��ţ�255����δִ���б���
    uint8_t playlist_num;
    uint8_t RESERVED[2];
} PlayingStateTypeDef;

extern PlayingStateTypeDef PlayingState;

enum
{
    STA_OFF = 0,
    STA_ON = 1,
};

typedef struct
{
    uint8_t Direction; //���� 1Ϊ�ӣ�0Ϊ��
    uint8_t Now;       //��ǰֵ
    uint8_t Target;    //Ŀ��ֵ
    uint8_t Set;       //�趨ֵ
} LightTypeDef;

// // typedef struct
// // {
// //     uint8_t POWER_SW;        // ����
// //     LightTypeDef Brightness; // ����
// // } SYS_TypeDef;
// // extern SYS_TypeDef SYS;

enum
{
    DYNAMIC_EFFECT, // ��̬
    STATIC_EFFECT,  // ��̬
    RHYTHM_EFFECT,  // �ɶ�
};

enum
{
    Light_Owner_MCU = 0, // MCU�ص�
    Light_Owner_APP = 1, // APP�ص�
};


typedef struct RunningMode
{
    uint8_t Now;
    uint8_t Sum;
} ModeTypeDef;

extern ModeTypeDef ModeArray[3];
extern uint8_t Mode_num;

typedef struct
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
} RGBW_Val;

typedef struct
{
    uint8_t X;
    uint8_t Y;
} Coord_TypeDef;
typedef struct
{
    uint8_t data1;
    // uint8_t data2;
}ContainerTypeDef;

typedef struct
{
    uint8_t ID;                 // id��ַ
    uint8_t DeviceType;         // �豸����
    uint8_t Lightnum;           // �ƹ����
    uint8_t Runingnum;          // ʵ�ʵƹ����б�ţ����ݵƹ��������
    RGBW_Val Color;             // ��ɫ
    Coord_TypeDef Coord;        // ����
    uint8_t Angle;              // �Ƕ� ֵ0~180
    ContainerTypeDef Container; // �������ݴ�ʹ��
} SlaveTypeDef;

typedef struct
{
    uint8_t Device_sum;         // �豸����
    uint8_t Light_sum;          // �ƹ����������ƹ���ţ�
    SlaveTypeDef SlaveData[32]; // �ӻ����ݰ�
} DeviceTypeDef;
extern DeviceTypeDef TangramDevice;

#define EffextImage_num ModeArray[Mode_num].Now // Ч�����

#define Slave_num 16
#define Slave_Data_num 10

extern uint8_t uart1_sendend_flag; // ����1���ͽ�����־
extern uint8_t Light_Owner; // 0��MCU�ص�    1��APP�ص�


extern const uint8_t IR_KeyTable[44];
extern uint8_t IR_KeyVal;
extern const uint8_t Numboard_KeyTable[10];
extern uint8_t FixedID_DeviceData[8][1];

extern uint8_t Uart1_rx_data; // ����1���յ�����

extern unsigned char Module_Num; // �����ӵĵư�ģ������

extern unsigned char Sequence_arr[16]; // ���ߵ���˳��
extern unsigned char Light_Sum;        // ���ߵ�������
extern unsigned char E_Type;           // ��Ч����
extern unsigned char E_Color;          // ��Ч��ɫ    ÿ����Ч���Ͷ�����һ���Ч��ɫ�������ڶ�ά������

extern unsigned char Device_Chief_ID; // ��ID
extern unsigned char Device_Minor_ID; // ��ID
extern unsigned char Device_Commu_ID; // ͨѶID
extern unsigned char Device_Type;     // �豸����

extern unsigned char Random_sys;  // ����ϵͳ�����
extern unsigned char Random_base; // ���������

extern unsigned char Slave_Array[1][Slave_Data_num]; // �ӻ��豸��Ϣ
extern unsigned char SlaveDevive_Num;    // ���ӻ����
extern unsigned char ModuleLight_Num; // �ƹ���������
extern unsigned char Module_Num;      // �����ӵĴӻ���������



void KeyS_On(void);
void Scene_MOD(void);
void Paring_Mod(uint8_t *keyval,uint8_t reset);
void NewParing_Mod(uint8_t *keyval,uint8_t reset);
// // // // void Frame_Working(void);

// // // // // // // // void Module_All_GradualChange(uint8_t modele_num);
// // // // // // void Module_SelfTest(void);

uint8_t MIC_Process(void);
// // void Runingnum_Bubble_Sort(void);

void Slave_SelfTest(void);

void DataUpdata_TO_APP(uint8_t *data_addr);

uint8_t KEY_AD_Test(void);
uint8_t Light_AD_Test(void);


uint32_t checksum_calculate(uint8_t *sur, uint32_t len); // ����У���

/*********/



#endif
