/**
  ******************************************************************************
  * @file    stm32f10x_rgb_init.h
  * @author  Makt
  * @version V3.5.0
  * @date    2016-04-04
  * @brief   STM32F10x_RGB_INIT 初始化函数头文件
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RGBINIT_H
#define	__RGBINIT_H

#include "stm32f10x.h"
#include "matrix_config.h"

#define TIME_NUM  REFISH_70HZ   //定时器时间 2.5ms   5 400Hz   10 200Hz

// Open and Closed Sign Messages
#define OPEN_MSG   "Please Come In"
#define CLOSED_MSG "Hours: M-F 9-5 Sat 10-3 Closed Sun"

void setupRGBMatrixPorts(void);
void NVIC_Configuration(void);
void TIM2_Configuration(u8,u16,u16);
void TIM3_Configuration(u8);
void TIM4_Configuration(u8);
void EXTI_Config(void);

#endif /* __STM32F10x_RGB_INIT_H */

/******************* (C) COPYRIGHT 2011 Makt *****END OF FILE****/
