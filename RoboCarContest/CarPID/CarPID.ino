#define enRight 6     // enRightble1 L293 Pin enRight
#define rightFront 9  // Motor1 L293 Pin rightFront
#define rightBack 8   // Motor1 L293 Pin rightBack
#define leftFront 11  // Motor2 L293 Pin rightFront
#define leftBack 10   // Motor2 L293 Pin rightBack
#define enLeft 5      // enRightble2 L293 Pin enLeft

const int sensorPins[4] = { A0, A1, A2, A3 };  // IR sensor pins
int sensorValues[4];                           // Sensor readings
int digitalValues[4];                          // Digital representation (0 or 1)

// PID variables
double Setpoint = 0;  // Target position (center)
double Input, Output;
double Kp = 2.0, Ki = 0.0, Kd = 1.0;  // PID coefficients
double integral = 0, lastError = 0;
int previousError = 0, P, I, D;
float Pvalue, Ivalue, Dvalue;
int lfspeed = 100;  // Speed of the robot

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 4; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  pinMode(enRight, OUTPUT);
  pinMode(rightFront, OUTPUT);
  pinMode(rightBack, OUTPUT);
  pinMode(leftFront, OUTPUT);
  pinMode(leftBack, OUTPUT);
  pinMode(enLeft, OUTPUT);

  digitalWrite(enRight, HIGH);
  digitalWrite(enLeft, HIGH);
}

void loop() {
  // Read sensor values
  for (int i = 0; i < 4; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);
    digitalValues[i] = (sensorValues[i] >= 110) ? 0 : 1;  // 0 for white, 1 for black
  }

  // Calculate sensor position
  int pos = (digitalValues[0] * -3) + (digitalValues[1] * -1) + (digitalValues[2] * 1) + (digitalValues[3] * 3);
  Input = pos;  // Use position as Input for PID

  // PID calculation
  PID_Linefollow(Input);

  // Control logic based on sensor values
  if ((digitalValues[0] == 0) && (digitalValues[3] == 0)) {
    setMotorSpeed(100, 100);  // Both sensors on white
  } else if ((digitalValues[0] == 1) && (digitalValues[3] == 0)) {
    turnRight();  // Right sensor on black
  } else if ((digitalValues[0] == 0) && (digitalValues[3] == 1)) {
    turnLeft();  // Left sensor on black
  } else if ((digitalValues[0] == 1) && (digitalValues[1] == 1) && (digitalValues[2] == 1) && (digitalValues[3] == 0)) {
    turnRight90();  // Sharp right turn condition
  } else if ((digitalValues[0] == 0) && (digitalValues[1] == 1) && (digitalValues[2] == 1) && (digitalValues[3] == 1)) {
    turnLeft90();  // Sharp left turn condition
  } else if ((digitalValues[0] == 1) && (digitalValues[1] == 1) && (digitalValues[2] == 1) && (digitalValues[3] == 1)) {
    acuteTurn();  // Acute turn right condition
  } else if ((digitalValues[0] == 1) && (digitalValues[3] == 1)) {
    Stop();  // Both sensors on black
  }

  // Print digital values and PID output
  Serial.print("Digital values: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(digitalValues[i]);
    Serial.print("\t");
  }
  Serial.print(" PID Output: ");
  Serial.println(Output);
}

void PID_Linefollow(int error) {
  P = error;
  I = constrain(I + error, -100, 100);  // Control I accumulation
  D = error - previousError;

  Pvalue = Kp * P;
  Ivalue = Ki * I;
  Dvalue = Kd * D;

  float PIDvalue = Pvalue + Ivalue + Dvalue;
  previousError = error;

  int lsp = lfspeed - PIDvalue;
  int rsp = lfspeed + PIDvalue;

  // Control motor speeds
  setMotorSpeed(constrain(lsp, -255, 255), constrain(rsp, -255, 255));
}

void setMotorSpeed(int speedRight, int speedLeft) {
  speedRight = constrain(speedRight, 0, 255);
  speedLeft = constrain(speedLeft, 0, 255);

  analogWrite(enRight, speedRight);
  analogWrite(enLeft, speedLeft);

  digitalWrite(rightFront, HIGH);  // Right Motor forward Pin
  digitalWrite(rightBack, LOW);    // Right Motor backward Pin
  digitalWrite(leftFront, HIGH);   // Left Motor forward Pin
  digitalWrite(leftBack, LOW);     // Left Motor backward Pin
}

void forward() {
  setMotorSpeed(100, 75);
}

void turnRight() {
  digitalWrite(rightFront, HIGH);
  digitalWrite(rightBack, LOW);
  digitalWrite(leftFront, LOW);
  digitalWrite(leftBack, LOW);
  analogWrite(enRight, 150);  // Right motor moves forward
  analogWrite(enLeft, 0);     // Stop left motor
}

void turnLeft() {
  digitalWrite(rightFront, LOW);
  digitalWrite(rightBack, LOW);
  digitalWrite(leftFront, HIGH);
  digitalWrite(leftBack, LOW);
  analogWrite(enRight, 0);   // Stop right motor
  analogWrite(enLeft, 130);  // Left motor moves forward
}

void Stop() {
  digitalWrite(rightFront, LOW);
  digitalWrite(rightBack, LOW);
  digitalWrite(leftFront, LOW);
  digitalWrite(leftBack, LOW);
}

// Add function for 90-degree turn
void turnRight90() {
  digitalWrite(rightFront, LOW);
  digitalWrite(rightBack, HIGH);
  digitalWrite(leftFront, HIGH);
  digitalWrite(leftBack, LOW);
  analogWrite(enRight, 150);   // Stop right motor
  analogWrite(enLeft, 130);  // Left motor moves forward
  delay(500); // Adjust this delay based on your motor speed and desired turn angle
  Stop(); // Stop after completing the turn
}

void turnLeft90() {
  digitalWrite(rightFront, HIGH);
  digitalWrite(rightBack, LOW);
  digitalWrite(leftFront, LOW);
  digitalWrite(leftBack, HIGH);
  analogWrite(enRight, 150);   // Right motor moves forward
  analogWrite(enLeft, 130);      // Stop left motor
  delay(500); // Adjust this delay based on your motor speed and desired turn angle
  Stop(); // Stop after completing the turn
}

void acuteTurn() {
  digitalWrite(rightFront, LOW);
  digitalWrite(rightBack, LOW);
  digitalWrite(leftFront, HIGH);
  digitalWrite(leftBack, LOW);
  analogWrite(enRight, 200);   // Stop right motor
  analogWrite(enLeft, 175);  // Left motor moves forward
  delay(200);

  digitalWrite(rightFront, HIGH);
  digitalWrite(rightBack, LOW);
  digitalWrite(leftFront, LOW);
  digitalWrite(leftBack, LOW);
  analogWrite(enRight, 200);   // Stop right motor
  analogWrite(enLeft, 175);  // Left motor moves forward
}
