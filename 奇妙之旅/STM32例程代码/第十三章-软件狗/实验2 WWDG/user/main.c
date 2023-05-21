#include "stm32f10x.h"
#include <string.h>
#include <stdlib.h>

#include "stdio.h"
#include "delay.h"
#include "led.h"
#include "wwdg.h"

int main(void)
{
    LED_Init();                                 //初始化LED
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2
    delay_ms(500);
    WWDG_Init();                               //初始化窗口看门狗 
    GPIO_SetBits(GPIOA, GPIO_Pin_6);           //LED1灯亮
    
    while(1)
    {
        //若LED1先灭500ms后一直亮，表示喂狗成功
        //若LED1闪烁表示喂狗失败
        delay_ms(30);//理想下延时在29.13ms~58.25ms之间（窗口期）
                     //但是执行设置计数值还需要时间，所以在30ms~56ms内能够喂狗成功
        WWDG_SetCounter(0x7F);//设置计数值
    }
    
}




