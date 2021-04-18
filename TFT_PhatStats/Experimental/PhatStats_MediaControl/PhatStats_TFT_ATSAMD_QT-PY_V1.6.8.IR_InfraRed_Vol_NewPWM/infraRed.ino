
/*
   ___ _  _ ___ ___    _      ___ ___ ___
  |_ _| \| | __| _ \  /_\ ___| _ \ __|   \
   | || .` | _||   / / _ \___|   / _|| |) |
  |___|_|\_|_| |_|_\/_/ \_\  |_|_\___|___/
*/

#ifdef enableIR
//------------------------IR Routine----------------------------------
void infraRed () {

if (irrecv.decode(&results)) {
  switch (results.value) {

    case Stop_Button
        //Serial.println("iRemote Stop");    // DEBUG
        Consumer.write(MEDIA_STOP);                // HID Stop Key
      delay(200);
      break;

    case Next_Button
        //Serial.println("iRemote Next Track");  // DEBUG
        Consumer.write(MEDIA_NEXT);                 // HID Next Track key
      delay(200);
      break;

    case Previous_Button
        //Serial.println("iRemote Prev Track"); // DEBUG
        Consumer.write(MEDIA_PREVIOUS);           // HID Previous Track key
      delay(200);
      break;

    case Vol_Up_Button
        //Serial.println("iRemote Vol+");    // DEBUG
        Consumer.write(MEDIA_VOLUME_UP);
      break;

    case Vol_Down_Button
        //Serial.println("iRemote Vol-"); // DEBUG
        Consumer.write(MEDIA_VOLUME_DOWN);
      break;

    //------------------------IR Mute LED---------------------------
    case Mute_Button     // Menu Button Code

        /*Use the defined remote code for Mute LED State*/

#ifdef IR_AppleWhite
        if ((irrecv.decode(&results)) && (results.value == 0x77E1C06D) ) {   //(Apple White Remote, Dont forget the change MUTE Code if you change remotes, or LED will not light
#endif

#ifdef IR_AppleAlu
          if ((irrecv.decode(&results)) && (results.value == 0x77E1C038) ) { //Apple Aluminium Remote, Dont forget the change MUTE Code if you change remotes, or LED will not light
#endif

#ifdef IR_BOSE
            if ((irrecv.decode(&results)) && (results.value == 0x1409939) ) { //Bose Sound Dock Series 1, Dont forget the change MUTE Code if you change remotes, or LED will not light
#endif

              if (state == 0) {
                state = 1;
                //Serial.println("iRemote MUTE LED= On");// DEBUG
              }
              else {
                state = 0;
                //Serial.println("iRemote Mute LED= Off"); // DEBUG
              }
              //delay(50);
              irrecv.resume();
            }
            //Serial.println("iRemote Mute");// DEBUG
            Consumer.write(MEDIA_VOLUME_MUTE);              // HID Mute
            delay(500);
            break;

          case Play_Button              // Play Button Code
              //Serial.println("iRemote Play"); // DEBUG
              Consumer.write(MEDIA_PLAY_PAUSE);           // HID Play Key
            delay(500);
            break;

          case PlayPause_Button             // Play Button Code
              //Serial.println("iRemote Play"); // DEBUG
              Consumer.write(MEDIA_PLAY_PAUSE);           // HID Play Key
            delay(500);
            break;

          }
          irrecv.resume();
        }
  }
#endif
