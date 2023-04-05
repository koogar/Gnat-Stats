

void buttonMode () {
  //Handle input
  int switchVal = digitalRead(switchPin);


  if (switchVal == LOW)
  {
    delay(500);
    counter ++;
    //Reset count if over max mode number
    if (counter == 3)
    {
      counter = 0;
    }
  }

  else
    //Change mode
    switch (counter) {

      default:
        DisplayStyle1 ();
        pixels.setPixelColor(0, BLACK);
        pixels.show(); // This sends the updated pixel color to the hardware


      case 0:
        DisplayStyle1 ();
        pixels.setPixelColor(0, RED);
        pixels.show(); // This sends the updated pixel color to the hardware

        break;
      case 1:
        DisplayStyle2 ();
        pixels.setPixelColor(0, GREEN);
        pixels.show(); // This sends the updated pixel color to the hardware
        break;

      case 2:
        DisplayStyle3 ();
        pixels.setPixelColor(0, BLUE);
        pixels.show(); // This sends the updated pixel color to the hardware
        break;




    }
}
