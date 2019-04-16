/*---------------------------------------------------------------------------------------------------
  - Mission - Wave Three LED (LED 3개를 차례로 켜고 끄기)
  목표 : LED를 사용하여 순차 프로그래밍 익히기
  구문 : digitalWrite(핀번호, 출력 선택)
  설명 : 2개의 LED가 차례로 켜지는 예제를 3개의 LED가 켜지고 꺼지게 만들어 봅시다.
  ---------------------------------------------------------------------------------------------------*/

void setup()
{
  // 사용할 수 있는 LED 번호는 4, 5, 6, 7 번
  
  pinMode(4, OUTPUT);      // 4번 핀을 출력으로 설정
  pinMode(5, OUTPUT);      // 5번 핀을 출력으로 설정
}

void loop()
{
  // LED 차례로 켜기

  digitalWrite(4, HIGH);   // LED 켜기  (4번 핀을 HIGH로 변경)
  delay(1000);             // 1초 기다리기 (1000 Milliseconds = 1second)

  digitalWrite(5, HIGH);   // LED 켜기  (5번 핀을 HIGH로 변경)
  delay(1000);             // 1초 기다리기 (1000 Milliseconds = 1second)


  // LED 차례로 끄기

  digitalWrite(5, LOW);    // LED 끄기  (5번 핀을 LOW로 변경)
  delay(1000);             // 1초 기다리기 (1000 Milliseconds = 1second)

  digitalWrite(4, LOW);    // LED 끄기  (4번 핀을 LOW로 변경)
  delay(1000);             // 1초 기다리기 (1000 Milliseconds = 1second)
}
