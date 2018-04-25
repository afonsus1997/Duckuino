

#include "Keyboard.h"

void setup(){
    Serial.begin(9600);

}

void loop(){
    Serial.println("HELLO WORLD");
    Keyboard.print("TEST");
    delay(1000);

}