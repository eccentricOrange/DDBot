#include <Arduino.h>

#include <array>

#ifndef DDBot_h
#define DDBot_h

class DDBot {
   private:
   public:
    std::array<uint8_t, 4> _directionPins;
    std::array<uint8_t, 4> _PWMPins;

    DDBot();
    DDBot(std::array<uint8_t, 4> directionPins);
    DDBot(std::array<uint8_t, 4> directionPins, std::array<uint8_t, 2> PWMPins);

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

#endif  // DDBot_h
