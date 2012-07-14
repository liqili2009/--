/**
  ******************************************************************************
  * @file    stm322xg_eval_ioe.h
  * @author  MCD Application Team
  * @version V4.6.1
  * @date    18-April-2011
  * @brief   This file contains all the functions prototypes for the
  *          stm322xg_eval_ioe.c driver.
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

  /* File Info : ---------------------------------------------------------------
    SUPPORTED FEATURES:
      - IO Read/write : Set/Reset and Read (Polling/Interrupt)
      - Joystick: config and Read (Polling/Interrupt)
      - Touch Screen Features: Single point mode (Polling/Interrupt)
      - TempSensor Feature: accuracy not determined (Polling).

    UNSUPPORTED FEATURES:
      - Row ADC Feature is not supported (not implemented on STM322xG_EVAL board)
  ----------------------------------------------------------------------------*/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM322xG_EVAL_IOE_H
#define __STM322xG_EVAL_IOE_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup STM32_EVAL
  * @{
  */ 

/** @addtogroup STM322xG_EVAL
  * @{
  */
    
/** @defgroup STM322xG_EVAL_IOE 
  * @{
  */    


/** @defgroup STM322xG_EVAL_IOE_Exported_Types
  * @{
  */ 

/** 
  * @brief  Joystick State definitions  
  */ 
#ifndef __STM32_EVAL_H
typedef enum 
{ 
  JOY_NONE = 0,
  JOY_SEL = 1,
  JOY_DOWN = 2,
  JOY_LEFT = 3,
  JOY_RIGHT = 4,
  JOY_UP = 5
} JOYState_TypeDef
;
#endif /* __STM32_EVAL_H */
 
/** 
  * @brief  IO_Expander Error codes  
  */ 
typedef enum
{
  IOE_OK = 0,
  IOE_FAILURE, 
  IOE_TIMEOUT,
  PARAM_ERROR,
  IOE1_NOT_OPERATIONAL, 
  IOE2_NOT_OPERATIONAL
}IOE_Status_TypDef;

/** 
  * @brief  IO bit values  
  */ 
typedef enum
{
  BitReset = 0,
  BitSet = 1
}IOE_BitValue_TypeDef;
/** 
  * @brief  IO bitpolarity  
  */ 
typedef enum
{
  Normal = 0,
  Invert = 1
}IOE_BitPolarity_TypeDef;
/** 
  * @brief  IOE DMA Direction  
  */ 
typedef enum
{
  IOE_DMA_TX = 0,
  IOE_DMA_RX = 1
}IOE_DMADirection_TypeDef;

/** @defgroup STM322xG_EVAL_IOE_Exported_Constants
  * @{
  */ 

/**
 * @brief Uncomment the line below to enable verfying each written byte in write
 *        operation. The I2C_WriteDeviceRegister() function will then compare the
 *        written and read data and return error status if a mismatch occurs.
 */
/* #define VERIFY_WRITTENDATA */

/**
 * @brief Uncomment the line below if you want to use user timeout callback.
 *        Function prototypes is declared in this file but function body may be
 *        implemented into user application.  
 */
/* #define USE_TIMEOUT_USER_CALLBACK */

/**
 * @brief Uncomment the line below if you want to use user defined Delay function
 *        (for precise timing), otherwise default _delay_ function defined within
 *         this driver is used (less precise timing).  
 */
/* #define USE_Delay */

#ifdef USE_Delay
#include "main.h"
 
  #define _delay_     Delay  /* !< User can provide more timing precise _delay_ function
                                   (with 10ms time base), using SysTick for example */
#else
  #define _delay_     delay      /* !< Default _delay_ function with less precise timing */
#endif    

/*------------------------------------------------------------------------------
    Hardware Configuration 
------------------------------------------------------------------------------*/
/** 
  * @brief  I2C port definitions  
  */ 
#define IOE_I2C                          I2C1
#define IOE_I2C_CLK                      RCC_APB1Periph_I2C1
#define IOE_I2C_SCL_PIN                  GPIO_Pin_6
#define IOE_I2C_SCL_GPIO_PORT            GPIOB
#define IOE_I2C_SCL_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define IOE_I2C_SCL_SOURCE               GPIO_PinSource6
#define IOE_I2C_SCL_AF                   GPIO_AF_I2C1
#define IOE_I2C_SDA_PIN                  GPIO_Pin_9
#define IOE_I2C_SDA_GPIO_PORT            GPIOB
#define IOE_I2C_SDA_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define IOE_I2C_SDA_SOURCE               GPIO_PinSource9
#define IOE_I2C_SDA_AF                   GPIO_AF_I2C1
#define IOE_I2C_DR                       ((uint32_t)0x40005410)

/* I2C clock speed configuration (in Hz) 
  WARNING: 
   Make sure that this define is not already declared in other files (ie. 
  stm322xg_eval.h file). It can be used in parallel by other modules. */
#ifndef I2C_SPEED
 #define I2C_SPEED                        100000
#endif /* I2C_SPEED */

/** 
  * @brief  IOE DMA definitions  
  */
#define IOE_DMA_CLK                      RCC_AHB1Periph_DMA1
#define IOE_DMA_CHANNEL                  DMA_Channel_1
#define IOE_DMA_TX_STREAM                DMA1_Stream6   
#define IOE_DMA_RX_STREAM                DMA1_Stream0
#define IOE_DMA_TX_TCFLAG                DMA_FLAG_TCIF6
#define IOE_DMA_RX_TCFLAG                DMA_FLAG_TCIF0

/** 
  * @brief  IO Expander Interrupt line on EXTI  
  */ 
#define IOE_IT_PIN                       GPIO_Pin_2
#define IOE_IT_GPIO_PORT                 GPIOI
#define IOE_IT_GPIO_CLK                  RCC_AHB1Periph_GPIOI
#define IOE_IT_EXTI_PORT_SOURCE          EXTI_PortSourceGPIOI
#define IOE_IT_EXTI_PIN_SOURCE           EXTI_PinSource2
#define IOE_IT_EXTI_LINE                 EXTI_Line2
#define IOE_IT_EXTI_IRQn                 EXTI2_IRQn   

/**
  * @brief Eval Board IO Pins definition 
  */ 
#define AUDIO_RESET_PIN             IO_Pin_5 /* IO_Exapnader_2 */ /* Output */
#define CAMERA_RESET_PIN            IO_Pin_4 /* IO_Exapnader_1 */ /* Output */
#define CAMERA_PLUG_PIN             IO_Pin_5 /* IO_Exapnader_1 */ /* Output */
#define MEMS_INT1_PIN               IO_Pin_6 /* IO_Exapnader_1 */ /* Input */
#define MEMS_INT2_PIN               IO_Pin_7 /* IO_Exapnader_1 */ /* Input */

/**
  * @brief Eval Board both IO Exapanders Pins definition 
  */ 
#define IO1_IN_ALL_PINS          (uint32_t)(MEMS_INT1_PIN | MEMS_INT2_PIN)
#define IO1_OUT_ALL_PINS         (uint32_t)(CAMERA_RESET_PIN | CAMERA_PLUG_PIN)
#define IO2_IN_ALL_PINS          (uint32_t)(JOY_IO_PINS)
#define IO2_OUT_ALL_PINS         (uint32_t)(AUDIO_RESET_PIN)

/** 
  * @brief  The 7 bits IO Expanders adresses 
  */ 
#define IOE_1_ADDR                 0x42    
#define IOE_2_ADDR                 0x46    

/*------------------------------------------------------------------------------
    Functional and Interrupt Management
------------------------------------------------------------------------------*/
/** 
  * @brief  Interrupt source configuration definitons  
  */ 
#define IOE_ITSRC_INMEMS        0x01  /* IO_Exapnder 1 */
#define IOE_ITSRC_JOYSTICK      0x02  /* IO_Exapnder 2 */

/*------------------------------------------------------------------------------
    CAT9544 device register definition
------------------------------------------------------------------------------*/
/** 
  * @brief  Identification registers  
  */ 


/** 
  * @brief  CAT9554 Registers  
  */ 
#define IOE_CAT9554_REG_INPUT        0x00  /* Input Port Register of CAT9554 */
#define IOE_CAT9554_REG_OUTPUT       0x01  /* Output Port Register of CAT9554 */
#define IOE_CAT9554_REG_POLARINV     0x02  /* Polarity Inversion Register of CAT9554 */
                                       /* 1-INVERT */
#define IOE_CAT9554_REG_CONFIG       0x03  /* Configuration Register of CAT9554 */
									   /* 1-INPUT   0-OUTPUT */
/*------------------------------------------------------------------------------
    Functions parameters defines
------------------------------------------------------------------------------*/
/**
  * @brief JOYSTICK Pins definition 
  */ 
#define IOE_JOY_IO_SEL                   IO_Pin_0
#define IOE_JOY_IO_DOWN                  IO_Pin_1
#define IOE_JOY_IO_LEFT                  IO_Pin_2
#define IOE_JOY_IO_UP                    IO_Pin_3
#define IOE_JOY_IO_RIGHT                 IO_Pin_4
#define IOE_JOY_IO_NONE                  IOE_JOY_IO_PINS
#define IOE_JOY_IO_PINS                  (uint32_t)(IO_Pin_0 | IO_Pin_1 | IO_Pin_2 | IO_Pin_3 | IO_Pin_4)

/**
  * @brief MEMS INT Pins definition 
  */ 
#define IOE_MEMSINT_IO_INT1              IO_Pin_6
#define IOE_MEMSINT_IO_INT2              IO_Pin_7
#define IOE_MEMSINT_IO_NONE              IOE_MEMSINT_IO_PINS
#define IOE_MEMSINT_IO_PINS              (uint32_t)(IO_Pin_6 | IO_Pin_7)

/** 
  * @brief  IO Pins  
  */ 
#define IO_Pin_0                 0x01
#define IO_Pin_1                 0x02
#define IO_Pin_2                 0x04
#define IO_Pin_3                 0x08
#define IO_Pin_4                 0x10
#define IO_Pin_5                 0x20
#define IO_Pin_6                 0x40
#define IO_Pin_7                 0x80
#define IO_Pin_ALL               0xFF

/** 
  * @brief  IO Pin directions  
  */ 
#define Direction_IN             0x01
#define Direction_OUT            0x00

/** 
  * @brief  Interrupt Line output parameters  
  */ 
#define Polarity_Invert          0x01
#define Polarity_Normal          0x00

/** 
  * @brief IO Interrupts  
  */ 
#define IO_IT_0                  0x01
#define IO_IT_1                  0x02
#define IO_IT_2                  0x04
#define IO_IT_3                  0x08
#define IO_IT_4                  0x10
#define IO_IT_5                  0x20
#define IO_IT_6                  0x40
#define IO_IT_7                  0x80
#define ALL_IT                   0xFF
#define IOE_JOY_IT               (uint8_t)(IO_IT_0 | IO_IT_1 | IO_IT_2 | IO_IT_3 | IO_IT_4)	/* IO_Exapnder 2 */
#define IOE_MEMS_IT            (uint8_t)(IO_IT_6 | IO_IT_7)	/* IO_Exapnder 1 */


/**
  * @}
  */ 



/** @defgroup STM322xG_EVAL_IOE_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 



/** @defgroup STM322xG_EVAL_IOE_Exported_Functions
  * @{
  */ 

/** 
  * @brief  Configuration and initialization functions  
  */
uint8_t IOE_Config(void);
uint8_t IOE_ITConfig(uint8_t IOE_ITSRC_Source);

/** 
  * @brief  Timeout user callback function. This function is called when a timeout
  *         condition occurs during communication with IO Expander. Only protoype
  *         of this function is decalred in IO Expander driver. Its implementation
  *         may be done into user application. This function may typically stop
  *         current operations and reset the I2C peripheral and IO Expander.
  *         To enable this function use uncomment the define USE_TIMEOUT_USER_CALLBACK
  *         at the top of this file.          
  */
#ifdef USE_TIMEOUT_USER_CALLBACK 
 uint8_t IOE_TimeoutUserCallback(void);
#else
 #define IOE_TimeoutUserCallback()  IOE_TIMEOUT
#endif /* USE_TIMEOUT_USER_CALLBACK */

/** 
  * @brief IO pins control functions
  */
uint8_t IOE_WriteIOPin(uint8_t DeviceAddr, uint8_t IO_Pin, IOE_BitValue_TypeDef BitVal);
uint8_t IOE_ReadIOPin(uint8_t DeviceAddr, uint8_t IO_Pin); 
JOYState_TypeDef IOE_JoyStickGetState(void);
//MEMSINTState_TypeDef IOE_MemsIntGetState(void);
/** 
  * @brief Interrupts Mangement functions
  */
FlagStatus IOE_GetITIOStatus(uint8_t DeviceAddr, uint8_t IO_IT);
/** 
  * @brief IO-Expander Control functions
  */
uint8_t IOE_IOPinConfig(uint8_t DeviceAddr, uint8_t IO_Pin, uint8_t Direction);
uint8_t IOE_IOITConfig(uint8_t DeviceAddr, uint8_t IO_Pin, FunctionalState NewState);

/** 
  * @brief Low Layer functions
  */
uint8_t IOE_InPolarConfig(uint8_t DeviceAddr,uint8_t IO_Pin, IOE_BitPolarity_TypeDef PolarityType);

uint8_t I2C_WriteDeviceRegister(uint8_t DeviceAddr, uint8_t RegisterAddr, uint8_t RegisterValue);
uint8_t I2C_ReadDeviceRegister(uint8_t DeviceAddr, uint8_t RegisterAddr);

#ifdef __cplusplus
}
#endif
#endif /* __STM322xG_EVAL_IOE_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */       
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
