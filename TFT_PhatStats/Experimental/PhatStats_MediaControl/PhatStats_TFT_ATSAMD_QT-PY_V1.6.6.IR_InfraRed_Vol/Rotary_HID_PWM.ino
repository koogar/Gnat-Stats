 
 /*Encoder HID Volume Function*/
 
void rotaryInterrupt()
{
  int rotaryState;

  // Read rotary state (Counter clockwise) -3, -2, -1, 0, 1, 2, 3 (Clockwise)
  rotaryState = rotary.read();

  if (rotaryState > 0)  {

    //Do Something Here
Consumer.write(MEDIA_VOLUME_DOWN);

  } else {

    if (rotaryState < 0)  {

      //Do Something Here
Consumer.write(MEDIA_VOLUME_UP);
    }
  }
}

 /*Encoder PWM Function */
 
//https://electropeak.com/learn/rotary-encoder-how-it-works-how-to-use-with-arduino/

#ifdef Encoder_PWM
/* Screen 3.3v PWM No Transistor, Rotary Encoder*/
void PWM_Encoder () {

  State = digitalRead(encoderOutA);
  if (State != old_State)
  {
    if (digitalRead(encoderOutB) != State)
    {
    
      TFT_brightness --;  TFT_brightness --; TFT_brightness --;
      PWM_Percent_Scale --; PWM_Percent_Scale --; PWM_Percent_Scale --;
    }
    else {
            
      TFT_brightness ++; TFT_brightness ++; TFT_brightness ++;
      PWM_Percent_Scale ++; PWM_Percent_Scale ++; PWM_Percent_Scale ++;
    }

    if (TFT_brightness >= 100)       TFT_brightness = 100 ;
    if (TFT_brightness <= 1)         TFT_brightness =   1 ;

    /* Scale in human 0-100%*/
    if (PWM_Percent_Scale >= 100) PWM_Percent_Scale = 100;
    if (PWM_Percent_Scale <= 1)   PWM_Percent_Scale =   1;


    tft.setFont(&Org_01);
    //tft.setTextColor(ILI9341_WHITE);
    tft.fillRoundRect  (105, 55, 94, 30, 4, ILI9341_RED); // print brightness % over CPU Freq
    tft.drawRoundRect  (105, 55, 94, 30, 4, ILI9341_WHITE);  // print brightness % over CPU Freq


    tft.setCursor(114, 66);
    tft.setTextSize(1);
    tft.print("Back- ");
    tft.setTextSize(1);
    tft.setCursor(114, 75);
    tft.print("Light");

    tft.setCursor(144, 74);
    tft.setTextSize(3);
    tft.print(PWM_Percent_Scale); // Print Scale in human 0-100%
    tft.setTextSize(2);
    tft.println("%");

#ifdef Debug
    /* Debug PWM*/
    tft.setFont(); // default font
    tft.fillRoundRect  (105, 25, 94, 21, 4, ILI9341_RED);   // print brightness  over CPU temp
    tft.drawRoundRect  (105, 25, 94, 21, 4, ILI9341_WHITE);    // print brightness  over CPU temp

    tft.setCursor(114, 36);
    tft.setTextSize(1);
    tft.print("Value  ");
    tft.setCursor(114, 28);
    tft.setTextSize(1);
    tft.print("PWM   ");
    tft.setTextSize(2);
    tft.println(TFT_brightness);
#endif

  }
  old_State = State; // the first position was changed

  analogWrite(TFT_backlight_PIN , TFT_brightness  );
}
#endif
