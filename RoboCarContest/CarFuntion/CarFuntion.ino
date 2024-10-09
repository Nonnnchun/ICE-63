// How 2 Use ??!



// void loop() {
//   followSharpTurn();
//   followZebraCrossing();
//   checkIntersection();
//   checkObstacle();
// }



// // -------------------------Stage 1 : Sharp Turn Use IR Sensor Control----------------------------------------

// void followSharpTurn() {
//   // อ่านค่าจากเซ็นเซอร์ IR
//   for (int i = 0; i < 5; i++) {
//     sensorValues[i] = analogRead(sensorPins[i]);
//     digitalValues[i] = (sensorValues[i] <= 700) ? 1 : 0;
//   }

//   // กรณีเจอทางโค้ง (เช่น เมื่อเซ็นเซอร์ด้านขวาตรวจเจอเส้นสีดำ)
//   if (digitalValues[0] == 1) {
//     // โค้งซ้าย
//     digitalWrite(inA, HIGH);
//     digitalWrite(inB, LOW);
//     analogWrite(enA, 150);  // ลดความเร็วข้างขวา
//     analogWrite(enB, 255);  // ข้างซ้ายวิ่งปกติ
//   } else if (digitalValues[4] == 1) {
//     // โค้งขวา
//     digitalWrite(inD, HIGH);
//     digitalWrite(inC, LOW);
//     analogWrite(enA, 255);  // ข้างขวาวิ่งปกติ
//     analogWrite(enB, 150);  // ลดความเร็วข้างซ้าย
//   } else {
//     // วิ่งตรง
//     moveForward(255);
//   }
// }


// // ---------------------------Stage : 2 Zebra Cross (Black/WHite) Use IR Sensor-----------------------------

// void followZebraCrossing() {
//   // อ่านค่าเซ็นเซอร์ IR
//   for (int i = 0; i < 5; i++) {
//     sensorValues[i] = analogRead(sensorPins[i]);
//     digitalValues[i] = (sensorValues[i] <= 700) ? 1 : 0;
//   }

//   // ตรวจหาทางม้าลาย (ดำสลับขาว)
//   if (digitalValues[2] == 1) {
//     // ดำตรงกลาง -> ขับตรง
//     moveForward(255);
//   } else if (digitalValues[2] == 0) {
//     // เจอสีขาว -> ขับต่อไปอีกเล็กน้อย
//     moveForward(255);
//     delay(500);  // ขับตรงไปอีกเล็กน้อย
//     // หาทางสีดำใหม่
//     while (digitalValues[2] == 0) {
//       for (int i = 0; i < 5; i++) {
//         sensorValues[i] = analogRead(sensorPins[i]);
//         digitalValues[i] = (sensorValues[i] <= 700) ? 1 : 0;
//       }
//     }
//   }
// }


// //------------------------------Stage : 3 Left Or Right Use LDR Sensor--------------------------------------

// void checkIntersection() {
//   int flashCount = 0;
//   stopCar();

//   unsigned long startTime = millis();
//   bool flashDetected = false;

//   // รอแฟลชครั้งแรก
//   while (millis() - startTime < 5000) {
//     if (isFlashDetected()) {
//       flashDetected = true;
//       flashCount++;
//       delay(500);  // ป้องกันการนับแฟลชซ้ำ
//     }
//   }

//   if (flashDetected) {
//     // รอ 5 วิ ว่าจะมีแฟลชเพิ่มหรือไม่
//     delay(5000);

//     if (isFlashDetected()) {
//       flashCount++;  // นับแฟลชอีกครั้ง
//     }
//   }

//   // ตรวจสอบจำนวนแฟลชและเลือกทิศทาง
//   if (flashCount == 1) {
//     turnLeft();
//   } else if (flashCount == 2) {
//     turnRight();
//   }
// }

// void turnLeft() {
//   // โค้ดสำหรับเลี้ยวซ้าย
//   digitalWrite(inA, HIGH);
//   digitalWrite(inB, LOW);
//   analogWrite(enA, 150);  // ลดความเร็ว
//   analogWrite(enB, 255);  // เลี้ยวซ้าย
// }

// void turnRight() {
//   // โค้ดสำหรับเลี้ยวขวา
//   digitalWrite(inD, HIGH);
//   digitalWrite(inC, LOW);
//   analogWrite(enA, 255);  // เลี้ยวขวา
//   analogWrite(enB, 150);  // ลดความเร็ว
// }


// // ------------------------------------stage : 4 Y Block My way?-------------------------------------------
// void checkObstacle() {
//   long distance = getDistance();

//   if (distance < 20) {  // ระยะห่างน้อยกว่า 20cm
//     stopCar();

//     // รอจนกว่าสิ่งกีดขวางจะถูกเอาออก
//     while (getDistance() < 20) {
//       delay(100);  // ตรวจสอบทุก 100 ms
//     }

//     // วิ่งต่อเมื่อไม่มีสิ่งกีดขวางแล้ว
//     moveForward(255);
//   }
// }

// // ---------------------------- Move Function ---------------------------------------------------------------

// void moveForward(int speed) {
//   digitalWrite(inA, HIGH);
//   digitalWrite(inB, LOW);
//   analogWrite(enA, speed);

//   digitalWrite(inD, HIGH);
//   digitalWrite(inC, LOW);
//   analogWrite(enB, speed);
// }


// void turnLeft() {
//   digitalWrite(inA, HIGH);
//   digitalWrite(inB, LOW);
//   analogWrite(enA, 100);  // ลดความเร็วข้างขวา

//   digitalWrite(inD, LOW);
//   digitalWrite(inC, HIGH);
//   analogWrite(enB, 50);   // หยุดหรือหมุนข้างซ้าย
// }


// void turnRight() {
//   digitalWrite(inA, LOW);
//   digitalWrite(inB, HIGH);
//   analogWrite(enA, 50);   // หยุดหรือหมุนข้างขวา

//   digitalWrite(inD, HIGH);
//   digitalWrite(inC, LOW);
//   analogWrite(enB, 100);  // ลดความเร็วข้างซ้าย
// }


// void stopCar() {
//   digitalWrite(inA, LOW);
//   digitalWrite(inB, LOW);
//   digitalWrite(inC, LOW);
//   digitalWrite(inD, LOW);
// }


// -----------------------------------Test : 1---------------------------------------------------------------

const int sensorPins[4] = { A0, A1, A2, A3 };  // ขาเชื่อมต่อของเซ็นเซอร์ IR
int sensorValues[4];                           // ตัวแปรเก็บค่าที่อ่านจากเซ็นเซอร์
int digitalValues[4];                          // ตัวแปรเก็บค่าที่แสดงเป็น digital (0 หรือ 1)

//--------------------IR Sensor------------------------------------------------

const int photoResistorPin = A5;  // ขาเชื่อมต่อของ photoresistor
// const int ledPin = 4;             // ขาเชื่อมต่อของ LED

//--------------------LDR Sensor-----------------------------------------------

const int trigPin = 12;  // ขา Trig
const int echoPin = 13;  // ขา Echo

//----------------Ultra Sonic Module--------------------------------------------

// motor one <<ซ้าย>>
int enA = 6;
int inA = 9;  //ไปหน้า
int inB = 8;  //ไปหลัง

// motor two <<ขวา>>
int enB = 5;
int inC = 11;  //ไปหน้า
int inD = 10;  //ไปหลัง

//-------------------------RoBo Car--------------------------------------------

void setup() {
  Serial.begin(9600);  // เริ่มต้น Serial Monitor
  // pinMode(ledPin, OUTPUT);   // ตั้งค่า LED เป็น OUTPUT
  pinMode(trigPin, OUTPUT);  // ตั้งค่า Trig เป็น OUTPUT
  pinMode(echoPin, INPUT);   // ตั้งค่า Echo เป็น INPUT

  // ตั้งค่าขาเซ็นเซอร์ IR เป็น INPUT
  for (int i = 0; i < 4; i++) {
    pinMode(sensorPins[i], INPUT);
  }

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

  // แสดงผลระยะทางใน Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  //----------------Ultra Sonic Module-----------------------------------------

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
  for (int i = 0; i < 4; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);  // อ่านค่าจากเซ็นเซอร์ IR

    // ปรับค่า analog เป็น digital ตามเงื่อนไข
    if (sensorValues[i] >= 700) {
      digitalValues[i] = 0;  // digital = 0 สำหรับพื้นที่สีขาว
    } else if (sensorValues[i] <= 699) {
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

  // เช็คเงื่อนไข A0 และ A4 เป็น 0 และ A1, A2, A3 เป็น 1
  if (digitalValues[0] == 0 && digitalValues[3] == 0 && digitalValues[1] == 1 && digitalValues[2] == 1) {
    // ถ้าอยู่บนเส้นสีดำ -> วิ่งตรง
    moveForward(100);
  } else if (digitalValues[0] == 1 && digitalValues[3] == 1 && digitalValues[1] == 1 && digitalValues[2] == 1) {
    // ถ้าอยู่บนเส้นสีดำ -> วิ่งตรง
    moveForward(100);
  }

  // ถ้าหลุดเส้น -> หาทางกลับสู่เส้น (คุณสามารถปรับทิศทางที่ต้องการได้)
  else if (digitalValues[0] == 0 && digitalValues[3] == 1 && digitalValues[1] == 1 && digitalValues[2] == 1) {
    // เซ็นเซอร์ซ้ายเจอสีดำ -> เลี้ยวซ้าย
    turnRight();

  } else if (digitalValues[0] == 1 && digitalValues[3] == 0 && digitalValues[1] == 1 && digitalValues[2] == 1) {
    // เซ็นเซอร์ขวาเจอสีดำ -> เลี้ยวขวา
    turnLeft();

  } else if (digitalValues[0] == 0 && digitalValues[3] == 1 && digitalValues[1] == 0 && digitalValues[2] == 1) {
    // เซ็นเซอร์ขวาเจอสีดำ -> เลี้ยวขวา
    turnLeft();

  } else if (digitalValues[0] == 1 && digitalValues[3] == 0 && digitalValues[1] == 1 && digitalValues[2] == 0) {
    // เซ็นเซอร์ซ้ายเจอสีดำ -> เลี้ยวซ้าย
    turnRight();
  } else {
    // หยุดถ้าหลุดเส้นทั้งหมด
    stopCar();
  }
  delay(10);  // รอ 100 มิลลิวินาที
}



void moveForward(int speed) {
  digitalWrite(inA, HIGH);
  digitalWrite(inB, LOW);
  analogWrite(enA, speed);

  digitalWrite(inD, LOW);
  digitalWrite(inC, HIGH);
  analogWrite(enB, speed);
}

void turnRight() {
  digitalWrite(inA, HIGH);
  digitalWrite(inB, LOW);
  analogWrite(enA, 100);  // ลดความเร็วข้างขวา

}

void turnLeft() {


  digitalWrite(inD, LOW);
  digitalWrite(inC, HIGH);
  analogWrite(enB, 100);  // ลดความเร็วข้างซ้าย
}

void stopCar() {
  digitalWrite(inA, LOW);
  digitalWrite(inB, LOW);
  digitalWrite(inC, LOW);
  digitalWrite(inD, LOW);
}
