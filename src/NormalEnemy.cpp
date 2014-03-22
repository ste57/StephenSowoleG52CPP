#include "header.h" 
#include "templates.h" 

#include "NormalEnemy.h"
#include "JPGImage.h"
#include "math.h"

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

		diff_X = ((diff_X/z) * 2);
		diff_Y = ((diff_Y/z) * 2);

		if (diff_X > 0.5) {

			diff_X = 0.5;
		}

		if (diff_Y > 0.5) {

			diff_Y = 0.5;
		}

		m_iCurrentScreenX += diff_X;
		m_iCurrentScreenY += diff_Y;
	}

	// Ensure that the object gets redrawn on the display, if something changed 
	RedrawObjects();
}
