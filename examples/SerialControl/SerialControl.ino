/* Serial Communication Example
    This example shows how to use the DDBot class to control a robot using serial communication.

    Here are the keys corresponding to the commands.
    * 'W' - move forward
    * 'S' - move backward
    * 'A' - turn left
    * 'D' - turn right
    * 'Q' - stop
    * 'J' - rotate counter-clockwise
    * 'L' - rotate clockwise

    You may additionally specify a number after the command to control the speed of the motors. This
    number should be between 0 and 100. For example, 'W 50' will move the robot forward at half
    speed.

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

// create a buffer to store the serial data
// byte 1 - command
// byte 2 - space
// bytes 3-5 - speed
// byte 6 - null terminator
const size_t bufferSize = 6;
char buffer[bufferSize];

// create a variable to store the number of bytes read from the serial connection
size_t lengthRead = 0;

// parse the user input and execute the relevant command
// returns true if the command was valid, false otherwise
bool parseDirectionCommand(char* userInput, DDBot bot) {

    // pull out the first character of the user input
    char command = userInput[0];

    switch (command) {
        case 'W':
            bot.forward();
            break;

        case 'S':
            bot.backward();
            break;

        case 'A':
            bot.left();
            break;

        case 'D':
            bot.right();
            break;

        case 'Q':
            bot.stop();
            break;

        case 'J':
            bot.counterClockwise();
            break;

        case 'L':
            bot.clockwise();
            break;

        default:
            return false;
            break;
    }

    return true;
}

// parse the user input and set the speed of the motors
// returns true if the speed was valid, false otherwise
bool parseSpeedCommand(char* userInput, size_t lengthOfCommands, DDBot bot) {
    
    // if the user specified a speed, parse it
    // the speed should be the third character and beyond
    if (lengthOfCommands > 2) {

        // convert the speed to an integer
        int speed = atoi(&userInput[2]);

        // if the speed is valid, set it
        if (speed >= 0 && speed <= 100) {
            bot.setSpeed(speed);
            return true;
        }

        return false;
    }

    return true;
}

void setup() {
    // set the pin modes for the motor DIO pins
    bot.setPinModes();

    // initialize the serial connection
    Serial.begin(9600);
}

void loop() {

    if (Serial.available()) {

        // read the serial data into the buffer (just a place to store the data)
        // the data should be terminated by a newline character ('\n')
        // the buffer should be one byte smaller than the size of the buffer (for the null
        // terminator)
        lengthRead = Serial.readBytesUntil('\n', buffer, bufferSize - 1);

        // add the null terminator to the end of the buffer
        // this prevents bugs like reading past the end of the buffer
        buffer[lengthRead] = NULL;

        // if the user entered a command, parse it
        if (
            lengthRead > 0
            && parseDirectionCommand(buffer, bot)
            && parseSpeedCommand(buffer, lengthRead, bot)
        ) {

            // if the command was valid, send it to the serial port, possibly for another robot
            Serial.println(buffer);
        }
    }

    // wait a bit before checking the serial connection again
    delay(10);
}