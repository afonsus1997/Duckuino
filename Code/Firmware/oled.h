#ifndef OLED_h
#define OLED_h
#include <Wire.h>
#include "Cytron_SSD1306.h"
#include "pins.h"

#define OLED_RESET 4




#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

void setupOLED();

void drawSplash();
void drawInfo();
#endif
