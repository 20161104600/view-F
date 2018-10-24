#include "robomodule_due_CAN.h"
#include <LobotServoController.h>
CRobomodule_due_CAN can;
LobotServoController myse;
int start = -1;
int par = -1;
int lightswitchleft = 9;
int lightswitchright = 10;
int lightswitchHL = 7;
int lightswitchHR = 8;
int valueleft = 0;
int valueright = 0;
int headL = 1;
int headR = 1;
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
}
//========================loop====================////========================loop====================////========================loop====================//
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("===================================================================");
  if (start == -1)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
    start++;
  }
  if (start == 0)//出家
  {
    chaosheng();
    shuchu();
    qianjin();
    if (cm3 < 35 && cm3 > 10)
    {
      start++;
    }
  }
  if (start == 1 || start == 2)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    start++;
  }
  if (start == 3)
  {
    zuo();
    delay(3000);
    start++;
  }
  if (start == 4)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
    start++;
  }
  if (start == 5)
  {
    valueleft = digitalRead(lightswitchleft);
    valueright = digitalRead(lightswitchright);
    headL = digitalRead(lightswitchHL);
    headR = digitalRead(lightswitchHR);
    if ((valueright == 0 && valueleft == 0) || (valueright == 1 && valueleft == 1))
    {
      qianjin();
    }
    if (valueright == 1 && valueleft == 0)
    {
      can.speedwheel(3500,  0, 1);
      can.speedwheel(3000,  0, 2);
      can.speedwheel(3500,  0, 3);
      can.speedwheel(3000,  0, 4);
    }
    if (valueright == 0 && valueleft == 1)
    {
      can.speedwheel(3000,  0, 1);
      can.speedwheel(3500,  0, 2);
      can.speedwheel(3000,  0, 3);
      can.speedwheel(3500,  0, 4);
    }
    if (start == 5)
    {
      //========================head====================//
      if (headL == 0 && headR == 1)
    {
      can.speedwheel(0,  0, 1);
      can.speedwheel(3000,  0, 2);
      can.speedwheel(0,  0, 3);
      can.speedwheel(3000,  0, 4);
    }
    if (headL == 1 && headR == 0)
    {
      can.speedwheel(3000,  0, 1);
      can.speedwheel(0,  0, 2);
      can.speedwheel(3000,  0, 3);
      can.speedwheel(0,  0, 4);
    }
      //========================head====================//
      if (headL == 0 && headR == 0)
      {
        can.initdriver(CAN_BPS_1000K, 0, 0, 4);
        start++;
      }
    }
  }
  if (start == 6)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    start++;
  }
  if (start == 7)
  {
    zuo();
    delay(3000);
    start++;
  }
  if (start == 8)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
    start++;
  }
  if (start == 9)//走向放置台
  {
    headL = digitalRead(lightswitchHL);
    headR = digitalRead(lightswitchHR);
    qianjin();
    if (headL == 0 && headR == 0)
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      start++;
    }
  }
  if (start == 10)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    start++;
  }
  if (start == 11)
  {
    zuo();
    delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(4000, 800000, 0, 1);//-200000   走向门
    can.positionwheel(4000, 800000, 0, 2);
    can.positionwheel(4000, 800000, 0, 3);//-200000
    can.positionwheel(4000, 800000, 0, 4);
    delay(6000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);//-200000    转
    you();
    delay(3000);
    start++;
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
  }
  if (start == 12) //走向墙
  {
    headL = digitalRead(lightswitchHL);
    headR = digitalRead(lightswitchHR);
    chaosheng();
    shuchu();
    qianjin();
     if (headL == 0 && headR == 1)
    {
      can.speedwheel(0,  0, 1);
      can.speedwheel(3000,  0, 2);
      can.speedwheel(0,  0, 3);
      can.speedwheel(3000,  0, 4);
    }
    if (headL == 1 && headR == 0)
    {
      can.speedwheel(3000,  0, 1);
      can.speedwheel(0,  0, 2);
      can.speedwheel(3000,  0, 3);
      can.speedwheel(0,  0, 4);
    }
    if ((headL == 0 && headR == 0 ) || cm3 < 10)
    {
      start++;
    }
  }
  if (start == 13)
  {
    chaosheng();
    shuchu();
    can.speedwheel(-500,  0, 1);
    can.speedwheel(-500,  0, 2);
    can.speedwheel(-500,  0, 3);
    can.speedwheel(-500,  0, 4);
    if (cm1 > 40) //找门
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      start++;
    }
  }
  if (start == 14)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    start++;
  }
  if (start == 15)
  {
    can.positionwheel(3000, -170000, 0, 1);//继续后退 到门口
    can.positionwheel(3000, -170000, 0, 2);
    can.positionwheel(3000, -170000, 0, 3);
    can.positionwheel(3000, -170000, 0, 4);
    delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    zuo();//-200000左  转向门
    delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(3000, 700000, 0, 1);//+200000  过门
    can.positionwheel(3000, 700000, 0, 2);
    can.positionwheel(3000, 700000, 0, 3);
    can.positionwheel(3000, 700000, 0, 4);
    delay(6000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    you();//-200000左 转向桥 换墙
    delay(3000);
    start++;
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
  }
  if (start == 16)
  {
    headL = digitalRead(lightswitchHL);
    headR = digitalRead(lightswitchHR);
    qianjin();
    //========================head====================//
    if (headL == 0 && headR == 1)
    {
      can.speedwheel(0,  0, 1);
      can.speedwheel(3000,  0, 2);
      can.speedwheel(0,  0, 3);
      can.speedwheel(3000,  0, 4);
    }
    if (headL == 1 && headR == 0)
    {
      can.speedwheel(3000,  0, 1);
      can.speedwheel(0,  0, 2);
      can.speedwheel(3000,  0, 3);
      can.speedwheel(0,  0, 4);
    }
    //========================head====================//
    if ( (headL == 0 && headR == 0 ) || cm3 < 12) //到放置台边
    {
      start++;
    }
  }
  if (start == 17)
  {
    chaosheng();
    shuchu();
    can.speedwheel(-3000,  0, 0);
    if (cm1 > 40)
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      start++;
    }
  }
  if (start == 18)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(3000, -250000, 0, 1);//继续后退 退到台子前
    can.positionwheel(3000, -250000, 0, 2);
    can.positionwheel(3000, -250000, 0, 3);
    can.positionwheel(3000, -250000, 0, 4);
    delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    zuo();
    delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
    start++;
  }
  if (start == 19) //找边  在台前停
  {
    headL = digitalRead(lightswitchHL);
    headR = digitalRead(lightswitchHR);
    qianjin();
    if (headL == 0 && headR == 1)
    {
      can.speedwheel(0,  0, 1);
      can.speedwheel(3000,  0, 2);
      can.speedwheel(0,  0, 3);
      can.speedwheel(3000,  0, 4);
    }
    if (headL == 1 && headR == 0)
    {
      can.speedwheel(3000,  0, 1);
      can.speedwheel(0,  0, 2);
      can.speedwheel(3000,  0, 3);
      can.speedwheel(0,  0, 4);
    }
    if ( ( headL == 0 && headR == 0 ) )
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      start++;
    }
  }
  if (start == 20)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(3000, -400000, 0, 1);//继续后退 退到放球处
    can.positionwheel(3000, -400000, 0, 2);
    can.positionwheel(3000, -400000, 0, 3);
    can.positionwheel(3000, -400000, 0, 4);
    delay(3500);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    you();
    delay(6000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
    start++;
  }
  if (start == 21)
  {
    headL = digitalRead(lightswitchHL);
    headR = digitalRead(lightswitchHR);
    qianjin();
    if (headL == 0 && headR == 1)
    {
      can.speedwheel(0,  0, 1);
      can.speedwheel(3000,  0, 2);
      can.speedwheel(0,  0, 3);
      can.speedwheel(3000,  0, 4);
    }
    if (headL == 1 && headR == 0)
    {
      can.speedwheel(3000,  0, 1);
      can.speedwheel(0,  0, 2);
      can.speedwheel(3000,  0, 3);
      can.speedwheel(0,  0, 4);
    }
    if ( ( headL == 0 && headR == 0 ) )// 到放球台前
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      start++;
    }
  }
  if (start == 22)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(3000, -100000, 0, 1);//继续后退 退到台子前
    can.positionwheel(3000, -100000, 0, 2);
    can.positionwheel(3000, -100000, 0, 3);
    can.positionwheel(3000, -100000, 0, 4);
    delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    zuo();
    delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 1);
    start++;
  }
  if (start == 23)
  {
    headL = digitalRead(lightswitchHL);
    headR = digitalRead(lightswitchHR);
    qianjin();
    if (headL == 0 && headR == 1)
    {
      can.speedwheel(0,  0, 1);
      can.speedwheel(3000,  0, 2);
      can.speedwheel(0,  0, 3);
      can.speedwheel(3000,  0, 4);
    }
    if (headL == 1 && headR == 0)
    {
      can.speedwheel(3000,  0, 1);
      can.speedwheel(0,  0, 2);
      can.speedwheel(3000,  0, 3);
      can.speedwheel(0,  0, 4);
    }
    if (headL == 0 && headR == 0)
    {
      can.initdriver(CAN_BPS_1000K, 0, 0, 4);
      start++;
    }
  }
  if (start == 24)
  {
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    you();
    delay(3000);
    can.initdriver(CAN_BPS_1000K, 0, 0, 4);
    can.positionwheel(3000, 370000, 0, 1);
    can.positionwheel(3000, 370000, 0, 2);
    can.positionwheel(3000, 370000, 0, 3);
    can.positionwheel(3000, 370000, 0, 4);
    delay(30000);
  }
}
//========================han==shu====================////========================han==shu====================////========================han==shu====================//
void ting()
{
  can.speedwheel(0,  0, 1);
  can.speedwheel(0,  0, 2);
  can.speedwheel(0,  0, 3);
  can.speedwheel(0,  0, 4);
}
void qianjin()
{
  can.speedwheel(3000,  0, 1);
  can.speedwheel(3000,  0, 2);
  can.speedwheel(3000,  0, 3);
  can.speedwheel(3000,  0, 4);
}
void houtui()
{
  can.speedwheel(-3000,  0, 1);
  can.speedwheel(-3000,  0, 2);
  can.speedwheel(-3000,  0, 3);
  can.speedwheel(-3000,  0, 4);
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
void yuan()
{
  can.positionwheel(3000, 0, 0, 1);
  can.positionwheel(3000, 0, 0, 2);
  can.positionwheel(3000, 0, 0, 3);
  can.positionwheel(3000, 0, 0, 4);
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
  delay(50);
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
