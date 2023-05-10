#ifndef _LED_H
#define _LED_H
// #include "sys.h"
#include "stdlib.h"
#include "stm32f10x.h"

#define RCC_LED1 RCC_APB2Periph_GPIOA
#define Pin_LED1 GPIO_Pin_6
#define GPIO_LED1 GPIOA

#define RCC_LED2 RCC_APB2Periph_GPIOA
#define Pin_LED2 GPIO_Pin_7
#define GPIO_LED2 GPIOA

#define RCC_LED3 RCC_APB2Periph_GPIOB
#define Pin_LED3 GPIO_Pin_0
#define GPIO_LED3 GPIOB

#define set_LED1() GPIO_SetBits(GPIOA,GPIO_Pin_6)
#define reset_LED1() GPIO_ResetBits(GPIOA, GPIO_Pin_6)

#define set_LED2() GPIO_SetBits(GPIOA,GPIO_Pin_7)
#define reset_LED2() GPIO_ResetBits(GPIOA, GPIO_Pin_7)

#define set_LED3() GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define reset_LED3() GPIO_ResetBits(GPIOB, GPIO_Pin_0)

/* 初始化 */
void LED_Init(void);                                                                            /* 初始化 */
void LEDx_Init(uint32_t RCC_APB2Periph,uint16_t GPIO_Pin,GPIO_TypeDef* GPIOx);
void X_led(int x);
#endif

