#include "led.h"
#include "btim.h"

/**********************************
* ����ȫ��:
* void Basic_TIM4_Init(uint16_t arr, uint16_t pre)
*
* ��������:
* ��ʼ�� TIM4
* ************************************/
void Basic_TIM4_Init(uint16_t arr, uint16_t pre)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //��ʱ��ʱ��CK_INT=2*PCLK1=2*32MHz=72MHz
    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler = pre; //CK_CNT=CKINT/(pre+1)
    // ʱ�ӷ�Ƶ���� ��������ʱ��û�У����ù�
    //TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    // ����������ģʽ��������ʱ��ֻ�����ϼ���
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    // �ظ���������ֵ��������ʱ��û�У����ù�
    //TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //��ʼ����ʱ��

    TIM_ClearFlag(TIM4,TIM_FLAG_Update);       //�����ʱ����״̬��־λ
    TIM_Cmd(TIM4, ENABLE);                     //�򿪶�ʱ��
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);   //���������жϣ������жϣ�
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  // �����ж���Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  // ѡ���ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // ������ռ���ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;   // ������Ӧ���ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   // ʹ���ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC��ʼ������
}

/**********************************
* ����ȫ��:
* void TIM4_IRQHandler(void)
*
* ��������:
* ÿ�β���һ���ж����ʱ��ͻ����һ���жϺ���
* ************************************/
void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET) //����Ƿ�����ж�
    {
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //����жϱ�־λ����������ʱ������жϷ�����

        LED2_Turn();
    }
}

