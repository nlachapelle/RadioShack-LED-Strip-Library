# RadioShack-LED-Strip-Library
Library for the RadioShack-brand Tricolor LED Strip. This library currently only works on the Arduino Uno (and potentially some of the other 62.5MHz Arduino boards), on pins 2-13.
The library was written using the specifications on the datasheet included with the LED Strip, which can be found through [this link](https://datasheet.octopart.com/2760339-RadioShack-datasheet-21172737.pdf). Waveforms for the '1' and '0' signals were measured experimentally using an oscilloscope, which is why the library is very specific to the Uno and 62.5MHz boards.

If anybody wants to add more support for other boards to the library, please feel free. The only reason I didn't is because building this library was just a step in a larger project involving the LED Strip, so I didn't feel like spending extra time implementing support for each board.

With that said, here are some terms I found useful when searching for information to write this library:
- Pin mapping --> Each board has a diagram showing which port each pin is on, and what its relative port value is (for example, pin 13 on the Uno is actually on Port B, and its relative port value is 5)
- Port manipulation --> Most people use digitalWrite() to control output to pins, but when outputs need to be precisely timed this presents a problem because it uses up a lot of clock cycles to run. Port manipulation is a method of performing digitalWrite() in a way that accesses the hardware more directly, and so less clock cycles are used.
- Interrupts --> The Arduino has three on-board timers that can be used to schedule certain 'interrupt' events. These can be useful at times, but when precisely timed events are being programmed, these need to be disabled so that the timed events are not interrupted while executing; otherwise, the timed events will be messed up.
- Busy loop/busy wait --> This library uses a busy loop for timing the data output to the LED strip. It's fairly straightforward, I'll leave it to you to look up.

## Details
To install the library, save the rsled.cpp and rsled.h files into a folder named 'RSLED' in the Arduino library folder on your computer.

The library is essentially two classes:
1. The RSLED class, which is used to attach the LED Strip to a specific pin
   - The setColors(colors) function takes an array of 10 Color objects
   - The blink() function takes no arguments, and blinks the LEDs one second on, one second off. Use to test if the strip works.
   - The clear() function takes no arguments, and turns off all the LEDs
2. The Color class, which is used to send RGB color values to the RSLED class
   - Can be instantiated like: Color c = {r, g, b}; where r, g, and b are integers from 0-255 representing the red, green, and blue values of the color

Specific code for instantiating these classes can be found in the example_code_for_RSLED.ino file. 
