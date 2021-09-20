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
    CCCDrive->stop(Motors[x]);
  }
  //CCCmotor motorFL(MotorFL);
  //motorFL.stop();
  //this->motorRL.stop();
  //this->motorFR.stop();
  //this->motorRR.stop();  
}

void CCCDrive::driveforward(int speed) {
  CCCDrive->drive(Motors[0], 1, speed);
  CCCDrive->drive(Motors[1], 1, speed);
  CCCDrive->drive(Motors[2], 2, speed);
  CCCDrive->drive(Motors[3], 2, speed);  
}

void CCCDrive::drive(int motor, int motorDirection, int motorSpeed){
  _motorSpeed = motorSpeed;
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
/*

void CCCDrive::drivereverse(int speed) {
  motorFL.drive(2, speed);
  motorRL.drive(2, speed);
  motorFR.drive(1, speed);
  motorRR.drive(1, speed);  
}

void CCCDrive::leftturn(int speed) {
  motorFL.drive(1, speed);
  motorRL.drive(1, speed);
  motorFR.drive(1, speed);
  motorRR.drive(1, speed);
}

void CCCDrive::rightturn(int speed) {
  motorFL.drive(2, speed);
  motorRL.drive(2, speed);
  motorFR.drive(2, speed);
  motorRR.drive(2, speed);  
}

void CCCDrive::strafe(int dir, int speed) {
  switch (dir) {
    case 1: //Left
      motorFL.drive(1, speed);
      motorRL.drive(2, speed);
      motorFR.drive(2, speed);
      motorRR.drive(1, speed);
      break;
    case 2: //Right
      motorFL.drive(2, speed);
      motorRL.drive(1, speed);
      motorFR.drive(1, speed);
      motorRR.drive(2, speed);
      break;
  }
}

void CCCDrive::diagonal(int dir, int speed) {
  switch (dir) {
    case 1: //Forward Left
      motorFL.drive(1, speed);
      motorRL.drive(2, speed);
      motorFR.drive(2, speed);
      motorRR.drive(1, speed);
      break;
    case 2: //Forward Right
      motorFL.drive(2, speed);
      motorRL.drive(1, speed);
      motorFR.drive(1, speed);
      motorRR.drive(2, speed);
      break;
    case 3: //Reverse Left
      motorFL.drive(1, speed);
      motorRL.drive(2, speed);
      motorFR.drive(2, speed);
      motorRR.drive(1, speed);
      break;
    case 4: //Reverse Right
      motorFL.drive(2, speed);
      motorRL.drive(1, speed);
      motorFR.drive(1, speed);
      motorRR.drive(2, speed);
      break;
  }
}
*/
