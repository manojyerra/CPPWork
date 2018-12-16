#include "Localize.h"
#include "GameInfo.h"

Localize* Localize::_ref = NULL;

Localize::Localize()
{
	mapStr.Set("Stars", "Sterne");
	mapStr.Set("Time", "Zeit");
	mapStr.Set("Moves", "Bewegt sich");
	mapStr.Set("Unlocked Levels", "Entriegelt ebenen");
	mapStr.Set("High Scores ( All Levels )", "High Scores (alle Ebenen)");
	mapStr.Set("Rank", "Rang");
	mapStr.Set("Name", "Name");
	mapStr.Set("Country", "Land");
	mapStr.Set("Levels Played", "Gespielt Ebenen");
	mapStr.Set("unnamed", "Unbenannt");
	mapStr.Set("New Record", "Neuer besten Partitur");
	mapStr.Set("Best Record", "besten Partitur");
}

Localize::~Localize()
{
}

Localize* Localize::GetInstance()
{
	if(_ref == NULL)
		_ref = new Localize();
	return _ref;
}

void Localize::DeleteInstance()
{
}
