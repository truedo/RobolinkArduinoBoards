/*---------------------------------------------------------------------------------------------------
  getSystemMode (드론의 시스템 동작 상태 값을 가져오기)
  목표 : 상태값 가져오기의 사용 방법
  구문 : getSystemMode()
  설명 : 현재 드론의 시스템 동작 상태 값을 가져옵니다.
         Boot, Start, Running, ReadyToReset, Error 의 상태를 가집니다.

         프로그램 입력이 완료되면 시리얼 모니터창을 열고 통신속도를 "57600bps"로 맞춥니다.
         
         드론의 시스템 동작 상태 값을 시리얼 모니터창에 출력하는 예제입니다.         
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin();             // 비행을 위한 초기화와 준비
}

void loop()
{
  // 드론의 동작 상태 값을 출력합니다.
  Serial.println("- State");
  Serial.print("getSystemMode\t");

  byte mode = CoDrone2.getSystemMode();      // 드론의 시스템 동작 상태 값을 가져옵니다.
  Serial.println(mode, HEX);                 // 드론의 시스템 동작 상태 값을 16진수로 출력합니다.

  displaySystemMode(mode);                    // 드론의 시스템 동작 상태 값의 정의를 출력합니다.

  Serial.println();
  delay(1000);
}

// 드론의 시스템 동작 상태 값의 정의를 출력하는 함수입니다.
void displaySystemMode(byte mode)
{
  switch (mode)
  {
    case 0:
      Serial.println("NONE");   break;
    case 0x01:
      Serial.println("Boot");  break;
    case 0x02:
      Serial.println("Start");  break;
    case 0x03:
      Serial.println("Running"); break;
    case 0x04:
      Serial.println("ReadyToReset"); break;
    case 0x05:
      Serial.println("Error"); break;
  }
}
