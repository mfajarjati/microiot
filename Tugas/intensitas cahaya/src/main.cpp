#define USE_BH1750_LIB
#include <Arduino.h>
#include <BH1750.h>
#include <Wire.h>

BH1750 lightMeter;

#define LED_PIN 2
#define PWM_CHANNEL 0
#define PWM_FREQ 5000
#define PWM_RESOLUTION 8

float baca_dataLux();
void print_Lux(float luxValue);
void atur_LED(float luxValue);

void setup()
{
  Serial.begin(9600);

  Wire.begin();
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);

  ledcAttachPin(LED_PIN, PWM_CHANNEL);
  lightMeter.begin();
  Serial.println(F("Sensor BH1750 Test begin..."));
}

void loop()
{
  float lux = baca_dataLux();
  print_Lux(lux);
  atur_LED(lux);
  delay(1000);
}

// baca data lux
float baca_dataLux()
{
  return lightMeter.readLightLevel();
}

// cetak nilai lux
void print_Lux(float luxValue)
{
  Serial.print("Cahaya : ");
  Serial.print(luxValue);
  Serial.println(" lux");
}

// mengatur nyala led berdasarkan lux
void atur_LED(float luxValue)
{
  if (luxValue > 2500)
  {
    ledcWrite(PWM_CHANNEL, 0);
  }
  else if (luxValue >= 0 && luxValue < 2500)
  {
    ledcWrite(PWM_CHANNEL, 255 - (luxValue / 10));
  }
}
