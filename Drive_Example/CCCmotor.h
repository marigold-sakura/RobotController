#ifndef CCCmotor_h
#define CCCmotor_h

#include "Arduino.h"
#include "Wire.h"

class CCCmotor{
    public:
        CCCmotor(int motorAddress);
        void drive(int motorDirection, int motorSpeed);
        void stop();
    private:
        int _motorAddress;
        int _motorDirection;
        int _motorSpeed;

};


#endif
