#include <Arduino.h>
#include "RobotMovil.h"
#include "NewPing.h"

//// PINS ////
// Motion
#define LEFT_SPEED_PIN 5
#define LEFT_FORWARD_PIN 7
#define LEFT_REVERSE_PIN 8
#define RIGHT_SPEED_PIN 6
#define RIGHT_FORWARD_PIN 2
#define RIGHT_REVERSE_PIN 4

#define LEFT_SENSOR_PIN A0
#define CENTER_SENSOR_PIN A4
#define RIGHT_SENSOR_PIN A5


// Line follow sensors
const int TOTAL_SENSORS = 3;
const int MAX_SENSOR_READS = 1;
const int SENSOR_RANGE = 200;
struct Sensor_data{
	int pin;
	int background_value;
};
struct Sensor_data sensor_states[TOTAL_SENSORS];
void resetSensorData();

// distance sensor
int DISTANCE_PIN = A2;
const int MAX_DISTANCE = 50;
NewPing sonar(DISTANCE_PIN, DISTANCE_PIN, MAX_DISTANCE);

// public //
RobotMovil::RobotMovil( ){
  pinMode( LEFT_SPEED_PIN, OUTPUT );
  pinMode( RIGHT_SPEED_PIN, OUTPUT );
  pinMode( LEFT_REVERSE_PIN, OUTPUT );
  pinMode( LEFT_FORWARD_PIN, OUTPUT );
  pinMode( RIGHT_REVERSE_PIN, OUTPUT );
  pinMode( RIGHT_FORWARD_PIN, OUTPUT );

  pinMode( LEFT_SENSOR_PIN, INPUT );
  pinMode( CENTER_SENSOR_PIN, INPUT );
  pinMode( RIGHT_SENSOR_PIN, INPUT );

  resetSensorData();
}

void RobotMovil::forward( int left_speed, int rigth_speed, int duration )
{
  analogWrite( LEFT_SPEED_PIN, left_speed );
  analogWrite( RIGHT_SPEED_PIN, rigth_speed );
  digitalWrite( LEFT_REVERSE_PIN, HIGH );
  digitalWrite( LEFT_FORWARD_PIN, LOW );
  digitalWrite( RIGHT_REVERSE_PIN, HIGH );
  digitalWrite( RIGHT_FORWARD_PIN, LOW );
  delay( duration );
}

void RobotMovil::reverse( int left_speed, int rigth_speed, int duration )
{
  analogWrite( LEFT_SPEED_PIN, left_speed );
  analogWrite( RIGHT_SPEED_PIN, rigth_speed );
  digitalWrite( LEFT_REVERSE_PIN, LOW );
  digitalWrite( LEFT_FORWARD_PIN, HIGH );
  digitalWrite( RIGHT_REVERSE_PIN, LOW );
  digitalWrite( RIGHT_FORWARD_PIN, HIGH );
  delay( duration );
}

void RobotMovil::brake( int duration )
{
  digitalWrite( LEFT_REVERSE_PIN, LOW );
  digitalWrite( LEFT_FORWARD_PIN, LOW );
  digitalWrite( RIGHT_REVERSE_PIN, LOW );
  digitalWrite( RIGHT_FORWARD_PIN, LOW );
  delay( duration );
}

void RobotMovil::rotate( int speed, int duration )
{
  analogWrite( LEFT_SPEED_PIN, abs(speed) );
  analogWrite( RIGHT_SPEED_PIN, abs(speed) );
  if ( speed<0 ) {
    digitalWrite( LEFT_REVERSE_PIN, HIGH );
    digitalWrite( LEFT_FORWARD_PIN, LOW );
    digitalWrite( RIGHT_REVERSE_PIN, LOW );
    digitalWrite( RIGHT_FORWARD_PIN, HIGH );
   } else {
    digitalWrite( LEFT_REVERSE_PIN, LOW );
    digitalWrite( LEFT_FORWARD_PIN, HIGH );
    digitalWrite( RIGHT_REVERSE_PIN, HIGH );
    digitalWrite( RIGHT_FORWARD_PIN, LOW );
  } 
  delay( duration );
}

void RobotMovil::autoCalibrateLineSensors(){
	resetSensorData();
	forward(100, 100, 1);
	int total = 0;
	const int MAXREADS = 32;
	for(int i=0; i<MAXREADS; i++){
		for(int j=0; j<TOTAL_SENSORS; j++){
			sensor_states[j].background_value += analogRead(sensor_states[j].pin);
		}
		delay(30);
	}
	brake(1000);
	sensor_states[LEFT_SENSOR].background_value /= MAXREADS;
	sensor_states[CENTER_SENSOR].background_value /= MAXREADS;
	sensor_states[RIGHT_SENSOR].background_value /= MAXREADS;
}

bool RobotMovil::detectLine(int which){
	int pin = sensor_states[which].pin;
	int value = analogRead(pin);
	for(int i=1; i<MAX_SENSOR_READS;i++){
		delay(1);
		value += analogRead(pin);
	}
	value /= MAX_SENSOR_READS;
	int difference = abs(sensor_states[which].background_value - value);
	if(difference > SENSOR_RANGE){
		return true;
	}else{
		//reajusts the background color
		sensor_states[which].background_value = sensor_states[which].background_value*0.9 + value*0.1;
		return false;
	}
}

int RobotMovil::getDistance(){
	return sonar.ping_cm();
}

void resetSensorData(){
	sensor_states[LEFT_SENSOR].pin = LEFT_SENSOR_PIN;
	sensor_states[CENTER_SENSOR].pin = CENTER_SENSOR_PIN;
	sensor_states[RIGHT_SENSOR].pin = RIGHT_SENSOR_PIN;
	sensor_states[LEFT_SENSOR].background_value = 0;
	sensor_states[CENTER_SENSOR].background_value = 0;
	sensor_states[RIGHT_SENSOR].background_value = 0;
}
