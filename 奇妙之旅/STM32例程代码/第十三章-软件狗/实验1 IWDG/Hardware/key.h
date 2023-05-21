#ifndef __KEY_H
#define __KEY_H

#include "stdlib.h"
#include "stm32f10x.h"

#define KEY1        GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)     /* 读取KEY1引脚 */
#define KEY3        GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)     /* 读取KEY3引脚 */
#define KEY2        GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)     /* 读取KEY2引脚 */

void KEY_Init(void);                /* 按键初始化函数 */
uint8_t KEY_Scan(void);             /* 按键扫描函数 */



#endif 

