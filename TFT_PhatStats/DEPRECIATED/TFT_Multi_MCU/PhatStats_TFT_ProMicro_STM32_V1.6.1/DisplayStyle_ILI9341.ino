/*
   _____ _____  _____ _____  _           __     __  _    _ _ _____  ______  _____
  |  __ \_   _|/ ____|  __ \| |        /\\ \   / / | |  | (_)  __ \|  ____|/ ____|
  | |  | || | | (___ | |__) | |       /  \\ \_/ /  | |__| |_| |__) | |__  | (___
  | |  | || |  \___ \|  ___/| |      / /\ \\   /   |  __  | |  _  /|  __|  \___ \
  | |__| || |_ ____) | |    | |____ / ____ \| |    | |  | | | | \ \| |____ ____) |
  |_____/_____|_____/|_|    |______/_/    \_\_|    |_|  |_|_|_|  \_\______|_____/

*/

/*Optimised for ILI9341 320 x 240 in portrait*/

void DisplayStyleTFT_ILI9341 () {  // When rotated 90 degrees, max coordinate 232 pixels down

  //--------------------------------------- Display Background ----------------------------------------------------

  /* Display Background */
#ifdef TFT_ILI9341
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);

  //--------------------------------------Borders----------------------------------------

  /*                 (X  ,Y ,  W ,  H , Radius ,    Color*/

  /* CPU Outline, */
  tft.drawRoundRect  (0,   0, 240, 103, 4,     ILI9341_BLUE);

  /* GPU Outline, */
  tft.drawRoundRect  (0, 105, 240, 136, 4,   ILI9341_GREEN);

  /* RAM Outline, */
  tft.drawRoundRect  (0, 242, 240, 47, 4,  ILI9341_YELLOW);

  /* USER Area Outline, */
  tft.drawRoundRect  (0, 290, 240, 27, 4,  ILI9341_RED);
  tft.setTextSize(1);
  tft.setCursor(4, 300);
  tft.print("TallManLabs.com - Phat-Stats ");
  //Set version
  tft.setTextSize(1);
  tft.print("TFT:v");
  tft.print (CODE_VERS);

#endif

  tft.setCursor(4, 27);
  tft.setTextSize(3);
  tft.println("CPU");

  tft.setTextSize(1);
  tft.setCursor(4, 60);
  tft.println("Temp/Load");

  tft.setTextSize(1);
  tft.setCursor(4, 76);
  tft.println("Frequency");

  tft.setTextSize(3);
  tft.setCursor(4, 132);
  tft.println("GPU");

  tft.setTextSize(1);
  tft.setCursor(4, 156);
  tft.println("Temp/Load");

  //displayDraw = 1;



  //---------------------------------------CPU & GPU Hardware ID----------------------------------------------------

  /*CPU & GPU Hardware ID*/

  if (inputString.indexOf("CPU") > -1)
  {
    String cpuName = "";
    tft.setTextSize(2);
    tft.setCursor(4, 4);

    int cpuNameStart = inputString.indexOf("CPU:");
    if (inputString.indexOf("Intel", cpuNameStart) > -1) {
      cpuNameStart = cpuNameStart + 10;
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
    tft.println(cpuName);

  }
  if (inputString.indexOf("GPU") > -1)
  {
    tft.setTextSize(2);
    tft.setCursor(4, 110);  // Position GPU Name
    //tft.setCursor(-41, 28);   // Negative spacing so, Nvidia doesn't cause a rollover, on the next line
    int gpuNameStart = inputString.indexOf("GPU:");
    if (inputString.indexOf("NVIDIA", gpuNameStart) > -1) {
      gpuNameStart = gpuNameStart + 11;
    }
    else {
      gpuNameStart = gpuNameStart + 8;
    }

    int gpuNameEnd = inputString.indexOf("|", gpuNameStart);
    String gpuName = inputString.substring(gpuNameStart, gpuNameEnd);
    tft.println(gpuName);
  }

  //------------------------------------------------------RX indicator---------------------------------------------------
#ifdef TFT_ILI9341
  tft.setTextSize(1);
  tft.setCursor(203, 11);
  tft.println("RX");
  tft.fillCircle(226, 14, 7, ILI9341_RED);// Flash top right corner when updating  //see "serialEvent();" loop
  tft.drawCircle(226, 14, 8, ILI9341_WHITE);
#endif
  //------------------------------------------ CPU Load/Temp -------------------------------------------------

  /* CPU Temp/Load String, */
  int cpuStringStart = inputString.indexOf("C");
  int cpuDegree = inputString.indexOf("c");
  int cpuStringLimit = inputString.indexOf("|");
  String cpuString1 = inputString.substring(cpuStringStart + 1, cpuDegree);
  String cpuString2 = inputString.substring(cpuDegree + 1, cpuStringLimit - 1);
  //Char erase and spacing adjust, MaDerer
  if (cpuString1.length() == 1) cpuString1 = " " + cpuString1;
  if (cpuString2.length() == 3) cpuString2 = " " + cpuString2;
  if (cpuString2.length() == 2) cpuString2 = "  " + cpuString2;

  /* CPU Temp display,*/
  tft.setTextSize(4);
  tft.setCursor(70 , 27);
  tft.print(cpuString1);
  tft.setTextSize(1);

#ifdef noDegree
  tft.print("C");       // Centigrade Symbol
#else
  tft.print((char)247); //Degrees Symbol
  tft.print("C");       // Centigrade Symbol
#endif

  /* CPU LOAD, ALL CORES Display, */
  tft.setTextSize(4);
  tft.print(cpuString2);
  tft.setTextSize(2);
  tft.println("%");    // Small Percent Symbol

  //------------------------------------------ CPU Freq -------------------------------------------------

  /*CPU Freq Display String*/
  int cpuCoreClockStart = inputString.indexOf("CHC") + 3;
  int cpuCoreClockEnd = inputString.indexOf("|", cpuCoreClockStart);
  String cpuClockString = inputString.substring(cpuCoreClockStart, cpuCoreClockEnd);

  /*CPU  Freq Display*/
  tft.setTextSize(3);
  tft.setCursor(70, 68);
  tft.print(cpuClockString);
  tft.setTextSize(3);
  tft.print("MHz");

  // Clear any artifacts trails from a slow string read
  tft.setTextSize(3);
  tft.println(" ");

  //------------------------------------------ GPU Load/Temp -------------------------------------------------

  /* GPU Temp/Load String,*/
  int gpuStringStart = inputString.indexOf("G", cpuStringLimit);
  int gpuDegree = inputString.indexOf("c", gpuStringStart);
  int gpuStringLimit = inputString.indexOf("|", gpuStringStart);
  String gpuString1 = inputString.substring(gpuStringStart + 1, gpuDegree);
  String gpuString2 = inputString.substring(gpuDegree + 1, gpuStringLimit - 1);
  //Char erase and spacing adjust, MaDerer
  if (gpuString2.length() == 3) gpuString2 = " " + gpuString2;
  if (gpuString2.length() == 2) gpuString2 = "  " + gpuString2;

  /* GPU Temp Display, */
  tft.setTextSize(4);
  tft.setCursor(70, 132);
  tft.print(gpuString1);
  tft.setTextSize(1);

#ifdef noDegree
  tft.print("C");       // Centigrade Symbol
#else
  tft.print((char)247); //Degrees Symbol
  tft.print("C");       // Centigrade Symbol
#endif

  /* GPU Load Display,*/
  tft.setTextSize(4);
  tft.print(gpuString2);
  tft.setTextSize(2);
  tft.println("%");      // Small Percent Symbol

  //------------------------------------------ GPU Freq/Temp -------------------------------------------------

  /* GPU Core Freq String, */
  int gpuCoreClockStart = inputString.indexOf("GCC") + 3;
  int gpuCoreClockEnd = inputString.indexOf("|", gpuCoreClockStart);
  String gpuCoreClockString = inputString.substring(gpuCoreClockStart, gpuCoreClockEnd);
  //Char erase and spacing adjust, MaDerer
  //if (gpuCoreClockString.length() == 3) gpuCoreClockString = " " + gpuCoreClockString;
  while (gpuCoreClockString.length() < 4) gpuCoreClockString = " " + gpuCoreClockString;


  /* GPU VRAM Freq String, */
  int gpuMemClockStart = inputString.indexOf("GMC") + 3;
  int gpuMemClockEnd = inputString.indexOf("|", gpuMemClockStart);
  String gpuMemClockString = inputString.substring(gpuMemClockStart, gpuMemClockEnd);
  //Char erase and spacing adjust, MaDerer
  //if (gpuMemClockString.length() == 3) gpuMemClockString = " " + gpuMemClockString;
  while (gpuMemClockString.length() < 4) gpuMemClockString = " " + gpuMemClockString;

  /* GPU SHADER Freq String, */
  int gpuShaderClockStart = inputString.indexOf("GSC") + 3;
  int gpuShaderClockEnd = inputString.indexOf("|", gpuShaderClockStart);
  String gpuShaderClockString = inputString.substring(gpuShaderClockStart, gpuShaderClockEnd);
  //Char erase and spacing adjust, MaDerer
  while (gpuShaderClockString.length() < 4) gpuShaderClockString = " " + gpuShaderClockString;

  /*GPU Memory Used String*/
  int gpuMemoryUsedStart = inputString.indexOf("GMU") + 3;
  int gpuMemoryUsedEnd = inputString.indexOf("|", gpuMemoryUsedStart);
  String gpuMemoryUsedString = inputString.substring(gpuMemoryUsedStart, gpuMemoryUsedEnd);

  /*GPU Total Memory*/
  int gpuMemoryStart = inputString.indexOf("GMT") + 3;
  int gpuMemoryEnd = inputString.indexOf("|", gpuMemoryStart);
  String gpuMemoryString = inputString.substring(gpuMemoryStart, gpuMemoryEnd);
  //Char erase and spacing adjust, MaDerer
  while (gpuMemoryString.length() < 4) gpuMemoryString = " " + gpuMemoryString;

  double totalGPUmem = atof(gpuMemoryString.c_str());
  double totalGPUmemSum = totalGPUmem / 1024;    // divide by 1024 to get the correct value
  float  totalGPUmemSumDP = totalGPUmemSum ;     // float to handle the decimal point when printed (totalGPUmemSumDP, 0)

  /*GPU Total Memory Used*/
  double gpuMemUsed = atof(gpuMemoryUsedString.c_str());
  double  gpuMemUsedSum = gpuMemUsed / 1024;
  //Char erase and spacing adjust, MaDerer
  while (gpuMemoryUsedString.length() < 4) gpuMemoryUsedString = " " + gpuMemoryUsedString;

  /*GPU Total Memory Display*/
  tft.setCursor(210, 110);  // Position GPU Total Memory
  tft.setTextSize(2);
  //tft.print(gpuMemoryString); // Show Value in MB
  tft.print(totalGPUmemSumDP, 0); // Show Value in GB
  tft.setTextSize(1);
  tft.print("GB");

  /*GPU Fan% String*/
  int gpuFanStart = inputString.indexOf("GFANL") + 5;  // GPU Fan Load %
  int gpuFanEnd = inputString.indexOf("|", gpuFanStart);
  String gpuFanString = inputString.substring(gpuFanStart, gpuFanEnd);
  //Char erase and spacing adjust, MaDerer
  while (gpuFanString.length() < 3) gpuFanString = " " + gpuFanString;


  /* GPU Core Freq Display, */
  tft.setCursor(30, 168);
  tft.setTextSize(2);
  tft.print("Core   :");
  tft.print(gpuCoreClockString);
  tft.setTextSize(2);
  tft.print("MHz");
  // Clear any artifacts trails from a slow string read
  tft.setTextSize(2);
  tft.print(" ");

  /* GPU VRAM Freq Display, */
  tft.setCursor(30, 185);
  tft.setTextSize(2);
  tft.print("VRAM   :");
  tft.print(gpuMemClockString);
  tft.setTextSize(2);
  tft.print("MHz");
  // Clear any artifacts trails from a slow string read
  tft.setTextSize(2);
  tft.print(" ");

  /*GPU Shader Display
    tft.setCursor(30, 202);
    tft.setTextSize(2);
    tft.print("Shader:");
    tft.print(gpuShaderClockString);
    tft.setTextSize(2);
    tft.print("MHz");
    // Clear any artifacts trails from a slow string read
    tft.setTextSize(2);
    tft.print(" ");
  */

  /*GPU Used Memory Display*/
  tft.setCursor(30, 202);
  tft.setTextSize(2);
  tft.print("GPU Mem:");
  tft.print(gpuMemoryUsedString); //  show values in MB
  tft.setTextSize(2);
  tft.println("MB");


  /*GPU FAN% Display*/
  tft.setTextSize(2);
  tft.setCursor(30, 219);
  tft.print("GPU Fan: ");
  tft.print(gpuFanString);
  tft.setTextSize(2);
  tft.println("%");

  //----------------------------------------SYSTEM RAM USAGE---------------------------------------------------

  /*SYSTEM RAM String*/
  int ramStringStart = inputString.indexOf("R", gpuStringLimit);
  int ramStringLimit = inputString.indexOf("|", ramStringStart);
  String ramString   = inputString.substring(ramStringStart + 1 , ramStringLimit - 2);
  //Char erase and spacing adjust, MaDerer
  while (ramString.length() < 4) ramString = " " + ramString;

  /* SYSTEM RAM AVALABLE String, */
  int AramStringStart = inputString.indexOf("RA", ramStringLimit);
  int AramStringLimit = inputString.indexOf("|", AramStringStart);
  String AramString = inputString.substring(AramStringStart + 2 , AramStringLimit);
  //Char erase and spacing adjust, MaDerer
  while (AramString.length() < 5) AramString = " " + AramString;

  /* SYSTEM RAM TOTAL String, */
  double intRam = atof(ramString.c_str());
  double intAram = atof(AramString.c_str());
  //double  intRamSum = intRam + intAram;
  float  intRamSum = intRam + intAram; //float to handle the decimal point when printed (intRamSum,0)

  /*Sytem RAM*/
  tft.setTextSize(2);
  tft.setCursor(4, 258); //(Left/Right, UP/Down)
  tft.print("SysMem:");
  tft.print(intRamSum, 0) ;
  tft.setTextSize(2);
  tft.print("GB");

  tft.setTextSize(2);
  tft.print(" /");
  tft.print(ramString);
  tft.setTextSize(2);
  tft.println("GB");

  //------------------------------------------ RX indicator Clear-----------------------------------------------
#ifdef TFT_ILI9341
  tft.fillCircle(226, 14, 7, ILI9341_BLACK); // Portrait Flash RX top right corner when updating
#endif
  //-------------------------------------------------------------------------------------------------------------

  displayDraw = 1;

  //--------------------------Trigger an event when CPU or GPU threshold is met ---------------------------------
#ifdef enableCustomThesholdtriggers

  CustomTriggerCPU_temp( cpuString1.toInt() ); //  CPU  Temperature
  CustomTriggerCPU_load( cpuString2.toInt() ); //  CPU  Load

  CustomTriggerGPU_temp( gpuString1.toInt() ); //  GPU  Temperature
  CustomTriggerGPU_load( gpuString2.toInt() ); //  GPU  Load

#endif

#ifdef enableNeopixelGauges

  CPU_loadGauge( cpuString2.toInt() ); // Neopixel Ring Gauge  CPU  Load
  //CPU_tempGauge( cpuString1.toInt() ); // Neopixel Ring Gauge  CPU  Temperature

  GPU_loadGauge( gpuString2.toInt() ); // Neopixel Ring Gauge  GPU  Load
  //GPU_tempGauge( gpuString1.toInt() ); // Neopixel Ring Gauge  GPU  Temperature

#endif
}
