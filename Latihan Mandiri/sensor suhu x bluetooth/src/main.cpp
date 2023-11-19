#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <BluetoothSerial.h>

#define DHT_PIN 4
#define DHT_TYPE DHT11

BluetoothSerial SerialBT;

DHT dht(DHT_PIN, DHT_TYPE);
float temp, humid;
String printData;
String tempSentence = "Suhu saat ini: ";
String humidSentence = "Kelembaban saat ini: ";

void updateData();

void setup()
{
  SerialBT.begin("ESP32-BTClassic");
  dht.begin();
}

void loop()
{

  updateData();
  // ESP_LOGI("SENSOR : ", "Temperatur : % 2.f", updateData());
  printData = tempSentence + String(temp) + String(" C");
  SerialBT.println(printData);
  printData = humidSentence + String(humid) + String(" %");
  SerialBT.println(printData);
  delay(5000);
}

void updateData()
{
  temp = dht.readTemperature();
  humid = dht.readHumidity();
}