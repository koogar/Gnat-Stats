

/*CPU/GPU Phat Tacho Side level Gauge Thresholds,*/

//---------------------- CPU--------------------

//>>>>>>>>>>>> CPU TEMP

void CPU_tempLevelGauge(int cpuDegree ) {

  /*Top CPU Temp Level Clear Box,*/
  tft.fillRoundRect(299 - 6, 0,   8, 102 , 1, ILI9341_BLACK);

  float CPUtempfactor = cpuDegree;

  /*Attempt to reverse direction of Bar Scale, and get rid of decimal point for coordinates,*/
  int CPUtempScalefactor = (CPUtempfactor + 1); // +1 so it always shows something

  if (CPUtempfactor >= 0 ) {
    /*Top CPU Temp Bar Scale,*/
    tft.fillRoundRect(299 - 6, 1,   8, CPUtempScalefactor  , 1, ILI9341_GREEN); // Top CPU Temp Scale
  }

  if (CPUtempfactor >= 45 ) {
    /*Top CPU Temp Bar Scale,*/
    tft.fillRoundRect(299 - 6, 1,   8, CPUtempScalefactor   , 1, ILI9341_GREEN); // Top CPU Temp Scale
  }

  if (CPUtempfactor >= 65 ) {
    /*Top CPU Temp Bar Scale,*/
    tft.fillRoundRect(299 - 6, 1,   8, CPUtempScalefactor   , 1, ILI9341_ORANGE); // Top CPU Temp Scale
  }

  if (CPUtempfactor >= 85 ) {
    /*Top CPU Temp Bar Scale,*/
    tft.fillRoundRect(299 - 6, 1,   8, CPUtempScalefactor  , 1, ILI9341_RED); // Top CPU Temp Scale
  }

  tft.drawRoundRect(299 - 6, 0,   8, 92  , 1, ILI9341_WHITE); // Draw rectangle round CPU temp bar
  
  /*Stop Scale running into MAX box,*/
  tft.fillRect (294 - 6 , 85 + 10,  27, 18 , ILI9341_BLACK); // Stop Scale running into MAX box

  // Max Text box CPU
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setCursor(298 + 2 - 6 , 90 + 10);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("MAX");
  tft.drawRoundRect(295 + 2 - 6 , 87 + 10,  23, 13 , 1, ILI9341_WHITE);

}


//>>>>>>>>>>>> CPU LOAD

void CPU_loadLevelGauge(int cpuUsage ) {

  /*Top CPU Load Level Clear Box,*/
  tft.fillRoundRect(311 - 5, 0,   8, 102 , 1, ILI9341_BLACK);

  float CPUloadfactor = cpuUsage;

  /*Attempt to reverse direction of Bar Scale, and get rid of decimal point for coordinates,*/
  int CPUloadScalefactor =   ( CPUloadfactor + 1); // +1 so it always shows something


  if (CPUloadfactor >= 0 ) {
    /*Top CPU Load Bar Scale,*/
    tft.fillRoundRect(311 - 5, 1,   8,  CPUloadScalefactor   , 1, ILI9341_GREEN); // Top CPU Load Scale
  }

  if (CPUloadfactor >= 50 ) {
    /*Top CPU Load Bar Scale,*/
    tft.fillRoundRect(311 - 5, 1,   8,  CPUloadScalefactor   , 1, ILI9341_GREEN); // Top CPU Load Scale
  }

  if (CPUloadfactor >= 75) {
    /*Top CPU Load Bar Scale,*/
    tft.fillRoundRect(311 - 5, 1,   8,  CPUloadScalefactor   , 1, ILI9341_ORANGE); // Top CPU Load Scale
  }

  if (CPUloadfactor >= 83 ) {
    /*Top CPU Load Bar Scale,*/
    tft.fillRoundRect(311 - 5, 1,   8,  CPUloadScalefactor  , 1, ILI9341_RED); // Top CPU Load Scale
  }
  
  tft.drawRoundRect(311 - 5, 0,   8,  92 , 1, ILI9341_WHITE);// Draw rectangle round CPU load bar
}







//---------------------- GPU--------------------


//>>>>>>>>>>>> GPU TEMP

void GPU_tempLevelGauge(int gpuDegree ) {

  /*Bottom GPU Temp Level Clear Box,*/
  tft.fillRoundRect(299 - 6 , 129,   8, 102 , 1, ILI9341_BLACK);

  float GPUtempfactor = gpuDegree;

  /*Attempt to reverse direction of Bar Scale, and get rid of decimal point for coordinates,*/
  int GPUtempScalefactor = (GPUtempfactor + 1); // +1 so it always shows something

  if (GPUtempfactor >= 0 ) {
    /*Bottom GPU Temp Bar Scale,*/
    tft.fillRoundRect(299 - 6 , 130,  8, GPUtempScalefactor , 1, ILI9341_GREEN); // Bottom GPU Temp Scale
  }

  if (GPUtempfactor >= 25 ) {
    /*Bottom GPU Temp Bar Scale,*/
    tft.fillRoundRect(299 - 6 , 130,  8, GPUtempScalefactor , 1, ILI9341_GREEN); // Bottom GPU Temp Scale
  }

  if (GPUtempfactor >= 50 ) {
    /*Bottom GPU Temp Bar Scale,*/
    tft.fillRoundRect(299 - 6 , 130,  8, GPUtempScalefactor , 1, ILI9341_GREEN); // Bottom GPU Temp Scale
  }

  if (GPUtempfactor >= 75 ) {
    /*Bottom GPU Temp Bar Scale,*/
    tft.fillRoundRect(299 - 6 , 130,  8, GPUtempScalefactor , 1, ILI9341_ORANGE); // Bottom GPU Temp Scale
  }

  if (GPUtempfactor >= 83 ) {
    /*Bottom GPU Temp Bar Scale,*/
    tft.fillRoundRect(299 - 6 , 130,  8, GPUtempScalefactor , 1, ILI9341_RED); // Bottom GPU Temp Scale
  }

  tft.drawRoundRect(299 - 6 , 129,   8, 92 , 1, ILI9341_WHITE);  // Draw rectangle round GPU temp bar
  
  /*Stop Scale running into MAX box,*/
  tft.fillRect (294  - 5 , 223,  27, 17 , ILI9341_BLACK);

  // Max Text box GPU
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setCursor(298 + 2 - 6 , 227);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("MAX");
  tft.drawRoundRect(295 + 2 - 6 , 224,  23, 13 , 1, ILI9341_WHITE);
}

//>>>>>>>>>>>> GPU LOAD

void GPU_loadLevelGauge(int gpuUsage ) {

  /*Bottom GPU Load Level Clear Box,*/
  tft.fillRoundRect(311 - 5 , 129,   8, 102 , 1, ILI9341_BLACK);

  float GPUloadfactor = gpuUsage;

  /*Attempt to reverse direction of Bar Scale, and get rid of decimal point for coordinates,*/
  int GPUloadScalefactor = (GPUloadfactor + 1); // +1 so it always shows something

  if (GPUloadfactor >= 0 ) {
    /*Bottom GPU Load Bar Scale,*/
    tft.fillRoundRect(311 - 5 , 130, 8, GPUloadScalefactor , 1, ILI9341_GREEN);
  }
  if (GPUloadfactor >= 25 ) {
    /*Bottom GPU Load Bar Scale,*/
    tft.fillRoundRect(311 - 5 , 130, 8, GPUloadScalefactor , 1, ILI9341_GREEN);
  }
  if (GPUloadfactor >= 50 ) {
    /*Bottom GPU Load Bar Scale,*/
    tft.fillRoundRect(311 - 5 , 130, 8, GPUloadScalefactor  , 1, ILI9341_GREEN);
  }
  if (GPUloadfactor >= 75 ) {
    /*Bottom GPU Load Bar Scale,*/
    tft.fillRoundRect(311 - 5 , 130, 8, GPUloadScalefactor , 1, ILI9341_ORANGE);
  }
  if (GPUloadfactor >= 90 ) {
    /*Bottom GPU Load Bar Scale,*/
    tft.fillRoundRect(311 - 5 , 130, 8, GPUloadScalefactor , 1, ILI9341_RED);
  }

    tft.drawRoundRect(311 - 5 , 129,   8, 92 , 1, ILI9341_WHITE); // Draw rectangle round GPU load bar
}
