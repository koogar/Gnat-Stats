/*

   ___  ___  ___ ___    ___ ___  ___  ___ ___
  | _ )/ _ \/ __| __|  / __/ _ \|   \| __/ __|
  | _ \ (_) \__ \ _|  | (_| (_) | |) | _|\__ \
  |___/\___/|___/___|  \___\___/|___/|___|___/
  
   Insert you generic remote codes in here
  #include "BoseSoundDock1.h"      // this is not a library its a local header Files
  NOTE DO NOT REPEAT DEFINE OR IR CODES IN HERE, OR YOU WILL GET AN ERROR
  HENCE THE CONSECUTIVE NUMBERED PLACEHOLDERS 0x00000000, 0x00000001, 0x00000002, ETC FOR UNUSED FUNCTIONS IN THE "void loop()" !

  BOSE Sound Dock Series 1
  -------------------------------
*/


#define PlayPause_Button       0x1732D99D: // Bose Play/Pause Button
#define Next_Button            0x9EE06A39: // Bose Next Track Button 
#define Previous_Button        0xE6C183D:  // Bose Previous Track Button 
#define Vol_Up_Button          0x43020535: // Bose Volume + Button
#define Vol_Down_Button        0x49C595B9: // Bose Volume - Button
#define Mute_Button            0x1409939:  // Bose Power OFF Button


//Place Holder for unused keys
//----------------------------
#define Playbackspeed_Button  0x00000000:
//#define Next_Button         0x00000001:
//#define Previous_Button     0x00000002:
//#define Vol_Up_Button       0x00000003:
//#define Vol_Down_Button     0x00000004:
//#define Mute_Button         0x00000005:
//#define PlayPause_Button   0x00000006:
#define Pause_Button          0x00000007:
#define Play_Button           0x00000008:
#define Repeat_Button         0x00000009:
#define Stop_Button           0x00000010:




/*

  Edit the Below in the main sketch to reflect the mute IR code, so the mute LED correctly lights when using the remote control
  case Mute_Button     // Menu Button Code
  if ((irrecv.decode(&results)) && (results.value==0x1409939) ) { //Bose Sound Dock Series 1, Dont forget the change MUTE Code if you change remotes, or LED will not light

   Bose Sound Dock V1 Remote Codes
  ---------------------------------

  0x1409939:   OFF
  0x43020535:  Volume Up
  0x49C595B9:  Volume Down
  0x9EE06A39:  Next Track
  0xE6C183D:   Previous Track
  0x1732D99D:  Play/Pause
  ==================================
  https://github.com/NicoHood/HID/wiki/Consumer-API

  MEDIA_FAST_FORWARD
  MEDIA_REWIND
  MEDIA_NEXT
  MEDIA_PREVIOUS
  MEDIA_STOP
  MEDIA_PLAY_PAUSE

  MEDIA_VOLUME_MUTE
  MEDIA_VOLUME_UP
  MEDIA_VOLUME_DOWN



*/
