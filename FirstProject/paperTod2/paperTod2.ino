#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6);  // RX, TX 

const int buttonUpPin = 2;
const int buttonDownPin = 3;

bool flag = false;
bool flagI = false;

enum GameState { IDLE,
                 RUNNING,
                 GAME_OVER };
GameState currentState = IDLE;

void setup() {
  Serial.begin(19200);
  mySerial.begin(19200); 
  pinMode(buttonUpPin, INPUT_PULLUP);
  pinMode(buttonDownPin, INPUT_PULLUP);
}

void loop() {
  bool buttonUpPressed = (digitalRead(buttonUpPin) == LOW);
  bool buttonDownPressed = (digitalRead(buttonDownPin) == LOW);
  if (currentState == IDLE) {
    Serial.println("IDLE!");
    if (flagI) {
      if (buttonUpPressed || buttonDownPressed) {
        currentState = IDLE;  // บังคับเข้า
      }
      while (buttonUpPressed || buttonDownPressed) {
        buttonUpPressed = (digitalRead(buttonUpPin) == LOW);
        buttonDownPressed = (digitalRead(buttonDownPin) == LOW);
      }
      flagI = false;
    }
    else if(buttonUpPressed || buttonDownPressed) {
      currentState = RUNNING;  // เปลี่ยนเป็นสถานะ RUNNING
    }
  }
  if (currentState == RUNNING) {
    if (mySerial.available() > 0) { 
      int state = mySerial.read();
      if (state == GAME_OVER) {
        currentState = GAME_OVER;
        flag = true;
      }
    }
  }
  if (currentState == GAME_OVER) {
    Serial.println("Game Over!");
    // รอให้ปุ่มถูกปล่อยก่อนเพื่อป้องกันการอ่านซ้ำ
    if (flag) {
      if (buttonUpPressed || buttonDownPressed) {
        currentState = GAME_OVER;  // บังคับหยุด
      }
      while (buttonUpPressed || buttonDownPressed) {
        buttonUpPressed = (digitalRead(buttonUpPin) == LOW);
        buttonDownPressed = (digitalRead(buttonDownPin) == LOW);
      }
      flag = false;
    }
    if (buttonUpPressed || buttonDownPressed) {
      currentState = IDLE;  // เปลี่ยนเป็นสถานะ IDLE
      flagI = true;
    }
  }
  Serial.print("Current State: ");
  Serial.println(currentState);
  // ส่งข้อมูลสถานะไปยังบอร์ด 2
  String dataToSend = String(currentState) + "," + String(buttonUpPressed ? 1 : 0) + "," + String(buttonDownPressed ? 1 : 0);
  mySerial.println(dataToSend);
  // รอสักครู่เพื่อป้องกันการอ่านซ้ำ
  delay(60);
}