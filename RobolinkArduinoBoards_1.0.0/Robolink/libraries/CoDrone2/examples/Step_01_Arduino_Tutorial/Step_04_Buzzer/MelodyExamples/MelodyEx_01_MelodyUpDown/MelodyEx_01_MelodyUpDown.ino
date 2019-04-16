/*---------------------------------------------------------------------------------------------------
  ToneMelodyUpDown (멜로디 예제 연주하기)
  목표 : Tone의 사용방법 익히기
  구문 : tone(pin, frequency)
         tone(pin, frequency, duration)
  설명 : 이 기능은 코드로더 보드에 있는 부저를 작동시킬수 있습니다.
         부저로 사용 가능한 번호는 8 입니다.
         계이름은 C D E F G A B C => 도 레 미 파 솔 라 시 도 다음과 같이 사용됩니다.
  ---------------------------------------------------------------------------------------------------*/

#include "pitches.h"

int buzzPin = 8;   // 변수에 부저 핀번호를 입력합니다.

// 계이름을 배열에 입력
int melody[] = {
  NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C4
};

// 음길이 입력 (4 = 4분음표, 8 = 8분음표...)
int noteDurations[] = {
  8, 8, 8, 8,  8, 8, 8, 8
};

void setup() {
  for (int thisNote = 0; thisNote < 8; thisNote++)    // 8개의 음계를 반복
  {
    int noteDuration = 1000 / noteDurations[thisNote]; // 음 길이를 계산합니다.
    tone(buzzPin, melody[thisNote], noteDuration);    // 음을 재생합니다.

    int pauseBetweenNotes = noteDuration * 1.30;      // 음을 구별하기 위한 노트사이의 시간을 계산합니다.(음의 지속 시간 + 30%)
    delay(pauseBetweenNotes);                         // 재생 시간 기다리기

    noTone(buzzPin);                                  // 음을 멈춤니다.
  }
}

void loop() {
}
