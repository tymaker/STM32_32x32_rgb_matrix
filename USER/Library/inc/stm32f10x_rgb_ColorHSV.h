/**
  ******************************************************************************
  * @file    stm32f10x_rgb_init.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    04-April-2016
  * @brief   STM32F10x_RGB_Appliction.h …œ≤„”¶”√
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Color_HSV_H
#define	__Color_HSV_H

#include "stm32f10x_rgb_matrix.h"
#include "math.h"

#define NUM_OF_COLOR_VALUES 256
#define MIN_COLOR_VALUE     0
#define MAX_COLOR_VALUE     255
#define PALETTE_SIZE        256
#define NUM_OF_PALETTES      12
#define GRAYSCALE_PALETTE     0
#define SPECTRUM_PALETTE      1
#define SIN1_PALETTE          2
#define SIN2_PALETTE          3
#define SIN3_PALETTE          4
#define SIN4_PALETTE          5
#define SIN5_PALETTE          6
#define RANDOM_PALETTE        7
#define FIRE_PALETTE          8
#define SEA_PALETTE           9
#define BLUERED_PALETTE       10
#define COLORWHEEL_PALETTE    11


void hsvToRGB(float hue, float saturation, float value, float * red, float * green, float * blue);
rgb24 CreateHSVColor(float hue, float saturation,  float value);
rgb24 CreateHSV_Color(int divisions, int index, float saturation, float value);
rgb24 CreateAHSVColor(int divisions, int index, float saturation, float value);
rgb24 CreateHSVColorWithDivisions(int divisions, int index);
#endif /* __STM32F10x_RGB_Color_HSV.h__ */
/******************* (C) COPYRIGHT 2011 Makt *****END OF FILE****/
