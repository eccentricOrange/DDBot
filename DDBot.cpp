#include "DDBot.h"

#include <Arduino.h>

#ifndef DDBot_cpp
#define DDBot_cpp

DDBot::DDBot() {}

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
    for (size_t i = 0; i < 2; i++) {
        pinMode(PWMPins[i], OUTPUT);
    }
}

void DDBot::setSpeed(uint8_t speed) {
    analogWrite(PWMPins[0], speed);
    analogWrite(PWMPins[1], speed);
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
ForwardDDBot::ForwardDDBot(uint8_t maxPwm, float adjustment) {
    this->maxPwm = maxPwm;
    this->adjustment = adjustment;
}

ForwardDDBot::ForwardDDBot(const uint8_t directionPins[4], const uint8_t PWMPins[2]) {
    for (size_t i = 0; i < 4; i++) {
        this->directionPins[i] = directionPins[i];
    }
    for (size_t i = 0; i < 2; i++) {
        this->PWMPins[i] = PWMPins[i];
    }
}
ForwardDDBot::ForwardDDBot(const uint8_t directionPins[4], const uint8_t PWMPins[2], uint8_t maxPwm, float adjustment) {
    for (size_t i = 0; i < 4; i++) {
        this->directionPins[i] = directionPins[i];
    }
    for (size_t i = 0; i < 2; i++) {
        this->PWMPins[i] = PWMPins[i];
    }

    this->maxPwm = maxPwm;
    this->adjustment = adjustment;
}

void ForwardDDBot::init() {
    setPinModes();
    _adjustedPwm = this->maxPwm * this->adjustment;
    forward(leftActualPwm, rightActualPwm);
}

void ForwardDDBot::left() {
    leftTargetPwm = _adjustedPwm;
    rightTargetPwm = maxPwm;
}

void ForwardDDBot::right() {
    leftTargetPwm = maxPwm;
    rightTargetPwm = _adjustedPwm;
}

void ForwardDDBot::right() {
    leftTargetPwm = maxPwm;
    rightTargetPwm = maxPwm;
}

void ForwardDDBot::stop() {
    leftTargetPwm = 0;
    rightTargetPwm = 0;
}

void ForwardDDBot::write() {
    // Update "actual" PWM values so that they get closer to the "target" values. This will
    // eventually get the values to equal, as exponential decay (but with integer division).
    leftActualPwm = (leftTargetPwm + leftActualPwm) / 2;
    rightActualPwm = (rightTargetPwm + rightActualPwm) / 2;

    // Write the actual PWM values to the motor driver
    analogWrite(PWMPins[0], leftActualPwm);
    analogWrite(PWMPins[1], rightActualPwm);
}

#endif  // DDBot_cpp
