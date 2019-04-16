/*---------------------------------------------------------------------------------------------------
  - Mission - Blink Two LED (LED 2개를 깜박이기) 
  목표 : digitalWrite 사용방법 익히기
  구문 : digitalWrite(핀번호, 출력 선택)
  설명 : 1개의 LED를 깜박이는 예제를 수정하여 2개의 LED가 깜박이도록 만들어 봅시다.
  ---------------------------------------------------------------------------------------------------*/

void setup()
{
  // 사용할 수 있는 LED 번호는 4, 5, 6, 7 번
  
  pinMode(4, OUTPUT);      // 4번 핀을 출력으로 설정
}

void loop()
{
   // LED 깜박이기
   
  digitalWrite(4, HIGH);   // LED 켜기  (4번 핀을 HIGH로 변경)

  delay(1000);             // 1초 기다리기 (1000 Milliseconds = 1second)

  digitalWrite(4, LOW);    // LED 끄기  (4번 핀을 LOW로 변경)

  delay(1000);             // 1초 기다리기 (1000 Milliseconds = 1second)
}
