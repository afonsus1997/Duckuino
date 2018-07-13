
#include "oled.h"
#include "splash.h"

Cytron_SSD1306 oled;

void setupOLED()   {                

  oled.begin();
  drawSplash();
  delay(250);

}

void drawSplash(){

  oled.drawBitmap(0, 0, Splash, 128, 32, 1);
  delay(2000);
  oled.clear();
  //oled.println("Firmware v0.1");
  //oled.println("Bootloader v0.1");
  //delay(250);
  oled.clear();
  delay(1);

}



