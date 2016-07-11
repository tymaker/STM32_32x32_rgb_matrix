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
#ifndef __VOLUMEBARS_H
#define	__VOLUMEBARS_H

#include "math.h"
#include "stm32f10x.h"
#include "stm32f10x_rgb_matrix.h"
#include "stm32f10x_rgb_gfx.h"
#include "stm32f10x_rgb_adc.h"



void InitBufInArray(void);
void GetPowerMag(void);
void Printf(void);
void VolumeBars_run(void);
void drawBarRow(int bar, uint8_t y, uint8_t r, uint8_t g, uint8_t b);

#endif

/*********************************************END OF FILE**********************/
