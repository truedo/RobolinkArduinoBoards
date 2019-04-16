/*---------------------------------------------------------------------------------------------------
  LED - GyroAngleToColor
  
  자이로 센서 값에 따라 드론의 LED 색과 밝기가 변합니다.
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  CoDrone2.begin();               // 비행을 위한 초기화와 준비
}

void loop()
{
  angledata angle;
  angle = CoDrone2.getGyroAngles();       // 수신된 드론의 각도 값을 저장

  // 가져온 드론의 각도 값을 출력합니다.
  Serial.println("- GyroAngles");
  Serial.print("angle roll : \t");
  Serial.println(angle.roll);
  Serial.print("angle pitch : \t");
  Serial.println(angle.pitch);
  Serial.print("angle yaw : \t");
  Serial.println(angle.yaw);

  // 가져온 드론의 각도 값이 음수(-)라면 양수(+)로 변경합니다.
  if (angle.roll < 0)   angle.roll =  -angle.roll;
  if (angle.pitch < 0)  angle.pitch =  -angle.pitch;
  if (angle.yaw < 0)    angle.yaw =  -angle.yaw;

  // 가져온 각도 값의 범위를 색상의 입력색과의 범위에 맞추어줍니다.(0~180 를 0~255 범위로 변경) map()함수를 사용합니다.
  byte red = map(angle.roll, 0, 180, 0, 255);
  byte green = map(angle.pitch, 0, 180, 0, 255);
  byte blue = map(angle.yaw, 0, 180, 0, 255);

  // 변환된 색상값을 출력합니다.
  Serial.println("- Colors");
  Serial.print("red : \t");
  Serial.println(red);
  Serial.print("green : \t");
  Serial.println(green);
  Serial.print("blue : \t");
  Serial.println(blue);
  Serial.println();

  CoDrone2.setLED(red, green , blue, BodyHold, 255);    // 변환된 드론의 각도 값이 색상으로 표시됩니다.

  delay(50);
}
