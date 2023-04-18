#include "Function_Init.H"
/*

#define W25_CS_ENABLE()         {W25_CS(0); us_delay(10);}
#define W25_CS_DISABLE()        {W25_CS(1); us_delay(10);}
#define SPI_Delay()             us_delay(1)

FLASH_SectorErase(0);           实测 9.12ms
FLASH_PageWrite(buf, 0, 256);   实测 18ms
FLASH_BufferRead(bufR, 0, 256); 实测 16.7ms








*/
void Print_HEX16(uint8_t *sur, uint16_t size)
{
    uint16_t i;
    uint8_t j;
    printf("\n");
    for (i = 0; i < size; i++)
    {
        printf("%2x ", *sur++);
        if (++j > 63)
        {
            j = 0;
            printf("|%4x|\n",i);
        }
    }
    printf("\n");
}

void SPI_FlashDebug(void)
{


    //




    uint8_t buf[SECTOR_SIZE+0x30];
    // uint8_t bufR[256];
    uint16_t i;
    static uint8_t hh;
    // // // printf("\r\n");
    // // // printf("start\r\n");
    // // // memset(buf, 0, sizeof(buf)); // 数据清零
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
    FlashSPI_Write(buf, USER_RESERVED_SECTOR0_ADDR-0x10, sizeof(buf));

    // // // // FLASH_PageWrite(buf, 256, 256);
    // // // memset(bufR, 0, sizeof(bufR)); // 数据清零

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

        // memset(colordata, 0, sizeof(color_group_TypeDef)); // 数据清零
        // memcpy(colordata, EF_DefaultData[num].color_array, EF_DefaultData[EF_Work.EF_ID].color_sum * 4);

// void FlashSPI_RandomRead (uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
// {

// }

void FlashSPI_Write(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t pwrite; // 写flash的指针
    uint16_t pread;  // 源数据待被读取的指针
    uint8_t *sur, *tar;
    uint16_t i;
    uint16_t pageAddr;    // 当前页首地址
    uint16_t pageOffset;  // 页内偏移地址
    uint16_t writedNum;   // 已写的字节数
    uint16_t pageRemain;  // 当前页内剩余空间
    uint16_t writeRemain; // 剩余需写字节数
    // // uint8_t flashbuffer[SPI_FLASH_PageSize];
    uint8_t flashbuffer[SECTOR_SIZE];
    writedNum = 0;
    pwrite = WriteAddr;
    pread = 0;
    for (pread = 0; pread < NumByteToWrite;)
    {
        // // // pageOffset = pwrite % SPI_FLASH_PageSize;                     // 页内偏移地址
        pageOffset = pwrite % SECTOR_SIZE; // 页内偏移地址
        pageAddr = pwrite - pageOffset;    // 当前页首地址
        // // // pageRemain = SPI_FLASH_PageSize - pageOffset;                 // 页内剩余空间
        pageRemain = SECTOR_SIZE - pageOffset; // 页内剩余空间
        writeRemain = NumByteToWrite - pread;  // 还未被写的字节数
        // // // FLASH_BufferRead(flashbuffer, pageAddr, sizeof(flashbuffer)); // 暂存原来Flash本页里的数据
        ROM_BufferRead(flashbuffer, pageAddr, sizeof(flashbuffer)); // 暂存原来Flash本页里的数据
        sur = pBuffer + pread;
        tar = flashbuffer + pageOffset;
        if (pageRemain >= writeRemain) // 当前页可以写完剩余数据，写完剩余数据
        {
            memcpy(tar, sur, writeRemain); // 拷贝新数据
            // // // // FLASH_PageErase(pageAddr);     // 擦除本页
            // // // // FLASH_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer));
            EraseSector(pageAddr);                                   // 擦除扇区
            ProgramPage(pageAddr, sizeof(flashbuffer), flashbuffer); // 写入新数据
            pwrite += writeRemain;
            pread += writeRemain;
        }
        else // 当前页写不完,先写满当前页
        {
            memcpy(tar, sur, pageRemain); // 拷贝新数据
            // // // // FLASH_PageErase(pageAddr);      // 擦除本页
            // // // // FLASH_PageWrite(flashbuffer, pageAddr, sizeof(flashbuffer));
            EraseSector(pageAddr);                                   // 擦除扇区
            ProgramPage(pageAddr, sizeof(flashbuffer), flashbuffer); // 写入新数据
            pwrite += pageRemain;
            pread += pageRemain;
        }
    }
}

void ROM_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint8_t *sur, *tar;
    sur = (uint8_t *)ReadAddr;
    tar = pBuffer;
    memcpy(tar, sur, NumByteToRead); // 拷贝新数据
}














/*

// 从指定地址开始写入指定长度的数据
// WriteAddr:起始地址(此地址必须为2的倍数!!)
// pBuffer:数据指针
// NumToWrite:半字(16位)数(就是要写入的16位数据的个数.)
#if STM32_FLASH_SIZE < 256
#define STM_SECTOR_SIZE 1024 // 字节
#else
#define STM_SECTOR_SIZE 2048
#endif
u16 STMFLASH_BUF[STM_SECTOR_SIZE / 2]; // 最多是2K字节
void STMFLASH_Write(u32 WriteAddr, u16 *pBuffer, u16 NumToWrite)
{
	u32 secpos;	   // 扇区地址
	u16 secoff;	   // 扇区内偏移地址(16位字计算)
	u16 secremain; // 扇区内剩余地址(16位字计算)
	u16 i;
	u32 offaddr; // 去掉0X08000000后的地址

	if (WriteAddr < STM32_FLASH_BASE || (WriteAddr >= (STM32_FLASH_BASE + 1024 * STM32_FLASH_SIZE)))
		return; // 非法地址

	HAL_FLASH_Unlock();						  // 解锁
	offaddr = WriteAddr - STM32_FLASH_BASE;	  // 实际偏移地址.
	secpos = offaddr / STM_SECTOR_SIZE;		  // 扇区地址  0~127 for STM32F103RBT6
	secoff = (offaddr % STM_SECTOR_SIZE) / 2; // 在扇区内的偏移(2个字节为基本单位.)
	secremain = STM_SECTOR_SIZE / 2 - secoff; // 扇区剩余空间大小
	if (NumToWrite <= secremain)
		secremain = NumToWrite; // 不大于该扇区范围
	while (1)
	{
		STMFLASH_Read(secpos * STM_SECTOR_SIZE + STM32_FLASH_BASE, STMFLASH_BUF, STM_SECTOR_SIZE / 2); // 读出整个扇区的内容
		for (i = 0; i < secremain; i++)																   // 校验数据
		{s
			if (STMFLASH_BUF[secoff + i] != 0XFFFF)
				break; // 需要擦除
		}
		if (i < secremain) // 需要擦除
		{
			FLASH_PageErase(secpos * STM_SECTOR_SIZE + STM32_FLASH_BASE); // 擦除这个扇区
			FLASH_WaitForLastOperation(FLASH_WAITETIME);				  // 等待上次操作完成
			CLEAR_BIT(FLASH->CR, FLASH_CR_PER);							  // 清除CR寄存器的PER位，此操作应该在FLASH_PageErase()中完成！
												// 但是HAL库里面并没有做，应该是HAL库bug！
			for (i = 0; i < secremain; i++) // 复制
			{
				STMFLASH_BUF[i + secoff] = pBuffer[i];
			}
			STMFLASH_Write_NoCheck(secpos * STM_SECTOR_SIZE + STM32_FLASH_BASE, STMFLASH_BUF, STM_SECTOR_SIZE / 2); // 写入整个扇区
		}
		else
		{
			FLASH_WaitForLastOperation(FLASH_WAITETIME);		   // 等待上次操作完成
			STMFLASH_Write_NoCheck(WriteAddr, pBuffer, secremain); // 写已经擦除了的,直接写入扇区剩余区间.
		}
		if (NumToWrite == secremain)
			break; // 写入结束了
		else	   // 写入未结束
		{
			secpos++;					// 扇区地址增1
			secoff = 0;					// 偏移位置为0
			pBuffer += secremain;		// 指针偏移
			WriteAddr += secremain * 2; // 写地址偏移(16位数据地址,需要*2)
			NumToWrite -= secremain;	// 字节(16位)数递减
			if (NumToWrite > (STM_SECTOR_SIZE / 2))
				secremain = STM_SECTOR_SIZE / 2; // 下一个扇区还是写不完
			else
				secremain = NumToWrite; // 下一个扇区可以写完了
		}
	};
	HAL_FLASH_Lock(); // 上锁
}
#endif

*/
