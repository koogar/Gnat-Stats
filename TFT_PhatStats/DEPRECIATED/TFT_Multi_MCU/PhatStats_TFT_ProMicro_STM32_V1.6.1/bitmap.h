/*
     ___ ___ _____ __  __   _   ___  ___
    | _ )_ _|_   _|  \/  | /_\ | _ \/ __|
    | _ \| |  | | | |\/| |/ _ \|  _/\__ \
    |___/___| |_| |_|  |_/_/ \_\_|  |___/
*/

#define CPU_BMP2_width 41
#define CPU_BMP2_height 41

const unsigned char CPU_BMP2 [] PROGMEM = {
  // 'CPU_41x41, 41x41px
  0x3f, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x00, 0xf8, 0x00, 0x00, 0x00,
  0x0f, 0x80, 0xe0, 0x00, 0x00, 0x00, 0x03, 0x80, 0xe0, 0x00, 0x00, 0x00, 0x03, 0x80, 0xc3, 0xff,
  0xff, 0xff, 0xe1, 0x80, 0xc7, 0xff, 0xff, 0xff, 0xf1, 0x80, 0xc7, 0xff, 0xff, 0xff, 0xf1, 0x80,
  0xc7, 0x80, 0x00, 0x00, 0xf1, 0x80, 0xc7, 0x00, 0x00, 0x00, 0x71, 0x80, 0xc7, 0x00, 0x00, 0x00,
  0x71, 0x80, 0xc7, 0x00, 0x00, 0x00, 0x71, 0x80, 0xc7, 0x00, 0x00, 0x00, 0x71, 0x80, 0xc7, 0x00,
  0x00, 0x00, 0x71, 0x80, 0xc7, 0x1c, 0x3c, 0x66, 0x71, 0x80, 0xc7, 0x3e, 0x3e, 0x66, 0x71, 0x80,
  0xc7, 0x33, 0x36, 0x66, 0x71, 0x80, 0xc7, 0x33, 0x33, 0x66, 0x71, 0x80, 0xc7, 0x33, 0x33, 0x66,
  0x71, 0x80, 0xc7, 0x30, 0x37, 0x66, 0x71, 0x80, 0xc7, 0x30, 0x3e, 0x66, 0x71, 0x80, 0xc7, 0x30,
  0x3e, 0x66, 0x71, 0x80, 0xc7, 0x33, 0x30, 0x66, 0x71, 0x80, 0xc7, 0x33, 0x30, 0x66, 0x71, 0x80,
  0xc7, 0x33, 0x30, 0x66, 0x71, 0x80, 0xc7, 0x3e, 0x30, 0x3e, 0x71, 0x80, 0xc7, 0x1c, 0x30, 0x1c,
  0x71, 0x80, 0xc7, 0x00, 0x00, 0x00, 0x71, 0x80, 0xc7, 0x00, 0x00, 0x00, 0x71, 0x80, 0xc7, 0x00,
  0x00, 0x00, 0x71, 0x80, 0xc7, 0x00, 0x00, 0x00, 0x71, 0x80, 0xc7, 0x00, 0x00, 0x00, 0x71, 0x80,
  0xc7, 0x80, 0x00, 0x00, 0xf1, 0x80, 0xc7, 0xff, 0xff, 0xff, 0xf1, 0x80, 0xc7, 0xff, 0xff, 0xff,
  0xf1, 0x80, 0xc3, 0xff, 0xff, 0xff, 0xe1, 0x80, 0xe0, 0x01, 0xff, 0xc0, 0x03, 0x80, 0xe0, 0x01,
  0xff, 0xc0, 0x03, 0x80, 0xf8, 0x01, 0xff, 0xc0, 0x0f, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x3f, 0xff, 0xff, 0xff, 0xfe, 0x00
};
//----------------------------------------------------------------------------------------------
#define CPU_BMP_width 34
#define CPU_BMP_height 14

const unsigned char CPU_BMP [] PROGMEM = {
  // 'CPU2, 34x14px
  0x00, 0x7f, 0xff, 0x80, 0x00, 0x7e, 0xc0, 0x00, 0xdf, 0x80, 0x7e, 0x5f, 0xfe, 0x9f, 0x80, 0x00,
  0xd0, 0x02, 0xc0, 0x00, 0x7e, 0x54, 0x42, 0x9f, 0x80, 0x7e, 0xd1, 0x12, 0xdf, 0x80, 0x00, 0x54,
  0x42, 0x80, 0x00, 0x00, 0x51, 0x12, 0x80, 0x00, 0x7e, 0xd4, 0x42, 0xdf, 0x80, 0x7e, 0x51, 0x12,
  0x9f, 0x80, 0x00, 0xd0, 0x02, 0xc0, 0x00, 0x7e, 0x5f, 0xfe, 0x9f, 0x80, 0x7e, 0xc0, 0x00, 0xdf,
  0x80, 0x00, 0x7f, 0xff, 0x80, 0x00
};


//----------------------------------------------------------------------------------------------

#define GPU_BMP2_width 44
#define GPU_BMP2_height 41

const unsigned char GPU_BMP2 [] PROGMEM = {
  // 'GPU_44x41, 44x41px
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xff, 
  0xff, 0xff, 0xff, 0xc0, 0x0e, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x70, 
  0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 
  0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x2f, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x2e, 0x7f, 
  0xff, 0xff, 0x00, 0xf0, 0x2e, 0x00, 0x00, 0x00, 0x78, 0x70, 0x2e, 0xff, 0xff, 0xf9, 0xfe, 0x30, 
  0x2e, 0x00, 0x00, 0x03, 0xff, 0x10, 0x2e, 0xff, 0xff, 0xf3, 0xcf, 0x10, 0x2e, 0xff, 0xff, 0xe7, 
  0x87, 0x90, 0x3e, 0x00, 0x00, 0x07, 0xb7, 0x90, 0x0e, 0xff, 0xff, 0xe7, 0x87, 0x90, 0x0e, 0xff, 
  0xff, 0xf3, 0xcf, 0x10, 0x0e, 0x00, 0x00, 0x01, 0xfe, 0x10, 0x3e, 0xff, 0xff, 0xf9, 0xfe, 0x30, 
  0x2e, 0x00, 0x00, 0x00, 0x78, 0x70, 0x2e, 0x7f, 0xff, 0xff, 0x00, 0xf0, 0x2f, 0x00, 0x00, 0x00, 
  0x01, 0xf0, 0x2f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x2f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 
  0xff, 0xff, 0xff, 0xf0, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x70, 0x0e, 0xff, 0xff, 0xff, 0xff, 0xf0, 
  0x0e, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0e, 0x06, 0xdb, 0x63, 0x6c, 0x00, 0x0e, 0x07, 0xff, 0xe3, 
  0xfc, 0x00, 0x0e, 0x07, 0xff, 0xe3, 0xfc, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x0c, 0x00, 0x00, 0x00, 0x00, 0x00
};
//----------------------------------------------------------------------------------------------
#define GPU_BMP_width 34
#define GPU_BMP_height 14

const unsigned char GPU_BMP [] PROGMEM = {
  // 'GPU, 34x14px
  0xc0, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0x80, 0x70, 0x00, 0x02, 0x01, 0xc0, 0xc8,
  0x00, 0x04, 0x70, 0xc0, 0xc7, 0xff, 0xf8, 0x89, 0x40, 0xc0, 0x00, 0x01, 0x54, 0x40, 0x5f, 0xff,
  0xf9, 0x25, 0x40, 0x40, 0x00, 0x01, 0x54, 0x40, 0xc7, 0xff, 0xf8, 0x89, 0x40, 0xc8, 0x00, 0x04,
  0x70, 0xc0, 0x70, 0x00, 0x02, 0x01, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0x80, 0x47, 0xff, 0x80, 0x00,
  0x00, 0x46, 0xff, 0x80, 0x00, 0x00
};
//----------------------------------------------------------------------------------------------

#define JustTheGnatBMP_width 64
#define JustTheGnatBMP_height 64

const unsigned char JustGnatBMP [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xe0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xf0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xcc, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe9, 0xf8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0xeb, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe3, 0xfc, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0xe1, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x78, 0x07, 0xe1, 0xe6, 0x00, 0x00, 0x00,
  0x00, 0xfc, 0x07, 0xcc, 0xce, 0x00, 0x00, 0x00, 0x01, 0xff, 0x03, 0xde, 0x1f, 0x00, 0x00, 0x00,
  0x03, 0xe7, 0xc1, 0x9e, 0x3f, 0x00, 0x00, 0x00, 0x07, 0xef, 0xe1, 0xff, 0x3f, 0x00, 0x00, 0x00,
  0x0f, 0xef, 0xf8, 0x7e, 0x1f, 0x80, 0x00, 0x00, 0x0e, 0xef, 0xfc, 0x3e, 0x9f, 0x80, 0x00, 0x00,
  0x1f, 0x0f, 0x9e, 0x1c, 0xc8, 0x80, 0x00, 0x00, 0x3f, 0xcf, 0x9f, 0x0d, 0xe3, 0x80, 0x00, 0x00,
  0x3f, 0xc7, 0xbf, 0x87, 0xe7, 0x80, 0x00, 0x00, 0x7f, 0xd0, 0xbf, 0xe3, 0xf7, 0x80, 0x00, 0x00,
  0x7f, 0x1c, 0x3f, 0xe1, 0xe7, 0x80, 0x00, 0x00, 0x7f, 0x3f, 0x1c, 0xf0, 0xe7, 0x00, 0x00, 0x00,
  0x3f, 0xff, 0x0d, 0xf9, 0xff, 0xe0, 0x00, 0x00, 0x0f, 0xff, 0x21, 0xff, 0xf0, 0x38, 0x00, 0x00,
  0x07, 0xff, 0x71, 0xfc, 0x00, 0x06, 0xc0, 0x00, 0x00, 0xfe, 0x79, 0xf8, 0x06, 0x0f, 0xe0, 0x00,
  0x00, 0x1f, 0xf8, 0xe0, 0x3f, 0x8f, 0xf8, 0x00, 0x00, 0x01, 0xfe, 0x60, 0xff, 0x8f, 0xfe, 0x00,
  0x00, 0x00, 0x7f, 0x41, 0xff, 0xc7, 0xff, 0x00, 0x00, 0x00, 0x0f, 0x83, 0xff, 0xc7, 0xff, 0x00,
  0x00, 0x00, 0x01, 0x87, 0xff, 0xe7, 0xff, 0x80, 0x00, 0x00, 0x01, 0x07, 0xff, 0xe3, 0xff, 0x80,
  0x00, 0x00, 0x03, 0x07, 0xff, 0xf3, 0x9f, 0x80, 0x00, 0x00, 0x02, 0x0f, 0xff, 0xf3, 0x0f, 0x80,
  0x00, 0x00, 0x06, 0x0f, 0xff, 0x32, 0x27, 0x80, 0x00, 0x00, 0x04, 0x0f, 0xfe, 0x1b, 0x07, 0x80,
  0x00, 0x00, 0x04, 0x0f, 0xfc, 0x49, 0x8f, 0x00, 0x00, 0x00, 0x04, 0x07, 0xfe, 0x09, 0xff, 0x80,
  0x00, 0x00, 0x0c, 0x03, 0xff, 0x18, 0xff, 0xe0, 0x00, 0x00, 0x0c, 0x01, 0xff, 0xf0, 0x3d, 0x60,
  0x00, 0x00, 0x0c, 0x00, 0xff, 0xc0, 0x01, 0x38, 0x00, 0x00, 0x04, 0x00, 0x07, 0x00, 0x01, 0x8c,
  0x00, 0x00, 0x06, 0x00, 0x00, 0x1e, 0x03, 0x86, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x76, 0x07, 0xe2,
  0x00, 0x00, 0x1b, 0x00, 0x00, 0xec, 0x1c, 0x30, 0x00, 0x00, 0x39, 0x80, 0x00, 0xd8, 0x30, 0x10,
  0x00, 0x00, 0x30, 0x80, 0x00, 0xb0, 0x78, 0x18, 0x00, 0x00, 0x30, 0xe0, 0x00, 0xe0, 0xdc, 0x18,
  0x00, 0x00, 0x30, 0x78, 0x00, 0xc3, 0x8e, 0x0e, 0x00, 0x03, 0xe0, 0x4c, 0x00, 0x07, 0x03, 0x0f,
  0x00, 0x3f, 0xc0, 0x46, 0x00, 0x0c, 0x03, 0x00, 0x00, 0x38, 0x00, 0x43, 0xe0, 0x18, 0x01, 0x80,
  0x00, 0x00, 0x00, 0xc1, 0xff, 0xf0, 0x00, 0x80, 0x00, 0x00, 0x00, 0xc1, 0x83, 0x80, 0x00, 0xc0,
  0x00, 0x00, 0x00, 0xc3, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0xc2, 0x00, 0x00, 0x00, 0x7c,
  0x00, 0x00, 0x07, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x06, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

};
//----------------------------------------------------------------------------------------------

#define WaitingDataBMP90_width 64
#define WaitingDataBMP90_height 128

const unsigned char WaitingDataBMP90 [] PROGMEM = {
  // '128x64_Template_90, 64x128px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00,
  0x01, 0xf3, 0x80, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x01, 0x99, 0x80, 0xff, 0xff, 0xff, 0xfe, 0x00,
  0x01, 0x99, 0x81, 0xff, 0xff, 0xff, 0xff, 0x00, 0x01, 0xcf, 0x83, 0xff, 0xff, 0xff, 0xdf, 0x80,
  0x00, 0xff, 0x03, 0xfb, 0xff, 0xfc, 0xdf, 0x80, 0x00, 0x7e, 0x07, 0xfb, 0xff, 0xfc, 0xdf, 0xc0,
  0x00, 0x00, 0x07, 0xfb, 0xff, 0xfc, 0xdf, 0xc0, 0x00, 0x00, 0x07, 0xfb, 0x00, 0x00, 0xdf, 0xc0,
  0x01, 0x83, 0x07, 0xfb, 0x00, 0x00, 0xdf, 0xc0, 0x01, 0x83, 0x07, 0xfb, 0xff, 0xfc, 0xdf, 0xc0,
  0x01, 0x81, 0x87, 0xfb, 0xff, 0xfc, 0xdf, 0xc0, 0x01, 0xff, 0x87, 0xfb, 0xff, 0xfc, 0xdf, 0xc0,
  0x01, 0xff, 0x87, 0xfb, 0xff, 0xff, 0xdf, 0xc0, 0x01, 0x80, 0x07, 0xfb, 0x00, 0x00, 0xdf, 0xc0,
  0x01, 0x80, 0x07, 0xfb, 0x00, 0x00, 0xdf, 0xc0, 0x00, 0x00, 0x07, 0xfb, 0xfe, 0x07, 0xdf, 0xc0,
  0x00, 0x7e, 0x07, 0xfb, 0xf8, 0x1f, 0xdf, 0xc0, 0x00, 0xff, 0x07, 0xfb, 0xc0, 0x7f, 0xdf, 0xc0,
  0x01, 0xf3, 0x87, 0xfb, 0xf8, 0x1f, 0xdf, 0xc0, 0x01, 0x99, 0x87, 0xfb, 0xfe, 0x07, 0xdf, 0xc0,
  0x01, 0x99, 0x87, 0xfb, 0x00, 0x00, 0xdf, 0xc0, 0x01, 0xcf, 0x87, 0xfb, 0x00, 0x00, 0xdf, 0xc0,
  0x00, 0xff, 0x07, 0xfb, 0xff, 0xff, 0xdf, 0xc0, 0x00, 0x7e, 0x07, 0xfb, 0xff, 0xff, 0xdf, 0xc0,
  0x00, 0x00, 0x07, 0xfb, 0x00, 0x00, 0xdf, 0xc0, 0x00, 0x00, 0x07, 0xfb, 0x00, 0x00, 0xdf, 0xc0,
  0x01, 0x83, 0x07, 0xfb, 0x3f, 0xff, 0xdf, 0xc0, 0x01, 0x83, 0x07, 0xfb, 0x3f, 0xff, 0xdf, 0xc0,
  0x01, 0x81, 0x87, 0xfb, 0x3f, 0xff, 0xdf, 0xc0, 0x01, 0xff, 0x87, 0xfb, 0x86, 0x7f, 0xdf, 0xc0,
  0x01, 0xff, 0x87, 0xfb, 0x02, 0x3f, 0xdf, 0xc0, 0x01, 0x80, 0x07, 0xfb, 0x3b, 0x3f, 0xdf, 0xc0,
  0x01, 0x80, 0x07, 0xfb, 0x3b, 0x3f, 0xdf, 0xc0, 0x00, 0x00, 0x07, 0xfb, 0x00, 0x3f, 0xdf, 0xc0,
  0x00, 0x7e, 0x07, 0xfb, 0x80, 0x7f, 0xdf, 0xc0, 0x00, 0xff, 0x07, 0xfb, 0xff, 0xff, 0xdf, 0xc0,
  0x01, 0xf3, 0x87, 0xfb, 0x00, 0x00, 0xdf, 0xc0, 0x01, 0x99, 0x87, 0xfb, 0x00, 0x00, 0xdf, 0xc0,
  0x01, 0x99, 0x87, 0xfb, 0x3f, 0x3f, 0xdf, 0xc0, 0x01, 0xcf, 0x87, 0xfb, 0x3f, 0x3f, 0xdf, 0xc0,
  0x00, 0xff, 0x07, 0xfb, 0x00, 0x3f, 0xdf, 0xc0, 0x00, 0x7e, 0x07, 0xfb, 0x80, 0x7f, 0xdf, 0xc0,
  0x00, 0x00, 0x07, 0xfb, 0xff, 0xff, 0xdf, 0xc0, 0x00, 0x00, 0x07, 0xfb, 0x98, 0x7f, 0xdf, 0xc0,
  0x01, 0x83, 0x07, 0xfb, 0x18, 0x3f, 0xdf, 0xc0, 0x01, 0x83, 0x07, 0xfb, 0x33, 0x3f, 0xdf, 0xc0,
  0x01, 0x81, 0x87, 0xfb, 0x23, 0x3f, 0xdf, 0xc0, 0x01, 0xff, 0x87, 0xfb, 0x06, 0x3f, 0xdf, 0xc0,
  0x01, 0xff, 0x87, 0xfb, 0x86, 0x7f, 0xdf, 0xc0, 0x01, 0x80, 0x07, 0xfb, 0xff, 0xff, 0xdf, 0xc0,
  0x01, 0x80, 0x07, 0xfb, 0xff, 0xff, 0xdf, 0xc0, 0x00, 0x00, 0x07, 0xfb, 0xff, 0xff, 0xdf, 0xc0,
  0x00, 0x7e, 0x03, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0xf3, 0x83, 0xff, 0xff, 0xff, 0xff, 0x80, 0x01, 0x99, 0x81, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x01, 0x99, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xcf, 0x80, 0x7f, 0xfe, 0xff, 0xfc, 0x00,
  0x00, 0xff, 0x00, 0x7f, 0xfe, 0xff, 0xfc, 0x00, 0x00, 0x7e, 0x00, 0x7f, 0xfe, 0xff, 0xfc, 0x00,
  0x00, 0x00, 0x00, 0x7f, 0xf8, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfb, 0xff, 0xfc, 0x00,
  0x01, 0x83, 0x00, 0x7f, 0xfb, 0xff, 0xfc, 0x00, 0x01, 0x83, 0x00, 0x7f, 0xf8, 0xff, 0xfc, 0x00,
  0x01, 0x81, 0x80, 0x7f, 0xfe, 0xff, 0xfc, 0x00, 0x01, 0xff, 0x80, 0x7c, 0x1e, 0xf0, 0x7c, 0x00,
  0x01, 0xff, 0x80, 0x7c, 0x1e, 0xf0, 0x7c, 0x00, 0x01, 0x80, 0x00, 0x7c, 0x1e, 0xf0, 0x7c, 0x00,
  0x01, 0x80, 0x00, 0x7c, 0x1e, 0xf0, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x1e, 0xf0, 0x7c, 0x00,
  0x00, 0x7e, 0x00, 0x7c, 0x1e, 0xf0, 0x7c, 0x00, 0x00, 0xff, 0x00, 0x7c, 0x1e, 0xf0, 0x7c, 0x00,
  0x01, 0xf3, 0x80, 0x7f, 0xfe, 0xff, 0xfc, 0x00, 0x01, 0x99, 0x80, 0x7f, 0xfe, 0x3f, 0xfc, 0x00,
  0x01, 0x99, 0x80, 0x7f, 0xff, 0xbf, 0xfc, 0x00, 0x01, 0xcf, 0x80, 0x7f, 0xff, 0xbf, 0xfc, 0x00,
  0x00, 0xff, 0x00, 0x7f, 0xfe, 0x3f, 0xfc, 0x00, 0x00, 0x7e, 0x00, 0x7f, 0xfe, 0xff, 0xfc, 0x00,
  0x00, 0x00, 0x00, 0x7f, 0xfe, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, 0xff, 0xf8, 0x00,
  0x01, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x81, 0x80, 0x00, 0x03, 0x80, 0x00, 0x00, 0x01, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0xff, 0x80, 0x00, 0x03, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x80, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x7e, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0xf3, 0x80, 0x00, 0x03, 0x80, 0x00, 0x00, 0x01, 0x99, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x99, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xcf, 0x87, 0xff, 0xff, 0xff, 0xff, 0xc0,
  0x00, 0xff, 0x06, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x7e, 0x04, 0x00, 0x00, 0x00, 0x00, 0x20,
  0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x20,
  0x01, 0x83, 0x04, 0x00, 0x00, 0x00, 0x00, 0x20, 0x01, 0x83, 0x04, 0x00, 0x00, 0x00, 0x00, 0x20,
  0x01, 0x81, 0x84, 0x00, 0x00, 0x00, 0x00, 0x20, 0x01, 0xff, 0x84, 0xf0, 0xe1, 0xc3, 0x87, 0x20,
  0x01, 0xff, 0x85, 0xf0, 0xe1, 0xc3, 0x87, 0xa0, 0x01, 0x80, 0x05, 0xff, 0xff, 0xff, 0xff, 0xa0,
  0x01, 0x80, 0x05, 0xff, 0xff, 0xff, 0xff, 0xa0, 0x00, 0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xa0,
  0x00, 0x7e, 0x05, 0xff, 0xff, 0xff, 0xff, 0xa0, 0x00, 0xff, 0x04, 0xff, 0xff, 0xff, 0xff, 0x20,
  0x01, 0xf3, 0x84, 0x00, 0x00, 0x00, 0x00, 0x20, 0x01, 0x99, 0x86, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x01, 0x99, 0x83, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x01, 0xcf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
//----------------------------------------------------------------------------------------------


#define WaitingDataBMP_width 128
#define WaitingDataBMP_height 64

const unsigned char WaitingDataBMP [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfc, 0x00,
  0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00,
  0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfa, 0x00, 0x00, 0x00, 0x00, 0x04, 0x03, 0xe2, 0x00,
  0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 0xf2, 0x00,
  0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 0xf2, 0x00,
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x7f, 0xff, 0xfe, 0x00, 0x04, 0x07, 0xf2, 0x00,
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x7f, 0xff, 0xff, 0x00, 0x04, 0x01, 0xf2, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x7f, 0xff, 0xff, 0x00, 0x04, 0x01, 0xf2, 0x00,
  0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x7f, 0xff, 0xff, 0x00, 0x04, 0x01, 0xf2, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x7f, 0xff, 0xff, 0x00, 0x04, 0x01, 0xf2, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x7f, 0x80, 0xff, 0x00, 0x04, 0x07, 0xf2, 0x00,
  0x01, 0xf0, 0x09, 0xf3, 0x3f, 0xf3, 0xff, 0xfb, 0x7f, 0x80, 0xff, 0x00, 0x04, 0x07, 0xf2, 0x00,
  0x01, 0xf0, 0x09, 0xf3, 0x3f, 0xf3, 0xff, 0xfb, 0x7f, 0x80, 0xff, 0x00, 0x04, 0x07, 0xf2, 0x00,
  0x01, 0xfe, 0x79, 0xf3, 0x3f, 0xf3, 0xff, 0xfb, 0x7f, 0x80, 0xff, 0x00, 0x04, 0x01, 0xf2, 0x00,
  0x01, 0xfe, 0x78, 0xe3, 0x3f, 0xf3, 0xff, 0xfb, 0x7f, 0x80, 0xff, 0x00, 0x04, 0x01, 0xf2, 0x00,
  0x01, 0xfe, 0x78, 0xe3, 0x3f, 0xf3, 0xff, 0xfb, 0x7f, 0xff, 0xff, 0x00, 0x04, 0x01, 0xf2, 0x00,
  0x01, 0xfe, 0x78, 0x43, 0x3f, 0xf3, 0xff, 0xfb, 0x7f, 0xff, 0xff, 0x00, 0x04, 0x01, 0xf2, 0x00,
  0x01, 0xfe, 0x78, 0x43, 0x3c, 0x30, 0x70, 0xfb, 0x7f, 0xff, 0x87, 0x00, 0x04, 0x07, 0xf2, 0x00,
  0x01, 0xfe, 0x78, 0x03, 0x38, 0x10, 0x20, 0x7b, 0x7f, 0xff, 0xb7, 0x2a, 0xa4, 0x07, 0xf2, 0x00,
  0x01, 0xfe, 0x78, 0x03, 0x39, 0x93, 0x26, 0x7b, 0x06, 0x00, 0x30, 0x2a, 0xa4, 0x07, 0xf2, 0x00,
  0x01, 0xfe, 0x79, 0x13, 0x3f, 0x93, 0x27, 0xfb, 0x76, 0xff, 0xff, 0x2a, 0xa4, 0x01, 0xf2, 0x00,
  0x01, 0xfe, 0x79, 0x13, 0x3c, 0x13, 0x21, 0xfb, 0x70, 0xff, 0xff, 0x00, 0x04, 0x01, 0xf2, 0x00,
  0x01, 0xfe, 0x79, 0xb3, 0x39, 0x93, 0x38, 0x7b, 0x7f, 0xff, 0xff, 0x00, 0x04, 0x01, 0xf2, 0x00,
  0x01, 0xfe, 0x79, 0xb3, 0x39, 0x93, 0x3c, 0x7b, 0x7f, 0xff, 0xff, 0x00, 0x04, 0x01, 0xf2, 0x00,
  0x01, 0xfe, 0x79, 0xb3, 0x39, 0x93, 0x26, 0x7b, 0x7f, 0x80, 0xff, 0x00, 0x04, 0x07, 0xf2, 0x00,
  0x01, 0xfe, 0x79, 0xf3, 0x00, 0x10, 0x20, 0x7b, 0x7f, 0x80, 0xff, 0x00, 0x04, 0x07, 0xf2, 0x00,
  0x01, 0xfe, 0x79, 0xf3, 0x04, 0x30, 0x70, 0xfb, 0x7f, 0x80, 0xff, 0x00, 0x04, 0x07, 0xf2, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x7f, 0x80, 0xff, 0x00, 0x04, 0x01, 0xf2, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x7f, 0x80, 0xff, 0x00, 0x04, 0x01, 0xf2, 0x00,
  0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x7f, 0xff, 0xff, 0x00, 0x04, 0x01, 0xf2, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x7f, 0xff, 0xff, 0x00, 0x04, 0x01, 0xf2, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x7f, 0xff, 0xff, 0x00, 0x04, 0x07, 0xf2, 0x00,
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x7f, 0xff, 0xff, 0x00, 0x04, 0x07, 0xf2, 0x00,
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x7f, 0xff, 0xfe, 0x00, 0x04, 0x07, 0xf2, 0x00,
  0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 0xf2, 0x00,
  0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x00, 0x00, 0x00, 0x00, 0x04, 0x03, 0xe2, 0x00,
  0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfa, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00,
  0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xfc, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xf0, 0x38, 0x3c, 0x0e, 0x0f, 0x03, 0x83, 0xc0, 0xe0, 0xf0, 0x38, 0x3c, 0x0e, 0x0f, 0x00,
  0x01, 0xf8, 0xf8, 0x7e, 0x3e, 0x1f, 0x8f, 0x87, 0xe3, 0xe1, 0xf8, 0xf8, 0x7e, 0x3e, 0x1f, 0x80,
  0x03, 0x9c, 0xd8, 0xe7, 0x36, 0x39, 0xcd, 0x8e, 0x73, 0x63, 0x9c, 0xd8, 0xe7, 0x36, 0x39, 0xc0,
  0x03, 0x1c, 0x18, 0xc7, 0x06, 0x31, 0xc1, 0x8c, 0x70, 0x63, 0x1c, 0x18, 0xc7, 0x06, 0x31, 0xc0,
  0x03, 0x7c, 0x18, 0xdf, 0x06, 0x37, 0xc1, 0x8d, 0xf0, 0x63, 0x7c, 0x18, 0xdf, 0x06, 0x37, 0xc0,
  0x03, 0xec, 0x18, 0xfb, 0x06, 0x3e, 0xc1, 0x8f, 0xb0, 0x63, 0xec, 0x18, 0xfb, 0x06, 0x3e, 0xc0,
  0x03, 0x8c, 0x18, 0xe3, 0x06, 0x38, 0xc1, 0x8e, 0x30, 0x63, 0x8c, 0x18, 0xe3, 0x06, 0x38, 0xc0,
  0x03, 0x9c, 0x18, 0xe7, 0x06, 0x39, 0xc1, 0x8e, 0x70, 0x63, 0x9c, 0x18, 0xe7, 0x06, 0x39, 0xc0,
  0x01, 0xf8, 0xfe, 0x7e, 0x3f, 0x9f, 0x8f, 0xe7, 0xe3, 0xf9, 0xf8, 0xfe, 0x7e, 0x3f, 0x9f, 0x80,
  0x00, 0xf0, 0xfe, 0x3c, 0x3f, 0x8f, 0x0f, 0xe3, 0xc3, 0xf8, 0xf0, 0xfe, 0x3c, 0x3f, 0x8f, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


//----------------------------------------------------------------------------------------------
#define WaitingDataBMP90_width 76
#define WaitingDataBMP90_height 154

const unsigned char WaitingDataBMP2_90 [] PROGMEM = {
  // '76x154_Template_90, 76x154px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x01, 0xff, 0xff,
  0xff, 0xff, 0x80, 0x00, 0x00, 0x01, 0x80, 0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x01,
  0x80, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x01, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff,
  0xf8, 0x00, 0x7f, 0xff, 0x80, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0x80, 0x7f,
  0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x7f, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0x00,
  0x7f, 0xff, 0x81, 0xff, 0xdf, 0xff, 0xff, 0x8e, 0xff, 0x80, 0x30, 0x01, 0x81, 0xff, 0xdf, 0xff,
  0xff, 0x8e, 0xff, 0xc0, 0x38, 0x01, 0x81, 0xff, 0xdf, 0xff, 0xff, 0x8e, 0xff, 0xc0, 0x18, 0x01,
  0x81, 0xff, 0xdf, 0xff, 0xff, 0x8e, 0xff, 0xc0, 0x1c, 0x01, 0x81, 0xff, 0xdc, 0x00, 0x00, 0x0e,
  0xff, 0xc0, 0x0c, 0x01, 0x81, 0xff, 0xdc, 0x00, 0x00, 0x0e, 0xff, 0xc0, 0x08, 0x00, 0x01, 0xff,
  0xdc, 0x00, 0x00, 0x0e, 0xff, 0xc0, 0x01, 0xe0, 0x01, 0xff, 0xdf, 0xff, 0xff, 0x8e, 0xff, 0xc0,
  0x0f, 0xfc, 0x01, 0xff, 0xdf, 0xff, 0xff, 0x8e, 0xff, 0xc0, 0x1f, 0xfe, 0x01, 0xff, 0xdf, 0xff,
  0xff, 0x8e, 0xff, 0xc0, 0x3f, 0xff, 0x01, 0xff, 0xdf, 0xff, 0xff, 0x8e, 0xff, 0xc0, 0x3f, 0x9f,
  0x81, 0xff, 0xdf, 0xff, 0xff, 0xfe, 0xff, 0xc0, 0x3b, 0x87, 0x81, 0xff, 0xdc, 0x00, 0x00, 0x0e,
  0xff, 0xc0, 0x71, 0xc3, 0x81, 0xff, 0xdc, 0x00, 0x00, 0x0e, 0xff, 0xc0, 0x70, 0xc1, 0x81, 0xff,
  0xdc, 0x00, 0x00, 0xfe, 0xff, 0xc0, 0x70, 0xe1, 0x81, 0xff, 0xdf, 0xff, 0x01, 0xfe, 0xff, 0xc0,
  0x30, 0x71, 0x81, 0xff, 0xdf, 0xe0, 0x07, 0xfe, 0xff, 0xc0, 0x3c, 0x37, 0x81, 0xff, 0xdf, 0x80,
  0x3f, 0xfe, 0xff, 0xc0, 0x3f, 0xff, 0x01, 0xff, 0xdf, 0x80, 0x3f, 0xfe, 0xff, 0xc0, 0x1f, 0xff,
  0x01, 0xff, 0xdf, 0xe0, 0x07, 0xfe, 0xff, 0xc0, 0x0f, 0xfe, 0x01, 0xff, 0xdf, 0xff, 0x01, 0xfe,
  0xff, 0xc0, 0x03, 0xf8, 0x01, 0xff, 0xdc, 0x00, 0x00, 0xfe, 0xff, 0xc0, 0x00, 0x00, 0x01, 0xff,
  0xdc, 0x00, 0x00, 0x0e, 0xff, 0xc0, 0x00, 0x00, 0x01, 0xff, 0xdc, 0x00, 0x00, 0x0e, 0xff, 0xc0,
  0x00, 0x01, 0x81, 0xff, 0xdf, 0xff, 0xff, 0xfe, 0xff, 0xc0, 0x00, 0x01, 0x81, 0xff, 0xdf, 0xff,
  0xff, 0xfe, 0xff, 0xc0, 0x00, 0x01, 0x81, 0xff, 0xdf, 0xff, 0xff, 0xfe, 0xff, 0xc0, 0x00, 0x01,
  0x81, 0xff, 0xdc, 0x00, 0x00, 0x0e, 0xff, 0xc0, 0x7f, 0xff, 0x81, 0xff, 0xdc, 0x00, 0x00, 0x0e,
  0xff, 0xc0, 0x7f, 0xff, 0x81, 0xff, 0xdc, 0x00, 0x00, 0x0e, 0xff, 0xc0, 0x7f, 0xff, 0x81, 0xff,
  0xdc, 0x7f, 0xff, 0xfe, 0xff, 0xc0, 0x7f, 0xff, 0x81, 0xff, 0xdc, 0x7f, 0xff, 0xfe, 0xff, 0xc0,
  0x30, 0x01, 0x81, 0xff, 0xdc, 0x7f, 0xff, 0xfe, 0xff, 0xc0, 0x38, 0x01, 0x81, 0xff, 0xdc, 0x7f,
  0xff, 0xfe, 0xff, 0xc0, 0x18, 0x01, 0x81, 0xff, 0xdf, 0x8f, 0x3f, 0xfe, 0xff, 0xc0, 0x1c, 0x01,
  0x81, 0xff, 0xdc, 0x03, 0x1f, 0xfe, 0xff, 0xc0, 0x0c, 0x01, 0x81, 0xff, 0xdc, 0x03, 0x0f, 0xfe,
  0xff, 0xc0, 0x08, 0x00, 0x01, 0xff, 0xdc, 0x73, 0x8f, 0xfe, 0xff, 0xc0, 0x07, 0xf8, 0x01, 0xff,
  0xdc, 0x73, 0x8f, 0xfe, 0xff, 0xc0, 0x0f, 0xfc, 0x01, 0xff, 0xdc, 0x00, 0x0f, 0xfe, 0xff, 0xc0,
  0x1f, 0xfe, 0x01, 0xff, 0xde, 0x00, 0x1f, 0xfe, 0xff, 0xc0, 0x3f, 0xff, 0x01, 0xff, 0xdf, 0x00,
  0x3f, 0xfe, 0xff, 0xc0, 0x3f, 0x87, 0x81, 0xff, 0xdf, 0xff, 0xff, 0xfe, 0xff, 0xc0, 0x3b, 0x83,
  0x81, 0xff, 0xdc, 0x00, 0x00, 0x0e, 0xff, 0xc0, 0x71, 0xc3, 0x81, 0xff, 0xdc, 0x00, 0x00, 0x0e,
  0xff, 0xc0, 0x70, 0xe1, 0x81, 0xff, 0xdc, 0x00, 0x00, 0x0e, 0xff, 0xc0, 0x70, 0xf1, 0x81, 0xff,
  0xdc, 0x7f, 0x8f, 0xfe, 0xff, 0xc0, 0x30, 0x73, 0x81, 0xff, 0xdc, 0x7f, 0x8f, 0xfe, 0xff, 0xc0,
  0x3c, 0x3f, 0x81, 0xff, 0xdc, 0x3f, 0x0f, 0xfe, 0xff, 0xc0, 0x3f, 0xff, 0x01, 0xff, 0xdc, 0x00,
  0x0f, 0xfe, 0xff, 0xc0, 0x1f, 0xff, 0x01, 0xff, 0xde, 0x00, 0x1f, 0xfe, 0xff, 0xc0, 0x07, 0xfc,
  0x01, 0xff, 0xdf, 0x00, 0x3f, 0xfe, 0xff, 0xc0, 0x00, 0xe0, 0x01, 0xff, 0xdf, 0xff, 0xff, 0xfe,
  0xff, 0xc0, 0x00, 0x00, 0x01, 0xff, 0xde, 0x38, 0x3f, 0xfe, 0xff, 0xc0, 0x00, 0x01, 0x81, 0xff,
  0xdc, 0x38, 0x0f, 0xfe, 0xff, 0xc0, 0x00, 0x01, 0x81, 0xff, 0xdc, 0x70, 0x0f, 0xfe, 0xff, 0xc0,
  0x00, 0x01, 0x81, 0xff, 0xdc, 0x43, 0x8f, 0xfe, 0xff, 0xc0, 0x00, 0x01, 0x81, 0xff, 0xdc, 0x43,
  0x8f, 0xfe, 0xff, 0xc0, 0x7f, 0xff, 0x81, 0xff, 0xdc, 0x07, 0x0f, 0xfe, 0xff, 0xc0, 0x7f, 0xff,
  0x81, 0xff, 0xde, 0x07, 0x1f, 0xfe, 0xff, 0xc0, 0x7f, 0xff, 0x81, 0xff, 0xdf, 0x0f, 0x3f, 0xfe,
  0xff, 0xc0, 0x7f, 0xff, 0x81, 0xff, 0xdf, 0xff, 0xff, 0xfe, 0xff, 0xc0, 0x70, 0x01, 0x81, 0xff,
  0xdf, 0xff, 0xff, 0xfe, 0xff, 0xc0, 0x38, 0x01, 0x81, 0xff, 0xdf, 0xff, 0xff, 0xfe, 0xff, 0xc0,
  0x38, 0x01, 0x80, 0xff, 0xdf, 0xff, 0xff, 0xfe, 0xff, 0x80, 0x1c, 0x01, 0x80, 0x7f, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x00, 0x1c, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0x00, 0x0f, 0xfc, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x1f, 0xfe, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x3f, 0xff, 0x00, 0x0f, 0xff, 0xff, 0x7f, 0xff, 0xf8, 0x00, 0x3b, 0x87, 0x80, 0x0f, 0xff, 0xff,
  0x7f, 0xff, 0xf8, 0x00, 0x73, 0x83, 0x80, 0x0f, 0xff, 0xff, 0x7f, 0xff, 0xf8, 0x00, 0x71, 0xc3,
  0x80, 0x0f, 0xff, 0xff, 0x7f, 0xff, 0xf8, 0x00, 0x70, 0xe1, 0x80, 0x0f, 0xff, 0xf8, 0x7f, 0xff,
  0xf8, 0x00, 0x70, 0x71, 0x80, 0x0f, 0xff, 0xfb, 0xff, 0xff, 0xf8, 0x00, 0x30, 0x73, 0x80, 0x0f,
  0xff, 0xfb, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0x3f, 0x80, 0x0f, 0xff, 0xfb, 0xff, 0xff, 0xf8, 0x00,
  0x3f, 0xff, 0x00, 0x0f, 0xff, 0xf8, 0x7f, 0xff, 0xf8, 0x00, 0x1f, 0xff, 0x00, 0x0f, 0xff, 0xff,
  0x7f, 0xff, 0xf8, 0x00, 0x07, 0xfc, 0x00, 0x0f, 0xff, 0xff, 0x7f, 0xff, 0xf8, 0x00, 0x00, 0xe0,
  0x00, 0x0f, 0xf0, 0x3f, 0x7e, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x3f, 0x7e, 0x07,
  0xf8, 0x00, 0x00, 0x01, 0x80, 0x0f, 0xf0, 0x3f, 0x7e, 0x07, 0xf8, 0x00, 0x00, 0x01, 0x80, 0x0f,
  0xf0, 0x3f, 0x7e, 0x07, 0xf8, 0x00, 0x00, 0x01, 0x80, 0x0f, 0xf0, 0x3f, 0x7e, 0x07, 0xf8, 0x00,
  0x00, 0x01, 0x80, 0x0f, 0xf0, 0x3f, 0x7e, 0x07, 0xf8, 0x00, 0x7f, 0xff, 0x80, 0x0f, 0xf0, 0x3f,
  0x7e, 0x07, 0xf8, 0x00, 0x7f, 0xff, 0x80, 0x0f, 0xf0, 0x3f, 0x7e, 0x07, 0xf8, 0x00, 0x7f, 0xff,
  0x80, 0x0f, 0xf0, 0x3f, 0x7e, 0x07, 0xf8, 0x00, 0x7f, 0xff, 0x80, 0x0f, 0xff, 0xff, 0x7f, 0xff,
  0xf8, 0x00, 0x30, 0x01, 0x80, 0x0f, 0xff, 0xff, 0x0f, 0xff, 0xf8, 0x00, 0x38, 0x01, 0x80, 0x0f,
  0xff, 0xff, 0xef, 0xff, 0xf8, 0x00, 0x18, 0x01, 0x80, 0x0f, 0xff, 0xff, 0xef, 0xff, 0xf8, 0x00,
  0x1c, 0x01, 0x80, 0x0f, 0xff, 0xff, 0xef, 0xff, 0xf8, 0x00, 0x0c, 0x01, 0x80, 0x0f, 0xff, 0xff,
  0x0f, 0xff, 0xf8, 0x00, 0x08, 0x00, 0x00, 0x0f, 0xff, 0xff, 0x7f, 0xff, 0xf8, 0x00, 0x01, 0xe0,
  0x00, 0x0f, 0xff, 0xff, 0x7f, 0xff, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x0f, 0xff, 0xff, 0x7f, 0xff,
  0xf8, 0x00, 0x1f, 0xfe, 0x00, 0x0f, 0xff, 0xff, 0x7f, 0xff, 0xf8, 0x00, 0x3f, 0xff, 0x00, 0x07,
  0xff, 0xff, 0x7f, 0xff, 0xf0, 0x00, 0x3f, 0x9f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x3b, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0xc3, 0x80, 0x00, 0x00, 0x03,
  0xe0, 0x00, 0x00, 0x00, 0x70, 0xc1, 0x80, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x70, 0xe1,
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x71, 0x80, 0x00, 0x00, 0x03, 0xe0, 0x00,
  0x00, 0x00, 0x3c, 0x37, 0x80, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00,
  0x1f, 0xfe, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x03, 0xe0, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x7f, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x7f, 0xff, 0x80, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x7f, 0xff,
  0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x30, 0x01, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x60, 0x38, 0x01, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x18, 0x01, 0x81, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x1c, 0x01, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x0c, 0x01, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x08, 0x00, 0x01, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x60, 0x07, 0xf8, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x0f, 0xfc,
  0x01, 0x9f, 0x83, 0xe1, 0xf0, 0x7c, 0x3e, 0x60, 0x1f, 0xfe, 0x01, 0x9f, 0x83, 0xe1, 0xf0, 0x7c,
  0x3f, 0x60, 0x3f, 0xff, 0x01, 0xbf, 0x83, 0xe1, 0xf0, 0x7c, 0x3f, 0x60, 0x3f, 0x87, 0x81, 0xbf,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x60, 0x3b, 0x83, 0x81, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x60,
  0x71, 0xc3, 0x81, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x60, 0x70, 0xc1, 0x81, 0xbf, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x60, 0x70, 0xe1, 0x81, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x60, 0x30, 0x73,
  0x81, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x60, 0x3c, 0x37, 0x81, 0x8f, 0xff, 0xff, 0xff, 0xff,
  0xfc, 0x60, 0x3f, 0xff, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x1f, 0xff, 0x01, 0xc0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x0f, 0xfe, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0,
  0x03, 0xf8, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};
