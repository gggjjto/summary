#include "stm32f10x.h"                  // Device header
#include "OLED.h"

int main(void)
{
	OLED_Init();   //��ʼ��OLED
	
//	��ʾ�ַ�
	OLED_ShowChar(1,1,'A');
//	��ʾ�ַ���
	OLED_ShowString(1,3,"HellowWorld!");
	
//	��ʾʮ��������
	OLED_ShowNum(2,1,66,2);
	
//	��ʾʮ�����з�����
	OLED_ShowSignedNum(2,3,-77,2);
	
//	��ʾʮ��������
	OLED_ShowHexNum(3,1,0XF0,4);
	
//	��ʾ����
	OLED_ShowChinese(4,1,0);
	OLED_ShowChinese(4,2,1);
	OLED_ShowChinese(4,3,2);
	OLED_ShowChinese(4,4,3);
	
	while(1)
	{
		
	}
}
