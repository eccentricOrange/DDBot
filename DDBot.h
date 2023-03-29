#include <Arduino.h>

#ifndef DDBot_h
#define DDBot_h

/* Differential Drive Bot
    This is a conventional **differential wheeled robot**, and direction is set by varying which motors spin
    and in which direction.

    Here, speed control of a motor simply controls how fast the robot moves. The expected use of this library
    just involves the user calling the method of the appropriate direction and/or speed in their main loop.
*/

class DDBot {
   private:
   public:
    static const uint8_t NUMBER_OF_DIRECTION_PINS = 4;
    static const uint8_t NUMBER_OF_PWM_PINS = 2;

    // the sequence of pins is important, and is used throughout the library
    // the first two pins are for the left motor, and the second two are for the right motor
    // the first pin in each pair is for the forward direction, and the second is for the backward direction
    uint8_t directionPins[NUMBER_OF_DIRECTION_PINS];

    // when each motor has a dedicated PWM pin, it's possible to control the speed of each motor independently
    // in other cases, the speed of each motor is controlled by the same PWM pin
    // two declarations exist to accommodate both cases, and this pattern is used throughout the library
    uint8_t PWMPins[NUMBER_OF_PWM_PINS] = {0, 0};
    uint8_t PWMPin = 0;

    // the constructors are responsible for setting the pin numbers from the arguments to the class properties
    DDBot();  // allow the user to directly set the arrays
    DDBot(uint8_t directionPins[NUMBER_OF_DIRECTION_PINS]);
    DDBot(uint8_t directionPins[NUMBER_OF_DIRECTION_PINS], uint8_t PWMPins[NUMBER_OF_PWM_PINS]);
    DDBot(uint8_t directionPins[NUMBER_OF_DIRECTION_PINS], uint8_t PWMPin);

    void setPinModes();

    void setSpeed(uint8_t speed);
    void setSpeed(uint8_t leftSpeed, uint8_t rightSpeed);

    void writeDirections(bool leftForward, bool leftBackward, bool rightForward, bool rightBackward);
    void writeDirections(bool leftForward, bool leftBackward, bool rightForward, bool rightBackward, uint8_t speed);
    void writeDirections(bool leftForward, bool leftBackward, bool rightForward, bool rightBackward, uint8_t leftSpeed, uint8_t rightSpeed);

    void forward();
    void forward(uint8_t speed);
    void forward(uint8_t leftSpeed, uint8_t rightSpeed);

    void backward();
    void backward(uint8_t speed);
    void backward(uint8_t leftSpeed, uint8_t rightSpeed);

    void left();
    void left(uint8_t speed);
    void left(uint8_t leftSpeed, uint8_t rightSpeed);

    void right();
    void right(uint8_t speed);
    void right(uint8_t leftSpeed, uint8_t rightSpeed);

    void clockwise();
    void clockwise(uint8_t speed);
    void clockwise(uint8_t leftSpeed, uint8_t rightSpeed);

    void counterClockwise();
    void counterClockwise(uint8_t speed);
    void counterClockwise(uint8_t leftSpeed, uint8_t rightSpeed);

    // it doesn't make sense to specify a PWM variant of a stop command
    void stop();

    ~DDBot();
};


/* Forward Differential Drive Bot
    This is a **differential wheeled robot** with a forward bias, and direction is set by varying just the
    speed of each motor. So while the classic differential drive bot can use the same physical structure,
    the functionality is different. For example, a forward differential drive bot can't turn in place or
    move backwards.

    This class was built for line following robots, where the robot is biased towards moving forward, and
    just incrementally varying the speed provides smoother control than the classic differential drive bot.
    This is important to ensure that the robot doesn't overshoot and lose track of the line.

    Conventionally, the direction of a differential wheeled robot is set by turning motors on
    or off in a specific direction. In this setup, they are set to move forward perpetually, and
    direction control is achieved by varying the speed of each motor instead. This allows for
    smoother turns and will (hopefully) help the robot to stay on its line more reliably.

    The main loop should be structured to use feedback control. To use this library, the user should call
    the method of the appropriate direction when they want, and call the `write()` method once per loop.
    This will update the speed of each motor to come closer to the target speed. This is done to avoid
    sudden changes in speed. A delay might have to be added to the main loop to allow the changes to
    propagate.
*/

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
    ForwardDDBot(uint8_t directionPins[NUMBER_OF_DIRECTION_PINS], uint8_t PWMPins[NUMBER_OF_PWM_PINS]);
    ForwardDDBot(uint8_t directionPins[NUMBER_OF_DIRECTION_PINS], uint8_t PWMPins[NUMBER_OF_PWM_PINS], uint8_t maxPWM, float adjustment);

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

#endif  // DDBot_h
