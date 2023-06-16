/* File Info
 * Author:      your name
 * CreateTime:  2022/5/26 11:23:19
 * LastEditor:  your name
 * ModifyTime:  2022/7/9 11:15:51
 * Description:
*/

#include "KEY.H"
#include "Function_Init.H"

struct KeyTypeDef K1, K2, K3, K4, K5;


/**
 * @description:根据按下时间来判断按键动作（长按/短按/双击）
 * @param {KeyTypeDef} *Key					按键结构体
 * @param {unsigned char} KeyVal			当前按键值/电平
 * @param {unsigned char} ON_Val			按键有效触发时的键值/电平
 * @param {unsigned char} OneClickTime 		短按触发时间(滤波时间)
 * @param {unsigned char} LongClickTime		长按首次触发时间
 * @param {unsigned char} LongTime			长按持续触发间隔时间,0(长按仅触发一次)/N(每隔N次触发一次)
 * @param {unsigned char} DoubleClickTime	0不启用双击检测/双击判断时间
 * @return {*}
 */

void Key_On(struct KeyTypeDef *Key, unsigned char KeyVal, unsigned char ON_Val, unsigned char OneClickTime, unsigned char LongClickTime, unsigned char LongTime, unsigned char DoubleClickTime)
{
	unsigned char Key_State_Temp = 0; // 实测问题：不同结构体变量调用本函数时，局部变量并未初始化，初始化值并不为0；导致数据出错，函数失效
	unsigned char Temp = 0;			  // 解决：必须手动初始化（赋值0）清零，否则变量执行“或”操作时，数据开始出错

	if ((*Key).TimeCnt < 0XFFFF)
	{
		(*Key).TimeCnt++;
	}

	if ((*Key).TimeCnt >= LongClickTime) // 长按判断
	{
		if (LongTime) // 使用持续触发
		{
			if ((*Key).TimeCnt > (LongClickTime + LongTime)) // 每隔LongTime，置位一次长按标志，可持续置位
			{
				(*Key).TimeCnt = LongClickTime + 1;
				Key_State_Temp |= 0X04; // 0000 0100	长按标志置位
			}
		}
		if ((*Key).TimeCnt == LongClickTime) // 长按标志 每次长按仅置位一次
		{
			Key_State_Temp |= 0X44; // 0100 0100	长按标志置位&单次长按标志置位
		}
		if (KeyVal != ON_Val) // 长按释放,会同时置位 长按标志和长按释放标志
		{
			Key_State_Temp |= 0X0C; // 0000 1100
			(*Key).TimeCnt = 0;
		}
	}
	else if ((*Key).TimeCnt > OneClickTime) // 短按判断
	{
		if (KeyVal != ON_Val) // 短按释放
		{
			Key_State_Temp |= 0X02; // 0000 0010	短按标志置位
			(*Key).TimeCnt = 0;
		}
	}
	else
	{
		if (KeyVal != ON_Val) // 按键触发时间不足，按键无效
		{
			(*Key).TimeCnt = 0;
		}
	}
	if (KeyVal == ON_Val) // 按键有效触发
	{
		Key_State_Temp |= 0X01; // 0000 0001 按键状态置位（更新此次按键状态）
	}
	/******************	双击判断 ******************/
	if (DoubleClickTime) // 启用双击检测
	{
		if (Key_State_Temp & 0X02) // 出现短按标志
		{
			Key_State_Temp &= 0XFD;	// 1111 1101 复位短按标志
			Key_State_Temp |= 0X10; // 0001 0000 置位内部短按标志
			/*
				启动双击检测后，只有等待双击检测超时后，仍没有出现第二次短按，
				才可以判断为短按操作；所以此处短按标志仅做首击置位，不做短按判断，需复位该标志。
			*/
		}
		if ((*Key).State & 0X10) // 此前出现短按（首击），则可进行双击判断
		{
			if ((*Key).Click_TimeCnt < 0XFFFF)
			{
				(*Key).Click_TimeCnt++; // 距离第一次单击的相隔时间
			}
			if ((*Key).Click_TimeCnt > DoubleClickTime) // 双击检测超时,完成本次双击检测
			{
				if (Key_State_Temp & 0X10) // 检测到第二次单击，则判断为双击
				{
					Key_State_Temp &= 0XEF; // 1110 1111 复位内部短按标志
					Key_State_Temp |= 0X20; // 0010 0000 置位双击标志
					(*Key).State &= 0XEF;	// 1110 1111 复位内部短按标志
				}
				else // 超时仍未检测第二次单击
				{
					Key_State_Temp |= 0X02; // 0000 0001 置位单击标志
					Key_State_Temp &= 0XEF; // 1110 1111 复位内部短按标志
					(*Key).State &= 0XEF;	// 1110 1111 复位内部短按标志
				}
				(*Key).Click_TimeCnt = 0; // 双击检测时间复位，准备下次双击检测
				(*Key).State &= 0XEF;	  // 首击标志复位，准备下次双击检测
			}
			else
			{
				if (Key_State_Temp & 0X10) // 在双击检测时间内，检测到第二次单击，则判断为双击,完成本次双击检测
				{
					Key_State_Temp |= 0X20;	  // 0010 0000 置位双击标志
					Key_State_Temp &= 0XEF;	  // 1110 1111 复位内部短按标志
					(*Key).State &= 0XEF;	  // 1110 1111 首击标志复位，准备下次双击检测
					(*Key).Click_TimeCnt = 0; // 双击检测时间复位，准备下次双击检测
				}
			}
		}
		Temp = (*Key).State & 0X3E;		//	0011 1110
		(*Key).State <<= 7;				//	更新上次按键状态
		(*Key).State |= Temp;			//  恢复原来标志状态
		(*Key).State &= 0XBE;			//  1011 1110
		(*Key).State |= Key_State_Temp; // 	更新此次按键标志状态
	}
	else
	{
		Temp = (*Key).State & 0X0E;		//	0000 1110
		(*Key).State <<= 7;				//	更新上次按键状态
		(*Key).State |= Temp;			//  恢复原来标志状态
		(*Key).State &= 0X8E;			//  1000 1110 ,双击功能关联的标志清零
		(*Key).State |= Key_State_Temp; // 	更新此次按键标志状态
	}
}


unsigned char KeyNum_Match(unsigned char *KeyVal, unsigned char *ValArray, unsigned char ArraySize)
{
	unsigned char i;
	for (i = 0; i < ArraySize; i++)
	{
		if (*KeyVal == ValArray[i])
		{
			return i;
		}
	}
	return 0xFF; // 返回FF，代表无匹配按键
}

unsigned char Numeric_Keyboard(unsigned char keyval, unsigned char command)
{
	static unsigned char OnesVal; // 个位数
	static unsigned char TensVal; // 十位数
	static unsigned char Inflag;  // 输入标志
	unsigned char temp;
	if (command == Com_KeyVal)
	{
		TensVal = OnesVal;
		OnesVal = keyval;
		Inflag = 1;
		return Return_nokey;
	}
	else if (command == Com_KeySet)
	{
		if (Inflag)
		{
			temp = TensVal * 10 + OnesVal;
			TensVal = 0;
			OnesVal = 0;
			Inflag = 0;
			return temp;
		}
		else
		{
			TensVal = 0;
			OnesVal = 0;
			Inflag = 0;
			return Return_nokey;
		}
	}
	else if (command == Com_KeyReset)
	{
		TensVal = 0;
		OnesVal = 0;
		Inflag = 0;
		return Return_nokey;
	}
}

void Keyboard_Out(uint8_t *keyval, uint8_t *OutVal)
{
	unsigned char temp;
	*OutVal = 0xFF;
	if (*keyval != 0xFF)
	{
		switch (*keyval)
		{
		case Numkey_Set:
			*OutVal = Numeric_Keyboard(0, Com_KeySet);
			break;
		case Numkey_Rst:
			Numeric_Keyboard(0, Com_KeyReset);
			break;
		default:
			temp = KeyNum_Match(keyval, &Numboard_KeyTable, sizeof(Numboard_KeyTable));
			if (temp!=0xFF)
			{
				Numeric_Keyboard(temp, Com_KeyVal);
			}
			break;
		}
	}
}

// // // void Numeric_Keyboard(uint8_t *keyval, uint8_t *OutVal)
// // // {
// // // 	static uint8_t OnesVal; // 个位数
// // // 	static uint8_t TensVal; // 十位数
// // // 	uint8_t temp;

// // // 	switch (*keyval)
// // // 	{
// // // 	case Numkey_Set:
// // // 		temp = TensVal * 10 + OnesVal;
// // // 		TensVal = 0;
// // // 		OnesVal = 0;
// // // 		*OutVal = temp;
// // // 		break;
// // // 	case Numkey_Rst:
// // // 		TensVal = 0;
// // // 		OnesVal = 0;
// // // 		break;
// // // 	default:
// // // 		temp = KeyNum_Match(keyval, &Numboard_KeyTable, sizeof(Numboard_KeyTable));
// // // 		TensVal = OnesVal;
// // // 		OnesVal = temp;
// // // 		break;
// // // 	}

// // // 	if (keyval == Com_KeyVal)
// // // 	{
// // // 		TensVal = OnesVal;
// // // 		OnesVal = keyval;
// // // 		return Return_nokey;
// // // 	}
// // // 	else if (command == Com_KeySet)
// // // 	{
// // // 		temp = TensVal * 10 + OnesVal;
// // // 		TensVal = 0;
// // // 		OnesVal = 0;
// // // 		return temp;
// // // 	}
// // // 	else if (command == Com_KeyReset)
// // // 	{
// // // 		TensVal = 0;
// // // 		OnesVal = 0;
// // // 		return Return_nokey;
// // // 	}
// // // }
