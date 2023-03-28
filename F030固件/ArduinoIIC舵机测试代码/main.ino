#include "robot.h"

Robot electron;

void setup()
{
  Wire.begin(8, 9); //sda 8,scl 9
  delay(2000);
  Serial.begin(115200);

}

void loop()
{

  int n =1;   //1-6
  electron.joint[n].angleMin = 0;
  electron.joint[n].angleMax = 180;
  electron.joint[n].angle = 0;
  electron.joint[n].modelAngelMin = -90;
  electron.joint[n].modelAngelMax = 90;
  electron.SetJointEnable(electron.joint[n], true);

  for (int i = -90; i < 90; i += 1)
  {
    float angle = i;
    electron.UpdateJointAngle(electron.joint[n], angle);

    delay(20);
  }
  for (int i = 90; i > -90; i -= 1)
  {
    float angle = i;
    electron.UpdateJointAngle(electron.joint[n], angle);

    delay(20);
  }
}
