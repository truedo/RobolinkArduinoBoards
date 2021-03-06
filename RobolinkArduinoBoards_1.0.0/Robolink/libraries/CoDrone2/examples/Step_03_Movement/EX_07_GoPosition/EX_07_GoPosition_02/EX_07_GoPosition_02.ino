/*---------------------------------------------------------------------------------------------------
  goPosition (위치로 이동)
  목표 : goPosition의 사용 방법
  구문 : goPosition(이동방향1, 이동거리1, 이동방향2, 이동거리2, 이동시간)
  설명 : 해당하는 위치로 이동합니다.
         원하는 위치와 시간에 따라 드론의 움직임을 제어할 수 있습니다.
         입력한 이동 방향과 이동거리, 이동시간에 따라 이동합니다.
         드론의 현재 기준으로  앞, 뒤, 왼쪽, 오른쪽, 위, 아래의 방향을 나타냅니다.
         
         여러 축(x,y,z)의 이동 명령을 동시에 할 수 있습니다.
         이동 거리는 m 단위입니다.
         이동 시간이 함께 사용됩니다.
         
         이 예제는 드론이 앞과 오른쪽 대각선방향로 뒤와 왼쪽 대각선 방향으로 이동합니다.
  ---------------------------------------------------------------------------------------------------*/

#include "CoDrone2.h"

int direction1 = 0;
int distance1 = 0;

int direction2 = 0;
int distance2 = 0;

int time = 0;

void setup()
{
  int flightDuration = 20;          // 비행 지속 시간 설정

  CoDrone2.begin(flightDuration);     // 비행을 위한 초기화와 준비 - 프로그램 시작 후 20초 뒤에 착륙

  CoDrone2.takeoff();               // 이륙 후 5초간의 대기 시간 필요

  CoDrone2.hover(5);                // 5초간 맴돌기 (호버링)

  // - 이동 방향과 거리, 시간 입력

  //------------------------------ 앞과 오른쪽 대각선 방향으로 이동 ----------------------------//

  direction1 = FORWARD;  // 방향 : 전진
  distance1 = 1;         // 거리 : 1m

  direction2 = RIGHT;  // 방향 : 오른쪽
  distance2 = 1;         // 거리 : 1m
  
  time = 2;             // 시간 : 2초  

  CoDrone2.goPositon(direction1, distance1, direction2, distance2, time);      // (FORWARD 1m) (RIGHT 1m) 를 2초 안에 이동
  CoDrone2.hover(1);                                  // 1초간 맴돌기 (호버링)
  
  //------------------------------- 뒤와 왼쪽 대각선 방향으로 이동 ---------------------------//

  CoDrone2.goPositon(BACKWARD, 1, LEFT, 1, 2);  // (BACKWARD 1m) (LEFT 1m) 를 2초 안에 이동
  CoDrone2.hover(1);                    // 1초간 맴돌기 (호버링)

  CoDrone2.land();                     // 바닥으로 천천히 착륙
}

void loop()
{
}
