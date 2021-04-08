/*

      _   ___ ___ _    ___  __      ___  _ ___ _____ ___    ___ ___  ___  ___ ___
     /_\ | _ \ _ \ |  | __| \ \    / / || |_ _|_   _| __|  / __/ _ \|   \| __/ __|
    / _ \|  _/  _/ |__| _|   \ \/\/ /| __ || |  | | | _|  | (_| (_) | |) | _|\__ \
   /_/ \_\_| |_| |____|___|   \_/\_/ |_||_|___| |_| |___|  \___\___/|___/|___|___/


   Insert you generic remote codes in here

  NOTE DO NOT REPEAT DEFINE OR IR CODES IN HERE, OR YOU WILL GET AN ERROR
  HENCE THE CONSECUTIVE NUMBERED PLACEHOLDERS 0x00000000, 0x00000001, 0x00000002, ETC FOR UNUSED FUNCTIONS IN THE "void loop()" !

  Apple White Plastic Remote Codes
  -------------------------------
*/
#define Next_Button       0x77E1606D: // Apple Right Button 
#define Previous_Button   0x77E1906D: // Apple Left Button 
#define Vol_Up_Button     0x77E1506D: // Apple UP Button
#define Vol_Down_Button   0x77E1306D: // Apple Down Button
#define Mute_Button       0x77E1C06D: // Apple Menu Button
#define PlayPause_Button 0x77E1A06D: // PLACE HOLDER PausePause_Button

//Place Holder for unused keys
//(if you are not using a defined key, above you need to uncomment the key below, otherwise you will get an error)
//----------------------------

#define Playbackspeed_Button  0x00000000:
//#define Next_Button         0x00000001:
//#define Previous_Button     0x00000002:
//#define Vol_Up_Button       0x00000003:
//#define Vol_Down_Button     0x00000004:
//#define Mute_Button         0x00000005:
//#define PlayPause_Button    0x00000006:
#define Pause_Button          0x00000007:
#define Play_Button           0x00000008:
#define Repeat_Button         0x00000009:
#define Stop_Button           0x00000010:


//  Edit the Below in the main sketch to reflect the mute IR code, so the mute LED correctly lights when using the remote control
//  case Mute_Button     // Menu Button Code
//   if ((irrecv.decode(&results)) && (results.value==0x77E1C06D) ) { //Mute Remote IR Code, Dont forget the change MUTE Code if you change remotes, or MUTE LED will not light


/*

   Apple (607-1231) Plastic Remote Codes
  ---------------------------------------
  0x77E1A06D:  Center PLAY/PAUSE Button Code
  0x77E1606D:  Right Button Code
  0x77E1906D:  Left Button Codeft
  0x77E1506D:  UP Button Code
  0x77E1306D:  Down Button Code
  0x77E1C06D:  Menu Button Code
  0xFFFFFFFF:  Repeat Code

   Arduino Leo HID.cpp Multimedia Functions, Arduino\hardware\arduino\cores\arduino (Arduino IDE 1.0.5)
   ==================================
   Remote.increase();  // VOLUME_UP
   Remote.decrease();  // VOLUME_DOWN
   Remote.mute();      // VOLUME_MUTE
   ...................................
   Remote.play();      // REMOTE_PLAY

   Remote.pause();     // REMOTE_PAUSE
   Remote.stop();      // REMOTE_STOP
   Remote.next();      // REMOTE_NEXT
   Remote.previous();  // REMOTE_PREVIOUS
   Remote.forward();   // REMOTE_FAST_FORWARD
   Remote.rewind();    // REMOTE_REWIND

   Remote.clear();     // Clear Last Function

*/
