#include "header.h"
#include "templates.h"

#include "MainGameFile.h"
#include "NormalEnemy.h"
#include "JPGImage.h"
#include "Bomb.h"

#include "time.h"

#define MAX_OBJECTS 100
#define MAX_ENEMY_COUNT 20
#define ENEMY_SPAWN_TIME 2000

#define MAX_POWERUP_COUNT 2
#define POWERUP_SPAWN_TIME 4000


MainGameFile::MainGameFile(void) : BaseEngine(MAX_OBJECTS)
{
}

MainGameFile::~MainGameFile(void)
{
	delete m_ppDisplayableObjects[0];
	m_ppDisplayableObjects = NULL;
	human = NULL;
}

int MainGameFile::InitialiseObjects(void)
{
	human = new Human(this);

	DrawableObjectsChanged(); 

	// Destroy any existing objects 
	DestroyOldObjects(); 

	// Create an array one element larger than the number of objects that you want. 
	m_ppDisplayableObjects = new DisplayableObject*[MAX_OBJECTS];

	for (int i = 0; i < MAX_OBJECTS; i++)
		m_ppDisplayableObjects[i] = NULL;

	m_ppDisplayableObjects[0] = human;
	m_ppDisplayableObjects[1] = NULL;

	arrayCounter = 1;
	enemyCounter = 0;
	spawnTimeStart = 0;

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

void MainGameFile::UpdateAllObjects(int iCurrentTime)
{
	spawnEnemies(iCurrentTime);

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

			} else if (m_ppDisplayableObjects[i]->isEnemy() == true) {

				m_ppDisplayableObjects[i]->EnemyUpdate(human->GetXCentre(),human->GetYCentre(),human->getWidth());
			}

			if ( m_iDrawableObjectsChanged )
				return; // Abort! Something changed in the array
		}
	}
}

void MainGameFile::spawnEnemies(int iCurrentTime) {

	if (((iCurrentTime - spawnTimeStart) >= ENEMY_SPAWN_TIME) && (enemyCounter <= MAX_ENEMY_COUNT) && (arrayCounter < MAX_OBJECTS)) {

		addEnemy();
		spawnTimeStart = iCurrentTime;
	}
}

void MainGameFile::addEnemy(void) {

	m_ppDisplayableObjects[arrayCounter] = new NormalEnemy(this);
	arrayCounter++;
	enemyCounter++;
}

void MainGameFile::removeObject(int position) {

	delete m_ppDisplayableObjects[position];

	for (position; m_ppDisplayableObjects[position] != NULL; position++) {

		m_ppDisplayableObjects[position] = m_ppDisplayableObjects[(position+1)];
	}

	arrayCounter--;
	enemyCounter--;
}
