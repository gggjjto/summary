#include "key.h"
#include "delay.h"
/**
 * @brief       ������ʼ������
 * @param       ��
 * @retval      ��
 */
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);             /* ʹ��A�˿�ʱ�� */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;                         /* KEY1���� */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                     /* ������Ҫ��ȡ�������õ��������� */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 /* ���� */
    GPIO_Init(GPIOA, &GPIO_InitStructure);                            /* ��ʼ��KEY1���� */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;                         /* KEY3���� */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                     /* ������Ҫ��ȡ�������õ��������� */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 /* ���� */
    GPIO_Init(GPIOA, &GPIO_InitStructure);                            /* ��ʼ��KEY3���� */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;                         /* KEY2���� */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                     /* ������Ҫ��ȡ�������õ��������� */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 /* ���� */
    GPIO_Init(GPIOA, &GPIO_InitStructure);                            /* ��ʼ��KEY2���� */

}

//����ɨ�躯��
uint8_t KEY_Scan(void)
{
    static uint8_t key_up = 1;  /* �������ɿ���־ */
    uint8_t keyval = 0;

    if (key_up && (KEY1 == 0 || KEY3 == 0 || KEY2 == 0))  /* �����ɿ���־Ϊ1, ��������һ������������ */
    {
        delay_ms(10);             /* ȥ���� */
        key_up = 0;

        if (KEY1 == 0)  keyval = 1;         /* KEY1������ */

        if (KEY3 == 0)  keyval = 3;         /* KEY3������ */

        if (KEY2 == 0)  keyval = 2;         /* KEY2������ */
    } 
    else if (KEY1 == 1 && KEY3 == 1 && KEY2 == 1) /* û���κΰ�������, ��ǰ����ɿ� */
    {
        key_up = 1;
        GPIO_ResetBits(GPIOA, GPIO_Pin_6);   /* LED1�� */
        GPIO_ResetBits(GPIOA, GPIO_Pin_7);   /* LED2�� */
        GPIO_ResetBits(GPIOB, GPIO_Pin_0);   /* LED3�� */
        GPIO_ResetBits(GPIOB, GPIO_Pin_13);  /* BEEP���� */
    }
    
   return keyval;              /* ���ؼ�ֵ */
}


