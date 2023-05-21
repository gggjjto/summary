#include "stm32f10x.h"                             // Device header
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "stm32f10x.h"
#include "can.h"
#include "key.h"

int main()
{
    int x=0;
	LED_Init();
	key_init();
        can_init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_Normal);
     
    while(1)
	{
                x=ScanfKeyX(0);
                X_led(x);
	}
}

