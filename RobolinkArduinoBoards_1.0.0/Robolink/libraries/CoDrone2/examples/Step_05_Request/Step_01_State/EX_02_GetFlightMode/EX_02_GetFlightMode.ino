/*---------------------------------------------------------------------------------------------------
  getFlightMode (비행 제어기 동작 상태 값 가져오기)
  목표 : 비행 제어기 동작 상태 값 가져오기의 사용 방법
  구문 : getFlightMode()
  설명 : 현재 드론의 비행 제어기 동작 상태 값을 가져옵니다.
         Ready, Start, Takeoff, Flight, Landing, Flip, Reverse, Stop, Accident, Error의 상태 값을 가집니다.
        
         프로그램 입력이 완료되면 시리얼 모니터창을 열고 통신속도를 "57600bps"로 맞춥니다.
         
         비행 제어기 동작 상태 값을 시리얼 모니터창에 출력하는 예제입니다.     
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin();             // 비행을 위한 초기화와 준비
}

void loop()
{
  // 비행 제어기 동작 상태 값을 출력합니다.
  Serial.println("- State");
  Serial.print("getFlightMode\t");

  byte mode = CoDrone2.getFlightMode();    // 비행 제어기 동작 상태 값을 가져옵니다.
  Serial.println(mode, HEX);               // 비행 제어기 동작 상태 값을 16진수로 출력합니다.

  displayFlightMode(mode);                  // 비행 제어기 동작 상태 값의 정의를 출력합니다.
  
  Serial.println();
  delay(1000);
}

// 비행 제어기 동작 상태 값의 정의를 출력하는 함수입니다.
void displayFlightMode(byte mode)
{
  switch (mode)
  {
    case 0:
      Serial.println("NONE");   break;
    case 0x10:
      Serial.println("Ready");  break;
    case 0x11:
      Serial.println("Start");  break;
    case 0x12:
      Serial.println("TakeOff"); break;
    case 0x13:
      Serial.println("Flight"); break;
    case 0x14:
      Serial.println("Landing"); break;
    case 0x15:
      Serial.println("Flip");   break;
    case 0x16:
      Serial.println("Reverse"); break;
    case 0x20:
      Serial.println("Stop");   break;
    case 0x30:
      Serial.println("Accident"); break;
    case 0x31:
      Serial.println("Error");    break;
  }
}
