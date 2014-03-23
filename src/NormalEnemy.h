#pragma once
#include "EnemyProperties.h"
class NormalEnemy :
	public EnemyProperties
{
public:

	NormalEnemy(BaseEngine* pEngine);
	~NormalEnemy(void);
	void Draw(void);
};

