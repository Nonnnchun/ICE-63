// Define sensor pins and motor control pins
const int sensorPins[4] = { A0, A1, A2, A3 };  // IR sensor pins
int sensorValues[4];                           // Store sensor readings
int digitalValues[4];                          // Store digital values (0 or 1)

const int photoResistorPin = A5;  // Photoresistor (LDR) pin for flash detection

// Ultrasonic sensor pins
const int trigPin = 12;
const int echoPin = 13;

// Motor control pins
int enA = 6;
int inA = 9;
int inB = 8;
int enB = 5;
int inC = 11;
int inD = 10;

void setup() {
  Serial.begin(9600);  // Start Serial Monitor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set IR sensor pins to input
  for (int i = 0; i < 4; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  // Set motor control pins to output
  pinMode(enA, OUTPUT);
  pinMode(inA, OUTPUT);
  pinMode(inB, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(inC, OUTPUT);
  pinMode(inD, OUTPUT);
}

void loop() {
  followSharpTurn();       // Stage 1: Handle sharp turns
  followZebraCrossing();   // Stage 2: Handle zebra crossings
  checkIntersection();     // Stage 3: Handle intersections with flash signals
  checkObstacle();         // Stage 4: Handle obstacle detection
}

// -------------------------Stage 1 : Sharp Turn Use IR Sensor Control----------------------------------------

void followSharpTurn() {
  readIRSensors();  // Read IR sensor values

  // Sharp turn detection (e.g., sensor detects sharp turn on the right)
  if (digitalValues[0] == 1) {
    // Turn left
    turnLeft();
  } else if (digitalValues[3] == 1) {
    // Turn right
    turnRight();
  } else {
    // Move straight
    moveForward(100);
  }
}

// ---------------------------Stage 2 : Zebra Cross (Black/White) Use IR Sensor-----------------------------

void followZebraCrossing() {
  readIRSensors();  // Read IR sensor values

  // Detect zebra crossing pattern (black-white)
  if (digitalValues[2] == 1) {
    // Black detected -> Move forward
    moveForward(100);
  } else if (digitalValues[2] == 0) {
    // White detected -> Move forward briefly and search for black again
    moveForward(100);
    delay(500);
    // Continue until black is found again
    while (digitalValues[2] == 0) {
      readIRSensors();
    }
  }
}

// ------------------------------Stage 3: Handle Flash Signals at Intersections------------------------------

void checkIntersection() {
  int flashCount = 0;
  stopCar();

  unsigned long startTime = millis();
  bool flashDetected = false;

  // Wait for the first flash
  while (millis() - startTime < 5000) {
    if (isFlashDetected()) {
      flashDetected = true;
      flashCount++;
      delay(500);  // Prevent duplicate flash counting
    }
  }

  if (flashDetected) {
    // Wait for 5 seconds to check for additional flashes
    delay(5000);

    if (isFlashDetected()) {
      flashCount++;  // Count another flash
    }
  }

  // Decide direction based on flash count
  if (flashCount == 1) {
    turnLeft();  // One flash -> Turn left
  } else if (flashCount == 2) {
    turnRight();  // Two flashes -> Turn right
  }
}

bool isFlashDetected() {
  int sensorValue = analogRead(photoResistorPin);
  return (sensorValue < 700);  // Adjust based on environment lighting
}

// -----------------------------------Stage 4: Obstacle Detection--------------------------------------------

void checkObstacle() {
  long distance = getDistance();

  if (distance < 20) {  // If obstacle is within 20 cm
    stopCar();

    // Wait until the obstacle is removed
    while (getDistance() < 20) {
      delay(100);  // Check every 100 ms
    }

    // Continue when the obstacle is removed
    moveForward(100);
  }
}

long getDistance() {
  // Clear trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echoPin
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;  // Convert to distance (cm)
}

// ---------------------------- Helper Functions ------------------------------------------------------------

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
  analogWrite(enA, 100);  // Slow down right side

  digitalWrite(inD, HIGH);
  digitalWrite(inC, LOW);
  analogWrite(enB, 50);   // Slow down left side
}

void turnLeft() {
  digitalWrite(inA, LOW);
  digitalWrite(inB, HIGH);
  analogWrite(enA, 50);   // Slow down right side

  digitalWrite(inD, LOW);
  digitalWrite(inC, HIGH);
  analogWrite(enB, 100);  // Slow down left side
}

void stopCar() {
  digitalWrite(inA, LOW);
  digitalWrite(inB, LOW);
  digitalWrite(inC, LOW);
  digitalWrite(inD, LOW);
}

void readIRSensors() {
  for (int i = 0; i < 4; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);  // Read from IR sensors

    // Convert analog to digital
    digitalValues[i] = (sensorValues[i] <= 700) ? 1 : 0;
  }

  // Display digital values (for debugging)
  Serial.print("Digital values: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(digitalValues[i]);
    Serial.print("\t");
  }
  Serial.println();
}
