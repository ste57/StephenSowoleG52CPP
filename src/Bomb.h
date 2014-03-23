#pragma once
#include "displayableobject.h"
class Bomb :
	public DisplayableObject
{
public:
	Bomb(BaseEngine* pEngine);
	~Bomb(void);
	void Draw(void);
	void PowerupUpdate(DisplayableObject ** enemyArray);
};

