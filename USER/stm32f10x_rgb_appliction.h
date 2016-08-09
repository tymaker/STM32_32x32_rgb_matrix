/**
  ******************************************************************************
  * @file    stm32f10x_rgb_application.h
  * @author  Makt
  * @version V3.5.0
  * @date    04-April-2016
  * @brief   STM32F10x_RGB_Appliction.h 上层应用
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APPLICTION_H
#define	__APPLICTION_H

#include <string.h>

#include "stm32f10x_rgb_matrix.h"
#include "stm32f10x_rgb_gfx.h"
#include "stm32f10x_rgb_dht11.h"
#include "stm32f10x_rgb_adc.h"
#include "stm32f10x_rgb_ColorHSV.h"
#include <math.h>
#include "stm32f10x_rgb_adc.h"
#include "stm32f10x_rgb_uart.h"
#include "stm32f10x_rgb_image.h"

// Analog Clock Attributes
#define NUMERICS_COLOR   Color888(120, 120, 120)

#define HOUR_HAND_RADIUS 6
#define HOUR_HAND_COLOR  Color888(0, 0, 255)

#define MIN_HAND_RADIUS  10
#define MIN_HAND_COLOR   Color888(0, 255, 0)

#define SEC_IND_RADIUS   15
#define SEC_IND_COLOR    Color888(255, 165, 0)

#define TIC_RADIUS       13
#define TIC_COLOR        Color888(255, 0, 0)

#define PI               3.1415

extern u8 hour,min,sec,w_month,w_date,week;//小时，分钟，秒，全局变量
extern u8 Display_PWM[MATRIX_MODULE*MATRIX_HEIGHT*2][3];

extern u8 Control;
extern u8 IMAGE[32*32][3];
extern u8 gImage_a[32*32][3];

uint8_t scale_col(int val, int lo, int hi);
void Rotate(int x, int y, float angle,
						float *new_x, float *new_y);
void Run(void);

u8 checkForTermination(void);

void drawClockTics(void);
void drawClockNumerics(void);
void _drawHourHand(int hour, int min, rgb24 color);
void _drawMinHand(int min, rgb24 color);
void _drawSecIndicator(int sec, rgb24 color);
void drawSecIndicator(int sec);
void analogClockMode(void);

void radiatingLinesPattern(void);
void rotatingLinesPattern(void);
void randomTrianglesPattern(void);
void Matrix_Text(void);
void timeAndTempMode(void);
void TempMode(void);
void ShowTime(void);
void drawClockNumerics(void);
void Batter(u8 num);
void fsin(void);
u8 Lcd_TimeX(unsigned char circle_x,unsigned char Length,unsigned char Angle);
u8 Lcd_TimeY(unsigned char circle_y,unsigned char Length,unsigned char Angle);
void init_Point_Clock(void);
void Display_Pointer(void);
void openSignMode(void);
void Display_Demo(void);
void show_Image(const u8 *image);
void show_PWM(void);
rgb24 createHSVColor(float hue, float saturation,  float value);
void welcomePattern(void);
void randomCirclesPattern(void);
void wwssaabb(void);
void bba(void);
void aabbcc(void);
void Show(void);

#endif /* __STM32F10x_RGB_APPLICTION_H */

/******************* (C) COPYRIGHT 2011 Makt *****END OF FILE**********s**/
