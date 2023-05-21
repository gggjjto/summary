#include "led.h"

/**
 * @brief       初始化LED相关IO口, 并使能时钟
 * @param       无
 * @retval      无
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
    RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);             /* LED时钟使能 */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;                         /* LED引脚 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                  /* 推挽输出 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 /* 高速 */
    GPIO_Init(GPIOx, &GPIO_InitStructure);                            /* 初始化LED引脚 */
    
    GPIO_ResetBits(GPIOx, GPIO_Pin);                                  /* 关闭 LED */
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
