#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHT_PIN 5
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);
float temp, humid;
String printData;
String tempSentence = "Suhu saat ini: ";
String humidSentence = "Kelembaban saat ini: ";

void updateData();

void setup()
{
  Serial.begin(9600);
  dht.begin();
}

void loop()
{

  updateData();
  // ESP_LOGI("SENSOR : ", "Temperatur : % 2.f", updateData());
  printData = tempSentence + String(temp) + String(" C");
  Serial.println(printData);
  printData = humidSentence + String(humid) + String(" %");
  Serial.println(printData);
  delay(5000);
}

void updateData()
{
  temp = dht.readTemperature();
  humid = dht.readHumidity();
}