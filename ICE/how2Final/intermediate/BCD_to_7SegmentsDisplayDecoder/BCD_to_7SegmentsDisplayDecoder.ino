const uint8_t digitPatterns[11] = {
  0b11000000,  // 0
  0b11111001,  // 1
  0b10100100,  // 2
  0b10110000,  // 3
  0b10011001,  // 4
  0b10010010,  // 5
  0b10000010,  // 6
  0b11111000,  // 7
  0b10000000,  // 8
  0b10010000,  // 9
  0b10111111   // -
};

const int segment[8] = { 4, 5, 6, 7, 8, 9, 10, 11 };

const short button1 = 12;
const short button2 = 2;

const short button3 = 3;
const short button4 = 13;

const uint8_t button[4] = { 13, 3, 2, 12 };

// unsigned long debounceDelay = 200;
// unsigned long lastDebounceTime = 0;

uint8_t a = 0b0000;
int lastButtonState[4] = { HIGH, HIGH, HIGH, HIGH };  // สถานะปุ่มก่อนหน้า

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {
    pinMode(segment[i], OUTPUT);
    digitalWrite(segment[i], HIGH);
  }

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

}

void displaySegment(uint8_t number) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segment[i], bitRead(digitPatterns[(number < 10) ? number : 10], i));
  }
}

void loop() {
  /*
  int buttonStates[4] = {
    digitalRead(button1),
    digitalRead(button2),
    digitalRead(button3),
    digitalRead(button4)
  };

  for (int i = 0; i < 4; i++) {
    if (buttonStates[i] == LOW && lastButtonState[i] == HIGH) {
      a |= (1 << (3 - i)); // ตั้งค่าบิตที่ตรงกับปุ่มที่กด
    }
    // ตรวจสอบการปล่อยปุ่ม
    if (buttonStates[i] == HIGH && lastButtonState[i] == LOW) {
      a = 0; // รีเซ็ตค่า a เป็น 0 เมื่อปล่อยปุ่ม
    }
    lastButtonState[i] = buttonStates[i]; // อัปเดตสถานะปุ่มก่อนหน้า
  }
  */

  // a = 0    0000 1000
  // bitWrite(a, 3, 1)
  // a = 8


  for (int i = 0; i < 4; i++) {
    bitWrite(a, i, digitalRead(button[i]));
  }

  displaySegment(a);
}



/*
//Hard Ware & Soft Ware test --> Count 0 - 9

void loop() {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 8; j++) {
      digitalWrite(segment[j], bitRead(digitPatterns[i], j));
      Serial.println(digitPatterns[i]);
    }
    delay(1000);

    for(int k = 0; k<8; k++){
    digitalWrite(segment[k], HIGH);
    }
  }
}
*/