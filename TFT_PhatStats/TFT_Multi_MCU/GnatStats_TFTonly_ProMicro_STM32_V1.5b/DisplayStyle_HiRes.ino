/*
   _____ _____  _____ _____  _           __     __  _    _ _ _____  ______  _____
  |  __ \_   _|/ ____|  __ \| |        /\\ \   / / | |  | (_)  __ \|  ____|/ ____|
  | |  | || | | (___ | |__) | |       /  \\ \_/ /  | |__| |_| |__) | |__  | (___
  | |  | || |  \___ \|  ___/| |      / /\ \\   /   |  __  | |  _  /|  __|  \___ \
  | |__| || |_ ____) | |    | |____ / ____ \| |    | |  | | | | \ \| |____ ____) |
  |_____/_____|_____/|_|    |______/_/    \_\_|    |_|  |_|_|_|  \_\______|_____/

*/

/*Optimised for ILI9341 320 x 240 in portrait and landscape*/

void DisplayStyleTFT_HiRes () {  // When rotated 90 degrees, max coordinate 232 pixels down

  //--------------------------------------- Display Background ----------------------------------------------------

#ifdef TFT_ST7735
  tft.setTextColor(ST7735_WHITE);
#endif

#ifdef TFT_ILI9341
  tft.setTextColor(ILI9341_WHITE);
#endif

  /* Display Background */

  tft.setCursor(1, 12 + 15);
  tft.setTextSize(3);
  tft.println("CPU");

  tft.setTextSize(1);
  tft.setCursor(1, 56);
  tft.println("Temp/Load");

  tft.setTextSize(1);
  tft.setCursor(1, 32 + 40);
  tft.println("Frequency");

  tft.setTextSize(1);
  tft.setCursor(1, 32 + 64);
  tft.println("________________________________________");

  tft.setTextSize(3);
  tft.setCursor(1, 68 + 64);
  tft.println("GPU");

  tft.setTextSize(1);
  tft.setCursor(1, 162);
  tft.println("Temp/Load");


  tft.setTextSize(1);
  tft.setCursor(1, 32 + 180);
  tft.println("________________________________________");

  tft.setTextSize(2);
  tft.setCursor(1, 118 + 106); //(Left/Right, UP/Down)
  tft.println("Memory Usage");

  tft.setTextSize(1);
  tft.setCursor(1, 32 + 206);
  tft.println("________________________________________");
  displayDraw = 1;

  /*CPU/GPU/RAM  Clearing Boxes, eg: tft.fillRect(<X>, ^Y^, W, H, Color);*/
  /*Optimised for ILI9341 320 x 240 in portrait and landscape*/

  tft.fillRect(210, 0, 42, 15, BLACK);     // Flash top right corner when updating  //see "serialEvent();" loop

  tft.fillRect(70,  26,   70, 30, BLACK);  // fill CPU Temp live stats section only
  tft.fillRect(150, 26,   86, 30, BLACK);  // fill CPU Load live stats section only

  tft.fillRect(70,  66,   166, 30, BLACK); // fill CPU Freq live stats section only
  tft.fillRect(70,  131,  70, 30, BLACK);  // fill GPU Temp
  tft.fillRect(150, 131,  86, 30, BLACK);  // fill GPU Load

  tft.fillRect(150, 168,  50, 48, BLACK);  // fill GPU Freq/VRAM/Shader live stats section only
  tft.fillRect(150, 223,  86, 16, BLACK);  // fill RAM live stats section only



  /* Position Test*/
  //tft.fillRect(210, 0, 42, 15, WHITE); // Flash top right corner when updating  //see "serialEvent();" loop

  //tft.fillRect(70,  26,   70, 30, WHITE);  // fill CPU Temp live stats section only
  //tft.fillRect(150, 26,   86, 30, WHITE);  // fill CPU Load live stats section only
  //tft.fillRect(70,  66,   166, 30, WHITE); // fill CPU Freq live stats section only

  //tft.fillRect(70,  131,  70, 30, WHITE);  // fill GPU Temp
  //tft.fillRect(150, 131,  86, 30, WHITE);  // fill GPU Load
  //tft.fillRect(150, 168,  50, 48, WHITE);  // fill GPU Freq/VRAM/Shader live stats section only

  //tft.fillRect(150, 223,  86, 16, WHITE); // fill RAM live stats section only


  //---------------------------------------CPU & GPU Hardware ID----------------------------------------------------

  /*CPU & GPU Hardware ID*/

  /*CPU Manual Position Test*/
  //tft.setTextSize(0);
  //tft.setCursor(-35, 1);// Negative spacing so, CPU ID doesn't cause a rollover, on the next line
  //String cpuName = "Intel Core i7-5820K"; // Name spacing test

  //tft.setTextSize(2); // string font size
  //String cpuName = "";
  //tft.println(cpuName);

  /* GPU Manual Position Test*/
  //tft.setTextSize(0);
  //tft.setCursor(-42, 28); // Negative spacing so, GPU ID doesn't cause a rollover, on the next line
  //String gpuName = "Nvidia GeForce GTX 1080"; // Name spacing test
  //tft.setTextSize(1); // string font size
  //String gpuName = "";
  //tft.println(gpuName);

  if (inputString.indexOf("CPU") > -1)
  {
    String cpuName = "";
    tft.setTextSize(2);
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
    tft.setTextSize(2);
    tft.setCursor(0, 58 + 50);  // Position GPU Name
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

  //------------------------------------------ CPU Load/Temp -------------------------------------------------

  /*CPU Display String*/
  int cpuStringStart = inputString.indexOf("C");
  int cpuDegree = inputString.indexOf("c");
  int cpuStringLimit = inputString.indexOf("|");
  String cpuString1 = inputString.substring(cpuStringStart + 1, cpuDegree);
  String cpuString2 = inputString.substring(cpuDegree + 1, cpuStringLimit - 1);

  /*CPU TEMPERATURE*/
  tft.setTextSize(4);
  tft.setCursor(42 + 28 , 12 + 15);
  tft.print(cpuString1);
  tft.setTextSize(1);

#ifdef noDegree
  tft.print("C");       // Centigrade Symbol
#else
  tft.print((char)247); //Degrees Symbol
  tft.print("C");       // Centigrade Symbol
#endif

  /*CPU LOAD, ALL CORES*/
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
  tft.setTextSize(4);
  tft.setCursor(42 + 28, 32 + 36);
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
  tft.setTextSize(4);
  tft.setCursor(42 + 28, 68 + 64);
  tft.print(gpuString1);
  tft.setTextSize(1);

#ifdef noDegree
  tft.print("C");       // Centigrade Symbol
#else
  tft.print((char)247); //Degrees Symbol
  tft.print("C");       // Centigrade Symbol
#endif

  /*GPU LOAD*/
  tft.setTextSize(4);
  tft.print(gpuString2);
  tft.setTextSize(2);
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


  tft.setTextSize(2);
  tft.setCursor(42 + 28, 88 + 80);
  tft.print("Core  :");
  tft.print(gpuCoreClockString);

  tft.setTextSize(1);
  tft.print("MHz");       // Centigrade Symbol
  tft.setCursor(42 + 28, 96 + 89);
  tft.setTextSize(2);
  tft.print("VRAM  :");
  tft.print(gpuMemClockString);
  tft.setTextSize(1);
  tft.print("MHz");
  tft.setCursor(42 + 28, 104 + 98);
  tft.setTextSize(2);
  tft.print("Shader:");
  tft.print(gpuShaderClockString);
  tft.setTextSize(1);
  tft.print("MHz");


  //----------------------------------------SYSTEM RAM USAGE---------------------------------------------------

  /*SYSTEM RAM String*/
  int ramStringStart = inputString.indexOf("R", gpuStringLimit);
  int ramStringLimit = inputString.indexOf("|", ramStringStart);
  String ramString   = inputString.substring(ramStringStart + 1 , ramStringLimit);


  /*RAM USAGE*/
  tft.setTextSize(2); //set background txt font size
  tft.setCursor(85 + 69, 118 + 106); // (Left/Right, UP/Down)
  tft.println(ramString);


  //--------------------------------------Top Right Display Number-----------------------------------------------
  tft.setTextSize(1);
  tft.setCursor(110 + 100, 1);
  tft.println("HiRes");

  splashScreen3();
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
