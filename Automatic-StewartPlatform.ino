#include <Config.h>
#include <StewartPlatform.h>
#include <Servo.h>
#include <Fastwire.h>
#include <Wire.h>
#include <I2Cdev.h>

#include "mpu.h"
#define MPU9250


StewartPlatform sp; 
Servo servos[6];
point_t rotation, translation = {};
float servosPos[6] = {0}; 
unsigned int tempo, ret;

void setup() {
    Fastwire::setup(400,0);
    Serial.begin(38400);
    Serial.println("Inicializando");
    
    mympu_open(200);  
    
    servos[0].attach(3, MIN_SERVO_PULSE, MAX_SERVO_PULSE);
    servos[1].attach(5, MIN_SERVO_PULSE, MAX_SERVO_PULSE);
    servos[2].attach(6, MIN_SERVO_PULSE, MAX_SERVO_PULSE);
    servos[3].attach(9, MIN_SERVO_PULSE, MAX_SERVO_PULSE);
    servos[4].attach(10, MIN_SERVO_PULSE, MAX_SERVO_PULSE);
    servos[5].attach(11, MIN_SERVO_PULSE, MAX_SERVO_PULSE);
    
      
    sp.getServoPosition(translation, rotation, servosPos);

    for(int i = 0; i < 6; i++){      
        servos[i].writeMicroseconds(servosPos[i]);
    }

    //Wait the accelerometer stabilize
    tempo = millis();
    while( millis() - tempo < 14000);
}

unsigned int c = 0; //cumulative number of successful MPU/DMP reads

void loop() {
    int ret = mympu_update();
    switch (ret) {
	  case 0: c++; break;
    }

    if (!(c%25)) {
      rotation.x = degToRad(mympu.ypr[1]);
      rotation.y = degToRad(mympu.ypr[2]);
      Serial.print("X: ");
      Serial.print(rotation.x);
      Serial.print("\tY: ");
      Serial.print(rotation.y);
      Serial.println();
    
      sp.getServoPosition(translation, rotation, servosPos);

      for(int i = 0; i < 6; i++){      
          servos[i].writeMicroseconds(servosPos[i]);
      }
    }
}

