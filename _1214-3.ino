// 使用可變電阻控制 Servo 的旋轉角度
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>
 
// 引用 Servo Library
#include <Servo.h>
#include <Wire.h>
// 建立一個 Servo 物件
Servo myservo;
// 儲存旋轉角度的變數
int val;

void setup()
{
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  myservo.attach(9);  // Servo 接在 pin 9
}

void loop()
{
  delay(15);                           // 等待 Servo 旋轉指定的位置
}

void receiveEvent(int howmany){
  val = Wire.read();
  myservo.write(val);                  // 設定 Servo 旋轉角度
  delay(15);                           // 等待 Servo 旋轉指定的位置
}

