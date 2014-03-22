#include "header.h"
#include "templates.h"

#include "MainGameFile.h"
#include "NormalEnemy.h"

#define ENEMY_COUNT 10


MainGameFile::MainGameFile(void) : BaseEngine(0)
{
}


MainGameFile::~MainGameFile(void)
{
}


int MainGameFile::InitialiseObjects(void)
{
	human = new Human(this);

	DrawableObjectsChanged(); 

	// Destroy any existing objects 
	DestroyOldObjects(); 

	// Create an array one element larger than the number of objects that you want. 
	m_ppDisplayableObjects = new DisplayableObject*[ENEMY_COUNT + 1]; 

	m_ppDisplayableObjects[0] = human; 

	for (int i = 1; i < ENEMY_COUNT; i++) {
		
		m_ppDisplayableObjects[i] = new NormalEnemy(this);
	}

	m_ppDisplayableObjects[ENEMY_COUNT] = NULL; 


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

				m_ppDisplayableObjects[i]->EnemyUpdate(human->GetXCentre(),human->GetYCentre());
			}

			if ( m_iDrawableObjectsChanged )
				return; // Abort! Something changed in the array
		}
	}
}
