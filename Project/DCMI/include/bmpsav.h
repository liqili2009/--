#ifndef __BMPSAV_H
#define __BMPSAV_H

#include "stm32f2xx.h"
//#include "ff.h"
#include "integer.h"
																	
#define RGB565toRGB555(RGB) ((RGB&0xF800)>>1)+((RGB&0x7C0)>>1)+(RGB&0x1f)
#define BGR565toRGB555(BGR) ((BGR&0x1f)<<10)+((BGR&0x7C0)>>1)+((BGR&0xF800)>>11)

#pragma pack(1)
typedef struct tagBITMAPFILEHEADER 
{ 
	WORD bfType;   
	DWORD bfSize; 
	WORD bfReserved1; 
	WORD bfReserved2; 
	DWORD bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
	DWORD biSize; 
	LONG biWidth; 
	LONG biHeight; 
	WORD biPlanes; 
	WORD biBitCount; 
	DWORD biCompression; 
	DWORD biSizeImage; 
	LONG biXPelsPerMeter; 
	LONG biYPelsPerMeter; 
	DWORD biClrUsed; 
	DWORD biClrImportant;
} BITMAPINFOHEADER;

void Save_Frame(void);
void WriteHeader(FIL* file);
void WriteBMPInfo(FIL* file);
u16 LCD_BGR2RGB(u16 c);

#endif