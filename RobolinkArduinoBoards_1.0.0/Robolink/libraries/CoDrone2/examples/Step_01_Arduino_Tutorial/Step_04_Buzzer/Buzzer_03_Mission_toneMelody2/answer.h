//----------------------------- Mission 답안 -----------------------------//

#include "pitches.h"  // 특정 음에 해당되는 주파수를 모아놓은 헤더파일

int buzzPin = 8;      // 변수에 부저 핀번호를 입력합니다.
int duration = 500;   // 음길이 : Tone 의 지속 시간 (밀리초 단위)

void setup()
{
  tone(buzzPin, NOTE_C4, duration);   // 4 옥타브 '도'를 0.5초 내기
  delay(500);                         // 0.5 초 기다리기 (500 Milliseconds = 0.5 second)

  tone(buzzPin, NOTE_D4, duration);   // 4 옥타브 '레'를 0.5초 내기
  delay(500);                         // 0.5 초 기다리기 (500 Milliseconds = 0.5 second)

  tone(buzzPin, NOTE_E4, duration);   // 4 옥타브 '미'를 0.5초 내기
  delay(500);                         // 0.5 초 기다리기 (500 Milliseconds = 0.5 second)

  tone(buzzPin, NOTE_F4, duration);   // 4 옥타브 '파'를 0.5초 내기
  delay(500);                         // 0.5 초 기다리기 (500 Milliseconds = 0.5 second)

  tone(buzzPin, NOTE_G4, duration);   // 4 옥타브 '솔'를 0.5초 내기
  delay(500);                         // 0.5 초 기다리기 (500 Milliseconds = 0.5 second)

  tone(buzzPin, NOTE_A4, duration);   // 4 옥타브 '라'를 0.5초 내기
  delay(500);                         // 0.5 초 기다리기 (500 Milliseconds = 0.5 second)

  tone(buzzPin, NOTE_B4, duration);   // 4 옥타브 '시'를 0.5초 내기
  delay(500);                         // 0.5 초 기다리기 (500 Milliseconds = 0.5 second)

  tone(buzzPin, NOTE_C5, duration);   // 4 옥타브 '도'를 0.5초 내기
  delay(500);                         // 0.5 초 기다리기 (500 Milliseconds = 0.5 second)
}

void loop() {
}
