
STM32控制RGB全彩点阵显示屏
=======================================================
编写者： Makt 天宇科技 个人博客: www.makt.top 

功能：
------------

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
	
 * 
 
 
函数介绍：
------------



硬件参数：
------------

 * STM32f103CBt6
 * AT24c02 Eeprom
 * SPI Flash 存放字库文件 w25Q16  2MByte
 * 2块16*32 RGB 点阵显示屏 
 * 若干排线
 * 5V 2A 电源
 
