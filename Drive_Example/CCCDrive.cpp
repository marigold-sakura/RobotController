#include "CCCDrive.h"
#include "Arduino.h"
#include "wire.h"

CCCDrive::CCCDrive(){
    pinMode(Trigger_Pin, OUTPUT);
    for(int x = 0; x < 3; x++) {
      pinMode(Echo_Pins[x], INPUT);
    }
}

void CCCDrive::sonar() {
  this->ping(0);
  delay(20);
  this->ping(1);
  delay(20);
  this->ping(2);
}

void CCCDrive::ping(int sensornumber) {
  long duration = 0;
  long distance = 0;
  long echotimer = 0;
  long echotimerend = 0;
  
  digitalWrite(Trigger_Pin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(Trigger_Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger_Pin, LOW);
  //Serial.println("Triggered");
  // Reads the echoPin, returns the sound wave travel time in microseconds
  //duration = pulseIn(Echo_Pins[sensornumber], HIGH);
  unsigned long numloops = 0;
  unsigned long maxloops = 10000;
  
  while(digitalRead(Echo_Pins[sensornumber]) == LOW) {
    if(numloops++ == maxloops) { 
      break; 
    } else {
      echotimer = micros();
    }
  }

  while(digitalRead(Echo_Pins[sensornumber]) == HIGH) {
    if(numloops++ == maxloops) { 
      break; 
    } else {
      echotimerend = micros();
    }
  }

  duration = echotimerend - echotimer;

  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  if(distance > 0) { 
    if(distance > 150) {
      echo[sensornumber] = 150; //max it out at 150 cm
    } else {
      echo[sensornumber] = distance;      
    }
  } else {
    echo[sensornumber] = 0;
  }
}

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
