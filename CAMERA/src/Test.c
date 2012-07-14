/*
项目:		激光测量
编写:		孙继东		SunJD99@Yahoo.com.cn
模块描述:	TFT显示程序定义
文件名:	tft.h
MCU:	STM32F10X		目前是STM32F101R8/STM32F103RB
开始时间:	2011-7-13 10:13:07
*/
#include "test.h"

/*以下为基本函数

描述:		发送数据到LCD
输入:		Data
输出:		无

HX8347D SPI速度
Write[received]		tSCYC	ns		80	- IOVCC=1.65~2.8V
Write[received]	tSCYC	ns		25	IOVCC=2.8~3.3V
Read[transmitted]		tSCYC	ns		200	-
25nS=40MHz
*/
void SendLcData(u16 Data)
{
	LCD->LCD_RAM = Data;
}

/*
描述:		发送命令到LCD
输入:		Command
输出:		无
*/
void SendLcdCommand(u8 Command)
{
	LCD->LCD_REG = Command;		//片选禁止
}

/*
描述:		发送命令到LCD
输入:		Command
输出:		无
*/
void SendLcdCommandData(u8 Command, u16 Data)
{
	/* Write 16-bit Index, then Write Reg */
	LCD->LCD_REG = Command;
	/* Write 16-bit Reg */
	LCD->LCD_RAM = Data;
}

u16 ReadLCDRegister(u8 Command)
{
	/* Write 16-bit Index (then Read Reg) */
	LCD->LCD_REG = Command;
	/* Read 16-bit Reg */
	return (LCD->LCD_RAM);
}

u16 ReadLcData(void)
{
	return (LCD->LCD_RAM);
}

//以下为正常流程

/*
描述:		初始化LCD
输入:		无
输出:		无
*/
void InitializeDisplay(void)
{
//	SetPortLcdResetHigh();
//	Delay(4);
//	SetPortLcdResetLow();
//	Delay(2);
//	SetPortLcdResetHigh();
//	Delay(2);

//	id = ReadLCDRegister(0);

#ifdef HX8347D_1
	SendLcdCommandData(0x2e, 0x79);		//
	SendLcdCommandData(0xee, 0x0c);		//

	//Driving ability Setting
	SendLcdCommandData(0xea, 0x00);		//Power control internal use,PTBA[15:8]
	SendLcdCommandData(0xeb, 0x20);		//Power control internal use,PTBA[7:0]
	SendLcdCommandData(0xec, 0x08);		//Source control internal use,STBA[15:8]
	SendLcdCommandData(0xed, 0xc4);		//Source control internal use,STBA[7:0]
	SendLcdCommandData(0xe8, 0x44);		//Source OP control_Normal,OPON[7:0]
	SendLcdCommandData(0xe9, 0x44);		//Source OP control_IDLE, OPON1[7:0]
	SendLcdCommandData(0xf1, 0x01);		//OTPS1B
	SendLcdCommandData(0xf2, 0x10);		//GEN
	SendLcdCommandData(0x27, 0xa3);		//

	//Gamma 2.2 Setting
	SendLcdCommandData(0x40, 0x1c);
	SendLcdCommandData(0x41, 0x21);
	SendLcdCommandData(0x42, 0x1f);
	SendLcdCommandData(0x43, 0x0a);
	SendLcdCommandData(0x44, 0x05);
	SendLcdCommandData(0x45, 0x0e);
	SendLcdCommandData(0x46, 0x17);
	SendLcdCommandData(0x47, 0x49);
	SendLcdCommandData(0x48, 0x05);
	SendLcdCommandData(0x49, 0x14);
	SendLcdCommandData(0x4a, 0x19);
	SendLcdCommandData(0x4b, 0x1b);
	SendLcdCommandData(0x4c, 0x19);
	SendLcdCommandData(0x50, 0x00);
	SendLcdCommandData(0x51, 0x2c);
	SendLcdCommandData(0x52, 0x34);
	SendLcdCommandData(0x53, 0x37);
	SendLcdCommandData(0x54, 0x38);
	SendLcdCommandData(0x55, 0x3d);
	SendLcdCommandData(0x56, 0x43);
	SendLcdCommandData(0x57, 0x7c);
	SendLcdCommandData(0x58, 0x0f);
	SendLcdCommandData(0x59, 0x05);
	SendLcdCommandData(0x5a, 0x07);
	SendLcdCommandData(0x5b, 0x0e);
	SendLcdCommandData(0x5c, 0x1b);
	SendLcdCommandData(0x5d, 0xff);

	//Power Voltage Setting
	SendLcdCommandData(0x1b, 0x32);		//VRH=4.65V
	SendLcdCommandData(0x1a, 0x05);		//BT (VGH~15V,VGL~-10V,DDVDH~5V)
	SendLcdCommandData(0x24, 0xa0);		//VMH(VCOM High voltage ~3.53V)
	SendLcdCommandData(0x25, 0x69);		//VML(VCOM Low voltage -2.03V)
	//VCOM offset
	SendLcdCommandData(0x23, 0x33);		//for Flicker adjust //can reload from OTP

	//Power on Setting
	SendLcdCommandData(0x18, 0x36);		//I/P_RADJ,N/P_RADJ, Normal mode 75Hz
	SendLcdCommandData(0x19, 0x01);		//OSC_EN='1', start Osc
	SendLcdCommandData(0x01, 0x00);		//DP_STB='0', out deep sleep
	SendLcdCommandData(0x1f, 0x88);		//GAS=1, VOMG=00, PON=0, DK=1, XDK=0, DVDH_TRI=0, STB=0
	Delay(5);
	SendLcdCommandData(0x1f, 0x82);		//GAS=1, VOMG=00, PON=0, DK=0, XDK=0, DVDH_TRI=0, STB=0
	Delay(5);
	SendLcdCommandData(0x1f, 0x92);		//GAS=1, VOMG=00, PON=1, DK=0, XDK=0, DVDH_TRI=0, STB=0
	Delay(5);
	SendLcdCommandData(0x1f, 0xd2);		//GAS=1, VOMG=10, PON=1, DK=0, XDK=0, DDVDH_TRI=0, STB=0
	Delay(5);

	//262k/65k color selection
	SendLcdCommandData(0x17, 0x05);		//default 0x06 262k color // 0x05 65k color

	//SET PANEL
	SendLcdCommandData(0x36, 0x02);		//SS_P, GS_P,REV_P,BGR_P
	//Display ON Setting
	SendLcdCommandData(0x28, 0x38);		//GON=1, DTE=1, D=1000
	Delay(40);
	SendLcdCommandData(0x28, 0x3c);		//GON=1, DTE=1, D=1100

#endif
#ifdef HX8347D_2

	SendLcdCommandData(0x01, 0x0000);
	SendLcdCommandData(0xEA, 0x0000);		//Reset Power Control 1
	SendLcdCommandData(0xEB, 0x0020);		//Power Control 2
	SendLcdCommandData(0xEC, 0x000C);		//Power Control 3
	SendLcdCommandData(0xED, 0x00C4);		//Power Control 4
	SendLcdCommandData(0xE8, 0x0040);		//Source OPON_N
	SendLcdCommandData(0xE9, 0x0038);		//Source OPON_I
	SendLcdCommandData(0xF1, 0x0001);		//
	SendLcdCommandData(0xF2, 0x0010);		//
	SendLcdCommandData(0x27, 0x00A3);		//Display Control 2

	//Power On sequence --------------------------------------------------
	SendLcdCommandData(0x1B, 0x001B);		//Power Control 2
	SendLcdCommandData(0x1A, 0x0001);		//Power Control 1
	SendLcdCommandData(0x24, 0x002F);		//Vcom Control 2
	SendLcdCommandData(0x25, 0x0057);		//Vcom Control 3
	SendLcdCommandData(0x23, 0x008D);		//Vcom Control 1

	//Gamma settings  ----------------------------------------------------
	SendLcdCommandData(0x40, 0x0000);
	SendLcdCommandData(0x41, 0x0000);
	SendLcdCommandData(0x42, 0x0001);
	SendLcdCommandData(0x43, 0x0013);
	SendLcdCommandData(0x44, 0x0010);
	SendLcdCommandData(0x45, 0x0026);
	SendLcdCommandData(0x46, 0x0008);
	SendLcdCommandData(0x47, 0x0051);
	SendLcdCommandData(0x48, 0x0002);
	SendLcdCommandData(0x49, 0x0012);
	SendLcdCommandData(0x4A, 0x0018);
	SendLcdCommandData(0x4B, 0x0019);
	SendLcdCommandData(0x4C, 0x0014);
	SendLcdCommandData(0x50, 0x0019);
	SendLcdCommandData(0x51, 0x002F);
	SendLcdCommandData(0x52, 0x002C);
	SendLcdCommandData(0x53, 0x003E);
	SendLcdCommandData(0x54, 0x003F);
	SendLcdCommandData(0x55, 0x003F);
	SendLcdCommandData(0x56, 0x002E);
	SendLcdCommandData(0x57, 0x0077);
	SendLcdCommandData(0x58, 0x000B);
	SendLcdCommandData(0x59, 0x0006);
	SendLcdCommandData(0x5A, 0x0007);
	SendLcdCommandData(0x5B, 0x000D);
	SendLcdCommandData(0x5C, 0x001D);
	SendLcdCommandData(0x5D, 0x00CC);

	//Power + Osc ----------------------------------------------------
	SendLcdCommandData(0x18, 0x0036);		//OSC Control 1
	SendLcdCommandData(0x19, 0x0001);		//OSC Control 2
	SendLcdCommandData(0x01, 0x0000);		//Display Mode Control
	SendLcdCommandData(0x1F, 0x0088);		//Power Control 6
	Delay(5);          		//Delay 5 ms
	SendLcdCommandData(0x1F, 0x0080);		//Power Control 6
	Delay(5);          		//Delay 5 ms
	SendLcdCommandData(0x1F, 0x0090);		//Power Control 6
	Delay(5);          		//Delay 5 ms
	SendLcdCommandData(0x1F, 0x00D0);		//Power Control 6
	Delay(5);          		//Delay 5 ms

	SendLcdCommandData(0x17, 0x0005);		//Colmod 16Bit/Pixel

	SendLcdCommandData(0x36, 0x0000);		//Panel Characteristic
	SendLcdCommandData(0x28, 0x0038);		//Display Control 3
	Delay(40);
	SendLcdCommandData(0x28, 0x003C);		//Display Control 3
	SendLcdCommandData(0x16, 0x0008);
#endif
#ifdef HX8347D_3
	SendLcdCommandData(0xEA, 0x00);
	SendLcdCommandData(0xEB, 0x20);
	SendLcdCommandData(0xEC, 0x0C);
	SendLcdCommandData(0xED, 0xC4);
	SendLcdCommandData(0xE8, 0x40);
	SendLcdCommandData(0xE9, 0x38);
	SendLcdCommandData(0xF1, 0x01);
	SendLcdCommandData(0xF2, 0x10);
	SendLcdCommandData(0x27, 0xA3);
	//GAMMA SETING
	SendLcdCommandData(0x40, 0x00);
	SendLcdCommandData(0x41, 0x00);
	SendLcdCommandData(0x42, 0x01);
	SendLcdCommandData(0x43, 0x12);
	SendLcdCommandData(0x44, 0x10);
	SendLcdCommandData(0x45, 0x26);
	SendLcdCommandData(0x46, 0x08);
	SendLcdCommandData(0x47, 0x53);
	SendLcdCommandData(0x48, 0x02);
	SendLcdCommandData(0x49, 0x15);
	SendLcdCommandData(0x4A, 0x19);
	SendLcdCommandData(0x4B, 0x19);
	SendLcdCommandData(0x4C, 0x16);
	SendLcdCommandData(0x50, 0x19);
	SendLcdCommandData(0x51, 0x2F);
	SendLcdCommandData(0x52, 0x2D);
	SendLcdCommandData(0x53, 0x3E);
	SendLcdCommandData(0x54, 0x3F);
	SendLcdCommandData(0x55, 0x3F);
	SendLcdCommandData(0x56, 0x2C);
	SendLcdCommandData(0x57, 0x77);
	SendLcdCommandData(0x58, 0x09);
	SendLcdCommandData(0x59, 0x06);
	SendLcdCommandData(0x5A, 0x06);
	SendLcdCommandData(0x5B, 0x0A);
	SendLcdCommandData(0x5C, 0x1D);
	SendLcdCommandData(0x5D, 0xCC);
	SendLcdCommandData(0x1B, 0x1B);
	SendLcdCommandData(0x1A, 0x01);
	SendLcdCommandData(0x24, 0x2f);
	SendLcdCommandData(0x25, 0x57);
	SendLcdCommandData(0x23, 0x8a);
	//POWER SETING
	SendLcdCommandData(0x18, 0x36);
	SendLcdCommandData(0x19, 0x01);
	SendLcdCommandData(0x01, 0x00);
	SendLcdCommandData(0x1F, 0x88);
	Delay(10);
	SendLcdCommandData(0x1F, 0x80);
	Delay(10);
	SendLcdCommandData(0x1F, 0x90);
	Delay(10);
	SendLcdCommandData(0x1F, 0xD0);
	Delay(10);
	SendLcdCommandData(0x17, 0x05);
	SendLcdCommandData(0x36, 0x00);
	SendLcdCommandData(0x28, 0x38);
	Delay(50);
	SendLcdCommandData(0x28, 0x3C);
	SendLcdCommandData(0x16, 0);
#endif

	uiColor = COLOR_GREEN;
//	SetActiveBuzzer(1);
}

/*	以下为接口函数

描述:		在某位置显示一个ASCII字符
输入:		某位置;颜色;字符内码(0x30~0x5a),超过的清除显示
输出:		无
*/

/* (C) COPYRIGHT 2006~2012 Mileseey
中国广东省深圳市宝安区西乡街道桃花源科技创新园A栋313~316
深圳迈测科技有限公司
电话0755-8632 9055
End Of File*/
