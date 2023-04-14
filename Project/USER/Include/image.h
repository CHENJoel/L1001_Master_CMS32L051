/*
 * @Author: your name
 * @Date: 2022-03-25 13:48:26
 * @LastEditTime: 2022-06-14 15:08:46
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @Description: ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \A5441_CMS8S6990_Master\code\image.h
 */
#ifndef _IMAGE_H_
#define _IMAGE_H_
#include "Function_Init.H"
// #include "Color.H"
#define Red             {255,0,0,0}
#define LightRed        {255,50,0,0}
#define Orange          {255,100,0,0}
#define LightYellow     {255,170,0,0}
#define Yellow          {255,255,0,0}
#define LightGreen      {0 ,255,30,0}
#define Green           {0,255,0,0}
#define LightCyan       {0,255,80,0}
#define Cyan            {0,255,255,0}
#define LightBlue       {0,100,255,0}
#define Blue            {0,0,255,0}
#define Purple          {80,0,250,0}
#define LightPink       {255,0,255,0}
#define Pink            {255,0,100,0}

#define White           {0,0,0,255}
#define Black           {0,0,0,0}

// // // // #define Imgae_KF_Num       EffectData[E_Type][E_Color][0]  // �ؼ�֡������ ��1~255��
// // // // #define Frame_In_Num    EffectData[E_Type][E_Color][1]  // ��֡�����ؼ�֮֡�䣩
// // // // #define Frame_time          EffectData[E_Type][E_Color][2]  // ��֡ʱ��/֡������
// // // // #define Frame_Play_Data     EffectData[E_Type][E_Color][3]  // ֡��������
// // // // #define Frame_Image_Num     EffectData[E_Type][E_Color][4]  // ��ǰ����ĵ�Ч����
// // // // #define Frame_Play_Mode     EffectData[E_Type][E_Color][5]  // ֡����ģʽ
// // // // #define Frame_Pixel_Num     EffectData[E_Type][E_Color][6]  // ÿ֡�������������� 1~255

// #define Imgae_KF_Num       EffectData[E_Type][E_Color][0]  // �ؼ�֡������ ��1~255��
// #define Frame_In_Num    EffectData[E_Type][E_Color][1]  // ��֡�����ؼ�֮֡�䣩
// #define Frame_time          EffectData[E_Type][E_Color][2]  // ��֡ʱ��/֡������
// #define Frame_Play_Data     EffectData[E_Type][E_Color][3]  // ֡��������
// #define Frame_Image_Num     EffectData[E_Type][E_Color][4]  // ��ǰ����ĵ�Ч����
// #define Frame_Play_Mode     EffectData[E_Type][E_Color][5]  // ֡����ģʽ
// #define Frame_Pixel_Num     EffectData[E_Type][E_Color][6]  // ÿ֡�������������� 1~255

#define Imgae_KF_Num    EffectData[E_Type][E_Color][0]  // �ؼ�֡������ ��1~255��KeyFrames
#define Image_EF_Num    EffectData[E_Type][E_Color][1]  // ��ǰ����Ч����
#define Frame_In_Num    EffectData[E_Type][E_Color][2]  // �Զ���֡�������ؼ�֮֡�䣩Insert Frames
#define Frame_Time_N    EffectData[E_Type][E_Color][3]  // ֡�������֡ʱ�䣩  Frames Time
#define Frame_Px_Num    EffectData[E_Type][E_Color][4]  // ��֡���������� Pixel number
#define Image_Para_1    EffectData[E_Type][E_Color][5]  // ����1 ƫ����
#define Image_Para_2    EffectData[E_Type][E_Color][6]  // ����2


#define FrameArry_Add       EffectAddress[E_Type][E_Color]  // ��Ч��֡��Ϣ����Ļ���ַ

#define Frame_All_Sum       (Imgae_KF_Num * (Frame_In_Num + 1))    // �õ�Ч����֡�������ϲ�֡��
    // // uint16_t FrameSum;    // ��Ч֡����

#define FrameSum Image_Dynamic[EffextImage_num].KeyFrameSum *(Image_Dynamic[EffextImage_num].InsertNum + 1) // ��Ч֡����

// typedef enum
// {
//     MOD_
// }Play_Mode;

typedef struct image
{
    uint8_t *image_adr;   // ��Чͼ������ָ��
    uint8_t KeyFrameSum;  // �ؼ�֡����
    uint8_t PixelSum;     // ͼ�����������
    uint8_t InsertNum;    // �Զ���֡����
    uint8_t IntervalTime; // ֡���ʱ��
    uint8_t PlayMod;      // ����ģʽ
    uint8_t Para_1;       // ģʽ����
} ImageTypeDef;

/* �µ�Ч */
typedef enum
{
    MOTION_STATIC, // Static ��̬
    MOTION_BREATH, // Breath ����
    MOTION_STREAM, // Stream ����
    MOTION_REVERB, // Reverberate ����
    MOTION_HOPSCO, // Hopscotch ����
    MOTION_LIGHTN, // Lightning ����
    MOTION_IGNITE, // Ignite ��ȼ
    MOTION_RANDOM, // Random ���
} Motion_TypeDef;

typedef enum
{
    MOVE_UP,       // �����ƶ�
    MOVE_DOWN,     // �����ƶ�
    MOVE_LEFT,     // �����ƶ�
    MOVE_RIGHT,    // �����ƶ�
    MOVE_SEPARATE, // ���ܷ�ɢ
    MOVE_CONVERGE, // ���Ļ��
} Move_TypeDef;

typedef enum
{
    MODE_NORMAL, // ��ͨģʽ
    MODE_RHYTHM, // �ɶ�ģʽ
} MODE_TypeDef;

#define arry(ary) ary
#define size(arry) sizeof(arry) / 4
#define time(t) t
#define insert(n) n
#define speed(n) n

typedef struct
{
    uint8_t *image_adr;   // ��ɫ����
    uint8_t *addr_table;  // ��ַ��
    uint8_t KeySum;       // �ؼ�֡����
    uint16_t InsertNum;   // �Զ���֡����
    uint8_t IntervalTime; // ֡���ʱ��
    uint8_t Speed;        // �ٶ�/������֡��
    uint32_t FrameAmount; // ��֡��
    // // // // // // uint8_t PixelSum;     // ͼ����������� .��ɾ
    MODE_TypeDef Mode;    // ��ͨ/�ɶ�
} FrameInfro_TypeDef;     // ֡��Ϣ

typedef struct
{
    uint8_t EF_ID; // ��Ч���
    // // // // uint8_t flash_flag; // ��Ч��λ��־
    // // // // uint8_t Direction;           // ����
    uint8_t Module_WorkNum;    // �õ���ģ����    0~15
    Motion_TypeDef MotionType; // ��Ч����
    Move_TypeDef MoveType;     // �˶�����
    // // // // // // // // uint8_t *para_ptr;           // ��Ч����ָ��
    uint8_t Color_buffer[256][4]; // ɫ����

    FrameInfro_TypeDef FrameInfro;
} Effect_TypeDef;

extern Effect_TypeDef EF_Work;

typedef struct
{
    // // uint8_t *addr_table;        // ��ַ��
    uint8_t *color_array;       // ɫ��
    uint8_t color_sum;          // ɫ������ɫ����
    Motion_TypeDef motion_flag; // ��Ч���
    Move_TypeDef move_flag;     // �˶�������
    MODE_TypeDef Mode;          // ��ͨ/�ɶ�
    uint8_t Speed;
} EFdata_TypeDef;

//�����ٶȡ���ʼ���ȡ���Ч���͡��˶�������ɫ��� �ɶ�����mic������
// // // // typedef struct
// // // // {
// // // //     // ��ɫָ��
// // // //     uint8_t bright;             // ����
// // // //     uint8_t speed;              // �ٶ�
// // // //     Motion_TypeDef motion_flag; // ��Ч���
// // // //     Move_TypeDef move_flag;     // �˶�������

// // // // } defaultdata_TypeDef;

extern ImageTypeDef img1;
extern const ImageTypeDef Image_Dynamic[100];
extern const ImageTypeDef Image_Static[20];

// extern unsigned char const Color_A0[2][4];

extern unsigned char *EffectAddress[][16];
extern unsigned char EffectData[][16][7];

extern const uint8_t Random_ColorTable[15][4];

extern unsigned char const PixelArrey_KeyFrame_A0[][4]; // �������еĹؼ�֡��

extern const unsigned char Rhythm_ColorTable[][4];
extern unsigned char Rhythm_ColorData[];

#endif
