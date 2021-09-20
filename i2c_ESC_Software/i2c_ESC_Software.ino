/*
 * Cyber City Circuits ESC Motor Driver 5A
 * Chris Williamson
 * 
 * i2c on Pins 18 and 19
 * address pins on 11 and 12
 * Address table:
 * -----------------------------
 *          D11        D12
 * 16       HIGH       HIGH
 * 17       HIGH       LOW
 * 18       LOW        LOW
 * 19       LOW        HIGH
 * 
 * I2C addresses can be 16, 17, 18, 19
 *
 *
 * I2C Registry Calls
 * 
 * First Byte is the command byte
 * -------------------------------------------
 * 1 = Forward
 *    Next byte is speed
 * 2 = Reverse
 *    Next byte is speed
 * 3 = Stop
 *    No byte expected
 * 4 = Encoder Reset
 *    No byte expected
 * 5 = Encoder Move Forward to Position
 *    Next bytes are encoder position
 *    Final byte is speed
 * 6 = Encder Move Reverse to Position
 *    Next bytes are encoder position
 *    Final byte is speed
 * 7 = Encoder Read
 *    Return current encoder count
 * 8 = Reset Driver
 *    Reset Motor Driver Chip 
 * 9 = Braking on Motor
 *    Next byte 0 for coasting or 1 for braking
 */

#include <Wire.h>
#include <SoftwareSerial.h>
#include <Encoder.h>

const int EncoderA = 2;
const int EncoderB = 3;
const int Dir = 5;
const int PWM = 6;
const int Enable = 7;
const int DIS = 8;
const int Status = 13;
const int Fault = 14;
boolean isfault = false;
long encPos;

int i2cadd = 16;
//SoftwareSerial mySerial(12, 11); // RX, TX
Encoder myEnc(2,3);

void setup() {
  //mySerial.begin(9600);
  
  pinMode(Dir, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(Enable, OUTPUT);
  pinMode(DIS, OUTPUT);
  pinMode(Status, OUTPUT);
  pinMode(Fault, INPUT);

  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  
  digitalWrite(Enable, HIGH);
  digitalWrite(DIS, LOW);

  Readi2caddress();
  
  Wire.begin(i2cadd);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event    
}

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != encPos) {
    encPos = newPosition;
  }
}

void Readi2caddress() {
  int pin1 = digitalRead(11);
  int pin2 = digitalRead(12);

  if(pin1 == 1 && pin2 == 1) {
    i2cadd = 16;
    return;
  }
  if(pin1 == 1 && pin2 == 0) {
    i2cadd = 17;
    return;
  }
  if(pin1 == 0 && pin2 == 0) {
    i2cadd = 18;
    return;
  }
  if(pin1 == 0 && pin2 == 1) {
    i2cadd = 19;
    return;
  }
}

void receiveEvent(int howMany)
{
  int mydata[10];
  int cur_byte = 0;
  int x;
  
  while (Wire.available()) {
    mydata[cur_byte] = Wire.read();
    if(mydata == 255) { break; }
    cur_byte++;
  }

  int array_length = cur_byte;

  switch (mydata[0]) {
    case 1:  //Drive Forward
      x = mydata[1];
      //x = Wire.read();    // receive byte as an integer
      processDir(1, x);
      //processForward(x);
      break;
    case 2:  //Drive Reverse
      x = mydata[1];
      processDir(0, x);
      //processReverse(x);
      break;
    case 3:  //Stop
      processStop();
      break;
    case 4:  //Encoder Reset
      encPos = 0;
      break;
    case 5:  //Encoder Move Forward to Position by Speed
      break;
    case 6:  //Encoder Move Reverse to Position by Speed
      break;
    case 7:  //Encoder Read
      Wire.write(encPos);
      break;   
    case 8:  //Reset Driver
      FaultState();
      break;
    case 9:  //Brake Mode
      break;
  }
  //mySerial.print("Direction: ");
  //mySerial.println(c);         // print the character

  //mySerial.print("Speed: ");
  //mySerial.println(x);         // print the integer
}

void processDir(int myDir, int aNumber) {
    int Speed = 0;
    Speed = map(aNumber, 0, 100, 0, 255);
    digitalWrite(Dir, myDir);
    analogWrite(PWM, Speed);
}

void processStop() {
    int aNumber = 1;
    int Speed = 0;
    Speed = map(aNumber, 0, 100, 0, 255);
    digitalWrite(Dir, LOW);
    analogWrite(PWM, Speed);
}

void FaultState() {
    digitalWrite(Status, LOW);
    for(int x = 0; x < 6; x++) {
      digitalWrite(Status, HIGH);
      delay(250);
      digitalWrite(Status, LOW);
      delay(100);
    }
    delay(500);
    digitalWrite(Enable, LOW);
    digitalWrite(DIS, HIGH);
    delay(100);
    digitalWrite(Enable, HIGH);
    digitalWrite(DIS, LOW);
    isfault = false;
}
