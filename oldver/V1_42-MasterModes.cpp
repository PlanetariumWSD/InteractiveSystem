#include <Arduino.h> //Required for Atom Editor
#include <CapacitiveSensor.h>
/* INTERACTIVE SYSTEM FOR ARM RESTS IN PLANETARIUM INTRO
===========================================================
Hardware API for Server Control ========================

**Chair/Device should send to server (when changes are made)
# bool buttonStatus[5] = {0, 0, 0, 0, 0};  The only information we want to hear back from the chairs is button's status.

**Server modifies these variables for routine control:
# byte masterMode = 255;  One Byte to each chair sets device in any of 255 modes of operation. (See below for mode description for each.)
# byte LEDDim[5] =  {100, 100, 100, 100, 100}; Any of the modes can be dimmed on the fly.

** Server modifies these variables and stores them into EEPROM.
# byte LEDMaxBright[5] = {45, 255, 30, 100, 100};  Master Max Brightness Values of individual LEDs to balance them out,  0-255 Anything over 125 is barely noticable to eye
# Network Specific information, IP address, Socket, Server IP etc...; This will be set on first boot remotely and/or repaired/replacement unit must be installed.
i.e. All flashed with generic firmware, no need to USB flash each one with unique network info.
*/
// ===========================================================
// ===========================================================
// HARDWARE VARIABLES; DO NOT USE THIS SECTION IN OTHER CODE ===================================
// These values are for function GetButtonStatus DO NOT USE OR CHANGE
// ===========================================================
  CapacitiveSensor   cs0 = CapacitiveSensor(2,A0);
  CapacitiveSensor   cs1 = CapacitiveSensor(2,A1);
  CapacitiveSensor   cs2 = CapacitiveSensor(2,A2);
  CapacitiveSensor   cs3 = CapacitiveSensor(2,A3);
  CapacitiveSensor   cs4 = CapacitiveSensor(2,A4);
  long total[5] = {0, 0, 0, 0, 0};
  byte csMinVal[5] = {200, 200, 200, 200, 200};  // Higher values means you must touch stronger.Default was 50
  bool buttonPress[5] = {0, 0, 0, 0, 0};
  bool buttonToggle[5] = {0, 0, 0, 0, 0};
  byte LEDOutputPin[5]= {3, 5, 6, 9, 10};          // Digital PWM Output Pin
  byte LEDMaxBright[5] = {45, 255, 30, 100, 100};  // Master Max Brightness Values of individual LEDs to balance them out,  0-255 Anything over 125 is barely noticable to eye
  unsigned long LEDperiod[5] =  {0, 0, 0, 0, 0};   // Length of LED effect.
  unsigned long LEDNextUpdate[5] = {0, 0, 0, 0, 0};// Time of the next future LED change.
  byte LEDCurValue[5] = {0, 0, 0, 0, 0};  // 0-255 PWM current value of the LED pin output
  byte LEDCurBright[5] = {0, 0, 0, 0, 0}; // Current MAX allowed Brightness.
// ===========================================================
// ===========================================================
// LOGIC VARIABLES; USE THESE IN COMMAND LOGIC FUNCTIONING
  bool buttonStatus[5] = {0, 0, 0, 0, 0}; // READ ONLY! Button Status returned from hardware, this is the logical value.

  byte masterMode = 255; // Device Master Modes: 0-(all LED off, no sensors) 1-(Freeze Answers ) 2-(True/False 1 of 2) 3-(Choose 1 of 3) 4-(Choose 1 of 4) 5-(Choose 1 of 5)
                        // more...Choose Up tp 5 etc.. (Fast Buzz in ? )12-(Any of 2) 13-(Any of 3) 14-(Any of 4) 15-(Any of 5)
                        // 255-(TEST ALL buttons and LEDs)

  bool masterModeSetupToggle = 0;  // allows setup parameters to run only once in a new master mode.
  byte previousMasterMode = 0;

  byte buttonMode[5] = {0, 0, 0, 0, 0};   // Button Mode Array 0-Disabled, 1-Interm, 2-ON/OFF 3-Inverted ON/OFF?
  bool LEDState[5] = {0, 0, 0, 0, 0};  // LED light effect on or off?
  byte LEDMode[5]= {0, 0, 0, 0, 0};  // LED Effects Modes (0- Off, 1- Solid, 20-29 Flash (fast medium slow), 30-39 Pulse ((fast medium slow) Dim ? More LED arrays? or live with a "reset option" [!! Use % of Max inside functions]

  byte LEDDim[5] =  {100, 100, 100, 100, 100};     // % of Allowable Bright LED is currently at. Used for dimmed modes.
// !!!! VERY LOW #s ON 0, 3 ARE BROKEN  {3, 1, 4, 1, 1};
// BETTER, have a function, Called that uses a single value LEDDIM (%) to calcluate and populate LEDCurBright for each LED. A reset (or function call to 100%) option to put back to LEDMaxBright.
// Could be a diferential table lookup/replace or calulations.
// ----------------------------------------------------------------------------------
void setup(){
  // Set TimeOut for unresponsive pins in mS Default is 2000 ms
  cs0.set_CS_Timeout_Millis(50);
  cs1.set_CS_Timeout_Millis(50);
  cs2.set_CS_Timeout_Millis(50);
  cs3.set_CS_Timeout_Millis(50);
  cs4.set_CS_Timeout_Millis(50);
  // Sets the current LED Brightness to Max hardware values.
  for (byte i = 0; i <= 4; i++){LEDCurBright[i] = LEDMaxBright[i];}
}
// ##################################################################################
// FUNCTIONS =================================
// ##################################################################################
void Command(){
  // ======== MASTER MODE 0 - STANDBY =========
  if (masterMode == 0){
    // Setup the new MODE one time
    if (previousMasterMode != 0) {
      masterModeSetupToggle = 0;
      previousMasterMode = 0;
    }
    if (masterModeSetupToggle == 0){
      // Setup stuff here
      masterModeSetupToggle = 1;
    }
    // MODE LOGIC
    for (byte i = 0; i<=4; i++){
      if (buttonMode [i] != 0){(buttonMode [i] = 0);}
      if (LEDMode [i] != 0){(LEDMode [i] = 0);}
      if (LEDState [i] != 0){(LEDState [i] = 0);}
    }
  }// ==========================================================

  // ======== MASTER MODE 1 - FREEZE Button Status and Lights (can't be changed anymore) =========
  if (masterMode == 1){
    // Setup the new MODE one time
    if (previousMasterMode != 1) {
      masterModeSetupToggle = 0;
      previousMasterMode = 1;
    }
    if (masterModeSetupToggle == 0){
      // Setup stuff here
      masterModeSetupToggle = 1;
    }
    // MODE LOGIC
    for (byte i = 0; i<=4; i++){
      if (buttonMode [i] != 0){(buttonMode [i] = 0);}
    }
  }// ==========================================================

  // ======== MASTER MODE 2 - (True/False 1 of 2 choices)  =========
  if (masterMode == 2){
    // Setup the new MODE one time
    if (previousMasterMode != 2) {
      masterModeSetupToggle = 0;
      previousMasterMode = 2;
    }
    if (masterModeSetupToggle == 0){
      // Setup stuff here
      if (buttonMode [0] != 0){(buttonMode [0] = 0);}
      if (buttonMode [1] != 1){(buttonMode [1] = 1);}
      if (buttonMode [2] != 0){(buttonMode [2] = 0);}
      if (buttonMode [3] != 1){(buttonMode [3] = 1);}
      if (buttonMode [4] != 0){(buttonMode [4] = 0);}
      if (LEDMode [0] != 0){(LEDMode [0] = 0);}
      if (LEDMode [1] != 1){(LEDMode [1] = 1);}
      if (LEDMode [2] != 0){(LEDMode [2] = 0);}
      if (LEDMode [3] != 1){(LEDMode [3] = 1);}
      if (LEDMode [4] != 0){(LEDMode [4] = 0);}
      masterModeSetupToggle = 1;
    }
    // MODE LOGIC
    if (buttonStatus[1] == 1 && buttonStatus[3] == 0)
      { LEDState[1] == 1;
        LEDState[3] == 0;
      }
    if (buttonStatus[1] == 0 && buttonStatus[3] == 1)
      { LEDState[1] == 1;
        LEDState[3] == 0;
      }

  }// ==========================================================
  // MORE Master Modes here....
  // MORE Master Modes here....
    // MORE Master Modes here....
      // MORE Master Modes here....
        // MORE Master Modes here....
          // MORE Master Modes here....

  // ======== MASTER MODE 255 - TEST ALL BUTTONS and LEDs ========= If buttonStatus is high, light the LED!
  if (masterMode == 255){
    // Setup the new MODE one time
    if (previousMasterMode != 255) {
      masterModeSetupToggle = 0;
      previousMasterMode = 255;
    }
    if (masterModeSetupToggle == 0){
      // Setup stuff here
      masterModeSetupToggle = 1;
    }
    // MODE LOGIC
    for (byte i = 0; i<=4; i++){
      if (buttonMode [i] != 2){(buttonMode [i] = 2);}
      if (LEDMode [i] != 1){(LEDMode [i] = 1);}
      LEDState[i] = buttonStatus[i];
    }
  }// ==========================================================
}
// ##################################################################################
void UpdateLEDS(){
  for (byte i = 0; i<=4; i++){
    if (LEDMode[i] > 0 ){
      // ======== LED MODE 1 - SOLID =========
      if (LEDMode[i] == 1){
        if (LEDState[i] == 0){LEDCurValue[i] = 0;}
        else if (LEDState[i] == 1){LEDCurValue[i] = LEDMaxBright[i];}
      }// ==========================================================

      // ======== LED MODE 20-29 - FLASH: 20 Slow - 29 Fast =========
      if (LEDMode[i] >= 20 && LEDMode[i] <= 29){
        if (LEDState[i] == 0){LEDCurValue[i] = 0;}

             if (LEDMode[i] == 20){LEDperiod[i] = 1500;}
        else if (LEDMode[i] == 21){LEDperiod[i] = 1250;}
        else if (LEDMode[i] == 22){LEDperiod[i] = 1000;}
        else if (LEDMode[i] == 23){LEDperiod[i] = 750;}
        else if (LEDMode[i] == 24){LEDperiod[i] = 500;}
        else if (LEDMode[i] == 25){LEDperiod[i] = 350;}
        else if (LEDMode[i] == 26){LEDperiod[i] = 250;}
        else if (LEDMode[i] == 27){LEDperiod[i] = 150;}
        else if (LEDMode[i] == 28){LEDperiod[i] = 100;}
        else if (LEDMode[i] == 29){LEDperiod[i] =  50;}

        if (buttonStatus[i] == 1){
          if (LEDNextUpdate[i] <= millis() ){
            if  (LEDCurValue[i] == LEDCurBright[i]){
                LEDCurValue[i] = 0;
            }   else {
                LEDCurValue[i] = LEDCurBright[i];
            }
          LEDNextUpdate[i] = (millis() + LEDperiod[i]);
          }
        }
      }// ========================================================

      // ======== LED MODE 30-39 - PULSE: 30 Slow - 39 Fast =========
      if (LEDMode[i] >= 30 && LEDMode[i] <= 39){
        if (LEDState[i] == 0){LEDCurValue[i] = 0;}

             if (LEDMode[i] == 30){LEDperiod[i] = 1500;}
        else if (LEDMode[i] == 31){LEDperiod[i] = 1250;}
        else if (LEDMode[i] == 32){LEDperiod[i] = 1000;}
        else if (LEDMode[i] == 33){LEDperiod[i] = 750;}
        else if (LEDMode[i] == 34){LEDperiod[i] = 500;}
        else if (LEDMode[i] == 35){LEDperiod[i] = 350;}
        else if (LEDMode[i] == 36){LEDperiod[i] = 250;}
        else if (LEDMode[i] == 37){LEDperiod[i] = 150;}
        else if (LEDMode[i] == 38){LEDperiod[i] = 100;}
        else if (LEDMode[i] == 39){LEDperiod[i] =  50;}

        if (LEDState[i] == 1){
          if (LEDNextUpdate[i] <= millis() ){
            if  (LEDCurValue[i] >0){
                LEDCurValue[i] = 0;
            }   else {
                LEDCurValue[i] = LEDCurBright[i];
            }
          LEDNextUpdate[i] = (millis() + LEDperiod[i]);
          }
        }
      }// ========================================

      analogWrite(LEDOutputPin[i],(LEDCurValue[i] * LEDDim[i]/100) );    // UPDATES LED PINOUTS WITH CURRENT VALUE AND BRIGHTNESS Add DIM multiplier here?? or Use in functions?
    }
  }
}
// ##################################################################################
void GetButtonStatus(){
  if (buttonMode[0] > 0 || buttonMode[1] > 0 || buttonMode[2] > 0 || buttonMode[3] > 0 || buttonMode[4] > 0){
      //unsigned long start = millis(); // This value may not be required except for debug report of performance.
      total[0] =  cs0.capacitiveSensor(30);
      total[1] =  cs1.capacitiveSensor(30);
      total[2] =  cs2.capacitiveSensor(30);
      total[3] =  cs3.capacitiveSensor(30);
      total[4] =  cs4.capacitiveSensor(30);
      for (byte i = 0; i<=4; i++){
        if (total[i] > csMinVal[i] && buttonPress[i] == 0){buttonPress[i] = 1;}
        else if (total[i] < csMinVal[i] && buttonPress[i] == 1){buttonPress[i] = 0;}
        if (buttonMode[i] == 1){  // INTERMITENT BUTTON MODE ==============
          if (buttonPress[i] == 1){buttonStatus[i] = 1;}
          else if (buttonPress[i] == 0){buttonStatus[i] = 0;}
        }
        if (buttonMode[i] == 2){  // ON-OFF BUTTON MODE =====================
          if (buttonPress[i] == 1 && buttonToggle[i] == 0){ buttonToggle[i] = 1; buttonStatus[i] = !buttonStatus[i];}
          else if (buttonPress[i] == 0 && buttonToggle[i] == 1){buttonToggle[i] = 0;}
        }
      }
   }
}
// ##################################################################################
void loop(){
  Command();
  GetButtonStatus();
  UpdateLEDS();
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
