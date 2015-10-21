#include "StewartPlatform.h"


StewartPlatform::StewartPlatform(): baseJoint{ { } }
									, platformJoint{ { } }
									, legLength{ { } }
									, translation{ }
									, rotation{ }
									, alpha{ }
									, beta{ BETA_ANGLES }
									, servoHorPos { SERVO_ZERO_POSITION }
{
	getPlatformJoints();
}


StewartPlatform::~StewartPlatform()
{
}

void StewartPlatform::getPlatformJoints(){	
	baseJoint[0].x = -PLATFORM_BASE_RADIUS * cos(degToRad(30) - THETA_ANGLE);
	baseJoint[1].x = -PLATFORM_BASE_RADIUS * cos(degToRad(30) - THETA_ANGLE);
	baseJoint[2].x =  PLATFORM_BASE_RADIUS * sin(THETA_ANGLE);
	baseJoint[3].x =  PLATFORM_BASE_RADIUS * cos(degToRad(30) + THETA_ANGLE);
	baseJoint[4].x =  PLATFORM_BASE_RADIUS * cos(degToRad(30) + THETA_ANGLE);
	baseJoint[5].x =  PLATFORM_BASE_RADIUS * sin(THETA_ANGLE);

	baseJoint[0].y = -PLATFORM_BASE_RADIUS * sin(degToRad(30) - THETA_ANGLE);
	baseJoint[1].y =  PLATFORM_BASE_RADIUS * sin(degToRad(30) - THETA_ANGLE);
	baseJoint[2].y =  PLATFORM_BASE_RADIUS * cos(THETA_ANGLE);
	baseJoint[3].y =  PLATFORM_BASE_RADIUS * sin(degToRad(30) + THETA_ANGLE);
	baseJoint[4].y = -PLATFORM_BASE_RADIUS * sin(degToRad(30) + THETA_ANGLE);
	baseJoint[5].y = -PLATFORM_BASE_RADIUS * cos(THETA_ANGLE);

	platformJoint[0].x = -PLATFORM_TOP_RADIUS * sin(degToRad(30) + THETA_R_ANGLE / 2);
	platformJoint[1].x = -PLATFORM_TOP_RADIUS * sin(degToRad(30) + THETA_R_ANGLE / 2);
	platformJoint[2].x = -PLATFORM_TOP_RADIUS * sin(degToRad(30) - THETA_R_ANGLE / 2);
	platformJoint[3].x =  PLATFORM_TOP_RADIUS * cos(THETA_R_ANGLE / 2);
	platformJoint[4].x =  PLATFORM_TOP_RADIUS * cos(THETA_R_ANGLE / 2);	
	platformJoint[5].x = -PLATFORM_TOP_RADIUS * sin(degToRad(30) - THETA_R_ANGLE / 2);

	platformJoint[0].y = -PLATFORM_TOP_RADIUS * cos(degToRad(30) + THETA_R_ANGLE / 2);
	platformJoint[1].y =  PLATFORM_TOP_RADIUS * cos(degToRad(30) + THETA_R_ANGLE / 2);
	platformJoint[2].y =  PLATFORM_TOP_RADIUS * cos(degToRad(30) - THETA_R_ANGLE / 2);
	platformJoint[3].y =  PLATFORM_TOP_RADIUS * sin(THETA_R_ANGLE / 2);
	platformJoint[4].y = -PLATFORM_TOP_RADIUS * sin(THETA_R_ANGLE / 2);
	platformJoint[5].y = -PLATFORM_TOP_RADIUS * cos(degToRad(30) - THETA_R_ANGLE / 2);
}

void StewartPlatform::setTranslation(const point_t pos) {
	translation.x = pos.x;
	translation.y = pos.y;
	translation.z = pos.z + PLATFORM_HEIGHT_DEFAULT;
}

void StewartPlatform::setRotation(const point_t rot) {
	rotation.x = rot.x;
	rotation.y = rot.y;
	rotation.z = rot.z;
}

void StewartPlatform::getRotationMatrix(float rotationMatrix[3][3]){

	float roll = rotation.x;
	float pitch = rotation.y;
	float yaw = rotation.z;

	rotationMatrix[0][0] =  cos(yaw) * cos(pitch);
	rotationMatrix[1][0] = -sin(yaw) * cos(roll) + cos(yaw) * sin(pitch) * sin(roll);
	rotationMatrix[2][0] =  sin(yaw) * sin(roll) + cos(yaw) * cos(roll)  * sin(pitch);
	
	rotationMatrix[0][1] = sin(yaw)  * cos(pitch);
	rotationMatrix[1][1] = cos(yaw)  * cos(roll) + sin(yaw) * sin(pitch) * sin(roll);
	rotationMatrix[2][1] = cos(pitch)* sin(roll);
	
	rotationMatrix[0][2] = -sin(pitch);
	rotationMatrix[1][2] = -cos(yaw)   * sin(roll) + sin(yaw) * sin(pitch) * cos(roll);
	rotationMatrix[2][2] =  cos(pitch) * cos(roll);
}

void StewartPlatform::calcLegLength() {
	float rotMatrix[3][3] = {};

	getRotationMatrix(rotMatrix);

	for (int i = 0; i < 6; i++) {
		legLength[i].x = (rotMatrix[0][0] * platformJoint[i].x) + (rotMatrix[0][1] * platformJoint[i].y) + (rotMatrix[0][2] * platformJoint[i].z);
		legLength[i].y = (rotMatrix[1][0] * platformJoint[i].x) + (rotMatrix[1][1] * platformJoint[i].y) + (rotMatrix[1][2] * platformJoint[i].z);
		legLength[i].z = (rotMatrix[2][0] * platformJoint[i].x) + (rotMatrix[2][1] * platformJoint[i].y) + (rotMatrix[2][2] * platformJoint[i].z);
		
		legLength[i].x += translation.x; 
		legLength[i].y += translation.y; 
		legLength[i].z += translation.z; 
	}
}  

void StewartPlatform::calcAlpha() {
	point_t basePoint, Li;
	double min, max, dist;

	for (int i = 0; i < 6; i++){		
		min = SERVO_MIN; 
		max = SERVO_MAX;
		for (int j = 0; j < 20; j++){
			basePoint.x = LENGTH_SERVO_ARM * cos(alpha[i]) * cos(beta[i]) + baseJoint[i].x;
			basePoint.y = LENGTH_SERVO_ARM * cos(alpha[i]) * sin(beta[i]) + baseJoint[i].y;
			basePoint.z = LENGTH_SERVO_ARM * sin(alpha[i]);

			Li.x = legLength[i].x - basePoint.x;
			Li.y = legLength[i].y - basePoint.y;
			Li.z = legLength[i].z - basePoint.z;

			dist = sqrt(Li.x * Li.x + Li.y * Li.y + Li.z * Li.z);

			if (abs(LENGTH_SERVO_LEG - dist) < 0.01) {
				break;
			}
			
			if (dist < LENGTH_SERVO_LEG) {
				max = alpha[i];
			}
			else {
				min = alpha[i];
			}
			if (max == SERVO_MIN || min == SERVO_MAX) {
				break;
			}
			
			alpha[i] = min + (max - min) / 2;
		}
	}
}

void StewartPlatform::getServoPosition(const point_t transl, const point_t rotat, float servoPos[6]) {
	setTranslation(transl);
	setRotation(rotat);
	calcLegLength();
	calcAlpha();
	calcServoPos(servoPos);
}

void StewartPlatform::calcServoPos(float servoPos[6]) {
	for (int i = 0; i < 6; i++) {
		if (i == INVERSE_SERVO_1 || i == INVERSE_SERVO_2 || i == INVERSE_SERVO_3) {
			servoPos[i] = constrain(servoHorPos[i] - (alpha[i]) *  SERVO_MULT , MIN_SERVO_PULSE, MAX_SERVO_PULSE);
		}
		else {
			servoPos[i] = constrain(servoHorPos[i] + (alpha[i]) *  SERVO_MULT , MIN_SERVO_PULSE, MAX_SERVO_PULSE);
		}
	}
}
