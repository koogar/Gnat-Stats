
//------------------------------- BT Limitations --------------------------------------

/*If BT is enabled you can not use HardwareSerialMonitor with USB serial, even though it is visible.
  You can still upload new code through the Arduino IDE as normal.

  Currently when using BT you only have to connect the device to Windows, no pairing is needed.
  When disconnected, you will need to manualy reconnect in HardwareSerialMonitor by clicking
  on the correct COM port “Standard Serial over Bluetooth link”.

  Note: Once connected, two “Standard Serial over Bluetooth link” will be visible
  one is Send, the other is Receive.
  When you know the correct port for Send you can disable the other in Device Manager
  so it does not to show up in HardwareSerialMonitor.*/

//--------------------------- Bluetooth or USB serial -----------------------------------
/*ESP32 Communication type, Uncomment only one option!!!*/

/*Uncomment to enable BT, else default to USB serial only,*/
//#define enable_BT

/*Uncomment to enable BT and USB serial,*/
#define enable_DualSerialEvent

//-------------------------------- DISCLAIMER -------------------------------------------
/*
  !!!THE WEMOS LOLIN32, NOT LIMITED TO, APPEARS TO HAVE NO "UNDERVOLTAGE PROTECTION"
  OR "OVER DISCHARGE PROTECTION" ON THE CHARGING CIRCUIT!!!

  OTHER BOARDS ARE THE SAME!!! USE A LiPo BATTERY WITH BUILT IN PROTECTION, EVEN THEN,
  BUILT IN PROTECTION IS CONSIDERED A LAST RESORT SAFETY NET OR "BELTS AND BRACERS" APPROACH.

  YOU MAY GET SOME BENEFITS, OVERVOLTAGE,OVERCURRENT AND SHORT CIRCUIT PROTECTION BUT, USUALLY
  THE OVER DISCHARGE PROTECTION CUT OFF VOLTAGE IS AROUND 2.4v WHICH IS WAY TOO LOW FOR THE
  CONTINUED MAINTAINED HEALTH OF THE BATTERY.

  RECOMMENDED OVER DISCHARGE PROTECTION VOLTAGES FOR LiPo's ARE AROUND 2.9 - 3 VOLTS.

  ALTERNATIVELY USE A BATTERY BANK THROUGH THE USB CONNECTOR

  !!!LITHIUM POLYMER PACKS / BATTERIES CAN BE VERY DANGEROUS, WITH A RISK OF FIRE!!! 

  If you are going to use a battery or LiPo pack you must take some responsibility, do your research!!!.
  No advice will be given, or implied regarding which you should use etc.

  Use the battery/type in accordance with the manufacturer's recommendations.*/
  

//--------------------- OLED Setup --------------------------
/*Uncomment the correct OLED display type, uncomment only one!!!*/

#define OLED_SSD1306
//#define OLED_SH1106

//>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

//>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*Rotate the display at the start:  0 or 2  (0, 180 degrees)*/
#define rotateScreen 2

/* Uncomment below, to enable positive and negative screen cycler */
//#define enableInvertscreen

/* Uncomment below, to take out small degree symbol for better spacing
   when hitting 100% cpu/gpu load the percent symbol gets clipped */
//#define noDegree

//--------------- Manual CPU/GPU Display Name Entry -------------------------
/* Requires DisplayStyles ending in "_NC" (NameChange),*/

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

//>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* Enable the built in LED blinking when transmitting, saves power when using battery if disabled,*/
#define enableTX_LED

//>>>>>>>>>>>>>>>>>>>>>>>>>>>

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
