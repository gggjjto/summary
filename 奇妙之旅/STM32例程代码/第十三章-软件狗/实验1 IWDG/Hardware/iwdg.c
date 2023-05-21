#include "iwdg.h"

/**********************************
* ����ȫ��:
* void IWDG_Init(uint8_t prer,uint16_t rlr) 
*
*�������ͣ�
* prer:��Ƶ��
* ��Ƶ����=4*2^prer.���ֵֻ����256!
* rlr:��װ�ؼĴ���ֵ
* ���ʱ�����:Tout=((4*2^prer)*rlr)/40 (ms).
*
* ��������:
* ��ʼ���������Ź�
* ************************************/
void IWDG_Init(uint8_t prer,uint16_t rlr) 
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //ȡ��д����
    IWDG_SetPrescaler(prer);  //����IWDGԤ��Ƶֵ
    IWDG_SetReload(rlr);  //����IWDG��װ��ֵ
    IWDG_ReloadCounter();  //����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������
    IWDG_Enable();  //ʹ��IWDG
}

