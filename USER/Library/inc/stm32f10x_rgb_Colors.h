/**
  ******************************************************************************
  * @file    color.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    18-April-2016
  * @brief   main 函数头文件
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COLOR_H
#define	__COLOR_H

#ifndef Color888
#define Color888(r, g, b)  (((u32)r << 16) | ((u32)g << 8) | (u32)b)
#endif

#define COLOR_BLACK   Color888(  0,   0,   0)
#define COLOR_RED     Color888(255,   0,   0)
#define COLOR_GREEN   Color888(  0, 255,   0)
#define COLOR_BLUE    Color888(  0,   0, 255)
#define COLOR_LGREEN  Color888(  0,  80,   0)
#define COLOR_WHITE   Color888(255, 255, 255)
#define COLOR_CYAN    Color888(  0, 255, 255)
#define COLOR_ORANGE  Color888(255, 165,   0)
#define COLOR_YELLOW  Color888(255, 255,   0)
#define COLOR_PURPLE  Color888(160,  32, 240)

#define COLOR_LGRAY   Color888(155, 155, 155)
#define COLOR_GRAY    Color888(127, 127, 127)
#define COLOR_DGRAY   Color888( 58,  58,  58)
#define COLOR_DDGRAY  Color888( 40,  40,  40)

#define COLOR_AQUAMARINE    0x7FFFD4   //碧绿色
#define COLOR_AZURE         0xF0FFFF   //天蓝色
#define COLOR_BEIGE         0xF5F5DC   //米色
#define COLOR_CADETBLUE     0x5F9EA0   //君兰色
#define COLOR_GOLD          0xFFD700   //金色

#endif /* __COLOR_H */

/******************* (C) COPYRIGHT 2016 Makt *****END OF FILE****/
