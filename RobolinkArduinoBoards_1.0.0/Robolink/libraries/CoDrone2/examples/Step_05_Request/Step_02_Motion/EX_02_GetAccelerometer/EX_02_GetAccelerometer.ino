/*---------------------------------------------------------------------------------------------------
  getAccelerometer (가속도 센서 값 가져오기)
  목표 : 드론의 가속도 센서 값 가져오기의 사용 방법
  구문 : getAccelerometer()
  설명 : 드론의 가속도 센서 값을 가져옵니다.
         x,y,z축의 값을 표시합니다.

         프로그램 입력이 완료되면 시리얼 모니터창을 열고 통신속도를 "57600bps"로 맞춥니다.
         
         가속도 x, y, z 축의 값을 시리얼 모니터창에 출력하는 예제입니다.  
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin();                         // 비행을 위한 초기화와 준비
}

void loop()
{
  acceldata accel;
  accel = CoDrone2.getAccelerometer();     // 수신된 가속도 센서 값을 저장

  // 드론의 가속도 센서 값을 출력합니다.
  Serial.println("- Accelerometer");
  Serial.print("accel x : \t");
  Serial.println(accel.x);
  Serial.print("accel y : \t");
  Serial.println(accel.y);
  Serial.print("accel z : \t");
  Serial.println(accel.z);

  Serial.println();
  delay(500);
}
