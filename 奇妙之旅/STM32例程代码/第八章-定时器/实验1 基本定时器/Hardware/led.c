#include "led.h"

//��ʼ��LED���IO��, ��ʹ��ʱ��
void LED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);             /* ʹ��A�˿�ʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);             /* ʹ��B�˿�ʱ�� */
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;                         /* LED1���� */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                  /* ������� */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 /* ���� */
    GPIO_Init(GPIOA, &GPIO_InitStructure);                            /* ��ʼ��LED1���� */
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;                         /* LED2���� */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                  /* ������� */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 /* ���� */
    GPIO_Init(GPIOA, &GPIO_InitStructure);                            /* ��ʼ��LED2���� */
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                         /* LED3���� */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                  /* ������� */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 /* ���� */
    GPIO_Init(GPIOB, &GPIO_InitStructure);                            /* ��ʼ��LED3���� */
    
    GPIO_ResetBits(GPIOA, GPIO_Pin_6);                                /* LED1�� */
    GPIO_ResetBits(GPIOA, GPIO_Pin_7);                                /* LED2�� */
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);                                /* LED3�� */
}

//״̬ȡ��
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
