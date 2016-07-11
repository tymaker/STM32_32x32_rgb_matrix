
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
#include "VolumeBars.h"
#include "stm32_dsp.h"
#include "table_fft.h"


const int width = 32;
const int height_ = 32;
const int numBars_ = 16;
const int barWidth_ = width/numBars_;

const u16 NPT = 256;
#define PI2 6.28318530717959
#define Fs  44800
long lBufInArray [NPT];
long lBufOutArray[NPT];
long lBufMagArray[NPT];

void InitBufInArray()
{
    unsigned short i;
    float fx;
    for(i=0; i<NPT; i++)
    {
        fx = 1500 * sin(PI2 * i * 350.0 / Fs) +
             2700 * sin(PI2 * i * 8400.0 / Fs) +
             4000 * sin(PI2 * i * 18725.0 / Fs);
        lBufInArray[i] = ((signed short)fx) << 16;
    }
		//cr4_fft_256_stm32(lBufOutArray, lBufInArray, NPT);
		cr4_fft_256_stm32(lBufOutArray, lBufInArray, NPT);
}

void GetPowerMag()
{
    signed short lX,lY;
    float X,Y,Mag;
    unsigned short i;
    for(i=0; i<NPT; i++)
    {
        lX  = (lBufOutArray[i] << 16) >> 16;
        lY  = (lBufOutArray[i] >> 16);
        X = NPT * ((float)lX) / 32768;
        Y = NPT * ((float)lY) / 32768;
        Mag = sqrt(X * X + Y * Y) / NPT;
        if(i == 0)
            lBufMagArray[i] = (unsigned long)(Mag * 32768);
        else
            lBufMagArray[i] = (unsigned long)(Mag * 65536);
				//printf("i=%d\tp=%ld\tMag=%ld\tX=%f\tY=%f\r\n",i,lBufOutArray[i],lBufMagArray[i],X,Y);
    }
}

/*void Printf(void){
	int i;
//	printf("i\tMag\t\r\n");
	for(i=0;i<64;i++){
	  printf("i=%d\tMag=%ld\t\r\n",i,lBufMagArray[i]);
		//if(i/5 == 0)printf("\r\n");
	}
}*/


void VolumeBars_run() {
	int barHeights_[numBars_];
	int barMeans_[numBars_];
	int barFreqs_[numBars_];
	int heightGreen_  = height_*4/12;
	int heightYellow_ = height_*8/12;
	int heightOrange_ = height_*10/12;
//	int heightRed_    = height_*12/12;
	int t_ = 0;
	// Array of possible bar means
	int numMeans = 10;
	int means[10] = {1,2,3,4,5,6,7,8,16,32};
	int i;
	for (i=0; i<numMeans; ++i) {
	  means[i] = height_ - means[i]*height_/8;
	}
	// Initialize bar means randomly
	//srand(time(NULL));
	for (i=0; i<numBars_; ++i) {
	  barMeans_[i] = random(1,8)%numMeans;
	  barFreqs_[i] = 1<<(random(1,2)%3);
	}

	// Start the loop
	while (1) {
	  if (t_ % 8 == 0) {
			// Change the means
			for (i=0; i<numBars_; ++i) {
				barMeans_[i] += random(0,3)%3 - 1;
				if (barMeans_[i] >= numMeans)
				barMeans_[i] = numMeans-1;
				if (barMeans_[i] < 0)
				barMeans_[i] = 0;
			}
	  }

	  // Update bar heights
	  t_++;
	  for (i=0; i<numBars_; ++i) {
			barHeights_[i] = (height_ - means[barMeans_[i]])
				* sin(0.1*t_*barFreqs_[i]) + means[barMeans_[i]];
			if (barHeights_[i] < height_/8)
				barHeights_[i] = random(0,3) % (height_/8) + 1;
			//barHeights_[i] = lBufMagArray[i*2];
	  }

	  for (i=0; i<numBars_; ++i) {
			int y;
			for (y=0; y<barHeights_[i]; ++y) {
				if (y<heightGreen_) {
				drawBarRow(i, y, 0, 200, 0);
				}
				else if (y<heightYellow_) {
				drawBarRow(i, y, 150, 150, 0);
				}
				else if (y<heightOrange_) {
				drawBarRow(i, y, 250, 100, 0);
				}
				else {
				drawBarRow(i, y, 200, 0, 0);
				}
			}
			// Anything above the bar should be black
			for (; y<height_; ++y) {
				drawBarRow(i, y, 0, 0, 0);
			}
	  }
	  //usleep(delay_ms_ * 1000);
		delay(50);
	}
}

void drawBarRow(int bar, uint8_t y, uint8_t r, uint8_t g, uint8_t b) {
	//u32 color = r<<16 | g<<8 | b;
	uint8_t x;
	for (x=bar*barWidth_; x<(bar+1)*barWidth_; ++x) {
		drawPixel(x, 32-1-y, 0x00);
		drawPixel(x, 32-1-y, Color888(r,g,b));
	}
}

/*********************************************END OF FILE**********************/
