/*---------------------------------------------------------------------------------------------------
  getRange (드론의 거리 센서 값 가져오기)
  목표 : 드론의 거리 센서 값 가져오기의 사용 방법
  구문 : getRange()
  설명 : 드론의 거리 센서 값을 가져옵니다.
  
         - bottom : 드론에 기본적으로 장착되어 있는 센서(높이를 측정)
         - front : 코드론2에 탑재되는 정면 감지용 센서
         - left : 좌측 감지용 센서 (추가적으로 센서를 구매하여 장착)
         - right : 우측 감지용 센서 (추가적으로 센서를 구매하여 장착)
         
         프로그램 입력이 완료되면 시리얼 모니터창을 열고 통신속도를 "57600bps"로 맞춥니다.
         
         드론의 거리 센서 값을 시리얼 모니터창에 출력하는 예제입니다. 
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin();                 // 비행을 위한 초기화와 준비
}
void loop()
{
  rangeData range;
  range = CoDrone2.getRange();      // 수신된 드론의 각도 값을 저장

  Serial.println("- Range Sensor");
  
  Serial.print("front : \t");       
  Serial.println(range.front);      // 정면 센서 감지 값을 표시합니다.
  
  Serial.print("left  : \t"); 
  Serial.println(range.left);       // 왼쪽 센서 감지 값을 표시합니다.
  
  Serial.print("right : \t");
  Serial.println(range.right);      // 오른쪽 센서 감지 값을 표시합니다.
  
  Serial.print("bottom : \t");
  Serial.println(range.bottom);     // 바닥 센서 감지 값을 표시합니다.
  
  delay(100);
}
