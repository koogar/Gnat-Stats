

//---------------------- CPU--------------------

void CPU_loadGauge(int cpuUsage ) {

  tft.fillRoundRect(296 + 15, 0,   8, 100 , 1, ILI9341_BLACK); // top right corner LS

  float CPUloadfactor = cpuUsage ;

  tft.fillRoundRect(296 + 15, 2,   8, CPUloadfactor   , 1, ILI9341_GREEN); // top right corner LS
}


void CPU_tempGauge(int cpuDegree ) {

  tft.fillRoundRect(270 + 29, 2,   8, 100 , 1, ILI9341_BLACK); // top right corner LS

  float CPUtempfactor = cpuDegree ;

  tft.fillRoundRect(270 + 29, 2,   8, CPUtempfactor  , 1, ILI9341_RED); // top right corner LS

  tft.setCursor(298, 90);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("MAX");
}



//---------------------- GPU--------------------


void GPU_loadGauge(int gpuUsage ) {

  tft.fillRoundRect(296+ 15 , 137,   8, 100 , 1, ILI9341_BLACK); // top right corner LS

  float GPUloadfactor = gpuUsage ;

  tft.fillRoundRect(296+ 15 , 137, 8, GPUloadfactor , 1, ILI9341_BLUE); // bottom right corner LS

}

void GPU_tempGauge(int gpuDegree ) {

  tft.fillRoundRect(270 + 29, 137,   8, 100 , 1, ILI9341_BLACK); // top right corner LS


  float GPUtempfactor = gpuDegree ;
  tft.fillRoundRect(270 + 29 , 137,  8, GPUtempfactor , 1, ILI9341_YELLOW); // bottom right corner LS

  tft.setCursor(298, 227);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("MAX");
}
