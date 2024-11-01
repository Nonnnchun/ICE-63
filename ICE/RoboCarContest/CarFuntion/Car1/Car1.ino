
// motor one <<ซ้าย>>
int enA = 6;
int inA = 9;  //ไปหน้า
int inB = 8;  //ไปหลัง

// motor two <<ขวา>>
int enB = 5;
int inC = 11;  //ไปหน้า
int inD = 10;  //ไปหลัง

void setup() {
  // set all the motor 1 control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(inA, OUTPUT);
  pinMode(inB, OUTPUT);

  // set all the motor 2 control pins to outputs
  pinMode(enB, OUTPUT);
  pinMode(inC, OUTPUT);
  pinMode(inD, OUTPUT);
}

void loop() {
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(inA, HIGH);
  digitalWrite(inB, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 100);  // Speed Control

  digitalWrite(inD, LOW);
  digitalWrite(inC, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 100);  // Speed Control
  delay(2000);


  // now turn off motors
  digitalWrite(inA, LOW);
  digitalWrite(inD, LOW);
}