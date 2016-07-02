/**
  ******************************************************************************
  * @file    stm32f10x_rgb_gfx.c
  * @author  Makt
  * @version V1.0
  * @date    2016-04-04
  * @brief   新的RGB 点阵显示 程序
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
#include <stm32f10x_rgb_gfx.h>


s8 _abs(s8 n)
{
return n * ( (n>>8<<1) +1);
}




// Bresenham's algorithm - thx wikpedia
void drawLine(s8 x0, s8 y0, s8 x1, s8 y1, u32 Color) {
  s8 steep = _abs(y1 - y0) > _abs(x1 - x0);
  s8 ystep, err, dx, dy;

	if (steep) {
    _swap_int8_t(x0, y0);
    _swap_int8_t(x1, y1);
  }

  if (x0 > x1) {
    _swap_int8_t(x0, x1);
    _swap_int8_t(y0, y1);
  }

  dx = x1 - x0;
  dy = _abs(y1 - y0);

  err = dx / 2;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, Color);
    } else {
      drawPixel(x0, y0, Color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}
//  u8 dx,dy,k,b;
//	dx = x1 - x0;
//	dy = y1 - y0;
//	k=dy/dx;
//	b=y0-(x0*k);
//	
//	for(;x0<x1;x0++)
//	{
//	  drawPixel(x0,(x0*k)+b,Color);
//	}


void drawFastVLine(s8 x, s8 y, s8 h, u32 Color) {
  // Update in subclasses if desired!
  drawLine(x, y, x, y+h-1, Color);
}

void drawFastHLine(s8 x, s8 y, s8 w, u32 Color)
{
  // Update in subclasses if desired!
  drawLine(x, y, x+w-1, y, Color);
}

// Draw a rectangle
void drawRect(s8 x, s8 y, s8 w, s8 h, u32 Color) {
  drawFastHLine(x, y, w, Color);
  drawFastHLine(x, y+h-1, w, Color);
  drawFastVLine(x, y, h, Color);
  drawFastVLine(x+w-1, y, h, Color);
}

void fillRect(s8 x, s8 y, s8 w, s8 h,u32 Color) {
  // Update in subclasses if desired!
  s8 i;
	for (i=x; i<x+w; i++) {
    drawFastVLine(i, y, h, Color);
  }
}

// Draw a circle outline
void drawCircle(s8 x0, s8 y0, s8 r, u32 color) {
  s8 f = 1 - r;
  s8 ddF_x = 1;
  s8 ddF_y = -2 * r;
  s8 x = 0;
  s8 y = r;

  drawPixel(x0  , y0+r, color);
  drawPixel(x0  , y0-r, color);
  drawPixel(x0+r, y0  , color);
  drawPixel(x0-r, y0  , color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
  }
}

void drawCircleHelper( s8 x0, s8 y0, s8 r, s8 cornername, u32 Color) {
  s8 f     = 1 - r;
  s8 ddF_x = 1;
  s8 ddF_y = -2 * r;
  s8 x     = 0;
  s8 y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      drawPixel(x0 + x, y0 + y, Color);
      drawPixel(x0 + y, y0 + x, Color);
    }
    if (cornername & 0x2) {
      drawPixel(x0 + x, y0 - y, Color);
      drawPixel(x0 + y, y0 - x, Color);
    }
    if (cornername & 0x8) {
      drawPixel(x0 - y, y0 + x, Color);
      drawPixel(x0 - x, y0 + y, Color);
    }
    if (cornername & 0x1) {
      drawPixel(x0 - y, y0 - x, Color);
      drawPixel(x0 - x, y0 - y, Color);
    }
  }
}

// Used to do circles and roundrects
void fillCircleHelper(s8 x0, s8 y0, s8 r, s8 cornername, s8 delta, u32 Color) {

  s8 f     = 1 - r;
  s8 ddF_x = 1;
  s8 ddF_y = -2 * r;
  s8 x     = 0;
  s8 y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      drawFastVLine(x0+x, y0-y, 2*y+1+delta, Color);
      drawFastVLine(x0+y, y0-x, 2*x+1+delta, Color);
    }
    if (cornername & 0x2) {
      drawFastVLine(x0-x, y0-y, 2*y+1+delta, Color);
      drawFastVLine(x0-y, y0-x, 2*x+1+delta, Color);
    }
  }
}

void fillCircle(s8 x0, s8 y0, s8 r, u32 Color) {
  drawFastVLine(x0, y0-r, 2*r+1, Color);
  fillCircleHelper(x0, y0, r, 3, 0, Color);
}

// Draw a triangle
void drawTriangle(s8 x0, s8 y0, s8 x1, s8 y1, s8 x2, s8 y2, u32 Color) {
  drawLine(x0, y0, x1, y1, Color);
  drawLine(x1, y1, x2, y2, Color);
  drawLine(x2, y2, x0, y0, Color);
}

// Fill a triangle
void fillTriangle(s8 x0, s8 y0, s8 x1, s8 y1, s8 x2, s8 y2, u32 Color) {

  int16_t a, b, y, last;
  int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1;
  int32_t
    sa   = 0,
    sb   = 0;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    _swap_int8_t(y0, y1); _swap_int8_t(x0, x1);
  }
  if (y1 > y2) {
    _swap_int8_t(y2, y1); _swap_int8_t(x2, x1);
  }
  if (y0 > y1) {
    _swap_int8_t(y0, y1); _swap_int8_t(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    drawFastHLine(a, y0, b-a+1, Color);
    return;
  }


  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it

  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) _swap_int8_t(a,b);
    drawFastHLine(a, y, b-a+1, Color);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) _swap_int8_t(a,b);
    drawFastHLine(a, y, b-a+1, Color);
  }
}


// Draw a rounded rectangle
void drawRoundRect(s8 x, s8 y, s8 w, s8 h, s8 r, u32 Color) {
  // smarter version
  drawFastHLine(x+r  , y    , w-2*r, Color); // Top
  drawFastHLine(x+r  , y+h-1, w-2*r, Color); // Bottom
  drawFastVLine(x    , y+r  , h-2*r, Color); // Left
  drawFastVLine(x+w-1, y+r  , h-2*r, Color); // Right
  // draw four corners
  drawCircleHelper(x+r    , y+r    , r, 1, Color);
  drawCircleHelper(x+w-r-1, y+r    , r, 2, Color);
  drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, Color);
  drawCircleHelper(x+r    , y+h-r-1, r, 8, Color);
}

// Fill a rounded rectangle
void fillRoundRect(s8 x, s8 y, s8 w, s8 h, s8 r, u32 Color) {
  // smarter version
  fillRect(x+r, y, w-2*r, h, Color);

  // draw four corners
  fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, Color);
  fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, Color);
}


void fillScreen(u32 Color) {
  fillRect(0, 0, MATRIX_MODULE, MATRIX_MODULE, Color);
}
/*********************************************END OF FILE**********************/
