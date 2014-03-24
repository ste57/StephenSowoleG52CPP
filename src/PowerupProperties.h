#pragma once
#include "displayableobject.h"
class PowerupProperties :
	public DisplayableObject
{

private:

	int powerupType;
	bool collideWithHuman;

public:

	PowerupProperties(BaseEngine* pEngine);
	~PowerupProperties(void);
	virtual int getPowerupType(void);
	virtual void setPowerupType(int powerup);
	virtual bool canCollideWithHuman(void);
	virtual void setCollideWithHuman(bool humanCollide);
	virtual void collideUpdate(int targetX, int targetY, int radius);
};

