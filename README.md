STM32F103 驱动 32*32 RGB 点阵显示屏

Overview
--------
 * stm32f103驱动 32*32 RGB点阵显示屏程序
 * 24位全彩驱动

 * Makt 天宇科技  更多详情见[我的博客](http://makt.top "http://Makt.top")  



Connection
----------

               | Pin | Pin |  Connection
--------------:|:---:|:---:|:--------------
    ** PC0 ** |   R0 |   G0 | **PB11 **
    ** PC1 ** |   B0 |  GND | ** GND **
    ** PC2 ** |   R1 |   R1 | **PB12 **
    ** PC3 ** |   B1 |  GND | ** GND **
    ** PC4 ** |   A  |   B  | ** PC6 **
    ** PC5 ** |   C  |  GND | ** GND **
    ** PB10** |  CLK |  STB | **PB13 **
    ** PC7 ** |   OE |  GND | ** GND **

 *  LED_R | PC12
 *  LED_G | PC8
 *  LED_B | PC9
 
 *  DHT11 | PA8
 
 *  GPIO1 | PB6
 *  GPIO2 | PB7

 *   KEY  | PC13


Running
-------
编译：编译环境采用keil 5.13
运行库：采用stm32f103 3.5版本库编译

运行：
	按住按键(PC13接地) --> 上电进入自检程序
	运行中按按键则切换显示模式


功能介绍
--------
 * 显示24位全彩图片 图片大小32 * 32
 * 显示16*16 中文（内置字库）
	void draw_hanzi(u8 x, u8 y, u32 Color, char *hanzi);
 * 支持4种字体ASCII 字符显示
	void drawChar(u8 x, u8 y, u32 Color, char character);
	void drawString(u8 x, u8 y, u32 Color, char *text);

 * 支持显示动态ASCII 字符文字
	setScrollMode(wrapForward); //显示模式
	setScrollSpeed(25);         //延时
	setScrollFont(font5x7);     //字体
	setScrollColor(Color888(5, 74,74));
	setScrollbgColor(Color888(5,5,5));
	setScrollXY(3);             //显示位置
	scrollText("Hello World", 1);//开始显示

 * 显示三角函数
	fsin();
	
 * 显示指针时钟
	init_Point_Clock();
	
 * 显示时间湿度
 
 * 显示
 
 * 测试SPI Flash
 	for(i=(45870*16);i<(766090);i=i+2)  //测试
	 printf("%04X ",SPI_FLASH_Read(i)); //测试 检测spi flash烧写正确与否
	 
 * 清屏
	ClearBuff(0,1024);
	


硬件资源
--------

 * STM32f103CBt6								*1
 * AT24c02 Eeprom								*1
 * SPI Flash 存放字库文件 w25Q16  2MByte		*1
 * 2块16*32 RGB 点阵显示屏 						*2
 * 若干排线										*n
 * 5V 2A 电源									*1

参考
----

