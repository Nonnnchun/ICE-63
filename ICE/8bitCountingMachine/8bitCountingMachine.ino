int led[8]={11,10,9,8,7,6,5,4};

int stopButton = 3;
int resetButton = 2;

int stopButtonState ;
int resetButtonState ;

int lastStopState = LOW;
int lastResetState = LOW;

bool isCount = false;

uint8_t a = 0;

unsigned long long lastDebounceTime = 0;
unsigned long long lastStopButtonTime = 0;
int debounceDelay = 100;
//bitRead(variable,position); --> return 0, 1

void setup()
{
  Serial.begin(9600);
  
  pinMode(3,INPUT);
  pinMode(2,INPUT);
  
  for(int i = 0; i<8; i++){
    pinMode(led[i],OUTPUT);
  }
  
  attachInterrupt(1,stop,RISING);
  attachInterrupt(0,reset,RISING);
}

void loop()
{
  count();
  if(!isCount){
    a++;
  }
}

void count(){
  for(int i = 0; i<8; i++){
    digitalWrite(led[i], bitRead(a,i));
  }
  if(a>255){
    a = 0;
  }
  delay(500);
}


void stop(){
  if (digitalRead(stopButton) && millis() - lastStopButtonTime >= 200) {
  	lastStopButtonTime = millis();
    isCount = !isCount;
    Serial.println("stop");
  }
}

void reset(){
  int readingReset = digitalRead(resetButton);
  
  if (readingReset && millis() - lastStopButtonTime >= 200) {
  	lastStopButtonTime = millis();
    a = 0;
    Serial.println("reset");
  }
}