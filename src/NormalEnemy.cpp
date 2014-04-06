#include "header.h" 
#include "templates.h" 

#include "NormalEnemy.h"
#include "JPGImage.h"
#include "math.h"

#define MIN_ENEMY_SPEED 1.45
#define MAX_ENEMY_SPPED 1.45//5

NormalEnemy::NormalEnemy(BaseEngine* pEngine ) 
	: EnemyProperties( pEngine )
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

	SetSpeed(RandomFloatBetween(MIN_ENEMY_SPEED, MAX_ENEMY_SPPED));

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

void NormalEnemy::Draw(void)
{
	if (!readyToDelete()) {

		ImageData x;
		x.LoadImage("Images/Enemy/Enemy.png");
		x.RenderImageWithMask( GetEngine()->GetForeground(),0,0,
			m_iCurrentScreenX, m_iCurrentScreenY, x.GetWidth(), x.GetHeight()
			);

		m_iDrawHeight = m_iDrawWidth = x.GetWidth();

		StoreLastScreenPositionAndUpdateRect();
	}
}

void NormalEnemy::checkCollisions(int targetX, int targetY, int radius)
{
	float diffx = m_iCurrentScreenX - (targetX - m_iDrawWidth/2);
	float diffy = m_iCurrentScreenY - (targetY - m_iDrawHeight/2);
	diffx = pow(diffx, 2);
	diffy = pow(diffy, 2);

	float lengthIntersect = pow((diffx + diffy), 0.5f);

	float distanceBetweenSprites = (radius + m_iDrawWidth) / 2;

	if ( lengthIntersect <= distanceBetweenSprites ) {

		setReadyToDelete(true);
	}
}

bool NormalEnemy::isEnemy(void) {

	return true;
}