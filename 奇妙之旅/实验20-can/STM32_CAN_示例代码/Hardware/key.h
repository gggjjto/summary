#ifndef __KEY_H
#define __KEY_H

#include "stdlib.h"
#include "stm32f10x.h"

#define RCC_KEY1 RCC_APB2Periph_GPIOA
#define Pin_KEY1 GPIO_Pin_3
#define GPIO_KEY1 GPIOA
#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)

#define RCC_KEY2 RCC_APB2Periph_GPIOA
#define Pin_KEY2 GPIO_Pin_4
#define GPIO_KEY2 GPIOA
#define KEY2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)

#define RCC_KEY3 RCC_APB2Periph_GPIOA
#define Pin_KEY3 GPIO_Pin_5
#define GPIO_KEY3 GPIOA
#define KEY3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)

void key_init(void);
int ScanfKeyX(int mode);
void KEYx_init(uint32_t RCC_APB2Periph,uint16_t GPIO_Pin,GPIO_TypeDef* GPIOx);

#endif
