#include "header.h"
#include "templates.h"

#include "MainGameFile.h"
#include "Human.h"
#include "NormalEnemy.h"


MainGameFile::MainGameFile(void) : BaseEngine(0)
{
}


MainGameFile::~MainGameFile(void)
{
}


int MainGameFile::InitialiseObjects(void)
{

	DrawableObjectsChanged(); 

	// Destroy any existing objects 
	DestroyOldObjects(); 

	// Create an array one element larger than the number of objects that you want. 
	m_ppDisplayableObjects = new DisplayableObject*[3]; 

	m_ppDisplayableObjects[0] = new Human(this); 
	m_ppDisplayableObjects[1] = new NormalEnemy(this);
	m_ppDisplayableObjects[2] = NULL; 

	return 0;
}


void MainGameFile::SetupBackgroundBuffer(void)
{

	FillBackground( 0x000000 );
}


void MainGameFile::UpdateAllObjects( int iCurrentTime )
{
	m_iDrawableObjectsChanged = 0;
	if ( m_ppDisplayableObjects != NULL )
	{
		for ( int i = 0 ; m_ppDisplayableObjects[i] != NULL ; i++ )
		{
			if (m_ppDisplayableObjects[i]->isHuman() == true) {

				m_ppDisplayableObjects[i]->DoUpdate(iCurrentTime);

			} else {

				m_ppDisplayableObjects[i]->EnemyUpdate(0,0);
			}

			if ( m_iDrawableObjectsChanged )
				return; // Abort! Something changed in the array
		}
	}
}
