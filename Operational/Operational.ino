#include <hd44780.h>
#include <Wire.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
hd44780_I2Cexp lcd;
#define THERMISTORNOMINAL 100000
#define TEMPERATURENOMINAL 25
#define NUMSAMPLES 2
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
    float first = voltage(0), second = voltage(1);
    float bridge = (first + second) / 2;
    float volts = bridge * (3.3 / 1023.0);
    float res = resistance(bridge);
    float temp = celsius(res);
    lcd.setCursor(5, 0);
    lcd.print(String(temp) + "C");
    lcd.setCursor(5, 1);
    lcd.print(String(volts) + "V");
    delay(1000);
    lcd.clear();
}

float voltage(int pin) {
    uint8_t i;
    float volt;
    for (i=0; i< NUMSAMPLES; i++) {
     samples[i] = analogRead(pin);
     delay(10);
    }
    volt = 0;
    for (i=0; i< NUMSAMPLES; i++) {
       volt += samples[i];
    }
    volt /= NUMSAMPLES;
    return volt;
}

float resistance(float volts) {
    volts = 1023 / volts - 1;
    volts = SERIESRESISTOR / volts;
    return volts;
}

float celsius(float res) {
    float celsius = res / THERMISTORNOMINAL;
    celsius = log(celsius);
    celsius /= BCOEFFICIENT;
    celsius += 1.0 / (TEMPERATURENOMINAL + 273.15);
    celsius = 1.0 / celsius;
    celsius -= 273.15;
    return celsius;
}
