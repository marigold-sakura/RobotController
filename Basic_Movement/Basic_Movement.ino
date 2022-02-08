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
  qtr.setSensorPins((const sensorArray[]){14, 15, 16, 17, 18, 19, 20, 21}, 8); //Don't know the analogs yet
  
  for (unint8_t i = 0; i < 250; i++)
  {
    qtr.calibrate();
    delay(20);

}


void loop() {
  CheckforButton();   //Main command, do not remove! This monitors button press for robot state
  
  if(Running == 1) {  //If the robot should be moving, do things here
    
    read(sensorArray);
    //Do the following need to be if, then if elses, or can they all just be if?
    //Perfectly centered on line, continue moving forward
    if(sensorArray[0] == 0 && sensorArray[1] == 0 && sensorArray[2] >= 1000 && sensorArray[3] >= 1000 && sensorArray[4] >= 1000 && sensorArray[5] >= 1000 && sensorArray[6] == 0 && sensorArray[7] == 0 ){
      Robot.driveforward(20);
      delay(3000); //Drive for 3 seconds
      Robot.allstop();
    } 

    /*Right Adjustments
    */
    //Para 1 of strafe is direction, 1 = right, 2 = left. Second para is speed, we want this to be very slow. Need to test out the speeds.
    //Strafe slightly right, robot is a bit to the left of center. Then go forward.
    if(sensorArray[0] == 0 && sensorArray[1] >= 1000 && sensorArray[2] >= 1000 && sensorArray[3] >= 1000 && sensorArray[4] >= 1000 && sensorArray[5] == 0 && sensorArray[6] == 0 && sensorArray[7] == 0 ){
      Robot.strafe(1, 10); //With each greater strafe adjustment, the strafe speed will be a bit faster
      delay(2000); //Strafe slowly to the right for 3 seconds
      Robot.allstop();
      Robot.driveforward(18); //With each greater strafe adjustment, the drive forward speed will be a bit slower
      delay(2000)
      Robot.allstop();  
    }
    //Strafe slightly right, robot is a little farther to the left of center. Then go forward.
    if(sensorArray[0] >= 1000 && sensorArray[1] >= 1000 && sensorArray[2] >= 1000 && sensorArray[3] >= 1000 && sensorArray[4] == 0 && sensorArray[5] == 0 && sensorArray[6] == 0 && sensorArray[7] == 0 ){
      Robot.strafe(1, 12); 
      delay(2000);
      Robot.allstop();
      Robot.driveforward(16);
      delay(2000)
      Robot.allstop();  
    }
    //Strafe right,robot is left of center. Then go forward. 
    if(sensorArray[0] == 1000 && sensorArray[1] == 1000 && sensorArray[2] >= 1000 && sensorArray[3] == 0 && sensorArray[4] == 0 && sensorArray[5] == 0 && sensorArray[6] == 0 && sensorArray[7] == 0 ){
      Robot.strafe(1, 14);
      delay(2000);
      Robot.allstop();
      Robot.driveforward(14);
      delay(2000)
      Robot.allstop();
    }
    //Strafe right, robot is a bit past left of center. Then go forward
    if(sensorArray[0] >= 1000 && sensorArray[1] >= 1000 && sensorArray[2] == 0 && sensorArray[3] == 0 && sensorArray[4] == 0 && sensorArray[5] == 0 && sensorArray[6] == 0 && sensorArray[7] == 0 ){
      Robot.strafe(1, 16);
      delay(2000);
      Robot.allstop();
      Robot.driveforward(12);
      delay(2000)
      Robot.allstop();
    }
    }
    //Major adjust right, robot is very left of the line, almost off it. Then go forward.
    if(sensorArray[0] >= 1000 && sensorArray[1] == 0 && sensorArray[2] == 0 && sensorArray[3] == 0 && sensorArray[4] == 0 && sensorArray[5] == 0 && sensorArray[6] == 0 && sensorArray[7] == 0 ){
      Robot.strafe(1, 18);
      delay(2000);
      Robot.allstop();
      Robot.driveforward(10);
      delay(2000)
      Robot.allstop();
    }
    
    
    /*Left Adjustments
     */
    //Strafe slightly left, robot is a bit to the right of center. Then go forward.
    if(sensorArray[0] == 0 && sensorArray[1] == 0 && sensorArray[2] == 0 && sensorArray[3] >= 1000 && sensorArray[4] >= 1000 && sensorArray[5] >= 1000 && sensorArray[6] >= 1000 && sensorArray[7] == 0 ){
      Robot.strafe(2, 10); 
      delay(2000); 
      Robot.allstop();
      Robot.driveforward(18); 
      delay(2000)
      Robot.allstop();
    }
    //Strafe slightly left, robot is a little farther to the right of center. Then go forward.
    if(sensorArray[0] == 0 && sensorArray[1] == 0 && sensorArray[2] == 0 && sensorArray[3] == 0 && sensorArray[4] >= 1000 && sensorArray[5] >= 1000 && sensorArray[6] >= 1000 && sensorArray[7] >= 1000 ){
      Robot.strafe(2, 12); 
      delay(2000); 
      Robot.allstop();
      Robot.driveforward(16); 
      delay(2000)
      Robot.allstop();
    }
    //Strafe left, robot is right of center. Then go forward.
    if(sensorArray[0] == 0 && sensorArray[1] == 0 && sensorArray[2] == 0 && sensorArray[3] == 0 && sensorArray[4] == 0 && sensorArray[5] >= 1000 && sensorArray[6] >= 1000 && sensorArray[7] >= 1000 ){
      Robot.strafe(2, 14); 
      delay(2000); 
      Robot.allstop();
      Robot.driveforward(14); 
      delay(2000)
      Robot.allstop();
    }
    //Strafe left, robot is a bit past right of center. Then go forward.
    if(sensorArray[0] == 0 && sensorArray[1] == 0 && sensorArray[2] == 0 && sensorArray[3] == 0 && sensorArray[4] == 0 && sensorArray[5] == 0 && sensorArray[6] >= 1000 && sensorArray[7] >= 1000){
      Robot.strafe(2, 16); 
      delay(2000); 
      Robot.allstop();
      Robot.driveforward(12); 
      delay(2000)
      Robot.allstop();
    }
    //Major adjust left, robot is very right of line, almost off it. Then go forward.
    if(sensorArray[0] == 0 && sensorArray[1] == 0 && sensorArray[2] == 0 && sensorArray[3] == 0 && sensorArray[4] == 0 && sensorArray[5] == 0 && sensorArray[6] == 0 && sensorArray[7] >= 1000){
      Robot.strafe(2, 18); 
      delay(2000); 
      Robot.allstop();
      Robot.driveforward(10); 
      delay(2000)
      Robot.allstop();
    }
    
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
