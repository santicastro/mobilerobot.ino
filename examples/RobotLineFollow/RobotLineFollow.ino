#include <RobotMovil.h>

#define NORMAL 220
#define ULTRAFAST 255
#define VERYSLOW 80

RobotMovil robot;

void setup()
{
  robot.autoCalibrateLineSensors();
}

void loop()
{
  bool lineOnCenter = robot.detectLine( CENTER_SENSOR );
  bool lineOnLeft = robot.detectLine( LEFT_SENSOR );
  bool lineOnRight = robot.detectLine( RIGHT_SENSOR );

  if( lineOnCenter ){
    robot.forward( NORMAL, NORMAL, 1 );
  }
  else if( lineOnLeft ){
    robot.forward( VERYSLOW, ULTRAFAST, 1 );
  }
  else if( lineOnRight ){
    robot.forward( ULTRAFAST, VERYSLOW, 1 );
  }
  else{
    robot.rotate( ULTRAFAST, 1 );
  }
}
