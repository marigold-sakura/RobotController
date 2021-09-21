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
  Serial.println("Driving Forward 50%");
  /*
  delay(2000);
  Robot.allstop();
  Serial.println("All Stop");
  delay(1000);
  Robot.drivereverse(50);
  Serial.println("Driving Reverse 50%");
  
  delay(2000);
  Robot.allstop();
  Serial.println("All Stop");
  delay(1000);

  Robot.leftturn(25);
  Serial.println("Left Turn 25%");
  delay(2000);
  Robot.allstop();
  Serial.println("All Stop");
  delay(1000);
  Robot.rightturn(25);
  Serial.println("Right Turn 25%");
  delay(2000);
  Robot.allstop();
  Serial.println("All Stop");
  delay(1000);

  Robot.strafe(1, 50);
  Serial.println("Strafe Left 50%");
  delay(2000);
  Robot.allstop();
  Serial.println("All Stop");
  delay(1000);
  Robot.strafe(2, 50);
  Serial.println("Strafe Right 50%");
  delay(2000);
  Robot.allstop();
  Serial.println("All Stop");
  delay(1000);
  */ 
}
