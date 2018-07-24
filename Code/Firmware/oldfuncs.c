void runLine(){
  #ifdef debug
    Serial.println("run: '"+String(buf).substring(0,bufSize)+"' ("+(String)bufSize+")");
  #endif
  int space = getSpace(0,bufSize);
  

 // for (int l = 0; l < space; l++) { oled.print(buf[l]);  }
  //for (int l = space+1; l < bufSize; l++) { oled.print(buf[l]);}
  
  char *cmd;
  char *arg;
  delay(500);
  oled.clear();

  for (int u = 0; u < 2; u++) {
	  if (u == 0) { cmd = strtok_r(buf, " ", &buf); }
	  if (u == 1) { arg = strtok_r(buf, " ", &buf); }
	  oled.print(cmd);
	  oled.println(arg);
 }
  
  if(space == -1) runCommand(0,bufSize);
  else{
    if(equalsBuffer(0,space,"DEFAULTDELAY") || equalsBuffer(0,space,"DEFAULT_DELAY")) defaultDelay = getInt(buf,space);
    else if(equalsBuffer(0,space,"DEFAULTCHARDELAY") || equalsBuffer(0,space,"DEFAULT_CHAR_DELAY")) defaultCharDelay = getInt(buf,space);
	else if (equals(buf, 0, space, "DELAY", strlen("DELAY"))) {
	//else if (strcmp("DELAY",arg)) {
		  //delay(getInt(buf, space)); //delay(String(buf).substring(space + 1, bufSize).toInt());
	}
    else if(equals(buf, 0, space, "STRING", strlen("STRING"))){
		
		for (int i = space + 1; i < bufSize; i++) { KeyboardWrite(buf[i]); }
    }

	
    else if(equalsBuffer(0,space,"MOUSE")){
      int nSpace = getSpace(space+1,bufSize);
      int x = getInt(buf,space);
      int y = getInt(buf,nSpace);
      Mouse.move(x,y);
      #ifdef debug
        Serial.println("Move mouse "+(String)x+" "+(String)y);
      #endif
    }
    else if(equalsBuffer(0,space,"SCROLL")) Mouse.move(0,0,getInt(buf,space));
    else if(equalsBuffer(0,space,"RANDOMMIN")) rMin = getInt(buf,space);
    else if(equalsBuffer(0,space,"RANDOMMAX")) rMax = getInt(buf,space);
    else if(equalsBuffer(0,space,"REM") || equalsBuffer(0,space,"REPEAT")){}
    else{
      runCommand(0,space);
	  //for (int k=0; k < bufSize; k++) { oled.print(char(buf[k])); }
	  while(space >= 0 && space < bufSize){
        int nSpace = getSpace(space+1,bufSize);
        if(nSpace == -1) nSpace = bufSize;
		//runCommand(space+1,nSpace);
        space = nSpace;
      }
    }
  }

  Keyboard.releaseAll();
  delay(defaultDelay);
}
