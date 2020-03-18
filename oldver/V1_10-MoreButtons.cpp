#include <Arduino.h> //Required for Atom Editor
#include <CapacitiveSensor.h>

/* Maximum Capacative Buttons each with matching LED to indicate pressed.
 *  IMPORTANT: Bottons not hooked up cause time out problems and severly reduce efficient operation.
 *  Forbidden pins: 0,1 (serial coms), 13 onboard LED
 * 6 (7 ?) LEDs max and need PWM pins for dimming LEDs 3,5,6,9,10,11 (? is Pin 13 PWM?)
 * Pin2 is sensor output pin
 * Button input pins are then.. 4, 7, 8, 12, A0, A1
 */
CapacitiveSensor   cs1 = CapacitiveSensor(2,A0);
//CapacitiveSensor   cs2 = CapacitiveSensor(2,A1);
//CapacitiveSensor   cs3 = CapacitiveSensor(2,A2);
//CapacitiveSensor   cs4 = CapacitiveSensor(2,A3);
//CapacitiveSensor   cs5 = CapacitiveSensor(2,A4);
//CapacitiveSensor   cs6 = CapacitiveSensor(2,A5);

byte cs1MinVal = 200; // Higher values means you must touch stronger.
//byte cs2MinVal = 50;
//byte cs3MinVal = 50;
//byte cs4MinVal = 50;
//byte cs5MinVal = 50;
//byte cs6MinVal = 50;

byte LEDMax = 64;

void setup()
{
 /* These are no needed and are from example only.
  //cs1.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 1 - just as an example
  //cs2.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 2 - just as an example
  //cs3.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 3 - just as an example
  //cs4.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 4 - just as an example
  //cs5.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 5 - just as an example
  //cs6.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 6 - just as an example
*/                                              // Default of 20 seconds or 200000 ms

  // Set Time out for unresponsive pins in mS Defualt is 2000 ms
  cs1.set_CS_Timeout_Millis(50);
  //cs2.set_CS_Timeout_Millis(50);
  //cs3.set_CS_Timeout_Millis(50);
  //cs4.set_CS_Timeout_Millis(50);
  //cs5.set_CS_Timeout_Millis(50);
  //cs6.set_CS_Timeout_Millis(50);

  Serial.begin(9600);
}

void loop()
{
  long start = millis();
  long total1 =  cs1.capacitiveSensor(30);
  //long total2 =  cs2.capacitiveSensor(30);
  //long total3 =  cs3.capacitiveSensor(30);
  //long total4 =  cs4.capacitiveSensor(30);
  //long total5 =  cs5.capacitiveSensor(30);
  //long total6 =  cs6.capacitiveSensor(30);

  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug window spacing

  Serial.print(total1);
  Serial.print("\t");
  //Serial.print(total2);
  //Serial.print("\t");
  //Serial.print(total3);
  //Serial.print("\t");
  //Serial.print(total4);
  //Serial.print("\t");
  //Serial.print(total5);
  //Serial.print("\t");
  //Serial.print(total6);
  Serial.println();
  //delay(10);                             // arbitrary delay to limit data to serial port

  if (total1 > cs1MinVal){
  analogWrite(3, LEDMax);
  }
  if (total1 < cs1MinVal){
  analogWrite(3, 0);
  }

}
