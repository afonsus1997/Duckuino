
#include "oled.h"
#include "splash.h"

Cytron_SSD1306 oled;

void setupOLED()   {                

  oled.begin();
  delay(2000);

}

void drawSplash(){

  oled.drawBitmap(0, 0, Splash, 128, 32, 1);
  delay(1);

}



