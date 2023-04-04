

/*Mode Button Function*/

void button_ISR () {
  // Check if the button state has changed and if enough time has passed since last debounce
  if (buttonState != lastButtonState && (millis() - lastDebounceTime) > debounceDelay) {
    // Reset debounce timer
    lastDebounceTime = millis();

    // Update last button state
    lastButtonState = buttonState;

    // Check if button is pressed (buttonState is LOW due to pull-up resistor)
    if (buttonState == LOW) {
      // Switch between different cases
      static int caseNum = 1;
      switch (caseNum) {

        
        case 1:
          DisplayStyle1_NC ();
          caseNum = 2;
          break;

        case 2:
          DisplayStyle2_NC ();
          caseNum = 3;
          break;

        case 3:
          DisplayStyle3_NC ();
          caseNum = 1;
          break;

        default:
          caseNum = 1;
          break;
      }
    }
  }
}

//void buttonInterrupt() {
// Set buttonPressed flag to indicate that the button has been pressed
//buttonPressed = true;
//}
