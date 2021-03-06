/*---------------------------------------------------------------------------------------------------
  - Mission - Button All with LED (버튼으로 두개의 LED를 켜고 끄기)
  목표 : digitalRead의 디지털 입력 사용방법 익히기
         여러개의 입력과 출력의 동시 제어
  구문 : digitalRead(핀번호, 출력 선택)
  설명 : 이 기능은 코드로더 보드에 있는 버튼의 디지털 상태 값을 읽을 수 있습니다.  
         LED로 사용 가능한 번호는 4,5,6,7 입니다.
         버튼으로 사용 가능한 번호는 2,3 입니다.
         버튼을 누르지 않을 때의 상태값은 HIGH(1)이며, 누른 경우에는 LOW(0) 값을 나타냅니다.
         
         다음 예제를 수정하여 두개 버튼의 디지털 상태에 따라서 각각의 LED를 켜거나 끄도록 만들어 보세요.
  ---------------------------------------------------------------------------------------------------*/

void setup()
{
  pinMode(7, OUTPUT);  // 7번 핀을 출력으로 설정 (사용 가능한 LED 번호 : 4, 5, 6, 7)
  pinMode(2, INPUT);   // 2번 핀을 입력으로 설정 (사용 가능한 버튼 번호 : 2, 3)
}

void loop()
{
  int buttonState = digitalRead(2); // 버튼의 상태값을 읽어옵니다.

  if (buttonState == LOW)           // 버튼 상태 값이 LOW 인경우 (버튼을 누른 경우)
  {
    digitalWrite(7, HIGH);     // LED 7번 켜기  (7번 핀을 HIGH로 변경)
  }
  else
  {
    digitalWrite(7, LOW);      // LED 7번 끄기  (7번 핀을 LOW로 변경)
  }
}
