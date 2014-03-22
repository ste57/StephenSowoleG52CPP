#pragma once
#include "baseengine.h"
class MainGameFile :
	public BaseEngine
{
public:
	MainGameFile(void);
	~MainGameFile(void);
	int InitialiseObjects(void);
	void SetupBackgroundBuffer(void);
	void UpdateAllObjects( int iCurrentTime );
};

