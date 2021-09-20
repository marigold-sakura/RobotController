#include "CCCDrive.h"
#include "CCCmotor.h"
#include "Arduino.h"
#include "wire.h"

CCCDrive::CCCDrive(){
    CCCmotor motorFL(MotorFL);
    //CCCmotor->motorRR(MotorRR);
    //CCCmotor->motorFR(MotorFR);
    //CCCmotor->motorRL(MotorRL);  
}


void CCCDrive::begin() {
  allstop();
}

void CCCDrive::allstop() {
  //CCCmotor motorFL(MotorFL);
  motorFL.stop();
  //this->motorRL.stop();
  //this->motorFR.stop();
  //this->motorRR.stop();  
}

/*

void CCCDrive::driveforward(int speed) {
  motorFL.drive(1, speed);
  motorRL.drive(1, speed);
  motorFR.drive(2, speed);
  motorRR.drive(2, speed);  
}

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
