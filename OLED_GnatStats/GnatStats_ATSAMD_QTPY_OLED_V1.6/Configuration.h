
//--------------------- MicroController Setup --------------------------
/*Uncomment the correct Micro type, uncomment only one!!!*/

/* Adafruit QT-PY*/
//#define QTPY   // uncomment to disable QT-PY built in Neopixel if you have a XIAO

/* Seeeduino XIAO,*/
#define XIAO

//>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* Enable the built in LED blinking when transmitting,*/
#define enableTX_LED

//--------------------- OLED Setup --------------------------
/*Uncomment the correct OLED display type, uncomment only one!!!*/

#define OLED_SSD1306
//#define OLED_SH1106

//>>>>>>>>>>>>>>>>>>>>>>>>>>>
//#define OLED_SH1106_SPi //  7 pin SPi Experimental Untested
//>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

//>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*Rotate the display at the start:  0 or 2  (0, 180 degrees)*/
#define rotateScreen 0

/* Uncomment below, to enable positive and negative screen cycler */
//#define enableInvertscreen

/* Uncomment below, to take out small degree symbol for better spacing
   when hitting 100% cpu/gpu load the percent symbol gets clipped */
//#define noDegree

//--------------- Manual CPU/GPU Display Name Entry -------------------------

/* Requires DisplayStyles ending in "_NC" (NameChange),*/
/* Characters to delete from the start of the CPU/GPU name eg: Remove "Intel" or "Nvidia" to save space*/
#define cpuNameStartLength 10
#define gpuNameStartLength 18

/* Manually name the  CPU,*/
//#define Manual_cpuName
String set_CPUname = "Core i6-666k";

/* Manually name the GPU,*/
//#define Manual_gpuName
String set_GPUname = "GeForce GTX 666";

/* Manually set GPU ram total,*/
//#define Manual_gpuRam
String set_GPUram = "66";

//------------------ Threshold Triggers -------------------

/* Uncomment below, to enable custom threshold event triggers*/

/* User Custom  Triggers,*/
//#define enableCustomThesholdtriggers

/* Gnat-Tacho, NeoPixel ring bargraph example,*/
#define enableNeopixelGauges //
/* Global NeoPixel Brightness,*/
#define neoBrightness 20

/* uVolume only,*/
//#define uVol_enableThesholdtriggers


//--------------------- Other Stuff ----------------------

/* comment out, to disable blank screen on serial timeout to retain info eg: PC crash fault diagnostics  */
#define enableActivityChecker

/* Time between "DisplayStyle" changes */
#define displayChangeDelay 18000

/* Timer for active connection to host*/
#define lastActiveDelay 6000

//>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Delay screen event, to help stop screen data corruption ESP8622 use 25, most others 5 will do*/
int Serial_eventDelay = 15;
int baud = 115200; //serial do not adjust
//>>>>>>>>>>>>>>>>>>>>>>>>>>>

//------------------ End of User configuration --------------
