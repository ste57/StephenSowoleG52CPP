#pragma once
#include "displayableobject.h"


class Human :
	public DisplayableObject
{
public:
	Human(BaseEngine* pEngine);
	~Human(void);
	void Draw(void);
	void DoUpdate(int iCurrentTime);
	bool isHuman(void);
	int getWidth(void);
};

