#include "diskio.h"
#include "fsmc_nand.h"
#include "ff.h"			/* FatFs configurations and declarations */
#include  "test.h"
#include "stm322xg_eval_lcd.h"

# define NULL 0
unsigned char ID_Code[4];

#define BUFFER_SIZE         0x800
#define NAND_HY_MakerID     0xEC//0xAD
#define NAND_HY_DeviceID    0XD5//0xF1  
#define BUFFER_SIZE           2048
//#define NAND_ST_MakerID     0x20
//#define NAND_ST_DeviceID    0x73
#define NAND_ST_MakerID     0xEC
#define NAND_ST_DeviceID    0xd5




/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
NAND_IDTypeDef NAND_ID;
GPIO_InitTypeDef GPIO_InitStructure;
NAND_ADDRESS WriteReadAddr;

extern u8 TxBuffer[BUFFER_SIZE], RxBuffer[BUFFER_SIZE];

ErrorStatus HSEStartUpStatus;
u8 Tx1Buffer[BUFFER_SIZE], Rx1Buffer[BUFFER_SIZE], Tx2Buffer[BUFFER_SIZE], Rx2Buffer[BUFFER_SIZE];
vu32 PageNumber = 2, status= 0;
u32 j = 0;
extern __IO uint32_t WriteReadStatus ;

//*******************************************************
void test_nandflsh_write_and_read(void)
{
       FSMC_NAND_Init();

  /* NAND read ID command */
  FSMC_NAND_ReadID(&NAND_ID);

  /* Verify the NAND ID */
  if((NAND_ID.Maker_ID == NAND_ST_MakerID) && (NAND_ID.Device_ID == NAND_ST_DeviceID))
  {
    LCD_DisplayStringLine(LCD_LINE_6, (uint8_t *)"ReadID is Ok");
    /* NAND memory address to write to */ 
    WriteReadAddr.Zone = 0x00;
    WriteReadAddr.Block = 0x00;
    WriteReadAddr.Page = 0x00; 

    /* Erase the NAND first Block */
    status = FSMC_NAND_EraseBlock(WriteReadAddr);

    /* Write data to FSMC NAND memory */
    /* Fill the buffer to send */
    Fill_Buffer(TxBuffer, BUFFER_SIZE , 0x66);


    status = FSMC_NAND_WriteSmallPage(TxBuffer, WriteReadAddr, PageNumber);

    /* Read back the written data */
    status = FSMC_NAND_ReadSmallPage (RxBuffer, WriteReadAddr, PageNumber);

   
    /* Verify the written data */
    for(j = 0; j < BUFFER_SIZE; j++)
    {
      if(TxBuffer[j] != RxBuffer[j])
      {     
        WriteReadStatus++;
      } 
    }

    if (WriteReadStatus == 0)
    {
	  LCD_DisplayStringLine(LCD_LINE_9, (uint8_t *)"Readback is Ok");
    }
    else
    { 
	   LCD_DisplayStringLine(LCD_LINE_9, (uint8_t *)"Readback failed"); 
    }
  }
  else
  {
     LCD_DisplayStringLine(LCD_LINE_6, (uint8_t *)"ReadID is wrong");
  }

  while(1)
  {
  }
    
}


void test_Fatfs_write_and_read(void)
{

    FATFS fs[2];        
    FIL fsrc, fdst;     
//    BYTE buffer1[128];   
    FRESULT res;        
    UINT br, bw; 
	  FATFS *pfs;  
	  DWORD clust;  
        
	NAND_Format(); 
    f_mount(0, &fs[0]); 
	res = f_mkfs(0,1,2048);
//    f_mount(1, &fs[1]);
  
	
//	res = f_getfree("/", &clust, &pfs);  

	Fill_Buffer(Tx1Buffer, BUFFER_SIZE , 0x1);

   loop1: 
    res = f_open(&fdst, "dstfile.txt", FA_CREATE_ALWAYS | FA_WRITE); 
    if(res != FR_OK) 
    { 
        goto loop1; 
    }
	loop2:
	res = f_write(&fdst, Tx1Buffer, BUFFER_SIZE, &bw);
	 if(res != FR_OK) 
    { 
        goto loop2; 
    }     

/*   loop3: 
    res = f_open(&fsrc, "dstfile.txt", FA_OPEN_EXISTING | FA_READ); 
    if(res != FR_OK) 
    { 
        goto loop3; 
    }  */
	loop4:
	res = f_read(&fdst, Rx1Buffer, BUFFER_SIZE, &br);
    if(res != FR_OK) 
    { 
        goto loop4; 
    }  
	 
	for(j = 0; j < BUFFER_SIZE; j++)
	{
		if(Tx1Buffer[j] != Rx1Buffer[j])
		{     
			WriteReadStatus++;
		} 
	/*	if(Tx2Buffer[j] != Rx2Buffer[j])
		{     
			WriteReadStatus++;
		} */
	}
	
	if (WriteReadStatus == 0)
	{
	
		GPIO_SetBits(GPIOF, GPIO_Pin_6);	//读写正常
	}
	else
	{ 
	
		GPIO_SetBits(GPIOF, GPIO_Pin_7);     
	}

    /* 关闭文件 */ 
    f_close(&fsrc); 
    f_close(&fdst);

    /* 注销工作区 */ 
    f_mount(0, NULL); 
//    f_mount(1, NULL); 
 
}



/*******************************************************************************
* Function name : Fill_Buffer
* Description   : Fill the buffer
* Input         : - pBuffer: pointer on the Buffer to fill
*                 - BufferSize: size of the buffer to fill
*                 - Offset: first value to fill on the Buffer
* Output param  : None
*******************************************************************************/
/*void Fill_Buffer(u8 *pBuffer, u16 BufferLenght, u32 Offset)
{
  u16 IndexTmp = 0;

  for (IndexTmp = 0; IndexTmp < BufferLenght; IndexTmp++ )
  {
    pBuffer[IndexTmp] = IndexTmp + Offset;
  }
}
*/