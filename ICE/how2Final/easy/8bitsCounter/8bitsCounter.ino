int led[8]={11,10,9,8,7,6,5,4};
uint8_t a = 0;
//bitRead(variable,position); --> return 0, 1

void setup()
{
  for(int i = 0; i<8; i++){
    pinMode(led[i],OUTPUT);
  }
}

void loop()
{
  for(int i = 0; i<8; i++){
    digitalWrite(led[i], bitRead(a,i));
  }
  a++;
  if(a>255){
    a = 0;
  }
  delay(200);
}
