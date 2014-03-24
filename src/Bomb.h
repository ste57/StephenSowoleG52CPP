#pragma once
#include "PowerupProperties.h"
class Bomb :
	public PowerupProperties
{

private:
	bool explode;

public:
	Bomb(BaseEngine* pEngine);
	~Bomb(void);
	void Draw(void);

	void collideUpdate(int targetX, int targetY, int radius);
	bool hasExploded(void);
};

