#include "src/CCCDrive/CCCDrive.h"
#include "src/Pololu/QTRSensors.h"
#include "src/Button/Button.h"

CCCDrive Robot;

Button start_btn(7); //Connect momentary to GPIO 7


int Running = 1;      //Set up variable to determine if the robot should be moving
long myTimer = 0;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Wire.setSDA(12);
  Wire.setSCL(13);
  Wire.begin();
  Robot.begin();
  start_btn.begin();
  Serial.println("- Cyber City Circuits -");
  Serial.println("Robot Online and Ready");
  Serial.println("Waiting on button to begin");
  
  qtr.setTypeAnalog();
  qtr/setSensorPins((const sensorArray[]){A0, A1, A2}, 8); //Don't know the analogs yet
  
  for (unint8_t i = 0; i < 250; i++)
  {
    qtr.calibrate();
    delay(20);

}


void loop() {
  CheckforButton();   //Main command, do not remove! This monitors button press for robot state
  
  if(Running == 1) {  //If the robot should be moving, do things here
    
    read(sensorArray);
    if (sensorArray[0] = 0 && sensorArray[1] = 0 sensorArray[2] sensorArray[3] sensorArray[4] sensorArray[5] sensorArray[6] sensorArray[7]) {
    
    
    }

    
    /*Robot.driveforward(50); 
    delay(5000);
    Robot.allstop();
    delay(5000);
    Robot.rightturn(50);
    delay(1000);
    Robot.drivereverse(50);
    delay(5000);
    Robot.diagonal(2,50);
    delay(1000);
    Robot.strafe(1, 60);
    delay(5000);
    Robot.allstop();*/
    
    
  }
 
 
}
void CheckforButton() {
  switch (Running) {
    case 0:
      if(start_btn.pressed()) {
        Serial.println("Button Pressed, Beginning Routine");
        Running = 1;  
       
      }
      break;
    case 1:
      if(start_btn.pressed()) {
        Serial.println("Button Pressed, Stopping Routine");
        Running = 0;
        
      }
      break;
  }
}
