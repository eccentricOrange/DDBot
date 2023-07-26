#include "DDBot.h"

#include <Arduino.h>

DDBot::DDBot() {}

DDBot::DDBot(
    uint8_t directionPinsIn[NUMBER_OF_DIRECTION_PINS],
    uint8_t PWMPinsIn[NUMBER_OF_PWM_PINS]
) {
    for (size_t i = 0; i < NUMBER_OF_DIRECTION_PINS; i++) {
        directionPins[i] = directionPinsIn[i];
    }
    for (size_t i = 0; i < NUMBER_OF_PWM_PINS; i++) {
        PWMPins[i] = PWMPinsIn[i];
    }
}

DDBot::DDBot(
    uint8_t directionPinsIn[NUMBER_OF_DIRECTION_PINS],
    uint8_t PWMPinIn
) {
    for (size_t i = 0; i < NUMBER_OF_DIRECTION_PINS; i++) {
        directionPins[i] = directionPinsIn[i];
    }
    PWMPin = PWMPinIn;
}

DDBot::DDBot(
    uint8_t leftForwardPin,
    uint8_t leftBackwardPin,
    uint8_t rightForwardPin,
    uint8_t rightBackwardPin,
    uint8_t leftPWMPin,
    uint8_t rightPWMPin
) {
    directionPins[0] = leftForwardPin;
    directionPins[1] = leftBackwardPin;
    directionPins[2] = rightForwardPin;
    directionPins[3] = rightBackwardPin;
    PWMPins[0] = leftPWMPin;
    PWMPins[1] = rightPWMPin;
}

DDBot::DDBot(
    uint8_t leftForwardPin,
    uint8_t leftBackwardPin,
    uint8_t rightForwardPin,
    uint8_t rightBackwardPin,
    uint8_t PWMPinIn
) {
    directionPins[0] = leftForwardPin;
    directionPins[1] = leftBackwardPin;
    directionPins[2] = rightForwardPin;
    directionPins[3] = rightBackwardPin;
    PWMPin = PWMPinIn;
}

void DDBot::setPinModes() {
    for (size_t i = 0; i < NUMBER_OF_DIRECTION_PINS; i++) {
        pinMode(directionPins[i], OUTPUT);
    }

    // do not set pinMode(s) for PWM pin(s) if they are not set (i.e. if they are 0)
    if (PWMPins[0] != 0 && PWMPins[1] != 0) {
        for (size_t i = 0; i < NUMBER_OF_PWM_PINS; i++) {
            pinMode(PWMPins[i], OUTPUT);
        }
    }

    if (PWMPin != 0) {
        pinMode(PWMPin, OUTPUT);
    }
}

void DDBot::setSpeed(uint8_t speed) {
    // scale from the user-friendly 0-100 range to the 0-255 range
    const uint8_t PWM = speed * SPEED_FACTOR;

    // do not set speed for PWM pin(s) if they are not set (i.e. if they are 0)
    if (PWMPins[0] != 0 && PWMPins[1] != 0) {
        analogWrite(PWMPins[0], PWM);
        analogWrite(PWMPins[1], PWM);
    }

    if (PWMPin != 0) {
        analogWrite(PWMPin, PWM);
    }
}

void DDBot::setSpeed(uint8_t leftSpeed, uint8_t rightSpeed) {
    // do not set speed for PWM pin(s) if they are not set (i.e. if they are 0)
    if (PWMPins[0] != 0 && PWMPins[1] != 0) {
        
        // scale from the user-friendly 0-100 range to the 0-255 range
        analogWrite(PWMPins[0], leftSpeed * SPEED_FACTOR);
        analogWrite(PWMPins[1], rightSpeed * SPEED_FACTOR);
    }
}

void DDBot::writeDirections(
    bool leftForward,
    bool leftBackward,
    bool rightForward,
    bool rightBackward
) {
    digitalWrite(directionPins[0], leftForward);
    digitalWrite(directionPins[1], leftBackward);
    digitalWrite(directionPins[2], rightForward);
    digitalWrite(directionPins[3], rightBackward);
}

void DDBot::writeDirections(
    bool leftForward,
    bool leftBackward,
    bool rightForward,
    bool rightBackward,
    uint8_t speed
) {
    digitalWrite(directionPins[0], leftForward);
    digitalWrite(directionPins[1], leftBackward);
    digitalWrite(directionPins[2], rightForward);
    digitalWrite(directionPins[3], rightBackward);
    setSpeed(speed);
}

void DDBot::writeDirections(
    bool leftForward,
    bool leftBackward,
    bool rightForward,
    bool rightBackward,
    uint8_t leftSpeed,
    uint8_t rightSpeed
) {
    digitalWrite(directionPins[0], leftForward);
    digitalWrite(directionPins[1], leftBackward);
    digitalWrite(directionPins[2], rightForward);
    digitalWrite(directionPins[3], rightBackward);
    setSpeed(leftSpeed, rightSpeed);
}

// the following methods set the direction of the robot by controlling which
// direction motors are going to turn and in which direction
// you can figure out these methods by trying to imagine the robot, maybe
// using a model or a drawing
void DDBot::forward() {
    writeDirections(HIGH, LOW, HIGH, LOW);
}

void DDBot::forward(uint8_t speed) {
    writeDirections(HIGH, LOW, HIGH, LOW, speed);
}

void DDBot::forward(uint8_t leftSpeed, uint8_t rightSpeed) {
    writeDirections(HIGH, LOW, HIGH, LOW, leftSpeed, rightSpeed);
}

void DDBot::backward() {
    writeDirections(LOW, HIGH, LOW, HIGH);
}

void DDBot::backward(uint8_t speed) {
    writeDirections(LOW, HIGH, LOW, HIGH, speed);
}

void DDBot::backward(uint8_t leftSpeed, uint8_t rightSpeed) {
    writeDirections(LOW, HIGH, LOW, HIGH, leftSpeed, rightSpeed);
}

void DDBot::left() {
    writeDirections(LOW, HIGH, LOW, LOW);
}

void DDBot::left(uint8_t speed) {
    writeDirections(LOW, HIGH, LOW, LOW, speed);
}

void DDBot::left(uint8_t leftSpeed, uint8_t rightSpeed) {
    writeDirections(LOW, HIGH, LOW, LOW, leftSpeed, rightSpeed);
}

void DDBot::right() {
    writeDirections(LOW, LOW, LOW, HIGH);
}

void DDBot::right(uint8_t speed) {
    writeDirections(LOW, LOW, LOW, HIGH, speed);
}

void DDBot::right(uint8_t leftSpeed, uint8_t rightSpeed) {
    writeDirections(LOW, LOW, LOW, HIGH, leftSpeed, rightSpeed);
}

void DDBot::clockwise() {
    writeDirections(LOW, HIGH, HIGH, LOW);
}

void DDBot::clockwise(uint8_t speed) {
    writeDirections(LOW, HIGH, HIGH, LOW, speed);
}

void DDBot::clockwise(uint8_t leftSpeed, uint8_t rightSpeed) {
    writeDirections(LOW, HIGH, HIGH, LOW, leftSpeed, rightSpeed);
}

void DDBot::counterClockwise() {
    writeDirections(HIGH, LOW, LOW, HIGH);
}

void DDBot::counterClockwise(uint8_t speed) {
    writeDirections(HIGH, LOW, LOW, HIGH, speed);
}

void DDBot::counterClockwise(uint8_t leftSpeed, uint8_t rightSpeed) {
    writeDirections(HIGH, LOW, LOW, HIGH, leftSpeed, rightSpeed);
}

void DDBot::stop() {
    writeDirections(LOW, LOW, LOW, LOW);
}
