#include <Arduino.h>

#define pin_led_4 4
#define pin_led_16 16
#define pin_led_17 17

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(pin_led_4, OUTPUT);
  pinMode(pin_led_16, OUTPUT);
  pinMode(pin_led_17, OUTPUT);
  Serial.begin(9600);
  delay(1000);
}

void loop()
{
  if (Serial.available())
  {
    char data = Serial.read();
    if (data == '1')
    {
      Serial.print("angka yang dimasukkan : ");
      Serial.println(data);
      digitalWrite(BUILTIN_LED, HIGH);
      delay(2000);
      digitalWrite(BUILTIN_LED, LOW);
    }
    else if (data == '2')
    {
      Serial.print("angka yang dimasukkan : ");
      Serial.println(data);
      digitalWrite(pin_led_4, HIGH);
      delay(2000);
      digitalWrite(pin_led_4, LOW);
    }
    else if (data == '3')
    {
      Serial.print("angka yang dimasukkan : ");
      Serial.println(data);
      digitalWrite(pin_led_16, HIGH);
      delay(2000);
      digitalWrite(pin_led_16, LOW);
    }
    else if (data == '4')
    {
      Serial.print("angka yang dimasukkan : ");
      Serial.println(data);
      digitalWrite(pin_led_17, HIGH);
      delay(2000);
      digitalWrite(pin_led_17, LOW);
    }
    else
    {
      Serial.println("Masukkan angka 1 hingga 4 yaa!!");
    }
  }
}
