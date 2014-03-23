#include "header.h" 
#include "templates.h" 

#include "Human.h"
#include "JPGImage.h"

#define HUMAN_SPEED 6

Human::Human(BaseEngine* pEngine ) 
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


Human::~Human(void)
{
}


void Human::Draw(void)
{
	ImageData x;
	x.LoadImage("Images/Human/human.png");
	x.RenderImageWithMask( GetEngine()->GetForeground(),0,0,
		m_iCurrentScreenX, m_iCurrentScreenY, x.GetWidth(), x.GetHeight()
		);

	m_iDrawWidth = m_iDrawHeight = (float)x.GetWidth();

	StoreLastScreenPositionAndUpdateRect();
}

bool Human::isHuman(void)
{

	return true;
}

int Human::getWidth(void)
{

	return m_iDrawWidth;
}


void Human::DoUpdate(int iCurrentTime)
{
	if ( GetEngine()->IsKeyPressed( SDLK_UP ) ) 
		m_iCurrentScreenY -= HUMAN_SPEED; 
	if ( GetEngine()->IsKeyPressed( SDLK_DOWN ) ) 
		m_iCurrentScreenY += HUMAN_SPEED; 
	if ( GetEngine()->IsKeyPressed( SDLK_LEFT ) ) 
		m_iCurrentScreenX -= HUMAN_SPEED; 
	if ( GetEngine()->IsKeyPressed( SDLK_RIGHT ) ) 
		m_iCurrentScreenX += HUMAN_SPEED; 

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