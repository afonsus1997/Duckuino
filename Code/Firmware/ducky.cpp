#include "ducky.h"
#include "Keyboard_PT.h"
#include <EEPROM.h>
//#include <Keyboard.h>
//#include "Mouse.h"
//#define debug
File payload;

char* buf = malloc(sizeof(char)*buffersize);
char* repeatBuffer = malloc(sizeof(char) * 12);

int keystatus = 0;
int eeaddr = 0;
int ispt = 0;
int delay_val;
int bufSize = 0;
int defaultDelay = 5;
int defaultCharDelay = 5;
bool ledOn = true;
int rMin = -100;
int rMax = 100;

char *cmd;
char *test;


int getSpace(int start, int end) {
	for (int i = start; i<end; i++) {
		if (buf[i] == ' ') return i;
	}
	return -1;
}

bool equals(char* strA, int start, int end, char* strB, int strLen) {
	if (end - start != strLen) return false;
	for (int i = 0; i<strLen; i++) {
		if (strA[start + i] != strB[i]) return false;
	}
	return true;
}

int toPositive(int num) {
	if (num < 0) return num * (-1);
	else return num;
}

bool equalsBuffer(int start, int end, char* str) { return equals(buf, start, end, str, String(str).length()); }

int getInt(char* str, int pos) {
	if (equals(str, pos + 1, pos + 7, "RANDOM", 6)) {
		return random(rMin, rMax);
	}
	else {
		return String(str).substring(pos + 1, pos + 6).toInt();
	}
}

void KeyboardWrite(uint8_t c) {
	Keyboard.press(c);
	delay(defaultCharDelay);
	Keyboard.release(c);
}

void KeyboardWrite_pt(uint8_t c) {
	Keyboard.press_pt(c);
	delay(defaultCharDelay);
	Keyboard.release_pt(c);
}




void runLine() {
#ifdef debug
	Serial.println("run: '" + String(buf).substring(0, bufSize) + "' (" + (String)bufSize + ")");
#endif
	int space = getSpace(0, bufSize);
	
	Serial.print("LINE:");  Serial.println(buf);
	oled.clear();
	oled.println("====== RUNNING ======"); oled.println(); oled.print(buf);

	char *arg;
	char *newArray = buf;


	cmd = strtok(buf, " ");



	if (space == -1) runCommand(0, bufSize);
	else {
		if (equalsBuffer(0, space, "DEFAULTDELAY") || equalsBuffer(0, space, "DEFAULT_DELAY")) defaultDelay = getInt(buf, space);
		else if (equalsBuffer(0, space, "DEFAULTCHARDELAY") || equalsBuffer(0, space, "DEFAULT_CHAR_DELAY")) defaultCharDelay = getInt(buf, space);
		else if (equals(buf, 0, space, "DELAY", strlen("DELAY"))) {
			cmd = strtok(NULL, " ");
			delay_val = atoi(cmd);

			//oled.println("DELAY"); oled.println(delay_val);
			delay(delay_val);

		}
		else if (equals(buf, 0, space, "STRING", strlen("STRING"))) {
			//oled.println("STRING");
			for (int i = space + 1; i < bufSize; i++) { if (ispt) { KeyboardWrite_pt(buf[i]); } else  KeyboardWrite(buf[i]);
			}
		}


		else if (equalsBuffer(0, space, "MOUSE")) {
			int nSpace = getSpace(space + 1, bufSize);
			int x = getInt(buf, space);
			int y = getInt(buf, nSpace);
			Mouse.move(x, y);
#ifdef debug
			Serial.println("Move mouse " + (String)x + " " + (String)y);
#endif
		}
		else if (equalsBuffer(0, space, "SCROLL")) Mouse.move(0, 0, getInt(buf, space));
		else if (equalsBuffer(0, space, "RANDOMMIN")) rMin = getInt(buf, space);
		else if (equalsBuffer(0, space, "RANDOMMAX")) rMax = getInt(buf, space);
		else if (equalsBuffer(0, space, "REM") || equalsBuffer(0, space, "REPEAT")) {}
		else {
			//runCommand(0, space);
			//for (int k=0; k < bufSize; k++) { oled.print(char(buf[k])); } 
			int nSpace;


			while (cmd != NULL) {

				runCommand(0, 0);
				cmd = strtok('\0', " \n");


			}
		}
	}

	Keyboard.releaseAll();
	delay(defaultDelay);
}

int checkKey() {
	if (strcmp(cmd, "ENTER") == 0) { Keyboard.press(KEY_RETURN); return 1; }
	else if (strcmp(cmd, "GUI") == 0) { Keyboard.press(KEY_LEFT_GUI); return 1; }//Keyboard.press(KEY_LEFT_GUI);
	else if (strcmp(cmd, "SHIFT") == 0) { Keyboard.press(KEY_LEFT_SHIFT); return 1; }
	else if (strcmp(cmd, "ALT") == 0 || strcmp(cmd, "ALT_LEFT") == 0 || strcmp(cmd, "ALTLEFT") == 0) { Keyboard.press(KEY_LEFT_ALT); return 1; }
	else if (strcmp(cmd, "ALT_RIGHT") == 0 || strcmp(cmd, "ALTRIGHT") == 0) { Keyboard.press(KEY_RIGHT_ALT); return 1; }
	else if (strcmp(cmd, "CTRL") == 0 || strcmp(cmd, "CONTROL") == 0) { Keyboard.press(KEY_LEFT_CTRL); return 1; }
	else if (strcmp(cmd, "CAPSLOCK") == 0) { Keyboard.press(KEY_CAPS_LOCK); return 1; }
	else if (strcmp(cmd, "DELETE") == 0) { Keyboard.press(KEY_DELETE); return 1; }
	else if (strcmp(cmd, "END") == 0) { Keyboard.press(KEY_END); return 1; }
	else if (strcmp(cmd, "ESC") == 0 || strcmp(cmd, "ESCAPE") == 0) {Keyboard.press(KEY_ESC);return 1;}
	else if (strcmp(cmd, "HOME") == 0) { Keyboard.press(KEY_HOME); return 1; return 1; }
	else if (strcmp(cmd, "INSERT") == 0) { Keyboard.press(KEY_INSERT); return 1; }
	else if (strcmp(cmd, "PAGEUP") == 0) {Keyboard.press(KEY_PAGE_UP);return 1;}
	else if (strcmp(cmd, "PAGEDOWN") == 0) { Keyboard.press(KEY_PAGE_DOWN); return 1; }
	else if (strcmp(cmd, "SPACE") == 0) { Keyboard.press(' '); return 1; }
	else if (strcmp(cmd, "TAB") == 0) { Keyboard.press(KEY_TAB); return 1; }
	else if (strcmp(cmd, "BACKSPACE") == 0) { Keyboard.press(KEY_BACKSPACE); return 1; }

	if (strcmp(cmd, "UP") == 0 || strcmp(cmd, "UPARROW") == 0) { Keyboard.press(KEY_UP_ARROW); return 1; }
	else if (strcmp(cmd, "DOWN") == 0 || strcmp(cmd, "DOWNARROW") == 0) { Keyboard.press(KEY_DOWN_ARROW); return 1; }
	else if (strcmp(cmd, "LEFT") == 0 || strcmp(cmd, "LEFTARROW") == 0) { Keyboard.press(KEY_LEFT_ARROW); return 1; }
	//else if (strcmp(cmd, "RIGHT") == 0 || strcmp(cmd, "RIGHTARROW") == 0) {Keyboard.press(KEY_RIGHT_ARROW); return 1;}

	//else if (strcmp(cmd, "PRINTSCREEN") == 0) { Keyboard.press(PRINTSCREEN); return 1; }
	
	else return 0;

}

int checkF() {
	if (strcmp(cmd, "F1") == 0) { Keyboard.press(KEY_F1); return 1; }
	
	else if (strcmp(cmd, "RIGHT") == 0 || strcmp(cmd, "RIGHTARROW") == 0) {Keyboard.press(KEY_RIGHT_ARROW); return 1;}

	else if (strcmp(cmd, "PRINTSCREEN") == 0) { Keyboard.press(PRINTSCREEN); return 1; }

	
	
	else if (strcmp(cmd, "F2") == 0) { Keyboard.press(KEY_F2); return 1; }
	else if (strcmp(cmd, "F3") == 0) { Keyboard.press(KEY_F3); return 1; }
	else if (strcmp(cmd, "F4") == 0) { Keyboard.press(KEY_F4); return 1; }
	else if (strcmp(cmd, "F5") == 0) { Keyboard.press(KEY_F5); return 1; }
	else if (strcmp(cmd, "F6") == 0) { Keyboard.press(KEY_F6); return 1; }
	else if (strcmp(cmd, "F7") == 0) { Keyboard.press(KEY_F7); return 1; }
	else if (strcmp(cmd, "F8") == 0) { Keyboard.press(KEY_F8); return 1; }
	else if (strcmp(cmd, "F9") == 0) { Keyboard.press(KEY_F9); return 1; }
	else if (strcmp(cmd, "F10") == 0) { Keyboard.press(KEY_F10); return 1; }
	else if (strcmp(cmd, "F11") == 0) { Keyboard.press(KEY_F11); return 1; }
	else if (strcmp(cmd, "F12") == 0) { Keyboard.press(KEY_F12); return 1; }
	else return 0;
}

int checkNUM() {
	if (strcmp(cmd, "NUM_0") == 0) {KeyboardWrite(KEYPAD_0); return 1; }
	else if (strcmp(cmd, "NUM_1") == 0) {KeyboardWrite(KEYPAD_1); return 1; }
	else if (strcmp(cmd, "NUM_2") == 0) {KeyboardWrite(KEYPAD_2); return 1; }
	else if (strcmp(cmd, "NUM_3") == 0) {KeyboardWrite(KEYPAD_3); return 1; }
	else if (strcmp(cmd, "NUM_4") == 0) {KeyboardWrite(KEYPAD_4); return 1; }
	else if (strcmp(cmd, "NUM_5") == 0) {KeyboardWrite(KEYPAD_5); return 1; }
	else if (strcmp(cmd, "NUM_6") == 0) {KeyboardWrite(KEYPAD_6); return 1; }
	else if (strcmp(cmd, "NUM_7") == 0) {KeyboardWrite(KEYPAD_7); return 1; }
	else if (strcmp(cmd, "NUM_8") == 0) {KeyboardWrite(KEYPAD_8); return 1; }
	else if (strcmp(cmd, "NUM_9") == 0) {KeyboardWrite(KEYPAD_9); return 1; }
	else if (strcmp(cmd, "NUM_ASTERISK") == 0) {KeyboardWrite(KEYPAD_ASTERIX); return 1; }
	else if (strcmp(cmd, "NUM_ENTER") == 0) {KeyboardWrite(KEYPAD_ENTER); return 1; }
	else if (strcmp(cmd, "NUM_MINUS") == 0) {KeyboardWrite(KEYPAD_MINUS); return 1; }
	else if (strcmp(cmd, "NUM_PERIOD") == 0) {KeyboardWrite(KEYPAD_PERIOD); return 1; }
	else if (strcmp(cmd, "NUM_PLUS") == 0) {KeyboardWrite(KEYPAD_PLUS); return 1; }
	else return 0;

}

int checkMOUSE() {
	if (strcmp(cmd, "CLICK") == 0 || strcmp(cmd, "CLICK_LEFT") == 0 || strcmp(cmd, "MOUSE_CLICK") == 0) {Mouse.click(); return 1; }
	else if (strcmp(cmd, "CLICK_RIGHT") == 0) {Mouse.click(MOUSE_RIGHT); return 1; }
	else if (strcmp(cmd, "CLICK_MIDDLE") == 0) {Mouse.click(MOUSE_MIDDLE); return 1; }

	else if (strcmp(cmd, "PRESS") == 0 || strcmp(cmd, "PRESS_LEFT")) {Mouse.press(); return 1; }
	else if (strcmp(cmd, "PRESS_LEFT") == 0) {Mouse.press(MOUSE_RIGHT); return 1; }
	else if (strcmp(cmd, "PRESS_MIDDLE") == 0) {Mouse.press(MOUSE_MIDDLE); return 1; }
	else if (strcmp(cmd, "RELEASE") == 0 || strcmp(cmd, "RELEASE_LEFT") == 0) {Mouse.release(); return 1; }
	else if (strcmp(cmd, "RELEASE_LEFT") == 0) {Mouse.release(MOUSE_RIGHT); return 1; }
	else if (strcmp(cmd, "RELEASE_MIDDLE") == 0) {Mouse.release(MOUSE_MIDDLE); return 1; }
	else return 0;
}

void runCommand(int s, int e) {



#ifdef debug 
	Serial.println("Press '" + String(buf).substring(s, e) + "'");
#endif
	Serial.print("CMD:"); Serial.println(cmd);
	Serial.print("Len:"); Serial.print(strlen(cmd)); Serial.print(" "); Serial.print(strcmp("GUI", cmd)); Serial.print(strcmp("ENTER", cmd)); Serial.println();

	//Serial.print("GUI:"); Serial.println(strcmp(cmd,"GUI"));
	//Serial.print("ENTER:"); Serial.println(strcmp(cmd,"ENTER"));
	//for (int l = s; l < e; l++) { oled.print(buf[l]); }
	//if (e - s < 2) Keyboard.press(buf[s]);
	
	//if (strlen(cmd)<=2) Keyboard.press(cmd[0]);
	keystatus = checkKey();
	if (!keystatus) checkF;
	if (!keystatus) checkNUM;
	//if (!keystatus) checkMOUSE;
	if (!keystatus) { if (ispt) { Keyboard.press_pt(cmd[0]); } else Keyboard.press(cmd[0]); }
	
	
	/*

	

	
	
	else Keyboard.press(cmd[0]);
	//else Serial.println("failed to find command");
	/* not implemented
	else if(equalsBuffer(s,e,"APP")) Keyboard.press();
	else if(equalsBuffer(s,e,"MENU")) Keyboard.press();
	else if(equalsBuffer(s,e,"BREAK") || equalsBuffer(s,e,"PAUSE",5)) Keyboard.press();
	else if(equalsBuffer(s,e,"NUMLOCK")) Keyboard.press();
	else if(equalsBuffer(s,e,"SCROLLLOCK")) Keyboard.press();
	*/
}

void duckySetup() {
#ifdef debug
	Serial.begin(115200);
	delay(200);
	Serial.println("Started!");
#endif
	ispt = EEPROM.read(eeaddr);
	if (ispt) {
		Serial.println("Keyboard: PT");
	}
	else {
		Serial.println("Keyboard: EN");
	}

	randomSeed(analogRead(0));

	pinMode(led1, OUTPUT);
	pinMode(led2, OUTPUT);


	pinMode(dip1, INPUT_PULLUP);
	pinMode(dip2, INPUT_PULLUP);
	pinMode(dip3, INPUT_PULLUP);
	pinMode(dip4, INPUT_PULLUP);

	pinMode(left, INPUT_PULLUP);
	pinMode(right, INPUT_PULLUP);
	pinMode(center, INPUT_PULLUP);

	if (digitalRead(center) == LOW) {
		oled.println("====== RUNNING ======");
		oled.println("Auto Mode!");
		delay(200);
		runDucky();
	}

	drawSplash();


	digitalWrite(led1, HIGH);
	digitalWrite(led2, HIGH);
	delay(100);
	digitalWrite(led1, LOW);
	digitalWrite(led2, LOW);
	delay(100);
	digitalWrite(led1, HIGH);
	digitalWrite(led2, HIGH);
	delay(100);
	digitalWrite(led1, LOW);
	digitalWrite(led2, LOW);
	delay(100);



	if (!SD.begin(4)) {

		Serial.println("couldn't access sd-card :(");
		oled.clear();
		oled.println("======= ERROR ======="); oled.println();
		oled.println("SD card error :(");


		return;
	}

	digitalWrite(led1, HIGH);



}


void runDucky() {

	String scriptName = ""; // Name of the file that will be opened
	if (digitalRead(dip1) == LOW) { scriptName += '1'; }
	else { scriptName += '0'; }
	if (digitalRead(dip2) == LOW) { scriptName += '1'; }
	else { scriptName += '0'; }
	if (digitalRead(dip3) == LOW) { scriptName += '1'; }
	else { scriptName += '0'; }
	if (digitalRead(dip4) == LOW) { scriptName += '1'; }
	else { scriptName += '0'; }

	scriptName += ".txt";
	//oled.println();
	oled.println();
	digitalWrite(led1, LOW);
	digitalWrite(led2, HIGH);
	oled.print("Running ");  oled.println(scriptName);

	ispt = EEPROM.read(0);

	SD.begin(4);

	payload = SD.open(scriptName);

	if (0) {
		//Serial.println("couldn't find script: '" + String(scriptName) + "'");
		//oled.print("Can't find "); oled.println(scriptName);
		return;
	}

	else {
		//oled.println("12345");

		//payload.close();
		Keyboard.begin();
		Mouse.begin();
		//delay(50);
		//oled.println("starting");
		//delay(50);
		while (payload.available()) {
			buf[bufSize] = payload.read();

			if (buf[bufSize] == '\r' || buf[bufSize] == '\n' || bufSize >= buffersize) {
				if (buf[bufSize] == '\r' && payload.peek() == '\n') payload.read();

				//---------REPEAT---------
				int repeatBufferSize = 0;
				int repeats = 0;
				unsigned long payloadPosition = payload.position();
				for (int i = 0; i<12; i++) {
					if (payload.available()) {
						repeatBuffer[repeatBufferSize] = payload.read();
						repeatBufferSize++;
					}
					else break;
				}

				if (repeatBufferSize > 6) {
					if (equals(repeatBuffer, 0, 6, "REPEAT", 6)) {
						repeats = getInt(repeatBuffer, 6);
					}
				}

				for (int i = 0; i<repeats; i++) runLine();

				payload.seek(payloadPosition);
				//------------------------
				//oled.println(buf);

				buf[bufSize] = '\0';
				//Serial.println(buf);
				runLine();
				bufSize = 0;
			}
			else bufSize++;
		}
		if (bufSize > 0) {
			

			int k = 0;

			buf[bufSize] = '\0';
			//Serial.println(buf);

			runLine();
			bufSize = 0;
		}
		payload.close();
		Mouse.end();
		Keyboard.end();
	}

	digitalWrite(led1, HIGH);
	digitalWrite(led2, LOW);

}