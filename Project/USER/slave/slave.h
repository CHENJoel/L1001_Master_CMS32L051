#ifndef _SLAVE_H
#define _SLAVE_H
#include "Function_Init.H"

#define SLAVEDEVICE_NUM 32 // ���֧�ֵĴӻ��豸����

typedef enum
{
    TRIANGLE_L, // ����
    TRIANGLE_M, // ����
    TRIANGLE_S, // С��
    SQUARE,     // ����
} device_type_enum;

typedef struct
{
    uint8_t id;            // �ư�id
    device_type_enum type; // ��״
    uint16_t angle;        // �Ƕ�
    uint16_t cooed_x;      // x����
    uint16_t cooed_y;      // y����
} device_detail_TypeDef;   // �豸����

typedef struct
{
    uint8_t num;                    // �豸����
    device_detail_TypeDef data[SLAVEDEVICE_NUM]; // �豸����
} device_data_TypeDef;              // �豸��Ϣ

extern device_data_TypeDef slave;

typedef struct
{
    uint8_t brightness; // ����
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
} color_TypeDef;

typedef struct
{
    color_TypeDef color[SLAVEDEVICE_NUM];
} device_color_TypeDef;
extern device_color_TypeDef slavecolor;

typedef struct
{
    uint8_t control; //
} device_control_TypeDef; //
extern device_control_TypeDef slave_control;

/*��������ư���Ϣ*/
void generate_virtual_device(void);
/*�����豸��Ϣ*/
uint8_t refresh_device_data(device_detail_TypeDef *p);
/*�����豸��ɫ*/
uint8_t refresh_device_color(color_TypeDef *p, uint8_t id);

#endif
