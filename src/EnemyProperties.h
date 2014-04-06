#pragma once
#include "displayableobject.h"
class EnemyProperties :
	public DisplayableObject
{
private:
	bool retreat;
	float speed;

public:

	bool isRetreating(void);
	void setRetreat(bool retreatSet);
	EnemyProperties(BaseEngine* pEngine);
	~EnemyProperties(void);
	void EnemyUpdate(int targetX, int targetY, int radius);
	void SetSpeed(float speedSet);
	float RandomFloatBetween(float firstNumber, float secondNumber);
	virtual void checkCollisions(int targetX, int targetY, int radius);
};

