#pragma once


#include "RobotLight.h"
#include "Helper/QuadMesh.h"
#include "Classes/Gun.h"

class Level
{
public:
	Level(unsigned int robotlightNumber) {
		Level::lightRobotNum = robotlightNumber;

		
		Level::cameraCenterPosition.x = 0.0f;
		Level::cameraCenterPosition.y = 3.0f;
		Level::cameraCenterPosition.z = Level::groundSize;

		Level::cameraLookAt.x = 0.0;
		Level::cameraLookAt.y = 3.0;
		Level::cameraLookAt.z = 0.0;

		generateLevel();
		float temp = (float)groundSize;
		cameraOffsetZ = 2.0f;
		gun = new Gun(0.0f, 1.0f, temp - cameraOffsetZ);
	}

	void generateGround();

	
	void generateLevel() {
		// Set up ground quad mesh
		generateGround();

		for (int i = 0; i < lightRobotNum; i++) {
			robotLightList.push_back(spawnRobotLight());
			robotLightList[i]->choseTarget(0.0f, groundSize);
		}
	}
	// generate Tree
	
	RobotLight* spawnRobotLight() {
		RobotLight* returnVal = new RobotLight(-20.0f, 0.0f, -50.0f, 0.1f);
		return returnVal;
	}

	// treeGenerateZone
	// RobotGenerateZone


	void update(float dt);
	
	void render();

	~Level() {
		for (int i = 0; i < lightRobotNum; i++) {
			delete robotLightList[i];
		}
		delete groundMesh;
		delete gun;
	}


	unsigned int groundSize = 20;

public:
	Gun* gun;
	VECTOR3D cameraCenterPosition, cameraLookAt;

private:
	unsigned int lightRobotNum;
	std::vector<RobotLight*> robotLightList;

	QuadMesh* groundMesh;

	float cameraOffsetZ;
	VECTOR3D gunPosition;

	
};

