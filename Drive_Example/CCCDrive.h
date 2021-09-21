#ifndef CCCDrive_h
#define CCCDrive_h

#include "Arduino.h"
#include "Wire.h"

class CCCDrive {
    public:
        CCCDrive();
        void begin();
        void stop(int motorAddress);
        void allstop();
        void driveforward(int speed);   
        void drivereverse(int speed);
        void leftturn(int speed);
        void rightturn(int speed);
        void strafe(int dir, int speed);
        void diagonal(int dir, int speed); 
        void drive(int motor, int dir, int speed); 
        void sonar();
        void ping(int sensornumber);   
        int RightFront = 16;
        int LeftRear = 17;
        int LeftFront = 18;
        int RightRear = 19;
        int Motors[4] = {LeftFront, LeftRear, RightFront, RightRear};
        int Echo_Pins[3] = {9, 10, 11};
        int Trigger_Pin = 8;
        long echo[3];
    private:
        int _motorAddress;
        int _motorDirection;
        int _motorSpeed;

};

#endif
