#include "ForwardDDBot.h"

#include <Arduino.h>

ForwardDDBot::ForwardDDBot() {}

ForwardDDBot::ForwardDDBot(uint8_t maxSpeedIn, float adjustmentIn) {
    maxSpeed = maxSpeedIn;
    adjustment = adjustmentIn;
}

ForwardDDBot::ForwardDDBot(
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

ForwardDDBot::ForwardDDBot(uint8_t directionPinsIn[NUMBER_OF_DIRECTION_PINS],
    uint8_t PWMPinsIn[NUMBER_OF_PWM_PINS],
    uint8_t maxSpeedIn,
    float adjustmentIn
) {
    for (size_t i = 0; i < NUMBER_OF_DIRECTION_PINS; i++) {
        directionPins[i] = directionPinsIn[i];
    }
    for (size_t i = 0; i < NUMBER_OF_PWM_PINS; i++) {
        PWMPins[i] = PWMPinsIn[i];
    }

    maxSpeed = maxSpeedIn;
    adjustment = adjustmentIn;
}

ForwardDDBot::ForwardDDBot(
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

ForwardDDBot::ForwardDDBot(
    uint8_t leftForwardPin,
    uint8_t leftBackwardPin,
    uint8_t rightForwardPin,
    uint8_t rightBackwardPin,
    uint8_t leftPWMPin,
    uint8_t rightPWMPin,
    uint8_t maxSpeedIn,
    float adjustmentIn
) {
    directionPins[0] = leftForwardPin;
    directionPins[1] = leftBackwardPin;
    directionPins[2] = rightForwardPin;
    directionPins[3] = rightBackwardPin;
    PWMPins[0] = leftPWMPin;
    PWMPins[1] = rightPWMPin;

    maxSpeed = maxSpeedIn;
    adjustment = adjustmentIn;
}

void ForwardDDBot::calculateAdjustedSpeed() {
    // this is the value used to "slow down" a motor
    // it is used when we want to turn, but don't want to set the speed of the other motor to 0
    _adjustedSpeed = maxSpeed * adjustment;
}

void ForwardDDBot::init() {
    setPinModes();
    calculateAdjustedSpeed();

    leftActualSpeed = maxSpeed;
    rightActualSpeed = maxSpeed;

    // set the robot to perpetually move forward
    forward(leftActualSpeed, rightActualSpeed);
}

// the following methods set the direction of the robot by controlling which
// motor spins faster and which one slower
// the logic here is the same as in the conventional differential drive robot
// and you can figure it out the same way
void ForwardDDBot::left() {
    leftTargetSpeed = _adjustedSpeed;
    rightTargetSpeed = maxSpeed;
}

void ForwardDDBot::right() {
    leftTargetSpeed = maxSpeed;
    rightTargetSpeed = _adjustedSpeed;
}

void ForwardDDBot::centre() {
    leftTargetSpeed = maxSpeed;
    rightTargetSpeed = maxSpeed;
}

void ForwardDDBot::stop() {
    leftTargetSpeed = 0;
    rightTargetSpeed = 0;
}

void ForwardDDBot::write() {
    // update "actual" speed values so that they get closer to the "target" values
    // this will eventually get the values to equal, as exponential decay (but
    // with integer division)
    leftActualSpeed = (leftTargetSpeed + leftActualSpeed) / 2;
    rightActualSpeed = (rightTargetSpeed + rightActualSpeed) / 2;

    // write the actual speed values to the motor driver
    setSpeed(leftActualSpeed, rightActualSpeed);
}