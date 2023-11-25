
#ifndef _PRINTLOG_H_
#define _PRINTLOG_H_
#include "Function_Init.H"
#include "comapp.h"
#include "L0_slave.h"
// #define printlog_enabled     // ʹ�ܴ�ӡlog
#define virtual_device  // ����ư���Ϣ



//����
#define vAssertCalled(char,int) printf("Error:%s,%d\r\n",char,int)

#ifdef printlog_enabled
    #define printlog(...) printf(__VA_ARGS__)
    #define printAssert() vAssertCalled(__FILE__,__LINE__)
    // #define printlog(str) printf(str)
    #define configASSERT(x) if((x)==0) vAssertCalled(__FILE__,__LINE__)
    #define printnumlog(num) printf("[num:%d]\r",num)
    // // #define configASSERT(x) vAssertCalled(__FILE__,__LINE__)
#else

    #define printlog(...)
    #define configASSERT(x)
    #define printAssert()
    #define printnumlog(num) printf("[num:%d]\r",num)
#endif

#define PRINT(window, fmt, args...) printlog("{"#window"}"fmt"\n", ##args)

// C����ʾ������
//         1.���ȶ���꺯���򻯺��ڹ�����ARMCC/ARMGCC/GCC����������
//             #define PRINT(window, fmt, args...) printf("{"#window"}"fmt"\n", ##args)
//         2.��Ҫ����ѹ�͵������ݽ��л�ͼ�������������ݷִ���ʾ�����������ã�
//             PRINT(plotter, "%d,%d", current, voltage);
//             PRINT(power, "the power is %d W", current * voltage);
//         3.ʵ����ʾЧ���������£�
//             {plotter}3,2
//             {power}the power is 6 W



/*��ӡhex*/
void printhex_my(uint8_t *sur, uint32_t len);
/*��ӡ�ַ���*/
void printstr_my(uint8_t *sur, uint32_t len);
/*��ӡ��̬Ч��*/
void print_flow(Flow_Enum num);
/*��ӡ�˶�����*/
void print_direction(Direction_Enum num);
/*��ӡ��Ч����*/
void print_effecttype(EffectType_Enum num);
/*��ӡ��Ч����*/
void print_attribute(Attribute_Enum num);
/*app��Ч����log*/
void print_com_effect_detial_log(com_effect_detial_TypeDef *p);
/*��Ч����log*/
void print_effect_detial(Efdetail_TypeDef *p,uint8_t efnum);
/*��ӡ��ȡ�洢���ĵ�Ч����*/
void print_get_ef_detial(uint8_t efnum);
/*��ӡ��Ч����*/
void print_effect_sketch(Efminidetail_TypeDef *p,uint8_t efnum);
/*��ӡ��ȡ�Զ����Ч�б�*/
void print_get_original_ef_ranklist(void);
/*��ӡ��ȡȫ����Ч�б�*/
void print_get_all_ef_ranklist(void);
/*��ӡ��ȡ�ղص�Ч�б�*/
void print_get_favorites_ef_ranklist(void);
/*��ӡ��ȡ�����б�*/
void print_get_playlist_ranklist(void);
/*��ӡ��Ч�б�*/
void print_ef_ranklist(ef_ranklist_TypeDef* p);
/*��ӡ�����б��˳���*/
void print_playlist_ranklist(playlist_ranklist_TypeDef* p);
/*��ӡͨ�Ų����б��˳���*/
void print_com_playlist_ranklist(com_playlist_TypeDef* p);
/*��ӡ��������*/
void print_playdetial(playdetail_TypeDef *p, uint8_t playnum);
/*��ӡapp�·���������*/
void print_com_playdetial(com_play_detial_TypeDef *p);
/*��ӡ������ʷ*/
void print_play_history(void);
/*��ӡ����״̬*/
void print_playstatus(void);
/*��ӡ�ӻ��豸��Ϣ*/
void print_slave_data(void);
/*��ӡ�ӻ��豸����ɫ*/
void print_slave_color(void);

/*��ӡ����*/
void print_name(name_TypeDef*p);
//
void print_clock_detial(clock_detail_TypeDef *p); // ��ӡ��ʱ������
void print_all_clock_detail(void);                // ��ӡȫ����ʱ������
//
/*��ӡ���ߴӻ���Ϣ*/
void print_online_slave_data(void);
/*���е�Ч����log*/
void print_play_effect_detial(void);

/*app���Ƶư��log*/
void print_device_control(app_device_control_Typedef *x);
//

void print_local_rtc_time(void); // ��ӡ����rtcʱ��
//

void print_mini_device_data(mini_device_data_TypeDef *dev); // ��ӡ�豸������Ϣ
//
void print_xPlay_color(L0_cmd_playCOLOR_Typedef *xPlay,uint8_t num);    // ��ӡ��ɫ���

#endif
