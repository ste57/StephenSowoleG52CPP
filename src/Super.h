#pragma once
#include "powerupproperties.h"
class Super :
	public PowerupProperties
{
public:
	Super(BaseEngine* pEngine);
	~Super(void);
	void Draw(void);

	void collideUpdate(int targetX, int targetY, int radius);
};

