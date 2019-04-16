//----------------------------- Mission 답안 -----------------------------//

void setup()
{
  Serial.begin(57600);                        // 시리얼 통신을 사용하고, 통신 속도를 57600 bps로 설정
  
  Serial.println("Hi~");                      // 문자를 출력하고 줄을 바꿉니다.

  Serial.print("My Name is ");                // 문자를 출력하고 줄을 바꾸지 않습니다.

  Serial.println("Kevin.");                   // 문자를 출력하고 줄을 바꿉니다. 이름을 입력합니다.

  Serial.print("My hobby is ");               // 문자를 출력하고 줄을 바꾸지 않습니다.

  Serial.println("listening to music.");      // 문자를 출력하고 줄을 바꿉니다. 취미를 입력합니다.
  
}

void loop()
{  
}
