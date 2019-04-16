/*---------------------------------------------------------------------------------------------------
  setEventLED (이벤트 LED 색상 지정)
  목표 : 이벤트 LED 색상 지정의 사용법
  구문 : setEventLED(색상, 조명 패턴, 패턴 간격, 반복 횟수)
         setEventLED(빨강색, 녹색, 파랑색, 조명 패턴, 패턴 간격, 반복 횟수)
  설명 : 이 기능은 LED가 반복 횟수만큼 작동하고 원래의 LED 상태로 돌아오게 됩니다.
         LED 색상, 조명 패턴 및 조명 패턴 간격을 설정합니다.
         빨강, 녹색 및 파랑 입력 값 또는 미리 정의 된 색상을 사용하여 색상을 설정할 수 있습니다.

         조명 패턴
         - BodyHold          : 지정한 색상을 계속 켭니다. 간격 값이 클수록 밝기가 밝아집니다.
         - BodyFlicker       : 지정한 색상으로 깜빡입니다. 간격 값이 작을 수록 빠르게 깜빡입니다.
         - BodyFlickerDouble : 지정한 색상으로 두 번씩 깜빡입니다. 간격 값이 작을 수록 빠르게 깜빡입니다.
         - BodyDimming       : 점점 밝아 졌다가 점점 어두워졌다를 반복합니다. 간격 값이 작을 수록 빠르게 변합니다.
         - BodySunrise       : 꺼진 상태에서 점점 밝아짐니다. 간격 값이 작을 수록 빠르게 변합니다.
         - BodySunset        : 켜진 상태에서 점점 어두워짐니다. 간격 값이 작을 수록 빠르게 변합니다.

        프로그램이 실행되면 드론의 앞쪽에 장착된 LED의 색상과 패턴이 달라집니다.
        반복 횟수만큼 실행하고 원래의 LED 패턴으로 돌아오게 됩니다.
  ---------------------------------------------------------------------------------------------------*/
#include "CoDrone2.h"

int colorR = 0;
int colorG = 0;
int colorB = 0;

void setup()
{
  CoDrone2.begin();     // Initialization and preparation for flight

  // - 정의된 색상을 사용하는 경우

  // 흰색으로 켜기
  CoDrone2.setEventLED(White, BodyHold, 10, 100);
  delay(3000);

  // 녹색으로 깜빡이기
  CoDrone2.setEventLED(Green, BodyFlicker, 20, 10);
  delay(3000);

  // 노란색으로 두번씩 깜빡이기
  CoDrone2.setEventLED(Yellow, BodyFlickerDouble, 10, 10);
  delay(3000);

  // 보라색으로 점점 밝아졌다 어두워졌다 반복하기
  CoDrone2.setEventLED(Purple, BodyDimming, 1, 10);
  delay(5000);



  // - R,G,B 색상을 사용하는 경우

  // 흰색으로 켜기
  colorR = 255;
  colorG = 255;
  colorB = 255;
  CoDrone2.setEventLED(colorR, colorG, colorB, BodyHold, 10, 100);
  delay(3000);

  // 녹색으로 깜빡이기
  colorR = 0;
  colorG = 255;
  colorB = 0;
  CoDrone2.setEventLED(colorR, colorG, colorB, BodyFlicker, 20, 10);
  delay(3000);

  // 노란색으로 두번씩 깜빡이기
  colorR = 255;
  colorG = 255;
  colorB = 0;

  CoDrone2.setEventLED(colorR, colorG, colorB, BodyFlickerDouble, 10, 10);
  delay(3000);

  // 보라색으로 점점 밝아졌다 어두워졌다 반복하기
  colorR = 255;
  colorG = 0;
  colorB = 255;

  CoDrone2.setEventLED(colorR, colorG, colorB, BodyDimming, 1, 10);
}

void loop()
{
}

/*   -- 사전 정의된 LED 색상  --
    AliceBlue, AntiqueWhite, Aqua,
    Aquamarine, Azure, Beige,
    Bisque, Black, BlanchedAlmond,
    Blue, BlueViolet, Brown,
    BurlyWood, CadetBlue, Chartreuse,
    Chocolate, Coral, CornflowerBlue,
    Cornsilk, Crimson, Cyan,
    DarkBlue, DarkCyan, DarkGoldenRod,
    DarkGray, DarkGreen, DarkKhaki,
    DarkMagenta, DarkOliveGreen, DarkOrange,
    DarkOrchid, DarkRed, DarkSalmon,
    DarkSeaGreen, DarkSlateBlue, DarkSlateGray,
    DarkTurquoise, DarkViolet, DeepPink,
    DeepSkyBlue, DimGray, DodgerBlue,
    FireBrick, FloralWhite, ForestGreen,
    Fuchsia, Gainsboro, GhostWhite,
    Gold, GoldenRod, Gray,
    Green, GreenYellow, HoneyDew,
    HotPink, IndianRed, Indigo,
    Ivory, Khaki, Lavender,
    LavenderBlush, LawnGreen, LemonChiffon,
    LightBlue, LightCoral, LightCyan,
    LightGoldenRodYellow, LightGray, LightGreen,
    LightPink, LightSalmon, LightSeaGreen,
    LightSkyBlue, LightSlateGray, LightSteelBlue,
    LightYellow, Lime, LimeGreen,
    Linen, Magenta, Maroon,
    MediumAquaMarine, MediumBlue, MediumOrchid,
    MediumPurple, MediumSeaGreen, MediumSlateBlue,
    MediumSpringGreen, MediumTurquoise, MediumVioletRed,
    MidnightBlue, MintCream, MistyRose,
    Moccasin, NavajoWhite, Navy,
    OldLace, Olive, OliveDrab,
    Orange, OrangeRed, Orchid,
    PaleGoldenRod, PaleGreen, PaleTurquoise,
    PaleVioletRed, PapayaWhip, PeachPuff,
    Peru, Pink, Plum,
    PowderBlue, Purple, RebeccaPurple,
    Red, RosyBrown, RoyalBlue,
    SaddleBrown, Salmon, SandyBrown,
    SeaGreen, SeaShell, Sienna,
    Silver, SkyBlue, SlateBlue,
    SlateGray, Snow, SpringGreen,
    SteelBlue, Tan, Teal,
    Thistle, Tomato, Turquoise,
    Violet, Wheat, White,
    WhiteSmoke, Yellow, YellowGreen,
    EndOfColor
*/
/*  -- LED 패턴 정의 --
    RearNone = 0x10,
    RearManual,             // 수동 제어
    RearHold,               // 지정한 색상을 계속 켬
    RearFlicker,            // 깜빡임
    RearFlickerDouble,      // 깜빡임(두 번 깜빡이고 깜빡인 시간만큼 꺼짐)
    RearDimming,            // 밝기 제어하여 천천히 깜빡임

    BodyNone = 0x20,
    BodyManual,             // 수동 제어
    BodyHold,               // 지정한 색상을 계속 켬
    BodyFlicker,            // 깜빡임
    BodyFlickerDouble,      // 깜빡임(두 번 깜빡이고 깜빡인 시간만큼 꺼짐)
    BodyDimming,            // 밝기 제어하여 천천히 깜빡임

    ANone = 0x30,
    AManual,                // 수동 제어
    AHold,                  // 지정한 색상을 계속 켬
    AFlicker,               // 깜빡임
    AFlickerDouble,         // 깜빡임(두 번 깜빡이고 깜빡인 시간만큼 꺼짐)
    ADimming,               // 밝기 제어하여 천천히 깜빡임

    BNone = 0x40,
    BManual,                // 수동 제어
    BHold,                  // 지정한 색상을 계속 켬
    BFlicker,               // 깜빡임
    BFlickerDouble,         // 깜빡임(두 번 깜빡이고 깜빡인 시간만큼 꺼짐)
    BDimming,               // 밝기 제어하여 천천히 깜빡임

    CNone = 0x50,
    CManual,                // 수동 제어
    CHold,                  // 지정한 색상을 계속 켬
    CFlicker,               // 깜빡임
    CFlickerDouble,         // 깜빡임(두 번 깜빡이고 깜빡인 시간만큼 꺼짐)
    CDimming,               // 밝기 제어하여 천천히 깜빡임
*/
