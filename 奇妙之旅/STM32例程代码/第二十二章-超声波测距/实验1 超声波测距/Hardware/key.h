#ifndef __KEY_H
#define __KEY_H

#include "stdlib.h"
#include "stm32f10x.h"

#define KEY1        GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)     /* ��ȡKEY1���� */
#define KEY3        GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)     /* ��ȡKEY3���� */
#define KEY2        GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)     /* ��ȡKEY2���� */

void KEY_Init(void);                /* ������ʼ������ */
uint8_t KEY_Scan(void);             /* ����ɨ�躯�� */



#endif 

