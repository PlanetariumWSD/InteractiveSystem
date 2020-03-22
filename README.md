# InteractiveSystem-Client
Planetarium Arm Chair Buttons: Users press buttons on Arduino Ethernet boards, which are then sent through HTTP to an Express.js server.

## Usage
1. Set up InteractiveSystem-Server as described in its README.md.
1. Using an IDE with PlatformIO installed, set the server and client variables to their desired values.
1. Use PlatformIO to install this program onto the desired Arduino Ethernet(s). The dependencies will be installed automatically.

## Notes
* Websockets, HTTP POST, and JSON parsing have been tested. LED lighting, and capacitive touch sensors have not.

* IMPORTANT: Buttons not hooked up cause timeout problems and severly reduce efficiency.
* Forbidden pins: 0, 1 (serial coms); 13 (builtin LED)
* 6 LED/buttons max. Each requires PWM pins for dimming LEDs 3, 5, 6, 9, 10, 11 (Pin 13 is NOT PWM)
* Pin 2 is sensor output pin.
* Button input pins are 4, 7, 8, 12, A0, A1, A2, A3, A4, A5...

## Future Improvements
* This program still needs a method to have eeprom data modified by server (e.g. `sensorThreshold`, `maxLedBrightness`, etc)
    * If `maxLedBrightness` is implemented, then the server's brightness value could be a percentage of maxLedBrightness instead of an absolute value
* This program does not have any LED lighting effects--it only employs simple on and off. In a previous commit, I had JLed functions employed, but this used up too much flash and RAM.
* In order to accomodate the above features, more memory efficient alternatives to the Arduino `String` class should be used.
