#include <Arduino.h>

// put function declarations here:
// int myFunction(int, int);

void setup()
{
  // put your setup code here, to run once:
  pinMode(BUILTIN_LED, OUTPUT);
  // int result = myFunction(2, 3);
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(BUILTIN_LED, HIGH);
  delay(2000);
  digitalWrite(BUILTIN_LED, LOW);
  delay(2000);
}

// // put function definitions here:
// int myFunction(int x, int y)
// {
//   return x + y;
// }