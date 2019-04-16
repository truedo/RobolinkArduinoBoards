/*---------------------------------------------------------------------------------------------------
  HappyBirthday (멜로디 예제 연주하기)
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
int melody[] = {NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_C4, NOTE_B3,
                NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_D4, NOTE_C4,
                NOTE_G3, NOTE_G3, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_B3, NOTE_A3,
                NOTE_F4, NOTE_F4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_C4
               };
// 음길이 입력 (4 = 4분음표, 8 = 8분음표...)
int noteDurations[] = { 8, 8, 4, 4, 4, 2, 8, 8, 4, 4, 4, 2, 8, 8, 4, 4, 4, 4, 3, 8, 8, 4, 4, 4, 2 };

void setup()
{
  for (int thisNote = 0; thisNote < 26; thisNote++)
  {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzPin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.60;
    delay(pauseBetweenNotes);
    noTone(buzzPin);
  }
}
void loop() {
}
