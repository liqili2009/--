/**
  ******************************************************************************
  * @file    DCMI/Camera/dcmi_ov9655.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    13-April-2012
  * @brief   This file includes the driver for OV9655 Camera module mounted on 
  *          STM322xG-EVAL board RevA and RevB.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "camera_api.h"
#include "dcmi_ov9655.h"

/** @addtogroup stm32f2xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup DCMI_Camera
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define  TIMEOUT  2
#define Bank1_SRAM2_ADDR  ((uint32_t)0x64000000)  
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* QQVGA 160x120 */
/*static unsigned char OV9655_QQVGA[][2]=
{
  0x00, 0x00,
  0x01, 0x80,
  0x02, 0x80,
  0x03, 0x02,
  0x04, 0x03,
  0x09, 0x01,
  0x0b, 0x57,
  0x0e, 0x61,
  0x0f, 0x40,
  0x11, 0x01,
  0x12, 0x62,
  0x13, 0xc7,
  0x14, 0x3a,
  0x16, 0x24,
  0x17, 0x18,
  0x18, 0x04,
  0x19, 0x01,
  0x1a, 0x81,
  0x1e, 0x00,//0x20
  0x24, 0x3c,
  0x25, 0x36,
  0x26, 0x72,
  0x27, 0x08,
  0x28, 0x08,
  0x29, 0x15,
  0x2a, 0x00,
  0x2b, 0x00,
  0x2c, 0x08,
  0x32, 0xa4,
  0x33, 0x00,
  0x34, 0x3f,
  0x35, 0x00,
  0x36, 0x3a,
  0x38, 0x72,
  0x39, 0x57,
  0x3a, 0xcc,
  0x3b, 0x04,
  0x3d, 0x99,
  0x3e, 0x0e,
  0x3f, 0xc1,
  0x40, 0xc0,
  0x41, 0x41,
  0x42, 0xc0,
  0x43, 0x0a,
  0x44, 0xf0,
  0x45, 0x46,
  0x46, 0x62,
  0x47, 0x2a,
  0x48, 0x3c,
  0x4a, 0xfc,
  0x4b, 0xfc,
  0x4c, 0x7f,
  0x4d, 0x7f,
  0x4e, 0x7f,
  0x4f, 0x98,
  0x50, 0x98,
  0x51, 0x00,
  0x52, 0x28,
  0x53, 0x70,
  0x54, 0x98,
  0x58, 0x1a,
  0x59, 0x85,
  0x5a, 0xa9,
  0x5b, 0x64,
  0x5c, 0x84,
  0x5d, 0x53,
  0x5e, 0x0e,
  0x5f, 0xf0,
  0x60, 0xf0,
  0x61, 0xf0,
  0x62, 0x00,
  0x63, 0x00,
  0x64, 0x02,
  0x65, 0x20,
  0x66, 0x00,
  0x69, 0x0a,
  0x6b, 0x5a,
  0x6c, 0x04,
  0x6d, 0x55,
  0x6e, 0x00,
  0x6f, 0x9d,
  0x70, 0x21,
  0x71, 0x78,
  0x72, 0x22,
  0x73, 0x02,
  0x74, 0x10,
  0x75, 0x10,
  0x76, 0x01,
  0x77, 0x02,
  0x7A, 0x12,
  0x7B, 0x08,
  0x7C, 0x16,
  0x7D, 0x30,
  0x7E, 0x5e,
  0x7F, 0x72,
  0x80, 0x82,
  0x81, 0x8e,
  0x82, 0x9a,
  0x83, 0xa4,
  0x84, 0xac,
  0x85, 0xb8,
  0x86, 0xc3,
  0x87, 0xd6,
  0x88, 0xe6,
  0x89, 0xf2,
  0x8a, 0x24,
  0x8c, 0x80,
  0x90, 0x7d,
  0x91, 0x7b,
  0x9d, 0x02,
  0x9e, 0x02,
  0x9f, 0x7a,
  0xa0, 0x79,
  0xa1, 0x40,
  0xa4, 0x50,
  0xa5, 0x68,
  0xa6, 0x4a,
  0xa8, 0xc1,
  0xa9, 0xef,
  0xaa, 0x92,
  0xab, 0x04,
  0xac, 0x80,
  0xad, 0x80,
  0xae, 0x80,
  0xaf, 0x80,
  0xb2, 0xf2,
  0xb3, 0x20,
  0xb4, 0x20,
  0xb5, 0x00,
  0xb6, 0xaf,
  0xb6, 0xaf,
  0xbb, 0xae,
  0xbc, 0x7f,
  0xbd, 0x7f,
  0xbe, 0x7f,
  0xbf, 0x7f,
  0xbf, 0x7f,
  0xc0, 0xaa,
  0xc1, 0xc0,
  0xc2, 0x01,
  0xc3, 0x4e,
  0xc6, 0x05,
  0xc7, 0x82,
  0xc9, 0xe0,
  0xca, 0xe8,
  0xcb, 0xf0,
  0xcc, 0xd8,
  0xcd, 0x93,

  0x12, 0x63,
  0x40, 0x10,
  0x15, 0x08,
};*/

/* QVGA 360x240 */
static unsigned char OV9655_QVGA[][2]=
{
  0x00, 0x00,
  0x01, 0x80,
  0x02, 0x80,
  0x03, 0x02,
  0x04, 0x03,
  0x09, 0x01,
  0x0b, 0x57,
  0x0e, 0x61,
  0x0f, 0x40,
  0x11, 0x01,
  0x12, 0x62,
  0x13, 0xc7,
  0x14, 0x3a,
  0x16, 0x24,
  0x17, 0x18,
  0x18, 0x04,
  0x19, 0x01,
  0x1a, 0x81,
  0x1e, 0x20,/*图像上下颠倒0x00*/
  0x24, 0x3c,
  0x25, 0x36,
  0x26, 0x72,
  0x27, 0x08,
  0x28, 0x08,
  0x29, 0x15,
  0x2a, 0x00,
  0x2b, 0x00,
  0x2c, 0x08,
  0x32, 0x12,
  0x33, 0x00,
  0x34, 0x3f,
  0x35, 0x00,
  0x36, 0x3a,
  0x38, 0x72,
  0x39, 0x57,
  0x3a, 0xcc,
  0x3b, 0x04,
  0x3d, 0x99,
  0x3e, 0x02,
  0x3f, 0xc1,
  0x40, 0xc0,
  0x41, 0x41,
  0x42, 0xc0,
  0x43, 0x0a,
  0x44, 0xf0,
  0x45, 0x46,
  0x46, 0x62,
  0x47, 0x2a,
  0x48, 0x3c,
  0x4a, 0xfc,
  0x4b, 0xfc,
  0x4c, 0x7f,
  0x4d, 0x7f,
  0x4e, 0x7f,
  0x4f, 0x98,
  0x50, 0x98,
  0x51, 0x00,
  0x52, 0x28,
  0x53, 0x70,
  0x54, 0x98,
  0x58, 0x1a,
  0x59, 0x85,
  0x5a, 0xa9,
  0x5b, 0x64,
  0x5c, 0x84,
  0x5d, 0x53,
  0x5e, 0x0e,
  0x5f, 0xf0,
  0x60, 0xf0,
  0x61, 0xf0,
  0x62, 0x00,
  0x63, 0x00,
  0x64, 0x02,
  0x65, 0x20,
  0x66, 0x00,
  0x69, 0x0a,
  0x6b, 0x5a,
  0x6c, 0x04,
  0x6d, 0x55,
  0x6e, 0x00,
  0x6f, 0x9d,
  0x70, 0x21,
  0x71, 0x78,
  0x72, 0x11,
  0x73, 0x01,
  0x74, 0x10,
  0x75, 0x10,
  0x76, 0x01,
  0x77, 0x02,
  0x7A, 0x12,
  0x7B, 0x08,
  0x7C, 0x16,
  0x7D, 0x30,
  0x7E, 0x5e,
  0x7F, 0x72,
  0x80, 0x82,
  0x81, 0x8e,
  0x82, 0x9a,
  0x83, 0xa4,
  0x84, 0xac,
  0x85, 0xb8,
  0x86, 0xc3,
  0x87, 0xd6,
  0x88, 0xe6,
  0x89, 0xf2,
  0x8a, 0x24,
  0x8c, 0x80,
  0x90, 0x7d,
  0x91, 0x7b,
  0x9d, 0x02,
  0x9e, 0x02,
  0x9f, 0x7a,
  0xa0, 0x79,
  0xa1, 0x40,
  0xa4, 0x50,
  0xa5, 0x68,
  0xa6, 0x4a,
  0xa8, 0xc1,
  0xa9, 0xef,
  0xaa, 0x92,
  0xab, 0x04,
  0xac, 0x80,
  0xad, 0x80,
  0xae, 0x80,
  0xaf, 0x80,
  0xb2, 0xf2,
  0xb3, 0x20,
  0xb4, 0x20,
  0xb5, 0x00,
  0xb6, 0xaf,
  0xb6, 0xaf,
  0xbb, 0xae,
  0xbc, 0x7f,
  0xbd, 0x7f,
  0xbe, 0x7f,
  0xbf, 0x7f,
  0xbf, 0x7f,
  0xc0, 0xaa,
  0xc1, 0xc0,
  0xc2, 0x01,
  0xc3, 0x4e,
  0xc6, 0x05,
  0xc7, 0x81,
  0xc9, 0xe0,
  0xca, 0xe8,
  0xcb, 0xf0,
  0xcc, 0xd8,
  0xcd, 0x93,

  0x12, 0x63,
  0x40, 0x10,
  0x15, 0x08,
};


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the hardware resources (I2C and GPIO) used to configure 
  *         the OV9655 camera.
  * @param  None
  * @retval None
  */
void OV9655_HW_Init(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
  I2C_InitTypeDef  I2C_InitStruct;

  /*** Configures the DCMI GPIOs to interface with the OV9655 camera module ***/
  /* Enable DCMI GPIOs clocks */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOH |
                         RCC_AHB1Periph_GPIOI, ENABLE);

  /* Connect DCMI pins to AF13 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);

  GPIO_PinAFConfig(GPIOH, GPIO_PinSource8, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource9, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource10, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource11, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource12, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource14, GPIO_AF_DCMI);

  GPIO_PinAFConfig(GPIOI, GPIO_PinSource5, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource6, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource7, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource4, GPIO_AF_DCMI);
  
  /* DCMI GPIO configuration */
  /* D0..D4(PH9/10/11/12/14), HSYNC(PH8) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |
                                GPIO_Pin_12 | GPIO_Pin_14| GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOH, &GPIO_InitStructure);

  /* D5..D7(PI4/6/7), VSYNC(PI5) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_5;
  GPIO_Init(GPIOI, &GPIO_InitStructure);

  /* PCLK(PA6) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /****** Configures the I2C1 used for OV9655 camera module configuration *****/
 /* I2C1 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

  /* GPIOB clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 

  /* Connect I2C1 pins to AF4 */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
  
  /* Configure I2C1 GPIOs */  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure I2C1 */
  /* I2C DeInit */
  I2C_DeInit(I2C1);
    
  /* Enable the I2C peripheral */
  I2C_Cmd(I2C1, ENABLE);
 
  /* Set the I2C structure parameters */
  I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStruct.I2C_OwnAddress1 = 0xFE;
  I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStruct.I2C_ClockSpeed = 30000;
  
  /* Initialize the I2C peripheral w/ selected parameters */
  I2C_Init(I2C1, &I2C_InitStruct);
}

/**
  * @brief  Resets the OV9655 camera.
  * @param  None
  * @retval None
  */
void OV9655_Reset(void)
{
  OV9655_WriteReg(OV9655_COM7, 0x80);
}

/**
  * @brief  Reads the OV9655 Manufacturer identifier.
  * @param  OV9655ID: pointer to the OV9655 Manufacturer identifier.
  * @retval None
  */
void OV9655_ReadID(OV9655_IDTypeDef* OV9655ID)
{
  OV9655ID->Manufacturer_ID1 = OV9655_ReadReg(OV9655_MIDH);
  OV9655ID->Manufacturer_ID2 = OV9655_ReadReg(OV9655_MIDL);
  OV9655ID->Version = OV9655_ReadReg(OV9655_VER);
  OV9655ID->PID = OV9655_ReadReg(OV9655_PID);
}

/**
  * @brief  Configures the DCMI/DMA to capture image from the OV9655 camera.
  * @param  ImageFormat: Image format BMP or JPEG
  * @param  BMPImageSize: BMP Image size  
  * @retval None
  */
void OV9655_Init(ImageFormat_TypeDef ImageFormat)
{
  DCMI_InitTypeDef DCMI_InitStructure;
  DMA_InitTypeDef  DMA_InitStructure;

  /*** Configures the DCMI to interface with the OV9655 camera module ***/
  /* Enable DCMI clock */
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);

  /* DCMI configuration */ 
  DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
  DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
  DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
  DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;
  DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_High;
  DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
  DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;

  /* Configures the DMA2 to transfer Data from DCMI */
  /* Enable DMA2 clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  
  /* DMA2 Stream1 Configuration */
  DMA_DeInit(DMA2_Stream1);

  DMA_InitStructure.DMA_Channel = DMA_Channel_1;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;	
  DMA_InitStructure.DMA_Memory0BaseAddr = FSMC_LCD_ADDRESS;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 0xffff;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

  switch(ImageFormat)
  {
    case BMP_QQVGA:
    {
      /* DCMI configuration */
      DCMI_Init(&DCMI_InitStructure);

      /* DMA2 IRQ channel Configuration */
      DMA_Init(DMA2_Stream1, &DMA_InitStructure);
      break;
    }
    case BMP_QVGA:
    {
      /* DCMI configuration */ 
      DCMI_Init(&DCMI_InitStructure);

      /* DMA2 IRQ channel Configuration */
      DMA_Init(DMA2_Stream1, &DMA_InitStructure); 
      break;
    }
    default:
    {
      /* DCMI configuration */ 
      DCMI_Init(&DCMI_InitStructure);

      /* DMA2 IRQ channel Configuration */
      DMA_Init(DMA2_Stream1, &DMA_InitStructure);
      break;
    }
  }   

  OV9655_Reset();
  OV9655_InitSet();
  
}

void OV9655_Display(ImageFormat_TypeDef ImageFormat)
{
	u16 i = 0 ,j = 0 ;
	u32 lseek0 = 0,lseek1 = 0;
	unsigned int  pIndex = Bank1_SRAM2_ADDR;
	switch(ImageFormat)
          {
            case BMP_QQVGA:
            {
                        
              break;
            }
            case BMP_QVGA:/*320*240*/
            {
                
              break;
            }
                 case BMP_VGA:/*640*480*/
            {
                lseek0 = 0;
                lseek1 = 318;
				//vuy422_to_rgb565((u16*)Bank1_SRAM2_ADDR,(u16*)Bank1_SRAM2_ADDR,640*480);
             
                break;
            }
                case BMP_SXGA:/*1280*1024*/
            {
                lseek0 = 0;
                lseek1 = 638;  
		//vuy422_to_rgb565((u16*)Bank1_SRAM2_ADDR,(u16*)Bank1_SRAM2_ADDR,640*480);
        
                break;
            }
            default:
            {
        
              break;
            }
          }

	


	
	
	pIndex +=lseek0;
	for( i = 0 ; i < 240 ; i++)

		{
			for(j = 0 ; j < 320 ; j++)
				{
                                           LCD_WriteRAM(*(u16*)pIndex);

					   pIndex+=2;
				}
			pIndex +=lseek1;
		}

	
  
	
}

void OV9655_InitSet()
{
  u32 i= 0 ;
 

  /* Initialize OV9655 */
  for(i=0; i<(sizeof(OV9655_QVGA)/2); i++)
  {
    OV9655_WriteReg(OV9655_QVGA[i][0], OV9655_QVGA[i][1]);
    
  }
}

/**
  * @brief  Configures the DCMI/DMA to capture image from the OV9655 camera.
  * @param  ImageFormat: Image format BMP or JPEG
  * @param  BMPImageSize: BMP Image size  
  * @retval None
  */
void OV9655_SinCapture(ImageFormat_TypeDef ImageFormat)
{
  DCMI_InitTypeDef DCMI_InitStructure;
  DMA_InitTypeDef  DMA_InitStructure;

  /*** Configures the DCMI to interface with the OV9655 camera module ***/
  /* Enable DCMI clock */
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);

  /* DCMI configuration */ 
  //DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_SnapShot;
  DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
  DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
  DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
  DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;
  DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_High;
  DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
  DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;

  /* Configures the DMA2 to transfer Data from DCMI */
  /* Enable DMA2 clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  
  /* DMA2 Stream1 Configuration */
 DMA_DeInit(DMA2_Stream1);

  DMA_InitStructure.DMA_Channel = DMA_Channel_1;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;	
  DMA_InitStructure.DMA_Memory0BaseAddr = Bank1_SRAM2_ADDR;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 307200;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  //DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
 	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  
  
 


    /* DCMI configuration */
      DCMI_Init(&DCMI_InitStructure);

      /* DMA2 IRQ channel Configuration */
      DMA_Init(DMA2_Stream1, &DMA_InitStructure);
      
   
       
       
  switch(ImageFormat)
  {
    case BMP_QQVGA:
    {
      OV9655_QQVGAConfig();
      break;
    }
    case BMP_QVGA:
    {
     OV9655_QVGAConfig();
    
      break;
    }
   
    case BMP_VGA:
    {
     OV9655_VGA_YUV();
      break;
    }
     case BMP_SXGA:
    {
       OV9655_SXGAConfig();
      break;
    }

    default:
    {
   
      break;
    }


  }  

  //DCMI_OV9655_SetExposure(ImageFormat);
}

/**
  * @brief  Configures the DCMI/DMA to capture image from the OV9655 camera.
  * @param  ImageFormat: Image format BMP or JPEG
  * @param  BMPImageSize: BMP Image size  
  * @retval None
  */
void OV9655_ZoomPreview(ImageFormat_TypeDef ImageFormat,uint8_t m)
{	
 	uint8_t temp = ImageFormat+m;
          if(temp <=3 && temp>=1)
 		{
  			OV9655_Init(ImageFormat);
                        DCMI_CROPInitTypeDef DCMI_CROPInitStructure;
			switch(temp)
			  {
			    case BMP_QQVGA:
			    {
			      	OV9655_QQVGAConfig();
				 	
			      break;
			    }
			    case BMP_QVGA:
			    {
			    	 OV9655_QVGAConfig();
                                 DCMI_CROPCmd(DISABLE);
					
			      break;
			    }
			   
			    case BMP_VGA:
			    {
			       	  OV9655_VGAConfig();

					
	
					

                                 
                                  LCD_Clear(Black);
                                  DCMI_CROPInitStructure.DCMI_HorizontalOffsetCount = 0;
                                  DCMI_CROPInitStructure.DCMI_VerticalStartLine = 240;
                                  DCMI_CROPInitStructure.DCMI_CaptureCount = 639;
                                  DCMI_CROPInitStructure.DCMI_VerticalLineCount = 479;
                                  /*DCMI_CROPInitStructure.DCMI_HorizontalOffsetCount = 0;
                                  DCMI_CROPInitStructure.DCMI_VerticalStartLine = 0;
                                  DCMI_CROPInitStructure.DCMI_CaptureCount = 319;
                                  DCMI_CROPInitStructure.DCMI_VerticalLineCount = 239;*/
                                  DCMI_CROPConfig(&DCMI_CROPInitStructure);
                                  //DCMI_CROPCmd(ENABLE);
                                        
                                        
                                     
			      break;
			    }
			     case BMP_SXGA:
			    {
			        OV9655_SXGAConfig();
				   	
					DCMI_CROPInitStructure.DCMI_HorizontalOffsetCount = 480 ; 
					DCMI_CROPInitStructure.DCMI_VerticalStartLine = 392;
					DCMI_CROPInitStructure.DCMI_CaptureCount = 320;
					DCMI_CROPInitStructure.DCMI_VerticalLineCount = 240;
					DCMI_CROPConfig(&DCMI_CROPInitStructure);
					DCMI_CROPCmd(ENABLE);
			      break;
			    }

			    default:
			    {
			   
			      break;
			    }
			}
			
 		}
  
}



/**
  * @brief  Configures the OV9655 camera in QQVGA mode.
  * @param  None
  * @retval None
  */
void OV9655_QQVGAConfig(void)
{

	OV9655_WriteReg(0x12,0x80);
	Delay(5);
	
  OV9655_InitSet();

  OV9655_WriteReg(0x32, 0xa4);   /* href */
  OV9655_WriteReg(0x3e, 0x0e);	
  OV9655_WriteReg(0x72, 0x22);   
  OV9655_WriteReg(0x73, 0x02);
  OV9655_WriteReg(0xC7, 0x82);   

 
}

/**
  * @brief  SConfigures the OV9655 camera in QVGA mode.
  * @param  None
  * @retval None
  */
void OV9655_QVGAConfig(void)
{
 

 
  	OV9655_InitSet();
	//OV9655_WriteReg(0x03, 0x12);   /* vref */
	//OV9655_WriteReg(0x17, 0x16);   /* hstart */
	//OV9655_WriteReg(0x18, 0x02);   /* hstop */
	//OV9655_WriteReg(0x19, 0x01);   /* vstrt */
	//OV9655_WriteReg(0x1a, 0x3d);   /* vstop */
	//OV9655_WriteReg(0x32, 0xff);   /* href */
	
  

  
  
}
void OV9655_QVGA_YUV()
{
	//OV9655_InitSet();
        OV9655_WriteReg(0x12, 0x62);
	OV9655_WriteReg(0x3a, 0x8c);    //0x80 to 0x8c, UYVY
	//OV9655_WriteReg(0x8c, 0x0c);
	
	OV9655_WriteReg(0x03, 0x12);   /* vref */
	OV9655_WriteReg(0x17, 0x16);   /* hstart */
	OV9655_WriteReg(0x18, 0x02);   /* hstop */
	OV9655_WriteReg(0x19, 0x01);   /* vstrt */
	OV9655_WriteReg(0x1a, 0x3d);   /* vstop */
	OV9655_WriteReg(0x32, 0xff);   /* href */
}

void test_init()
{
	//14.3fps
OV9655_WriteReg(0x12, 0x80);
OV9655_WriteReg(0xb5, 0x00);
OV9655_WriteReg(0x35, 0x00);
OV9655_WriteReg(0xa8, 0xc1);
OV9655_WriteReg(0x3a, 0x8c);    //0x80 to 0x8c, UYVY
OV9655_WriteReg(0x3d, 0x99);
OV9655_WriteReg(0x77, 0x02);
OV9655_WriteReg(0x13, 0xe7);
OV9655_WriteReg(0x26, 0x72);
OV9655_WriteReg(0x27, 0x08);
OV9655_WriteReg(0x28, 0x08);
OV9655_WriteReg(0x29, 0x15);
OV9655_WriteReg(0x2c, 0x08);
OV9655_WriteReg(0xab, 0x04);
OV9655_WriteReg(0x6e, 0x00);
OV9655_WriteReg(0x6d, 0x55);
OV9655_WriteReg(0x00, 0x32);
OV9655_WriteReg(0x10, 0x7b);
OV9655_WriteReg(0xbb, 0xae);
OV9655_WriteReg(0x72, 0x00);
OV9655_WriteReg(0x3e, 0x0c);
OV9655_WriteReg(0x74, 0x3a);
OV9655_WriteReg(0x76, 0x01);
OV9655_WriteReg(0x75, 0x35);
OV9655_WriteReg(0x73, 0x00);
OV9655_WriteReg(0xc7, 0x80);
OV9655_WriteReg(0xc3, 0x4e);
OV9655_WriteReg(0x33, 0x00);
OV9655_WriteReg(0xa4, 0x50);
OV9655_WriteReg(0xaa, 0x92);
OV9655_WriteReg(0xc2, 0x01);
OV9655_WriteReg(0xc1, 0xc8);
OV9655_WriteReg(0x1e, 0x04);
OV9655_WriteReg(0xa9, 0xef);
OV9655_WriteReg(0x0e, 0x61);
OV9655_WriteReg(0x39, 0x57);
OV9655_WriteReg(0x0f, 0x42);
OV9655_WriteReg(0x24, 0x3c);
OV9655_WriteReg(0x25, 0x36);
OV9655_WriteReg(0x12, 0x63);//0x62 to 0x63
OV9655_WriteReg(0x03, 0x12);
OV9655_WriteReg(0x32, 0xff);
OV9655_WriteReg(0x17, 0x16);
OV9655_WriteReg(0x18, 0x02);
OV9655_WriteReg(0x19, 0x01);
OV9655_WriteReg(0x1a, 0x3d);
OV9655_WriteReg(0x36, 0xfa);
OV9655_WriteReg(0x69, 0x0a);
OV9655_WriteReg(0x8c, 0x8d);
OV9655_WriteReg(0xc0, 0xaa);
OV9655_WriteReg(0x40, 0xc0);
OV9655_WriteReg(0xc6, 0x85);
OV9655_WriteReg(0xcb, 0xf0);
OV9655_WriteReg(0xcc, 0xd8);
OV9655_WriteReg(0x71, 0x78);
OV9655_WriteReg(0xa5, 0x68);
OV9655_WriteReg(0x6f, 0x9e);
OV9655_WriteReg(0x42, 0xc1);   //0xc0 to 0xc1, 50HZ banding filer
OV9655_WriteReg(0x3f, 0x82); 
OV9655_WriteReg(0x8a,0x23);
OV9655_WriteReg(0x14,0x18);   //0x1a to 0x18
OV9655_WriteReg(0x3b, 0x0c);
OV9655_WriteReg(0x2d, 0x00);
OV9655_WriteReg(0x2e, 0x00);
OV9655_WriteReg(0x34, 0x3d);
OV9655_WriteReg(0x41, 0x40);
OV9655_WriteReg(0xc9, 0xe0);
OV9655_WriteReg(0xca, 0xe8);
OV9655_WriteReg(0xcd, 0x93);
OV9655_WriteReg(0x7a, 0x20);
OV9655_WriteReg(0x7b, 0x1c);
OV9655_WriteReg(0x7c, 0x28);
OV9655_WriteReg(0x7d, 0x3c);
OV9655_WriteReg(0x7e, 0x5a);
OV9655_WriteReg(0x7f, 0x68);
OV9655_WriteReg(0x80, 0x76);
OV9655_WriteReg(0x81, 0x80);
OV9655_WriteReg(0x82, 0x88);
OV9655_WriteReg(0x83, 0x8f);
OV9655_WriteReg(0x84, 0x96);
OV9655_WriteReg(0x85, 0xa3);
OV9655_WriteReg(0x86, 0xaf);
OV9655_WriteReg(0x87, 0xc4);
OV9655_WriteReg(0x88, 0xd7);
OV9655_WriteReg(0x89, 0xe8);
OV9655_WriteReg(0x4f, 0x98);
OV9655_WriteReg(0x50, 0x98);
OV9655_WriteReg(0x51, 0x00);
OV9655_WriteReg(0x52, 0x28);
OV9655_WriteReg(0x53, 0x70);
OV9655_WriteReg(0x54, 0x98);
OV9655_WriteReg(0x58, 0x1a);
OV9655_WriteReg(0x90, 0x86);
OV9655_WriteReg(0x91, 0x84);
OV9655_WriteReg(0x9f, 0x75);
OV9655_WriteReg(0xa0, 0x73);
OV9655_WriteReg(0x16, 0x24);
OV9655_WriteReg(0x2a, 0x00);
OV9655_WriteReg(0x2b, 0x00);
OV9655_WriteReg(0xac, 0x80);
OV9655_WriteReg(0xad, 0x80);
OV9655_WriteReg(0xae, 0x80);
OV9655_WriteReg(0xaf, 0x80);
OV9655_WriteReg(0xb2, 0xf2);
OV9655_WriteReg(0xb3, 0x20);
OV9655_WriteReg(0xb4, 0x20);
OV9655_WriteReg(0xb6, 0xaf);
OV9655_WriteReg(0xb6, 0xaf);
OV9655_WriteReg(0x04, 0x03);
OV9655_WriteReg(0x05, 0x2b);
OV9655_WriteReg(0x06, 0x35);
OV9655_WriteReg(0x07, 0x36);
OV9655_WriteReg(0x08, 0x3b);
OV9655_WriteReg(0x2f, 0x35);
OV9655_WriteReg(0x4a, 0xea);
OV9655_WriteReg(0x4b, 0xe6);
OV9655_WriteReg(0x4c, 0xe6);
OV9655_WriteReg(0x4d, 0xe6);
OV9655_WriteReg(0x4e, 0xe6);
OV9655_WriteReg(0x70, 0x0b);
OV9655_WriteReg(0xa6, 0x40);
OV9655_WriteReg(0xbc, 0x04);
OV9655_WriteReg(0xbd, 0x01);
OV9655_WriteReg(0xbe, 0x03);
OV9655_WriteReg(0xbf, 0x01);
OV9655_WriteReg(0xbf, 0x01);
OV9655_WriteReg(0x43, 0x14);
OV9655_WriteReg(0x44, 0xf0);
OV9655_WriteReg(0x45, 0x46);
OV9655_WriteReg(0x46, 0x62);
OV9655_WriteReg(0x47, 0x2a);
OV9655_WriteReg(0x48, 0x3c);
OV9655_WriteReg(0x59, 0x85);
OV9655_WriteReg(0x5a, 0xa9);
OV9655_WriteReg(0x5b, 0x64);
OV9655_WriteReg(0x5c, 0x84);
OV9655_WriteReg(0x5d, 0x53);
OV9655_WriteReg(0x5e, 0x0e);
OV9655_WriteReg(0x6c, 0x0c);
OV9655_WriteReg(0x6d, 0x55);
OV9655_WriteReg(0x6e, 0x00);
OV9655_WriteReg(0x6f, 0x9e);
OV9655_WriteReg(0x62, 0x10);    //0x00 to 0x10
OV9655_WriteReg(0x63, 0xd0);    //0x00 to 0xd0
OV9655_WriteReg(0x64, 0x06);    //0x08 to 0x06
OV9655_WriteReg(0x65, 0x00);    //0x20 to 0x00
OV9655_WriteReg(0x66, 0x05);    
OV9655_WriteReg(0x9d, 0x06);    //0x08 to 0x06
OV9655_WriteReg(0x9e, 0x08);    //0x09 to 0x08
OV9655_WriteReg(0x29, 0x15);
OV9655_WriteReg(0xa9, 0xef);
OV9655_WriteReg(0x11, 0x01);

OV9655_WriteReg(0x6b, 0x5a);    //0x1a to 0x5a

OV9655_WriteReg(0x92, 0x18);
OV9655_WriteReg(0x93, 0x00);
OV9655_WriteReg(0xa2, 0x4a);    //0x4b to 0x4a
OV9655_WriteReg(0xa3, 0x3e);    //0x4b to 0x3e
OV9655_WriteReg(0x6a, 0x06);    //0x4b to 0x06
OV9655_WriteReg(0xc5, 0x07);    //add
OV9655_WriteReg(0x1e, 0x04);    //0x14 to 0x04, no flip/mirror
OV9655_WriteReg(0x55, 0x00);
OV9655_WriteReg(0x56, 0x40);
OV9655_WriteReg(0xc6, 0x05);
OV9655_WriteReg(0x24, 0x50);
OV9655_WriteReg(0x25, 0x48);
OV9655_WriteReg(0x26, 0x82);


OV9655_WriteReg(0x15, 0x08);

}

void test_vga()
{
	OV9655_WriteReg(0x11, 0x01);  

OV9655_WriteReg(0x6b, 0x5a);    //0x1a to 0x5a
OV9655_WriteReg(0x72, 0x00);
OV9655_WriteReg(0x3e, 0x0c);
OV9655_WriteReg(0x74, 0x3a);
OV9655_WriteReg(0x75, 0x35);
OV9655_WriteReg(0x73, 0x00);
OV9655_WriteReg(0xc7, 0x81);

OV9655_WriteReg(0x12, 0x62);
OV9655_WriteReg(0x03, 0x12);
OV9655_WriteReg(0x32, 0xff);
OV9655_WriteReg(0x17, 0x16);
OV9655_WriteReg(0x18, 0x02);
OV9655_WriteReg(0x19, 0x01);
OV9655_WriteReg(0x1a, 0x3d);
OV9655_WriteReg(0x41, 0x40);

OV9655_WriteReg(0x36, 0xfa);
OV9655_WriteReg(0x69, 0x0a);
OV9655_WriteReg(0x8c, 0x8d);
OV9655_WriteReg(0xc0, 0xaa);
OV9655_WriteReg(0x92, 0x18);
OV9655_WriteReg(0x93, 0x00);
OV9655_WriteReg(0xa2, 0x4a);    //0x4b to 0x4a
OV9655_WriteReg(0xa3, 0x3e);    //0x4b to 0x3e
OV9655_WriteReg(0x6a, 0x06);    //0x4b to 0x06
OV9655_WriteReg(0xc5, 0x07);    //add
OV9655_WriteReg(0x8B,00);

   
}
void test_qvga()
{
	OV9655_WriteReg(0x11, 0x01);

OV9655_WriteReg(0x6b, 0x5a);    //0x1a to 0x5a
   
OV9655_WriteReg(0x72, 0x11);    
OV9655_WriteReg(0x3e, 0x0e);   
OV9655_WriteReg(0x74, 0x10);    
OV9655_WriteReg(0x75, 0x10);    
OV9655_WriteReg(0x73, 0x01);    
OV9655_WriteReg(0xc7, 0x81);    

OV9655_WriteReg(0x12, 0x63);
OV9655_WriteReg(0x03, 0x02);
OV9655_WriteReg(0x32, 0x12);
OV9655_WriteReg(0x17, 0x18);
OV9655_WriteReg(0x18, 0x04);
OV9655_WriteReg(0x19, 0x01);
OV9655_WriteReg(0x1a, 0x81);
OV9655_WriteReg(0x41, 0x41);

OV9655_WriteReg(0x36, 0x3a);    
OV9655_WriteReg(0x69, 0x0a);
OV9655_WriteReg(0x8c, 0x80);   
OV9655_WriteReg(0xc0, 0xaa);
OV9655_WriteReg(0x92, 0x18);
OV9655_WriteReg(0x93, 0x00);
OV9655_WriteReg(0xa2, 0x4a);    
OV9655_WriteReg(0xa3, 0x3e);    
OV9655_WriteReg(0x6a, 0x06);    
OV9655_WriteReg(0xc5, 0x07);    
}

/*void vuy422_to_rgb(unsigned char* yuv, char* rgb, unsigned int width, unsigned int height)
{
	int yy, uu, vv, ug_plus_vg, ub, vr;
	int r,g,b;
	unsigned int total = width*height;
	total /= 2;
	while (total--) {
		yy = yuv[1] << 8;
		uu = yuv[0] - 128;
		vv = yuv[2] - 128;
		ug_plus_vg = uu * 88 + vv * 183;
		ub = uu * 454;
		vr = vv * 359;
		r = (yy + vr) >> 8;
		g = (yy - ug_plus_vg) >> 8;
		b = (yy + ub) >> 8;
		rgb[0] = r < 0 ? 0 : (r > 255 ? 255 : (unsigned char)r);
		rgb[1] = g < 0 ? 0 : (g > 255 ? 255 : (unsigned char)g);
		rgb[2] = b < 0 ? 0 : (b > 255 ? 255 : (unsigned char)b);
		yy = yuv[3] << 8;
		r = (yy + vr) >> 8;
		g = (yy - ug_plus_vg) >> 8;
		b = (yy + ub) >> 8;
		rgb[3] = r < 0 ? 0 : (r > 255 ? 255 : (unsigned char)r);
		rgb[4] = g < 0 ? 0 : (g > 255 ? 255 : (unsigned char)g);
		rgb[5] = b < 0 ? 0 : (b > 255 ? 255 : (unsigned char)b);
		yuv += 4;
		rgb += 6;
	}

}*/
	
	void IMG_ycbcr422p_rgb_c
	(
		const short 			coeff[5],	/* Matrix coefficients. 			*/
		const unsigned char 	*y_data,	/* Luminence data		 (Y')		*/
		const unsigned char 	*cb_data,	/* Blue color-difference (B'-Y')	*/
		const unsigned char 	*cr_data,	/* Red color-difference  (R'-Y')	*/
		unsigned short *restrict rgb_data,	/* RGB 5:6:5 packed pixel output.	*/
		unsigned				num_pixels	/* # of luma pixels to process. 	*/
	)
	{
		int 	i;						/* Loop counter 					*/
		int 	y0, y1; 				/* Individual Y components			*/
		int 	cb, cr; 				/* Color difference components		*/
		int 	y0t,y1t;				/* Temporary Y values				*/
		int 	rt, gt, bt; 			/* Temporary RGB values 			*/
		int 	r0, g0, b0; 			/* Individual RGB components		*/
		int 	r1, g1, b1; 			/* Individual RGB components		*/
		int 	r0t,g0t,b0t;			/* Truncated RGB components 		*/
		int 	r1t,g1t,b1t;			/* Truncated RGB components 		*/
		int 	r0s,g0s,b0s;			/* Saturated RGB components 		*/
		int 	r1s,g1s,b1s;			/* Saturated RGB components 		*/
	
		short	luma = coeff[0];		/* Luma scaling coefficient.		*/
		short	r_cr = coeff[1];		/* Cr's contribution to Red.		*/
		short	g_cb = coeff[2];		/* Cb's contribution to Green.		*/
		short	g_cr = coeff[3];		/* Cr's contribution to Green.		*/
		short	b_cb = coeff[4];		/* Cb's contribution to Blue.		*/
	
		unsigned short	rgb0, rgb1; 	/* Packed RGB pixel data			*/
		unsigned short	a,b;
		/* -------------------------------------------------------------------- */
		/*	Iterate for num_pixels/2 iters, since we process pixels in pairs.	*/
		/* -------------------------------------------------------------------- */
		i = num_pixels >> 1;
	
		while (i-->0)
		{
			/* ---------------------------------------------------------------- */
			/*	Read in YCbCr data from the separate data planes.				*/
			/*																	*/
			/*	The Cb and Cr channels come in biased upwards by 128, so		*/
			/*	subtract the bias here before performing the multiplies for 	*/
			/*	the color space conversion itself.	Also handle Y's upward		*/
			/*	bias of 16 here.												*/
			/* ---------------------------------------------------------------- */
	
			y0 = *y_data++	- 16;
			y1 = *y_data++	- 16;
			cb = *cb_data++ - 128;
			cr = *cr_data++ - 128;
	
			/* ================================================================ */
			/*	Convert YCrCb data to RGB format using the following matrix:	*/
			/*																	*/
			/*		[ coeff[0] 0.0000	coeff[1] ]	 [ Y' -  16 ]	  [ R'] 	*/
			/*		[ coeff[0] coeff[2] coeff[3] ] * [ Cb - 128 ]  =  [ G'] 	*/
			/*		[ coeff[0] coeff[4] 0.0000	 ]	 [ Cr - 128 ]	  [ B'] 	*/
			/*																	*/
			/*	We use signed Q13 coefficients for the coefficients to make 	*/
			/*	good use of our 16-bit multiplier.	Although a larger Q-point	*/
			/*	may be used with unsigned coefficients, signed coefficients 	*/
			/*	add a bit of flexibility to the kernel without significant		*/
			/*	loss of precision.												*/
			/* ================================================================ */
	
			/* ---------------------------------------------------------------- */
			/*	Calculate chroma channel's contribution to RGB. 				*/
			/* ---------------------------------------------------------------- */
			rt	= r_cr * (short)cr;
			gt	= g_cb * (short)cb + g_cr * (short)cr;
			bt	= b_cb * (short)cb;
	
			/* ---------------------------------------------------------------- */
			/*	Calculate intermediate luma values.  Include bias of 16 here.	*/
			/* ---------------------------------------------------------------- */
			y0t = luma * (short)y0;
			y1t = luma * (short)y1;
	
			/* ---------------------------------------------------------------- */
			/*	Mix luma, chroma channels.										*/
			/* ---------------------------------------------------------------- */
			r0	= y0t + rt; r1 = y1t + rt;
			g0	= y0t + gt; g1 = y1t + gt;
			b0	= y0t + bt; b1 = y1t + bt;
	
			/* ================================================================ */
			/*	At this point in the calculation, the RGB components are		*/
			/*	nominally in the format below.	If the color is outside the 	*/
			/*	our RGB gamut, some of the sign bits may be non-zero,			*/
			/*	triggering saturation.											*/
			/*																	*/
			/*					3	  2 2		 1 1							*/
			/*					1	  1 0		 3 2		 0					*/
			/*				   [ SIGN  | COLOR	  | FRACTION ]					*/
			/*																	*/
			/*	This gives us an 8-bit range for each of the R, G, and B		*/
			/*	components.  (The transform matrix is designed to transform 	*/
			/*	8-bit Y/C values into 8-bit R,G,B values.)	To get our final	*/
			/*	5:6:5 result, we "divide" our R, G and B components by 4, 8,	*/
			/*	and 4, respectively, by reinterpreting the numbers in the		*/
			/*	format below:													*/
			/*																	*/
			/*			Red,	3	  2 2	  1 1								*/
			/*			Blue	1	  1 0	  6 5			 0					*/
			/*				   [ SIGN  | COLOR | FRACTION	 ]					*/
			/*																	*/
			/*					3	  2 2	   1 1								*/
			/*			Green	1	  1 0	   5 4			 0					*/
			/*				   [ SIGN  | COLOR	| FRACTION	 ]					*/
			/*																	*/
			/*	"Divide" is in quotation marks because this step requires no	*/
			/*	actual work.  The code merely treats the numbers as having a	*/
			/*	different Q-point.												*/
			/* ================================================================ */
	
			/* ---------------------------------------------------------------- */
			/*	Shift away the fractional portion, and then saturate to the 	*/
			/*	RGB 5:6:5 gamut.												*/
			/* ---------------------------------------------------------------- */
			r0t = r0 >> 16;
			g0t = g0 >> 15;
			b0t = b0 >> 16;
			r1t = r1 >> 16;
			g1t = g1 >> 15;
			b1t = b1 >> 16;
	
			r0s = r0t < 0 ? 0 : r0t > 31 ? 31 : r0t;
			g0s = g0t < 0 ? 0 : g0t > 63 ? 63 : g0t;
			b0s = b0t < 0 ? 0 : b0t > 31 ? 31 : b0t;
			r1s = r1t < 0 ? 0 : r1t > 31 ? 31 : r1t;
			g1s = g1t < 0 ? 0 : g1t > 63 ? 63 : g1t;
			b1s = b1t < 0 ? 0 : b1t > 31 ? 31 : b1t;
	
			/* ---------------------------------------------------------------- */
			/*	Merge values into output pixels.								*/
			/* ---------------------------------------------------------------- */
			rgb0 = (r0s << 11) + (g0s <<  5) + (b0s <<	0);
			a=rgb0>>8;	  
			b=rgb0<<8;
			rgb0=a+b;
			rgb0=rgb0<<2;
			
			rgb1 = (r1s << 11) + (g1s <<  5) + (b1s <<	0);
			a=rgb1>>8;
			b=rgb1<<8;
			rgb1=a+b;
		   
		   
			/* ---------------------------------------------------------------- */
			/*	Store resulting pixels to memory.								*/
			/* ---------------------------------------------------------------- */
			*rgb_data++ = rgb0;
			*rgb_data++ = rgb1;
		}
	
		return;
	
	}


/*void vuy422_to_rgb565(u16* yuv, u16* rgb, int num)
{
	int yy, uu, vv, ug_plus_vg, ub, vr;
	int r,g,b;
	u16 data[3];
	//unsigned int total = width*height;
	num /= 2;
	while (num--) {
		yy = yuv[0]&0xff00;
		uu = yuv[0]&0xff - 128;
		vv = yuv[1]&0xff - 128;
		ug_plus_vg = uu * 88 + vv * 183;
		ub = uu * 454;
		vr = vv * 359;
		r = (yy + vr) >> 8;
		g = (yy - ug_plus_vg) >> 8;
		b = (yy + ub) >> 8;
		data[0] = r < 0 ? 0 : (r > 255 ? 255 : (unsigned char)r);
		data[1] = g < 0 ? 0 : (g > 255 ? 255 : (unsigned char)g);
		data[2] = b < 0 ? 0 : (b > 255 ? 255 : (unsigned char)b);

		rgb[0] = data[2]>>3|(data[1]&0xfc)<<3|(data[0]&0xf8)<<8;
		yy = yuv[1] &0xff00;
		r = (yy + vr) >> 8;
		g = (yy - ug_plus_vg) >> 8;
		b = (yy + ub) >> 8;
		data[0] = r < 0 ? 0 : (r > 255 ? 255 : (unsigned char)r);
		data[1] = g < 0 ? 0 : (g > 255 ? 255 : (unsigned char)g);
		data[2] = b < 0 ? 0 : (b > 255 ? 255 : (unsigned char)b);


		rgb[1] = data[2]>>3|(data[1]&0xfc)<<3|(data[0]&0xf8)<<8;
		yuv += 2;
		rgb += 2;
	}
}*/



void vuy422_to_rgb565(u16* yuv, u16* rgb, int num)
{
	int yy, uu, vv, ug_plus_vg, ub, vr;
	int r,g,b;
	u16 data[3];
	//unsigned int total = width*height;
	num /= 2;
	while (num--) {
		yy = (yuv[0]&0xff00)>>8;
		uu = yuv[0]&0xff;
		vv = yuv[1]&0xff;
		ug_plus_vg = uu * 88 + vv * 183;
		ub = uu * 454;
		vr = vv * 359;


		
		
		
		r = yy;
		g = yy;
		b = yy;
		

		data[0] = r < 0 ? 0 : (r > 255 ? 255 : (unsigned char)r);
		data[1] = g < 0 ? 0 : (g > 255 ? 255 : (unsigned char)g);
		data[2] = b < 0 ? 0 : (b > 255 ? 255 : (unsigned char)b);

		rgb[0] = data[2]>>3|(data[1]&0xfc)<<3|(data[0]&0xf8)<<8;
		yy = (yuv[1] &0xff00)>>8;
		r = yy ;
		g = yy;
		b = yy ;
		data[0] = r < 0 ? 0 : (r > 255 ? 255 : (unsigned char)r);
		data[1] = g < 0 ? 0 : (g > 255 ? 255 : (unsigned char)g);
		data[2] = b < 0 ? 0 : (b > 255 ? 255 : (unsigned char)b);


		rgb[1] = data[2]>>3|(data[1]&0xfc)<<3|(data[0]&0xf8)<<8;
		yuv += 2;
		rgb += 2;
	}
}



void OV9655_VGA_YUV(void)
{
	OV9655_Reset();
	OV9655_InitSet();
	 
	OV9655_WriteReg(0x36, 0xfa);	/* aref3 */
	OV9655_WriteReg(0x69, 0x0a);	/* hv */
	OV9655_WriteReg(0x8c, 0x89);	/* com22 */
	OV9655_WriteReg(0x14, 0x28);	/* com9 */
	OV9655_WriteReg(0x3e, 0x0c);	/* com14 */
	OV9655_WriteReg(0x41, 0x40);	/* com16 */
	OV9655_WriteReg(0x72, 0x00);
	OV9655_WriteReg(0x73, 0x00);
	OV9655_WriteReg(0x74, 0x3a);
	OV9655_WriteReg(0x75, 0x35);
	OV9655_WriteReg(0x76, 0x01);
	OV9655_WriteReg(0xc7, 0x80);	/* com24 */
	OV9655_WriteReg(0x03, 0x12);	/* vref */
	OV9655_WriteReg(0x17, 0x16);	/* hstart */
	OV9655_WriteReg(0x18, 0x02);	/* hstop */
	OV9655_WriteReg(0x19, 0x01);	/* vstrt */
	OV9655_WriteReg(0x1a, 0x3d);	/* vstop */
	OV9655_WriteReg(0x32, 0xff);	/* href */
	OV9655_WriteReg(0xc0, 0xaa);
	OV9655_WriteReg(0x12, 0x63);  /* com7 - 30fps VGA YUV */
	OV9655_WriteReg(0X15,0X08);
	OV9655_WriteReg(0X04,0X03);
	OV9655_WriteReg(0X40,0X10);

	
	
}



/**
  * @brief  SConfigures the OV9655 camera in VGA mode.
  * @param  None
  * @retval None
  */
void OV9655_VGAConfig(void)
{
 

	/*OV9655_Reset();
	OV9655_InitSet();

	
   OV9655_WriteReg(0x04, 0x00);

OV9655_WriteReg(0x12, 0x03);   
OV9655_WriteReg(0x11, 0x00); 
OV9655_WriteReg(0x36, 0xfa);   
OV9655_WriteReg(0x69, 0x0a);  
OV9655_WriteReg(0x8c, 0x89);   
OV9655_WriteReg(0x14, 0x28);   
//OV9655_WriteReg(0x3e, 0x0c);
 OV9655_WriteReg(0x41, 0x40);  
OV9655_WriteReg(0x72, 0x00);
OV9655_WriteReg(0x73, 0x00);
OV9655_WriteReg(0x74, 0x3a);
 OV9655_WriteReg(0x75, 0x35);
OV9655_WriteReg(0x76, 0x01);
 OV9655_WriteReg(0xc7, 0x81);*/

	OV9655_WriteReg(0x12, 0x80);
        Delay(3);
        OV9655_WriteReg(0x00, 0x00);//11镜像
	OV9655_WriteReg(0x01, 0x80);
	OV9655_WriteReg(0x02, 0x80);
	OV9655_WriteReg(0x03, 0x12);
	OV9655_WriteReg(0x04, 0x43);
	OV9655_WriteReg(0x0b, 0x57);
	OV9655_WriteReg(0x0e, 0x61);
	OV9655_WriteReg(0x0f, 0x40);
	OV9655_WriteReg(0x11, 0x05);////601:05 pclk=8.33M 或07pclk=6.5M //656:07  05
	OV9655_WriteReg(0x12, 0x63);
	OV9655_WriteReg(0x13, 0xc7);
	OV9655_WriteReg(0x14, 0x3a);
	OV9655_WriteReg(0x16, 0x24);
	OV9655_WriteReg(0x17, 0x16);
	OV9655_WriteReg(0x18, 0x02);
	OV9655_WriteReg(0x19, 0x01);
	OV9655_WriteReg(0x1a, 0x3d);
	OV9655_WriteReg(0x1e, 0x04);
	OV9655_WriteReg(0x24, 0x3c);
	OV9655_WriteReg(0x25, 0x36);
	OV9655_WriteReg(0x26, 0x72);
	OV9655_WriteReg(0x27, 0x08);
	OV9655_WriteReg(0x28, 0x08);
	OV9655_WriteReg(0x29, 0x15);
	OV9655_WriteReg(0x2a, 0x00);
	OV9655_WriteReg(0x2b, 0x00);
	OV9655_WriteReg(0x2c, 0x08);
	OV9655_WriteReg(0x32, 0xff);
	OV9655_WriteReg(0x33, 0x00);
	OV9655_WriteReg(0x34, 0x3F);
	OV9655_WriteReg(0x35, 0x00);
	OV9655_WriteReg(0x36, 0xfa);
	OV9655_WriteReg(0x38, 0x72);
	OV9655_WriteReg(0x39, 0x57);
	//OV9655_WriteReg(0x3a, 0x8c);//601模蔝 UYVY//656：88
	OV9655_WriteReg(0x3b, 0x04);
	OV9655_WriteReg(0x3d, 0x99);
	OV9655_WriteReg(0x3e, 0x0c);
	OV9655_WriteReg(0x3f, 0xc1);
	OV9655_WriteReg(0x40, 0xc0);
	OV9655_WriteReg(0x41, 0x00);
	OV9655_WriteReg(0x42, 0xc0);
	OV9655_WriteReg(0x43, 0x0a);
	OV9655_WriteReg(0x44, 0xf0);
	OV9655_WriteReg(0x45, 0x46);
	OV9655_WriteReg(0x46, 0x62);
	OV9655_WriteReg(0x47, 0x2a);
	OV9655_WriteReg(0x48, 0x3c);
	OV9655_WriteReg(0x4a, 0xfc);
	OV9655_WriteReg(0x4b, 0xfc);
	OV9655_WriteReg(0x4c, 0x7f);
	OV9655_WriteReg(0x4d, 0x7f);
	OV9655_WriteReg(0x4e, 0x7f);
	OV9655_WriteReg(0x4f, 0x98);
	OV9655_WriteReg(0x50, 0x98);
	OV9655_WriteReg(0x51, 0x00);
	OV9655_WriteReg(0x52, 0x28);
	OV9655_WriteReg(0x53, 0x70);
	OV9655_WriteReg(0x54, 0x98);
	OV9655_WriteReg(0x58, 0x1a);
	OV9655_WriteReg(0x59, 0x85);
	OV9655_WriteReg(0x5a, 0xa9);
	OV9655_WriteReg(0x5b, 0x64);
	OV9655_WriteReg(0x5c, 0x84);
	OV9655_WriteReg(0x5d, 0x53);
	OV9655_WriteReg(0x5e, 0x0e);
	OV9655_WriteReg(0x5f, 0xf0);
	OV9655_WriteReg(0x60, 0xf0);
	OV9655_WriteReg(0x61, 0xf0);
	OV9655_WriteReg(0x62, 0x00);
	OV9655_WriteReg(0x63, 0x00);
	OV9655_WriteReg(0x64, 0x02);
	OV9655_WriteReg(0x65, 0x20);
	OV9655_WriteReg(0x66, 0x00);
	OV9655_WriteReg(0x69, 0x0a);
	OV9655_WriteReg(0x6b, 0x5a);
	OV9655_WriteReg(0x6c, 0x04);
	OV9655_WriteReg(0x6d, 0x55);
	OV9655_WriteReg(0x6e, 0x00);
	OV9655_WriteReg(0x6f, 0x9d);
	OV9655_WriteReg(0x70, 0x21);
	OV9655_WriteReg(0x71, 0x78);
	OV9655_WriteReg(0x72, 0x00);
	OV9655_WriteReg(0x73, 0x00);
	OV9655_WriteReg(0x74, 0x3a);
	OV9655_WriteReg(0x75, 0x35);
	OV9655_WriteReg(0x76, 0x01);
	OV9655_WriteReg(0x77, 0x02);
	OV9655_WriteReg(0x7A, 0x12);
	OV9655_WriteReg(0x7B, 0x08);
	OV9655_WriteReg(0x7C, 0x16);
	OV9655_WriteReg(0x7D, 0x30);
	OV9655_WriteReg(0x7E, 0x5e);
	OV9655_WriteReg(0x7F, 0x72);
	OV9655_WriteReg(0x80, 0x82);
	OV9655_WriteReg(0x81, 0x8e);
	OV9655_WriteReg(0x82, 0x9a);
	OV9655_WriteReg(0x83, 0xa4);
	OV9655_WriteReg(0x84, 0xac);
	OV9655_WriteReg(0x85, 0xb8);
	OV9655_WriteReg(0x86, 0xc3);
	OV9655_WriteReg(0x87, 0xd6);
	OV9655_WriteReg(0x88, 0xe6);
	OV9655_WriteReg(0x89, 0xf2);
	OV9655_WriteReg(0x8a, 0x24);
	OV9655_WriteReg(0x8c, 0x8d);
	OV9655_WriteReg(0x90, 0x7d);
	OV9655_WriteReg(0x91, 0x7b);
	OV9655_WriteReg(0x9d, 0x02);
	OV9655_WriteReg(0x9e, 0x02);
	OV9655_WriteReg(0x9f, 0x7a);
	OV9655_WriteReg(0xa0, 0x79);
	OV9655_WriteReg(0xa1, 0x40);
	OV9655_WriteReg(0xa4, 0x50);
	OV9655_WriteReg(0xa5, 0x68);
	OV9655_WriteReg(0xa6, 0x4a);
	OV9655_WriteReg(0xa8, 0xc1);
	OV9655_WriteReg(0xa9, 0xef);
	OV9655_WriteReg(0xaa, 0x92);
	OV9655_WriteReg(0xab, 0x04);
	OV9655_WriteReg(0xac, 0x80);
	OV9655_WriteReg(0xad, 0x80);
	OV9655_WriteReg(0xae, 0x80);
	OV9655_WriteReg(0xaf, 0x80);
	OV9655_WriteReg(0xb2, 0xf2);
	OV9655_WriteReg(0xb3, 0x20);
	OV9655_WriteReg(0xb4, 0x20);
	OV9655_WriteReg(0xb5, 0x00);
	OV9655_WriteReg(0xb6, 0xaf);
	OV9655_WriteReg(0xbb, 0xae);
	OV9655_WriteReg(0xbc, 0x7f);
	OV9655_WriteReg(0xbd, 0x7f);
	OV9655_WriteReg(0xbe, 0x7f);
	OV9655_WriteReg(0xbf, 0x7f);
	OV9655_WriteReg(0xc0, 0xaa);
	OV9655_WriteReg(0xc1, 0xc0);
	OV9655_WriteReg(0xc2, 0x01);
	OV9655_WriteReg(0xc3, 0x4e);
	OV9655_WriteReg(0xc6, 0x05);
	OV9655_WriteReg(0xc7, 0x80);
	OV9655_WriteReg(0xc9, 0xe0);
	OV9655_WriteReg(0xca, 0xe8);
	OV9655_WriteReg(0xcb, 0xf0);
	OV9655_WriteReg(0xcc, 0xd8);
	OV9655_WriteReg(0xcd, 0x93);
	OV9655_WriteReg(0xcd, 0x93);

 






				   
		
				   

  
  
 
}
/**
  * @brief  SConfigures the OV9655 camera in SXGA mode.
  * @param  None
  * @retval None
  */
void OV9655_SXGAConfig(void)
{
   OV9655_WriteReg(0X12,0X80);
  Delay(5);
OV9655_WriteReg(0X13,0X00);
OV9655_WriteReg(0X00,0X00);
OV9655_WriteReg(0X01,0X80);
OV9655_WriteReg(0X02,0X80);
OV9655_WriteReg(0X03,0X1B);
OV9655_WriteReg(0X0E,0X61);
OV9655_WriteReg(0X0F,0X42);
OV9655_WriteReg(0X10,0XF0);
OV9655_WriteReg(0X11,0X01);
OV9655_WriteReg(0X12,0X02);//0X12,0X03//SXGA
OV9655_WriteReg(0X14,0X1A);
OV9655_WriteReg(0X16,0X14);
OV9655_WriteReg(0X17,0X1D);
OV9655_WriteReg(0X18,0XBD);
OV9655_WriteReg(0X19,0X01);
OV9655_WriteReg(0X1A,0X81);
OV9655_WriteReg(0X1E,0X04);
OV9655_WriteReg(0X24,0X3C);
OV9655_WriteReg(0X25,0X36);
OV9655_WriteReg(0X26,0X72);
OV9655_WriteReg(0X27,0X08);
OV9655_WriteReg(0X28,0X08);
OV9655_WriteReg(0X2A,0X00);
OV9655_WriteReg(0X2B,0X4C);
OV9655_WriteReg(0X2C,0X08);
OV9655_WriteReg(0X2D,0XD2);
OV9655_WriteReg(0X32,0XFF);
OV9655_WriteReg(0X33,0X00);
OV9655_WriteReg(0X34,0X3D);
OV9655_WriteReg(0X35,0X00);
OV9655_WriteReg(0X36,0XF0);
OV9655_WriteReg(0X39,0X57);
OV9655_WriteReg(0X3A,0XCC);
OV9655_WriteReg(0X3B,0XAC);
OV9655_WriteReg(0X3D,0X99);
OV9655_WriteReg(0X3E,0X0C);
OV9655_WriteReg(0X3F,0X42);
OV9655_WriteReg(0X41,0X40);
OV9655_WriteReg(0X42,0XC0);
OV9655_WriteReg(0X6B,0X5A);
OV9655_WriteReg(0X71,0XA0);
OV9655_WriteReg(0X72,0X00);
OV9655_WriteReg(0X73,0X01);
OV9655_WriteReg(0X74,0X3A);
OV9655_WriteReg(0X75,0X35);
OV9655_WriteReg(0X76,0X01);
OV9655_WriteReg(0X77,0X02);
OV9655_WriteReg(0X7A,0X20);
OV9655_WriteReg(0X7B,0X1C);
OV9655_WriteReg(0X7C,0X28);
OV9655_WriteReg(0X7D,0X3C);
OV9655_WriteReg(0X7E,0X5A);
OV9655_WriteReg(0X7F,0X68);
OV9655_WriteReg(0X80,0X76);
OV9655_WriteReg(0X81,0X80);
OV9655_WriteReg(0X82,0X88);
OV9655_WriteReg(0X83,0X8F);
OV9655_WriteReg(0X84,0X96);
OV9655_WriteReg(0X85,0XA3);
OV9655_WriteReg(0X86,0XAF);
OV9655_WriteReg(0X87,0XC4);
OV9655_WriteReg(0X88,0XD7);
OV9655_WriteReg(0X89,0XE8);
OV9655_WriteReg(0X8A,0X23);
OV9655_WriteReg(0X8C,0X80);
OV9655_WriteReg(0X90,0X20);
OV9655_WriteReg(0X91,0X20);
OV9655_WriteReg(0X9F,0X20);
OV9655_WriteReg(0XA0,0X20);
OV9655_WriteReg(0XA4,0X50);
OV9655_WriteReg(0XA5,0X90);
OV9655_WriteReg(0XA8,0XC1);
OV9655_WriteReg(0XA9,0XFA);
OV9655_WriteReg(0XAA,0X92);
OV9655_WriteReg(0XAB,0X04);
OV9655_WriteReg(0XAC,0X80);
OV9655_WriteReg(0XAD,0X80);
OV9655_WriteReg(0XAE,0X80);
OV9655_WriteReg(0XAF,0X80);
OV9655_WriteReg(0XB2,0XF2);
OV9655_WriteReg(0XB3,0X20);
OV9655_WriteReg(0XB4,0X20);
OV9655_WriteReg(0XB5,0X52);
OV9655_WriteReg(0XB6,0XAF);
OV9655_WriteReg(0XBB,0XAE);
OV9655_WriteReg(0XB5,0X00);
OV9655_WriteReg(0XC1,0XC8);
OV9655_WriteReg(0XC2,0X01);
OV9655_WriteReg(0XC3,0X4E);
OV9655_WriteReg(0XC6,0X85);
OV9655_WriteReg(0XC7,0X80);
OV9655_WriteReg(0XC9,0XE0);
OV9655_WriteReg(0XCA,0XE8);
OV9655_WriteReg(0XCB,0XF0);
OV9655_WriteReg(0XCC,0XD8);
OV9655_WriteReg(0XCD,0X93);
OV9655_WriteReg(0X4F,0X98);
OV9655_WriteReg(0X50,0X98);
OV9655_WriteReg(0X51,0X00);
OV9655_WriteReg(0X52,0X28);
OV9655_WriteReg(0X53,0X70);
OV9655_WriteReg(0X54,0X98);
OV9655_WriteReg(0X3B,0XCC);
OV9655_WriteReg(0X43,0X14);
OV9655_WriteReg(0X44,0XF0);
OV9655_WriteReg(0X45,0X46);
OV9655_WriteReg(0X46,0X62);
OV9655_WriteReg(0X47,0X2A);
OV9655_WriteReg(0X48,0X3C);
OV9655_WriteReg(0X59,0X85);
OV9655_WriteReg(0X5A,0XA9);
OV9655_WriteReg(0X5B,0X64);
OV9655_WriteReg(0X5C,0X84);
OV9655_WriteReg(0X5D,0X53);
OV9655_WriteReg(0X5E,0X0E);
OV9655_WriteReg(0X6C,0X0C);
OV9655_WriteReg(0X6D,0X55);
OV9655_WriteReg(0X6E,0X00);
OV9655_WriteReg(0X6F,0X9E);
OV9655_WriteReg(0X62,0X00);
OV9655_WriteReg(0X63,0X00);
OV9655_WriteReg(0X64,0X01);
OV9655_WriteReg(0X65,0X20);
OV9655_WriteReg(0X9D,0X01);
OV9655_WriteReg(0X9E,0X02);
OV9655_WriteReg(0X66,0X05);
OV9655_WriteReg(0X29,0X15);
OV9655_WriteReg(0XA9,0XEF);
OV9655_WriteReg(0X13,0XE7);
OV9655_WriteReg(0XA3,0X4A);
OV9655_WriteReg(0X3B,0XAC);
OV9655_WriteReg(0X14,0X1A);
OV9655_WriteReg(0X66,0X00);
OV9655_WriteReg(0X2D,0X00);
OV9655_WriteReg(0X2E,0X00);
OV9655_WriteReg(0X2A,0X10);
OV9655_WriteReg(0X2B,0X6E);
OV9655_WriteReg(0X92,0XD2);
OV9655_WriteReg(0X93,0X00);
OV9655_WriteReg(0X2A,0X00);
OV9655_WriteReg(0X2B,0X00);
OV9655_WriteReg(0X92,0X37);
OV9655_WriteReg(0X93,0X00);
OV9655_WriteReg(0XA2,0X4E);
OV9655_WriteReg(0XA3,0X4E);
OV9655_WriteReg(0X6A,0X4E);
OV9655_WriteReg(0X6B,0X5A);

OV9655_WriteReg(0X15,0X08);
OV9655_WriteReg(0X04,0X03);
OV9655_WriteReg(0X40,0X10);
/*not insert dummy pixls and lines*/
OV9655_WriteReg(0X2A,0X00);
OV9655_WriteReg(0X2B,0X00);
OV9655_WriteReg(0X92,0X00);
OV9655_WriteReg(0X93,0X00);




}


/**
  * @brief  Configures the OV9655 camera brightness.
  * @param  Brightness: Brightness value, where Brightness can be: 
  *         positively (0x01 ~ 0x7F) and negatively (0x80 ~ 0xFF)
  * @retval None
  */
void OV9655_BrightnessConfig(uint8_t Brightness)
{
  OV9655_WriteReg(OV9655_BRTN, Brightness);
}

/**
  * @brief  Writes a byte at a specific Camera register
  * @param  Addr: OV9655 register address
  * @param  Data: data to be written to the specific register
  * @retval 0x00 if write operation is OK
  *         0xFF if timeout condition occured (device not connected or bus error).
  */
uint8_t OV9655_WriteReg(uint16_t Addr, uint8_t Data)
{
  uint32_t timeout = DCMI_TIMEOUT_MAX;
  
  /* Generate the Start Condition */
  I2C_GenerateSTART(I2C1, ENABLE);

  /* Test on I2C1 EV5 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
   
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(I2C1, OV9655_DEVICE_WRITE_ADDRESS, I2C_Direction_Transmitter);
 
  /* Test on I2C1 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
 
  /* Send I2C1 location address LSB */
  I2C_SendData(I2C1, (uint8_t)(Addr));

  /* Test on I2C1 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
  
  /* Send Data */
  I2C_SendData(I2C1, Data);

  /* Test on I2C1 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }  
 
  /* Send I2C1 STOP Condition */
  I2C_GenerateSTOP(I2C1, ENABLE);
  
  /* If operation is OK, return 0 */
  return 0;
}

/**
  * @brief  Reads a byte from a specific Camera register
  * @param  Addr: OV9655 register address.
  * @retval data read from the specific register or 0xFF if timeout condition
  *         occured.
  */
uint8_t OV9655_ReadReg(uint16_t Addr)
{
  uint32_t timeout = DCMI_TIMEOUT_MAX;
  uint8_t Data = 0;

  /* Generate the Start Condition */
  I2C_GenerateSTART(I2C1, ENABLE);

  /* Test on I2C1 EV5 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
  
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(I2C1, OV9655_DEVICE_READ_ADDRESS, I2C_Direction_Transmitter);
 
  /* Test on I2C1 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }

  /* Send I2C1 location address LSB */
  I2C_SendData(I2C1, (uint8_t)(Addr));

  /* Test on I2C1 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  
  /* Clear AF flag if arised */
  I2C1->SR1 |= (uint16_t)0x0400;

  /* Generate the Start Condition */
  I2C_GenerateSTART(I2C1, ENABLE);
  
  /* Test on I2C1 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(I2C1, OV9655_DEVICE_READ_ADDRESS, I2C_Direction_Receiver);

  /* Test on I2C1 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
 
  /* Prepare an NACK for the next data received */
  I2C_AcknowledgeConfig(I2C1, DISABLE);

  /* Test on I2C1 EV7 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }

  /* Prepare Stop after receiving data */
  I2C_GenerateSTOP(I2C1, ENABLE);

  /* Receive the Data */
  Data = I2C_ReceiveData(I2C1);

  /* return the read data */
  return Data;
}


void DCMI_OV9655_SetExposure(ImageFormat_TypeDef ImageFormat)
{
	OV9655_WriteReg(0x13,0xc2);//stop AEC
	u16 Gain =  OV9655_ReadReg(0x00)|(OV9655_ReadReg(0x03)&0XC0)<<2;
	u16 Preview_Exposure = (OV9655_ReadReg(0xa1)&0X3F)<<10|OV9655_ReadReg(0x10)<<2|(OV9655_ReadReg(0x04)&0X3);
	/*u8 reg06 = OV9655_ReadReg(0x06);
	u32 Capture_Exposure = Preview_Exposure;
	u32 Capture_Gain =  Gain & 0x0f + 16
	if (Gain & 0x10)
		Capture_Gain = Capture_Gain << 1;
	if (Gain & 0x20)
		Capture_Gain = Capture_Gain << 1;
	if (Gain & 0x40)
		Capture_Gain = Capture_Gain << 1;
	if (Gain & 0x80)
		Capture_Gain = Capture_Gain << 1;

	u32 Capture_Exposure_Gain = Capture_Exposure * Capture_Gain* Target_Luminance / reg06*/

	switch(ImageFormat)
  	{
	    case BMP_QQVGA:
	    {
	      if(Preview_Exposure < 248)
		 	Preview_Exposure = 248;
	      break;
	    }
	    case BMP_QVGA:
	    {
	     if(Preview_Exposure < 248)
		 	Preview_Exposure = 248;
	      break;
	    }
	   
	    case BMP_VGA:
	    {
	     if(Preview_Exposure < 498)
		 	Preview_Exposure = 498;
	      break;
	    }
	     case BMP_SXGA:
	    {
	      if(Preview_Exposure < 1048)
		 	Preview_Exposure = 1048;
	      break;
	    }

	    default:
	    {
	   
	      break;
	    }
	}

        Preview_Exposure = 248;
	OV9655_WriteReg (0x04,(OV9655_ReadReg(0x04) & 0xfc) | (Preview_Exposure & 0x03));
	OV9655_WriteReg (0x10,(Preview_Exposure >> 2) & 0xff);
	OV9655_WriteReg (0xa1,(OV9655_ReadReg(0xa1)&0XC0)|Preview_Exposure >> 10);
	
	OV9655_WriteReg(0x03,OV9655_ReadReg(0x03)&0x1f);
	OV9655_WriteReg(0x00,0xf0);

	
}


/**
* @brief  Set the Internal Clock Prescaler.
* @param  OV9655_Prescaler: the new value of the prescaler.
*         This parameter can be a value between 0x0 and 0x1F
* @retval None
*/
void DCMI_OV9655_SetPrescaler(uint8_t OV9655_Prescaler)
{
	OV9655_WriteReg( OV9655_CLKRC, OV9655_Prescaler);
}

/**
* @brief  Select the Output Format.
* @param  OV9655_OuputFormat: the Format of the ouput Data.
*         This parameter can be one of the following values:
*           @arg OUTPUT_FORMAT_RAWRGB_DATA
*           @arg OUTPUT_FORMAT_RAWRGB_INTERP
*           @arg OUTPUT_FORMAT_YUV
*           @arg OUTPUT_FORMAT_RGB
* @retval None
*/
void DCMI_OV9655_SelectOutputFormat(uint8_t OV9655_OuputFormat)
{
	OV9655_WriteReg(OV9655_COM7, OV9655_OuputFormat);
}

/**
* @brief  Select the Output Format Resolution.
* @param  OV9655_FormatResolution: the Resolution of the ouput Data.
*         This parameter can be one of the following values:
*           @arg FORMAT_CTRL_15fpsVGA
*           @arg FORMAT_CTRL_30fpsVGA_NoVArioPixel
*           @arg FORMAT_CTRL_30fpsVGA_VArioPixel
* @retval None
*/
void DCMI_OV9655_SelectFormatResolution(uint8_t OV9655_FormatResolution)
{
	OV9655_WriteReg(OV9655_COM7, OV9655_FormatResolution);
}



/**
* @brief  Select the HREF Control signal option
* @param  OV9665_HREFControl: the HREF Control signal option.
*         This parameter can be one of the following value:
*           @arg OV9665_HREFControl_Opt1: HREF edge offset to data output.
*           @arg OV9665_HREFControl_Opt2: HREF end 3 LSB
*           @arg OV9665_HREFControl_Opt3: HREF start 3 LSB
* @retval None
*/
void DCMI_OV9655_HREFControl(uint8_t OV9665_HREFControl)
{
	OV9655_WriteReg(OV9655_HREF, OV9665_HREFControl);
}

/**
* @brief  Select the RGB format option
* @param  OV9665_RGBOption: the RGB Format option.
*         This parameter can be one of the following value:
*           @arg RGB_NORMAL
*           @arg RGB_565
*           @arg RGB_555
* @retval None
*/
void DCMI_OV9655_SelectRGBOption(uint8_t OV9665_RGBOption)
{
	OV9655_WriteReg(OV9655_COM15, OV9665_RGBOption);
}

/**


/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
