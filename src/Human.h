#pragma once
#include "displayableobject.h"


class Human :
	public DisplayableObject
{
private:
	bool power, transition;

public:

	void setPower(bool powerSet);
	Human(BaseEngine* pEngine);
	~Human(void);
	void Draw(void);
	void DoUpdate(int iCurrentTime);
	bool isHuman(void);
};

