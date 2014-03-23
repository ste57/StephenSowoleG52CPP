#include "header.h" 
#include "templates.h" 

#include "NormalEnemy.h"
#include "JPGImage.h"
#include "math.h"

#define MIN_ENEMY_SPEED 1.7
#define MAX_ENEMY_SPPED 2.0//5

NormalEnemy::NormalEnemy(BaseEngine* pEngine ) 
	: DisplayableObject( pEngine ) 
{
	// Current and previous coordinates for the object - set them the same 
	//initially 

	int xVal, yVal;

	switch (rand()%4)
	{
	case 0:
		xVal = - (m_iDrawWidth/2);
		yVal = rand() % GetEngine()->GetScreenHeight();
		break;

	case 1:	
		xVal = rand() % GetEngine()->GetScreenWidth();
		yVal = - (m_iDrawHeight/2);
		break;

	case 2:
		xVal = rand() % GetEngine()->GetScreenWidth();
		yVal = GetEngine()->GetScreenHeight() + (m_iDrawHeight/2);
		break;

	case 3:
		xVal = GetEngine()->GetScreenWidth() + (m_iDrawWidth/2);
		yVal = rand() % GetEngine()->GetScreenHeight();
		break;

	default:
		break;
	}

	speed = RandomFloatBetween(MIN_ENEMY_SPEED, MAX_ENEMY_SPPED);
	printf("speed = %f\n", speed);

	m_iCurrentScreenX = m_iPreviousScreenX = xVal; 
	m_iCurrentScreenY = m_iPreviousScreenY = yVal; 
	// The object coordinate will be the top left of the object 

	m_iStartDrawPosX = 0; 
	m_iStartDrawPosY = 0;

	// And make it visible 
	SetVisible(true); 
}


NormalEnemy::~NormalEnemy(void)
{
}

float NormalEnemy::RandomFloatBetween(float firstNumber, float secondNumber)
{
	float diff = secondNumber - firstNumber;
	return (((float) (rand() % ((unsigned)RAND_MAX + 1)) / RAND_MAX) * diff) + firstNumber;
}


void NormalEnemy::Draw(void)
{
	ImageData x;
	x.LoadImage("Images/Enemy/Enemy.png");
	x.RenderImageWithMask( GetEngine()->GetForeground(),0,0,
		m_iCurrentScreenX, m_iCurrentScreenY, x.GetWidth(), x.GetHeight()
		);

	m_iDrawWidth = m_iDrawHeight = x.GetWidth(); 

	StoreLastScreenPositionAndUpdateRect();
}

void NormalEnemy::EnemyUpdate(int targetX, int targetY) {

	float diff_X = ((targetX - m_iDrawWidth/2) - m_iCurrentScreenX);
	float diff_Y = ((targetY - m_iDrawHeight/2) - m_iCurrentScreenY);
	float z = pow((pow(diff_X,2) + pow(diff_Y,2)), 0.5f);

	if (diff_X != 0 || diff_Y != 0) {

		m_iCurrentScreenX += ((diff_X/z) * speed);
		m_iCurrentScreenY += ((diff_Y/z) * speed);
	}

	// Ensure that the object gets redrawn on the display, if something changed 
	RedrawObjects();
}
