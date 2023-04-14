
// // // // // void Frame_Working(void)
// // // // // {
// // // // //     static uint16_t Time_Cnt;


// // // // //     // if (++Time_Cnt >= Frame_Time_N)
// // // // //      if (++Time_Cnt >= ImageData[EffextImage_num].IntervalTime)
// // // // //     {
// // // // //         Time_Cnt = 0;
// // // // //         LED3_REV();
// // // // //         // if (Frame_Px_Num == 1) // µã³ÉÏñ


// // // // //         if (ImageData[EffextImage_num].PixelSum==1)
// // // // //         {
// // // // //             //



// // // // //             // // Frame_Skewing(FrameSum, &Tangram.MO1.Frame_Now, &Tangram.MO1.Frame_Now, 1);
// // // // //             // // Frame_Skewing(FrameSum, &Tangram.MO2.Frame_Now, &Tangram.MO1.Frame_Now, ImageData[EffextImage_num].Para_1);
// // // // //             // // Frame_Skewing(FrameSum, &Tangram.MO3.Frame_Now, &Tangram.MO2.Frame_Now, ImageData[EffextImage_num].Para_1);
// // // // //             // // Frame_Skewing(FrameSum, &Tangram.MO4.Frame_Now, &Tangram.MO3.Frame_Now, ImageData[EffextImage_num].Para_1);

// // // // //             // // Frame_Skewing(FrameSum, &Tangram.MO5.Frame_Now, &Tangram.MO4.Frame_Now, ImageData[EffextImage_num].Para_1);
// // // // //             // // Frame_Skewing(FrameSum, &Tangram.MO6.Frame_Now, &Tangram.MO5.Frame_Now, ImageData[EffextImage_num].Para_1);
// // // // //             // // Frame_Skewing(FrameSum, &Tangram.MO7.Frame_Now, &Tangram.MO6.Frame_Now, ImageData[EffextImage_num].Para_1);
// // // // //             // // Frame_Skewing(FrameSum, &Tangram.MO8.Frame_Now, &Tangram.MO7.Frame_Now, ImageData[EffextImage_num].Para_1);

// // // // //             // // Frame_Skewing(FrameSum, &Tangram.MO9.Frame_Now, &Tangram.MO8.Frame_Now, ImageData[EffextImage_num].Para_1);
// // // // //             // // Frame_Skewing(FrameSum, &Tangram.MO10.Frame_Now, &Tangram.MO9.Frame_Now, ImageData[EffextImage_num].Para_1);
// // // // //             // // Frame_Skewing(FrameSum, &Tangram.MO11.Frame_Now, &Tangram.MO10.Frame_Now, ImageData[EffextImage_num].Para_1);
// // // // //             // // Frame_Skewing(FrameSum, &Tangram.MO12.Frame_Now, &Tangram.MO11.Frame_Now, ImageData[EffextImage_num].Para_1);

// // // // //             // // Frame_Skewing(FrameSum, &Tangram.MO13.Frame_Now, &Tangram.MO12.Frame_Now, ImageData[EffextImage_num].Para_1);
// // // // //             // // Frame_Skewing(FrameSum, &Tangram.MO14.Frame_Now, &Tangram.MO13.Frame_Now, ImageData[EffextImage_num].Para_1);
// // // // //             // // Frame_Skewing(FrameSum, &Tangram.MO15.Frame_Now, &Tangram.MO14.Frame_Now, ImageData[EffextImage_num].Para_1);
// // // // //             // // Frame_Skewing(FrameSum, &Tangram.MO16.Frame_Now, &Tangram.MO15.Frame_Now, ImageData[EffextImage_num].Para_1);

// // // // //             // // ImagePixel_Cal(&ImageData[EffextImage_num],&Tangram.MO1,0);
// // // // //             // // printf("%d %d %d %d\n",Tangram.MO1.R,Tangram.MO1.G,Tangram.MO1.B,Tangram.MO1.W);
// // // // //                     // Tangram.MO1.R = 0;
// // // // //         // Tangram.MO1.G = 255;
// // // // //         // Tangram.MO1.B = 0;
// // // // //         // Tangram.MO1.W = 0;
// // // // //             /***********************************************************************************/

// // // // //             // // // Frame_Skewing(Frame_All_Sum, &Tangram.MO1.Frame_Now, &Tangram.MO1.Frame_Now, 1);
// // // // //             // // // Frame_Skewing(Frame_All_Sum, &Tangram.MO2.Frame_Now, &Tangram.MO1.Frame_Now, Image_Para_1);
// // // // //             // // // Frame_Skewing(Frame_All_Sum, &Tangram.MO3.Frame_Now, &Tangram.MO2.Frame_Now, Image_Para_1);
// // // // //             // // // Frame_Skewing(Frame_All_Sum, &Tangram.MO4.Frame_Now, &Tangram.MO3.Frame_Now, Image_Para_1);

// // // // //             // // // Frame_Skewing(Frame_All_Sum, &Tangram.MO5.Frame_Now, &Tangram.MO4.Frame_Now, Image_Para_1);
// // // // //             // // // Frame_Skewing(Frame_All_Sum, &Tangram.MO6.Frame_Now, &Tangram.MO5.Frame_Now, Image_Para_1);
// // // // //             // // // Frame_Skewing(Frame_All_Sum, &Tangram.MO7.Frame_Now, &Tangram.MO6.Frame_Now, Image_Para_1);
// // // // //             // // // Frame_Skewing(Frame_All_Sum, &Tangram.MO8.Frame_Now, &Tangram.MO7.Frame_Now, Image_Para_1);

// // // // //             // // // Frame_Skewing(Frame_All_Sum, &Tangram.MO9.Frame_Now, &Tangram.MO8.Frame_Now, Image_Para_1);
// // // // //             // // // Frame_Skewing(Frame_All_Sum, &Tangram.MO10.Frame_Now, &Tangram.MO9.Frame_Now, Image_Para_1);
// // // // //             // // // Frame_Skewing(Frame_All_Sum, &Tangram.MO11.Frame_Now, &Tangram.MO10.Frame_Now, Image_Para_1);
// // // // //             // // // Frame_Skewing(Frame_All_Sum, &Tangram.MO12.Frame_Now, &Tangram.MO11.Frame_Now, Image_Para_1);

// // // // //             // // // Frame_Skewing(Frame_All_Sum, &Tangram.MO13.Frame_Now, &Tangram.MO12.Frame_Now, Image_Para_1);
// // // // //             // // // Frame_Skewing(Frame_All_Sum, &Tangram.MO14.Frame_Now, &Tangram.MO13.Frame_Now, Image_Para_1);
// // // // //             // // // Frame_Skewing(Frame_All_Sum, &Tangram.MO15.Frame_Now, &Tangram.MO14.Frame_Now, Image_Para_1);
// // // // //             // // // Frame_Skewing(Frame_All_Sum, &Tangram.MO16.Frame_Now, &Tangram.MO15.Frame_Now, Image_Para_1);

// // // // //             // // // Pixel_Cal(&Tangram.MO1, FrameArry_Add, 0);
// // // // //             // // // Pixel_Cal(&Tangram.MO2, FrameArry_Add, 0);
// // // // //             // // // Pixel_Cal(&Tangram.MO3, FrameArry_Add, 0);
// // // // //             // // // Pixel_Cal(&Tangram.MO4, FrameArry_Add, 0);

// // // // //             // // // Pixel_Cal(&Tangram.MO5, FrameArry_Add, 0);
// // // // //             // // // Pixel_Cal(&Tangram.MO6, FrameArry_Add, 0);
// // // // //             // // // Pixel_Cal(&Tangram.MO7, FrameArry_Add, 0);
// // // // //             // // // Pixel_Cal(&Tangram.MO8, FrameArry_Add, 0);

// // // // //             // // // Pixel_Cal(&Tangram.MO9, FrameArry_Add, 0);
// // // // //             // // // Pixel_Cal(&Tangram.MO10, FrameArry_Add, 0);
// // // // //             // // // Pixel_Cal(&Tangram.MO11, FrameArry_Add, 0);
// // // // //             // // // Pixel_Cal(&Tangram.MO12, FrameArry_Add, 0);

// // // // //             // // // Pixel_Cal(&Tangram.MO13, FrameArry_Add, 0);
// // // // //             // // // Pixel_Cal(&Tangram.MO14, FrameArry_Add, 0);
// // // // //             // // // Pixel_Cal(&Tangram.MO15, FrameArry_Add, 0);
// // // // //             // // // Pixel_Cal(&Tangram.MO16, FrameArry_Add, 0);

// // // // //             // printf("AllFrame: %d Frame: %d\n",Frame_All_Sum,Tangram.MO1.Frame_Now);
// // // // //             Tangram_Buffer_load();
// // // // //         }
// // // // //         else
// // // // //         {
// // // // //             Frame_Skewing(Frame_All_Sum, &Tangram.MO1.Frame_Now, &Tangram.MO1.Frame_Now, Image_Para_1);
// // // // //             Frame_Skewing(Frame_All_Sum, &Tangram.MO2.Frame_Now, &Tangram.MO2.Frame_Now, Image_Para_1);
// // // // //             Frame_Skewing(Frame_All_Sum, &Tangram.MO3.Frame_Now, &Tangram.MO3.Frame_Now, Image_Para_1);
// // // // //             Frame_Skewing(Frame_All_Sum, &Tangram.MO4.Frame_Now, &Tangram.MO4.Frame_Now, Image_Para_1);

// // // // //             Frame_Skewing(Frame_All_Sum, &Tangram.MO5.Frame_Now, &Tangram.MO5.Frame_Now, Image_Para_1);
// // // // //             Frame_Skewing(Frame_All_Sum, &Tangram.MO6.Frame_Now, &Tangram.MO6.Frame_Now, Image_Para_1);
// // // // //             Frame_Skewing(Frame_All_Sum, &Tangram.MO7.Frame_Now, &Tangram.MO7.Frame_Now, Image_Para_1);
// // // // //             Frame_Skewing(Frame_All_Sum, &Tangram.MO8.Frame_Now, &Tangram.MO8.Frame_Now, Image_Para_1);

// // // // //             Frame_Skewing(Frame_All_Sum, &Tangram.MO9.Frame_Now, &Tangram.MO9.Frame_Now, Image_Para_1);
// // // // //             Frame_Skewing(Frame_All_Sum, &Tangram.MO10.Frame_Now, &Tangram.MO10.Frame_Now, Image_Para_1);
// // // // //             Frame_Skewing(Frame_All_Sum, &Tangram.MO11.Frame_Now, &Tangram.MO11.Frame_Now, Image_Para_1);
// // // // //             Frame_Skewing(Frame_All_Sum, &Tangram.MO12.Frame_Now, &Tangram.MO12.Frame_Now, Image_Para_1);

// // // // //             Frame_Skewing(Frame_All_Sum, &Tangram.MO13.Frame_Now, &Tangram.MO13.Frame_Now, Image_Para_1);
// // // // //             Frame_Skewing(Frame_All_Sum, &Tangram.MO14.Frame_Now, &Tangram.MO14.Frame_Now, Image_Para_1);
// // // // //             Frame_Skewing(Frame_All_Sum, &Tangram.MO15.Frame_Now, &Tangram.MO15.Frame_Now, Image_Para_1);
// // // // //             Frame_Skewing(Frame_All_Sum, &Tangram.MO16.Frame_Now, &Tangram.MO16.Frame_Now, Image_Para_1);

// // // // //             Pixel_Cal(&Tangram.MO1, FrameArry_Add, 0);
// // // // //             Pixel_Cal(&Tangram.MO2, FrameArry_Add, 1);
// // // // //             Pixel_Cal(&Tangram.MO3, FrameArry_Add, 2);
// // // // //             Pixel_Cal(&Tangram.MO4, FrameArry_Add, 3);

// // // // //             Pixel_Cal(&Tangram.MO5, FrameArry_Add, 4);
// // // // //             Pixel_Cal(&Tangram.MO6, FrameArry_Add, 5);
// // // // //             Pixel_Cal(&Tangram.MO7, FrameArry_Add, 6);
// // // // //             Pixel_Cal(&Tangram.MO8, FrameArry_Add, 7);

// // // // //             Pixel_Cal(&Tangram.MO9, FrameArry_Add, 8);
// // // // //             Pixel_Cal(&Tangram.MO10, FrameArry_Add, 9);
// // // // //             Pixel_Cal(&Tangram.MO11, FrameArry_Add, 10);
// // // // //             Pixel_Cal(&Tangram.MO12, FrameArry_Add, 11);

// // // // //             Pixel_Cal(&Tangram.MO13, FrameArry_Add, 12);
// // // // //             Pixel_Cal(&Tangram.MO14, FrameArry_Add, 13);
// // // // //             Pixel_Cal(&Tangram.MO15, FrameArry_Add, 14);
// // // // //             Pixel_Cal(&Tangram.MO16, FrameArry_Add, 15);
// // // // //             Tangram_Buffer_load();
// // // // //         }
// // // // //     }
// // // // // }


A_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,
A_color,B_color,A_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,
A_color,B_color,B_color,A_color,B_color,A_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,
A_color,B_color,B_color,B_color,B_color,B_color,B_color,A_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,
A_color,B_color,B_color,B_color,A_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,B_color,
A_color,B_color,B_color,B_color,B_color,B_color,A_color,B_color,B_color,B_color,B_color,A_color,B_color,B_color,B_color,B_color,


const uint8_t Static_A7[][4] =
{
    statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,
};
const uint8_t Static_B3[][4] =
{
    statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,statColor,
};
