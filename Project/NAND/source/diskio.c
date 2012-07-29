#include "diskio.h"
#include "fsmc_nand.h"
#define DEBUG
//#include "rtc.h"

typedef u16    uint16_t;
typedef u32    uint32_t;
typedef u8    uint8_t;

uint32_t DiskCount = 0 ;

typedef struct
{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t week;
	uint8_t hour;
	uint8_t minutes;
	uint8_t secon;
}tm;

DSTATUS disk_initialize (BYTE drv)
{
#ifdef SD_FLASH
	if(drv==0)
	{
		//if(
		SD_Init();
		//)
		//return 1;//初始化失败，返回未初始化
		//else 
		//return 0;//初始化成功
	}
#else
//	FlashInit();//FSMC_NAND_Init();
	DiskCount = 0 ;
#endif 
	//else 
	//return 2;//盘符不是SD卡，返回无媒体在此驱动器
	return 0;//初始化成功
}

DSTATUS disk_status (BYTE drv)
{
	return drv;
}

DRESULT disk_read (BYTE drv, BYTE *buff, DWORD sector, BYTE count)
{
	if(drv)return RES_PARERR;//返回无效参数
#ifdef SD_FLASH
	if(count==1)
	SD_ReadBlock((uint8_t *)buff, sector*512,  512);
	else 
	SD_ReadMultiBlocks((uint8_t *)buff,sector*512,512,count);
#else

if(count == 1)
{
   FlashReadOneSector(sector>>9, (uint8_t *)buff, 0);	
}
else
{
   NandFlash_ReadMultiSector((uint8_t *)buff , sector>>9 , count );
}

#endif

	return RES_OK;
}

DRESULT disk_write (BYTE drv, const BYTE *buff, DWORD sector, BYTE count)
{
	if(drv)return RES_PARERR;//返回无效参数
#ifdef SD_FLASH
	if(count==1)
	SD_WriteBlock((uint8_t *)buff, sector<<9,  512);
	else 
	SD_WriteMultiBlocks((uint8_t *)buff,sector<<9,512,count);
#else

if(count == 1)
{
	FlashWriteOneSector(sector>>9, (uint8_t *)buff, 0);
}
else
{
    NandFlash_WriteMultiSector((uint8_t *)buff,sector>>9,count); 	 //FlashWriteOneSector(
}

#endif

	return RES_OK;
}
DRESULT disk_ioctl (BYTE drv, BYTE ctrl, void *buff)
{/*
	//return RES_OK;
	  {  
	   DRESULT res = RES_OK;  
	   uint32_t result;  
	  
	      if (drv){ return RES_PARERR;}  
	     
	      switch(ctrl)  
	      {  
	       case CTRL_SYNC:  
	           break;  
	       case GET_BLOCK_SIZE:  
	           *(DWORD*)buff = NAND_BLOCK_SIZE;  
	           break;  
	       case GET_SECTOR_COUNT:  
	           *(DWORD*)buff = (((NAND_MAX_ZONE/2) * NAND_ZONE_SIZE) * NAND_BLOCK_SIZE);  
               break;  
	       case GET_SECTOR_SIZE:  
	           *(WORD*)buff = NAND_PAGE_SIZE;  
              break;  
	       default:  res = RES_PARERR;  
           break;  
	    }  
	      return res;  
	  }  	*/   	
}


DWORD get_fattime(void)
{
	DWORD temp=0;
	//Get_Time();
	tm time;
	time.year = 2000;
	time.month = 12	;
	time.day   = 21;
	time.hour  = 11 ;
	time.minutes =22;
	time.secon	 =11;


	temp|=((time.year-1980)<<25);
	temp|=(time.month<<21);
	temp|=(time.day<<16);
	temp|=(time.hour<<11);
	temp|=(time.minutes<<5);
	temp|=(time.secon/2);
	return temp;
}
/******************* (C) COPYRIGHT 2010 OF WANGHAIDONG *****END OF FILE****/
