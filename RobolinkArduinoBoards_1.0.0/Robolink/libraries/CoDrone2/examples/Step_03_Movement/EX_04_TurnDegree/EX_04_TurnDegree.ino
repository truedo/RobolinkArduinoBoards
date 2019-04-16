/*---------------------------------------------------------------------------------------------------
  turnDegree (각도로 방향 회전)
  목표 : 각도로 방향 회전에 대한 사용법
  구문 : turnDegree(회전방향, 각도, 지속 시간)
  설명 : 입력한 방향의 각도로 드론을 회전시킵니다.
         입력한 각도와 지속시간에 따라 회전속도가 정해집니다.

        - LEFT  : 왼쪽 회전
        - RIGHT : 오른쪽 회전      
          
        이 예제는 드론이 입력한 방향으로 입력한 각도를 회전하는 예제입니다.        
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

void setup()
{
  int flightDuration = 10;          // 비행 지속 시간 설정
  
  CoDrone2.begin(flightDuration);     // 비행을 위한 초기화와 준비 - 프로그램 시작 후 10초 뒤에 착륙

  CoDrone2.takeoff();                 // 이륙 후 5초간의 대기 시간 필요

  CoDrone2.hover(5);                  // 5초간 맴돌기 (호버링)

  int direction = RIGHT;
  float degree = 90;
  int time = 3;
  
  // 오른쪽 방향으로 90도 각도를 3초안에 회전
  CoDrone2.turnDegree(direction, degree, time);  

  CoDrone2.land();                    // 바닥으로 천천히 착륙
}

void loop()
{
}
