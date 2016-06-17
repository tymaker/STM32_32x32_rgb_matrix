/**
  ******************************************************************************
  * @file    stm32f10x_rgb_ColorHSV.c
  * @author  Makt
  * @version V1.0
  * @date    2016-04-04
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
#include "stm32f10x_rgb_ColorHSV.h"


// HSV to RGB color conversion
// Input arguments
// hue in degrees (0 - 360.0)
// saturation (0.0 - 1.0)
// value (0.0 - 1.0)
// Output arguments
// red, green blue (0.0 - 1.0)
void hsvToRGB(float hue, float saturation, float value, float * red, float * green, float * blue) {

    int i;
    float f, p, q, t;

    if (saturation == 0) {
        // achromatic (grey)
        *red = *green = *blue = value;
        return;
    }
    hue /= 60;                  // sector 0 to 5
    i = floor(hue);
    f = hue - i;                // factorial part of h
    p = value * (1 - saturation);
    q = value * (1 - saturation * f);
    t = value * (1 - saturation * (1 - f));
    switch (i) {
    case 0:
        *red = value;
        *green = t;
        *blue = p;
        break;
    case 1:
        *red = q;
        *green = value;
        *blue = p;
        break;
    case 2:
        *red = p;
        *green = value;
        *blue = t;
        break;
    case 3:
        *red = p;
        *green = q;
        *blue = value;
        break;
    case 4:
        *red = t;
        *green = p;
        *blue = value;
        break;
    default:
        *red = value;
        *green = p;
        *blue = q;
        break;
    }
}

// Create a HSV color
rgb24 CreateHSVColor(float hue, float saturation,  float value) {

    float r, g, b;
    rgb24 color;

    hsvToRGB(hue, saturation, value, &r, &g, &b);

    color   = (u32)(r * MAX_COLOR_VALUE)<<16;
    color = color | ((u32)(g * MAX_COLOR_VALUE) <<8); 
    color = color | (u32)(b * MAX_COLOR_VALUE) ;
	
	  //color = color <<16;
    return color;
}

// Create an HSV color
rgb24 CreateHSV_Color(int divisions, int index, float saturation, float value) {

    float hueAngle = (360.0 * index) / divisions;
    return CreateHSVColor(hueAngle, saturation, value);
}

// Create an HSV color
rgb24 CreateAHSVColor(int divisions, int index, float saturation, float value) {

    index %= divisions;
    return CreateHSV_Color(divisions, index, saturation, value);
}

rgb24 CreateHSVColorWithDivisions(int divisions, int index) {

    return CreateAHSVColor(divisions, index, 1.0, 1.0);
}


/*********************************************END OF FILE**********************/
