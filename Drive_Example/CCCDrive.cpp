#include "CCCDrive.h"
#include "Arduino.h"
#include "wire.h"

CCCDrive::CCCDrive(){}


void CCCDrive::begin() {
  this->allstop();
}

void CCCDrive::allstop() {
  for(int x = 0; x < 4; x++) {
    this->stop(Motors[x]);
  }
}

void CCCDrive::driveforward(int speed) {
  this->drive(Motors[0], 2, speed); //Left Front
  this->drive(Motors[1], 2, speed); //Left Rear
  this->drive(Motors[2], 1, speed); //Right Front
  this->drive(Motors[3], 1, speed); //Right Rear
}

void CCCDrive::drive(int motor, int motorDirection, int motorSpeed){
  _motorSpeed = motorSpeed; // may need to remove the private variables later
  _motorDirection = motorDirection;
  Wire.beginTransmission(motor);
  Wire.write(_motorDirection);
  Wire.write(_motorSpeed);  
  Wire.write(255); //Stop
  Wire.endTransmission();
}

void CCCDrive::stop(int motorAddress){
  _motorAddress = motorAddress;
  Wire.beginTransmission(motorAddress);
  Wire.write(3);
  Wire.write(255); //Stop
  Wire.endTransmission();
}


void CCCDrive::drivereverse(int speed) {
  this->drive(Motors[0], 1, speed); //Left Front
  this->drive(Motors[1], 1, speed); //Left Rear
  this->drive(Motors[2], 2, speed); //Right Front
  this->drive(Motors[3], 2, speed); //Right Rear
}


void CCCDrive::leftturn(int speed) {
  this->drive(Motors[0], 1, speed); //Left Front
  this->drive(Motors[1], 1, speed); //Left Rear
  this->drive(Motors[2], 1, speed); //Right Front
  this->drive(Motors[3], 1, speed); //Right Rear
}

void CCCDrive::rightturn(int speed) {
   this->drive(Motors[0], 2, speed);
   this->drive(Motors[1], 2, speed);
   this->drive(Motors[2], 2, speed);
   this->drive(Motors[3], 2, speed);   
}

void CCCDrive::strafe(int dir, int speed) {
  switch (dir) {
    case 1: //Left
      this->drive(Motors[0], 1, speed);
      this->drive(Motors[1], 2, speed);
      this->drive(Motors[2], 1, speed);
      this->drive(Motors[3], 2, speed);
      break;
    case 2: //Right
      this->drive(Motors[0], 2, speed); //Left Front
      this->drive(Motors[1], 1, speed); //Left Rear
      this->drive(Motors[2], 2, speed); //Right Front
      this->drive(Motors[3], 1, speed); //Right Rear
      break;
  }
}

void CCCDrive::diagonal(int dir, int speed) {
  switch (dir) {
    case 1: //Forward Left
      this->stop(Motors[0]); //Left Front
      this->drive(Motors[1], 2, speed); //Left Rear
      this->drive(Motors[2], 1, speed); //Right Front
      this->stop(Motors[3]); //Right Rear
      break;
    case 2: //Forward Right
      this->drive(Motors[0], 2, speed); //Left Rear
      this->stop(Motors[1]); //Left Front
      this->stop(Motors[2]); //Right Rear
      this->drive(Motors[3], 1, speed); //Right Front
      break;
    case 3: //Reverse Left
      this->drive(Motors[0], 1, speed); //Left Rear
      this->stop(Motors[1]); //Left Front
      this->stop(Motors[2]); //Right Rear
      this->drive(Motors[3], 2, speed); //Right Front
      break;
    case 4: //Reverse Right
      this->stop(Motors[0]); //Left Front
      this->drive(Motors[1], 1, speed); //Left Rear
      this->drive(Motors[2], 2, speed); //Right Front
      this->stop(Motors[3]); //Right Rear
      break;
  }
}
