/*  This is a Basic Example of How to control a Stewart Platform 
 *  using the StewartPlatform Library.
 *  
 *  Setting up the translation and rotation you will have the desired movements.
 *  
 *  Make sure you have all your servos conected, and
 *  remeber to configure yours servos Pins in Setup and yours
 *  platform values in Config.h
 */

#include <Config.h>
#include <StewartPlatform.h>
#include <Servo.h>

StewartPlatform sp;
Servo servos[6];
float servosPosition[6];

point_t translation = {}, rotation = {};

void setup() {

  /* MIN_SERVO_PULSE AND MAX_SERVO_PULSE are defined in CONFIG.H */
  /* Attach yours Servos Pins here */
  servos[0].attach(3, MIN_SERVO_PULSE, MAX_SERVO_PULSE);
  servos[1].attach(5, MIN_SERVO_PULSE, MAX_SERVO_PULSE);
  servos[2].attach(6, MIN_SERVO_PULSE, MAX_SERVO_PULSE);
  servos[3].attach(9, MIN_SERVO_PULSE, MAX_SERVO_PULSE);
  servos[4].attach(10, MIN_SERVO_PULSE, MAX_SERVO_PULSE);
  servos[5].attach(11, MIN_SERVO_PULSE, MAX_SERVO_PULSE);
}

void loop() {  
  sp.getServoPosition(translation, rotation, servosPosition);
  
  for(int i = 0; i < 6; i++){      
    servos[i].writeMicroseconds(servosPosition[i]);
  }  
}