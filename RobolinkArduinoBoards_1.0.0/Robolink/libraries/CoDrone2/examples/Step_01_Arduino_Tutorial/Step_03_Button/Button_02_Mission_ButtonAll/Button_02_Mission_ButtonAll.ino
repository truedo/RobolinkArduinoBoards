/*---------------------------------------------------------------------------------------------------
  - Mission - Button All (두개 버튼의 디지털 상태 값을 읽기)
  목표 : digitalRead의 사용방법 익히기
         여러개의 입력에 대한 처리방법
  구문 : digitalRead(핀번호)
  설명 : 이 기능은 코드로더 보드에 있는 버튼의 디지털 상태 값을 읽을 수 있습니다.
         버튼으로 사용 가능한 번호는 2,3 입니다.
         버튼을 누르지 않을 때의 상태값은 HIGH(1)이며, 누른 경우에는 LOW(0) 값을 나타냅니다.

         프로그램입력이 완료되면 시리얼 모니터창을 열고 통신속도를 "57600bps"로 맞춥니다.
         
         다음 예제를 수정하여 두개 버튼의 디지털 상태를 시리얼 모니터창에 출력하도록 만들어 보세요.          
  ---------------------------------------------------------------------------------------------------*/

void setup()
{
  Serial.begin(57600); // 시리얼 통신을 사용하고, 통신 속도를 57600 bps로 설정
  pinMode(2, INPUT);    // 2번 핀을 입력으로 설정 (사용 가능한 버튼 번호 : 2, 3)
  pinMode(3, INPUT);    // 3번 핀을 입력으로 설정 (사용 가능한 버튼 번호 : 2, 3)
}

void loop()
{
  int state = digitalRead(2);  // 버튼의 상태값을 읽어옵니다.
  Serial.print("State : ");   // "State : " 문자열 출력
  Serial.println(state);      // 버튼의 상태값을 출력
}
