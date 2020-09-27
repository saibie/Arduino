// Simple gamepad example that demonstraits how to read five Arduino
// digital pins and map them to the Arduino Joystick library.
//
// The digital pins 1 - 13 are grounded when they are pressed.
// Pin 1 = WIPER_HI
// Pin 2 = WIPER_LO
// Pin 3 = WIPER_INT
// Pin 4 = WIPER_MIST
// Pin 5 = WIPER_WASH
// Pin 6 = FAST INT
// Pin 7 = 
// Pin 8 = REAR LIGHT
// Pin 9 = HEAD LIGHT
// Pin 10 = FOG LIGHT
// Pin 11 = HIGH BEAM
// Pin 12 = LEFT
// Pin 13 = RIGHT
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2016-11-24
//--------------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick; //(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
//  1, 0,                  // Button Count, Hat Switch Count
//  true, true, false,     // X and Y, but no Z Axis
//  false, false, false,   // No Rx, Ry, or Rz
//  false, false,          // No rudder or throttle
//  false, false, false);  // No accelerator, brake, or steering
int k[13];
void setup() {
  // Initialize Button Pins
  for(int i = 0;i < 13;i++){
    pinMode(i + 1, INPUT_PULLUP);
  }
  Serial.begin(9600);
  
  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
}

void loop() {
  // Read pin states
  for(int i = 0;i < 13;i++){
    k[i] = digitalRead(i + 1);
  }
  // Show PinNumber
  for(int i = 0;i < 13;i++){
    if(i < 9){Serial.print("0");}
    Serial.print(i + 1);
    Serial.print(" ");
  }
  Serial.println(" ");

  // Show Status
  for(int i = 0;i < 13;i++){
    Serial.print(k[i]);
    Serial.print(k[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
  // Read pin values
  /*for (int index = 0; index < 5; index++)
  {
    int currentButtonState = !digitalRead(index + 2);
    if (currentButtonState != lastButtonState[index])
    {
      switch (index) {
        case 0: // UP
          if (currentButtonState == 1) {
            Joystick.setYAxis(-1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 1: // RIGHT
          if (currentButtonState == 1) {
            Joystick.setXAxis(1);
          } else {
            Joystick.setXAxis(0);
          }
          break;
        case 2: // DOWN
          if (currentButtonState == 1) {
            Joystick.setYAxis(1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 3: // LEFT
          if (currentButtonState == 1) {
            Joystick.setXAxis(-1);
          } else {
            Joystick.setXAxis(0);
          }
          break;
        case 4: // FIRE
          Joystick.setButton(0, currentButtonState);
          break;
      }
      lastButtonState[index] = currentButtonState;
    }
  }*/

  delay(100);
}
