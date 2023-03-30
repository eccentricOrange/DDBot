/* Square
    This example shows how to use the DDBot library to make the robot move in a square.

    The robot will move forward for 2 seconds, then turn right for 1 second, then move forward for 2
   seconds, then turn right for 1 second, and so on.

    The circuit:
    * Pin 2 to left motor forward
    * Pin 3 to left motor backward
    * Pin 4 to right motor forward
    * Pin 5 to right motor backward
    * Pin 10 to left motor speed
    * Pin 11 to right motor speed
*/

#include <Arduino.h>
#include <DDBot.h>

// define the pins used by the motors
uint8_t directionPins[4] = {2, 3, 4, 5};
uint8_t speedPins[2] = {10, 11};

// create an instance of the DDBot class
// this allows you to potentially control multiple robots at once using multiple instances
DDBot bot(directionPins, speedPins);

void setup() {
    // set the pin modes for the motor DIO pins
    bot.setPinModes();
}

void loop() {
    // move forward with full speed for 2 seconds
    bot.forward(100);
    delay(2000);

    // turn right with full speed for 1 second
    bot.right(100);
    delay(1000);
}