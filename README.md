# Automatic-StewartPlatformAutomation

A project to automatically control a Stewart Platform using an IMU sensor.

- **Libraries** - contains the library to perform the Stewart Calculations to control the platform.
- **Stewart_Platform_Templates** - contains the template used in the manufacturing of the platform . It was adapted from [Thomas KENT](https://github.com/ThomasKNR) design to fit our components.
- **Automatic-StewartPlatform.ino** - contains the code used to control the Stewart Platform automatically.


Our thanks to [ThomasKNR](https://github.com/ThomasKNR)  and [thiagohersan](https://github.com/thiagohersan) work!!!

## Problem

Ships are constantly moving over the sea due to ocean waves . Because of that, pilots can have difficulties to land in those ships. in some occasions, when those ships are going through a storm the difficulty raises significantly.

A good approach to solve this problem would be using a Stewart Platform controlled automatically to predict the ship's movements
and keep the platform stable for the pilot to land. Using an IMU sensor to predict the ship movements, the platform could be controlled
and stay stable regardless of the ship movement.

## Goal

Develop a Automatic, low cost, Stewart Platform using an IMU Sensor and 6 rotary micro servos.

## Materials
```
6x Micro Servos 9g - We used the MicroServos TowerPro SG90.
6x OUTBACK Bamboo 12" Kebab Skewers - You can buy a threaded rod if you want.
12x Hollow Balls Traxxas-Tra5347 .
1x IMU Sensor - We used a MPU9250.
1x Stewart Platform Base.	
1x Stewart Platform Top. 	
1x Arduino UNO.
Alot of Screws...
```

The templates for cutting can be found in this repository or in [here](https://github.com/ThomasKNR).

## How to control a Stewart Platform
After mounting the Platform itself you will have to do some math calculations to control it coordinately. 

To perform all those calculations we made a library that can be found in Libraries.

This library is used at this project at all, but if you want to do another project you can still use the library to perform the Stewart calculations.

To help you with this, we recommend taking a look into those links:
* [Here](http://www.instructables.com/id/Stewart-Platform/?ALLSTEPS) you can find a very detailed paper explaining how to do all the calculations.
* [Here](http://www.instructables.com/id/Stewart-Platform/?ALLSTEPS) you can find a little bit about the calculations, how to build your own platform and how to find the platform's values to perform the calculations..

All the math involved can be found in those links. We used them as reference to build our library and the platform itself.

Just to sum up, all the calculations involve three steps:
* Calculate the virtual leg length to move the platform to the desired position.
* Calculate the servo's angle to get the virtual leg length.
* Calculate the servo's pulse to get the desired angle.

We only could do this because of ThomasKNR and thiagohersan work. So, again, our thanks to [ThomasKNR](https://github.com/ThomasKNR).  and [thiagohersan](https://github.com/thiagohersan). 

## Using just the Library
To only use the library you only have to set up the `Config.h` and include the library on your `Arduino IDE`.
You will have to put all the platform's values and servo's configurations inside of `Config.h`.

There is some examples showing how to call the API inside the library, and how to get the platform's values to set up in `Config.h`.

Be sure you have your Stewart Platform made and all the six servos are working.

If you want, you can use the library in a simulator too. We used the thiagohersan Processing Simulator to validate the SP Calculations. 

`This has been tested using Arduino 1.6.5 libraries and a Arduino Uno.`

## Using the whole Project

To use the whole project you will first need to include some Libraries:
* `MPU9250 Library` - It is a library to get the Yaw, Pitch and Roll from an MPU9250 sensor. Can be found in [here](https://github.com/rpicopter/ArduinoMotionSensorExample "MPU9250 Library").
* `I2Cdev.h` - It is a library used in MPU9250. Can be found in [here](https://github.com/rpicopter/ArduinoMotionSensorExample "I2Cdev Library").
* `Fastwire.h` - It is a library used in MPU9250. Can be found in [here](  https://github.com/landis/arduino/tree/master/libraries/Fastwire "Fastwire Library").
* `Wire.h` - It is a library used in MPU9250. Can be found on your Arduino IDE.
* `Servo.h` - It is a library to control arduino servos. Can be found on your Arduino IDE.
* `StewartPlatform.h` - It is a library to perform all the Stewart Platform Control Maths. Can be found in this repository.

After installing the dependencies, you just have to set up the `Config.h` inside the StewartPlatform library to your platform's values. After that, just run `Automatic-RotaryStewartPlatform.ino` on your Arduino.

Information about how to get the platform values can be found in `Config.h` or in [here](http://www.instructables.com/id/Arduino-controlled-Rotary-Stewart-Platform/?ALLSTEPS).

## License 

The content of this project itself is licensed under the MIT license.
