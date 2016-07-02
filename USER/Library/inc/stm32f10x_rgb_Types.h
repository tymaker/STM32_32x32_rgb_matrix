/**
  ******************************************************************************
  * @file    stm32f10x_rgb_Types.h
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    04-April-2016
  * @brief   types 结构体 函数头文件
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TYPES_H
#define	__TYPES_H

#include "stm32f10x.h"
// Pointer to a function taking no parameters and returning void
typedef void(*ptr2Function)();

// Pointer to a function taking two rgb24 parameters and returning void
typedef void(*ptr2SetFunction)(u32, u32);

// Mode definition structure
typedef struct {
	char *name;
	ptr2Function function;
}
NAMED_FUNCTION;

enum USER_INTERACTION_CODE {
	UICODE_HOME, UICODE_SELECT, UICODE_LEFT, UICODE_RIGHT
};


#endif /* __TYPES_H */

/******************* (C) COPYRIGHT 2011 Makt *****END OF FILE****/
