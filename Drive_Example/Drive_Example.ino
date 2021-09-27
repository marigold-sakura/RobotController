
#include "src/CCCDrive/CCCDrive.h"
#include "src/Pololu/QTRSensors.h"
#include "src/Button/Button.h"

CCCDrive Robot;
QTRSensors qtr;
Button start_btn(7); //Connect momentary to GPIO 7

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

int StateMachine = 0; //Set up variable to hold state machine logic
int Running = 1;      //Set up variable to determine if the robot should be moving
long myTimer = 0;




void setup()
{
  // configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){15, 22, 21, 20, 19, 18, 17, 16}, SensorCount);
  qtr.setEmitterPin(14);

  Serial.begin(115200);
  delay(10000);
  Wire.setSDA(12);
  Wire.setSCL(13);
  Wire.begin();
  Robot.begin();
  start_btn.begin();
  Serial.println("- Cyber City Circuits -");
   Serial.println("Robot Online and Ready");
  Serial.println("Waiting on button to begin");

}


void loop()
{
  // read raw sensor values
  qtr.read(sensorValues);
  CheckforButton();   //Main command, do not remove! This monitors button press for robot state
  
  if(Running == 1) {  //If the robot should be moving, do things here
    LineFollowing();
    
    
    }



    switch (StateMachine) {
    case 0: 
      Serial.println("Waiting to go!");
      Robot.led(0);                             //Turn the onboard LED Off
      Robot.allstop();
      break;
    case 100: 
    Robot.driveforward(50);

    break;
    case 101:
    Robot.leftturn(50);

    break;
    case 102:

    Robot.rightturn(50);




    break;
    }

     


    

  // print the sensor values as numbers from 0 to 2500, where 0 means maximum
  // reflectance and 2500 means minimum reflectance

    
    
 
}


void CheckforButton() {
  switch (Running) {
    case 0:
      if(start_btn.pressed()) {
        Serial.println("Button Pressed, Beginning Routine");
        Running = 1;  
        StateMachine = 1;
      }
      break;
    case 1:
      if(start_btn.pressed()) {
        Serial.println("Button Pressed, Stopping Routine");
        Running = 0;
        StateMachine = 0;
      }
      break;
  }
}

void LineFollowing(){
  
    //go straight if the middle two sensors detect reflectance
    if (sensorValues[20] && sensorValues[19] > 94){
    
  
    StateMachine = 100;
  
    }

    //turn left if the left 3 
    if ((sensorValues[15] || sensorValues[22]) || (sensorValues[21] && sensorValues[22])){
  
    StateMachine = 101;
    //turn left
  
    }



    if ((sensorValues[18] || sensorValues[17]) || (sensorValues[16] && sensorValues[17])){
  
    StateMachine = 102;
    //turn right
  
    }



    


  
  }
