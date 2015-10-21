/* This is a CONFIG File used to perform the Stewart Calculation  
*  Be sure you replace all this constants to yours Platform values.
*  
*  You can get this values looking your Stewart Platform and from your Servo Datasheet.
*
*/

/* The max e min pulse width from my Servo (TowerPro SG90) Datasheet */
#define MAX_SERVO_PULSE 2200
#define MIN_SERVO_PULSE 700

/* Position of servos mounted in inverse direction */
#define INVERSE_SERVO_1 0
#define INVERSE_SERVO_2 2
#define INVERSE_SERVO_3 4

/* Multiplier used to convert radian to pulses in us */
#define SERVO_MULT ( 400.0/(PI/4.0))

/* The max e min range of Servos in radians */
#define SERVO_MIN degToRad(-80)
#define SERVO_MAX degToRad(80)

/* Here you should put Your Platform Values in millimeters */
/* Here you put the length of your servos arm . */
#define LENGTH_SERVO_ARM 15
/* Here you put the length of your rods length. */
#define LENGTH_SERVO_LEG 120
/* Here you put the default Heigh of your platform. 
 * This value should be close to yours rods length.
*/
#define PLATFORM_HEIGHT_DEFAULT 115
/* Here you put the radius of the top of your platform. */
#define PLATFORM_TOP_RADIUS 45.5
/* Here you put the radius of the base of your platform. */
#define PLATFORM_BASE_RADIUS 67.5
/* Here you put the angle between two servos axis points */
#define THETA_P_ANGLE degToRad(67)
/* Here you put the angle between two platform attachment points */
#define THETA_R_ANGLE degToRad(12)
/* Here you dont need to change*/
#define THETA_ANGLE ((PI/3.0 - THETA_P_ANGLE) / 2.0)
/* Here you put the pulses of each of yours servos respective to their position in horizontal */
#define SERVO_ZERO_POSITION 1550, 1450, 1350, 1600, 1500, 1600
/* Here you put the rotation of servo arms in respect to axis X */
#define BETA_ANGLES PI / 2, -PI / 2, -PI / 6, 5 * PI / 6, -5 * PI / 6, PI / 6