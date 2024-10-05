#include <LedControl.h>

// พินเชื่อมต่อจอแสดงผล MAX7219
#define DIN 12
#define CS 10
#define CLK 11
#define NUM_MATRICES 4  // จำนวนจอแสดงผล 8x8 ที่ต่อกัน

LedControl lc = LedControl(DIN, CLK, CS, NUM_MATRICES);

// กำหนดขาของปุ่มกด
const int buttonUpPin = 2;
const int buttonDownPin = 3;

// ตำแหน่งของตัวละคร
int playerX = 0;  // อยู่ที่ขอบซ้ายของหน้าจอ
int playerY = 3;  // เริ่มต้นที่ตรงกลางในแกน Y

// ตัวอักษรในคำว่า "START"
byte S[8] = { B00000000,
              B00111110,
              B01000000,
              B00111100,
              B00000010,
              B01111100,
              B00000000,
              B00000000 };  // "S"
byte T[8] = { B00000000,
              B01111100,
              B00010000,
              B00010000,
              B00010000,
              B00010000,
              B00000000,
              B00000000 };  // "T"
byte A[8] = { B00000000,
              B00111100,
              B01000010,
              B01111110,
              B01000010,
              B01000010,
              B00000000,
              B00000000 };  // "A"
byte R[8] = { B00000000,
              B00111100,
              B01000010,
              B01111100,
              B01001000,
              B01000110,
              B00000000,
              B00000000 };  // "R"
byte x[8] = { B00000000,
              B00000000,
              B00000000,
              B00000000,
              B00000000,
              B00000000,
              B00000000,
              B00000000 };  // " "
byte C[8] = { B00000000,
              B00111100,
              B01000010,
              B01000000,
              B01000010,
              B00111100,
              B00000000,
              B00000000 };  // "C"
byte O[8] = { B00000000,
              B00111100,
              B01000010,
              B01000010,
              B01000010,
              B00111100,
              B00000000,
              B00000000 };  // "O"
byte E[8] = { B00000000,
              B00111110,
              B01000000,
              B00111100,
              B01000000,
              B00111110,
              B00000000,
              B00000000 };  // "E"

byte num0[8] = { B00000000,
                 B01111110,
                 B01000010,
                 B01000010,
                 B01000010,
                 B01111110,
                 B00000000,
                 B00000000 };  // "0"
byte num1[8] = { B00000000,
                 B00011000,
                 B00001000,
                 B00001000,
                 B00001000,
                 B00111100,
                 B00000000,
                 B00000000 };  // "1"
byte num2[8] = { B00000000,
                 B01111100,
                 B00000100,
                 B01111100,
                 B01000000,
                 B01111100,
                 B00000000,
                 B00000000 };  // "2"
byte num3[8] = { B00000000,
                 B01111100,
                 B00000100,
                 B00111100,
                 B00000100,
                 B01111100,
                 B00000000,
                 B00000000 };  // "3"
byte num4[8] = { B00000100,
                 B00100100,
                 B01000100,
                 B01111110,
                 B00000100,
                 B00000100,
                 B00000000,
                 B00000000 };  // "4"
byte num5[8] = { B00000000,
                 B01111100,
                 B01000000,
                 B01111110,
                 B00000010,
                 B01111110,
                 B00000000,
                 B00000000 };  // "5"
byte num6[8] = { B00000000,
                 B01111100,
                 B01000000,
                 B01111110,
                 B01000010,
                 B01111110,
                 B00000000,
                 B00000000 };  // "6"
byte num7[8] = { B00000000,
                 B01111100,
                 B00000100,
                 B00000100,
                 B00001000,
                 B00001000,
                 B00000000,
                 B00000000 };  // "7"
byte num8[8] = { B00000000,
                 B01111110,
                 B01000010,
                 B01111110,
                 B01000010,
                 B01111110,
                 B00000000,
                 B00000000 };  // "8"
byte num9[8] = { B00000000,
                 B01111110,
                 B01000010,
                 B01111110,
                 B00000010,
                 B00111110,
                 B00000000,
                 B00000000 };  // "9"



byte* charactersScore[6] = { S, C, O, R, E, x };  // เก็บตัวอักษร "SCORE"

// ตัวอักษรในคำว่า "START" จัดเรียงในรูปแบบ array
byte* characters[6] = { S, T, A, R, T, x };  // ใช้เพื่อเก็บลำดับตัวอักษร

// กำหนดตัวแปรสำหรับการเลื่อนวน
unsigned long lastUpdateTime = 0;
int currentCharIndex = 0;
long displayInterval = 1000;  // ระยะเวลาในการเปลี่ยนตัวอักษร

// ตำแหน่งของสิ่งกีดขวาง
int obstacleX[5];                           // ตำแหน่งแกน X ของก้อนสิ่งกีดขวาง
int obstacleY[5];                           // ตำแหน่งแกน Y ของก้อนสิ่งกีดขวาง
int obstacleWidth[5] = { 1, 1, 1, 1, 1 };   // ความกว้างของสิ่งกีดขวางแต่ละก้อน
int obstacleHeight[5] = { 1, 1, 1, 1, 1 };  // ความสูงของสิ่งกีดขวางแต่ละก้อน

// สถานะของปุ่มกด
bool buttonUpPressed = false;
bool buttonDownPressed = false;

// สถานะของเกม
enum GameState { IDLE,
                 RUNNING,
                 GAME_OVER
};
GameState currentState = IDLE;

// เพิ่มตัวแปรสำหรับจับเวลา
unsigned long startTime = 0;    // เวลาที่เริ่มเกม
unsigned long elapsedTime = 0;  // เวลาที่ผ่านไปในช่วง RUNNING


long interval = 111;  // ความเร็วเริ่มต้นใน Stage 1

void setup() {
  for (int i = 0; i < NUM_MATRICES; i++) {
    lc.shutdown(i, false);  // เปิดจอแสดงผลแต่ละตัว
    lc.setIntensity(i, 3);  // ตั้งค่าความสว่าง (0-15)
    lc.clearDisplay(i);     // ล้างหน้าจอแสดงผลแต่ละตัว
  }

  // เริ่ม Serial Monitor ที่ baud rate 9600
  Serial.begin(9600);

  // กำหนดปุ่มกดเป็นอินพุต
  pinMode(buttonUpPin, INPUT_PULLUP);
  pinMode(buttonDownPin, INPUT_PULLUP);

  // สุ่มตำแหน่งเริ่มต้นของสิ่งกีดขวาง
  randomSeed(analogRead(0));
  for (int i = 0; i < 5; i++) {
    obstacleX[i] = i * 8 + 32;                        // ให้สิ่งกีดขวางเคลื่อนที่จากด้านขวาเข้ามาทางซ้าย
    obstacleY[i] = random(0, 8 - obstacleHeight[i]);  // สุ่มตำแหน่ง Y ของสิ่งกีดขวางโดยคำนึงถึงความสูง
  }
}

void loop() {
  // อัปเดตสถานะของปุ่มกด
  buttonUpPressed = (digitalRead(buttonUpPin) == LOW);
  buttonDownPressed = (digitalRead(buttonDownPin) == LOW);

  // เรียกใช้ฟังก์ชันตามสถานะปัจจุบัน
  switch (currentState) {
    case IDLE:
      idleState();
      break;

    case RUNNING:
      runningState();
      break;

    case GAME_OVER:
      gameOverState();
      break;
  }
}

void idleState() {
  unsigned long currentTime = millis();

  // ตรวจสอบว่าถึงเวลาที่จะแสดงตัวอักษรถัดไปหรือไม่
  if (currentTime - lastUpdateTime >= displayInterval) {
    lastUpdateTime = currentTime;  // บันทึกเวลาล่าสุดที่อัปเดต
    clearAllDisplays();            // ล้างจอแสดงผลทั้งหมด

    int startModule = 3;  // เริ่มที่ module 3

    for (int i = 0; i < NUM_MATRICES; i++) {
      // คำนวณตำแหน่งของ module ใหม่โดยเริ่มที่ module 3 และเลื่อนไปทางซ้าย
      int moduleIndex = (startModule - i + NUM_MATRICES) % NUM_MATRICES;
      setCharOnMatrix(moduleIndex, characters[(currentCharIndex + i) % 6]);  // แสดงตัวอักษร S, T, A, R, T วนไป
    }

    // เลื่อนลำดับไปยังตัวอักษรถัดไป
    currentCharIndex = (currentCharIndex + 1) % 6;  // วนไปเรื่อย ๆint startModule = 3; // เริ่มที่ module 3
  }

  // รีเซ็ตเวลาเมื่อเข้าสู่สถานะ IDLE
  elapsedTime = 0;
  interval = 111;  // รีเซ็ตความเร็วเป็นค่าเริ่มต้นสำหรับ Stage 1

  // เริ่มเกมถ้ามีการกดปุ่ม
  if (buttonUpPressed || buttonDownPressed) {
    clearAllDisplays();      // ล้างหน้าจอเพื่อเริ่มเกม
    startTime = millis();    // บันทึกเวลาที่เริ่มเกม
    currentState = RUNNING;  // เปลี่ยนเป็นสถานะ RUNNING
  }
}

void runningState() {
  unsigned long currentTime = millis();

  // คำนวณเวลาที่ผ่านไปในสถานะ RUNNING
  elapsedTime = currentTime - startTime;

  // แสดงเวลาที่ผ่านไปใน Serial Monitor
  Serial.print("Elapsed Time: ");
  Serial.println(elapsedTime / 1000.0, 2);  // แสดงเป็นวินาทีและทศนิยม 2 ตำแหน่ง

  // ปรับความเร็วตาม stage
  if (elapsedTime >= 20000) {
    interval = 50;  // Stage 3: ปรับความเร็วเป็น 30 เมื่อเวลาผ่านไป 20 วินาที
  } else if (elapsedTime >= 10000) {
    interval = 70;  // Stage 2: ปรับความเร็วเป็น 60 เมื่อเวลาผ่านไป 10 วินาที
  }
  if (currentTime - lastUpdateTime >= interval) {
    lastUpdateTime = currentTime;

    // เคลื่อนที่ของตัวละครตามการกดปุ่ม
    if (buttonUpPressed && playerY > 0) {
      playerY--;
    }
    if (buttonDownPressed && playerY < 7) {  // ขอบเขตการเคลื่อนที่ในแกน Y
      playerY++;
    }

    // เคลื่อนที่สิ่งกีดขวางจากขวาไปซ้าย
    for (int i = 0; i < 5; i++) {
      obstacleX[i]--;
      if (obstacleX[i] < 0 - obstacleWidth[i]) {  // ถ้าสิ่งกีดขวางหลุดจากจอซ้ายสุด รีเซ็ตตำแหน่งใหม่
        obstacleX[i] = 32;
        obstacleY[i] = random(0, 8);  // สุ่มตำแหน่งใหม่ของสิ่งกีดขวางในแกน Y
      }

      // ตรวจสอบการชน
      if (checkCollision(playerX, playerY, 1, 1, obstacleX[i], obstacleY[i], obstacleWidth[i], obstacleHeight[i])) {
        currentState = GAME_OVER;
      }
    }

    // วาดเกมบนหน้าจอ
    drawGame();
  }
}

void displayScrollingScoreWithNumber() {
  unsigned long currentTime = millis();

  if (currentTime - lastUpdateTime >= displayInterval) {
    lastUpdateTime = currentTime;  // บันทึกเวลาล่าสุดที่อัปเดต
    clearAllDisplays();            // ล้างจอแสดงผลทั้งหมด

    // คำว่า "SCORE" + ตัวเลข
    int score = elapsedTime / 1000;  // คำนวณคะแนนเป็นวินาที (แสดงเฉพาะส่วนเต็ม)

    // แปลงคะแนนเป็น string เช่น "15"
    String scoreStr = String(score);

    // สร้างลำดับตัวอักษรสำหรับเลื่อน: "  SCORE 15" (เว้น 2 ช่องก่อน "SCORE" และเว้น 1 ช่องก่อน "15")
    byte* scrollingCharacters[12];  // ขนาด 12 สำหรับช่องว่าง 2 ช่อง + "SCORE" + ช่องว่าง 1 ช่อง + ตัวเลข
    scrollingCharacters[0] = x;     // ช่องว่างที่ 1
    scrollingCharacters[1] = x;     // ช่องว่างที่ 2
    scrollingCharacters[2] = S;
    scrollingCharacters[3] = C;
    scrollingCharacters[4] = O;
    scrollingCharacters[5] = R;
    scrollingCharacters[6] = E;
    scrollingCharacters[7] = x;  // ช่องว่างก่อนตัวเลข

    // แปลงตัวเลขแต่ละหลักเป็น byte เพื่อใส่ใน array
    for (int i = 0; i < scoreStr.length(); i++) {
      scrollingCharacters[8 + i] = getDigitCharacter(scoreStr[i] - '0');  // แปลง char เป็นตัวเลขแล้วนำไปแสดง
    }

    int totalLength = 8 + scoreStr.length();  // ความยาวของตัวอักษรทั้งหมด ("SCORE" + ช่องว่าง + ตัวเลข)

    // แสดงตัวอักษรทั้งหมดบนหน้าจอ
    for (int i = 0; i < NUM_MATRICES; i++) {
      int moduleIndex = (3 - i + NUM_MATRICES) % NUM_MATRICES;
      setCharOnMatrix(moduleIndex, scrollingCharacters[(currentCharIndex + i) % totalLength]);  // เลื่อนตัวอักษร S, C, O, R, E ตามด้วยตัวเลข
    }

    currentCharIndex = (currentCharIndex + 1) % totalLength;  // เลื่อนตัวอักษรทั้งหมดไปเรื่อย ๆ
  }
}

// ฟังก์ชันสำหรับแปลงตัวเลขเป็นตัวอักษรในรูปแบบ matrix
byte* getDigitCharacter(int digit) {
  switch (digit) {
    case 0:
      return num0;
    case 1:
      return num1;
    case 2:
      return num2;
    case 3:
      return num3;
    case 4:
      return num4;
    case 5:
      return num5;
    case 6:
      return num6;
    case 7:
      return num7;
    case 8:
      return num8;
    case 9:
      return num9;
    default:
      return x;
  }
}

void gameOverState() {
  // กระพริบไฟที่ตำแหน่งของตัวละครเพื่อแสดงว่าชนแล้ว
  for (int i = 0; i < 5; i++) {
    clearAllDisplays();
    delay(300);
    setLed(playerX, playerY, true);  // กระพริบตำแหน่งของตัวละคร
    delay(300);
  }

  // รีเซ็ตตัวแปร currentCharIndex เพื่อให้เริ่มแสดงจากตัว "S" ของคำว่า "SCORE" เสมอ
  currentCharIndex = 0;

  // แสดงคำว่า "SCORE" เลื่อนบนจอไปเรื่อยๆ จนกว่าจะกดปุ่ม
  while (true) {
    displayScrollingScoreWithNumber();  // แสดงคำว่า "SCORE" เลื่อนวนไปเรื่อยๆ

    // อัปเดตสถานะของปุ่มกด
    buttonUpPressed = (digitalRead(buttonUpPin) == LOW);
    buttonDownPressed = (digitalRead(buttonDownPin) == LOW);

    // ตรวจสอบว่ามีการกดปุ่มเพื่อออกจาก gameOverState หรือไม่
    if (buttonUpPressed || buttonDownPressed) {
      clearAllDisplays();   // ล้างหน้าจอเพื่อเริ่มเกมใหม่
      currentState = IDLE;  // เปลี่ยนสถานะกลับเป็น IDLE เพื่อเริ่มเกมใหม่
      break;                // ออกจากลูป
    }
  }

  // รีเซ็ตตัวแปรของเกม
  playerY = 3;
  for (int i = 0; i < 5; i++) {
    obstacleX[i] = i * 8 + 32;
    obstacleY[i] = random(0, 8 - obstacleHeight[i]);
  }
}

void drawGame() {
  clearAllDisplays();

  // วาดตัวละคร
  setLed(playerX, playerY, true);

  // วาดสิ่งกีดขวางที่เป็นก้อนใหญ่
  for (int i = 0; i < 5; i++) {
    for (int w = 0; w < obstacleWidth[i]; w++) {
      for (int h = 0; h < obstacleHeight[i]; h++) {
        setLed(obstacleX[i] + w, obstacleY[i] + h, true);
      }
    }
  }
}

// ฟังก์ชันสำหรับเคลียร์จอทั้งหมด
void clearAllDisplays() {
  for (int i = 0; i < NUM_MATRICES; i++) {
    lc.clearDisplay(i);
  }
}

void setCharOnMatrix(int matrixIndex, byte character[8]) {
  for (int row = 0; row < 8; row++) {
    lc.setRow(matrixIndex, row, character[row]);
  }
}

// ฟังก์ชันในการตั้งค่า LED ในตำแหน่งที่ต้องการ
void setLed(int x, int y, bool state) {
  if (x >= 0 && x < 33) {  // ตรวจสอบว่าค่า X อยู่ในขอบเขตของจอที่เชื่อมต่อกัน (จาก 0 ถึง 32)
    // Mapping of X positions to the corresponding module
    int matrix = 3;  // Start with module 3

    if (x >= 24 && x <= 32) {  // ตำแหน่งใน Module 3
      matrix = 0;
      x = x - 24;                     // คำนวณตำแหน่งภายใน Module 3
    } else if (x >= 16 && x <= 23) {  // ตำแหน่งใน Module 2
      matrix = 1;
      x = x - 16;                    // คำนวณตำแหน่งภายใน Module 2
    } else if (x >= 8 && x <= 15) {  // ตำแหน่งใน Module 1
      matrix = 2;
      x = x - 8;                    // คำนวณตำแหน่งภายใน Module 1
    } else if (x >= 0 && x <= 7) {  // ตำแหน่งใน Module 0
      matrix = 3;
      // ไม่ต้องคำนวณเพิ่ม เพราะ X อยู่ในขอบเขตของ Module 0 แล้ว
    }

    lc.setLed(matrix, y, x, state);  // ตั้งค่า LED ในตำแหน่งที่คำนวณแล้ว
  }
}

// ฟังก์ชันตรวจสอบการชน
bool checkCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
  return !(x1 + w1 - 1 < x2 || x1 > x2 + w2 - 1 || y1 + h1 - 1 < y2 || y1 > y2 + h2 - 1);
}