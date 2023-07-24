#include "Function_Init.H"
#include "ProtocolCom.H"

// // // // // // // Userdata_Typedef Userdata;

// // // // // // // /*计算校验和*/
// // // // // // // uint16_t CheckSum_Calu(uint8_t *sur, uint16_t len)
// // // // // // // {
// // // // // // // 	uint16_t i;
// // // // // // // 	uint16_t sum = 0;
// // // // // // // 	for (i = 0; i < len; i++)
// // // // // // // 	{
// // // // // // // 		sum += *sur++;
// // // // // // // 	}
// // // // // // // 	return sum;
// // // // // // // }
// // // // // // // /*指令分析*/
// // // // // // // void Command_Analyse(CmdTypenum CmdType, uint16_t Reg, uint16_t Val)
// // // // // // // {
// // // // // // // 	uint16_t temp;
// // // // // // // 	;
// // // // // // // 	if (CmdType == CMD_READREG || CmdType == CMD_WRITEREG) // 寄存器操作
// // // // // // // 	{
// // // // // // // 		switch (Reg)
// // // // // // // 		{
// // // // // // // 		case REG_WERTE_PROTECT: /*写保护寄存器*/
// // // // // // // 			CmdReg_RW((CmdTypenum)CmdType, (Regenum)Reg, Val, p_REG(sys.writeprotect));
// // // // // // // 			break;
// // // // // // // 		case REG_DEVICEID: /*设备ID*/
// // // // // // // 			CmdReg_RW((CmdTypenum)CmdType, (Regenum)Reg, Val, p_REG(Userdata.Appdata.deviceID));
// // // // // // // 			break;
// // // // // // // 		case REG_COMMUNID: /*通讯ID*/
// // // // // // // 			CmdReg_RW((CmdTypenum)CmdType, (Regenum)Reg, Val, p_REG(Userdata.Appdata.communID));
// // // // // // // 			break;
// // // // // // // 		case REG_STARTTIME: /*开机次数*/
// // // // // // // 			CmdReg_RW((CmdTypenum)CmdType, (Regenum)Reg, Val, p_REG(Userdata.Appdata.starttime));
// // // // // // // 			break;
// // // // // // // 		case REG_DEVICETYPE: /*设备类型*/
// // // // // // // 			CmdReg_RW((CmdTypenum)CmdType, (Regenum)Reg, Val, p_REG(Userdata.Appdata.deviceType));
// // // // // // // 			break;
// // // // // // // 		default:
// // // // // // // 			break;
// // // // // // // 		}
// // // // // // // 	}
// // // // // // // 	else if (CmdType == CMD_READADDR || CmdType == CMD_WRITEADDR) // 地址数据操作
// // // // // // // 	{
// // // // // // // 		if (sys.writeprotect == MARK1001) // 解除写保护
// // // // // // // 		{
// // // // // // // 			CmdAdr_RW(CmdType, Reg, Val); // 单字节读写
// // // // // // // 		}
// // // // // // // 	}
// // // // // // // 	else if (CmdType == CMD_CONTROL) // 控制指令
// // // // // // // 	{
// // // // // // // 		switch (Reg)
// // // // // // // 		{
// // // // // // // 		case CMD_RESET_DEVICE: /*重启设备*/
// // // // // // // 			// // printf("CMD_RESET_DEVICE\r");
// // // // // // // 			__NVIC_SystemReset();
// // // // // // // 			break;
// // // // // // // 		case CMD_GOTO_IAPMODE: /*进入程序升级状态*/
// // // // // // // 			temp = MARK1001;
// // // // // // // 			FlashROM_Insert((uint8_t *)&temp, (uint32_t) & (DATAFLASH->user.Bootdata.iap_permit), 2); // 单字节写
// // // // // // // 			// // // printf("CMD_GOTO_IAPMODE\r");
// // // // // // // 			__NVIC_SystemReset();
// // // // // // // 			break;
// // // // // // // 		case CMD_CONNECT_COID: /*握手通信ID*/
// // // // // // // 			ACK_comCmd(CMD_CTRLACK, CMD_CONNECT_COID, Random_Generate(), Random_Generate());
// // // // // // // 			break;
// // // // // // // 		case CMD_REFRESH_COID: /*更新通信ID*/
// // // // // // // 			temp = 0x00;
// // // // // // // 			while (temp == 0x00 || temp == 0xFF)
// // // // // // // 			{
// // // // // // // 				temp = Random_Generate(); // 获取随机数
// // // // // // // 			}
// // // // // // // 			Userdata.Appdata.communID = temp; // 通讯ID更新为随机数
// // // // // // // 			break;
// // // // // // // 		case CMD_RESETUSERDATA: /*数据恢复默认值*/
// // // // // // // 			Reset_Userdata();
// // // // // // // 			break;
// // // // // // // 		default:
// // // // // // // 			break;
// // // // // // // 		}
// // // // // // // 	}
// // // // // // // }
// // // // // // // /*寄存器读写*/
// // // // // // // void CmdReg_RW(CmdTypenum CmdType, Regenum RegNum, uint32_t Val, uint32_t *pREG, uint8_t size)
// // // // // // // {
// // // // // // // 	uint32_t REG_Val;
// // // // // // // 	uint8_t *pReg_8bit;
// // // // // // // 	uint16_t *pReg_16bit;
// // // // // // // 	uint32_t *pReg_32bit;
// // // // // // // 	if (CmdType == CMD_READREG) // 查询指令
// // // // // // // 	{
// // // // // // // 		switch (size)
// // // // // // // 		{
// // // // // // // 		case 1: /*1字节数据*/
// // // // // // // 			REG_Val = (*(uint8_t *)pREG) & 0xFF;
// // // // // // // 			break;
// // // // // // // 		case 2: /*2字节数据*/
// // // // // // // 			REG_Val = (*(uint16_t *)pREG) & 0xFFFF;
// // // // // // // 			break;
// // // // // // // 		case 4: /*4字节数据*/
// // // // // // // 			REG_Val = (*(uint32_t *)pREG) & 0xFFFFFFFF;
// // // // // // // 			break;
// // // // // // // 		default:
// // // // // // // 			break;
// // // // // // // 		}
// // // // // // // 		ACK_comRW(CMD_RETURNREG, RegNum, REG_Val);
// // // // // // // 	}
// // // // // // // 	else if (CmdType == CMD_WRITEREG) // 设置指令
// // // // // // // 	{
// // // // // // // 		switch (size)
// // // // // // // 		{
// // // // // // // 		case 1: /*1字节数据*/
// // // // // // // 			pReg_8bit = (uint8_t *)pREG;
// // // // // // // 			*pReg_8bit = Val;
// // // // // // // 			break;
// // // // // // // 		case 2: /*2字节数据*/
// // // // // // // 			pReg_16bit = (uint16_t *)pREG;
// // // // // // // 			*pReg_16bit = Val;
// // // // // // // 			break;
// // // // // // // 		case 4: /*4字节数据*/
// // // // // // // 			pReg_32bit = (uint32_t *)pREG;
// // // // // // // 			*pReg_32bit = Val;
// // // // // // // 			break;
// // // // // // // 		default:
// // // // // // // 			break;
// // // // // // // 		}
// // // // // // // 	}
// // // // // // // }
// // // // // // // /*指定地址读写1字节*/
// // // // // // // void CmdAdr_RW(CmdTypenum CmdType, uint32_t addr, uint32_t Val)
// // // // // // // {
// // // // // // // 	uint8_t data;
// // // // // // // 	if (addr < USERDATA_SIZE)
// // // // // // // 	{
// // // // // // // 		addr += USERDATA_BASEADDR;
// // // // // // // 		if (CmdType == CMD_READADDR) // 读地址数据
// // // // // // // 		{
// // // // // // // 			FlashROM_Insert((uint8_t *)&Val, addr, 1); // 单字节写
// // // // // // // 		}
// // // // // // // 		else if (CmdType == CMD_WRITEADDR) // 写地址数据
// // // // // // // 		{
// // // // // // // 			FlashROM_BufferRead((uint8_t *)&data, addr, 1); // 单字节读
// // // // // // // 			ACK_comRW(CMD_RETURADDR, addr, data);
// // // // // // // 		}
// // // // // // // 	}
// // // // // // // }

// // // // // // // /*应答返回寄存器/地址的值*/
// // // // // // // void ACK_comRW(CmdTypenum CmdType, uint16_t Reg, uint16_t Val)
// // // // // // // {
// // // // // // // 	comRW_Typedef tx;
// // // // // // // 	uint8_t i;
// // // // // // // 	uint8_t *sur;
// // // // // // // 	tx.com_head = SCMD_HEADER;				   // 从机帧头
// // // // // // // 	tx.com_addr = Userdata.Appdata.communID; // 本机通讯地址
// // // // // // // 	tx.com_cmdType = CmdType;
// // // // // // // 	tx.com_regaddr = Reg;
// // // // // // // 	tx.com_regval = Val;
// // // // // // // 	sur = (uint8_t *)&tx;
// // // // // // // 	tx.com_checksum = 0;
// // // // // // // 	for (i = 0; i < sizeof(tx); i++)
// // // // // // // 	{
// // // // // // // 		UART0_Send(*sur);
// // // // // // // 		tx.com_checksum += *sur;
// // // // // // // 		sur++;
// // // // // // // 	}
// // // // // // // } /*应答控制指令*/
// // // // // // // void ACK_comCmd(CmdTypenum CmdType, Cmdenum cmd, uint8_t Val1, uint8_t Val2)
// // // // // // // {
// // // // // // // 	comCmd_Typedef tx;
// // // // // // // 	uint8_t i;
// // // // // // // 	uint8_t *sur;
// // // // // // // 	tx.com_head = SCMD_HEADER;				   // 从机帧头
// // // // // // // 	tx.com_addr = Userdata.Appdata.communID; // 本机通讯地址
// // // // // // // 	tx.com_cmdType = CmdType;
// // // // // // // 	tx.com_cmd = cmd;
// // // // // // // 	tx.com_val1 = Val1;
// // // // // // // 	tx.com_val2 = Val2;
// // // // // // // 	sur = (uint8_t *)&tx;
// // // // // // // 	tx.com_checksum = 0;
// // // // // // // 	for (i = 0; i < sizeof(tx); i++)
// // // // // // // 	{
// // // // // // // 		UART0_Send(*sur);
// // // // // // // 		tx.com_checksum += *sur;
// // // // // // // 		sur++;
// // // // // // // 	}
// // // // // // // }

// // // // // // // /*指令处理*/
// // // // // // // void Instruction_Process(void)
// // // // // // // {
// // // // // // // 	uint8_t i;
// // // // // // // 	uint8_t sum;
// // // // // // // 	uint16_t regaddr, regval;
// // // // // // // 	uint8_t rec[8];
// // // // // // // 	for (i = 0; i < 1000; i++) // 单次限制处理（取出）50个数据
// // // // // // // 	{
// // // // // // // 		if (Uart_Buffer.Read != Uart_Buffer.Write) // 缓存数据未完全处理（读出）
// // // // // // // 		{
// // // // // // // 			/* USER CODE BEGIN */
// // // // // // // 			/* Uart_Buffer.Read 指向当前需要处理的数据 */
// // // // // // // 			rec[0] = FIFO_ReadByte_Extract(&Uart_Buffer, 7);
// // // // // // // 			if (rec[0] == MPLAY_HEADER || rec[0] == MCMD_HEADER || rec[0] == UPPER_HEADER) // 帧头校验（从机APP仅接收主机发出的数据）
// // // // // // // 			{
// // // // // // // 				rec[1] = FIFO_ReadByte_Extract(&Uart_Buffer, 6); // 地址校验
// // // // // // // 				if (rec[1] == Public_Addr || rec[1] == Userdata.Appdata.communID)
// // // // // // // 				{
// // // // // // // 					rec[2] = FIFO_ReadByte_Extract(&Uart_Buffer, 5); // 指令类型/亮度
// // // // // // // 					rec[3] = FIFO_ReadByte_Extract(&Uart_Buffer, 4); // 寄存器地址低八位/R值
// // // // // // // 					rec[4] = FIFO_ReadByte_Extract(&Uart_Buffer, 3); // 寄存器地址高八位/G值
// // // // // // // 					rec[5] = FIFO_ReadByte_Extract(&Uart_Buffer, 2); // 寄存器的值低八位/B值
// // // // // // // 					rec[6] = FIFO_ReadByte_Extract(&Uart_Buffer, 1); // 寄存器的值高八位/W值
// // // // // // // 					rec[7] = FIFO_ReadByte_Extract(&Uart_Buffer, 0); // 校验和
// // // // // // // 					sum = CheckSum_Calu((uint8_t *)&rec, sizeof(rec) - 1);
// // // // // // // 					if (rec[7] == sum) // 校验和
// // // // // // // 					{
// // // // // // // 						if (rec[0] == MPLAY_HEADER) // 播放信息
// // // // // // // 						{
// // // // // // // 							LostConnect_Time = 0; // 通讯链接成功
// // // // // // // 							out.Bright = rec[2];
// // // // // // // 							out.R = rec[3];
// // // // // // // 							out.G = rec[4];
// // // // // // // 							out.B = rec[5];
// // // // // // // 							out.W = rec[6];
// // // // // // // 							out.W = rec[6];
// // // // // // // 						}
// // // // // // // 						else // 指令信息
// // // // // // // 						{
// // // // // // // 							regaddr = (rec[4] << 8) | rec[3];
// // // // // // // 							regval = (rec[6] << 8) | rec[5];
// // // // // // // 							Command_Analyse((CmdTypenum)rec[2], regaddr, regval);
// // // // // // // 						}
// // // // // // // 					}
// // // // // // // 				}
// // // // // // // 			}
// // // // // // // 			/* USER CODE END */
// // // // // // // 			if (Uart_Buffer.Read < (sizeof(Uart_Buffer.Buffer) - 1)) // 指出下次处理的数据的地址
// // // // // // // 			{
// // // // // // // 				Uart_Buffer.Read++;
// // // // // // // 			}
// // // // // // // 			else
// // // // // // // 			{
// // // // // // // 				Uart_Buffer.Read = 0;
// // // // // // // 			}
// // // // // // // 		}
// // // // // // // 		else
// // // // // // // 		{
// // // // // // // 			break;
// // // // // // // 		}
// // // // // // // 	}
// // // // // // // }
