/*---------------------------------------------------------------------------------------------------
  getAngularSpeed (자이로 센서 값 가져오기)
  목표 : 드론의 자이로 센서 값 가져오기의 사용 방법
  구문 : getAngularSpeed()
  설명 : 드론의 자이로 센서 값을 가져옵니다.
         롤, 피치, 요로 자이로 값을 표시합니다.

         프로그램 입력이 완료되면 시리얼 모니터창을 열고 통신속도를 "57600bps"로 맞춥니다.
         
         자이로 센서의 롤, 피치, 요를 시리얼 모니터창에 출력하는 예제입니다.    
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin();
}

void loop()
{
  gyrodata gyro;
  gyro = CoDrone2.getAngularSpeed();     // 수신된 드론의 자이로 센서 값을 저장

  // 드론의 자이로 센서 값을 출력합니다.
  Serial.println("- AngularSpeed");
  Serial.print("gyro roll : \t");
  Serial.println(gyro.roll);
  Serial.print("gyro pitch : \t");
  Serial.println(gyro.pitch);
  Serial.print("gyro yaw : \t");
  Serial.println(gyro.yaw);

  Serial.println();
  delay(500);
}
