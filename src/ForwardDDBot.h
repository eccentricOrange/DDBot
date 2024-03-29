/* Forward Differential Drive Bot
    This is a **differential wheeled robot** with a forward bias, and direction is set by varying
   just the speed of each motor. So while the classic differential drive bot can use the same
   physical structure, the functionality is different. For example, a forward differential drive bot
   can't turn in place or move backwards.

    This class was built for line following robots, where the robot is biased towards moving
   forward, and just incrementally varying the speed provides smoother control than the classic
   differential drive bot. This is important to ensure that the robot doesn't overshoot and lose
   track of the line.

    Conventionally, the direction of a differential wheeled robot is set by turning motors on or off
   in a specific direction. In this setup, they are set to move forward perpetually, and direction
   control is achieved by varying the speed of each motor instead. This allows for smoother turns
   and will (hopefully) help the robot to stay on its line more reliably.

    The main loop should be structured to use open-loop control. To use this library, the user
   should call the method of the appropriate direction when they want, and call the `write()`
   method once per loop. This will update the speed of each motor to come closer to the target
   speed. This is done to avoid sudden changes in speed. A delay might have to be added to the main
   loop to allow the changes to propagate.
*/

#if !defined(ForwardDDBot_h)
#define ForwardDDBot_h

#include <Arduino.h>

#include "DDBot.h"

class ForwardDDBot : public DDBot {
   private:
    // this is the value used to "slow down" a motor
    // it is used when we want to turn, but don't want to set the speed of the other motor to 0
    // this will be calculated in the init() method by multiplying the maxSpeed by the adjustment
    // factor
    uint8_t _adjustedSpeed;

    // "actual" values are written to a motor during a given call of the write() method
    // "target" values are the values that the user wants to write to a motor
    // in each call of the write() method, the actual values are adjusted to come closer to the
    // target values
    uint8_t rightTargetSpeed, leftTargetSpeed;
    uint16_t rightActualSpeed, leftActualSpeed;  // 16-bit to avoid overflow in the `write()` method

   public:
    uint8_t maxSpeed;    // maximum "speed" for each motor
    float adjustment;  // scaling factor used when slowing down a given motor

    // the constructors are responsible for setting the pin numbers from the arguments to the class
    // properties
    ForwardDDBot();  // allow the user to directly set the arrays or the default PWM pin values
    ForwardDDBot(uint8_t maxSpeedIn, float adjustmentIn);
    ForwardDDBot(
        uint8_t directionPinsIn[NUMBER_OF_DIRECTION_PINS],
        uint8_t PWMPinsIn[NUMBER_OF_PWM_PINS]
    );
    ForwardDDBot(
        uint8_t directionPinsIn[NUMBER_OF_DIRECTION_PINS],
        uint8_t PWMPinsIn[NUMBER_OF_PWM_PINS],
        uint8_t maxSpeedIn,
        float adjustmentIn
    );
    ForwardDDBot(
        uint8_t leftForwardPin,
        uint8_t leftBackwardPin,
        uint8_t rightForwardPin,
        uint8_t rightBackwardPin,
        uint8_t leftPWMPin,
        uint8_t rightPWMPin
    );
    ForwardDDBot(
        uint8_t leftForwardPin,
        uint8_t leftBackwardPin,
        uint8_t rightForwardPin,
        uint8_t rightBackwardPin,
        uint8_t leftPWMPin,
        uint8_t rightPWMPin,
        uint8_t maxSpeedIn,
        float adjustmentIn
    );

    void init();
    void calculateAdjustedSpeed();

    void left();
    void centre();
    void right();
    void stop();

    // recall that rotations and moving backwards are not possible with this type of robot
    // so these methods are not implemented

    void write();

    ~ForwardDDBot() = default;
};

#endif  // ForwardDDBot_h
