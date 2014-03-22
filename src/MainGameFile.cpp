#include "header.h"
#include "templates.h"

#include "MainGameFile.h"
#include "NormalEnemy.h"
#include "JPGImage.h"

#include "time.h"

#define ENEMY_COUNT 10


MainGameFile::MainGameFile(void) : BaseEngine((ENEMY_COUNT+1))
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
	m_ppDisplayableObjects = new DisplayableObject*[(ENEMY_COUNT + 2)]; 

	m_ppDisplayableObjects[0] = human; 

	for (int i = 1; i < (ENEMY_COUNT + 1); i++) {

		m_ppDisplayableObjects[i] = new NormalEnemy(this);
	}

	m_ppDisplayableObjects[(ENEMY_COUNT + 1)] = NULL; 


	return 0;
}


void MainGameFile::SetupBackgroundBuffer(void)
{
	ImageData x;

	srand(time(NULL));

	switch (rand()%2)
	{

	case 0:
		x.LoadImage("Images/Background/Map1.jpg");
		break;

	case 1:
		x.LoadImage("Images/Background/Map2.jpg");
		break;

	default:
		break;
	}

	x.RenderImage(this->GetBackground(), 0, 0, 0, 0, x.GetWidth(), x.GetHeight());
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
