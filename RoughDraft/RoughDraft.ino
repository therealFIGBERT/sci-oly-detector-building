#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);
    int thermistor = A0;
    float R1 = 10000;
    float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
}

void loop() {
    int sensorValue = analogRead(thermistor)
    float voltage = sensorValue * (3.3 / 1023.0);
    float celsius = (voltage - 0.5) * 100;
    float fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
    lcd.setCursor(5, 0);
    lcd.print(String(celsius) + "C");
    lcd.setCursor(5, 1);
    lcd.print(String(fahrenheit) + "F");
}

