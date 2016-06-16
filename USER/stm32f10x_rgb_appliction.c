/**
  ******************************************************************************
  * @file    stm32f10x_rgb_init.c
  * @author  Makt
  * @version V1.0
  * @date    2016-04-04
  * @brief   新的RGB 点阵显示 程序
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
#include "stm32f10x_rgb_appliction.h"
#include "stm32f10x_rgb_adc.h"
#include "math.h"
#include "stm32f10x_rgb_uart.h"

uint8_t scale_col(int val, int lo, int hi) {
	if (val < lo) return 0;
	if (val > hi) return 255;
	return 255 * (val - lo) / (hi - lo);
}
void Rotate(int x, int y, float angle,
						float *new_x, float *new_y) {
	*new_x = x * cosf(angle) - y * sinf(angle);
	*new_y = x * sinf(angle) + y * cosf(angle);
}
void Run() {
	const s8 cent_x = 32 / 2;
	const s8 cent_y = 32 / 2;

	// The square to rotate (inner square + black frame) needs to cover the
	// whole area, even if diagnoal. Thus, when rotating, the outer pixels from
	// the previous frame are cleared.
	const float rotate_square = min(28, 28) * 1.41;
	const s8 min_rotate = cent_x - rotate_square / 2;
	const s8 max_rotate = cent_x + rotate_square / 2;

	// The square to display is within the visible area.
	const float display_square = min(28, 28) * 0.7;
	const s8 min_display = cent_x - display_square / 2;
	const s8 max_display = cent_x + display_square / 2;

	const float deg_to_rad = 2 * 3.14 / 360;
	int rotation = 0;

	while (1) {
		s8 x,y;
		//delay(15);
		rotation %= 360;
		for (x = min_rotate; x < max_rotate; ++x) {
			for (y = min_rotate; y < max_rotate; ++y) {
				float rot_x, rot_y;
				Rotate(x - cent_x, y - cent_x,
							 deg_to_rad * rotation, &rot_x, &rot_y);
				if (x >= min_display && x < max_display &&
						y >= min_display && y < max_display) { // within display square
					drawPixel((u8)(rot_x + cent_x), (u8)(rot_y + cent_y),0x00);
					drawPixel((u8)(rot_x + cent_x), (u8)(rot_y + cent_y),
														 (u32)(scale_col(x, min_display, max_display)<<16 | 
														 ((255 - scale_col(y, min_display, max_display))<<8) | 
														 (scale_col(y, min_display, max_display))));
				}
				else{
					// black frame.
					drawPixel((u8)(rot_x + cent_x), (u8)(rot_y + cent_y),0x00);
				}
			}
		}
		++rotation;
		if(checkForTermination())
			return;
	}
}

u8 checkForTermination(void){
	u8 cont = Control &= 0x80;
	if(cont == 0x80){
		Control &= 0x7f;
		cont = 1;
	}
	else
		cont = 0;
	return cont;
}

// Draw clock tics 画表盘 12点式表盘
void drawClockTics(void) {
    int x, y, d;

    // Draw tics
    for (d = 0; d < 360; d+=30) {
        x = (u32)(16 + TIC_RADIUS * cos(d * 3.14 / 180.0));
        y = (u32)(16 - TIC_RADIUS * sin(d * 3.14 / 180.0));

        drawPixel(x, y, TIC_COLOR);
    }
    //matrix.swapBuffers();        
}

// Draw clock numerics
void drawClockNumerics(void) {

    // Draw numerics
    drawString(13,  5, NUMERICS_COLOR, "12");
    drawString(25, 14, NUMERICS_COLOR, "3");
    drawString(15, 23, NUMERICS_COLOR, "6");
    drawString( 5, 14, NUMERICS_COLOR, "9");
    
}

void _drawHourHand(int hour, int min, rgb24 color) {

    // Calculate angle of hour hand in radians taking
    // minutes into consideration.
    double radians = (90 - ((hour * 30) + ((min * 29) / 60))) * 3.14 / 180.0;

    int x = (u32)(16 + HOUR_HAND_RADIUS * cos(radians));
    int y = (u32)(16 - HOUR_HAND_RADIUS * sin(radians));

    drawLine(16, 16, x, y, color);
}

void _drawMinHand(int min, rgb24 color) {
		int x,y;
    double radians = (90 - (min * 6)) * 3.14 / 180.0;

    x = (16 + MIN_HAND_RADIUS * cos(radians));
    y = (16 - MIN_HAND_RADIUS * sin(radians));

    drawLine(16, 16, x, y, color);
}

void _drawSecIndicator(int sec, rgb24 color) {
		int x,y;
    double radians = (90 - (sec * 6)) * 3.14 / 180.0;

    x = (16 + SEC_IND_RADIUS * cos(radians));
    y = (16 - SEC_IND_RADIUS * sin(radians));

    drawPixel(x, y, color);
}

// Analog Clock Mode
void analogClockMode() {

    // Clear screen
    fillScreen(COLOR_BLACK);
    // Draw clock face
    drawClockTics();
    //drawClockNumerics();

    while (1) {
				RTC_Get();  //hour,min,sec
        //if (oldSec != sec) {    // Has a second elasped ?
        //    oldSec = sec;       // Update old value

            // Draw seconds indicator
            _drawSecIndicator(sec,SEC_IND_COLOR);

            //if (oldMin != min) {    // Has a min elasped ?
            //    oldMin = min;

                // Draw min and hour hands
                _drawMinHand(min,MIN_HAND_COLOR);
                _drawHourHand(hour, min, HOUR_HAND_COLOR);

                // Redraw numerics in case min hand drew over them
                //drawClockNumerics();
            //}
        //}    

        // See if user has aborted
        if (checkForTermination()) {
            return;
        }

        delay(200);
				_drawSecIndicator(sec,COLOR_BLACK);
				_drawMinHand(min,COLOR_BLACK);
        _drawHourHand(hour, min, COLOR_BLACK);
    }
}


/*
 * 画10条随机线
 */
void radiatingLinesPattern(void) {

    // Pick the attributes of the burst
    int smallRadius = random(2, 5);
    int mediumRadius = random(smallRadius + 4, 13);
    int largeRadius = 15;

    int degreeInc;
	
    int xi=0, xo=0, yi=0, yo=0;
    double rads;
    rgb24 color;
	
    int numberOfSpokes = 360 / degreeInc;
    int colorIndex = 0;
    u8 inner = 0;
    // Pick the delay for this time through
    int delayTime = random(10, 80);

    // Pick the burst spoke pitch
    switch(random(0,4)) {
    case 0:
        degreeInc = 12;
        break;
    case 1:
        degreeInc = 18;
        break;
    case 2:
        degreeInc = 30;
        break;
    case 3:
        degreeInc = 36;
        break;
    }


    numberOfSpokes = 360 / degreeInc;

    while (1) {
				int degree;
        for (degree = 0; degree < 360; degree += degreeInc) {

            // Convert degrees to radians
            rads = ((double) degree)  * PI / 180.0;
						
            xi = smallRadius * cos(rads) + 16;
            yi = smallRadius * sin(rads) + 16;

            if (inner) {
                // Drawing shorter spokes
                xo = mediumRadius * cos(rads) + 16;
                yo = mediumRadius * sin(rads) + 16;
            }
            else  {
                // Drawing longer spokes
                xo = largeRadius * cos(rads) + 16;
                yo = largeRadius * sin(rads) + 16;
            }
            // Toggle inner to outer and vise versa
            inner = ! inner;

            // Create longer spoke color
            color = CreateAHSVColor(numberOfSpokes, colorIndex++, 1.0, 1.0);
						drawLine(xi, yi, xo, yo, 0x00);
            // Draw the spoke
            drawLine(xi, yi, xo, yo, color);
            //matrix.swapBuffers();

            delay(delayTime);
						
        }
        colorIndex += 2;
        // Check for termination
        if (checkForTermination()) {
            return;
        }
    }
}

void rotatingLinesPattern() {
	rgb24 color;
	float hueAngle = 0.0;
	int x,y;
	while(1){
		// Draw diagonal lines from top to bottom, left to right
		for (x = 0; x < 31; x++) {

				// Get a color for the line
				color = CreateHSVColor(hueAngle, 1.0, 1.0);
				hueAngle += 5.0;
				if (hueAngle >= 360.0) {
						hueAngle = 0.0;
				}
				drawLine(x, 0, 31 - x, 31, 0x00);
				drawLine(x, 0, 31 - x, 31, color);
				delay(10);
		}
		// Draw diagonal lines from right to left, top to bottom
		for (y = 0; y < 32; y++) {

				// Get a color for the line
				color = CreateHSVColor(hueAngle, 1.0, 1.0);
				hueAngle += 5.0;
				if (hueAngle >= 360.0) {
						hueAngle = 0;
				}
				drawLine(31, y, 0, 31 - y, 0x00);
				drawLine(31, y, 0, 31 - y, color);
				delay(10);
		}
		// Check for termination
		if (checkForTermination()) {
				return;
		}
	}
}





void Matrix_Text(void)
{
	u8 i;
	LED_BLUE_ON
  delay(30);
	LED_BLUE_OFF
	delay(30);
	LED_BLUE_ON
  delay(30);
	LED_BLUE_OFF
  delay(30);
	ClearBuff(0,1024);
	setFont(font5x7);
	delay(300);
	//drawPixel(0, 0, Color888(255, 255, 255)); 
	delay(100);
	fillScreen(Color888(17, 17, 17));
	delay(100);
	drawRect(0, 0, 32, 32, Color888(255, 255, 0));
	delay(100);
  drawLine(0, 0, 31, 31, Color888(255, 0, 0));
  drawLine(31, 0, 0, 31, Color888(255, 0, 0));
	delay(100);
	drawCircle(7, 7, 7, Color888(0, 0, 255));
	delay(100);
	fillCircle(23, 7, 7, Color888(255, 0, 255));
	delay(100);
	fillScreen(Color888(0, 0, 0));
	ClearBuff(0,1024);
	//fillScreen(0x00101010);
	setFont(font5x7);
	drawString(4,0,Color888(234,23,75),"STM32");
	drawString(4,7,0x00ffffff," RGB ");
	setFont(font3x5);
	drawString(4,14,0x00FF4040,"Matrix");
	delay(100);
	ClearBuff(0,32*32);
	for(i=0;i<4;i++)
	{
		delay(10);
		LED_GREEN_ON
		fillScreen(COLOR_RED);
		delay(50);
		ClearBuff(0,1024);
		fillScreen(COLOR_GREEN);
		delay(50);
		ClearBuff(0,1024);
		fillScreen(COLOR_BLUE);
		delay(50);
		ClearBuff(0,1024);
		LED_GREEN_OFF
	}
	fillScreen(0x00ffffff);
  while(1){
	}
}

// Time and Temperature Display Mode
void timeAndTempMode() {
		DHT11_Data_TypeDef DHT11_Data;    //温度湿度缓冲
		char text[10];
    rgb24 bgColor = COLOR_BLACK;
    rgb24 fgColor = Color888(0, 202, 9);
    rgb24 tempColor = Color888(9, 255, 202);
    ClearBuff(0,1024);
    fillScreen(bgColor);
    //swapBuffers();

    // Setup for scrolling display
    setScrollMode(wrapForward);
    setScrollSpeed(15);
    setScrollFont(font3x5);
    setScrollColor(fgColor);  
    setScrollXY(19); 
    scrollText("", 1);

    while (1) {
        // Get the temperature
				TIM3_Configuration(DISABLE);
				if( Read_DHT11(&DHT11_Data)==SUCCESS){
					sprintf(text,"%d.%dF",DHT11_Data.temp_int,DHT11_Data.temp_deci);
					scrollText(text, 1);}
				TIM3_Configuration(ENABLE);

        // Clear the display
        fillScreen(bgColor);

        // Pick font
        setFont(font6x10);

        // Display temp message
        drawString(4, 0, tempColor, "Temp");
        // Pick font
        setFont(font5x7);
        drawString(5, 12, tempColor, text);
			  RTC_Get();
				sprintf(text," hum %d.%d",DHT11_Data.humi_int,DHT11_Data.humi_deci);
        // Scroll the formatted time and date once
        scrollText(text, 1);
        // Wait a second
				if(checkForTermination())
					return;
    }
}


void ShowTime(void)
{
		char text[10];
    rgb24 fgColor = Color888(0, 202, 202);
    //rgb24 tempColor = Color888(9, 255, 202);
    ClearBuff(0,1024);
    // Setup for scrolling display
    setScrollMode(wrapForward);
    setScrollSpeed(20);
    setScrollFont(font5x7);
	  setScrollbgColor(COLOR_BLACK);
    setScrollColor(fgColor);
    setScrollXY(12); 
	  while(1){
			RTC_Get();
			sprintf(text,"    %d:%d:%d  %d-%d",hour,min,sec,w_month,w_date);
			scrollText(text, 1);
			delay(100);
			if(checkForTermination()){
				setScrollMode(off);
				scrollText("",1);
				return;
			}
		}
}



void Batter(u8 num)
{
	#define x = 10,y = 10;
	drawRect(7,12,18,7,0x00ffffff);
	fillRect(25,13,2,5,0x00ffffff);
	//fillRect(21,2,1,3,0x00ffffff);
  switch(num)
	{
		case 4:
			fillRect(8,13,16,5,0x00555555);
		  break;
		case 3:
			fillRect(8,13,12,5,0x00555555);
		  break;
		case 2:
			fillRect(8,13,8,5,0x00555555);
		  break;
		case 1:
			fillRect(8,13,4,5,0x00ff0000);
		  break;
		default:
			break;
	}
}

void fsin()
{
	float a,b;
	u8 x1,y1;
	drawLine(15,0,15,31,0x00ffffff);
	drawLine(0,15,31,15,0x00ffffff);

	for(a=0;a<(4*3.1415);a+=0.2)  //默认步长0.01
	{
		b = sin(a);
		x1 = 5*a;
		y1 = 16-(5*b+0.5);
		drawPixel(x1, y1, Color888(255, 255, 255)); 
	}
	while(1){
		if(checkForTermination())
			return;
}
}


u8 Lcd_TimeX(unsigned char circle_x,unsigned char Length,unsigned char Angle)
{
   u8 a;
   if((Angle>0) && (Angle<=15))
   {
     a = circle_x + Length * (sin(PI * Angle / 30));    
   }
   else if(Angle > 15 && Angle <= 30)   
   {  
      a = circle_x + Length * cos((PI * Angle) / 30 - (PI / 2 ));
   }
   else if(Angle > 30 && Angle <= 45)
   {
       a = circle_x - Length * sin((PI * Angle) / 30- PI);
   }
   else 
   {
       a = circle_x-Length * cos((PI * Angle) / 30 - ((3 * PI) / 2)); 
   }  
        return a;                       
}


u8 Lcd_TimeY(unsigned char circle_y,unsigned char Length,unsigned char Angle)
{
   u8 y;
   if((Angle>0) && (Angle<=15))
   {  
      y = circle_y - Length * (cos(PI * Angle / 30));    
   }
   else if(Angle > 15 && Angle <= 30)   
   {  
      y = circle_y + Length * sin((PI * Angle) / 30 - (PI / 2 ));
   }
   else if(Angle > 30 && Angle <= 45)
   {
       y = circle_y + Length * cos((PI * Angle) / 30- PI);
   }
   else 
   {
       y = circle_y - Length * sin((PI * Angle) / 30 - ((3 * PI) / 2)); 
   } 
   return y;                       
}


void init_Point_Clock() 
{
      u8 i;
      for(i=0;i<60;i++)
     {
        if((i%5)==0)
       {
				   /* 绘画表盘 */
           drawLine(Lcd_TimeX(16,16,i),Lcd_TimeY(16,16,i),Lcd_TimeX(16,17,i),Lcd_TimeY(16,17,i),0x00ffffff);
       }
    }
}


void Display_Pointer()
{
	ClearBuff(0,1024);
	init_Point_Clock(); //画表盘函数
	//drawClockTics();
	while(1){
		//u32 Color = 0x00008446;//random(0,255)<<16|random(0,255)<<8|random(0,255); //获取随机数函数
		RTC_Get();  //hour,min,sec
		
		/*  画指针 */
		drawLine(Lcd_TimeX(16,12,sec),Lcd_TimeY(16,12,sec),16,16,SEC_IND_COLOR);  //sec指针
		drawLine(Lcd_TimeX(16,8,min),Lcd_TimeY(16,8,min),16,16,MIN_HAND_COLOR);
		drawLine(Lcd_TimeX(16,6,min/10+5*(hour%12)),Lcd_TimeY(16,6,min/10+5*(hour%12)),16,16,HOUR_HAND_COLOR);  
		delay(500);
		/*  清除指针*/
		drawLine(Lcd_TimeX(16,12,sec),Lcd_TimeY(16,12,sec),16,16,0x00);  //sec指针
		drawLine(Lcd_TimeX(16,8,min),Lcd_TimeY(16,8,min),16,16,0x00);
		drawLine(Lcd_TimeX(16,6,min/10+5*(hour%12)),Lcd_TimeY(16,6,min/10+5*(hour%12)),16,16,0x00);  
		if(checkForTermination())
			return;
	}
}



void Display_Demo(void)
{
  u16 a;
	u8 b;
	for(a=0;a<1024;a++)
	{
		for(b=0;b<3;b++){
		  Display_PWM[a][b] = a/4;
		}
	}
}
/*********************************************END OF FILE**********************/
