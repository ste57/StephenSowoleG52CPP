#pragma once
#include "baseengine.h"
#include "Human.h"

class MainGameFile :
	public BaseEngine
{
public:

	int arrayCounter, enemyCounter, powerupCounter, spawnTimeStart, powerupTimeStart;
	Human* human;

	MainGameFile(void);
	~MainGameFile(void);
	int InitialiseObjects(void);
	void SetupBackgroundBuffer(void);
	void UpdateAllObjects( int iCurrentTime );
	void removeObject(int position);
	void spawnEnemies(int iCurrentTime);
	void addEnemy(void);
	void spawnPowerups(int iCurrentTime);
	void addPowerup(void);
};

