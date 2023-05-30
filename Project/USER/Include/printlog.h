#ifndef _PRINTLOG_H_
#define _PRINTLOG_H_
#include "Function_Init.H"
#include "comapp.h"

#define printlog_enabled    // ʹ�ܴ�ӡlog

//����
#define vAssertCalled(char,int) printf("Error:%s,%d\r\n",char,int)


#ifdef printlog_enabled
    #define printlog(str) printf(str)
    #define configASSERT(x) if((x)==0) vAssertCalled(__FILE__,__LINE__)
#else
    #define printlog(str) ;
    #define configASSERT(x) ;
#endif





/*��ӡhex*/
void printhex_my(uint8_t *sur, uint8_t len);
/*��ӡ�ַ���*/
void printstr_my(uint8_t *sur, uint8_t len);
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
/*��ӡ��Ч�б�*/
void print_ef_ranklist(ef_ranklist_TypeDef* p);
#endif
