/**
  ******************************************************************************
  * @file    stm32f10x_rgb_init.c
  * @author  Makt
  * @version V1.0
  * @date    2016-04-04
  * @brief   点阵显示屏初始化文件
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
#include "stm32f10x_rgb_init.h"

/*
 *
 */
void setupRGBMatrixPorts(void)
{
	//LED初始化 led OE 
	GPIO_InitTypeDef GPIO_InitStructure;
  /* enable GPIO port Clock */

	RCC_APB2PeriphClockCmd(BOARD_LED_RCCPB, ENABLE);                  // enable LED GPIO port GPIOA
	RCC_APB2PeriphClockCmd(MTX_RCCPB, ENABLE);                        // enable matrix GPIO port GPIOB
	RCC_APB2PeriphClockCmd(LED_RCCPB, ENABLE);                        // enable LED GPIO port GPIOC

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	/* Init board led */
	GPIO_InitStructure.GPIO_Pin =BOARD_LED;
	GPIO_Init(BOARD_LED_PORT, &GPIO_InitStructure);
  /* Status indicator */
	GPIO_InitStructure.GPIO_Pin =LED_R | LED_G | LED_B;	
	GPIO_Init(LED_PORT, &GPIO_InitStructure);
  /* MITRIX GPIO */
	GPIO_InitStructure.GPIO_Pin = MTX_PCLK | MTX_PG0 | MTX_PG1 | MTX_PSTB;	
	GPIO_Init(MTX_PORT, &GPIO_InitStructure);

  /*  GPIO */
	GPIO_InitStructure.GPIO_Pin = GPIO_6 | GPIO_7;	
	GPIO_Init(GPIO_PORT, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = MTX_PR0 | MTX_PB0 | MTX_PR1 | MTX_PB1 | MTX_PA | MTX_PC  | MTX_PB | MTX_POE;	
	GPIO_Init(LED_PORT, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC, GPIO_Pin_7);	  // OE初始化为高电平 不显示

	/* EXTI line gpio config(PC13) */	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;       
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 // 上拉输入
	GPIO_Init(GPIOC, &GPIO_InitStructure);

  /********************************************************************/
	GPIO_ResetBits(MTX_PORTc, MTX_PA | MTX_PB | MTX_PC);  // A  B  C
	GPIO_ResetBits(MTX_PORTc, MTX_PR0);     // R0
	GPIO_ResetBits(MTX_PORTc, MTX_PR1);     // R1
	GPIO_ResetBits(MTX_PORT, MTX_PG0);      // G0
	GPIO_ResetBits(MTX_PORT, MTX_PG1);      // G1
	GPIO_ResetBits(MTX_PORTc, MTX_PG0);     // B0
	GPIO_ResetBits(MTX_PORTc, MTX_PG1);     // B1

	GPIO_ResetBits(MTX_PORT, MTX_PCLK | MTX_PSTB);  // SCK LE 初始化
  /*****************  LED  ********************************************/
	GPIO_SetBits(BOARD_LED_PORT, BOARD_LED);        // LED   H 关闭led 显示
	GPIO_SetBits(LED_PORT, LED_R | LED_G | LED_B);  // LED_RED   H
	GPIO_SetBits(GPIO_PORT, GPIO_6 |GPIO_7);        // GPIO_6 GPIO_7    H
	
	//GPIO_ResetBits(GPIO_PORT,GPIO_Pin_6);
	
}

/*
 * 函数名：NVIC_Configuration
 * 描述  ：配置嵌套向量中断控制器NVIC
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置P[A|B|C|D|E]0为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

  /* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&NVIC_InitStructure);

}

/*TIM_Period--1000   TIM_Prescaler--71 -->中断周期为1ms*/
void TIM2_Configuration(u8 EN,u16 TIME_period, u16 TIME_perescaler)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period=TIME_period -1;		 								/* 自动重装载寄存器周期的值(计数值) */
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
    TIM_TimeBaseStructure.TIM_Prescaler= (TIME_perescaler - 1);				    /* 时钟预分频数 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* 采样分频 */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* 向上计数模式 */
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);							    		/* 清除溢出中断标志 */
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    if(EN==ENABLE)
      TIM_Cmd(TIM2, ENABLE);
    else
			TIM_Cmd(TIM2, DISABLE);
		/* 开启时钟 */
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);		/*先关闭等待使用*/    
}


/*TIM_Period--1000   TIM_Prescaler--71 -->中断周期为1ms*/
void TIM3_Configuration(u8 EN)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
    TIM_DeInit(TIM3);
    TIM_TimeBaseStructure.TIM_Period=TIME_NUM-1;		 								/* 自动重装载寄存器周期的值(计数值) 1000*/
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
    TIM_TimeBaseStructure.TIM_Prescaler= (36000-1);				    /* 时钟预分频数 72M/72 72-1*/
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* 采样分频 */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* 向上计数模式 */
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);							    		/* 清除溢出中断标志 */
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	  if(EN==ENABLE)
      TIM_Cmd(TIM3, ENABLE);																		/* 开启时钟 */
    else
			TIM_Cmd(TIM3, DISABLE);
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);		/*先关闭等待使用*/    
}

/*TIM_Period--1000   TIM_Prescaler--71 -->中断周期为1ms*/
void TIM4_Configuration(u8 EN)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
    TIM_DeInit(TIM4);
    TIM_TimeBaseStructure.TIM_Period=2;		 								/* 自动重装载寄存器周期的值(计数值) 1000*/
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
    TIM_TimeBaseStructure.TIM_Prescaler= (36000-1);				    /* 时钟预分频数 72M/72 72-1*/
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* 采样分频 */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* 向上计数模式 */
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);							    		/* 清除溢出中断标志 */
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	  if(EN==ENABLE)
      TIM_Cmd(TIM4, ENABLE);																		/* 开启时钟 */
    else
			TIM_Cmd(TIM4, DISABLE);
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , DISABLE);		/*先关闭等待使用*/
}

/*
 * 函数名：EXTI_PB0_Config
 * 描述  ：配置 PB0 为线中断口，并设置中断优先级
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void EXTI_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;

	/* config the extiline(PC13) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//RCC_APB2Periph_GPIOB | 
  //	/* config the NVIC(PC13) */
  //	NVIC_Configuration();
	/* EXTI line(PC13) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line13;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}



/*********************************************END OF FILE**********************/
