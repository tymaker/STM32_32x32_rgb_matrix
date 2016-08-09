/**
  ******************************************************************************
  * @file    stm32f10x_rgb_systick.c
  * @author  fire
  * @version V2.0
  * @date    2013-xx-xx
  * @brief   STM32 RGB点阵延时头文件
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "stm32f10x_rgb_systick.h"

static __IO u32 TimingDelay;
__IO u32 Timing;

/*
 * 函数名：SysTick_Init
 * 描述  ：启动系统滴答定时器 SysTick
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用 
 */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if (SysTick_Config(72000000 / 1000))
  { 
    /* Capture error */ 
    while (1);
  }
}


/*
 * 函数名：Delay_us
 * 描述  ：us延时程序,1ms为一个单位
 * 输入  ：- nTime
 * 输出  ：无
 * 调用  ：Delay_us( 1 ) 则实现的延时为 1ms
 *       ：外部调用 
 */

void Delay_us(__IO u32 nTime)
{ 
  //TimingDelay = nTime;

  //while(TimingDelay != 0);
	
   u16 i=0;  
   while(nTime--)
   {
      i=13350;
      while(i--) ;    
   }
}

void delay(__IO u32 nTime)
{
	TIM4_Configuration(ENABLE);
  TimingDelay = nTime;

  while(TimingDelay != 0);
	TIM4_Configuration(DISABLE);

}

/*
 * 函数名：TimingDelay_Decrement
 * 描述  ：获取节拍程序
 * 输入  ：无
 * 输出  ：无
 * 调用  ：在 SysTick 中断函数 SysTick_Handler()调用
 */  
void TimingDelay_Decrement(void)
{
	/*Timing++;  //总计数值
	if(Timing==0xffffffff)
	{
		Timing=0;
	}*/
  Get_Flag(); //判断flag
  /*if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }*/
}

void delay_interupt(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}
/******************* (C) COPYRIGHT 2016 *****END OF FILE****/
