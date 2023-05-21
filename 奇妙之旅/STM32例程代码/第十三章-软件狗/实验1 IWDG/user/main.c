#include "stm32f10x.h"
#include <string.h>
#include <stdlib.h>

#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "iwdg.h"

int main(void)
{
    uint8_t key;
    uart_init(115200);
    LED_Init();	         //初始化LED
    KEY_Init();          //按键初始化
    delay_ms(200);       //延时200ms再初始化看门狗,LED1的变化"可见" 
    IWDG_Init(4,625);   //Tout=((4*2^4)*625)/40 (ms) = 1000 ms,溢出时间为1s
    GPIO_SetBits(GPIOA, GPIO_Pin_6);
    
    printf("No!\r\n");  //未喂狗
    while(1)
    {
        key = KEY_Scan(); /* 得到键值 */
        if(key == 1)      /* 按下KEY1 */
        {
            IWDG_ReloadCounter();//如果按下KEY1,则喂狗
            printf("Yes!\r\n");//喂狗
        }
    }
}

