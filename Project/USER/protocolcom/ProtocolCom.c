#include "Function_Init.H"
#include "ProtocolCom.H"

// // // // // // // Userdata_Typedef Userdata;

// // // // // // // /*����У���*/
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
// // // // // // // /*ָ�����*/
// // // // // // // void Command_Analyse(CmdTypenum CmdType, uint16_t Reg, uint16_t Val)
// // // // // // // {
// // // // // // // 	uint16_t temp;
// // // // // // // 	;
// // // // // // // 	if (CmdType == CMD_READREG || CmdType == CMD_WRITEREG) // �Ĵ�������
// // // // // // // 	{
// // // // // // // 		switch (Reg)
// // // // // // // 		{
// // // // // // // 		case REG_WERTE_PROTECT: /*д�����Ĵ���*/
// // // // // // // 			CmdReg_RW((CmdTypenum)CmdType, (Regenum)Reg, Val, p_REG(sys.writeprotect));
// // // // // // // 			break;
// // // // // // // 		case REG_DEVICEID: /*�豸ID*/
// // // // // // // 			CmdReg_RW((CmdTypenum)CmdType, (Regenum)Reg, Val, p_REG(Userdata.Appdata.deviceID));
// // // // // // // 			break;
// // // // // // // 		case REG_COMMUNID: /*ͨѶID*/
// // // // // // // 			CmdReg_RW((CmdTypenum)CmdType, (Regenum)Reg, Val, p_REG(Userdata.Appdata.communID));
// // // // // // // 			break;
// // // // // // // 		case REG_STARTTIME: /*��������*/
// // // // // // // 			CmdReg_RW((CmdTypenum)CmdType, (Regenum)Reg, Val, p_REG(Userdata.Appdata.starttime));
// // // // // // // 			break;
// // // // // // // 		case REG_DEVICETYPE: /*�豸����*/
// // // // // // // 			CmdReg_RW((CmdTypenum)CmdType, (Regenum)Reg, Val, p_REG(Userdata.Appdata.deviceType));
// // // // // // // 			break;
// // // // // // // 		default:
// // // // // // // 			break;
// // // // // // // 		}
// // // // // // // 	}
// // // // // // // 	else if (CmdType == CMD_READADDR || CmdType == CMD_WRITEADDR) // ��ַ���ݲ���
// // // // // // // 	{
// // // // // // // 		if (sys.writeprotect == MARK1001) // ���д����
// // // // // // // 		{
// // // // // // // 			CmdAdr_RW(CmdType, Reg, Val); // ���ֽڶ�д
// // // // // // // 		}
// // // // // // // 	}
// // // // // // // 	else if (CmdType == CMD_CONTROL) // ����ָ��
// // // // // // // 	{
// // // // // // // 		switch (Reg)
// // // // // // // 		{
// // // // // // // 		case CMD_RESET_DEVICE: /*�����豸*/
// // // // // // // 			// // printf("CMD_RESET_DEVICE\r");
// // // // // // // 			__NVIC_SystemReset();
// // // // // // // 			break;
// // // // // // // 		case CMD_GOTO_IAPMODE: /*�����������״̬*/
// // // // // // // 			temp = MARK1001;
// // // // // // // 			FlashROM_Insert((uint8_t *)&temp, (uint32_t) & (DATAFLASH->user.Bootdata.iap_permit), 2); // ���ֽ�д
// // // // // // // 			// // // printf("CMD_GOTO_IAPMODE\r");
// // // // // // // 			__NVIC_SystemReset();
// // // // // // // 			break;
// // // // // // // 		case CMD_CONNECT_COID: /*����ͨ��ID*/
// // // // // // // 			ACK_comCmd(CMD_CTRLACK, CMD_CONNECT_COID, Random_Generate(), Random_Generate());
// // // // // // // 			break;
// // // // // // // 		case CMD_REFRESH_COID: /*����ͨ��ID*/
// // // // // // // 			temp = 0x00;
// // // // // // // 			while (temp == 0x00 || temp == 0xFF)
// // // // // // // 			{
// // // // // // // 				temp = Random_Generate(); // ��ȡ�����
// // // // // // // 			}
// // // // // // // 			Userdata.Appdata.communID = temp; // ͨѶID����Ϊ�����
// // // // // // // 			break;
// // // // // // // 		case CMD_RESETUSERDATA: /*���ݻָ�Ĭ��ֵ*/
// // // // // // // 			Reset_Userdata();
// // // // // // // 			break;
// // // // // // // 		default:
// // // // // // // 			break;
// // // // // // // 		}
// // // // // // // 	}
// // // // // // // }
// // // // // // // /*�Ĵ�����д*/
// // // // // // // void CmdReg_RW(CmdTypenum CmdType, Regenum RegNum, uint32_t Val, uint32_t *pREG, uint8_t size)
// // // // // // // {
// // // // // // // 	uint32_t REG_Val;
// // // // // // // 	uint8_t *pReg_8bit;
// // // // // // // 	uint16_t *pReg_16bit;
// // // // // // // 	uint32_t *pReg_32bit;
// // // // // // // 	if (CmdType == CMD_READREG) // ��ѯָ��
// // // // // // // 	{
// // // // // // // 		switch (size)
// // // // // // // 		{
// // // // // // // 		case 1: /*1�ֽ�����*/
// // // // // // // 			REG_Val = (*(uint8_t *)pREG) & 0xFF;
// // // // // // // 			break;
// // // // // // // 		case 2: /*2�ֽ�����*/
// // // // // // // 			REG_Val = (*(uint16_t *)pREG) & 0xFFFF;
// // // // // // // 			break;
// // // // // // // 		case 4: /*4�ֽ�����*/
// // // // // // // 			REG_Val = (*(uint32_t *)pREG) & 0xFFFFFFFF;
// // // // // // // 			break;
// // // // // // // 		default:
// // // // // // // 			break;
// // // // // // // 		}
// // // // // // // 		ACK_comRW(CMD_RETURNREG, RegNum, REG_Val);
// // // // // // // 	}
// // // // // // // 	else if (CmdType == CMD_WRITEREG) // ����ָ��
// // // // // // // 	{
// // // // // // // 		switch (size)
// // // // // // // 		{
// // // // // // // 		case 1: /*1�ֽ�����*/
// // // // // // // 			pReg_8bit = (uint8_t *)pREG;
// // // // // // // 			*pReg_8bit = Val;
// // // // // // // 			break;
// // // // // // // 		case 2: /*2�ֽ�����*/
// // // // // // // 			pReg_16bit = (uint16_t *)pREG;
// // // // // // // 			*pReg_16bit = Val;
// // // // // // // 			break;
// // // // // // // 		case 4: /*4�ֽ�����*/
// // // // // // // 			pReg_32bit = (uint32_t *)pREG;
// // // // // // // 			*pReg_32bit = Val;
// // // // // // // 			break;
// // // // // // // 		default:
// // // // // // // 			break;
// // // // // // // 		}
// // // // // // // 	}
// // // // // // // }
// // // // // // // /*ָ����ַ��д1�ֽ�*/
// // // // // // // void CmdAdr_RW(CmdTypenum CmdType, uint32_t addr, uint32_t Val)
// // // // // // // {
// // // // // // // 	uint8_t data;
// // // // // // // 	if (addr < USERDATA_SIZE)
// // // // // // // 	{
// // // // // // // 		addr += USERDATA_BASEADDR;
// // // // // // // 		if (CmdType == CMD_READADDR) // ����ַ����
// // // // // // // 		{
// // // // // // // 			FlashROM_Insert((uint8_t *)&Val, addr, 1); // ���ֽ�д
// // // // // // // 		}
// // // // // // // 		else if (CmdType == CMD_WRITEADDR) // д��ַ����
// // // // // // // 		{
// // // // // // // 			FlashROM_BufferRead((uint8_t *)&data, addr, 1); // ���ֽڶ�
// // // // // // // 			ACK_comRW(CMD_RETURADDR, addr, data);
// // // // // // // 		}
// // // // // // // 	}
// // // // // // // }

// // // // // // // /*Ӧ�𷵻ؼĴ���/��ַ��ֵ*/
// // // // // // // void ACK_comRW(CmdTypenum CmdType, uint16_t Reg, uint16_t Val)
// // // // // // // {
// // // // // // // 	comRW_Typedef tx;
// // // // // // // 	uint8_t i;
// // // // // // // 	uint8_t *sur;
// // // // // // // 	tx.com_head = SCMD_HEADER;				   // �ӻ�֡ͷ
// // // // // // // 	tx.com_addr = Userdata.Appdata.communID; // ����ͨѶ��ַ
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
// // // // // // // } /*Ӧ�����ָ��*/
// // // // // // // void ACK_comCmd(CmdTypenum CmdType, Cmdenum cmd, uint8_t Val1, uint8_t Val2)
// // // // // // // {
// // // // // // // 	comCmd_Typedef tx;
// // // // // // // 	uint8_t i;
// // // // // // // 	uint8_t *sur;
// // // // // // // 	tx.com_head = SCMD_HEADER;				   // �ӻ�֡ͷ
// // // // // // // 	tx.com_addr = Userdata.Appdata.communID; // ����ͨѶ��ַ
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

// // // // // // // /*ָ���*/
// // // // // // // void Instruction_Process(void)
// // // // // // // {
// // // // // // // 	uint8_t i;
// // // // // // // 	uint8_t sum;
// // // // // // // 	uint16_t regaddr, regval;
// // // // // // // 	uint8_t rec[8];
// // // // // // // 	for (i = 0; i < 1000; i++) // �������ƴ���ȡ����50������
// // // // // // // 	{
// // // // // // // 		if (Uart_Buffer.Read != Uart_Buffer.Write) // ��������δ��ȫ����������
// // // // // // // 		{
// // // // // // // 			/* USER CODE BEGIN */
// // // // // // // 			/* Uart_Buffer.Read ָ��ǰ��Ҫ��������� */
// // // // // // // 			rec[0] = FIFO_ReadByte_Extract(&Uart_Buffer, 7);
// // // // // // // 			if (rec[0] == MPLAY_HEADER || rec[0] == MCMD_HEADER || rec[0] == UPPER_HEADER) // ֡ͷУ�飨�ӻ�APP�������������������ݣ�
// // // // // // // 			{
// // // // // // // 				rec[1] = FIFO_ReadByte_Extract(&Uart_Buffer, 6); // ��ַУ��
// // // // // // // 				if (rec[1] == Public_Addr || rec[1] == Userdata.Appdata.communID)
// // // // // // // 				{
// // // // // // // 					rec[2] = FIFO_ReadByte_Extract(&Uart_Buffer, 5); // ָ������/����
// // // // // // // 					rec[3] = FIFO_ReadByte_Extract(&Uart_Buffer, 4); // �Ĵ�����ַ�Ͱ�λ/Rֵ
// // // // // // // 					rec[4] = FIFO_ReadByte_Extract(&Uart_Buffer, 3); // �Ĵ�����ַ�߰�λ/Gֵ
// // // // // // // 					rec[5] = FIFO_ReadByte_Extract(&Uart_Buffer, 2); // �Ĵ�����ֵ�Ͱ�λ/Bֵ
// // // // // // // 					rec[6] = FIFO_ReadByte_Extract(&Uart_Buffer, 1); // �Ĵ�����ֵ�߰�λ/Wֵ
// // // // // // // 					rec[7] = FIFO_ReadByte_Extract(&Uart_Buffer, 0); // У���
// // // // // // // 					sum = CheckSum_Calu((uint8_t *)&rec, sizeof(rec) - 1);
// // // // // // // 					if (rec[7] == sum) // У���
// // // // // // // 					{
// // // // // // // 						if (rec[0] == MPLAY_HEADER) // ������Ϣ
// // // // // // // 						{
// // // // // // // 							LostConnect_Time = 0; // ͨѶ���ӳɹ�
// // // // // // // 							out.Bright = rec[2];
// // // // // // // 							out.R = rec[3];
// // // // // // // 							out.G = rec[4];
// // // // // // // 							out.B = rec[5];
// // // // // // // 							out.W = rec[6];
// // // // // // // 							out.W = rec[6];
// // // // // // // 						}
// // // // // // // 						else // ָ����Ϣ
// // // // // // // 						{
// // // // // // // 							regaddr = (rec[4] << 8) | rec[3];
// // // // // // // 							regval = (rec[6] << 8) | rec[5];
// // // // // // // 							Command_Analyse((CmdTypenum)rec[2], regaddr, regval);
// // // // // // // 						}
// // // // // // // 					}
// // // // // // // 				}
// // // // // // // 			}
// // // // // // // 			/* USER CODE END */
// // // // // // // 			if (Uart_Buffer.Read < (sizeof(Uart_Buffer.Buffer) - 1)) // ָ���´δ�������ݵĵ�ַ
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
