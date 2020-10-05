// Simple gamepad example that demonstraits how to read five Arduino
// digital pins and map them to the Arduino Joystick library.
//
// The digital pins 1 - 13 are grounded when they are pressed.
// Pin 1 = WIPER_HI *
// Pin 2 = WIPER_LO *
// Pin 3 = WIPER_INT *
// Pin 4 = WIPER_MIST *
// Pin 5 = WIPER_WASH *
// Pin 6 = FAST INT *
// Pin 7 = 
// Pin 8 = REAR LIGHT
// Pin 9 = HEAD LIGHT
// Pin 10 = FOG LIGHT *
// Pin 11 = HIGH BEAM *
// Pin 12 = LEFT *
// Pin 13 = RIGHT *
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2016-11-24
//--------------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  13, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

int R[13];
int C[13];
int LeftRightSwitch1[] = {0, 0};
int LeftRightSwitch2[] = {0, 0};
int WiperState = 0;
int CWiperState = 0;
int CCWiperState = 0;
int WiperSwitch = 0;
int WiperDelay = 0;
int LightState = 0;
int CLightState = 0;
int LightLoop = 0;
int LightLoop2 = 0;
int HighBeamState = 0;

void setup() {
  // Initialize Button Pins
  for(int i = 0;i < 13;i++){
    pinMode(i + 1, INPUT_PULLUP);
    C[i] = 0;
  }
//  Serial.begin(9600);
  // Initialize Joystick Library
  Joystick.begin();
//  Joystick.setXAxisRange(-1, 1);
//  Joystick.setYAxisRange(-1, 1);
}

void loop() {
  // Read pin states
  for(int i = 0;i < 13;i++){
    R[i] = digitalRead(i + 1);
  }
  
  // Switching Gears - LEFT and RIGHT : Button 0, 1
  for(int i = 11; i < 13; i++){
    if(LeftRightSwitch2[i-11] > 0){
      if(LeftRightSwitch1[i-11] == LeftRightSwitch2[i-11]){
        LeftRightSwitch1[i-11]--;
        Joystick.setButton(i-11, 1);
      }
      else{
        LeftRightSwitch2[i-11]--;
        Joystick.setButton(i-11, 0);
      }
    }
    
    if(R[i] != C[i]){
      C[i] = R[i];
      LeftRightSwitch1[i-11]++;
      LeftRightSwitch2[i-11]++;
    }
    
  }
  
  // WIPER : Button 2, 3
  if(WiperState != CWiperState){
    CWiperState = WiperState;
  }
  if(WiperSwitch != 0){
    WiperSwitch = 0;
    Joystick.setButton(2, 0);
    Joystick.setButton(3, 0);
    CCWiperState = WiperState;
  }
  WiperState = 0;
  for(int i = 0; i < 3; i++){ // Read WiperState : 0~3
    if(R[i] == 0){
      WiperState = 3 - i;    
    }
  }  
  if(WiperState == 0 && CWiperState != 0){
    WiperDelay = 10;
  }
  if(WiperDelay <= 0 || WiperState != 0){
    WiperDelay = 0;
    if(WiperState > CCWiperState){
      Joystick.setButton(3, 1);
      WiperSwitch = 1;
    }
    else if(WiperState < CCWiperState){
      Joystick.setButton(2, 1);
      WiperSwitch = 1;
    }
  }
  if(WiperDelay > 0){WiperDelay--;}
//  Serial.print(WiperDelay);
//  Serial.println(WiperSwitch);
  
  // Light Control : Button 4
  if(LightLoop2 > 0){
    if(LightLoop == LightLoop2){
      LightLoop--;
      Joystick.setButton(4, 1);
    }
    else{
      LightLoop2--;
      Joystick.setButton(4, 0);
    }
  }
  
  CLightState = LightState;
  if(R[8] == 0){LightState = 2;}
  else if(R[7] == 0){LightState = 1;
  }else{LightState = 0;}
  
  if(LightState > CLightState){
    LightLoop = LightLoop + 1;
    LightLoop2 = LightLoop2 + 1;
  }
  else if(LightState < CLightState){
    LightLoop = LightLoop + 2;
    LightLoop2 = LightLoop2 + 2;
  }

  // Switching Gears - High Beam : Button 5
  if(HighBeamState == 1){
    Joystick.setButton(5, 0);
    HighBeamState = 0;
    C[10] = R[10];
  }
  if(R[10] != C[10]){
    Joystick.setButton(5, 1);
    HighBeamState = 1;
  }
  
  // Gears Like Normal Button : Button 6 ~ 10
  int ind[] = {3, 4, 5, 9};
  for (int i = 0; i < 4; i++)
  {
    int currentButtonState = !R[ind[i]];
    if (currentButtonState != C[ind[i]])
    {
      Joystick.setButton(i + 6, currentButtonState);
      C[ind[i]] = currentButtonState;
    }
  }

  delay(10);
}
