#ifndef DUCKY_h
#define DUCKY_h

#define buffersize 128

#define KEYPAD_0 234
#define KEYPAD_1 225
#define KEYPAD_2 226
#define KEYPAD_3 227
#define KEYPAD_4 228
#define KEYPAD_5 229
#define KEYPAD_6 230
#define KEYPAD_7 231
#define KEYPAD_8 232
#define KEYPAD_9 233
#define KEYPAD_ASTERIX 221
#define KEYPAD_ENTER 224
#define KEYPAD_MINUS 222
#define KEYPAD_PERIOD 235
#define KEYPAD_PLUS 223
#define KEYPAD_SLASH 220
#define PRINTSCREEN 206

//#include "Keyboard_PT.h"
//#include <Keyboard.h>
#include "Mouse.h"
#include <SPI.h>
#include <SD.h>
#include "pins.h"
#include "oled.h"
extern Cytron_SSD1306 oled;


int getSpace(int start, int end);

bool equals(char* strA, int start, int end, char* strB, int strLen);

int toPositive(int num);

bool equalsBuffer(int start, int end, char* str);

int getInt(char* str, int pos);

void KeyboardWrite(uint8_t c);

void runLine();

void runCommand(int s, int e);

void duckySetup();

void runDucky();

#endif
