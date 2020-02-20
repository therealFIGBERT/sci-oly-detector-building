#include <hd44780.h>
#include <Wire.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
hd44780_I2Cexp lcd;

void setup() {
    lcd.begin(16, 2);
    lcd.backlight();
    Serial.begin(9600);
}

void loop() {
    int sensorValue = analogRead(A0)
    float voltage = sensorValue * (3.3 / 1023.0);
    float celsius = (voltage - 0.5) * 100;
    float fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
    lcd.setCursor(5, 0);
    lcd.write(String(celsius) + "C");
    lcd.setCursor(5, 1);
    lcd.write(String(fahrenheit) + "F");
}
