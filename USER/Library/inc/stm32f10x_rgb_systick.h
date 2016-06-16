/**
  ******************************************************************************
  * @file    stm32f10x_rgb_systick.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    04-April-2016
  * @brief   main 函数头文件
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"
#include "matrix_config.h"
#include "stm32f10x_rgb_uart.h"

void SysTick_Init(void);
void Delay_us(__IO u32 nTime);
void delay(__IO u32 nTime);
void TimingDelay_Decrement(void);
void delay_interupt(void);

#endif /* __SYSTICK_H */
