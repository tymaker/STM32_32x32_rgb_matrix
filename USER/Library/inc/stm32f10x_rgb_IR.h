/**
  ******************************************************************************
  * @file    main.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define	__MAIN_H

#define GPIO_IR GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)

#include "stm32f10x.h"
#include "stm32f10x_rgb_systick.h"

u8 hongwai(void);

#endif /* __STM32F10X_RGB_IR_H */

/******************* (C) COPYRIGHT 2016 Makt *****END OF FILE****/
