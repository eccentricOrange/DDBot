#include <Arduino.h>

#ifndef DDBot_h
#define DDBot_h

class DDBot {
   private:
   public:
    uint8_t directionPins[4];
    uint8_t PWMPins[2];
    uint8_t PWMPin;

    DDBot();
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

    void stop();

    ~DDBot();
};

class ForwardDDBot: public DDBot {
   private:
    float _adjustedPwm;

    uint8_t leftActualPwm = 255,
            leftTargetPwm = 255,
            rightActualPwm = 255,
            rightTargetPwm = 255;

   public:
    uint8_t maxPwm;    // Maximum "speed" for each motor
    float adjustment;  // Scaling factor used when slowing down a given motor.

    ForwardDDBot();
    ForwardDDBot(uint8_t maxPwm, float adjustment);
    ForwardDDBot(uint8_t directionPins[4], uint8_t PWMPins[2]);
    ForwardDDBot(uint8_t directionPins[4], uint8_t PWMPins[2], uint8_t maxPwm, float adjustment);

    void init();

    void left();
    void centre();
    void right();
    void stop();

    void write();

    ~ForwardDDBot();
};

#endif  // DDBot_h
