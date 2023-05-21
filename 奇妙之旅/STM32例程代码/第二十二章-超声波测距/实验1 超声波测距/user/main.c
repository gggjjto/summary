
#include "stm32f10x.h"
#include <string.h>
#include <stdlib.h>

#include "stdio.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "led.h"
#include "ultrasonsic.h"
#include "atim.h"

int i=0;
int main(void)
{
    float length;
    char str[32];
    
    uart_init(115200); //初始化串口，波特率115200 	
    LED_Init();                                 /* 初始化LED */
    OLED_Init();                                /* 初始化OLED */
    OLED_Clear();                               /* 清屏 */
    Hcsr04_Init();
    TIM3_init(10000 -1, 7200 -1);
    
    {
        //蜂鸣器初始化
        GPIO_InitTypeDef  GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);      /* BEEP时钟使能 */
 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;                  /* LED1引脚 */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            /* 推挽输出 */
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           /* 高速 */
        GPIO_Init(GPIOB, &GPIO_InitStructure);                      /* 初始化LED1引脚 */
        
        GPIO_ResetBits(GPIOB, GPIO_Pin_13);                         /* 关闭BEEP */
    }
    
    while(1)
    {
        i++;
        
        length=Hcsr04GetLength(); //获取距离
        OLED_ShowCHinese(0, 0, 6);  //距
        OLED_ShowCHinese(16, 0, 7); //离
        OLED_ShowCHinese(32, 0, 5 );//：
        sprintf(str,"%f",length);
        OLED_ShowString(40,1,str,8);          /* OLED屏显示 */
      
        if(length < 10){//小于10cm
            GPIO_ResetBits(GPIOA, GPIO_Pin_6); //LED1灭
            GPIO_SetBits(GPIOA, GPIO_Pin_7);   //LED2亮
            GPIO_SetBits(GPIOB, GPIO_Pin_13);                         /* 打开BEEP */
            delay_ms(300);
         }else{//正常
            GPIO_SetBits(GPIOA, GPIO_Pin_6);   //LED1亮
            GPIO_ResetBits(GPIOA, GPIO_Pin_7); //LED1灭
            GPIO_ResetBits(GPIOB, GPIO_Pin_13);                      /* 关闭BEEP */
        }
    }
}




