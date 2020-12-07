/*
   ___ ___ ___ ___ _      ___   __  ___  ___ ___ ___ ___ _  _   ____
  |   \_ _/ __| _ \ |    /_\ \ / / / __|/ __| _ \ __| __| \| | |__ /
  | |) | |\__ \  _/ |__ / _ \ V /  \__ \ (__|   / _|| _|| .` |  |_ \
  |___/___|___/_| |____/_/ \_\_|   |___/\___|_|_\___|___|_|\_| |___/

*/

  //optimised for the ST7735 128x160 in vertical and horizontal aspects
  
void DisplayStyleTFT_3 () {

  //--------------------------------------- Display Background ----------------------------------------------------

#ifdef TFT_ST7735
  tft.setTextColor(ST7735_WHITE);
  //tft.fillScreen(ST7735_BLACK);
#endif

#ifdef TFT_ILI9341
  tft.setTextColor(ILI9341_WHITE);
#endif

  /* Dispaly Background */
  tft.setTextSize(2); //set background txt font size
  tft.setCursor(1, 12);
  tft.println("CPU");
  tft.setCursor(1, 32);
  tft.println("FRQ");
  tft.setCursor(1, 68);
  tft.println("GPU");
  tft.setTextSize(1); //set background txt font size
  tft.setCursor(1, 118); //(Left/Right, UP/Down)
  tft.println("Memory Usage :");

  displayDraw = 1;

  /*CPU/GPU/RAM  Clearing Boxes, eg: tft.fillRect(<X>, ^Y^, W, H, Color);*/
  /*Optimised for ST7735 in portrait and landscape*/
  tft.fillRect(103, 0 , 25, 10, BLACK); // fill DisplayStyle number when updating
  
  tft.fillRect(38, 11,  50, 16, BLACK); // fill CPU Temp live stats section only
  tft.fillRect(90, 11,  34, 16, BLACK); // fill CPU Load live stats section only
  tft.fillRect(38, 31,  90, 16, BLACK); // fill CPU Freq live stats section only
  
  tft.fillRect(38, 67,  90, 16, BLACK); // fill GPU live stats section only
  tft.fillRect(82, 87,  26, 27, BLACK); // fill GPU Freq/VRAM/Shader live stats section only
  
  tft.fillRect(85, 118, 36, 10, BLACK); // fill RAM live stats section only


  /* Position Test*/
  //tft.drawRect(68, 54 , 58, 10, WHITE); // Flash bottom right corner when updating
  
  //tft.fillRect(38, 11,  50, 16, WHITE); // fill CPU Temp live stats section only
  //tft.fillRect(90, 11,  34, 16, WHITE); // fill CPU Load live stats section only
  //tft.fillRect(38, 31,  50, 16, WHITE); // fill CPU Freq live stats section only
  
  //tft.fillRect(38, 67,  90, 16, WHITE); // fill GPU live stats section only
  //tft.fillRect(82, 87,  26, 27, WHITE); // fill GPU Freq/VRAM/Shader live stats section only
  
  //tft.fillRect(85, 118, 36, 10, WHITE); // fill RAM live stats section only
  

  //---------------------------------------CPU & GPU Hardware ID----------------------------------------------------

  /*CPU & GPU Hardware ID*/

  /*CPU Manual Position Test*/
  //tft.setTextSize(0);
  //tft.setCursor(-35, 1);// Negative spacing so, CPU ID doesn't cause a rollover, on the next line
  //String cpuName = "Intel Core i7-5820K"; // Name spacing test

  //tft.setTextSize(0); // string font size
  //String cpuName = "";
  //tft.println(cpuName);

  /* GPU Manual Position Test*/
  //tft.setTextSize(0);
  //tft.setCursor(-42, 28); // Negative spacing so, GPU ID doesn't cause a rollover, on the next line
  //String gpuName = "Nvidia GeForce GTX 1080"; // Name spacing test

  //tft.setTextSize(0); // string font size
  //String gpuName = "";
  //tft.println(gpuName);

  if (inputString.indexOf("CPU") > -1)
  {
    String cpuName = "";
    tft.setTextSize(1);
    tft.setCursor(0, 1);
    //tft.setCursor(-35, 1);

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
    tft.setTextSize(0);

    tft.setCursor(0, 58);
    //tft.setCursor(-41, 28); // Negative spacing so, Nvidia doesn't cause a rollover, on the next line
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

  //------------------------------------------ CPU Load/Temp -------------------------------------------------

  /*CPU Display String*/
  int cpuStringStart = inputString.indexOf("C");
  int cpuDegree = inputString.indexOf("c");
  int cpuStringLimit = inputString.indexOf("|");
  String cpuString1 = inputString.substring(cpuStringStart + 1, cpuDegree);
  String cpuString2 = inputString.substring(cpuDegree + 1, cpuStringLimit - 1);

  /*CPU TEMPERATURE*/
  tft.setTextSize(2);
  tft.setCursor(42, 12);
  tft.print(cpuString1);
  tft.setTextSize(1);

#ifdef noDegree
  tft.print("C");       // Centigrade Symbol
#else
  tft.print((char)247); //Degrees Symbol
  tft.print("C");       // Centigrade Symbol
#endif

  /*CPU LOAD, ALL CORES*/
  tft.setTextSize(2);
  tft.print(cpuString2);
  tft.setTextSize(1);
  tft.println("%");    // Small Percent Symbol

  //------------------------------------------ CPU Freq -------------------------------------------------

  /*CPU Freq Display String*/
  int cpuCoreClockStart = inputString.indexOf("CHC") + 3;
  int cpuCoreClockEnd = inputString.indexOf("|", cpuCoreClockStart);
  String cpuClockString = inputString.substring(cpuCoreClockStart, cpuCoreClockEnd);

  /*CPU  Freq Display*/
  tft.setTextSize(2);
  tft.setCursor(42, 32);
  tft.print(cpuClockString);
  tft.setTextSize(1);
  tft.print("MHz");

  //------------------------------------------ GPU Load/Temp -------------------------------------------------

  /*GPU Display String*/
  int gpuStringStart = inputString.indexOf("G", cpuStringLimit);
  int gpuDegree = inputString.indexOf("c", gpuStringStart);
  int gpuStringLimit = inputString.indexOf("|", gpuStringStart);
  String gpuString1 = inputString.substring(gpuStringStart + 1, gpuDegree);
  String gpuString2 = inputString.substring(gpuDegree + 1, gpuStringLimit - 1);

  /*GPU TEMPERATURE*/
  tft.setTextSize(2);
  tft.setCursor(42, 68);
  tft.print(gpuString1);
  tft.setTextSize(1);

#ifdef noDegree
  tft.print("C");       // Centigrade Symbol
#else
  tft.print((char)247); //Degrees Symbol
  tft.print("C");       // Centigrade Symbol
#endif

  /*GPU LOAD*/
  tft.setTextSize(2);
  tft.print(gpuString2);
  tft.setTextSize(1);
  tft.println("%");      // Small Percent Symbol

  //------------------------------------------ GPU Freq/Temp -------------------------------------------------

  /* GPU temp V's GPU freq to check for throttling and max 'GPU Boost' */

  /*GPU Core Freq */


  int gpuCoreClockStart = inputString.indexOf("GCC") + 3;
  int gpuCoreClockEnd = inputString.indexOf("|", gpuCoreClockStart);
  String gpuCoreClockString = inputString.substring(gpuCoreClockStart, gpuCoreClockEnd);

  int gpuMemClockStart = inputString.indexOf("GMC") + 3;
  int gpuMemClockEnd = inputString.indexOf("|", gpuMemClockStart);
  String gpuMemClockString = inputString.substring(gpuMemClockStart, gpuMemClockEnd);

  int gpuShaderClockStart = inputString.indexOf("GSC") + 3;
  int gpuShaderClockEnd = inputString.indexOf("|", gpuShaderClockStart);
  String gpuShaderClockString = inputString.substring(gpuShaderClockStart, gpuShaderClockEnd);


  tft.setTextSize(1);
  tft.setCursor(42, 88);
  tft.print("Core  :");
  tft.print(gpuCoreClockString);
  tft.setTextSize(1);
  tft.print("MHz");       // Centigrade Symbol
  tft.setCursor(42, 96);
  tft.print("VRAM  :");
  tft.print(gpuMemClockString);
  tft.print("MHz");
  tft.setCursor(42, 104);
  tft.print("Shader:");
  tft.print(gpuShaderClockString);
  tft.print("MHz");


  //----------------------------------------SYSTEM RAM USAGE---------------------------------------------------

  /*SYSTEM RAM String*/
  int ramStringStart = inputString.indexOf("R", gpuStringLimit);
  int ramStringLimit = inputString.indexOf("|", ramStringStart);
  String ramString   = inputString.substring(ramStringStart + 1 , ramStringLimit);


  /*RAM USAGE*/
  tft.setTextSize(1); //set background txt font size
  tft.setCursor(85, 118); // (Left/Right, UP/Down)
  tft.println(ramString);


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

  tft.setTextSize(1);
  tft.setCursor(115, 1);
  tft.println("D3");

  displayDraw = 1;

}
