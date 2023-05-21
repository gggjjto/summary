#include "atim.h"
#include "oled.h"

 extern int i;
void TIM3_init(uint16_t arr, uint16_t pre)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;     //�������ڶ�ʱ�����õĽṹ��
    NVIC_InitTypeDef NVIC_InitStruct;

     //��ʱ����ʼ�� ʹ��TIM3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   //ʹ�ܶ�ӦRCCʱ��
    TIM_DeInit(TIM3);//���ö�ʱ�������ṹ��
     //�Զ���װ��ֵ�Ĵ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period = arr;//��������Ϊ1s
    //ʱ��Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_Prescaler = pre;
    //ʱ�ӷ�Ƶ����
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    //����������ģʽ���������ϼ�����
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    //�ظ���������ֵ
    //TIM_TimeBaseStructure.TIM_RepetitionCounter=0 ;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
    
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);   //�����ʱ����״̬��־λ
    TIM_Cmd(TIM3,ENABLE); 
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);    //�򿪶�ʱ�������ж�
   
    NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn; //�����ж���Դ
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //���������ȼ�
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;//���ô����ȼ�
    NVIC_Init(&NVIC_InitStruct);                  //��ʼ��
}

//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET){
        /*��������жϱ�־λ*/
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
        printf("cnt=%d\n",i);
        OLED_ShowNum(1,3,i,1,16);
        i=0;
    }
}
