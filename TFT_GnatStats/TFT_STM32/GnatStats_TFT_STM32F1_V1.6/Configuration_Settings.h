/*
      ____  __  _____  ______   ______________  ___________    __________________
     / __ \/ / / /   |/_  __/  / ___/_  __/   |/_  __/ ___/   /_  __/ ____/_  __/
    / /_/ / /_/ / /| | / /_____\__ \ / / / /| | / /  \__ \     / / / /_    / /
   / ____/ __  / ___ |/ /_____/__/ // / / ___ |/ /  ___/ /    / / / __/   / /
  /_/   /_/ /_/_/  |_/_/     /____//_/ /_/  |_/_/  /____/    /_/ /_/     /_/

  /*

  GNAT-STATS & PHAT-STATS PC Performance Monitor - Version 1.x  Rupert Hirst & Colin Conway © 2016
  http://tallmanlabs.com  & http://runawaybrainz.blogspot.com/

  Licence
  -------

  Attribution-NonCommercial-ShareAlike  CC BY-NC-SA

  This license lets others remix, tweak, and build upon your work non-commercially, as long as they credit you and license their new creations under the identical terms.

  https://creativecommons.org/licenses/

  https://rop.nl/truetype2gfx/   //truetype2gfx - Converting fonts from TrueType to Adafruit GFX
  http://slemi.info/2020/03/19/custom-glcd-font-tutorial/



  Notes:
  Link Below for the STM32 Bootloader and Arduino Core (you may have to install the Arduino Due core also for the compiler.

  https://github.com/rogerclarkmelbourne/Arduino_STM32

  https://github.com/rogerclarkmelbourne/STM32duino-bootloader/tree/master/binaries

  BluePill_generic_boot20_pc13.bin  (On the "Bluepill" bootloader "_pc13" refers to the LED pin. )

  https://github.com/rogerclarkmelbourne/Arduino_STM32/wiki/Installation

    Adafruit_GFX Version 1.8.0 and higher doesn't compile for ESP8266 & STM32 Boards -
  Downgrade to Adafruit_GFX Version 1.7.5 in the library manager.

  UNO/NANO/MINI are not supported!!! use this sketch with STM32/ESP8622/ATSAMD21 based boards , due to larger memory.

  The Windows application "HardwareSerialMonitor v1.3"  uses the OpenHardwareMonitorLib.dll to detect the hardware, OpenHardwareMonitor is not required!!  http://openhardwaremonitor.org/

  This Sketch Requires HardwareSerialMonitor v1.3 or higher

  "Hardware Serial Monitor" Was inspired by the Visual Studio project kindly shared by psyrax see: https://github.com/psyrax/SerialMonitor


  V1.58:  STM32 ( / ILI9431 TFT (320 x 240) only preview version for the new features in HardwareSerialmonitor v1.3.

          Button to change between portrait and landscape mode.

          Additional GPU Features:
          Fan Speed Load%, Fan Speed RPM, Total Memory, Used Memory, Current Power Consumption in Watts (Nvidia).

          Additional system RAM features:
          Total Memory, Available Memory, Memory Load.

          Config Options:
          Intel/AMD  CPU and GPU Bitmaps.
          Specify CPG/GPU TJMax Warnings.


  V1.58b:
        Config Options:
        Debug Screen CFG Setting.
        PWM Backlight Direct Pin Connection for 3.3v.
        PWM Backlight PNP Transitor Pin Connection for 5v.

  V1.59:
        Rotary Encoder Brightness Control.

v1.59.6:
        ADD: CPU Turbo & GPU Boost Clock Indicator with Overclock Frequency Gain Display

        Minimise Screen Refresh Blinking using "tft.setTextColor(Text, Background);"
        and "Magic Digit Eraser" Function for digits that gain in length.
        (the above only works for the default font!!! (This is a limitation of the GRFX library)

   v1.6:

        ADD: Tweaks


  Note: Gnat-Stats/Phat-Stats is optimised for desktop CPU's with dedicated graphics cards, such as Nvidia/Radeon.
      You may get weird results on mobile CPUs and integrated GPU's (iGPU's) on laptops.

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


/* Debug Screen, Update Erasers, */
//#define Debug
//-------------------------------------------------------

/* Uncomment your CPU,*/
//#define AMD_CPU
#define INTEL_CPU

/* Uncomment your GPU,*/
//#define NVIDIA_GRAPHICS
#define AMD_GRAPHICS

//-------------------------------------------------------

/* CPU & GPU Thermal Junction Max Temperature before throttling,*/
#define CPU_TJMAX 100  //  TJ Max for the Intel 9900K    = 100c
#define GPU_TJMAX 83   //  TJ Max for the Nvidia GTX1080 = 83c

/* CPU & GPU Turbo/Boost Frequency Values */
#define CPU_BOOST 3700  //  Intel Core i9600k = 3700MHz Turbo to 4600MHz
#define GPU_BOOST 1683  //  MSi GamingX 1080 = 1683MHz

//-------------------------------------------------------

#define noDegree      // lose the "o"
#define smallPercent  // Use small percent symbol

/* Characters to delete from the start of the CPU/GPU name eg: Remove "Intel" or "Nvidia" to save space*/
#define cpuNameStartLength 10
#define gpuNameStartLength 11

//-------------------------------------------------------

/* Uncomment below to enable custom triggers,*/

#define CPU_OverClocked // Uncomment if your CPU is overclocked with Turbo boost disabled, to stop "TURBO" indicator

#define enable_ShowFrequencyGain // Show Overlock/Turbo & Boost Clock Frequency Gains  eg: "+985MHz"

#define enable_ThrottleIndicator // Show TJMax Indicator 

#define enable_BoostIndicator    // Show CPU & GPU Turbo/Boost Indicator

//-------------------------------------------------------

/* Define your Backlight PWM, Uncomment only one choice, */

/* PWM Using a Static fixed value, connected direct to the MCU PIN*/
//#define Static_PWM // use Fixed value for PWM screen brightness control with NPN Transistor . initial start brightness

/* PWM connected direct to the MCU PIN*/
#define Encoder_PWM // use rotary encoder for PWM screen brightness control with no Transistor 3.3v . initial start brightness

/* PWM Using a Rotary Encoder with a PNP transistor*/
/* 3906 PNP Transitor - VCC ((E)Emitter) - ((B)Base) MCU PIN Through Series Resistor 1k+ ((C)Collector)  TFT Back Light+ */
//#define Encoder_PWM_PNP // use rotary encoder for PWM screen brightness control with NPN Transistor 5v.

//-------------------------------------------------------

/* Direct MCU connection start-up level. Predefined Brightness Start-UP Level,*/
#ifdef Static_PWM
int TFT_brightness = 255; // 0 - 255
#endif

/* Do not adjust, it will affect the GUI % value */
#ifdef Encoder_PWM
int TFT_brightness = 100;

#endif
/* Do not adjust, it will affect the GUI % value */
#ifdef Encoder_PWM_PNP
int TFT_brightness = 155;
#endif

//-------------------------------------------------------

/* Uncomment below to blank the screen on serial timeout to retain info eg: PC crash fault diagnostics  */
#define enableActivityChecker

/* How long the display takes to timeout due to inactive serial data from the windows application */
#define lastActiveDelay 10000

//------------------------------------------------------------------------------------------------------------


/* Display screen rotation  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)*/
int ASPECT = 0; //Do not adjust,

/* Debounce Rotary Encoder Button,Sometimes it gets caught during a screen refresh and doesnt change*/
int debounceEncButton = 200; //  Use a 0.1uf/100nf/(104) ceramic capacitor from button Pin to GND and set at "0"

/* Delay screen event, to stop screen data corruption ESP8622 use 25, most others 5 will do*/
int Serial_eventDelay = 0; //
