#include "Function_Init.H"
#include "default_data.h"
#define endingcolor 255, 255, 255, 255, // ������ɫ��־�������жϵ�ǰΪ���һ����ɫ
df_data_TypeDef dfdata[built_in_ef_num] =
{
    {"df_White_4000K", (p_arry)df_White_4000K,  STATIC_TYPE, FLOW_STATIC },/*0*/
    {"df_White_3500K", (p_arry)df_White_3500K,  STATIC_TYPE, FLOW_STATIC },/*1*/
    {"df_White_3000K", (p_arry)df_White_3000K,  STATIC_TYPE, FLOW_STATIC },/*2*/
    {"df_White_2700K", (p_arry)df_White_2700K,  STATIC_TYPE, FLOW_STATIC },/*3*/
    {"df_Vitality",    (p_arry)df_Vitality,     STATIC_TYPE, FLOW_STATIC },/*4*/
    {"df_Spring",      (p_arry)df_Spring,       STATIC_TYPE, FLOW_STATIC },/*5*/
    {"df_Summer",      (p_arry)df_Summer,       STATIC_TYPE, FLOW_STATIC },/*6*/
    {"df_Autumn",      (p_arry)df_Autumn,       STATIC_TYPE, FLOW_STATIC },/*7*/
    {"df_Winter",      (p_arry)df_Winter,       STATIC_TYPE, FLOW_STATIC },/*8*/
    {"df_Cyberpunk",   (p_arry)df_Cyberpunk,    STATIC_TYPE, FLOW_STATIC },/*9*/

    {"df_Deep_Breath", (p_arry)df_Deep_Breath,  DYNAMIC_TYPE,FLOW_BREATH },/*10*/
    {"df_Sweet",       (p_arry)df_Sweet,        DYNAMIC_TYPE,FLOW_BREATH },/*11*/
    {"df_Romantic",    (p_arry)df_Romantic,     DYNAMIC_TYPE,FLOW_STREAM },/*12*/
    {"df_Aurora",      (p_arry)df_Aurora,       DYNAMIC_TYPE,FLOW_REVERB },/*13*/
    {"df_Ocean",       (p_arry)df_Ocean,        DYNAMIC_TYPE,FLOW_REVERB },/*14*/
    {"df_lightning",   (p_arry)df_lightning,    DYNAMIC_TYPE,FLOW_LIGHTN },/*15*/
    {"df_fireworks",   (p_arry)df_fireworks,    DYNAMIC_TYPE,FLOW_IGNITE },/*16*/
    {"df_Snake",       (p_arry)df_Snake,        DYNAMIC_TYPE,FLOW_STREAM },/*17*/
    {"df_BouncyBall",  (p_arry)df_BouncyBall,   DYNAMIC_TYPE,FLOW_REVERB },/*18*/
    {"df_Lightsaber",  (p_arry)df_Lightsaber,   DYNAMIC_TYPE,FLOW_IGNITE },/*19*/
    {"df_Thanksgiving",(p_arry)df_Thanksgiving, DYNAMIC_TYPE,FLOW_REVERB },/*20*/
    {"df_Halloween",   (p_arry)df_Halloween,    DYNAMIC_TYPE,FLOW_IGNITE },/*21*/
    {"df_Christmas",   (p_arry)df_Christmas,    DYNAMIC_TYPE,FLOW_HOPSCO },/*22*/
    {"df_Colorful",    (p_arry)df_Colorful,     DYNAMIC_TYPE,FLOW_RANDOM },/*23*/
    {"df_Kaleidoscope",(p_arry)df_Kaleidoscope, DYNAMIC_TYPE,FLOW_RANDOM },/*24*/

    {"df_Rhythm",      (p_arry)df_Rhythm,       RHYTHM_TYPE,FLOW_RANDOM },/*25*/
    {"df_Meditation",  (p_arry)df_Meditation,   RHYTHM_TYPE,FLOW_BREATH },/*26*/
    {"df_GamingTime",  (p_arry)df_GamingTime,   RHYTHM_TYPE,FLOW_LIGHTN },/*27*/
    {"df_Disco",       (p_arry)df_Disco,        RHYTHM_TYPE,FLOW_REVERB },/*28*/
    {"df_DanceParty",  (p_arry)df_DanceParty,   RHYTHM_TYPE,FLOW_RANDOM },/*29*/
};

const uint8_t df_testcolor1[][4] = {
    {0, 255, 0, 0},
    {endingcolor},
};
const uint8_t df_testcolor2[][4] = {
    {0, 0, 255, 0},
    {endingcolor},
};
const uint8_t df_testcolor3[][4] = {
    {255, 0, 0, 0},
    {endingcolor},
};
const uint8_t df_testcolor4[][4] = {
    {0, 0, 255, 0}, // ��ɫ
    {0, 255, 0, 0}, // ��ɫ
    {255, 0, 0, 0}, // ��ɫ
    {endingcolor},
};
const uint8_t df_testcolor5[][4] = {
    {255, 0, 0, 0},   // ��
    {255, 165, 0, 0}, // ��
    {255, 255, 0, 0}, // ��
    {0, 255, 0, 0},   // ��
    {0, 127, 255, 0}, // ��
    {0, 0, 255, 0},   // ��
    {139, 0, 255, 0}, // ��
    // {18, 0, 83, 0},   // ��
};

const uint8_t df_White_4000K[][4] = {
    {0, 21, 9, 194},
    {endingcolor},
};
const uint8_t df_White_3500K[][4] = {
    {0, 14, 6, 214},
    {endingcolor},
};
const uint8_t df_White_3000K[][4] = {
    {0, 6, 2, 240},
    {endingcolor},
};
const uint8_t df_White_2700K[][4] = {
    {11, 7, 0, 221},
    {endingcolor},
};
const uint8_t df_Vitality[][4] = {
    {255, 128, 0, 0}, // ��ɫ
    {endingcolor},
};
const uint8_t df_Spring[][4] = {
    {200, 255, 37, 0}, // ������
    {endingcolor},
};
const uint8_t df_Summer[][4] = {
    {233, 71, 9, 0}, // �Ⱥ�
    {endingcolor},
};
const uint8_t df_Autumn[][4] = {
    {237, 175, 32, 0}, // ��ɫ
    {endingcolor},
};
const uint8_t df_Winter[][4] = {
    {87, 140, 188, 0}, // ��ɫ
    {endingcolor},
};
const uint8_t df_Cyberpunk[][4] = {
    {37, 188, 255, 0}, // ǳ��
    {23, 129, 232, 0}, // ��
    {146, 35, 255, 0}, // ��
    {230, 45, 232, 0}, // ����
    {255, 13, 192, 0}, // �Ϻ�
    {endingcolor},
};
const uint8_t df_Deep_Breath[][4] = {
    {90, 167, 167, 0},  // ��
    {150, 215, 198, 0}, // ����
    {186, 201, 74, 0},  // ����
    {108, 140, 191, 0}, // ��ɫ
    {endingcolor},
};
const uint8_t df_Sweet[][4] = {
    {240, 218, 220, 0}, // ��ɫ
    {245, 150, 176, 0}, // ���
    {254, 225, 153, 0}, // ��ɫ
    {118, 214, 201, 0}, // ��ɫ
    {133, 188, 218, 0}, // ��ɫ
    {endingcolor},
};

const uint8_t df_Romantic[][4] = {
    {252, 172, 230, 0}, // ǳ��
    {253, 135, 221, 0}, // ��ɫ
    {250, 28, 195, 0},  // ���ɫ
    {238, 0, 242, 0},   // ǳ�Ϻ�
    {112, 0, 240, 0},   // ǳ��ɫ
    {60, 0, 169, 0},    // ����ɫ
    {endingcolor},
};
const uint8_t df_Aurora[][4] = {
    {24, 16, 55, 0},    // ����ɫ
    {57, 35, 97, 0},    // ��ɫ
    {113, 84, 174, 0},  // ǳ��
    {128, 156, 228, 0}, // ǳ����
    {98, 191, 215, 0},  // ǳ��
    {82, 209, 192, 0},  // ǳ��
    {121, 246, 194, 0}, // ����
    {4, 164, 94, 0},    // ��ɫ
    {endingcolor},
};

const uint8_t df_Ocean[][4] = {
    {241, 242, 237, 0}, // �Ұ�
    {128, 211, 215, 0}, // ǳ��
    {113, 185, 223, 0}, // ��ɫ
    {41, 15, 180, 0},   // ����ɫ
    {endingcolor},
};

const uint8_t df_lightning[][4] = {
    {246, 234, 246, 0}, // ����
    {72, 27, 137, 0},   // ��ɫ
    {endingcolor},
};
const uint8_t df_fireworks[][4] = {
    {247, 198, 166, 0}, // ��ɫ
    {247, 131, 137, 0}, // ��ɫ
    {166, 58, 76, 0},   // ���
    {38, 38, 94, 0},    // ����
    {endingcolor},
};
const uint8_t df_Snake[][4] = {
    {236, 229, 126, 0}, // ��
    {227, 135, 0, 0},   // ��
    {83, 155, 87, 0},   // ��
    {204, 48, 115, 0},  // �Ϻ�
    {237, 229, 196, 0}, // �װ�
    {92, 72, 148, 0},   // ��ɫ
    {endingcolor},
};
const uint8_t df_BouncyBall[][4] = {
    {122, 33, 158, 0},  // ��ɫ
    {0, 86, 214, 0},    // ��ɫ
    {244, 164, 192, 0}, // ��ɫ
    {118, 87, 64, 0},   // ��ɫ
    {endingcolor},
};
const uint8_t df_Lightsaber[][4] = {
    {0, 255, 255, 0},   // ��
    {0, 255, 0, 0},     // ��
    {255, 13, 192, 0},  // ��
    {255, 0, 0, 0},     // ��
    {255, 255, 0, 0},   // ��
    {227, 135, 0, 0},   // ��
    {255, 255, 255, 0}, // ��
    {endingcolor},
};
const uint8_t df_Thanksgiving[][4] = {
    {254, 202, 120, 0}, // ����ɫ
    {248, 132, 27, 0},  // ��ɫ
    {227, 93, 34, 0},   // �Ⱥ�ɫ
    {endingcolor},
};

const uint8_t df_Halloween[][4] = {
    {0, 0, 0, 0},       // ��ɫ
    {247, 103, 24, 0},  // ��ɫ
    {255, 255, 255, 0}, // ��ɫ
    {endingcolor},
};
const uint8_t df_Christmas[][4] = {
    {25, 70, 31, 0},   // ��ɫ
    {255, 176, 87, 0}, // ��ɫ
    {230, 70, 37, 0},  // �Ⱥ�
    {154, 5, 2, 0},    // ��ɫ
    {endingcolor},
};
const uint8_t df_Colorful[][4] = {
    {255, 0, 0, 0},   // ��
    {255, 165, 0, 0}, // ��
    {255, 255, 0, 0}, // ��
    {0, 255, 0, 0},   // ��
    {0, 127, 255, 0}, // ��
    {0, 0, 255, 0},   // ��
    {139, 0, 255, 0}, // ��
    {18, 0, 83, 0},   // ��
    {endingcolor},
};
const uint8_t df_Kaleidoscope[][4] = {
    {249, 255, 12, 0},  // ��
    {252, 74, 8, 0},    // ��
    {226, 0, 57, 0},    // ��
    {57, 0, 123, 0},    // ��
    {124, 140, 216, 0}, // ǳ��
    {15, 121, 143, 0},  // ��
    {16, 123, 2, 0},    // ����
    {137, 218, 7, 0},   // ǳ��
    {endingcolor},
};
const uint8_t df_Rhythm[][4] = {
    {249, 255, 12, 0},  // ��
    {252, 74, 8, 0},    // ��
    {226, 0, 57, 0},    // ��
    {57, 0, 123, 0},    // ��
    {124, 140, 216, 0}, // ǳ��
    {15, 121, 143, 0},  // ��
    {16, 123, 2, 0},    // ����
    {137, 218, 7, 0},   // ǳ��
    {endingcolor},
};
const uint8_t df_Meditation[][4] = {
    {0, 64, 128, 0},    // ������
    {0, 217, 217, 0},   // ����ɫ
    {232, 183, 212, 0}, // ���
    {endingcolor},
};
const uint8_t df_GamingTime[][4] = {
    {37, 188, 255, 0}, // ǳ��
    {23, 129, 232, 0}, // ��
    {146, 35, 255, 0}, // ��
    {230, 45, 232, 0}, // ����
    {255, 13, 192, 0}, // �Ϻ�
    {endingcolor},
};
const uint8_t df_Disco[][4] = {
    {0, 0, 255, 0}, // ��ɫ
    {0, 255, 0, 0}, // ��ɫ
    {255, 0, 0, 0}, // ��ɫ
    {endingcolor},
};
const uint8_t df_DanceParty[][4] = {
    {255, 0, 0, 0},   // ��
    {255, 165, 0, 0}, // ��
    {255, 255, 0, 0}, // ��
    {0, 255, 0, 0},   // ��
    {0, 127, 255, 0}, // ��
    {0, 0, 255, 0},   // ��
    {139, 0, 255, 0}, // ��
    {18, 0, 83, 0},   // ��
    {endingcolor},
};
