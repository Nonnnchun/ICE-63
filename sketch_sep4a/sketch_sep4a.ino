#define BUTTON_NORTH 8
#define LED_N_R 13
#define LED_N_Y 12
#define LED_N_G 11

#define BUTTON_EAST 7
#define LED_E_R 6
#define LED_E_Y 5
#define LED_E_G 4

#define BUTTON_HUMAN 1
#define LED_Walk_R 10
#define LED_Walk_G 9

#define goN 0
#define waitN 1
#define goE 2
#define waitE 3
#define W1 4
#define W2 5
#define flashing 7
#define flashing1 8
#define flashing2 9
#define flashing3 10
#define flashing4 11
#define flashing5 12
#define flashing6 13

struct state {
  unsigned long STATE_Out;
  unsigned long Time;
  unsigned long STATE_Next[8];
};

typedef const struct state Stype;
Stype FSM[15] = {
  { B01001100, 5000, { goN, waitN, goN, waitN, W1, W1, W1, waitN } },
  { B01010100, 2000, { goE, goE, goE, goE, W1, W1, W1, goE } },
  { B01100001, 5000, { goE, goE, waitE, waitE, W2, W2, W2, waitE } },
  { B01100010, 2000, { goN, goN, goN, goN, W2, W2, W2, W2 } },
  //yellow road light
  { B10100100, 2000, { 4, 6, 6, 6, 4, 6, 6, 6 } },
  { B10100100, 2000, { 5, 6, 6, 6, 5, 6, 6, 6 } },
  //ไฟเดันเขียว ไฟรถแดง
  { B10100100, 5000, { flashing, flashing, flashing, flashing, flashing, flashing, flashing, flashing } },
  //ตดับติด 3 รอบ
  { B00100100, 500, { flashing1, flashing1, flashing1, flashing1, flashing1, flashing1, flashing1, flashing1 } },
  { B10100100, 500, { flashing2, flashing2, flashing2, flashing2, flashing2, flashing2, flashing2, flashing2 } },
  { B00100100, 500, { flashing3, flashing3, flashing3, flashing3, flashing3, flashing3, flashing3, flashing3 } },
  { B10100100, 500, { flashing4, flashing4, flashing4, flashing4, flashing4, flashing4, flashing4, flashing4 } },
  { B00100100, 500, { flashing5, flashing5, flashing5, flashing5, flashing5, flashing5, flashing5, flashing5 } },
  { B10100100, 500, { goE, goN, goN, goE, flashing, goE, goN, goN } }
};

unsigned long ST = 0;

void setup() {
  pinMode(LED_N_R, OUTPUT);
  pinMode(LED_N_Y, OUTPUT);
  pinMode(LED_N_G, OUTPUT);
  pinMode(BUTTON_NORTH, INPUT);
  pinMode(LED_E_R, OUTPUT);
  pinMode(LED_E_Y, OUTPUT);
  pinMode(LED_E_G, OUTPUT);
  pinMode(BUTTON_EAST, INPUT);
  pinMode(LED_Walk_R, OUTPUT);
  pinMode(LED_Walk_G, OUTPUT);
  pinMode(BUTTON_HUMAN, INPUT);
}
int input, input1, input2, input3;


void loop() {
  digitalWrite(LED_Walk_G, FSM[ST].STATE_Out & B10000000);
  digitalWrite(LED_Walk_R, FSM[ST].STATE_Out & B01000000);
  digitalWrite(LED_N_R, !(FSM[ST].STATE_Out & B00100000));
  digitalWrite(LED_N_Y, !(FSM[ST].STATE_Out & B00010000));
  digitalWrite(LED_N_G, !(FSM[ST].STATE_Out & B00001000));
  digitalWrite(LED_E_R, !(FSM[ST].STATE_Out & B00000100));
  digitalWrite(LED_E_Y, !(FSM[ST].STATE_Out & B00000010));
  digitalWrite(LED_E_G, !(FSM[ST].STATE_Out & B00000001));

  delay(FSM[ST].Time);
  input1 = digitalRead(BUTTON_NORTH);
  input2 = digitalRead(BUTTON_EAST);
  input3 = digitalRead(BUTTON_HUMAN);
  input = input1 * 2 + input2 + input3 * 4;
  ST = FSM[ST].STATE_Next[input];
}