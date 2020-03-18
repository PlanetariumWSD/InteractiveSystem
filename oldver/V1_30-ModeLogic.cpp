#include <Arduino.h> //Required for Atom Editor
#include <CapacitiveSensor.h>
// Notes at bottom

// DO NOT USE IN OTHER CODE ===================================
// These values are for function GetButtonStatus DO NOT USE
  CapacitiveSensor   cs0 = CapacitiveSensor(2,A0);
  CapacitiveSensor   cs1 = CapacitiveSensor(2,A1);
  CapacitiveSensor   cs2 = CapacitiveSensor(2,A2);
  CapacitiveSensor   cs3 = CapacitiveSensor(2,A3);
  CapacitiveSensor   cs4 = CapacitiveSensor(2,A4);
  long total[5] = {0, 0, 0, 0, 0};
  byte csMinVal[5] = {200, 200, 200, 200, 200};  // Higher values means you must touch stronger.Default was 50
  bool buttonPress[5] = {0, 0, 0, 0, 0};
  bool buttonToggle[5] = {0, 0, 0, 0, 0};
 // ===========================================================

byte MasterMode = 15;  // Device Master 255 Modes: 0-(all LED off, no sensors) 1-(Freeze Answers ) 2-(True/False 1 of 2) 3-(Choose 1 of 3) 4-(Choose 1 of 4) 5-(Choose 1 of 5)
                      // more...Choose Up tp 5 etc.. (Fast Buzz in ? )12-(Any of 2) 13-(Any of 3) 14-(Any of 4) 15-(Any of 5)
byte buttonMode[5] = {2, 2, 2, 2, 2};            // Button Mode Array 0-Disabled, 1-Interm, 2-ON/OFF
bool buttonStatus[5] = {0, 0, 0, 0, 0};          // Button Status, this is the logical value
byte LEDMaxBright[5] = {45, 255, 30, 100, 100};  // Brightness Values of LEDs,  0-255 Anything over 125 is barely noticable to eye
byte LEDMode[5]= {0, 0, 0, 0, 0};                // LED 255 Modes   (Off, Flash (fast medium slow), Pulse ((fast medium slow) Dim ? More LED arrays? or live with a "reset option" [!! Use % of Max inside functions]

bool debugMode = 1; // Set to zero for no Serial printing and remove from final product.

// ----------------------------------------------------------------------------------
void setup(){
  // Set TimeOut for unresponsive pins in mS Default is 2000 ms
  cs0.set_CS_Timeout_Millis(50);
  cs1.set_CS_Timeout_Millis(50);
  cs2.set_CS_Timeout_Millis(50);
  cs3.set_CS_Timeout_Millis(50);
  cs4.set_CS_Timeout_Millis(50);

  if (debugMode == 1){Serial.begin(9600);} // Remove from final product.

}
// ##################################################################################
// ##################################################################################
// FUNCTIONS =================================

void GetButtonStatus(){
  if (buttonMode[0] > 0 || buttonMode[1] > 0 || buttonMode[2] > 0 || buttonMode[3] > 0 || buttonMode[4] > 0){
      long start = millis(); // This value may not be required except for debug report of performance.
      total[0] =  cs0.capacitiveSensor(30);
      total[1] =  cs1.capacitiveSensor(30);
      total[2] =  cs2.capacitiveSensor(30);
      total[3] =  cs3.capacitiveSensor(30);
      total[4] =  cs4.capacitiveSensor(30);
      for (byte i = 0; i<=4; i++){
        if (total[i] > csMinVal[i] && buttonPress[i] == 0){buttonPress[i] = 1;}
        else if (total[i] < csMinVal[i] && buttonPress[i] == 1){buttonPress[i] = 0;}
        if (buttonMode[i] == 1){
          if (buttonPress[i] == 1){buttonStatus[i] = 1;}
          else if (buttonPress[i] == 0){buttonStatus[i] = 0;}
        }
        if (buttonMode[i] == 2){
          if (buttonPress[i] == 1 && buttonToggle[i] == 0){ buttonToggle[i] = 1; buttonStatus[i] = !buttonStatus[i];}
          else if (buttonPress[i] == 0 && buttonToggle[i] == 1){buttonToggle[i] = 0;}
        }
      }
      if (debugMode == 1) {
        Serial.print(millis() - start);        // check on performance in milliseconds
        Serial.print("\t");                    // tab character for debug window spacing
        Serial.print(total[0]);
        Serial.print("\t");
        Serial.print(total[1]);
        Serial.print("\t");
        Serial.print(total[2]);
        Serial.print("\t");
        Serial.print(total[3]);
        Serial.print("\t");
        Serial.print(total[4]);
        Serial.print("\t");
        Serial.println();
      }
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
void loop(){// ##################################################################################
  GetButtonStatus();
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
