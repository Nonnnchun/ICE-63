
//----------------------------------------------------------Tester Ep.1000000--------------------------------------------------------------

// Arduino Line Follower Robot Code
float Kp = 18.312, Ki = 0.012, Kd = 0.15;  //0.012 5
float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
// float I_max = 50;   // ค่าขีดจำกัดสูงสุดสำหรับ I
// float I_min = -50;  // ค่าขีดจำกัดต่ำสุดสำหรับ I
float previous_error = 0;
int sensorValues[5];   // ตัวแปรเก็บค่าที่อ่านจากเซ็นเซอร์
int digitalValues[5];  // ตัวแปรเก็บค่าที่แสดงเป็น digital (0 หรือ 1)
int initial_moter_speed = 80;

unsigned long previousMillis = 0;  // ตัวแปรสำหรับเก็บเวลา
// const long interval = 2000;        // เวลาหน่วง (2000 มิลลิวินาที)

void read_sensor_value(void);
void calculate_pid(void);
void motor_control(void);
void stop_car(void);

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

  // digitalWrite(enLeft, HIGH);
  // digitalWrite(enRight, HIGH);

  // เริ่มการตั้งค่าเริ่มต้น
  // Serial.println("Enter initial motor speed (0-255):");
}

void loop() {

  read_sensor_value();
  calculate_pid();
  motor_control();
  monitor_value();
  if ((digitalValues[4] == 1) && (digitalValues[3] == 1) && (digitalValues[2] == 1) && (digitalValues[1] == 1) && (digitalValues[0] == 1)) {
    stop_car();
  }
  // } else if ((digitalValues[4] == 0) && (digitalValues[3] == 0) && (digitalValues[2] == 0) && (digitalValues[1] == 0) && (digitalValues[0] == 0)) {
  //   //ไปข้างหน้าต่อ 1 วิ ถ้าไม่เจออะไรให้ถอยหลังกลับมาที่เดิม (ระยะทางเท่ากับที่เดินตอนอยู่บนสีขาว)
  //   forwardOneSec();
  //   // delay(1000);       // รอ 1 วินาที
  //   stop_car();        // หยุดรถ
  //   // delay(500);        // รอครึ่งวินาทีก่อนที่จะถอยหลัง
  //   backwardOneSec();  // ถอยหลัง 1 วินาที
  // }
}

void read_sensor_value() {
  sensorValues[0] = analogRead(A0);  // อ่านค่าจากเซ็นเซอร์ IR
  sensorValues[1] = analogRead(A1);  // อ่านค่าจากเซ็นเซอร์ IR
  sensorValues[2] = analogRead(A2);  // อ่านค่าจากเซ็นเซอร์ IR
  sensorValues[3] = analogRead(A3);  // อ่านค่าจากเซ็นเซอร์ IR
  sensorValues[4] = analogRead(A4);  // อ่านค่าจากเซ็นเซอร์ IR

  for (int i = 0; i < 5; i++) {
    // ปรับค่า analog เป็น digital ตามเงื่อนไข
    if (sensorValues[i] >= 750) {
      digitalValues[i] = 0;  // digital = 0 สำหรับพื้นที่สีขาว
    } else if (sensorValues[i] <= 749) {
      digitalValues[i] = 1;  // digital = 1 สำหรับพื้นที่สีดำ
    }
  }

  // for (int i = 0; i < 5; i++) {
  //   Serial.print(digitalValues[i]);
  //   Serial.print("\t");
  // }
  // Serial.println();

  if ((digitalValues[4] == 1) && (digitalValues[3] == 1) && (digitalValues[2] == 1) && (digitalValues[1] == 1) && (digitalValues[0] == 1)) {
    stop_car();
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 0) && (digitalValues[2] == 0) && (digitalValues[1] == 0) && (digitalValues[0] == 1)) {
    error = -4;
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 0) && (digitalValues[2] == 0) && (digitalValues[1] == 1) && (digitalValues[0] == 1)) {
    error = -3;
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 0) && (digitalValues[2] == 0) && (digitalValues[1] == 1) && (digitalValues[0] == 0)) {
    error = -2;
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 0) && (digitalValues[2] == 1) && (digitalValues[1] == 1) && (digitalValues[0] == 0)) {
    error = -1;
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 0) && (digitalValues[2] == 1) && (digitalValues[1] == 0) && (digitalValues[0] == 0)) {
    error = 0;
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 1) && (digitalValues[2] == 1) && (digitalValues[1] == 0) && (digitalValues[0] == 0)) {
    error = 1;
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 1) && (digitalValues[2] == 0) && (digitalValues[1] == 0) && (digitalValues[0] == 0)) {
    error = 2;
  } else if ((digitalValues[4] == 1) && (digitalValues[3] == 1) && (digitalValues[2] == 0) && (digitalValues[1] == 0) && (digitalValues[0] == 0)) {
    error = 3;
  } else if ((digitalValues[4] == 1) && (digitalValues[3] == 0) && (digitalValues[2] == 0) && (digitalValues[1] == 0) && (digitalValues[0] == 0)) {
    error = 4;
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 0) && (digitalValues[2] == 1) && (digitalValues[1] == 0) && (digitalValues[0] == 1)) {
    if ((digitalValues[4] == 0) && (digitalValues[3] == 0) && (digitalValues[2] == 1) && (digitalValues[1] == 1) && (digitalValues[0] == 1)) {
      error = -6;
    }
  } else if ((digitalValues[4] == 1) && (digitalValues[3] == 0) && (digitalValues[2] == 1) && (digitalValues[1] == 0) && (digitalValues[0] == 0)) {
    if ((digitalValues[4] == 1) && (digitalValues[3] == 1) && (digitalValues[2] == 1) && (digitalValues[1] == 0) && (digitalValues[0] == 0)) {
      error = -6;
    }
  } else if ((digitalValues[4] == 1) && (digitalValues[3] == 1) && (digitalValues[2] == 1) && (digitalValues[1] == 0) && (digitalValues[0] == 0)) {
    error = 5;
  } else if ((digitalValues[4] == 0) && (digitalValues[3] == 0) && (digitalValues[2] == 1) && (digitalValues[1] == 1) && (digitalValues[0] == 1)) {
    error = -5;
  }
}

void calculate_pid() {

  P = error;
  I += error;  // ใช้ค่า error ปัจจุบันในการคำนวณ I

  // จำกัดค่า I ไม่ให้สูงหรือต่ำเกินไป
  // I = constrain(I, I_min, I_max);

  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  previous_error = error;
}

void motor_control() {
  float left_moter_speed = initial_moter_speed - PID_value;
  float right_moter_speed = initial_moter_speed + PID_value;

  left_moter_speed = constrain(left_moter_speed, 0, 255);
  right_moter_speed = constrain(right_moter_speed, 0, 255);

  // Serial.print("left_moter_speed = ");
  // Serial.println(left_moter_speed+18);
  // Serial.print("right_moter_speed = ");
  // Serial.println(right_moter_speed);

  analogWrite(enLeft, left_moter_speed);
  analogWrite(enRight, right_moter_speed);

  digitalWrite(leftFront, HIGH);
  digitalWrite(leftBack, LOW);
  digitalWrite(rightFront, HIGH);
  digitalWrite(rightBack, LOW);
  // delay(90);
}

// void set_initial_speed(int speed) {
//   if (speed >= 0 && speed <= 255) {
//     initial_moter_speed = speed;
//     Serial.print("Initial motor speed set to: ");
//     Serial.println(initial_moter_speed);
//   } else {
//     Serial.println("Invalid speed! Please enter a value between 0 and 255.");
//     initial_moter_speed = constrain(initial_moter_speed, 0, 255);  // ตรวจสอบให้แน่ใจว่าอยู่ในขอบเขต
//   }
// }

void stop_car() {
  digitalWrite(leftFront, LOW);
  digitalWrite(leftBack, LOW);
  digitalWrite(rightFront, LOW);
  digitalWrite(rightBack, LOW);
}

void forwardOneSec() {
  analogWrite(enLeft, 75);
  analogWrite(enRight, 95);
  digitalWrite(leftFront, HIGH);
  digitalWrite(leftBack, LOW);
  digitalWrite(rightFront, HIGH);
  digitalWrite(rightBack, LOW);
  delay(1000);  // ขับไปข้างหน้า 1 วินาที
  stop_car();   // หยุดรถ
}

void backwardOneSec() {
  analogWrite(enLeft, 75);
  analogWrite(enRight, 95);
  digitalWrite(leftFront, LOW);
  digitalWrite(leftBack, HIGH);
  digitalWrite(rightFront, LOW);
  digitalWrite(rightBack, HIGH);
  delay(1000);  // ถอยหลัง 1 วินาที
  stop_car();   // หยุดรถ
}

void monitor_value() {
  // for (int i = 0; i < 5; i++) {
  //   Serial.print(digitalValues[i]);
  //   Serial.print("\t");
  // }
  // Serial.println();

  // Serial.println();
  // Serial.print("Error = ");
  // Serial.println(error);
  // Serial.print("PID_value = ");
  Serial.println(Kp);
  Serial.println(Ki);
  Serial.println(Kd);
  Serial.println(PID_value);
  // // Serial.println(P);
  // // Serial.println(I);
  // // Serial.println(D);
  Serial.println(initial_moter_speed);

  // delay(2000);
}
