#include "PowerupProperties.h"


PowerupProperties::PowerupProperties(BaseEngine* pEngine ) 
	: DisplayableObject( pEngine ) 
{

	collideWithHuman = true;
}


PowerupProperties::~PowerupProperties(void)
{
}

void PowerupProperties::setPowerupType(int powerup) {

	powerupType = powerup;
}

int PowerupProperties::getPowerupType(void) {

	return powerupType;
}

void PowerupProperties::setCollideWithHuman(bool humanCollide) {

	collideWithHuman = humanCollide;
}

bool PowerupProperties::canCollideWithHuman(void) {

	return collideWithHuman;
}

void PowerupProperties::humanCollideUpdate(int targetX, int targetY, int radius) {


}