# InteractiveSystem-Client
Planetarium Arm Chair Buttons: Users press buttons on Arduino Ethernet boards, which are then sent through HTTP to an Express.js server.

## Usage
1. Set up InteractiveSystem-Server as described in its README.md.
1. Using an IDE with PlatformIO installed, set the server and client variables to their desired values.
1. Use PlatformIO to install this program onto the desired Arduino Ethernet(s). The dependencies will be installed automatically.
1. The server will send JSON data to the Arduino through Websockets in the following form:
    ```
    [
        {
            "live": true,
            "brightness": 255
        },
        {
            "live": false,
            "brightness": 0
        },
        {
            "live": true,
            "brightness": 255
        },
        {
            "live": false,
            "brightness": 15
        },
        {
            "live": true,
            "brightness": 100
        }
    ]
    ```
    Each item in the array represents one of the buttons. `live === true` says "send every new button press to the server". `live === false` says "ignore this button". `brightness` is the brightness to set a button to once it has been pressed. All other buttons are set to 0 brightness. (All buttons start at `brightness` brightness before any have been pressed.)
        * Data is sent to the server via an HTTP POST to the endpoint `/states/:seatNum`. The JSON posted is of the following form, where `latestPress` is the ID of the new button that has been pressed: `{ "latestPress": 1}`.

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
* This program does not have any LED lighting effects--it only employs simple on and off. In a previous commit, I had JLed functions employed, but this used up too much flash and RAM. This attempt can be found [here](https://github.com/PlanetariumWSD/InteractiveSystem-Client/commit/8bf9fbcb5a93130a3ccc170112060ffce1fa4a81).
* In order to accomodate the above features, more memory efficient alternatives to the Arduino `String` class should be used.
