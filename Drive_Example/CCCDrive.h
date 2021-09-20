#ifndef CCCDrive_h
#define CCCDrive_h

#include "Arduino.h"
#include "Wire.h"
#include "CCCmotor.h"

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
        void allstop();
        void driveforward(int speed);   
        void drivereverse(int speed);
        void leftturn(int speed);
        void rightturn(int speed);
        void strafe(int dir, int speed);
        void diagonal(int dir, int speed);     
        int MotorFL = 16;
        int MotorFR = 17;
        int MotorRR = 18;
        int MotorRL = 19;
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

};

#endif
