
#include "stm32f10x.h"
#include <string.h>
#include <stdlib.h>

#include "stdio.h"
#include "delay.h"
#include "led.h"
#include "btim.h"

int main(void)
{
    LED_Init();                                 /* 初始化LED */
    Basic_TIM4_Init(10000 -1, 7200 -1);/* 10KHZ的计数频率，计数10K次为1s */
    
    while(1)
    {
        LED1_Turn();  //作为程序在运行的标志
        delay_ms(200);
    }
}




