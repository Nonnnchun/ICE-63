int ledR=5;
int ledG=6;
int ledY=7;

int buttonR = 8;
int buttonG = 9;
int buttonY = 10;

int ledStateR = LOW;
int ledStateG = LOW;
int ledStateY = LOW;

int buttonStateR;
int buttonStateG;
int buttonStateY;

int lastButtonStateG = LOW;
int lastButtonStateR = LOW;
int lastButtonStateY = LOW;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

//
void setup()
{

  pinMode(ledR, OUTPUT);
  pinMode(buttonR, INPUT);
  digitalWrite(ledR, ledStateR);

  pinMode(ledG, OUTPUT);
  pinMode(buttonG, INPUT);
  digitalWrite(ledG, ledStateG);
  
  pinMode(ledY, OUTPUT);
  pinMode(buttonY, INPUT_PULLUP);
  digitalWrite(ledY, ledStateY);
}

void loop()
{
  int readR = digitalRead(buttonR);
  int readG = digitalRead(buttonG);
  int readY = digitalRead(buttonY);
  
  if(readR != lastButtonStateR){
    lastDebounceTime = millis();
  }
  
  if(readG != lastButtonStateG){
    lastDebounceTime = millis();
  }
  
   if(readY != lastButtonStateY){
    lastDebounceTime = millis();
  }
  
  if((millis()-lastDebounceTime) > debounceDelay){
    if(readR != buttonStateR){
      buttonStateR = readR;
      
      if(buttonStateR == HIGH){
        ledStateR = !ledStateR;
      }
    }
  }
  
  if((millis()-lastDebounceTime) > debounceDelay){
    if(readG != buttonStateG){
      buttonStateG = readG;
      
      if(buttonStateG == LOW){
        ledStateG = !ledStateG;
      }
    }
  }
  
   if((millis()-lastDebounceTime) > debounceDelay){
    if(readY != buttonStateY){
      buttonStateY = readY;
      
      if(buttonStateY == LOW){
        ledStateY = !ledStateY;
      }
    }
  }
  
  digitalWrite(ledR, ledStateR);
  digitalWrite(ledG, ledStateG);
  digitalWrite(ledY, ledStateY);

  
  lastButtonStateR = readR;
  lastButtonStateG = readG;
  lastButtonStateY = readY;

}