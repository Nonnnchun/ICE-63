void setup(){
  for (int i = 5; i <= 10; i++){
    pinMode(i, OUTPUT);
  }
}

void soClose(){
  for (int i = 5; i <= 10; i++){
    digitalWrite(i, LOW);
  }
}

void loop(){
  for (int i = 0; i < 100; i++)
  {
    soClose();
    digitalWrite(10, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(6, HIGH);
    delay(5);
    soClose();
    digitalWrite(9, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(5, HIGH);
    delay(5);
  }

  
  for (int i = 0; i < 100; i++)
  {
    soClose();
    digitalWrite(10, HIGH);
    digitalWrite(8, HIGH);
    delay(5);
    soClose();
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(6, HIGH);
    delay(5);
  }
  
  soClose();
}