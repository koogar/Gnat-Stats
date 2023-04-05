
void splashScreenA () {

  display.drawBitmap(0, 0, GnatBmp, 128, 64, WHITE);
  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();

  //looks cool... wastes a lot of memory
  display.drawBitmap(0, 0, WaitingDataBMP, 128, 64, WHITE);
  display.display();

  display.clearDisplay();
  //display.display();//note... not needed "main loop" will initiate this, when serial coms establish

  pixels.setPixelColor(0, RED);
  pixels.show(); // This sends the updated pixel color to the hardware

}

void splashScreenB () {
  
  display.drawBitmap(0, 0, JustTheGnatBMP, 64, 64, WHITE);
  display.setTextSize(3);
  display.setCursor(58, 5);
  display.println("GNAT-");
  display.setTextSize(2);
  display.setCursor(64, 30);
  display.println("STATS");
  display.setTextSize(1);
  display.setCursor(80, 55);
  display.println("Ver:1.0");
  display.display();

  delay(3000);
  display.clearDisplay();
  display.display();
  //inverter(); // inverted splashscreen image
  //looks cool... wastes a lot of memory
  display.drawBitmap(0, 0, WaitingDataBMP, 128, 64, WHITE);
  display.display();
  display.clearDisplay();
  //display.display();//note... not needed "main loop" will initiate this, when serial coms establish

  pixels.setPixelColor(0, RED);
  pixels.show(); // This sends the updated pixel color to the hardware

}

void splashScreenC () {

  display.drawBitmap(0, 0, GnatBmp, 128, 64, WHITE);
  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();

  //inverter(); // inverted splashscreen image
  display.setTextSize(3); //set background txt font size
  display.setCursor(1, 1);
  display.println(">");
  display.display();
  display.setTextSize(2);
  display.setCursor(20, 30);
  display.display();
  display.println("0101010..");
  display.display();
  display.setTextSize(1);
  display.setCursor(1, 54);
  display.println("waiting for data.....");
  
  display.display(); 
  display.clearDisplay();
  //display.display(); //note... not needed "main loop" will initiate this, when serial coms establish


  pixels.setPixelColor(0, RED);
  pixels.show(); // This sends the updated pixel color to the hardware

}

void splashScreenD () {


  //inverter(); // inverted splashscreen image

  display.drawBitmap(0, 0, JustTheGnatBMP, 64, 64, WHITE);
  display.setTextSize(3);
  display.setCursor(58, 5);
  display.println("GNAT-");
  display.setTextSize(2);
  display.setCursor(64, 30);
  display.println("STATS");
  display.setTextSize(1);
  display.setCursor(80, 55);
  display.println("Ver:1.0");
  display.display();

  delay(3000);
  
  display.display();
  display.clearDisplay();

  //inverter(); // inverted splashscreen image
  display.setTextSize(3); //set background txt font size
  display.setCursor(1, 1);
  display.println(">");
  display.display();
  display.setTextSize(2);
  display.setCursor(20, 30);
  display.display();
  display.println("0101010..");
  display.display();
  display.setTextSize(1);
  display.setCursor(1, 54);
  display.println("waiting for data.....");
  display.display();
  display.clearDisplay();
  //display.display(); //note... not needed "main loop" will initiate this, when serial coms establish


  pixels.setPixelColor(0, RED);
  pixels.show(); // This sends the updated pixel color to the hardware

}





//--------------------------------------------------------------------------------------------------------


void splashScreen2() {
  display.drawBitmap(0, 0, GnatBmp, 128, 64, WHITE);
  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();
}
