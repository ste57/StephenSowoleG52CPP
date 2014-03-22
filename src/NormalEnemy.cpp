#include "header.h" 
#include "templates.h" 

#include "NormalEnemy.h"
#include "JPGImage.h"

#define ENEMY_CIRCUMFERENCE 15

NormalEnemy::NormalEnemy(BaseEngine* pEngine ) 
	: DisplayableObject( pEngine ) 
{
	// Current and previous coordinates for the object - set them the same 
	//initially 
	m_iCurrentScreenX = m_iPreviousScreenX = (GetEngine()->GetScreenWidth() / 2); 
	m_iCurrentScreenY = m_iPreviousScreenY = (GetEngine()->GetScreenHeight() / 2); 
	// The object coordinate will be the top left of the object 
	m_iStartDrawPosX = 0; 
	m_iStartDrawPosY = 0; 

	m_iDrawWidth = m_iDrawHeight = ENEMY_CIRCUMFERENCE;

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
		100,100, x.GetWidth(), x.GetHeight()
		);

	StoreLastScreenPositionAndUpdateRect();
}

void NormalEnemy::EnemyUpdate(int targetX, int targetY) {


}
