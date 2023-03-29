#include<DDBot.h>
#include<Arduino.h>

#ifndef ForwardDDBot_h
#define ForwardDDBot_h

class ForwardDDBot : public DDBot {
   private:

    // this is the value used to "slow down" a motor
    // it is used when we want to turn, but don't want to set the speed of the other motor to 0
    // this will be calculated in the init() method by multiplying the maxPWM by the adjustment factor
    uint8_t _adjustedPWM;

    // "actual" values are written to a motor during a given call of the write() method
    // "target" values are the values that the user wants to write to a motor
    // in each call of the write() method, the actual values are adjusted to come closer to the target values
    uint8_t leftActualPWM, leftTargetPWM, rightActualPWM, rightTargetPWM;

   public:
    uint8_t maxPWM;    // maximum "speed" for each motor
    float adjustment;  // scaling factor used when slowing down a given motor


    // the constructors are responsible for setting the pin numbers from the arguments to the class properties
    ForwardDDBot();  // allow the user to directly set the arrays or the default PWM values
    ForwardDDBot(uint8_t maxPWM, float adjustment);
    ForwardDDBot(uint8_t directionPins[4], uint8_t PWMPins[2]);
    ForwardDDBot(uint8_t directionPins[4], uint8_t PWMPins[2], uint8_t maxPWM, float adjustment);

    void init();
    void calculateAdjustedPWM();

    void left();
    void centre();
    void right();
    void stop();

    // recall that rotations and moving backwards are not possible with this type of robot
    // so these methods are not implemented

    void write();

    ~ForwardDDBot();
};


#endif // ForwardDDBot_h
