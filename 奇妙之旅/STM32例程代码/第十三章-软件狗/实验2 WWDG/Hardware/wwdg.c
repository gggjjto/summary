#include "wwdg.h"
#include "led.h"
#include "delay.h"

/**********************************
* 函数全称:
* void WWDG_Init(void)
*
* 辅助解释：
* 超时时间计算:Tout=((4096*2^WDGTB)*（T[5:0]+1）)/Fwwdg
* ((4096*8)*（127 - 95))/36000 = 29.13ms 非窗口期，喂狗产生复位，127是0x7F
* ((4096*8)*（127 - 63))/36000 = 58.25ms，初始化之后经过58.25ms到达窗口期下限值，63是0x3F
* 所以可以得到在20.13ms到58.25ms之间喂狗不产生复位
*
* 函数作用:
* 初始化窗口看门狗
* ************************************/
void WWDG_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);//使能APB1时钟
    
    WWDG_SetPrescaler(WWDG_Prescaler_8);//预分频系数设为8
    WWDG_SetWindowValue(0x5F);//上窗口值为0x5F，95是0x5F
    WWDG_Enable(0x7F);//使能WWDG
    
    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;//WWDG中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;   // 设置响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   // 使能中断通道
    NVIC_Init(&NVIC_InitStructure);  // 调用NVIC初始化函数
    WWDG_ClearFlag();//清除提前唤醒中断标志位
    
    WWDG_EnableIT();//开启中断
}

/**********************************
* 函数全称:
* void WWDG_IRQHandler(void)
*
* 辅助解释：
* 当计数值为0x40时可产生中断
* 
* 函数作用:
* 中断服务函数
* ************************************/
void WWDG_IRQHandler(void)
{
    //delay_ms(1);//由于设置的WDGTB = 3,最小超时值为910us，所以延时1ms后，喂狗会失败，LED2会不亮
//    WWDG_SetCounter(0x7F); //设置计数值
//    WWDG_ClearFlag();//清除提前唤醒中断标志位
//    LED2_Turn(); //LED2翻转，喂狗成功可以看见LED2闪烁
}

