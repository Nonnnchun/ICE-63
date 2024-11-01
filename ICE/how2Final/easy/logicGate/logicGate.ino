int led[6] = { 7, 6, 5, 4, 11, 10 };

const short buttonA = 3;
const short buttonB = 13;
const short buttonC = 2;

uint8_t a = 0b00000000;
uint8_t b = 0b00000000;
uint8_t c = 0b00000000;

int caseOperator = 0;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200;

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(led[i], OUTPUT);
  }

  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT);

  Serial.begin(9600);
}

void loop() {

  if (digitalRead(buttonA) && (millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    if (digitalRead(buttonA) == HIGH) {
      a = a + 1;
      if (a > 3) {
        a = 0;
      }
    }
  }

  if (digitalRead(buttonB) && (millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    if (digitalRead(buttonB) == HIGH) {
      b += 1;
      if (b > 3) {
        b = 0;
      }
    }
  }

  if (digitalRead(buttonC) && (millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    if (digitalRead(buttonC) == HIGH) {
      caseOperator += 1;
      if (caseOperator > 3) {
        caseOperator = 0;
      }
    }
  }

  switch (caseOperator) {
    case 0:
      c = a & b;
      Serial.print((b < 2 ? "0" : "") + String(b, BIN));
      Serial.print(" & ");
      Serial.print((a < 2 ? "0" : "") + String(a, BIN));
      Serial.print(" = ");
      Serial.println((c < 2 ? "0" : "") + String(c, BIN));
      break;
    case 1:
      c = a | b;
      Serial.print((b < 2 ? "0" : "") + String(b, BIN));
      Serial.print(" | ");
      Serial.print((a < 2 ? "0" : "") + String(a, BIN));
      Serial.print(" = ");
      Serial.println((c < 2 ? "0" : "") + String(c, BIN));
      break;
    case 2:
      c = a ^ b;
      Serial.print((b < 2 ? "0" : "") + String(b, BIN));
      Serial.print(" ^ ");
      Serial.print((a < 2 ? "0" : "") + String(a, BIN));
      Serial.print(" = ");
      Serial.println((c < 2 ? "0" : "") + String(c, BIN));
      break;
    case 3:
      c = ~b & 0x03;
      Serial.print(" ~ ");
      Serial.print((a < 2 ? "0" : "") + String(a, BIN));
      Serial.print(" = ");
      Serial.println((c < 2 ? "0" : "") + String(c, BIN));
      break;
  }

  for (int i = 0; i < 6; i++) {
    if (i >= 2 && i < 4) {
      digitalWrite(led[i], bitRead(b, i - 2));
    } else if (i >= 4 && i < 6) {
      digitalWrite(led[i], bitRead(c, i - 4));
    } else {
      digitalWrite(led[i], bitRead(a, i));
    }
  }
}