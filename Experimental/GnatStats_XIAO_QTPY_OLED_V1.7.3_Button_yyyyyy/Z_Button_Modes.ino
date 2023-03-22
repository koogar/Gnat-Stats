

/*Mode Button Function*/

void button_Modes() {

  int display_ButtonVal = digitalRead(mode_Button);
  if (display_ButtonVal == LOW)


  {
    delay(debounceButton); // Debounce Button
    display_Button_counter ++;

    /* Clear Screen*/
    display.fillRect(0, 0, 128 , 64, BLACK);
    display.display();


    /* Reset count if over max mode number, */
    if (display_Button_counter == 2) // Number of screens available when button pressed
    {
      display_Button_counter = 0;
    }
  }

  else

    /* Change Mode */
    switch (display_Button_counter) {

      case 0: // 1st SCREEN

        /* OLED DRAW STATS */
        if (stringComplete) {

          if (bootMode) {
            display.clearDisplay();
            display.display();
            //display.stopscroll();
            bootMode = false;
          }

          lastActiveConn = millis();

          //----------Displays Style Here----------------

          DisplayStyle1_NC ();
          //--------------------------------------------

          inputString = "";
          stringComplete = false;


          /* Keep running anti screen burn, whilst serial is active */
          if ((millis() - lastInvertTime) > invertDelay && oledDraw == 1) {
            lastInvertTime = millis();

          }
        }

        break;

      case 1: // 2nd SCREEN
        /* OLED DRAW STATS */
        if (stringComplete) {

          if (bootMode) {
            display.clearDisplay();
            display.display();
            //display.stopscroll();
            bootMode = false;
          }

          lastActiveConn = millis();

          //----------Displays Style Here----------------
          DisplayStyle2_NC ();
          //--------------------------------------------

          inputString = "";
          stringComplete = false;


          /* Keep running anti screen burn, whilst serial is active */
          if ((millis() - lastInvertTime) > invertDelay && oledDraw == 1) {
            lastInvertTime = millis();

          }
        }

        break;

    }
}
