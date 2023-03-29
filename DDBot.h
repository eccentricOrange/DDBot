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

    // the sequence of pins is important, and is used throughout the library
    // the first two pins are for the left motor, and the second two are for the right motor
    // the first pin in each pair is for the forward direction, and the second is for the backward direction
    uint8_t directionPins[4];

    // when each motor has a dedicated PWM pin, it's possible to control the speed of each motor independently
    // in other cases, the speed of each motor is controlled by the same PWM pin
    // two declarations exist to accommodate both cases, and this pattern is used throughout the library
    uint8_t PWMPins[2] = {0, 0};
    uint8_t PWMPin = 0;

    // the constructors are responsible for setting the pin numbers from the arguments to the class properties
    DDBot();  // allow the user to directly set the arrays
    DDBot(uint8_t directionPins[4]);
    DDBot(uint8_t directionPins[4], uint8_t PWMPins[2]);
    DDBot(uint8_t directionPins[4], uint8_t PWMPin);

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




#endif  // DDBot_h
