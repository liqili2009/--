
#include "stm322xg_eval_NRF24l01.h"

u8 SPI3_ReadWriteByte(u8 TxData)                                        //SPI��д���ݺ���
{		
	u8 retry=0;				 	
	/* Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET)      //���ͻ����־λΪ��
		{
		retry++;
		if(retry>200)return 0;
		}			  
	/* Send byte through the SPI3 peripheral */
	SPI_I2S_SendData(SPI3, TxData);                                    //ͨ������SPI3����һ������
	retry=0;
	/* Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET);   //���ջ����־λ��Ϊ��
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	/* Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(SPI3);                                 //ͨ��SPI3���ؽ�������				    
}
//NRF24L01 �������� 

	 
const u8 TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ
const u8 RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ							    
//��ʼ��24L01��IO��
void NRF24L01_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef    SPI_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;  

  /* Enable SPI Alternate Function clocks */
  //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);	
  	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOB, ENABLE); 

  GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_SPI3);  
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_SPI3);	
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_SPI3);

  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;//GPIO_PuPd_DOWN;//  

  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
  GPIO_Init(GPIOC,&GPIO_InitStructure);   	   
												   
  /*!< SPI configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;//SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;//SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;//SPI_BaudRatePrescaler_4;

  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI3, &SPI_InitStructure);

  //CS
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_25MHz;
  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;// GPIO_PuPd_NOPULL;// 

  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
  GPIO_Init(GPIOC,&GPIO_InitStructure); 
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
  GPIO_Init(GPIOF,&GPIO_InitStructure);     	    			

  Set_NRF24L01_CE;                                           //��ʼ��ʱ������ 
  Set_NRF24L01_CSN                                           //��ʼ��ʱ������ 
  	
  /* Set EXTI pin as Input PullUp - TP_PENIOQ_INT */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  
  
  /* Connect Button EXTI Line to TP_PENIOQ GPIO Pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource2);   
/* Configure Button EXTI line */
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);  
                                                       //��ʼ��SPI
	/* Enable SPI3  */
	SPI_Cmd(SPI3, ENABLE);                                              //ʹ��SPI3����
	
	SPI3_ReadWriteByte(0xff);                                           //��������

	Clr_NRF24L01_CE; 	                               //��ֹ24L01
	Set_NRF24L01_CSN;                                  //SPIƬѡȡ��
}
//�ϵ���NRF24L01�Ƿ���λ
//д5������Ȼ���ٶ��������бȽϣ���ͬʱ����ֵ:0����ʾ��λ;���򷵻�1����ʾ����λ	
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 buf1[5];
	u8 i; 
 	 
	NRF24L01_Write_Buf(SPI_WRITE_REG+TX_ADDR,buf,5);//д��5���ֽڵĵ�ַ.
	NRF24L01_Read_Buf(TX_ADDR,buf1,5);              //����д��ĵ�ַ  	

	for(i=0;i<5;i++)if(buf1[i]!=0XA5)break;					   
	if(i!=5)return 1;                               //NRF24L01����λ	
	return 0;		                                //NRF24L01��λ
}	 	 
//ͨ��SPIд�Ĵ���
u8 NRF24L01_Write_Reg(u8 regaddr,u8 data)
{
	u8 status;	
    Clr_NRF24L01_CSN;                    //ʹ��SPI����
  	status =SPI3_ReadWriteByte(regaddr); //���ͼĴ����� 
  	SPI3_ReadWriteByte(data);            //д��Ĵ�����ֵ
  	Set_NRF24L01_CSN;                    //��ֹSPI����	   
  	return(status);       		         //����״ֵ̬
}
//��ȡSPI�Ĵ���ֵ ��regaddr:Ҫ���ļĴ���
u8 NRF24L01_Read_Reg(u8 regaddr)
{
	u8 reg_val;	    
 	Clr_NRF24L01_CSN;                //ʹ��SPI����		
  	SPI3_ReadWriteByte(regaddr);     //���ͼĴ�����
  	reg_val=SPI3_ReadWriteByte(0XFF);//��ȡ�Ĵ�������
  	Set_NRF24L01_CSN;                //��ֹSPI����		    
  	return(reg_val);                 //����״ֵ̬
}	
//��ָ��λ�ö���ָ�����ȵ�����
//*pBuf:����ָ��
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ 
u8 NRF24L01_Read_Buf(u8 regaddr,u8 *pBuf,u8 datalen)
{
	u8 status,u8_ctr;	       
  	Clr_NRF24L01_CSN;                     //ʹ��SPI����
  	status=SPI3_ReadWriteByte(regaddr);   //���ͼĴ���ֵ(λ��),����ȡ״ֵ̬   	   
 	for(u8_ctr=0;u8_ctr<datalen;u8_ctr++)pBuf[u8_ctr]=SPI3_ReadWriteByte(0XFF);//��������
  	Set_NRF24L01_CSN;                     //�ر�SPI����
  	return status;                        //���ض�����״ֵ̬
}
//��ָ��λ��дָ�����ȵ�����
//*pBuf:����ָ��
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
u8 NRF24L01_Write_Buf(u8 regaddr, u8 *pBuf, u8 datalen)
{
	u8 status,u8_ctr;	    
 	Clr_NRF24L01_CSN;                                    //ʹ��SPI����
  	status = SPI3_ReadWriteByte(regaddr);                //���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
  	for(u8_ctr=0; u8_ctr<datalen; u8_ctr++)SPI3_ReadWriteByte(*pBuf++); //д������	 
  	Set_NRF24L01_CSN;                                    //�ر�SPI����
  	return status;                                       //���ض�����״ֵ̬
}				   
//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:�������״��
u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 state;   
	Clr_NRF24L01_CE;
  	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//д���ݵ�TX BUF  32���ֽ�
 	Set_NRF24L01_CE;                                     //��������	   
	while(READ_NRF24L01_IRQ!=0);                              //�ȴ��������
	state=NRF24L01_Read_Reg(STATUS);                     //��ȡ״̬�Ĵ�����ֵ	   
	NRF24L01_Write_Reg(SPI_WRITE_REG+STATUS,state);      //���TX_DS��MAX_RT�жϱ�־
	if(state&MAX_TX)                                     //�ﵽ����ط�����
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);               //���TX FIFO�Ĵ��� 
		return MAX_TX; 
	}
	if(state&TX_OK)                                      //�������
	{
		return TX_OK;
	}
	return 0xff;                                         //����ԭ����ʧ��
}
//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:0��������ɣ��������������
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 state;		    							      
	state=NRF24L01_Read_Reg(STATUS);                //��ȡ״̬�Ĵ�����ֵ    	 
	NRF24L01_Write_Reg(SPI_WRITE_REG+STATUS,state); //���TX_DS��MAX_RT�жϱ�־
	if(state&RX_OK)                                 //���յ�����
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
		NRF24L01_Write_Reg(FLUSH_RX,0xff);          //���RX FIFO�Ĵ��� 
		return 0; 
	}	   
	return 1;                                      //û�յ��κ�����
}

//�ú�����ʼ��NRF24L01��RXģʽ
//����RX��ַ,дRX���ݿ��,ѡ��RFƵ��,�����ʺ�LNA HCURR
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
void RX_Mode(void)
{
	Clr_NRF24L01_CE;	  
  	NRF24L01_Write_Buf(SPI_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ
	  
  	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��    
  	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ  	 
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_CH,40);	     //����RFͨ��Ƶ��		  
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ�� 	    
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_SETUP,0x0f); //����TX�������,0db����,2Mbps,���������濪��   
  	NRF24L01_Write_Reg(SPI_WRITE_REG+CONFIG, 0x0f);  //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
  	Set_NRF24L01_CE;                                //CEΪ��,�������ģʽ 
}						 
//�ú�����ʼ��NRF24L01��TXģʽ
//����TX��ַ,дTX���ݿ��,����RX�Զ�Ӧ��ĵ�ַ,���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR
//PWR_UP,CRCʹ��
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
//CEΪ�ߴ���10us,����������.	 
void TX_Mode(void)
{														 
	Clr_NRF24L01_CE;	    
  	NRF24L01_Write_Buf(SPI_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);    //дTX�ڵ��ַ 
  	NRF24L01_Write_Buf(SPI_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK	  

  	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    
  	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  
  	NRF24L01_Write_Reg(SPI_WRITE_REG+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_CH,40);       //����RFͨ��Ϊ40
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
  	NRF24L01_Write_Reg(SPI_WRITE_REG+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
	Set_NRF24L01_CE;                                  //CEΪ��,10us����������
}		  


