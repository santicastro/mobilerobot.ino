#ifndef RobotMovil_h
#define RobotMovil_h
#define LEFT_SENSOR 0
#define CENTER_SENSOR 1
#define RIGHT_SENSOR 2

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <WProgram.h>
	#include <pins_arduino.h>
#endif

#include <avr/io.h>
#include <avr/interrupt.h>


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
