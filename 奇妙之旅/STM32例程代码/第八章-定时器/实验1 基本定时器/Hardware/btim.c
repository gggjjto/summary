#include "led.h"
#include "btim.h"

/**********************************
* 函数全称:
* void Basic_TIM4_Init(uint16_t arr, uint16_t pre)
*
* 函数作用:
* 初始化 TIM4
* ************************************/
void Basic_TIM4_Init(uint16_t arr, uint16_t pre)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //定时器时钟CK_INT=2*PCLK1=2*32MHz=72MHz
    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler = pre; //CK_CNT=CKINT/(pre+1)
    // 时钟分频因子 ，基本定时器没有，不用管
    //TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    // 计数器计数模式，基本定时器只能向上计数
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    // 重复计数器的值，基本定时器没有，不用管
    //TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //初始化定时器

    TIM_ClearFlag(TIM4,TIM_FLAG_Update);       //清除定时器的状态标志位
    TIM_Cmd(TIM4, ENABLE);                     //打开定时器
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);   //开启更新中断（上溢中断）
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  // 设置中断组为 0
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  // 选择中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 设置抢占优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;   // 设置响应优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   // 使能中断通道
    NVIC_Init(&NVIC_InitStructure);  //调用NVIC初始化函数
}

/**********************************
* 函数全称:
* void TIM4_IRQHandler(void)
*
* 函数作用:
* 每次产生一个中断溢出时间就会进入一次中断函数
* ************************************/
void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET) //检测是否溢出中断
    {
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //清除中断标志位，否则启动时会进入中断服务函数

        LED2_Turn();
    }
}

