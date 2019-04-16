//----------------------------- Mission 답안 -----------------------------//

void setup()
{
  // 사용할 수 있는 LED 번호는 4, 5, 6, 7 번
    
  pinMode(4, OUTPUT);      // 4번 핀을 출력으로 설정
  pinMode(5, OUTPUT);      // 5번 핀을 출력으로 설정
  pinMode(5, OUTPUT);      // 6번 핀을 출력으로 설정
}

void loop()
{
  digitalWrite(4, HIGH);   // LED 켜기  (4번 핀을 HIGH로 변경)
  digitalWrite(6, LOW);    // LED 끄기  (6번 핀을 LOW로 변경)  
  delay(1000);             // 1초 기다리기 (1000 Milliseconds = 1second)

  digitalWrite(5, HIGH);   // LED 켜기  (5번 핀을 HIGH로 변경)
  digitalWrite(4, LOW);    // LED 끄기  (4번 핀을 LOW로 변경)
  delay(1000);             // 1초 기다리기 (1000 Milliseconds = 1second)

  digitalWrite(6, HIGH);   // LED 켜기  (6번 핀을 HIGH로 변경)
  digitalWrite(5, LOW);    // LED 끄기  (5번 핀을 LOW로 변경)
  delay(1000);   
}
