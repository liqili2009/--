/**
  ******************************************************************************
  * @file    stm322xg_eval_ioe.c
  * @author  MCD Application Team
  * @version V4.6.1
  * @date    18-April-2011
  * @brief   This file provides a set of functions needed to manage the STMPE811
  *          IO Expander devices mounted on STM322xG-EVAL evaluation board(MB786)
  *          RevA and RevB.
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
  
    Note:
    -----
    - This driver uses the DMA method for sending and receiving data on I2C bus
      which allow higher efficiency and reliability of the communication.  
  
      SUPPORTED FEATURES:
      - IO Read/write : Set/Reset and Read (Polling/Interrupt)
      - Joystick: config and Read (Polling/Interrupt)
      - Audio Features:Reset(output)
      - Camera Feature: Reset(output),Plug(output)
	  - Mems Feature: Int1(input),Int2(input)
  ----------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm322xg_eval_ioe_uda1380.h"

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
  * @brief  This file includes the IO Expander driver for CAT9554 IO Expander 
  *         devices.
  * @{
  */ 
  

/** @defgroup STM322xG_EVAL_IOE_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM322xG_EVAL_IOE_Private_Defines
  * @{
  */ 
#define TIMEOUT_MAX    0x3000 /*<! The value of the maximal timeout for I2C waiting loops */
/**
  * @}
  */ 


/** @defgroup STM322xG_EVAL_IOE_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM322xG_EVAL_IOE_Private_Variables
  * @{
  */ 
uint32_t IOE_TimeOut = TIMEOUT_MAX; /*<! Value of Timeout when I2C communication fails */
/**
  * @}
  */ 


/** @defgroup STM322xG_EVAL_IOE_Private_FunctionPrototypes
  * @{
  */ 
static void IOE_GPIO_Config(void);
static void IOE_I2C_Config(void);
static void IOE_DMA_Config(IOE_DMADirection_TypeDef Direction, uint8_t* buffer);
static void IOE_EXTI_Config(void);

#if 0//ndef USE_Delay
static void delay(__IO uint32_t nCount);
#endif /* USE_Delay*/
/**
  * @}
  */ 


/** @defgroup STM322xG_EVAL_IOE_Private_Functions
  * @{
  */ 


/**
  * @brief  Initializes and Configures the two IO_Expanders Functionalities 
  *         (IOs, Touch Screen ..) and configures all STM322xG_EVAL necessary
  *         hardware (GPIOs, APB clocks ..).
  * @param  None
  * @retval IOE_OK if all initializations done correctly. Other value if error.
  */
uint8_t IOE_Config(void)
{
  /* Configure the needed pins */
  IOE_GPIO_Config(); 
  
  IOE_I2C_Config();
    
  /* ---------------------- IO Expander 1 configuration --------------------- */
  /* Configure the MEMS interrupt pins in Input mode */
  IOE_IOPinConfig(IOE_1_ADDR, (uint8_t)(MEMS_INT1_PIN | MEMS_INT2_PIN), Direction_IN); 
  /* Configure the Camera Reset pin and Plug pin in output mode pin*/
  IOE_IOPinConfig(IOE_1_ADDR, (uint8_t)(CAMERA_RESET_PIN | CAMERA_PLUG_PIN), Direction_OUT);
  /* Apply the default state for the out pins */
  IOE_WriteIOPin(IOE_1_ADDR, CAMERA_RESET_PIN, BitSet);
  IOE_WriteIOPin(IOE_1_ADDR, CAMERA_PLUG_PIN, BitReset);
  /* ------------------------------------------------------------------------ */
  
  /* ---------------------- IO Expander 2 configuration --------------------- */
  /* Configure the Joystick pins in Input mode */
  IOE_IOPinConfig(IOE_2_ADDR, IOE_JOY_IO_PINS , Direction_IN); 
  /* Configure the Audio Codec Reset pin in output mode pin*/
  IOE_IOPinConfig(IOE_2_ADDR, (uint32_t)(AUDIO_RESET_PIN), Direction_OUT); 
  /* Apply the default state for the out pins */
  IOE_WriteIOPin(IOE_2_ADDR, AUDIO_RESET_PIN, BitSet);   
  /* ------------------------------------------------------------------------ */
  
  /* Configuration is OK */
  return IOE_OK; 
}

/**
  * @brief  Configures The selected interrupts on the IO Expanders.
  * @param  IOE_ITSRC_Source: the source of the interrupts. Could be one or a 
  *         combination of the following parameters:
  *   @arg  IOE_ITSRC_JOYSTICK: Joystick IO intputs.
  *   @arg  IOE_ITSRC_INMEMS: MEMS interrupt lines.
  * @retval IOE_OK: if all initializations are OK. Other value if error.
  */
uint8_t IOE_ITConfig(uint8_t IOE_ITSRC_Source)
{   
  /* Manage the Joystick Interrupts */  
  if (IOE_ITSRC_Source & IOE_ITSRC_JOYSTICK)
  {     
    /* Enable the Joystick pins to generate interrupt (infact IO pin in) */
    IOE_IOITConfig(IOE_2_ADDR, IOE_JOY_IT, ENABLE);         
  }

  /* Manage the MEMS Interrupts lines  */  
  if (IOE_ITSRC_Source & IOE_ITSRC_INMEMS)
  {
    /* Enable the pins to generate interrupt (infact IO pin in) */
    IOE_IOITConfig(IOE_1_ADDR, IOE_MEMS_IT, ENABLE);        
  }    
    
  /* Configure the Interrupt line as EXTI source */
  IOE_EXTI_Config();    
  
  /* If all OK return IOE_OK */
  return IOE_OK;
}

/**
  * @brief  Writes a bit value to an output IO pin.
  * @param IO_Pin: The output pin to be set or reset. This parameter can be one 
  *        of the following values:
  *   @arg  AUDIO_RESET_PIN: Audio codec reset pin
  *   @arg  MII_INT_PIN: Ethernet Phy MII interrupt pin
  *   @arg  VBAT_DIV_PIN: Battery divider pin
  * @param BitVal: The value to be set. This parameter can be one of the
  *        following values: BitSet or BitReset. See IOE_BitVal_TypeDef.
  * @retval IOE_OK or PARAM_ERROR
  */
uint8_t IOE_WriteIOPin(uint8_t DeviceAddr, uint8_t IO_Pin, IOE_BitValue_TypeDef BitVal)
{
  //uint8_t DeviceAddr = 0;
  uint8_t tmp = 0;
 
  /* get the Interrupt status */
  tmp = I2C_ReadDeviceRegister(DeviceAddr, IOE_CAT9554_REG_OUTPUT);
  /* Get the IO expander Address according to which pin is to be controlled */
 /* if (IO_Pin & IO1_OUT_ALL_PINS)
  {
    DeviceAddr = IOE_1_ADDR;
  }
  else if (IO_Pin & IO2_OUT_ALL_PINS)
  {
    DeviceAddr = IOE_2_ADDR;
  }
  else
  {
    return PARAM_ERROR;
  }	 */
  
  /* Apply the bit value to the selected pin */
  if (BitVal == BitReset)
  {
    tmp&=~(uint8_t)IO_Pin;
    /* Set the register */
    I2C_WriteDeviceRegister(DeviceAddr, IOE_CAT9554_REG_OUTPUT, tmp);
  }
  else
  {
	tmp|=(uint8_t)IO_Pin;
    /* Set the register */
    I2C_WriteDeviceRegister(DeviceAddr, IOE_CAT9554_REG_OUTPUT, tmp);
  }
  
  return IOE_OK;
}


/**
  * @brief  Returns the status of the selected input IO pin.
  * @param IO_Pin: The input pin to be read. This parameter can be one 
  *  of the following values:
  *   @arg  MEMS_INT1_PIN: MEMS interrupt line 1.
  *   @arg  MEMS_INT2_PIN: MEMS interrupt line 2.
  *   @arg  JOY_IO_PINS: Joystick IO pins (use IOE_JoyStickGetState for these pins)  
  * @retval None
  */
uint8_t IOE_ReadIOPin(uint8_t DeviceAddr, uint8_t IO_Pin)
{
  //uint8_t DeviceAddr = 0;
  uint8_t tmp = 0;  
  /*if (IO_Pin & IO1_IN_ALL_PINS)
  {
    DeviceAddr = IOE_1_ADDR;
  }
  else if (IO_Pin & IO2_IN_ALL_PINS)
  {
    DeviceAddr = IOE_2_ADDR;
  }
  else 
  {
    return PARAM_ERROR;
  }	*/
  
  /* Get all the Pins status */
  tmp = I2C_ReadDeviceRegister(DeviceAddr, IOE_CAT9554_REG_INPUT);
  if ((tmp & (uint8_t)IO_Pin) != 0)
  {
    return BitSet;
  }  
  else 
  {
    return BitReset;
  }
}
/**
  * @brief  Returns the current Mems status.
  * @param  None
  * @retval The code of the Joystick key pressed: 
  *   @arg  MEMS_NONE
  *   @arg  MEMS_INT1
  *   @arg  MEMS_INT2
  */
#if 0
MEMSINTState_TypeDef IOE_MemsIntGetState(void)
{
  uint8_t tmp = 0;
  /* Read the status of all pins */
  tmp = (uint32_t)I2C_ReadDeviceRegister(IOE_1_ADDR, IOE_CAT9554_REG_INPUT);
   
  /* Check the pressed keys */
  if ((tmp & IOE_MEMSINT_IO_NONE) == IOE_MEMSINT_IO_NONE)
  {
    return (MEMSINTState_TypeDef) MEMSINT_NONE;
  }
  else if (!(tmp & IOE_MEMSINT_IO_INT1))
  {
    return (MEMSINTState_TypeDef) MEMSINT_1;
  }
  else if (!(tmp & IOE_MEMSINT_IO_INT2))
  {
    return (MEMSINTState_TypeDef) MEMSINT_2;
  }	  
  else
  { 
    return (MEMSINTState_TypeDef) MEMSINT_NONE;
  }
}
  #endif
/**
  * @brief  Returns the current Joystick status.
  * @param  None
  * @retval The code of the Joystick key pressed: 
  *   @arg  JOY_NONE
  *   @arg  JOY_SEL
  *   @arg  JOY_DOWN
  *   @arg  JOY_LEFT
  *   @arg  JOY_RIGHT
  *   @arg  JOY_UP
  */
JOYState_TypeDef IOE_JoyStickGetState(void)
{
  uint8_t tmp = 0;
  /* Read the status of all pins */
  tmp = (uint32_t)I2C_ReadDeviceRegister(IOE_2_ADDR, IOE_CAT9554_REG_INPUT);
   
  /* Check the pressed keys */
  if ((tmp & IOE_JOY_IO_NONE) == IOE_JOY_IO_NONE)
  {
    return (JOYState_TypeDef) JOY_NONE;
  }
  else if (!(tmp & IOE_JOY_IO_SEL))
  {
    return (JOYState_TypeDef) JOY_SEL;
  }
  else if (!(tmp & IOE_JOY_IO_DOWN))
  {
    return (JOYState_TypeDef) JOY_DOWN;
  }
  else if (!(tmp & IOE_JOY_IO_LEFT))
  {
    return (JOYState_TypeDef) JOY_LEFT;
  }
  else if (!(tmp & IOE_JOY_IO_RIGHT))
  {
    return (JOYState_TypeDef) JOY_RIGHT;
  }
  else if (!(tmp & IOE_JOY_IO_UP))
  {
    return (JOYState_TypeDef) JOY_UP;
  }
  else
  { 
    return (JOYState_TypeDef) JOY_NONE;
  }
}
/**
  * @brief  Checks the status of the selected IO interrupt pending bit
  * @param  DeviceAddr: The address of the IOExpander, could be : IOE_1_ADDR
  *         or IOE_2_ADDR.
  * @param  IO_Pin: the IO level to be checked could be IO_Pinx Where x can be 
  *         from 0 to 7.             
  * @retval Status of the checked flag. Could be SET or RESET.
  */
FlagStatus IOE_GetITIOStatus(uint8_t DeviceAddr, uint8_t IO_Pin)
{
  uint8_t tmp = 0;
 
  /* get the Interrupt status */
  tmp = I2C_ReadDeviceRegister(DeviceAddr, IOE_CAT9554_REG_INPUT);
  
  if ((tmp & (uint8_t)IO_Pin) != 0)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}


/**
  * @brief  Configures the selected pin direction (to be an input or an output)
  * @param  DeviceAddr: The address of the IOExpander, could be : IOE_1_ADDR
  *         or IOE_2_ADDR.
  * @param  IO_Pin: IO_Pin_x: Where x can be from 0 to 7.   
  * @param  Direction: could be Direction_IN or Direction_OUT.      
  * @retval IOE_OK: if all initializations are OK. Other value if error.
  */
uint8_t IOE_IOPinConfig(uint8_t DeviceAddr, uint8_t IO_Pin, uint8_t Direction)
{
  uint8_t tmp = 0;   
  
  /* Get all the Pins direction */
  tmp = I2C_ReadDeviceRegister(DeviceAddr, IOE_CAT9554_REG_CONFIG);
  
  if (Direction != Direction_IN)
  {
    tmp &= ~(uint8_t)IO_Pin;
  }  
  else 
  {
    tmp |= (uint8_t)IO_Pin;	 
  }
  
  /* Write the register new value */
  I2C_WriteDeviceRegister(DeviceAddr, IOE_CAT9554_REG_CONFIG, tmp);
  
  /* If all OK return IOE_OK */
  return IOE_OK;      
}

/**
  * @brief  Configures the selected pins to generate an interrupt or not.
  * @param  DeviceAddr: The address of the IOExpander, could be : IOE_1_ADDR
  *         or IOE_2_ADDR.
  * @param  IO_Pin: The IO interrupt to be configured. This parameter could be any
  *         combination of the following values:
  *   @arg  IO_Pin_x: where x can be from 0 to 7.
  * @param  NewState: could be ENABLE or DISABLE.  
  * @retval IOE_OK: if all initializations are OK. Other value if error.
  */
uint8_t IOE_IOITConfig(uint8_t DeviceAddr, uint8_t IO_Pin, FunctionalState NewState)
{
  uint8_t tmp = 0;
 
  /* Get all the Pins direction */
  tmp = I2C_ReadDeviceRegister(DeviceAddr, IOE_CAT9554_REG_CONFIG);
  
  if (NewState != DISABLE)
  {
    /* Set the interrupts to be Enabled */    
    tmp |= (uint8_t)IO_Pin;
  }
  else
  {
    /* Set the interrupts to be Disabled */    
    tmp &= ~(uint8_t)IO_Pin;
  }
  
  /* Set the register */
  I2C_WriteDeviceRegister(DeviceAddr, IOE_CAT9554_REG_CONFIG, tmp);
  
  /* If all OK return IOE_OK */
  return IOE_OK;   
}
/**
  * @brief  Configures the input pin polarity invert or not
  * @param  Polarity: could be
  *   @arg  Normal:       
  *   @arg  Invert: input level invert     
  * @param  IO_Pin: The IO interrupt to be configured. This parameter could be any
  *         combination of the following values:
  *   @arg  IO_Pin_x: where x can be from 0 to 7.    
  * @retval IOE_OK: if all initializations are OK. Other value if error.
  */
uint8_t IOE_InPolarConfig(uint8_t DeviceAddr,uint8_t IO_Pin, IOE_BitPolarity_TypeDef PolarityType)
{
  uint8_t tmp = 0;

  /* Get all the Pins Polarity */
  tmp = I2C_ReadDeviceRegister(DeviceAddr, IOE_CAT9554_REG_POLARINV);
  /* Modify the input Polarity configuration */
  if(PolarityType == Invert)
  {
    tmp |= (uint8_t)IO_Pin;
	/* Set the register */
    I2C_WriteDeviceRegister(DeviceAddr, IOE_CAT9554_REG_POLARINV, tmp);
  }
  else
  {	
    tmp &= ~(uint8_t)IO_Pin;
	/* Set the register */
    I2C_WriteDeviceRegister(DeviceAddr, IOE_CAT9554_REG_POLARINV, tmp);
  }	  
  
  /* If all OK return IOE_OK */
  return IOE_OK;  
}
/**
  * @brief  Writes a value in a register of the device through I2C.
  * @param  DeviceAddr: The address of the IOExpander, could be : IOE_1_ADDR
  *         or IOE_2_ADDR. 
  * @param  RegisterAddr: The target register address
  * @param  RegisterValue: The target register value to be written 
  * @retval IOE_OK: if all operations are OK. Other value if error.
  */
uint8_t I2C_WriteDeviceRegister(uint8_t DeviceAddr, uint8_t RegisterAddr, uint8_t RegisterValue)
{
  uint32_t read_verif = 0;  
  uint8_t IOE_BufferTX = 0;
  
  /* Get Value to be written */
  IOE_BufferTX = RegisterValue;
  
  /* Configure DMA Peripheral */
  IOE_DMA_Config(IOE_DMA_TX, (uint8_t*)(&IOE_BufferTX));
  
  /* Enable the I2C peripheral */
  I2C_GenerateSTART(IOE_I2C, ENABLE);
  
  /* Test on SB Flag */
  IOE_TimeOut = TIMEOUT_MAX;
  while (I2C_GetFlagStatus(IOE_I2C,I2C_FLAG_SB) == RESET) 
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }
  
  /* Transmit the slave address and enable writing operation */
  I2C_Send7bitAddress(IOE_I2C, DeviceAddr, I2C_Direction_Transmitter);
  
  /* Test on ADDR Flag */
  IOE_TimeOut = TIMEOUT_MAX;
  while (!I2C_CheckEvent(IOE_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }
  
  /* Transmit the first address for r/w operations */
  I2C_SendData(IOE_I2C, RegisterAddr);
  
  /* Test on TXE FLag (data dent) */
  IOE_TimeOut = TIMEOUT_MAX;
  while ((!I2C_GetFlagStatus(IOE_I2C,I2C_FLAG_TXE)) && (!I2C_GetFlagStatus(IOE_I2C,I2C_FLAG_BTF)))  
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }
  
  /* Enable I2C DMA request */
  I2C_DMACmd(IOE_I2C,ENABLE);
  
  /* Enable DMA TX Channel */
  DMA_Cmd(IOE_DMA_TX_STREAM, ENABLE);
  
  /* Wait until DMA Transfer Complete */
  IOE_TimeOut = TIMEOUT_MAX;
  while (!DMA_GetFlagStatus(IOE_DMA_TX_STREAM,IOE_DMA_TX_TCFLAG))
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }  
  
  /* Wait until BTF Flag is set before generating STOP */
  IOE_TimeOut = 2 * TIMEOUT_MAX;
  while ((!I2C_GetFlagStatus(IOE_I2C,I2C_FLAG_BTF)))  
  {
  }
  
  /* Send STOP Condition */
  I2C_GenerateSTOP(IOE_I2C, ENABLE);
  
  /* Disable DMA TX Channel */
  DMA_Cmd(IOE_DMA_TX_STREAM, DISABLE);
  
  /* Disable I2C DMA request */  
  I2C_DMACmd(IOE_I2C,DISABLE);
  
  /* Clear DMA TX Transfer Complete Flag */
  DMA_ClearFlag(IOE_DMA_TX_STREAM,IOE_DMA_TX_TCFLAG);
  
#ifdef VERIFY_WRITTENDATA
  /* Verify (if needed) that the loaded data is correct  */
  
  /* Read the just written register*/
  read_verif = I2C_ReadDeviceRegister(DeviceAddr, RegisterAddr);
  /* Load the register and verify its value  */
  if (read_verif != RegisterValue)
  {
    /* Control data wrongly transferred */
    read_verif = IOE_FAILURE;
  }
  else
  {
    /* Control data correctly transferred */
    read_verif = 0;
  }
#endif
  
  /* Return the verifying value: 0 (Passed) or 1 (Failed) */
  return read_verif;
}

/**
  * @brief  Reads a register of the device through I2C.
  * @param  DeviceAddr: The address of the device, could be : IOE_1_ADDR
  *         or IOE_2_ADDR. 
  * @param  RegisterAddr: The target register address (between 00x and 0x24)
  * @retval The value of the read register (0xAA if Timeout occurred)   
  */
uint8_t I2C_ReadDeviceRegister(uint8_t DeviceAddr, uint8_t RegisterAddr)
{
  uint8_t IOE_BufferRX[2] = {0x00, 0x00};  
  
  /* Configure DMA Peripheral */
  IOE_DMA_Config(IOE_DMA_RX, (uint8_t*)IOE_BufferRX);
  
  /* Enable DMA NACK automatic generation */
  I2C_DMALastTransferCmd(IOE_I2C, ENABLE);
  
  /* Enable the I2C peripheral */
  I2C_GenerateSTART(IOE_I2C, ENABLE);
  
  /* Test on SB Flag */
  IOE_TimeOut = TIMEOUT_MAX;
  while (!I2C_GetFlagStatus(IOE_I2C,I2C_FLAG_SB)) 
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }
  
  /* Send device address for write */
  I2C_Send7bitAddress(IOE_I2C, DeviceAddr, I2C_Direction_Transmitter);
  
  /* Test on ADDR Flag */
  IOE_TimeOut = TIMEOUT_MAX;
  while (!I2C_CheckEvent(IOE_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) 
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }
  
  /* Send the device's internal address to write to */
  I2C_SendData(IOE_I2C, RegisterAddr);  
  
  /* Test on TXE FLag (data dent) */
  IOE_TimeOut = TIMEOUT_MAX;
  while ((!I2C_GetFlagStatus(IOE_I2C,I2C_FLAG_TXE)) && (!I2C_GetFlagStatus(IOE_I2C,I2C_FLAG_BTF)))  
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }
  
  /* Send START condition a second time */  
  I2C_GenerateSTART(IOE_I2C, ENABLE);
  
  /* Test on SB Flag */
  IOE_TimeOut = TIMEOUT_MAX;
  while (!I2C_GetFlagStatus(IOE_I2C,I2C_FLAG_SB)) 
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }
  
  /* Send IOExpander address for read */
  I2C_Send7bitAddress(IOE_I2C, DeviceAddr, I2C_Direction_Receiver);
  
  /* Test on ADDR Flag */
  IOE_TimeOut = TIMEOUT_MAX;
  while (!I2C_CheckEvent(IOE_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))   
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }
    
  /* Enable I2C DMA request */
  I2C_DMACmd(IOE_I2C,ENABLE);
  
  /* Enable DMA RX Channel */
  DMA_Cmd(IOE_DMA_RX_STREAM, ENABLE);
  
  /* Wait until DMA Transfer Complete */
  IOE_TimeOut = 2 * TIMEOUT_MAX;
  while (!DMA_GetFlagStatus(IOE_DMA_RX_STREAM,IOE_DMA_RX_TCFLAG))
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }        
  
  /* Send STOP Condition */
  I2C_GenerateSTOP(IOE_I2C, ENABLE);
  
  /* Disable DMA RX Channel */
  DMA_Cmd(IOE_DMA_RX_STREAM, DISABLE);
  
  /* Disable I2C DMA request */  
  I2C_DMACmd(IOE_I2C,DISABLE);
  
  /* Clear DMA RX Transfer Complete Flag */
 DMA_ClearFlag(IOE_DMA_RX_STREAM,IOE_DMA_RX_TCFLAG);
  
  /* return a pointer to the IOE_Buffer */
  return (uint8_t)IOE_BufferRX[0];
}


/**
  * @brief  Initializes the GPIO pins used by the IO expander.
  * @param  None
  * @retval None
  */
static void IOE_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Enable IOE_I2C and IOE_I2C_GPIO_PORT & Alternate Function clocks */
  RCC_APB1PeriphClockCmd(IOE_I2C_CLK, ENABLE);
  RCC_AHB1PeriphClockCmd(IOE_I2C_SCL_GPIO_CLK | IOE_I2C_SDA_GPIO_CLK |
                         IOE_IT_GPIO_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Reset IOE_I2C IP */
  RCC_APB1PeriphResetCmd(IOE_I2C_CLK, ENABLE);
  
  /* Release reset signal of IOE_I2C IP */
  RCC_APB1PeriphResetCmd(IOE_I2C_CLK, DISABLE);
  
  /* IOE_I2C SCL and SDA pins configuration */
  GPIO_InitStructure.GPIO_Pin = IOE_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(IOE_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = IOE_I2C_SDA_PIN;
  GPIO_Init(IOE_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(IOE_I2C_SCL_GPIO_PORT, IOE_I2C_SCL_SOURCE, IOE_I2C_SCL_AF);
  GPIO_PinAFConfig(IOE_I2C_SDA_GPIO_PORT, IOE_I2C_SDA_SOURCE, IOE_I2C_SDA_AF);  
  
  /* Set EXTI pin as Input PullUp - IO_Expander_INT */
  GPIO_InitStructure.GPIO_Pin = IOE_IT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(IOE_IT_GPIO_PORT, &GPIO_InitStructure);  
  
  /* Connect Button EXTI Line to Button GPIO Pin */
  SYSCFG_EXTILineConfig(IOE_IT_EXTI_PORT_SOURCE, IOE_IT_EXTI_PIN_SOURCE);  
}

/**
  * @brief  Configure the I2C Peripheral used to communicate with IO_Expanders.
  * @param  None
  * @retval None
  */
static void IOE_I2C_Config(void)
{
  I2C_InitTypeDef I2C_InitStructure;
  
  /* IOE_I2C configuration */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = I2C_SPEED;
  
  I2C_Init(IOE_I2C, &I2C_InitStructure);
}

/**
  * @brief  Configure the DMA Peripheral used to handle communication via I2C.
  * @param  None
  * @retval None
  */

static void IOE_DMA_Config(IOE_DMADirection_TypeDef Direction, uint8_t* buffer)
{
  DMA_InitTypeDef DMA_InitStructure;
  
  RCC_AHB1PeriphClockCmd(IOE_DMA_CLK, ENABLE);
  
  /* Initialize the DMA_Channel member */
  DMA_InitStructure.DMA_Channel = IOE_DMA_CHANNEL;
  
  /* Initialize the DMA_PeripheralBaseAddr member */
  DMA_InitStructure.DMA_PeripheralBaseAddr = IOE_I2C_DR;
  
  /* Initialize the DMA_Memory0BaseAddr member */
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)buffer;
  
  /* Initialize the DMA_PeripheralInc member */
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  
  /* Initialize the DMA_MemoryInc member */
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  
  /* Initialize the DMA_PeripheralDataSize member */
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  
  /* Initialize the DMA_MemoryDataSize member */
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  
  /* Initialize the DMA_Mode member */
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  
  /* Initialize the DMA_Priority member */
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  
  /* Initialize the DMA_FIFOMode member */
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
  
  /* Initialize the DMA_FIFOThreshold member */
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
  
  /* Initialize the DMA_MemoryBurst member */
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  
  /* Initialize the DMA_PeripheralBurst member */
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  
  /* If using DMA for Reception */
  if (Direction == IOE_DMA_RX)
  {    
    /* Initialize the DMA_DIR member */
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    
    /* Initialize the DMA_BufferSize member */
    DMA_InitStructure.DMA_BufferSize = 2;
    
    DMA_DeInit(IOE_DMA_RX_STREAM);
    
    DMA_Init(IOE_DMA_RX_STREAM, &DMA_InitStructure);
  }
  /* If using DMA for Transmission */
  else if (Direction == IOE_DMA_TX)
  { 
    /* Initialize the DMA_DIR member */
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    
    /* Initialize the DMA_BufferSize member */
    DMA_InitStructure.DMA_BufferSize = 1;
    
    DMA_DeInit(IOE_DMA_TX_STREAM);
    
    DMA_Init(IOE_DMA_TX_STREAM, &DMA_InitStructure);
  }
}


/**
  * @brief  Configures the IO expander Interrupt line and GPIO in EXTI mode.
  * @param  None        
  * @retval None
  */
static void IOE_EXTI_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
 
  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(IOE_IT_GPIO_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure Button pin as input floating */
  GPIO_InitStructure.GPIO_Pin = IOE_IT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(IOE_IT_GPIO_PORT, &GPIO_InitStructure);  
  
  /* Connect Button EXTI Line to Button GPIO Pin */
  SYSCFG_EXTILineConfig(IOE_IT_EXTI_PORT_SOURCE, IOE_IT_EXTI_PIN_SOURCE);  
  
  /* Configure Button EXTI line */
  EXTI_InitStructure.EXTI_Line = IOE_IT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = IOE_IT_EXTI_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

#if 0//ndef USE_Delay
/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
static void delay(__IO uint32_t nCount)
{
  __IO uint32_t index = 0; 
  for(index = (100000 * nCount); index != 0; index--)
  {
  }
}
#endif /* USE_Delay*/
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
