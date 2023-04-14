#include "Function_Init.H"
#include "colorbox.h"
#include "Color.H"

// Çà£¨90,167,167£©
// ·ÛÂÌ£¨150,215,198£©
// ÄÛÂÌ£¨186,201,74£©
// À¶É«£¨108,140,191£©

// // // {255, 0, 0, 0},
// // // {0, 255, 0, 0},
// // // {0, 0, 255, 0},
// // // {0, 0, 0, 255},

/*
16?RGB?????5????6?????5?????
4*/

const uint8_t testcolor1[][4] = {
    {0, 255, 0, 0},
};
const uint8_t testcolor2[][4] = {
    {0, 0, 255, 0},
};
const uint8_t testcolor3[][4] = {
    {255, 0, 0, 0},
};
const uint8_t testcolor4[][4] = {
    {0, 0, 255, 0}, // À¶É«
    {0, 255, 0, 0}, // ÂÌÉ«
    {255, 0, 0, 0}, // ºìÉ«
};
const uint8_t testcolor5[][4] = {
    {255, 0, 0, 0},   // ³à
    {255, 165, 0, 0}, // ³È
    {255, 255, 0, 0}, // »Æ
    {0, 255, 0, 0},   // ÂÌ
    {0, 127, 255, 0}, // Çà
    {0, 0, 255, 0},   // À¶
    {139, 0, 255, 0}, // ×Ï
    // {18, 0, 83, 0},   // ÷ì
};

const uint8_t White_4000K[][4] = {
    {0, 21, 9, 194},
};
const uint8_t White_3500K[][4] = {
    {0, 14, 6, 214},
};
const uint8_t White_3000K[][4] = {
    {0, 6, 2, 240},
};
const uint8_t White_2700K[][4] = {
    {11, 7, 0, 221},
};
const uint8_t Vitality[][4] = {
    {255, 128, 0, 0}, // ³ÈÉ«
};
const uint8_t Spring[][4] = {
    {200, 255, 37, 0}, // µ­»ÆÂÌ
};
const uint8_t Summer[][4] = {
    {233, 71, 9, 0}, // ³Èºì
};
const uint8_t Autumn[][4] = {
    {237, 175, 32, 0}, // »ÆÉ«
};
const uint8_t Winter[][4] = {
    {87, 140, 188, 0}, // À¶É«
};
const uint8_t Cyberpunk[][4] = {
    {37, 188, 255, 0}, // Ç³À¶
    {23, 129, 232, 0}, // À¶
    {146, 35, 255, 0}, // ×Ï
    {230, 45, 232, 0}, // ·Û×Ï
    {255, 13, 192, 0}, // ×Ïºì
};
const uint8_t Deep_Breath[][4] = {
    {90, 167, 167, 0},  // Çà
    {150, 215, 198, 0}, // ·ÛÂÌ
    {186, 201, 74, 0},  // ÄÛÂÌ
    {108, 140, 191, 0}, // À¶É«
};
const uint8_t Sweet[][4] = {
    {240, 218, 220, 0}, // ·ÛÉ«
    {245, 150, 176, 0}, // Éî·Û
    {254, 225, 153, 0}, // »ÆÉ«
    {118, 214, 201, 0}, // ÇàÉ«
    {133, 188, 218, 0}, // À¶É«
};

const uint8_t Romantic[][4] = {
    {252, 172, 230, 0}, // Ç³·Û
    {253, 135, 221, 0}, // ·ÛÉ«
    {250, 28, 195, 0},  // Éî·ÛÉ«
    {238, 0, 242, 0},   // Ç³×Ïºì
    {112, 0, 240, 0},   // Ç³×ÏÉ«
    {60, 0, 169, 0},    // À¶×ÏÉ«

};
const uint8_t Aurora[][4] = {
    {24, 16, 55, 0},    // Éî×ÏÉ«
    {57, 35, 97, 0},    // ×ÏÉ«
    {113, 84, 174, 0},  // Ç³×Ï
    {128, 156, 228, 0}, // Ç³À¶×Ï
    {98, 191, 215, 0},  // Ç³À¶
    {82, 209, 192, 0},  // Ç³Çà
    {121, 246, 194, 0}, // ·ÛÂÌ
    {4, 164, 94, 0},    // ÂÌÉ«
};

const uint8_t Ocean[][4] = {
    {241, 242, 237, 0}, // »Ò°×
    {128, 211, 215, 0}, // Ç³À¶
    {113, 185, 223, 0}, // À¶É«
    {41, 15, 180, 0},   // º£À¶É«
};

const uint8_t lightning[][4] = {
    {246, 234, 246, 0}, // °××Ï
    {72, 27, 137, 0},   // ×ÏÉ«
};
const uint8_t fireworks[][4] = {
    {247, 198, 166, 0}, // ³ÈÉ«
    {247, 131, 137, 0}, // ºìÉ«
    {166, 58, 76, 0},   // Öìºì
    {38, 38, 94, 0},    // À¶×Ï
};
const uint8_t Snake[][4] = {
    {236, 229, 126, 0}, // »Æ
    {227, 135, 0, 0},   // ³È
    {83, 155, 87, 0},   // ÂÌ
    {204, 48, 115, 0},  // ×Ïºì
    {237, 229, 196, 0}, // Ã×°×
    {92, 72, 148, 0},   // ×ÏÉ«
};
const uint8_t BouncyBall[][4] = {
    {122, 33, 158, 0},  // ×ÏÉ«
    {0, 86, 214, 0},    // À¶É«
    {244, 164, 192, 0}, // ·ÛÉ«
    {118, 87, 64, 0},   // ÂÌÉ«
};
const uint8_t Lightsaber[][4] = {
    {0, 255, 255, 0},   // À¶
    {0, 255, 0, 0},     // ÂÌ
    {255, 13, 192, 0},  // ×Ï
    {255, 0, 0, 0},     // ºì
    {255, 255, 0, 0},   // »Æ
    {227, 135, 0, 0},   // ³È
    {255, 255, 255, 0}, // °×
};
const uint8_t Thanksgiving[][4] = {
    {254, 202, 120, 0}, // µ­³ÈÉ«
    {248, 132, 27, 0},  // ³ÈÉ«
    {227, 93, 34, 0},   // ³ÈºìÉ«
};

const uint8_t Halloween[][4] = {
    {0, 0, 0, 0},       // ºÚÉ«
    {247, 103, 24, 0},  // ³ÈÉ«
    {255, 255, 255, 0}, // °×É«
};
const uint8_t Christmas[][4] = {
    {25, 70, 31, 0},   // ÂÌÉ«
    {255, 176, 87, 0}, // ³ÈÉ«
    {230, 70, 37, 0},  // ³Èºì
    {154, 5, 2, 0},    // ºìÉ«

};
const uint8_t Colorful[][4] = {
    {255, 0, 0, 0},   // ³à
    {255, 165, 0, 0}, // ³È
    {255, 255, 0, 0}, // »Æ
    {0, 255, 0, 0},   // ÂÌ
    {0, 127, 255, 0}, // Çà
    {0, 0, 255, 0},   // À¶
    {139, 0, 255, 0}, // ×Ï
    {18, 0, 83, 0},   // ÷ì
};
const uint8_t Kaleidoscope[][4] = {
    {249, 255, 12, 0},  // »Æ
    {252, 74, 8, 0},    // ³È
    {226, 0, 57, 0},    // ºì
    {57, 0, 123, 0},    // ×Ï
    {124, 140, 216, 0}, // Ç³×Ï
    {15, 121, 143, 0},  // Çà
    {16, 123, 2, 0},    // ÉîÂÌ
    {137, 218, 7, 0},   // Ç³ÂÌ
};
const uint8_t Rhythm[][4] = {
    {249, 255, 12, 0},  // »Æ
    {252, 74, 8, 0},    // ³È
    {226, 0, 57, 0},    // ºì
    {57, 0, 123, 0},    // ×Ï
    {124, 140, 216, 0}, // Ç³×Ï
    {15, 121, 143, 0},  // Çà
    {16, 123, 2, 0},    // ÉîÂÌ
    {137, 218, 7, 0},   // Ç³ÂÌ
};
const uint8_t Meditation[][4] = {
    {0, 64, 128, 0},    // º£¾üÀ¶
    {0, 217, 217, 0},   // À¶ÂÌÉ«
    {232, 183, 212, 0}, // Èá·Û
};
const uint8_t GamingTime[][4] = {
    {37, 188, 255, 0}, // Ç³À¶
    {23, 129, 232, 0}, // À¶
    {146, 35, 255, 0}, // ×Ï
    {230, 45, 232, 0}, // ·Û×Ï
    {255, 13, 192, 0}, // ×Ïºì
};
const uint8_t Disco[][4] = {
    {0, 0, 255, 0}, // À¶É«
    {0, 255, 0, 0}, // ÂÌÉ«
    {255, 0, 0, 0}, // ºìÉ«
};
const uint8_t DanceParty[][4] = {
    {255, 0, 0, 0},   // ³à
    {255, 165, 0, 0}, // ³È
    {255, 255, 0, 0}, // »Æ
    {0, 255, 0, 0},   // ÂÌ
    {0, 127, 255, 0}, // Çà
    {0, 0, 255, 0},   // À¶
    {139, 0, 255, 0}, // ×Ï
    {18, 0, 83, 0},   // ÷ì
};

    // MODE_NORMAL, // ÆÕÍ¨Ä£Ê½
    // MODE_RHYTHM, // ÂÉ¶¯Ä£Ê½

// // // // // // // // // // // // // // // // // // // // // // // const EFdata_TypeDef EF_DefaultData[30] = {
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(White_4000K), size(White_4000K),  MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*0*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(White_3500K), size(White_3500K),  MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*1*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(White_3000K), size(White_3000K),  MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*2*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(White_2700K), size(White_2700K),  MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*3*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Vitality),    size(Vitality),     MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*4*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Spring),      size(Spring),       MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*5*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Summer),      size(Summer),       MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*6*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Autumn),      size(Autumn),       MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*7*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Winter),      size(Winter),       MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*8*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Cyberpunk),   size(Cyberpunk),    MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*9*/

// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Deep_Breath), size(Deep_Breath),  MOTION_BREATH, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*10*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Sweet),       size(Sweet),        MOTION_BREATH, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*11*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Romantic),    size(Romantic),     MOTION_STREAM, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*12*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Aurora),      size(Aurora),       MOTION_REVERB, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*13*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Ocean),       size(Ocean),        MOTION_REVERB, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*14*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(lightning),   size(lightning),    MOTION_LIGHTN, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*15*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(fireworks),   size(fireworks),    MOTION_IGNITE, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*16*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Snake),       size(Snake),        MOTION_STREAM, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*17*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(BouncyBall),  size(BouncyBall),   MOTION_REVERB, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*18*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Lightsaber),  size(Lightsaber),   MOTION_IGNITE, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*19*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Thanksgiving),size(Thanksgiving), MOTION_REVERB, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*20*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Halloween),   size(Halloween),    MOTION_IGNITE, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*21*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Christmas),   size(Christmas),    MOTION_HOPSCO, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*22*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Colorful),    size(Colorful),     MOTION_RANDOM, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*23*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Kaleidoscope),size(Kaleidoscope), MOTION_RANDOM, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*24*/

// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Rhythm),      size(Rhythm),       MOTION_RANDOM, MOVE_RIGHT, MODE_RHYTHM, speed(5)},/*25*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Meditation),  size(Meditation),   MOTION_BREATH, MOVE_RIGHT, MODE_RHYTHM, speed(5)},/*26*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(GamingTime),  size(GamingTime),   MOTION_LIGHTN, MOVE_RIGHT, MODE_RHYTHM, speed(5)},/*27*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(Disco),       size(Disco),        MOTION_REVERB, MOVE_RIGHT, MODE_RHYTHM, speed(5)},/*28*/
// // // // // // // // // // // // // // // // // // // // // // //     {NULL, arry(DanceParty),  size(DanceParty),   MOTION_RANDOM, MOVE_RIGHT, MODE_RHYTHM, speed(5)},/*29*/
// // // // // // // // // // // // // // // // // // // // // // // };


const EFdata_TypeDef EF_DefaultData[30] = {

    {arry(testcolor1), size(testcolor1),  MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*0*/
    {arry(testcolor2), size(testcolor2),  MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*1*/
    {arry(testcolor3), size(testcolor3),  MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*2*/
    {arry(testcolor4), size(testcolor4),  MOTION_REVERB, MOVE_RIGHT, MODE_NORMAL, speed(20)},/*3*/
    {arry(testcolor5), size(testcolor5),  MOTION_RANDOM, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*4*/

    // // // {arry(White_4000K), size(White_4000K),  MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*0*/
    // // // {arry(White_3500K), size(White_3500K),  MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*1*/
    // // // {arry(White_3000K), size(White_3000K),  MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*2*/
    // // // {arry(White_2700K), size(White_2700K),  MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*3*/
    // // // {arry(Vitality),    size(Vitality),     MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*4*/
    {arry(Spring),      size(Spring),       MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*5*/
    {arry(Summer),      size(Summer),       MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*6*/
    {arry(Autumn),      size(Autumn),       MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*7*/
    {arry(Winter),      size(Winter),       MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*8*/
    {arry(Cyberpunk),   size(Cyberpunk),    MOTION_STATIC, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*9*/

    {arry(Deep_Breath), size(Deep_Breath),  MOTION_BREATH, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*10*/
    {arry(Sweet),       size(Sweet),        MOTION_BREATH, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*11*/
    {arry(Romantic),    size(Romantic),     MOTION_STREAM, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*12*/
    {arry(Aurora),      size(Aurora),       MOTION_REVERB, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*13*/
    {arry(Ocean),       size(Ocean),        MOTION_REVERB, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*14*/
    {arry(lightning),   size(lightning),    MOTION_LIGHTN, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*15*/
    {arry(fireworks),   size(fireworks),    MOTION_IGNITE, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*16*/
    {arry(Snake),       size(Snake),        MOTION_STREAM, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*17*/
    {arry(BouncyBall),  size(BouncyBall),   MOTION_REVERB, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*18*/
    {arry(Lightsaber),  size(Lightsaber),   MOTION_IGNITE, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*19*/
    {arry(Thanksgiving),size(Thanksgiving), MOTION_REVERB, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*20*/
    {arry(Halloween),   size(Halloween),    MOTION_IGNITE, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*21*/
    {arry(Christmas),   size(Christmas),    MOTION_HOPSCO, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*22*/
    {arry(Colorful),    size(Colorful),     MOTION_RANDOM, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*23*/
    {arry(Kaleidoscope),size(Kaleidoscope), MOTION_RANDOM, MOVE_RIGHT, MODE_NORMAL, speed(5)},/*24*/

    {arry(Rhythm),      size(Rhythm),       MOTION_RANDOM, MOVE_RIGHT, MODE_RHYTHM, speed(5)},/*25*/
    {arry(Meditation),  size(Meditation),   MOTION_BREATH, MOVE_RIGHT, MODE_RHYTHM, speed(5)},/*26*/
    {arry(GamingTime),  size(GamingTime),   MOTION_LIGHTN, MOVE_RIGHT, MODE_RHYTHM, speed(5)},/*27*/
    {arry(Disco),       size(Disco),        MOTION_REVERB, MOVE_RIGHT, MODE_RHYTHM, speed(5)},/*28*/
    {arry(DanceParty),  size(DanceParty),   MOTION_RANDOM, MOVE_RIGHT, MODE_RHYTHM, speed(5)},/*29*/
};
