/**
  ******************************************************************************
  * @file    main.c
  * @author  Makt
  * @version V1.0
  * @date    2016-04-04
  * @brief   Maktrix µãÕóÏÔÊ¾³ÌÐò
  ******************************************************************************
  * @attention
	*
  ******************************************************************************
  */
#include "SnakeGame.h"
#include "stm32f10x_rgb_matrix.h"


void reset(void) {
	int x,y;
  // Clear screen
  fillScreen(COLOR_BLACK);

  score = 0;
  sprintf(scoreText, "%d", score);

  newApple();

  segmentCount = 4;
  segmentIncrement = 4;
  segmentIncrementMultiplier = 1;


  x = 16;
  y = 16;

  direction = RIGHT;

  drawPixel(snakeHead.x, snakeHead.y, COLOR_GREEN);
}

void newApple(void) {
  while (1) {
    apple.x = random(5, 32);
    apple.y = random(5, 32);

    u32 color = readPixel(apple.x, apple.y);
    if (RGB24_ISEQUAL(color, COLOR_BLACK))
      break;
  }

  drawPixel(apple.x, apple.y, COLOR_RED);
}

void setup(void) {
  isPaused = -1;

  randomSeed(analogRead(5));

  // Turn off any text scrolling
  scrollText("", 1);
  setScrollMode(off);

  //setColorCorrection(cc24);

  // Fonts are font3x5, font5x7, font6x10, font8x13
  setFont(font3x5);

  screenWidth = getScreenWidth();
  screenHeight = getScreenHeight();

  reset();
}

void update(void) {
  if (millis() - lastMillis >= moveSpeed)
  {
    Point newSnakeHead;
    newSnakeHead.x = snakeHead.x;
    newSnakeHead.y = snakeHead.y;

    // move the snake
    switch (direction)
    {
    case UP:
      newSnakeHead.y--;
      break;
    case DOWN:
      newSnakeHead.y++;
      break;
    case LEFT:
      newSnakeHead.x--;
      break;
    case RIGHT:
      newSnakeHead.x++;
      break;
    }

    // wrap the snake if it hits the edge of the screen (for now)
    if (newSnakeHead.x >= screenWidth) {
      newSnakeHead.x = 0;
    }
    else if (newSnakeHead.x < 0) {
      newSnakeHead.x = screenWidth - 1;
    }

    if (newSnakeHead.y >= screenHeight) {
      newSnakeHead.y = 5;
    }
    else if (newSnakeHead.y < 5) {
      newSnakeHead.y = screenHeight - 1;
    }

    rgb24 color = readPixel(newSnakeHead.x, newSnakeHead.y);
    if (RGB24_ISEQUAL(color, COLOR_GREEN)) {
      // snake ate itself
      die();
    }

    segments.enqueue(newSnakeHead);

    // draw the new location for the snake head
    drawPixel(newSnakeHead.x, newSnakeHead.y, COLOR_GREEN);

    if (newSnakeHead.x == apple.x && newSnakeHead.y == apple.y) {
      segmentCount += segmentIncrement * segmentIncrementMultiplier;

      score++;
      sprintf(scoreText, "%d", score);

      if (segmentCount > maxSegmentCount) {
        segmentCount = maxSegmentCount;
      }
      newApple();
    }

    // trim the end of the snake if it gets too long
    while (segments.count() > segmentCount) {
      Point oldSnakeSegment = segments.dequeue();
      drawPixel(oldSnakeSegment.x, oldSnakeSegment.y, COLOR_BLACK);
    }

    snakeHead = newSnakeHead;

    lastMillis = millis();
  }
}

void die(void) {
  delay(1000);
  reset();
}

void draw(void) {
  // draw score
  fillRectangle(0, 0, 31, 4, COLOR_DDGRAY);
  drawString(0, 0, COLOR_WHITE, scoreText);

}

void run(void) {

  setup();

  while (1) {

    //if (input == IRCODE_HOME)
    //  return;

    if (!isPaused) {
      update();
    }

    draw();
  }
}

