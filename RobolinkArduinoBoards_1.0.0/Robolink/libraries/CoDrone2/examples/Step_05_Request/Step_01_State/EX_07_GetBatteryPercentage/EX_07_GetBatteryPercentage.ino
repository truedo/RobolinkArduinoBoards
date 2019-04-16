/*---------------------------------------------------------------------------------------------------
  getBatteryPercentage (배터리 잔량 확인)
  목표 : 배터리 잔량 확인의 사용 방법
  구문 : getBatteryPercentage()
  설명 : 현재 드론의 배터리 잔량을 확인합니다.
         배터리양을 최저 0에서 최고 100의 값으로 나타냅니다.
         
         프로그램 입력이 완료되면 시리얼 모니터창을 열고 통신속도를 "57600bps"로 맞춥니다.
         
         배터리 잔량 값을 시리얼 모니터창에 출력하는 예제입니다.    
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin();             // 비행을 위한 초기화와 준비
}

void loop()
{
  // 드론의 배터리 잔량을 출력합니다.
  Serial.println("- State");
  Serial.print("getBatteryPercentage\t");
 
  byte battery = CoDrone2.getBatteryPercentage(); // 드론의 배터리 잔량을 가져옵니다.
  
  Serial.println(battery);                        // 드론의 배터리 잔량을 표시합니다.
  
  Serial.println();
  delay(1000);
}
