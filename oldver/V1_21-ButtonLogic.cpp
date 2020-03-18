#include <Arduino.h> //Required for Atom Editor
#include <CapacitiveSensor.h>
// Notes at bottom

CapacitiveSensor   cs0 = CapacitiveSensor(2,A0);
CapacitiveSensor   cs1 = CapacitiveSensor(2,A1);
CapacitiveSensor   cs2 = CapacitiveSensor(2,A2);
CapacitiveSensor   cs3 = CapacitiveSensor(2,A3);
CapacitiveSensor   cs4 = CapacitiveSensor(2,A4);

// Brightness Values of LEDs,  0-255 Anything over 125 is barely noticable to eye
byte LEDMaxBright[5] = {45, 255, 30, 100, 100};
byte LEDMode[5]= {0, 0, 0, 0, 0};         //LED More Array  (Off, Flash (fast medium slow), Pulse ((fast medium slow) Dim ? More LED arrays? or live with a "reset option"
byte buttonMode[5] = {0, 0, 0, 0, 0};     //Button Mode Array Interm, ON/OFF, OFF
bool buttonStatus[5] = {0, 0, 0, 0, 0};   // Button Status Array Bool

//bool buttonStatus0= 0;
bool buttonPress0= 0;
//bool buttonStatus1= 0;
bool buttonPress1= 0;
bool buttonToggle1 = 0;
//bool buttonStatus2= 0;
bool buttonPress2= 0;
//bool buttonStatus3= 0;
bool buttonPress3= 0;
//bool buttonStatus4= 0;
bool buttonPress4= 0;


bool debugMode = 1; // Set to zero for no Serial printing.

void setup(){
  // Set TimeOut for unresponsive pins in mS Default is 2000 ms
  cs0.set_CS_Timeout_Millis(50);
  cs1.set_CS_Timeout_Millis(50);
  cs2.set_CS_Timeout_Millis(50);
  cs3.set_CS_Timeout_Millis(50);
  cs4.set_CS_Timeout_Millis(50);

  if (debugMode == 1){Serial.begin(9600);}
}

// ##################################################################################
// ##################################################################################
// FUNCTIONS =================================

void MultipleChoice(){
  if (buttonStatus[0] == 1 && buttonStatus[0] == 0){
    buttonPress1 = 0;
    buttonStatus[0] = !buttonStatus[0];
    }
  }

/*
void SingleChoice(){
  if (total1 > csMinVal1 && buttonPress1 == 0){
    buttonPress1 = 1;
    buttonStatus1 = !buttonStatus1;
  }
  else if (total1 < csMinVal1 && buttonPress1 == 1){
    buttonPress1 = 0;
  }
  if (total2 > csMinVal2 && buttonPress2 == 0){
    buttonPress2 = 1;
    buttonStatus2 = !buttonStatus2;
  }
  else if (total2 < csMinVal2 && buttonPress2 == 1){
    buttonPress2 = 0;
  }
  if (total3 > csMinVal3 && buttonPress3 == 0){
    buttonPress3 = 1;
    buttonStatus3 = !buttonStatus3;
  }
  else if (total3 < csMinVal3 && buttonPress3 == 1){
    buttonPress3 = 0;
  }
    if (total4 > csMinVal4 && buttonPress4 == 0){
    buttonPress4 = 1;
    buttonStatus4 = !buttonStatus4;
  }
  else if (total4 < csMinVal4 && buttonPress4 == 1){
    buttonPress4 = 0;
  }
    if (total5 > csMinVal5 && buttonPress5 == 0){
    buttonPress5 = 1;
    buttonStatus5 = !buttonStatus5;
  }
  else if (total5 < csMinVal5 && buttonPress5 == 1){
    buttonPress5 = 0;
  }

}
*/
void TouchTest(){
  if (buttonPress0 == 1){buttonStatus[0] = 1;}
  if (buttonPress1 == 1){buttonStatus[1] = 1;}
  if (buttonPress2 == 1){buttonStatus[2] = 1;}
  if (buttonPress3 == 1){buttonStatus[3] = 1;}
  if (buttonPress4 == 1){buttonStatus[4] = 1;}

}

void GetButtonStatus(){
  byte csMinVal0 = 200; // Higher values means you must touch stronger.Default was 50
  byte csMinVal1 = 200;
  byte csMinVal2 = 200;
  byte csMinVal3 = 200;
  byte csMinVal4 = 200;
  long start = millis();
  long total0 =  cs0.capacitiveSensor(30);
  long total1 =  cs1.capacitiveSensor(30);
  long total2 =  cs2.capacitiveSensor(30);
  long total3 =  cs3.capacitiveSensor(30);
  long total4 =  cs4.capacitiveSensor(30);
  if (total0 > csMinVal0 && buttonPress0 == 0){buttonPress0 = 1;}
    else if (total0 < csMinVal0 && buttonPress0 == 1){buttonPress0 = 0;}
  if (total1 > csMinVal1 && buttonPress1 == 0){buttonPress1 = 1;}
    else if (total1 < csMinVal1 && buttonPress1 == 1){buttonPress1 = 0;}
  if (total2 > csMinVal2 && buttonPress2 == 0){buttonPress2 = 1;}
    else if (total2 < csMinVal2 && buttonPress2 == 1){buttonPress2 = 0;}
  if (total3 > csMinVal3 && buttonPress3 == 0){buttonPress3 = 1;}
    else if (total3 < csMinVal3 && buttonPress3 == 1){buttonPress3 = 0;}
  if (total4 > csMinVal4 && buttonPress4 == 0){buttonPress4 = 1;}
    else if (total4 < csMinVal4 && buttonPress4 == 1){buttonPress4 = 0;}

if (debugMode == 1) {
  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug window spacing
  Serial.print(total0);
  Serial.print("\t");
  Serial.print(total1);
  Serial.print("\t");
  Serial.print(total2);
  Serial.print("\t");
  Serial.print(total3);
  Serial.print("\t");
  Serial.print(total4);
  Serial.print("\t");
  Serial.println();
 }

}

void UpdateLEDS(){
  if (buttonStatus[0] == 1){analogWrite(3,LEDMaxBright[0]);}
  if (buttonStatus[0] == 0){analogWrite(3, 0);}
  if (buttonStatus[1] == 1){analogWrite(5, LEDMaxBright[1]);}
  if (buttonStatus[1] == 0){analogWrite(5, 0);}
  if (buttonStatus[2] == 1){analogWrite(6, LEDMaxBright[2]);}
  if (buttonStatus[2] == 0){analogWrite(6, 0);}
  if (buttonStatus[3] == 1){analogWrite(9, LEDMaxBright[3]);}
  if (buttonStatus[3] == 0){analogWrite(9, 0);}
  if (buttonStatus[4] == 1){analogWrite(10, LEDMaxBright[4]);}
  if (buttonStatus[4] == 0){analogWrite(10, 0);}

}

// ##################################################################################
// ##################################################################################
void loop(){ // ##################################################################################
  GetButtonStatus();
  TouchTest();
  //MultipleChoice();
  //SingleChoice();
  UpdateLEDS();
} // ##################################################################################

// NOTES ===========================================================================
/* Maximum Capacative Buttons each with matching LED to indicate pressed.
 *  IMPORTANT: Bottons not hooked up cause time out problems and severly reduce efficient operation.
 *  Forbidden pins: 0,1 (serial coms), 13 onboard LED
 * 6 LED/buttons max and need PWM pins for dimming LEDs 3,5,6,9,10,11 (Pin 13 is NOT PWM)
 * Pin2 is sensor output pin
 * Button input pins are then.. 4, 7, 8, 12, A0, A1, A2, A3, A4, A5 ...
 * Maybe when/if making a header, all pins should be inline with eachother?
 */
