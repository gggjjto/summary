#include "key.h"
#include "delay.h"
/**
 * @brief       按键初始化函数
 * @param       无
 * @retval      无
 */
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);             /* 使能A端口时钟 */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;                         /* KEY1引脚 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                     /* 这里需要读取按键，用的上拉输入 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 /* 高速 */
    GPIO_Init(GPIOA, &GPIO_InitStructure);                            /* 初始化KEY1引脚 */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;                         /* KEY3引脚 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                     /* 这里需要读取按键，用的上拉输入 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 /* 高速 */
    GPIO_Init(GPIOA, &GPIO_InitStructure);                            /* 初始化KEY3引脚 */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;                         /* KEY2引脚 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                     /* 这里需要读取按键，用的上拉输入 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 /* 高速 */
    GPIO_Init(GPIOA, &GPIO_InitStructure);                            /* 初始化KEY2引脚 */

}

//按键扫描函数
uint8_t KEY_Scan(void)
{
    static uint8_t key_up = 1;  /* 按键按松开标志 */
    uint8_t keyval = 0;

    if (key_up && (KEY1 == 0 || KEY3 == 0 || KEY2 == 0))  /* 按键松开标志为1, 且有任意一个按键按下了 */
    {
        delay_ms(10);             /* 去抖动 */
        key_up = 0;

        if (KEY1 == 0)  keyval = 1;         /* KEY1被按下 */

        if (KEY3 == 0)  keyval = 3;         /* KEY3被按下 */

        if (KEY2 == 0)  keyval = 2;         /* KEY2被按下 */
    } 
    else if (KEY1 == 1 && KEY3 == 1 && KEY2 == 1) /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
        GPIO_ResetBits(GPIOA, GPIO_Pin_6);   /* LED1灭 */
        GPIO_ResetBits(GPIOA, GPIO_Pin_7);   /* LED2灭 */
        GPIO_ResetBits(GPIOB, GPIO_Pin_0);   /* LED3灭 */
        GPIO_ResetBits(GPIOB, GPIO_Pin_13);  /* BEEP不响 */
    }
    
   return keyval;              /* 返回键值 */
}


