#ifndef CCCDrive_h
#define CCCDrive_h

#include "Arduino.h"
#include "Wire.h"
//#include "CCCmotor.h"

/*
#define MotorFL 16
#define MotorFR 17
#define MotorRR 18
#define MotorRL 19
*/

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
        int Motors[4] = {16,17,18,19};
        //CCCmotor motorFL(16);
        //CCCmotor motorRR(17);
        //CCCmotor motorFR(18);
        //CCCmotor motorRL(19);  
        /*
        CCCmotor motorFL(MotorFL);
        CCCmotor motorRR(MotorRR);
        CCCmotor motorFR(MotorFR);
        CCCmotor motorRL(MotorRL);  
        */
    private:
    int _motorAddress;
    int _motorDirection;
    int _motorSpeed;

};

#endif
