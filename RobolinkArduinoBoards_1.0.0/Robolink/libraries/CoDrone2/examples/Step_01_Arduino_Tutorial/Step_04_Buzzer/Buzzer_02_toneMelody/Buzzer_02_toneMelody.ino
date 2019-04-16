/*---------------------------------------------------------------------------------------------------
  Tone Melody (멜로디 연주하기)
  목표 : Tone의 사용방법 익히기
  구문 : tone(pin, frequency)
         tone(pin, frequency, duration)
  설명 : 이 기능은 코드로더 보드에 있는 부저로 음을 발생시켜 멜로디를 재생할수 있습니다.
         부저로 사용 가능한 핀 번호는 8번 입니다.
         입력 값은 다음과 같습니다.
        - pin: tone을 발생시킬 핀
        - frequency: tone의 주파수 (Hz 단위) - unsigned int
        - duration (옵션) : tone 의 지속 시간 (밀리초 단위) - unsigned long
        Tone 기능은 동작을 하기전에 핀모드를 출력으로 설정하므로, 따로 핀모드를 설정할 필요가 없습니다.     

        특정 음에 해당하는 주파수를  pitch,h에서 정의해 놓았습니다.
        이를 사용하면 원하는 음계를 낼 수 있습니다.

        음계는 다음과 같이 표시됩니다.       
         
        C 도
        D 레
        E 미
        F 파
        G 솔
        A 라
        B 시
        C 도           

        NOTE_C4는 4옥타브의 '도' 라는 의미입니다.
        NOTE_C6는 6옥타브의 '도' 라는 의미입니다.
        
       다음 예제는 '도,레,미' 멜로디를 출력 합니다.        
  ---------------------------------------------------------------------------------------------------*/

#include "pitches.h"  // 특정 음에 해당되는 주파수를 모아놓은 헤더파일

int buzzPin = 8;      // 변수에 부저 핀번호를 입력합니다.
int duration = 500;   // 음길이 : Tone 의 지속 시간 (밀리초 단위 500 = 0.5초)

void setup()
{    
  tone(buzzPin, NOTE_C4, duration);   // 4 옥타브 '도'를 0.5초 내기
  delay(500);                         // 0.5 초 기다리기 (500 Milliseconds = 0.5 second)
  
  tone(buzzPin, NOTE_D4, duration);   // 4 옥타브 '레'를 0.5초 내기
  delay(500);                         // 0.5 초 기다리기 (500 Milliseconds = 0.5 second)
  
  tone(buzzPin, NOTE_E4, duration);   // 4 옥타브 '미'를 0.5초 내기
  delay(500);                         // 0.5 초 기다리기 (500 Milliseconds = 0.5 second)
}

void loop() {
}
