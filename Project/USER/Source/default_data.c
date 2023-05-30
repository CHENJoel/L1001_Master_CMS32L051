#include "Function_Init.H"
#include "default_data.h"
#define endingcolor 255, 255, 255, 255, // ½áÊøÑÕÉ«±êÖ¾£¬ÓÃÓÚÅÐ¶Ïµ±Ç°Îª×îºóÒ»¸öÑÕÉ«
df_data_TypeDef dfdata[built_in_ef_num] =
{
    {"Reading",     (p_arry)df_White_4000K,  STATIC_TYPE, FLOW_STATIC },/*0*/
    {"Working",     (p_arry)df_White_3500K,  STATIC_TYPE, FLOW_STATIC },/*1*/
    {"3000K",       (p_arry)df_White_3000K,  STATIC_TYPE, FLOW_STATIC },/*2*/
    {"Night light", (p_arry)df_White_2700K,  STATIC_TYPE, FLOW_STATIC },/*3*/
    {"vitality",    (p_arry)df_Vitality,     STATIC_TYPE, FLOW_STATIC },/*4*/
    {"Spring",      (p_arry)df_Spring,       STATIC_TYPE, FLOW_STATIC },/*5*/
    {"Summer",      (p_arry)df_Summer,       STATIC_TYPE, FLOW_STATIC },/*6*/
    {"Autumn",      (p_arry)df_Autumn,       STATIC_TYPE, FLOW_STATIC },/*7*/
    {"Winter",      (p_arry)df_Winter,       STATIC_TYPE, FLOW_STATIC },/*8*/
    {"Cyberpunk",   (p_arry)df_Cyberpunk,    STATIC_TYPE, FLOW_STATIC },/*9*/

    {"Deep Breath", (p_arry)df_Deep_Breath,  DYNAMIC_TYPE,FLOW_BREATH },/*10*/
    {"Sweet",       (p_arry)df_Sweet,        DYNAMIC_TYPE,FLOW_BREATH },/*11*/
    {"Romantic",    (p_arry)df_Romantic,     DYNAMIC_TYPE,FLOW_STREAM },/*12*/
    {"Aurora",      (p_arry)df_Aurora,       DYNAMIC_TYPE,FLOW_REVERB },/*13*/
    {"Ocean",       (p_arry)df_Ocean,        DYNAMIC_TYPE,FLOW_REVERB },/*14*/
    {"lightning",   (p_arry)df_lightning,    DYNAMIC_TYPE,FLOW_LIGHTN },/*15*/
    {"fireworks",   (p_arry)df_fireworks,    DYNAMIC_TYPE,FLOW_IGNITE },/*16*/
    {"Snake",       (p_arry)df_Snake,        DYNAMIC_TYPE,FLOW_STREAM },/*17*/
    {"Bouncy ball", (p_arry)df_BouncyBall,   DYNAMIC_TYPE,FLOW_REVERB },/*18*/
    {"Lightsaber",  (p_arry)df_Lightsaber,   DYNAMIC_TYPE,FLOW_IGNITE },/*19*/
    {"Thanksgiving",(p_arry)df_Thanksgiving, DYNAMIC_TYPE,FLOW_REVERB },/*20*/
    {"Halloween",   (p_arry)df_Halloween,    DYNAMIC_TYPE,FLOW_IGNITE },/*21*/
    {"Christmas",   (p_arry)df_Christmas,    DYNAMIC_TYPE,FLOW_HOPSCO },/*22*/
    {"Colorful",    (p_arry)df_Colorful,     DYNAMIC_TYPE,FLOW_RANDOM },/*23*/
    {"Kaleidoscope",(p_arry)df_Kaleidoscope, DYNAMIC_TYPE,FLOW_RANDOM },/*24*/

    {"Rhythm",      (p_arry)df_Rhythm,       RHYTHM_TYPE,FLOW_RANDOM },/*25*/
    {"Meditation",  (p_arry)df_Meditation,   RHYTHM_TYPE,FLOW_BREATH },/*26*/
    {"GamingTime",  (p_arry)df_GamingTime,   RHYTHM_TYPE,FLOW_LIGHTN },/*27*/
    {"Disco",       (p_arry)df_Disco,        RHYTHM_TYPE,FLOW_REVERB },/*28*/
    {"Dance Party",  (p_arry)df_DanceParty,  RHYTHM_TYPE,FLOW_RANDOM },/*29*/
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
    {0, 0, 255, 0}, // À¶É«
    {0, 255, 0, 0}, // ÂÌÉ«
    {255, 0, 0, 0}, // ºìÉ«
    {endingcolor},
};
const uint8_t df_testcolor5[][4] = {
    {255, 0, 0, 0},   // ³à
    {255, 165, 0, 0}, // ³È
    {255, 255, 0, 0}, // »Æ
    {0, 255, 0, 0},   // ÂÌ
    {0, 127, 255, 0}, // Çà
    {0, 0, 255, 0},   // À¶
    {139, 0, 255, 0}, // ×Ï
    // {18, 0, 83, 0},   // ÷ì
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
    {255, 128, 0, 0}, // ³ÈÉ«
    {endingcolor},
};
const uint8_t df_Spring[][4] = {
    {200, 255, 37, 0}, // µ­»ÆÂÌ
    {endingcolor},
};
const uint8_t df_Summer[][4] = {
    {233, 71, 9, 0}, // ³Èºì
    {endingcolor},
};
const uint8_t df_Autumn[][4] = {
    {237, 175, 32, 0}, // »ÆÉ«
    {endingcolor},
};
const uint8_t df_Winter[][4] = {
    {87, 140, 188, 0}, // À¶É«
    {endingcolor},
};
const uint8_t df_Cyberpunk[][4] = {
    {37, 188, 255, 0}, // Ç³À¶
    {23, 129, 232, 0}, // À¶
    {146, 35, 255, 0}, // ×Ï
    {230, 45, 232, 0}, // ·Û×Ï
    {255, 13, 192, 0}, // ×Ïºì
    {endingcolor},
};
const uint8_t df_Deep_Breath[][4] = {
    {90, 167, 167, 0},  // Çà
    {150, 215, 198, 0}, // ·ÛÂÌ
    {186, 201, 74, 0},  // ÄÛÂÌ
    {108, 140, 191, 0}, // À¶É«
    {endingcolor},
};
const uint8_t df_Sweet[][4] = {
    {240, 218, 220, 0}, // ·ÛÉ«
    {245, 150, 176, 0}, // Éî·Û
    {254, 225, 153, 0}, // »ÆÉ«
    {118, 214, 201, 0}, // ÇàÉ«
    {133, 188, 218, 0}, // À¶É«
    {endingcolor},
};

const uint8_t df_Romantic[][4] = {
    {252, 172, 230, 0}, // Ç³·Û
    {253, 135, 221, 0}, // ·ÛÉ«
    {250, 28, 195, 0},  // Éî·ÛÉ«
    {238, 0, 242, 0},   // Ç³×Ïºì
    {112, 0, 240, 0},   // Ç³×ÏÉ«
    {60, 0, 169, 0},    // À¶×ÏÉ«
    {endingcolor},
};
const uint8_t df_Aurora[][4] = {
    {24, 16, 55, 0},    // Éî×ÏÉ«
    {57, 35, 97, 0},    // ×ÏÉ«
    {113, 84, 174, 0},  // Ç³×Ï
    {128, 156, 228, 0}, // Ç³À¶×Ï
    {98, 191, 215, 0},  // Ç³À¶
    {82, 209, 192, 0},  // Ç³Çà
    {121, 246, 194, 0}, // ·ÛÂÌ
    {4, 164, 94, 0},    // ÂÌÉ«
    {endingcolor},
};

const uint8_t df_Ocean[][4] = {
    {241, 242, 237, 0}, // »Ò°×
    {128, 211, 215, 0}, // Ç³À¶
    {113, 185, 223, 0}, // À¶É«
    {41, 15, 180, 0},   // º£À¶É«
    {endingcolor},
};

const uint8_t df_lightning[][4] = {
    {246, 234, 246, 0}, // °××Ï
    {72, 27, 137, 0},   // ×ÏÉ«
    {endingcolor},
};
const uint8_t df_fireworks[][4] = {
    {247, 198, 166, 0}, // ³ÈÉ«
    {247, 131, 137, 0}, // ºìÉ«
    {166, 58, 76, 0},   // Öìºì
    {38, 38, 94, 0},    // À¶×Ï
    {endingcolor},
};
const uint8_t df_Snake[][4] = {
    {236, 229, 126, 0}, // »Æ
    {227, 135, 0, 0},   // ³È
    {83, 155, 87, 0},   // ÂÌ
    {204, 48, 115, 0},  // ×Ïºì
    {237, 229, 196, 0}, // Ã×°×
    {92, 72, 148, 0},   // ×ÏÉ«
    {endingcolor},
};
const uint8_t df_BouncyBall[][4] = {
    {122, 33, 158, 0},  // ×ÏÉ«
    {0, 86, 214, 0},    // À¶É«
    {244, 164, 192, 0}, // ·ÛÉ«
    {118, 87, 64, 0},   // ÂÌÉ«
    {endingcolor},
};
const uint8_t df_Lightsaber[][4] = {
    {0, 255, 255, 0},   // À¶
    {0, 255, 0, 0},     // ÂÌ
    {255, 13, 192, 0},  // ×Ï
    {255, 0, 0, 0},     // ºì
    {255, 255, 0, 0},   // »Æ
    {227, 135, 0, 0},   // ³È
    {255, 255, 255, 0}, // °×
    {endingcolor},
};
const uint8_t df_Thanksgiving[][4] = {
    {254, 202, 120, 0}, // µ­³ÈÉ«
    {248, 132, 27, 0},  // ³ÈÉ«
    {227, 93, 34, 0},   // ³ÈºìÉ«
    {endingcolor},
};

const uint8_t df_Halloween[][4] = {
    {0, 0, 0, 0},       // ºÚÉ«
    {247, 103, 24, 0},  // ³ÈÉ«
    {255, 255, 255, 0}, // °×É«
    {endingcolor},
};
const uint8_t df_Christmas[][4] = {
    {25, 70, 31, 0},   // ÂÌÉ«
    {255, 176, 87, 0}, // ³ÈÉ«
    {230, 70, 37, 0},  // ³Èºì
    {154, 5, 2, 0},    // ºìÉ«
    {endingcolor},
};
const uint8_t df_Colorful[][4] = {
    {255, 0, 0, 0},   // ³à
    {255, 165, 0, 0}, // ³È
    {255, 255, 0, 0}, // »Æ
    {0, 255, 0, 0},   // ÂÌ
    {0, 127, 255, 0}, // Çà
    {0, 0, 255, 0},   // À¶
    {139, 0, 255, 0}, // ×Ï
    {18, 0, 83, 0},   // ÷ì
    {endingcolor},
};
const uint8_t df_Kaleidoscope[][4] = {
    {249, 255, 12, 0},  // »Æ
    {252, 74, 8, 0},    // ³È
    {226, 0, 57, 0},    // ºì
    {57, 0, 123, 0},    // ×Ï
    {124, 140, 216, 0}, // Ç³×Ï
    {15, 121, 143, 0},  // Çà
    {16, 123, 2, 0},    // ÉîÂÌ
    {137, 218, 7, 0},   // Ç³ÂÌ
    {endingcolor},
};
const uint8_t df_Rhythm[][4] = {
    {249, 255, 12, 0},  // »Æ
    {252, 74, 8, 0},    // ³È
    {226, 0, 57, 0},    // ºì
    {57, 0, 123, 0},    // ×Ï
    {124, 140, 216, 0}, // Ç³×Ï
    {15, 121, 143, 0},  // Çà
    {16, 123, 2, 0},    // ÉîÂÌ
    {137, 218, 7, 0},   // Ç³ÂÌ
    {endingcolor},
};
const uint8_t df_Meditation[][4] = {
    {0, 64, 128, 0},    // º£¾üÀ¶
    {0, 217, 217, 0},   // À¶ÂÌÉ«
    {232, 183, 212, 0}, // Èá·Û
    {endingcolor},
};
const uint8_t df_GamingTime[][4] = {
    {37, 188, 255, 0}, // Ç³À¶
    {23, 129, 232, 0}, // À¶
    {146, 35, 255, 0}, // ×Ï
    {230, 45, 232, 0}, // ·Û×Ï
    {255, 13, 192, 0}, // ×Ïºì
    {endingcolor},
};
const uint8_t df_Disco[][4] = {
    {0, 0, 255, 0}, // À¶É«
    {0, 255, 0, 0}, // ÂÌÉ«
    {255, 0, 0, 0}, // ºìÉ«
    {endingcolor},
};
const uint8_t df_DanceParty[][4] = {
    {255, 0, 0, 0},   // ³à
    {255, 165, 0, 0}, // ³È
    {255, 255, 0, 0}, // »Æ
    {0, 255, 0, 0},   // ÂÌ
    {0, 127, 255, 0}, // Çà
    {0, 0, 255, 0},   // À¶
    {139, 0, 255, 0}, // ×Ï
    {18, 0, 83, 0},   // ÷ì
    {endingcolor},
};
