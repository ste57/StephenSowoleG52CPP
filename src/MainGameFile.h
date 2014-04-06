#pragma once
#include "baseengine.h"
#include "Human.h"

class MainGameFile :
	public BaseEngine
{

private:
	bool lightActive, superActive, lifeLost;
	int arrayCounter, enemyCounter, powerupCounter, superPowerCounter, spawnTimeStart, powerupTimeStart;
	Human* human;

public:

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
	void powerupCollision(int position);
	void enemyCollision(int position);
};

