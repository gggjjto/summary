#include "wwdg.h"
#include "led.h"
#include "delay.h"

/**********************************
* ����ȫ��:
* void WWDG_Init(void)
*
* �������ͣ�
* ��ʱʱ�����:Tout=((4096*2^WDGTB)*��T[5:0]+1��)/Fwwdg
* ((4096*8)*��127 - 95))/36000 = 29.13ms �Ǵ����ڣ�ι��������λ��127��0x7F
* ((4096*8)*��127 - 63))/36000 = 58.25ms����ʼ��֮�󾭹�58.25ms���ﴰ��������ֵ��63��0x3F
* ���Կ��Եõ���20.13ms��58.25ms֮��ι����������λ
*
* ��������:
* ��ʼ�����ڿ��Ź�
* ************************************/
void WWDG_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);//ʹ��APB1ʱ��
    
    WWDG_SetPrescaler(WWDG_Prescaler_8);//Ԥ��Ƶϵ����Ϊ8
    WWDG_SetWindowValue(0x5F);//�ϴ���ֵΪ0x5F��95��0x5F
    WWDG_Enable(0x7F);//ʹ��WWDG
    
    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;//WWDG�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;   // ������Ӧ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   // ʹ���ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);  // ����NVIC��ʼ������
    WWDG_ClearFlag();//�����ǰ�����жϱ�־λ
    
    WWDG_EnableIT();//�����ж�
}

/**********************************
* ����ȫ��:
* void WWDG_IRQHandler(void)
*
* �������ͣ�
* ������ֵΪ0x40ʱ�ɲ����ж�
* 
* ��������:
* �жϷ�����
* ************************************/
void WWDG_IRQHandler(void)
{
    //delay_ms(1);//�������õ�WDGTB = 3,��С��ʱֵΪ910us��������ʱ1ms��ι����ʧ�ܣ�LED2�᲻��
//    WWDG_SetCounter(0x7F); //���ü���ֵ
//    WWDG_ClearFlag();//�����ǰ�����жϱ�־λ
//    LED2_Turn(); //LED2��ת��ι���ɹ����Կ���LED2��˸
}

