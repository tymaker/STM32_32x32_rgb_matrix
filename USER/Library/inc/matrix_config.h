/**
  ******************************************************************************
  * @file    matrix_config.h
  * @author  Makt
  * @version V1.0
  * @date    2016-04-04
  * @brief   全彩点阵显示屏配置文件
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __MATIRX_CONFIG_H
#define __MATIRX_CONFIG_H

/*
 *  PC0   R0  | G0   PB11
 *  PC1   B0  | GND  GND
 *  PC2   R1  | G1   PB12
 *  PC3   B1  | GND   /
 *  PC4   A   | B    PC6
 *  PC5   C   | GND   /
 *  PB10  CLK | LE   PB13
 *  PC7   OE  | GND
 *
 *
 *  LED_R | PC12
 *  LED_G | PC8
 *  LED_B | PC9
 *
 *
	 *  DHT11 | PA8
	 *
	 *  GPIO1 | PB6
	 *  GPIO2 | PB7
 * 
 */
 
/* 状态指示灯 */
#define LED_PORT 	GPIOC
#define LED_R			GPIO_Pin_12
#define LED_G			GPIO_Pin_8
#define LED_B			GPIO_Pin_9
#define LED_RCCPB	RCC_APB2Periph_GPIOC
/* 板子内部指示灯 */
#define BOARD_LED_PORT 	GPIOA
#define BOARD_LED			  GPIO_Pin_2
#define BOARD_LED_RCCPB	RCC_APB2Periph_GPIOA

#define GPIO_PORT 	GPIOB
#define GPIO_6			GPIO_Pin_6
#define GPIO_7      GPIO_Pin_7
#define GPIO_RCCPB	RCC_APB2Periph_GPIOB
#define GPIO6_HIGH  GPIO_PORT->BSRR = GPIO_6
#define GPIO6_LOW   GPIO_PORT->BRR = GPIO_6
#define GPIO7_HIGH  GPIO_PORT->BSRR = GPIO_7
#define GPIO7_LOW   GPIO_PORT->BSRR = GPIO_7


#define MTX_PORT	GPIOB  //当使能GPIOB的时钟时，也要使能GPIOC时钟 因为ABC 挂载GPIOC上
#define MTX_PORTc GPIOC
#define MTX_RCCPB	RCC_APB2Periph_GPIOB

#define MTX_PR0		GPIO_Pin_0   //GPIOC
#define MTX_PG0		GPIO_Pin_11  //GPIOB
#define MTX_PB0		GPIO_Pin_1   //GPIOC

#define MTX_PR1		GPIO_Pin_2   //GPIOC
#define MTX_PG1		GPIO_Pin_12  //GPIOB
#define MTX_PB1		GPIO_Pin_3   //GPIOC

#define MTX_PA		GPIO_Pin_4   //GPIOC
#define MTX_PB		GPIO_Pin_6   //GPIOC
#define MTX_PC		GPIO_Pin_5   //GPIOC

#define MTX_PSTB	GPIO_Pin_13  //GPIOB
#define MTX_POE		GPIO_Pin_7   //GPIOC
#define MTX_PCLK	GPIO_Pin_10  //GPIOB

#define DISP_ON         MTX_PORTc->BRR = MTX_POE;
#define DISP_OFF        MTX_PORTc->BSRR = MTX_POE;
#define CLK_TOGGLE      MTX_PORT->BSRR = MTX_PCLK; MTX_PORT->BRR = MTX_PCLK;
#define STROBE          MTX_PORT->BSRR = MTX_PSTB; MTX_PORT->BRR = MTX_PSTB;

#define MATRIX_WIDTH    64
#define MATRIX_HEIGHT   16
#define MATRIX_MODULE   32

#define MATRIX_SIZE     MATRIX_WIDTH*MATRIX_HEIGHT


#define LED_RED_ON     LED_PORT->BRR  = LED_R;  //GPIO_ResetBits(LED_PORT, LED_R);
#define LED_RED_OFF    LED_PORT->BSRR = LED_R;  //GPIO_SetBits(LED_PORT, LED_R);
#define LED_GREEN_ON   LED_PORT->BRR  = LED_G;  //LED_GREEN_ON
#define LED_GREEN_OFF  LED_PORT->BSRR = LED_G;  //LED_GREEN
#define LED_BLUE_ON    LED_PORT->BRR  = LED_B;
#define LED_BLUE_OFF   LED_PORT->BSRR = LED_B;

#define DISP_ZISE(a)   ((sizeof(a) / sizeof(*(a)))-1) //缓存大小

#endif
