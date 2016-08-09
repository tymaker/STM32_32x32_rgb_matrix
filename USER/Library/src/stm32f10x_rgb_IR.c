/**
  ******************************************************************************
  * @file    IR.c
  * @author  Makt
  * @version V1.0
  * @date    2016-04-04
  * @brief   Maktrix 点阵显示程序
  ******************************************************************************
  * @attention
  * 连线参见 matrix_config.h 配置文件
	* 用到资源：ADC 用作产生随机数
	* 
	* 按键：按住按键，开机会进入自检程序
	* 			正常启动模式下按按键会切换显示模式
  ******************************************************************************
  */

#include "stm32f10x_rgb_IR.h"
#include "matrix_config.h"
#include "stm32f10x_rgb_matrix.h"

__asm int delay_us_private(u32 usec)
{
     ALIGN
     PUSH.W {r1}  //2时钟周期
     MOV r1,#20  //1时钟周期
     MUL r0,r1  //1时钟周期
     SUB r0,#3  //1时钟周期
loop
     SUBS r0,#1   //1时钟周期
     BNE loop   //如果跳转则为3个周期，不跳则只有1个周期
     POP {r1}   //2时钟周期
     BX lr    //3个时钟周期
                  //总共所用周期为(usec*4)-4,此处减4主要用于抵消调用此函数的消耗时钟周期（传参1时钟，BLX跳转3时钟）
}

u8 hongwai(void){
	#define ERROR 0XFF
	u8 key=0;
	u8 LOW_TIME=0,HIGHTIME=0;
	LED_BLUE_ON;
	Display_Enable(DISABLE);
	TIM4_Configuration(DISABLE);
	while(GPIO_IR==0){
		delay_us_private(100);
		LOW_TIME++;
	}
	while(GPIO_IR==1){
		delay_us_private(100);
		HIGHTIME++;
	}
	if((LOW_TIME>125)&&(LOW_TIME<135)&&(HIGHTIME>25)&&(HIGHTIME<35)){
		//?????
		u8 i;
		LED_BLUE_ON;
		HIGHTIME=LOW_TIME=0;
		for(i=0;i<6;i++){
			while(GPIO_IR==0)
				HIGHTIME=0;
			while(GPIO_IR==1){
				delay_us_private(100);
				HIGHTIME++; 
				if(HIGHTIME>=250)
					return ERROR;
			}
			if((HIGHTIME<11)&&(HIGHTIME>9)){
				key=key&0x7f;
			}
			else if((HIGHTIME<33)&&(HIGHTIME>22)){
				key=key|0x80;
			}
		}
		key=key<<2;
	}
	LED_BLUE_OFF;
	TIM4_Configuration(ENABLE);
	Display_Enable(ENABLE);
	return key;
}
