
void button_Mode () {

  //Handle input
  int switchVal = digitalRead(switchPin);

  if (switchVal == LOW)
  {
    delay(deBounce);
    counter ++;
    //Reset count if over max mode number
    if (counter == 4)
    {
      counter = 0;
    }
  }

  else
    //Change mode
    switch (counter) {

      //default:
      //DisplayStyle1_OLED ();
      //pixels.setPixelColor(0, BLACK);
      //pixels.show(); // This sends the updated pixel color to the hardware
      //break;

      case 0:
        DisplayStyle1_OLED ();
        //pixels.setPixelColor(0, RED);
        //pixels.show(); // This sends the updated pixel color to the hardware

        break;
      case 1:
        DisplayStyle2_OLED ();
        //pixels.setPixelColor(0, GREEN);
        //pixels.show(); // This sends the updated pixel color to the hardware
        break;

      case 2:
        DisplayStyle3_OLED ();
        //pixels.setPixelColor(0, BLUE);
        //pixels.show(); // This sends the updated pixel color to the hardware
        break;

      case 3:
        DisplayStyle4_OLED ();
        //pixels.setPixelColor(0, BLUE);
        //pixels.show(); // This sends the updated pixel color to the hardware
        break;


#ifdef enable_Invertscreen
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
