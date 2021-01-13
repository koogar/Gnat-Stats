

    
/*
  Feather M0 (untested)
  ------------
  ATSAMD21G18 @ 48MHz with 3.3V logic/power
  256KB of FLASH + 32KB of RAM

  --------------
  (TFT)
  CS     =  17-A3 /PB04
  RST    =  18-A4 / PB05
  DC     =  19-A5 /PB02
  SCLK   =  24    /PB11
  MOSI   =  23    /PB10
  MISO   =  22    /PA12
  BLIGHT =  5 or 9/A7    /PA15

  Rotary Encoder
  ---------------
  EncoderA = 16/PB09
  EncoderB = 15/PB08

  Button   = 14/PB02
  ---------------

  SCL = 27       /32/PA23
  SDA = 26       /31/PA22
  
  Built in LED     = 13
  Built in Neopixel=  8

  //-------------------------------------------

  ESP32 LOLIN32 V1 (untested)
  --------------

  Flash memory  4M bytes
  Clock speed 240MHz

  (TFT)
  CS     = 02/
  RST    = 15/
  DC     = 17/
  SCLK   = 18/
  MOSI   = 23/
  MISO   = 19/
  BLIGHT = 0 /

  Rotary Encoder
  ---------------
  EncoderA = 04/
  EncoderB = 16/

  Button   = 17/
  ---------------

  SCL = 22
  SDA = 21

  //-------------------------------------------

  ESP8266 (NodeMCU 0.9)
  ------------
    (TFT)
  CS     = D8
  RST    = D0
  DC     = D4
  SCLK   = D5
  MOSI   = D7
  BLIGHT = D6

  Button   = D1
  ---------------

  SCL = D1
  SDA = D2

  SPARE = A0
*/
