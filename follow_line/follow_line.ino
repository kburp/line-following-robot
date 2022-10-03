#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
int input = 0;
int right_sensor_pin = A0;
int left_sensor_pin = A1;
Adafruit_DCMotor *right_motor = AFMS.getMotor(1);
Adafruit_DCMotor *left_motor = AFMS.getMotor(2);

int forward_speed = 0;
int sensor_threshold = 900;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  right_motor->setSpeed(forward_speed);
  left_motor->setSpeed(forward_speed);
  Serial.println("Type \"f\" to increase speed or \"s\" to decrease speed");
}

void loop() {
  right_motor->setSpeed(forward_speed);
  left_motor->setSpeed(forward_speed);
  if (Serial.available() > 0) {
    input = Serial.read();
    if (input == 102) {
      forward_speed++;
      Serial.print("Speed: ");
      Serial.println(forward_speed);
      
    }
    else if (input == 115 && forward_speed > 0) {
      forward_speed--;
      Serial.print("Speed: ");
      Serial.println(forward_speed);
    }
    else if (input == 48) {
      forward_speed = 0;
      Serial.println("Stopped");
    }
    else if (input == 114) {
      forward_speed = 150;
      Serial.println("Speed Reset");
    }
    else if (input == 99) {
      Serial.print("Speed: ");
      Serial.println(forward_speed);
    }
    else if (input != 10) {
      Serial.println("Invalid input");
    }
  }
  if (analogRead(right_sensor_pin) > sensor_threshold) {
    right_motor->run(RELEASE);
    left_motor->run(FORWARD);
  }
  else if (analogRead(left_sensor_pin) > sensor_threshold) {
    right_motor->run(FORWARD);
    left_motor->run(RELEASE);
  }
  else {
    right_motor->run(FORWARD);
    left_motor->run(FORWARD);
  }
  delay(50);
}
