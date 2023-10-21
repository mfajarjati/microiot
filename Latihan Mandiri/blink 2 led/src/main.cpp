#include <arduino.h>
#define LED_PIN 2
#define LED_PIN_EX 4

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_EX, OUTPUT);
}

void loop()
{
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(LED_PIN_EX, LOW);
  delay(2000);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_PIN_EX, HIGH);
  delay(2000);
}