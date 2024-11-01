int led[8]={4,5,6,7,8,9,10,11};
unsigned short speed = A1;
//
void setup()
{
  for(int i = 0; i<8; i++){
    pinMode(led[i],OUTPUT);
  }
}

void loop()
{
  int speed = analogRead(A1);
  for(int i = 0; i<8; i++){
    int speed = analogRead(A1);
    digitalWrite(led[i],HIGH);
    delay(speed);
    digitalWrite(led[i],LOW);
  }
  for(int i = 6; i>0; i--){
    int speed = analogRead(A1);
    digitalWrite(led[i],HIGH);
    delay(speed);
    digitalWrite(led[i],LOW);
  }
}