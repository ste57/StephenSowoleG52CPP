#pragma once
#include "baseengine.h"
#include "Human.h"

class MainGameFile :
	public BaseEngine
{
public:
	Human* human;

	MainGameFile(void);
	~MainGameFile(void);
	int InitialiseObjects(void);
	void SetupBackgroundBuffer(void);
	void UpdateAllObjects( int iCurrentTime );
};

