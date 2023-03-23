#include "DDBot.h"

#include <Arduino.h>

#ifndef DDBot_cpp
#define DDBot_cpp

DDBot::DDBot() {}

DDBot::DDBot(std::array<uint8_t, 4> directionPins) {
    for (size_t i = 0; i < directionPins.size(); i++) {
        this->_directionPins[i] = directionPins[i];
    }
}

DDBot::DDBot(std::array<uint8_t, 4> directionPins, std::array<uint8_t, 2> PWMPins) {
    for (size_t i = 0; i < directionPins.size(); i++) {
        this->_directionPins[i] = directionPins[i];
    }
    for (size_t i = 0; i < PWMPins.size(); i++) {
        this->_PWMPins[i] = PWMPins[i];
    }
}

void DDBot::setPinModes() {
    for (size_t i = 0; i < _directionPins.size(); i++) {
        pinMode(_directionPins[i], OUTPUT);
    }
    for (size_t i = 0; i < _PWMPins.size(); i++) {
        pinMode(_PWMPins[i], OUTPUT);
    }
}

void DDBot::setSpeed(uint8_t speed) {
    analogWrite(_PWMPins[0], speed);
    analogWrite(_PWMPins[1], speed);
}

void DDBot::setSpeed(uint8_t leftSpeed, uint8_t rightSpeed) {
    analogWrite(_PWMPins[0], leftSpeed);
    analogWrite(_PWMPins[1], rightSpeed);
}

void DDBot::writeDirections(bool leftForward, bool leftBackward, bool rightForward, bool rightBackward) {
    digitalWrite(_directionPins[0], leftForward);
    digitalWrite(_directionPins[1], leftBackward);
    digitalWrite(_directionPins[2], rightForward);
    digitalWrite(_directionPins[3], rightBackward);
}

void DDBot::writeDirections(bool leftForward, bool leftBackward, bool rightForward, bool rightBackward, uint8_t speed) {
    digitalWrite(_directionPins[0], leftForward);
    digitalWrite(_directionPins[1], leftBackward);
    digitalWrite(_directionPins[2], rightForward);
    digitalWrite(_directionPins[3], rightBackward);
    setSpeed(speed);
}

void DDBot::writeDirections(bool leftForward, bool leftBackward, bool rightForward, bool rightBackward, uint8_t leftSpeed, uint8_t rightSpeed) {
    digitalWrite(_directionPins[0], leftForward);
    digitalWrite(_directionPins[1], leftBackward);
    digitalWrite(_directionPins[2], rightForward);
    digitalWrite(_directionPins[3], rightBackward);
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

#endif  // DDBot_cpp
