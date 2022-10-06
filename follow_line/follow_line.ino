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

void setup() {
  // begin serial communication and the motor shield
  Serial.begin(9600);
  AFMS.begin();
  right_motor->setSpeed(forward_speed);
  left_motor->setSpeed(forward_speed);
  Serial.println("Type \"f\" to increase speed or \"s\" to decrease speed");
}

void loop() {
  // set the speed of the motors
  right_motor->setSpeed(forward_speed);
  left_motor->setSpeed(forward_speed);
  // check if there is a new message from serial
  if (Serial.available() > 0) {
    input = Serial.read();
    // increase speed if input is "f"
    if (input == 102) {
      forward_speed++;
      Serial.print("Speed: ");
      Serial.println(forward_speed);
    }
    // decrease speed if input is "s" and speed is positive
    else if (input == 115 && forward_speed > 0) {
      forward_speed--;
      Serial.print("Speed: ");
      Serial.println(forward_speed);
    }
    // stop motors if input is "0"
    else if (input == 48) {
      forward_speed = 0;
      Serial.println("Stopped");
    }
    // reset speed to default value if input is "r"
    else if (input == 114) {
      forward_speed = default_forward_speed;
      Serial.println("Speed Reset");
    }
    // check speed if input is "c"
    else if (input == 99) {
      Serial.print("Speed: ");
      Serial.println(forward_speed);
    }
    // warn user of invalid input if input is not "\n"
    else if (input != 10) {
      Serial.println("Invalid input");
    }
  }
  // turn right if the right sensor is on the line
  if (analogRead(right_sensor_pin) > sensor_threshold) {
    right_motor->run(BACKWARD);
    left_motor->run(FORWARD);
  }
  // turn left if the left sensor is on the line
  else if (analogRead(left_sensor_pin) > sensor_threshold) {
    right_motor->run(FORWARD);
    left_motor->run(BACKWARD);
  }
  // move forward if neither sensor is on the line
  else {
    right_motor->run(BACKWARD);
    left_motor->run(BACKWARD);
  }
  delay(50);
}
