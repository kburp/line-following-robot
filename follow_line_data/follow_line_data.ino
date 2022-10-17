// import necessary packages
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// initialize pins
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
int input = 0;
int right_sensor_pin = A0;
int left_sensor_pin = A2;
Adafruit_DCMotor *right_motor = AFMS.getMotor(1);
Adafruit_DCMotor *left_motor = AFMS.getMotor(2);


// set initial sensor and motor values
int forward_speed = 0;
int sensor_threshold = 900;
int default_forward_speed = 30;
int right_speed = 0;
int left_speed = 0;
unsigned long t;

void setup() {
  // begin serial communication and the motor shield
  Serial.begin(9600);
  AFMS.begin();
  right_motor->setSpeed(forward_speed);
  left_motor->setSpeed(forward_speed);  
}

void loop() {
  // set the speed of the motors to 30
  right_motor->setSpeed(default_forward_speed);
  left_motor->setSpeed(default_forward_speed); 
  // turn right if the right sensor is on the line and update
  // left and right wheel speeds
  if (analogRead(right_sensor_pin) > sensor_threshold) {
    right_motor->run(BACKWARD);
    left_motor->run(FORWARD);
    right_speed = default_forward_speed;
    left_speed = -default_forward_speed ;
  }
  // turn left if the left sensor is on the line and update
  // left and right wheel speeds
  else if (analogRead(left_sensor_pin) > sensor_threshold) {
    right_motor->run(FORWARD);
    left_motor->run(BACKWARD);
    right_speed = -default_forward_speed;
    left_speed = default_forward_speed ;
  }
  // move forward if neither sensor is on the line and update
  // left and right wheel speeds
  else {
    right_motor->run(BACKWARD);
    left_motor->run(BACKWARD);
    right_speed = default_forward_speed;
    left_speed = default_forward_speed ;
  }
  // print time, left sensor value, right sensor value, left speed
  // and right speed to serial monitor 
  Serial.print(millis());    Serial.print(",");
  Serial.print(analogRead(left_sensor_pin));    Serial.print(",");
  Serial.print(analogRead(right_sensor_pin));    Serial.print(",");
  Serial.print(left_speed);    Serial.print(",");
  Serial.println(right_speed);
  delay(50);
 
}
