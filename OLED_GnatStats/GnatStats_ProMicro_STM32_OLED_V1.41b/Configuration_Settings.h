/*
  ------------------------------------------------------------------------------------------
    _____             _    _____ _        _          ____  _      ______ _____
   / ____|           | |  / ____| |      | |        / __ \| |    |  ____|  __ \
  | |  __ _ __   __ _| |_| (___ | |_ __ _| |_ ___  | |  | | |    | |__  | |  | |
  | | |_ | '_ \ / _` | __|\___ \| __/ _` | __/ __| | |  | | |    |  __| | |  | |
  | |__| | | | | (_| | |_ ____) | || (_| | |_\__ \ | |__| | |____| |____| |__| |
   \_____|_| |_|\__,_|\__|_____/ \__\__,_|\__|___/  \____/|______|______|_____/

  ------------------------------------------------------------------------------------------
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

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/*Define correct MCU & OLED display type!!!*/
/*1st define correct MCU & OLED display type!!!*/

#define ProMicro       // ProMicro i2c SDA:2       SCL:3  / NeoPixel: 4
//#define STM32_BluePill // STM32    i2C SDA:PB7(B7) SCL:PB6(PB7)  / NeoPixel: PA7 (no need to define it, just connect to pin A7)

//--------------------------------------------------------------------------------------

/*2nd define correct OLED display type!!!*/
/*Warning!!!! Please check you have the correct polarity for the selected OLED screen*/

#define OLED_SSD1306
//#define OLED_SH1106 

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/* Screen rotation for oled*/
int ASPECT =        0;// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

//---------------------------------------------------------------------------------------

/* Neo Pixel Setup */
int NeoBrightness = 50; // Atmel Global Brightness (does not work for STM32!!!!)

//---------------------------------------------------------------------------------------

/* Uncomment below, to enable custom threshold event triggers*/
//#define uVol_enableThesholdtriggers
//#define enableCustomThesholdtriggers
#define enableNeopixelGauges // NeoPixel ring bargraph example

//---------------------------------------------------------------------------------------

/* comment out, to disable blank screen on serial timeout to retain info eg: PC crash fault diagnostics  */
#define enableActivityChecker

/* How long the display takes to timeout due to inactive serial data from the windows application */

#define lastActiveDelay 8000

//---------------------------------------------------------------------------------------

/* Uncomment below, to enable positive and negative screen cycler */
//#define enableInvertscreen

/* How long before inverting the display */
long invertDelay = 60000; // 60 sec  delay

//---------------------------------------------------------------------------------------
/* DisplayStyles 1 to 3 are place holders, for example only. Tweak them as you see fit */
/* Time between "DisplayStyle" changes */

#define displayChangeDelay 18000

//---------------------------------------------------------------------------------------
