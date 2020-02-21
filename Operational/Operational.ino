#include <hd44780.h>
#include <Wire.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
hd44780_I2Cexp lcd;
#define THERMISTORNOMINAL 100000
#define TEMPERATURENOMINAL 25
#define NUMSAMPLES 10
#define BCOEFFICIENT 4000
#define SERIESRESISTOR 100000    
 
int samples[NUMSAMPLES];

void setup() {
    lcd.begin(16, 2);
    lcd.backlight();
    Serial.begin(9600);
    analogReference(EXTERNAL);
}

void loop() {
    float first = temperature(0), second = temperature(1);
    float celsius = (first + second) / 2;
    lcd.setCursor(5, 0);
    lcd.print(String(celsius) + "C");
    float fahrenheit = (celsius * 1.8) + 32;
    lcd.setCursor(5, 1);
    lcd.print(String(fahrenheit) + "F");
    delay(1000);
}

float temperature(int pin) {
    uint8_t i;
    float average;
    for (i=0; i< NUMSAMPLES; i++) {
     samples[i] = analogRead(pin);
     delay(10);
    }
    average = 0;
    for (i=0; i< NUMSAMPLES; i++) {
       average += samples[i];
    }
    average /= NUMSAMPLES;
    average = 1023 / average - 1;
    average = SERIESRESISTOR / average;
    float celsius = average / THERMISTORNOMINAL;
    celsius = log(celsius);
    celsius /= BCOEFFICIENT;
    celsius += 1.0 / (TEMPERATURENOMINAL + 273.15);
    celsius = 1.0 / celsius;
    celsius -= 273.15;
    return celsius;
}
