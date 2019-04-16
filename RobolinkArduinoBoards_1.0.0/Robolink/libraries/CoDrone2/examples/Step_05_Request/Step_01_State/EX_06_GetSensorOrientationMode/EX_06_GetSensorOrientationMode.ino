/*---------------------------------------------------------------------------------------------------
  getSensorOrientationMode (센서 방향 값 가져오기)
  목표 : 센서 방향 값 가져오기의 사용 방법
  구문 : getSensorOrientationMode()
  설명 : 드론의 센서 방향 값을 가져옵니다.
         Normal, ReverseStart, Reversed 의 상태 값을 가집니다.
         드론이 뒤집혀 있는지 알수 있습니다.
         값이 1 인 경우 정상, 2인 경우 뒤집히기 시작, 3인 경우에 뒤집힌 상태를 뜻합니다.

         프로그램 입력이 완료되면 시리얼 모니터창을 열고 통신속도를 "57600bps"로 맞춥니다.
         
         센서 방향 값을 시리얼 모니터창에 출력하는 예제입니다.    
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin();             // 비행을 위한 초기화와 준비
}

void loop()
{
  // 드론의 센서 방향 값을 출력합니다.
  Serial.println("- State");
  Serial.print("getSensorOrientationMode\t");

  byte mode = CoDrone2.getSensorOrientationMode();       // 드론의 센서 방향 값을 가져옵니다.
  Serial.println(mode, HEX);                             // 드론의 센서 방향 값을 16진수로 출력합니다.

  displaySensorOrientationMode(mode);                     // 드론의 센서 방향 값의 정의를 출력합니다.

  Serial.println();
  delay(1000);
}

// 드론의 센서 방향 값의 정의를 출력합니다.
void displaySensorOrientationMode(byte mode)
{
  switch (mode)
  {
    case 0:
      Serial.println("NONE");   break;
    case 0x01:
      Serial.println("Normal");  break;
    case 0x02:
      Serial.println("ReverseStart");  break;
    case 0x03:
      Serial.println("Reversed");  break;
  }
}
