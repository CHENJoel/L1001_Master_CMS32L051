#ifndef _SLAVE_H
#define _SLAVE_H
#include "Function_Init.H"
#include "ProtocolCom.H"

#define SLAVEDEVICE_NUM 32 // ���֧�ֵĴӻ��豸����

extern uint8_t connect_id; // ��ǰ����ID

typedef enum
{
    ANSWER_EMPTY, // ��Ӧ��
    ANSWER_WRONG, // ����Ӧ��
    ANSWER_RIGHT, // ��ȷӦ��
} answer_status;  // Ӧ��״̬

typedef enum
{
    TRIANGLE_L,         // ��������
    TRIANGLE_M,         // ��������
    TRIANGLE_S,         // С������
    SQUARE,             // ������
    OTHER_SHAPE = 0xFF, // ������״
} device_shape_enum;


typedef struct
{
    uint8_t id;              // �ư�id
    device_shape_enum shape; // ��״
    uint16_t angle;          // �Ƕ�
    uint16_t cooed_x;        // x����
    uint16_t cooed_y;        // y����
    uint8_t runnum;          // ����˳���ţ��洢ֵ��ʵ�����ã�
} device_detail_TypeDef;     // �豸����

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
uint8_t refresh_slave_data(device_detail_TypeDef *p);
/*�����豸��ɫ*/
uint8_t refresh_device_color(color_TypeDef *p, uint8_t id);


/*************************************/

typedef enum
{
    PACK_EMPTY,   // �����ݰ�
    PACK_WRONG,   // �������ݰ�
    PACK_RIGHT,   // ��ȷ���ݰ�
} cmdpack_status; // ָ�����ݰ�״̬

/*���ڷ������ݴ�*/
void tx_uart_data(uint8_t *data, uint16_t len);
/*�������Ӵӻ��豸*/
void connect_slave_device(uint8_t id);
/*Ҫ��������дӻ���ͨѶid*/
void refresh_slave_comid(void);
/*����ӻ�����״��Ϣ*/
void ask_slave_shape(uint8_t id);
/*��fifo�������ӻ���Ӧ���ź�*/
cmdpack_status get_slave_ack_from_fifo(uint8_t *fifobuf, uint16_t bufsize, uint16_t *pr, uint16_t *pw, comCmd_Typedef *pack);
/*��ѯ�����ߵĴӻ��豸*/
void poll_slave_id(void);
/*��ȡ�ӻ�����״��Ϣ*/
void get_slave_shape(void);
/*��ȡ�ӻ�λ����Ϣ*/
void get_slave_place(void);
/*��ʼ�����ߵĴӻ���Ϣ*/
void slave_online_data_init(void);



/*���������ӻ�*/
void slave_light_in_turn(void);
/*
 * @Description: ����������һ����
 * @param:
 * @return:
*/
void light_up_only_one_slave(uint8_t id);

/********/

void slave_answer_parse(uint8_t *p, uint16_t len);//�ӻ�Ӧ�����


#endif
