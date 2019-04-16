/*---------------------------------------------------------------------------------------------------
  getHeadlessMode (방위 기준 값을 가져오기)
  목표 : 방위 기준 값 가져오기의 사용 방법
  구문 : getHeadlessMode()
  설명 : 조종시 방향의 기준 값을 가져옵니다.
         Headless는 사용자 중심 좌표로써 드론이 어느 방향을 바라보더라도 이륙 할때의 방향 또는 사용자가 지정한 방향을 기준으로 움직입니다.
         Normal은 드론 중심 좌표로써 드론이 현재 향하는 방향을 기준으로 움직입니다.
         기본 설정은 Normal 입니다.

         프로그램 입력이 완료되면 시리얼 모니터창을 열고 통신속도를 "57600bps"로 맞춥니다.
         
         방위 기준 값을 시리얼 모니터창에 출력하는 예제입니다.     
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin();             // 비행을 위한 초기화와 준비
}

void loop()
{
  // 방위 기준 값을 출력합니다.
  Serial.println("- State");
  Serial.print("getHeadlessMode\t");

  byte mode = CoDrone2.getHeadlessMode();      // 드론의 방위 기준 값을 가져옵니다.
  Serial.println(mode, HEX);                   // 드론의 방위 기준 값을 16진수로 출력합니다.

  displayHeadlessMode(mode);                    // 드론의 방위 기준 값의 정의를 출력합니다.

  Serial.println();
  delay(1000);
}

// 드론의 방위 기준 값의 정의를 출력하는 함수입니다.
void displayHeadlessMode(byte mode)
{
  switch (mode)
  {
    case 0:
      Serial.println("NONE");   break;
    case 0x01:
      Serial.println("Headless");  break;
    case 0x02:
      Serial.println("Normal");  break;
  }
}
