#include "CCCmotor.h"
#include "CCCDrive.h"

/*
#define MotorFL 16
#define MotorFR 17
#define MotorRR 18
#define MotorRL 19
*/

/*
        CCCmotor motorFL(16);
        CCCmotor motorRR(17);
        CCCmotor motorFR(18);
        CCCmotor motorRL(19);  
*/

//CCCmotor motorFL(MotorFL);

CCCDrive Robot;

void setup() {
  Serial.begin(115200);
  delay(5000);
  Wire.setSDA(12);
  Wire.setSCL(13);
  Wire.begin();
  Robot.begin();
}

void setup1() {
  
}

void loop1() {
  
}

void loop() {
 
  Robot.allstop();
   

  
  Robot.driveforward(50);
  
  delay(2000);
  Robot.allstop();
  delay(1000);
  Robot.drivereverse(50);
  
  delay(2000);
  Robot.allstop();
  delay(1000);

  Robot.leftturn(25);
  delay(2000);
  Robot.allstop();
  delay(1000);
  Robot.rightturn(25);
  delay(2000);
  Robot.allstop();
  delay(1000);

  Robot.strafe(1, 50);
  delay(2000);
  Robot.allstop();
  delay(1000);
  Robot.strafe(2, 50);
  delay(2000);
  Robot.allstop();
  delay(1000);

  
  /* 
  motorFL.drive(2, 100);
  Serial.println("Motor Front Left Forward at 100%");
  delay(5000);
  motorFL.stop();
  Serial.println("Motor Front Left Stop");
  delay(1000);
  motorFL.drive(1, 50);
  Serial.println("Motor Front Left Reverse 50%");
  delay(5000);
  motorFL.stop();
  Serial.println("Motor Front Left Stop");
  motorRR.drive(1, 50);
  Serial.println("Motor Rear Right Forward 50%");
  delay(5000);
  motorRR.stop();
  Serial.println("Motor Rear Right Stop");
  delay(1000);
  motorRR.drive(2, 75);
  Serial.println("Motor Rear Right Reverse 75%");
  delay(5000);
  motorRR.stop();
  Serial.println("Motor Rear Right Stop");
  delay(5000);
  Serial.println("FL and RR Forward 50%");
  motorFL.drive(2, 50);
  motorRR.drive(1, 50);
  delay(5000);
  Serial.println("FL and RR Stop");
  motorFL.drive(1, 0);
  motorRR.drive(1, 0);
  delay(5000);
  */
}

/*
void allstop() {
  motorFL.stop();
  motorRL.stop();
  motorFR.stop();
  motorRR.stop();  
}

void driveforward(int speed) {
  motorFL.drive(1, speed);
  motorRL.drive(1, speed);
  motorFR.drive(2, speed);
  motorRR.drive(2, speed);  
}

void drivereverse(int speed) {
  motorFL.drive(2, speed);
  motorRL.drive(2, speed);
  motorFR.drive(1, speed);
  motorRR.drive(1, speed);  
}

void leftturn(int speed) {
  motorFL.drive(1, speed);
  motorRL.drive(1, speed);
  motorFR.drive(1, speed);
  motorRR.drive(1, speed);
}

void rightturn(int speed) {
  motorFL.drive(2, speed);
  motorRL.drive(2, speed);
  motorFR.drive(2, speed);
  motorRR.drive(2, speed);  
}

void strafe(int dir, int speed) {
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
*/
