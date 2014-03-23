#pragma once
#include "displayableobject.h"
class NormalEnemy :
	public DisplayableObject
{
public:

	float speed;

	NormalEnemy(BaseEngine* pEngine);
	~NormalEnemy(void);
	void Draw(void);
	void EnemyUpdate(int targetX, int targetY);
	float RandomFloatBetween(float firstNumber, float secondNumber);
};

