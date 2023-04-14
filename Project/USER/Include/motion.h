#ifndef _MOTION_H_
#define _MOTION_H_
#include "Function_Init.H"



#define base_frame 10

#define Motion_Static_framepara 0        /*��̬֡����*/
#define Motion_Breath_framepara 255      /*����֡����*/
#define Motion_Stream_framepara 255      /*����֡����*/
#define Motion_Reverberate_framepara 255 /*����֡����*/
#define Motion_Hopscotch_framepara 255   /*����֡����*/
#define Motion_Lightning_framepara 255   /*����֡����*/
#define Motion_Ignite_framepara 500      /*��ȼ֡����*/
#define Motion_Random_framepara 255      /*���֡����*/

void Effect_Init(void);   // ��Ч��ʼ��
void Fetch_EF_DATA(void); // ��ȡ��ǰ��Ч���������
void Frame_Reset(void);   // ֡���ȸ�λ

void Motion_Static_Init(void);
void Motion_Breath_Init(void);
void Motion_Stream_Init(void);
void Motion_Reverberate_Init(void);
void Motion_Hopscotch_Init(void);
void Motion_Lightning_Init(void);
void Motion_Ignite_Init(void);
void Motion_Random_Init(void);

void Motion_Output(void);
void Motion_Static(void);               /*��̬*/
void Motion_Breath(uint8_t speed);      /*����*/
void Motion_Stream(uint8_t speed);      /*����*/
void Motion_Reverberate(uint8_t speed); /*����*/
void Motion_Hopscotch(uint8_t speed);   /*����*/
void Motion_Lightning(uint8_t speed);   /*����*/
void Motion_Ignite(uint8_t speed);      /*��ȼ*/
void Motion_Random(uint8_t speed);      /*���*/

#endif
