#include <SoftwareSerial.h>

const int buttonUpPin = 2;    // up == left
const int buttonDownPin = 3;  // down == right

long interval = 111;  // ความเร็วเริ่มต้นใน Stage 1

bool buttonUpPressed = false;
bool buttonDownPressed = false;

int playerX = 0;
int playerY = 3;

unsigned long startTime = 0;    // เวลาที่เริ่มเกม
unsigned long elapsedTime = 0;  // เวลาที่ผ่านไปในช่วง RUNNING
unsigned long lastUpdateTime = 0;

// ตำแหน่งของสิ่งกีดขวาง
int obstacleX[5];                           // ตำแหน่งแกน X ของก้อนสิ่งกีดขวาง
int obstacleY[5];                           // ตำแหน่งแกน Y ของก้อนสิ่งกีดขวาง
int obstacleWidth[5] = { 1, 1, 1, 1, 1 };   // ความกว้างของสิ่งกีดขวางแต่ละก้อน
int obstacleHeight[5] = { 1, 1, 1, 1, 1 };  // ความสูงของสิ่งกีดขวางแต่ละก้อน

int currentState = 0;  // เริ่มต้นที่สถานะ IDLE


// กำหนดพินสำหรับ SoftwareSerial (RX = 5, TX = 6)
SoftwareSerial mySerial(5, 6);

enum States {
  STATE_IDLE,
  STATE_START,
  STATE_RUNNING,
  STATE_GAME_OVER
};

void setup() {
  pinMode(buttonUpPin, INPUT_PULLUP);
  pinMode(buttonDownPin, INPUT_PULLUP);
  mySerial.begin(4800);  // เริ่มการสื่อสาร SoftwareSerial กับ Arduino ตัวที่ 2
  Serial.begin(4800);    // เปิด Serial Monitor สำหรับตรวจสอบ
}

void loop() {
  // อ่านสถานะของปุ่ม
  buttonUpPressed = (digitalRead(buttonUpPin) == LOW);
  buttonDownPressed = (digitalRead(buttonDownPin) == LOW);

  // if (receivedData.StartWith("GAME_OVER")){
  //   //-------------------------------------------ยังไม่เสร็จ-------------------
  // }
  // ควบคุมการเริ่มเกมจากสถานะ IDLE ไปสู่ RUNNING
  if (currentState == STATE_IDLE) {
    mySerial.println("IDEL");  // ส่งคำว่า "START" ไปแสดงบน Dot Matrix
    Serial.println("ส่งคำว่า IDEL");
    delay(100);
  }

  if (currentState == STATE_IDLE && (buttonUpPressed || buttonDownPressed)) {
    currentState = STATE_RUNNING;
    startTime = millis();       // บันทึกเวลาเริ่มเกม
    mySerial.println("START");  // ส่งคำว่า "START" ไปแสดงบน Dot Matrix
    Serial.println("ส่งคำว่า START");
  }

  // หากอยู่ในสถานะ RUNNING ให้ส่งตำแหน่งผู้เล่นและสถานะ
  if (currentState == STATE_RUNNING) {
    updatePlayerPosition();
    sendPlayerPosition();
    checkGameEnd();  // ตรวจสอบว่าเกมจบหรือไม่
  }

  if (currentState == STATE_GAME_OVER && (buttonUpPressed || buttonDownPressed)) {
    currentState = STATE_RUNNING;
    startTime = millis();       // บันทึกเวลาเริ่มเกม
    mySerial.println("START");  // ส่งคำว่า "START" ไปแสดงบน Dot Matrix
    Serial.println("ส่งคำว่า START");
  }

  delay(100);  // เพิ่ม delay เพื่อไม่ให้ loop ทำงานเร็วเกินไป
}

//---------------------------------------------------------STATE------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------Input Serial-----------------------------------------------------------------------------------------------

void updatePlayerPosition() {
  if (buttonUpPressed && playerY > 0) {  // up == left
    playerY--;
    Serial.println("Left");
  }
  if (buttonDownPressed && playerY < 7) {  // down == right
    playerY++;
    Serial.println("Right");
  }
}

void sendPlayerPosition() {
  String message = "POS:" + String(playerY);
  mySerial.println(message);
  Serial.println("ส่งตำแหน่งผู้เล่น: " + message);  // แสดงใน Serial Monitor
}

void checkGameEnd() {
  // กำหนดให้เกมจบหลังจาก 30 วินาที
  elapsedTime = millis() - startTime;
  if (elapsedTime >= 10000000) {
    currentState = STATE_GAME_OVER;
    mySerial.println("SCORE:" + String(elapsedTime / 1000));  // ส่งคะแนนที่ใช้เวลาในวินาที
    Serial.println("ส่ง SCORE และคะแนน: " + String(elapsedTime / 1000));
  }
}

void sendState() {
  switch (currentState) {
    case STATE_IDLE:
      mySerial.println("IDLE");
      Serial.println("ส่งสถานะ: IDLE");
      break;
    case STATE_START:
      mySerial.println("START");
      Serial.println("ส่งสถานะ: START");
      break;
      case STATE_RUNNING:
      mySerial.println("RUNNING");
      Serial.println("ส่งสถานะ: RUNNING");
      break;
    case STATE_GAME_OVER:
      mySerial.println("GAME_OVER");
      Serial.println("ส่งสถานะ: GAME_OVER");
      break;
  }
}

// ---------------------------------------------------------Bool Die Or Not------------------------------------------------------------------------------------------------

bool checkCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
  return !(x1 + w1 - 1 < x2 || x1 > x2 + w2 - 1 || y1 + h1 - 1 < y2 || y1 > y2 + h2 - 1);
}