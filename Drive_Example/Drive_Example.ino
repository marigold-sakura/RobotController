#include "CCCDrive.h"

CCCDrive Robot;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Wire.setSDA(12);
  Wire.setSCL(13);
  Wire.begin();
  Robot.begin();
  Serial.println("- Cyber City Circuits -");
  Serial.println("Robot Online and Ready");
}

void setup1() {
  
}

void loop1() {
  
}

void loop() {

  Robot.sonar();
  Serial.print("Sensor 0: ");
  Serial.println(Robot.echo[0]);
  
  Serial.print("Sensor 1: ");
  Serial.println(Robot.echo[1]);

  Serial.print("Sensor 2: ");
  Serial.println(Robot.echo[2]);

  if(Robot.echo[1] > 40) {
    Robot.driveforward(25);
    Serial.println("Driving Forward, nothing in my way!");
  } else {
    Robot.allstop();
    Serial.println("I'm about to crash, stopped!");
    Robot.rightturn(25);
    Serial.println("Turning Right for 4 seconds");
    delay(4000);    
  }

  if(Robot.echo[2] < 40) {
    Robot.rightturn(25);
    Serial.println("Turning Right for 2 seconds");
    delay(2000);
  }

  if(Robot.echo[0] < 40) {
    Serial.println("Turning Left for 2 seconds");
    Robot.leftturn(25);
    delay(2000);
  }

/*  
  Robot.driveforward(50); 
  Serial.println("Driving Forward 50%");
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
