#include <Arduino.h>

#define pin_potentiometer 4
int adcValue = 0;
float voltage = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  adcValue = analogRead(pin_potentiometer);
  String print_data = "ADC yang terbaca: " + String(adcValue);
  Serial.println(print_data);

  voltage = (float(adcValue) / 4095.0) * 3.3;
  print_data = "Voltage yang terbaca: " + String(voltage) + " v";
  Serial.println(print_data);

  delay(5000);
}
