#include "robomodule_due_CAN.h"
CRobomodule_due_CAN can;
int start = 0;
int par = -1;
int lightswitchleft = 9;
int lightswitchright = 10;
int valueleft;
int valueright;
#include <Servo.h>
Servo myservo;
#define TrigPin1 2
#define EchoPin1 3
#define TrigPin2 11
#define EchoPin2 12
#define TrigPin3 4
#define EchoPin3 5
float cm1, cm2, cm3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TrigPin1, OUTPUT);
  pinMode(EchoPin1, INPUT);
  pinMode(TrigPin2, OUTPUT);
  pinMode(EchoPin2, INPUT);
  pinMode(TrigPin3, OUTPUT);
  pinMode(EchoPin3, INPUT);
  myservo.attach(30);
  pinMode(lightswitchleft, INPUT);
  pinMode(lightswitchright, INPUT);
  can.initdriver(CAN_BPS_1000K, 0, 0, 1);
}
//========================loop====================////========================loop====================////========================loop====================//
void loop() {
  // put your main code here, to run repeatedly:
  chaosheng();
  shuchu();
  Serial.println("===================================================================");
  if (start == 0)//出家
  {
    qianjin();
    if (cm3 <= 27)
    {
      start++;
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    }
  }
  if (start == 1)
  {
    you();
    delay(3500);
    start++;
  }
  if (start == 2)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
    start++;
  }
  if(start == 3)
  {
    valueleft = digitalRead(lightswitchleft);
    valueright = digitalRead(lightswitchright);
    //if()
    qianjin();
  }
}
//========================han==shu====================////========================han==shu====================////========================han==shu====================//
void qianjin()
{
  can.speedwheel(3000,  0, 1);
  can.speedwheel(3060,  0, 2);
  can.speedwheel(3000,  0, 3);
  can.speedwheel(3060,  0, 4);
}
void zuo()
{
  can.positionwheel(3000, -200000, 0, 1);
  can.positionwheel(3000, 200000, 0, 2);
  can.positionwheel(3000, -200000, 0, 3);
  can.positionwheel(3000, 200000, 0, 4);
}
void you()
{
  can.positionwheel(3000, 200000, 0, 1);
  can.positionwheel(3000, -200000, 0, 2);
  can.positionwheel(3000, 200000, 0, 3);
  can.positionwheel(3000, -200000, 0, 4);
}
//========================han==shu====================////========================han==shu====================////========================han==shu====================//
void chaosheng()
{
  digitalWrite(TrigPin1, LOW); //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin1, LOW);
  cm1 = pulseIn(EchoPin1, HIGH) / 58.0; //将回波时间换算成cm
  cm1 = (int(cm1 * 100.0)) / 100.0; //保留两位小数
  delay(90);
  digitalWrite(TrigPin2, LOW); //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin2, LOW);
  cm2 = pulseIn(EchoPin2, HIGH) / 58.0; //将回波时间换算成cm
  cm2 = (int(cm2 * 100.0)) / 100.0; //保留两位小数
  digitalWrite(TrigPin3, LOW); //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin3, LOW);
  cm3 = pulseIn(EchoPin3, HIGH) / 58.0; //将回波时间换算成cm
  cm3 = (int(cm3 * 100.0)) / 100.0; //保留两位小数
  delay(90);
}
void shuchu()
{
  Serial.print(cm1);
  Serial.print("cm1");
  Serial.print("     ");
  Serial.print(cm2);
  Serial.print("cm2");
  Serial.print("     ");
  Serial.print(cm3);
  Serial.print("cm3");
  Serial.println("     ");
}
//========================han==shu====================////========================han==shu====================////========================han==shu====================//
