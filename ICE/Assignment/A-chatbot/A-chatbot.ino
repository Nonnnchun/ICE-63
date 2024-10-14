#include <SoftwareSerial.h>

String inputString = "";
SoftwareSerial mySerial(10,11);

void setup()
{
  Serial.begin(4800);
  Serial.println("A");
  mySerial.begin(4800);
}

void loop()
{
  while(Serial.available())
  {
    char inChar=(char)Serial.read();
    inputString = inputString + inchar;
    if (inChar == '\n')
    {
      mySerial.print("A -> ");
      mySerial.println(inputString);
      inputString = "";
    }
  }
  
  while(mySerial.available())
  {
    Serial.print((char)mySerial.read());
  }
}