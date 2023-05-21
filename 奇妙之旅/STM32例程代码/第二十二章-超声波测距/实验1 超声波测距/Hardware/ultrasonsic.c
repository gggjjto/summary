#include "ultrasonsic.h"
#include "delay.h"

u8 msHcCount = 0;//ms����

void Hcsr04_Init()
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;     //�������ڶ�ʱ�����õĽṹ��
    NVIC_InitTypeDef NVIC_InitStruct;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); /*����GPIOBʱ��*/
     
        //IO��ʼ��
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2;   //���͵�ƽ����TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_2);//һ��ʼ�͵�ƽ
     
    GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_3;     //���ص�ƽ����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
    GPIO_ResetBits(GPIOA,GPIO_Pin_3); //Ĭ�ϵ͵�ƽ   
     
     //��ʱ����ʼ�� ʹ��TIM2
    RCC_APB1PeriphClockCmd(TIMx_CLK, ENABLE);   //ʹ�ܶ�ӦRCCʱ��
    TIM_DeInit(TIMx);//���ö�ʱ�������ṹ��
     //�Զ���װ��ֵ�Ĵ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period = TIMx_Period;//��������Ϊ1000us
    //ʱ��Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_Prescaler = TIMx_Prescaler;//��Ƶ��72
    //ʱ�ӷ�Ƶ����
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    //����������ģʽ���������ϼ�����
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    //�ظ���������ֵ
    //TIM_TimeBaseStructure.TIM_RepetitionCounter=0 ;
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure); 
    
    TIM_ClearFlag(TIMx, TIM_FLAG_Update);   //�����ʱ����״̬��־λ
    TIM_Cmd(TIMx,ENABLE);
    TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE);    //�򿪶�ʱ�������ж�
   
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn; //�����ж���Դ
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //���������ȼ�
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;//���ô����ȼ�
    NVIC_Init(&NVIC_InitStruct);                  //��ʼ��
}

//��ʱ��2�жϷ������
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIMx,TIM_IT_Update) != RESET){
        /*��������жϱ�־λ*/
        TIM_ClearITPendingBit(TIMx,TIM_IT_Update);
        msHcCount++;
    }
}

//��ȡ��ʱ��ʱ��
u32 GetEchoTimer(void)
{
    u32 time = 0;
    /*//�������źźܳ��ǣ�����ֵ������ظ�������overCount���ж��������������*/
    time = msHcCount*1000;//msHcCount���룬time΢��
    time += TIM_GetCounter(TIMx);//��ȡ��TIM2���Ĵ����еļ���ֵ����������ź�ʱ��
    TIMx->CNT = 0;  //��TIM2�����Ĵ����ļ���ֵ����
    delay_ms(50);
    return time;
}

float Hcsr04GetLength(void )
{
    /*��5�����ݼ���һ��ƽ��ֵ*/
    float length = 0;
    float t = 0;
    float sum = 0;
    u16 j = 0;
    while(j != 5){
        GPIO_SetBits(GPIOA,GPIO_Pin_2);//trig�����źţ������ߵ�ƽ
        delay_us(20);//����ʱ�䳬��10us
        GPIO_ResetBits(GPIOA,GPIO_Pin_2);
        /*Echo�����ź� �ȴ������ź�*/
       /* ���뷽����ģ����Զ�����8��40KHz�����������ͬʱ�ز����ţ�Echo���˵ĵ�ƽ����0��Ϊ1����ʱӦ��������ʱ����ʱ����
          �����������ر�ģ����յ�ʱ���ز����Ŷ˵ĵ�ƽ����1��Ϊ0����ʱӦ��ֹͣ��ʱ����������
          ��ʱ�����µ����ʱ�伴Ϊ�������ɷ��䵽���ص���ʱ����*/
        while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) == 0);//echo�ȴ�����
        /*������ʱ��*/
        TIM_SetCounter(TIMx,0); //���������
        msHcCount = 0;
        TIM_Cmd(TIMx,ENABLE);//ʹ�ܶ�ʱ��
        j = j+1; //ÿ�յ�һ�λ����ź�+1���յ�5�ξͼ����ֵ
        while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) == 1);
        /*�رն�ʱ��*/
       TIM_Cmd(TIMx,DISABLE);
        /*��ȡEcho�ߵ�ƽʱ��ʱ��*/
        t = GetEchoTimer();
        length = (float)t/58;//��λΪcm
        printf("dis = %fcm\r\n",length);
        sum += length;
    }
    length = sum/5;//���ƽ��ֵ
    printf("dis_average = %fcm\r\n",length); //��ӡƽ������
    return length;
}
