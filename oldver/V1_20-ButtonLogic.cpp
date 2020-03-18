#include <Arduino.h> //Required for Atom Editor
#include <CapacitiveSensor.h>

/* Maximum Capacative Buttons each with matching LED to indicate pressed.
 *  IMPORTANT: Bottons not hooked up cause time out problems and severly reduce efficient operation.
 *  Forbidden pins: 0,1 (serial coms), 13 onboard LED
 * 6 LEDs max and need PWM pins for dimming LEDs 3,5,6,9,10,11 (Pin 13 is NOT PWM)
 * Pin2 is sensor output pin
 * Button input pins are then.. 4, 7, 8, 12, A0, A1
 */
CapacitiveSensor   cs1 = CapacitiveSensor(2,A0);
CapacitiveSensor   cs2 = CapacitiveSensor(2,A1);
CapacitiveSensor   cs3 = CapacitiveSensor(2,A2);
CapacitiveSensor   cs4 = CapacitiveSensor(2,A3);
CapacitiveSensor   cs5 = CapacitiveSensor(2,A4);
CapacitiveSensor   cs6 = CapacitiveSensor(2,A5);

long start = millis();
long total1 = 0;
long total2 = 0;
long total3 = 0;
long total4 = 0;
long total5 = 0;

byte cs1MinVal = 200; // Higher values means you must touch stronger.Default was 50
byte cs2MinVal = 200;
byte cs3MinVal = 200;
byte cs4MinVal = 200;
byte cs5MinVal = 200;
byte cs6MinVal = 200;

byte LED1Max = 75; // 0-255 Anything over 125 is barely noticable to eye
byte LED2Max = 255;
byte LED3Max = 255;
byte LED4Max = 255;
byte LED5Max = 255;

bool buttonStatus1= 0;
bool buttonPress1= 0;
bool buttonStatus2= 0;
bool buttonPress2= 0;
bool buttonStatus3= 0;
bool buttonPress3= 0;
bool buttonStatus4= 0;
bool buttonPress4= 0;
bool buttonStatus5= 0;
bool buttonPress5= 0;


void setup(){
 /* These are no needed and are from example only.
  //cs1.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 1 - just as an example
  //cs2.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 2 - just as an example
  //cs3.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 3 - just as an example
  //cs4.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 4 - just as an example
  //cs5.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 5 - just as an example
  //cs6.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 6 - just as an example
*/                                              // Default of 20 seconds or 200000 ms

  // Set Time out for unresponsive pins in mS Default is 2000 ms
  cs1.set_CS_Timeout_Millis(50);
  cs2.set_CS_Timeout_Millis(50);
  cs3.set_CS_Timeout_Millis(50);
  cs4.set_CS_Timeout_Millis(50);
  cs5.set_CS_Timeout_Millis(50);
  cs6.set_CS_Timeout_Millis(50);
   Serial.begin(9600);
}





// MODE FUNCTIONS =================================

void GetButtonStatus()
{
  if (total1 > cs1MinVal && buttonPress1 == 0){
    buttonPress1 = 1;
  }
  else if (total1 < cs1MinVal && buttonPress1 == 1){
    buttonPress1 = 0;
  }
if (total2 > cs2MinVal && buttonPress2 == 0){
    buttonPress2 = 1;
  }
  else if (total2 < cs2MinVal && buttonPress2 == 1){
    buttonPress2 = 0;
  }

}



void SingleChoice(){
  if (total1 > cs1MinVal && buttonPress1 == 0){
    buttonPress1 = 1;
    buttonStatus1 = !buttonStatus1;
  }
  else if (total1 < cs1MinVal && buttonPress1 == 1){
    buttonPress1 = 0;
  }
  if (total2 > cs2MinVal && buttonPress2 == 0){
    buttonPress2 = 1;
    buttonStatus2 = !buttonStatus2;
  }
  else if (total2 < cs2MinVal && buttonPress2 == 1){
    buttonPress2 = 0;
  }
  if (total3 > cs3MinVal && buttonPress3 == 0){
    buttonPress3 = 1;
    buttonStatus3 = !buttonStatus3;
  }
  else if (total3 < cs3MinVal && buttonPress3 == 1){
    buttonPress3 = 0;
  }
    if (total4 > cs4MinVal && buttonPress4 == 0){
    buttonPress4 = 1;
    buttonStatus4 = !buttonStatus4;
  }
  else if (total4 < cs4MinVal && buttonPress4 == 1){
    buttonPress4 = 0;
  }
    if (total5 > cs5MinVal && buttonPress5 == 0){
    buttonPress5 = 1;
    buttonStatus5 = !buttonStatus5;
  }
  else if (total5 < cs5MinVal && buttonPress5 == 1){
    buttonPress5 = 0;
  }

}

void MultipleChoice(){
  if (buttonStatus1 == 1 && buttonPress1 == 0 ){
    buttonPress1 = 1;
    buttonStatus1 = !buttonStatus1;
  }
  if (buttonStatus1 == 0 && buttonPress1 == 1 ){
    buttonPress1 = 0;
  }
}

void GetSensorData(){
  start = millis();
  total1 =  cs1.capacitiveSensor(30);
  total2 =  cs2.capacitiveSensor(30);
  total3 =  cs3.capacitiveSensor(30);
  total4 =  cs4.capacitiveSensor(30);
  total5 =  cs5.capacitiveSensor(30);
  total6 =  cs6.capacitiveSensor(30);
}

void UpdateLEDS(){
  if (buttonStatus1 == 1){analogWrite(3, LED1Max); }
  if (buttonStatus1 == 0){analogWrite(3, 0);  }
  if (buttonStatus2 == 1){analogWrite(5, LED2Max); }
  if (buttonStatus2 == 0){analogWrite(5, 0);  }
  if (buttonStatus3 == 1){analogWrite(6, LED3Max); }
  if (buttonStatus3 == 0){analogWrite(6, 0);  }
  if (buttonStatus4 == 1){analogWrite(9, LED4Max); }
  if (buttonStatus4 == 0){analogWrite(9, 0);  }
  if (buttonStatus5 == 1){analogWrite(10, LED5Max); }
  if (buttonStatus5 == 0){analogWrite(10, 0);  }
}

void DebugSerial(){
  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug window spacing
  Serial.print(total1);
  Serial.print("\t");
  Serial.print(total2);
  Serial.print("\t");
  Serial.print(total3);
  Serial.print("\t");
  Serial.print(total4);
  Serial.print("\t");
  Serial.print(total5);
  Serial.print("\t");
  Serial.print(total6);
  Serial.println();
  //delay(10);                             // arbitrary delay to limit data to serial port
}

void loop(){
  GetSensorData();
  SingleChoice();
  UpdateLEDS();
  DebugSerial();

  delay(10);
}
