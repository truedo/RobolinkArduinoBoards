/*---------------------------------------------------------------------------------------------------
  go (방향을 설정하여 이동)
  목표 : 방향을 설정하여 이동에 대한 사용법
  구문 : go(방향, 출력, 지속시간)
  설명 : 쉬운 방식의 비행 이동입니다.
         입력한 방향으로 지속 시간과 힘에 따라 이동합니다.
                 
         - FORWARD : 전진
         - BACKWARD  : 후진
         - LEFT  : 왼쪽 이동
         - RIGHT : 오른쪽 이동
         - UP : 상승
         - DOWN : 하강

         이 예제는 드론이 이륙하여 앞으로 전진한 후에 착륙합니다.
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  int flightDuration = 10;       // 비행 지속 시간 설정
  
  CoDrone2.begin(flightDuration);   // 비행을 위한 초기화와 준비 - 프로그램 시작 후 10초 뒤에 착륙

  CoDrone2.takeoff();               // 이륙 후 5초간의 대기 시간 필요

  CoDrone2.hover(5);                // 5초간 맴돌기 (호버링)

  int direction = FORWARD;  
  int power = 30;
  float durationTime = 1;
  
  // 앞쪽 방향으로 30%의 힘으로 1초간 이동
  CoDrone2.go(direction, power, durationTime);

  CoDrone2.land();                  // 바닥으로 천천히 착륙
}

void loop()
{
}
