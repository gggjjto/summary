#include "led.h"

/**
 * @brief       ��ʼ��LED���IO��, ��ʹ��ʱ��
 * @param       ��
 * @retval      ��
 */
void LED_Init(void)
{
    LEDx_Init(RCC_LED1,Pin_LED1,GPIO_LED1);
    LEDx_Init(RCC_LED2,Pin_LED2,GPIO_LED2);
    LEDx_Init(RCC_LED3,Pin_LED3,GPIO_LED3);
}

void LEDx_Init(uint32_t RCC_APB2Periph,uint16_t GPIO_Pin,GPIO_TypeDef* GPIOx)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);             /* LEDʱ��ʹ�� */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;                         /* LED���� */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                  /* ������� */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 /* ���� */
    GPIO_Init(GPIOx, &GPIO_InitStructure);                            /* ��ʼ��LED���� */
    
    GPIO_ResetBits(GPIOx, GPIO_Pin);                                  /* �ر� LED */
}

void X_led(int x)
{
	uint8_t msg[8]={0};
	if(x==1){
		set_LED1();
		delay_ms(300);
		reset_LED1();
	}
	if(x==3){
		set_LED2();
		delay_ms(300);
		reset_LED2();
	}
	if(x==2){
		set_LED3();
		delay_ms(300);
		reset_LED3();
	}
	if(x!=0)
	{
		msg[0]=x;
		CAN1_Send_Msg(msg,1);
	}
}
