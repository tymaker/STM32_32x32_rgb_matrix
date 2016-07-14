/**
  ******************************************************************************
  * @file    main.c
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

#include "main.h"
#include "VolumeBars.h"
#include "matrixman-gamefile.h"

//const char text[] = "www.makt.top";

/*void Disp_zh(const char *p)
{
	u16 num_zh = GET_ARRAY_LEN(text);
	char a[2];
	u8 i;
	if(num_zh / 4 != 0){
		u16 a = num_zh % 4;
		num_zh = num_zh + a;
	}
	printf("%d字符长度",num_zh);
	for(i=0;i<num_zh;i+=8){
		ClearBuff(0,1023);
		a[0] = p[i+0];
		a[1] = p[i+1];
		draw_hanzi(0,0,0x00ffffff,a);
		a[0] = p[i+2];
		a[1] = p[i+3];
		draw_hanzi(16,0,0x00ffffff,a);
		a[0] = p[i+4];
		a[1] = p[i+5];
		draw_hanzi(0,16,0x00ffffff,a);
		a[0] = p[i+6];
		a[1] = p[i+7];
		draw_hanzi(16,16,0x00ffffff,a);
		delay(1000);
	}
	while(1);
}*/

void GPIO_Config()
{
    GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC,ENABLE);
	  
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOC,&GPIO_InitStructure);
	  //GPIO_SetBits(GPIOC,GPIO_Pin_7);
	  GPIO_ResetBits(GPIOC,GPIO_Pin_7);
}



void System_Init(void)
{
//	SystemInit();
  setupRGBMatrixPorts(); //初始化GPIO
	LED_BLUE_ON
	SysTick_Init();  //初始化SysTick
	I2C_Init_GPIO();  //初始化I2C引脚
	DHT11_GPIO_Config();	/*初始化DTT11的引脚*/
	USART1_Config(ENABLE,115200); //初始化串口
  USART_ClearFlag(USART1,USART_FLAG_TC); //Clear interrupt Flag
	NVIC_Configuration();         //初始化nvic
  SPI_FLASH_Init(ENABLE);                //Enable SPI 
  RTC_Config();                 //RTC初始化
	ADC1_Init();

	//AT24Cxx_WriteOneByte(VERSION,0x4);
	//AT24Cxx_WriteOneByte(VERSION_L,0x00);
	//dt=AT24Cxx_ReadTwoByte(0);
  //printf("字符串输出 dt=%X\r\n",dt);

	printf("\n\n\tRGB MATRIX SYSTEM IS RUN\t\t\n");
	printf("+-----------------------------------------------+\n");
	printf("| System information :\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t|\n");
	printf("| MCU : STM32F103RBT6 \t\t\t\t|\n");
	printf("| Flash ID is : %X-%X-%X\t|\n",
	        *(__IO u32 *)(0X1FFFF7F0),*(__IO u32 *)(0X1FFFF7EC),*(__IO u32 *)(0X1FFFF7E8));
  printf("| Flash Capacity: %dK\t\t\t\t|\n", *(__IO u16 *)(0X1FFFF7E0));		
  RTC_Get();                    //获取
	printf("| System Time is %d-%d-%d  %d:%d:%d\t\t|\n",w_year,w_month,\
		    w_date,hour,min,sec);
	//Delay_us(20);
	if( Read_DHT11(&DHT11_Data)==SUCCESS){
		printf("| Humidity is %d.%d ％RH Temperature is %d.%d\t|\n",\
		DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
		//printf("\r\n 湿度:%d,温度:%d \r\n" ,DHT11_Data.humi_int,DHT11_Data.temp_int);
	}else printf("| [ERROR] Read DHT11 ERROR!\t\t\t|\n");
	printf("| RGB Matrix WiFi : ESP8266 ip:192.168.4.1\t|\n");
	printf("| RGB Matrix EEPROM : AT24C02 \t\t\t|\n");
	printf("| RGB Matrix SPI FLASH : 25Q16 2M spi flash\t|\n");
	printf("| RGB Matrix HIGHT:%d WIDTH:%d \t\t\t|\n", MATRIX_HEIGHT, MATRIX_WIDTH);
	printf("| System Version : V %X.%X \t\t\t|\n",AT24Cxx_ReadOneByte(VERSION),AT24Cxx_ReadOneByte(VERSION_L));
	printf("|\t\t\t\t\t\t|\n");
	printf("+-----------------------------------------------+\n");
	//Delay_us(500);
	USART2_Config(ENABLE,115200);        //初始化USART2
	TIM2_Configuration(DISABLE,250,36000);  //2000 是1s 
	TIM3_Configuration(ENABLE);   //初始化定时器3 
	TIM4_Configuration(DISABLE);
  if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==0)
	{
		Matrix_Text();
	}
  EXTI_Config();
	LED_BLUE_OFF
}

/*
int8_t demo(void)
{
    int8_t a=-3;
	  if(a>0) a=a;
	  else a=-a;
	  
	  a=a>0?a:-a;
	  return a;
}*/

void abc(void)
{
		#define A 1
    double x,y;
	  u8 x1,y1;
    printf("画心函数");
    for(y=-4;y<=0;y+=0.3)
    {
			for(x=-2;x<=4;x+=0.2)
				if(fabs(sqrt(x*x+y*y)-A*sin(2*atan(y/x)))<=1 ||fabs(sqrt(x*x+y*y)-A*sin(2*atan(-y/x)))<=1){
					drawPixel(x1,y1,0x00ff);
				  x1++;
					printf("*");
				}
				else{
					printf(" ");
				  drawPixel(x1,y1,0x00);
					x1++;
				}
			printf("\n");
			y1++;
			x1=0;
    }
    for(y=-1;y<=0;y+=0.2)
    {
			for(x=-2;x<=4;x+=0.2)
				if(fabs(y)-0.65*x*x>=0.2){
					drawPixel(x1,y1,0x00ff);
					x1++;
					printf("*");
				}
				else {
					printf(" ");
				  drawPixel(x1,y1,0x00);
					x1++;
				}
				printf("\n");
				y1++;
				x1=0;
    }
   while(1);
}

int main(void)
{
	System_Init();
	memcpy(Display_PWM,gImage_a,3072);
  delay(2000);
	ClearBuff(0,1024);
	//PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
	//Display_Demo();
	//InitBufInArray();
	//GetPowerMag();
	//Printf();
	//abc();
	//aabbcc();
	//VolumeBars_run();
	//playMatrixman();
	//aabbcc();
	while(1)
	{
		  show_Image();
			ClearBuff(0,1024);
		  Run();
			ClearBuff(0,1024);
			radiatingLinesPattern();
			ClearBuff(0,1024);
			Display_Pointer();
			ClearBuff(0,1024);
			analogClockMode();
			ClearBuff(0,1024);
			rotatingLinesPattern();
			ClearBuff(0,1024);
			//fsin();
			//ClearBuff(0,1024);
		  randomCirclesPattern();
			ClearBuff(0,1024);
			welcomePattern();
		  ClearBuff(0,1024);
  		ShowTime();
		  ClearBuff(0,1024);


	}
}

/*********************************************END OF FILE**********************/
