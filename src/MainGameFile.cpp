#include "header.h"
#include "templates.h"

#include "MainGameFile.h"
#include "NormalEnemy.h"
#include "JPGImage.h"

#include "time.h"

#define MAX_OBJECTS 100

#define ENEMY_COUNT 10


MainGameFile::MainGameFile(void) : BaseEngine(MAX_OBJECTS)
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
	m_ppDisplayableObjects = new DisplayableObject*[MAX_OBJECTS];

	for (int i = 0; i < MAX_OBJECTS; i++) {

		m_ppDisplayableObjects[i] = NULL;
	}

	m_ppDisplayableObjects[0] = human;
	//m_ppDisplayableObjects[1] = NULL;

	for (int i = 1; i <= ENEMY_COUNT; i++) {

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
			if ( m_ppDisplayableObjects[i]->readyToDelete()) {
				
				removeObject(i);
				continue;
			}

			if (m_ppDisplayableObjects[i]->isHuman() == true) {

				m_ppDisplayableObjects[i]->DoUpdate(iCurrentTime);

			} else {

				m_ppDisplayableObjects[i]->EnemyUpdate(human->GetXCentre(),human->GetYCentre(),human->getWidth());
			}

			if ( m_iDrawableObjectsChanged )
				return; // Abort! Something changed in the array
		}
	}
}

void MainGameFile::removeObject(int position) {

	delete m_ppDisplayableObjects[position];

	for (position; m_ppDisplayableObjects[position] != NULL; position++) {

		m_ppDisplayableObjects[position] = m_ppDisplayableObjects[(position+1)];
	}
}
