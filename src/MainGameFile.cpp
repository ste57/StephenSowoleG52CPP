#include "header.h"
#include "templates.h"

#include "Config.h"

#include "MainGameFile.h"
#include "NormalEnemy.h"
#include "JPGImage.h"
#include "Bomb.h"
#include "Light.h"
#include "Super.h"
#include "PowerupProperties.h"

#include "time.h"

#define MAX_OBJECTS 100
#define MAX_ENEMY_COUNT 5
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
	delete human;
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
	powerupCounter = 0;
	spawnTimeStart = 0;
	powerupTimeStart = 0;
	superPowerCounter = 0;
	lightActive = false;
	superActive = false;
	lifeLost = false;

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
	spawnPowerups(iCurrentTime);

	m_iDrawableObjectsChanged = 0;

//	enemyCounter = 0;

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

				if (!lifeLost) {

					enemyCollision(i);
				}

			} else {

				powerupCollision(i);
			}

			if ( m_iDrawableObjectsChanged )
				return; // Abort! Something changed in the array
		}

		if (superPowerCounter == 0) {

			superPowerCounter = iCurrentTime;
		}

		if (superActive && (iCurrentTime - superPowerCounter) >= SUPER_ACTIVE_TIME*1000) {

			EnemyProperties* b;

			for ( int i = 0 ; m_ppDisplayableObjects[i] != NULL; i++ )
			{
				if (m_ppDisplayableObjects[i]->isEnemy()) {

					b = (EnemyProperties*)m_ppDisplayableObjects[i];
					b->setRetreat(false);
				}
			}

			superActive = false;
			human->setPower(false);

			b = NULL;
			delete b;
		}
	}
}

void MainGameFile::enemyCollision(int position) {

	EnemyProperties* b = (EnemyProperties*)m_ppDisplayableObjects[position];

	if (!lightActive) {

		if (superActive && !b->isRetreating()) {

			b->setRetreat(true);

		}

		if (!b->isRetreating()) {

			b->EnemyUpdate(human->GetXCentre(),human->GetYCentre(),human->getWidth());

			if (b->readyToDelete()) {

				lifeLost = true;
				printf("somewhere new\n");
			}

		} else {

			b->EnemyUpdate(human->GetXCentre(),human->GetYCentre(),human->getWidth());
		}
	}

	b = NULL;
	delete b;
}

void MainGameFile::powerupCollision(int position) {

	PowerupProperties *powerup = (PowerupProperties*)m_ppDisplayableObjects[position];

	switch (powerup->getPowerupType())
	{

	case BOMB:

		if (powerup->canCollideWithHuman()) {

			powerup->collideUpdate(human->GetXCentre(),human->GetYCentre(),human->getWidth());

			if (!(powerup->canCollideWithHuman())) {

				powerupCounter--;
			}

		} else {

			Bomb* b = (Bomb*)powerup;

			if (b->hasExploded()) {

				b->setReadyToDelete(true);
			}

			for ( int i = 0 ; m_ppDisplayableObjects[i] != NULL; i++ )
			{
				if (m_ppDisplayableObjects[i]->isEnemy()) {

					b->collideUpdate(m_ppDisplayableObjects[i]->GetXCentre(),m_ppDisplayableObjects[i]->GetYCentre(),m_ppDisplayableObjects[i]->getWidth());

					if (b->hasExploded()) {

						m_ppDisplayableObjects[i]->EnemyUpdate(b->GetXCentre(),b->GetYCentre(),b->getWidth());	

						//if (m_ppDisplayableObjects[i]->readyToDelete()) {

						//	enemyCounter--;
						//}
					}
				}
			}

			if (b->hasExploded()) {
				GameRender();
			}

			b = NULL;
			delete b;
		}
		break;

	case LIGHT:

		if (powerup->canCollideWithHuman()) {

			powerup->collideUpdate(human->GetXCentre(),human->GetYCentre(),human->getWidth());

			if (!(powerup->canCollideWithHuman())) {

				lightActive = true;
				powerupCounter--;
			}

		} else {

			Light* b = (Light*)powerup;

			for ( int i = 0 ; m_ppDisplayableObjects[i] != NULL; i++ )
			{
				if (m_ppDisplayableObjects[i]->isEnemy()) {

					m_ppDisplayableObjects[i]->EnemyUpdate(b->GetXCentre(),b->GetYCentre(),b->getWidth());

					b->collideUpdate(m_ppDisplayableObjects[i]->GetXCentre(),m_ppDisplayableObjects[i]->GetYCentre(),m_ppDisplayableObjects[i]->getWidth());
				}
			}

			if (b->readyToDelete()) {

				lightActive = false;
			}

			b = NULL;
			delete b;
		}

		break;

	case SUPER:

		if (powerup->canCollideWithHuman()) {

			powerup->collideUpdate(human->GetXCentre(),human->GetYCentre(),human->getWidth());

			if (!(powerup->canCollideWithHuman())) {

				superActive = true;
				human->setPower(true);
				superPowerCounter = 0;
				powerupCounter--;
			}
		}

		break;

	default:
		break;
	}

	powerup = NULL;
	delete powerup;
}

void MainGameFile::spawnPowerups(int iCurrentTime) {

	if (((iCurrentTime - powerupTimeStart) >= POWERUP_SPAWN_TIME) && (powerupCounter < MAX_POWERUP_COUNT) && (arrayCounter < MAX_OBJECTS)) {

		addPowerup();
		powerupTimeStart = iCurrentTime;
	}
}

void MainGameFile::addPowerup(void) {

	switch (rand() % NUMBER_OF_POWERUPS)
	{

	case 0:
		m_ppDisplayableObjects[arrayCounter] = new Bomb(this);
		break;

	case 1:

		if (!lightActive) {

			m_ppDisplayableObjects[arrayCounter] = new Light(this);

		} else {

			m_ppDisplayableObjects[arrayCounter] = new Bomb(this);
		}
		break;

	case 2:
		m_ppDisplayableObjects[arrayCounter] = new Super(this);
		break;

	default:
		break;
	}


	arrayCounter++;
	powerupCounter++;
}

void MainGameFile::spawnEnemies(int iCurrentTime) {

	if (((iCurrentTime - spawnTimeStart) >= ENEMY_SPAWN_TIME) && (enemyCounter < MAX_ENEMY_COUNT) && (arrayCounter < MAX_OBJECTS)) {

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
}
