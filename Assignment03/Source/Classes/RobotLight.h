#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utility>
#include <vector>

#include <iostream>
#include <math.h>

#include <gl/glut.h>
#include "Helper/VECTOR3D.h"


class RobotLight
{
public:
	RobotLight(float pos_x, float pos_y, float pos_z, float walking_speed) {
		Pos.x = pos_x;
		Pos.y = pos_y;
		Pos.z = pos_z;
		walkingSpeed = walking_speed;

		Vel.LoadZero();
	}
	
	void choseTarget(float gunPosX, float gunPosZ) {
		float DirX = gunPosX - Pos.x;
		float DirZ = gunPosZ - Pos.z;

		DirX = DirX / sqrt(pow(DirX, 2) + pow(DirZ, 2));
		DirZ = DirZ / sqrt(pow(DirX, 2) + pow(DirZ, 2));

		Vel.x = DirX * walkingSpeed;
		Vel.z = DirZ * walkingSpeed;

		robotAngleY = (atan2f(DirX, DirZ)/3.14) * 180;
	}

	void update(float dt) {
		Pos += Vel;
	}
	
	void render() {
		drawRobot();
	}
	
	~RobotLight() {
		std::cout << "cleaning up" << std::endl;
	}

	VECTOR3D Pos, Vel;

	float walkingSpeed;

	// Control Robot body rotation on base
	float robotAngleX = 0.0;
	float robotAngleY = 0.0;
	float robotAngleZ = 0.0;

private:
	float robotBodyWidth = 5;
	float robotBodyLength = 5;
	float robotBodyDepth = 5;

	float hipWidth = 2.0;
	float hipLength = 2.0;
	float hipDepth = 3.0;

	float upperArmLength = robotBodyWidth / 2;
	float upperArmWidth = 0.125 * robotBodyWidth;
	float upperArmDepth = upperArmWidth;

	float gunLength = 2 * upperArmLength;
	float gunWidth = upperArmWidth;
	float gunDepth = upperArmWidth;

	float upperLegLength = 0.7 * robotBodyWidth;
	float upperLegWidth = 0.125 * robotBodyWidth;
	float upperLegDepth = upperLegWidth;

	float lowerLegLength = 0.7 * upperLegLength;
	float lowerLegWidth = upperLegWidth;
	float lowerLegDepth = upperLegWidth;

	float stanchionLength = robotBodyLength;
	float stanchionRadius = 0.2 * robotBodyDepth;

	float robotTotalHeight = robotBodyLength + stanchionLength + hipLength + upperLegLength + lowerLegLength;

	//Control robot body spining from hip
	float bodyAngleY = 0.0;
	float bodyAngleX = 0.0;

	// Control arm rotation
	float leftShoulderAngle = 1.0;
	float rightShoulderAngle = 1.0;

	float rightgunAngle = -1.0;
	float leftgunAngle = -1.0;

	//control Leg rotation
	float leftLegAngle = -20.0;
	float rightLegAngle = -20.0;

	float leftKneeAngle = 20.0;
	float rightKneeAngle = 20.0;

	//control Ankle rotation
	float leftAnkleAngle = 0.0;
	float rightAnkleAngle = 0.0;

	//control Hip rotation
	float hipAngleX = 0.0;
	float hipAngleY = 0.0;

	//control Cannon rotation
	float CnAngleR = 0.0;
	float CnAngleL = 0.0;

	GLfloat robotBody_mat_ambient  [4] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat robotBody_mat_specular [4] = { 0.45f,0.55f,0.45f,1.0f };
	GLfloat robotBody_mat_diffuse  [4] = { 0.132f, 0.147f,0.152f,1.0f };
	GLfloat robotBody_mat_shininess[1] = { 32.0F };


	GLfloat robotArm_mat_ambient[4] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
	GLfloat robotArm_mat_diffuse[4] = { 0.1f,0.1f,0.1f,1.0f };
	GLfloat robotArm_mat_specular[4] = { 0.7f, 0.6f, 0.6f, 1.0f };
	GLfloat robotArm_mat_shininess[1] = { 32.0F };

	GLfloat shoulder_mat_ambient[4] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
	GLfloat shoulder_mat_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat shoulder_mat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat shoulder_mat_shininess[1] = { 32.0F };

	GLfloat gun_mat_ambient[4] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
	GLfloat gun_mat_diffuse[4] = { 0.132f, 0.147f,0.152f,1.0f };
	GLfloat gun_mat_specular[4] = { 0.7f, 0.6f, 0.6f, 1.0f };
	GLfloat gun_mat_shininess[1] = { 32.0F };

	GLfloat robotLeg_mat_ambient[4] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
	GLfloat robotLeg_mat_diffuse[4] = { 0.5f,0.0f,0.0f,1.0f };
	GLfloat robotLeg_mat_specular[4] = { 0.7f, 0.6f, 0.6f, 1.0f };
	GLfloat robotLeg_mat_shininess[1] = { 32.0F };

	GLfloat knee_mat_ambient[4] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
	GLfloat knee_mat_diffuse[4] = { 0.5f,0.0f,0.0f,1.0f };
	GLfloat knee_mat_specular[4] = { 0.7f, 0.6f, 0.6f, 1.0f };
	GLfloat knee_mat_shininess[1] = { 32.0f };

	GLfloat robotLowerBody_mat_ambient[4] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat robotLowerBody_mat_diffuse[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat robotLowerBody_mat_specular[4] = { 0.774597f, 0.774597f, 0.774597f, 1.0f };
	GLfloat robotLowerBody_mat_shininess[1] = { 0.8F };


	bool	stop = false;
	bool	pause = false;
	bool	aim = false;
	bool	aimm = false;
	float	spin = false;
	float	temp = 0.0;
	float*	anglePoint = &temp;

	bool step1 = false;
	bool step2 = false;
	bool step3 = false;
	bool step4 = false;
	bool step5 = false;
	bool step6 = false;

	void animationHandle(int param);
	void CannonRev(int param);
	void CannonSpin(int param);
	void walking(int param);
	void walkingRev(int param);



	void drawRobot();
	void drawBody();
	void drawLeftLeg();
	void drawRightLeg();
	void drawLowerBody();
	void drawHip();
	void drawLeftArm();
	void drawRightArm();


	void drawCylinder();

};

