/*---------------------------------------------------------------------------------------------------
  getTrim (트림(미세 조정) 설정 값 가져오기)
  목표 : 트림(미세 조정) 값 가져오기의 사용 방법
  구문 : getTrim()
  설명 : 드론의 트림 설정값을 가져옵니다.

         프로그램 입력이 완료되면 시리얼 모니터창을 열고 통신속도를 "57600bps"로 맞춥니다.
         
         미세조정 값을 시리얼 모니터창에 출력하는 예제입니다. 
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin();                   // 비행을 위한 초기화와 준비
}

void loop()
{
  // 트림 데이터를 출력합니다.
  trimdata trim;
  trim = CoDrone2.getTrim();                     // 수신된 트림데이터 값을 저장

  Serial.println("- Trim");
  Serial.print("trim roll : \t");
  Serial.println(trim.roll);
  Serial.print("trim pitch : \t");
  Serial.println(trim.pitch);
  Serial.print("trim yaw : \t");
  Serial.println(trim.yaw);
  Serial.print("trim throttle : \t");
  Serial.println(trim.throttle);

  Serial.println();
  delay(500);
}
