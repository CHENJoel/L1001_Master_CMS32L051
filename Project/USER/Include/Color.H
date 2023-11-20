/*
 * @Author: your name
 * @Date: 2021-12-31 11:54:33
 * @LastEditTime: 2023-11-03 14:46:14
 * @LastEditors: DESKTOP-AKTRQKB\MY sandote@163.com
.chen sandote@163.om
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \L1001_Master_CMS32L051\Project\USER\Include\Color.H
 */
#ifndef _COLOR_H_
#define _COLOR_H_
#include "Function_Init.H"


// // // extern unsigned char Brightness; // 灯组亮度

#define MAX_E_Type  10   //灯效类型总数量
// #define MAX_E_Color 8   //单项等效类型的颜色数量



typedef struct
{
    uint8_t Now;
    uint8_t Target;
} DataTypeDef;

typedef struct
{
	DataTypeDef R;
	DataTypeDef G;
	DataTypeDef B;
    DataTypeDef W;
    unsigned int Frame_Now;    // 当前帧
}ColorTypeDef;

typedef struct
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t W;
} RGBWTypeDef;




typedef struct
{
    // // // // RGBWTypeDef Present; // 当前值
    RGBWTypeDef Blink;  // 暂态值
    RGBWTypeDef Normal; // 常态值
    uint8_t Priority;   // 优先级
    // uint8_t Progress;   // 进度 0(缓冲期)/1(爬升)
    uint8_t Speed;      // 渐变速度
    uint8_t Task_Flag;  // 任务标志
} ModelTypeDef;         // 律动模式

typedef struct
{
    DataTypeDef R;
    DataTypeDef G;
    DataTypeDef B;
    DataTypeDef W;
    // // // // // uint8_t addr;
    ModelTypeDef Model;
    uint16_t Frame_Now; // 当前帧
} ModuleTypeDef;

extern ModuleTypeDef Tangram[32];   // 模组


// extern ModelTypeDef Model[16];   // 模型（律动）

// extern ColorTypeDef L1,L2, L3, L4, L5, L6, L7, L8, L9, L10, L11, L12, L13, L14, L15, L16; // 共16块七巧板

void Pixel_Calculate(ColorTypeDef *light, unsigned char *KF_Adr,unsigned char Pixel_Num);

void Color_GradualChange(ColorTypeDef *light);
void Color_DirectChange(ColorTypeDef *light);
void Gradual_Calculation(unsigned char *Value_Now, unsigned char *Value_Target, unsigned char Speed);
void Float_Calculation(unsigned char Data1, unsigned char Data2, unsigned char *ColorVal, unsigned char Beat);
// void Color_Calculate(ColorTypeDef *light);
// void Color_Calculate(ColorTypeDef *light,unsigned char *Frame_addr,unsigned char InsertNum);
void Color_Calculate(ColorTypeDef *light,unsigned char *Frame_addr,unsigned char *Frame_data);
// // void Color_Calculate(unsigned char *ColorArray[][3],ColorTypeDef *light);
// // // void FrameInsert_Calculate(unsigned char Data1, unsigned char Data2, unsigned char *ColorVal, unsigned char Beat,unsigned char BeatSum);
void FrameInsert_Calculate(unsigned char Current_KF_data, unsigned char Next_KF_data, unsigned char *Target, unsigned char Insert_Num, unsigned char Insert_Sum);
// // // // void Color_RGBW_Flowing();
void Color_Flowing(ColorTypeDef *light,unsigned char Speed);
void Color_Skewing(ColorTypeDef *light,ColorTypeDef *lightBase,unsigned int Skewing);

// void Color_Data_Send(unsigned char Address, ColorTypeDef *light);

void Color_Data_Send(ColorTypeDef *light,unsigned char Address);

void Demo_Flowing(ColorTypeDef *light, unsigned int va1,unsigned int va2);


void Frame_Skewing(uint16_t total_num, uint16_t *dst_adr,uint16_t *src_adr,uint16_t offset);
void Pixel_Cal(ModuleTypeDef *struct_adr, uint8_t *KF_Adr, uint8_t Pixel_Num);
void ImagePixel_Cal(ImageTypeDef *image_ptr, ModuleTypeDef *module_ptr, uint8_t Pixel_Num);
void StaticPixel_Cal(ImageTypeDef *image_ptr, ModuleTypeDef *module_ptr, uint8_t Pixel_Num);

void Module_Gradual_Change(ModuleTypeDef *modele_adr);
void Model_Gradual_Change(ModuleTypeDef *modele_adr);   // 律动渐变
void Module_ColorInsert(ModuleTypeDef *modele_adr, uint8_t *colortable_adr);
void Random_ColorTrigger(uint8_t modele_maxnum);
/***********************************************************************************/



/* 新灯效 */

void ModuleColor_Cal(FrameInfro_TypeDef *image_ptr, ModuleTypeDef *module_ptr, uint8_t Pixel_Num);





#endif
