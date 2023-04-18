#include "Function_Init.H"
/*

#define W25_CS_ENABLE()         {W25_CS(0); us_delay(10);}
#define W25_CS_DISABLE()        {W25_CS(1); us_delay(10);}
#define SPI_Delay()             us_delay(1)

FLASH_SectorErase(0);           ʵ�� 9.12ms
FLASH_PageWrite(buf, 0, 256);   ʵ�� 18ms
FLASH_BufferRead(bufR, 0, 256); ʵ�� 16.7ms








*/
void Print_HEX16(uint8_t *sur, uint16_t size)
{
    uint16_t i;
    uint8_t j = 0;
    printf("\n");
    for (i = 0; i < size; i++)
    {
        if (j == 0)
        {
            printf("|0x%4x| ", i);
        }
        printf("%2x ", *sur++);
        if (++j > 63)
        {
            j = 0;
            printf("\n");
        }
    }
    printf("\n");
}

void SPI_FlashDebug(void)
{


    //

    uint8_t buf[0X40];
    uint8_t bufR[0X300];
    uint16_t i;
    static uint8_t hh;
    // // // printf("\r\n");
    // // // printf("start\r\n");
    // // // memset(buf, 0, sizeof(buf)); // ��������

    for (i = 0; i < sizeof(buf); i++)
    {
        buf[i] = hh;
        // // buf[i] = i;
    }




    for (i = 0; i < sizeof(buf); i++)
    {
        buf[i] = hh;
        // // buf[i] = i;
    }
    hh++;
    // // // // // FLASH_SectorErase(0);
    // // // FLASH_PageErase(5);
    // // // LED1_ON();
    // // // FLASH_PageWrite(buf, 0, 64);
    // // // // LED1_OFF();
    FlashSPI_Write(buf, 0x640, sizeof(buf));

    FLASH_BufferRead(bufR, 0x400, sizeof(bufR)); // �ݴ�ԭ��Flash��ҳ�������
    Print_HEX16(bufR,sizeof(bufR));



    // // // // FLASH_PageWrite(buf, 256, 256);
    // // // memset(bufR, 0, sizeof(bufR)); // ��������

    // // // FLASH_BufferRead(bufR, 0, 256);
    // // // Print_HEX16(bufR,sizeof(bufR));
    // // // FLASH_BufferRead(bufR, 256, 256);
    // // // Print_HEX16(bufR,sizeof(bufR));


    // // printf("before\r\n");
    // FLASH_SectorErase(0);
    // FLASH_PageErase(0);
    // printf("after\r\n");
    // FLASH_BufferRead(bufR, 0, 256);
    // Print_HEX16(bufR,sizeof(bufR));
    // FLASH_BufferRead(bufR, 256, 256);
    // Print_HEX16(bufR,sizeof(bufR));
}

        // memset(colordata, 0, sizeof(color_group_TypeDef)); // ��������
        // memcpy(colordata, EF_DefaultData[num].color_array, EF_DefaultData[EF_Work.EF_ID].color_sum * 4);

// void FlashSPI_RandomRead (uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
// {

// }

/*
    Դ���ݵ�ָ��
    ��д��ַ
    Ҫд����ֽ���
*/
void FlashSPI_Write(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t pwrite; // дflash��ָ��
    uint16_t pread;  // Դ���ݴ�����ȡ��ָ�루��д���ֽ�����
    uint8_t *sur, *tar;
    uint16_t pageAddr;                       // ��ǰҳ�׵�ַ
    uint16_t pageOffset;                     // ҳ��ƫ�Ƶ�ַ
    uint16_t pageRemain;                     // ��ǰҳ��ʣ��ռ�
    uint16_t writeRemain;                    // ʣ����д�ֽ���
    uint8_t flashbuffer[SPI_FLASH_PageSize]; // �ݴ�
    pwrite = WriteAddr;
    for (pread = 0; pread < NumByteToWrite;)
    {
        pageOffset = pwrite % SPI_FLASH_PageSize;                     // ҳ��ƫ�Ƶ�ַ
        pageAddr = pwrite - pageOffset;                               // ��ǰҳ�׵�ַ
        pageRemain = SPI_FLASH_PageSize - pageOffset;                 // ҳ��ʣ��ռ�
        writeRemain = NumByteToWrite - pread;                         // ��δ��д���ֽ���
        FLASH_BufferRead(flashbuffer, pageAddr, sizeof(flashbuffer)); // �ݴ�ԭ��Flash��ҳ�������
        sur = pBuffer + pread;                                        // ��ȡԴ���ݵĵ�N������
        tar = flashbuffer + pageOffset;                               // �޸ĵ�ǰҳƫ�Ƶ�ַ�ϵ�����
        if (pageRemain >= writeRemain)                                // ��ǰҳ����д��ʣ�����ݣ�д��ʣ������
        {
            memcpy(tar, sur, writeRemain);                               // ����������
            FLASH_PageErase(pageAddr);                                   // ������ҳ
            FLASH_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer)); // д���޸ĺ��ҳ����
            pwrite += writeRemain;                                       // ָ��ƫ����д���ֽ���
            pread += writeRemain;                                        // ָ��ƫ����д���ֽ���
        }
        else // ��ǰҳд����,��д����ǰҳ
        {
            memcpy(tar, sur, pageRemain);                                // ����������
            FLASH_PageErase(pageAddr);                                   // ������ҳ
            FLASH_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer)); // д���޸ĺ��ҳ����
            pwrite += pageRemain;                                        // ָ��ƫ����д���ֽ���
            pread += pageRemain;                                         // ָ��ƫ����д���ֽ���
        }
    }
}

void ROM_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint8_t *sur, *tar;
    sur = (uint8_t *)ReadAddr;
    tar = pBuffer;
    memcpy(tar, sur, NumByteToRead); // ����������
}














/*

// ��ָ����ַ��ʼд��ָ�����ȵ�����
// WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ2�ı���!!)
// pBuffer:����ָ��
// NumToWrite:����(16λ)��(����Ҫд���16λ���ݵĸ���.)
#if STM32_FLASH_SIZE < 256
#define STM_SECTOR_SIZE 1024 // �ֽ�
#else
#define STM_SECTOR_SIZE 2048
#endif
u16 STMFLASH_BUF[STM_SECTOR_SIZE / 2]; // �����2K�ֽ�
void STMFLASH_Write(u32 WriteAddr, u16 *pBuffer, u16 NumToWrite)
{
	u32 secpos;	   // ������ַ
	u16 secoff;	   // ������ƫ�Ƶ�ַ(16λ�ּ���)
	u16 secremain; // ������ʣ���ַ(16λ�ּ���)
	u16 i;
	u32 offaddr; // ȥ��0X08000000��ĵ�ַ

	if (WriteAddr < STM32_FLASH_BASE || (WriteAddr >= (STM32_FLASH_BASE + 1024 * STM32_FLASH_SIZE)))
		return; // �Ƿ���ַ

	HAL_FLASH_Unlock();						  // ����
	offaddr = WriteAddr - STM32_FLASH_BASE;	  // ʵ��ƫ�Ƶ�ַ.
	secpos = offaddr / STM_SECTOR_SIZE;		  // ������ַ  0~127 for STM32F103RBT6
	secoff = (offaddr % STM_SECTOR_SIZE) / 2; // �������ڵ�ƫ��(2���ֽ�Ϊ������λ.)
	secremain = STM_SECTOR_SIZE / 2 - secoff; // ����ʣ��ռ��С
	if (NumToWrite <= secremain)
		secremain = NumToWrite; // �����ڸ�������Χ
	while (1)
	{
		STMFLASH_Read(secpos * STM_SECTOR_SIZE + STM32_FLASH_BASE, STMFLASH_BUF, STM_SECTOR_SIZE / 2); // ������������������
		for (i = 0; i < secremain; i++)																   // У������
		{s
			if (STMFLASH_BUF[secoff + i] != 0XFFFF)
				break; // ��Ҫ����
		}
		if (i < secremain) // ��Ҫ����
		{
			FLASH_PageErase(secpos * STM_SECTOR_SIZE + STM32_FLASH_BASE); // �����������
			FLASH_WaitForLastOperation(FLASH_WAITETIME);				  // �ȴ��ϴβ������
			CLEAR_BIT(FLASH->CR, FLASH_CR_PER);							  // ���CR�Ĵ�����PERλ���˲���Ӧ����FLASH_PageErase()����ɣ�
												// ����HAL�����沢û������Ӧ����HAL��bug��
			for (i = 0; i < secremain; i++) // ����
			{
				STMFLASH_BUF[i + secoff] = pBuffer[i];
			}
			STMFLASH_Write_NoCheck(secpos * STM_SECTOR_SIZE + STM32_FLASH_BASE, STMFLASH_BUF, STM_SECTOR_SIZE / 2); // д����������
		}
		else
		{
			FLASH_WaitForLastOperation(FLASH_WAITETIME);		   // �ȴ��ϴβ������
			STMFLASH_Write_NoCheck(WriteAddr, pBuffer, secremain); // д�Ѿ������˵�,ֱ��д������ʣ������.
		}
		if (NumToWrite == secremain)
			break; // д�������
		else	   // д��δ����
		{
			secpos++;					// ������ַ��1
			secoff = 0;					// ƫ��λ��Ϊ0
			pBuffer += secremain;		// ָ��ƫ��
			WriteAddr += secremain * 2; // д��ַƫ��(16λ���ݵ�ַ,��Ҫ*2)
			NumToWrite -= secremain;	// �ֽ�(16λ)���ݼ�
			if (NumToWrite > (STM_SECTOR_SIZE / 2))
				secremain = STM_SECTOR_SIZE / 2; // ��һ����������д����
			else
				secremain = NumToWrite; // ��һ����������д����
		}
	};
	HAL_FLASH_Lock(); // ����
}
#endif

*/
