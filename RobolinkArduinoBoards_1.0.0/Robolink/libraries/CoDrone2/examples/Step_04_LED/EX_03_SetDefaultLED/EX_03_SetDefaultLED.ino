/*---------------------------------------------------------------------------------------------------
  setDefaultLED (기본 LED 색상 지정)
  목표 : 기본 LED 색상 지정의 사용법
  구문 : setDefaultLED(색상, 조명 패턴, 패턴 간격)
         setDefaultLED(빨강색, 녹색, 파랑색, 조명 패턴, 패턴 간격)
  설명 : 이 기능은 기본 LED 색뿐만 아니라 모드를 설정하므로 전원을 껐다가 다시 켠 후에도 해당 색과 조명 패턴을 유지합니다.
         빨강, 녹색 및 파랑 입력 값 또는 미리 정의 된 색상을 사용하여 색상을 설정할 수 있습니다.

         프로그램이 실행되면 입력한 LED 상태가 기본 LED 상태가 됩니다. 전원을 껏다가 켜도 LED 상태가 유지됩니다.
  ---------------------------------------------------------------------------------------------------*/
#include "CoDrone2.h"

int colorR = 0;
int colorG = 0;
int colorB = 0;

void setup()
{
  CoDrone2.begin();     // Initialization and preparation for flight

  // 전원을 켜면 빨간색이 켜진 상태가 됩니다.
  CoDrone2.setDefaultLED(Red, BodyHold, 100);

  /*
    colorR = 255;
    colorG = 0;
    colorB = 0;
    CoDrone2.setDefaultLED(colorR, colorG, colorB, BodyHold, 100);
  */
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
