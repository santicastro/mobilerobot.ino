#define limit 15

#include <RobotMovil.h>
RobotMovil robot;

void setup() {
}

void loop()
{
  delay(30);
  int dist = robot.getDistance();
  if (dist==0) {
    dist=50;
  }

  if (dist<limit) {
    robot.reverse(120,120,0);
  }
  if (dist>limit) {
    robot.forward(120,120,0);
  }
  if (dist==limit) {
    robot.brake(0);
  }
}
