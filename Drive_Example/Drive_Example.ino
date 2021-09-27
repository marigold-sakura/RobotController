//test push
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

void setup() {
  Serial.begin(115200);
  delay(2000);
  Wire.setSDA(12);
  Wire.setSCL(13);
  Wire.begin();
  Robot.begin();
  start_btn.begin();
  Serial.println("- Cyber City Circuits -");

  Serial.println("Setting up Line Sensors");
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){16, 17, 18, 19, 20, 21, 22, 15}, SensorCount);
//  qtr.setEmitterPin(14);
/*
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }

  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }

  Serial.println("Line Sensors Ready");
*/

  Serial.println("Robot Online and Ready");
  Serial.println("Waiting on button to begin");

}

void setup1() {
  
}

void loop1() {
  
}

void loop() {
  CheckforButton();   //Main command, do not remove! This monitors button press for robot state
  
  if(Running == 1) {  //If the robot should be moving, do things here
    CheckSonar();
  }
  //CheckLineSensor();
  
  switch (StateMachine) {
    case 0: 
      Serial.println("Waiting to go!");
      Robot.led(0);                             //Turn the onboard LED Off
      Robot.allstop();
      break;
    case 1:                                     //Drive Forward State
      Robot.led(1);                             //Turn the onboard LED On
      Robot.driveforward(50); 
      Serial.println("Driving Forward 50%");
      StateMachine = 2;
      myTimer = millis() + 2000;                //Set up a timer flag for 2 seconds (2000 mS)
      Serial.println(StateMachine);
      break;
    case 2:                                     
      if(millis() > myTimer) {                  //Keep checking timer until time has passed, increase state machine
        StateMachine = 3;            
      }
      break;
    case 3:
      Robot.allstop();                          //Stop robot
      Serial.println("Stopping");
      StateMachine = 4;                         //Move ahead
      myTimer = millis() + 2000;                //Set up a timer flag for 2 seconds (2000 mS)
      break;      
    case 4:
      if(millis() > myTimer) {                  //Keep checking timer until time has passed
        StateMachine = 1;                       //Start machine state over
      }
      break;
    case 5:
      break;
    case 50:                                    //Forward Obstacle Avoidance
      Robot.allstop();
      int myTurn;
      myTurn = random(2);
      if(myTurn == 0) {
        Robot.leftturn(50);
      } else {
        Robot.rightturn(50);
      }
      myTimer = millis() + 500;                 //Set up 1/2 second timer (500mS)
      StateMachine = 51;
      break;
    case 51:
      if(millis() > myTimer) {                  //Check for time out to occur and finish turning
        StateMachine = 52;                      //Change State Machine
      }
      break;
    case 52:
      StateMachine = 1;                         //Go back to state machine 1
      break;
    case 60:                                    //Left Obstacle Avoidance
      Robot.allstop();
      Robot.rightturn(50);
      myTimer = millis() + 250;                 //Set up 1/4 second timer (250mS)
      StateMachine = 61;
      break;
    case 61:
      if(millis() > myTimer) {                  //Check for time out to occur and finish turning
        StateMachine = 62;                      //Change State Machine
      }
      break;
    case 62:
      StateMachine = 1;                         //Go back to state machine 1
      break;
    case 70:                                    //Right Obstacle Avoidance
      Robot.allstop();
      Robot.leftturn(50);
      myTimer = millis() + 250;                 //Set up 1/4 second timer (250mS)
      StateMachine = 71;
      break;
    case 71:
      if(millis() > myTimer) {                  //Check for time out to occur and finish turning
        StateMachine = 72;                      //Change State Machine
      }
      break;
    case 72:
      StateMachine = 1;                         //Go back to state machine 1
      break;
    case 100:
      Robot.allstop();
      break;
  }
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

void CheckSonar() {
  Robot.sonar();

  Serial.print("Sensor 0: ");
  Serial.println(Robot.leftecho); //Left Sensor
  
  Serial.print("Sensor 1: ");
  Serial.println(Robot.centerecho); //Middle Sensor

  Serial.print("Sensor 2: ");
  Serial.println(Robot.rightecho); //Right Sensor

  if(Robot.centerecho < 50) {       //If anything gets within 50 CM of this sensor, trigger
    if(StateMachine != 51) {        //If we've already been here, we want to give time for the turn to clear
      StateMachine = 50;            //Trigger front obstacle avoidance
      Serial.println("Moving to State 50");
    }
  }

  if(Robot.rightecho < 40) {     //If anything gets within 40 CM of this sensor, trigger
    StateMachine = 60;           //Trigger left obstacle avoidance
    Serial.println("Moving to State 60");
  }

  if(Robot.leftecho < 40) {
    StateMachine = 70;           //Trigger right obstacle avoidance
    Serial.println("Moving to State 70");
  }

}

void CheckLineSensor() {
  uint16_t position = qtr.readLineWhite(sensorValues);
  Serial.print("Line Position: ");
  Serial.println(position);  
}
