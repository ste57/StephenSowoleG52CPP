#pragma once
#include "EnemyProperties.h"
class NormalEnemy :
	public EnemyProperties
{
public:
	bool isReadyToDelete;

	NormalEnemy(BaseEngine* pEngine);
	~NormalEnemy(void);
	void Draw(void);
	void checkCollisions(int targetX, int targetY, int radius);
	bool readyToDelete(void);
};

