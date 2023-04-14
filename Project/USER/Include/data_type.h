
#ifndef DATA_TYPE_C_HEADER
#define DATA_TYPE_C_HEADER

typedef bit 			    BOOL; 		// 布尔变量（位变量）
typedef unsigned char		CHAR;		// 字符变量
typedef unsigned char 		INT8U; 		// 无符号8位整型变量  
typedef signed char 		INT8S; 		// 有符号8位整型变量  
typedef unsigned int 		INT16U; 	// 无符号16位整型变量 
typedef signed int 		    INT16S; 	// 有符号16位整型变量
typedef unsigned long 		INT32U; 	// 无符号32位整型变量
typedef signed long 		INT32S; 	// 有符号32位整型变量 
typedef float 			    FP32; 		// 单精度浮点数(32位长度) 
typedef double 			    FP64; 		// 双精度浮点数(64位长度)

#define	uchar	unsigned	char 
#define	uint	unsigned	int
#define	uint32	unsigned	double	int

#define		BS(SFR,NUM)		(SFR|=(1<<NUM))		//清bit位
#define		BC(SFR,NUM)		(SFR&=~(1<<NUM))	//bit位置1

#define 	True		1
#define 	False		0
#define 	Enable		1
#define 	Disable		0

#define		BIT0	0x01
#define		BIT1	0x02
#define		BIT2	0x04
#define		BIT3	0x08
#define		BIT4	0x10
#define		BIT5	0x20
#define		BIT6	0x40
#define		BIT7	0x80
#define		BIT8	0x0100
#define		BIT9	0x0200

#define EXT8BITS(name, v1, v2, v3, v4, v5, v6, v7, v8) \
    extern bdata unsigned char name;                   \
    extern bit name##v1;                               \
    extern bit name##v2;                               \
    extern bit name##v3;                               \
    extern bit name##v4;                               \
    extern bit name##v5;                               \
    extern bit name##v6;                               \
    extern bit name##v7;                               \
    extern bit name##v8
#define DEF8BITS(name, v1, v2, v3, v4, v5, v6, v7, v8) \
    bdata unsigned char name;                          \
    sbit name##v1 = name ^ 0;                          \
    sbit name##v2 = name ^ 1;                          \
    sbit name##v3 = name ^ 2;                          \
    sbit name##v4 = name ^ 3;                          \
    sbit name##v5 = name ^ 4;                          \
    sbit name##v6 = name ^ 5;                          \
    sbit name##v7 = name ^ 6;                          \
    sbit name##v8 = name ^ 7
#define WRITE1_8(nbit, the_bit, value) nbit##the_bit = value
#define READ1_8(nbit, the_bit) nbit##the_bit

typedef union
{
	unsigned char byte;
	struct
	{
		uchar bit0 : 1;
		uchar bit1 : 1;
		uchar bit2 : 1;
		uchar bit3 : 1;
		uchar bit4 : 1;
		uchar bit5 : 1;
		uchar bit6 : 1;
		uchar bit7 : 1;
	} bits;
}Flag;	

#endif
