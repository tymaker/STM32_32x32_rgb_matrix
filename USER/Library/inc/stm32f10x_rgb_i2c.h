/**
  ******************************************************************************
  * @file    i2c.c
  * @author  Makt
  * @version V1.0
  * @date    2016-04-04
  * @brief   软件i2c 功能文件
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __RGB_I2C_EE_H
#define	__RGB_I2C_EE_H

#include "stm32f10x.h"
#include "stm32f10x_rgb_systick.h"

/* EEPROM Addresses defines */
#define EEPROM_Block0_ADDRESS 0xA0   /* E2 = 0 */
//#define EEPROM_Block1_ADDRESS 0xA2 /* E2 = 0 */
//#define EEPROM_Block2_ADDRESS 0xA4 /* E2 = 0 */
//#define EEPROM_Block3_ADDRESS 0xA6 /* E2 = 0 */

#define I2C_SCL GPIO_Pin_6
#define I2C_SDA GPIO_Pin_7
#define GPIO_I2C GPIOB

#define I2C_SCL_H GPIO_SetBits(GPIO_I2C,I2C_SCL)
#define I2C_SCL_L GPIO_ResetBits(GPIO_I2C,I2C_SCL)

#define I2C_SDA_H GPIO_SetBits(GPIO_I2C,I2C_SDA)
#define I2C_SDA_L GPIO_ResetBits(GPIO_I2C,I2C_SDA)

#define AT24C01  127
#define AT24C02  255
#define AT24C04  511
#define AT24C08  1023
#define AT24C16  2047
#define AT24C32  4095
#define AT24C64  8191
#define AT24C128 16383
#define AT24C256 32767

#define EE_TYPE  AT24C02

#define VERSION    0X01
#define VERSION_L  0X02


void I2C_Init_GPIO(void);
void I2C_SDA_OUT(void);
void I2C_SDA_IN(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_NAck(void);
u8   I2C_Wait_Ack(void);
void I2C_Send_Byte(u8 txd);
u8   I2C_Read_Byte(u8 ack);
u8 AT24Cxx_ReadOneByte(u16 addr);
u16 AT24Cxx_ReadTwoByte(u16 addr);
void AT24Cxx_WriteOneByte(u16 addr,u8 dt);
void AT24Cxx_WriteTwoByte(u16 addr,u16 dt);



#endif /* __RGB_I2C_EE_H */
