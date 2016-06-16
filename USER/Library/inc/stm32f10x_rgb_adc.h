#ifndef __ADC_H
#define	__ADC_H

#include "stm32f10x.h"
static void ADC1_GPIO_Config(void);
static void ADC1_Mode_Config(void);
void ADC1_Init(void);
u16 random(u16 a, u16 b);

#endif /* __STM32F103_MATRIX_ADC_H */

