/* SpeedTuner
    This example shows how to use the DDBot library to figure out the right values for tuning PWM
   parameters for use with the Forward-biased Differential Drive robot.

    The robot will start with 0 adjustment. It will then increase the adjustment by 0.05, attempt to
   forward for 3 seconds, and then increase the adjustment by 0.05 again. This process repeats until
   the adjustment is 1.0, at which point the robot will stop.

    It will then repeat the process while going backwards, increasing the adjustment from 0 to 1.0
   in 0.05 increments.

    At each stage, it will output the adjustment value and the adjusted PWM to the Serial monitor,
   so that you can determine when it has sufficient PWM to accelerate.

    The circuit:
    * Pin 2 to left motor forward
    * Pin 3 to left motor backward
    * Pin 4 to right motor forward
    * Pin 5 to right motor backward
    * Pin 10 to left motor speed
    * Pin 11 to right motor speed
*/

#include <Arduino.h>
#include <ForwardDDBot.h>

// define the pins used by the motors
uint8_t directionPins[4] = {2, 3, 4, 5};
uint8_t speedPins[2] = {10, 11};

// create an instance of the DDBot class
// this allows you to potentially control multiple robots at once using multiple instances
ForwardDDBot bot(directionPins, speedPins);

void setup() {
    // use the maximum possible PWM value
    bot.maxPWM = 100;

    // set the pin modes for the motor DIO pins
    bot.init();

    // initialize the adjustment value
    bot.adjustment = 0.0;

    // open the Serial connection
    Serial.begin(115200);

    bot.forward();

    // 1 / 0.05 per increment = 20 increments, so we have 20 iterations
    for (int counter = 0; counter < 20; counter++) {
        bot.adjustment += 0.05;
        bot.calculateAdjustedPWM();

        Serial.print("[Forward] Adjustment: ");
        Serial.print(bot.adjustment);
        Serial.print(", Adjusted PWM: ");
        Serial.println(bot.maxPWM * bot.adjustment);

        // we need to update the PWM values to allow the open-loop control to work
        // we do this by calling the write() method 300 times, with a 10 ms delay between each call,
        // which is a total of 3 seconds
        for (int i = 0; i < 300; i++) {
            delay(10);
            bot.write();
        }
    }

    // stop the robot for 5 seconds
    bot.stop();
    delay(5000);

    // reset the adjustment value
    bot.adjustment = 0.0;

    bot.backward();

    // again, we have 20 iterations, for a total of 1.0 adjustment over 3 seconds
    for (int counter = 0; counter < 20; counter++) {
        bot.adjustment += 0.05;
        bot.calculateAdjustedPWM();

        Serial.print("[Backward] Adjustment: ");
        Serial.print(bot.adjustment);
        Serial.print(", Adjusted PWM: ");
        Serial.println(bot.maxPWM * bot.adjustment);

        // again, we need to update the PWM values to allow the open-loop control to work
        // so 300 iterations * 10 ms per iteration = 3 seconds
        for (int i = 0; i < 300; i++) {
            delay(10);
            bot.write();
        }
    }

    bot.stop();
}

void loop() {}