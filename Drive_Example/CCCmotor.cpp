#include "Arduino.h"
#include "CCCmotor.h"
#include "wire.h"



CCCmotor::CCCmotor(int motorAddress){

    _motorAddress = motorAddress;
}


void CCCmotor::drive(int motorDirection, int motorSpeed){
  _motorSpeed = motorSpeed;
  _motorDirection = motorDirection;
  Wire.beginTransmission(_motorAddress);
  Wire.write(_motorDirection);
  Wire.write(_motorSpeed);  
  Wire.write(255); //Stop
  Wire.endTransmission();

}

void CCCmotor::stop(){
  Wire.beginTransmission(_motorAddress);
  Wire.write(3);
  Wire.write(255); //Stop
  Wire.endTransmission();
}
