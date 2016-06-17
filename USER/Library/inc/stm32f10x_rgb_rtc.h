/**
  ******************************************************************************
  * @file    stm32f10x_rgb_rtc.c
  * @author  Makt
  * @version V1.0
  * @date    2016-04-04
  * @brief   RTC 功能头文件
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __RTC_H
#define	__RTC_H


#include "stm32f10x.h"

/* 如果定义了下面这个宏的话,PC13就会输出频率为RTC Clock/64的时钟 */   
//#define RTCClockOutput_Enable  /* RTC Clock/64 is output on tamper pin(PC.13) */

void RTC_Config(void);
u8 Is_Leap_Year(u16 year);
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);
u8 RTC_Get(void);
u8 RTC_Get_Week(u16 year,u8 month,u8 day);

#endif /* __XXX_H */
