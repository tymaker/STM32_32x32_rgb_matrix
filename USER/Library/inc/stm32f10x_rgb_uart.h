/**
  ******************************************************************************
  * @file    stm32f10x_uart.h
  * @author  Makt
  * @version V3.5.0
  * @date    2016-04-04
  * @brief   串口头文件
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __UART1_H
#define	__UART1_H

#include "stm32f10x.h"
#include <stdio.h>
#define Max_UART_String 150  //接受缓冲区字数
#define TRUE 1
#define FALSE 0

void USART1_Config(u8,u32);
void USART2_Config(u8,u32);
char strcmp1(char *,char *);
int fputc(int ch, FILE *f);
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
void Get_Flag(void);
void SystemReset(void);

#endif /* __UART1_H */
/************************* (C) COPYRIGHT 2016  END OF FILE **********************/ 
