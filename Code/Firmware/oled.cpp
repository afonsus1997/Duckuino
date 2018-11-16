
#include "oled.h"
#include "splash.h"

Cytron_SSD1306 oled;

void setupOLED()   {                

  oled.begin();
  //drawSplash();
  delay(100);

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

void drawInfo() {
	//oled.println("Afonso Muralha - 2018");
	//oled.println("github.com/afonsus1997/Duckuino");
	//oled.println("HW: 2.0     SW:0.8");
	oled.drawBitmap(0, 0, info, 128, 32, 1);
	delay(2000);

}



