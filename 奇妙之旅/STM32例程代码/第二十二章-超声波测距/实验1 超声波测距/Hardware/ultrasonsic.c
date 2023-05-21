#include "ultrasonsic.h"
#include "delay.h"

u8 msHcCount = 0;//ms计数

void Hcsr04_Init()
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;     //生成用于定时器设置的结构体
    NVIC_InitTypeDef NVIC_InitStruct;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); /*开启GPIOB时钟*/
     
        //IO初始化
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2;   //发送电平引脚TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设置推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_2);//一开始低电平
     
    GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_3;     //返回电平引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
    GPIO_ResetBits(GPIOA,GPIO_Pin_3); //默认低电平   
     
     //定时器初始化 使用TIM2
    RCC_APB1PeriphClockCmd(TIMx_CLK, ENABLE);   //使能对应RCC时钟
    TIM_DeInit(TIMx);//配置定时器基础结构体
     //自动重装载值寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period = TIMx_Period;//设置周期为1000us
    //时钟预分频数
    TIM_TimeBaseStructure.TIM_Prescaler = TIMx_Prescaler;//分频数72
    //时钟分频因子
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    //计数器计数模式，设置向上计数，
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    //重复计数器的值
    //TIM_TimeBaseStructure.TIM_RepetitionCounter=0 ;
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure); 
    
    TIM_ClearFlag(TIMx, TIM_FLAG_Update);   //清除定时器的状态标志位
    TIM_Cmd(TIMx,ENABLE);
    TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE);    //打开定时器更新中断
   
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn; //设置中断来源
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //设置主优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;//设置次优先级
    NVIC_Init(&NVIC_InitStruct);                  //初始化
}

//定时器2中断服务程序
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIMx,TIM_IT_Update) != RESET){
        /*清除更新中断标志位*/
        TIM_ClearITPendingBit(TIMx,TIM_IT_Update);
        msHcCount++;
    }
}

//获取定时器时间
u32 GetEchoTimer(void)
{
    u32 time = 0;
    /*//当回响信号很长是，计数值溢出后重复计数，overCount用中断来保存溢出次数*/
    time = msHcCount*1000;//msHcCount毫秒，time微妙
    time += TIM_GetCounter(TIMx);//获取计TIM2数寄存器中的计数值，计算回响信号时间
    TIMx->CNT = 0;  //将TIM2计数寄存器的计数值清零
    delay_ms(50);
    return time;
}

float Hcsr04GetLength(void )
{
    /*测5次数据计算一次平均值*/
    float length = 0;
    float t = 0;
    float sum = 0;
    u16 j = 0;
    while(j != 5){
        GPIO_SetBits(GPIOA,GPIO_Pin_2);//trig拉高信号，发出高电平
        delay_us(20);//持续时间超过10us
        GPIO_ResetBits(GPIOA,GPIO_Pin_2);
        /*Echo发出信号 等待回响信号*/
       /* 输入方波后，模块会自动发射8个40KHz的声波，与此同时回波引脚（Echo）端的电平会由0变为1（此时应该启动定时器计时）；
          当超声波返回被模块接收到时，回波引脚端的电平会由1变为0（此时应该停止定时器计数），
          定时器记下的这个时间即为超声波由发射到返回的总时长；*/
        while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) == 0);//echo等待回响
        /*开启定时器*/
        TIM_SetCounter(TIMx,0); //清除计数器
        msHcCount = 0;
        TIM_Cmd(TIMx,ENABLE);//使能定时器
        j = j+1; //每收到一次回响信号+1，收到5次就计算均值
        while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) == 1);
        /*关闭定时器*/
       TIM_Cmd(TIMx,DISABLE);
        /*获取Echo高电平时间时间*/
        t = GetEchoTimer();
        length = (float)t/58;//单位为cm
        printf("dis = %fcm\r\n",length);
        sum += length;
    }
    length = sum/5;//五次平均值
    printf("dis_average = %fcm\r\n",length); //打印平均距离
    return length;
}
