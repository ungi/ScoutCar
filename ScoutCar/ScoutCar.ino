#include "Time.h"

void setup()
{
  Serial.begin(9600);
  setTime(12,0,0,1,1,11);
}

void loop()
{
  Serial.print("I'm sending a message at ");
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
  delay(2000);
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
  {
    Serial.print("0");
  }
}

