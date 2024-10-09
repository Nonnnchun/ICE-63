const int sensorPins[4] = { A0, A1, A2, A3};  // ขาเชื่อมต่อของเซ็นเซอร์ IR
int sensorValues[4];                               // ตัวแปรเก็บค่าที่อ่านจากเซ็นเซอร์

//--------------------IR Sensor-------------------------------

const int photoResistorPin = A5;  // ขาเชื่อมต่อของ photoresistor
// const int ledPin = 4;            // ขาเชื่อมต่อของ LED

//--------------------LDR Sensor------------------------------

const int trigPin = 12;   // ขา Trig
const int echoPin = 13;  // ขา Echo

//----------------Ultra Sonic Module--------------------------



void setup() {
  Serial.begin(9600);       // เริ่มต้น Serial Monitor
  // pinMode(ledPin, OUTPUT);  // ตั้งค่า LED เป็น OUTPUT

  pinMode(trigPin, OUTPUT);  // ตั้งค่า Trig เป็น OUTPUT
  pinMode(echoPin, INPUT);   // ตั้งค่า Echo เป็น INPUT
}

void loop() {
  long duration, distance;

  // เคลียร์ค่า Trig Pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // ส่ง Pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // อ่านค่า Echo Pin
  duration = pulseIn(echoPin, HIGH);

  // คำนวณระยะทาง (cm)
  distance = duration * 0.0343 / 2;

  // แสดงผลระยะทางใน Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(15);  // รอ 1 วินาที

  //---------------Ultra Sonic Module--------------------------

  int sensorValue = analogRead(photoResistorPin);  // อ่านค่าจาก photoresistor
  Serial.print("LDR Value: ");
  Serial.println(sensorValue);  // แสดงค่าที่อ่านได้

  // // เปรียบเทียบค่าและเปิด/ปิด LED
  // if (sensorValue < 300) {       // ปรับค่าตามความต้องการ
  //   digitalWrite(ledPin, HIGH);  // เปิด LED ถ้ามีแสงน้อย
  // } else {
  //   digitalWrite(ledPin, LOW);  // ปิด LED ถ้ามีแสงมาก
  // }

  delay(10);  // รอ 1 วินาที

  //--------------------LDR Sensor-----------------------------

  // อ่านค่าจากเซ็นเซอร์ IR
  delay(10);
  for (int i = 0; i < 4; i++) {
    Serial.print("\t\t");
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(analogRead(sensorPins[i]));
    delay(10);
  }
  Serial.println();

  //---------------------IR Sensor-----------------------------

  delay(100);
}
