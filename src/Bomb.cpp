#include "header.h" 
#include "templates.h" 
#include "JPGImage.h"

#include "Bomb.h"
#include "Config.h"
#include "math.h"


Bomb::Bomb(BaseEngine* pEngine ) 
	: PowerupProperties( pEngine ) 
{
	// Current and previous coordinates for the object - set them the same 
	//initially
	m_iCurrentScreenX = m_iPreviousScreenX = (rand() % GetEngine()->GetScreenWidth()); 
	m_iCurrentScreenY = m_iPreviousScreenY = (rand() % GetEngine()->GetScreenHeight()); 
	// The object coordinate will be the top left of the object 
	m_iStartDrawPosX = 0; 
	m_iStartDrawPosY = 0;

	setPowerupType(BOMB);

	// And make it visible 
	SetVisible(true); 
}


Bomb::~Bomb(void)
{
}

void Bomb::Draw(void) {

	if (!readyToDelete()) {

		ImageData x;
		x.LoadImage("Images/Powerup/bomb.png");
		x.RenderImageWithMask( GetEngine()->GetForeground(),0,0,
			m_iCurrentScreenX, m_iCurrentScreenY, x.GetWidth(), x.GetHeight()
			);

		m_iDrawWidth = m_iDrawHeight = (float)x.GetWidth();

		StoreLastScreenPositionAndUpdateRect();
	}
}

void Bomb::humanCollideUpdate(int targetX, int targetY, int radius) {

	float diffx = m_iCurrentScreenX - (targetX - m_iDrawWidth/2);
	float diffy = m_iCurrentScreenY - (targetY - m_iDrawHeight/2);
	diffx = pow(diffx, 2);
	diffy = pow(diffy, 2);
	float lengthIntersect = pow((diffx + diffy), 0.5f);

	float distanceBetweenSprites = (radius + m_iDrawWidth) / 2;

	if ( lengthIntersect <= distanceBetweenSprites ) {

		setReadyToDelete(true);
	};
}