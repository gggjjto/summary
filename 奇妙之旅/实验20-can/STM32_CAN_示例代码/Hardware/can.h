
#ifndef __CAN_H
#define __CAN_H
/******************************************************************************/

#include "stm32f10x.h"
#include "usart.h"
#include "led.h"
#include <stdio.h>

void can_init(uint8_t tsjw,uint8_t tbs2,uint8_t tbs1,uint16_t brp,uint8_t mode);
void CAN_ITConfig_Init(void);
void CAN_FilterInitStructure_Init(void);
uint16_t CAN1_Send_Msg(uint8_t* msg,uint8_t len);

#define CAN1_RX0_INT_ENABLE 1   //can1中断 1启动，0不启动

#define CAN_RX_GPIO_PIN GPIO_Pin_8
#define CAN_RX_GPIO     GPIOB
#define CAN_TX_GPIO_PIN GPIO_Pin_9
#define CAN_TX_GPIO     GPIOB
/******************************************************************************/

#endif

