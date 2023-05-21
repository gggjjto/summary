#include "stm32f10x.h"                  // Device header
#include "OLED.h"

int main(void)
{
	OLED_Init();   //初始化OLED
	
//	显示字符
	OLED_ShowChar(1,1,'A');
//	显示字符串
	OLED_ShowString(1,3,"HellowWorld!");
	
//	显示十进制正数
	OLED_ShowNum(2,1,66,2);
	
//	显示十进制有符号数
	OLED_ShowSignedNum(2,3,-77,2);
	
//	显示十六进制数
	OLED_ShowHexNum(3,1,0XF0,4);
	
//	显示汉字
	OLED_ShowChinese(4,1,0);
	OLED_ShowChinese(4,2,1);
	OLED_ShowChinese(4,3,2);
	OLED_ShowChinese(4,4,3);
	
	while(1)
	{
		
	}
}
