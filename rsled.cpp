#include "Arduino.h"
#include "rsled.h"

const unsigned char pinMappings[] = {
  0, 1, 2, 3, 4, 5, 6, 7, //PORTD
  0, 1, 2, 3, 4, 5,       //PORTB
};

RSLED::RSLED(int pin) {
  pinMode(pin, OUTPUT);
  pinNum = pin;             //These are the same value, pinNum is just the class attribute
  if (pin >= 2 && pin <= 7) {
    portRegister = &PORTD;  //Pins 2-7 located on PORTD
  }
  if (pin >= 8 && pin <= 13) {
    portRegister = &PORTB;  //Pins 8-13 located on PORTB
  }
}

//Sets the colors for each of the 10 segments of the LED strip
void RSLED::setColors(Color colors[10]) {
  noInterrupts(); //Timing for color data transfer requires too much precision for interrupts to be enabled
  byte colorBytes[30];  //Store each byte for each LEDs RGB values in the same array to minimize time spent accessing them later on
  for (int i = 0; i < 10; i++) {
    //Each 3 indices are the R byte, G byte, and B byte for each LED's color
    colorBytes[3*i] = colors[i].getRed();
    colorBytes[3*i+1] = colors[i].getGreen();
    colorBytes[3*i+2] = colors[i].getBlue();
  }
  for (int j = 0; j < 30; j++) {
    sendByte(colorBytes[j]);
  }
  interrupts(); //Timing-sensitive code is finished, interrupts can be re-enabled
  delayMicroseconds(24);  //24 microsecond low signal resets the LED to display the new color data it just received
}

//Turns off all of the LEDs
void RSLED::clear() {
  noInterrupts();
  for (int i = 0; i < 30; i++) {  //30 bytes / 3 bytes per color = 10 LED segments
    sendByte(B00000000);
  }
  interrupts();
}

//Sends one byte of color data to the LED strip based on the datasheet's method of data transfer
void RSLED::sendByte(byte b) {
  unsigned char pin = pinMappings[pinNum];  //Storing the pin number as a local variable eliminates time spent accessing it
  byte high = (1 << pin);   //Storing the evaluation of these two expressions will also eliminate some access time
  byte low = ~(1 << pin);
  volatile uint8_t* localRegister = portRegister;  //Same reasoning as above ^^^
  for (int i = 7; i >= 0; i--) {  //Bit masking to send individual bits from the byte
    if (b & (1 << i)) {
        //This code is super ugly, but it's the only way I was able to get the correct precision for data transfer to the LED strip
        //Even introducing a for loop messed up the precision
        *localRegister |= high;
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        *localRegister ^= high;
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
    } else {
        *localRegister |= high;
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        *localRegister ^= high;
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
        __asm__("nop \n \t");
     }
  }
}

//Method for testing if the LED strip is working. Blinks lights on and off, one second each
void RSLED::blink() {
  noInterrupts();
  unsigned char pin = pinMappings[pinNum];
  for (int i = 0; i < 30; i++) {
    sendByte(B11111111);
  }
  interrupts();
  delay(1000);
  noInterrupts();
  for (int i = 0; i < 30; i++) {
   sendByte(B00000000);
  }
  interrupts();
  delay(1000);
}

//Color class used to send colors to RSLED class
Color::Color() {
  red = B00000000;
  green = B00000000;
  blue = B00000000;
}

Color::Color(int r, int g, int b) {
  red = (byte) r;
  green = (byte) g;
  blue = (byte) b;
}

byte Color::getRed() {
  return red;
}

byte Color::getGreen() {
  return green;
}

byte Color::getBlue() {
  return blue;
}
