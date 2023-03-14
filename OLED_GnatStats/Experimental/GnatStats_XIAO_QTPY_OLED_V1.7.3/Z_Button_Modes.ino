

/*Mode Button Function*/

void button_Modes() {

  int display_ButtonVal = digitalRead(mode_Button);
  if (display_ButtonVal == LOW)


  {
    delay(debounceButton); // Debounce Button
    display_Button_counter ++;

    /* Clear Screen*/
    //backlightOFF();
    //tft.fillScreen(ILI9341_BLACK);

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
        DisplayStyle1_NC();
        break;

      case 1: // 2nd SCREEN
        DisplayStyle2_NC();
        break;

    }
}
