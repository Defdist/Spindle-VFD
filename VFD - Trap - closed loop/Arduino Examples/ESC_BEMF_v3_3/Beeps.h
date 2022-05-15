void beep_1KHZ (int milliseconds)
{
  int x = 0;
  PORTD = B00001000;      //Set D2 (CL) to HIGH and the rest to LOW
  while (x < milliseconds)
  { 
    PORTB = B00000010;      //Set D90 (AH) to HIGH (BH) to LOW
    delayMicroseconds(50);
    PORTB = B00000000;      //Set D90 (AH) to HIGH (BH) to LOW
    delayMicroseconds(450);
    
    PORTB = B00000100;      //Set D10 (BH) to HIGH (AH) to LOW 
    delayMicroseconds(50);
    PORTB = B00000000;      //Set D10 (BH) to HIGH (AH) to LOW 
    delayMicroseconds(450);
    x = x + 1;
  }
   PORTD = B00000000;      //Set D2 (CL) to HIGH and the rest to LOW
   PORTB = B00000000;      //Set D10 (BH) to HIGH (AH) to LOW 
}


void beep_2KHZ (int milliseconds)
{
  int x = 0;
  PORTD = B00001000;      //Set D2 (CL) to HIGH and the rest to LOW
  while (x < milliseconds)
  { 
    PORTB = B00000010;      //Set D90 (AH) to HIGH (BH) to LOW
    delayMicroseconds(50);
    PORTB = B00000000;      //Set D90 (AH) to HIGH (BH) to LOW
    delayMicroseconds(200);
    
    PORTB = B00000100;      //Set D10 (BH) to HIGH (AH) to LOW 
    delayMicroseconds(50);
    PORTB = B00000000;      //Set D10 (BH) to HIGH (AH) to LOW 
    delayMicroseconds(200);

    PORTB = B00000010;      //Set D90 (AH) to HIGH (BH) to LOW
    delayMicroseconds(50);
    PORTB = B00000000;      //Set D90 (AH) to HIGH (BH) to LOW
    delayMicroseconds(200);
    
    PORTB = B00000100;      //Set D10 (BH) to HIGH (AH) to LOW 
    delayMicroseconds(50);
    PORTB = B00000000;      //Set D10 (BH) to HIGH (AH) to LOW 
    delayMicroseconds(200);
    x = x + 1;
  }
   PORTD = B00000000;      //Set D2 (CL) to HIGH and the rest to LOW
   PORTB = B00000000;      //Set D10 (BH) to HIGH (AH) to LOW 
}


void beep_3KHZ (int milliseconds)
{
  int x = 0;
  PORTD = B00001000;      //Set D2 (CL) to HIGH and the rest to LOW
  while (x < milliseconds)
  { 
    PORTB = B00000010;      //Set D90 (AH) to HIGH (BH) to LOW
    delayMicroseconds(50);
    PORTB = B00000000;      //Set D90 (AH) to HIGH (BH) to LOW
    delayMicroseconds(150);

    PORTB = B00000010;      //Set D90 (AH) to HIGH (BH) to LOW
    delayMicroseconds(50);
    PORTB = B00000000;      //Set D90 (AH) to HIGH (BH) to LOW
    delayMicroseconds(150);

    PORTB = B00000010;      //Set D90 (AH) to HIGH (BH) to LOW
    delayMicroseconds(50);
    PORTB = B00000000;      //Set D90 (AH) to HIGH (BH) to LOW
    delayMicroseconds(150);

    PORTB = B00000010;      //Set D90 (AH) to HIGH (BH) to LOW
    delayMicroseconds(50);
    PORTB = B00000000;      //Set D90 (AH) to HIGH (BH) to LOW
    delayMicroseconds(150);

    PORTB = B00000010;      //Set D90 (AH) to HIGH (BH) to LOW
    delayMicroseconds(50);
    PORTB = B00000000;      //Set D90 (AH) to HIGH (BH) to LOW
    delayMicroseconds(150);
    x = x + 1;
  }
   PORTD = B00000000;      //Set D2 (CL) to HIGH and the rest to LOW
   PORTB = B00000000;      //Set D10 (BH) to HIGH (AH) to LOW 
}
