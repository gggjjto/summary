#include "can.h"



GPIO_InitTypeDef        GPIO_InitStructure; 
CAN_InitTypeDef        	CAN_InitStructure;
CAN_FilterInitTypeDef  	CAN_FilterInitStructure;

#if CAN1_RX0_INT_ENABLE 
	NVIC_InitTypeDef  NVIC_InitStructure;
#endif

/**
 * @brief       CAN��ʼ��
 * @param       tsjw    : ����ͬ����Ծʱ�䵥Ԫ.��Χ: 1~3;
 * @param       tbs2    : ʱ���2��ʱ�䵥Ԫ.��Χ: 1~8;
 * @param       tbs1    : ʱ���1��ʱ�䵥Ԫ.��Χ: 1~16;
 * @param       brp     : �����ʷ�Ƶ��.��Χ: 1~1024;
 *   @note      ����4������, �ں����ڲ����1, ����, �κ�һ�����������ܵ���0
 *              CAN����APB1����, ������ʱ��Ƶ��Ϊ Fpclk1 = PCLK1 = 36Mhz
 *              tq     = brp * tpclk1;
 *              ������ = Fpclk1 / ((tbs1 + tbs2 + 1) * brp);
 *              �������� can_init(1, 8, 9, 4, 1), ��CAN������Ϊ:
 *              36M / ((8 + 9 + 1) * 4) = 500Kbps
 *
 * @param       mode    : CAN_MODE_NORMAL,  ��ͨģʽ;
                          CAN_MODE_LOOPBACK,�ػ�ģʽ;
 * @retval      0,  ��ʼ���ɹ�; ����, ��ʼ��ʧ��;
 */

void can_init(uint8_t tsjw,uint8_t tbs2,uint8_t tbs1,uint16_t brp,uint8_t mode)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);	                   											 
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);	
	GPIO_PinRemapConfig(GPIO_Remap1_CAN1,ENABLE);
 
	GPIO_InitStructure.GPIO_Pin = CAN_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	GPIO_Init(CAN_RX_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = CAN_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
    GPIO_Init(CAN_RX_GPIO, &GPIO_InitStructure);
	
   	CAN_InitStructure.CAN_TTCM=DISABLE;
  	CAN_InitStructure.CAN_ABOM=DISABLE;
  	CAN_InitStructure.CAN_AWUM=DISABLE;
  	CAN_InitStructure.CAN_NART=DISABLE;
  	CAN_InitStructure.CAN_RFLM=DISABLE;
  	CAN_InitStructure.CAN_TXFP=DISABLE;


  	CAN_InitStructure.CAN_Mode= mode;
  	CAN_InitStructure.CAN_SJW= tsjw;	
  	CAN_InitStructure.CAN_BS1= tbs1; 
  	CAN_InitStructure.CAN_BS2= tbs2;
  	CAN_InitStructure.CAN_Prescaler=brp;


  	CAN_Init(CAN1, &CAN_InitStructure);

	CAN_FilterInitStructure_Init();

    #if CAN1_RX0_INT_ENABLE
		CAN_ITConfig_Init();
	#endif
}
#if CAN1_RX0_INT_ENABLE 
/**
 * @brief       CAN �����жϳ�ʼ��
 *   @note      
 * @param       
 * @retval      
 */
void CAN_ITConfig_Init(void)
{
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
    CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);
	CAN_ITConfig(CAN1,CAN_IT_BOF,ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;           
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  	NVIC_Init(&NVIC_InitStructure);
}
#endif

/**
 * @brief       CAN ��ʼ��������
 * @note      	���ղ���ѡ��������Ĵ�С��ģʽ
 * @param       
 * @retval      
 */
void CAN_FilterInitStructure_Init(void)
{
        CAN_FilterInitStructure.CAN_FilterNumber=1;						// ָ��������Ϊ1
        CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;	// ָ��������Ϊ��ʶ������λģʽ���б�ģʽ������ģʽ��
        CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit;	// ������λ��Ϊ16λ

        CAN_FilterInitStructure.CAN_FilterIdHigh=0x200<<5;				// ��������ʶ���ĸ�8λֵ
        CAN_FilterInitStructure.CAN_FilterIdLow=0x201<<5;				// ��������ʶ���ĵ�8λֵ
        CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x202<<5;			// ���������α�ʶ���ĸ�8λֵ
        CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x203<<5;			// ���������α�ʶ���ĵ�8λֵ

        CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;		// �趨��ָ���������FIFOΪ0
        CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;			// ʹ�ܹ�����
        CAN_FilterInit(&CAN_FilterInitStructure);						// ������Ĳ�����ʼ��������
}

#if CAN1_RX0_INT_ENABLE 

/**
 * @brief       CAN ���մ����ж�
 *   @note      
 * @param       RxMessage  : ����֡
 * @retval     	
 */
void USB_LP_CAN1_RX0_IRQHandler(void)
{
		int i=0;
  	    CanRxMsg RxMessage;
		RxMessage.StdId=0x00;	 
		RxMessage.ExtId=0x00;	 
		RxMessage.IDE=0;		  
		RxMessage.RTR=0;		
		RxMessage.FMI=0;

		for(i=0;i<8;i++){
			RxMessage.Data[i]=0;
		}
		i=0;
		CAN_Receive(CAN1, 0, &RxMessage);
		//USART1_DATA(RxMessage.Data,RxMessage.DLC);
		X_led(RxMessage.Data[0]);
}
#endif

/**
 * @brief       CAN ����һ������
 *   @note      ���͸�ʽ�̶�Ϊ: ��׼ID, ����֡
 * @param       id      : ��׼ID(11λ)
 * @retval      ����״̬ 0-�ɹ�; 1-ʧ��;
 */
uint16_t CAN1_Send_Msg(uint8_t* msg,uint8_t len)
{	
    uint8_t mbox;
    uint16_t i=0;
    CanTxMsg TxMessage;

    TxMessage.StdId=0x1;	 
    TxMessage.ExtId=0x00;
    TxMessage.IDE=CAN_ID_STD;		 
    TxMessage.RTR=CAN_RTR_Data;		
    TxMessage.DLC=len;						
    for(i=0;i<len;i++)
            TxMessage.Data[i]=*(msg+i);				 
        
    mbox= CAN_Transmit(CAN1, &TxMessage);  
    while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	
    if(i>=0XFFF)return 1;
    return 0;
 
}
