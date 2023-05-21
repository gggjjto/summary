#include "key.h"
#include "delay.h"
void key_init(void)
{
    KEYx_init(RCC_KEY1,Pin_KEY1,GPIO_KEY1);
    KEYx_init(RCC_KEY2,Pin_KEY2,GPIO_KEY2);
    KEYx_init(RCC_KEY3,Pin_KEY3,GPIO_KEY3);

}


void KEYx_init(uint32_t RCC_APB2Periph,uint16_t GPIO_Pin,GPIO_TypeDef* GPIOx)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph,ENABLE);

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOx,&GPIO_InitStructure);
}

int ScanfKeyX(int mode)
{
    static uint8_t key_up = 1;  /* 按键按松开标志 */
    uint8_t keyval = 0;

    if (mode) key_up = 1;       /* 支持连按 */

    if (key_up && (KEY1 == 0 || KEY2 == 0 || KEY3 == 0)) 
    {
        delay_ms(10);           /* 去抖动 */
        key_up = 0;

        if (KEY1 == 0)  keyval = 1;

        if (KEY2 == 0)  keyval = 2;

        if (KEY3 == 0) keyval = 3;
    }
    else if (KEY1 == 1 && KEY2 == 1 && KEY3 == 1) /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
    }

    return keyval;              /* 返回键值 */
}

