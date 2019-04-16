/*---------------------------------------------------------------------------------------------------
  getRawMotion (가공되지 않은 모션 센서값 가져오기)
  목표 : 가공되지 않은 모션 센서값 가져오기에 대한 사용법
  구문 : getRawMotion()
  설명 : 가공되지 않은 모션 센서(가속도, 자이로) 자체의 값을 가져옵니다.
         드론에서는 센서에서 이렇게 입력된 값을 다양한 방법으로 계산하여 실제 자세를 제어합니다.
         
         프로그램 입력이 완료되면 시리얼 모니터창을 열고 통신속도를 "57600bps"로 맞춥니다.
         
         드론의 가속도와 자이로 센서 값을 시리얼 모니터창에 출력하는 예제입니다. 
  ---------------------------------------------------------------------------------------------------*/ 

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin();   // 비행을 위한 초기화와 준비
}

void loop()
{
  rawmotion motion;
  motion = CoDrone2.getRawMotion();    // 가공되지 않은 모션 센서값을 저장
  
  // 모션 센서값 출력
  Serial.println("- RAW Motion");
  Serial.print("accel x : \t");
  Serial.println(motion.x);
  Serial.print("accel y : \t");
  Serial.println(motion.y);
  Serial.print("accel z : \t");
  Serial.println(motion.z);
  Serial.print("angle roll : \t");
  Serial.println(motion.roll);
  Serial.print("angle pitch : \t");
  Serial.println(motion.pitch);
  Serial.print("angle yaw : \t");
  Serial.println(motion.yaw);

  Serial.println();
  delay(500);
}
