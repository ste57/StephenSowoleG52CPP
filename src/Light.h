#pragma once
#include "powerupproperties.h"
class Light :
	public PowerupProperties
{
public:
	Light(BaseEngine* pEngine);
	~Light(void);

	void Draw(void);
	void collideUpdate(int targetX, int targetY, int radius);
};

