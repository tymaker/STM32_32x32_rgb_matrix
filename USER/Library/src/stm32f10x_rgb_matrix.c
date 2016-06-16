/**
  ******************************************************************************
  * @file    matrix.c
  * @author  Makt
  * @version V1.0
  * @date    2016-04-04
  * @brief   新的RGB 点阵显示 程序
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
/*

 * rgb_matrix Library - Methods for interacting with background layer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
 
#include "stm32f10x_rgb_matrix.h"
#include <string.h>

u8 Display_PWM[MATRIX_MODULE*MATRIX_HEIGHT*2][3]={
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,
0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X00,0X7F,0X00,
0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0X00,
0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,
0X00,0X7F,0X00,0X00,0X7F,0X7F,0X00,0X7F,0X7F,0X00,0X7F,0X7F,0X7F,0X00,0X00,0X7F,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,
0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X7F,
0X00,0X7F,0X7F,0X00,0X7F,0X7F,0X00,0X7F,0X7F,0X00,0X7F,0X7F,0X00,0X7F,0X7F,0X7F,
0X00,0X00,0X7F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X00,0X7F,
0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X7F,0X00,0X7F,0X7F,0X00,0X7F,0X7F,
0X00,0X7F,0X7F,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,
0XFF,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X00,0X7F,
0X00,0X00,0X7F,0X00,0X00,0X7F,0X7F,0X00,0X7F,0X7F,0X00,0X7F,0X7F,0XFF,0XFF,0X00,
0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,
0XFF,0X00,0XFF,0XFF,0X00,0X7F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0X00,0X7F,0X00,0X00,0X7F,
0X00,0X00,0X7F,0X7F,0X00,0X7F,0X7F,0X00,0X7F,0X7F,0XFF,0XFF,0X00,0XFF,0XFF,0X00,
0XFF,0XFF,0X00,0XFF,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,
0XFF,0X00,0X00,0XFF,0X00,0X7F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X00,0X7F,0X00,0X00,0X7F,
0X00,0X00,0X7F,0X7F,0X00,0X7F,0X7F,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,0XFF,0X00,
0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,
0XFF,0X00,0X00,0XFF,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,
0X7F,0X00,0X7F,0X7F,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0X00,0XFF,0X00,
0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,
0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X7F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,
0X7F,0X00,0X7F,0X7F,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,
0X00,0XFF,0X00,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,
0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X7F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0X00,0X7F,0X7F,0X00,0X7F,0X7F,0X00,0X7F,
0X7F,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,
0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0XFF,0X00,0XFF,0XFF,
0X00,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,0X7F,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0X00,0X7F,0X7F,0X00,0X7F,0X7F,0X00,0X7F,
0X7F,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0X00,0XFF,
0X00,0X00,0XFF,0X00,0X00,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,0XFF,
0X00,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,0X7F,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X00,0X7F,0X7F,0XFF,0XFF,
0X00,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0X00,0XFF,
0X00,0X00,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,0X7F,
0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0XFF,0XFF,
0X00,0XFF,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0X00,0XFF,0X00,0X00,0XFF,
0XFF,0X00,0XFF,0XFF,0X00,0XFF,0XFF,0X00,0XFF,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,
0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,
0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0XFF,0X00,0X00,0X00,0XFF,0X00,0X00,0XFF,
0XFF,0X00,0XFF,0XFF,0X00,0XFF,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,
0X00,0X00,0X7F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X00,
0X00,0X7F,0X00,0X00,0X00,0XFF,0X00,0X00,0X00,0XFF,0X00,0X00,0XFF,0XFF,0X00,0XFF,
0XFF,0X00,0XFF,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X00,0X00,0XFF,0X00,0X00,0XFF,0XFF,0X00,0XFF,
0XFF,0X00,0XFF,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0XFF,0X00,0XFF,0XFF,0X00,0XFF,
0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,
0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,
0X7F,0X00,0X00,0X7F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,0X00,
0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC9,0X81,0X3E,0XC9,0X81,0X3E,0X7F,0X51,0X26,
0X7F,0X51,0X26,0X7F,0X51,0X26,0X7F,0X51,0X26,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,
0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,
0X00,0X00,0X7F,0X00,0X00,0X00,0X00,0XC9,0X81,0X3E,0XC9,0X81,0X3E,0X7F,0X51,0X26,
0X7F,0X51,0X26,0X7F,0X51,0X26,0X7F,0X51,0X26,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,
0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,
0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,
0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0XC9,0X81,0X3E,0XC9,0X81,0X3E,0X7F,0X51,0X26,
0X7F,0X51,0X26,0X7F,0X51,0X26,0X7F,0X51,0X26,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,
0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,
0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,
0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,
0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,
0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0XC9,0X81,0X3E,0XC9,0X81,0X3E,0X7F,0X51,0X26,
0X7F,0X51,0X26,0X7F,0X51,0X26,0X7F,0X51,0X26,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,
0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,
0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,
0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,
0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,
0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,
0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,
0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,
0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,0X00,0X7F,0X00,
};

bitmap_font *font = (bitmap_font *) &apple3x5;
const bitmap_font *scrollFont = &apple5x7;
// Scrolling
ScrollMode scrollmode = bounceForward;
// scroll text
const u8 textLayerMaxStringLength = 255;
char scrolBuff[textLayerMaxStringLength];
u32 ScrolColor; //颜色
u32 ScrolbgColor;
u16 textlen,textWidth; //字符个数 总移位数
u8 ScrollPosition = 0; //滚动位置
u8 Scroll_Y;

u8 Control = 1;
/*
*/
/*
 *    7    6    5    4     3     2       1        0
 *                       left  right  灰度模式  字符显示
 */

extern u8 ASCii[62][16];
extern u8 ASCII_8_4[10][16];
const u8 scan = MATRIX_HEIGHT / 2;
//const u16 waits[] = { 5, 10, 20, 40, 80, 160, 320, 640, 1280, 2560 };
const u16 waits[] =   { 1, 5, 20, 40, 80, 160, 280, 640, 980};
const u16 waita[] =   {									  	 5,  20, 80, 980};

extern const unsigned char __apple3x5_bitmap__[];
extern const unsigned char __apple5x7_bitmap__[];


/**
 * Displays the buffer on the display using binary encoding (PWM equivalent).
 */
//void displayBuffer(void) {
//	u8 s;
//	u8 plane;
//	#if(MATRIX_WIDTH == 32)
//		for(plane = 0; plane < scan; plane ++) //行扫描
//		{
//				setRow(s);
//			  Send_RGB_Module(plane,0);
//				showLine(waits[8]);
//		}
//	#else
//		//GPIO6_LOW; //调试
//		for(plane = 0; plane < scan; plane ++) //行扫描
//		{
//				setRow(plane);
//				for(s = 0; s <2 /*= (MATRIX_WIDTH/32)*/; s ++) //扫2模块 32*2 个点
//				{
//					Send_RGB_Module(plane,s);  //发送一屏 32*16 数据  8/1 扫描
//				}
//				showLine(waits[8]);  //8(5): 2.12 0.38
//		}
//		//GPIO6_HIGH; //调试
//	#endif
//}

/**
  * @brief  定时器中断函数
  * @param  None
  * @retval None
  */
void Timer_Move_interrupt()
{
	  ScrollPosition ++;
	  if(ScrollPosition >= textWidth)
			ScrollPosition = 0;
		//TODO:
	  ClearBuff(Scroll_Y*32,(Scroll_Y + scrollFont->Height)*32);
		if(ScrolbgColor != 0)
			fillRect(0 ,Scroll_Y , 32, scrollFont->Height,ScrolbgColor);
		if(scrollmode == showtime){
			Scrolshowtime();
		  //setScrollColor(ScrolColor);
		}
		//Scroll_Y
		drawScrollString(ScrollPosition,0,24);
}

/**
 * Displays the buffer on the display using binary encoding (PWM equivalent).
 * 8 位灰度显示模式
 * Display_PWM[MATRIX_MODULE*MATRIX_HEIGHT*2][3] 为缓存
 */
void display_PWM(void) {
	u8 s;
	u8 plane;
	u8 Display_Cache[64][3];
	u8 Display_Cache1[64][3];

	#if(MATRIX_WIDTH == 32)
		for(plane = 0; plane < scan; plane ++) //行扫描
		{
				setRow(s);
					Send_RGB_Module(plane,0);
				showLine(waits[1]);
		}
	#else
		//GPIO6_LOW;
		for(plane = 0; plane < scan; plane ++) //行扫描 扫描8行
		{
				u8 num,a;
			  for(a=0;a<32;a++){
					u16 number;
					number = plane *32 + a;
				  Display_Cache[a][0]=Display_PWM[number][0];
				  Display_Cache[a][1]=Display_PWM[number][1];
				  Display_Cache[a][2]=Display_PWM[number][2];
				  Display_Cache[a+32][0]=Display_PWM[number+512][0];
				  Display_Cache[a+32][1]=Display_PWM[number+512][1];
				  Display_Cache[a+32][2]=Display_PWM[number+512][2];
					
				  Display_Cache1[a][0]=Display_PWM[number+256][0];
				  Display_Cache1[a][1]=Display_PWM[number+256][1];
				  Display_Cache1[a][2]=Display_PWM[number+256][2];
				  Display_Cache1[a+32][0]=Display_PWM[number+768][0];
				  Display_Cache1[a+32][1]=Display_PWM[number+768][1];
				  Display_Cache1[a+32][2]=Display_PWM[number+768][2];
				}
			  setRow(plane);  // 行选择
			  for(num=8;num>0;num--) //每一行扫描8次
			  {
						for(s = 0; s <2 /*= (MATRIX_WIDTH/32)*/; s ++) //扫2模块 32*2 个点
						{
								for(a=0;a<MATRIX_MODULE;a++) //循环从0 ~ 32
								{
										if((Display_Cache[s*32+a][0] & 0x80) == 0x80)
											MTX_PORTc->BSRR = MTX_PR0;
										else
											MTX_PORTc->BRR  = MTX_PR0; 										
										if((Display_Cache[s*32+a][1] & 0x80) == 0x80)
											MTX_PORT->BSRR = MTX_PG0;
										else
											MTX_PORT->BRR  = MTX_PG0;
										if((Display_Cache[s*32+a][2] & 0x80) == 0x80)
											MTX_PORTc->BSRR = MTX_PB0;
										else
											MTX_PORTc->BRR  = MTX_PB0;

										if((Display_Cache1[s*32+a][0] & 0x80) == 0x80)
											MTX_PORTc->BSRR = MTX_PR1;
										else
											MTX_PORTc->BRR  = MTX_PR1; 
										if((Display_Cache1[s*32+a][1] & 0x80) == 0x80)
											MTX_PORT->BSRR = MTX_PG1;
										else
											MTX_PORT->BRR  = MTX_PG1;
										if((Display_Cache1[s*32+a][2] & 0x80) == 0x80)
											MTX_PORTc->BSRR = MTX_PB1;
										else
											MTX_PORTc->BRR  = MTX_PB1;
										CLK_TOGGLE
								}
						}
						for(a=0;a<64;a++)
						{
							Display_Cache[a][0] = Display_Cache[a][0] <<1;
							Display_Cache[a][1] = Display_Cache[a][1] <<1;
							Display_Cache[a][2] = Display_Cache[a][2] <<1;
							Display_Cache1[a][0] = Display_Cache1[a][0] <<1;
							Display_Cache1[a][1] = Display_Cache1[a][1] <<1;
							Display_Cache1[a][2] = Display_Cache1[a][2] <<1;
						}
						if(num >4){
						showLine(waita[num-5]);  //8(5): 2.12 0.38
						}
						showLine(waits[num]);  //8(5): 2.12 0.38
				}
		}
		//GPIO6_HIGH;
	#endif
}

/**
 * sets the row on the row gpio ports
 */
void setRow(u8 row) {
	// todo: perhaps a lookup table could give us a tiny boost here.

	if (row & 0x01) MTX_PORTc->BSRR = MTX_PA;
	else MTX_PORTc->BRR = MTX_PA;

	if (row & 0x02) MTX_PORTc->BSRR = MTX_PB;
	else MTX_PORTc->BRR = MTX_PB;

	if (row & 0x04) MTX_PORTc->BSRR = MTX_PC;
	else MTX_PORTc->BRR = MTX_PC;
}

/**
 * loads rgb1 and rgb2 gpio ports with the given bitplane
 */
void setRGB(uint32_t rgb1, uint32_t rgb2, uint8_t plane) {
	// using bitshifting seems to be faster due to gcc optimization
	// than using a bitmask lookup table here.

	if (rgb1 & (1 << plane))        MTX_PORTc->BSRR = MTX_PR0;
	else                            MTX_PORTc->BRR  = MTX_PR0;

	if (rgb1 & (1 << (plane + 8))) 	MTX_PORT->BSRR = MTX_PG0;
	else                            MTX_PORT->BRR  = MTX_PG0;

	if (rgb1 & (1 << (plane + 16))) MTX_PORTc->BSRR = MTX_PB0;
	else                            MTX_PORTc->BRR  = MTX_PB0;

	if (rgb2 & (1 << plane))        MTX_PORTc->BSRR = MTX_PR1;
	else                            MTX_PORTc->BRR  = MTX_PR1;

	if (rgb2 & (1 << (plane + 8))) 	MTX_PORT->BSRR = MTX_PG1;
	else                            MTX_PORT->BRR  = MTX_PG1;

	if (rgb2 & (1 << (plane + 16))) MTX_PORTc->BSRR = MTX_PB1;
	else                            MTX_PORTc->BRR  = MTX_PB1;
}


/**
 * strobes / shows a line for a n*nop amount of time.
 */
void showLine(u16 amount) {
	u16 c;
	STROBE;
	DISP_ON;
	for (c=0; c<amount; c++) /*asm("nop")*/;
	DISP_OFF;
}


// order needs to match fontChoices enum
const bitmap_font *fontArray[] = {
    &apple3x5,
    &apple5x7,
    &apple6x10,
    &apple8x13,
};

const bitmap_font * fontLookup(fontChoices font) {
    return fontArray[font];
}

/**
  * @brief  设置字体函数
  * @param  None
  * @retval None
	* @canshu font3x5, font5x7, font6x10, font8x13
  */
void setFont(fontChoices newFont)
{
  // Fonts are font3x5, font5x7, font6x10, font8x13
	font = (bitmap_font *)fontLookup(newFont);
  //printf("\n%d\n",newFont);
}


u8 getBitmapFontPixelAtXY(unsigned char letter, unsigned char x, unsigned char y, char *font)
{
    int location = 0;

    if (__apple3x5_bitmap__[(location * 6) + y] & (0x80 >> x))
        return 1;
    else
        return 0;
}

void drawChar(u8 x, u8 y, u32 Color, char character)
{
  u8 xcnt, ycnt;
  character =character - 32;
	for (ycnt = 0; ycnt < font->Height; ycnt++) {
			for (xcnt = 0; xcnt < font->Width; xcnt++) {
					if (font->Bitmap[(character * (font->Height)) + ycnt] & (0x80 >> xcnt)){
							drawPixel(x + xcnt, y + ycnt, Color);
					}
			}
	}
}


//  32*((High8bit-0xa0-1)*94+(Low8bit-0xa0-1))
void draw_hanzi(u8 x, u8 y, u32 Color, char *hanzi)
{
  u8 xcnt, ycnt;
	u32 number;
	number = (((hanzi[0]-0x81)*192) + ((hanzi[1]>>4)-4)*16 + (hanzi[1]&0x0F)) - (hanzi[0]-0x81);
	if((hanzi[1]>>4) < 8)
	{
		number = number - (hanzi[0]-0x81);
	}
	else
		number = number - ((hanzi[0]-0x81)+1);
	for (ycnt = 0; ycnt < 16; ycnt++) {
			for (xcnt = 0; xcnt < 16; xcnt++) {
					if(SPI_FLASH_Read(number*32 + ycnt*2) & (0x8000 >>xcnt)){
							drawPixel(x + xcnt, y + ycnt, Color);
					}
			}
	}
}

void drawString(u8 x, u8 y, u32 Color, char *text) {
    u8 xcnt, ycnt, i = 0, offset = 0;
    char character;
	
    // limit text to 10 chars, why?
    for (i = 0; i < 10; i++) {
        character = text[offset++];
        if (character == '\0')
            return;
        character -= 32;
        for (ycnt = 0; ycnt < font->Height; ycnt++) {
            for (xcnt = 0; xcnt < font->Width; xcnt++) {
                //if (getBitmapFontPixelAtXY(character, xcnt, ycnt, font)) {
							    if(font->Bitmap[(character * (font->Height)) + ycnt] & (0x80 >> xcnt)) {
                    drawPixel(x + xcnt, y + ycnt, Color);
                }
            }
        }
        x += font->Width;
    }
}

void drawScrollString(u8 scrollnum, u8 x, u8 y)
{
    u8 xcnt, ycnt, i = 0, offset = ScrollPosition / scrollFont->Width;
    char character;
	  u8 scrollF = ScrollPosition % scrollFont->Width - scrollFont->Width +1;
	  //printf("%d  %d \n",offset,scrollF);
    // limit text to 10 chars, why?
    for (i = 0; i < 10; i++) {
        character = scrolBuff[offset++];
        if (character == '\0')
            return;
        character -= 32;
        for (ycnt = 0; ycnt < scrollFont->Height; ycnt++) {
            for (xcnt = 0; xcnt < scrollFont->Width; xcnt++) {
							    if(scrollFont->Bitmap[(character * (scrollFont->Height)) + ycnt] & (0x80 >> xcnt)) {
                    drawPixel(x + xcnt - scrollF, Scroll_Y + ycnt, ScrolColor);
                }
            }
        }
        x += scrollFont->Width;
    }
}


// stops the scrolling text on the next refresh
void stopScrollText(void) {
    // STOP
	  TIM2_Configuration(DISABLE,100,36000);
}

// returns 0 if stopped
// returns positive number indicating number of loops left if running
// returns -1 if continuously scrolling
int8_t getScrollStatus(void) {
    return 0;
}

void scrollText(char inputtext[], int8_t numScrolls) {
	  u8 i = 0;
    u8 length = strlen((char *)inputtext);
    if (length > textLayerMaxStringLength)
        length = textLayerMaxStringLength;

    textlen = length;

    textWidth = (textlen * scrollFont->Width) - 1;
		for(i = 0; i < textLayerMaxStringLength; i ++){
			scrolBuff[i] = 0;
		}
		i = 0;
    switch (scrollmode) {
    case wrapForward:
				while(i <= length){
						i++;
						scrolBuff[i] = inputtext[i];
				}
			  break;
    case bounceForward:
    case bounceReverse:
/*        ScrollMin = -textWidth;
        //ScrollMax = screenConfig.localWidth;

        ScrollPosition = ScrollMax;

        if (scrollmode == bounceReverse)
            ScrollPosition = ScrollMin;

        // TODO: handle special case - put content in fixed location if wider than window*/

        break;
		case showtime:
				break;
    case stopped:
			  stopScrollText();
		    break;
    case off:
        ScrollPosition = 0;
		    stopScrollText();
		    ClearBuff(Scroll_Y*32,(Scroll_Y + scrollFont->Height)*32);
        break;
    }
}

// TODO: recompute stuff after changing mode, font, etc
void setScrollMode(ScrollMode mode) {
    scrollmode = mode;
}

void setScrollSpeed(u8 pixels_per_second) {
    //framesperscroll = (MATRIX_REFRESH_RATE * 1.0) / pixels_per_second;
	  TIM2_Configuration(ENABLE,pixels_per_second*10,36000);
}

void setScrollFont(fontChoices newFont) {
    scrollFont = fontLookup(newFont);
}

void setScrollColor(u32 newColor) {
    //copyRgb24(&textcolor, &newColor);
	  ScrolColor = newColor;
}


void setScrollbgColor(u32 newColor) {
    //copyRgb24(&textcolor, &newColor);
	  ScrolbgColor = newColor;
}


void setScrollXY(u8 row) {
	if(scrollFont->Height + row <= MATRIX_MODULE)
    Scroll_Y = row;
	else
		Scroll_Y = 0;
}

void Scrolshowtime(void)
{
	u8 i;
	char a[] = "Now Time is: ";
	RTC_Get();
	for(i = 0; i < textLayerMaxStringLength; i ++){
	  scrolBuff[i] = 0;
	}
	for(i = 0; i < 13; i ++){
		 scrolBuff[i] = a[i];
	}
	scrolBuff[13] = (hour/10) + 48;
	scrolBuff[14] = (hour%10) + 48;
	scrolBuff[15] = ':';
	scrolBuff[16] = (min/10) + 48;
	scrolBuff[17] = (min%10) + 48;
	scrolBuff[18] = ':';
	scrolBuff[19] = (sec/10) + 48;
	scrolBuff[20] = (sec%10) + 48;
	scrolBuff[21] = ' ';
	scrolBuff[22] = ' ';
	scrolBuff[23] = (w_month/10) + 48;
	scrolBuff[24] = (w_month%10) + 48;
	scrolBuff[25] = ' ';
	scrolBuff[26] = (w_date/10) + 48;
	scrolBuff[27] = (w_date%10) + 48;

  textlen = 27;
  textWidth = (textlen * scrollFont->Width) - 1;
}

void drawImage(u8 x, u8 y, s8 w, s8 h, u32 Color, u8 *addres){
	u8 a,b;
	for(a=0;a<w;a++){
		for(b=0;b<h;b++){
			drawPixel(x+a,y+b,Color);
		}
	}
}
/*********************************************END OF FILE**********************/
