
//--------------------- MicroController Setup --------------------------
/*Uncomment the correct Micro type, uncomment only one!!!*/


#define Seeeduino_XIAO_ATSAMD
//#define Adafruit_QTPY_ATSAMD
//#define Seeeduino_XIAO_RP2040   // Adafruit QT PY RP2040  (untested)
//#define Seeeduino_XIAO_NRF52840 // Adafruit QT PY NRF52840(untested)
//#define Seeeduino_XIAO_ESP32C3  // Adafruit QT PY ESP32S2, QT PY ESP32S3,  QT Py ESP32 Pico (untested)

//#define ProMicro_32u4 // Unofficial Legacy update


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
#define rotateScreen 0

/* Uncomment below, to enable positive and negative screen cycler */
//#define enableInvertscreen

/* Uncomment below, to take out small degree symbol for better spacing
   when hitting 100% cpu/gpu load the percent symbol gets clipped */
//#define noDegree


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
#define enableCustomThesholdtriggers

/* Gnat-Tacho, NeoPixel ring bargraph example,*/
//#define enableNeopixelGauges //

//--------------------- Other Stuff ----------------------

/* Enable the built in LED blinking when transmitting data,*/
//#define enableTX_LED
int TX_LED_Delay = 100; // TX blink delay

/* comment out, to disable blank screen on serial timeout to retain info eg: PC crash fault diagnostics  */
#define enableActivityChecker

/* Time between "DisplayStyle" changes */
#define displayChangeDelay 18000

/* Timer for active connection to host*/
#define lastActiveDelay 6000

//>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Delay screen event, to help stop screen data corruption ESP8622 use 25, most others 5 will do*/
int Serial_eventDelay = 15;
int baud = 9600; //serial do not adjust

//>>>>>>>>>>>>>>>>>>>>>>>>>>>

//------------------ End of User configuration --------------

/* uVolume only,*/
//#define uVol_enableThesholdtriggers
