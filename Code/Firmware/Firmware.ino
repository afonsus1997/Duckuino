
#include "ducky.h";
#include "oled.h";
#include "Menu.h";



void setup()
{
	setupOLED();
	
	duckySetup();
	setupMenu();

	Serial.begin(9600);

}


void loop()
{
	checkHardware();
	delay(100);
}
