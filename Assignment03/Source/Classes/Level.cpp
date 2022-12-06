#include <vector>

//#include "QuadMesh.h"
#include "Level.h"


void Level::update(float dt) {
	for (int i = 0; i < lightRobotNum; i++) {
		robotLightList[i]->update(dt);
	}
	if (!gun->update(dt)) {
		Level::cameraLookAt.x = gun->barrelPos.x;
		Level::cameraLookAt.y = gun->barrelPos.y + cameraOffsetZ;
		Level::cameraLookAt.z = gun->barrelPos.z;
	}

}


void Level::render() {

	glPushMatrix();
		gun->render();
		
		for (int i = 0; i < lightRobotNum; i++) {
			robotLightList[i]->render();
		}

		glPushMatrix();
			//glScalef(5.0f, 5.0f, 5.0f);
			groundMesh->DrawMesh(groundSize);
		glPopMatrix();
	glPopMatrix();

}


void Level::generateGround() {
	VECTOR3D origin = VECTOR3D(-16.0f, 0.0f, 16.0f);
	VECTOR3D dir1v = VECTOR3D(1.0f, 0.0f, 0.0f);
	VECTOR3D dir2v = VECTOR3D(0.0f, 0.0f, -1.0f);
	groundMesh = new QuadMesh(Level::groundSize, 32.0);
	groundMesh->InitMesh(Level::groundSize, origin, 32.0, 32.0, dir1v, dir2v);

	VECTOR3D ambient = VECTOR3D(0.0f, 0.05f, 0.0f);
	VECTOR3D diffuse = VECTOR3D(0.4f, 0.8f, 0.4f);
	VECTOR3D specular = VECTOR3D(0.04f, 0.04f, 0.04f);
	float shininess = 0.2f;
	groundMesh->SetMaterial(ambient, diffuse, specular, shininess);
}


