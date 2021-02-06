
/*
   ___ _  _ ___ ___    _      ___ ___ ___
  |_ _| \| | __| _ \  /_\ ___| _ \ __|   \
   | || .` | _||   / / _ \___|   / _|| |) |
  |___|_|\_|_| |_|_\/_/ \_\  |_|_\___|___/
*/

void infraRed () {


  //------------------------IR Routine----------------------------------

  if (irrecv.decode(&results)) {
    switch (results.value) {

      case Stop_Button

          Consumer.write(MEDIA_STOP);                // HID Stop Key
        delay(200);

        //Serial.println("iRemote Stop");    // DEBUG
        break;


      case Next_Button

          Consumer.write(MEDIA_NEXT);                 // HID Next Track key
        delay(200);

        //Serial.println("iRemote Next Track");  // DEBUG
        break;


      case Previous_Button

          Consumer.write(MEDIA_PREVIOUS);           // HID Previous Track key
        delay(200);

        //Serial.println("iRemote Prev Track"); // DEBUG
        break;


      case Vol_Up_Button

          //   RemFeedbackVolUpLED();
          Consumer.write(MEDIA_VOLUME_UP);

        //Serial.println("iRemote Vol+");    // DEBUG
        break;

      case Vol_Down_Button

          //  RemFeedbackVolDwnLED();
          Consumer.write(MEDIA_VOLUME_DOWN);

        //Serial.println("iRemote Vol-"); // DEBUG
        break;


      case Mute_Button     // Menu Button Code
          //------------------------IR Mute LED---------------------------


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

                  // MuteOnLED();


                }
                else {
                  state = 0;
                  //Serial.println("iRemote Mute LED= Off"); // DEBUG

                  // MuteOffLED();


                }
                //delay(50);
                irrecv.resume();
              }
              //--------------------------------------------------------------

              Consumer.write(MEDIA_VOLUME_MUTE);              // HID Mute

              delay(500);

              //Serial.println("iRemote Mute");// DEBUG
              break;


            case Play_Button              // Play Button Code
                // IRFeedbackLED();
                Consumer.write(MEDIA_PLAY_PAUSE);           // HID Play Key
              delay(500);

              //Serial.println("iRemote Play"); // DEBUG
              break;

            case PlayPause_Button             // Play Button Code
                // IRFeedbackLED();
                Consumer.write(MEDIA_PLAY_PAUSE);           // HID Play Key

              //Keyboard.press(KEY_SPACE);// Youtube / VLC "SPACE" key pause. Browser window has to be focused on the Youtube video portion of the screen for space bar to pause the video!!!
              //delay(100);
              //Keyboard.release(KEY_SPACE);

              delay(500);

              //Serial.println("iRemote Play"); // DEBUG
              break;


            }



            irrecv.resume();
          }
    }
