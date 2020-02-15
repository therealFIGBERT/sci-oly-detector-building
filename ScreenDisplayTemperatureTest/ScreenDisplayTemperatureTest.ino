#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  int leftSideOfRatio = 5 / voltage;
  String HalfwayThroughCircutVolts = String(voltage) + " V";
  String RatioBetweenCenterAndStartVolts = String(leftSideOfRatio) + ":1";
  lcd.setCursor(5, 0);
  lcd.print(HalfwayThroughCircutVolts);
  lcd.setCursor(6, 1);
  lcd.print(RatioBetweenCenterAndStartVolts);
}
