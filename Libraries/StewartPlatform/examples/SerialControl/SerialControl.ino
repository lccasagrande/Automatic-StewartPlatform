/* This is a example of how to control a Stewart Platform via Serial command. 
 * 
 * You already have to set up the values in Config.h to your Platform Values.
 * 
 * Remember to configure yours Servos Pins in Setup. 
 * Here we are using all PWMs Pin from Arduino UNO.
*/

#include <Config.h>
#include <StewartPlatform.h>
#include <Servo.h>

Servo servos[6];
float servosPosition[6];
StewartPlatform sp;

//Init rotation and translation with zeros
point_t rotation = {};
point_t translation = {};

//Hold the values readed from Serial
float* values = new float[6];

void setup() {
  Serial.begin(38400);
  Serial.println("Init...");

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

  //Send a message like this: 30,0,20,0,0,0
  // 30,0,20,0,0,0 - X, Y, Z, GX, GY, GZ
  if(Serial.available() >= 11)
  {
    String rsp = Serial.readStringUntil('\n');
    values = getValuesFromString(rsp);
    translation.x = values[0];
    translation.y = values[1];
    translation.z = values[2];
    rotation.x = values[3];
    rotation.y = values[4];
    rotation.z = values[5];
  }

  // Get the Servos Position.
  sp.getServoPosition(translation, rotation, servosPosition); 

  // Set servos to the desired position.  
  for(int i = 0; i < 6; i++){      
    servos[i].writeMicroseconds(servosPosition[i]);
  }  
}

// Here we extract the values from the string received.
float* getValuesFromString(String rsp){
  int lastIndex = 0, j = 0, i;
  float values[6];
  for(i = 0; i < rsp.length(); i++){
    if(rsp.substring(i, i+1) == ","){
      values[j++] = (rsp.substring(lastIndex, i)).toFloat(); 
      lastIndex = i + 1;
      
      if( j == 6) break;
    }
  }
  values[j] = (rsp.substring(lastIndex, i)).toFloat(); 
  return values;
}
