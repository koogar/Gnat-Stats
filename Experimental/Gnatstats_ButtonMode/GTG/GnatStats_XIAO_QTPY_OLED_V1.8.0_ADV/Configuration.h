/*
   _____ __  __ _         _            ___           _   ___ _        _
  |_   _|  \/  | |   __ _| |__ ______ / __|_ _  __ _| |_/ __| |_ __ _| |_ ___
    | | | |\/| | |__/ _` | '_ (_-<___| (_ | ' \/ _` |  _\__ \  _/ _` |  _(_-<
    |_| |_|  |_|____\__,_|_.__/__/    \___|_||_\__,_|\__|___/\__\__,_|\__/__/

   uVolume, GNATSTATS OLED, PHATSTATS TFT PC Performance Monitor & HardwareSerialMonitor Windows Client
   Rupert Hirst © 2016-2023

   http://tallmanlabs.com  http://runawaybrainz.blogspot.com/
   https://github.com/koogar/Gnat-Stats  https://hackaday.io/project/181320-gnat-stats-tiny-oled-pc-performance-monitor


   Licence
   -------
   GPL v3*/

//--------------------- MicroController Setup --------------------------
/*Uncomment the correct Micro type, uncomment only one!!!*/

//#define Seeeduino_XIAO_ATSAMD
#define Adafruit_QTPY_ATSAMD
//#define Seeeduino_XIAO_RP2040   // Adafruit QT PY RP2040  (untested)
//#define Seeeduino_XIAO_NRF52840 // Adafruit QT PY NRF52840(untested)
//#define Seeeduino_XIAO_ESP32C3  // Adafruit QT PY ESP32S2, QT PY ESP32S3,  QT Py ESP32 Pico (untested)


//--------------------- OLED Setup --------------------------

/*Uncomment the correct OLED display type, uncomment only one display!!!*/

/* SSD1306 Compatability -->> QT PY ATSAMD21(YES), XIAO ATSAMD21(YES), XIAO RP2040 (YES), XIAO NRF52840 (YES), XIAO ESP32C3 (YES)*/
/* SH1106  Compatability -->> QT PY ATSAMD21(YES), XIAO ATSAMD21(YES), XIAO RP2040 (YES), XIAO NRF52840 (YES), XIAO ESP32C3 (YES)*/

/*---------------- SSD1306 -------------*/
#define OLED_SSD1306
//#define dim_Display // dim display SD1306 Only!!!

/*---------------- SH1106 --------------*/
//#define OLED_SH1106

//--------------------- Set i2c OLED address  --------------------------
/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

/*Flip the display:  0 or 2  (0, 180 degrees)*/
#define rotateScreen 2


//--------------- Manual CPU/GPU Display Name Entry -------------------------

/* Requires DisplayStyles ending in "_NC" (NameChange),*/
/* Characters to delete from the start of the auto detected CPU/GPU name eg: Remove "Intel" or "Nvidia" to save space*/

#define cpuNameStartLength 10
#define gpuNameStartLength 18

/* Manually set the CPU, GPU details*/

//#define Manual_cpuName
String set_CPUname = "xxxxxxx";

//#define Manual_gpuName
String set_GPUname = "xxxxxxx";

//#define Manual_gpuRam size in GB
String set_GPUram = "xx";

//------------------ Threshold Triggers -------------------

/* Uncomment below, to enable custom threshold event triggers*/

/* Global NeoPixel Brightness,*/
#define neoBrightness 20

/* User Custom  Triggers,*/
//#define enableCustomThesholdtriggers

/* Gnat-Tacho, NeoPixel ring bargraph example,*/
//#define enableNeopixelGauges //

/* uVolume only,*/
//#define uVol_enableThesholdtriggers
//--------------------- Other Stuff ----------------------

/* Enable button to change screens else use auto timer change*/
#define enable_buttonMode // auto_Mode is currently broken
int deBounce = 350;

/* Enable the built in LED blinking when transmitting data,*/
#define enableTX_LED
int TX_LED_Delay = 10; // TX blink delay

/* comment out, to disable blank screen on serial timeout to retain info eg: PC crash fault diagnostics  */
#define enableActivityChecker

/* Time between "DisplayStyle" changes */
#define displayChangeDelay 18000

/* Timer for active connection to host*/
#define lastActiveDelay 6000

/* Delay screen event, to help stop screen data corruption ESP8622 use 25, most others 0 will do*/
int Serial_eventDelay = 0; //serial do not adjust
int baud = 9600;           //serial do not adjust


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Anti Screen Burn */
//#define enableInvertscreen  // broken in button_Mod
/* Inverted timer for oled*/
long invertDelay    = 20000;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* Uncomment below, to take out small degree symbol for better spacing
   when hitting 100% cpu/gpu load the percent symbol gets clipped */
//#define noDegree

//---------------------------------------------- Versions ------------------------------------

/*
  Notes:
  UNO/NANO are not supported!!! use this sketch with Atmel 32u4 based boards such as, the Leonardo or ProMicro, due to to its native USB support.
  The Windows application "HardwareSerialMonitor v1.1 & V1.3"  uses the OpenHardwaremonitor  OpenHardwareMonitorLib.dll to detect the hardware.  http://openhardwaremonitor.org/
  The application will not detect integrated graphics as a GPU!!!

  Arduino UNO/NANO/MINI ETC. (Atmel ATMega 328 Chips) are not supported, Please don't ask!!!


    Version 1.6
                     : ATSAMD21 SH1106 Support

    Version 1.6.1
                     : Add Display Dim SD1306 Only!! #define dim_Display // dim display

    Version 1.7.1

        Add support for:
                        XIAO NRF52840 / QT PY NRF52840(untested)
                        XIAO RP2040   / QT PY RP2040  (untested)
                        XIAO ESP32C3  / QT PY ESP32C3 (untested)

    ---------------------------------------------------------------
  ASCII: http://patorjk.com/software/taag/
*/
