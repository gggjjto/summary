#ifndef _ULTRASONSIC_H
#define _ULTRASONSIC_H
// #include "sys.h"
#include "stdlib.h"
#include "stm32f10x.h"


/*TIM2*/
#define TIMx           TIM2
#define TIMx_CLK       RCC_APB1Periph_TIM2
#define TIMx_IRQn       TIM2_IRQn
#define TIMx_Period    (1000-1)
#define TIMx_Prescaler (72-1)

void Hcsr04_Init(void);  /* 定时中断初始化函数 */
float Hcsr04GetLength(void);

#endif
