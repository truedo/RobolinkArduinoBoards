/*---------------------------------------------------------------------------------------------------
  getPosition (드론의 위치 가져오기)
  목표 : 드론의 위치 가져오기에 대한 사용법
  구문 : getPosition()
  설명 : 드론의 위치를 가져옵니다.
         드론의 위치를 x, y, z 값으로 표시합니다. (m 단위)
         드론의 처음 위치를 기준(0, 0, 0)으로 표시됩니다.  

         프로그램 입력이 완료되면 시리얼 모니터창을 열고 통신속도를 "57600bps"로 맞춥니다.
         
         위치를 x,y,z 값으로 시리얼 모니터창에 출력하는 예제입니다. 
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin();                   // 비행을 위한 초기화와 준비
}

void loop()
{
  position pos;
  pos = CoDrone2.getPosition();        // 드론의 위치 값을 저장
  
  // 위치 값을 출력
  Serial.println("- position");
  Serial.print("position x : \t");    // 드론의 x 위치 값
  Serial.println(pos.x);
  Serial.print("position y : \t");    // 드론의 x 위치 값
  Serial.println(pos.y);
  Serial.print("position z : \t");    // 드론의 z 위치 값
  Serial.println(pos.z);

  Serial.println();
  delay(500);
}
