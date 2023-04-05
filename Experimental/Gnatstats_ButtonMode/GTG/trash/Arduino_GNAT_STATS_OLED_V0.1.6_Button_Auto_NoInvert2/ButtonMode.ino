

void ButtonMode () {
  
  //>>>>>>>>>>>>>>>>>>>>>>>>>>
  int switchVal = digitalRead(switchPin);

  /* OLED DRAW STATS */
  if (stringComplete) {

    if (bootMode) {
      //splashScreen2();
      display.clearDisplay();
      display.display();

      bootMode = false;
    }

    lastActiveConn = millis();


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //Handle input


    if (switchVal == LOW)
    {
      delay(500);
      counter ++;
      //Reset count if over max mode number
      if (counter == 3)
      {
        counter = 0;
      }
    }

    else
      //Change mode
      switch (counter) {


        case 0:
          DisplayStyle1_NC ();
          //oledDraw = 1;
          //counter = 2;
          break;

        case 1:
          DisplayStyle2_NC ();
          //oledDraw = 1;
          //counter = 3;
          break;

        case 2:
          DisplayStyle3_NC ();
          //oledDraw = 1;
          //counter = 1;
          break;

        default:
          DisplayStyleDefualt_NC ();
          //oledDraw = 1;
          //counter = 0;
          break;


          inputString = "";
          stringComplete = false;

          // Keep running function continuously
          if (oledDraw == 1 && !serialEvent) {

            /*Serial stuff*/

          }

      }
  }
}
