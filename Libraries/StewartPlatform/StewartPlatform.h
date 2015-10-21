/*
* The MIT License (MIT)
*
* Copyright (c) <2015> <Lucas C. Casagrande - https://github.com/elcasagrande>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#ifndef _STEWARTPLATFORM_H
#define _STEWARTPLATFORM_H

#ifndef PI
#define PI 3.14159265359
#endif

#ifndef degToRad
#define degToRad(degree) (degree * PI / 180.0)
#endif
#ifndef radToDeg
#define radToDeg(radians)  ((radians * 180.0) / PI)
#endif


#include <math.h>
#include "Arduino.h"
#include "Config.h"

typedef struct point_s {
	float x;
	float y;
	float z;
} point_t;

class StewartPlatform
{
public:
	StewartPlatform();
	virtual ~StewartPlatform();
	void getServoPosition(const point_t, const point_t, float[6]);
protected:

private:
	const double beta[6];
	const int servoHorPos[6];
	float alpha[6]; 
	point_t baseJoint[6], platformJoint[6], legLength[6];
	point_t translation, rotation;

	void setTranslation(const point_t);
	void setRotation(const point_t);
	void getRotationMatrix(float[3][3]);
	void getPlatformJoints();
	
	void calcLegLength();
	void calcAlpha();
	void calcServoPos(float[6]);

};

#endif // SPLATFORM_H
