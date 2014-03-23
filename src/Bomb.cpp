#include "header.h" 
#include "templates.h" 
#include "JPGImage.h"

#include "Bomb.h"


Bomb::Bomb(BaseEngine* pEngine ) 
	: DisplayableObject( pEngine ) 
{
	// Current and previous coordinates for the object - set them the same 
	//initially 
	m_iCurrentScreenX = m_iPreviousScreenX = (GetEngine()->GetScreenWidth() / 2); 
	m_iCurrentScreenY = m_iPreviousScreenY = (GetEngine()->GetScreenHeight() / 2); 
	// The object coordinate will be the top left of the object 
	m_iStartDrawPosX = 0; 
	m_iStartDrawPosY = 0;

	// And make it visible 
	SetVisible(true); 
}


Bomb::~Bomb(void)
{
}

void Bomb::Draw(void) {

	ImageData x;
	x.LoadImage("Images/Powerup/bomb.png");
	x.RenderImageWithMask( GetEngine()->GetForeground(),0,0,
		m_iCurrentScreenX, m_iCurrentScreenY, x.GetWidth(), x.GetHeight()
		);

	m_iDrawWidth = m_iDrawHeight = (float)x.GetWidth();

	StoreLastScreenPositionAndUpdateRect();
}

void Bomb::PowerupUpdate(DisplayableObject ** enemyArray) {


}
