int led[8]={4,5,6,7,8,9,10,11};
//
void setup()
{
  for(int i = 0; i<8; i++){
    pinMode(led[i],OUTPUT);
  }
}

void loop()
{
  for(int i = 0; i<8; i++){
    digitalWrite(led[i],HIGH);
    delay(500);
    digitalWrite(led[i],LOW);
  }
  for(int i = 6; i>0; i--){
    digitalWrite(led[i],HIGH);
    delay(500);
    digitalWrite(led[i],LOW);
  }
}