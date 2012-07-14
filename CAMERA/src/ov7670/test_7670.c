/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"
#include "stm32_eval.h"
#include "stm322xg_eval_lcd.h"
#include "usart.h"
//#include "LCD/LCD.h"
#include "dcmi_OV7670.h"
 /* Private define ------------------------------------------------------------*/
#define LCD_REG              (*((volatile unsigned short *) 0x6F000000)) /* RS = 0 */
#define LCD_RAM              (*((volatile unsigned short *) 0x6F010000)) /* R = 1 */
/** @addtogroup STM32F2xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup IOToggle
  * @{
  */ 


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */

/*
static const u8 bmpheader[54]={//构造bmp首部
	0x42, 0x4D, 0x36, 0x84, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 
	0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x84, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
//FatFS用到的变量
static FATFS fs;            // Work area (file system object) for logical drive
static FIL fsrc, fdst;      // file objects
static FRESULT res;         // FatFs function common result code
static BYTE buffer[1028];
static UINT br,bw;
static BYTE temp[323];

//++++++++++++++++++++++++++++++++++++++++++++++
//bmp文件格式的数据头结构
//++++++++++++++++++++++++++++++++++++++++++++++
typedef __packed struct
{
	u8  pic_head[2];				//1
	u16 pic_size_l;			    //2
	u16 pic_size_h;			    //3
	u16 pic_nc1;				    //4
	u16 pic_nc2;				    //5
	u16 pic_data_address_l;	    //6
	u16 pic_data_address_h;		//7	
	u16 pic_message_head_len_l;	//8
	u16 pic_message_head_len_h;	//9
	u16 pic_w_l;					//10
	u16 pic_w_h;				    //11
	u16 pic_h_l;				    //12
	u16 pic_h_h;				    //13	
	u16 pic_bit;				    //14
	u16 pic_dip;				    //15
	u16 pic_zip_l;			    //16
	u16 pic_zip_h;			    //17
	u16 pic_data_size_l;		    //18
	u16 pic_data_size_h;		    //19
	u16 pic_dipx_l;			    //20
	u16 pic_dipx_h;			    //21	
	u16 pic_dipy_l;			    //22
	u16 pic_dipy_h;			    //23
	u16 pic_color_index_l;	    //24
	u16 pic_color_index_h;	    //25
	u16 pic_other_l;			    //26
	u16 pic_other_h;			    //27
	u16 pic_color_p01;		    //28
	u16 pic_color_p02;		    //29
	u16 pic_color_p03;		    //30
	u16 pic_color_p04;		    //31
	u16 pic_color_p05;		    //32
	u16 pic_color_p06;		    //33
	u16 pic_color_p07;		    //34
	u16 pic_color_p08;			//35			
}BMP_HEAD;
*/

int test_7670(void)
{
	OV7670_IDTypeDef OV7670ID;
	RCC_ClocksTypeDef SYS_Clocks;
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f2xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
        system_stm32f2xx.c file
     */
	RCC_GetClocksFreq(&SYS_Clocks);

	USART_Configuration();
	USART_NVIC_Config();

	printf("SYSCLK:%dM\r\n",SYS_Clocks.SYSCLK_Frequency/1000000);
	printf("HCLK:%dM\r\n",SYS_Clocks.HCLK_Frequency/1000000);
	printf("PCLK1:%dM\r\n",SYS_Clocks.PCLK1_Frequency/1000000);
	printf("PCLK2:%dM\r\n",SYS_Clocks.PCLK2_Frequency/1000000);

	/*LCD_Initializtion();
	LCD_Clear(White);*/

	/* Initialize the LCD */
	STM322xG_LCD_Init();
#ifdef CAMERA
	LCD_Clear(LCD_COLOR_BLUE);
#else
	LCD_Clear(LCD_COLOR_WHITE);
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_DisplayStringLine(LINE(2), "   Camera Init..");
#endif
	

	printf("\r\n\r\nWelcome to WaveShare STM32F2 series MCU Board Open207Z\r\n");
	printf("OV7670 Init..\r\n");
	if(DCMI_OV7670_Init()==0){
		printf("Camera Have Init..\r\n");
	
		}
	else {
		printf("OV7670 Init fails!!\r\n");
	
		}

		DCMI_OV7670_ReadID(&OV7670ID);
	if(DCMI_OV7670_ReadID(&OV7670ID)==0)
	{	
		if(OV7670ID.Manufacturer_ID1==0x7f || OV7670ID.Manufacturer_ID2==0xa2 ||OV7670ID.Version==0x73 ||OV7670ID.PID==0x76)
			printf("OV7670 ID:0x%x 0x%x 0x%x 0x%x\r\n",OV7670ID.Manufacturer_ID1, OV7670ID.Manufacturer_ID2, OV7670ID.PID, OV7670ID.Version);
		else
			printf("OV7670 ID is Error!\r\n");
	}
			
	/*LCD_WriteReg(0x0011,0x6078);
	LCD_SetCursor(0,0);
	LCD_REG = 0x0022;*/


	LCD_DisplayStringLine(LINE(2), "                ");
		/* LCD Display window */
	#if defined (QQVGA_SIZE)
		LCD_SetDisplayWindow(_X(60), _Y(80), 120, 160);
	#elif defined (QVGA_SIZE)
		LCD_SetDisplayWindow(0, 0, 240, 320);
	#endif
		LCD_WriteRAM_Prepare();

	/* Start Image capture and Display on the LCD *****************************/
    /* Enable DMA transfer */
    DMA_Cmd(DMA2_Stream1, ENABLE);

    /* Enable DCMI interface */
    DCMI_Cmd(ENABLE); 

    /* Start Image capture */ 
    DCMI_CaptureCmd(ENABLE);
	
	if(DCMI_SingleRandomWrite_(0x71, 0x80)!=0); //color test	on
	delay_ms(0x5fff);
	if(DCMI_SingleRandomWrite_(0x71, 0x00)!=0); //color test off

	while (1)
	{
	}
}

/*
static void Save_as_bmp(void)
{ u32 a;
  u16 ReadValue; 
  s32 tx,ty;
  u8 R,G,B;
  char s[30];

  //挂载文件系统
  f_mount(0, &fs);

  sprintf(s, "pic%d.bmp",pic_counter);
  //建立新文件
  res = f_open(&fdst, s, FA_CREATE_ALWAYS | FA_WRITE);
  if(res!=FR_OK){
     //f_mount(0, NULL); 
     // MSD_Init();//重新初始化SD卡
	// return;
  }




  //构造bmp头
  res = f_write(&fdst, bmpheader, 54, &bw);//写入BMP首部
          
  //Set_Cs;
  //LCD_GPIO_INPUT();
 // FIFO_CS_L(); 

  // Copy source to destination
	 for (ty = 0; ty < 240; ty++)
     {
		  for(tx=319;tx>=0;tx--)
          { 	     	  		       
		   FIFO_RD_L();	
		   ReadValue = ((GPIO_ReadInputData(GPIOB))&0XFF00);	   //读fifo一个八位    	  高位
		   FIFO_RD_H();

		   FIFO_RD_L();
		   ReadValue |= ((GPIO_ReadInputData(GPIOB)>>8)&0X00FF);	   //读fifo一个八位    	  低位
		   FIFO_RD_H(); 
		 
           R = (ReadValue>>8)&0xF8;
           G = (ReadValue>>3)&0xFC;
           B = (ReadValue<<3)&0xF8;
		   buffer[tx*3+2] = R;
		   buffer[tx*3+1] = G;
		   buffer[tx*3+0] = B;
		  }

        res = f_write(&fdst, buffer, 960, &bw);
     }

  FIFO_CS_H();
  LCD_GPIO_OUTPUT();


  f_close(&fdst);

  // Unregister a work area before discard it
  f_mount(0, NULL);



}*/

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {

  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
