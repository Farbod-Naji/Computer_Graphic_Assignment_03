#include "RobotLight.h"


// helper funtion
void RobotLight::drawCylinder() {
	glPushMatrix();
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	gluDisk(gluNewQuadric(), 0.0, 1.0, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 1.0f);
	gluDisk(gluNewQuadric(), 0.0, 1.0, 20, 10);
	glPopMatrix();

	glPushMatrix();
	gluCylinder(gluNewQuadric(), 1.0, 1.0, 1.0, 20, 10);
	glPopMatrix();
}

// ------------------------------------------------------------

void RobotLight::drawRobot()
{

	//--------Rotate the whole RobotLight-------------
	glPushMatrix();
		glTranslatef(Pos.x, Pos.y + robotTotalHeight/2, Pos.z);

		glRotatef(robotAngleY, 0.0, 1.0, 0.0);	// spin robot on Y. 
		glRotatef(robotAngleX, 1.0, 0.0, 0.0);	// spin robot on X
		glRotatef(robotAngleZ, 0.0, 0.0, 1.0);	// spin robot on Z

		//--------rotate the upper body---------------
		glPushMatrix();
			glRotatef(bodyAngleX, 0.0, 1.0, 0.0);
			glRotatef(bodyAngleY, 1.0, 0.0, 0.0);
			drawBody();
			drawLeftArm();
			drawRightArm();

			//---------rotate the lower body --------------
				glPushMatrix();
				glRotatef(hipAngleX, 1.0, 0.0, 0);
				glRotatef(hipAngleY, 0, 1.0, 0);
				drawLeftLeg();
				drawRightLeg();
				drawHip();
				drawLowerBody();
				glPopMatrix();
			glPopMatrix();

		glPopMatrix();

	glPopMatrix();
}


void RobotLight::drawBody()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, robotBody_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotBody_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotBody_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotBody_mat_shininess);

	// for upper torso
	glPushMatrix();

	glTranslatef(0.0, 2.5, 0.0);
	glutSolidSphere(3.0, 15, 15);

	glPushMatrix();
	glTranslatef(0.0, 0.0, 1.5);
	glutSolidSphere(2.0, 15, 15);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1.5);
	glutSolidSphere(1.0, 15, 15);
	glPopMatrix();
	glPopMatrix();
}

void RobotLight::drawHip() {

	glMaterialfv(GL_FRONT, GL_AMBIENT, robotBody_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotBody_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotBody_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotBody_mat_shininess);

	// for lower hip
	glPushMatrix();
	glTranslatef(0.0f, -(robotBodyLength / 2), 0.0f);
	glScalef(2.0, 1.0, 1.0);
	glutSolidCube(1.0);

	glPopMatrix();
}

void RobotLight::drawLeftArm()
{
	glPushMatrix();
	glTranslatef((0.5 * robotBodyWidth + upperArmWidth), 0.0, 0.0);

	glRotatef(leftShoulderAngle, 1.0, 0.0, 0.0);
	glRotatef(-25, 0.0, 0.0, -1.0);

	// shoulder joint
	glPushMatrix();
	glutSolidSphere(1, 15, 15);
	glPopMatrix();

	// upper arm
	glPushMatrix();
	glTranslatef(0.0, -upperArmLength / 2, 0.0);
	glScalef(upperArmWidth, upperArmLength, upperArmDepth);
	glutSolidCube(1);
	glPopMatrix();

	// !Elbow Down!
	glPushMatrix();

	glTranslatef(0.0, -upperArmLength, 0.0);
	glRotatef(25, 0.0, 0.0, -1.0);
	glRotatef(leftgunAngle, 1.0, 0.0, 0.0);


	//Elbow joint
	glPushMatrix();
	glutSolidSphere(0.6, 15, 15);
	glPopMatrix();

	// forarm
	glPushMatrix();
	glTranslatef(0.0, -gunLength / 2, 0.0);
	glScalef(gunWidth, gunLength, gunDepth);
	glutSolidCube(1.0);
	glPopMatrix();



	//////-----------------------shield on arm
	//glPushMatrix();
	//// rotate gun
	//	glTranslatef(-(0.5 * robotBodyWidth + 0.5 * upperArmWidth), -(0.5 * upperArmLength), 0.0);
	//	//glRotatef(leftgunAngle, 1.0, 0.0, 0.0);
	//	glTranslatef((0.5 * robotBodyWidth + 0.5 * upperArmWidth), (0.5 * upperArmLength), 0.0);

	//	// Position gun with respect to parent arm 
	//	glTranslatef(0.5, -(0.5 * upperArmLength + gunLength/2), 0.0);

	//	// build lower Arm
	//	glScalef(0.1, gunLength + 1, gunDepth + 2);
	//	glutSolidCube(1.0);
	//	glPopMatrix();

	//--------------------------Gun------------
	glPushMatrix();
	glRotatef(CnAngleL, 0.0, 1.0, 0.0);
	glTranslatef(-(gunWidth / 2), -gunLength / 2, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	/*glRotatef(leftgunAngle, 1.0, 0.0, 0.0);*/
	glPushMatrix();
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 3.0f, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 3.0f);
	gluDisk(gluNewQuadric(), 0.0f, 1.0f, 20, 10);
	glPushMatrix();
	gluCylinder(gluNewQuadric(), 0.3f, 0.3f, 3.0f, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 3.0f);
	gluDisk(gluNewQuadric(), 0.0f, 0.3f, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180.0f, 0.0f, 2.0f, 0.0f);
	gluDisk(gluNewQuadric(), 0.0f, 0.3f, 20, 10);
	glPushMatrix();
	glTranslatef(0.0f, -0.5f, -2.0f);
	gluCylinder(gluNewQuadric(), 0.2f, 0.2f, 2.0f, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180.0f, 0.0f, 2.0f, 0.0f);
	gluDisk(gluNewQuadric(), 0.0f, 0.2f, 20, 10);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glRotatef(180.0f, 0.0f, 2.0f, 0.0f);
	gluDisk(gluNewQuadric(), 0.0f, 1.0f, 20, 10);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}
void RobotLight::drawRightArm()
{
	glPushMatrix();
	// 2.5 to corrrect a miss alignment
	glTranslatef(-(0.5 * robotBodyWidth + upperArmWidth), 2.5, 0.0);

	glRotatef(rightShoulderAngle, 1.0, 0.0, 0.0);
	glRotatef(-25, 0.0, 0.0, 1.0);

	// shoulder joint
	glPushMatrix();
	glutSolidSphere(1, 15, 15);
	glPopMatrix();

	// upper arm
	glPushMatrix();
	glTranslatef(0.0, -upperArmLength / 2, 0.0);
	glScalef(upperArmWidth, upperArmLength, upperArmDepth);
	glutSolidCube(1);
	glPopMatrix();

	// !Elbow Down!
	glPushMatrix();

	glTranslatef(0.0, -upperArmLength, 0.0);
	glRotatef(25, 0.0, 0.0, 1.0);
	glRotatef(rightgunAngle, 1.0, 0.0, 0.0);


	//Elbow joint
	glPushMatrix();
	glutSolidSphere(0.6, 15, 15);
	glPopMatrix();

	// forarm
	glPushMatrix();
	glTranslatef(0.0, -gunLength / 2, 0.0);
	glScalef(gunWidth, gunLength, gunDepth);
	glutSolidCube(1.0);
	glPopMatrix();
	//--------------------------Gun------------
	glPushMatrix();
	glRotatef(CnAngleR, 0.0, 1.0, 0.0);
	glTranslatef((gunWidth / 2), -gunLength / 2, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glPushMatrix();
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 3.0f, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 3.0f);
	gluDisk(gluNewQuadric(), 0.0f, 1.0f, 20, 10);
	glPushMatrix();
	gluCylinder(gluNewQuadric(), 0.3f, 0.3f, 3.0f, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 3.0f);
	gluDisk(gluNewQuadric(), 0.0f, 0.3f, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180.0f, 0.0f, 2.0f, 0.0f);
	gluDisk(gluNewQuadric(), 0.0f, 0.3f, 20, 10);
	glPushMatrix();
	glTranslatef(0.0f, -0.5f, -2.0f);
	gluCylinder(gluNewQuadric(), 0.2f, 0.2f, 2.0f, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180.0f, 0.0f, 2.0f, 0.0f);
	gluDisk(gluNewQuadric(), 0.0f, 0.2f, 20, 10);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glRotatef(180.0f, 0.0f, 2.0f, 0.0f);
	gluDisk(gluNewQuadric(), 0.0f, 1.0f, 20, 10);
	glPopMatrix();
	glPopMatrix();


	//////-----------------------shield on arm
	//	glPushMatrix();
	//		// rotate gun
	//		glTranslatef((0.5 * robotBodyWidth + 0.5 * upperArmWidth + gunWidth/2), -(0.5 * upperArmLength), 0.0);
	//		//glRotatef(leftgunAngle, 1.0, 0.0, 0.0);
	//		glTranslatef(-(0.5 * robotBodyWidth + 0.5 * upperArmWidth), (0.5 * upperArmLength), 0.0);

	//		// Position gun with respect to parent arm 
	//		glTranslatef(-0.5, -(0.5 * upperArmLength + gunLength / 2), 0.0);

	//		// build lower Arm
	//		glScalef(0.1, gunLength + 1, gunDepth + 2);
	//		glutSolidCube(1.0);
	//		glPopMatrix();
	//		glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}




void RobotLight::drawLowerBody()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, robotLowerBody_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotLowerBody_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotLowerBody_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotLowerBody_mat_shininess);

	glPushMatrix();
	// Position waist and base with respect to body
	glTranslatef(0, -(robotBodyLength) / 2, 0.0); // this will be done last
	glScalef(stanchionRadius / 2, stanchionLength / 2, stanchionRadius / 2);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0, 1.0, 1.0, 20, 10);
	glPopMatrix();

}

void RobotLight::drawLeftLeg()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, robotLeg_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotLeg_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotLeg_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotLeg_mat_shininess);

	glPushMatrix();
	glTranslatef(-(hipWidth + lowerLegWidth) / 2, -(robotBodyLength) / 2, 0);
	glRotatef(leftLegAngle, 1.0, 0.0, 0.0);

	//-----------hip joint-----------------
	glPushMatrix();
	glutSolidSphere(0.5, 15, 15);
	glPopMatrix();
	//----------- upper leg -----------------
	glPushMatrix();
	glTranslatef(0.0, -upperLegLength / 2, 0.0);
	glPushMatrix();
	glScalef(upperLegWidth, upperLegLength, upperLegDepth);
	glutSolidCube(1.0);
	glPopMatrix();

	//-------------knee joinnt -----------
	glPushMatrix();
	glTranslatef(0.0, -upperLegLength / 2, 0.0);
	glRotatef(leftKneeAngle, 1.0, 0.0, 0.0);
	glutSolidSphere(0.6, 15, 15);
	//---------knee down (lowerLeg) --------
	glPushMatrix();
	glTranslatef(0.0, -lowerLegLength / 2, 0.0);
	glPushMatrix();
	glScalef(lowerLegWidth, lowerLegLength, lowerLegDepth);
	glutSolidCube(1.0);
	glPopMatrix();
	//--------ankle joint -----------
	glPushMatrix();
	glTranslatef(0.0, -(lowerLegLength / 2), 0.0);
	glRotatef(leftAnkleAngle, 1.0, 0.0, 0.0);
	glutSolidSphere(0.6, 15, 15);
	//-------- foot ---------------
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.6);
	glScalef(1.0, 0.5, 2.0);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();



	glPopMatrix();
	glPopMatrix();
}
void RobotLight::drawRightLeg()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, robotLeg_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotLeg_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotLeg_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotLeg_mat_shininess);

	glPushMatrix();
	glTranslatef((hipWidth + lowerLegWidth) / 2, -(robotBodyLength) / 2, 0);
	glRotatef(rightLegAngle, 1.0, 0.0, 0.0);

	//-----------hip joint-----------------
	glPushMatrix();
	glutSolidSphere(0.5, 15, 15);
	glPopMatrix();
	//----------- upper leg -----------------
	glPushMatrix();
	glTranslatef(0.0, -upperLegLength / 2, 0.0);
	glPushMatrix();
	glScalef(upperLegWidth, upperLegLength, upperLegDepth);
	glutSolidCube(1.0);
	glPopMatrix();
	//-------------knee joinnt -----------
	glPushMatrix();
	glTranslatef(0.0, -upperLegLength / 2, 0.0);
	glRotatef(rightKneeAngle, 1.0, 0.0, 0.0);
	glutSolidSphere(0.6, 15, 15);
	//---------knee down (lowerLeg) --------
	glPushMatrix();
	glTranslatef(0.0, -lowerLegLength / 2, 0.0);
	glPushMatrix();
	glScalef(lowerLegWidth, lowerLegLength, lowerLegDepth);
	glutSolidCube(1.0);
	glPopMatrix();
	//--------ankle joint -----------
	glPushMatrix();
	glTranslatef(0.0, -(lowerLegLength / 2), 0.0);
	glRotatef(rightAnkleAngle, 1.0, 0.0, 0.0);
	glutSolidSphere(0.6, 15, 15);
	//-------- foot ---------------
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.6);
	glScalef(1.0, 0.5, 2.0);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();



	glPopMatrix();
	glPopMatrix();
}









//void RobotLight::walking(int param) {
//
//	if (!step1) { // left step
//		if (rightLegAngle > -20.0) {
//			rightLegAngle -= 1.0;
//			glutPostRedisplay();
//			glutTimerFunc(30, walking, 0.0);
//		}
//		if (rightLegAngle <= -20.0) {
//			rightLegAngle -= 1.0;
//			rightKneeAngle += 1.0;
//			rightAnkleAngle -= 0.5;
//			glutPostRedisplay();
//			glutTimerFunc(30, walking, 0.0);
//		}
//
//		if (rightLegAngle <= -75.0) {
//			if (rightKneeAngle >= 45.0) {
//				if (rightAnkleAngle <= -5.0) {
//					step1 = true;
//				}
//			}
//		}
//	}
//	else if (!step2) {
//		rightKneeAngle -= 1.0;
//		rightAnkleAngle += 1.0;
//		if (rightKneeAngle == 20.0) {
//			if (rightAnkleAngle >= 0.0) {
//
//				step2 = true;
//
//			}
//		}
//		glutPostRedisplay();
//		glutTimerFunc(30, walking, 0.0);
//	}
//	else if (!step3) {
//		if (rightLegAngle >= -75.0) {
//			rightLegAngle += 1.0;
//			rightAnkleAngle -= 0.5;
//			if (rightLegAngle == -20.0) {
//				if (rightAnkleAngle >= 0.0) {
//					step3 = true;
//				}
//			}
//			glutPostRedisplay();
//			glutTimerFunc(30, walking, 0.0);
//		}
//	}
//	//---------------------------------------------------------------------
//	else if (!step4) { // right step
//		if (leftLegAngle > -20.0) {
//			leftLegAngle -= 1.0;
//			glutPostRedisplay();
//			glutTimerFunc(30, walking, 0.0);
//		}
//		if (leftLegAngle <= -20.0) {
//			leftLegAngle -= 1.0;
//			leftKneeAngle += 1.0;
//			leftAnkleAngle -= 0.5;
//			glutPostRedisplay();
//			glutTimerFunc(30, walking, 0.0);
//		}
//
//		if (leftLegAngle <= -75.0) {
//			if (leftKneeAngle >= 45.0) {
//				if (leftAnkleAngle <= -5.0) {
//					step4 = true;
//				}
//			}
//		}
//	}
//	else if (!step5) {
//		leftKneeAngle -= 1.0;
//		leftAnkleAngle += 1.0;
//		if (leftKneeAngle == 20.0) {
//			if (leftAnkleAngle >= 0.0) {
//
//				step5 = true;
//
//			}
//		}
//		glutPostRedisplay();
//		glutTimerFunc(30, walking, 0.0);
//	}
//	else if (!step6) {
//		if (leftLegAngle >= -75.0) {
//			leftLegAngle += 1.0;
//			leftAnkleAngle -= 0.5;
//			if (leftLegAngle == -20.0) {
//				if (leftAnkleAngle >= 0.0) {
//
//
//					step6 = true;
//					step1 = false;
//					step2 = false;
//					step3 = false;
//					step4 = false;
//					step5 = false;
//					step6 = false;
//				}
//
//			}
//			glutPostRedisplay();
//			glutTimerFunc(30, walking, 0.0);
//		}
//	}
//
//
//}
//
//
//void RobotLight::walkingRev(int param) {
//	if (!pause)
//	{
//		if (!stop) {
//
//			if (rightLegAngle > -20.0) {
//				rightLegAngle -= 1.0;
//				glutPostRedisplay();
//				glutTimerFunc(30, walkingRev, 0.0);
//			}
//			else if (rightLegAngle < -20.0) {
//				rightLegAngle += 1.0;
//				glutPostRedisplay();
//				glutTimerFunc(30, walkingRev, 0.0);
//			}
//			if (rightKneeAngle > 20.0)
//			{
//				rightKneeAngle -= 1.0;
//				glutPostRedisplay();
//				glutTimerFunc(30, walkingRev, 0.0);
//			}
//			else if (rightKneeAngle < 20.0) {
//				rightKneeAngle += 1.0;
//				glutPostRedisplay();
//				glutTimerFunc(30, walkingRev, 0.0);
//			}
//			if (rightAnkleAngle < 0.0)
//			{
//				rightAnkleAngle += 1.0;
//				glutPostRedisplay();
//				glutTimerFunc(30, walkingRev, 0.0);
//			}
//			else if (rightAnkleAngle > 0.0)
//			{
//				rightAnkleAngle -= 1.0;
//				glutPostRedisplay();
//				glutTimerFunc(30, walkingRev, 0.0);
//				stop = true;
//			}
//
//
//		}
//
//		glutPostRedisplay();
//		glutTimerFunc(30, walkingRev, 0.0);
//	}
//}
//
//void RobotLight::animationHandle(int param)
//{
//	if (!stop) {
//		if (!pause)
//		{
//			if (rightShoulderAngle <= 1) {
//				(rightShoulderAngle -= 1);
//				glutPostRedisplay();
//
//				if (rightShoulderAngle == -90.0) {
//					(rightgunAngle += 1);
//					glutPostRedisplay();
//
//					if (rightgunAngle = 0.0) {
//						pause = true;
//					}
//				}
//			}
//			if (leftShoulderAngle <= 1) {
//				(leftShoulderAngle -= 1);
//				glutPostRedisplay();
//
//				if (leftShoulderAngle == -90.0) {
//					(leftgunAngle += 1);
//					glutPostRedisplay();
//
//					if (leftgunAngle = 0.0) {
//						pause = true;
//					}
//
//					pause = true;
//
//				}
//			}
//			else if (rightShoulderAngle > -25) {
//				(rightShoulderAngle -= 1.0);
//				glutPostRedisplay();
//
//				if (rightShoulderAngle == -90.0) {
//					(rightgunAngle += 1.0);
//					glutPostRedisplay();
//
//					if (rightgunAngle = 0.0) {
//						pause = true;
//					}
//				}
//			}
//			else if (leftShoulderAngle > -25) {
//				(leftShoulderAngle -= 1.0);
//				glutPostRedisplay();
//
//				if (leftShoulderAngle == -90.0) {
//					(leftgunAngle += 1.0);
//					glutPostRedisplay();
//
//					if (leftgunAngle = 0.0) {
//						pause = true;
//					}
//				}
//			}
//		}
//		CnAngleL += 5.0;
//		CnAngleR -= 5.0;
//		glutPostRedisplay();
//		glutTimerFunc(10, animationHandle, 0.0);
//
//	}
//}
//
//void RobotLight::CannonRev(int param) {
//	if (!aim) {
//		stop = true;
//		CnAngleL = 0.0;
//		CnAngleR = 0.0;
//		if (rightShoulderAngle < 0.0) {
//			rightShoulderAngle += 1.0;
//			if (rightShoulderAngle == 0.0) {
//				glutPostRedisplay();
//				aim = true;
//			}
//		}
//		else if (rightShoulderAngle > 0.0) {
//			rightShoulderAngle -= 1.0;
//			if (rightShoulderAngle == 0.0) {
//				glutPostRedisplay();
//				aim = true;
//			}
//		}
//		glutPostRedisplay();
//		glutTimerFunc(30, CannonRev, 0.0);
//	}
//	if (!aimm) {
//		if (leftShoulderAngle < 0.0) {
//			leftShoulderAngle += 1.0;
//			if (leftShoulderAngle == 0.0) {
//				glutPostRedisplay();
//				aim = true;
//			}
//		}
//		else if (leftShoulderAngle > 0.0) {
//			leftShoulderAngle -= 1.0;
//			if (leftShoulderAngle == 0.0) {
//				glutPostRedisplay();
//				aim = true;
//			}
//		}
//	}
//
//}
//
//void RobotLight::CannonSpin(int param) {
//	if (!stop) {
//		CnAngleL += 5.0;
//		CnAngleR -= 5.0;
//	}
//	glutPostRedisplay();
//	glutTimerFunc(10, CannonSpin, 0.0);
//}
