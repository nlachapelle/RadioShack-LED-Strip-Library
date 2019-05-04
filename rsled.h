#include "Arduino.h"

class Color {
  public:
    Color();
    Color(int r, int g, int b);
    byte getRed();
    byte getGreen();
    byte getBlue();
  private:
    byte red;
    byte green;
    byte blue;
};


class RSLED {
  public:
    RSLED(int pin);

    int pinNum;
    volatile uint8_t* portRegister;

    void setColors(Color colors[10]);
    void blink();
    void clear();
  private:
    void sendByte(byte b);
};
