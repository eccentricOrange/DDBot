# Differential Drive Robot

This library provides an interface to easily control a [differential wheeled robot](https://en.wikipedia.org/wiki/Differential_wheeled_robot) using an Arduino-compatible microcontroller.

The expectation is that you have an even number of motors, with one half on either side of a structure that looks like a rover or a car. You then control the direction the robot moves in by controlling which motors turn on and in which direction. For example, if the left motors spin forward and the right motors spin backwards, the robot will rotate clockwise.

Check out [line-follower-std](https://github.com/eccentricOrange/line-follower-std) and [line-follower-smooth](https://github.com/eccentricOrange/line-follower-smooth) for two examples where this library is used in a project.

## Overview of the library
In general, using this library involves the following steps. Don't worry if you don't understand the specific methods yet, we'll look at them in more detail later.

1.  Create an instance of the relevant class. You can either set the pin numbers arrays property of the instances, or pass them as arguments to the constructor

    ```cpp
    // either
    DDBot bot();

    // or
    uint8_t directionPins[4] = {2, 3, 4, 5};
    DDBot bot(directionPins);
    ```

2.  Initialize the pin modes and any other settings. You just have to call the function (usually in `void setup()`).

    ```cpp
    void setup() {
        bot.setPinModes();
    }
    ```

3.  Now you're all set! You can now call the direction and speed methods wherever like (`void loop()`, `void setup()`, or one of your own functions).

    ```cpp
    bot.forward();
    delay(2000);

    bot.forward(255);
    delay(1000);


## Types of robots offered by the library
There are classes for two kinds of robots included in this library.

*   **Standard Differential Drive Robot**

    This is a normal differential drive robot, with motors on each side. It is what we described above: the direction is controlled by controlling which motors turn on and in which direction.

    The class for this is `DDBot`.

*   **Forward-biased Differential Drive Robot**

    The physical robot for this can be the same as a standard differential drive robot, but the control is different. In this case, the robot's motor's are *always set to move forward*. The direction is controlled by varying the speeds of the motors. In certain cases (like line followers), it is expected that this library leads to more less jerky motion of the robot.

    The class for this is `ForwardDDBot`.

## Standard Differential Drive Robot
1.  The first step for using this library is to create an instance of the `DDBot` class.

    In doing so, you can communicate to the library which pins you'll use for the motors.

    This is based on two arrays, each of type `uint8_t` (basically just an integer).
    *   **`directionPins[4]`**
        
        This sets the pins for the direction of the motors. The first two pins are for the left motors, and the last two are for the right motors. The first pin in each pair is for the first motor, and the second is for the second motor. These can be any DIO pins (though it's recommended to avoid pins 0 and 1, as they are used for serial communication with your computer).

        **This is a compulsory argument and you must specify this before setting the pin modes or using the direction/speed methods.**

    *  **`PWMPins[2]`**
        
        This sets the pins for the speed of the motors. The first pin is for the left motors, and the second is for the right motors. These pins must be PWM pins (i.e. pins 3, 5, 6, 9, 10, or 11 on an Arduino Uno). You can check the [Arduino Reference for `analogWrite()`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/) to see which pins are PWM pins on your board.

        **This is an optional argument. If you don't specify this, the library provide only the direction control and ignores the speed control.**

    The easiest way to set these pins is to pass them as an array to the constructor. For example, if you want to use pins 2, 3, 4, and 5 for the direction pins, and pins 10 and 11 for the speed pins, you can do the following:

    ```cpp
    uint8_t directionPins[4] = {2, 3, 4, 5};
    uint8_t speedPins[2] = {10, 11};

    DDBot bot(directionPins, speedPins);
    ```

    You can also set the pin arrays after creating the instance. For example, if you want to use pins 2, 3, 4, and 5 for the direction pins, and pins 10 and 11 for the speed pins, you can do the following:

    ```cpp
    DDBot bot();

    uint8_t directionPins[4] = {2, 3, 4, 5};
    uint8_t speedPins[2] = {10, 11};

    for (int i = 0; i < 4; i++) {
        bot.directionPins[i] = directionPins[i];
    }

    for (int i = 0; i < 2; i++) {
        bot.PWMPins[i] = speedPins[i];
    }
    ```

2.  Now that you've created an instance of the `DDBot` class, you can set the pin modes. This is done by calling the `setPinModes()` method. This method takes no arguments and returns nothing.

    This method must be called before you can use the direction and speed methods.

    If you have not specified the speed pins, this method will only set the direction pins to `OUTPUT` mode. If you have specified the speed pins, this method will set both the direction and speed pins to `OUTPUT` mode.

    ```cpp
    void setup() {
        bot.setPinModes();
    }
    ```

3.  Now you're all set! You can now call the direction and speed methods wherever like (`void loop()`, `void setup()`, or one of your own functions).

    Let's look at the different methods you can call.

    *   **`setSpeed()`**
        
        This method sets the speed of the motors. The speeds are specified as integers between 0 and 255, where 0 is stopped and 255 is full speed (this follows from how the `analogWrite()` function works).

        If you pass in only one argument, it will set the speed of both motors to that value. If you pass in two arguments, it will set the speed of the left motors to the first argument, and the speed of the right motors to the second argument.

        **Note:** If you have not specified the speed pins, this method will do nothing.

    *   **`writeDirections()`**

        This method lets you directly set which motor spins backwards and which motors spins forwards. You can use this if you want to add more complex control to your robot.

        The arguments correspond to the pins required by something like an L293D or an L298 H-bridge. See [How to Mechatronics' tutorial](https://howtomechatronics.com/tutorials/arduino/arduino-dc-motor-control-tutorial-l298n-pwm-h-bridge/) for more information.

        Here is how this function is declared, so you can see the parameters:

        ```cpp
        void writeDirections(bool leftForward, bool leftBackward, bool rightForward, bool rightBackward);
        ```

        You can optionally pass in none, one, or two additional arguments for speed control. Just like the `setSpeed()` method, if you pass in only one argument, it will set the speed of both motors to that value. If you pass in two arguments, it will set the speed of the left motors to the first argument, and the speed of the right motors to the second argument.

    *   **The direction methods**

        There are several methods for controlling the direction of the robot, and all of them follow the same pattern.

        You can optionally pass in none, one, or two additional arguments for speed control. Just like the `setSpeed()` method, if you pass in only one argument, it will set the speed of both motors to that value. If you pass in two arguments, it will set the speed of the left motors to the first argument, and the speed of the right motors to the second argument.

        The following methods are available, and their purpose can be inferred from their name.

        *   `forward()`
        *   `backward()`
        *   `left()`  (this has a forward bias)
        *   `right()`  (this has a forward bias)
        *   `clockwise()`  (the robot rotates in place)
        *   `counterclockwise()` (the robot rotates in place)

    *   **`stop()`**

        This method stops the robot by setting all direction pins to `LOW`.

        It does not affect the PWM output pins, so if you have specified the speed pins, the motors will resume spinning at the last speed you set.

## Forward Differential Drive Robot
One of the key concepts behind this type of robot is that it relies on closed-loop control. If you specify a change in speed or direction, it will not be set immediately. Instead, it will be set gradually over time. This is done to prevent the robot from jerking around.

So, when you call a direction method, it just sets two variables internally. You must then call another method in each iteration of your `loop()` function to update the actual values being written to the robot.

1.  The first step for using this library is to create an instance of the `ForwardDDBot` class.

    Just like the `DDBot` class, you can pass in the direction and speed pins to the constructor. However, the `ForwardDDBot` class has a two additional arguments.
    
    **These additional arguments and the `PWMPins` argument are both compulsory.**

    *  **maxPWM**
        
        This sets the maximum PWM value that will be written to the motors. This is useful if you want to limit the maximum speed of the robot. This value must be between 0 and 255, following from how the `analogWrite()` function works.

    *   **adjustment**

        This is a value between 0 and 1 that will be multiplied by the PWM value to produce a "slow" PWM value. This is used to steer the robot without setting any motor to 0 and thus not stopping the robot.

    You set the direction and speed pins just like you would with the `DDBot` class. A similar philosophy is used for the additional `maxPWM` and `adjustment` arguments.

    ```cpp
    uint8_t directionPins[4] = {2, 3, 4, 5};
    uint8_t speedPins[2] = {10, 11};

    ForwardDDBot bot(directionPins, speedPins, 255, 0.5);
    ```

    **You should always call the `calculateAdjustedPWM()` method after you set the `adjustment` or `maxPWM` values, after calling the `init()` method.**

2.  Now that you've created an instance of the `ForwardDDBot` class, you can set the pin modes and the initial speed and direction. This is done by calling the `init()` method. This method takes no arguments and returns nothing.

    This method must be called before you can use the direction and speed methods.

    This method would set the pin modes, set the "slow" PWM value, and set the direction to forward. It also initializes the motors to full speed, to help with the initial acceleration.

    ```cpp
    void setup() {
        bot.init();
    }
    ```

3.  Now you're all set! You can now call the direction and speed methods in a continuous loop.

    Though this inherits all the methods from the `DDBot` class, only four implement closed-loop control. These are `left()`, `right()`, `centre()`, and `stop()`. They don't take any argument.

    Remember that you must call the `write()` method in each iteration of your `loop()` function to update the actual values being written to the robot.

    Here is a simple example. We'll assume that we get the user's input from some `getUserCommand()` function as a single character. Then depending on the character, we'll set the direction of the root.

    ```cpp
    void loop() {
        switch (getUserCommand()) {
            'C':
                bot.centre();
                break;

            'L':
                bot.left();
                break;

            'R':
                bot.right();
                break;

            default:
                bot.stop();
                break;
        }


        bot.write();

        // Wait between loop iterations to allow the motors to smoothly change or maintain their direction.
        delay(10);
    }
    ```

