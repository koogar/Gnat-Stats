
/*
   ___ _  _  ___ ___  ___  ___ ___
  | __| \| |/ __/ _ \|   \| __| _ \
  | _|| .` | (_| (_) | |) | _||   /
  |___|_|\_|\___\___/|___/|___|_|_\
  
*/


void encoderbutton () {

  if (digitalRead(encoderSwitchPin)) {               // Encoder Button Mute

    //Encoder button is not being pushed
  }
  else {

    //Encoder button is being pushed
    //Serial.println("Encoder Switch, Mute");        // DEBUG
    if (state == 0) {
      state = 1;


      allNeoPixelsOff();
      delay(40);

      neoRED();
      delay(40);

      allNeoPixelsOff();
      delay(40);

      neoRED();
      delay(40);

      //display.clearDisplay();
      //display.setTextSize(1); //set background txt font size
      //display.setCursor(84, 56);
      //display.print("MUTEON");
      //display.display();
      //Serial.println("Encoder MUTE On LED");// DEBUG
    }
    else {
      state = 0;

      neoBLUE();

      //Serial.println("Encoder Mute Off LED"); // DEBUG
    }

    Consumer.write(MEDIA_VOLUME_MUTE);                  // HID  Mute
    delay(500); // Debounce

    //display.clearDisplay();
    //display.setTextSize(1); //set background txt font size
    //display.setCursor(84, 56);
    //display.print("MUTEOFF");
    //display.clearDisplay();
    //display.display();

  }
}



//--------------------------------------------------------------------------------------------------------


void rotaryEncoder () {

}

ISR(PCINT0_vect) {
  unsigned char result = r.process();
  if (result == DIR_NONE) {

    /*NeoPixel Idle colour*/
    neoBLUE();

  }
  else if (result == DIR_CW) {
    // See HID Project documentation for more Consumer keys

    Consumer.write(MEDIA_VOLUME_UP);
    delay(50);
    neoRED();
    //display.clearDisplay();
    //display.setTextSize(1); //set background txt font size
    //display.setCursor(84, 56);
    //display.print("Vol-");
    //display.display();
  }
  else if (result == DIR_CCW) {
    // See HID Project documentation for more Consumer keys

    Consumer.write(MEDIA_VOLUME_DOWN);
    delay(50);
    neoRED();

    //display.clearDisplay();
    //display.setTextSize(1); //set background txt font size
    //display.setCursor(84, 56);
    //display.print("Vol+");
    // display.display();

  }

}

//--------------------------------------------------------------------------------------------------------
