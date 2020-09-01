#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int val;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
//  lcd.setCursor(0, 0);
//  lcd.print("Hello, world!");
//  lcd.setCursor(0, 1);
//  lcd.print("Eduino");
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(A2);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(val);
  delay(100);
}
