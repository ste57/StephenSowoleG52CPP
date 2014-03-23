#pragma once
#include "displayableobject.h"
class EnemyProperties :
	public DisplayableObject
{
public:
	float speed;

	EnemyProperties(BaseEngine* pEngine);
	~EnemyProperties(void);
	void EnemyUpdate(int targetX, int targetY, int radius);
	void SetSpeed(float speedSet);
	float RandomFloatBetween(float firstNumber, float secondNumber);
	virtual void checkCollisions(int targetX, int targetY, int radius);
};

