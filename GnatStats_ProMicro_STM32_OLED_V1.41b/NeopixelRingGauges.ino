
/*
  ------------------------------------------------------------------------------------------
   _   _            _____ _          _    _____                        _
  | \ | |          |  __ (_)        | |  / ____|                      ( )
  |  \| | ___  ___ | |__) |__  _____| | | |  __  __ _ _   _  __ _  ___|/ ___
  | . ` |/ _ \/ _ \|  ___/ \ \/ / _ \ | | | |_ |/ _` | | | |/ _` |/ _ \ / __|
  | |\  |  __/ (_) | |   | |>  <  __/ | | |__| | (_| | |_| | (_| |  __/ \__ \
  |_| \_|\___|\___/|_|   |_/_/\_\___|_|  \_____|\__,_|\__,_|\__, |\___| |___/
                                                             __/ |
                                                            |___/

  Adafruit NeoPixel Ring CPU or GPU Gauge example (contibuted: James Bowen (Jimbob))

  CPU_loadGauge( cpuString2.toInt() ); // Neopixel Ring Gauge  CPU  Load
  CPU_tempGauge( cpuString1.toInt() ); // Neopixel Ring Gauge  CPU  Temperature

  GPU_loadGauge( gpuString2.toInt() ); // Neopixel Ring Gauge  GPU  Load
  GPU_tempGauge( gpuString1.toInt() ); // Neopixel Ring Gauge  GPU  Temperature

  refreshNeopixels(); // Clear neopixels every screen refresh, only have one instance running!!!

  CPU Pixel 15 - 8
  GPU Pixel  0 - 7
  ------------------------------------------------------------------------------------------
*/

void refreshNeopixels() {
  for ( int i = 0; i < NUMPIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 0, 0 );
  }
  //pixels.show();
}


//---------------------- CPU--------------------

void CPU_loadGauge(int cpuUsage ) {

  refreshNeopixels();

  float CPUloadfactor = cpuUsage ;

  if (CPUloadfactor >= 0 ) {
    pixels.setPixelColor(15, 229, 193, 0);
  }
  if (CPUloadfactor >= 12.5 ) {
    pixels.setPixelColor(14, 230, 165, 1);
  }
  if (CPUloadfactor >= (12.5 * 2) ) {
    pixels.setPixelColor(13, 232, 137, 2);
  }
  if (CPUloadfactor >= (12.5 * 3) ) {
    pixels.setPixelColor(12, 233, 110, 3);
  }
  if (CPUloadfactor >= (12.5 * 4) ) {
    pixels.setPixelColor(11, 235, 82, 4);
  }
  if (CPUloadfactor >= (12.5 * 5) ) {
    pixels.setPixelColor(10, 236, 55, 5);
  }
  if (CPUloadfactor >= (12.5 * 6) ) {
    pixels.setPixelColor(9, 238, 27, 6);
  }
  if (CPUloadfactor >= (12.5 * 7) ) {
    pixels.setPixelColor(8, 240, 0, 7);
  }

  pixels.show();

}



void CPU_tempGauge(int cpuDegree ) {

  //refreshNeopixels();

  float CPUtempfactor = cpuDegree ;

  if (CPUtempfactor >= 0 ) {
    pixels.setPixelColor(0, 229, 193, 0);
  }
  if (CPUtempfactor >= 12.5 ) {
    pixels.setPixelColor(1, 230, 165, 1);
  }
  if (CPUtempfactor >= (12.5 * 2) ) {
    pixels.setPixelColor(2, 232, 137, 2);
  }
  if (CPUtempfactor >= (12.5 * 3) ) {
    pixels.setPixelColor(3, 233, 110, 3);
  }
  if (CPUtempfactor >= (12.5 * 4) ) {
    pixels.setPixelColor(4, 235, 82, 4);
  }
  if (CPUtempfactor >= (12.5 * 5) ) {
    pixels.setPixelColor(5, 236, 55, 5);
  }
  if (CPUtempfactor >= (12.5 * 6) ) {
    pixels.setPixelColor(6, 238, 27, 6);
  }
  //if (CPUtempfactor >= (12.5 * 7) ){
  //  pixels.setPixelColor(7, 240, 0, 7);
  //}

  pixels.show();

}

//---------------------- GPU--------------------




void GPU_loadGauge(int gpuUsage ) {

  //refreshNeopixels();

  float GPUloadfactor = gpuUsage ;

  if (GPUloadfactor >= 0 ) {
    pixels.setPixelColor(0, 229, 193, 0);
  }
  if (GPUloadfactor >= 12.5 ) {
    pixels.setPixelColor(1, 230, 165, 1);
  }
  if (GPUloadfactor >= (12.5 * 2) ) {
    pixels.setPixelColor(2, 232, 137, 2);
  }
  if (GPUloadfactor >= (12.5 * 3) ) {
    pixels.setPixelColor(3, 233, 110, 3);
  }
  if (GPUloadfactor >= (12.5 * 4) ) {
    pixels.setPixelColor(4, 235, 82, 4);
  }
  if (GPUloadfactor >= (12.5 * 5) ) {
    pixels.setPixelColor(5, 236, 55, 5);
  }
  if (GPUloadfactor >= (12.5 * 6) ) {
    pixels.setPixelColor(6, 238, 27, 6);
  }
  if (GPUloadfactor >= (12.5 * 7) ) {
    pixels.setPixelColor(7, 240, 0, 7);
  }

  pixels.show();

}



void GPU_tempGauge(int gpuDegree ) {

  //refreshNeopixels();

  float GPUtempfactor = gpuDegree ;

  if (GPUtempfactor >= 0 ) {
    pixels.setPixelColor(0, 229, 193, 0);
  }
  if (GPUtempfactor >= 12.5 ) {
    pixels.setPixelColor(1, 230, 165, 1);
  }
  if (GPUtempfactor >= (12.5 * 2) ) {
    pixels.setPixelColor(2, 232, 137, 2);
  }
  if (GPUtempfactor >= (12.5 * 3) ) {
    pixels.setPixelColor(3, 233, 110, 3);
  }
  if (GPUtempfactor >= (12.5 * 4) ) {
    pixels.setPixelColor(4, 235, 82, 4);
  }
  if (GPUtempfactor >= (12.5 * 5) ) {
    pixels.setPixelColor(5, 236, 55, 5);
  }
  if (GPUtempfactor >= (12.5 * 6) ) {
    pixels.setPixelColor(6, 238, 27, 6);
  }
  if (GPUtempfactor >= (12.5 * 7) ) {
    pixels.setPixelColor(7, 240, 0, 7);
  }

  pixels.show();

}
