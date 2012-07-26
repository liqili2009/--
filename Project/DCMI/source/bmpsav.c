#include "bmpsav.h"
#include "stm322xg_eval_lcd.h"
#include "stm322xg_eval_ioe.h"
#include "camera_api.h"

u16 Line_buf[240];
extern u32 lcdid;
void Save_Frame(void)
{
	u8 res;
	u16 i,j;
	FATFS fatfs;
	UINT WRBytes;            
	FIL fileW;	
			
	res=f_mount(0, &fatfs);
	while(res)LCD_String(20,20,"SD mount failed!",RED);
	res=f_open(&fileW,"0:/DCMI/ph1.bmp",FA_WRITE|FA_CREATE_ALWAYS);//创建并打开
	while(res)LCD_String(20,20,"file create failed!",RED);
	WriteHeader(&fileW);
	WriteBMPInfo(&fileW);
	for(i=0;i<320;i++)
	{
		for(j=0;j<240;j++)
		{
			LCD_Cursor(j,i);
			if((lcdid&0xff00)==0x9300)Line_buf[j]=BGR565toRGB555(LCD_ReadRAM());
			else Line_buf[j]=RGB565toRGB555(LCD_ReadRAM());
		}
		f_write(&fileW,(u8*)Line_buf,480,&WRBytes);
	}
	f_close(&fileW);
	LEDOn(LED4);
	while(1);			
}



void WriteHeader(FIL* file)
{
	UINT WRBytes;
	u8 BMP_header[14];	
	BITMAPFILEHEADER* bmph;

	bmph=(BITMAPFILEHEADER*)BMP_header;
	bmph->bfType=0x4d42;
	bmph->bfSize=0x25836;//文件大小,待定
	bmph->bfReserved1=0;//保留,必须设置为0
	bmph->bfReserved2=0;
	bmph->bfOffBits=54;//从文件头到位图数据所需偏移字节
	f_write(file,BMP_header,14,&WRBytes);
}


void WriteBMPInfo(FIL* file)
{
 	UINT WRBytes;
	u8 BMP_info[40];	
	BITMAPINFOHEADER* bmpi;

	bmpi=(BITMAPINFOHEADER*)BMP_info;
	bmpi->biSize=40;
	bmpi->biWidth=240;
	bmpi->biHeight=320;
	bmpi->biPlanes=1;
	bmpi->biBitCount=16;
	bmpi->biCompression=0;
	bmpi->biSizeImage=0;
	bmpi->biXPelsPerMeter=0;
	bmpi->biYPelsPerMeter=0;
	bmpi->biClrUsed=0;
	bmpi->biClrImportant=0;
	f_write(file,BMP_info,40,&WRBytes);
}