/*****************************************************************
  getDroneTemp - 드론 온도 표시
  드론의 현재 온도를 표시합니다.

  드론을 켠 상태에서 PC와 보드를 USB로 연결합니다.
  아두이노 창의 시리얼 모니터를 열고 통신 속도를 115200bps로 설정합니다.

*******************************************************************/

#include <CodeLoader.h>

void setup()
{
  CodeLoaderBegin(0);                               // 준비 및 타임 아웃 셋팅(초) - 0초 : 타임 아웃 사용 안함
}

void loop()
{
  int temperature = CoDrone.getDroneTemp();       //  데이터 요청 및 저장 

  Serial.println("");
  Serial.println("--------- Now -----------");
  Serial.print("temperature : \t");
  Serial.println(temperature);

  delay(100);
}
