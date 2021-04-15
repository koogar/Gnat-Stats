/*
   ___ ___ ___ ___ _      ___   __  ___  ___ ___ ___ ___ _  _   _
  |   \_ _/ __| _ \ |    /_\ \ / / / __|/ __| _ \ __| __| \| | / |
  | |) | |\__ \  _/ |__ / _ \ V /  \__ \ (__|   / _|| _|| .` | | |
  |___/___|___/_| |____/_/ \_\_|   |___/\___|_|_\___|___|_|\_| |_|
*/

//optimised for the ST7735 128x160 in vertical and horizontal aspects
void DisplayStyleTFT_ST7735 () {

  // Display Background
  //--------------------------------------- Display Background ----------------------------------------------------
#ifdef TFT_ST7735
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  tft.drawFastHLine(0, 52 , 128, ST7735_WHITE);
  tft.drawFastHLine(0, 130, 128, ST7735_WHITE);
  tft.drawFastHLine(0, 159, 128, ST7735_WHITE);
#endif

#ifdef TFT_ILI9341
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.drawFastHLine(0, 52 , 128, ILI9341_WHITE);
  tft.drawFastHLine(0, 130, 128, ILI9341_WHITE);
  tft.drawFastHLine(0, 159, 128, ILI9341_WHITE);
#endif


  tft.setTextSize(1); //set background txt font size
  tft.setCursor(1, 14);
  tft.println("CPU");
  tft.setCursor(1, 32);
  tft.println("FRQ");
  tft.setCursor(1, 68);
  tft.println("GPU");

  //    displayDraw = 1;

  //---------------------------------------CPU & GPU Hardware ID----------------------------------------------------

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
    tft.println(cpuName.substring(0, 12));

  }
  if (inputString.indexOf("GPU") > -1)
  {
    tft.setTextSize(0);

    tft.setCursor(0, 58);
    int gpuNameStart = inputString.indexOf("GPU:");
    if (inputString.indexOf("NVIDIA", gpuNameStart) > -1) {
      gpuNameStart = gpuNameStart + 11;
    }
    else {
      gpuNameStart = gpuNameStart + 4;
    }

    int gpuNameEnd = inputString.indexOf("|", gpuNameStart);
    String gpuName = inputString.substring(gpuNameStart, gpuNameEnd);
    tft.println(gpuName.substring(0, 18));

  }

  //------------------------------------------------------RX indicator---------------------------------------------------

#ifdef TFT_ST7735
  tft.setTextSize(1);
  tft.setCursor(104, 2);
  tft.println("RX");
  tft.fillCircle(122, 5, 3, ST7735_RED);// Flash top right corner when updating  //see "serialEvent();" loop
  tft.drawCircle(122, 5, 4, ST7735_WHITE);
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
  tft.setTextSize(2);
  tft.setCursor(30, 14);
  tft.print(cpuString1);
  tft.setTextSize(1);
  tft.print((char)247); //Degrees Symbol
  tft.print("C");

  /* CPU LOAD, ALL CORES Display, */
  tft.setTextSize(2);
  tft.setCursor(66, 14);
  tft.print(cpuString2);
  tft.setTextSize(1);
  tft.println("%");    // Small Percent Symbol

  //------------------------------------------ CPU Freq -------------------------------------------------


  /* CPU Freq Display String, */
  int cpuCoreClockStart = inputString.indexOf("CHC") + 3;
  int cpuCoreClockEnd = inputString.indexOf("|", cpuCoreClockStart);
  String cpuClockString = inputString.substring(cpuCoreClockStart, cpuCoreClockEnd);

  /* CPU  Freq Display, */
  tft.setTextSize(2);
  tft.setCursor(30, 32);
  tft.print(cpuClockString);
  tft.setTextSize(2);
  tft.print("MHz");
  // Clear any artifacts trails from a slow string read
  tft.setTextSize(2);
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
  tft.setTextSize(2);
  tft.setCursor(30, 68);
  tft.print(gpuString1);
  tft.setTextSize(1);
  tft.print((char)247); //Degrees Symbol
  tft.print("C");       // Centigrade Symbol

  /* GPU Load Display,*/
  tft.setTextSize(2);
  tft.setCursor(66, 68);
  tft.print(gpuString2);
  tft.setTextSize(1);
  tft.println("%");      // Small Percent Symbol


  //------------------------------------------ GPU Freq/Temp -------------------------------------------------

  /* GPU Core Freq String, */
  int gpuCoreClockStart = inputString.indexOf("GCC") + 3;
  int gpuCoreClockEnd = inputString.indexOf("|", gpuCoreClockStart);
  String gpuCoreClockString = inputString.substring(gpuCoreClockStart, gpuCoreClockEnd);
  //Char erase and spacing adjust, MaDerer
  if (gpuCoreClockString.length() == 3) gpuCoreClockString = " " + gpuCoreClockString;

  /* GPU VRAM Freq String, */
  int gpuMemClockStart = inputString.indexOf("GMC") + 3;
  int gpuMemClockEnd = inputString.indexOf("|", gpuMemClockStart);
  String gpuMemClockString = inputString.substring(gpuMemClockStart, gpuMemClockEnd);
  //Char erase and spacing adjust, MaDerer
  if (gpuMemClockString.length() == 3) gpuMemClockString = " " + gpuMemClockString;

  /* GPU SHADER Freq String, */
  int gpuShaderClockStart = inputString.indexOf("GSC") + 3;
  int gpuShaderClockEnd = inputString.indexOf("|", gpuShaderClockStart);
  String gpuShaderClockString = inputString.substring(gpuShaderClockStart, gpuShaderClockEnd);

  /*GPU Memory Used String*/
  int gpuMemoryUsedStart = inputString.indexOf("GMU") + 3;
  int gpuMemoryUsedEnd = inputString.indexOf("|", gpuMemoryUsedStart);
  String gpuMemoryUsedString = inputString.substring(gpuMemoryUsedStart, gpuMemoryUsedEnd);

  double gpuMemUsed = atof(gpuMemoryUsedString.c_str());
  double  gpuMemUsedSum = gpuMemUsed / 1024;
  //Char erase and spacing adjust, MaDerer
  while (gpuMemoryUsedString.length() < 4) gpuMemoryUsedString = " " + gpuMemoryUsedString;

  /*GPU Total Memory*/
  int gpuMemoryStart = inputString.indexOf("GMT") + 3;
  int gpuMemoryEnd = inputString.indexOf("|", gpuMemoryStart);
  String gpuMemoryString = inputString.substring(gpuMemoryStart, gpuMemoryEnd);
  //Char erase and spacing adjust, MaDerer
  while (gpuMemoryString.length() < 4) gpuMemoryString = " " + gpuMemoryString;

  double totalGPUmem = atof(gpuMemoryString.c_str());
  double totalGPUmemSum = totalGPUmem / 1024;    // divide by 1024 to get the correct value
  float  totalGPUmemSumDP = totalGPUmemSum ;     // float to handle the decimal point when printed (totalGPUmemSumDP, 0)

  /*GPU Fan% String*/
  int gpuFanStart = inputString.indexOf("GFANL") + 5;  // GPU Fan Load %
  int gpuFanEnd = inputString.indexOf("|", gpuFanStart);
  String gpuFanString = inputString.substring(gpuFanStart, gpuFanEnd);
  //Char erase and spacing adjust, MaDerer
  while (gpuFanString.length() < 5) gpuFanString = " " + gpuFanString;

  /* GPU Core Freq Display, */
  tft.setTextSize(1);
  tft.setCursor(30, 88);
  tft.print("Core : ");
  tft.print(gpuCoreClockString);
  tft.setTextSize(1);
  tft.print("MHz ");
  // Clear any artifacts trails from a slow string read
  tft.setTextSize(1);
  tft.println(" ");

  /* GPU VRAM Freq Display, */
  tft.setCursor(30, 96);
  tft.setTextSize(1);
  tft.print("VRAM : ");
  tft.print(gpuMemClockString);
  tft.print("MHz ");
  // Clear any artifacts trails from a slow string read
  tft.setTextSize(1);
  tft.println(" ");

  /*GPU FAN% Display*/
  tft.setTextSize(1);
  tft.setCursor(1, 108); //
  tft.print("GPU Fan Load: ");
  tft.setTextSize(1);
  tft.print(gpuFanString);
  tft.setTextSize(1);
  tft.println("%");

  /*GPU Shader Display
    tft.setCursor(30, 104);
    tft.print("Shader:");
    tft.print(gpuShaderClockString);
    tft.print("MHz");
    // Clear any artifacts trails from a slow string read
    tft.setTextSize(1);
    tft.println(" ");
  */

  /*GPU Used Memory Display*/
  tft.setCursor(1, 118);
  tft.print("GPU Mem Used: ");
  tft.print(gpuMemoryUsedString); //  show values in MB
  tft.setTextSize(1);
  tft.println("MB");

  /*GPU Total Memory Display, Side of the GPU Name*/
  tft.setCursor(105, 58);  // Position GPU Total Memory
  tft.setTextSize(1);
  //tft.print(gpuMemoryString); // Show Value in MB
  tft.print(totalGPUmemSumDP, 0); // Show Value in GB
  tft.setTextSize(1);
  tft.print("GB");

  //----------------------------------------SYSTEM RAM USAGE---------------------------------------------------

  /*System RAM String*/
  int ramStringStart = inputString.indexOf("R", gpuStringLimit);
  int ramStringLimit = inputString.indexOf("|", ramStringStart);
  String ramString = inputString.substring(ramStringStart + 1, ramStringLimit);
  //Char erase and spacing adjust, MaDerer
  while (ramString.length() < 6) ramString = " " + ramString;

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

  /*System RAM Usage Display*/
  tft.setTextSize(1); //set background txt font size
  tft.setCursor(1, 140);
  tft.print("SYS Mem:");
  tft.print(intRamSum, 0) ;
  tft.print("GB");
  tft.print(" /");
  tft.print(ramString);
 
  //------------------------------------------ RX indicator Clear-----------------------------------------------
#ifdef TFT_ST7735
  tft.fillCircle(122, 5, 3, ST7735_BLACK);// Flash top right corner when updating
#endif
  //-------------------------------------------------------------------------------------------------------------

  //--------------------------Trigger an event when CPU or GPU threshold is met ---------------------------------
#ifdef enableNeopixelGauges

  CPU_loadGauge( cpuString2.toInt() ); // Neopixel Ring Gauge  CPU  Load
  //CPU_tempGauge( cpuString1.toInt() ); // Neopixel Ring Gauge  CPU  Temperature

  GPU_loadGauge( gpuString2.toInt() ); // Neopixel Ring Gauge  GPU  Load
  //GPU_tempGauge( gpuString1.toInt() ); // Neopixel Ring Gauge  GPU  Temperature

#endif

#ifdef enableCustomThesholdtriggers

  CustomTriggerCPU_temp( cpuString1.toInt() ); //  CPU  Temperature
  CustomTriggerCPU_load( cpuString2.toInt() ); //  CPU  Load

  CustomTriggerGPU_temp( gpuString1.toInt() ); //  GPU  Temperature
  CustomTriggerGPU_load( gpuString2.toInt() ); //  GPU  Load

#endif

  displayDraw = 1;

}
