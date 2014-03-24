#pragma once
#include "PowerupProperties.h"
class Bomb :
	public PowerupProperties
{
public:
	Bomb(BaseEngine* pEngine);
	~Bomb(void);
	void Draw(void);

	void humanCollideUpdate(int targetX, int targetY, int radius);
};

