
#include "stm32f10x.h"
#include <string.h>
#include <stdlib.h>

#include "stdio.h"
#include "delay.h"
#include "led.h"
#include "pwm.h"

int main(void)
{
    u16 led0pwmval=500; //舵机初始状态
    u8 dir=1;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LED_Init();                                 /* 初始化LED */
    My_TIM3_Init(19999,71);//周期为20ms （arr+1)(psc+1)/Tclk =72MHz72000000hz=0.02s

    while(1)
    {
      if(dir)//旋转0->180度
        {
            led0pwmval+=100;
        }
      else //旋转 180度->0
      { 
          led0pwmval-=100;
      }
      //if(led0pwmval>2500)dir=0;
      //if(led0pwmval==500)dir=1;
      
      TIM_SetCompare1(TIM3,led0pwmval);
      
       LED1_Turn();  //作为程序在运行的标志
        delay_ms(200);
    }
}




