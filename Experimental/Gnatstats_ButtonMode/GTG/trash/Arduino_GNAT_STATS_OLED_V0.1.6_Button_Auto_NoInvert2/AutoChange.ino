//>>>>>>>>>>>>>>>>>>> Auto Change >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void auto_DisplayStyle () {
  
  serialEvent();
  activityChecker();
  
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
      //display.stopscroll();
      bootMode = false;
    }

    lastActiveConn = millis();

    if (displayChangeMode == 1) {
      DisplayStyle1_NC();

    }
    else if (displayChangeMode == 2) {
      DisplayStyle2_NC ();
    }
    else if (displayChangeMode == 3) {
      DisplayStyle3_NC ();
    }


    inputString = "";
    stringComplete = false;
    
// Keep running function continuously
    if (oledDraw == 1 && !serialEvent) {
      
    }
  }
}
