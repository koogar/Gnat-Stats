

void auto_Mode () {


#ifdef ProMicro_32u4


  /*change display screen*/
  if ((millis() - lastDisplayChange) > displayChangeDelay)
  {
    if (displayChangeMode == 1) {
      displayChangeMode = 2;
      display.fillRect(0, 0, 128 , 64, BLACK);
    }
    else if (displayChangeMode == 2) {
      displayChangeMode = 1;
      display.fillRect(0, 0, 128 , 64, BLACK);
    }

    lastDisplayChange = millis();
  }

  /* OLED DRAW STATS */
  if (stringComplete) {

    if (bootMode) {
      display.clearDisplay();
      display.display();

      bootMode = false;
    }

    lastActiveConn = millis();

    //NOTE:ProMicro_32u4 // Limited to 2 DisplayStyles Due to Memory
    if (displayChangeMode == 1) {
      DisplayStyle1_OLED();

    }
    else if (displayChangeMode == 2) {
      DisplayStyle2_OLED ();
    }

    inputString = "";
    stringComplete = false;

#ifdef enableInvertscreen
    /* Keep running anti screen burn, whilst serial is active */
    if ((millis() - lastInvertTime) > invertDelay && oledDraw == 1) {
      lastInvertTime = millis();

      /* Anti Screen Burn */
      inverter();

#else
    // Keep running function continuously
    if (oledDraw == 1 && !serialEvent) {
    }
#endif


//------------------------------------------------------------------
      
#else //-------------else use extended DisplayStyles----------------

  /*change display screen*/
  if ((millis() - lastDisplayChange) > displayChangeDelay)
  {
    if (displayChangeMode == 1) {
      displayChangeMode = 2;
      display.fillRect(0, 0, 128 , 64, BLACK);
    }
    else if (displayChangeMode == 2) {
      displayChangeMode = 3;
      display.fillRect(0, 0, 128 , 64, BLACK);
    }
    else if (displayChangeMode == 3) {
      displayChangeMode = 1;
      display.fillRect(0, 0, 128 , 64, BLACK);
    }

    lastDisplayChange = millis();
  }

  /* OLED DRAW STATS */
  if (stringComplete) {

    if (bootMode) {
      display.clearDisplay();
      display.display();

      bootMode = false;
    }

    lastActiveConn = millis();

    if (displayChangeMode == 1) {
      DisplayStyle1_OLED();

    }
    else if (displayChangeMode == 2) {
      DisplayStyle2_OLED ();
    }
    else if (displayChangeMode == 3) {
      DisplayStyle3_OLED ();
    }

    inputString = "";
    stringComplete = false;

#ifdef enableInvertscreen
    /* Keep running anti screen burn, whilst serial is active */
    if ((millis() - lastInvertTime) > invertDelay && oledDraw == 1) {
      lastInvertTime = millis();

      /* Anti Screen Burn */
      inverter();

#else
    // Keep running function continuously
    if (oledDraw == 1 && !serialEvent) {
    }
#endif

#endif
    }
  }


  
