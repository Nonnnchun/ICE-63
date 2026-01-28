//----------------------------------------------------------Tester Ep.1000000--------------------------------------------------------------

// Arduino Line Follower Robot Code
const int photoResistorPin = A5;        // ขาเชื่อมต่อของ photoresistor
const int trigPin = 12;                 // ขา Trig
const int echoPin = 13;                 // ขา Echo
float Kp = 18.6, Ki = 0.0, Kd = 1.575;  //0.012 5
float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float I_max = -10;  // ค่าขีดจำกัดสูงสุดสำหรับ I
float I_min = 10;   // ค่าขีดจำกัดต่ำสุดสำหรับ I
float previous_error = 0;
float previous_D = 0;  // เก็บค่า D ก่อนหน้าเพื่อใช้ใน low-pass filter
float alpha = 0.1;     // ค่าคงที่สำหรับ low-pass filter (ระหว่าง 0 ถึง 1)
int sensorValues[5];   // ตัวแปรเก็บค่าที่อ่านจากเซ็นเซอร์
int digitalValues[5];  // ตัวแปรเก็บค่าที่แสดงเป็น digital (0 หรือ 1)
int initial_moter_speed = 80;

unsigned long previousMillis = 0;  // ตัวแปรสำหรับเก็บเวลา
unsigned long previousTime = 0;    // ตัวแปรสำหรับเก็บเวลา
bool stop = false;
bool slow = false;
// const long interval = 2000;        // เวลาหน่วง (2000 มิลลิวินาที)

void read_sensor_value(void);
void calculate_pid(void);
void motor_control(void);

#define enLeft 6     //enLeftble1 L293 Pin enLeft
#define leftFront 8  //Motor1  L293 Pin leftFront
#define leftBack 9   //Motor1  L293 Pin leftBack

#define enRight 5      //enLeftble2 L293 Pin enRight
#define rightFront 10  //Motor2  L293 Pin leftFront
#define rightBack 11   //Motor2  L293 Pin leftFBack

void setup() {
  Serial.begin(9600);

  pinMode(enLeft, OUTPUT);
  pinMode(leftFront, OUTPUT);
  pinMode(leftBack, OUTPUT);

  pinMode(enRight, OUTPUT);
  pinMode(rightFront, OUTPUT);
  pinMode(rightBack, OUTPUT);

  pinMode(trigPin, OUTPUT);  // ตั้งค่า Trig เป็น OUTPUT
  pinMode(echoPin, INPUT);   // ตั้งค่า Echo เป็น INPUT
}

int detectFlashes() {
  int flashCount = 0;
  unsigned long startTime = millis();  // เก็บเวลาที่เริ่มต้นตรวจจับแฟลช
  int threshold = 400;                 // ค่าความเข้มแสงที่บ่งบอกว่ามีแฟลช (ปรับตามความเหมาะสม)
  int ldrValue, lastLdrValue;
  bool flashActive = false;
  unsigned long lastFlashTime = 0;  // เวลาเมื่อแฟลชถูกตรวจจับครั้งล่าสุด
  int debounceDelay = 300;          // หน่วงเวลาหลังตรวจจับแฟลช (300ms ป้องกันการตรวจจับซ้ำ)

  lastLdrValue = analogRead(photoResistorPin);  // อ่านค่าเริ่มต้นจาก LDR

  while (millis() - startTime < 5000) {       // รอการตรวจจับแฟลชเป็นเวลา 5 วินาที
    ldrValue = analogRead(photoResistorPin);  // อ่านค่าปัจจุบันจาก LDR

    // ตรวจจับการเปิดแฟลชจากการที่ค่าความเข้มแสงลดลงต่ำกว่า threshold (มีแฟลช)
    if (ldrValue < threshold && !flashActive && millis() - lastFlashTime > debounceDelay) {
      flashActive = true;  // ตั้งค่าว่ามีแฟลชเปิดอยู่
      flashCount++;
      Serial.println("Flash detected!");
      lastFlashTime = millis();  // เก็บเวลาที่ตรวจจับแฟลช
    }
    // ตรวจจับการปิดแฟลช (ค่าความเข้มแสงกลับมาสูงกว่า threshold)
    else if (ldrValue >= threshold && flashActive) {
      flashActive = false;  // ตั้งค่าว่าแฟลชปิดแล้ว
    }

    lastLdrValue = ldrValue;  // เก็บค่าล่าสุดไว้เพื่อเปรียบเทียบในรอบถัดไป
  }

  return flashCount;
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
  distance = duration * 0.034 / 2;

  int sensorValue = analogRead(photoResistorPin);
  Serial.println(sensorValue);
  // Serial.print(distance);
  // Serial.println(" cm");
  if (distance <= 20 && distance > 5) {
    Serial.println("SLOW");
    slow = true;
  }
  if (distance <= 5) {
    Serial.println("STOP");
    stop = true;
  } else {
    read_sensor_value();
  }
  calculate_pid();
  motor_control();
}

void read_sensor_value() {
  sensorValues[0] = analogRead(A0);  // อ่านค่าจากเซ็นเซอร์ IR
  sensorValues[1] = analogRead(A1);  // อ่านค่าจากเซ็นเซอร์ IR
  sensorValues[2] = analogRead(A2);  // อ่านค่าจากเซ็นเซอร์ IR
  sensorValues[3] = analogRead(A3);  // อ่านค่าจากเซ็นเซอร์ IR
  sensorValues[4] = analogRead(A4);  // อ่านค่าจากเซ็นเซอร์ IR

  for (int i = 0; i < 5; i++) {
    // ปรับค่า analog เป็น digital ตามเงื่อนไข
    if (sensorValues[i] >= 600) {
      digitalValues[i] = 0;  // digital = 0 สำหรับพื้นที่สีขาว
    } else if (sensorValues[i] <= 599) {
      digitalValues[i] = 1;  // digital = 1 สำหรับพื้นที่สีดำ
    }
  }

  for (int i = 0; i < 5; i++) {
    Serial.print(sensorValues[i]);
    Serial.print("\t");
  }
  Serial.println();

  if ((digitalValues[4] == 1) && (digitalValues[3] == 1) && (digitalValues[2] == 1) && (digitalValues[1] == 1) && (digitalValues[0] == 1)) {
    Serial.println("CarStop");
    stop = true;
    analogWrite(enLeft, 90);
    analogWrite(enRight, 90);
    digitalWrite(leftFront, LOW);
    digitalWrite(leftBack, LOW);
    digitalWrite(rightFront, LOW);
    digitalWrite(rightBack, LOW);

    Serial.println("Intersection detected. Waiting for flash signal...");

    // รอการตรวจจับแฟลช
    int flashes = detectFlashes();

    if (flashes == 1) {
      Serial.println("Turning left based on 1 flash.");
      digitalWrite(leftFront, LOW);
      digitalWrite(leftBack, LOW);
      digitalWrite(rightFront, HIGH);
      digitalWrite(rightBack, LOW);
      delay(1750);  // รอให้เลี้ยวเสร็จ
    } else if (flashes >= 2) {
      Serial.println("Turning right based on 2 flashes.");
      digitalWrite(leftFront, HIGH);
      digitalWrite(leftBack, LOW);
      digitalWrite(rightFront, LOW);
      digitalWrite(rightBack, LOW);
      delay(1750);  // รอให้เลี้ยวเสร็จ
    }
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 0) && (digitalValues[2] == 0) && (digitalValues[1] == 0) && (digitalValues[0] == 1)) {
    Serial.println("Case-4");
    error = -4;
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 0) && (digitalValues[2] == 0) && (digitalValues[1] == 1) && (digitalValues[0] == 1)) {
    Serial.println("Case-3");
    error = -3;
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 0) && (digitalValues[2] == 0) && (digitalValues[1] == 1) && (digitalValues[0] == 0)) {
    Serial.println("Case-2");
    error = -2;
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 0) && (digitalValues[2] == 1) && (digitalValues[1] == 1) && (digitalValues[0] == 0)) {
    Serial.println("TurnRight");
    error = -1;
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 0) && (digitalValues[2] == 1) && (digitalValues[1] == 0) && (digitalValues[0] == 0)) {
    Serial.println("Go");
    error = 0;
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 1) && (digitalValues[2] == 1) && (digitalValues[1] == 0) && (digitalValues[0] == 0)) {
    Serial.println("TurnLeft");
    error = 1;
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 1) && (digitalValues[2] == 0) && (digitalValues[1] == 0) && (digitalValues[0] == 0)) {
    Serial.println("Case2");
    error = 2;
  } else if ((digitalValues[4] == 1) && (digitalValues[3] == 1) && (digitalValues[2] == 0) && (digitalValues[1] == 0) && (digitalValues[0] == 0)) {
    Serial.println("Case3");
    error = 3;
  } else if ((digitalValues[4] == 1) && (digitalValues[3] == 0) && (digitalValues[2] == 0) && (digitalValues[1] == 0) && (digitalValues[0] == 0)) {
    Serial.println("Case4");
    error = 4;
  } else if ((digitalValues[4] == 1) && (digitalValues[3] == 1) && (digitalValues[2] == 1) && (digitalValues[1] == 0) && (digitalValues[0] == 0)) {
    Serial.println("Case5");  // 90
    error = 5;
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 0) && (digitalValues[2] == 1) && (digitalValues[1] == 1) && (digitalValues[0] == 1)) {
    Serial.println("Case-5");  // 90
    error = -5;
  } else if (digitalValues[0] == 1) {
    Serial.println("Case-6");
    error = -6;
  } else if (digitalValues[4] == 1) {
    Serial.println("Case6");
    error = 6;
  }
}

void calculate_pid() {
  P = error;
  unsigned long currentTime = millis();
  unsigned long deltaTime = currentTime - previousTime;
  if (deltaTime == 0) deltaTime = 1;  // ป้องกันการหารด้วยศูนย์
  I += (error * deltaTime);
  // จำกัดค่า I ไม่ให้สูงหรือต่ำเกินไป
  I = constrain(I, I_min, I_max);
  if (error == 0) {
    I = 0;
  }
  // kp น้อย หลุดโค้ง kp มาก เลี้ยวเยอะ ส่ายมาก kd ใช้ต้านถ้า kp เลี้ยวมากไป ดูค่า error ki ทำให้รถวิ่งเข้าใกล้ 0
  // คำนวณค่า Derivative term
  D = (error - previous_error) / deltaTime;

  // ใช้ Low-pass filter เพื่อลด noise ในค่า D
  D = alpha * D + (1 - alpha) * previous_D;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  previousTime = currentTime;
  previous_error = error;
  previous_D = D;
}

void motor_control() {
  float left_moter_speed, right_moter_speed;
  if (slow) {
    left_moter_speed = 80 - PID_value;
    right_moter_speed = 80 + PID_value;
    slow = false;
  } else {
    left_moter_speed = initial_moter_speed - PID_value;
    right_moter_speed = initial_moter_speed + PID_value;
  }

  left_moter_speed = constrain(left_moter_speed, 0, 255);
  right_moter_speed = constrain(right_moter_speed, 0, 255);

  analogWrite(enLeft, left_moter_speed);
  analogWrite(enRight, right_moter_speed);

  if (stop) {
    digitalWrite(leftFront, LOW);
    digitalWrite(leftBack, LOW);
    digitalWrite(rightFront, LOW);
    digitalWrite(rightBack, LOW);
    stop = false;
  } else {
    digitalWrite(leftFront, HIGH);
    digitalWrite(leftBack, LOW);
    digitalWrite(rightFront, HIGH);
    digitalWrite(rightBack, LOW);
  }
}
