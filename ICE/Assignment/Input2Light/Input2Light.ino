//หลอดไฟติด
//ฝั่งส่ง

void setup()
{
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(2, INPUT);
}

void loop()
{
  while (Serial.available() > 0)
  {
    String input = Serial.readStringUntil('\n');
    int num = input.toInt();
    Serial.println(num);
    
    if (num > 9) {
      num = 0;
    }
    
    for (int i=0; i<num; i++) {
      digitalWrite(3, HIGH);
      delay(250);
      digitalWrite(3, LOW);
      delay(250);
    }
  }
}

//ฝั่งรับ + ให้ไฟติด

void setup()
{
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(2, INPUT);
  
  pinMode(13, OUTPUT);
}

void loop()
{
  if (digitalRead(2) == HIGH)
  {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
}