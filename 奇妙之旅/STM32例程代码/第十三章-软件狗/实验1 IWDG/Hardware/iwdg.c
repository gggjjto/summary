#include "iwdg.h"

/**********************************
* 函数全称:
* void IWDG_Init(uint8_t prer,uint16_t rlr) 
*
*辅助解释：
* prer:分频数
* 分频因子=4*2^prer.最大值只能是256!
* rlr:重装载寄存器值
* 溢出时间计算:Tout=((4*2^prer)*rlr)/40 (ms).
*
* 函数作用:
* 初始化独立看门狗
* ************************************/
void IWDG_Init(uint8_t prer,uint16_t rlr) 
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //取消写保护
    IWDG_SetPrescaler(prer);  //设置IWDG预分频值
    IWDG_SetReload(rlr);  //设置IWDG重装载值
    IWDG_ReloadCounter();  //按照IWDG重装载寄存器的值重装载IWDG计数器
    IWDG_Enable();  //使能IWDG
}

