#ifndef SCREEN_LIB

#include "lcd5110.h"
#include "math.h"

#define SCREEN_LIB

LCD5110_display lcd1;


void LCD_INIT();
void LCD_PRINT_UI();
double scale_distance(double dist);
void u_LCD_DRAWPOINT(double angle, double distance);

#endif
