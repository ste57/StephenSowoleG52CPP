#include "header.h" 
#include "templates.h" 

#include "DemoBObject.h"


DemoBObject::DemoBObject(BaseEngine* pEngine ) 
	: DisplayableObject( pEngine ) 
{ 


	// Current and previous coordinates for the object - set them the same 
	//initially 
	m_iCurrentScreenX = m_iPreviousScreenX = 100; 
	m_iCurrentScreenY = m_iPreviousScreenY = 100; 
	// The object coordinate will be the top left of the object 
	m_iStartDrawPosX = 0; 
	m_iStartDrawPosY = 0; 
	// Record the ball size as both height and width 
	m_iDrawWidth = 100; 
	m_iDrawHeight = 50; 
	// And make it visible 
	SetVisible(true); 


}


DemoBObject::~DemoBObject(void)
{
}


void DemoBObject::Draw(void)
{

	GetEngine()->DrawScreenRectangle( 
		m_iCurrentScreenX, m_iCurrentScreenY, 
		m_iCurrentScreenX + m_iDrawWidth -1, 
		m_iCurrentScreenY + m_iDrawHeight -1, 
		0x00ff00 ); 

	// This will store the position at which the object was drawn 
	// so that the background can be drawn over the top. 
	// This will then remove the object from the screen.

	StoreLastScreenPositionAndUpdateRect(); 
}


void DemoBObject::DoUpdate(int iCurrentTime)
{
	// Change speed if player presses a key 
	if ( GetEngine()->IsKeyPressed( SDLK_UP ) ) 
		m_iCurrentScreenY -= 2; 
	if ( GetEngine()->IsKeyPressed( SDLK_DOWN ) ) 
		m_iCurrentScreenY += 2; 
	if ( GetEngine()->IsKeyPressed( SDLK_LEFT ) ) 
		m_iCurrentScreenX -= 2; 
	if ( GetEngine()->IsKeyPressed( SDLK_RIGHT ) ) 
		m_iCurrentScreenX += 2; 

	if ( m_iCurrentScreenX < 0 ) 
		m_iCurrentScreenX = 0; 
	if ( m_iCurrentScreenX >= GetEngine()->GetScreenWidth() - m_iDrawWidth ) 
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - m_iDrawWidth; 
	if ( m_iCurrentScreenY < 0 ) 
		m_iCurrentScreenY = 0; 
	if ( m_iCurrentScreenY >= GetEngine()->GetScreenHeight() - m_iDrawHeight) 
		m_iCurrentScreenY = GetEngine()->GetScreenHeight() - m_iDrawHeight; 

	// Ensure that the object gets redrawn on the display, if something changed 
	RedrawObjects();
}
