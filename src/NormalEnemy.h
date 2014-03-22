#pragma once
#include "displayableobject.h"
class NormalEnemy :
	public DisplayableObject
{
public:
	NormalEnemy(BaseEngine* pEngine);
	~NormalEnemy(void);
	void Draw(void);
	void EnemyUpdate(int targetX, int targetY);
};

