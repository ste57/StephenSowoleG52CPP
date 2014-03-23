#include "EnemyProperties.h"
#include "math.h"


EnemyProperties::EnemyProperties (BaseEngine* pEngine ) 
	: DisplayableObject( pEngine ) 
{

}


EnemyProperties::~EnemyProperties(void)
{


}

void EnemyProperties::EnemyUpdate(int targetX, int targetY) {

	float diff_X = ((targetX - m_iDrawWidth/2) - m_iCurrentScreenX);
	float diff_Y = ((targetY - m_iDrawHeight/2) - m_iCurrentScreenY);
	float z = pow((pow(diff_X,2) + pow(diff_Y,2)), 0.5f);

	if (diff_X != 0 || diff_Y != 0) {

		m_iCurrentScreenX += ((diff_X/z) * speed);
		m_iCurrentScreenY += ((diff_Y/z) * speed);
	}

	checkCollisions(targetX, targetY);

	// Ensure that the object gets redrawn on the display, if something changed 
	RedrawObjects();
}

void EnemyProperties::checkCollisions(int targetX, int targetY)
{



}

void EnemyProperties::SetSpeed(float speedSet)
{
	speed = speedSet;
}


float EnemyProperties::RandomFloatBetween(float firstNumber, float secondNumber)
{
	float diff = secondNumber - firstNumber;
	return (((float) (rand() % ((unsigned)RAND_MAX + 1)) / RAND_MAX) * diff) + firstNumber;
}
