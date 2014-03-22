#include "header.h"
#include "templates.h"

#include "DemoAMain.h"
#include "DemoBObject.h" 



DemoAMain::DemoAMain(void) : BaseEngine(6)
{
}


DemoAMain::~DemoAMain(void)
{
}


void DemoAMain::SetupBackgroundBuffer(void)
{
	FillBackground( 0x000000 ); 

	for ( int iX = 0 ; iX < GetScreenWidth() ; iX++ ) 

		for ( int iY = 0 ; iY < GetScreenHeight() ; iY++ ) 

			switch( rand()%100 ) 
		{ 
			case 0: SetBackgroundPixel( iX, iY, 0xFF0000 ); break; 
			case 1: SetBackgroundPixel( iX, iY, 0x00FF00 ); break; 
			case 2: SetBackgroundPixel( iX, iY, 0x0000FF ); break; 
			case 3: SetBackgroundPixel( iX, iY, 0xFFFF00 ); break; 
			case 4: SetBackgroundPixel( iX, iY, 0x00FFFF ); break; 
			case 5: SetBackgroundPixel( iX, iY, 0xFF00FF ); break; 
		} 

}


void DemoAMain::MouseDown(int iButton, int iX, int iY)
{

	printf( "%d %d\n", iX, iY ); 


	if ( iButton == SDL_BUTTON_LEFT ) 
	{ 
		DrawBackgroundRectangle( iX-10, iY-10, iX+10, iY+10, 0xffff00 ); 
		//SetSDLUpdateRectImmediately( iX-10, iY-10, 21, 21 ); 
		Redraw(true); 
	} 
	else if ( iButton == SDL_BUTTON_RIGHT ) 
	{ 
		DrawBackgroundOval( iX-10, iY-10, iX+10, iY+10, 0xff0000 ); 
		//SetSDLUpdateRectImmediately( iX-10, iY-10, 21, 21 ); 
		Redraw(true); 
	} 



}


void DemoAMain::KeyDown(int iKeyCode)
{
	switch( iKeyCode ) 
	{ 
	case SDLK_SPACE: 
		SetupBackgroundBuffer(); 
		Redraw(true); 
		break; 
	} 

}


int DemoAMain::InitialiseObjects(void)
{
	// Record the fact that we are about to change the array - so it doesn't get 
	//used elsewhere without reloading it 
	DrawableObjectsChanged(); 

	// Destroy any existing objects 
	DestroyOldObjects(); 

	// Create an array one element larger than the number of objects that you want. 
	m_ppDisplayableObjects = new DisplayableObject*[2]; 

	// You MUST set the array entry after the last one that you create to NULL, so 
	//that the system knows when to stop. 
	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in 
	//order to work out where the end of the array is. 
	m_ppDisplayableObjects[0] = new DemoBObject(this); 
	m_ppDisplayableObjects[1] = NULL; 

	return 0; 

}
