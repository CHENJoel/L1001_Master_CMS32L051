#ifndef _KEY_H_
#define _KEY_H_
#include "Function_Init.H"

typedef enum
{
	Com_KeyVal,
	Com_KeySet,
	Com_KeyReset,
	Return_nokey = 0xFF,
} KeyCommandTypeDef;

typedef enum
{
	RM_Key_B_U = 0,
	RM_Key_B_D = 1,
	RM_Key_OFF = 2,
	RM_Key_ON = 3,

	// RM_Dynam_U = 19,
	// RM_Dynam_D = 23,
	// RM_Stati_U = 18,
	// RM_Stati_D = 22,

	RM_Mode1 = 16,
	RM_Mode2 = 20,
	RM_Mode3 = 24,
	RM_Mode1_L = 17,
	RM_Mode1_R = 18,
	RM_Mode2_L = 21,
	RM_Mode2_R = 22,
	RM_Mode3_L = 25,
	RM_Mode3_R = 26,

	Key_Fu_SET = 5,

	Key_Tri_A1 = 15,
	Key_Tri_A2 = 19,
	Key_Tri_B1 = 23,
	Key_Tri_C1 = 27,
	Key_Tri_C2 = 31,
	Key_Tri_C3 = 35,
	Key_Tri_C4 = 39,
	Key_Square = 43,

	Numkey_Set = 40,
	Numkey_Rst = 42,
}
RemoteKeyTypeDef;

struct KeyTypeDef
{
	unsigned char State;		 /* 按键状态标志位
									bit7	上次按键电平/按键触发状态;
									bit6	单次长按标志（需手动清零，每次长按仅能置位一次）；
									bit5	双击标志;
									bit4	内部短按标志（仅内部用于双击检测，不对外开放此标志）;

									bit3	长按释放标志（需手动清零）;
									bit2	多次长按标志 （需手动清零，每次长按可多次置位，长按释放时，此位也会置位）;
									bit1	短按/单击标志（需手动清零）;
									bit0	本次按键电平/按键触发状态;
								 */
	unsigned int TimeCnt;		// 按键触发时间
	unsigned int Click_TimeCnt; // 用于双击计时（不用双击功能时,可去掉）
};
extern struct KeyTypeDef K1, K2, K3, K4, K5;

void Key_On(struct KeyTypeDef *Key, unsigned char KeyVal, unsigned char ON_Val, unsigned char OneClickTime, unsigned char LongClickTime, unsigned char LongTime, unsigned char DoubleClickTime);
unsigned char KeyNum_Match(unsigned char *KeyVal,unsigned char *ValArray,unsigned char ArraySize);
void Keyboard_Out(uint8_t *keyval, uint8_t *OutVal);

/**************************************** KK 示例 ****************************************/
//标志位-置位
#define KK_Click              K1.State & 0X02  // 0000 0010 单击置位
#define KK_DoubleClick        K1.State & 0X20  // 0010 0000 双击置位
#define KK_Long               K1.State & 0X04  // 0000 0100 长按可多次置位（长按/持续长按/长按释放）
#define KK_LongOnce           K1.State & 0X40  // 0100 0000 长按仅置位一次
#define KK_LongRelease        K1.State & 0X08  // 0000 1000 长按释放
//标志位-复位
#define KK_Click_Reset        K1.State &= 0XFD  // 1111 1101 复位单击标志
#define KK_DoubleClick_Reset  K1.State &= 0XDF  // 1101 1111 复位双击标志
#define KK_Long_Reset         K1.State &= 0XFB  // 1111 1011 复位长按（可多次置位）标志
#define KK_LongOnce_Reset     K1.State &= 0XBF  // 1011 1111 复位长按（仅置位一次）标志
#define KK_LongRelease_Reset  K1.State &= 0XF7  // 1111 0111 复位长按释放标志
#define KK_AllClick_Reset     K1.State &= 0XDD  // 1101 1101 复位单击、双击标志
#define KK_AllLong_Reset      K1.State &= 0XB3  // 1011 0011 复位多次长按、单次长按、长按释放标志
/**************************************** Rename ****************************************/
//标志位-置位
#define Rename_Click                KK_Click                // 0000 0010 单击置位
#define Rename_DoubleClick          KK_DoubleClick          // 0000 0010 单击置位
#define Rename_Long                 KK_Long                 // 0000 0100 长按可多次置位（长按/持续长按/长按释放）
#define Rename_LongOnce             KK_LongOnce             // 0100 0000 长按仅置位一次
#define Rename_LongRelease          KK_LongRelease          // 0000 1000 长按释放
//标志位-复位
#define Rename_Click_Reset          KK_Click_Reset          // 1111 1101 复位单击标志
#define Rename_DoubleClick_Reset    KK_DoubleClick_Reset    // 1101 1111 复位双击标志
#define Rename_Long_Reset           KK_Long_Reset           // 1111 1011 复位多次长按标志
#define Rename_LongOnce_Reset       KK_LongOnce_Reset       // 1011 1111 复位单次长按标志
#define Rename_LongRelease_Reset    KK_LongRelease_Reset    // 1111 0111 复位长按释放标志
#define Rename_AllClick_Reset       KK_AllClick_Reset       // 1101 1101 复位单击、双击标志
#define Rename_AllLong_Reset        KK_AllLong_Reset        // 1011 0011 复位多次长按、单次长按、长按释放标志
/**************************************** KK 示例 ****************************************/




/**************************************** K1 ****************************************/
//标志位-置位
#define KEY1_Click              K1.State & 0X02    // 0000 0010 单击置位
#define KEY1_DoubleClick        K1.State & 0X20    // 0000 0010 单击置位
#define KEY1_Long               K1.State & 0X04    // 0000 0100 长按可多次置位（长按/持续长按/长按释放）
#define KEY1_LongOnce           K1.State & 0X40    // 0100 0000 长按仅置位一次
#define KEY1_LongRelease        K1.State & 0X08    // 0000 1000 长按释放
//标志位-复位
#define KEY1_Click_Reset        K1.State &= 0XFD    // 1111 1101 复位单击标志
#define KEY1_DoubleClick_Reset  K1.State &= 0XDF    // 1101 1111 复位双击标志
#define KEY1_Long_Reset         K1.State &= 0XFB    // 1111 1011 复位多次长按标志
#define KEY1_LongOnce_Reset     K1.State &= 0XBF    // 1011 1111 复位单次长按标志
#define KEY1_LongRelease_Reset  K1.State &= 0XF7    // 1111 0111 复位长按释放标志
#define KEY1_AllClick_Reset     K1.State &= 0XDD    // 1101 1101 复位单击、双击标志
#define KEY1_AllLong_Reset      K1.State &= 0XB3    // 1011 0011 复位多次长按、单次长按、长按释放标志
/************************************************************************************/

/**************************************** K2 ****************************************/
//标志位-置位
#define KEY2_Click              K2.State & 0X02    // 0000 0010 单击置位
#define KEY2_DoubleClick        K2.State & 0X20    // 0000 0010 单击置位
#define KEY2_Long               K2.State & 0X04    // 0000 0100 长按可多次置位（长按/持续长按/长按释放）
#define KEY2_LongOnce          	K2.State & 0X40    // 0100 0000 长按仅置位一次
#define KEY2_LongRelease        K2.State & 0X08    // 0000 1000 长按释放
//标志位-复位
#define KEY2_Click_Reset        K2.State &= 0XFD    // 1111 1101 复位单击标志
#define KEY2_DoubleClick_Reset  K2.State &= 0XDF    // 1101 1111 复位双击标志
#define KEY2_Long_Reset         K2.State &= 0XFB    // 1111 1011 复位长按（可多次置位）标志
#define KEY2_LongOnce_Reset     K2.State &= 0XBF    // 1011 1111 复位单次长按标志
#define KEY2_LongRelease_Reset  K2.State &= 0XF7    // 1111 0111 复位长按释放标志
#define KEY2_AllClick_Reset     K2.State &= 0XDD    // 1101 1101 复位单击、双击标志
#define KEY2_AllLong_Reset      K2.State &= 0XB3    // 1011 0011 复位多次长按、单次长按、长按释放标志
/************************************************************************************/

/**************************************** K3 ****************************************/
//标志位-置位
#define KEY3_Click              K3.State & 0X02    // 0000 0010 单击置位
#define KEY3_DoubleClick        K3.State & 0X20    // 0000 0010 单击置位
#define KEY3_Long               K3.State & 0X04    // 0000 0100 长按可多次置位（长按/持续长按/长按释放）
#define KEY3_LongOnce          	K3.State & 0X40    // 0100 0000 长按仅置位一次
#define KEY3_LongRelease        K3.State & 0X08    // 0000 1000 长按释放
//标志位-复位
#define KEY3_Click_Reset        K3.State &= 0XFD    // 1111 1101 复位单击标志
#define KEY3_DoubleClick_Reset  K3.State &= 0XDF    // 1101 1111 复位双击标志
#define KEY3_Long_Reset         K3.State &= 0XFB    // 1111 1011 复位长按（可多次置位）标志
#define KEY3_LongOnce_Reset     K3.State &= 0XBF    // 1011 1111 复位单次长按标志
#define KEY3_LongRelease_Reset  K3.State &= 0XF7    // 1111 0111 复位长按释放标志
#define KEY3_AllClick_Reset     K3.State &= 0XDD    // 1101 1101 复位单击、双击标志
#define KEY3_AllLong_Reset      K3.State &= 0XB3    // 1011 0011 复位多次长按、单次长按、长按释放标志
/************************************************************************************/

/**************************************** K4 ****************************************/
//标志位-置位
#define KEY4_Click              K4.State & 0X02    // 0000 0010 单击置位
#define KEY4_DoubleClick        K4.State & 0X20    // 0000 0010 单击置位
#define KEY4_Long               K4.State & 0X04    // 0000 0100 长按可多次置位（长按/持续长按/长按释放）
#define KEY4_LongOnce           K4.State & 0X40    // 0100 0000 长按仅置位一次
#define KEY4_LongRelease        K4.State & 0X08    // 0000 1000 长按释放
//标志位-复位
#define KEY4_Click_Reset        K4.State &= 0XFD    // 1111 1101 复位单击标志
#define KEY4_DoubleClick_Reset  K4.State &= 0XDF    // 1101 1111 复位双击标志
#define KEY4_Long_Reset         K4.State &= 0XFB    // 1111 1011 复位长按（可多次置位）标志
#define KEY4_LongOnce_Reset     K4.State &= 0XBF    // 1011 1111 复位单次长按标志
#define KEY4_LongRelease_Reset  K4.State &= 0XF7    // 1111 0111 复位长按释放标志
#define KEY4_AllClick_Reset     K4.State &= 0XDD    // 1101 1101 复位单击、双击标志
#define KEY4_AllLong_Reset      K4.State &= 0XB3    // 1011 0011 复位多次长按、单次长按、长按释放标志
/************************************************************************************/

/**************************************** K5 ****************************************/
//标志位-置位
#define KEY5_Click              K5.State & 0X02    // 0000 0010 单击置位
#define KEY5_DoubleClick        K5.State & 0X20    // 0000 0010 单击置位
#define KEY5_Long               K5.State & 0X04    // 0000 0100 长按可多次置位（长按/持续长按/长按释放）
#define KEY5_LongOnce          	K5.State & 0X40    // 0100 0000 长按仅置位一次
#define KEY5_LongRelease        K5.State & 0X08    // 0000 1000 长按释放
//标志位-复位
#define KEY5_Click_Reset        K5.State &= 0XFD    // 1111 1101 复位单击标志
#define KEY5_DoubleClick_Reset  K5.State &= 0XDF    // 1101 1111 复位双击标志
#define KEY5_Long_Reset         K5.State &= 0XFB    // 1111 1011 复位长按（可多次置位）标志
#define KEY5_LongOnce_Reset     K5.State &= 0XBF    // 1011 1111 复位单次长按标志
#define KEY5_LongRelease_Reset  K5.State &= 0XF7    // 1111 0111 复位长按释放标志
#define KEY5_AllClick_Reset     K5.State &= 0XDD    // 1101 1101 复位单击、双击标志
#define KEY5_AllLong_Reset      K5.State &= 0XB3    // 1011 0011 复位多次长按、单次长按、长按释放标志
/************************************************************************************/

// // // /**************************************** K6 ****************************************/
// // // //标志位-置位
// // // #define KEY6_Click              K6.State & 0X02    // 0000 0010 单击置位
// // // #define KEY6_DoubleClick        K6.State & 0X20    // 0000 0010 单击置位
// // // #define KEY6_Long               K6.State & 0X04    // 0000 0100 长按可多次置位（长按/持续长按/长按释放）
// // // #define KEY6_LongOnce          	K6.State & 0X40    // 0100 0000 长按仅置位一次
// // // #define KEY6_LongRelease        K6.State & 0X08    // 0000 1000 长按释放
// // // //标志位-复位
// // // #define KEY6_Click_Reset        K6.State &= 0XFD    // 1111 1101 复位单击标志
// // // #define KEY6_DoubleClick_Reset  K6.State &= 0XDF    // 1101 1111 复位双击标志
// // // #define KEY6_Long_Reset         K6.State &= 0XFB    // 1111 1011 复位长按（可多次置位）标志
// // // #define KEY6_LongOnce_Reset     K6.State &= 0XBF    // 1011 1111 复位单次长按标志
// // // #define KEY6_LongRelease_Reset  K6.State &= 0XF7    // 1111 0111 复位长按释放标志
// // // #define KEY6_AllClick_Reset     K6.State &= 0XDD    // 1101 1101 复位单击、双击标志
// // // #define KEY6_AllLong_Reset      K6.State &= 0XB3    // 1011 0011 复位多次长按、单次长按、长按释放标志
// // // /************************************************************************************/

// // // /**************************************** K7 ****************************************/
// // // //标志位-置位
// // // #define KEY7_Click              K7.State & 0X02    // 0000 0010 单击置位
// // // #define KEY7_DoubleClick        K7.State & 0X20    // 0000 0010 单击置位
// // // #define KEY7_Long               K7.State & 0X04    // 0000 0100 长按可多次置位（长按/持续长按/长按释放）
// // // #define KEY7_LongOnce          	K7.State & 0X40    // 0100 0000 长按仅置位一次
// // // #define KEY7_LongRelease        K7.State & 0X08    // 0000 1000 长按释放
// // // //标志位-复位
// // // #define KEY7_Click_Reset        K7.State &= 0XFD    // 1111 1101 复位单击标志
// // // #define KEY7_DoubleClick_Reset  K7.State &= 0XDF    // 1101 1111 复位双击标志
// // // #define KEY7_Long_Reset         K7.State &= 0XFB    // 1111 1011 复位长按（可多次置位）标志
// // // #define KEY7_LongOnce_Reset     K7.State &= 0XBF    // 1011 1111 复位单次长按标志
// // // #define KEY7_LongRelease_Reset  K7.State &= 0XF7    // 1111 0111 复位长按释放标志
// // // #define KEY7_AllClick_Reset     K7.State &= 0XDD    // 1101 1101 复位单击、双击标志
// // // #define KEY7_AllLong_Reset      K7.State &= 0XB3    // 1011 0011 复位多次长按、单次长按、长按释放标志
// // // /************************************************************************************/



#endif
