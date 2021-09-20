//#include "CCCmotor.h"
#include "CCCDrive.h"
#include "Arduino.h"
#include "wire.h"

CCCDrive::CCCDrive(){
    //CCCmotor motorFL(MotorFL);
    //CCCmotor->motorRR(MotorRR);
    //CCCmotor->motorFR(MotorFR);
    //CCCmotor->motorRL(MotorRL);  
}


void CCCDrive::begin() {
  allstop();
}

void CCCDrive::allstop() {
  for(int x = 0; x < 4; x++) {
    this->stop(Motors[x]);
  }
  //CCCmotor motorFL(MotorFL);
  //motorFL.stop();
  //this->motorRL.stop();
  //this->motorFR.stop();
  //this->motorRR.stop();  
}

void CCCDrive::driveforward(int speed) {
  this->drive(Motors[0], 1, speed);
  this->drive(Motors[1], 1, speed);
  this->drive(Motors[2], 2, speed);
  this->drive(Motors[3], 2, speed);  
}

void CCCDrive::drive(int motor, int motorDirection, int motorSpeed){
  _motorSpeed = motorSpeed; // may need to remove these or add the _motorAddress = motorAddress back to the stop function
  _motorDirection = motorDirection;
  Wire.beginTransmission(motor);
  Wire.write(_motorDirection);
  Wire.write(_motorSpeed);  
  Wire.write(255); //Stop
  Wire.endTransmission();
}

void CCCDrive::stop(int motorAddress){
  Wire.beginTransmission(motorAddress);
  Wire.write(3);
  Wire.write(255); //Stop
  Wire.endTransmission();
}


void CCCDrive::drivereverse(int speed) {
   this->drive(Motors[0], 2, speed);
   this->drive(Motors[1], 2, speed);
   this->drive(Motors[2], 1, speed);
   this->drive(Motors[3], 1, speed);
}


void CCCDrive::leftturn(int speed) {
   this->drive(Motors[0], 1, speed);
   this->drive(Motors[1], 1, speed);
   this->drive(Motors[2], 1, speed);
   this->drive(Motors[3], 1, speed); 
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
      this->drive(Motors[2], 2, speed);
      this->drive(Motors[3], 1, speed); 
      break;
    case 2: //Right
      this->drive(Motors[0], 2, speed);
      this->drive(Motors[1], 1, speed);
      this->drive(Motors[2], 1, speed);
      this->drive(Motors[3], 2, speed);
      break;
  }
}

void CCCDrive::diagonal(int dir, int speed) {
  switch (dir) {
    case 1: //Forward Left
      this->drive(Motors[0], 1, speed);
      this->drive(Motors[1], 2, speed);
      this->drive(Motors[2], 2, speed);
      this->drive(Motors[3], 1, speed);
      break;
    case 2: //Forward Right
      this->drive(Motors[0], 2, speed);
      this->drive(Motors[1], 1, speed);
      this->drive(Motors[2], 1, speed);
      this->drive(Motors[3], 2, speed);
      break;
    case 3: //Reverse Left
      this->drive(Motors[0], 1, speed);
      this->drive(Motors[1], 2, speed);
      this->drive(Motors[2], 2, speed);
      this->drive(Motors[3], 1, speed);
      break;
    case 4: //Reverse Right
      this->drive(Motors[0], 2, speed);
      this->drive(Motors[1], 1, speed);
      this->drive(Motors[2], 1, speed);
      this->drive(Motors[3], 2, speed);
      break;
  }
}
