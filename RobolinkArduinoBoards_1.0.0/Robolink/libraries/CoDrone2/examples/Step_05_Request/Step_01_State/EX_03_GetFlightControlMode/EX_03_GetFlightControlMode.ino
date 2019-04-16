/*---------------------------------------------------------------------------------------------------
  getFlightControlMode (비행 제어 모드 값 가져오기)
  목표 : 비행 제어 모드 값 가져오기의 사용 방법
  구문 : getFlightControlMode()
  설명 : 현재 드론의 비행 제어 모드 값을 가져옵니다.
         다음과 같은 제어모드를 가지고 있습니다.
         Attitude (자세 - X,Y는 각도(deg)로 입력받음, Z,Yaw는 속도(m/s)로 입력 받음)
         Position (위치 - X,Y,Z,Yaw는 속도(m/s)로 입력 받음)
         Function (기능 - X,Y,Z,Yaw는 속도(m/s)로 입력 받음)
         
         프로그램 입력이 완료되면 시리얼 모니터창을 열고 통신속도를 "57600bps"로 맞춥니다.
         
         비행 제어 모드 값을 시리얼 모니터창에 출력하는 예제입니다.  
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin();             // 비행을 위한 초기화와 준비
}

void loop()
{
  // 비행 제어 모드 값을 출력합니다.
  Serial.println("- State");
  Serial.print("getFlightControlMode\t");

  byte mode = CoDrone2.getFlightControlMode();      // 비행 제어 모드 값을 가져옵니다.
  Serial.println(mode, HEX);                        // 비행 제어 모드 값을 16진수로 출력합니다.

  displayFlightControlMode(mode);                    // 비행 제어 모드 상태 값의 정의를 출력합니다.

  Serial.println();
  delay(1000);
}

// 비행 제어 모드 상태 값의 정의를 출력하는 함수입니다.
void displayFlightControlMode(byte mode)
{
  switch (mode)
  {
    case 0:
      Serial.println("NONE");   break;
    case 0x10:
      Serial.println("Attitude");  break;
    case 0x11:
      Serial.println("Position");  break;
    case 0x12:
      Serial.println("Function"); break;
  }
}
