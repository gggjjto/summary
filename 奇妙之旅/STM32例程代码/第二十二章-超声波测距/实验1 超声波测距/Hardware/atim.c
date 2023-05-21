#include "atim.h"
#include "oled.h"

 extern int i;
void TIM3_init(uint16_t arr, uint16_t pre)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;     //生成用于定时器设置的结构体
    NVIC_InitTypeDef NVIC_InitStruct;

     //定时器初始化 使用TIM3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   //使能对应RCC时钟
    TIM_DeInit(TIM3);//配置定时器基础结构体
     //自动重装载值寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period = arr;//设置周期为1s
    //时钟预分频数
    TIM_TimeBaseStructure.TIM_Prescaler = pre;
    //时钟分频因子
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    //计数器计数模式，设置向上计数，
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    //重复计数器的值
    //TIM_TimeBaseStructure.TIM_RepetitionCounter=0 ;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
    
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);   //清除定时器的状态标志位
    TIM_Cmd(TIM3,ENABLE); 
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);    //打开定时器更新中断
   
    NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn; //设置中断来源
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //设置主优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;//设置次优先级
    NVIC_Init(&NVIC_InitStruct);                  //初始化
}

//定时器3中断服务程序
void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET){
        /*清除更新中断标志位*/
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
        printf("cnt=%d\n",i);
        OLED_ShowNum(1,3,i,1,16);
        i=0;
    }
}
