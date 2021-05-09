/*Optimised for 1.3" SPI Colour Round LCD ST7789V (240x240), Same ST7789 library as the square version*/

/*Portrait offsets,*/
int X_Offset = 40; // Landscape = 0
int Y_Offset = 40; //  Landscape = 0

void DisplayStyle_Circle_ESP () {



#ifdef enable_DualSerialEvent
  serialBTEvent();    // Check for Bluetooth Serial Activity
#endif

#ifdef enable_BT
  serialBTEvent();    // Check for Bluetooth Serial Activity
#else //USB
  serialEvent();     // Check for USB Serial Activity
#endif

#ifdef  enableActivityChecker
  activityChecker();      // Turn off screen when no activity
#endif

  /* TFT DRAW STATS */
  if (stringComplete) {

    if (bootMode) {

      //splashScreen2();

      tft.fillScreen(ILI9341_BLACK);

      tft.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
      tft.setFont(); // set to default Adafruit library font

      //tft.fillCircle(160, 120, 112, ILI9341_RED); // landscape circle 119 for radius -1 for line thickness
      tft.fillCircle(160 - X_Offset, 120 + Y_Offset, 112, ILI9341_BLACK); // landscape circle 119 for radius -1 for line thickness

      //tft.invertDisplay(true);
      //tft.invertDisplay(false);


      bootMode = false;
    }

    lastActiveConn = millis();


    //--------------------------------------- Display Background ----------------------------------------------------

    backlightON (); //Turn ON display when there is  activity



    //tft.setTextColor(ILI9341_BLACK, ILI9341_WHITE);
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);

#ifdef Debug
    tft.setTextColor(ILI9341_BLACK, ILI9341_RED); // used to stop flickering when updating digits that do not increase in length. CPU/GPU load still need a clear box on the end digits
#endif

    //tft.setCursor(284, 9);
    //tft.println("BT");
    //tft.fillCircle(240, 240, 0, ILI9341_BLUE);// Flash top right corner when updating  //see "serialEvent();" loop

    //            (X  , Y  , Rad,        Colour)
    //tft.drawCircle(160 - X_Offset , 120 + Y_Offset , 119, ILI9341_WHITE); // 240x240 landscape circle 119 for radius -1 for line tickness
    //tft.fillCircle(160 -X_Offset, 120 +Y_Offset, 112, ILI9341_RED); // landscape circle 119 for radius -1 for line tickness

    /* Display Background */
    //----------------------------------------- Boost/Turbo Clear Box----------------------------------------------


    /* CPU Portrait TURBO/TJMAX, */
    //tft.fillRoundRect  (107, 91, 86, 20, 4, ILI9341_BLACK);   //
    //tft.drawRoundRect  (106, 90, 88, 22, 4, ILI9341_SILVER); //

    /* GPU Portrait BOOST/TJMAX, */
    //tft.fillRoundRect  (107, 210, 86, 20, 4, ILI9341_BLACK);   //
    //tft.drawRoundRect  (106, 209, 88, 22, 4, ILI9341_SILVER); //

    /* Middle Line */
    tft.drawFastHLine(44 - X_Offset, 120 + Y_Offset, 236,  ILI9341_WHITE);
    //tft.drawFastVLine(160 - X_Offset, 04 + Y_Offset, 236,  ILI9341_WHITE);// test alignment center line

    /*GPU Memory Used Line */
    //tft.drawFastHLine(110, 170, 200, ILI9341_SILVER);

    //--------------------------------------Borders----------------------------------------

    /* (X  ,Y ,  W ,  H , Radius ,    Color*/

    /* CPU Outline, */
    //tft.drawRoundRect  (13,  22, 88,  89, 6,    ILI9341_WHITE);

    /* GPU Outline, */
    //tft.drawRoundRect  (13, 144, 88,  89, 6,    ILI9341_WHITE);

    //tft.drawRoundRect  (0,   0  , 320, 120, 8,    ILI9341_BLUE);

    //tft.drawRoundRect  (0, 124, 320, 116, 8,    ILI9341_GREEN);


    //------------------------------------CPU/GPU/RAM BMP IMAGES--------------------------------------------

    /* Blank CPU PCB BMP, */
    //tft.drawBitmap(16, 25, CPU3_BMP, 82, 82, ILI9341_GREEN);

#ifdef INTEL_CPU
    //tft.drawBitmap(16, 25, IntelCoreOnly_BMP, 88, 82, ILI9341_BLUE);
    //tft.drawBitmap(16, 25, IntelCoreOnly_BMP, 88, 82, ILI9341_SILVER);
#endif

#ifdef AMD_CPU
    //tft.drawBitmap(16, 25, AMDCoreOnly_BMP, 88, 82, ILI9341_RED);
#endif


    //tft.setTextSize(1);
    //tft.setCursor(116, 8); // (Left/Right, UP/Down)
    //tft.println("Temp     /     Load"); // CPU

    //tft.setTextSize(1);
    //tft.setCursor(200, 130);
    //tft.println("Load  /  Fan Load"); // GPU

    //tft.setTextSize(3);
    //tft.setCursor(1, 132); // (Left/Right, UP/Down)

#ifdef NVIDIA_GRAPHICS
    //tft.drawBitmap(16, 148, Nvidia_Logo_BMP, 82, 82, ILI9341_GREEN); // Nvidia Logo
#endif

#ifdef AMD_GRAPHICS
    //tft.drawBitmap(16, 148, RADEON_Logo_BMP, 82, 82, ILI9341_RED); // Nvidia Logo
#endif

#ifdef INTEL_GRAPHICS
    //tft.fillRoundRect  (14, 141, 86,  87, 5,    ILI9341_BLUE);  // INTEL GPU Logo
    //tft.drawBitmap(13, 147, IntelCoreOnly_BMP, 88, 82, ILI9341_BLUE);
#endif


    //---------------------------------------CPU & GPU Hardware ID---------------------------------------------------------

    /* CPU & GPU Hardware ID */

    if (inputString.indexOf("CPU") > -1)
    {

      String cpuName = "";

      tft.setTextSize(1);
      tft.setCursor(122 - X_Offset, 19 + X_Offset); // (Left/Right, UP/Down)
      //tft.setCursor(-35, 1);

      int cpuNameStart = inputString.indexOf("CPU:");
      if (inputString.indexOf("Intel", cpuNameStart) > -1) {
        cpuNameStart = cpuNameStart + cpuNameStartLength;
      }
      else {
        cpuNameStart = cpuNameStart + 8;
      }
      if (inputString.indexOf("GPU") > -1)
      {
        cpuName = inputString.substring(cpuNameStart, inputString.indexOf("GPU:"));
      }
      else
        cpuName = inputString.substring(cpuNameStart);

      /* CPU Manual Name*/
#ifdef Manual_cpuName
      tft.println(set_CPUname);
#else
      /* CPU Auto Detect Name*/
      tft.println(cpuName);
#endif

    }
    if (inputString.indexOf("GPU") > -1)
    {
      tft.setTextSize(1);
      tft.setCursor(100 - X_Offset, 130 + Y_Offset); // Position GPU Name
      //tft.setCursor(-41, 28);   // Negative spacing so, Nvidia doesn't cause a rollover, on the next line
      int gpuNameStart = inputString.indexOf("GPU:");
      if (inputString.indexOf("NVIDIA", gpuNameStart) > -1) {
        gpuNameStart = gpuNameStart + gpuNameStartLength;
      }
      else {
        gpuNameStart = gpuNameStart + 8;
      }

      int gpuNameEnd = inputString.indexOf("|", gpuNameStart);


      /* GPU Manual Name*/
#ifdef Manual_gpuName
      String gpuName = set_GPUname; // Name spacing test
#else
      /* GPU Auto Detect Name*/
      String gpuName = inputString.substring(gpuNameStart, gpuNameEnd);
#endif

      tft.println(gpuName);
    }

    //------------------------------------------------------RX indicator---------------------------------------------------

#ifdef enable_BT
    tft.setCursor(284, 9);
    tft.println("BT");
    tft.fillCircle(306, 12, 7, ILI9341_BLUE);// Flash top right corner when updating  //see "serialEvent();" loop
    tft.drawCircle(306, 12, 8, ILI9341_WHITE);

    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 111, ILI9341_BLUE); // landscape circle 119 for radius -1 for line tickness
    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 112, ILI9341_BLUE); // landscape circle 119 for radius -1 for line tickness
    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 113, ILI9341_BLUE); // landscape circle 119 for radius -1 for line tickness
    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 114, ILI9341_BLUE); // landscape circle 119 for radius -1 for line tickness
    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 115, ILI9341_BLUE); // landscape circle 119 for radius -1 for line tickness
    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 116, ILI9341_WHITE); // landscape circle 119 for radius -1 for line tickness
    //tft.drawCircle(160, 120, 117, ILI9341_BLUE); // landscape circle 119 for radius -1 for line tickness
#else
    tft.setCursor(284, 9);
    tft.println("RX");
    tft.fillCircle(306, 12, 7, ILI9341_RED);// Flash top right corner when updating  //see "serialEvent();" loop
    tft.drawCircle(306, 12, 8, ILI9341_WHITE);


    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 111, ILI9341_GREEN); // // flash circle surround
    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 112, ILI9341_GREEN); // // flash circle surround
    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 113, ILI9341_GREEN); // // flash circle surround
    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 114, ILI9341_GREEN); // // flash circle surround
    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 115, ILI9341_GREEN); // // flash circle surround
    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 116, ILI9341_GREEN); // // flash circle surround
    //tft.drawCircle(160 -X_Offset, 120 +Y_Offset, 117, ILI9341_GREEN); // // flash circle surround
#endif

    //--------------------------------------------DATA CLEARING BOXES------------------------------------------------------

    /* New Update Clearing Boxes see: tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);*/
#ifdef Debug

    tft.setTextColor(ILI9341_WHITE, ILI9341_RED);

#define ILI9341_updateBox ILI9341_GREY  // Fill boxes grey for text alignment 

#else

#define ILI9341_updateBox  ILI9341_BLACK // Default for normal running

#endif

    //------------------------------------------ CPU Load/Temp -------------------------------------------------

    /* CPU Display String */
    int cpuStringStart = inputString.indexOf("C");
    int cpuDegree = inputString.indexOf("c");
    int cpuStringLimit = inputString.indexOf("|");
    String cpuString1 = inputString.substring(cpuStringStart + 1, cpuDegree);
    String cpuString2 = inputString.substring(cpuDegree + 1, cpuStringLimit - 1);

    //Char erase and spacing adjust, MaDerer
    /* CPU TEMP,*/
    if (cpuString1.length() == 1) cpuString1 = " "  + cpuString1;

    /* CPU LOAD,*/
    if (cpuString2.length() == 3) cpuString2 = " "  + cpuString2;
    if (cpuString2.length() == 2) cpuString2 = "  " + cpuString2;

    /* CPU TEMPERATURE */
    tft.setTextSize(3);
    tft.setCursor(88 - X_Offset, 72 + Y_Offset); // (Left/Right, UP/Down)
    tft.print(cpuString1);  // CPU TEMP
    //tft.println("100"); // Test Spacing
    tft.setTextSize(1);

#ifdef noDegree
    tft.print("C");       // Centigrade Symbol
#else
    tft.print((char)247); //Degrees Symbol
    tft.print("C");       // Centigrade Symbol
#endif

    /* CPU LOAD, ALL CORES */
    tft.setTextSize(3);
    tft.setCursor(146 - X_Offset, 72 + Y_Offset); // (Left/Right, UP/Down)
    tft.print(cpuString2);  // CPU Load

#ifdef  smallPercent
    tft.setTextSize(2);
    tft.print("%");
#else
    tft.setTextSize(3);
    tft.print("%");
#endif

    //------------------------------------------ CPU Freq -------------------------------------------------

    /* CPU Freq Display String*/
    int cpuCoreClockStart = inputString.indexOf("CHC") + 3;
    int cpuCoreClockEnd = inputString.indexOf("|", cpuCoreClockStart);
    String cpuClockString = inputString.substring(cpuCoreClockStart, cpuCoreClockEnd);

    //Char erase and spacing adjust, MaDerer
    while (cpuClockString.length() < 4) cpuClockString = " " + cpuClockString;

    /* CPU OVERCLOCK Freq Gain */
    double cpuOverclockGain = atof(cpuClockString.c_str());
    double  cpuOverclockSum = cpuOverclockGain - CPU_BOOST; //values in Mhz

    /* CPU OVERCLOCK Freq Gain in Percent, eg: 3700MHz/100 = 37MHz(1%)  , (OC Gain)895MHz / 37MHz(1%) = 24.19%,*/

    double cpuOverclockGainPercentSum = cpuOverclockSum / (CPU_BOOST / 100); // % of gain over Stock CPU

    /* CPU  Freq Display */
    tft.setTextSize(4);
    tft.setCursor(114 - X_Offset, 35 + Y_Offset ); // (Left/Right, UP/Down)
    tft.print(cpuClockString);
    tft.setTextSize(1);
    tft.print("MHz");

    /* CPU OVERCLOCK Display Freq Gain */
    //tft.setCursor(225, 48);// (Left/Right, UP/Down)
    //tft.setTextSize(1);
    //tft.print ("CPU O/C: ");
    //tft.print(cpuOverclockSum, 0); // Show Value in MHZ
    //tft.println ("MHz");

#ifdef  enable_ShowFrequencyGain

    /* CPU OVERCLOCK Display Freq Gain in MHz */
    tft.setCursor(109, 94);// (Left/Right, UP/Down)

    //tft.print ("O/C:+ ");

#ifdef ShowFrequencyGainMHz
    tft.setTextSize(2);
    tft.print ("+");
    tft.print(cpuOverclockSum, 0);            // Show Value in MHz
    tft.setTextSize(1);
    tft.println ("MHz");
#endif
#ifdef ShowFrequencyGain%
    tft.setTextSize(2);
    tft.print (" +");
    tft.print(cpuOverclockGainPercentSum, 0); // Show Value in %
    tft.println ("%");
#endif
#endif



    //------------------------------------------ GPU Load/Temp -------------------------------------------------

    /* GPU Display String */
    int gpuStringStart = inputString.indexOf("G", cpuStringLimit);
    int gpuDegree = inputString.indexOf("c", gpuStringStart);
    int gpuStringLimit = inputString.indexOf("|", gpuStringStart);
    String gpuString1 = inputString.substring(gpuStringStart + 1, gpuDegree);
    String gpuString2 = inputString.substring(gpuDegree + 1, gpuStringLimit - 1);

    //Char erase and spacing adjust, MaDerer
    /* GPU TEMP,*/
    if (gpuString1.length() == 1) gpuString1 = " "  + cpuString1;
    /* GPU LOAD,*/
    if (gpuString2.length() == 3) gpuString2 = " "  + gpuString2;
    if (gpuString2.length() == 2) gpuString2 = "  " + gpuString2;

    /* GPU TEMPERATURE */
    tft.setTextSize(3);
    tft.setCursor(88 - X_Offset, 144 + Y_Offset); // (Left/Right, UP/Down)
    tft.print(gpuString1);
    tft.setTextSize(1);

#ifdef noDegree
    tft.print("C");       // Centigrade Symbol
#else
    tft.print((char)247); //Degrees Symbol
    tft.print("C");       // Centigrade Symbol
#endif

    /* GPU LOAD */
    tft.setTextSize(3);
    tft.setCursor(146 - X_Offset, 144 + Y_Offset); // (Left/Right, UP/Down)
    tft.print(gpuString2);

#ifdef  smallPercent
    tft.setTextSize(2);
    tft.print("%");
#else
    tft.setTextSize(3);
    tft.print("%");
#endif



    //------------------------------------------ GPU Freq/Temp -------------------------------------------------

    /* GPU temp V's GPU freq to check for throttling and max 'GPU Boost' */

    /* GPU Core Freq, */
    int gpuCoreClockStart = inputString.indexOf("GCC") + 3;
    int gpuCoreClockEnd = inputString.indexOf("|", gpuCoreClockStart);
    String gpuCoreClockString = inputString.substring(gpuCoreClockStart, gpuCoreClockEnd);

    //Char erase and spacing adjust, MaDerer
    while (gpuCoreClockString.length() < 4) gpuCoreClockString = " " + gpuCoreClockString;

    /* GPU VRAM Freq, */
    int gpuMemClockStart = inputString.indexOf("GMC") + 3;
    int gpuMemClockEnd = inputString.indexOf("|", gpuMemClockStart);
    String gpuMemClockString = inputString.substring(gpuMemClockStart, gpuMemClockEnd);

    /* GPU SHADER Freq, */
    int gpuShaderClockStart = inputString.indexOf("GSC") + 3;
    int gpuShaderClockEnd = inputString.indexOf("|", gpuShaderClockStart);
    String gpuShaderClockString = inputString.substring(gpuShaderClockStart, gpuShaderClockEnd);

    /* GPU OVERCLOCK Freq Gain in MHz, */
    double gpuOverclockGain = atof(gpuCoreClockString.c_str());
    double  gpuOverclockSum = gpuOverclockGain - GPU_BOOST; //values in Mhz

    /* GPU OVERCLOCK Freq Gain in Percent, eg: 1683MHz/100 = 16.83MHz(1%) , (OC Gain)254MHz / 16.83MHz(1%) = 15.09%,*/
    double gpuOverclockGainPercentSum = gpuOverclockSum / (GPU_BOOST / 100); // % of gain over Stock GPU


#ifdef  enable_ShowFrequencyGain
    /* GPU OVERCLOCK Display Freq Gain, */
    //tft.setCursor(225, 56);// (Left/Right, UP/Down)
    tft.setCursor(109, 213);
    //tft.print ("GPU O/C: ");

#ifdef ShowFrequencyGainMHz
    tft.setTextSize(2);
    tft.print ("+");
    tft.print(gpuOverclockSum, 0);            // Show Value in MHz
    tft.setTextSize(1);
    tft.println ("MHz");
#endif
#ifdef ShowFrequencyGain%
    tft.setTextSize(2);
    tft.print ("  +");
    tft.print(gpuOverclockGainPercentSum, 0); // Show Value in %
    tft.println ("%");
#endif

#endif


    tft.setCursor(200, 180);// (Left/Right, UP/Down)
    tft.setTextSize(1);
    //tft.print("VRAM     :");
    //tft.print(gpuMemClockString);

    tft.setTextSize(1);
    //tft.print("MHz");

    tft.setCursor(200, 190); // (Left/Right, UP/Down)
    tft.setTextSize(1);
    //tft.print("Shader   :");
    //tft.print(gpuShaderClockString);

    tft.setTextSize(1);
    //tft.print("MHz");

    tft.setTextSize(4);
    tft.setCursor(114 - X_Offset, 200 - 30 + Y_Offset); // (Left/Right, UP/Down)
    //tft.print("Core     :");
    tft.print(gpuCoreClockString);

    tft.setTextSize(1);
    tft.print("MHz");       // Centigrade Symbol

    //----------------------------------------------GPU Memory Total----------------------------------------------------------

    int gpuMemoryStart = inputString.indexOf("GMT") + 3;
    int gpuMemoryEnd = inputString.indexOf("|", gpuMemoryStart);
    String gpuMemoryString = inputString.substring(gpuMemoryStart, gpuMemoryEnd);
    //Char erase and spacing adjust, MaDerer
    while (gpuMemoryString.length() < 4) gpuMemoryString = " " + gpuMemoryString;

    double totalGPUmem = atof(gpuMemoryString.c_str());
    double totalGPUmemSum = totalGPUmem / 1024;    // divide by 1024 to get the correct value
    float  totalGPUmemSumDP = totalGPUmemSum ;     // float to handle the decimal point when printed (totalGPUmemSumDP, 0)

    tft.setTextSize(1);
    tft.setCursor(200 - X_Offset, 130 + Y_Offset); // Position GPU Total Memory

#ifdef Manual_gpuRam
    tft.print(set_GPUram);
#else
    tft.print(totalGPUmemSumDP, 0); // Show Value in GB
#endif

    tft.setTextSize(1);
    tft.print("GB");
    //----------------------------------------------GPU Memory Used----------------------------------------------------------

    /*GPU Memory Used */
    int gpuMemoryUsedStart = inputString.indexOf("GMU") + 3;
    int gpuMemoryUsedEnd = inputString.indexOf("|", gpuMemoryUsedStart);
    String gpuMemoryUsedString = inputString.substring(gpuMemoryUsedStart, gpuMemoryUsedEnd);
    //Char erase and spacing adjust, MaDerer
    while (gpuMemoryUsedString.length() < 4) gpuMemoryUsedString = " " + gpuMemoryUsedString;

    tft.setCursor(123 + 4 - X_Offset, 179 + 25 + Y_Offset); // (Left/Right, UP/Down)
    tft.setTextSize(3);
    tft.print(gpuMemoryUsedString); //  show values in MB

    tft.setTextSize(1);
    tft.print("MB");



    //------------------------------------------------GPU Power Consumption--------------------------------------------------------
#ifdef enable_gpuPowerStats

    /* GPU Power */  // Nvidia Driver 457.51 works. Broken in Driver Version: 460.79 460.89
    int gpuPowerStart = inputString.indexOf("GPWR") + 4;
    int gpuPowerEnd = inputString.indexOf("|", gpuPowerStart);
    String gpuPowerString = inputString.substring(gpuPowerStart, gpuPowerEnd);
    //Char erase and spacing adjust, MaDerer
    while (gpuPowerString.length() < 6) gpuPowerString = " " + gpuPowerString;

    tft.setTextSize(1);
    tft.setCursor(200, 222);   // (Left/Right, UP/Down)
    tft.print("Power    :");
    tft.print(gpuPowerString); //GPU Power Watts

    tft.setTextSize(1);
    tft.print("w");
#endif

    //------------------------------------------------GPU FAN Speed Percentage-------------------------------------------------------
#ifdef enable_gpuFanStats%
    /* GPU Fan Load% */
    int gpuFanStart = inputString.indexOf("GFANL") + 5;  //
    int gpuFanEnd = inputString.indexOf("|", gpuFanStart );
    String gpuFanString = inputString.substring(gpuFanStart, gpuFanEnd);
    //Char erase and spacing adjust, MaDerer
    while (gpuFanString.length() < 3) gpuFanString = " " + gpuFanString;

    tft.setTextSize(3);
    tft.setCursor(242, 144);   // (Left/Right, UP/Down)
    //tft.print("Fan Load :");
    tft.print(gpuFanString);   //GPU Fan %

#ifdef  smallPercent
    tft.setTextSize(2);
    tft.print("%");
#else
    tft.setTextSize(3);
    tft.print("%");
#endif
#endif

#ifdef enable_gpuFanStatsRPM
    /* GPU Fan RPM */
    int gpuRPMStart = inputString.indexOf("GRPM") + 4;
    int gpuRPMEnd = inputString.indexOf("|", gpuRPMStart);
    String gpuRPMString = inputString.substring(gpuRPMStart, gpuRPMEnd);
    //Char erase and spacing adjust, MaDerer
    while (gpuRPMString.length() < 4) gpuRPMString = " " + gpuRPMString;

    tft.setTextSize(1);
    //tft.setCursor(150, 120); // (Left/Right, UP/Down)
    tft.setCursor(200, 210);   // (Left/Right, UP/Down)
    tft.print("Fan Speed:");
    tft.print(gpuRPMString);   //GPU Fan RPM

    tft.setTextSize(1);
    tft.print("RPM");
#endif
    //----------------------------------------SYSTEM RAM USAGE---------------------------------------------------

    /* SYSTEM RAM String */
    int ramStringStart = inputString.indexOf("R", gpuStringLimit);
    int ramStringLimit = inputString.indexOf("|", ramStringStart);
    String ramString   = inputString.substring(ramStringStart + 1 , ramStringLimit - 2);
    //Char erase and spacing adjust, MaDerer
    while (ramString.length() < 4) ramString = " " + ramString;

    /* SYSTEM RAM AVALABLE String */
    int AramStringStart = inputString.indexOf("RA", ramStringLimit);
    int AramStringLimit = inputString.indexOf("|", AramStringStart);
    String AramString = inputString.substring(AramStringStart + 2 , AramStringLimit);
    //Char erase and spacing adjust, MaDerer
    while (AramString.length() < 5) AramString = " " + AramString;

    /* SYSTEM RAM TOTAL String */
    double intRam = atof(ramString.c_str());
    double intAram = atof(AramString.c_str());
    //double  intRamSum = intRam + intAram;
    float  intRamSum = intRam + intAram; //float to handle the decimal point when printed (intRamSum,0)

    /* RAM & TOTAL */

    tft.setCursor(110 - X_Offset, 100 + Y_Offset); // (Left/Right, UP/Down)
    tft.setTextSize(2);
    tft.print(intRamSum, 0) ; tft.setTextSize(0); tft.print("GB"); tft.print(" / ");
    tft.setTextSize(2);
    tft.print(ramString)    ; tft.setTextSize(0); tft.println("GB");

    //------------------------------------------ RX indicator Clear------------------------------------------------

    delay(TX_LED_Delay);

    tft.fillCircle(306, 12, 7, ILI9341_BLACK);// Flash top right corner when updating

    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 111, ILI9341_BLACK); // landscape circle 119 for radius -1 for line thickness
    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 112, ILI9341_BLACK); // landscape circle 119 for radius -1 for line thickness
    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 113, ILI9341_BLACK); // landscape circle 119 for radius -1 for line thickness
    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 114, ILI9341_BLACK); // landscape circle 119 for radius -1 for line thickness
    tft.drawCircle(160 - X_Offset, 120 + Y_Offset, 115, ILI9341_BLACK); // landscape circle 119 for radius -1 for line thickness
    //tft.drawCircle(160 -X_Offset, 120 +Y_Offset, 116, ILI9341_BLACK); // landscape circle 119 for radius -1 for line thickness
    //tft.drawCircle(160 -X_Offset, 120 +Y_Offset, 117, ILI9341_BLACK); // landscape circle 119 for radius -1 for line thickness

    //-------------------------------------------------------------------------------------------------------------

    displayDraw = 1;

    inputString = "";
    stringComplete = false;
    //tft.fillScreen(ILI9341_BLACK);

  }
}
