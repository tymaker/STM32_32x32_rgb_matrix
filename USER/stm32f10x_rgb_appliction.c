/**
  ******************************************************************************
  * @file    stm32f10x_rgb_application.c
  * @author  Makt
  * @version V1.0
  * @date    2016-04-04
  * @brief   新的RGB 应用
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
#include "stm32f10x_rgb_appliction.h"

extern const u8 Image6[];
extern const u8 Image5[];


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
	const s8 cent_x = MATRIX_MODULE / 2;
	const s8 cent_y = MATRIX_MODULE / 2;

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
		delay(15);
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
		if(checkForTermination()){
			ClearBuff(0,1024);
			break;
		}
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
						ClearBuff(0,1024);
            break;
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
						ClearBuff(0,1024);
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
			  ClearBuff(0,1024);
				break;
		}
	}
}





void Matrix_Text(void)
{
	u8 i;
	LED_BLUE_ON;
  delay(100);
	LED_BLUE_OFF;
	delay(100);
	LED_BLUE_ON;
  delay(100);
	LED_BLUE_OFF;
  delay(100);
	LED_GREEN_ON;
	ClearBuff(0,1023);
	setFont(font5x7);
	delay(300);
	//drawPixel(0, 0, Color888(255, 255, 255)); 
	setFont(font5x7);
	drawString(4,0,Color888(234,23,75),"STM32");
	drawString(4,7,0x00ffffff," RGB ");
	setFont(font3x5);
	drawString(4,14,0x00FF4040,"Matrix");
	drawString(4,20,0x00FF4040," test ");
	delay(2000);
	ClearBuff(0,1023);	
	fillScreen(Color888(17, 17, 17));
	delay(500);
	drawRect(0, 0, 32, 32, Color888(255, 255, 0));
	delay(500);
  drawLine(0, 0, 31, 31, Color888(255, 0, 0));
  drawLine(31, 0, 0, 31, Color888(255, 0, 0));
	delay(500);
	drawCircle(7, 7, 7, Color888(0, 0, 255));
	delay(500);
	fillCircle(23, 7, 7, Color888(255, 0, 255));
	delay(500);
	fillScreen(Color888(0, 0, 0));
	ClearBuff(0,1023);
	for(i=0;i<2;i++)
	{
		delay(500);
		LED_GREEN_ON;
		fillScreen(COLOR_RED);
		delay(500);
		ClearBuff(0,1023);
		fillScreen(COLOR_GREEN);
		delay(500);
		ClearBuff(0,1023);
		fillScreen(COLOR_BLUE);
		delay(500);
		ClearBuff(0,1023);
		LED_GREEN_OFF;
	}
	for(i=0;i<255;i+=5){
		ClearBuff(0,1024);
		fillScreen(Color888(i,0,0));
		delay(200);
	}
	for(i=0;i<255;i+=5){
		ClearBuff(0,1024);
		fillScreen(Color888(0,i,0));
		delay(200);
	}
	for(i=0;i<255;i+=5){
		ClearBuff(0,1024);
		fillScreen(Color888(0,0,i));
		delay(200);
	}
	fillScreen(0x00ffffff);
	LED_GREEN_OFF;
  delay(3000);
	SystemReset();
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

void TempMode(void){
	char text[8],text1[8];
	DHT11_Data_TypeDef DHT11_Data;    //温度湿度缓冲
	drawImage(0,0,COLOR_YELLOW,Image5);
	drawImage(0,16,COLOR_RED,Image6);
	while(1){
		TIM3_Configuration(DISABLE);
		if( Read_DHT11(&DHT11_Data)==SUCCESS){
			sprintf(text,"%d.%dC",DHT11_Data.temp_int,DHT11_Data.temp_deci);
			sprintf(text1,"%d.%dH",DHT11_Data.humi_int,DHT11_Data.humi_deci);
		}
		else{
			sprintf(text,"Error");
			sprintf(text1,"Error");
		}
		TIM3_Configuration(ENABLE);
		setFont(font5x7);
		drawString(8,5,Color888(80,80,80),text);
		drawString(8,21,Color888(80,80,80),text1);
		delay(2000);
		drawString(8,5,0x00,text);
		drawString(8,21,0x00,text1);

		//drawString(8,5,0x00,"       ");
		//drawString(8,21,0x00,"      ");
		if(checkForTermination()){
			ClearBuff(0,1024);
			break;
		}
	}
}

void ShowTime(void)
{
		char text[20];
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
			sprintf(text,"      %02d:%02d:%02d  %02d-%0d",hour,min,sec,w_month,w_date);
			scrollText(text, 1);
			delay(100);
			if(checkForTermination()){
				setScrollMode(off);
				scrollText("",1);
				ClearBuff(0,1024);
				break;
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
		drawPixel(x1, y1, Color888(255, 0, 0)); 
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
		if(checkForTermination()){
			ClearBuff(0,1024);
			break;
		}
	}
}

// Open Sign Mode
void openSignMode() {

    u8 textMode = 0;
	  u32 bgColor = Color888(0,30,30);
    fillScreen(bgColor);

    // Setup for scrolling mode
    setScrollMode(wrapForward);
    setScrollSpeed(10);
    setScrollFont(font6x10);
    setScrollColor(COLOR_GREEN);
	  setScrollXY(22);
	  //setScrollbgColor(0x00003030);
    scrollText(OPEN_MSG, -1);

    setFont(font8x13);


    while (1) {

        // First clear the string area
			  ClearBuff(0,1024);
        drawString(0, 3, bgColor, "OPEN");
        switch (textMode) {

        case 0:
					  //ClearBuff(0,1024);
            drawString(0, 3, COLOR_WHITE, "O");
            break;

        case 1:
					  //ClearBuff(0,1024);
            drawString(0, 3, COLOR_WHITE, "OP");
            break;

        case 2:
					  //ClearBuff(0,1024);
            drawString(0, 3, COLOR_WHITE, "OPE");
            break;

        case 3:
					  //ClearBuff(0,1024);
            drawString(0, 3, COLOR_WHITE, "OPEN");
            break;

        case 4:
					  //ClearBuff(0,1024);
            drawString(0, 3, bgColor, "OPEN");
            break;
        }
        textMode++;
        if (textMode >= 5) {
            textMode = 0;
        }

        //swapBuffers();
        Delay_us(100);
				
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

void show_Image(const u8 *image)
{
		u8 i, j;
		for(j=0;j<32;j++){
			for(i=0;i<32;i++){
				//drawPixel(i,j,Color888(IMAGE[j*32+i],IMAGE[j*32+i+1],IMAGE[j*32+i+2]));
			drawPixel(i,j,((u32)image[j*32+i] << 16) | ((u32)image[j*32+i+1]<<8) | ((u32)image[j*32+i+2]));}
		}
}

void show_PWM(){
  u8 a;
	while(1){
		for(a=0;a<255;a+=5){
			ClearBuff(0,1024);
			fillScreen(Color888(a,0,0));
			delay(200);
		}
		for(a=0;a<255;a+=5){
			ClearBuff(0,1024);
			fillScreen(Color888(0,a,0));
			delay(200);
		}
		for(a=0;a<255;a+=5){
			ClearBuff(0,1024);
			fillScreen(Color888(0,0,a));
			delay(200);
		}
	}
}

// Create a HSV color
rgb24 createHSVColor(float hue, float saturation,  float value) {

    float r, g, b;
    rgb24 color;

    hsvToRGB(hue, saturation, value, &r, &g, &b);

    color = (u32)(r * MAX_COLOR_VALUE)<<16;
    color = color | ((u32)(g * MAX_COLOR_VALUE) <<8); 
    color = color | (u32)(b * MAX_COLOR_VALUE) ;

    return color;
}

void welcomePattern() {

    rgb24 color;
    float hueAngle = 0.0;
		int i;
    // Write welcome message
    setScrollColor(COLOR_WHITE);
    setScrollMode(wrapForward);
    setScrollSpeed(10);
    setScrollFont(font6x10);
    setScrollOffsetFromEdge(11);
    scrollText("Welcome  ~#%*%#~", 1);

    while (1) {

        // Get a color for the line
        color = createHSVColor(hueAngle, 1.0, 1.0);
        hueAngle += 15.0;
        if (hueAngle >= 360.0) {
            hueAngle = 0.0;
        }

        // Draw diagonal lines on left
        for (i = 0; i < 32; i++) {
					  drawLine(0, i, i, 31, 0x00);
            drawLine(0, i, i, 31, color);
            //swapBuffers();
            delay(50);
        }

        // Get a color for the line
        color = createHSVColor(hueAngle, 1.0, 1.0);
        hueAngle += 15.0;
        if (hueAngle >= 360.0) {
            hueAngle = 0.0;
        }
        // Draw diagonal lines on bottom
        for (i = 0; i < 32; i++) {
					  drawLine(i, 31, 31, 31 - i, 0x00);
            drawLine(i, 31, 31, 31 - i, color);
            //swapBuffers();
            delay(50);
        }

        // Get a color for the line
        color = createHSVColor(hueAngle, 1.0, 1.0);
        hueAngle += 15.0;
        if (hueAngle >= 360.0) {
            hueAngle = 0.0;
        }

        // Draw diagonal lines on right
        for (i = 0; i < 32; i++) {
					  drawLine(31, 31 - i, 31 - i, 0, 0x00);
            drawLine(31, 31 - i, 31 - i, 0, color);
            //swapBuffers();
            delay(50);
        }

        // Get a color for the line
        color = createHSVColor(hueAngle, 1.0, 1.0);
        hueAngle += 15.0;
        if (hueAngle >= 360.0) {
            hueAngle = 0.0;
        }
        // Draw diagonal lines on top
        for (i = 0; i < 32; i++) {
					  drawLine(31 - i, 0, 0, i, 0x00);
            drawLine(31 - i, 0, 0, i, color);
            //swapBuffers();
            delay(50);
        }

        // Test for termination
        if (checkForTermination()) {
					  ClearBuff(0,1024);
            break;
        }
    }
}

void randomCirclesPattern() {

    float hue, val;
    rgb24 color;
    int xc, yc, radius, count;

    while (1) {
        // Clear the screen
        fillScreen(COLOR_BLACK);

        // Pick a random clear count
        count = random(10, 50);

        while (count-- >= 0) {

            hue = random(0,360);
            val = ((float) random(30, 100)) / 100.0;
            color = createHSVColor(hue, 1.0,  val);

            xc = random(1,32);
            yc = random(1,32);
            radius = random(1,16);
            drawCircle(xc, yc, radius, 0x00);
            drawCircle(xc, yc, radius, color);

            //swapBuffers();

            // Check for termination
            if (checkForTermination()) {
							  ClearBuff(0,1024);
                return;
            }
            delay(250);
        }
    }
}

void wwssaabb(void){
	
	u8 X,Y;
	u8 r,g,b;
	while(1){
  // Draw top half
  for (X=0; X < 32; X++) {      
    for (Y=0; Y < 8; Y++) {  
			drawPixel(X, Y, 0x00);
      drawPixel(X, Y, Color888(r, g, b));
      r++;
      if (r == 8) {
        r = 0;
        g++;
        if (g == 8) {
          g = 0;
          b++;
        }
      }
    }
  }

  // Draw bottom half
  for (X=0; X < 32; X++) {      
    for (Y=8; Y < 16; Y++) {  
			drawPixel(X, Y, 0x00);
      drawPixel(X, Y, Color888(r, g, b));
      r++;
      if (r == 8) {
        r = 0;
        g++;
        if (g == 8) {
          g = 0;
          b++;
        }
      }
    }
  }
	}
}

void bba(void){
  // Bounce three balls around
	u8 i;
	int8_t ball[3][4] = {
		{  3,  0,  1,  1 }, // Initial X,Y pos & velocity for 3 bouncy balls
		{ 17, 15,  1, -1 },
		{ 27,  4, -1,  1 }
	};
	
	u32 ballcolor[3] = {
  0x000000ff, // Green=1
  0x0000ff00, // Blue=1
  0x00ff0000  // Red=1
	};
  while(1){
		for(i=0; i<3; i++) {
			// Draw 'ball'
			fillCircle(ball[i][0], ball[i][1], 4, ballcolor[i]);
			delay(10);
			fillCircle(ball[i][0], ball[i][1], 4, 0x00);
			// Update X, Y position
			ball[i][0] += ball[i][2];
			ball[i][1] += ball[i][3];
			// Bounce off edges
			if((ball[i][0] == 0) || (ball[i][0] == (32 - 1)))
				ball[i][2] *= -1;
			if((ball[i][1] == 0) || (ball[i][1] == (16 - 1)))
				ball[i][3] *= -1;
		}
	}
}

void aabbcc(void){
	ClearBuff(0,1023);
	setFont(font6x10);
	drawChar( 0,0,Color888(7,0,0),'3');
	drawChar( 6,0,Color888(7,4,0),'2');
	drawChar(12,0,Color888(7,7,0),'x');
	drawChar(18,0,Color888(4,7,0),'3');
	drawChar(24,0,Color888(0,7,0),'2');
	
	drawChar( 0,10,Color888(0,7,7),'*');
	drawChar( 6,10,Color888(0,4,7),'R');
	drawChar(12,10,Color888(0,0,7),'G');
	drawChar(18,10,Color888(4,0,7),'B');
	drawChar(24,10,Color888(7,0,4),'*');
	while(1);
}


/*********************************************END OF FILE**********************/
