/*
项目:		激光测量
编写:		孙继东		SunJD99@Yahoo.com.cn
模块描述:	TFT显示程序定义
文件名:	tft.h
MCU:	STM32F10X		目前是STM32F101R8/STM32F103RB
开始时间:	2011-7-13 10:13:07

HX8347D
HX8347-D(T) 240RGB x 320 dot, 262K color, with internal GRAM, TFT Mobile Single Chip Driver
240*320*2=153 600Bytes

ns
Signal  Symbol  Parameter  Min.  Max.  Unit  Description
DNC_SCL
	tAST Address setup time	0
	tAHT	Address hold time (Write/Read)	10
NCS	
	tCHW	Chip select “H” pulse width		0
	tCS		Chip select setup time (Write)		15
	tRCS	Chip select setup time (Read ID)	45
	tRCSFM	Chip select setup time (Read FM)	355
	tCSF	Chip select wait time (Write/Read)	10
	tCSH	Chip select hold time				10
NWR_SCL	
	tWC		Write cycle						66
		tWRH	Control pulse “H” duration	15
		tWRL	Control pulse “L” duration	15
NRD(ID)	
	tRC		Read cycle (ID)							160
		tRDH	Control pulse “H” duration (ID)	90
		tRDL	Control pulse “L” duration (ID)	45	When read ID data
NRD(FM)	
	tRCFM	Read cycle (FM)						450
	tRDHFM	Control pulse “H” duration (FM)	90
	tRDLFM	Control pulse “L” duration (FM)	355	When read from frame memory
DB17 to DB0
	tDST	Data setup time			10
	tDHT	Data hold time			10
	tRAT	Read access time (ID)		40
	tRATFM	Read access time (FM)		340
	tODH	Output disable time		20	80

内存中数据结构,65536色
D15	D14	D13	D12	D11	D10	D9	D8	D7	D6	D5	D4	D3	D2	D1	D0
R5	R4	R3	R2	R1	G5	G4	G3	G2	G1	G0	B5	B4	B3	B2	B1
R=RED
G=GREEN
B=BLUE
D=DATA
*/


//#include "global.h"
#include "D:\Program Files\IAR Systems\ARM\arm\inc\ST\STM32F2xx_StdPeriph_Driver\stm32f2xx.h"
/*
typedef struct		//显示位置
{
	u8 pX;		//X位置
	u8 dX;		//X大小
	u16 pY;		//Y位置
	u16 dY;		//Y大小
} TypePosition;

typedef struct		//显示位置+颜色
{
	TypePosition Place;		//位置
	u8 color;		//颜色
} TypeDisplay;
*/
//#include "test.global.h"

//以下为宏定义
//#define ILI9320
//#define HX8347D_1
//#define HX8347D_2
#define HX8347D_3

//以下为结构体
typedef struct
{
	vu16 LCD_REG;
	vu16 LCD_RAM;
} LCD_TypeDef;

//以下为常量
#define LCD_BASE	((u32)(0x60000000 | 0x08000000))
#define LCD		((LCD_TypeDef *) LCD_BASE)

#define COMMAND_X_START1	0x06		//X Address Start1 Instruction
#define COMMAND_X_START2	0x07		//X Address Start2 Instruction
#define COMMAND_X_END1		0x08		//X Address End1 Instruction
#define COMMAND_X_END2		0x09		//X Address End2 Instruction
#define COMMAND_Y_START1	0x02		//Y Address Start1 Instruction
#define COMMAND_Y_START2	0x03		//Y Address Start2 Instruction
#define COMMAND_Y_END1		0x04		//Y Address End1 Instruction
#define COMMAND_Y_END2		0x05		//Y Address End2 Instruction
#define COMMAND_WRITE_DATA	0x22		//Write Data to DRAM

#define COLOR_NULL		0		//空
#define COLOR_WRITE		0xffff//白
#define COLOR_BLUE		0x1f	//蓝
#define COLOR_GREEN		0x7e0	//绿
#define COLOR_RED		0xf800	//红
#define COLOR_PURPLE	COLOR_BLUE + COLOR_RED	//紫色
#define COLOR_YELLOW	COLOR_BLUE + COLOR_GREEN	//黄
#define COLOR_ORANGE	COLOR_GREEN + COLOR_RED	//橙
#define COLOR_START		0xe600	//蓝
#define COLOR_MAGENTA	0xf81f	//粉
#define COLOR_CYAN		0x7fff	//青
#define COLOR_GREY		0xf7de	//灰
#define COLOR_NAVY		0x000f
#define COLOR_OLIVE		0x7be0

#define TIMER_4_FLASH	5

//以下为数据表

//以下为显示的字符串

//以下为变量
vu8 ucTimerDisplayMs;
vu16 uiColor;
u16 uiDataBuffer[32];

//以下为位变量

/* (C) CopyRight 2006~2012 Mileseey
中国广东省深圳市宝安区西乡街道桃花源科技创新园A栋313~316
深圳迈测科技有限公司
电话0755-8632 9055
End Of File*/
