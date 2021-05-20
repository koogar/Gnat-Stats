
/*

//*CPU/GPU Phat Tacho Simple Side level Gauge,*
//---------------------- CPU--------------------
//>>>>>>>>>>>> CPU LOAD

void CPU_loadLevelGauge(int cpuUsage ) {

  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);


  //*Top CPU Load Level Clear Box,*
  tft.fillRoundRect(311, 0,   8, 102 , 1, ILI9341_BLACK);

  float CPUloadfactor = cpuUsage;

  //*Attempt to reverse direction of Bar Scale, and get rid of decimal point for coordinates,*
  int CPUloadScalefactor =   ( CPUloadfactor + 1 ); // +1 so it always shows something


  //*Top CPU Load Bar Scale,*
  tft.fillRoundRect(311, 2,   8,  CPUloadScalefactor   , 1, ILI9341_GREEN); // Top CPU Load Scale

  //tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  //tft.print(CPUloadScalefactor);
}

//>>>>>>>>>>>> CPU TEMP

void CPU_tempLevelGauge(int cpuDegree ) {

  //*Top CPU Temp Level Clear Box,*
  tft.fillRoundRect(299, 2,   8, 102 , 1, ILI9341_BLACK);

  float CPUtempfactor = cpuDegree;

  //*Attempt to reverse direction of Bar Scale, and get rid of decimal point for coordinates,*
  int CPUtempScalefactor = (CPUtempfactor + 1); // +1 so it always shows something

  //*Top CPU Temp Bar Scale,*
  tft.fillRoundRect(299, 2,   8, CPUtempScalefactor  , 1, ILI9341_RED);  // Top CPU Temp Scale

  //*Stop Scale running into MAX box,*

  tft.fillRect (294 + 2 , 83,  25, 17 , ILI9341_BLACK); // Stop Scale running into MAX box

  // Max Text box CPU
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setCursor(298 + 2 , 90);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("MAX");
  tft.drawRoundRect(295 + 2 , 87,  23, 13 , 1, ILI9341_WHITE);

}



//---------------------- GPU--------------------
//>>>>>>>>>>>> GPU LOAD

void GPU_loadLevelGauge(int gpuUsage ) {

  //*Bottom GPU Load Level Clear Box,*
  tft.fillRoundRect(311 , 137,   8, 102 , 1, ILI9341_BLACK);

  float GPUloadfactor = gpuUsage;

  //*Attempt to reverse direction of Bar Scale, and get rid of decimal point for coordinates,*
  int GPUloadScalefactor = (GPUloadfactor + 1); // +1 so it always shows something

  //tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  //*Bottom GPU Load Bar Scale,*
  tft.fillRoundRect(311 , 137, 8, GPUloadScalefactor , 1, ILI9341_GREEN);

}

//>>>>>>>>>>>> GPU TEMP

void GPU_tempLevelGauge(int gpuDegree ) {

  //*Bottom GPU Temp Level Clear Box,*
  tft.fillRoundRect(299 , 137,   8, 102 , 1, ILI9341_BLACK);

  float GPUtempfactor = gpuDegree;

  //*Attempt to reverse direction of Bar Scale, and get rid of decimal point for coordinates,*
  int GPUtempScalefactor = (GPUtempfactor + 1); // +1 so it always shows something

  //*Bottom GPU Temp Bar Scale,*
  tft.fillRoundRect(299 , 137,  8, GPUtempScalefactor , 1, ILI9341_RED); // Bottom GPU Temp Scale

  //Stop Scale running into MAX box,*
  tft.fillRect (294 + 2 , 219,  25, 17 , ILI9341_BLACK);

  // Max Text box GPU
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setCursor(298 + 2 , 227);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("MAX");
  tft.drawRoundRect(295 + 2 , 224,  23, 13 , 1, ILI9341_WHITE);
}

*/
