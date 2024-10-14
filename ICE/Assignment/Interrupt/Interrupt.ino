const int ledPins[] = {8, 9, 10, 11};
const int switchCount = 4;

void setup() {
  for (int i = 0; i < switchCount; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  Serial.begin(9600);
}

void loop() {
  int read = analogRead(A0);
  Serial.println(read);
  
	if(read==930){
    digitalWrite(ledPins[2],HIGH);
    }else {digitalWrite(ledPins[2],LOW);}
  
    if(read==512){
    digitalWrite(ledPins[3],HIGH);
    }else {digitalWrite(ledPins[3],LOW);}
  
	if(read==977){
    digitalWrite(ledPins[1],HIGH);
    }else {digitalWrite(ledPins[1],LOW);}
  
	if(read==1001){
    digitalWrite(ledPins[0],HIGH);
    }else {digitalWrite(ledPins[0],LOW);}
  
  delay(100);
}
