/*---------------------------------------------------------------------------------------------------
  getGyroAngles (각도 값 가져오기)
  목표 : 자세 각도 값 가져오기의 사용 방법
  구문 : getGyroAngles()
  설명 : 드론의 자세(각도) 값을 가져옵니다.
         가속도와 자이로값으로 만들어진 각도 값입니다.
         롤, 피치, 요의 각도를 표시합니다.

         프로그램 입력이 완료되면 시리얼 모니터창을 열고 통신속도를 "57600bps"로 맞춥니다.
         
         드론의 롤, 피치, 요 각도를 시리얼 모니터창에 출력하는 예제입니다. 
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin();                         // 비행을 위한 초기화와 준비
}

void loop()
{
  angledata angle;
  angle = CoDrone2.getGyroAngles();       // 수신된 드론의 각도 값을 저장

  // 드론의 각도 값을 출력합니다.
  Serial.println("- GyroAngles");
  Serial.print("angle roll : \t");
  Serial.println(angle.roll);
  Serial.print("angle pitch : \t");
  Serial.println(angle.pitch);
  Serial.print("angle yaw : \t");
  Serial.println(angle.yaw);

  Serial.println();
  delay(500);
  
}
