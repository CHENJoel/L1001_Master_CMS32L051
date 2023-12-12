
#include "Color.H"


ModuleTypeDef Tangram[32];
// ColorTypeDef L1, L2, L3, L4, L5, L6, L7, L8, L9, L10, L11, L12, L13, L14, L15, L16; // 共16块七巧板

// // // // void Color_Calculate(ColorTypeDef *light)
// // // // {                                                      // 一个像素组成一帧信息
// // // //     unsigned char Currnt_KF;                           // 当前关键帧（keyframe）编号
// // // //     unsigned char Next_KF;                             // 下个关键帧（keyframe）编号
// // // //     unsigned char Temp_FrameNum;                       // 临时帧编号，换算为当前帧（frame）处于当前关键帧（keyframe）至下一关键帧（keyframe）的之间的帧编号
// // // //     Currnt_KF = (*light).Frame_Now / Frame_In_Num;     // 计算当前帧 已经过的 最近/当前 关键帧
// // // //     Temp_FrameNum = (*light).Frame_Now % Frame_In_Num; //
// // // //     Next_KF = Currnt_KF + 1;                           // 计算当前帧 准备经过的 下一关键帧
// // // //     if (Next_KF >= Imgae_KF_Num)
// // // //     {
// // // //         Next_KF = 0; // 切回数组的第一个关键帧
// // // //     }
// // // //     FrameInsert_Calculate(*(FrameArry_Add + Currnt_KF * 3 + 0), *(FrameArry_Add + Next_KF * 3 + 0), &(*light).R.Target, Temp_FrameNum, Frame_In_Num);
// // // //     FrameInsert_Calculate(*(FrameArry_Add + Currnt_KF * 3 + 1), *(FrameArry_Add + Next_KF * 3 + 1), &(*light).G.Target, Temp_FrameNum, Frame_In_Num);
// // // //     FrameInsert_Calculate(*(FrameArry_Add + Currnt_KF * 3 + 2), *(FrameArry_Add + Next_KF * 3 + 2), &(*light).B.Target, Temp_FrameNum, Frame_In_Num);
// // // // }


// void Color_Calculate(ColorTypeDef *light,unsigned char *Frame_addr,unsigned char InsertNum)
// {                                                      // 一个像素组成一帧信息
//     unsigned char Currnt_KF;                           // 当前关键帧（keyframe）编号
//     unsigned char Next_KF;                             // 下个关键帧（keyframe）编号
//     unsigned char Temp_FrameNum;                       // 临时帧编号，换算为当前帧（frame）处于当前关键帧（keyframe）至下一关键帧（keyframe）的之间的帧编号
//     Currnt_KF = (*light).Frame_Now / InsertNum;     // 计算当前帧 已经过的 最近/当前 关键帧
//     Temp_FrameNum = (*light).Frame_Now % InsertNum; //
//     Next_KF = Currnt_KF + 1;                           // 计算当前帧 准备经过的 下一关键帧
//     if (Next_KF >= Imgae_KF_Num)
//     {
//         Next_KF = 0; // 切回数组的第一个关键帧
//     }
//     FrameInsert_Calculate(*(Frame_addr + Currnt_KF * 3 + 0), *(Frame_addr + Next_KF * 3 + 0), &(*light).R.Target, Temp_FrameNum, InsertNum);
//     FrameInsert_Calculate(*(Frame_addr + Currnt_KF * 3 + 1), *(Frame_addr + Next_KF * 3 + 1), &(*light).G.Target, Temp_FrameNum, InsertNum);
//     FrameInsert_Calculate(*(Frame_addr + Currnt_KF * 3 + 2), *(Frame_addr + Next_KF * 3 + 2), &(*light).B.Target, Temp_FrameNum, InsertNum);
// }
/*
// void Color_Calculate(ColorTypeDef *light, unsigned char *Frame_addr, unsigned char *Frame_data)
// {
// #define KF_num Frame_data[0]                         // 关键帧总数量 （1~255）KeyFrames
// #define insert_num Frame_data[2]                     // 自动补帧数量（关键帧之间）Insert Frames
//                                                      // 一个像素组成一帧信息
//     unsigned char Currnt_KF;                         // 当前关键帧（keyframe）编号
//     unsigned char Next_KF;                           // 下个关键帧（keyframe）编号
//     unsigned char Temp_FrameNum;                     // 临时帧编号，换算为当前帧（frame）处于当前关键帧（keyframe）至下一关键帧（keyframe）的之间的帧编号
//     Currnt_KF = (*light).Frame_Now / insert_num;     // 计算当前帧 已经过的 最近/当前 关键帧
//     Temp_FrameNum = (*light).Frame_Now % insert_num; //
//     Next_KF = Currnt_KF + 1;                         // 计算当前帧 准备经过的 下一关键帧
//     if (Next_KF >= KF_num)
//     {
//         Next_KF = 0; // 切回数组的第一个关键帧
//     }
//     FrameInsert_Calculate(*(Frame_addr + Currnt_KF * 3 + 0), *(Frame_addr + Next_KF * 3 + 0), &(*light).R.Target, Temp_FrameNum, insert_num);
//     FrameInsert_Calculate(*(Frame_addr + Currnt_KF * 3 + 1), *(Frame_addr + Next_KF * 3 + 1), &(*light).G.Target, Temp_FrameNum, insert_num);
//     FrameInsert_Calculate(*(Frame_addr + Currnt_KF * 3 + 2), *(Frame_addr + Next_KF * 3 + 2), &(*light).B.Target, Temp_FrameNum, insert_num);

//     // printf("%d %d %d %d %d\n", (*light).Frame_Now,Currnt_KF,Next_KF,KF_num,insert_num);
//     // printf("%d %d %d %d %d\n", (*light).Frame_Now,Currnt_KF,Next_KF,Frame_addr[1],*(Frame_addr + Currnt_KF * 3));
//     // printf("%d %d %d %d %d\n", (*light).Frame_Now,Currnt_KF,Next_KF,*(Frame_addr + Currnt_KF * 3 + 0),*(Frame_addr + Next_KF * 3 + 0));
// }
*/

// // // // // /**
// // // // //  * @description:计算该像素点内的帧颜色信息
// // // // //  * @param {ColorTypeDef} *light     像素点的结构体
// // // // //  * @param {unsigned char} *KF_Adr   帧信息的数组地址
// // // // //  * @param {unsigned char} Pixel_Num 像素点的序号 0~255
// // // // //  * @return {*}
// // // // //  */
// // // // // void Pixel_Calculate(ColorTypeDef *light, unsigned char *KF_Adr, unsigned char Pixel_Num)
// // // // // {                                                            // 一个像素组成一帧信息
// // // // //     unsigned char Currnt_KF;                                 // 当前关键帧（keyframe）编号
// // // // //     unsigned char Next_KF;                                   // 下个关键帧（keyframe）编号
// // // // //     unsigned char Temp_FrameNum;                             // 临时帧编号，换算为当前帧（frame）处于当前关键帧（keyframe）至下一关键帧（keyframe）的之间的帧编号
// // // // //     Currnt_KF = (*light).Frame_Now / (Frame_In_Num + 1);     // 计算当前帧 已经过的 最近/当前 关键帧
// // // // //     Temp_FrameNum = (*light).Frame_Now % (Frame_In_Num + 1); //
// // // // //     Next_KF = Currnt_KF + 1;                                 // 计算当前帧 准备经过的 下一关键帧
// // // // //     if (Next_KF >= Imgae_KF_Num)
// // // // //     {
// // // // //         Next_KF = 0; // 切回数组的第一个关键帧
// // // // //     }
// // // // //     FrameInsert_Calculate(*(KF_Adr + (Currnt_KF * 3 * Frame_Px_Num) + (Pixel_Num * 3) + 0), *(KF_Adr + (Next_KF * 3 * Frame_Px_Num) + (Pixel_Num * 3) + 0), &(*light).R.Target, Temp_FrameNum, Frame_In_Num);
// // // // //     FrameInsert_Calculate(*(KF_Adr + (Currnt_KF * 3 * Frame_Px_Num) + (Pixel_Num * 3) + 1), *(KF_Adr + (Next_KF * 3 * Frame_Px_Num) + (Pixel_Num * 3) + 1), &(*light).G.Target, Temp_FrameNum, Frame_In_Num);
// // // // //     FrameInsert_Calculate(*(KF_Adr + (Currnt_KF * 3 * Frame_Px_Num) + (Pixel_Num * 3) + 2), *(KF_Adr + (Next_KF * 3 * Frame_Px_Num) + (Pixel_Num * 3) + 2), &(*light).B.Target, Temp_FrameNum, Frame_In_Num);
// // // // // }
// // // // // */

/**
 * @description:计算该像素点内的帧颜色信息
 * @param {ColorTypeDef} *light     像素点的结构体
 * @param {unsigned char} *KF_Adr   帧信息的数组地址
 * @param {unsigned char} Pixel_Num 像素点的序号 0~255
 * @return {*}
 */
void Pixel_Cal(ModuleTypeDef *struct_adr, uint8_t *KF_Adr, uint8_t Pixel_Num)
{                                                               // 一个像素组成一帧信息
    uint8_t Currnt_KF;                                          // 当前关键帧（keyframe）编号
    uint8_t Next_KF;                                            // 下个关键帧（keyframe）编号
    uint8_t Temp_FrameNum;                                      // 临时帧编号，换算为当前帧（frame）处于当前关键帧（keyframe）至下一关键帧（keyframe）的之间的帧编号
    Currnt_KF = struct_adr->Frame_Now / (Frame_In_Num + 1);     // 计算当前帧 已经过的 最近/当前 关键帧
    Temp_FrameNum = struct_adr->Frame_Now % (Frame_In_Num + 1); //
    Next_KF = Currnt_KF + 1;                                    // 计算当前帧 准备经过的 下一关键帧
    if (Next_KF >= Imgae_KF_Num)
    {
        Next_KF = 0; // 切回数组的第一个关键帧
    }
    FrameInsert_Calculate(*(KF_Adr + (Currnt_KF * 4 * Frame_Px_Num) + (Pixel_Num * 4) + 0), *(KF_Adr + (Next_KF * 4 * Frame_Px_Num) + (Pixel_Num * 4) + 0), &struct_adr->R, Temp_FrameNum, Frame_In_Num);
    FrameInsert_Calculate(*(KF_Adr + (Currnt_KF * 4 * Frame_Px_Num) + (Pixel_Num * 4) + 1), *(KF_Adr + (Next_KF * 4 * Frame_Px_Num) + (Pixel_Num * 4) + 1), &struct_adr->G, Temp_FrameNum, Frame_In_Num);
    FrameInsert_Calculate(*(KF_Adr + (Currnt_KF * 4 * Frame_Px_Num) + (Pixel_Num * 4) + 2), *(KF_Adr + (Next_KF * 4 * Frame_Px_Num) + (Pixel_Num * 4) + 2), &struct_adr->B, Temp_FrameNum, Frame_In_Num);
    FrameInsert_Calculate(*(KF_Adr + (Currnt_KF * 4 * Frame_Px_Num) + (Pixel_Num * 4) + 3), *(KF_Adr + (Next_KF * 4 * Frame_Px_Num) + (Pixel_Num * 4) + 3), &struct_adr->W, Temp_FrameNum, Frame_In_Num);
}

void ImagePixel_Cal(ImageTypeDef *image_ptr, ModuleTypeDef *module_ptr, uint8_t Pixel_Num)
{
    uint8_t Currnt_KF;                                                  // 当前关键帧（keyframe）编号
    uint8_t Next_KF;                                                    // 下个关键帧（keyframe）编号
    uint8_t Temp_FrameNum;                                              // 临时帧编号，换算为当前帧（frame）处于当前关键帧（keyframe）至下一关键帧（keyframe）的之间的帧编号
    Currnt_KF = module_ptr->Frame_Now / ((image_ptr->InsertNum) + 1);     // 计算当前帧 已经过的 最近/当前 关键帧
    Temp_FrameNum = module_ptr->Frame_Now % ((image_ptr->InsertNum) + 1); //
    Next_KF = Currnt_KF + 1;                                            // 计算当前帧 准备经过的 下一关键帧
    if (Next_KF >= image_ptr->KeyFrameSum)
    {
        Next_KF = 0; // 切回数组的第一个关键帧
    }
    // // printf("%d %d %d %d \n\n",module_ptr->Frame_Now,Pixel_Num,Currnt_KF,Next_KF);
    // // FrameInsert_Calculate(*(image_ptr->image_adr + (Currnt_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 0), *(image_ptr->image_adr + (Next_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 0), &module_ptr->R, Temp_FrameNum, image_ptr->InsertNum);
    // // FrameInsert_Calculate(*(image_ptr->image_adr + (Currnt_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 1), *(image_ptr->image_adr + (Next_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 1), &module_ptr->G, Temp_FrameNum, image_ptr->InsertNum);
    // // FrameInsert_Calculate(*(image_ptr->image_adr + (Currnt_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 2), *(image_ptr->image_adr + (Next_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 2), &module_ptr->B, Temp_FrameNum, image_ptr->InsertNum);
    // // FrameInsert_Calculate(*(image_ptr->image_adr + (Currnt_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 3), *(image_ptr->image_adr + (Next_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 3), &module_ptr->W, Temp_FrameNum, image_ptr->InsertNum);


    FrameInsert_Calculate(*(image_ptr->image_adr + (Currnt_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 0), *(image_ptr->image_adr + (Next_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 0), &module_ptr->R.Now, Temp_FrameNum, image_ptr->InsertNum);
    FrameInsert_Calculate(*(image_ptr->image_adr + (Currnt_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 1), *(image_ptr->image_adr + (Next_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 1), &module_ptr->G.Now, Temp_FrameNum, image_ptr->InsertNum);
    FrameInsert_Calculate(*(image_ptr->image_adr + (Currnt_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 2), *(image_ptr->image_adr + (Next_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 2), &module_ptr->B.Now, Temp_FrameNum, image_ptr->InsertNum);
    FrameInsert_Calculate(*(image_ptr->image_adr + (Currnt_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 3), *(image_ptr->image_adr + (Next_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 3), &module_ptr->W.Now, Temp_FrameNum, image_ptr->InsertNum);
}

void StaticPixel_Cal(ImageTypeDef *image_ptr, ModuleTypeDef *module_ptr, uint8_t Pixel_Num)
{
    // // module_ptr->R = *(image_ptr->image_adr + (Pixel_Num * 4) + 0);
    // // module_ptr->G = *(image_ptr->image_adr + (Pixel_Num * 4) + 1);
    // // module_ptr->B = *(image_ptr->image_adr + (Pixel_Num * 4) + 2);
    // // module_ptr->W = *(image_ptr->image_adr + (Pixel_Num * 4) + 3);

    module_ptr->R.Now = *(image_ptr->image_adr + (Pixel_Num * 4) + 0);
    module_ptr->G.Now = *(image_ptr->image_adr + (Pixel_Num * 4) + 1);
    module_ptr->B.Now = *(image_ptr->image_adr + (Pixel_Num * 4) + 2);
    module_ptr->W.Now = *(image_ptr->image_adr + (Pixel_Num * 4) + 3);
}


/* 新灯效 */

// void

void ModuleColor_Cal(FrameInfro_TypeDef *image_ptr, ModuleTypeDef *module_ptr, uint8_t Pixel_Num)
{
    uint16_t Currnt_KF;                                                    // 当前关键帧（keyframe）编号
    uint16_t Next_KF;                                                      // 下个关键帧（keyframe）编号
    uint16_t Temp_FrameNum;                                                // 临时帧编号，换算为当前帧（frame）处于当前关键帧（keyframe）至下一关键帧（keyframe）的之间的帧编号
    Currnt_KF = module_ptr->Frame_Now / ((image_ptr->InsertNum) + 1);     // 计算当前帧 已经过的 最近/当前 关键帧
    Temp_FrameNum = module_ptr->Frame_Now % ((image_ptr->InsertNum) + 1); //
    Next_KF = Currnt_KF + 1;                                              // 计算当前帧 准备经过的 下一关键帧
    if (Next_KF >= image_ptr->KeySum)
    {
        Next_KF = 0; // 切回数组的第一个关键帧
    }
    /* 未删除PixelSum
    // FrameInsert_Calculate(*(image_ptr->image_adr + (Currnt_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 0), *(image_ptr->image_adr + (Next_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 0), &module_ptr->R.Now, Temp_FrameNum, image_ptr->InsertNum);
    // FrameInsert_Calculate(*(image_ptr->image_adr + (Currnt_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 1), *(image_ptr->image_adr + (Next_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 1), &module_ptr->G.Now, Temp_FrameNum, image_ptr->InsertNum);
    // FrameInsert_Calculate(*(image_ptr->image_adr + (Currnt_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 2), *(image_ptr->image_adr + (Next_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 2), &module_ptr->B.Now, Temp_FrameNum, image_ptr->InsertNum);
    // FrameInsert_Calculate(*(image_ptr->image_adr + (Currnt_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 3), *(image_ptr->image_adr + (Next_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 3), &module_ptr->W.Now, Temp_FrameNum, image_ptr->InsertNum);
    */

    FrameInsert_Calculate(*(image_ptr->image_adr + (Currnt_KF * 4) + (Pixel_Num * 4) + 0), *(image_ptr->image_adr + (Next_KF * 4) + (Pixel_Num * 4) + 0), &module_ptr->R.Now, Temp_FrameNum, image_ptr->InsertNum);
    FrameInsert_Calculate(*(image_ptr->image_adr + (Currnt_KF * 4) + (Pixel_Num * 4) + 1), *(image_ptr->image_adr + (Next_KF * 4) + (Pixel_Num * 4) + 1), &module_ptr->G.Now, Temp_FrameNum, image_ptr->InsertNum);
    FrameInsert_Calculate(*(image_ptr->image_adr + (Currnt_KF * 4) + (Pixel_Num * 4) + 2), *(image_ptr->image_adr + (Next_KF * 4) + (Pixel_Num * 4) + 2), &module_ptr->B.Now, Temp_FrameNum, image_ptr->InsertNum);
    // // // module_ptr->W.Now=*(image_ptr->image_adr + (Currnt_KF * 4));    // 颜色类型标志位
    /*
    FrameInsert_Calculate(*(image_ptr->image_adr + (Currnt_KF * 4) + (Pixel_Num * 4) + 3), *(image_ptr->image_adr + (Next_KF * 4) + (Pixel_Num * 4) + 3), &module_ptr->W.Now, Temp_FrameNum, image_ptr->InsertNum);
    */

    // // // printf("C:%2d N:%2d ,%d\r",Currnt_KF,Next_KF,*(image_ptr->image_adr + (Currnt_KF * 4 * image_ptr->PixelSum) + (Pixel_Num * 4) + 0));
    // // printf("C:%2d N:%2d K:%2d I:%4d tf:%d\r", Currnt_KF, Next_KF, image_ptr->KeySum, image_ptr->InsertNum,Temp_FrameNum);
}

/**
 * @description: 灯效流动，即灯效进度+Speed
 * @param {ColorTypeDef} *light
 * @return {*}
 */
void Color_Flowing(ColorTypeDef *light, unsigned char Speed)
{
    unsigned int Temp;
    Temp = (*light).Frame_Now + Speed;
    (*light).Frame_Now = Temp % Frame_All_Sum;
}

/**
 * @description:将灯效与基准灯效进行相位偏移
 * @param {ColorTypeDef} *light     相位偏移后的颜色进度
 * @param {ColorTypeDef} *lightBase 基准颜色进度
 * @param {unsigned int} Skewing    相位偏移度
 * @return {*}
 */
void Color_Skewing(ColorTypeDef *light, ColorTypeDef *lightBase, unsigned int Skewing)
{
    unsigned int Temp;
    if (Skewing)
    {
        Temp = (*lightBase).Frame_Now + Skewing;
        (*light).Frame_Now = Temp % Frame_All_Sum;
    }
    else
    {
        (*light).Frame_Now = (*lightBase).Frame_Now;
    }
}

/**
 * @description:帧偏移
 * @param {uint16_t} total_num 帧总数
 * @param {uint16_t} *dst_adr  目标帧编号
 * @param {uint16_t} *src_adr  源头帧编号
 * @param {uint16_t} offset    帧偏移量
 * @return {*}
 */
void Frame_Skewing(uint16_t total_num, uint16_t *dst_adr,uint16_t *src_adr,uint16_t offset)
{
    uint32_t Temp;
    if (offset)
    {
        Temp = *src_adr + offset;
        *dst_adr = Temp % total_num;
    }
    else
    {
        *dst_adr = *src_adr;
    }
}



/**
 * @description:  颜色直接转变，无需渐变
 * @param {ColorTypeDef} *light
 * @return {*}
 */
void Color_DirectChange(ColorTypeDef *light)
{
    (*light).R.Now = (*light).R.Target;
    (*light).G.Now = (*light).G.Target;
    (*light).B.Now = (*light).B.Target;
}

/**
 * @description:插帧计算（单色），自动计算出关键帧之间的过度帧信息
 * @param {unsigned char} Current_KF_data   当前关键帧信息.输入
 * @param {unsigned char} Next_KF_data      下一关键帧信息.输入
 * @param {unsigned char} *Target           目标帧信息.输出
 * @param {unsigned char} Insert_Num        过渡帧编号： 0 ~ Insert_Sum
 * @param {unsigned char} Insert_Sum        插帧数量： 0 ~ 255
 * @return {*}
 */

void FrameInsert_Calculate(unsigned char Current_KF_data, unsigned char Next_KF_data, unsigned char *Target, uint16_t Insert_Num, uint16_t Insert_Sum)
{
    uint32_t temp;
    uint32_t tempDiff;
    if (Insert_Sum == 0) // 插帧数为0，即不插帧
    {
        *Target = Current_KF_data;
    }
    else
    {
        if (Current_KF_data < Next_KF_data)
        {
            tempDiff = Next_KF_data - Current_KF_data; // 关键帧的数据差值
            temp = tempDiff * Insert_Num;              // 先乘法
            temp = temp / (Insert_Sum + 1);            // 后除法 避免浮点运算

            if (temp > Next_KF_data) // 防止数据溢出
            {
                temp = Next_KF_data;
            }
            *Target = Current_KF_data + temp; //正增长
        }
        else if (Current_KF_data > Next_KF_data)
        {
            tempDiff = Current_KF_data - Next_KF_data; // 差值
            temp = tempDiff * Insert_Num;              // 先乘法
            temp = temp / (Insert_Sum + 1);            // 后除法 避免浮点运算

            if (temp > Current_KF_data) // 防止数据溢出
            {
                temp = Current_KF_data;
            }
            *Target = Current_KF_data - temp; //正增长
        }
        else
        {
            *Target = Current_KF_data;
        }
    }
}

/**
 * @description:
 * @param {unsigned char} Address
 * @param {ColorTypeDef} *light
 * @return {*}
 */
// // void Color_Data_Send(unsigned char Address, ColorTypeDef *light)
// void Color_Data_Send(ColorTypeDef *light, unsigned char Address)
// {
//     Data_TX(Address, SYS.Brightness.Now, (*light).R.Now, (*light).G.Now, (*light).B.Now, 0);
// }

void Demo_Flowing(ColorTypeDef *light, unsigned int va1, unsigned int va2)
{
    // // static unsigned int Temp;
    // // // // if (++Temp > 48)
    // // // // {
    // // // //     Temp = 0;
    // // // // }
    // // // // (*light).Frame_Now = Temp;

    // // // Temp=va1/42;
    // // // (*light).Frame_Now = 48;
    (*light).Frame_Now = va1 / 2;
    // (*light).Frame_Now = va1;
    // (*light).Frame_Now ++;
    if ((*light).Frame_Now > (Frame_All_Sum / 2))
    {
        // (*light).Frame_Now=0;
        (*light).Frame_Now = (Frame_All_Sum / 2);
    }

    // // // Temp = (*light).Frame_Now + Speed;
    // // // (*light).Frame_Now = Temp % Frame_All_Sum;
    // // // (*light).Frame_Now = Frame_All_Sum /2;
    // printf("A%d\r\n", (*light).Frame_Now);
    // printf("B%d\r\n\r\n", Frame_All_Sum);
}

void CMD_Send(void)
{
    /*
    帧头
    命令

    校验
    帧尾
    */
}


/***********************************************************************



**********************************************************************/
void Module_Gradual_Change(ModuleTypeDef *modele_adr)
{
    // Gradual_Change(&modele_adr->R.Now, &modele_adr->R.Target, modele_adr->Speed);
    // Gradual_Change(&modele_adr->G.Now, &modele_adr->G.Target, modele_adr->Speed);
    // Gradual_Change(&modele_adr->B.Now, &modele_adr->B.Target, modele_adr->Speed);
    // Gradual_Change(&modele_adr->W.Now, &modele_adr->W.Target, modele_adr->Speed);

    Gradual_Change(&modele_adr->R.Now, &modele_adr->R.Target, 10);
    Gradual_Change(&modele_adr->G.Now, &modele_adr->G.Target, 10);
    Gradual_Change(&modele_adr->B.Now, &modele_adr->B.Target, 10);
    Gradual_Change(&modele_adr->W.Now, &modele_adr->W.Target, 10);
}

void Model_Gradual_Change(ModuleTypeDef *modele_adr)
{
    if (modele_adr->Model.Task_Flag)
    {
        modele_adr->R.Target = modele_adr->Model.Blink.R;
        modele_adr->G.Target = modele_adr->Model.Blink.G;
        modele_adr->B.Target = modele_adr->Model.Blink.B;
        modele_adr->W.Target = modele_adr->Model.Blink.W;
    }
    else
    {
        modele_adr->R.Target = modele_adr->Model.Normal.R;
        modele_adr->G.Target = modele_adr->Model.Normal.G;
        modele_adr->B.Target = modele_adr->Model.Normal.B;
        modele_adr->W.Target = modele_adr->Model.Normal.W;
    }
    Gradual_Change(&modele_adr->R.Now, &modele_adr->R.Target, 10);
    Gradual_Change(&modele_adr->G.Now, &modele_adr->G.Target, 10);
    Gradual_Change(&modele_adr->B.Now, &modele_adr->B.Target, 10);
    Gradual_Change(&modele_adr->W.Now, &modele_adr->W.Target, 10);
    if (modele_adr->R.Now == modele_adr->R.Target)
    {
        if (modele_adr->G.Now == modele_adr->G.Target)
        {
            if (modele_adr->B.Now == modele_adr->B.Target)
            {
                if (modele_adr->W.Now == modele_adr->W.Target)
                {
                    modele_adr->Model.Task_Flag = 0; // 颜色完成转换，任务完成
                }
            }
        }
    }
}

void Module_ColorInsert(ModuleTypeDef *modele_adr, uint8_t *colortable_adr)
{
    modele_adr->R.Target = *(colortable_adr + 0);
    modele_adr->G.Target = *(colortable_adr + 1);
    modele_adr->B.Target = *(colortable_adr + 2);
    modele_adr->W.Target = *(colortable_adr + 3);
    // printf("R:%d G:%d B:%d W:%d \n\n",modele_adr->R.Target,modele_adr->G.Target,modele_adr->B.Target,modele_adr->W.Target);
}

void Random_ColorTrigger(uint8_t modele_maxnum)
{
    // uint8_t i, j;
    // uint8_t temp_array[modele_maxnum][2];
    // for ( i = 0; i < modele_maxnum; i++)
    // {
    //     temp_array[i][0]=i;
    //     temp_array[i][1]=Tangram[i].Priority;
    // }
    // Bubble_Sort_2D(&temp_array, modele_maxnum, 2, 1);

    // j = get_random_number() % modele_maxnum;
    // j = j / 2;

    // i = temp_array[j][0];

    // j = get_random_number() % (sizeof(Random_ColorTable) / 4);

    // Module_ColorInsert(&Tangram[i], &Random_ColorTable[j][0]);
    // j = i;
    // for (i = 0; i < modele_maxnum; i++)
    // {
    //     if (Tangram[i].Priority > 0)
    //     {
    //         Tangram[i].Priority--;
    //     }
    // }
    // Tangram[j].Priority = modele_maxnum;
}

void Priority_Calculate(ModuleTypeDef *modele_adr)
{
    uint8_t r_cha, g_cha, b_cha, w_cha;
    uint8_t max = 0;

    if (modele_adr->Model.Task_Flag)
    {
        modele_adr->Model.Priority = 255;
    }
    else
    {
        if (modele_adr->R.Target > modele_adr->R.Now)
        {
            r_cha = modele_adr->R.Target - modele_adr->R.Now;
        }
        else
        {
            r_cha = modele_adr->R.Now - modele_adr->R.Target;
        }

        if (modele_adr->G.Target > modele_adr->G.Now)
        {
            g_cha = modele_adr->G.Target - modele_adr->G.Now;
        }
        else
        {
            g_cha = modele_adr->G.Now - modele_adr->G.Target;
        }

        if (modele_adr->B.Target > modele_adr->B.Now)
        {
            b_cha = modele_adr->B.Target - modele_adr->B.Now;
        }
        else
        {
            b_cha = modele_adr->B.Now - modele_adr->B.Target;
        }

        if (modele_adr->W.Target > modele_adr->W.Now)
        {
            w_cha = modele_adr->W.Target - modele_adr->W.Now;
        }
        else
        {
            w_cha = modele_adr->W.Now - modele_adr->W.Target;
        }

        if (max < r_cha)
        {
            max = r_cha;
        }
        if (max < g_cha)
        {
            max = g_cha;
        }
        if (max < b_cha)
        {
            max = b_cha;
        }
        if (max < w_cha)
        {
            max = w_cha;
        }

        modele_adr->Model.Priority = max;
    }
}

void ColorTrigger(uint8_t modele_maxnum)
{
    uint8_t i, j;
    uint8_t temp_array[modele_maxnum][2];
    uint8_t temp;
    for (i = 0; i < modele_maxnum; i++)
    {
        Priority_Calculate(&Tangram[i]); // 与目标值对比，进行优先级评分
        // printf("[%d]:%d\n",i,Tangram[i].Model.Priority);
    }

    for (i = 0; i < modele_maxnum; i++)
    {
        temp_array[i][0] = i;
        temp_array[i][1] = Tangram[i].Model.Priority;
    }
    Bubble_Sort_2D(&temp_array, modele_maxnum, 2, 1); // 根据优先级进行排序

    temp = 0;
    for (i = 0; i < modele_maxnum; i++)
    {
        if (temp_array[i][1] != 0)
        {
            temp = 1;
            break;
        }
    }
    if (temp)
    {
        i = temp_array[0][0]; // 优先级最高的模组进行换色
    }
    else
    {
        i = get_random_number() % modele_maxnum; // 若全部优先级一致，则随机选一个
    }

    j = get_random_number() % (sizeof(Random_ColorTable) / 4); // 取色
    // printf("i=%d,j=%d\r\n",i,j);
    Tangram[i].Model.Blink.R = Random_ColorTable[j][0]; // 赋色
    Tangram[i].Model.Blink.G = Random_ColorTable[j][1]; // 赋色
    Tangram[i].Model.Blink.B = Random_ColorTable[j][2]; // 赋色
    Tangram[i].Model.Blink.W = Random_ColorTable[j][3]; // 赋色
    Tangram[i].Model.Task_Flag = 1;                     // 创建变色任务
}
