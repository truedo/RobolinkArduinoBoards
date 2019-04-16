/*****************************************************************
  getState - 드론의 현재 상태값을 표시합니다.
  상태값은 다음과 같습니다.
  fMode_Ready     준비 상태
  fMode_TakeOff   이륙 상태
  fMode_Flight    비행 상태
  fMode_Stop      정지 상태
  fMode_Landing   착륙 상태
  fMode_Reverse   뒤집기 실행 상태
  fMode_Accident  부딪히는 등의 사고가 상태

  드론을 켠 상태에서 PC와 보드를 USB로 연결합니다.
  아두이노 창의 시리얼 모니터를 열고 통신 속도를 115200bps로 설정합니다.  
*******************************************************************/

#include <CodeLoader.h>

void setup()
{
  CodeLoaderBegin(0);                       // 준비 및 타임 아웃 셋팅(초) - 0초 : 타임 아웃 사용 안함
}

void loop()
{
  int state = CoDrone.getState();          // 데이터 요청 및 저장 

  Serial.print("Drone State : \t");

  if (state == fMode_Ready)                Serial.println("Ready");
  else if (state == fMode_TakeOff)         Serial.println("TakeOff");
  else if (state == fMode_Flight)          Serial.println("Flight");
  else if (state == fMode_Stop)            Serial.println("Stop");
  else if (state == fMode_Landing)         Serial.println("Landing");
  else if (state == fMode_Reverse)         Serial.println("Reverse");
  else if (state == fMode_Accident)        Serial.println("Accident");

  delay(100);
}
