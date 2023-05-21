#include "led.h"

//初始化LED相关IO口, 并使能时钟
void LED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);             /* 使能A端口时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);             /* 使能B端口时钟 */
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;                         /* LED1引脚 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                  /* 推挽输出 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 /* 高速 */
    GPIO_Init(GPIOA, &GPIO_InitStructure);                            /* 初始化LED1引脚 */
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;                         /* LED2引脚 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                  /* 推挽输出 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 /* 高速 */
    GPIO_Init(GPIOA, &GPIO_InitStructure);                            /* 初始化LED2引脚 */
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                         /* LED3引脚 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                  /* 推挽输出 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 /* 高速 */
    GPIO_Init(GPIOB, &GPIO_InitStructure);                            /* 初始化LED3引脚 */
    
    GPIO_ResetBits(GPIOA, GPIO_Pin_6);                                /* LED1灭 */
    GPIO_ResetBits(GPIOA, GPIO_Pin_7);                                /* LED2灭 */
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);                                /* LED3灭 */
}

//状态取反
void LED1_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_6) == 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_6);
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_6);
    }
}

void LED2_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_7) == 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_7);
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_7);
    }
}

void LED3_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_0) == 0)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_0);
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_0);
    }
}
