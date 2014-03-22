#pragma once
#include "displayableobject.h"

class DemoBObject : public DisplayableObject
{
public:
	DemoBObject(BaseEngine* pEngine);
	~DemoBObject(void);
	void Draw(void);
	void DoUpdate(int iCurrentTime);
};

