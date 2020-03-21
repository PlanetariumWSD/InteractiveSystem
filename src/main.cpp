/**
 * Notes:
 * Soon (once PlatformIO recognizes v4.5.0 of JLed), we'll be able to write `button[i].led.MaxBrightness(200);`
*/

#include <Arduino.h>
#include <Ethernet.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <CapacitiveSensor.h>
#include <jled.h>

struct Button
{
  CapacitiveSensor sensor;
  JLed led;
  long sensorThreshold = 200;
  Button(uint8_t sensorPin, byte ledPin) : sensor(2, sensorPin), led(ledPin)
  {
    sensor.set_CS_Timeout_Millis(50);
  }
};

Button buttons[5] = {
    Button(A0, 3),
    Button(A1, 5),
    Button(A2, 6),
    Button(A3, 9),
    Button(A4, 10)};

void setup()
{
}

void checkWS()
{
}

void checkButtons()
{
}

void loop()
{
  checkWS();
  checkButtons();

  for (byte i = 0; i < 4; i++)
  {
    buttons[i].led.Update();
  }
}

// ##################################################################################
/* NOTES ===========================================================================
 * Maximum Capacative Buttons each with matching LED to indicate pressed.
 *  IMPORTANT: Bottons not hooked up cause time out problems and severly reduce efficient operation.
 *  Forbidden pins: 0,1 (serial coms), 13 onboard LED
 * 6 LED/buttons max and need PWM pins for dimming LEDs 3,5,6,9,10,11 (Pin 13 is NOT PWM)
 * Pin2 is sensor output pin
 * Button input pins are then.. 4, 7, 8, 12, A0, A1, A2, A3, A4, A5 ...
 * Maybe when/if making a header, all pins should be inline with eachother?
 */
