// Arduino Line Follower Robot Code


#define enA 6  //Enable1 L293 Pin enA

#define in1 9  //Motor1  L293 Pin in1

#define in2 8  //Motor1  L293 Pin in1

#define in3 11  //Motor2  L293 Pin in1

#define in4 10  //Motor2  L293 Pin in1

#define enB 5  //Enable2 L293 Pin enB

const int sensorPins[4] = { A0, A1, A2, A3 };  // ขาเชื่อมต่อของเซ็นเซอร์ IR
int sensorValues[4];                           // ตัวแปรเก็บค่าที่อ่านจากเซ็นเซอร์
int digitalValues[4];                          // ตัวแปรเก็บค่าที่แสดงเป็น digital (0 หรือ 1)

void setup() {
  Serial.begin(9600);

  // ตั้งค่าขาเซ็นเซอร์ IR เป็น INPUT
  for (int i = 0; i < 4; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  pinMode(enA, OUTPUT);

  pinMode(in1, OUTPUT);

  pinMode(in2, OUTPUT);

  pinMode(in3, OUTPUT);

  pinMode(in4, OUTPUT);

  pinMode(enB, OUTPUT);

  digitalWrite(enA, HIGH);

  digitalWrite(enB, HIGH);

  delay(1000);
}

void loop() {

  for (int i = 0; i < 4; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);  // อ่านค่าจากเซ็นเซอร์ IR

    // ปรับค่า analog เป็น digital ตามเงื่อนไข
    if (sensorValues[i] >= 110) {
      digitalValues[i] = 0;  // digital = 0 สำหรับพื้นที่สีขาว
    } else if (sensorValues[i] <= 109) {
      digitalValues[i] = 1;  // digital = 1 สำหรับพื้นที่สีดำ
    }
  }

  // แสดงค่าที่แสดงเป็น digital
  Serial.print("Digital values: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(sensorValues[i]);
    Serial.print("\t");
  }
  Serial.println();

  if ((digitalValues[0] == 0) && (digitalValues[3] == 0)) { forward(); }  //if Right Sensor and Left Sensor are at White color then it will call forword function

  if ((digitalValues[0] == 1) && (digitalValues[3] == 0)) { turnRight(); }  //if Right Sensor is Black and Left Sensor is White then it will call turn Right function

  if ((digitalValues[0] == 0) && (digitalValues[3] == 1)) { turnLeft(); }  //if Right Sensor is White and Left Sensor is Black then it will call turn Left function

  if ((digitalValues[0] == 1) && (digitalValues[3] == 1)) { Stop(); }  //if Right Sensor and Left Sensor are at Black color then it will call Stop function

  if ((digitalValues[0] == 1) && (digitalValues[3] == 1) && (digitalValues[0] == 1) && (digitalValues[3] == 1)) { forwardOneSec(); }  //if Right Sensor and Left Sensor are at Black color then it will call Stop function
}

void forwardOneSec() {  //forword
  analogWrite(enA, 75);
  analogWrite(enB, 75);

  digitalWrite(in1, HIGH);  //Right Motor forword Pin

  digitalWrite(in2, LOW);  //Right Motor backword Pin

  digitalWrite(in3, HIGH);  //Left Motor backword Pin

  digitalWrite(in4, LOW);  //Left Motor forword Pin
  delay(1000);
  //---------------------------------------------------------

  digitalWrite(in1, LOW);  //Right Motor forword Pin

  digitalWrite(in2, LOW);  //Right Motor backword Pin

  digitalWrite(in3, LOW);  //Left Motor backword Pin

  digitalWrite(in4, LOW);  //Left Motor forword Pin
}

void forward() {  //forword
  analogWrite(enA, 75);
  analogWrite(enB, 75);

  digitalWrite(in1, HIGH);  //Right Motor forword Pin

  digitalWrite(in2, LOW);  //Right Motor backword Pin

  digitalWrite(in3, HIGH);  //Left Motor backword Pin

  digitalWrite(in4, LOW);  //Left Motor forword Pin
}

void turnRight() {  //turnRight
  analogWrite(enA, 75);
  analogWrite(enB, 75);

  digitalWrite(in1, HIGH);  //Right Motor forword Pin

  digitalWrite(in2, LOW);  //Right Motor backword Pin

  digitalWrite(in3, LOW);  //Left Motor backword Pin

  digitalWrite(in4, HIGH);  //Left Motor forword Pin
}

void turnLeft() {  //turnLeft
  analogWrite(enA, 75);
  analogWrite(enB, 75);

  digitalWrite(in1, LOW);  //Right Motor forword Pin

  digitalWrite(in2, HIGH);  //Right Motor backword Pin

  digitalWrite(in3, HIGH);  //Left Motor backword Pin

  digitalWrite(in4, LOW);  //Left Motor forword Pin
}

void Stop() {  //stop

  digitalWrite(in1, LOW);  //Right Motor forword Pin

  digitalWrite(in2, LOW);  //Right Motor backword Pin

  digitalWrite(in3, LOW);  //Left Motor backword Pin

  digitalWrite(in4, LOW);  //Left Motor forword Pin
}