/*

    _____             _    _____ _        _         _______ ______ _______
   / ____|           | |  / ____| |      | |       |__   __|  ____|__   __|
  | |  __ _ __   __ _| |_| (___ | |_ __ _| |_ ___     | |  | |__     | |
  | | |_ | '_ \ / _` | __|\___ \| __/ _` | __/ __|    | |  |  __|    | |
  | |__| | | | | (_| | |_ ____) | || (_| | |_\__ \    | |  | |       | |
   \_____|_| |_|\__,_|\__|_____/ \__\__,_|\__|___/    |_|  |_|       |_|

  GNATSTATS PC Performance Monitor - Version 1.x  Rupert Hirst & Colin Conway © 2016
  http://tallmanlabs.com  & http://runawaybrainz.blogspot.com/

  Licence
  -------

  Attribution-NonCommercial-ShareAlike  CC BY-NC-SA

  This license lets others remix, tweak, and build upon your work non-commercially, as long as they credit you and license their new creations under the identical terms.

  https://creativecommons.org/licenses/

  --------------------------------------------------------------------------------------
    ___ ___  _  _ ___ ___ ___ _   _ ___    _ _____ ___ ___  _  _
   / __/ _ \| \| | __|_ _/ __| | | | _ \  /_\_   _|_ _/ _ \| \| |
  | (_| (_) | .` | _| | | (_ | |_| |   / / _ \| |  | | (_) | .` |
   \___\___/|_|\_|_| |___\___|\___/|_|_\/_/ \_\_| |___\___/|_|\_|
     ___  ___ _____ ___ ___  _  _ ___
    / _ \| _ \_   _|_ _/ _ \| \| / __|
   | (_) |  _/ | |  | | (_) | .` \__ \
    \___/|_|   |_| |___\___/|_|\_|___/


  --------------------------------------------------------------------------------------
*/

/*1st define correct MCU & TFT display type!!!
  Arduino UNO/NANO/MINI ETC. (Atmel ATMega 328 Chips) are not supported
  Use Leonardo / ProMicro (Atmel 32u4) or STM32BluePill

    UNO/NANO/MINI are not supported!!! use this sketch with STM32/ESP8622/ATSAMD21 based boards , due to larger memory.

  Link Below for the STM32 Bootloader and Arduino Core (you may have to install the Arduino Due core also for the compiler.)

  https://github.com/rogerclarkmelbourne/Arduino_STM32

  https://github.com/rogerclarkmelbourne/STM32duino-bootloader/tree/master/binaries

  BluePill_generic_boot20_pc13.bin  (On the "Bluepill" bootloader "_pc13" refers to the LED pin. )

  https://github.com/rogerclarkmelbourne/Arduino_STM32/wiki/Installation

  USB Issues:
  https://www.onetransistor.eu/2017/11/stm32-bluepill-arduino-ide.html

  Adafruit_GFX Version 1.8.0 and higher doesn't compile for ESP8266 & STM32 Boards -
  Downgrade to Adafruit_GFX Version 1.7.5 in the library manager.

  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
               SEE CONFIGURATION TAB FIRST, FOR QUICK SETTINGS!!!!
               SEE CONFIGURATION TAB FIRST, FOR QUICK SETTINGS!!!!
               SEE CONFIGURATION TAB FIRST, FOR QUICK SETTINGS!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

/* Uncomment below
  Adafruit_GFX Version 1.8.0 and higher doesn't compile for ESP8266 & STM32 Boards -
  Downgrade to Adafruit_GFX Version 1.7.5 in the library manager.*/
  
/*2nd define correct TFT display type!!!
  /* Uncomment below*/
#define ProMicro       // ProMicro SPi(Hardware):  CS:10   RST:Reset Pin    DC:9   SCLK:15  MOSI:16
//#define STM32_BluePill // STM32 SPi(Hardware) :  CS:PB11 RST:PB10 DC:PB1 SCLK:PA5 MOSI:PA7

/*2nd define correct TFT display type!!!
  /* Uncomment below*/

//#define TFT_ST7735  // Beware on ProMicro these are 3.3v backlight and logic
#define TFT_ILI9341   // Beware on ProMicro these are 3.3v backlight and logic

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/* 3906 PNP Transitor - VCC ((E)Emitter) - ((B)Base) MCU PIN Through Series Resistor 1k+ ((C)Collector)  TFT Back Light+ */

/* PWM TFT backlight */
int TFT_brightness = 150;   // PWM 0=100% 255=0%

/* Display screen rotation  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)*/
int ASPECT = 0;

//------------------------------------------------------------------------------------------------------------
/* Uncomment below to blank the screen on serial timeout to retain info eg: PC crash fault diagnostics  */
#define enableActivityChecker

/* How long the display takes to timeout due to inactive serial data from the windows application */
#define lastActiveDelay 6000

//------------------------------------------------------------------------------------------------------------

/* Time between "DisplayStyle" changes */
#define displayChangeDelay 6000

//------------------------------------------------------------------------------------------------------------

/* Uncomment below, to enable positive and negative screen cycler not much use on a TFT */
//#define enableInvertscreen
/* How long before inverting the display */
long invertDelay = 60000; // 60 sec  delay

//------------------------------------------------------------------------------------------------------------
#ifdef ProMicro
/* !!!!!! Sorry no NeoPixels for the STM32 as it uses the TFT SPi MOSI pin !!!!!!!! */
/* Uncomment below, to enable custom threshold event triggers*/

#define enableNeopixelGauges // NeoPixel ring bargraph example

/* Set NeoPixel intensity, this only works on the ProMicro  */
int NeoBrightness = 10;
#endif

/* Uncomment below to enable user custom triggers see "CustomTreshholdTriggers" tab */
//#define enableCustomThesholdtriggers

//------------------------------------------------------------------------------------------------------------
