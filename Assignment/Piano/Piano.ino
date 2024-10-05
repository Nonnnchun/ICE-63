int tones[] = {466, 440, 392, 349, 330, 294, 262};
int recording = 0; // สถานะการบันทึก (0 = ไม่บันทึก, 1 = บันทึก)
int recorded[150]; // อาร์เรย์สำหรับบันทึกโน้ต
int start = 0; // จุดเริ่มต้นของการบันทึก
int end = 0; // จุดสิ้นสุดของการบันทึก

int lastRecordButtonState = LOW; // สถานะก่อนหน้าของปุ่มบันทึก

void setup()
{
  Serial.begin(9600);

  // ตั้งค่าพิน 6 ถึง 12 เป็น INPUT สำหรับปุ่มโน้ต
  for (int i = 6; i <= 12; i++)
  {
    pinMode(i, INPUT);
  }
  
  // ตั้งค่าพิน 4 เป็น INPUT สำหรับปุ่มเล่น
  pinMode(4, INPUT);
  // ตั้งค่าพิน 5 เป็น INPUT สำหรับปุ่มบันทึก
  pinMode(5, INPUT);
  // ตั้งค่าพิน 3 เป็น OUTPUT สำหรับหยุดเสียง
  pinMode(3, OUTPUT);
}

void loop()
{
  // อ่านสถานะของปุ่มโน้ตและเล่นโน้ตที่เกี่ยวข้อง
  for (int i = 6, k = 0; i <= 12; i++, k++)
  {
    if (digitalRead(i) == HIGH)
    {
      tone(3, tones[k]);
      delay(200);
      noTone(3);
      Serial.print("Note: ");
      Serial.print(k);
      
      if (recording == 1)
      {
        // บันทึกโน้ตที่กด
        Serial.println(" recorded");
        recorded[end] = tones[k];
        end++;
      }
    }
  }
  
  // อ่านสถานะปุ่มบันทึก
  int currentRecordButtonState = digitalRead(5);

  // ตรวจสอบการเปลี่ยนแปลงของปุ่มบันทึก
  if (currentRecordButtonState == HIGH && lastRecordButtonState == LOW)
  {
    if (recording == 0)
    {
      Serial.println("Start Recording");
      recording = 1;
      start = end;
    }
    else
    {
      Serial.println("Stop Recording");
      recording = 0;
    }
  }
  
  // อัปเดตสถานะก่อนหน้าของปุ่มบันทึก
  lastRecordButtonState = currentRecordButtonState;
  
  // ตรวจสอบสถานะของปุ่มเล่น
  if (digitalRead(4) == HIGH)
  {
    delay(100);
    Serial.println("Play Recorded");
    for (int i = start; i < end; i++)
    {
      tone(3, recorded[i]);
      Serial.println(recorded[i]);
      delay(500);
      noTone(3);
    }
  }

  // หยุดเสียงหากไม่มีการกดปุ่มโน้ต
  if (digitalRead(6) == LOW && digitalRead(7) == LOW && digitalRead(8) == LOW &&
      digitalRead(9) == LOW && digitalRead(10) == LOW && digitalRead(11) == LOW &&
      digitalRead(12) == LOW)
  {
    noTone(3);
  }
}
