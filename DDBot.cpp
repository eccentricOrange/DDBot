#include "DDBot.h"

#include <Arduino.h>

#ifndef DDBot_cpp
#define DDBot_cpp

DDBot::DDBot() {}
DDBot::~DDBot() {}

DDBot::DDBot(uint8_t directionPins[4]) {
    for (size_t i = 0; i < 4; i++) {
        this->directionPins[i] = directionPins[i];
    }
}

DDBot::DDBot(uint8_t directionPins[4], uint8_t PWMPins[2]) {
    for (size_t i = 0; i < 4; i++) {
        this->directionPins[i] = directionPins[i];
    }
    for (size_t i = 0; i < 2; i++) {
        this->PWMPins[i] = PWMPins[i];
    }
}

DDBot::DDBot(uint8_t directionPins[4], uint8_t PWMPin) {
    for (size_t i = 0; i < 4; i++) {
        this->directionPins[i] = directionPins[i];
    }
    this->PWMPin = PWMPin;
}

void DDBot::setPinModes() {
    for (size_t i = 0; i < 4; i++) {
        pinMode(directionPins[i], OUTPUT);
    }

    // do not set pinMode(s) for PWM pin(s) if they are not set (i.e. if they are 0)
    if (PWMPins[0] != 0 && PWMPins[1] != 0) {
        for (size_t i = 0; i < 2; i++) {
            pinMode(PWMPins[i], OUTPUT);
        }
    }

    if (PWMPin != 0) {
        pinMode(PWMPin, OUTPUT);
    }
}

void DDBot::setSpeed(uint8_t speed) {
    // do not set speed for PWM pin(s) if they are not set (i.e. if they are 0)
    if (PWMPins[0] != 0 && PWMPins[1] != 0) {
        analogWrite(PWMPins[0], speed);
        analogWrite(PWMPins[1], speed);
    }

    if (PWMPin != 0) {
        analogWrite(PWMPin, speed);
    }
}

void DDBot::setSpeed(uint8_t leftSpeed, uint8_t rightSpeed) {
    analogWrite(PWMPins[0], leftSpeed);
    analogWrite(PWMPins[1], rightSpeed);
}

void DDBot::writeDirections(bool leftForward, bool leftBackward, bool rightForward, bool rightBackward) {
    digitalWrite(directionPins[0], leftForward);
    digitalWrite(directionPins[1], leftBackward);
    digitalWrite(directionPins[2], rightForward);
    digitalWrite(directionPins[3], rightBackward);
}

void DDBot::writeDirections(bool leftForward, bool leftBackward, bool rightForward, bool rightBackward, uint8_t speed) {
    digitalWrite(directionPins[0], leftForward);
    digitalWrite(directionPins[1], leftBackward);
    digitalWrite(directionPins[2], rightForward);
    digitalWrite(directionPins[3], rightBackward);
    setSpeed(speed);
}

void DDBot::writeDirections(bool leftForward, bool leftBackward, bool rightForward, bool rightBackward, uint8_t leftSpeed, uint8_t rightSpeed) {
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

ForwardDDBot::ForwardDDBot() {}
ForwardDDBot::~ForwardDDBot() {}

ForwardDDBot::ForwardDDBot(uint8_t maxPWM, float adjustment) {
    this->maxPWM = maxPWM;
    this->adjustment = adjustment;
}

ForwardDDBot::ForwardDDBot(uint8_t directionPins[4], uint8_t PWMPins[2]) {
    for (size_t i = 0; i < 4; i++) {
        this->directionPins[i] = directionPins[i];
    }
    for (size_t i = 0; i < 2; i++) {
        this->PWMPins[i] = PWMPins[i];
    }
}
ForwardDDBot::ForwardDDBot(uint8_t directionPins[4], uint8_t PWMPins[2], uint8_t maxPWM, float adjustment) {
    for (size_t i = 0; i < 4; i++) {
        this->directionPins[i] = directionPins[i];
    }
    for (size_t i = 0; i < 2; i++) {
        this->PWMPins[i] = PWMPins[i];
    }

    this->maxPWM = maxPWM;
    this->adjustment = adjustment;
}

void ForwardDDBot::calculateAdjustedPWM() {
    // this is the value used to "slow down" a motor
    // it is used when we want to turn, but don't want to set the speed of the other motor to 0
    _adjustedPWM = this->maxPWM * this->adjustment;
}

void ForwardDDBot::init() {
    setPinModes();
    calculateAdjustedPWM();

    this->leftActualPWM = maxPWM;
    this->rightActualPWM = maxPWM;

    // set the robot to perpetually move forward
    forward(leftActualPWM, rightActualPWM);
}

// the following methods set the direction of the robot by controlling which
// motor spins faster and which one slower
// the logic here is the same as in the conventional differential drive robot
// and you can figure it out the same way
void ForwardDDBot::left() {
    leftTargetPWM = _adjustedPWM;
    rightTargetPWM = maxPWM;
}

void ForwardDDBot::right() {
    leftTargetPWM = maxPWM;
    rightTargetPWM = _adjustedPWM;
}

void ForwardDDBot::centre() {
    leftTargetPWM = maxPWM;
    rightTargetPWM = maxPWM;
}

void ForwardDDBot::stop() {
    leftTargetPWM = 0;
    rightTargetPWM = 0;
}

void ForwardDDBot::write() {
    // update "actual" PWM values so that they get closer to the "target" values
    // this will eventually get the values to equal, as exponential decay (but
    // with integer division)
    leftActualPWM = (leftTargetPWM + leftActualPWM) / 2;
    rightActualPWM = (rightTargetPWM + rightActualPWM) / 2;

    // write the actual PWM values to the motor driver
    analogWrite(PWMPins[0], leftActualPWM);
    analogWrite(PWMPins[1], rightActualPWM);
}

#endif  // DDBot_cpp
