#include "ForwardDDBot.h"
#include <Arduino.h>

ForwardDDBot::ForwardDDBot() {}
ForwardDDBot::~ForwardDDBot() {}

ForwardDDBot::ForwardDDBot(uint8_t maxPWMIn, float adjustmentIn) {
    maxPWM = maxPWMIn;
    adjustment = adjustmentIn;
}

ForwardDDBot::ForwardDDBot(uint8_t directionPinsIn[NUMBER_OF_DIRECTION_PINS], uint8_t PWMPinsIn[NUMBER_OF_PWM_PINS]) {
    for (size_t i = 0; i < NUMBER_OF_DIRECTION_PINS; i++) {
        directionPins[i] = directionPinsIn[i];
    }
    for (size_t i = 0; i < NUMBER_OF_PWM_PINS; i++) {
        PWMPins[i] = PWMPinsIn[i];
    }
}
ForwardDDBot::ForwardDDBot(uint8_t directionPinsIn[NUMBER_OF_DIRECTION_PINS], uint8_t PWMPinsIn[NUMBER_OF_PWM_PINS], uint8_t maxPWMIn, float adjustmentIn) {
    for (size_t i = 0; i < NUMBER_OF_DIRECTION_PINS; i++) {
        directionPins[i] = directionPinsIn[i];
    }
    for (size_t i = 0; i < NUMBER_OF_PWM_PINS; i++) {
        PWMPins[i] = PWMPinsIn[i];
    }

    maxPWM = maxPWMIn;
    adjustment = adjustmentIn;
}

void ForwardDDBot::calculateAdjustedPWM() {
    // this is the value used to "slow down" a motor
    // it is used when we want to turn, but don't want to set the speed of the other motor to 0
    _adjustedPWM = maxPWM * adjustment;
}

void ForwardDDBot::init() {
    setPinModes();
    calculateAdjustedPWM();

    leftActualPWM = maxPWM;
    rightActualPWM = maxPWM;

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