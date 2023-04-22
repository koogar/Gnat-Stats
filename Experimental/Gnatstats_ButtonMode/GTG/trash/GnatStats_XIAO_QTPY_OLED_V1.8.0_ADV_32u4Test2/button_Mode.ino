
void button_Mode () {

  //Handle input
  int switchVal = digitalRead(switchPin);

  if (switchVal == LOW)
  {
    delay(deBounce);
    counter ++;
    //Reset count if over max mode number

#ifdef ProMicro_32u4 // Limited to 2 DisplayStyles Due to Memory
    if (counter == 3)
#else
    if (counter == 3)
#endif

    {
      counter = 0;
    }
  }

  else
    //Change mode
    switch (counter) {


      default:
        DisplayStyle1_OLED ();
        break;

      case 0:
        DisplayStyle1_OLED ();
        break;

      case 1:
        DisplayStyle2_OLED ();
        break;

      //NOTE:ProMicro_32u4 // Limited to 2 DisplayStyles Due to Memory
      //-------------else use extended DisplayStyles----------------
      case 2:
        DisplayStyle3_OLED ();
        break;

      case 3:
        DisplayStyle4_OLED ();
        break;

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

        }
    }

  //---------------------------------------------------------------------------------------

  void button_Mode_32u4 () {

    //Handle input
    int switchVal = digitalRead(switchPin);

    if (switchVal == LOW)
    {
      delay(deBounce);
      counter ++;
      //Reset count if over max mode number

      if (counter == 2)

      {
        counter = 0;
      }
    }

    else
      //Change mode
      switch (counter) {

        default:
          DisplayStyle1_OLED ();
          break;

        case 0:
          DisplayStyle1_OLED ();
          break;

        case 1:
          DisplayStyle2_OLED ();
          break;



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

          }
      }
