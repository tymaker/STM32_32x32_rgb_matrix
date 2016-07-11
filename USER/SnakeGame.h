#ifndef SnakeGame_H
#define SnakeGame_H

#include "stm32f10x_rgb_Types.h"
#include "stm32f10x_rgb_Colors.h"

int score;
enum DIRECTION {
	UP, DOWN, LEFT, RIGHT
} direction = RIGHT;
char scoreText[8];
struct Point {
	int16_t x;
	int16_t y;
} snakeHead,apple;

int16_t screenWidth;
int16_t screenHeight;
char positionBuffer[5]; // XX,YY
s8 isPaused = 0;
int segmentCount = 1;
int maxSegmentCount = 1024;
int segmentIncrement = 1;
int segmentIncrementMultiplier = 1;

unsigned long lastMillis = 0;
int moveSpeed = 150;

void reset(void);
void newApple(void);
void setup(void);
//unsigned long handleInput(IRrecv &irReceiver);
void update(void);
void die(void);
void draw(void);
//void run(IRrecv &irReceiver);


#endif

/******************* (C) COPYRIGHT 2016 Makt *****END OF FILE****/
