//----------------------------- Mission 답안 -----------------------------//

void setup()
{
  Serial.begin(57600); // 시리얼 통신을 사용하고, 통신 속도를 57600 bps로 설정
  pinMode(2, INPUT);    // 2번 핀을 입력으로 설정 (사용 가능한 버튼 번호 : 2, 3)
  pinMode(3, INPUT);    // 3번 핀을 입력으로 설정 (사용 가능한 버튼 번호 : 2, 3)
}

void loop()
{
  int state1 = digitalRead(2);   // 첫번째 버튼의 상태값을 읽어옵니다.
  int state2 = digitalRead(3);   // 두번째 버튼의 상태값을 읽어옵니다.

  Serial.print("State1 : ");    // "State1 : " 문자열 출력
  Serial.print(state1);         // 두번째 버튼의 상태값을 출력 (줄을 변경합니다.)
  
  Serial.print(" , ");          // 문장에 공백을 입력 합니다.
  
  Serial.print("State2 : ");    // "State2 : " 문자열 출력
  Serial.println(state2);       // 두번째 버튼의 상태값을 출력 (줄을 변경합니다.)
}
