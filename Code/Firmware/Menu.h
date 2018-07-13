#pragma once

#ifndef MENU_h
#define MENU_h

#include <MenuSystem.h>
#include "oled.h";
#include "pins.h";
extern Cytron_SSD1306 oled;

void setupMenu();

void checkHardware();

#endif