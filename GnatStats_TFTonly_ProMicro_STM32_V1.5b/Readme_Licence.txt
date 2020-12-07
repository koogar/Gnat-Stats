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

  Notes:

  I strongly suggest using this sketch with Atmel 32u4 based boards such as, the Leonardo or ProMicro, due to to its native USB support.

  The Windows application "HardwareSerialMonitor v1"  uses the OpenHardwaremonitor  OpenHardwareMonitorLib.dll to detect the hardware.  http://openhardwaremonitor.org/
  The Windows application "HardwareSerialMonitor v1.1"  uses the LibreHardwareMonitor OpenHardwareMonitorLib.dll to detect the hardware.  https://github.com/LibreHardwareMonitor/LibreHardwareMonitor

  The application will not detect integrated graphics as a GPU!!!
  Presently HardwareSerialMonitor does not like virtual Bluetooth COM ports present on the users PC!!!

  ALWAYS RUN "HARDWARE SERIAL MONITOR" AS ADMIN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  "Hardware Serial Monitor" Was inspired by the Visual Studio project kindly shared by psyrax see: https://github.com/psyrax/SerialMonitor


  ProMicro hookup:
  ----------------
  NeoPixel DataIn: P5 with 220r series resistor


    OLED Version 1     : Initial release
    OLED Version 1.1   : Fix intermittent screen flicker when in no activity mode "screen off" (due to inverter function?) fill the screen 128x64 black rectangle during this time.
    OLED Version 1.2   : Fix Freeze screen issue
    OLED Version 1.2.1 : Top Config option to disable/enable positive/negative screen cycle

    Move HSMonitor(v1.1) to .Net 4.6.2

    OLED Version 1.3   : Option to trigger an event at a given CPU or GPU threshold eg: LED indicator at 100% CPU Load.
                    Top Config option to disable all pre-selected power/gnd pins on Arduino pins D4 and D5 when not powering OLED from ProMicro
                    Top Config option to disable/enable "activitychecker" (Enable blank screen on serial timeout eg: PC powered down,
                    Disable to retain last sampled info eg: PC crash or overclocking diagnostics)

    OLED Version 1.31   : MOVE CONFLICTING!!! NEOPIXEL PIN TO 10

    OLED Version 1.4    : STM32 BluePill Support
                        
                        : Remove PowerPin Support

     TFT Version 1.5    : STM32 BluePill & ProMicro Suppport
                        : 128x160 ST7735 & 240x320 ILI9341 TFT Support
                        : Add PWM Output for Back Light
                        : Seperate "Configuration_Settings.h" to make settings easier
                    

         ToDo:
         Windows custom GnatStats device icon
         Auto or button screen change option,
         PC Diagnostic switch / mode eg: Min / Max readings,
         Analogue Panel Meter Readings output

  STM32 BluePill Reference Pins: i2c : SDA:PB7 - SCL:PB6  / PWM BackLight:PB0 /  STM32    SPi(Hardware):  CS:PB11 RST:PB10 DC:PB1 SCLK:PA5 MOSI:PA7
  32u4  ProMicro Reference Pins  i2c : SDA:2   - SCL:3    / PWM BackLight:6   /  ProMicro SPi(Hardware):  CS:10   RST:RST  DC:9   SCLK:15  MOSI:16 / Neopixel Pin: 5

  ASCII: http://patorjk.com/software/taag/

   _    ___ ___ ___    _   ___ ___ ___ ___
  | |  |_ _| _ ) _ \  /_\ | _ \_ _| __/ __|
  | |__ | || _ \   / / _ \|   /| || _|\__ \
  |____|___|___/_|_\/_/ \_\_|_\___|___|___/


  ATMEL Libraries
  ---------------

  Adafruit Atmel Neopixel
  https://github.com/adafruit/Adafruit_NeoPixel

  Adafruit Neopixel STM32 library
   Note. Library uses SPI1. Connect the WS2812B data input to MOSI (A7) on your board.
  https://github.com/rogerclarkmelbourne/Arduino_STM32/tree/master/STM32F1/libraries/WS2812B

  Adafruit GFX Library Atmel & STM32
  https://github.com/adafruit/Adafruit-GFX-Library

  ILI9341 TFT  Atmel & STM32
  https://github.com/adafruit/Adafruit_ILI9341

  ST7735 TFT  Atmel & STM32
  https://github.com/adafruit/Adafruit-ST7735-Library

*/