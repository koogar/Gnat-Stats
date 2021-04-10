
/*
     _   ___ ___ _    ___     _   _   _   _    ___ ___  ___  ___ ___
    /_\ | _ \ _ \ |  | __|   /_\ | | | | | |  / __/ _ \|   \| __/ __|
   / _ \|  _/  _/ |__| _|   / _ \| |_| |_| | | (_| (_) | |) | _|\__ \
  /_/ \_\_| |_| |____|___| /_/ \_\____\___/   \___\___/|___/|___|___/

   Insert you generic remote codes in here

  NOTE DO NOT REPEAT DEFINE OR IR CODES IN HERE, OR YOU WILL GET AN ERROR
  HENCE THE CONSECUTIVE NUMBERED PLACEHOLDERS 0x00000000, 0x00000001, 0x00000002, ETC FOR UNUSED FUNCTIONS IN THE "void loop()" !

  Apple Aluminium Remote Codes
  -------------------------------
*/


#define Next_Button         0x77E16038: // Apple Right Button 
#define Previous_Button     0x77E19038: // Apple Left Button 
#define Vol_Up_Button       0x77E15038: // Apple UP Button 
#define Vol_Down_Button     0x77E13038: // Apple Down Button
#define Mute_Button         0x77E1C038: // Apple Menu Button
#define PlayPause_Button    0x77E1FA38: // Apple Play Button  //TEMP HID.CPP HACK (PLAY/PAUSE with usage code 'CD' from "USB HID USAGE" tables)


//Place Holder for unused keys
//(if you are not using a defined key, above you need to uncomment the key below, otherwise you will get an error)
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




/* Apple Aluminium Remote Codes
  ---------------------------------
  0x77E13A38:   Center Button Code
  0x77E16038:   Right Button Code
  0x77E19038:   Left Button Code
  0x77E15038:   UP Button Code
  0x77E13038:   Down Button Code
  0x77E1C038:   Menu Button Code
  0x77E1FA38:   Play Button Code
  0xFFFFFFFF:   Repeat Code

   Apple Plastic Remote Codes
  ---------------------------------
  0x77E1A0CB:  Center Button Code
  0x77E160CB:  Right Button Code
  0x77E190CB:  Left Button Codeft
  0x77E150CB:  UP Button Code
  0x77E130CB:  Down Button Code
  0xFFFFFFFF:   Repeat Code

*/
