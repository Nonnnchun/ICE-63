int pin1 = 8;
int pin2 = 9;
int pin3 = 10;

void setup() {
}

void loop() {

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, INPUT);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  delay(500);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, INPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(500);

  pinMode(8, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  delay(500);

  pinMode(8, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  delay(500);

  //-------------------------------------------------------------------

  pinMode(8, OUTPUT);
  pinMode(9, INPUT);
  pinMode(10, OUTPUT);
  digitalWrite(8, HIGH);
  digitalWrite(10, LOW);
  delay(500);

  pinMode(8, OUTPUT);
  pinMode(9, INPUT);
  pinMode(10, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(10, HIGH);
  delay(500);

}
