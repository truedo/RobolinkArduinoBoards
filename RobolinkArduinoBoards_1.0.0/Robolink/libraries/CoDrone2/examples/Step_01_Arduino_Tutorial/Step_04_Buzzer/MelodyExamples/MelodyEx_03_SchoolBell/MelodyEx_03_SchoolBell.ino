/*---------------------------------------------------------------------------------------------------
  SchoolBell (멜로디 예제 연주하기)
  목표 : Tone의 사용방법 익히기
  구문 : tone(pin, frequency)
         tone(pin, frequency, duration)
  설명 : 이 기능은 코드로더 보드에 있는 부저를 작동시킬수 있습니다.
         부저로 사용 가능한 번호는 8 입니다.
         계이름은 C D E F G A B C => 도 레 미 파 솔 라 시 도 다음과 같이 사용됩니다.
  ---------------------------------------------------------------------------------------------------*/

#define NOTE_C4  262  // 도 
#define NOTE_D4  294  // 레 
#define NOTE_E4  330  // 미 
#define NOTE_F4  349  // 파 
#define NOTE_G4  392  // 솔 
#define NOTE_A4  440  // 라 
#define NOTE_B4  494  // 시 

int buzzPin = 8;   // 변수에 부저 핀번호를 입력합니다.

// 계이름을 배열에 입력
int notes[25] = { NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, 0,
                  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_C4
                };
                
// 음길이 설정 - 전체 4분 음표로 설정 (noteDuration = 1000/4) 
int tempo = 250; 

void setup()
{
  for (int i = 0; i < 25; i++)
  {
    tone (buzzPin, notes[i], tempo);
    delay (350);
  }
}

void loop() {
}
