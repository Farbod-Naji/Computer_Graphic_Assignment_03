#pragma once
#include <iostream>
#define M_PI 3.14
#include "Helper/VECTOR3D.h"

// how to setup gun controls
// where to save bullet array
// 

class Gun
{
public:
	Gun(float x, float y, float z){
		gunPos.x = x;
		gunPos.y = y;
		gunPos.z = z;

		recalculateBarrel();
	}

	bool update(float dt);

	void render();

	~Gun();
	


	void gunTurnY(float dy) {
		gunTurned = true;

		gunRotation.y -= dy;

		if (gunRotation.y < gunLeftLimit) {
			gunRotation.y = gunLeftLimit;
		}

		else if (gunRotation.y > gunRightLimit) {
			gunRotation.y = gunRightLimit;
		}
		recalculateBarrel();
	}

	void gunTurnX(float dx) {
		gunTurned = true;

		gunRotation.x -= dx;

		if (gunRotation.x < gunUpperLimit) {
			gunRotation.x = gunUpperLimit;
		}

		else if (gunRotation.x > gunLowerLimit) {
			gunRotation.x = gunLowerLimit;
		}
		recalculateBarrel();
	}


	//void gunTurnRight(float dy) {
	//	gunTurned = true;
	//	gunRotation.y -= dy;
	//
	//	if (gunRotation.y < gunLeftLimit) {
	//		gunRotation.y = gunLeftLimit;
	//	}
	//}

	//void gunTurnLeft(float dy) {
	//	gunTurned = true;
	//	gunRotation.y += dy;
	//
	//	if (gunRotation.y > gunRightLimit) {
	//		gunRotation.y = gunRightLimit;
	//	}
	//}

	//void gunTurnUp(float dx) {
	//	gunTurned = true;
	//	gunRotation.x -= dx;
	//	if (gunRotation.x < gunUpperLimit) {
	//		gunRotation.x = gunUpperLimit;
	//	}
	//}

	//void gunTurnDown(float dx) {
	//	gunTurned = true;
	//	gunRotation.x += dx;
	//	if (gunRotation.x > gunLowerLimit) {
	//		gunRotation.x = gunLowerLimit;
	//	}
	//}
private:
	void recalculateBarrel() {
		barrelPos.LoadZero();
		barrelPos.z -= gunLength;
		
		VECTOR3D returnVal;
		returnVal = rotateAroundY(barrelPos.x, barrelPos.z, gunRotation.y);
		barrelPos.x = returnVal.x;
		barrelPos.z = returnVal.z;
		
		returnVal = rotateAroundX(barrelPos.y, barrelPos.z, gunRotation.x);
		barrelPos.y = returnVal.y;
		barrelPos.z = returnVal.z;

		barrelPos += gunPos;

	}


	VECTOR3D rotateAroundY(double x, double z, double theta)
	{
		VECTOR3D newVector;

		newVector.x =  cos(theta / 180 * M_PI) * x + sin(theta / 180.0 * M_PI) * z;
		newVector.z = -sin(theta / 180 * M_PI) * x + cos(theta / 180.0 * M_PI) * z;
		return newVector;
	}

	VECTOR3D rotateAroundX(double y, double z, double theta)
	{
		VECTOR3D newVector;

		newVector.y =  cos(theta / 180 * M_PI) * y + sin(theta / 180.0 * M_PI) * z;
		newVector.z = -sin(theta / 180 * M_PI) * y + cos(theta / 180.0 * M_PI) * z;

		return newVector;
	}

public:
	VECTOR3D gunPos;
	VECTOR3D gunRotation;

	VECTOR3D barrelPos;

private:
	float robotBody_mat_ambient[4] = { 0.0f,0.0f,0.0f,1.0f };
	float robotBody_mat_specular[4] = { 0.45f,0.55f,0.45f,1.0f };
	float robotBody_mat_diffuse[4] = { 0.132f, 0.147f,0.152f,1.0f };
	float robotBody_mat_shininess[1] = { 32.0F };

	void drawGun();
	void drawCylinder();

	float gunUpperLimit = -20.0f;
	float gunLowerLimit = 0.0f;
	float gunLeftLimit = -30.0f;
	float gunRightLimit = 30.0f;



	//VECTOR3D bulletVelocity;

	bool gunTurned = false;

	float gunTurningAngle = 0.0;
	float gunTurningSpeed = 1.7f;

	float gunSize = 0.5f;

	float gunWidth = gunSize * (4 / 5.0f);
	float gunLength = gunSize * 14.0;
	float gunDepth = gunSize * (4 / 5.0f);
};

