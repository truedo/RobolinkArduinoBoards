/*---------------------------------------------------------------------------------------------------
  getFlightRecord (드론의 비행 기록 가져오기)
  목표 : 드론의 비행 기록 가져오기의 사용 방법
  구문 : getFlightRecord()
  설명 : 드론의 비행 기록을 가져옵니다.
         드론의 비행 시간, 이륙 횟수, 착륙 횟수, 사고 횟수를 표시합니다.

         프로그램 입력이 완료되면 시리얼 모니터창을 열고 통신속도를 "57600bps"로 맞춥니다.
         
         드론의 비행 기록을 시리얼 모니터창에 출력하는 예제입니다. 
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin();                       // 비행을 위한 초기화와 준비

  flightrecord record;
  record  = CoDrone2.getFlightRecord();   // 수신된 비행 기록 값을 저장

  // 비행 기록 값을 출력
  Serial.println("- FlightRecord");

  // 비행 시간  출력
  Serial.print("FlightTime\t");           
  Serial.print(record.hour);              // 드론의 비행시간 : 시간  
  Serial.print(" hour "); 
  Serial.print(record.minute);            // 드론의 비행시간 : 분  
  Serial.print(" minute ");
  Serial.print(record.second, 3);         // 드론의 비행시간 : 초  
  Serial.println(" second");              

  // 이륙 횟수 출력
  Serial.print("countTakeOff\t");
  Serial.println(record.takeoff);         // 드론의 이륙 횟수  

  // 착륙 횟수 출력
  Serial.print("countLanding\t");         // 드론의 착륙 횟수
  Serial.println(record.landing);

  // 사고 횟수 출력
  Serial.print("countAccident\t");        // 드론의 사고 횟수
  Serial.println(record.accident);
}

void loop()
{
}
