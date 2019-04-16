/*---------------------------------------------------------------------------------------------------
  getOptFlowPosition (옵티컬 플로우 값 가져오기)
  목표 : 옵티컬 플로우 값 가져오기의 사용 방법
  구문 : getOptFlowPosition()
  설명 : 드론의 옵티컬 플로우 값을 가져옵니다.
         x, y 값으로 표시됩니다.
          
         프로그램 입력이 완료되면 시리얼 모니터창을 열고 통신속도를 "57600bps"로 맞춥니다.
         
         옵티컬 플로우 x,y 값을 시리얼 모니터창에 출력하는 예제입니다. 
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin();                         // 비행을 위한 초기화와 준비
}

void loop()
{
  optdata opt;
  opt = CoDrone2.getOptFlowPosition();      // 수신된 옵티컬 플로우 값을 저장

  // 옵티컬 플로우 값을 출력
  Serial.println("- Optical Flow");       

  Serial.print("opt x : \t");               // 옵티컬 플로우 x 값
  Serial.println(opt.x);
  Serial.print("opt y : \t");               // 옵티컬 플로우 y 값
  Serial.println(opt.y);

  Serial.println();
  delay(500);
}
