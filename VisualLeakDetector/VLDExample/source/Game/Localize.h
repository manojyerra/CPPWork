#ifndef LOCALIZE_H
#define LOCALIZE_H

#include "MapStr.h"

class Localize
{
private:
	static Localize* _ref;
	MapStr mapStr;
	
	Localize();
	~Localize();

public:
	static Localize* GetInstance();
	static void DeleteInstance();
};

#endif