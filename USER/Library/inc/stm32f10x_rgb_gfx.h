/**
  ******************************************************************************
  * @file    stm32f10x_rgb_init.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    04-April-2016
  * @brief   STM32F10x_RGB_GFX 绘画功能头文件
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GFX_H
#define	__GFX_H

#include "stm32f10x.h"
#include "matrix_config.h"
#include "stm32f10x_rgb_matrix.h"
#include "stm32f10x_rgb_Colors.h"

//#include <math.h> 

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef _swap_int8_t
#define _swap_int8_t(a, b) { int8_t t = a; a = b; b = t; }
#endif



s8 _abs(s8);

void drawLine(s8,s8,s8,s8,u32);

void drawFastVLine(s8, s8, s8, u32);

void drawFastHLine(s8, s8, s8, u32);

void drawRect(s8, s8, s8, s8, u32);

void fillRect(s8 x, s8 y ,s8 w, s8 h, u32 Color);

void fillScreen(u32 Color);

void drawCircle(s8 x0, s8 y0, s8 r, u32 Color);

void drawCircleHelper(s8 x0, s8 y0, s8 r, s8 cornername,	u32 Color);

void fillCircleHelper(s8 x0, s8 y0, s8 r, s8 cornername,	s8 delta, u32 Color);

void fillCircle(s8 x0, s8 y0, s8 r, u32 color);

void drawTriangle(s8 x0, s8 y0, s8 x1, s8 y1,	s8 x2, s8 y2, u32 Color);

void fillTriangle(s8 x0, s8 y0, s8 x1, s8 y1, s8 x2, s8 y2, u32 Color);

void drawRoundRect(s8 x0, s8 y0, s8 w, s8 h,	s8 radius, u32 Color);

void fillRoundRect(s8 x0, s8 y0, s8 w, s8 h,	s8 radius, u32 Color);

void fillScreen(u32 Color);

/*
void drawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap,	int16_t w, int16_t h, uint16_t color);
*/



#endif /* __STM32F10x_RGB_GFX_H */

/******************* (C) COPYRIGHT 2011 Makt *****END OF FILE****/
