#ifndef RobotMovil_h
#define RobotMovil_h
#define LEFT_SENSOR 0
#define CENTER_SENSOR 1
#define RIGHT_SENSOR 2

class RobotMovil {
  public:
    RobotMovil();

	//// Motion ////
    void forward(int left_speed, int rigth_speed, int duration);
    void reverse(int left_speed, int rigth_speed, int duration);
    void rotate(int speed, int duration); // when speed is positive, rotates clockwise
    void brake(int duration);

	// Line follow
	void autoCalibrateLineSensors();
	bool detectLine(int sensor);

	// Ultrasonic frontal distance
	int getDistance();
};
#endif
