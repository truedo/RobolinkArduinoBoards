//----------------------------- Mission 답안 -----------------------------//

void setup()
{
  pinMode(7, OUTPUT);     // 4번 핀을 출력으로 설정 (사용 가능한 LED 번호 : 4, 5, 6, 7)
  pinMode(4, OUTPUT);     // 7번 핀을 출력으로 설정 (사용 가능한 LED 번호 : 4, 5, 6, 7)
  
  pinMode(2, INPUT);   // 2번 핀을 입력으로 설정 (사용 가능한 버튼 번호 : 2, 3)
  pinMode(3, INPUT);   // 3번 핀을 입력으로 설정 (사용 가능한 버튼 번호 : 2, 3)
}

void loop()
{

  int buttonState1 = digitalRead(2);  // 첫번째 버튼의 상태값을 읽어옵니다.
  int buttonState2 = digitalRead(3);  // 두번째 버튼의 상태값을 읽어옵니다.

  if (buttonState1 == LOW)  // 첫번째 버튼상태값이 LOW 인경우 (버튼을 누른 경우)
  {
    digitalWrite(7, HIGH);  // LED 7번 켜기  (7번 핀을 HIGH로 변경)
  }
  else
  {
    digitalWrite(7, LOW);   // LED 7번 끄기  (7번 핀을 LOW로 변경)
  }

  if (buttonState2 == LOW)  // 두번째 버튼상태값이 LOW 인경우 (버튼을 누른 경우)
  {
    digitalWrite(4, HIGH);  // LED 4번 켜기  (4번 핀을 HIGH로 변경)
  }
  else
  {
    digitalWrite(4, LOW);   // LED 4번 끄기  (4번 핀을 LOW로 변경)
  }
}


  
